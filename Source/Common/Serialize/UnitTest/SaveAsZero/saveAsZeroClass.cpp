/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Serialize/UnitTest/SaveAsZero/saveAsZero.h'
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/UnitTest/SaveAsZero/saveAsZero.h>



// External pointer and enum types
extern const hkClass TestArrayNullsClass;

//
// Enum TestZero::Value
//
static const hkInternalClassEnumItem TestZeroValueEnumItems[] =
{
	{0, "VALUE_0"},
	{1, "VALUE_1"},
	{2, "VALUE_2"},
	{3, "VALUE_3"},
	{8, "VALUE_8"},
	{16, "VALUE_16"},
	{32, "VALUE_32"},
};
static const hkInternalClassEnum TestZeroEnums[] = {
	{"Value", TestZeroValueEnumItems, 7, HK_NULL, 0 }
};
extern const hkClassEnum* TestZeroValueEnum = reinterpret_cast<const hkClassEnum*>(&TestZeroEnums[0]);

//
// Class TestZero
//
HK_REFLECTION_DEFINE_SIMPLE(TestZero);
static const hkInternalClassMember TestZeroClass_Members[] =
{
	{ "value8", HK_NULL, TestZeroValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(TestZero,m_value8), HK_NULL },
	{ "value16", HK_NULL, TestZeroValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT16, 0, 0, HK_OFFSET_OF(TestZero,m_value16), HK_NULL },
	{ "value32", HK_NULL, TestZeroValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(TestZero,m_value32), HK_NULL },
	{ "zero8", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(TestZero,m_zero8), HK_NULL },
	{ "zero16", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT16, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(TestZero,m_zero16), HK_NULL },
	{ "zero32", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(TestZero,m_zero32), HK_NULL }
};
extern const hkClass TestZeroClass;
const hkClass TestZeroClass(
	"TestZero",
	HK_NULL, // parent
	sizeof(TestZero),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(TestZeroEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(TestZeroClass_Members),
	HK_COUNT_OF(TestZeroClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class TestArrayNulls
//
HK_REFLECTION_DEFINE_SIMPLE(TestArrayNulls);
static const hkInternalClassMember TestArrayNullsClass_Members[] =
{
	{ "array", &TestArrayNullsClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(TestArrayNulls,m_array), HK_NULL }
};
const hkClass TestArrayNullsClass(
	"TestArrayNulls",
	HK_NULL, // parent
	sizeof(TestArrayNulls),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(TestArrayNullsClass_Members),
	HK_COUNT_OF(TestArrayNullsClass_Members),
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
