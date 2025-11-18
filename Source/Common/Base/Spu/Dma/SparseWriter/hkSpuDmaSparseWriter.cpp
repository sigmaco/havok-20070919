/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */



#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>
#include <Common/Base/Spu/Dma/SparseWriter/hkSpuDmaSparseWriter.h>

void hkSpuDmaSparseWriter::putToMainMemorySmall64(hkReal val0, hkReal val1, HK_CPU_PTR(void*) dstInMainMemory)
{
	// (1) Put the requests in 
	{
		// (a) add padding till offset relative to 16-byte boundary is the same in dstInMainMemory & currentPosInBuffer

		const int paddingBytes = int((hkUlong(dstInMainMemory) - hkUlong(m_currentPositionInWorkBuffer.val())) & 0xf);
		m_currentPositionInWorkBuffer = hkAddByteOffset(m_currentPositionInWorkBuffer.val(), paddingBytes);
		HK_ASSERT2(0xad8764da, (hkUlong(dstInMainMemory) & 0xf) == (hkUlong(m_currentPositionInWorkBuffer.val()) & 0xf), "Buffers aligment offset not the same.");

		reinterpret_cast<hkReal*>(m_currentPositionInWorkBuffer.val())[0] = val0;
		reinterpret_cast<hkReal*>(m_currentPositionInWorkBuffer.val())[1] = val1;

		if ( (hkUlong(dstInMainMemory) & 0x7) != 0 )
		{
			// address is 4 byte aligned: can't write 8 byte block; write 2x 4 byte block instead

			hkSpuDmaManager::putToMainMemorySmall( dstInMainMemory, m_currentPositionInWorkBuffer, sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
			HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( dstInMainMemory, m_currentPositionInWorkBuffer, sizeof(hkReal) );

			hkSpuDmaManager::putToMainMemorySmall( hkAddByteOffset(dstInMainMemory, 4), hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 4), sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
			HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( hkAddByteOffset(dstInMainMemory, 4), hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 4), sizeof(hkReal) );
		}
		else
		{
			hkSpuDmaManager::putToMainMemorySmall( dstInMainMemory, m_currentPositionInWorkBuffer, 2 * sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
			HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( dstInMainMemory, m_currentPositionInWorkBuffer, 2 * sizeof(hkReal) );
		}

		m_currentPositionInWorkBuffer = hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 8 );
	}

	// (2) Assert the buffers for overflow
	HK_ASSERT2( 0xad7877dd, m_currentPositionInWorkBuffer.val() <= hkAddByteOffset(m_workBufferInfo->m_terminalMarker.val(), m_overflowBufferSize), "The hkSpuDmaSparseWriter has been overflown." );

	// (3) Swap buffers if needed
	if (m_currentPositionInWorkBuffer.val() >= m_workBufferInfo->m_terminalMarker)
	{
		writeBackBuffer();
	}
}

void hkSpuDmaSparseWriter::putToMainMemorySmall128(hkReal val0, hkReal val1, hkReal val2, hkReal val3, HK_CPU_PTR(void*) dstInMainMemory)
{
	// (1) Put the requests in 
	{
		// (a) add padding till offset relative to 16-byte boundary is the same in dstInMainMemory & currentPosInBuffer

		const int paddingBytes = int((hkUlong(dstInMainMemory) - hkUlong(m_currentPositionInWorkBuffer.val())) & 0xf);
		m_currentPositionInWorkBuffer = hkAddByteOffset(m_currentPositionInWorkBuffer.val(), paddingBytes);
		HK_ASSERT2(0xad8764da, (hkUlong(dstInMainMemory) & 0xf) == (hkUlong(m_currentPositionInWorkBuffer.val()) & 0xf), "Buffers aligment offset not the same.");

		reinterpret_cast<hkReal*>(m_currentPositionInWorkBuffer.val())[0] = val0;
		reinterpret_cast<hkReal*>(m_currentPositionInWorkBuffer.val())[1] = val1;
		reinterpret_cast<hkReal*>(m_currentPositionInWorkBuffer.val())[2] = val2;
		reinterpret_cast<hkReal*>(m_currentPositionInWorkBuffer.val())[3] = val3;

		if ( (hkUlong(dstInMainMemory) & 0xf) == 0 )
		{
			hkSpuDmaManager::putToMainMemorySmall( dstInMainMemory, m_currentPositionInWorkBuffer, 4 * sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
			HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( dstInMainMemory, m_currentPositionInWorkBuffer, 4 * sizeof(hkReal) );
		}
		else
		{

			if ( (hkUlong(dstInMainMemory) & 0x7) != 0 )
			{
				// address is 4 byte aligned: 1x 4 byte put, 1x 8 byte put, 1x 4 byte put
				hkSpuDmaManager::putToMainMemorySmall( dstInMainMemory, m_currentPositionInWorkBuffer, sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
				HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( dstInMainMemory, m_currentPositionInWorkBuffer, sizeof(hkReal) );

				hkSpuDmaManager::putToMainMemorySmall( hkAddByteOffset(dstInMainMemory, 4), hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 4), 2 * sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
				HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( hkAddByteOffset(dstInMainMemory, 4), hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 4), 2 * sizeof(hkReal) );

				hkSpuDmaManager::putToMainMemorySmall( hkAddByteOffset(dstInMainMemory, 12), hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 12), sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
				HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( hkAddByteOffset(dstInMainMemory, 12), hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 12), sizeof(hkReal) );

			}
			else
			{
				// address is 8 byte aligned: 2x 8 byte put
				hkSpuDmaManager::putToMainMemorySmall( dstInMainMemory, m_currentPositionInWorkBuffer, 2 * sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
				HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( dstInMainMemory, m_currentPositionInWorkBuffer, 2 * sizeof(hkReal) );

				hkSpuDmaManager::putToMainMemorySmall( hkAddByteOffset(dstInMainMemory, 8), hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 8), 2 * sizeof(hkReal), hkSpuDmaManager::WRITE_NEW, m_workBufferInfo->m_dmaGroup );
				HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT( hkAddByteOffset(dstInMainMemory, 8), hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 8), 2 * sizeof(hkReal) );

			}
		}
		m_currentPositionInWorkBuffer = hkAddByteOffset(m_currentPositionInWorkBuffer.val(), 16);
	}

	// (2) Assert the buffers for overflow
	HK_ASSERT2( 0xad7877dd, m_currentPositionInWorkBuffer.val() <= hkAddByteOffset(m_workBufferInfo->m_terminalMarker.val(), m_overflowBufferSize), "The hkSpuDmaSparseWriter has been overflown." );

	// (3) Swap buffers if needed
	if (m_currentPositionInWorkBuffer.val() >= m_workBufferInfo->m_terminalMarker.val())
	{
		writeBackBuffer();
	}
}



void hkSpuDmaSparseWriter::writeBackBuffer()
{
	// (3) swap buffers.
	{
		BufferInfo* tmp = m_workBufferInfo;
		m_workBufferInfo = m_transferBufferInfo;
		m_transferBufferInfo = tmp;

		m_currentPositionInWorkBuffer = m_workBufferInfo->m_buffer;
	}

	// (3) wait for dma completed for the transfer buffer
	{
		hkSpuDmaManager::waitForDmaCompletion(m_workBufferInfo->m_dmaGroup);
	}
}



void hkSpuDmaSparseWriter::flush()
{
	writeBackBuffer();
	writeBackBuffer();
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
