/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Packfile/hkPackfileData.h>
#include <Common/Base/Reflection/hkTypeInfo.h>

#if 0 && defined(HK_DEBUG)
#	include <Common/Base/Fwd/hkcstdio.h>
	using namespace std;
#	define TRACE(A) A
#else
#	define TRACE(A) // nothing
#endif

hkPackfileData::hkPackfileData()
	: m_name(HK_NULL)
{
}

void hkPackfileData::callDestructors()
{
	for( TrackedObjectMap::Iterator it = m_trackedObjects.getIterator();
		m_trackedObjects.isValid(it); it = m_trackedObjects.getNext(it) )
	{
		if( hkTypeInfo::CleanupLoadedObjectFunction f = m_trackedObjects.getValue(it)->getCleanupFunction() )
		{
			TRACE(printf("-dtor\t%s at %p...", m_trackedObjects.getValue(it)->getTypeName(), m_trackedObjects.getKey(it)));
			(*f)(m_trackedObjects.getKey(it));
			TRACE(printf("done.\n"));
		}
	}
	m_trackedObjects.clear();
}

hkPackfileData::~hkPackfileData()
{
	callDestructors();

	hkThreadMemory& mem = hkThreadMemory::getInstance();
	int i;
	for( i = 0; i < m_memory.getSize(); ++i )
	{
		mem.deallocate(m_memory[i]);
	}
	for( i = 0; i < m_chunks.getSize(); ++i )
	{
		mem.deallocateChunk(m_chunks[i].pointer, m_chunks[i].numBytes, m_chunks[i].memClass );
	}
	hkDeallocate<char>(m_name);
}

void hkPackfileData::setName(const char* n)
{
	hkDeallocate<char>(m_name);
	m_name = hkString::strDup(n);
}

void hkPackfileData::getImportsExports( hkArray<Import>& impOut, hkArray<Export>& expOut )
{
	impOut = m_imports;
	expOut = m_exports;
}

void hkPackfileData::addExport( const char* symbolName, void* object )
{
	Export& e = m_exports.expandOne();
	e.name = symbolName;
	e.data = object;
}

void hkPackfileData::removeExport( void* object )
{
	for( int i = m_exports.getSize() - 1; i >= 0; --i )
	{
		if( m_exports[i].data == object )
		{
			m_exports.removeAt(i);
			// no early out: object may be exported under several names
		}
	}
}

void hkPackfileData::addImport( const char* symbolName, void** location )
{
#	if defined(HK_DEBUG)
	for( int i = 0; i < m_imports.getSize(); ++i )
	{
		HK_ASSERT2( 0x80fd563f, m_imports[i].location != location, "Duplicate import location found");
	}
#	endif
	Import& i = m_imports.expandOne();
	i.name = symbolName;
	i.location = location;
}


void hkPackfileData::removeImport( void** location )
{
	for( int i = m_imports.getSize() - 1; i >= 0; --i )
	{
		if( m_imports[i].location == location )
		{
			m_imports.removeAt(i);
			// early out: location is unique
			break;
		}
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
