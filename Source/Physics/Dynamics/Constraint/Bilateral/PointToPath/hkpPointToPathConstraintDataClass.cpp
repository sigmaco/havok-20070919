/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Bilateral/PointToPath/hkpPointToPathConstraintData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Bilateral/PointToPath/hkpPointToPathConstraintData.h>



// External pointer and enum types
extern const hkClass hkpBridgeAtomsClass;
extern const hkClass hkpParametricCurveClass;
extern const hkClass hkpSolverResultsClass;

//
// Enum hkpPointToPathConstraintData::OrientationConstraintType
//
static const hkInternalClassEnumItem hkpPointToPathConstraintDataOrientationConstraintTypeEnumItems[] =
{
	{0, "CONSTRAIN_ORIENTATION_INVALID"},
	{1, "CONSTRAIN_ORIENTATION_NONE"},
	{2, "CONSTRAIN_ORIENTATION_ALLOW_SPIN"},
	{3, "CONSTRAIN_ORIENTATION_TO_PATH"},
	{4, "CONSTRAIN_ORIENTATION_MAX_ID"},
};
static const hkInternalClassEnum hkpPointToPathConstraintDataEnums[] = {
	{"OrientationConstraintType", hkpPointToPathConstraintDataOrientationConstraintTypeEnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkpPointToPathConstraintDataOrientationConstraintTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpPointToPathConstraintDataEnums[0]);

//
// Class hkpPointToPathConstraintData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpPointToPathConstraintData);
const hkInternalClassMember hkpPointToPathConstraintData::Members[] =
{
	{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPointToPathConstraintData,m_atoms), HK_NULL },
	{ "path", &hkpParametricCurveClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpPointToPathConstraintData,m_path), HK_NULL },
	{ "maxFrictionForce", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPointToPathConstraintData,m_maxFrictionForce), HK_NULL },
	{ "angularConstrainedDOF", HK_NULL, hkpPointToPathConstraintDataOrientationConstraintTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpPointToPathConstraintData,m_angularConstrainedDOF), HK_NULL },
	{ "transform_OS_KS", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkpPointToPathConstraintData,m_transform_OS_KS), HK_NULL }
};
extern const hkClass hkpConstraintDataClass;

extern const hkClass hkpPointToPathConstraintDataClass;
const hkClass hkpPointToPathConstraintDataClass(
	"hkpPointToPathConstraintData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpPointToPathConstraintData),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpPointToPathConstraintDataEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpPointToPathConstraintData::Members),
	HK_COUNT_OF(hkpPointToPathConstraintData::Members),
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
