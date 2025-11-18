/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

static HK_FORCE_INLINE int calcCacheRowIndex(void* addr, int mod)
{
	// knuths multiplicative golden hash
	return ( ( hkUint16(hkUlong(addr)) * hkUint16(35761) )>>16) & mod;
}

	// This zeros all bits but the lowest one for a number
static HK_FORCE_INLINE unsigned int getLowestBit (unsigned int w)
{
	if (w==0) return 0;
	return ((w ^ (w-1))>>1)+1;
}



template <typename ElemType, int numCacheRows, int overflowBufferSize>
void hkSpuDmaCache<ElemType, numCacheRows, overflowBufferSize>::init(int dmaGroupStart, int numDmaGroups)
{
	HK_ASSERT2(0xad67d899, getLowestBit(numCacheRows) == numCacheRows, "Number of cache rows must be a power of 2.");

#if defined(HK_DEBUG)
	// we don't have hkString::memSet on PS3SPU so we just do the clearing manually
	{
		for (unsigned i = 0; i < sizeof(m_rows); i++)
		{
			((hkUint8*)m_rows)[i] = 0;
		}
	}
	{
		for (unsigned i = 0; i < sizeof(m_overflowArray); i++)
		{
			((hkUint8*)m_overflowArray)[i] = 0;
		}
	}
#endif

	m_dmaGroupStart = dmaGroupStart;
	m_numDmaGroups = numDmaGroups;
	m_currDmaGroupIdx = 0;

	for (int r = 0; r < numCacheRows; r++)
	{
		CacheRow* row = &m_rows[r];
		hkSpuDmaCacheLine<ElemType>* lines = row->m_lines;

		lines[0].m_originalAddress = HK_NULL;
		lines[0].m_lockCount = 0;
		lines[0].m_dmaGroup = -1;

		lines[1].m_originalAddress = HK_NULL;
		lines[1].m_lockCount = 0;
		lines[1].m_dmaGroup = -1;
	}
	for (int i = 0; i < overflowBufferSize; i++)
	{
		hkSpuDmaCacheLine<ElemType>* line = &m_overflowArray[i];
		line->m_originalAddress = HK_NULL;
		line->m_lockCount = 0;
		line->m_dmaGroup = -1;
	}
}


template <typename ElemType, int numCacheRows, int overflowBufferSize>
void hkSpuDmaCache<ElemType, numCacheRows, overflowBufferSize>::exit()
{
#if defined(HK_SIMULATE_SPU_DMA_ON_CPU)
	for (int r = 0; r < numCacheRows; r++)
	{
		CacheRow* row = &m_rows[r];
		hkSpuDmaCacheLine<ElemType>* lines = row->m_lines;

		if ( lines[0].m_originalAddress)
		{
			HK_SPU_DMA_PERFORM_FINAL_CHECKS( lines[0].m_originalAddress.val(), &lines[0].m_object, sizeof(ElemType));
		}
		if ( lines[1].m_originalAddress)
		{
			HK_SPU_DMA_PERFORM_FINAL_CHECKS( lines[1].m_originalAddress.val(), &lines[1].m_object, sizeof(ElemType));
		}
	}
	for (int i = 0; i < overflowBufferSize; i++)
	{
		hkSpuDmaCacheLine<ElemType>* line = &m_overflowArray[i];
		if ( line->m_originalAddress )
		{
			HK_SPU_DMA_PERFORM_FINAL_CHECKS( line->m_originalAddress.val(), &line->m_object, sizeof(ElemType));
		}
	}
#endif
}



template <typename ElemType, int numCacheRows, int overflowBufferSize>
const ElemType* hkSpuDmaCache<ElemType, numCacheRows, overflowBufferSize>::getFromMainMemory(HK_CPU_PTR(const ElemType*) addressInMainMemory)
{
	const int idx = calcCacheRowIndex((void *)hkUlong(addressInMainMemory), numCacheRows-1);

	CacheRow* row = &m_rows[ HK_HINT_SIZE16(idx)];
	hkSpuDmaCacheLine<ElemType>* lines = row->m_lines;

	//
	// Check if object is already present in either of the two cache lines within the cache row.
	//
	if ( lines[0].m_originalAddress == addressInMainMemory ) 
	{  
		lines[0].m_lockCount = lines[0].m_lockCount + 1; 
		return &lines[0].m_object; 
	}
	if ( lines[1].m_originalAddress == addressInMainMemory ) 
	{ 
		lines[1].m_lockCount = lines[1].m_lockCount + 1; 
		return &lines[1].m_object; 
	}

	hkSpuDmaCacheLine<ElemType>* freeCacheLine;

	//
	// Upload object to oldest (and unused) cache line in row
	//
	if ( lines[0].m_lockCount == 0 )
	{
		freeCacheLine = &lines[0];
		goto uploadToCacheLine;
	}
	if ( lines[1].m_lockCount == 0 )
	{
		freeCacheLine = &lines[1];
		goto uploadToCacheLine;
	}

	//
	// Upload object to overflow buffer (or return pointer if it is already present there)
	//
	{
		freeCacheLine = &m_overflowArray[0];
		for ( int i = overflowBufferSize-1; i >=0 ; i--)
		{
			if ( freeCacheLine->m_originalAddress == addressInMainMemory ) 
			{
				freeCacheLine->m_lockCount = freeCacheLine->m_lockCount + 1; 
				return &freeCacheLine->m_object; 
			}
			if ( freeCacheLine->m_lockCount == 0 )
			{
				goto uploadToCacheLine;
			}
			freeCacheLine++;
		}
	}

	HK_ASSERT2(0xaf384721, false, "Dma cache overflow.");
	//return HK_NULL;

uploadToCacheLine:
	if ( freeCacheLine->m_originalAddress)
	{
		HK_SPU_DMA_PERFORM_FINAL_CHECKS( freeCacheLine->m_originalAddress, &freeCacheLine->m_object, sizeof(ElemType) );
	}
	{
		const int dmaGroup = getNextDmaGroup();

		freeCacheLine->m_originalAddress = addressInMainMemory;
		freeCacheLine->m_lockCount = 1;
		freeCacheLine->m_dmaGroup = dmaGroup;

		ElemType* object = &freeCacheLine->m_object;
		hkSpuDmaManager::getFromMainMemory(object, addressInMainMemory, sizeof(ElemType), hkSpuDmaManager::READ_ONLY, dmaGroup);

		return object;
	}
}



template <typename ElemType, int numCacheRows, int overflowBufferSize>
void hkSpuDmaCache<ElemType, numCacheRows, overflowBufferSize>::waitForDmaCompletion(const ElemType* addressOnSpu)
{
	// note: we will always 'wait' for dma operation to finish; to avoid any unncessary waiting for already cached-in data,
	// we will in this case use an 'idle' dma group, that is never used for any real get/put operations
	hkSpuDmaCacheLine<ElemType>* cacheLine = getCacheLineForObject(addressOnSpu);
	hkSpuDmaManager::waitForDmaCompletion( cacheLine->m_dmaGroup );
	cacheLine->m_dmaGroup = HK_SPU_DMA_GROUP_IDLE;
}



template <typename ElemType, int numCacheRows, int overflowBufferSize>
void hkSpuDmaCache<ElemType, numCacheRows, overflowBufferSize>::releaseObjectAt(const ElemType* addressOnSpu)
{
	hkSpuDmaCacheLine<ElemType>* cacheLine = getCacheLineForObject(addressOnSpu);
	HK_ASSERT2(0xaf395865, cacheLine->m_dmaGroup == HK_SPU_DMA_GROUP_IDLE, "Cannot unlock data until it's dma'ed in.");
	cacheLine->m_lockCount = cacheLine->m_lockCount-1;
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
