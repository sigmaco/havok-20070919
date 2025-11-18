/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpu8WayFixedSizedDmaCache.h>
#include <Common/Base/hkBase.h>




void hkSpu8WayFixedSizedDmaCacheBase::baseInit(CacheRow8Way* rows, int numCacheRows, int elemSize, void* cacheLines)
{
	HK_ASSERT2(0xad67d899, hkMath::isPower2(numCacheRows), "Number of cache rows must be a power of 2.");
	HK_ASSERT(0xadd7d89a, hkMath::isPower2(elemSize) );
	HK_ASSERT(0xadd7d89b, hkMath::isPower2(sizeof(CacheRow8Way)) );

#if defined(HK_DEBUG)
	m_misses = 0;
	m_hits = 0;
#endif

#if defined(HK_PLATFORM_PS3SPU)
	static const vec_uint4 ageInitA = {0,1,2,3};
	static const vec_uint4 ageInitB = {4,5,6,7};
	vec_uint4 baseOffset = { elemSize * 0, elemSize * 1, elemSize * 2, elemSize * 3 };
	const vec_uint4 baseInc = {elemSize * 4, elemSize * 4, elemSize * 4, elemSize * 4 };
	vec_uint4 baseAddress = spu_add( spu_splats( (unsigned int) cacheLines ), baseOffset);

	// Initialize the cache rows
	for (int r=0; r < numCacheRows; r++)
	{
		rows->m_ageA = ageInitA;
		rows->m_ageB = ageInitB;

		rows->m_originalAddressesA = spu_splats(0U);
		rows->m_originalAddressesB = spu_splats(0U);

		rows->m_spuAddressesA = baseAddress;
		baseAddress = spu_add( baseAddress, baseInc );
		rows->m_spuAddressesB = baseAddress;
		baseAddress = spu_add( baseAddress, baseInc );
		rows++;
	}
#else
	for (int r=0; r < numCacheRows; r++)
	{
		for (int i=0; i < 8; i++)
		{
			rows->m_spuAddresses[i]			= hkAddByteOffset(cacheLines, (r*8 + i) * elemSize );
			rows->m_originalAddresses[i]	= 0;
			rows->m_age[i]					= i;
		}
		rows++;
	}
#endif
}


const void* hkSpu8WayFixedSizedDmaCacheBase::getObject(const void *address, CacheRow8Way& row, int dmaGroup, int transferSize, hkSpuDmaManager::READ_MODE mode)
{
	// Cache miss
	HK_ON_DEBUG( m_misses = m_misses + 1; )

#if defined(HK_PLATFORM_PS3SPU)

	vec_uint4 addressV  = spu_splats( (unsigned int)address );

	// Find the lru cache line - This is the oldest one (max age)

		// find max of all ages and move max to ageMax.xyzw
	vec_uint4 ageMax;
	{
		vec_uint4 cmp = spu_cmpgt( row.m_ageA, row.m_ageB );
		ageMax = spu_sel( row.m_ageB, row.m_ageA, cmp );

		vec_uint4 shiftAge = vec_rotl( ageMax, 8 );
		cmp = spu_cmpgt( ageMax, shiftAge );
		ageMax = spu_sel( shiftAge, ageMax, cmp );

		shiftAge = spu_shuffle(ageMax,ageMax, HK_VECTOR4_SHUFFLE(1,0,3,2));
		cmp = spu_cmpgt( ageMax, shiftAge );
		ageMax = spu_sel( shiftAge, ageMax, cmp );
	}

	vec_uint4 maskA = spu_cmpeq( ageMax, row.m_ageA );
	vec_uint4 maskB = spu_cmpeq( ageMax, row.m_ageB );

	vec_uint4 spuaddressVA = spu_orx( spu_and(row.m_spuAddressesA, maskA ) );
	vec_uint4 spuaddressVB = spu_orx( spu_and(row.m_spuAddressesB, maskB ) );

	vec_uint4 originalAddressesA	= spu_sel ( row.m_originalAddressesA, addressV, maskA );
	vec_uint4 originalAddressesB	= spu_sel ( row.m_originalAddressesB, addressV, maskB );

	vec_uint4 ageA					= spu_andc( row.m_ageA, maskA );
	vec_uint4 ageB					= spu_andc( row.m_ageB, maskB );

	spuaddressVA = spu_or( spuaddressVA, spuaddressVB );

	row.m_originalAddressesA = originalAddressesA;
	row.m_originalAddressesB = originalAddressesB;

	row.m_ageA = ageA;
	row.m_ageB = ageB;

	void* object = (void*)( si_to_ptr((qword)spuaddressVA) );

#else

	// Find the lru cache way
	int max = -1;
	int lruIndex = 0;
	for (int i=0; i < 8; i++)
	{
		if ( row.m_age[i] > max)
		{
			max = row.m_age[i];
			lruIndex = i;
		}
	}

	if ( row.m_originalAddresses[ lruIndex ] )
	{
		HK_SPU_DMA_PERFORM_FINAL_CHECKS( row.m_originalAddresses[ lruIndex ], row.m_spuAddresses[ lruIndex ], 0 );
	}

	row.m_originalAddresses[ lruIndex ] = address;
	row.m_age              [ lruIndex ] = 0;

	void* object = const_cast<void*>( row.m_spuAddresses[ lruIndex ] );

#endif

	hkSpuDmaManager::getFromMainMemory(object, address, transferSize, mode, dmaGroup);
	return object;
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
