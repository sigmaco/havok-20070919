/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/Memory/FreeList/hkFreeListMemory.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

#ifdef HK_DEBUG

static HK_FORCE_INLINE void MEMORY_SCRUB(void* ptr, int val, int nbytes)
{
    // if you want to use NAN: for (int i =0; i < nbytes/4; i++) ((int*)ptr)[i] = 0x7FC00000;
    if (ptr)
    {
        hkString::memSet(ptr, val, nbytes);
    }
}

static HK_FORCE_INLINE void MEMORY_SCRUB_BATCH(void** ptrs,int numPtrs, int val, int nbytes)
{
    // if you want to use NAN: for (int i =0; i < nbytes/4; i++) ((int*)ptr)[i] = 0x7FC00000;
    for (int i=0;i<numPtrs;i++)
    {
        void* ptr = ptrs[i];
        if (ptr)
        {
            hkString::memSet(ptr, val, nbytes);
        }
    }
}

static HK_FORCE_INLINE void MEMORY_CHECK(const void* ptr, int val, int nbytes)
{
    if (ptr == HK_NULL)
    {
        return;
    }

    const hkUint8* p = static_cast<const hkUint8*>(ptr);
    for( int i = 0; i < nbytes; ++i )
    {
        if( p[i] != val )
        {
            HK_BREAKPOINT(0);
        }
    }
}

#else
#	define MEMORY_SCRUB(PTR, WHAT, NBYTES) /* nothing */
#   define MEMORY_SCRUB_BATCH(PTR,NUM_PTRS, WHAT, NBYTES) /* nothing */
#	define MEMORY_CHECK(PTR, WHAT, NBYTES) /* nothing */
#endif

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                          hkFreeListMemory

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

hkFreeListMemory::hkFreeListMemory(hkMemoryBlockServer* server)
:	m_criticalSection (4000),
	m_server(server),
	m_largeAllocator(server),
    m_numFreeLists(0),
	m_listener(HK_NULL)
{
	setMemorySoftLimit(0);

	m_hardLimit = server->getMemoryLimit();

    hk_size_t freeListSpace = sizeof(hkFreeList)*MAX_UNIQUE_FREELISTS;

    // This object needs to be informed if memory gets limited
    m_largeAllocator.setLimitedMemoryListener(this);

    // do the allocate
    // NOTE! We don't allocate freelists directly from the freelist allocator, as each freelist is fairly small
    // and the smallest block the large block allocator will alloc is 256 bytes
    m_freeListMemory = reinterpret_cast<hkFreeList*>(m_largeAllocator.alloc(freeListSpace));

    if (!m_freeListMemory)
    {
        // If you hit here - the server is unable to serve even enough space for the freelists!!!
        // Things aren't going to progress well unless there is actually some memory available :)
        HK_BREAKPOINT(0);
    }
    m_topFreeList = m_freeListMemory;
    m_lastFreeList = m_topFreeList + MAX_UNIQUE_FREELISTS;

    // Zero them all first
    for (int i = 0; i < MAX_FREELISTS;i++)
    {
        m_sizeToFreeList[i] = HK_NULL;
    }

	// Set up known sizes
	m_sizeToFreeList[512>>FREELIST_SHIFT] = _newFreeList(512,128,64*1024);
    //
	m_sizeToFreeList[256>>FREELIST_SHIFT] = _newFreeList(256,32,32*1024);
    // For zero sized allocs
	m_sizeToFreeList[0] = _newFreeList(0,sizeof(void*),256);

    // Set all of the simple sizes
    // Go from the largest size downward so we create the one with the largest block first
    for (int i=MAX_FREELIST_SIZE; i>=FREELIST_ALIGNMENT; i-=FREELIST_ALIGNMENT)
    {
        if (m_sizeToFreeList[i>>FREELIST_SHIFT])
        {
            continue;
        }

        hk_size_t blockSize = 1024;
        hk_size_t alignment = 16;

        if (i>0)
        {
            // By default each block has at least 16 elements
            blockSize = i*16;
        }

        // Min block size is 4k
        if (blockSize < 4096)
        {
            blockSize = 4096;
        }
        if (i>=64)
        {
            alignment = 32;
        }

        // Create all of the freelists
        m_sizeToFreeList[i >> FREELIST_SHIFT] = _newFreeList(i,alignment,blockSize);
    }

	m_numValidBigBlocks = 0;
}

hkFreeListMemory::~hkFreeListMemory()
{
	freeRuntimeBlocks();
    // delete all of the freelists
    for (int i = 0; i < m_numFreeLists; i++)
    {
        _deleteFreeList(m_freeLists[i]);
    }

    // Free the freelist memory
    m_largeAllocator.free(m_freeListMemory);

    // Free all memory
    m_largeAllocator.freeAll();
}

void
hkFreeListMemory::setLimitedMemoryListener(hkLimitedMemoryListener* listener)
{
	m_criticalSection.enter();
    m_listener = listener;
    m_criticalSection.leave();
}

hkLimitedMemoryListener*
hkFreeListMemory::getLimitedMemoryListener()
{
    return m_listener;
}

hkBool
hkFreeListMemory::_hasMemoryAvailable(hk_size_t size)
{
    // Find out what the limit is
	hk_size_t limit = m_softLimit ? m_softLimit: m_hardLimit;
    if (limit == 0)
    {
        return true;
    }

    // We need to work out the total memory used quickly
    hk_size_t largeUsed = m_largeAllocator.getTotalMemoryUsed();
    if (largeUsed + size < limit)
    {
        return true;
    }
    // Work out how much free space there is on freelists
    hk_size_t freeAvailable = 0;
    for (int i = 0;i< m_numFreeLists; i++)
    {
        hkFreeList* list = m_freeLists[i];
        freeAvailable += list->getElementSize() * list->getNumFreeElements();
    }

    hk_size_t totalUsed = largeUsed - freeAvailable;
    return (totalUsed + size < limit);
}

hkBool
hkFreeListMemory::hasMemoryAvailable(hk_size_t size)
{
	// We don't need a critical section here - as the worst that can happen
	// is the amount of memory that is available will be slightly off.
	// In order for this to work the hkFreeList + hkLargeBlock allocators have to be 
	// complicit in having methods that are 'thread safe' (in this case the 
	// safeness is because the method just return a contained member variable, 
	// and reads and writes from that variable are atomic on all known 
	// platforms)
	//m_criticalSection.enter();
    hkBool res = _hasMemoryAvailable(size);
    //m_criticalSection.leave();
    return res;
}

void
hkFreeListMemory::cannotAllocate(hk_size_t size)
{
    // Tell the world
    if (m_listener)
    {
        m_listener->cannotAllocate(this,size);
    }
    // Try a garbage collect
    garbageCollect();
}

void
hkFreeListMemory::allocationFailure(hk_size_t size)
{
    // Sigh and give up

    // Tell the world
    if (m_listener)
    {
        m_listener->allocationFailure(this,size);
    }
}

void
hkFreeListMemory::calculateStatistics(hkMemoryStatistics& stats)
{
	m_criticalSection.enter();

    // Get the large memory statistics
    m_largeAllocator.calculateStatistics(stats);

    hkMemoryStatistics freeTotals;
    freeTotals.m_allocated = 0;
    freeTotals.m_used = 0;
    freeTotals.m_available = 0;

    for (int i =0; i < m_numFreeLists; i++)
    {
        hkMemoryStatistics freeStats;
        hkFreeList* list = m_freeLists[i];
        list->calculateStatistics(freeStats);

        if (list->isFreeElementAvailable() && list->getElementSize() > stats.m_largestBlock)
        {
            stats.m_largestBlock = list->getElementSize();
        }

        freeTotals.m_available += freeStats.m_available;
        freeTotals.m_used += freeStats.m_used;
        freeTotals.m_allocated += freeStats.m_allocated;
    }

    stats.m_available += freeTotals.m_available;
    stats.m_used = stats.m_used - freeTotals.m_allocated + freeTotals.m_used;

    // Lets ask the server
    hk_size_t serverAvailable = m_server->getTotalAvailableMemory();

    if (serverAvailable == hkMemoryStatistics::INFINITE_SIZE)
    {
        stats.m_totalAvailable = hkMemoryStatistics::INFINITE_SIZE;
    }
    else
    {
        stats.m_totalAvailable = serverAvailable + stats.m_available;
    }

    m_criticalSection.leave();
}

hkBool
hkFreeListMemory::isOk() const
{
	m_criticalSection.enter();
    hkBool ok = true;
    for (int i = 0; i < m_numFreeLists; i++)
    {
        if (!m_freeLists[i]->isOk())
        {
            ok = false;
            break;
        }
    }
	m_criticalSection.enter();
    return ok;
}

hkFreeList* hkFreeListMemory::_newFreeList(hk_size_t elementSize,hk_size_t alignment,hk_size_t blockSize)
{
    if (m_topFreeList >= m_lastFreeList)
    {
        HK_ASSERT(0x32432423,"Too many freelists have been allocated -> MAX_UNIQUE_FREELISTS isn't big enough to cope");
        HK_BREAKPOINT(0);
    }

    hkFreeList* list = m_topFreeList++;
    new (list) hkFreeList(elementSize,alignment,blockSize,&m_largeAllocator);

    // See if we already have one of the same element size
    for (int i = 0; i < m_numFreeLists; i++)
    {
        if (m_freeLists[i]->getElementSize() == list->getElementSize())
        {
            _deleteFreeList(list);
            return m_freeLists[i];
        }
    }

    m_freeLists[m_numFreeLists++] = list;
    return list;
}

void hkFreeListMemory::_deleteFreeList(hkFreeList* freeList)
{
    // Call the destructor
    freeList->~hkFreeList();
    if (freeList + 1 == m_topFreeList)
    {
        m_topFreeList--;
    }
}

int hkFreeListMemory::getAllocatedSize( int nbytes )
{

    if (nbytes < MAX_FREELIST_SIZE)
    {
        hkFreeList* list = m_sizeToFreeList[nbytes>>FREELIST_SHIFT];
        if (list)
        {
            return int(list->getElementSize());
        }
    }
    // Else its coming from the large memory allocator
    return int(m_largeAllocator.getEstimatedAllocSize(nbytes));
}

void hkFreeListMemory::printStatistics(hkOstream* c)
{
    HK_ASSERT(0x675bd4a3, c != HK_NULL);
    c->printf("printStatistics is not supported on hkFreeListMemory - use hkDebugMemory or hkPoolMemory\n");
}

//
// allocateChunk and deallocateChunk
//
void* hkFreeListMemory::allocateChunk(int nbytes, HK_MEMORY_CLASS cl)
{
	//HK_TIMER_CODE_BLOCK("allocateChunk", HK_NULL );

	m_criticalSection.enter();

    void* ret;
    if (nbytes < MAX_FREELIST_SIZE)
    {
        hkFreeList* list = m_sizeToFreeList[(nbytes+FREELIST_ALIGNMENT-1)>>FREELIST_SHIFT];
        ret = list->alloc();
    }
    else
    {
        ret = m_largeAllocator.alloc(nbytes);
    }

	MEMORY_SCRUB(ret, s_fillReturnedToUser, nbytes);
	m_criticalSection.leave();
	return ret;
}

void hkFreeListMemory::allocateChunkBatch( void** blocksOut, int nblocks, int nbytes )
{
	m_criticalSection.enter();

    if (nbytes < MAX_FREELIST_SIZE)
    {
        hkFreeList* list = m_sizeToFreeList[(nbytes+FREELIST_ALIGNMENT-1)>>FREELIST_SHIFT];
        list->allocBatch(blocksOut,nblocks);

        MEMORY_SCRUB_BATCH(blocksOut,nblocks, s_fillReturnedToUser, nbytes);
    }
    else
    {
        for (int i = 0; i < nblocks; i++)
        {
            void* ret = m_largeAllocator.alloc(nbytes);
            MEMORY_SCRUB(ret, s_fillReturnedToUser, nbytes);
            blocksOut[i] = ret;
        }
    }

	m_criticalSection.leave();
}

void  hkFreeListMemory::deallocateChunk(void* p, int nbytes, HK_MEMORY_CLASS cl)
{
	if(p)
	{
		m_criticalSection.enter();
        if (nbytes < MAX_FREELIST_SIZE)
        {
            hkFreeList* list = m_sizeToFreeList[(nbytes+FREELIST_ALIGNMENT-1)>>FREELIST_SHIFT];
            list->free(p);
        }
        else
        {
            m_largeAllocator.free(p);
        }
		m_criticalSection.leave();
	}
}

void hkFreeListMemory::deallocateChunkBatch(void** blocks, int nblocks, int nbytes )
{
	m_criticalSection.enter();

    if (nbytes < MAX_FREELIST_SIZE)
    {
        hkFreeList* list = m_sizeToFreeList[(nbytes+FREELIST_ALIGNMENT-1)>>FREELIST_SHIFT];
        list->freeBatch(blocks,nblocks);
    }
    else
    {
		for( int i = 0; i < nblocks; ++i )
		{
			void* mem = blocks[i];
            if (mem)
            {
                m_largeAllocator.free(mem);
            }
		}
    }
	m_criticalSection.leave();
}


hkResult hkFreeListMemory::walkMemory(hkMemoryWalkCallback callback,void* param)
{
    // Okay this tricky - because freelist allocations are actually embedded inside
    // of the large memory allocations.

    // We need a block of memory which holds all of the freelist blocks in order
    int numBlocks = 0;
    for (int i = 0; i < m_numFreeLists; i++)
    {
        numBlocks += m_freeLists[i]->getTotalNumBlocks();
    }

    // <js.todo.b Use critical alloc
    void** freeListBlocks = reinterpret_cast<void**>(allocateChunk(numBlocks*sizeof(void*),HK_MEMORY_CLASS_BASE));
    if (!freeListBlocks)
    {
        return HK_FAILURE;
    }

    void** cur = freeListBlocks;
    for (int i = 0; i < m_numFreeLists; i++)
    {
        hkFreeList* list = m_freeLists[i];
        int curNumBlocks = list->getTotalNumBlocks();

        list->getBlocks(cur,curNumBlocks);
        cur += curNumBlocks;
    }
    // Sort these
    hkSort(freeListBlocks,numBlocks,_comparePointers);

    cur = freeListBlocks;
    hkLargeBlockAllocator::Iterator iter = m_largeAllocator.getIterator();
    for (; iter.isValid(); m_largeAllocator.nextBlock(iter))
    {
        void* block = iter.getAddress();

        if (block == *cur)
        {
            /// If we hit the freelist block, then we skip it
            cur++;
        }
        else
        {
            // Ignore if its the alloc we needed to get this far
            //if (block == freeListBlocks) continue;
            // Do the callback
            callback(block, iter.getSize(),iter.isInuse(),0,param);
        }
    }
    // free
    deallocateChunk(freeListBlocks,numBlocks * sizeof(void*),HK_MEMORY_CLASS_BASE);

    for (int i = 0; i < m_numFreeLists; i++)
    {
        hkFreeList* list = m_freeLists[i];
        list->walkMemory(callback, i + 1, param);
    }

    return HK_SUCCESS;
}

void hkFreeListMemory::preAllocateRuntimeBlock(int nbytes, HK_MEMORY_CLASS cl)
{
	m_criticalSection.enter();

	HK_ASSERT2(0xafee4265, nbytes >= hkThreadMemory::MEMORY_MAX_SIZE_LARGE_BLOCK, "Big block too small.");
	HK_ASSERT2(0xafee4264, m_numValidBigBlocks < BIG_BLOCKS_SLOTS, "Out of big memory block slots.");

	//
	// append new block in slot list
	//
	BigBlockData* newBigBlock = &m_bigBlockDataArray[m_numValidBigBlocks++];
	{
		newBigBlock->m_available			= true;
		newBigBlock->m_size					= nbytes;
		newBigBlock->m_memory				= allocateChunk(nbytes, cl);
		newBigBlock->m_class				= cl;
		newBigBlock->m_providedByOutside	= false;
	}

	m_criticalSection.leave();
}

void hkFreeListMemory::freeRuntimeBlocks()
{
	m_criticalSection.enter();

    for ( int i = 0; i < m_numValidBigBlocks; i++)
	{
		BigBlockData* bigBlock = &m_bigBlockDataArray[i];
		if ( bigBlock->m_providedByOutside == false )
		{
			deallocateChunk(bigBlock->m_memory, bigBlock->m_size, bigBlock->m_class);
		}
	}
	m_numValidBigBlocks = 0;

	m_criticalSection.leave();
}

void* hkFreeListMemory::allocateRuntimeBlock(int nbytes, HK_MEMORY_CLASS cl)
{
	if ( nbytes < hkThreadMemory::MEMORY_MAX_SIZE_LARGE_BLOCK)
	{
		return hkThreadMemory::getInstance().allocateChunk( nbytes, cl );
	}

	hkCriticalSectionLock lock(&m_criticalSection);

	BigBlockData* smallestBigBlock = HK_NULL;

	//
	// try to find the smallest(!) fitting block that is available
	//
    for ( int i=0; i < m_numValidBigBlocks; i++)
	{
		BigBlockData* bigBlock = &m_bigBlockDataArray[i];

		if ( bigBlock->m_available == true && bigBlock->m_size >= nbytes )
		{
			if ( smallestBigBlock == HK_NULL || bigBlock->m_size < smallestBigBlock->m_size )
			{
				smallestBigBlock = bigBlock;
			}
		}
	}

	if ( smallestBigBlock != HK_NULL )
	{
		smallestBigBlock->m_available = false;
		return smallestBigBlock->m_memory;
	}

	//
	// no block available or no block large enough: allocate a new block
	//
	void* memory;
	{
		//
		// calculate next 'best fitting' size; 64 bytes is the estimated OS memory management overhead
		//
		int sizeToAllocate;
		{
			sizeToAllocate = 1;
            for ( int i = nbytes + 64; i >0; i = i>>1 )
			{
				sizeToAllocate += sizeToAllocate;
			}
			sizeToAllocate -= 64;
		}

		if ( m_numValidBigBlocks < BIG_BLOCKS_SLOTS )
		{
			HK_WARN_ALWAYS(0xaf55adde, "No block of size " << nbytes << " currently available. Allocating new block from system memory.");
			BigBlockData* newBigBlock = &m_bigBlockDataArray[m_numValidBigBlocks++];
			{
				newBigBlock->m_available			= false;
				newBigBlock->m_size					= sizeToAllocate;
				newBigBlock->m_memory				= allocateChunk(sizeToAllocate, cl);
				newBigBlock->m_class				= cl;
				newBigBlock->m_providedByOutside	= false;
			}
			memory = newBigBlock->m_memory;
		}
		else
		{
			HK_WARN_ALWAYS(0xaf55adde, "No block of size " << nbytes << " currently available and out of big block memory slots. Allocating unmanaged system memory.");
			memory = allocateChunk(nbytes, cl);
		}
	}

	return memory;
}

void hkFreeListMemory::deallocateRuntimeBlock(void* p, int nbytes, HK_MEMORY_CLASS cl)
{
	if ( nbytes < hkThreadMemory::MEMORY_MAX_SIZE_LARGE_BLOCK)
	{
		hkThreadMemory::getInstance().deallocateChunk( p, nbytes, cl );
		return;
	}

	hkCriticalSectionLock lock(&m_criticalSection);

    for ( int i = 0; i < m_numValidBigBlocks; i++)
	{
		BigBlockData* bigBlock = &m_bigBlockDataArray[i];
		if ( bigBlock->m_memory == p )
		{
			bigBlock->m_available = true;
			return;
		}
	}

	HK_WARN_ALWAYS(0xaf55addf, "Deallocating unmanaged big block.");
	deallocateChunk(p, nbytes, cl);
}

void hkFreeListMemory::provideRuntimeBlock(void* p, int nbytes, HK_MEMORY_CLASS cl)
{
	m_criticalSection.enter();

	HK_ASSERT2(0xaf55adda, m_numValidBigBlocks < BIG_BLOCKS_SLOTS, "Out of big memory block slots. Cannot accept provided memory.");

	BigBlockData* newBigBlock = &m_bigBlockDataArray[m_numValidBigBlocks++];
	{
		newBigBlock->m_available			= true;
		newBigBlock->m_size					= nbytes;
		newBigBlock->m_memory				= p;
		newBigBlock->m_class				= cl;
		newBigBlock->m_providedByOutside	= true;
	}

	m_criticalSection.leave();
}

void hkFreeListMemory::reservePagesFromSystemMemory( int numBytes )
{
}

void hkFreeListMemory::garbageCollect()
{
	m_criticalSection.enter();
    // We can garbage collect freelists
    // We are going to keep running around this list until we've wringed the last chunk of free memory out of them
    hkBool memoryFreed = false;
	hkBool collectFailed = false;
	int totalFreed = 0;
    do
    {
        memoryFreed = false;
        for (int i = 0; i < m_numFreeLists; i++)
        {
            hkFreeList* list = m_freeLists[i];
            // If it has free blocks then there will be blocks freed
            // Look for garbage
            if (list->findGarbage()<0)
            {
                collectFailed = true;
            }
            // If we have some free blocks then some memory was found
            if (list->hasFreeBlocks())
            {
                memoryFreed = true;
            }
            // Free all of the blocks
            totalFreed += list->freeAllFreeBlocks();
        }
    }    while (memoryFreed&&collectFailed);

    // Collect the large block allocator
    m_largeAllocator.garbageCollect();

	m_criticalSection.leave();
}

void
hkFreeListMemory::setMemoryHardLimit(hk_size_t maxMemory)
{
    hkCriticalSectionLock lock(&m_criticalSection);
    hkBool res = m_server->setMemoryLimit(maxMemory);
    HK_ASSERT(0x3423432,res);

	m_hardLimit = m_server->getMemoryLimit();
}

hk_size_t
hkFreeListMemory::getMemoryHardLimit()
{
    hkCriticalSectionLock lock(&m_criticalSection);
    return m_server->getMemoryLimit();
}

void
hkFreeListMemory::setMemorySoftLimit(hk_size_t maxMemory)
{
    hkCriticalSectionLock lock(&m_criticalSection);
    hk_size_t hardLimit = m_server->getMemoryLimit();
    HK_ASSERT(0x2423432, !(hardLimit && maxMemory > hardLimit));
    if (hardLimit && maxMemory > hardLimit) return;
    m_softLimit = maxMemory;
}

hk_size_t
hkFreeListMemory::getMemorySoftLimit()
{
    return m_softLimit;
}

void hkFreeListMemory::optimize()
{
	m_criticalSection.enter();
    // We can garbage collect freelists
    for (int i = 0; i < m_numFreeLists; i++)
    {
        hkFreeList* list = m_freeLists[i];
        int found = list->findGarbage();

        if (found > 0)
		{
			hk_size_t blockSize = list->getBlockSize();
            // remove all of those blocks that are 10% smaller
            list->freeSmallFreeBlocks(blockSize - (blockSize / 10));
		}
    }
	m_criticalSection.leave();
}

void hkFreeListMemory::releaseUnusedPagesToSystemMemory()
{
}


/*
* Havok SDK - PUBLIC RELEASE, BUILD(#20070919)
*
* Confidential Information of Havok.  (C) Copyright 1999-2007 
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
*
* Use of this software for evaluation purposes is subject to and indicates 
* acceptance of the End User licence Agreement for this product. A copy of 
* the license is included with this software and is also available from salesteam@havok.com.
*
*/
