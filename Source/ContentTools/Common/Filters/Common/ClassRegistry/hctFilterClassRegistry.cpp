/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

#include <ContentTools/Common/Filters/Common/ClassRegistry/hctFilterClassRegistry.h>

#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>
#include <Common/Base/Reflection/Registry/hkTypeInfoRegistry.h>
#include <Common/Base/Reflection/Registry/hkClassNameRegistry.h>

struct hctFilterClassRegistry::Implementation
{
	hkVtableClassRegistry vreg;
	hkTypeInfoRegistry treg;
	hkClassNameRegistry nreg;
};

hctFilterClassRegistry::hctFilterClassRegistry()
{
	m_impl = new Implementation();
}

hctFilterClassRegistry::~hctFilterClassRegistry()
{
	delete m_impl;
}

const hkVtableClassRegistry& hctFilterClassRegistry::getVtableRegistry() const
{
	return m_impl->vreg;
}

const hkTypeInfoRegistry& hctFilterClassRegistry::getTypeInfoRegistry() const
{
	return m_impl->treg;
}


const hkClassNameRegistry& hctFilterClassRegistry::getClassNameRegistry() const
{
	return m_impl->nreg;
}

hkVtableClassRegistry& hctFilterClassRegistry::getVtableRegistry()
{
	return m_impl->vreg;
}

hkTypeInfoRegistry& hctFilterClassRegistry::getTypeInfoRegistry()
{
	return m_impl->treg;
}


hkClassNameRegistry& hctFilterClassRegistry::getClassNameRegistry()
{
	return m_impl->nreg;
}

const hkClass* hctFilterClassRegistry::getClassFromVirtualInstance(void* o) const
{
	return m_impl->vreg.getClassFromVirtualInstance(o);
}

void hctFilterClassRegistry::registerClass(const hkTypeInfo* ti, const hkClass* ci)
{
	if (ti->getVtable()!=HK_NULL)
	{
		m_impl->vreg.registerVtable( ti->getVtable(), ci );
	}
	m_impl->treg.registerTypeInfo( ti );
	m_impl->nreg.registerClass( ci );
}

void hctFilterClassRegistry::registerClasses(const hkTypeInfo* const * tis, const hkClass* const * cis)
{
	m_impl->vreg.registerList(tis, cis);
	m_impl->treg.registerList(tis);
	m_impl->nreg.registerList(cis);
}

void hctFilterClassRegistry::merge( const hctFilterClassRegistry& mergeFrom )
{
	m_impl->vreg.merge( mergeFrom.m_impl->vreg );
	m_impl->treg.merge( mergeFrom.m_impl->treg );
	m_impl->nreg.merge( mergeFrom.m_impl->nreg );
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
