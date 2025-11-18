/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Motor/Callback/hkpCallbackConstraintMotor.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Motor/Callback/hkpCallbackConstraintMotor.h>



//
// Enum hkpCallbackConstraintMotor::CallbackType
//
static const hkInternalClassEnumItem hkpCallbackConstraintMotorCallbackTypeEnumItems[] =
{
	{0, "CALLBACK_MOTOR_TYPE_HAVOK_DEMO_SPRING_DAMPER"},
	{1, "CALLBACK_MOTOR_TYPE_USER_0"},
	{2, "CALLBACK_MOTOR_TYPE_USER_1"},
	{3, "CALLBACK_MOTOR_TYPE_USER_2"},
	{4, "CALLBACK_MOTOR_TYPE_USER_3"},
};
static const hkInternalClassEnum hkpCallbackConstraintMotorEnums[] = {
	{"CallbackType", hkpCallbackConstraintMotorCallbackTypeEnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkpCallbackConstraintMotorCallbackTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpCallbackConstraintMotorEnums[0]);

//
// Class hkpCallbackConstraintMotor
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpCallbackConstraintMotor);
static const hkInternalClassMember hkpCallbackConstraintMotorClass_Members[] =
{
	{ "callbackFunc", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpCallbackConstraintMotor,m_callbackFunc), HK_NULL },
	{ "callbackType", HK_NULL, hkpCallbackConstraintMotorCallbackTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkpCallbackConstraintMotor,m_callbackType), HK_NULL },
	{ "userData0", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCallbackConstraintMotor,m_userData0), HK_NULL },
	{ "userData1", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCallbackConstraintMotor,m_userData1), HK_NULL },
	{ "userData2", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCallbackConstraintMotor,m_userData2), HK_NULL }
};
extern const hkClass hkpLimitedForceConstraintMotorClass;

extern const hkClass hkpCallbackConstraintMotorClass;
const hkClass hkpCallbackConstraintMotorClass(
	"hkpCallbackConstraintMotor",
	&hkpLimitedForceConstraintMotorClass, // parent
	sizeof(hkpCallbackConstraintMotor),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpCallbackConstraintMotorEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpCallbackConstraintMotorClass_Members),
	HK_COUNT_OF(hkpCallbackConstraintMotorClass_Members),
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
