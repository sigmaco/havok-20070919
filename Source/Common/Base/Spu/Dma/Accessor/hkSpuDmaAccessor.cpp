/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */



#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>
#include <Common/Base/Spu/Dma/Accessor/hkSpuDmaAccessor.h>


void hkSpuDmaAccessor::startInit(HK_CPU_PTR(void*) bufferInMainMemory, int size, void* bufferOnSpu, int baseBufferSize, int overflowBufferSize, int firstDmaGroup, hkBool initAllToZero) 
{ 
	HK_ASSERT2(0xaf319455, !(hkUlong(bufferInMainMemory) & 0x0f),	"Destination buffer in main memory must be 16-bytes-aligned!");
	HK_ASSERT2(0xaf319455, !(hkUlong(bufferOnSpu) & 0x0f),			"Buffer on spu must be 16-bytes-aligned!");
	HK_ASSERT2(0xaf319456, !(size				& 0x0f),			"Destination buffer size must be a multiple of 16!");
	HK_ASSERT2(0xaf319455, !(baseBufferSize		& 0x0f),			"baseBufferSize must be a multiple of 16");
	HK_ASSERT2(0xaf319455, !(overflowBufferSize & 0x0f),			"overflowBufferSize must be a multiple of 16");

	m_initAllToZero = initAllToZero;

	m_bufferStartInMainMemory = bufferInMainMemory;

	m_baseBufferSize     = baseBufferSize;
	m_overflowBufferSize = overflowBufferSize;

	// init buffer infos
	for (int i = 0; i < 3; i++)
	{
		BufferInfo& info = m_bufferInfos[i];

		info.m_buffer = hkAddByteOffset(bufferOnSpu, i * (overflowBufferSize+baseBufferSize+overflowBufferSize));
		info.m_startMarker = hkAddByteOffset(info.m_buffer.val(), overflowBufferSize);
		info.m_terminalMarker = hkAddByteOffset(info.m_buffer.val(), overflowBufferSize + baseBufferSize);
		info.m_startOfData = info.m_startMarker;
		info.m_dmaGroup = firstDmaGroup + i;

#		if defined (HK_PLATFORM_WIN32)
		info.m_mainMemPtrForFinalChecks = HK_NULL;
		info.m_mainMemSizeForFinalChecks = 0;
#		endif
	}

	// init buffer info pointers (Order cannto be changed -- look at the loop below!)
	m_workInfo = m_bufferInfos;
	m_prefetchInfo = m_bufferInfos + 1;
	m_writeInfo = m_bufferInfos + 2;

	// init main memory pointers
	m_currentReadPositionInMainMemory  = bufferInMainMemory;
	m_currentWritePositionInMainMemory = bufferInMainMemory;
	m_bufferEndInMainMemory = hkAddByteOffsetCpuPtr(bufferInMainMemory, size);

	// start dma reads into the work buffer and the prefetch buffer.
	if (! m_initAllToZero.val() )
	{
		for(int d = 0; d < 2; d++)
		{
			BufferInfo* info = m_bufferInfos + d;

			// start first and second dma
			const int bytesLeftToRead = (int)hkGetByteOffset(m_currentReadPositionInMainMemory, m_bufferEndInMainMemory);
			const int maxReadBufferSize = baseBufferSize+overflowBufferSize;
			//const int readSize = hkMath::min2(bytesLeftToRead, baseBufferSize+overflowBufferSize);
			const int readSize = bytesLeftToRead <= maxReadBufferSize ? bytesLeftToRead : maxReadBufferSize;
			if (readSize)
			{
				HK_DMA_SPU_ACCESSOR_STORE_INFO_FOR_PERFORM_FINAL_CHECKS(info, m_currentReadPositionInMainMemory, readSize);
				hkSpuDmaManager::getFromMainMemory(info->m_startMarker.val(), m_currentReadPositionInMainMemory, readSize, hkSpuDmaManager::READ_COPY, info->m_dmaGroup);
				m_currentReadPositionInMainMemory = hkAddByteOffset(m_currentReadPositionInMainMemory.val(), readSize);
			}
		}
	}
}

void* hkSpuDmaAccessor::switchBuffers(void* currentPositionOnSpu)
{
	const void* currentPositionInWorkBuffer16 = (void*)((~0xf) & hkUlong(currentPositionOnSpu));

	if (!m_initAllToZero.val())
	{	// wait for dmaCompleted for the next buffer
		hkSpuDmaManager::waitForDmaCompletion( m_prefetchInfo->m_dmaGroup);
		HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS(m_prefetchInfo, m_prefetchInfo->m_startMarker);
	}
	else
	{
		hkString::memClear16(m_prefetchInfo->m_startMarker.val(), ((unsigned int)(m_baseBufferSize + m_overflowBufferSize)) >> 4 );
	}

	{	// copy remaining data in current buffer to the next one

		const int copyStartPoint = (int)hkGetByteOffsetInt(m_workInfo->m_terminalMarker, currentPositionInWorkBuffer16);
		HK_ASSERT2(0xad6754bd, copyStartPoint >= 0, "Offset must be positive.");
		const int copySize = m_overflowBufferSize - copyStartPoint;

		HK_ASSERT2(0XAD987d55, 0 == (copySize & 0xf), "Data sizes not 16-byte aligned.");
		hkString::memCpy16( hkAddByteOffsetCpuPtr(m_prefetchInfo->m_buffer.val(), copyStartPoint), currentPositionInWorkBuffer16, copySize >> 4);

		m_prefetchInfo->m_startOfData = hkAddByteOffsetCpuPtr(m_prefetchInfo->m_buffer.val(), copyStartPoint);
	}

	{	// trigger write of the current buffer
		const int dataSize = (int)hkGetByteOffset(m_workInfo->m_startOfData, currentPositionInWorkBuffer16);
		HK_DMA_SPU_ACCESSOR_STORE_INFO_FOR_PERFORM_FINAL_CHECKS(m_workInfo, m_currentWritePositionInMainMemory, dataSize)
		hkSpuDmaManager::putToMainMemory( m_currentWritePositionInMainMemory, m_workInfo->m_startOfData, dataSize, hkSpuDmaManager::WRITE_NEW, m_workInfo->m_dmaGroup );
		m_currentWritePositionInMainMemory = hkAddByteOffset(m_currentWritePositionInMainMemory.val(), dataSize);
	}

	// moved this out of the following if statement, to avoid saving spu memory start
	{
		//   wait for (write) dmaCompleted of next(x2) buffer
		hkSpuDmaManager::waitForDmaCompletion(m_writeInfo->m_dmaGroup);
		HK_DMA_SPU_ACCESSOR_PERFORM_FINAL_CHECKS(m_writeInfo, m_writeInfo->m_startOfData);
	}


	//   if more data to be prefetched
	if (!m_initAllToZero.val() && m_currentReadPositionInMainMemory < m_bufferEndInMainMemory)
	{

		//   start preFetching into next(x2) buffer
		const int maxDataSize = m_baseBufferSize + m_overflowBufferSize;
		const int dataLeft = (int)hkGetByteOffset(m_currentReadPositionInMainMemory.val(), m_bufferEndInMainMemory);
		//const int dataSize = hkMath::min2(maxDataSize, dataLeft);
		const int dataSize = maxDataSize <= dataLeft ? maxDataSize : dataLeft;
		HK_DMA_SPU_ACCESSOR_STORE_INFO_FOR_PERFORM_FINAL_CHECKS(m_writeInfo, m_currentReadPositionInMainMemory, dataSize);
		hkSpuDmaManager::getFromMainMemory(m_writeInfo->m_startMarker, m_currentReadPositionInMainMemory, dataSize, hkSpuDmaManager::READ_COPY, m_writeInfo->m_dmaGroup);
		m_currentReadPositionInMainMemory = hkAddByteOffset(m_currentReadPositionInMainMemory.val(), dataSize);
	}
	// or zero buffer here .... 

	{	
		const hkUlong bufferDeltaPos = hkGetByteOffset(m_workInfo->m_terminalMarker, m_prefetchInfo->m_buffer);
		currentPositionOnSpu = hkAddByteOffsetCpuPtr(currentPositionOnSpu, bufferDeltaPos);

		// use next buffer as current
		BufferInfo* tmp = m_workInfo;
		m_workInfo = m_prefetchInfo;
		m_prefetchInfo = m_writeInfo;
		m_writeInfo = tmp;
	}
	return currentPositionOnSpu;
}


void hkSpuDmaAccessor::startFlush(void*& currentPositionOnSpu)
{
	HK_ASSERT2(0xad678daa, m_currentReadPositionInMainMemory <= m_bufferEndInMainMemory, "We've read past the buffer end.");

	if (m_workInfo->m_startOfData != currentPositionOnSpu)
	{
		// ! We're assuming that was the last data 
		currentPositionOnSpu = (void*)HK_NEXT_MULTIPLE_OF(16, hkUlong(currentPositionOnSpu));
		HK_ASSERT2(0xad678dab, m_currentReadPositionInMainMemory <= m_bufferEndInMainMemory, "We've read past the buffer end.");

		{	// trigger write of the current buffer

			const int dataSize = (int)hkGetByteOffset(m_workInfo->m_startOfData, currentPositionOnSpu);
			HK_DMA_SPU_ACCESSOR_STORE_INFO_FOR_PERFORM_FINAL_CHECKS(m_workInfo, m_currentWritePositionInMainMemory, dataSize)
			hkSpuDmaManager::putToMainMemory( m_currentWritePositionInMainMemory, m_workInfo->m_startOfData, dataSize, hkSpuDmaManager::WRITE_NEW, m_workInfo->m_dmaGroup );
			m_currentWritePositionInMainMemory = hkAddByteOffset(m_currentWritePositionInMainMemory.val(), dataSize);
		}

		HK_ASSERT2(0xad678daa, m_currentWritePositionInMainMemory <= m_currentReadPositionInMainMemory || m_initAllToZero.val(), "Writing out more than was read.");
	}

	currentPositionOnSpu = HK_NULL;
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
