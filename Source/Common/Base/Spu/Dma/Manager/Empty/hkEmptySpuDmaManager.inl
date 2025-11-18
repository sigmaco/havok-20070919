/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


			// Start fetching data from main memory. 
HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::getFromMainMemory(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xf02134d1, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId )
{
	HK_ASSERT(0xf02134d2, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::getFromMainMemoryLargeAndWaitForCompletion(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId )
{
	HK_ASSERT(0xf02ff4d2, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::putToMainMemory(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xf02134d3, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::putToMainMemoryAndWaitForCompletion(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId )
{
	HK_ASSERT(0xf02134d4, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::putToMainMemorySmallAndWaitForCompletion(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId )
{
	HK_ASSERT(0xf0213454, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::getFromMainMemorySmall(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xf02d34d4, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::putToMainMemorySmall(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId)
{
	HK_ASSERT(0xf02434d4, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::waitForDmaCompletion(int dmaGroupMask)
{
	HK_ASSERT(0xf02134d5, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::waitForAllDmaCompletion()
{
	HK_ASSERT(0xf02134d9, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::performFinalChecks( const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size )
{
	HK_ASSERT(0xaf774451, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::tryToPerformFinalChecks(const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size )
{
	HK_ASSERT(0xaf774452, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::deferFinalChecksUntilWait(const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size )
{
	HK_ASSERT(0xaf774453, false);
}

HK_FORCE_INLINE void HK_CALL hkSpuDmaManager::convertReadOnlyToReadWrite(void* ppu, const void* spu, int size)
{
	HK_ASSERT(0xaf774454, false);
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
