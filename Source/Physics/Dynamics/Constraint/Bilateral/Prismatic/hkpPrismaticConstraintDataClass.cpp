/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Bilateral/Prismatic/hkpPrismaticConstraintData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Bilateral/Prismatic/hkpPrismaticConstraintData.h>



// External pointer and enum types
extern const hkClass hkpAngConstraintAtomClass;
extern const hkClass hkpLinConstraintAtomClass;
extern const hkClass hkpLinFrictionConstraintAtomClass;
extern const hkClass hkpLinLimitConstraintAtomClass;
extern const hkClass hkpLinMotorConstraintAtomClass;
extern const hkClass hkpPrismaticConstraintDataAtomsClass;
extern const hkClass hkpSetLocalTransformsConstraintAtomClass;
extern const hkClass hkpSolverResultsClass;

//
// Enum hkpPrismaticConstraintData::Atoms::Axis
//
static const hkInternalClassEnumItem hkpPrismaticConstraintDataAtomsAxisEnumItems[] =
{
	{0, "AXIS_SHAFT"},
	{1, "AXIS_PERP_TO_SHAFT"},
};
static const hkInternalClassEnum hkpPrismaticConstraintDataAtomsEnums[] = {
	{"Axis", hkpPrismaticConstraintDataAtomsAxisEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* hkpPrismaticConstraintDataAtomsAxisEnum = reinterpret_cast<const hkClassEnum*>(&hkpPrismaticConstraintDataAtomsEnums[0]);

//
// Class hkpPrismaticConstraintData::Atoms
//
HK_REFLECTION_DEFINE_SCOPED_NONVIRTUAL(hkpPrismaticConstraintData,Atoms);
static const hkInternalClassMember hkpPrismaticConstraintData_AtomsClass_Members[] =
{
	{ "transforms", &hkpSetLocalTransformsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPrismaticConstraintData::Atoms,m_transforms), HK_NULL },
	{ "motor", &hkpLinMotorConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPrismaticConstraintData::Atoms,m_motor), HK_NULL },
	{ "friction", &hkpLinFrictionConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPrismaticConstraintData::Atoms,m_friction), HK_NULL },
	{ "ang", &hkpAngConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPrismaticConstraintData::Atoms,m_ang), HK_NULL },
	{ "lin0", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPrismaticConstraintData::Atoms,m_lin0), HK_NULL },
	{ "lin1", &hkpLinConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPrismaticConstraintData::Atoms,m_lin1), HK_NULL },
	{ "linLimit", &hkpLinLimitConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPrismaticConstraintData::Atoms,m_linLimit), HK_NULL }
};
const hkClass hkpPrismaticConstraintDataAtomsClass(
	"hkpPrismaticConstraintDataAtoms",
	HK_NULL, // parent
	sizeof(hkpPrismaticConstraintData::Atoms),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpPrismaticConstraintDataAtomsEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpPrismaticConstraintData_AtomsClass_Members),
	HK_COUNT_OF(hkpPrismaticConstraintData_AtomsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPrismaticConstraintData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpPrismaticConstraintData);
static const hkInternalClassMember hkpPrismaticConstraintDataClass_Members[] =
{
	{ "atoms", &hkpPrismaticConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpPrismaticConstraintData,m_atoms), HK_NULL }
};
extern const hkClass hkpConstraintDataClass;

extern const hkClass hkpPrismaticConstraintDataClass;
const hkClass hkpPrismaticConstraintDataClass(
	"hkpPrismaticConstraintData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpPrismaticConstraintData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPrismaticConstraintDataClass_Members),
	HK_COUNT_OF(hkpPrismaticConstraintDataClass_Members),
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
