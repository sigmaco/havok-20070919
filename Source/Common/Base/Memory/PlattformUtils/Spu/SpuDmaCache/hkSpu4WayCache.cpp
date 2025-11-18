/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpu4WayCache.h>


void hkSpu4WayCache::initBuffer(void* buffer)
{
	HK_ASSERT2(0xaf35ee12, !(hkUlong(buffer) & 0xf), "4way cache buffer must be 16byte aligned." );

	m_lines	= reinterpret_cast<hkUint8*>( buffer );

	int bufferSizeForCacheLines	= 4 * HK_HINT_SIZE16(m_elemSize) * HK_HINT_SIZE16(m_numCacheRows);
	m_rows	= reinterpret_cast<CacheRow4Way*>( hkAddByteOffset(buffer, bufferSizeForCacheLines) );

#if defined(HK_DEBUG)
	m_misses = 0;
	m_hits = 0;
#endif

	//
	// Initialize the cache rows
	//
#if defined(HK_PLATFORM_PS3SPU)

	static const vec_uint4 ageInit	= { 0, 1, 2, 3 };
	const vec_int4  zero = spu_splats( (int)(0) );
	const vec_uint4 baseOffset	= (vec_uint4) spu_madd( (vector signed short)ageInit, spu_splats( (short int) (m_elemSize) ), zero);
	const vec_uint4 baseInc		= spu_splats( (unsigned int) (m_elemSize * 4) );
	vec_uint4 baseAddress = spu_add( spu_splats( (unsigned int) m_lines.val() ), baseOffset);

	CacheRow4Way* row = m_rows;
	int numCacheRows = m_numCacheRows;

	{
		int r = 0;
		do 
		{
			row->m_spuAddresses			= baseAddress;
			row->m_originalAddresses	= spu_splats(0U);
			row->m_age					= ageInit;

			row++;
			baseAddress = spu_add( baseAddress, baseInc );
		}
		while ( ++r < numCacheRows );
	}

#else

	{
		for (int r=0; r < m_numCacheRows; r++)
		{
			for (int i=0; i < 4; i++)
			{
				m_rows[r].m_spuAddresses[i]			= &m_lines[ (r*4*m_elemSize) + (i*m_elemSize) ];
				m_rows[r].m_originalAddresses[i]	= 0;
				m_rows[r].m_age[i]					= i;
			}
		}
	}

#endif
}


// this function will either return an already cached object or get it from memory and wait for it.
const void* hkSpu4WayCache::getObject(HK_CPU_PTR(const void *) addressInMainMemory, int transferSize, int dmaGroup, CacheRow4Way& row, bool waitForDmaCompletion)
{
	HK_ON_DEBUG( m_misses = m_misses + 1; )

#if defined(HK_PLATFORM_PS3SPU)

	vec_uint4 addressV = spu_splats( (unsigned int)addressInMainMemory );

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

	vec_uint4 spuaddressV = spu_orx( spu_and(row.m_spuAddresses, lruMask ) );
	void* object = (void*)si_to_ptr((qword)spuaddressV);

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

	// If the cache's overall read-mode is READ_ONLY we can delay the finalization of this transfer until the currently fetched object is evicted from the cache again. This way
	// we are able to catch any illegal modifications on objects stored in a read-only cache.
	if ( m_readMode == hkSpuDmaManager::READ_ONLY )
	{
		if ( row.m_originalAddresses[ lruIndex ] ) 	 
		{ 	 
			HK_SPU_DMA_PERFORM_FINAL_CHECKS( row.m_originalAddresses[ lruIndex ], row.m_spuAddresses[ lruIndex ], 0 ); 	 
		}
	}

	row.m_originalAddresses[lruIndex] = addressInMainMemory;
	row.m_age              [lruIndex] = 0;

	void* object = row.m_spuAddresses[lruIndex];

#endif

	hkSpuDmaManager::getFromMainMemory(object, addressInMainMemory, transferSize, (hkSpuDmaManager::READ_MODE)m_readMode.val(), dmaGroup);

	// If the cache's overall read-mode is READ_COPY we have to immediately (i.e. upon the wait() call) finalize this transfer as somebody might change the cacheline's
	// content after returning from this function call.
	if ( m_readMode == hkSpuDmaManager::READ_COPY )
	{
		HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( addressInMainMemory, object, transferSize );
	}

	if ( waitForDmaCompletion )
	{
		hkSpuDmaManager::waitForDmaCompletion(dmaGroup);
	}
	return object;
}


const void* hkSpu4WayCache::getFromMainMemory(HK_CPU_PTR(const void *) addressInMainMemory, int transferSize)
{
	CacheRow4Way&	row			= calcCacheRow(addressInMainMemory);
	const void*		spuAddress	= cacheLookup (addressInMainMemory, row);

	if ( spuAddress )
	{
		HK_ON_DEBUG( m_hits = m_hits + 1; )
		return spuAddress;
	}

	const void* object = getObject(addressInMainMemory, transferSize, HK_SPU_DMA_GROUP_STALL, row, true);
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
