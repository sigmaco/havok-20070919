/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/hkpConstraintData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/hkpConstraintData.h>



// External pointer and enum types
extern const hkClass hkpConstraintAtomClass;

//
// Enum hkpConstraintData::ConstraintType
//
static const hkInternalClassEnumItem hkpConstraintDataConstraintTypeEnumItems[] =
{
	{0, "CONSTRAINT_TYPE_BALLANDSOCKET"},
	{1, "CONSTRAINT_TYPE_HINGE"},
	{2, "CONSTRAINT_TYPE_LIMITEDHINGE"},
	{3, "CONSTRAINT_TYPE_POINTTOPATH"},
	{6, "CONSTRAINT_TYPE_PRISMATIC"},
	{7, "CONSTRAINT_TYPE_RAGDOLL"},
	{8, "CONSTRAINT_TYPE_STIFFSPRING"},
	{9, "CONSTRAINT_TYPE_WHEEL"},
	{10, "CONSTRAINT_TYPE_GENERIC"},
	{11, "CONSTRAINT_TYPE_CONTACT"},
	{12, "CONSTRAINT_TYPE_BREAKABLE"},
	{13, "CONSTRAINT_TYPE_MALLEABLE"},
	{14, "CONSTRAINT_TYPE_POINTTOPLANE"},
	{15, "CONSTRAINT_TYPE_PULLEY"},
	{16, "CONSTRAINT_TYPE_ROTATIONAL"},
	{18, "CONSTRAINT_TYPE_HINGE_LIMITS"},
	{19, "CONSTRAINT_TYPE_RAGDOLL_LIMITS"},
	{100, "BEGIN_CONSTRAINT_CHAIN_TYPES"},
	{100, "CONSTRAINT_TYPE_STIFF_SPRING_CHAIN"},
	{101, "CONSTRAINT_TYPE_BALL_SOCKET_CHAIN"},
	{102, "CONSTRAINT_TYPE_POWERED_CHAIN"},
};
static const hkInternalClassEnum hkpConstraintDataEnums[] = {
	{"ConstraintType", hkpConstraintDataConstraintTypeEnumItems, 21, HK_NULL, 0 }
};
extern const hkClassEnum* hkpConstraintDataConstraintTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintDataEnums[0]);

//
// Class hkpConstraintData
//

static const hkInternalClassMember hkpConstraintDataClass_Members[] =
{
	{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConstraintData,m_userData), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpConstraintDataClass;
const hkClass hkpConstraintDataClass(
	"hkpConstraintData",
	&hkReferencedObjectClass, // parent
	sizeof(hkpConstraintData),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpConstraintDataEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpConstraintDataClass_Members),
	HK_COUNT_OF(hkpConstraintDataClass_Members),
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
