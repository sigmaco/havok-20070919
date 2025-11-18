/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/SceneExport/hctSceneExport.h> // PCH
#include <ContentTools/Common/SceneExport/Error/hctSceneExportError.h> 

#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>
#include <Common/Base/System/Io/Writer/Stdio/hkStdioStreamWriter.cxx>


int hctSceneExportError::message(Message type, int id, const char* description, const char* file, int line)
{
	// Skip disabled ids
	if( !isEnabled(id) )
	{
		return 0;
	}
	
	// Create the new log entry
	LogEntry entry( type, id, description, file, line );
	
	// Prefix with the current indent
	for( int i=0; i<m_indent; ++i )
	{
		entry.m_text = hkString("    ") + entry.m_text;
	}
	
	// Store the entry
	m_log.pushBack( entry );
	
	return ( type == MESSAGE_ASSERT || type == MESSAGE_ERROR );
}


void hctSceneExportError::setEnabled( int id, hkBool enabled )
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

hkBool hctSceneExportError::isEnabled( int id )
{
	return m_disabledAssertIds.getWithDefault(id, 0) == 0;
}

void hctSceneExportError::enableAll()
{
	m_disabledAssertIds.clear();
}


void hctSceneExportError::sectionBegin(int id, const char* desc) 
{
	char buf[1024];
	{
		hkOstream os(buf, sizeof(buf), true);
		os << "[ " << desc << " ]";
	}

	message( MESSAGE_REPORT, 0, buf, 0, 0 );
	m_indent++;
}

void hctSceneExportError::sectionEnd() 
{ 
	m_indent--;
}


void hctSceneExportError::merge( const hctSceneExportError* otherHandler )
{
	if( otherHandler )
	{
		for( int i=0; i<otherHandler->m_log.getSize(); ++i )
		{
			m_log.pushBack( otherHandler->m_log[i] );
		}
	}
}


hctSceneExportError::LogEntry::LogEntry(hkError::Message type, int id, const char* desc, const char* file, int line)
{
	m_type = type;
	
	hkString messageStr;
	switch( type )
	{
	case MESSAGE_REPORT:
		m_text = desc;
		return;
	case MESSAGE_WARNING:
		messageStr = "Warning";
		break;
	case MESSAGE_ASSERT:
		messageStr = "Assert";
		break;
	case MESSAGE_ERROR:
		messageStr = "Error";
		break;
	}
	
	if( id == 0 )
	{
		m_text.printf( "%s: %s", messageStr.cString(), desc );
	}
	else
	{
		m_text.printf( "%s [0x%x]: %s", messageStr.cString(), id, desc );
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
