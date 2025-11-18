/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Config/hkConfigVersion.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Base/Container/StringMap/hkStringMap.h>
#include <Common/Serialize/Version/hkVersionRegistry.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Serialize/Util/hkStructureLayout.h>
#include <Common/Serialize/Version/hkVersionUtil.h>

static int getNumElements(const hkVersionRegistry::Updater** p)
{
	int i = 0;
	while( *p != HK_NULL )
	{
		++i;
		++p;
	}
	return i;
}

static inline void computeMemberOffsetsInplace(hkClass*const* klasses)
{
	hkStructureLayout layout;
	hkPointerMap<const hkClass*, int> done;
	hkClass*const* ci = klasses;
	while(*ci != HK_NULL)
	{
		layout.computeMemberOffsetsInplace( **ci, done );
		++ci;
	}
}

hkVersionRegistry::hkVersionRegistry()
	: m_updaters( StaticLinkedUpdaters, getNumElements(StaticLinkedUpdaters), getNumElements(StaticLinkedUpdaters) )
{
}

hkVersionRegistry::~hkVersionRegistry()
{
	for (hkStringMap<hkClassNameRegistry*>::Iterator iter = m_versionToClassNameRegistryMap.getIterator(); m_versionToClassNameRegistryMap.isValid(iter); iter = m_versionToClassNameRegistryMap.getNext(iter))
	{
		hkClassNameRegistry* classRegistry = m_versionToClassNameRegistryMap.getValue(iter);
		classRegistry->removeReference();
	}
	m_versionToClassNameRegistryMap.clear();
}

void hkVersionRegistry::registerUpdater( const Updater* updater )
{
	m_updaters.pushBack(updater);
}

static inline int strEqual(const char* s0, const char* s1)
{
	return hkString::strCmp( s0, s1 ) == 0;
}

hkResult hkVersionRegistry::getVersionPath( const char* fromVersion, const char* toVersion, hkArray<const Updater*>& pathOut ) const
{
	if( hkString::strCmp(fromVersion, toVersion) == 0 )
	{
		return HK_SUCCESS; // succeed trivially
	}

	hkArray<int> nextEdge;
	nextEdge.setSize( m_updaters.getSize(), -1 );

	hkArray<int> sourceIndices;
	hkArray<int> targetIndices;
	{
		for( int updaterIndex = 0; updaterIndex < m_updaters.getSize(); ++updaterIndex )
		{
			if( strEqual( toVersion, m_updaters[updaterIndex]->toVersion) )
			{
				// early out if we're there
				if( strEqual( fromVersion, m_updaters[updaterIndex]->fromVersion) )
				{
					pathOut.pushBack( m_updaters[updaterIndex] );
					return HK_SUCCESS;
				}

				targetIndices.pushBack( updaterIndex );
			}
			else
			{
				sourceIndices.pushBack( updaterIndex );
			}
		}
	}

	while( targetIndices.getSize() )
	{
		hkArray<int> nextTargetIndices;
		for( int sourceIndexIndex = sourceIndices.getSize()-1; sourceIndexIndex >= 0; --sourceIndexIndex )
		{
			int sourceIndex = sourceIndices[sourceIndexIndex];

			for( int targetIndexIndex = 0; targetIndexIndex < targetIndices.getSize(); ++targetIndexIndex )
			{
				int targetIndex = targetIndices[targetIndexIndex];

				if( strEqual( m_updaters[sourceIndex]->toVersion, m_updaters[targetIndex]->fromVersion) )
				{
					nextEdge[sourceIndex] = targetIndex;
					if( strEqual( m_updaters[sourceIndex]->fromVersion, fromVersion ) )
					{
						int i = sourceIndex;
						while( i != -1 )
						{
							pathOut.pushBack(m_updaters[i]);
							i = nextEdge[i];
						}
						return HK_SUCCESS;
					}
					
					nextTargetIndices.pushBack( sourceIndex );
					sourceIndices.removeAt( sourceIndexIndex );
				}
			}
		}
		targetIndices.swap( nextTargetIndices );
	}
	
	return HK_FAILURE;
}

const hkClassNameRegistry* hkVersionRegistry::getClassNameRegistry( const char* versionString )
{
	HK_ASSERT(0x5997db19, versionString != HK_NULL);

	hkClassNameRegistry* classRegistry;
	hkResult res = m_versionToClassNameRegistryMap.get(versionString, &classRegistry);
	if (res == HK_SUCCESS)
	{
		return classRegistry;
	}

	ClassList* classList = StaticLinkedClassList;
	classRegistry = HK_NULL;
	// register other versions
	while (classList->version != HK_NULL)
	{
		if (hkString::strCmp(versionString, classList->version) == 0)
		{
			if (hkString::strCmp(versionString, HAVOK_SDK_VERSION_STRING) == 0)
			{
				classRegistry = hkBuiltinTypeRegistry::getInstance().getClassNameRegistry();
				classRegistry->addReference();
			}
			else
			{
				// lazily create new registry
				classRegistry = new hkClassNameRegistry();
				classRegistry->registerList(classList->getClasses());
			}
			m_versionToClassNameRegistryMap.insert(classList->version, classRegistry);
			break;
		}
		++classList;
	}
	// the version string is not presented in the static class
	// list we return HK_NULL (classRegistry initialized to HK_NULL)
	return classRegistry;
}

const hkClass*const* hkVersionRegistry::ClassList::getClasses()
{
	if( readyToUse == false )
	{
		hkVersionUtil::recomputeClassMemberOffsets( privateClasses, classVersion );
		readyToUse = true;
	}
	return privateClasses;
}

HK_SINGLETON_IMPLEMENTATION(hkVersionRegistry);

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
