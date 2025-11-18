/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Chain/HingeLimits/hkpHingeLimitsData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Chain/HingeLimits/hkpHingeLimitsData.h>



// External pointer and enum types
extern const hkClass hkp2dAngConstraintAtomClass;
extern const hkClass hkpAngLimitConstraintAtomClass;
extern const hkClass hkpHingeLimitsDataAtomsClass;
extern const hkClass hkpSetLocalRotationsConstraintAtomClass;
extern const hkClass hkpSolverResultsClass;

//
// Enum hkpHingeLimitsData::Atoms::Axis
//
static const hkInternalClassEnumItem hkpHingeLimitsDataAtomsAxisEnumItems[] =
{
	{0, "AXIS_AXLE"},
	{1, "AXIS_PERP_TO_AXLE_1"},
	{2, "AXIS_PERP_TO_AXLE_2"},
};
static const hkInternalClassEnum hkpHingeLimitsDataAtomsEnums[] = {
	{"Axis", hkpHingeLimitsDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
};
extern const hkClassEnum* hkpHingeLimitsDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpHingeLimitsDataAtomsEnums[0]);

//
// Class hkpHingeLimitsData::Atoms
//
HK_REFLECTION_DEFINE_SCOPED_NONVIRTUAL(hkpHingeLimitsData,Atoms);
static const hkInternalClassMember hkpHingeLimitsData_AtomsClass_Members[] =
{
	{ "rotations", &hkpSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpHingeLimitsData::Atoms,m_rotations), HK_NULL },
	{ "angLimit", &hkpAngLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpHingeLimitsData::Atoms,m_angLimit), HK_NULL },
	{ "2dAng", &hkp2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpHingeLimitsData::Atoms,m_2dAng), HK_NULL }
};
const hkClass hkpHingeLimitsDataAtomsClass(
	"hkpHingeLimitsDataAtoms",
	HK_NULL, // parent
	sizeof(hkpHingeLimitsData::Atoms),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpHingeLimitsDataAtomsEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpHingeLimitsData_AtomsClass_Members),
	HK_COUNT_OF(hkpHingeLimitsData_AtomsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpHingeLimitsData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpHingeLimitsData);
static const hkInternalClassMember hkpHingeLimitsDataClass_Members[] =
{
	{ "atoms", &hkpHingeLimitsDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpHingeLimitsData,m_atoms), HK_NULL }
};
extern const hkClass hkpConstraintDataClass;

extern const hkClass hkpHingeLimitsDataClass;
const hkClass hkpHingeLimitsDataClass(
	"hkpHingeLimitsData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpHingeLimitsData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpHingeLimitsDataClass_Members),
	HK_COUNT_OF(hkpHingeLimitsDataClass_Members),
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
