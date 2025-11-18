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

#include <Common/Base/Memory/Memory/FreeList/SystemMemoryBlockServer/hkSystemMemoryBlockServer.h>

hkSystemMemoryBlockServer::hkSystemMemoryBlockServer(hk_size_t minBlockSize):
	m_allocated(0),
    m_memoryLimit(0)
{
    /// Okay this is complete hackery. I want it to be big, but I need enough room so that it will use up a few pages
    if (minBlockSize == 0)
    {
        m_minAllocSize = 128*1024;
    }
    else
    {
        m_minAllocSize = minBlockSize;
    }
}

hk_size_t
hkSystemMemoryBlockServer::recommendSize(hk_size_t size)
{
	// If we have a limit, just alloc the remaining
	if (m_memoryLimit)
	{
		hk_size_t remaining = m_memoryLimit - m_allocated;
		/// If its doesn't fit we just have to return the size, as this function should
		/// never return a size less than what is passed in
		if (remaining < size) return size;
		return remaining;
	}
    if (size<m_minAllocSize) return m_minAllocSize;

    if (m_memoryLimit)
    {
        /// Lets just return a chunk thats as big as whats remaining
        hk_size_t remaining = m_memoryLimit - m_allocated;
        if (size<remaining) return remaining;
    }

    const hk_size_t roundUp = 32*1024;
    return ( size + roundUp-1)&~(roundUp-1);
}

void*
hkSystemMemoryBlockServer::allocate(hk_size_t size,hk_size_t& sizeOut)
{
    if (m_memoryLimit != 0&&m_allocated + size > m_memoryLimit)
    {
        /// If we are over the limit return HK_NULL
        return HK_NULL;
    }

        /// Its probably bigger but we've got no way of knowing through this allocator
    sizeOut = size;
    m_allocated += size;
    return hkSystemMalloc((int)size,16);
}

void
hkSystemMemoryBlockServer::free(void* data,hk_size_t size)
{
    m_allocated -= size;
    hkSystemFree(data);
}

hk_size_t
hkSystemMemoryBlockServer::getTotalAvailableMemory()
{
    if (m_memoryLimit ==0) return hkMemoryStatistics::INFINITE_SIZE;
    return m_memoryLimit - m_allocated;
}


hk_size_t
hkSystemMemoryBlockServer::getMemoryLimit()
{
    return m_memoryLimit;
}
hkBool
hkSystemMemoryBlockServer::setMemoryLimit(hk_size_t size)
{
    if (size==0)
    {
            /// Remove any limit
        m_memoryLimit = size;
        return true;
    }

        /// More than thats already been allocated, so can't be done
    if (m_allocated > size) return false;

        /// Set it
    m_memoryLimit = size;
    return true;
}

void*
hkSystemMemoryBlockServer::criticalAlloc(hk_size_t size)
{
    return hkSystemMalloc((int)size,16);
}

void
hkSystemMemoryBlockServer::criticalFree(void* data,hk_size_t size)
{
    hkSystemFree(data);
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
