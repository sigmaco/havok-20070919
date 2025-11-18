/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_8WAY_FIXED_DMA_CACHE_H
#define HK_SPU_8WAY_FIXED_DMA_CACHE_H


#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>


class hkSpu8WayFixedSizedDmaCacheBase
{
	public:

		struct CacheRow8Way
		{
#if defined(HK_PLATFORM_PS3SPU)
			vec_uint4	m_spuAddressesA;
			vec_uint4	m_spuAddressesB;

			vec_uint4	m_originalAddressesA;
			vec_uint4	m_originalAddressesB;

			vec_uint4	m_ageA;	// The age of each entry (used for LRU)
			vec_uint4	m_ageB;	// The age of each entry (used for LRU)

			vec_uint4	m_padA;
			vec_uint4	m_padB;
#else
			const void*	m_spuAddresses[8];
			const void*	m_originalAddresses[8];
			int			m_age[8];
			int			m_padding[8];
#endif
		};

	public:

		// Cache Statistics
		HK_ON_DEBUG( hkPadSpu<int> m_hits   );
		HK_ON_DEBUG( hkPadSpu<int> m_misses );

	public:

			// Initialize the cache
		void baseInit(CacheRow8Way* rows, int numCacheRows, int elemSize, void* cacheLines);

	protected:

		const void* getObject(const void *address, CacheRow8Way& row, int dmaGroup, int transferSize, hkSpuDmaManager::READ_MODE mode);

};


/// This is a 8-way associative cache, we're using 8 cache lines per row
/// Cache line replacement policy is guaranteed to be least recently used.
template <typename ElemType, int numCacheRows>
class hkSpu8WayFixedSizedDmaCache: public hkSpu8WayFixedSizedDmaCacheBase
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

	private:

		HK_FORCE_INLINE CacheRow8Way&	calcCacheRow(const void* address) const;
		HK_FORCE_INLINE const ElemType*	cacheLookup (const void* address, CacheRow8Way* rows, int elemSize, void* cacheLines);

	public:

		HK_ALIGN16( hkUchar m_lines[ numCacheRows * 8 * sizeof(ElemType) ] );
		CacheRow8Way m_rows [ numCacheRows ];

};


#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpu8WayFixedSizedDmaCache.inl>


#endif // HK_SPU_8WAY_FIXED_DMA_CACHE_H

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
