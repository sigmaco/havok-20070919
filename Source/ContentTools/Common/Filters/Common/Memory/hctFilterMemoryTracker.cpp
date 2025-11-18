/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

hctFilterMemoryTracker::hctFilterMemoryTracker() 
: m_chunkAllocs(HK_NULL), m_allocs(HK_NULL), m_alignedAllocs(HK_NULL) 
{ 
}

hctFilterMemoryTracker::~hctFilterMemoryTracker()
{
	deallocateAll();
}
	
inline void hctFilterMemoryTracker::deallocateAll()
{
	MemoryAlloc* na = m_allocs;
	while (na)
	{
		MemoryAlloc* next = na->m_next;
		hkDeallocate(na->m_mem);
		hkDeallocateChunk(na, 1, HK_MEMORY_CLASS_EXPORT);
		na = next;
	}
	m_allocs = HK_NULL;
	
	MemoryAlloc* aa = m_alignedAllocs;
	while (aa)
	{
		MemoryAlloc* next = aa->m_next;
		hkAlignedDeallocate(aa->m_mem);
		hkDeallocateChunk(aa, 1, HK_MEMORY_CLASS_EXPORT);
		aa = next;
	}
	m_alignedAllocs = HK_NULL;

	MemoryChunk* mc = m_chunkAllocs;
	while(mc)
	{
		MemoryChunk* next = mc->m_next;
		hkDeallocateChunk(mc->m_mem, mc->m_memSize, mc->m_memClass);
		hkDeallocateChunk(mc, 1, HK_MEMORY_CLASS_EXPORT);
		mc = next;
	}
	m_chunkAllocs = HK_NULL;
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
