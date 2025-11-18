/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>

#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

#include <Common/Base/Algorithm/Sort/hkSort.h>

#include <Common/Base/Memory/Memory/hkMemory.h>

#include <Common/Base/Memory/Memory/FreeList/FixedMemoryBlockServer/hkFixedMemoryBlockServer.h>
#include <Common/Base/Memory/Memory/FreeList/SystemMemoryBlockServer/hkSystemMemoryBlockServer.h>

// this
#include <Common/Base/Memory/Memory/FreeList/hkLargeBlockAllocator.h>

hkLargeBlockAllocator::hkLargeBlockAllocator(hkMemoryBlockServer* server):
	m_limitedListener(HK_NULL),
    m_server(server)
{
    _init();
}

hkLargeBlockAllocator::~hkLargeBlockAllocator()
{
    hkMemPage* cur = m_pages.m_next;
    hkMemPage* end = &m_pages;

    while (cur != end)
    {
        hkMemPage* next = cur->m_next;
        // Free the allocation
        m_server->free(cur,cur->m_size);
        /// Next page
        cur = next;
    }
}

void
hkLargeBlockAllocator::_init()
{
    m_used = 0;

    m_treemap = 0;
    m_leastAddr = HK_NULL;

    for (int i=0;i<int(sizeof(m_treebins)/sizeof(m_treebins[0]));i++)
    {
        m_treebins[i] = HK_NULL;
    }

        ///
    m_zeroChunk.head = hk_size_t(0|hkMemChunk::PINUSE_BIT|hkMemChunk::CINUSE_BIT);
    m_zeroChunk.prevFoot = hk_size_t(0);

        // Its empty
    m_top = &m_zeroChunk;
    m_topsize = hk_size_t(0);

	m_pages.m_next = HK_NULL;
	m_pages.m_prev = HK_NULL;

    /// Set up the pages list
    m_pages.m_next = &m_pages;
    m_pages.m_prev = &m_pages;
}


void
hkLargeBlockAllocator::freeAll()
{
    hkMemPage* cur = m_pages.m_next;
    hkMemPage* end = &m_pages;

    while (cur != end)
    {
        hkMemPage* next = cur->m_next;
        // Free the allocation
        m_server->free(cur,cur->m_size);
        /// Next page
        cur = next;
    }

    //
    _init();
}

void hkLargeBlockAllocator::_insertLargeChunk( hkMemTreeChunk* x, hk_size_t s)
{
    hkBinIndex i = _computeTreeIndex(s);

        /// Find the associated bin
    hkMemTreeChunk** h = &m_treebins[i];

        /// Initialize X
    x->index = i;
    x->child[0] = x->child[1] = 0;

        /// If the treemap isn't marked, then presumably that part of the tree is empty
    if (!_isTreeMapMarked(i))
    {
            /// Mark up the tree
        _markTreeMap(i);
            /// Point the treebin to this
        *h = x;
            /// parent is not pointing to a parent block but to the tree bin that its currently in
        x->parent = (hkMemTreeChunk*)h;
            /// Make the doubly linked list point to self
        x->next = x;
        x->prev = x;
    }
    else
    {
        hkMemTreeChunk* t = *h;
        hk_size_t k = s << _leftShiftForTreeIndex(i);
        for (;;)
        {
            if (t->getChunkSize() != s)
            {
                hkMemTreeChunk** c = &(t->child[(k >> (SIZE_T_BITSIZE- hk_size_t(1))) & 1]);
                k <<= 1;
                if (*c != HK_NULL)
                {
                    t = *c;
                }
                else
                {
                    HK_ASSERT(0x13423432,_isOkAddress(c));

                    *c = x;

                    x->parent = t;
                    x->next = x;
                    x->prev = x;
                    break;
                }
            }
            else
            {
                hkMemTreeChunk*  f = reinterpret_cast<hkMemTreeChunk*>(t->next);

                HK_ASSERT(0x32332432,_isOkAddress(t)&&_isOkAddress(f));

                t->next = f->prev = x;
                x->next = f;
                x->prev = t;
                x->parent = HK_NULL;
                break;
            }
        }
    }
}

/*
  Unlink steps:

  1. If x is a chained node, unlink it from its same-sized fd/bk links
     and choose its bk node as its replacement.
  2. If x was the last node of its size, but not a leaf node, it must
     be replaced with a leaf node (not merely one with an open left or
     right), to make sure that lefts and rights of descendents
     correspond properly to bit masks.  We use the rightmost descendent
     of x.  We could use any other leaf, but this is easy to locate and
     tends to counteract removal of leftmosts elsewhere, and so keeps
     paths shorter than minimally guaranteed.  This doesn't loop much
     because on average a node in a tree is near the bottom.
  3. If x is the base of a chain (i.e., has parent links) relink
     x's parent and children to x's replacement (or null if none).
*/

void hkLargeBlockAllocator::_unlinkLargeChunk( hkMemTreeChunk* x)
{
    hkMemTreeChunk* xp = x->parent;
    hkMemTreeChunk* r;

    if (x->prev != x)
    {
        hkMemTreeChunk* f = reinterpret_cast<hkMemTreeChunk*>(x->next);
        r = reinterpret_cast<hkMemTreeChunk*>(x->prev);

        HK_ASSERT(0x34534534,_isOkAddress(f));

            /// Detatch
        f->prev = r;
        r->next = f;
    }
    else
    {
        hkMemTreeChunk** rp;
        if (((r = *(rp = &(x->child[1]))) != HK_NULL) ||
            ((r = *(rp = &(x->child[0]))) != HK_NULL))
        {
            hkMemTreeChunk** cp;
            while ((*(cp = &(r->child[1])) != 0) ||
                    (*(cp = &(r->child[0])) != 0))
            {
                r = *(rp = cp);
            }

            HK_ASSERT(0x34233434,_isOkAddress(rp));
            *rp = HK_NULL;
        }
    }


    if (xp != HK_NULL)
    {
        hkMemTreeChunk** h = &m_treebins[x->index];
        if (x == *h)
        {
            if ((*h = r) == HK_NULL) _clearTreeMap( x->index);
        }
        else
        {
            HK_ASSERT(0x543636,_isOkAddress(xp));
            if (xp->child[0] == x)
                xp->child[0] = r;
            else
                xp->child[1] = r;
        }

        if (r != HK_NULL)
        {
            HK_ASSERT(0x4534543,_isOkAddress(r));

            hkMemTreeChunk* c0, *c1;
            r->parent = xp;
            if ((c0 = x->child[0]) != HK_NULL)
            {
                HK_ASSERT(0x3234234,_isOkAddress(c0));
                r->child[0] = c0;
                c0->parent = r;
            }

            if ((c1 = x->child[1]) != HK_NULL )
            {
                HK_ASSERT(0x3435435,_isOkAddress(c1));
                r->child[1] = c1;
                c1->parent = r;
            }
        }
    }
}

/* allocate a large request from the best fitting chunk in a treebin */
void*
hkLargeBlockAllocator::_allocLarge( hk_size_t nb)
{
    hkMemChunk* v = HK_NULL;
		/// This basically making the rsize, invalidly large, so the first valid block will be a fit
    hk_size_t rsize = hk_size_t(-((hkSignedSizeT)nb));

    int idx = _computeTreeIndex(nb);

    hkMemTreeChunk* t = m_treebins[idx];

    if (t)
    {
			/// Traverse tree for this bin looking for node with size == nb
        hk_size_t sizebits = nb << _leftShiftForTreeIndex(idx);
			/// The deepest untaken right subtree
        hkMemTreeChunk* rst = HK_NULL;
        for (;;)
        {
				/// The amount of bytes at the end of the current chunk being examined
            hk_size_t trem = t->getChunkSize() - nb;
				/// See if we have a better match
            if (trem < rsize)
            {
					/// Save in v the best fit
                v = t;
					/// If its an exact match we are done
                if ((rsize = trem) == 0) break;
            }

            hkMemTreeChunk* rt = t->child[1];

				/// The shift here will return 0, unless the MSB is hit
            t = t->child[(sizebits >> (SIZE_T_BITSIZE- hk_size_t(1))) & 1];

            if (rt != HK_NULL && rt != t) rst = rt;

            if (t == HK_NULL)
            {
                t = rst; /* set t to least subtree holding sizes > nb */
                break;
            }
				/// shift up
            sizebits += sizebits;
        }
    }

    if (t == HK_NULL && v == HK_NULL)
    {
        /* set t to root of next non-empty treebin */
        hkBinMap leftBits = _leftBits(_indexToBit(idx)) & m_treemap;

        if (leftBits != 0)
        {
            hkBinMap leastbit = _leastBit(leftBits);
            hkBinIndex i = _bitToIndex(leastbit);
            t = m_treebins[i];
        }
    }

    while (t != HK_NULL)
    {
        /* find smallest of tree or subtree */
        hk_size_t trem = t->getChunkSize() - nb;
        if (trem < rsize)
        {
            rsize = trem;
            v = t;
        }
        t = t->leftMostChild();
    }

		/// If we couldn't find a block fail
	if (v== HK_NULL) return HK_NULL;

    /*  If dv is a better fit, return 0 so malloc will use it */
    //if (v != HK_NULL && rsize < (hk_size_t)(m_dvsize - nb))
    {
        HK_ASSERT(0x4243244,_isOkAddress(v));

        /* split */
        hkMemChunk*  r = v->chunkPlusOffset(nb);
        HK_ASSERT(0x3434344,v->getChunkSize() == rsize + nb);
        HK_ASSERT(0x3434342,_okNext(v,r));

        _unlinkLargeChunk(reinterpret_cast<hkMemTreeChunk*>(v));

		if (rsize < MIN_LARGE_SIZE)
		{
			v->setInuseAndPinuse(rsize + nb);

                /// We add the remainder too
            m_used += rsize + nb;
		}
		else
		{
			v->setSizeAndPinuseOfInuseChunk(nb);

                /// Alter m_used to keep up to date
            m_used += nb;

			r->setSizeAndPinuseOfFreeChunk(rsize);

			_insertLargeChunk( static_cast<hkMemTreeChunk*>(r),rsize);
		}

        return v->getPayload();
    }
    //return NULL;
}

hk_size_t
hkLargeBlockAllocator::_findLargestTreeBlockSize(hkMemTreeChunk* t,hk_size_t largest)
{
    while (t)
    {
            /// The amount of bytes at the end of the current chunk being examined
        hk_size_t chunkSize = t->getChunkSize();

        if (chunkSize > largest) { largest = chunkSize; }

            /// Go rightmost if we can
        if (t->child[1])
        {
            t = t->child[1];
            continue;
        }
            /// Else try leftmost
        t = t->child[0];
    }
    return largest;
}

hk_size_t
hkLargeBlockAllocator::findLargestBlockSize()
{
        /// Assume top is largest
    hk_size_t largest = m_topsize;

        /// Theres no point searching buckets smaller than what we have
    int smallestBin = _computeTreeIndex(largest);

        // Lets search the tree
    for (int i=NTREEBINS-1;i>=smallestBin;i--)
    {
            /// Look for a bin with nodes in it
        hkMemTreeChunk* t = m_treebins[i];

            /// Either the block we have or a block in this tree will be the largest
        if (t) return _findLargestTreeBlockSize(t,largest);
    }
        /// This must be the largest
    return largest;
}

void
hkLargeBlockAllocator::_makeTopValid() const
{
        /// Set is size + that its free
    m_top->head = m_topsize | hkMemChunk::PINUSE_BIT;
    hkMemChunk* footer = m_top->chunkPlusOffset(m_topsize);
    footer->prevFoot = m_topsize;
}

void*
hkLargeBlockAllocator::_allocFromTop(hk_size_t nb)
{
    //HK_ASSERT(0x34243,m_used == _calculateUsed());

    // Allocated
    m_used += nb;

    /* Split top */
    hk_size_t rsize = m_topsize -= nb;

    hkMemChunk* p = m_top;

    hkMemChunk* r = m_top = p->chunkPlusOffset(nb);

    r->head = rsize | hkMemChunk::PINUSE_BIT;
    r->prevFoot = nb;

    p->setSizeAndPinuseOfInuseChunk(nb);

    void* mem = p->getPayload();
    //check_top_chunk(gm, gm->top);
    //check_malloced_chunk(gm, mem, nb);

    //HK_ASSERT(0x34243,m_used == _calculateUsed());

    return mem;
}

hk_size_t
hkLargeBlockAllocator::getEstimatedAllocSize(hk_size_t size) const
{
    if (size<MIN_LARGE_SIZE-hkMemChunk::PAYLOAD_OFFSET) return MIN_LARGE_SIZE;
        /// Align + add the payload offset
    return ((size+hkMemChunk::ALIGN_MASK)&~hkMemChunk::ALIGN_MASK) + hkMemChunk::PAYLOAD_OFFSET;
}

hkBool
hkLargeBlockAllocator::_resizeSingleBlockServerPage(hk_size_t newSize)
{
    HK_ASSERT(0x34234324,_hasPages()&&m_server->isSingleBlockServer());
    hkMemPage* page = m_pages.m_next;

    hk_size_t outSize;
    if (!m_server->resize(page,page->m_size,newSize,outSize)) return false;

    // It worked
    hk_size_t footsize = m_top->chunkPlusOffset(m_topsize)->getChunkSize();

    int change = int(outSize) - int(page->m_size);
    change &= ~hkMemChunk::ALIGN_MASK;

    m_topsize += change;

    page->m_size = outSize;
    page->m_end += change;

    // New footer?
    hkMemChunk* newFooter = m_top->chunkPlusOffset(m_topsize);
    newFooter->head = (footsize - change) | hkMemChunk::CINUSE_BIT;

    return true;
}

/* nb is the padded amount of bytes */

void*
hkLargeBlockAllocator::_alloc(hk_size_t nb)
{
    if (m_treemap != 0)
    {
        //HK_ASSERT(0x34243,m_used == _calculateUsed());
        void* mem = _allocLarge(nb);
        if (mem)
        {
            //HK_ASSERT(0x34243,m_used == _calculateUsed());
            return mem;
        }
    }

        // See if there is enough memory in top
    if (nb + MIN_LARGE_SIZE < m_topsize  )
    {
        //HK_ASSERT(0x34243,m_used == _calculateUsed());
        void* mem = _allocFromTop(nb);
        //HK_ASSERT(0x34243,m_used == _calculateUsed());
        return mem;
    }

    return HK_NULL;
}

void*
hkLargeBlockAllocator::alloc(hk_size_t bytes)
{
  /*
       1. Find the smallest available binned chunk that fits, and use it
       2. If it is big enough, use the top chunk.
       3. Use the server to allocate more memory, and try again...
  */

    hk_size_t nb = _padRequest(bytes);

        /// This is the minimum allocation size
    if (nb<MIN_LARGE_SIZE) nb = MIN_LARGE_SIZE;

    void* p = _alloc(nb);
    if (p) return p;

    // Okay this is where we are going to have to create a new block - if we have a single block server
    // things are substantially simpler
    if (m_server->isSingleBlockServer()&&_hasPages())
    {
        hkMemPage* page = m_pages.m_next;
        if (_resizeSingleBlockServerPage(page->m_size + nb))
        {
            // Allocate from top
            return _allocFromTop(nb);
        }

        if (m_limitedListener)
		{
			m_limitedListener->cannotAllocate(nb);
            p = _alloc(nb);
            if (p) return p;

			/// Try the resize again?
			if (_resizeSingleBlockServerPage(page->m_size + nb))
			{
				// Allocate from top
				return _allocFromTop(nb);
			}
			/// Okay didn't work, time to cry
			m_limitedListener->allocationFailure(nb);
		}

        return HK_NULL;
    }

        /// Okay we need a whole new block
        /// We need space for both a header and a footer
    hk_size_t neededSize = nb + sizeof(hkMemPage) + hkMemChunk::PAYLOAD_OFFSET + hkMemChunk::ALIGN + MIN_LARGE_SIZE;
    hk_size_t reqSize = m_server->recommendSize(neededSize);

    hkMemPage* newPage = (hkMemPage*)m_server->allocate(reqSize,reqSize);
        // If we couldn't create the page then we failed
    if (!newPage)
	{
		if (!m_limitedListener) return HK_NULL;

			/// This could cause a garbage collet
		m_limitedListener->cannotAllocate(nb);
        p = _alloc(nb);
        if (p) return p;

			/// Work out the size again
		reqSize = m_server->recommendSize(neededSize);
		/// Okay we can try and allocate a page again..
		newPage = (hkMemPage*)m_server->allocate(reqSize,reqSize);
		if (!newPage)
		{
			m_limitedListener->allocationFailure(nb);
			return HK_NULL;
		}
    }

    // Set up the page
    newPage->m_numAllocs = 0;
    newPage->m_size = reqSize;
    newPage->m_start = (char*)(newPage+1);
    newPage->m_end = ((char*)newPage) + reqSize;
        /// Align forward
    newPage->m_start = (char*)((hk_size_t(newPage->m_start)+hkMemChunk::ALIGN_MASK)&~hkMemChunk::ALIGN_MASK);
        /// Align backward
    newPage->m_end = (char*)((hk_size_t(newPage->m_end))&~hkMemChunk::ALIGN_MASK);

    // Find where we are going to insert

    hkMemPage* cur = m_pages.m_next;
    while (cur != &m_pages && cur < newPage) { cur = cur->m_next; }

    // we want to add the page before this page, as its either hit the end or the page its on is at a higher address

    newPage->m_next = cur;
    newPage->m_prev = cur->m_prev;
    newPage->m_prev->m_next = newPage;
    cur->m_prev = newPage;

    // If there is a top we need to add it too the tree
    if (m_top != &m_zeroChunk)
    {
            /// Sets up stuff so its not all rubbish
        _makeTopValid();
            /// Insert so its available
        _insertLargeChunk( static_cast<hkMemTreeChunk*>(m_top),m_top->getChunkSize());
    }

        // Work out the new top
    m_topsize = newPage->getMaxChunkSize();
    m_top = newPage->getFirstChunk();
        // make it valid
    _makeTopValid();

        /// Mark the footer as in use
	{
		hkMemChunk* footerChunk = newPage->getFooter();
		HK_ASSERT(0x32423432,footerChunk == m_top->chunkPlusOffset(m_topsize));

		footerChunk->head = hkMemChunk::CINUSE_BIT;
		if (newPage->m_next != &m_pages)
		{
			/// There is a page in front so attach to it
			hkMemChunk* nextChunk = newPage->m_next->getFirstChunk();
			HK_ASSERT(0x32423432,nextChunk->isPinuse());
			hk_size_t footerSize = (char*)nextChunk - (char*)footerChunk;
			HK_ASSERT(0x34234,(footerSize&hkMemChunk::INUSE_BITS)==0);
			footerChunk->head = hkMemChunk::CINUSE_BIT|footerSize;
		}
	}
	{
			/// There may be a previous we need to sort
		if (newPage->m_prev != &m_pages)
		{
			hkMemChunk* prevFooter = newPage->m_prev->getFooter();
			hk_size_t chunkSize = (char*)m_top - (char*)prevFooter;
			HK_ASSERT(0x34234,(chunkSize&hkMemChunk::INUSE_BITS)==0);
			hk_size_t bits = (prevFooter->head&hkMemChunk::INUSE_BITS);
			prevFooter->head = bits|chunkSize;
			HK_ASSERT(0x34233423,prevFooter->isInuse()==true&&m_top->isInuse()==false&&m_top->isPinuse()==true);
		}
	}

        /// We can allocate from the top
    return _allocFromTop(nb);
}

void*
hkLargeBlockAllocator::criticalAlloc(hk_size_t size)
{
    size = (size + hkMemChunk::ALIGN + hkMemChunk::ALIGN_MASK)&~hkMemChunk::ALIGN_MASK;
	hkLargeBlockLimitedMemoryListener* listener = m_limitedListener;
	m_limitedListener = HK_NULL;
    // try allocating here
    void* out = alloc(size);
	m_limitedListener = listener;
    if (out)
    {
        /// Mark it
        *(AllocType*)out = NORMAL_ALLOC;
        return (void*)(((char*)out) + hkMemChunk::ALIGN);
    }
    out = m_server->criticalAlloc(size);
    if (out)
    {
        *(AllocType*)out = CRITICAL_ALLOC;
        return (void*)(((char*)out) + hkMemChunk::ALIGN);
    }
        /// Failed...
    return HK_NULL;
}

void
hkLargeBlockAllocator::criticalFree(void* ptr,hk_size_t size)
{
    size = (size + hkMemChunk::ALIGN + hkMemChunk::ALIGN_MASK)&~hkMemChunk::ALIGN_MASK;
    void* data = (void*)(((char*)ptr)-hkMemChunk::ALIGN);
    switch (*(AllocType*)data)
    {
        case NORMAL_ALLOC: free(data); break;
        case CRITICAL_ALLOC: m_server->criticalFree(data,size); break;
    }
}

void
hkLargeBlockAllocator::garbageCollect()
{
    // If we traverse, we want this set up correctly
    _makeTopValid();

    // Free any pages which are totally not in use
    {
        hkMemPage* page = m_pages.m_next;
        while (page != &m_pages)
        {
            // Lets see if all this memory is free
            hkMemChunk* chunk = page->getFirstChunk();
            if ((!chunk->isInuse())&&chunk->nextChunk() == page->getFooter())
            {
                hkMemPage* next = page->m_next;

                // This is a dead page.. we can free it
                // First delink
                page->m_prev->m_next = page->m_next;
                page->m_next->m_prev = page->m_prev;

				if (chunk == m_top)
				{
						/// If we freed the block with the top block, make top block invalid.
						/// No need to unlink the block as its never in the tree
					m_top = HK_NULL;
					m_topsize = 0;
				}
				else
				{
						// We need to unlink this
					_unlinkLargeChunk((hkMemTreeChunk*)chunk);
				}

                // Free it
                m_server->free((void*)page,page->m_size);
                // Next
                page = next;
            }
            else
            {
                page = page->m_next;
            }
        }
    }

    if (!_hasPages())
    {
        m_top = HK_NULL;
        m_topsize = 0;
        return;
    }

    if (m_server->isSingleBlockServer())
    {
        // We need to find the amount of space remaining in the top block
        hkMemPage* page = m_pages.m_next;

		// No point unless there is enough space
		if (m_topsize < 32*1024) return;

        hk_size_t usedSize = (((char*)m_top) + (hkMemChunk::PAYLOAD_OFFSET*2 + 256)) - page->getStart();
		//
        _resizeSingleBlockServerPage(usedSize);
        return;
    }

    /// Lets go looking for a new top block - find the largest block in a page
    /// NOTE! This means the top block is not the top of all allocations, merely the top of a page.
    {

			/// If there is a top block, we insert into tree whilst we look for a new one
		if (m_top)
		{
			_insertLargeChunk((hkMemTreeChunk*)m_top,m_topsize);
			/// Say there is no top block currently
			m_top = HK_NULL;
			m_topsize = 0;
		}

			/// Lets look for the best block

        hkMemChunk* bestChunk = HK_NULL;

        hkMemPage* page = m_pages.m_next;
        while (page != &m_pages)
        {
            hkMemChunk* chunk = page->getFooter();

            if (!chunk->isPinuse())
            {
                hkMemChunk* prev = chunk->previousChunk();
                if (bestChunk == HK_NULL || prev->getChunkSize()>bestChunk->getChunkSize())
                {
                    bestChunk = prev;
                }
            }
            page = page->m_next;
        }
        if (bestChunk)
        {
			// Need to unlink it - as it must be in the tree
			_unlinkLargeChunk((hkMemTreeChunk*)bestChunk);

			/// Its the new top block
            m_top = bestChunk;
            m_topsize = bestChunk->getChunkSize();
        }
    }
}

hkBool
hkLargeBlockAllocator::isValidAlloc(void* in)
{
    if (!hkMemChunk::isAligned(in)) return false;
    hkMemChunk* p = hkMemChunk::toChunk(in);
    if (!p->isInuse()) return false;

    // Okay lets see what page its in

    char* charAlloc = (char*)in;

    hkMemPage* page = m_pages.m_next;
    while (page != &m_pages)
    {
        // Work out if its in the range
        char* start = page->getStart();
        char* end = page->getEnd();

        if (charAlloc>=start&&charAlloc<end)
        {
            // Its in this block, but that doesn' make it valid

            hkMemChunk* cur = (hkMemChunk*)start;
            hkMemChunk* footer = (hkMemChunk*)(end - hkMemChunk::PAYLOAD_OFFSET);
            while (cur != footer)
            {
                hk_size_t chunkSize = cur->getChunkSize();
                if (cur == p) return true;

                /// Next block
                cur = cur->chunkPlusOffset(chunkSize);
            }
            // We didn't find it, so its not valid
            return false;
        }
        page = page->m_next;
    }

    return false;
}


void
hkLargeBlockAllocator::free(void* mem)
{
    HK_ASSERT(0x3423432,hkMemChunk::isAligned(mem));
    /*
        Consolidate freed chunks with preceeding or succeeding bordering
        free chunks, if they exist, and then place in a bin.  Intermixed
        with special cases for top.
    */
    if (mem == HK_NULL) return;

    //HK_ASSERT(0x34243,m_used == _calculateUsed());

    hkMemChunk* p = hkMemChunk::toChunk(mem);

    HK_ASSERT(0x3434343,_isOkAddress(p));
    HK_ASSERT(0x3443434,p->isInuse());

    hk_size_t psize = p->getChunkSize();

    /// We've freed it
    m_used -= psize;

    //
    hkMemChunk* next = p->chunkPlusOffset(psize);

    if (!p->isPinuse())
    {
        hk_size_t prevsize = p->prevFoot;

        hkMemChunk* prev = p->chunkMinusOffset(prevsize);
        HK_ASSERT(0x54325443,_isOkAddress(prev));

            /// Consolidate backward
        _unlinkLargeChunk(static_cast<hkMemTreeChunk*>(prev));

            // Work out the new size
        psize += prevsize;
        p = prev;
    }

    HK_ASSERT(0x342432,_okNext(p,next)&&next->isPinuse());
    if (!next->isInuse())
    {
        /* consolidate forward */
        if (next == m_top)
        {
            hk_size_t tsize = m_topsize += psize;
            m_top = p;

			p->head = tsize | hkMemChunk::PINUSE_BIT;

            /// Check its not in use
            HK_ASSERT(0x3425425,!p->isInuse());
            //HK_ASSERT(0x34243,m_used == _calculateUsed());

			return;
        }
        else
        {
            hk_size_t nsize = next->getChunkSize();
            psize += nsize;

                /// Unlink next
            _unlinkLargeChunk(static_cast<hkMemTreeChunk*>(next));

            p->setSizeAndPinuseOfFreeChunk(psize);
        }
    }
    else
    {
        p->setFreeWithPinuse(psize, next);
    }

    // Insert the chunk back
    _insertLargeChunk( static_cast<hkMemTreeChunk*>(p),psize);

    // Check the block is free
    //HK_ASSERT(0x2312321,_checkFreeChunk(p));
    //HK_ASSERT(0x34243,m_used == _calculateUsed());
}

hk_size_t
hkLargeBlockAllocator::getAllocSize(void* mem)
{
    hkMemChunk* p = hkMemChunk::toChunk(mem);
    HK_ASSERT(0x342434,_checkUsedAlloc(mem));
    return p->getPayloadSize();
}

hk_size_t
hkLargeBlockAllocator::getAllocTotalSize(void* mem)
{
    hkMemChunk* p = hkMemChunk::toChunk(mem);
    HK_ASSERT(0x342434,_checkUsedAlloc(mem));
    return p->getChunkSize();
}

void
hkLargeBlockAllocator::forAllAllocs(hkMemBlockCallback callback,void* param)
{
	// We should write into top just so we don't have to special case it
	m_top->head = m_topsize | hkMemChunk::PINUSE_BIT;

		// Okay lets traverse the pages
	hkMemPage* page = m_pages.m_next;
	while (page != &m_pages)
	{
		hkMemChunk* cur = (hkMemChunk*)page->getStart();
		hkMemChunk* footer = (hkMemChunk*)(page->getEnd() - hkMemChunk::PAYLOAD_OFFSET);
		while (cur != footer)
		{
			hk_size_t chunkSize = cur->getChunkSize();
			if (cur->isInuse())
			{
				// Callback with the block
				callback(cur->getPayload(),cur->getPayloadSize(),param);
			}

			/// Next block
			cur = cur->chunkPlusOffset(chunkSize);
		}

		// Onto the next page
		page = page->m_next;
	}
}

hkLargeBlockAllocator::Iterator
hkLargeBlockAllocator::getIterator()
{
	m_top->head = m_topsize | hkMemChunk::PINUSE_BIT;

    /// If there are no pages then ther is no memory
    if (m_pages.m_next == &m_pages) return Iterator();

	hkMemPage* page = m_pages.m_next;
    hkMemChunk* start = (hkMemChunk*)page->getStart();
    hkMemChunk* end = (hkMemChunk*)(page->getEnd() - hkMemChunk::PAYLOAD_OFFSET);

    return Iterator(start,page,end);
}

hkBool
hkLargeBlockAllocator::nextBlock(Iterator& iter)
{
    if (iter.m_chunk == HK_NULL) return false;
    // go to the next chunk
    iter.m_chunk = iter.m_chunk->nextChunk();
    /// if we are at the end we need to go to the next page
    if (iter.m_chunk == iter.m_end)
    {
        hkMemPage* page = iter.m_page->m_next;
        if (page == &m_pages)
        {
            // Make invalid
            iter.m_chunk = HK_NULL;
            return false;
        }
            /// Skip to the next page
        iter.m_page = page;
        iter.m_chunk = (hkMemChunk*)page->getStart();
        iter.m_end = (hkMemChunk*)(page->getEnd() - hkMemChunk::PAYLOAD_OFFSET);
    }
    // success
    return true;
}


hk_size_t
hkLargeBlockAllocator::_calculateUsed() const
{
    hk_size_t used = 0;

    _makeTopValid();

	hkMemPage* page = m_pages.m_next;
	while (page != &m_pages)
	{
        hkMemChunk* cur = page->getFirstChunk();
            /// The last chunk in this page
        hkMemChunk* footer = page->getFooter();
        while (cur != footer)
        {
            if (cur->isInuse())
            {
                used += cur->getChunkSize();
            }
            /// Step to next block
            cur = cur->nextChunk();
        }
            // Onto the next page
		page = page->m_next;
	}
    return used;
}


void
hkLargeBlockAllocator::calculateStatistics(hkMemoryStatistics& stats)
{
    stats.m_allocated = calculateTotalMemoryAllocated();
    //HK_ASSERT(0x34234,m_used == _calculateUsed());
    stats.m_used = m_used;
    stats.m_available = stats.m_allocated - m_used;
    stats.m_largestBlock = findLargestBlockSize();
    stats.m_totalAvailable = 0;
}

hk_size_t
hkLargeBlockAllocator::calculateTotalMemoryAllocated() const
{
    hk_size_t allocated = 0;
	hkMemPage* page = m_pages.m_next;
	while (page != &m_pages)
	{
            /// Accumulate the size
        allocated += page->m_size;
            // Onto the next page
		page = page->m_next;
	}
    return allocated;
}

#if 0

/// This has been disabled, because theres a bug in there which causes errors. Will look into again when the structures
/// have been cleaned up abit

void
hkLargeBlockAllocator::resizeAlloc(void* in,hk_size_t newSize)
{
        /// Work out the size the new chunk would need to be
		/// We add the PAYLOAD_OFFSET as it could bigger than the sizeof(hkMemChunk), as it takes into account alignment
    hk_size_t newChunkSize = (newSize + hkMemChunk::PAYLOAD_OFFSET + hkMemChunk::ALIGN_MASK)&~hkMemChunk::ALIGN_MASK;
        /// Must at least be as big as the min block size
    if (newChunkSize < MIN_LARGE_SIZE) newChunkSize = MIN_LARGE_SIZE;

    hkMemChunk* p = hkMemChunk::toChunk(in);
    HK_ASSERT(0x342434,_checkUsedAlloc(in));

        /// Get the chunk size
    hk_size_t chunkSize = p->getChunkSize();

        /// If the size is the same, we are done
    if (newChunkSize == chunkSize) return;

    HK_ASSERT(0x34242423,newChunkSize<chunkSize);
    if (newChunkSize>chunkSize) { return; }

        /// Work out the remainder size.
    hk_size_t remSize = chunkSize - newChunkSize;

        /// If the change is too small to make a new block, then we are done
    if (remSize <  MIN_LARGE_SIZE) { return; }

        /// This is where the new block will start
    hkMemChunk* remChunk = p->chunkPlusOffset(chunkSize - remSize);

        /// Get the next chunk
    hkMemChunk* next = p->chunkPlusOffset(chunkSize);

    HK_ASSERT(0x342432,_okNext(p,next)&&next->isPinuse());
    if (!next->isInuse())
    {
        /* consolidate forward */
        if (next == m_top)
        {
                /// Make the top bigger
            m_topsize += remSize;
                /// Make this the new top
            m_top = remChunk;

                /// Set the new head size
            remChunk->head = m_topsize | hkMemChunk::PINUSE_BIT;

                /// Need to fix the old block
            p->head = (p->head&hkMemChunk::PINUSE_BIT)|hkMemChunk::CINUSE_BIT|(chunkSize - remSize);

                /// p remains in use, m_top is not in use
            HK_ASSERT(0x3425425,p->isInuse()&&!m_top->isInuse());
            return;
        }
        else
        {
                /// Add the next block
            remSize += next->getChunkSize();

                /// Unlink next
            _unlinkLargeChunk(static_cast<hkMemTreeChunk*>(next));

                /// Set up rem chunk
            remChunk->setSizeAndPinuseOfFreeChunk(remSize);
        }
    }
    else
    {
        remChunk->setFreeWithPinuse(remSize, next);
    }
    // Insert the chunk back
    _insertLargeChunk( static_cast<hkMemTreeChunk*>(remChunk),remSize);

    // Check the block is free
    HK_ASSERT(0x2312321,_checkFreeChunk(remChunk));
}
#endif


hkBool
hkLargeBlockAllocator::_checkUsedAlloc(void* mem)
{
    hkMemChunk* p = hkMemChunk::toChunk(mem);

    if (!hkMemChunk::isAligned(mem)) return false;

    if (!_isOkAddress(p)) return false;

    if (!p->isInuse()) return false;
    /// Its size must be at least as large as the smallest block
    hk_size_t minSize = _padRequest(0);

    hk_size_t size = p->getChunkSize();

    if (size < minSize) return false;

    /// Look at the next block - its pinuse should be true, and its prevFoot should be the size of this block
    hkMemChunk* next = p->chunkPlusOffset(size);

    if (!next->isPinuse()) return false;

    // prevFoot is only set if the previous block is free
    if (!p->isPinuse())
    {
        hkMemChunk* prev = p->chunkMinusOffset(p->prevFoot);
        // Previous must be free (otherwise how could we be here
        if (prev->isInuse()!=false) return false;
        /// The previous block must be same size a prevFoot
        if (prev->getChunkSize() != p->prevFoot) return false;
    }

    return true;
}

hkBool
hkLargeBlockAllocator::_checkFreeChunk(hkMemChunk* p)
{
    if (!hkMemChunk::isAligned((void*)p)) return false;

		/// It can't be in use or how can it be free?
    if (p->isInuse()) return false;

    if (!_isOkAddress(p)) return false;

    // The block before and after must be used, because we always automatically combine

    hk_size_t size = p->getChunkSize();
    hkMemChunk* next = p->chunkPlusOffset(size);

        /// The previous is not in use
    if (next->isPinuse()) return false;
        /// This must be in use
    if (!next->isInuse()) return false;

        /// The previous must be in use
    if (!p->isPinuse()) return false;

        /// prevFoot must be invalid - because prevFoot is only valid when Pinuse is false (ie when its free),
        /// but it can't be free otherwise we would have consolidated it, as this block is supposedly free

    return true;
}

hkBool
hkLargeBlockAllocator::checkAllocations(void** allocs,int size)
{
    for (int i=0;i<size;i++)
    {
        if (!_checkUsedAlloc(allocs[i])) return false;
    }
    return true;
}

/* static */void
hkLargeBlockAllocator::_addAlloc(void* data,hk_size_t size,void* param)
{
    hkArray<void*>& array = *(hkArray<void*>*)param;
    array.pushBack(data);
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// selfTest

#ifdef HK_DEBUG

/* static */void HK_CALL
hkLargeBlockAllocator::allocatorTest(hkLargeBlockAllocator& allocator,int testSize)
{
	int maxPtrs = testSize/1000;
	if (maxPtrs <50 ) maxPtrs = 50;

    hkArray<void*> ptrs;
    hkPseudoRandomGenerator rand(12345);

    for (int i=0;i<testSize;i++)
    {
        int num = rand.getRand32();

        if ((num&15)>4&&ptrs.getSize()<maxPtrs)
        {
            // Add an allocation
            hk_size_t size = rand.getRand32()%50000;
            // do the allocation

            //if (size<100) size = 100;

            HK_ASSERT(0x4234324,allocator.checkAllocations(ptrs.begin(),ptrs.getSize()));

            void* alloc = allocator.alloc(size);
            if (alloc)
            {
                if (!allocator._checkUsedAlloc(alloc))
                {
                    HK_ASSERT(0x34234,allocator._checkUsedAlloc(alloc));
                }

                ptrs.pushBack(alloc);
                hkString::memSet(alloc,0,(int)size);
            }
            else
            {
                /// Failed to alloc

            }

            HK_ASSERT(0x4234324,allocator.checkAllocations(ptrs.begin(),ptrs.getSize()));
        }

#if 0
        if ((num&0x1000)&&ptrs.getSize()>0)
        {
            // We need to remove an allocation
            int index = rand.getRand32()%ptrs.getSize();
            void* alloc = ptrs[index];

            hk_size_t blockSize = allocator.getAllocSize(alloc);

            for (hk_size_t j=blockSize;j>=0;j--)
            {
                //allocator.resizeAlloc(alloc,j);

                hkString::memSet(alloc,0,(int)(j));
                if (j==0) break;
            }
        }
#endif

        if ((num&0x100)&&ptrs.getSize()>0)
        {
            // We need to remove an allocation
            int index = rand.getRand32()%ptrs.getSize();

            void* alloc = ptrs[index];
            HK_ASSERT(0x4234324,allocator.checkAllocations(ptrs.begin(),ptrs.getSize()));

            allocator.free(alloc);
            ptrs.removeAt(index);

            HK_ASSERT(0x4234324,allocator.checkAllocations(ptrs.begin(),ptrs.getSize()));
        }

        if (((num&0xff00)>>8) > 253)
        {
            // Lets check the callback stuff
            hkArray<void*> foundPtrs;

            allocator.forAllAllocs(_addAlloc,&foundPtrs);

            HK_ASSERT(0x32432423,foundPtrs.getSize() == ptrs.getSize());

            // Sort both
            hkSort(ptrs.begin(),ptrs.getSize(),_comparePointers);
            hkSort(foundPtrs.begin(),foundPtrs.getSize(),_comparePointers);

            for (int j=0;j<ptrs.getSize();j++)
            {
                HK_ASSERT(0x34234234,ptrs[j] == foundPtrs[j]);
            }
        }


        num = (rand.getRand32())&0xffff;
        if (num>4000 && num<4002)
        {
            /// Free them all
            HK_ASSERT(0x4234324,allocator.checkAllocations(ptrs.begin(),ptrs.getSize()));
            for (int i=0;i<ptrs.getSize();i++) allocator.free(ptrs[i]);
            ptrs.clear();
            HK_ASSERT(0x4234324,allocator.checkAllocations(ptrs.begin(),ptrs.getSize()));
        }
    }

    for (int i=0;i<ptrs.getSize();i++) allocator.free(ptrs[i]);
}


/* static */void HK_CALL
hkLargeBlockAllocator::selfTest()
{
    {
        hkSystemMemoryBlockServer server;
		hkLargeBlockAllocator allocator(&server);

        //allocatorTest(allocator,100000);
    }

	{
		const hk_size_t size = 1024*1024;
		void* mem = hkSystemMalloc(size,16);


		hkFixedMemoryBlockServer server(mem,size);
		hkLargeBlockAllocator allocator(&server);

		{
			// Right less put it to the test
			void* p0 = allocator.alloc(size-10*1024);
			HK_ASSERT(0x12313,p0);
			void* p1 = allocator.alloc(5*1024);
			HK_ASSERT(0x12313,p1);
				/// Should push this on a bucket, because its not next to top
			allocator.free(p0);

			// Okay lets allocate something that must go into p0s old memory
			p0 = allocator.alloc(10*1024);
			HK_ASSERT(0x12313,p0);

			allocator.free(p1);
			allocator.free(p0);
		}

        allocatorTest(allocator,100000);

		// Shouldn't we just have the top block and thats it?

		allocator.freeAll();

        hkSystemFree(mem);
	}
	{
		const hk_size_t size = 4096;
		char mem[size];

		hkFixedMemoryBlockServer server(mem,size);
		hkLargeBlockAllocator allocator(&server);

		void* p1 = allocator.alloc(10);
		void* p2 = allocator.alloc(20);
		void* p3 = allocator.alloc(30);

		allocator.free(p2);

		p2 = allocator.alloc(20);

		allocator.free(p1);
		allocator.free(p2);
		allocator.free(p3);
	}
}

#endif

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
