/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Bilateral/Wheel/hkpWheelConstraintData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Bilateral/Wheel/hkpWheelConstraintData.h>



// External pointer and enum types
extern const hkClass hkp2dAngConstraintAtomClass;
extern const hkClass hkpLinConstraintAtomClass;
extern const hkClass hkpLinLimitConstraintAtomClass;
extern const hkClass hkpLinSoftConstraintAtomClass;
extern const hkClass hkpSetLocalRotationsConstraintAtomClass;
extern const hkClass hkpSetLocalTransformsConstraintAtomClass;
extern const hkClass hkpSolverResultsClass;
extern const hkClass hkpWheelConstraintDataAtomsClass;

//
// Enum hkpWheelConstraintData::Atoms::Axis
//
static const hkInternalClassEnumItem hkpWheelConstraintDataAtomsAxisEnumItems[] =
{
	{0, "AXIS_SUSPENSION"},
	{1, "AXIS_PERP_SUSPENSION"},
	{0, "AXIS_AXLE"},
	{1, "AXIS_STEERING"},
};
static const hkInternalClassEnum hkpWheelConstraintDataAtomsEnums[] = {
	{"Axis", hkpWheelConstraintDataAtomsAxisEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* hkpWheelConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpWheelConstraintDataAtomsEnums[0]);

//
// Class hkpWheelConstraintData::Atoms
//
HK_REFLECTION_DEFINE_SCOPED_NONVIRTUAL(hkpWheelConstraintData,Atoms);
static const hkInternalClassMember hkpWheelConstraintData_AtomsClass_Members[] =
{
	{ "suspensionBase", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData::Atoms,m_suspensionBase), HK_NULL },
	{ "lin0Limit", &hkpLinLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData::Atoms,m_lin0Limit), HK_NULL },
	{ "lin0Soft", &hkpLinSoftConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData::Atoms,m_lin0Soft), HK_NULL },
	{ "lin1", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData::Atoms,m_lin1), HK_NULL },
	{ "lin2", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData::Atoms,m_lin2), HK_NULL },
	{ "steeringBase", &hkpSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData::Atoms,m_steeringBase), HK_NULL },
	{ "2dAng", &hkp2dAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData::Atoms,m_2dAng), HK_NULL }
};
const hkClass hkpWheelConstraintDataAtomsClass(
	"hkpWheelConstraintDataAtoms",
	HK_NULL, // parent
	sizeof(hkpWheelConstraintData::Atoms),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpWheelConstraintDataAtomsEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpWheelConstraintData_AtomsClass_Members),
	HK_COUNT_OF(hkpWheelConstraintData_AtomsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpWheelConstraintData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpWheelConstraintData);
static const hkInternalClassMember hkpWheelConstraintDataClass_Members[] =
{
	{ "atoms", &hkpWheelConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpWheelConstraintData,m_atoms), HK_NULL },
	{ "initialAxleInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData,m_initialAxleInB), HK_NULL },
	{ "initialSteeringAxisInB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWheelConstraintData,m_initialSteeringAxisInB), HK_NULL }
};
extern const hkClass hkpConstraintDataClass;

extern const hkClass hkpWheelConstraintDataClass;
const hkClass hkpWheelConstraintDataClass(
	"hkpWheelConstraintData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpWheelConstraintData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpWheelConstraintDataClass_Members),
	HK_COUNT_OF(hkpWheelConstraintDataClass_Members),
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
