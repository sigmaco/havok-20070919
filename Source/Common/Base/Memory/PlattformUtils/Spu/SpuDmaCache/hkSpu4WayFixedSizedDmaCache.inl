/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

template <typename ElemType, int numCacheRows>
int hkSpu4WayFixedSizedDmaCache<ElemType, numCacheRows>::calcCacheRowIndex(void* addr, int mod) const
{
	// knuths multiplicative golden hash
	//return ( ( hkUint16(hkUlong(addr)) * hkUint16(35761) )>>16) & mod;

	return int( (hkUlong)addr / sizeof(ElemType) ) & mod;
}


template <typename ElemType, int numCacheRows>
void hkSpu4WayFixedSizedDmaCache<ElemType, numCacheRows>::init()
{
	HK_ASSERT2(0xad67d899, hkMath::isPower2(numCacheRows), "Number of cache rows must be a power of 2.");

#if defined(HK_DEBUG)
	// we don't have hkString::memSet on PS3SPU so we just do the clearing manually
	{
		for (unsigned i = 0; i < sizeof(m_rows); i++)
		{
			((hkUint8*)m_rows)[i] = 0;
		}
	}
	m_misses = 0;
	m_hits = 0;
#endif

#if defined(HK_PLATFORM_PS3SPU)
	static const vec_uint4 ageInit = {0,1,2,3};
	static const vec_uint4 baseOffset = { sizeof(ElemType) * 0, sizeof(ElemType) * 1, sizeof(ElemType) * 2, sizeof(ElemType) * 3 };
	static const vec_uint4 baseInc = { sizeof(ElemType) * 4, sizeof(ElemType) * 4, sizeof(ElemType) * 4, sizeof(ElemType) * 4 };
	vec_uint4 baseAddress = spu_add( spu_splats( (unsigned int) m_lines ), baseOffset);

	// Initialize the cache rows
	for (int r=0; r < numCacheRows; r++)
	{
		m_rows[r].m_age = ageInit;
		m_rows[r].m_originalAddresses = spu_splats(0U);
		m_rows[r].m_spuAddresses = baseAddress;
		baseAddress = spu_add( baseAddress, baseInc );
	}
#else
	for (int r=0; r < numCacheRows; r++)
	{
		for (int i=0; i < 4; i++)
		{
			m_rows[r].m_spuAddresses[i]			= reinterpret_cast<ElemType*>( &m_lines[ (r*4*sizeof(ElemType)) + (i*sizeof(ElemType)) ] );
			m_rows[r].m_originalAddresses[i]	= 0;
			m_rows[r].m_age[i]					= i;
		}
	}
#endif
}


template <typename ElemType, int numCacheRows>
void hkSpu4WayFixedSizedDmaCache<ElemType, numCacheRows>::exit()
{
#if defined(HK_SIMULATE_SPU_DMA_ON_CPU)
	for (int r = 0; r < numCacheRows; r++)
	{
		CacheRow4Way* row = &m_rows[r];

		for (int i=0; i < 4; i++ )
		{
			if ( row->m_originalAddresses[i])
			{
				HK_SPU_DMA_PERFORM_FINAL_CHECKS( row->m_originalAddresses[i], &m_lines[ (r*4*sizeof(ElemType)) + (i*sizeof(ElemType)) ], 0);
			}
		}
	}
#endif
}


// returns true if hit, false otherwise
template <typename ElemType, int numCacheRows>
bool hkSpu4WayFixedSizedDmaCache<ElemType, numCacheRows>::testHit( const void * addressInMainMemory ) const
{
	const int idx = calcCacheRowIndex((void *)hkUlong(addressInMainMemory), numCacheRows-1);
	const CacheRow4Way& row = m_rows[ HK_HINT_SIZE16(idx)];

#if defined(HK_PLATFORM_PS3SPU)

	vec_uint4 addressV = spu_splats( (unsigned int)addressInMainMemory );

	vec_uint4 mask = spu_cmpeq( addressV, row.m_originalAddresses );

	// Or across the result to place it in correct position for return;
	mask = spu_orx( mask );
	return (const ElemType*)spu_extract(mask, 0); 

#else

	for (int i=0; i < 4; i++)
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
const ElemType* hkSpu4WayFixedSizedDmaCache<ElemType, numCacheRows>::cacheLookup( const void * addressInMainMemory, CacheRow4Way& row, int& cacheLineIdx)
{
#if defined(HK_PLATFORM_PS3SPU)

	static const vec_uint4 ones  = {1,1,1,1};
	static const vec_uint4 cacheLineIndices  = {0,1,2,3};

	vec_uint4 addressV = spu_splats( (unsigned int)addressInMainMemory ); // Should reduce to just ila but doesn't
	
	vec_uint4 mask = spu_cmpeq( addressV, row.m_originalAddresses );

	// extract the cache line index
	{
		vec_uint4 cacheLineIdxTmp = spu_and( mask, cacheLineIndices );
		cacheLineIdxTmp = spu_orx( cacheLineIdxTmp );
		cacheLineIdx = spu_extract(cacheLineIdxTmp, 0);
	}

	// Use the mask to select the spu address
	vec_uint4 result = spu_and( mask, row.m_spuAddresses );

	// Increment age for all other lines, reset for hit line
	row.m_age = spu_andc( spu_add( row.m_age, ones ), mask );

	 // Or across the result to place it in correct position for return;
	result = spu_orx( result );
	return (const ElemType*)spu_extract(result, 0); 

#else

	for (int i=0; i < 4; i++)
	{
		row.m_age[i]++; // make all lines older
	}

	for (int i=0; i < 4; i++)
	{
		if (row.m_originalAddresses[i] == addressInMainMemory)
		{
			row.m_age[i] = 0; // reset age for this line
			cacheLineIdx = i;
			return row.m_spuAddresses[i];
		}
	}

	return HK_NULL;

#endif
}

// this function will either return an already cached object or start prefetching it.
// It calls the version below
template <typename ElemType, int numCacheRows>
const ElemType* hkSpu4WayFixedSizedDmaCache<ElemType, numCacheRows>::getFromMainMemoryNoGroupAndWaitForCompletion(HK_CPU_PTR(const void *) addressInMainMemory, int transferSize)
{
	const ElemType* elem =  hkSpu4WayFixedSizedDmaCache<ElemType, numCacheRows>::getFromMainMemory(addressInMainMemory, 0, hkSpuDmaManager::READ_COPY, transferSize);
	hkSpuDmaManager::waitForAllDmaCompletion();
	return elem;
}

// this function will either return an already cached object or start prefetching it
template <typename ElemType, int numCacheRows>
const ElemType* hkSpu4WayFixedSizedDmaCache<ElemType, numCacheRows>::getFromMainMemory(HK_CPU_PTR(const void *) addressInMainMemory, int dmaGroup, hkSpuDmaManager::READ_MODE mode, int transferSize)
{
	const int idx = calcCacheRowIndex((void *)hkUlong(addressInMainMemory), numCacheRows-1);
	CacheRow4Way& row = m_rows[ HK_HINT_SIZE16(idx)];

	int cacheLineIdx;
	const ElemType* spuAddress = cacheLookup( addressInMainMemory, row, cacheLineIdx );
	if (spuAddress)
	{
		HK_ON_DEBUG( m_hits = m_hits + 1; )
		return spuAddress;
	}

	// Cache miss: initiate a transfer from main memory
	HK_ON_DEBUG( m_misses = m_misses + 1; )

#if defined(HK_PLATFORM_PS3SPU)

	static const vec_uint4 lineOffset = { sizeof(ElemType) * 0, sizeof(ElemType) * 1, sizeof(ElemType) * 2, sizeof(ElemType) * 3 };
	vec_uint4 lineBase = spu_splats( (unsigned) &m_lines[idx * 4 * sizeof(ElemType)] );

	// rowAddresses = &row.m_lines[0*sizeof(ElemType)], &row.m_lines[1*sizeof(ElemType)], &row.m_lines[2*sizeof(ElemType)], &row.m_lines[3*sizeof(ElemType)];
	vec_uint4 rowAddresses = spu_add( lineBase, lineOffset );

	vec_uint4 addressV  = spu_splats( (unsigned int)addressInMainMemory );

	// Find the lru cache line - This is the oldest one (max age)
	vec_uint4 lruMask;
	{
		vec_uint4 xSplat = vec_splat(row.m_age, 0);
		vec_uint4 ySplat = vec_splat(row.m_age, 1);
		vec_uint4 zSplat = vec_splat(row.m_age, 2);
		vec_uint4 wSplat = vec_splat(row.m_age, 3);

		vec_uint4 gtX = spu_cmpgt(xSplat, row.m_age);
		vec_uint4 gtY = spu_cmpgt(ySplat, row.m_age);
		vec_uint4 gtZ = spu_cmpgt(zSplat, row.m_age);
		vec_uint4 gtW = spu_cmpgt(wSplat, row.m_age);

		vec_uint4 leX = spu_or( spu_cmpeq(xSplat, row.m_age), spu_nor(gtX, gtX) );
		vec_uint4 leY = spu_or( spu_cmpeq(ySplat, row.m_age), spu_nor(gtY, gtX) );
		vec_uint4 leZ = spu_or( spu_cmpeq(zSplat, row.m_age), spu_nor(gtZ, gtX) );
		vec_uint4 leW = spu_or( spu_cmpeq(wSplat, row.m_age), spu_nor(gtW, gtX) );

		vec_uint4 leXY = spu_and( leX, leY );
		vec_uint4 leZW = spu_and( leZ, leW );
		lruMask = spu_and( leXY, leZW ); // Now contains a mask of the minimum values

		HK_ASSERT2( 0x4545378, hkMath::isPower2(si_to_int((qword)spu_gather( lruMask ))), "Cache inconsistency -  some ways are the same age!" );

	}
	row.m_originalAddresses	= spu_sel ( row.m_originalAddresses, addressV, lruMask );
	row.m_age				= spu_andc( row.m_age, lruMask );
	row.m_spuAddresses		= spu_sel ( row.m_spuAddresses, rowAddresses, lruMask );

	vec_uint4 spuaddressV = spu_orx( spu_and(row.m_spuAddresses, lruMask ) );
	ElemType* object = reinterpret_cast<ElemType*>( si_to_ptr((qword)spuaddressV) );
	hkSpuDmaManager::getFromMainMemory(object, addressInMainMemory, transferSize, mode, dmaGroup);
	return object;

#else

	// Find the lru cache way
	int max = -1;
	int lruIndex = 0;
	for (int i=0; i < 4; i++)
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

	{
		row.m_originalAddresses[ lruIndex ] = addressInMainMemory;
		row.m_age              [ lruIndex ] = 0;
		row.m_spuAddresses     [ lruIndex ] = reinterpret_cast<ElemType*>( &m_lines[ (idx*4*sizeof(ElemType)) + (lruIndex*sizeof(ElemType)) ] );

		ElemType* object = const_cast<ElemType*>( row.m_spuAddresses[ lruIndex ] );
		hkSpuDmaManager::getFromMainMemory(object, addressInMainMemory, transferSize, mode, dmaGroup);
		return object;
	}

#endif
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
