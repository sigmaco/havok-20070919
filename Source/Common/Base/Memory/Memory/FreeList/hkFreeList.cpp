/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>

#include <Common/Base/Memory/Memory/FreeList/hkFreeList.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                            hkFreeList

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

hkFreeList::hkFreeList(hk_size_t elementSize,hk_size_t align,hk_size_t blockSize,hkLargeBlockAllocator* largeBlockAllocator)
:	m_free(HK_NULL),
	m_blocks(HK_NULL),
    m_freeBlocks(HK_NULL),
    m_blockSize(blockSize),
    m_align(align),
    m_top(HK_NULL),
    m_blockEnd(HK_NULL),
    m_numFreeElements(0),
    m_totalNumElements(0),
	m_alloc(largeBlockAllocator)
{
    HK_ASSERT(0x324235,align >= sizeof(Element));

    // This needs to be true for alignment assumptions to work correctly
	HK_COMPILE_TIME_ASSERT( (sizeof(Block) & 0xf) == 0);

    if (elementSize < align)
    {
        elementSize = align;
    }
    else
    {
        elementSize = (elementSize + align - 1) & ~(align - 1);
    }
    m_elementSize = elementSize;
    m_maxBlockSize = bestBlockSize(4096 - sizeof(Block),m_align);
}

hkBool
hkFreeList::_checkFreeBlocks()
{
    Element* cur = m_free;

    while (cur)
    {
        hkUint8* byteCur = (hkUint8*)cur;
        /// This must be the block
        /// Check the alignment

        if ((hk_size_t(byteCur) & (m_align - 1)) != 0)
		{
			return false;
		}

        hkBool found = false;
        // FInd the block it is in
        Block* block = m_blocks;
        while (block)
        {
            if (!m_alloc->isValidAlloc(block))
			{
				return false;
			}

            hkUint8* start = block->m_start;
            hk_size_t maxEle = block->m_numElements;
            hkUint8* end = start + m_elementSize * maxEle;

            if (byteCur >= start && byteCur < end)
            {
				// Check its on the boundary correctly
                if ((byteCur - start) % m_elementSize !=0)
				{
					return false;
				}

				// Its found
                found = true;
                break;
            }
            block = block->m_next;
        }
        if (!found)
		{
			return false;
		}

        // Next
        cur = cur->m_next;
    }
    return true;
}

int
hkFreeList::_freeBlocks(Block* cur)
{
	int numFreed = 0;
    // Free all the blocks in the list
    while (cur)
    {
		numFreed ++;

        m_totalNumElements -= cur->m_numElements;
		m_numFreeElements -= cur->m_numElements;

        Block* next = cur->m_next;
        m_alloc->free(cur);
        cur = next;
    }
	return numFreed;
}

void hkFreeList::freeAllMemory()
{
    _freeBlocks(m_blocks);
    m_blocks = HK_NULL;
    _freeBlocks(m_freeBlocks);
    m_freeBlocks = HK_NULL;

    m_free = HK_NULL;
    // Reset the block size
    m_blockSize = 0;

	m_numFreeElements = 0;
	m_totalNumElements = 0;

    // There is no current block
    m_top = HK_NULL;
    m_blockEnd = HK_NULL;
}

hk_size_t hkFreeList::_calcNumFreeElements() const
{
    hk_size_t num = 0;
    Element* ele = m_free;
    while (ele)
    {
        num++;
        ele = ele->m_next;
    }
    // Don't forget, we've also got the remains of the 'top block'
    num += (m_blockEnd - m_top) / m_elementSize;
    //
    return num;
}

hk_size_t hkFreeList::_calcTotalNumElements(Block* cur)
{
    hk_size_t num = 0;
    while (cur)
    {
        num += cur->m_numElements;
        cur = cur->m_next;
    }
    return num;
}

hk_size_t hkFreeList::_calculateBlocksTotalSize(Block* cur)
{
    hk_size_t size = 0;
    while (cur)
    {
        size += m_alloc->getAllocTotalSize(cur);
        // Next
        cur = cur->m_next;
    }
    return size;
}


hk_size_t hkFreeList::_calcTotalNumElements() const
{
    return _calcTotalNumElements(m_blocks) + _calcTotalNumElements(m_freeBlocks);
}

int hkFreeList::findGarbage()
{
    // See if there are no blocks
    if ( m_blocks == HK_NULL )
    {
        return 0;
    }

#if 0
    {
        hk_size_t numElements = getNumElements();
        hk_size_t numFree = getNumFreeElements();
    }
#endif

    // One thing that makes this trickier is we don't want to use hkArray etc, because it may allocate memory
    // from this freelist, and therefore screw things up royally. So what we do is allocate the memory for
    // doing the collect directly from m_alloc, so there are no side effects on the freelist

    // First find out how many blocks there are
    hk_size_t numBlocks = 0;
    {
        Block* cur = m_blocks;
        while (cur)
        {
            numBlocks++;
            cur = cur->m_next;
        }
    }

    Block** blocks = reinterpret_cast<Block**>(m_alloc->criticalAlloc(sizeof(Block*) * numBlocks));

    // If couldn't allocate space for blocks we need to fail
    if (!blocks)
    {
        return -1;
    }

    {
        Block* cur = m_blocks;
        int i = 0;
        while (cur)
        {
            // Add to the list of blocks
            blocks[i++] = cur;
            cur = cur->m_next;
        }
        // Sort the blocks
        hkSort(blocks,int(numBlocks),_compareBlocks);
    }

    // We have any elements which remain on after top
    hk_size_t numElements = (m_blockEnd - m_top) / m_elementSize;
    {
        Element* cur = m_free;
        while (cur)
        {
            numElements++;
            cur = cur->m_next;
        }
    }

    // Find all of the pointers on the freelist
    Element** elements = reinterpret_cast<Element**>(m_alloc->criticalAlloc(sizeof(Element*) * numElements));
    if (!elements)
    {
        m_alloc->criticalFree(blocks,sizeof(Block*) * numBlocks);
        return -1;
    }

    {
        Element* cur = m_free;
        int i=0;
        while (cur)
        {
            elements[i++] = cur;
            cur = cur->m_next;
        }

        // Add any of the top block elements
        hkUint8* top = m_top;
        while (top < m_blockEnd)
        {
            elements[i++] = reinterpret_cast<Element*>(top);
            top += m_elementSize;
        }

		// The blocks are now in the freelist
		m_blockEnd = HK_NULL;
		m_top = HK_NULL;

        // Sort the blocks
        hkSort(elements,int(numElements),_compareElements);
    }

    Element** curEle = elements;
    Element** endEle = elements + numElements;

    int numUnusedBlocksFound = 0;

    // Okay lets see how we match up
    for (hk_size_t i = 0;i< numBlocks && curEle < endEle; i++)
    {
        Block* block = blocks[i];

        hk_size_t maxElements = block->m_numElements;
        hkUint8* cur = block->m_start;
        hkUint8* end = cur + maxElements * m_elementSize;

        // See if they all match up :)
        while (curEle < endEle && cur == reinterpret_cast<hkUint8*>(*curEle) && cur < end)
        {
            cur += m_elementSize;
            curEle++;
        }

        if ( cur == end)
        {
            // They must have all matched :)
            // So we can add this block to the free blocks list

            numUnusedBlocksFound++;

            // Chain onto the list of free blocks
            block->m_next = m_freeBlocks;
            m_freeBlocks = block;

            // Mark this block as dead
            blocks[i] = HK_NULL;

#if 0
            // We need to remove the Elements from the list
            {
                // The start of this run of blocks
                Element** dst = curEle - maxElements;
                // We should be pointing to the end
                Element** src = curEle;
                // Remove all of the removed elements by copying down
                while (src < endEle)
                {
                    *dst++ = *src++;
                }
                // Move the end down
                endEle -= maxElements;
                // This is where we are at now
				curEle -= maxElements;
            }
#else
            {
                // Mark all of the elements as being invalid
                Element** dst = curEle - maxElements;
                while (dst < curEle)
                {
                    *dst++ = HK_NULL;
                }
            }
#endif

        }
        else
        {
            // Didn't match we need to skip thru all the entries remaining in this block
            while (curEle < endEle && reinterpret_cast<hkUint8*>(*curEle) < end)
            {
                curEle++;
            }
        }
    }

    {
        // Lets relink up the blocks
        Block** prev = &m_blocks;
        for (hk_size_t i = 0; i< numBlocks; i++)
        {
            // Link up into a singly linked list
            Block* block = blocks[i];
            // Ignore the blocks which have been destroyed
            if (block)
            {
                // Set the previous to point to this
                *prev = block;
                // Make the next prev point to the this's next
                prev = &block->m_next;
            }
        }
        // Mark the end
        *prev = HK_NULL;
    }

    {
        // Okay we need to relink up these Elements
        Element** prev = &m_free;
        for (curEle = elements; curEle < endEle; curEle++)
        {
            // Link up into a singly linked list
            Element* ele = *curEle;
            // If the element is HK_NULL the block it was in has been put on the free block list
            if (ele)
            {
                // Set the previous to point to this
                *prev = ele;
                // Make the next prev point to the this's next
                prev = &ele->m_next;
            }
        }
        // Mark the end
        *prev = HK_NULL;
    }

    // Free the elements
    m_alloc->criticalFree(elements,sizeof(Element*) * numElements);

    // Free the blocks
    m_alloc->criticalFree(blocks,sizeof(Block*) * numBlocks);

	return numUnusedBlocksFound;
}

void hkFreeList::_walkMemoryBlockList(Block* block,hkMemoryWalkCallback callback,int pool,void* param)
{
    // Do all the free blocks
    for ( ;block != HK_NULL; block = block->m_next)
    {
        // All these elements are free

        hkUint8* cur = block->m_start;
        hkUint8* end = cur + block->m_numElements * m_elementSize;
        while (cur < end)
        {
            // This ones free
            callback(cur,m_elementSize,false,pool,param);
            cur += m_elementSize;
        }
    }
}


void hkFreeList::walkMemory(hkMemoryWalkCallback callback,int pool,void* param)
{
    HK_ASSERT(0x342434,_calcNumFreeElements() == m_numFreeElements && _calcTotalNumElements() == m_totalNumElements);

    _walkMemoryBlockList(m_freeBlocks,callback,pool,param);

    // See if there are no blocks
    if ( m_blocks == HK_NULL && m_free == HK_NULL)
    {
        HK_ASSERT(0xf23434,m_top == m_blockEnd);
        HK_ASSERT(0xf23434,m_numFreeElements == m_totalNumElements);
        return;
    }

    // One thing that makes this trickier is we don't want to use hkArray etc, because it may allocate memory
    // from this freelist, and therefore screw things up royally. So what we do is allocate the memory for
    // doing the collect directly from m_alloc, so there are no side effects on the freelist

    // First find out how many blocks there are
    hk_size_t numBlocks = 0;
    {
        Block* cur = m_blocks;
        while (cur)
        {
            numBlocks++;
            cur = cur->m_next;
        }
    }
    // <js.todo.b Use the hkStackAllocate critial memory allocation

    Block** blocks = reinterpret_cast<Block**>(m_alloc->alloc(sizeof(Block*) * numBlocks));
    // If couldn't allocate space for blocks we need to fail
    if (!blocks)
    {
        return;
    }

    {
        Block* cur = m_blocks;
        int i = 0;
        while (cur)
        {
            // Add to the list of blocks
            blocks[i++] = cur;
            cur = cur->m_next;
        }
        // Sort the blocks
        hkSort(blocks, int(numBlocks), _compareBlocks);
    }

    // We have any elements which remain on after top
    hk_size_t numElements = (m_blockEnd - m_top) / m_elementSize;
    {
        Element* cur = m_free;
        while (cur)
        {
            numElements++;
            cur = cur->m_next;
        }
    }

    // Find all of the pointers on the freelist
    Element** elements = reinterpret_cast<Element**>(m_alloc->alloc(sizeof(Element*) * numElements));
    if (!elements)
    {
        m_alloc->free(blocks);
        return;
    }

    {
        Element* cur = m_free;
        int i = 0;
        while (cur)
        {
            elements[i++] = cur;
            cur = cur->m_next;
        }
        // Add any of the top block elements
        hkUint8* top = m_top;
        while (top < m_blockEnd)
        {
            elements[i++] = reinterpret_cast<Element*>(top);
            top += m_elementSize;
        }
        // Sort the blocks
        hkSort(elements,int(numElements),_compareElements);
    }

    Element** curEle = elements;
    Element** endEle = elements + numElements;

    // Okay lets see how we match up
    for (hk_size_t i = 0; i < numBlocks && curEle < endEle; i++)
    {
        Block* block = blocks[i];

        hk_size_t maxElements = block->m_numElements;
        hkUint8* cur = block->m_start;
        hkUint8* end = cur + maxElements * m_elementSize;

        // See if they all match up :)
        while (cur < end)
        {
            if (cur == reinterpret_cast<void*>(*curEle))
            {
                // This ones free
                callback(cur,m_elementSize,false,pool,param);
                curEle++;
            }
            else
            {
                // This ones allocated
                callback(cur,m_elementSize,true,pool,param);
            }
            cur += m_elementSize;
        }
    }
    // Free the elements
    m_alloc->free(elements);
    // Free the blocks
    m_alloc->free(blocks);
}

int hkFreeList::freeAllFreeBlocks()
{
    // Free it all
    int numFreed = _freeBlocks(m_freeBlocks);
    m_freeBlocks = HK_NULL;
	return numFreed;
}

void hkFreeList::freeSmallFreeBlocks(hk_size_t minSize)
{
    Block** prev = &m_freeBlocks;
    Block* cur = m_freeBlocks;

    while (cur)
    {
        if (cur->m_blockSize <= minSize)
        {
            // Right we free this block
            Block* next = cur->m_next;
            *prev = next;

            // Fix up the counts
            m_totalNumElements -= cur->m_numElements;
			m_numFreeElements -= cur->m_numElements;

            // Free the block
            m_alloc->free(cur);

            // Onto the next
            cur = next;
            continue;
        }

        prev = &cur->m_next;
        cur = cur->m_next;
    }
}


void* hkFreeList::addSpace()
{
    if (m_freeBlocks)
    {
        Block* block = m_freeBlocks;
        m_freeBlocks = block->m_next;

        // We have a block!
        _addBlockElements(block);

        // Attach to the list of active blocks
        block->m_next = m_blocks;
        m_blocks = block;

        // One less free
        m_numFreeElements--;
        // Return an allocation from the top
        void* data = (void*)m_top;
        m_top += m_elementSize;

        return data;
    }

    // we need to work out how big a block we are going to make
    if (m_blockSize <= 0)
    {
        // Make 256 the minimum allocation
        hk_size_t numElements = 256 / m_elementSize;
        // We need at least one element
        numElements = (numElements < 1 )? 1 : numElements;
        // Work out the size taking into account alignment etc
        m_blockSize = bestBlockSize(numElements * m_elementSize,m_align);
    }
    else
    {
        if (m_blockSize < m_maxBlockSize)
        {
            // We may need to make the block size bigger
            hk_size_t numElements = m_blockSize / m_elementSize;
            if (numElements < 8)
            {
                numElements = 8;
            }
            else
            {
                numElements = numElements + (numElements >> 1);
            }

            m_blockSize = bestBlockSize(numElements * m_elementSize,m_align);
        }
    }

    // Allocate the block
    Block* block = reinterpret_cast<Block*>(m_alloc->alloc(m_blockSize));

    // Ouch allocation failed....
    if (!block)
    {
        return HK_NULL;
    }

    // Store how big it is
    block->m_blockSize = m_alloc->getAllocSize(block);

    // Work out where the payload starts
    block->m_start = reinterpret_cast<hkUint8*>((((hk_size_t)(block + 1)) + m_align - 1)&(~hk_size_t(m_align - 1)));
    block->m_numElements = (((reinterpret_cast<hkUint8*>(block)) + block->m_blockSize) - block->m_start) / m_elementSize;

    // I could reduce the size of the alloc here, if the alignment is high, it could save a bit of space
    //hk_size_t remainingSpace = (((hkUint8*)block) + block->m_blockSize) - (block->m_start + block->m_numElements*m_elementSize);

    // Add all of the elements
    _addBlockElements(block);

    // attach the 'used' block list. This is a fair assumption because presumably the request
    // for more space means, that one of the freeblocks we just added is going to be used
	block->m_next = m_blocks;
	m_blocks = block;

    // Fix up the counts
    m_totalNumElements += block->m_numElements;
    m_numFreeElements += block->m_numElements - 1;

    // Return an allocation from the top
    void* data = (void*)m_top;
    m_top += m_elementSize;
    return data;
}

hk_size_t hkFreeList::bestBlockSize(hk_size_t elementSpace,hk_size_t align)
{
    if (align <= 16) return elementSpace + sizeof(Block);
        /// Okay this should be the max amount I should have to align with otherwise
    return sizeof(Block) + (align - 16) + elementSpace;
}

void hkFreeList::freeAll()
{
    // All the elements are now free
    m_numFreeElements = m_totalNumElements;

    // No active blocks means nothing could be allocated
    if (m_blocks==HK_NULL)
    {
        return;
    }

    // First mark all the blocks
    m_free = HK_NULL;

    // We need to add the blocks to the free blocks
    Block* cur = m_blocks;
    while (cur->m_next != HK_NULL)
    {
        cur = cur->m_next;
    }

    // Concat the left free blocks
    cur->m_next = m_freeBlocks;

    // The blocks are now the free blocks
    m_freeBlocks = m_blocks;
    m_blocks = HK_NULL;

    // There is no top
    m_top = HK_NULL;
    m_blockEnd = HK_NULL;
}

void hkFreeList::calculateStatistics(hkMemoryStatistics& stats)
{
    // Total amount of allocated space
    stats.m_allocated = _calculateBlocksTotalSize(m_blocks) + _calculateBlocksTotalSize(m_freeBlocks);

    hk_size_t numFreeElements = getNumFreeElements();
    hk_size_t numElements = getTotalNumElements();

    //HK_ASSERT(0x324234,numFreeElements==_calcNumFreeElements());
    //HK_ASSERT(0x324234,numElements==_calcTotalNumElements());

    // The amount thats available
    stats.m_available = numFreeElements * m_elementSize;
    // The amount thats used
    stats.m_used = (numElements - numFreeElements) * m_elementSize;

    stats.m_largestBlock = m_elementSize;
    stats.m_totalAvailable = stats.m_available;
}


void hkFreeList::getBlocks(void** blocks,int numBlocks)
{
    HK_ASSERT(0x3243242,getTotalNumBlocks() == numBlocks);

    Block* cur = m_blocks;
    while (cur)
    {
        *blocks++ = reinterpret_cast<void*>(cur);
        cur = cur->m_next;
    }
    cur= m_freeBlocks;
    while (cur)
    {
        *blocks++ = reinterpret_cast<void*>(cur);
        cur = cur->m_next;
    }
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
