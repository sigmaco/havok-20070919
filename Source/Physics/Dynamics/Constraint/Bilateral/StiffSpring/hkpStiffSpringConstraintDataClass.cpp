/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Bilateral/StiffSpring/hkpStiffSpringConstraintData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Bilateral/StiffSpring/hkpStiffSpringConstraintData.h>



// External pointer and enum types
extern const hkClass hkpSetLocalTranslationsConstraintAtomClass;
extern const hkClass hkpSolverResultsClass;
extern const hkClass hkpStiffSpringConstraintAtomClass;
extern const hkClass hkpStiffSpringConstraintDataAtomsClass;

//
// Class hkpStiffSpringConstraintData::Atoms
//
HK_REFLECTION_DEFINE_SCOPED_NONVIRTUAL(hkpStiffSpringConstraintData,Atoms);
static const hkInternalClassMember hkpStiffSpringConstraintData_AtomsClass_Members[] =
{
	{ "pivots", &hkpSetLocalTranslationsConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringConstraintData::Atoms,m_pivots), HK_NULL },
	{ "spring", &hkpStiffSpringConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpStiffSpringConstraintData::Atoms,m_spring), HK_NULL }
};
const hkClass hkpStiffSpringConstraintDataAtomsClass(
	"hkpStiffSpringConstraintDataAtoms",
	HK_NULL, // parent
	sizeof(hkpStiffSpringConstraintData::Atoms),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStiffSpringConstraintData_AtomsClass_Members),
	HK_COUNT_OF(hkpStiffSpringConstraintData_AtomsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpStiffSpringConstraintData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpStiffSpringConstraintData);
static const hkInternalClassMember hkpStiffSpringConstraintDataClass_Members[] =
{
	{ "atoms", &hkpStiffSpringConstraintDataAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpStiffSpringConstraintData,m_atoms), HK_NULL }
};
extern const hkClass hkpConstraintDataClass;

extern const hkClass hkpStiffSpringConstraintDataClass;
const hkClass hkpStiffSpringConstraintDataClass(
	"hkpStiffSpringConstraintData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpStiffSpringConstraintData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpStiffSpringConstraintDataClass_Members),
	HK_COUNT_OF(hkpStiffSpringConstraintDataClass_Members),
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
