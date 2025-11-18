/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */



#include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>

hkSpuDmaSparseWriter::hkSpuDmaSparseWriter()
{
}



hkSpuDmaSparseWriter::~hkSpuDmaSparseWriter() 
{
#ifdef HK_DEBUG
	if ( m_currentPositionInWorkBuffer != m_workBufferInfo->m_buffer )
	{
		//HK_ASSERT2(0xaf38de44, false, "You have to manually flush the hkSpuDmaSparseWriter before calling its destructor.");
	}
#endif
}

void hkSpuDmaSparseWriter::init(void* bufferOnSpu, int baseBufferSize, int overflowBufferSize, int firstDmaGroup) 
{ 
	HK_ASSERT2(0xaf312455, !(hkUlong(bufferOnSpu) & 0x0f),     "Buffer on spu must be 16-bytes-aligned!");
	HK_ASSERT2(0xaf319755, !((baseBufferSize) & 0x0f),     "baseBufferSize must be a multiple of 16");
	HK_ASSERT2(0xaf319425, !((overflowBufferSize) & 0x0f), "overflowBufferSize must be a multiple of 16");

	for (int i = 0; i < 2; i++)
	{
		m_bufferInfos[i].m_buffer                = hkAddByteOffset(bufferOnSpu, i * (baseBufferSize + overflowBufferSize));
		HK_ASSERT2(0xad8755dd, !i || (hkAddByteOffset(m_bufferInfos[i-1].m_terminalMarker.val(), overflowBufferSize) == m_bufferInfos[i].m_buffer.val()), "Internal error: Buffer overlap conflict.");
		m_bufferInfos[i].m_terminalMarker        = hkAddByteOffset(m_bufferInfos[i].m_buffer.val(), baseBufferSize);
		m_bufferInfos[i].m_dmaGroup = firstDmaGroup + i;
	}

	m_workBufferInfo = m_bufferInfos;
	m_transferBufferInfo = m_bufferInfos + 1;

	m_currentPositionInWorkBuffer = m_workBufferInfo->m_buffer;

	m_overflowBufferSize = overflowBufferSize;
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
