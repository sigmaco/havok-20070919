/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Reader/LineNumber/hkLineNumberStreamReader.h>

hkLineNumberStreamReader::hkLineNumberStreamReader(hkStreamReader* s)
	:	m_stream(s),
		m_lineNumber(0),
		m_lineNumberAtMark(0)
{
	HK_ASSERT(0x1437d124, s != HK_NULL);
	m_stream->addReference();
}

hkLineNumberStreamReader::~hkLineNumberStreamReader()
{
	m_stream->removeReference();
}

int hkLineNumberStreamReader::read(void* buf, int nbytes)
{
	int n = m_stream->read(buf, nbytes);
	char* cbuf = static_cast<char*>(buf);
	for( int i = 0; i < n; ++i )
	{
		m_lineNumber += (cbuf[i] == '\n');
	}
	return n;
}

hkBool hkLineNumberStreamReader::isOk() const
{
	return m_stream->isOk();
}

hkBool hkLineNumberStreamReader::markSupported() const
{
	return m_stream->markSupported();
}

hkResult hkLineNumberStreamReader::setMark(int limit)
{
	hkResult r = m_stream->setMark(limit);
	if( r == HK_SUCCESS )
	{
		m_lineNumberAtMark = m_lineNumber;
	}
	return r;
}

hkResult hkLineNumberStreamReader::rewindToMark()
{
	hkResult r = m_stream->rewindToMark();
	if( r == HK_SUCCESS )
	{
		m_lineNumber = m_lineNumberAtMark;
	}
	return r;
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
