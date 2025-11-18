/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>

void hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
	getFromMainMemory(dstOnSpu, srcInMainMemory, size, mode, dmaGroupId);
	waitForDmaCompletion( dmaGroupId );
}


void hkSpuDmaManager::getFromMainMemoryLargeAndWaitForCompletion(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
#if !defined(HK_PLATFORM_WIN32)
	const int maxTransferSize = 0x4000;
	do
	{
		int transferSize = (size > maxTransferSize) ? maxTransferSize : size;
		getFromMainMemory(dstOnSpu, srcInMainMemory, transferSize, mode, dmaGroupId);
		size -= transferSize;
		dstOnSpu        = hkAddByteOffset(      dstOnSpu       , transferSize);
		srcInMainMemory = hkAddByteOffsetConst( srcInMainMemory, transferSize);
	} while ( size > 0 );
#else
	HK_ASSERT (0xf0344953, (dmaGroupId >= 0) && (dmaGroupId < 31) );
	HK_ASSERT2(0xf097d84f, !(size                     & 0xf), "size must be a multiple of 16.");
	HK_ASSERT2(0xf097d8dd, !(hkUlong(dstOnSpu)        & 0xf), "dstOnSpu must be 16-byte aligned. Try getFromMainMemorySmall instead.");
	HK_ASSERT2(0xf097d8de, !(hkUlong(srcInMainMemory) & 0xf), "srcInMainMemory must be 16-byte aligned. Try getFromMainMemorySmall instead.");
	HK_ASSERT(0xaf635ef2, hkUlong(dstOnSpu) > 0x100 && hkUlong(srcInMainMemory) > 0x100 );

	HK_ASSERT2(0xaf8374fe, hkSpuSimulator::Client::getInstance(), "You have to create an instance of hkSpuSimulator::Client first!");
	hkSpuSimulator::Client::getInstance()->getFromMainMemory( dstOnSpu, srcInMainMemory, size, mode, dmaGroupId );
#endif
	waitForDmaCompletion( dmaGroupId );
}



void hkSpuDmaManager::getFromMainMemorySmallAndWaitForCompletion(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
	getFromMainMemorySmall(dstOnSpu, srcInMainMemory, size, mode, dmaGroupId);
	waitForDmaCompletion( dmaGroupId );
}


void hkSpuDmaManager::putToMainMemoryAndWaitForCompletion(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId)
{
	putToMainMemory(dstInMainMemory, srcOnSpu, size, mode, dmaGroupId);
	waitForDmaCompletion( dmaGroupId );
}


void hkSpuDmaManager::putToMainMemorySmallAndWaitForCompletion(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId)
{
	putToMainMemorySmall(dstInMainMemory, srcOnSpu, size, mode, dmaGroupId);
	waitForDmaCompletion( dmaGroupId );
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
