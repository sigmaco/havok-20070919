/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/hkpConstraintInstance.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/hkpConstraintInstance.h>



// External pointer and enum types
extern const hkClass hkConstraintInternalClass;
extern const hkClass hkpConstraintAtomClass;
extern const hkClass hkpConstraintDataClass;
extern const hkClass hkpConstraintInstanceClass;
extern const hkClass hkpConstraintOwnerClass;
extern const hkClass hkpConstraintRuntimeClass;
extern const hkClass hkpEntityClass;
extern const hkClass hkpModifierConstraintAtomClass;
extern const hkClassEnum* hkpConstraintInstanceConstraintPriorityEnum;

//
// Enum hkpConstraintInstance::ConstraintPriority
//
static const hkInternalClassEnumItem hkpConstraintInstanceConstraintPriorityEnumItems[] =
{
	{0, "PRIORITY_INVALID"},
	{1, "PRIORITY_PSI"},
	{2, "PRIORITY_TOI"},
	{3, "PRIORITY_TOI_HIGHER"},
	{4, "PRIORITY_TOI_FORCED"},
};

//
// Enum hkpConstraintInstance::InstanceType
//
static const hkInternalClassEnumItem hkpConstraintInstanceInstanceTypeEnumItems[] =
{
	{0, "TYPE_NORMAL"},
	{1, "TYPE_CHAIN"},
};

//
// Enum hkpConstraintInstance::AddReferences
//
static const hkInternalClassEnumItem hkpConstraintInstanceAddReferencesEnumItems[] =
{
	{0, "DO_NOT_ADD_REFERENCES"},
	{1, "DO_ADD_REFERENCES"},
};

//
// Enum hkpConstraintInstance::CloningMode
//
static const hkInternalClassEnumItem hkpConstraintInstanceCloningModeEnumItems[] =
{
	{0, "CLONE_INSTANCES_ONLY"},
	{1, "CLONE_DATAS_WITH_MOTORS"},
};
static const hkInternalClassEnum hkpConstraintInstanceEnums[] = {
	{"ConstraintPriority", hkpConstraintInstanceConstraintPriorityEnumItems, 5, HK_NULL, 0 },
	{"InstanceType", hkpConstraintInstanceInstanceTypeEnumItems, 2, HK_NULL, 0 },
	{"AddReferences", hkpConstraintInstanceAddReferencesEnumItems, 2, HK_NULL, 0 },
	{"CloningMode", hkpConstraintInstanceCloningModeEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* hkpConstraintInstanceConstraintPriorityEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintInstanceEnums[0]);
extern const hkClassEnum* hkpConstraintInstanceInstanceTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintInstanceEnums[1]);
extern const hkClassEnum* hkpConstraintInstanceAddReferencesEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintInstanceEnums[2]);
extern const hkClassEnum* hkpConstraintInstanceCloningModeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConstraintInstanceEnums[3]);

//
// Class hkpConstraintInstance
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpConstraintInstance);
const hkInternalClassMember hkpConstraintInstance::Members[] =
{
	{ "owner", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpConstraintInstance,m_owner), HK_NULL },
	{ "data", &hkpConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpConstraintInstance,m_data), HK_NULL },
	{ "constraintModifiers", &hkpModifierConstraintAtomClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpConstraintInstance,m_constraintModifiers), HK_NULL },
	{ "entities", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 2, 0, HK_OFFSET_OF(hkpConstraintInstance,m_entities), HK_NULL },
	{ "priority", HK_NULL, hkpConstraintInstanceConstraintPriorityEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpConstraintInstance,m_priority), HK_NULL },
	{ "wantRuntime", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConstraintInstance,m_wantRuntime), HK_NULL },
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConstraintInstance,m_name), HK_NULL },
	{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConstraintInstance,m_userData), HK_NULL },
	{ "internal", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpConstraintInstance,m_internal), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

const hkClass hkpConstraintInstanceClass(
	"hkpConstraintInstance",
	&hkReferencedObjectClass, // parent
	sizeof(hkpConstraintInstance),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpConstraintInstanceEnums),
	4, // enums
	reinterpret_cast<const hkClassMember*>(hkpConstraintInstance::Members),
	HK_COUNT_OF(hkpConstraintInstance::Members),
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
