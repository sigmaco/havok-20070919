/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_DMA_CACHE_H
#define HK_SPU_DMA_CACHE_H


#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>


template <typename ElemType>
struct hkSpuDmaCacheLine
{
	HK_ALIGN16( ElemType m_object );

	hkPadSpu<HK_CPU_PTR(const ElemType*)> m_originalAddress;

		// Num of requests for the object. 
		//Each getFromMainMemory() call must be matched by a releaseObjectAt() call.
	hkPadSpu<int> m_lockCount;

		// this is set to -1 once the object is ready.
	hkPadSpu<int> m_dmaGroup;

};



/// This is a 2-way associative cache, we're using 2 cache lines per CacheRow
template <typename ElemType, int numCacheRows, int overflowBufferSize>
class hkSpuDmaCache
{

	public:

		HK_FORCE_INLINE void init(int dmaGroupStart, int numDmaGroups);

			// for debug checks only, but has to be called
		HK_FORCE_INLINE void exit();


			/// Upload data from main memory onto spu memory.
			///
			/// Immediately returns a valid POINTER to the object, although the object DATA might
			/// not be valid yet (unless dma has already finished or object already was found in cache)
		/*HK_FORCE_INLINE*/ const ElemType* getFromMainMemory(HK_CPU_PTR(const ElemType*) addressInMainMemory);

			/// Wait until supplied object has been successfully uploaded from main memory.
			///
			/// Stalls the execution until the object has been uploaded from main memory onto spu memory.
		HK_FORCE_INLINE void waitForDmaCompletion(const ElemType* addressOnSpu);

			/// Unlock/Free the cache line containing the supplied object.
			///
			/// This marks the cacheline for the supplied object as 'available again'. The object in this
			/// cacheline is no longer valid until the cacheline is re-used and a new object has been
			/// uploaded to it.
		HK_FORCE_INLINE void releaseObjectAt(const ElemType* addressOnSpu);


	private:

		struct CacheRow
		{
			hkSpuDmaCacheLine<ElemType> m_lines[2];
		};


	private:

		HK_FORCE_INLINE int getNextDmaGroup()
		{
			m_currDmaGroupIdx = (m_currDmaGroupIdx+1) & (m_numDmaGroups-1);
			return m_dmaGroupStart + m_currDmaGroupIdx;
		}

		HK_FORCE_INLINE hkSpuDmaCacheLine<ElemType>* getCacheLineForObject(const ElemType* addressOnSpu) { return reinterpret_cast< hkSpuDmaCacheLine<ElemType>* >(const_cast<ElemType*>(addressOnSpu)); }


	private:

		hkPadSpu<int> m_dmaGroupStart;
		hkPadSpu<int> m_numDmaGroups;
		hkPadSpu<int> m_currDmaGroupIdx;

		CacheRow                    m_rows[numCacheRows];
		hkSpuDmaCacheLine<ElemType> m_overflowArray[overflowBufferSize];


		//
		// Methods for statistics & testing only
		//
	public:

		hkBool didTheObjectGoToOverflowBuffer( const ElemType* cachedObject ) const 
		{
			if ( (hkUlong(cachedObject) >= hkUlong(m_rows)) && (hkUlong(cachedObject) < hkUlong(m_rows+numCacheRows) ) ) { return false; }
			if ( (hkUlong(cachedObject) >= hkUlong(m_overflowArray)) && (hkUlong(cachedObject) < hkUlong(m_overflowArray+overflowBufferSize) ) ) { return true; }
			HK_ASSERT2(0xaf843674, false, "Object not in ");
			return false;
		}

		int getNumOverflowCacheLinesUsed() const 
		{
			int numCacheLinesUsed = 0;
			for (int i = 0; i < overflowBufferSize; i++)
			{
				numCacheLinesUsed += (m_overflowArray[i].m_lockCount > 0);
			}
			return numCacheLinesUsed;
		}

		hkBool areAllCacheLinesUnlocked() const 
		{
			{
				for (int i = 0; i < numCacheRows; i++)
				{
					if ( m_rows[i].m_lines[0].m_lockCount > 0 ) { return false; }
					if ( m_rows[i].m_lines[1].m_lockCount > 0 ) { return false; }
				}
			}
			{
				for (int i = 0; i < overflowBufferSize; i++)
				{
					if ( m_overflowArray[i].m_lockCount > 0 ) { return false; }
				}
			}

			return true;
		}
};



#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpuDmaCache.inl>



#endif // HK_SPU_DMA_CACHE_H

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
