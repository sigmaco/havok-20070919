/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>

hkRootLevelContainer::NamedVariant::NamedVariant()
{
	set(HK_NULL, HK_NULL, HK_NULL);
}

hkRootLevelContainer::NamedVariant::NamedVariant(const char* name, void* object, const hkClass* klass)
{
	set(name, object, klass);
}

hkRootLevelContainer::NamedVariant::NamedVariant(const char* name, const hkVariant& v)
{
	set(name, v);
}

void* hkRootLevelContainer::findObjectByType( const char* typeName, const void* prevObject ) const
{
	int index = 0;
	while ((prevObject) && (index < m_numNamedVariants) && (m_namedVariants[index++].getObject() != prevObject));

	for (int i=index; i < m_numNamedVariants; i++)
	{
		if ( hkString::strCmp( typeName, m_namedVariants[i].getTypeName() ) == 0 )
		{
			return m_namedVariants[i].getObject();
		}
	}
	return HK_NULL;
}

void* hkRootLevelContainer::findObjectByName( const char* objectName, const void* prevObject ) const
{
	int index = 0;
	while ((prevObject) && (index < m_numNamedVariants) && (m_namedVariants[index++].getObject() != prevObject));

	for (int i=index; i < m_numNamedVariants; i++)
	{
		if (hkString::strCmp( objectName, m_namedVariants[i].getName() ) == 0)
		{
			return m_namedVariants[i].getObject();
		}
	}
	return HK_NULL;

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
