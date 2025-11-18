/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Chain/StiffSpring/hkpStiffSpringChainData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Chain/StiffSpring/hkpStiffSpringChainData.h>



// External pointer and enum types
extern const hkClass hkpBridgeAtomsClass;
extern const hkClass hkpStiffSpringChainDataConstraintInfoClass;

//
// Class hkpStiffSpringChainData::ConstraintInfo
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpStiffSpringChainData,ConstraintInfo);
static const hkInternalClassMember hkpStiffSpringChainData_ConstraintInfoClass_Members[] =
{
	{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringChainData::ConstraintInfo,m_pivotInA), HK_NULL },
	{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringChainData::ConstraintInfo,m_pivotInB), HK_NULL },
	{ "springLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringChainData::ConstraintInfo,m_springLength), HK_NULL }
};
const hkClass hkpStiffSpringChainDataConstraintInfoClass(
	"hkpStiffSpringChainDataConstraintInfo",
	HK_NULL, // parent
	sizeof(hkpStiffSpringChainData::ConstraintInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStiffSpringChainData_ConstraintInfoClass_Members),
	HK_COUNT_OF(hkpStiffSpringChainData_ConstraintInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpStiffSpringChainData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpStiffSpringChainData);
static const hkInternalClassMember hkpStiffSpringChainDataClass_Members[] =
{
	{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringChainData,m_atoms), HK_NULL },
	{ "infos", &hkpStiffSpringChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpStiffSpringChainData,m_infos), HK_NULL },
	{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringChainData,m_tau), HK_NULL },
	{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringChainData,m_damping), HK_NULL },
	{ "cfm", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringChainData,m_cfm), HK_NULL }
};
extern const hkClass hkpConstraintChainDataClass;

extern const hkClass hkpStiffSpringChainDataClass;
const hkClass hkpStiffSpringChainDataClass(
	"hkpStiffSpringChainData",
	&hkpConstraintChainDataClass, // parent
	sizeof(hkpStiffSpringChainData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStiffSpringChainDataClass_Members),
	HK_COUNT_OF(hkpStiffSpringChainDataClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

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
