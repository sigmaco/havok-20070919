/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Motor/hkpConstraintMotor.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Motor/hkpConstraintMotor.h>



//
// Enum hkpConstraintMotor::MotorType
//
static const hkInternalClassEnumItem hkpConstraintMotorMotorTypeEnumItems[] =
{
	{0, "TYPE_INVALID"},
	{1, "TYPE_POSITION"},
	{2, "TYPE_VELOCITY"},
	{3, "TYPE_SPRING_DAMPER"},
	{4, "TYPE_CALLBACK"},
	{5, "TYPE_MAX"},
};
static const hkInternalClassEnum hkpConstraintMotorEnums[] = {
	{"MotorType", hkpConstraintMotorMotorTypeEnumItems, 6, HK_NULL, 0 }
};
extern const hkClassEnum* hkpConstraintMotorMotorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintMotorEnums[0]);

//
// Class hkpConstraintMotor
//

static const hkInternalClassMember hkpConstraintMotorClass_Members[] =
{
	{ "type", HK_NULL, hkpConstraintMotorMotorTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpConstraintMotor,m_type), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpConstraintMotorClass;
const hkClass hkpConstraintMotorClass(
	"hkpConstraintMotor",
	&hkReferencedObjectClass, // parent
	sizeof(hkpConstraintMotor),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpConstraintMotorEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpConstraintMotorClass_Members),
	HK_COUNT_OF(hkpConstraintMotorClass_Members),
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
