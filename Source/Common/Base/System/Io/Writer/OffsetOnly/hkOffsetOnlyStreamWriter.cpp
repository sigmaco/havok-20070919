/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Writer/OffsetOnly/hkOffsetOnlyStreamWriter.h>

hkOffsetOnlyStreamWriter::hkOffsetOnlyStreamWriter()
	: m_offset(0), m_eofOffset(0)
{
}

hkBool hkOffsetOnlyStreamWriter::isOk() const
{
	return true;
}

int hkOffsetOnlyStreamWriter::write(const void*, int n)
{
	m_offset += n;
	m_eofOffset = m_offset > m_eofOffset ? m_offset : m_eofOffset;
	return n;
}

hkBool hkOffsetOnlyStreamWriter::seekTellSupported() const
{
	return true;
}

hkResult hkOffsetOnlyStreamWriter::seek(int offset, SeekWhence whence)
{
	switch(whence)
	{
		case hkStreamWriter::STREAM_SET:
			m_offset = offset;
			break;
		case STREAM_CUR:
			m_offset += offset;
			break;
		case STREAM_END:
			m_offset = m_eofOffset - offset;
			break;
		default:
			HK_ASSERT2(0x783b0cbf, 0, "Unknown seek type given to fake stream writer.");
	}
	m_eofOffset = m_offset > m_eofOffset ? m_offset : m_eofOffset;
	HK_ASSERT2(0x50df405e, m_offset >= 0, "Underflow in seek() on fake stream writer." );
	return HK_SUCCESS;
}

int hkOffsetOnlyStreamWriter::tell() const
{
	return m_offset;
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
