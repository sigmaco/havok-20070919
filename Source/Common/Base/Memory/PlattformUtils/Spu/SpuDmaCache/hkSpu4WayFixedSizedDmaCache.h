/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_4WAY_FIXED_DMA_CACHE_H
#define HK_SPU_4WAY_FIXED_DMA_CACHE_H


#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>


/// This is a 4-way associative cache, we're using 4 cache lines per row
/// Cache line replacement policy is guaranteed to be least recently used.
template <typename ElemType, int numCacheRows>
class hkSpu4WayFixedSizedDmaCache
{

	public:

			// Initialize the cache
		HK_FORCE_INLINE void init();

			// For debug checks only, but has to be called
		HK_FORCE_INLINE void exit();

			/// Tests if an address (in main memory) is in the cache - should only be used for asserts.
		HK_FORCE_INLINE bool testHit(const void *addressInMainMemory) const;

		/// Upload data from main memory onto SPU memory.
		///
		/// Immediately returns a valid POINTER to the object, although the object DATA might
		/// not be valid yet (unless dma has already finished or object already was found in cache).
		HK_FORCE_INLINE const ElemType* getFromMainMemory(HK_CPU_PTR(const void *) addressInMainMemory, int dmaGroup, hkSpuDmaManager::READ_MODE mode = hkSpuDmaManager::READ_ONLY, int transferSize = sizeof(ElemType));

		/// Upload data from main memory onto SPU memory.
		///
		/// Returns a valid POINTER to the object (since we'll have waited for dma completion if object not already in cache)
		HK_FORCE_INLINE const ElemType* getFromMainMemoryNoGroupAndWaitForCompletion(HK_CPU_PTR(const void *) addressInMainMemory, int transferSize = sizeof(ElemType));

	public:

		struct CacheRow4Way
		{
	
#if defined(HK_PLATFORM_PS3SPU)
			vec_uint4	m_spuAddresses;

			vec_uint4	m_originalAddresses;

			vec_uint4	m_age;	// The age of each entry (used for LRU)

			vec_uint4	m_padding;
#else
			const ElemType*	m_spuAddresses[4];

			const void*		m_originalAddresses[4];

			int				m_age[4];

			int				m_padding[4];
#endif
		};


	private:

		HK_FORCE_INLINE int calcCacheRowIndex(void* addr, int mod) const;
		HK_FORCE_INLINE const ElemType* cacheLookup( const void *address, CacheRow4Way& row, int& cacheLineIdx );

	public:

		HK_ALIGN16( hkUchar m_lines[ numCacheRows * 4 * sizeof(ElemType) ] );
		CacheRow4Way  m_rows [ numCacheRows ];

	public:

		// Cache Statistics
		HK_ON_DEBUG( hkPadSpu<int> m_hits );
		HK_ON_DEBUG( hkPadSpu<int> m_misses );

};


#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpu4WayFixedSizedDmaCache.inl>



#endif // HK_SPU_4WAY_FIXED_DMA_CACHE_H

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
