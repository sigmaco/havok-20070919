/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


template <typename ElemType, int numCacheRows>
hkSpu8WayFixedSizedDmaCacheBase::CacheRow8Way& hkSpu8WayFixedSizedDmaCache<ElemType, numCacheRows>::calcCacheRow(const void* addr) const
{
	hkUint32 addrI = hkUint32(hkUlong(addr));
	if ( sizeof(ElemType) > sizeof(CacheRow8Way) )
	{
		addrI = addrI / (sizeof(ElemType) / sizeof(CacheRow8Way));
	}
	int offset = addrI  & ((numCacheRows-1) * sizeof(CacheRow8Way));

	CacheRow8Way* row = hkAddByteOffset(const_cast<CacheRow8Way*>(&m_rows[0]), offset);
	return *row;
}


template <typename ElemType, int numCacheRows>
void hkSpu8WayFixedSizedDmaCache<ElemType, numCacheRows>::init()
{
	baseInit(&m_rows[0], numCacheRows, sizeof(ElemType), &m_lines[0]);
}


template <typename ElemType, int numCacheRows>
void hkSpu8WayFixedSizedDmaCache<ElemType, numCacheRows>::exit()
{
#if defined(HK_SIMULATE_SPU_DMA_ON_CPU)
	for (int r = 0; r < numCacheRows; r++)
	{
		CacheRow8Way* row = &m_rows[r];

		for (int i=0; i < 8; i++ )
		{
			if ( row->m_originalAddresses[i])
			{
				HK_SPU_DMA_PERFORM_FINAL_CHECKS( row->m_originalAddresses[i], &m_lines[ (r*8*sizeof(ElemType)) + (i*sizeof(ElemType)) ], 0);
			}
		}
	}
#endif
}


// returns true if hit, false otherwise
template <typename ElemType, int numCacheRows>
bool hkSpu8WayFixedSizedDmaCache<ElemType, numCacheRows>::testHit(const void* addressInMainMemory) const
{
	const CacheRow8Way& row = calcCacheRow(addressInMainMemory);

#if defined(HK_PLATFORM_PS3SPU)

	vec_uint4 addressV = spu_splats( (unsigned int)addressInMainMemory );

	vec_uint4 maskA = spu_cmpeq( addressV, row.m_originalAddressesA );
	vec_uint4 maskB = spu_cmpeq( addressV, row.m_originalAddressesB );

	// Or across the result to place it in correct position for return;
	maskA = spu_orx( maskA );
	maskB = spu_orx( maskB );
	maskA = spu_or( maskA, maskB);
	return (const ElemType*)spu_extract(maskA, 0); 
#else

	for (int i=0; i < 8; i++)
	{
		if (row.m_originalAddresses[i] == addressInMainMemory)
		{
			return true;
		}
	}
	return false;

#endif
}


// returns the spu address if hit, null otherwise
template <typename ElemType, int numCacheRows>
const ElemType* hkSpu8WayFixedSizedDmaCache<ElemType, numCacheRows>::cacheLookup(const void* addressInMainMemory, CacheRow8Way* row, int elemSize, void* cacheLines)
{
#if defined(HK_PLATFORM_PS3SPU)

	vec_uint4 ones = {1,1,1,1};

	vec_uint4 addressV = spu_splats( (unsigned int)addressInMainMemory ); // Should reduce to just ila but doesn't
	
	vec_uint4 maskA = spu_cmpeq( addressV, row->m_originalAddressesA );
	vec_uint4 maskB = spu_cmpeq( addressV, row->m_originalAddressesB );

	vec_uint4 ageA = row->m_ageA;
	vec_uint4 ageB = row->m_ageB;

	// Use the mask to select the spu address
	vec_uint4 resultA = spu_and( maskA, row->m_spuAddressesA );
	vec_uint4 resultB = spu_and( maskB, row->m_spuAddressesB );

	// Increment age for all other lines, reset for hit line
	ageA = spu_andc( spu_add( ageA, ones ), maskA );
	ageB = spu_andc( spu_add( ageB, ones ), maskB );

	 // Or across the result to place it in correct position for return;
	resultA = spu_orx( resultA );
	resultB = spu_orx( resultB );
	resultA = spu_or( resultA, resultB );

	row->m_ageA = ageA;
	row->m_ageB = ageB;

	return (const ElemType*)spu_extract(resultA, 0); 
#else

	for (int i=0; i < 8; i++)
	{
		row->m_age[i]++; // make all lines older
	}

	for (int i=0; i < 8; i++)
	{
		if (row->m_originalAddresses[i] == addressInMainMemory)
		{
			row->m_age[i] = 0; // reset age for this line
			return (const ElemType*)row->m_spuAddresses[i];
		}
	}

	return HK_NULL;
#endif
}


// this function will either return an already cached object or start prefetching it
template <typename ElemType, int numCacheRows>
const ElemType* hkSpu8WayFixedSizedDmaCache<ElemType, numCacheRows>::getFromMainMemory(HK_CPU_PTR(const void *) addressInMainMemory, int dmaGroup, hkSpuDmaManager::READ_MODE mode, int transferSize)
{
	CacheRow8Way&	row			= calcCacheRow(addressInMainMemory);
	const ElemType*	spuAddress	= cacheLookup (addressInMainMemory, &row, sizeof(ElemType), &m_lines[0] );

	if ( spuAddress )
	{
		HK_ON_DEBUG( m_hits = m_hits + 1; )
		return spuAddress;
	}

	const ElemType* object = reinterpret_cast<const ElemType*>( getObject(addressInMainMemory, row, dmaGroup, transferSize, mode ) );
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
