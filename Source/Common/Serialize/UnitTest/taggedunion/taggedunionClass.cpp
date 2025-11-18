/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Serialize/UnitTest/taggedunion/taggedunion.h'
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/UnitTest/taggedunion/taggedunion.h>



//
// Enum ::hkSimpleUnion3
//
static const hkInternalClassEnumItem Common_Serialize_UnitTest_taggedunion_taggedunionhkSimpleUnion3EnumItems[] =
{
	{1, "SIMPLE_TYPE_ONE"},
	{2, "SIMPLE_TYPE_TWO"},
	{100, "SIMPLE_HIGH_START"},
	{100/*SIMPLE_HIGH_START*/, "SIMPLE_AFTER_GAP"},
	{101, "SIMPLE_TYPE_MAX"},
};
static const hkInternalClassEnum Common_Serialize_UnitTest_taggedunion_taggedunionEnums[] = {
	{"hkSimpleUnion3", Common_Serialize_UnitTest_taggedunion_taggedunionhkSimpleUnion3EnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkSimpleUnion3Enum = reinterpret_cast<const hkClassEnum*>(&Common_Serialize_UnitTest_taggedunion_taggedunionEnums[0]);
// hkSimpleUnion3

// External pointer and enum types
extern const hkClass hkAfterGapClass;
extern const hkClass hkTypeOneClass;
extern const hkClass hkTypeTwoClass;
extern const hkClassEnum* hkSimpleUnion3Enum;

//
// Class hkTypeOne
//
HK_REFLECTION_DEFINE_SIMPLE(hkTypeOne);
static const hkInternalClassMember hkTypeOneClass_Members[] =
{
	{ "type", HK_NULL, hkSimpleUnion3Enum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkTypeOne,m_type), HK_NULL },
	{ "h", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkTypeOne,m_h), HK_NULL }
};
const hkClass hkTypeOneClass(
	"hkTypeOne",
	HK_NULL, // parent
	sizeof(hkTypeOne),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkTypeOneClass_Members),
	HK_COUNT_OF(hkTypeOneClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkTypeTwo
//
HK_REFLECTION_DEFINE_SIMPLE(hkTypeTwo);
static const hkInternalClassMember hkTypeTwoClass_Members[] =
{
	{ "type", HK_NULL, hkSimpleUnion3Enum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkTypeTwo,m_type), HK_NULL },
	{ "f", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkTypeTwo,m_f), HK_NULL },
	{ "g", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkTypeTwo,m_g), HK_NULL }
};
const hkClass hkTypeTwoClass(
	"hkTypeTwo",
	HK_NULL, // parent
	sizeof(hkTypeTwo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkTypeTwoClass_Members),
	HK_COUNT_OF(hkTypeTwoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkAfterGap
//
HK_REFLECTION_DEFINE_SIMPLE(hkAfterGap);
static const hkInternalClassMember hkAfterGapClass_Members[] =
{
	{ "type", HK_NULL, hkSimpleUnion3Enum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkAfterGap,m_type), HK_NULL },
	{ "f", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkAfterGap,m_f), HK_NULL },
	{ "g", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkAfterGap,m_g), HK_NULL },
	{ "b", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 16, 0, HK_OFFSET_OF(hkAfterGap,m_b), HK_NULL }
};
const hkClass hkAfterGapClass(
	"hkAfterGap",
	HK_NULL, // parent
	sizeof(hkAfterGap),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkAfterGapClass_Members),
	HK_COUNT_OF(hkAfterGapClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Enum hkSimpleUnion3::hkSimpleUnion3
//
static const hkInternalClassEnumItem hkSimpleUnion3hkSimpleUnion3EnumItems[] =
{
	{1, "SIMPLE_TYPE_ONE"},
	{2, "SIMPLE_TYPE_TWO"},
	{100, "SIMPLE_HIGH_START"},
	{100/*SIMPLE_HIGH_START*/, "SIMPLE_AFTER_GAP"},
	{101, "SIMPLE_TYPE_MAX"},
};
static const hkInternalClassEnum hkSimpleUnion3Enums[] = {
	{"hkSimpleUnion3", hkSimpleUnion3hkSimpleUnion3EnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkSimpleUnion3hkSimpleUnion3Enum = reinterpret_cast<const hkClassEnum*>(&hkSimpleUnion3Enums[0]);

//
// Class hkSimpleUnion3
//
HK_REFLECTION_DEFINE_SIMPLE(hkSimpleUnion3);
static const hkInternalClassMember hkSimpleUnion3Class_Members[] =
{
	{ "SIMPLE_TYPE_ONE", &hkTypeOneClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
	{ "SIMPLE_TYPE_TWO", &hkTypeTwoClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL },
	{ "SIMPLE_AFTER_GAP", &hkAfterGapClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, 0, HK_NULL }
};
extern const hkClass hkSimpleUnion3Class;
const hkClass hkSimpleUnion3Class(
	"hkSimpleUnion3",
	HK_NULL, // parent
	sizeof(hkSimpleUnion3),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkSimpleUnion3Enums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkSimpleUnion3Class_Members),
	HK_COUNT_OF(hkSimpleUnion3Class_Members),
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
