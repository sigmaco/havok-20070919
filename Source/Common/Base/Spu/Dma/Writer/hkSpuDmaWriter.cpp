/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */



#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Dma/Writer/hkSpuDmaWriter.h>
#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>



void hkSpuDmaWriter::writeBackBuffer(int sizebufferUsed)
{
	HK_ASSERT2(0xad76bcad, 0 == (0xf & sizebufferUsed), "Data not 16-byte aligned");

	// Dma writeback
	{
		HK_ASSERT2(0xad6789dd, !m_dstEnd || hkAddByteOffsetCpuPtr( m_currentDstPosition.val(), sizebufferUsed ) <= m_dstEnd, "Ppu destination buffer overflown." );
		hkSpuDmaManager::putToMainMemory( m_currentDstPosition, m_workBuffer, sizebufferUsed, hkSpuDmaManager::WRITE_NEW, m_workDmaGroup );
		m_currentDstPosition = hkAddByteOffsetCpuPtr( m_currentDstPosition.val(), sizebufferUsed );
	}

	// Swap buffers
	{ hkPadSpu<void*> h = m_workBuffer;   m_workBuffer   = m_transferBuffer;   m_transferBuffer = h; }
	{ hkPadSpu<int>  h = m_workDmaGroup; m_workDmaGroup = m_transferDmaGroup; m_transferDmaGroup = h; }


	// Make sure our new work buffer dma has finished.
	{
		hkSpuDmaManager::waitForDmaCompletion( m_workDmaGroup );
		HK_ON_DEBUG( m_wasBufferRequested = false );

		HK_SPU_DMA_TRY_TO_PERFORM_FINAL_CHECKS( HK_NULL, m_workBuffer.val(), 0 );
	}

	m_currentPositionInWorkBuffer = m_workBuffer;
}



void hkSpuDmaWriter::flush()
{
	const int bufferUsed = (int)hkGetByteOffset( m_workBuffer, m_currentPositionInWorkBuffer );
	const int bufferUsedAligned = HK_NEXT_MULTIPLE_OF(16, bufferUsed );

	// Dma writeback
	if ( bufferUsed > 0 )
	{
		HK_ASSERT2(0xad6789dd, !m_dstEnd || hkAddByteOffsetCpuPtr( m_currentDstPosition.val(), bufferUsedAligned ) <= m_dstEnd, "Ppu destination buffer overflown." );
		hkSpuDmaManager::putToMainMemory( m_currentDstPosition, m_workBuffer, bufferUsedAligned, hkSpuDmaManager::WRITE_NEW, m_workDmaGroup );
		m_currentDstPosition = hkAddByteOffsetCpuPtr( m_currentDstPosition.val(), bufferUsed );
	}

	HK_ASSERT2(0xad7865dd, m_currentDstPosition <= m_dstEnd, "Wrote past destination end.");

	// reset the work buffer
	m_currentPositionInWorkBuffer = m_workBuffer;

	// safety: wait for dma's finished for both buffers
	hkSpuDmaManager::waitForDmaCompletionUsingBitfield( HK_DMAWAIT_BITSHIFT(m_workDmaGroup) | HK_DMAWAIT_BITSHIFT(m_transferDmaGroup) );

	if ( bufferUsed > 0 )
	{
		HK_SPU_DMA_PERFORM_FINAL_CHECKS( HK_NULL, m_workBuffer.val(), 0 );
	}

	HK_SPU_DMA_TRY_TO_PERFORM_FINAL_CHECKS( HK_NULL, m_transferBuffer.val(), 0 );
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
