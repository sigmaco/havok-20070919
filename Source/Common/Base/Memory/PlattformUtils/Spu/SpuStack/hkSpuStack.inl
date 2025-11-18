/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */



#if !defined(HK_PLATFORM_PS3SPU)
hkSpuStack::hkSpuStack()
{
	m_next = HK_NULL;
	m_size = 0;
#if defined (HK_SIMULATE_SPU_DMA_ON_CPU)
	m_numAllocInfos = 0;
#endif
}

HK_FORCE_INLINE hkSpuStack::~hkSpuStack()
{
#if defined (HK_SIMULATE_SPU_DMA_ON_CPU)
	HK_ASSERT2(0x5f82931b, !m_numAllocInfos, "Not all allocations got freed");
#endif
}
#endif

void hkSpuStack::initMemory(void* p, int size)
{
	m_next = p;
	m_size = size;

#if defined (HK_SIMULATE_SPU_DMA_ON_CPU)
	hkString::memSet(p, 0xcd, size);
	m_maxStackSize = size;
#endif
}


void* hkSpuStack::allocateStackRoundSizeTo128(int numBytes, const char* what)
{
	int allocationSize = HK_NEXT_MULTIPLE_OF(128, numBytes);
	return allocateStack( allocationSize, what );
}

void* hkSpuStack::allocateStack(int numBytes, const char* what)
{
	HK_ASSERT2(0xaf8365de, !(numBytes & 0x7f) , "Allocation-size should be a multiple of 128.");
	HK_ASSERT2(0xaf8365df, m_size >= hkUint32(numBytes), "Out of stack memory.");

	void* current = m_next;

	m_next = hkAddByteOffset(current, numBytes);
	HK_ON_DEBUG(m_size = m_size.val() - numBytes);

#if defined (HK_SIMULATE_SPU_DMA_ON_CPU)
	{
		int currentlyAllocated = m_maxStackSize - m_size;
		AllocInfo& allocInfo = m_allocInfos[m_numAllocInfos++];
		{
			allocInfo.m_p = current;
			allocInfo.m_size = numBytes;
			hkString::snprintf(allocInfo.m_what, sizeof(allocInfo.m_what), "HighMark=%i (%i)  by %i(%s)", currentlyAllocated, m_maxStackSize, numBytes, what  );
			allocInfo.m_what[ sizeof(allocInfo.m_what) - 1 ] = HK_NULL;
		}
		if ( currentlyAllocated > m_numBytesAllocatedHighMark )
		{
			m_numBytesAllocatedHighMark = currentlyAllocated;
			HK_WARN_ALWAYS( 0xf0231232, "***** SpuStackHighMark reset ****");
			for (int i =0; i < m_numAllocInfos; i++)
			{
				HK_WARN_ALWAYS( 0xf0231233, m_allocInfos[i].m_what );
			}
		}
	}
#endif

	return current;
}



void hkSpuStack::deallocateStack(void* p)
{
#if defined (HK_SIMULATE_SPU_DMA_ON_CPU)
	{
		AllocInfo& allocInfo = m_allocInfos[--m_numAllocInfos];
		HK_ASSERT2(0xaf83d35f, allocInfo.m_p == p, "Deallocating invalid memory pointer." );
		hkString::memSet(allocInfo.m_p, 0xcd, allocInfo.m_size);
		hkString::memSet(&allocInfo, 0x0, sizeof(AllocInfo));
	}
#endif

	HK_ON_DEBUG(hkUint32 numBytes = hkUint32(hkGetByteOffset(p, m_next)));
	m_next = p;
	HK_ON_DEBUG(m_size = m_size.val() + numBytes);
}

void hkSpuStack::shrinkAllocatedStack(void* p, int newSize )
{
#if defined (HK_SIMULATE_SPU_DMA_ON_CPU)
	{
		AllocInfo& allocInfo = m_allocInfos[m_numAllocInfos-1];
		HK_ASSERT2(0xaf83d35f, allocInfo.m_p == p, "Deallocating invalid memory pointer." );
		allocInfo.m_size = newSize;
	}
#endif
	HK_ON_DEBUG(hkUint32 numBytes = hkUint32(hkGetByteOffset(p, m_next)));
	m_next = hkAddByteOffset(p, newSize);
	HK_ON_DEBUG(m_size = m_size.val() + numBytes - newSize);
}



void hkSpuStack::deallocateStack(int numBytes)
{
#if defined (HK_SIMULATE_SPU_DMA_ON_CPU)
	{
		AllocInfo& allocInfo = m_allocInfos[--m_numAllocInfos];
		HK_ASSERT2(0xaf83d35f, allocInfo.m_size == numBytes, "Deallocating invalid memory size." );
		hkString::memSet(allocInfo.m_p, 0xcd, allocInfo.m_size);
		hkString::memSet(&allocInfo, 0x0, sizeof(AllocInfo));
	}
#endif

	m_next = hkAddByteOffset(m_next.val(), -numBytes);
	HK_ON_DEBUG(m_size = m_size.val() + numBytes);
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
