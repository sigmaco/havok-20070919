/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */



#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>


hkSpuDmaReader::hkSpuDmaReader()
{
}

hkSpuDmaReader::~hkSpuDmaReader() 
{
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


void hkSpuDmaReader::finishInit()
{
	// Wait for the first batch of data to arrive.
	hkSpuDmaManager::waitForDmaCompletion(m_workInfo->m_dmaGroup);
	HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS( m_workInfo, m_workInfo->m_startMarker.val() );
}


void hkSpuDmaReader::controlBufferProgress(const void*& currentPositionOnSpu)
{
	// assert we haven't overflown
	HK_ASSERT2( 0xad7899dd, currentPositionOnSpu <= hkAddByteOffsetConst(m_workInfo->m_terminalMarker.val(), m_overflowBufferSize), "hkSpuDmaReader's buffer has been overflown." );

	if (currentPositionOnSpu >= m_workInfo->m_terminalMarker)
	{
		currentPositionOnSpu = switchBuffers(currentPositionOnSpu);
	}
}

void hkSpuDmaReader::waitForDmaAndClose()
{
	HK_ASSERT2(0xad678daa, m_currentReadPositionInMainMemory <= m_bufferEndInMainMemory, "We've read past the buffer end.");
	hkSpuDmaManager::waitForDmaCompletion(m_prefetchInfo->m_dmaGroup);
	HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS(m_prefetchInfo, m_prefetchInfo->m_startMarker);
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
