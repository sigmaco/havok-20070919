/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/Memory/hkMemory.h>

#include <Common/Base/Algorithm/Sort/hkSort.h>

// this
#include <Common/Base/Memory/hkDebugMemorySnapshot.h>


void
hkDebugMemorySnapshot::reset()
{
    if (m_pointers)
    {
        hkSystemFree(m_pointers);
        hkSystemFree(m_info);
    }
    m_pointers = HK_NULL;
    m_info = HK_NULL;
    m_size = 0;
}

void
hkDebugMemorySnapshot::ascendingOrder()
{
    if (m_size<=1) return;

    void*** sortPtrs = (void***)hkSystemMalloc(sizeof(void**)*m_size,16);
    for (int i=0;i<m_size;i++)
    {
        sortPtrs[i] = &m_pointers[i];
    }

    /// sort them
    hkSort(sortPtrs,m_size,_comparePointers);

    // make new space for the pointers

    void** ptrs = (void**) hkSystemMalloc(sizeof(void*)*m_size,16);
    hkDebugMemory::PointerInfo* info = (hkDebugMemory::PointerInfo*)hkSystemMalloc(sizeof(hkDebugMemory::PointerInfo)*m_size,16);

    for (int i=0;i<m_size;i++)
    {
        ptrs[i] = *sortPtrs[i];

        hk_size_t offset = sortPtrs[i] - m_pointers;
        info[i] = m_info[offset];
    }

	hkSystemFree(sortPtrs);

    hkSystemFree(m_pointers);
    hkSystemFree(m_info);

    m_pointers = ptrs;
    m_info = info;
}

void
hkDebugMemorySnapshot::subtract(hkDebugMemorySnapshot& rhs)
{
    ascendingOrder();
    rhs.ascendingOrder();

    void** cur = m_pointers;
    void** curEnd = cur + m_size;
    void** sub = rhs.m_pointers;
    void** subEnd = sub + rhs.m_size;

    while (cur<curEnd && sub < subEnd)
    {
        char* curPtr = (char*)*cur;
        char* subPtr = (char*)*sub;

        if (curPtr == subPtr)
        {
            // Remove
            *cur = HK_NULL;
            cur ++;
            sub ++;
            continue;
        }

            // Which one do we move...
        if (curPtr < subPtr)
        {
            cur ++;
        }
        else
        {
            sub ++;
        }
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
