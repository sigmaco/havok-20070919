/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/Serialize/hkObjectSerializeRegistry.h>

typedef hkPointerMap< hkUint64, void* >::Iterator     PtrMapIterator;
typedef hkPointerMap< hkUint64, hkUint32 >::Iterator  SizeMapIterator;

hkObjectSerializeRegistry::~hkObjectSerializeRegistry()
{
	clear();
}

void hkObjectSerializeRegistry::clear()
{
	PtrMapIterator iter = m_idToObjectMap.getIterator();
	while (m_idToObjectMap.isValid(iter))
	{
		hkDeallocate<char>( reinterpret_cast<char*>(m_idToObjectMap.getValue(iter)) );
		iter = m_idToObjectMap.getNext(iter);
	}
	m_idToObjectMap.clear();
	m_idToObjectSizeMap.clear();
}

void hkObjectSerializeRegistry::addObject( hkUint64 id, void* data, hkUint32 dataSize )
{
	char* prevData = HK_NULL;
	PtrMapIterator iter = m_idToObjectMap.findKey( id );
	if ( m_idToObjectMap.isValid(iter) )
	{
		hkDeallocate<char>( prevData ); // replace data
		
		SizeMapIterator siter = m_idToObjectSizeMap.findKey( id );
		m_idToObjectMap.setValue(iter, data);
		m_idToObjectSizeMap.setValue(siter, dataSize);
	}
	else // new id.
	{
		m_idToObjectMap.insert( id, data );
		m_idToObjectSizeMap.insert( id, dataSize);
	}
}

void hkObjectSerializeRegistry::deleteObject( hkUint64 id)
{
	PtrMapIterator iter = m_idToObjectMap.findKey( id );
	if ( m_idToObjectMap.isValid(iter) )
	{
		hkDeallocate<char>( reinterpret_cast<char*>( m_idToObjectMap.getValue(iter)) );
		SizeMapIterator siter = m_idToObjectSizeMap.findKey( id );
		
		m_idToObjectMap.remove(iter);
		m_idToObjectSizeMap.remove(siter);
	}
}

void* hkObjectSerializeRegistry::getObjectData( hkUint64 id )
{
	return m_idToObjectMap.getWithDefault(id, HK_NULL);
}

hkUint32 hkObjectSerializeRegistry::getObjectSize( hkUint64 id )
{
	return m_idToObjectSizeMap.getWithDefault(id, 0);
}

hkUint64 hkObjectSerializeRegistry::findObjectID( const void* data )
{
	PtrMapIterator iter = m_idToObjectMap.getIterator( );
	while (m_idToObjectMap.isValid(iter))
	{
		if ( m_idToObjectMap.getValue(iter) == data )
			return m_idToObjectMap.getKey(iter);

		iter = m_idToObjectMap.getNext(iter);
	}
	return 0;
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
