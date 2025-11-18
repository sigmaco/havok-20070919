/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Pulley/hkpPulleyConstraintData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Pulley/hkpPulleyConstraintData.h>



// External pointer and enum types
extern const hkClass hkpPulleyConstraintAtomClass;
extern const hkClass hkpPulleyConstraintDataAtomsClass;
extern const hkClass hkpSetLocalTranslationsConstraintAtomClass;
extern const hkClass hkpSolverResultsClass;

//
// Class hkpPulleyConstraintData::Atoms
//
HK_REFLECTION_DEFINE_SCOPED_NONVIRTUAL(hkpPulleyConstraintData,Atoms);
static const hkInternalClassMember hkpPulleyConstraintData_AtomsClass_Members[] =
{
	{ "translations", &hkpSetLocalTranslationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPulleyConstraintData::Atoms,m_translations), HK_NULL },
	{ "pulley", &hkpPulleyConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPulleyConstraintData::Atoms,m_pulley), HK_NULL }
};
const hkClass hkpPulleyConstraintDataAtomsClass(
	"hkpPulleyConstraintDataAtoms",
	HK_NULL, // parent
	sizeof(hkpPulleyConstraintData::Atoms),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPulleyConstraintData_AtomsClass_Members),
	HK_COUNT_OF(hkpPulleyConstraintData_AtomsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPulleyConstraintData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpPulleyConstraintData);
static const hkInternalClassMember hkpPulleyConstraintDataClass_Members[] =
{
	{ "atoms", &hkpPulleyConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpPulleyConstraintData,m_atoms), HK_NULL }
};
extern const hkClass hkpConstraintDataClass;

extern const hkClass hkpPulleyConstraintDataClass;
const hkClass hkpPulleyConstraintDataClass(
	"hkpPulleyConstraintData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpPulleyConstraintData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPulleyConstraintDataClass_Members),
	HK_COUNT_OF(hkpPulleyConstraintDataClass_Members),
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
