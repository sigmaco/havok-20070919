/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */



#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>

hkSpuDmaAccessor::hkSpuDmaAccessor()
{
}

hkSpuDmaAccessor::~hkSpuDmaAccessor() 
{
	HK_ASSERT2(0xad76be4e, m_currentWritePositionInMainMemory <= m_currentReadPositionInMainMemory || m_initAllToZero.val(), "Can't write what we haven't read.");
	HK_ASSERT2(0xad76be4e, m_currentReadPositionInMainMemory <= m_bufferEndInMainMemory, "Read from main memory past the buffer end.");
}


#if defined (HK_PLATFORM_WIN32)
#	define HK_DMA_SPU_ACCESSOR_STORE_INFO_FOR_PERFORM_FINAL_CHECKS(info, readStart, readSize) info->m_mainMemPtrForFinalChecks = readStart; info->m_mainMemSizeForFinalChecks = readSize;
#	define HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS(info, spuBufferStart) \
		if (info->m_mainMemSizeForFinalChecks) { hkSpuDmaManager::performFinalChecks(info->m_mainMemPtrForFinalChecks, spuBufferStart, info->m_mainMemSizeForFinalChecks); info->m_mainMemSizeForFinalChecks = 0; }
#else
#	define HK_DMA_SPU_ACCESSOR_STORE_INFO_FOR_PERFORM_FINAL_CHECKS(info, readStart, readSize) 
#	define HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS(info, spuBufferStart) 
#endif


void hkSpuDmaAccessor::finishInit()
{
	if ( m_initAllToZero.val() == false)
	{
		// Wait for the first batch of data to arrive.
		hkSpuDmaManager::waitForDmaCompletion(m_workInfo->m_dmaGroup);
		HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS( m_workInfo, m_workInfo->m_startMarker.val() );
	}
	else
	{
		// initialize all with zeros
		hkString::memClear16(m_workInfo->m_startMarker.val(), ((unsigned int)(m_baseBufferSize + m_overflowBufferSize)) >> 4 );
	}
}


	// ag.todo change the signiture of the function to void *hkSpuDmaAccessor::controlBufferProgress(void* currentPositionOnSpu) which produces much nicer code on ps3 spu
void hkSpuDmaAccessor::controlBufferProgress(void*& currentPositionOnSpu)
{
	// assert we haven't overflown
	HK_ASSERT2( 0xad7899dd, currentPositionOnSpu <= hkAddByteOffset(m_workInfo->m_terminalMarker.val(), m_overflowBufferSize), "hkSpuDmaAccessor's buffer has been overflown." );

	if (currentPositionOnSpu >= m_workInfo->m_terminalMarker)
	{
		currentPositionOnSpu = switchBuffers(currentPositionOnSpu);
	}
}

void hkSpuDmaAccessor::finishFlushAndClose()
{
	//   wait for (write) dmaCompleted for other buffers
	hkSpuDmaManager::waitForDmaCompletion(m_prefetchInfo->m_dmaGroup);
	HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS(m_prefetchInfo, m_prefetchInfo->m_startMarker);
	hkSpuDmaManager::waitForDmaCompletion(m_writeInfo->m_dmaGroup);
	HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS(m_writeInfo, m_writeInfo->m_startOfData);

	hkSpuDmaManager::waitForDmaCompletion(m_workInfo->m_dmaGroup);
	HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS(m_workInfo, m_workInfo->m_startOfData)
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
