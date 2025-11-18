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

#include <Common/Base/Memory/Memory/FreeList/FixedMemoryBlockServer/hkFixedMemoryBlockServer.h>

hkFixedMemoryBlockServer::hkFixedMemoryBlockServer(void* startIn,hk_size_t size)
{
    char* start = ((char*)startIn);
    char* end = start + size;

    // Align them
    m_start = (char*)(hk_size_t(start + ALIGN-1) & ~hk_size_t(ALIGN-1));
    m_end = (char*)(hk_size_t(end) & ~hk_size_t(ALIGN-1));
    m_limit = m_end;
    m_break = m_start;
    /// Okay this is complete hackery. I want it to be big, but I need enough room so that it will use up a few pages
    m_minAllocSize = 32*1024;
}

hk_size_t
hkFixedMemoryBlockServer::recommendSize(hk_size_t size)
{
    /// Else work out the biggest remaining, and ig thats not big enough we must just return what was input
    hk_size_t left = m_limit - m_break;
    return (left>=size)?left:size;
}

void*
hkFixedMemoryBlockServer::allocate(hk_size_t size,hk_size_t& sizeOut)
{
        /// If there is a break then we can allocate no more
    if (m_break != m_start) return HK_NULL;

    hk_size_t totalSize = m_limit-m_start;
    if (totalSize < size) { return HK_NULL; }

	m_break = m_start + totalSize;

    sizeOut = totalSize;
    return (void*)m_start;
}

hkBool
hkFixedMemoryBlockServer::resize(void* data,hk_size_t oldSize,hk_size_t newSize,hk_size_t& sizeOut)
{
    /// Something must have been allocated, and it must start at the start of this block
    HK_ASSERT(0x32432432,data == (void*)m_start);
    HK_ASSERT(0x34234234,hk_size_t(m_break - m_start) == oldSize);

        /// Eh? We've given a block that doesn't belong to us
    if ((void*)m_start != data) return false;

    char* newBreak = m_start + newSize;
        /// If its outside the range something has gone wrong
    if (newBreak < m_start || newBreak >m_limit) return false;
        /// Else thats out new break
    m_break = newBreak;
    sizeOut = newBreak - m_start;
    return true;
}

void
hkFixedMemoryBlockServer::free(void* data,hk_size_t size)
{
    if (m_break == m_start || hk_size_t(m_break-m_start) != size)
    {
        /// Eh? Nothings been allocated so how can I free it
        HK_BREAKPOINT(0);
        return;
    }
    HK_ASSERT(0x3424234,data == m_start);
    /// Say its all deallocated
    m_break = HK_NULL;
}

hk_size_t
hkFixedMemoryBlockServer::getTotalAvailableMemory()
{
    return m_limit - m_break;
}

hk_size_t
hkFixedMemoryBlockServer::getMemoryLimit()
{
        /// If there is no limit set, return 0
    if (m_limit == m_end) return 0;
        /// The amount of memory being served
    return m_limit - m_start;
}

hkBool
hkFixedMemoryBlockServer::setMemoryLimit(hk_size_t size)
{
    if (size==0)
    {
        /// If there is no limit, just set
        m_limit = m_end;
        return true;
    }

    char* limit = m_start + size;
    if (limit > m_end) return false;
    if (limit < m_break) return false;

    m_limit = limit;
    return true;
}

void*
hkFixedMemoryBlockServer::criticalAlloc(hk_size_t size)
{
    return hkThreadMemory::getInstance().allocateStack(int(size));
}

void
hkFixedMemoryBlockServer::criticalFree(void* data,hk_size_t size)
{
    hkThreadMemory::getInstance().deallocateStack(data);
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
