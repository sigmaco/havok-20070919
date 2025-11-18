/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Util/hkChainedClassNameRegistry.h>


hkChainedClassNameRegistry::hkChainedClassNameRegistry( const hkClassNameRegistry* nextReg )
	: m_nextRegistry(nextReg)
{
	if( m_nextRegistry != HK_NULL )
	{
		m_nextRegistry->addReference();
	}
}

hkChainedClassNameRegistry::~hkChainedClassNameRegistry()
{
	if( m_nextRegistry )
	{
		m_nextRegistry->removeReference();
	}
}

void hkChainedClassNameRegistry::setNextRegistry(const hkClassNameRegistry* nextRegistry)
{
	if( m_nextRegistry )
	{
		m_nextRegistry->removeReference();
	}
	m_nextRegistry = nextRegistry;
	if( m_nextRegistry )
	{
		m_nextRegistry->addReference();
	}
}

const hkClass* hkChainedClassNameRegistry::getClassByName( const char* className ) const
{
	if( const hkClass* c = hkClassNameRegistry::getClassByName( className ) )
	{
		return c;
	}
	return m_nextRegistry
		? m_nextRegistry->getClassByName( className )
		: HK_NULL;
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
