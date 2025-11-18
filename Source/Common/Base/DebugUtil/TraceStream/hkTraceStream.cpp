/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/DebugUtil/TraceStream/hkTraceStream.h>
#include <Common/Base/Fwd/hkcstdarg.h>
using namespace std;

HK_SINGLETON_IMPLEMENTATION(hkTraceStream);

static const int HK_TRACE_STREAM_MAX_STRING_SIZE = 1024;

void hkTraceStream::printf( const char* title, const char* fmt, ... )
{
	// break if title is not supported
	{
		for (int i = 0; i < m_titles.getSize(); i++)
		{
			if (0 == hkString::strCmp(m_titles[i].m_value, title))
			{
				//don't display this message
				return;
			}
		}
	}

	m_counter++;
	if ( m_counter == 2051)
	{
		// place your breakpoint here:
		m_counter *= 1;
	}

	if ( m_stream )
	{
		char buf[HK_TRACE_STREAM_MAX_STRING_SIZE];
		//
		//	output line number
		//
		va_list args; 
		va_start(args, fmt);

		if ( fmt[0] == '#')
		{
			hkString::sprintf( buf, "%4i\t\t", m_counter );
			m_stream->write(buf, hkString::strLen( buf ) );
			hkString::vsnprintf(buf, HK_TRACE_STREAM_MAX_STRING_SIZE, fmt+1, args);
		}
		else
		{
			hkString::vsnprintf(buf, HK_TRACE_STREAM_MAX_STRING_SIZE, fmt, args);
		}
		va_end(args);
		m_stream->write(buf, hkString::strLen( buf ) );
	}
}

void hkTraceStream::dontPrintf( const char* title, const char* fmt, ... )
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
