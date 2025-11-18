/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_DEFAULT_ERROR
#define HK_DEFAULT_ERROR

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Base/Memory/StackTracer/hkStackTracer.h>
#include <Common/Base/System/Io/Writer/Buffered/hkBufferedStreamWriter.h>

/// This is the default implementation of our error handling interface.
/// It supports error and assert enabling and disabling and where possible
/// it walks and reports the full stack trace leading up to the error.
/// Usually you will derive from this class and override showMessage when
/// integrating this class in you game.
class hkDefaultError : public hkError
{
	public:

		hkDefaultError( hkErrorReportFunction errorReportFunction, void* errorReportObject = HK_NULL )
			: m_errorFunction(errorReportFunction), m_errorObject(errorReportObject)
		{
		}

		virtual void setEnabled( int id, hkBool enabled )
		{
			if( enabled )
			{
				m_disabledAssertIds.remove(id);
			}
			else
			{
				m_disabledAssertIds.insert(id, 1);
			}
		}

		virtual hkBool isEnabled( int id )
		{
			return m_disabledAssertIds.getWithDefault(id, 0) == 0;
		}

		virtual void enableAll()
		{
			m_disabledAssertIds.clear();
		}

protected:

	void showMessage(const char* what, int id, const char* desc, const char* file, int line, hkBool stackTrace=true)
	{
		char idAsHex[12];
		hkString::sprintf(idAsHex, "0x%x", id);

		char buf[512];
		hkBufferedStreamWriter writer(buf, sizeof(buf), true);
		hkOstream os(&writer);
#if !defined(HK_PLATFORM_UNIX)
		os << file << '(' << line << "): [" << idAsHex << "] " << what << " : '" << desc << "'\n";
#else
		os << file << ':' << line << ": ["  << idAsHex << "] " << what << " : '" << desc << "'\n";
#endif
		(*m_errorFunction)( buf, m_errorObject );

		if( stackTrace )
		{
			hkStackTracer strace;
			hkUlong trace[20];
			int ntrace = strace.getStackTrace(trace, sizeof(trace)/sizeof(trace[0]) );
			if( ntrace > 2 )
			{
				(*m_errorFunction)("Stack trace is:\n", m_errorObject);
				// first two frames are in this file.

				strace.dumpStackTrace(trace+2, ntrace-2, m_errorFunction, m_errorObject);
			}
		}
	}

public:


		virtual int message(hkError::Message msg, int id, const char* description, const char* file, int line)
		{
			if( id == -1 && m_sectionIds.getSize() )
			{
				id = m_sectionIds.back();
			}

			if (!isEnabled(id))
			{
				return 0;
			}

			const char* what = "";

			hkBool stackTrace = false;
			switch( msg )
			{
				case MESSAGE_REPORT:
					what = "Report";
					break;
				case MESSAGE_WARNING:
					what = "Warning";
					break;
				case MESSAGE_ASSERT:
					what = "Assert";
					stackTrace = true;
					break;
				case MESSAGE_ERROR:
					what = "Error";
					stackTrace = true;
					break;
			}
			showMessage(what, id, description, file, line, stackTrace);
			return msg == MESSAGE_ASSERT || msg == MESSAGE_ERROR;
		}

		virtual void sectionBegin(int id, const char* sectionName)
		{
			m_sectionIds.pushBack(id);
		}

		virtual void sectionEnd()
		{
			m_sectionIds.popBack();
		}

		hkPointerMap<int, int> m_disabledAssertIds;
		hkArray<int> m_sectionIds;
		hkErrorReportFunction m_errorFunction;
		void* m_errorObject;
};

#endif // HK_DEFAULT_ERROR


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
