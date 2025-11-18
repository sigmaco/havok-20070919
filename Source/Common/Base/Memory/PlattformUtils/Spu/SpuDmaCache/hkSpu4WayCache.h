/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_4WAY_CACHE_H
#define HK_SPU_4WAY_CACHE_H


#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>
#include <Common/Base/hkBase.h>


/// This is a code-size efficient 4-way associative cache using 4 cache lines per cache row.
/// Cache line replacement policy is guaranteed to be 'least recently used'.
/// This cache will always stall code execution if the ordered data cannot be found in the cache and will
/// get it from main memory using a dma transfer.
/// The cache does not hold its own buffer but will use an externally allocated buffer. The user has to take care
/// of allocating and deallocating this buffer himself.
/// The getFromMainMemory() functions are available both as inlined and out-of-line, while the internal function
/// to actually fetch the data from main memory will always be out-of-line.
class hkSpu4WayCache
{

public:

	// Return the necessary buffer size; the user has to allocate this buffer and pass it in using initBuffer()
	HK_FORCE_INLINE static int getBufferSize(int elemSize, int numCacheRows);

	// Initialize the basic cache values and return the necessary buffer size; the user has to allocate this buffer and pass it in using initBuffer()
	HK_FORCE_INLINE int initAndGetBufferSize(int elemSize, int numCacheRows, hkSpuDmaManager::READ_MODE readMode);

	// Initialize the cache buffer; the buffer has to be 16byte aligned!
	void initBuffer(void* buffer);

	// Returns a pointer to the cache's buffer; this is equal to the pointer passed in by the user during the call to initBuffer()
	HK_FORCE_INLINE void* getBuffer();

	// For debug checks only, but has to be called
	HK_FORCE_INLINE void exit();

	/// Tests if an address (in main memory) is in the cache - should only be used for asserts.
	HK_FORCE_INLINE bool testHit(HK_CPU_PTR(const void *) addressInMainMemory) const;

	/// Flushes an address (in main memory) from the cache.
	HK_FORCE_INLINE void flush(HK_CPU_PTR(const void *) addressInMainMemory);

	/// Upload data from main memory onto SPU memory.
	///
	/// This call will either be executed very fast (if the data is still available in the cache) or it
	/// will stall while fetching the data from main memory using a dma transfer.
	const void* getFromMainMemory(HK_CPU_PTR(const void *) addressInMainMemory, int transferSize);

	/// The inlined version of getFromMainMemory(). This version allows to explicitly decide whether to wait for the dma transfer to be completed or not.
	HK_FORCE_INLINE const void* getFromMainMemoryInlined(HK_CPU_PTR(const void *) addressInMainMemory, int transferSize, int dmaGroup, bool waitForDmaCompletion);

public:

	struct CacheRow4Way
	{
#if defined(HK_PLATFORM_PS3SPU)
		vec_uint4	m_spuAddresses;
		vec_uint4	m_originalAddresses;
		vec_uint4	m_age;	// The age of each entry (used for LRU)
		vec_uint4	m_padding;
#else
		void*		m_spuAddresses[4];
		const void*	m_originalAddresses[4];
		int			m_age[4];
		int			m_padding[4];
#endif
	};


private:

	HK_FORCE_INLINE CacheRow4Way& calcCacheRow(HK_CPU_PTR(const void *) addressInMainMemory) const;
	HK_FORCE_INLINE const void* cacheLookup(HK_CPU_PTR(const void *) addressInMainMemory, CacheRow4Way& cacheRow);

	const void* getObject(HK_CPU_PTR(const void *) addressInMainMemory, int transferSize, int dmaGroup, CacheRow4Way& row, bool waitForDmaCompletion);

public:

	// Cache Statistics
	HK_ON_DEBUG( hkPadSpu<int> m_hits   );
	HK_ON_DEBUG( hkPadSpu<int> m_misses );

protected:

	hkPadSpu<int>							m_readMode;
	hkPadSpu<int>							m_elemSize;
	hkPadSpu<int>							m_cacheRowMask;
	hkPadSpu<int>							m_numCacheRows;
	hkPadSpu<hkUint8*>						m_lines; // if you change the order of m_lines & m_rows here, don't forget to adjust the implementation of getBuffer()!
	hkPadSpu<CacheRow4Way*>					m_rows;

};


#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpu4WayCache.inl>

template <typename TYPE>
HK_ALWAYS_INLINE const TYPE* HK_CALL hkGetArrayElemWithByteStridingUsingCache( const TYPE* base, int index, int elemsize, hkSpu4WayCache* cache, const int cacheLineSize, int dmaGroup = HK_SPU_DMA_GROUP_STALL , bool waitForDmaCompletion = true )
{
	HK_ASSERT2(0x65e4e432, ((hkUlong)base & (elemsize-1)) == 0, "Base must be aligned on proper elemsize boundary");
	HK_ASSERT2(0x65e4e432, (cacheLineSize % elemsize) == 0, "Elements must fit evenly into cache");
	hkUlong arrayAddrPpu = reinterpret_cast<hkUlong>(base) + ( index * elemsize );
	const int mask  = cacheLineSize-1;
	hkUlong arrayAddrAligned = arrayAddrPpu & (~mask);
	hkUlong alignedDataSpu = (hkUlong)cache->getFromMainMemoryInlined( (const void*)arrayAddrAligned , cacheLineSize, dmaGroup, waitForDmaCompletion );
	return reinterpret_cast<const TYPE*> ( alignedDataSpu + (arrayAddrPpu & mask) );
}

template <typename TYPE>
HK_ALWAYS_INLINE const TYPE* HK_CALL hkGetArrayElemUsingCache( const TYPE* base, int index, hkSpu4WayCache* cache, const int cacheLineSize, int dmaGroup = HK_SPU_DMA_GROUP_STALL , bool waitForDmaCompletion = true )
{
	return hkGetArrayElemWithByteStridingUsingCache( base, index, sizeof(TYPE), cache, cacheLineSize, dmaGroup, waitForDmaCompletion );
}

#endif // HK_SPU_4WAY_CACHE_H

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
