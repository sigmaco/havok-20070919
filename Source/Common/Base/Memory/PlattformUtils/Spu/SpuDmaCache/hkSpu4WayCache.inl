/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

int hkSpu4WayCache::getBufferSize(int elemSize, int numCacheRows)
{
	HK_ASSERT2(0xaf35e211, !(elemSize & 0xf), "4way cache elem size must be a multiple of 16." );
	HK_ASSERT2(0xaf35e213, hkMath::isPower2(numCacheRows), "Number of cache rows must be a power of 2.");

	int bufferSizeForCacheRows	= sizeof(CacheRow4Way) * numCacheRows;
	int bufferSizeForCacheLines	= 4 * elemSize * numCacheRows;
	int bufferSizeTotal			= bufferSizeForCacheRows + bufferSizeForCacheLines;

	return bufferSizeTotal;
}


int hkSpu4WayCache::initAndGetBufferSize(int elemSize, int numCacheRows, hkSpuDmaManager::READ_MODE readMode)
{
	m_readMode		= readMode;
	m_elemSize		= elemSize;
	m_numCacheRows  = numCacheRows;
	m_cacheRowMask = (numCacheRows-1) * sizeof(CacheRow4Way);

	return getBufferSize(elemSize, numCacheRows);
}


void hkSpu4WayCache::exit()
{
#if defined(HK_SIMULATE_SPU_DMA_ON_CPU) 	 
	if ( m_readMode == hkSpuDmaManager::READ_ONLY )
	{
		for (int r = 0; r < m_numCacheRows; r++)
		{
			CacheRow4Way* row = &m_rows[r];
			for (int i=0; i < 4; i++ )
			{
				if ( row->m_originalAddresses[i])
				{
					HK_SPU_DMA_PERFORM_FINAL_CHECKS( row->m_originalAddresses[i], &m_lines[ (r*4*m_elemSize) + (i*m_elemSize) ], 0);
				}
			}
		}
	}
#endif
}


void* hkSpu4WayCache::getBuffer()
{
	return m_lines;
}


hkSpu4WayCache::CacheRow4Way& hkSpu4WayCache::calcCacheRow(HK_CPU_PTR(const void *) addressInMainMemory) const
{
	hkUint32 addrI = hkUint32(hkUlong(addressInMainMemory));

	HK_ASSERT(0xf0dfde34, int(m_elemSize) <= 512 );
	addrI = addrI / (512/sizeof(CacheRow4Way));	// assuming a cache line size of 512. If we are wrong nothing serious happens

	int offset = addrI  & m_cacheRowMask;

	CacheRow4Way* row = hkAddByteOffset(&m_rows[0], offset);
	return *row;
}


// returns the spu address if hit, null otherwise
const void* hkSpu4WayCache::cacheLookup(HK_CPU_PTR(const void *) addressInMainMemory, CacheRow4Way& cacheRow)
{
#if defined(HK_PLATFORM_PS3SPU)
	static const vec_uint4 ones  = {1,1,1,1};

	vec_uint4 addressV = spu_splats( (unsigned int)addressInMainMemory ); // Should reduce to just ila but doesn't
	
	vec_uint4 mask = spu_cmpeq( addressV, cacheRow.m_originalAddresses );

	// Use the mask to select the spu address
	vec_uint4 result = spu_and( mask, cacheRow.m_spuAddresses );

	// Increment age for all other lines, reset for hit line
	cacheRow.m_age = spu_andc( spu_add( cacheRow.m_age, ones ), mask );

	 // Or across the result to place it in correct position for return;
	result = spu_orx( result );
	return (const void*)spu_extract(result, 0); 

#else

	for (int i=0; i < 4; i++)
	{
		cacheRow.m_age[i]++; // age all lines
	}

	for (int i=0; i < 4; i++)
	{
		if (cacheRow.m_originalAddresses[i] == addressInMainMemory)
		{
			cacheRow.m_age[i] = 0; // reset age for this line
			return cacheRow.m_spuAddresses[i];
		}
	}

	return HK_NULL;

#endif
}

void hkSpu4WayCache::flush(HK_CPU_PTR(const void *) addressInMainMemory)
{
	CacheRow4Way& row = calcCacheRow(addressInMainMemory);

#if defined(HK_PLATFORM_PS3SPU)

	vec_uint4 addressV = spu_splats( (unsigned int)addressInMainMemory );

	vec_uint4 mask = spu_cmpeq( addressV, row.m_originalAddresses );

	// Or across the result to place it in correct position for return;
	row.m_originalAddresses = spu_andc(row.m_originalAddresses, mask);

#else

	for (int i=0; i < 4; i++)
	{
		if (row.m_originalAddresses[i] == addressInMainMemory)
		{
#if defined(HK_SIMULATE_SPU_DMA_ON_CPU)
			// In READ_ONLY mode we delay the finalization of this cacheline's transfer until we evict its content from the cache again (which happens just now).
			if ( m_readMode == hkSpuDmaManager::READ_ONLY )
			{
				HK_SPU_DMA_PERFORM_FINAL_CHECKS( row.m_originalAddresses[i], row.m_spuAddresses[i], 0 ); 	 
			}
#endif

			row.m_originalAddresses[i] = 0;
		}
	}

#endif
}


bool hkSpu4WayCache::testHit(HK_CPU_PTR(const void *) addressInMainMemory) const
{
	const CacheRow4Way& row = calcCacheRow(addressInMainMemory);

#if defined(HK_PLATFORM_PS3SPU)

	vec_uint4 addressV = spu_splats( (unsigned int)addressInMainMemory );

	vec_uint4 mask = spu_cmpeq( addressV, row.m_originalAddresses );

	// Or across the result to place it in correct position for return;
	mask = spu_orx( mask );
	return (const void*)spu_extract(mask, 0); 

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


const void* hkSpu4WayCache::getFromMainMemoryInlined(HK_CPU_PTR(const void *) addressInMainMemory, int transferSize, int dmaGroup, bool waitForDmaCompletion)
{
	CacheRow4Way&	row			= calcCacheRow(addressInMainMemory);
	const void*		spuAddress	= cacheLookup (addressInMainMemory, row);

	if ( spuAddress )
	{
		HK_ON_DEBUG( m_hits = m_hits + 1; )
		return spuAddress;
	}

	const void* object = getObject(addressInMainMemory, transferSize, dmaGroup, row, waitForDmaCompletion);
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
