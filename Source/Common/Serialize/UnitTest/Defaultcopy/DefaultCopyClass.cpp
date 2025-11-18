/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Serialize/UnitTest/Defaultcopy/DefaultCopy.h'
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/UnitTest/Defaultcopy/DefaultCopy.h>



// External pointer and enum types
extern const hkClass Modified_WithNestedNestedClass;
extern const hkClass Original_WithNestedNestedClass;

//
// Class Original_DefaultCopy
//
HK_REFLECTION_DEFINE_SIMPLE(Original_DefaultCopy);
extern const hkClass Original_DefaultCopyClass;
const hkClass Original_DefaultCopyClass(
	"Original_DefaultCopy",
	HK_NULL, // parent
	sizeof(Original_DefaultCopy),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	HK_NULL,
	0,
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Enum Modified_DefaultCopy::Value
//
static const hkInternalClassEnumItem Modified_DefaultCopyValueEnumItems[] =
{
	{111, "VALUE_FIRST"},
	{156, "VALUE_SECOND"},
	{123, "VALUE_THIRD"},
	{99, "VALUE_ONLY_IN_MODIFIED"},
};
static const hkInternalClassEnum Modified_DefaultCopyEnums[] = {
	{"Value", Modified_DefaultCopyValueEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* Modified_DefaultCopyValueEnum = reinterpret_cast<const hkClassEnum*>(&Modified_DefaultCopyEnums[0]);

//
// Class Modified_DefaultCopy
//
HK_REFLECTION_DEFINE_SIMPLE(Modified_DefaultCopy);
static const hkInternalClassMember Modified_DefaultCopyClass_Members[] =
{
	{ "int0", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_DefaultCopy,m_int0), HK_NULL },
	{ "bool0", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_DefaultCopy,m_bool0), HK_NULL },
	{ "bool1", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_DefaultCopy,m_bool1), HK_NULL },
	{ "bool2", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_DefaultCopy,m_bool2), HK_NULL },
	{ "value8", HK_NULL, Modified_DefaultCopyValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(Modified_DefaultCopy,m_value8), HK_NULL },
	{ "vec0", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_DefaultCopy,m_vec0), HK_NULL },
	{ "vec1", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_DefaultCopy,m_vec1), HK_NULL },
	{ "vec2", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_DefaultCopy,m_vec2), HK_NULL }
};
namespace
{
	struct Modified_DefaultCopy_DefaultStruct
	{
		int s_defaultOffsets[8];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		int m_int0;
		_hkBool m_bool0;
		_hkBool m_bool2;
		hkInt8 /* hkEnum<Value, hkInt8> */ m_value8;
		_hkVector4 m_vec1;
		_hkVector4 m_vec2;
	};
	const Modified_DefaultCopy_DefaultStruct Modified_DefaultCopy_Default =
	{
		{HK_OFFSET_OF(Modified_DefaultCopy_DefaultStruct,m_int0),HK_OFFSET_OF(Modified_DefaultCopy_DefaultStruct,m_bool0),-1,HK_OFFSET_OF(Modified_DefaultCopy_DefaultStruct,m_bool2),HK_OFFSET_OF(Modified_DefaultCopy_DefaultStruct,m_value8),-1,HK_OFFSET_OF(Modified_DefaultCopy_DefaultStruct,m_vec1),HK_OFFSET_OF(Modified_DefaultCopy_DefaultStruct,m_vec2)},
100,true,true, Modified_DefaultCopy::VALUE_THIRD ,	{44,55,66,77},	{88,99,11}
	};
}
extern const hkClass Modified_DefaultCopyClass;
const hkClass Modified_DefaultCopyClass(
	"Modified_DefaultCopy",
	HK_NULL, // parent
	sizeof(Modified_DefaultCopy),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(Modified_DefaultCopyEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(Modified_DefaultCopyClass_Members),
	HK_COUNT_OF(Modified_DefaultCopyClass_Members),
	&Modified_DefaultCopy_Default,
	HK_NULL, // attributes
	0
	);

//
// Class Original_WithNested::Nested
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(Original_WithNested,Nested);
static const hkInternalClassMember Original_WithNested_NestedClass_Members[] =
{
	{ "enabled", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Original_WithNested::Nested,m_enabled), HK_NULL },
	{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Original_WithNested::Nested,m_radius), HK_NULL }
};
const hkClass Original_WithNestedNestedClass(
	"Original_WithNestedNested",
	HK_NULL, // parent
	sizeof(Original_WithNested::Nested),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(Original_WithNested_NestedClass_Members),
	HK_COUNT_OF(Original_WithNested_NestedClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class Original_WithNested
//
HK_REFLECTION_DEFINE_SIMPLE(Original_WithNested);
static const hkInternalClassMember Original_WithNestedClass_Members[] =
{
	{ "foo", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Original_WithNested,m_foo), HK_NULL },
	{ "nested", &Original_WithNestedNestedClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Original_WithNested,m_nested), HK_NULL },
	{ "bar", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Original_WithNested,m_bar), HK_NULL }
};
extern const hkClass Original_WithNestedClass;
const hkClass Original_WithNestedClass(
	"Original_WithNested",
	HK_NULL, // parent
	sizeof(Original_WithNested),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(Original_WithNestedClass_Members),
	HK_COUNT_OF(Original_WithNestedClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class Modified_WithNested::Nested
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(Modified_WithNested,Nested);
static const hkInternalClassMember Modified_WithNested_NestedClass_Members[] =
{
	{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(Modified_WithNested::Nested,m_pad), HK_NULL },
	{ "enabled2", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_WithNested::Nested,m_enabled2), HK_NULL },
	{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_WithNested::Nested,m_radius), HK_NULL }
};
namespace
{
	struct Modified_WithNestedNested_DefaultStruct
	{
		int s_defaultOffsets[3];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		_hkBool m_enabled2;
	};
	const Modified_WithNestedNested_DefaultStruct Modified_WithNestedNested_Default =
	{
		{-1,HK_OFFSET_OF(Modified_WithNestedNested_DefaultStruct,m_enabled2),-1},
		true
	};
}
const hkClass Modified_WithNestedNestedClass(
	"Modified_WithNestedNested",
	HK_NULL, // parent
	sizeof(Modified_WithNested::Nested),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(Modified_WithNested_NestedClass_Members),
	HK_COUNT_OF(Modified_WithNested_NestedClass_Members),
	&Modified_WithNestedNested_Default,
	HK_NULL, // attributes
	0
	);

//
// Class Modified_WithNested
//
HK_REFLECTION_DEFINE_SIMPLE(Modified_WithNested);
static const hkInternalClassMember Modified_WithNestedClass_Members[] =
{
	{ "foo", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_WithNested,m_foo), HK_NULL },
	{ "foo2", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_WithNested,m_foo2), HK_NULL },
	{ "nested", &Modified_WithNestedNestedClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_WithNested,m_nested), HK_NULL },
	{ "bar", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_WithNested,m_bar), HK_NULL },
	{ "bar2", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(Modified_WithNested,m_bar2), HK_NULL }
};
extern const hkClass Modified_WithNestedClass;
const hkClass Modified_WithNestedClass(
	"Modified_WithNested",
	HK_NULL, // parent
	sizeof(Modified_WithNested),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(Modified_WithNestedClass_Members),
	HK_COUNT_OF(Modified_WithNestedClass_Members),
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
