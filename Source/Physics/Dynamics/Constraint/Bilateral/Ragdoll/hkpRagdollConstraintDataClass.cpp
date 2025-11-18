/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Bilateral/Ragdoll/hkpRagdollConstraintData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Bilateral/Ragdoll/hkpRagdollConstraintData.h>



// External pointer and enum types
extern const hkClass hkpAngFrictionConstraintAtomClass;
extern const hkClass hkpBallSocketConstraintAtomClass;
extern const hkClass hkpConeLimitConstraintAtomClass;
extern const hkClass hkpRagdollConstraintDataAtomsClass;
extern const hkClass hkpRagdollMotorConstraintAtomClass;
extern const hkClass hkpSetLocalTransformsConstraintAtomClass;
extern const hkClass hkpSolverResultsClass;
extern const hkClass hkpTwistLimitConstraintAtomClass;

//
// Enum hkpRagdollConstraintData::MotorIndex
//
static const hkInternalClassEnumItem hkpRagdollConstraintDataMotorIndexEnumItems[] =
{
	{0, "MOTOR_TWIST"},
	{1, "MOTOR_PLANE"},
	{2, "MOTOR_CONE"},
};
static const hkInternalClassEnum hkpRagdollConstraintDataEnums[] = {
	{"MotorIndex", hkpRagdollConstraintDataMotorIndexEnumItems, 3, HK_NULL, 0 }
};
extern const hkClassEnum* hkpRagdollConstraintDataMotorIndexEnum = reinterpret_cast<const hkClassEnum*>(&hkpRagdollConstraintDataEnums[0]);

//
// Enum hkpRagdollConstraintData::Atoms::Axis
//
static const hkInternalClassEnumItem hkpRagdollConstraintDataAtomsAxisEnumItems[] =
{
	{0, "AXIS_TWIST"},
	{1, "AXIS_PLANES"},
	{2, "AXIS_CROSS_PRODUCT"},
};
static const hkInternalClassEnum hkpRagdollConstraintDataAtomsEnums[] = {
	{"Axis", hkpRagdollConstraintDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
};
extern const hkClassEnum* hkpRagdollConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpRagdollConstraintDataAtomsEnums[0]);

//
// Class hkpRagdollConstraintData::Atoms
//
HK_REFLECTION_DEFINE_SCOPED_NONVIRTUAL(hkpRagdollConstraintData,Atoms);
static const hkInternalClassMember hkpRagdollConstraintData_AtomsClass_Members[] =
{
	{ "transforms", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollConstraintData::Atoms,m_transforms), HK_NULL },
	{ "ragdollMotors", &hkpRagdollMotorConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollConstraintData::Atoms,m_ragdollMotors), HK_NULL },
	{ "angFriction", &hkpAngFrictionConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollConstraintData::Atoms,m_angFriction), HK_NULL },
	{ "twistLimit", &hkpTwistLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollConstraintData::Atoms,m_twistLimit), HK_NULL },
	{ "coneLimit", &hkpConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollConstraintData::Atoms,m_coneLimit), HK_NULL },
	{ "planesLimit", &hkpConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollConstraintData::Atoms,m_planesLimit), HK_NULL },
	{ "ballSocket", &hkpBallSocketConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollConstraintData::Atoms,m_ballSocket), HK_NULL }
};
const hkClass hkpRagdollConstraintDataAtomsClass(
	"hkpRagdollConstraintDataAtoms",
	HK_NULL, // parent
	sizeof(hkpRagdollConstraintData::Atoms),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpRagdollConstraintDataAtomsEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpRagdollConstraintData_AtomsClass_Members),
	HK_COUNT_OF(hkpRagdollConstraintData_AtomsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpRagdollConstraintData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpRagdollConstraintData);
static const hkInternalClassMember hkpRagdollConstraintDataClass_Members[] =
{
	{ "atoms", &hkpRagdollConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpRagdollConstraintData,m_atoms), HK_NULL }
};
extern const hkClass hkpConstraintDataClass;

extern const hkClass hkpRagdollConstraintDataClass;
const hkClass hkpRagdollConstraintDataClass(
	"hkpRagdollConstraintData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpRagdollConstraintData),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpRagdollConstraintDataEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpRagdollConstraintDataClass_Members),
	HK_COUNT_OF(hkpRagdollConstraintDataClass_Members),
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
