/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Chain/BallSocket/hkpBallSocketChainData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Chain/BallSocket/hkpBallSocketChainData.h>



// External pointer and enum types
extern const hkClass hkpBallSocketChainDataConstraintInfoClass;
extern const hkClass hkpBridgeAtomsClass;

//
// Class hkpBallSocketChainData::ConstraintInfo
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpBallSocketChainData,ConstraintInfo);
static const hkInternalClassMember hkpBallSocketChainData_ConstraintInfoClass_Members[] =
{
	{ "pivotInA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBallSocketChainData::ConstraintInfo,m_pivotInA), HK_NULL },
	{ "pivotInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBallSocketChainData::ConstraintInfo,m_pivotInB), HK_NULL }
};
const hkClass hkpBallSocketChainDataConstraintInfoClass(
	"hkpBallSocketChainDataConstraintInfo",
	HK_NULL, // parent
	sizeof(hkpBallSocketChainData::ConstraintInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpBallSocketChainData_ConstraintInfoClass_Members),
	HK_COUNT_OF(hkpBallSocketChainData_ConstraintInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpBallSocketChainData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpBallSocketChainData);
static const hkInternalClassMember hkpBallSocketChainDataClass_Members[] =
{
	{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBallSocketChainData,m_atoms), HK_NULL },
	{ "infos", &hkpBallSocketChainDataConstraintInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpBallSocketChainData,m_infos), HK_NULL },
	{ "tau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBallSocketChainData,m_tau), HK_NULL },
	{ "damping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBallSocketChainData,m_damping), HK_NULL },
	{ "cfm", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBallSocketChainData,m_cfm), HK_NULL },
	{ "maxErrorDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBallSocketChainData,m_maxErrorDistance), HK_NULL }
};
extern const hkClass hkpConstraintChainDataClass;

extern const hkClass hkpBallSocketChainDataClass;
const hkClass hkpBallSocketChainDataClass(
	"hkpBallSocketChainData",
	&hkpConstraintChainDataClass, // parent
	sizeof(hkpBallSocketChainData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpBallSocketChainDataClass_Members),
	HK_COUNT_OF(hkpBallSocketChainDataClass_Members),
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
