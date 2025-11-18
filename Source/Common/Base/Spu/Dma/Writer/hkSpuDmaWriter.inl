/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */



#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>

hkSpuDmaWriter::hkSpuDmaWriter()
{
}



hkSpuDmaWriter::~hkSpuDmaWriter() 
{
#ifdef HK_DEBUG
	if ( m_currentPositionInWorkBuffer != m_workBuffer )
	{
		HK_ASSERT2(0xaf38de44, false, "You have to manually flush the hkSpuDmaWriter before calling its destructor.");
	}
#endif
}



void hkSpuDmaWriter::init(HK_CPU_PTR(void*) dstInMainMemory, int size, void* bufferOnSpu, int baseBufferSize, int overflowBufferSize, int dmaGroup0, int dmaGroup1) 
{ 
	HK_ASSERT2(0xaf319455, !(hkUlong(dstInMainMemory) & 0x0f), "Destination buffer in main memory must be 16-bytes-aligned!");
	HK_ASSERT2(0xaf312455, !(hkUlong(bufferOnSpu) & 0x0f),     "Buffer on spu must be 16-bytes-aligned!");
	HK_ASSERT2(0xaf349456, (size==-1) || !(size & 0x0f),   "Destination buffer size must be a multiple of 16!");
	HK_ASSERT2(0xaf319755, !((baseBufferSize) & 0x0f),     "baseBufferSize must be a multiple of 16");
	HK_ASSERT2(0xaf319425, !((overflowBufferSize) & 0x0f), "overflowBufferSize must be a multiple of 16");

	m_workDmaGroup             = dmaGroup0;
	m_transferDmaGroup         = dmaGroup1;
	m_workBuffer               = bufferOnSpu;
	m_transferBuffer           = hkAddByteOffset(bufferOnSpu, (baseBufferSize+overflowBufferSize));
	m_baseBufferSize           = baseBufferSize;
	m_currentDstPosition       = dstInMainMemory;

	m_currentPositionInWorkBuffer = m_workBuffer;

	HK_ON_DEBUG( m_wasBufferRequested = false );
	m_overflowBufferSize = overflowBufferSize;
	m_dstEnd = (size != -1) ? hkAddByteOffsetCpuPtr(dstInMainMemory, size) : HK_NULL;
}



void* hkSpuDmaWriter::requestBuffer()
{
	HK_ASSERT2(0xaf639dd5, !m_wasBufferRequested.val(), "Cannot call requestBuffer twice in a row.");
	HK_ON_DEBUG( m_wasBufferRequested = true );
	return m_currentPositionInWorkBuffer;
}


void* hkSpuDmaWriter::getCurrentDestInMainMemory()
{
	hkUlong offsetInWorkBuffer = hkGetByteOffset(m_workBuffer, m_currentPositionInWorkBuffer);
	void *destInMainMemory = hkAddByteOffsetCpuPtr(m_currentDstPosition.val(), offsetInWorkBuffer);
	return destInMainMemory;
}


void hkSpuDmaWriter::finishWrite(void* currentPositionOnSpu)
{
	HK_ASSERT2(0xaf639dd5, m_wasBufferRequested.val(), "Call requestBuffer() before calling finishWrite().");
	HK_ON_DEBUG( m_wasBufferRequested = false );

	m_currentPositionInWorkBuffer = currentPositionOnSpu;

	// Amount/size of the buffer used
	const int sizebufferUsed = hkGetByteOffsetInt( m_workBuffer, m_currentPositionInWorkBuffer );

	// assert we haven't overflown
	HK_ASSERT2( 0xad7899dd, sizebufferUsed <= m_baseBufferSize + m_overflowBufferSize, "The hkSpuDmaWriter has been overflown." );

	// check if past the main buffer part, if so then start dma writeback
	if ( sizebufferUsed >= m_baseBufferSize )
	{
		writeBackBuffer(sizebufferUsed);
	}
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
