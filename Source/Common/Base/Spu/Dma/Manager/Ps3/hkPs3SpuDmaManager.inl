/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>

#include <spu_intrinsics.h>
#include <sys/spu_thread.h>
#include <sys/spu_event.h>
#include <stdint.h>

#if !defined(HK_DEBUG)
#	define NO_CELL_DMA_ASSERT
#endif

#include <cell/dma.h>
#include <cell/atomic.h>


#include <Common/Base/Thread/Semaphore/hkSemaphoreBusyWait.h>



void hkSpuDmaManager::getFromMainMemory(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
	// no asserts needed as we have asserts in the cellDmaGet
	cellDmaGet(dstOnSpu, (hkUlong)srcInMainMemory, size, dmaGroupId, 0, 0);
}

void hkSpuDmaManager::putToMainMemory(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId)
{
	// no asserts needed as we have asserts in the cellDmaGet
	cellDmaPut(srcOnSpu, (hkUlong)dstInMainMemory, size, dmaGroupId, 0, 0);
}

void hkSpuDmaManager::getFromMainMemorySmall(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId)
{
	// no asserts needed as we have asserts in the cellDmaGet
	cellDmaSmallGet(dstOnSpu, (hkUlong)srcInMainMemory, size, dmaGroupId, 0, 0);
}

void hkSpuDmaManager::putToMainMemorySmall(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId)
{
	// no asserts needed as we have asserts in the cellDmaGet
	cellDmaSmallPut(srcOnSpu, (hkUlong)dstInMainMemory, size, dmaGroupId, 0, 0);
}

void hkSpuDmaManager::getFromMainMemoryList(void* dstOnSpu, hkSpuDmaListElement* listOnSpu, int numListEntries, int spuBufferSize, READ_MODE mode, int dmaGroupId)
{
	// no asserts needed as we have asserts in the cellDmaGet
	cellDmaListGet(dstOnSpu, 0, (CellDmaListElement*)listOnSpu, numListEntries*sizeof(CellDmaListElement), dmaGroupId, 0, 0);
}

void hkSpuDmaManager::putToMainMemoryList(void* srcOnSpu, hkSpuDmaListElement* listOnSpu, int numListEntries, int spuBufferSize, WRITE_MODE mode, int dmaGroupId)
{
	// no asserts needed as we have asserts in the cellDmaGet
	cellDmaListPut(srcOnSpu, 0, (CellDmaListElement*)listOnSpu, numListEntries*sizeof(CellDmaListElement), dmaGroupId, 0, 0);
}

void hkSpuDmaManager::waitForDmaCompletion(int dmaGroupId)
{
	cellDmaWaitTagStatusAll( HK_DMAWAIT_BITSHIFT(dmaGroupId) );
}

void hkSpuDmaManager::waitForDmaCompletionUsingBitfield(int dmaGroupMask)
{
	cellDmaWaitTagStatusAll( dmaGroupMask );
}

void hkSpuDmaManager::waitForAllDmaCompletion()
{
	cellDmaWaitTagStatusAll(0xffffffff);
}

hkUint32 hkSpuDmaManager::atomicExchangeAdd(hkUint32* varOnPpu, int increment)
{
	hkUint32 oldValue = cellAtomicAdd32( &hkSemaphoreBusyWait::m_cacheLine[0], (hkUlong)varOnPpu, increment );
	return oldValue;
}


void hkSpuDmaManager::performFinalChecks( const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size )
{
}

void hkSpuDmaManager::tryToPerformFinalChecks(const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size )
{
}

void hkSpuDmaManager::deferFinalChecksUntilWait(const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size )
{
}

void hkSpuDmaManager::abortDebugTracking(const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size )
{
}

void hkSpuDmaManager::convertReadOnlyToReadWrite(void* ppu, const void* spu, int size)
{
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
