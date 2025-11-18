/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>
#include <Common/Base/Reflection/hkClass.h>

void hkVtableClassRegistry::registerList( const hkTypeInfo* const * infos, const hkClass* const * classes)
{
	const hkTypeInfo* const * ti = infos;
	const hkClass* const * ci = classes;
	while(*ti != HK_NULL && *ci != HK_NULL)
	{
		if( const void* vtable = (*ti)->getVtable() )
		{
			registerVtable( vtable, *ci );
		}
		++ti;
		++ci;
	}
}

void hkVtableClassRegistry::merge(const hkVtableClassRegistry& mergeFrom)
{
	hkPointerMap<const void*, const hkClass*>::Iterator iter = mergeFrom.m_map.getIterator();
	while (mergeFrom.m_map.isValid(iter))
	{
		m_map.insert( mergeFrom.m_map.getKey(iter), mergeFrom.m_map.getValue(iter) );
		iter = mergeFrom.m_map.getNext(iter);
	}
}

HK_SINGLETON_IMPLEMENTATION(hkVtableClassRegistry);

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
