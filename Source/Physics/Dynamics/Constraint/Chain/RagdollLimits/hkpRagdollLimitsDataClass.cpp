/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Chain/RagdollLimits/hkpRagdollLimitsData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Chain/RagdollLimits/hkpRagdollLimitsData.h>



// External pointer and enum types
extern const hkClass hkpConeLimitConstraintAtomClass;
extern const hkClass hkpRagdollLimitsDataAtomsClass;
extern const hkClass hkpSetLocalRotationsConstraintAtomClass;
extern const hkClass hkpSolverResultsClass;
extern const hkClass hkpTwistLimitConstraintAtomClass;

//
// Enum hkpRagdollLimitsData::Atoms::Axis
//
static const hkInternalClassEnumItem hkpRagdollLimitsDataAtomsAxisEnumItems[] =
{
	{0, "AXIS_TWIST"},
	{1, "AXIS_PLANES"},
	{2, "AXIS_CROSS_PRODUCT"},
};
static const hkInternalClassEnum hkpRagdollLimitsDataAtomsEnums[] = {
	{"Axis", hkpRagdollLimitsDataAtomsAxisEnumItems, 3, HK_NULL, 0 }
};
extern const hkClassEnum* hkpRagdollLimitsDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpRagdollLimitsDataAtomsEnums[0]);

//
// Class hkpRagdollLimitsData::Atoms
//
HK_REFLECTION_DEFINE_SCOPED_NONVIRTUAL(hkpRagdollLimitsData,Atoms);
static const hkInternalClassMember hkpRagdollLimitsData_AtomsClass_Members[] =
{
	{ "rotations", &hkpSetLocalRotationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollLimitsData::Atoms,m_rotations), HK_NULL },
	{ "twistLimit", &hkpTwistLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollLimitsData::Atoms,m_twistLimit), HK_NULL },
	{ "coneLimit", &hkpConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollLimitsData::Atoms,m_coneLimit), HK_NULL },
	{ "planesLimit", &hkpConeLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRagdollLimitsData::Atoms,m_planesLimit), HK_NULL }
};
const hkClass hkpRagdollLimitsDataAtomsClass(
	"hkpRagdollLimitsDataAtoms",
	HK_NULL, // parent
	sizeof(hkpRagdollLimitsData::Atoms),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpRagdollLimitsDataAtomsEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpRagdollLimitsData_AtomsClass_Members),
	HK_COUNT_OF(hkpRagdollLimitsData_AtomsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpRagdollLimitsData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpRagdollLimitsData);
static const hkInternalClassMember hkpRagdollLimitsDataClass_Members[] =
{
	{ "atoms", &hkpRagdollLimitsDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpRagdollLimitsData,m_atoms), HK_NULL }
};
extern const hkClass hkpConstraintDataClass;

extern const hkClass hkpRagdollLimitsDataClass;
const hkClass hkpRagdollLimitsDataClass(
	"hkpRagdollLimitsData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpRagdollLimitsData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpRagdollLimitsDataClass_Members),
	HK_COUNT_OF(hkpRagdollLimitsDataClass_Members),
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
