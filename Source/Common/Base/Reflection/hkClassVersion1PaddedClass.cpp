/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>

// dummy declaration to stop flagging as stale
HK_REFLECTION_CLASSFILE_HEADER("../hkBase.h");

class hkClassVersion1Padded;
class hkClassMemberVersion1Padded;
class hkClassEnumVersion1Padded;
// External pointer and enum types
extern const hkClass hkClassVersion1PaddedClass;
extern const hkClass hkClassVersion2PaddedClass;
extern const hkClass hkClassMemberVersion1PaddedClass;
extern const hkClass hkClassEnumVersion1PaddedClass;

class hkClassVersion1Padded
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_HKCLASS, hkClassVersion1Padded );
		HK_DECLARE_REFLECTION();

	protected:

		const char* m_name;
		const hkClassVersion1Padded* m_parent;
		int m_objectSize;
		int m_numImplementedInterfaces;
		const class hkClassEnumVersion1Padded* m_declaredEnums;
		int m_numDeclaredEnums;
		const class hkClassMemberVersion1Padded* m_declaredMembers;
		int m_numDeclaredMembers;
		hkBool m_hasVtable;
		char m_padToSizeOfClass[sizeof(void*) - sizeof(hkBool)];
		void* m_customAttributes;//same size as hkClass
		hkUint32 m_flags;
		int m_describedVersion;
};

HK_COMPILE_TIME_ASSERT( sizeof(hkClassVersion1Padded) == sizeof(hkClass) );

class hkClassVersion2Padded
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_HKCLASS, hkClassVersion2Padded );
		HK_DECLARE_REFLECTION();

	protected:

		const char* m_name;
		const hkClassVersion2Padded* m_parent;
		int m_objectSize;
		int m_numImplementedInterfaces;
		const class hkClassEnumVersion1Padded* m_declaredEnums;
		int m_numDeclaredEnums;
		const class hkClassMemberVersion1Padded* m_declaredMembers;
		int m_numDeclaredMembers;
		void* m_defaults;
		void* m_customAttributes;//same size as hkClass
		hkUint32 m_flags;
		int m_describedVersion;
};

HK_COMPILE_TIME_ASSERT( sizeof(hkClassVersion2Padded) == sizeof(hkClass) );

class hkClassMemberVersion1Padded
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_HKCLASS, hkClassMemberVersion1Padded);
		HK_DECLARE_REFLECTION();

		enum Type
		{
			TYPE_VOID = 0,
			TYPE_BOOL,
			TYPE_CHAR,
			TYPE_INT8,
			TYPE_UINT8,
			TYPE_INT16,
			TYPE_UINT16,
			TYPE_INT32,
			TYPE_UINT32,
			TYPE_INT64,
			TYPE_UINT64,
			TYPE_REAL,
			TYPE_VECTOR4,
			TYPE_QUATERNION,
			TYPE_MATRIX3,
			TYPE_ROTATION,
			TYPE_QSTRANSFORM,
			TYPE_MATRIX4,
			TYPE_TRANSFORM,
			TYPE_ZERO,
			TYPE_POINTER,
			TYPE_FUNCTIONPOINTER,
			TYPE_ARRAY,
			TYPE_INPLACEARRAY,
			TYPE_ENUM,
			TYPE_STRUCT,
			TYPE_SIMPLEARRAY,
			TYPE_HOMOGENEOUSARRAY,
			TYPE_VARIANT,
			TYPE_CSTRING,
			TYPE_ULONG,
			TYPE_FLAGS,
			TYPE_MAX
		};

		enum Flags
		{
			POINTER_OPTIONAL = 1,
			POINTER_VOIDSTAR = 2,
			ENUM_8 = 8,
			ENUM_16 = 16,
			ENUM_32 = 32,
			ARRAY_RAWDATA = 64
		};

		enum Range
		{
			INVALID = 0,
			DEFAULT = 1,
			ABS_MIN = 2,
			ABS_MAX = 4,
			SOFT_MIN = 8,
			SOFT_MAX = 16,
			RANGE_MAX = 32
		};

		const char* m_name;
		const hkClassVersion1Padded* m_class;
		const hkClassEnumVersion1Padded* m_enum;
		hkEnum<Type,hkUint8> m_type;
		hkEnum<Type,hkUint8> m_subtype;
		hkInt16 m_cArraySize;
		hkUint16 m_flags;
		hkUint16 m_offset;
		void* m_customAttributes;
};

class hkClassEnumVersion1Padded
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_HKCLASS, hkClassEnumVersion1Padded);
		HK_DECLARE_REFLECTION();

			/// A single enumerated name and value pair.
		class Item
		{
			public:
				
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Item);
				HK_DECLARE_REFLECTION();
				int m_value;
				const char* m_name;
		};

		const char* m_name;
		const class Item* m_items;
		int m_numItems;
		void* m_attributes;
		hkUint32 m_flags;
};

//
// Class hkClass
//
const hkInternalClassMember hkClassVersion1Padded::Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_name) },
	{ "parent", &hkClassVersion1PaddedClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_parent) },
	{ "objectSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_objectSize) },
	{ "numImplementedInterfaces", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_numImplementedInterfaces) },
	{ "declaredEnums", &hkClassEnumVersion1PaddedClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_declaredEnums) },
	{ "declaredMembers", &hkClassMemberVersion1PaddedClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_declaredMembers) },
	{ "hasVtable", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_hasVtable) },
	{ "customAttributes", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_customAttributes) },
	{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_flags) },
	{ "describedVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1Padded,m_describedVersion) }
};
const hkClass hkClassVersion1PaddedClass(
	"hkClass",
	HK_NULL, // parent
	sizeof(hkClassVersion1PaddedClass),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkClassVersion1Padded::Members),
	HK_COUNT_OF(hkClassVersion1Padded::Members), // members
	HK_NULL // defaults
	);
const hkInternalClassMember hkClassVersion2Padded::Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_name) },
	{ "parent", &hkClassVersion2PaddedClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_parent) },
	{ "objectSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_objectSize) },
	{ "numImplementedInterfaces", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_numImplementedInterfaces) },
	{ "declaredEnums", &hkClassEnumVersion1PaddedClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_declaredEnums) },
	{ "declaredMembers", &hkClassMemberVersion1PaddedClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_declaredMembers) },
	{ "defaults", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_defaults) },
	{ "customAttributes", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_customAttributes) },
	{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_flags) },
	{ "describedVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2Padded,m_describedVersion) }
};
const hkClass hkClassVersion2PaddedClass(
	"hkClass",
	HK_NULL, // parent
	sizeof(hkClassVersion2PaddedClass),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkClassVersion2Padded::Members),
	HK_COUNT_OF(hkClassVersion2Padded::Members), // members
	HK_NULL // defaults
	);

static const hkInternalClassEnumItem hkClassMemberVersion1PaddedTypeEnumItems[] =
{
	{0, "TYPE_VOID"},
	{1, "TYPE_BOOL"},
	{2, "TYPE_CHAR"},
	{3, "TYPE_INT8"},
	{4, "TYPE_UINT8"},
	{5, "TYPE_INT16"},
	{6, "TYPE_UINT16"},
	{7, "TYPE_INT32"},
	{8, "TYPE_UINT32"},
	{9, "TYPE_INT64"},
	{10, "TYPE_UINT64"},
	{11, "TYPE_REAL"},
	{12, "TYPE_VECTOR4"},
	{13, "TYPE_QUATERNION"},
	{14, "TYPE_MATRIX3"},
	{15, "TYPE_ROTATION"},
	{16, "TYPE_QSTRANSFORM"},
	{17, "TYPE_MATRIX4"},
	{18, "TYPE_TRANSFORM"},
	{19, "TYPE_ZERO"},
	{20, "TYPE_POINTER"},
	{21, "TYPE_FUNCTIONPOINTER"},
	{22, "TYPE_ARRAY"},
	{23, "TYPE_INPLACEARRAY"},
	{24, "TYPE_ENUM"},
	{25, "TYPE_STRUCT"},
	{26, "TYPE_SIMPLEARRAY"},
	{27, "TYPE_HOMOGENEOUSARRAY"},
	{28, "TYPE_VARIANT"},
	{29, "TYPE_CSTRING"},
	{30, "TYPE_ULONG"},
	{31, "TYPE_FLAGS"},
	{32, "TYPE_MAX"},
};
static const hkInternalClassEnumItem hkClassMemberVersion1PaddedFlagsEnumItems[] =
{
	{1, "POINTER_OPTIONAL"},
	{2, "POINTER_VOIDSTAR"},
	{8, "ENUM_8"},
	{16, "ENUM_16"},
	{32, "ENUM_32"},
	{64, "ARRAY_RAWDATA"},
};
static const hkInternalClassEnumItem hkClassMemberVersion1PaddedRangeEnumItems[] =
{
	{0, "INVALID"},
	{1, "DEFAULT"},
	{2, "ABS_MIN"},
	{4, "ABS_MAX"},
	{8, "SOFT_MIN"},
	{16, "SOFT_MAX"},
	{32, "RANGE_MAX"},
};
static const hkInternalClassEnum hkClassMemberVersion1PaddedEnums[] = {
	{"Type", hkClassMemberVersion1PaddedTypeEnumItems, HK_COUNT_OF(hkClassMemberVersion1PaddedTypeEnumItems) },
	{"Flags", hkClassMemberVersion1PaddedFlagsEnumItems, HK_COUNT_OF(hkClassMemberVersion1PaddedFlagsEnumItems) },
	{"Range", hkClassMemberVersion1PaddedRangeEnumItems, HK_COUNT_OF(hkClassMemberVersion1PaddedRangeEnumItems) }
};
static const hkClassEnum* hkClassMemberVersion1PaddedTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberVersion1PaddedEnums[0]);
static const hkClassEnum* hkClassMemberVersion1PaddedFlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberVersion1PaddedEnums[1]);
static const hkClassEnum* hkClassMemberVersion1PaddedRangeEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberVersion1PaddedEnums[2]);

static hkInternalClassMember hkClassMemberVersion1PaddedClass_Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_name) },
	{ "class", &hkClassVersion1PaddedClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_class) },
	{ "enum", &hkClassEnumVersion1PaddedClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_enum) },
	{ "type", HK_NULL, hkClassMemberVersion1PaddedTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_type) },
	{ "subtype", HK_NULL, hkClassMemberVersion1PaddedTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_subtype) },
	{ "cArraySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_cArraySize) },
	{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_flags) },
	{ "offset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_offset) },
	{ "customAttributes", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1Padded,m_customAttributes) }
};

const hkClass hkClassMemberVersion1PaddedClass(
	"hkClassMember",
	HK_NULL, // parent
	sizeof(hkClassMemberVersion1Padded),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkClassMemberVersion1PaddedEnums),
	3, // enums
	reinterpret_cast<const hkClassMember*>(hkClassMemberVersion1PaddedClass_Members),
	HK_COUNT_OF(hkClassMemberVersion1PaddedClass_Members), // members
	HK_NULL // defaults
	);

const hkInternalClassMember hkClassEnumVersion1Padded::Item::Members[] =
{
    { "value", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1Padded::Item,m_value) },
    { "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1Padded::Item,m_name) }
};
const hkClass hkClassEnumItemVersion1PaddedClass(
    "hkClassEnumItem",
    HK_NULL, // parent
    sizeof(hkClassEnumVersion1Padded::Item),
    HK_NULL,
    0, // interfaces
    HK_NULL,
    0, // enums
    reinterpret_cast<const hkClassMember*>(hkClassEnumVersion1Padded::Item::Members),
    HK_COUNT_OF(hkClassEnumVersion1Padded::Item::Members),
    HK_NULL // defaults
    );      
const hkInternalClassMember hkClassEnumVersion1Padded::Members[] =
{           
    { "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1Padded,m_name) },
    { "items", &hkClassEnumItemVersion1PaddedClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1Padded,m_items) },
	{ "attributes", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1Padded,m_attributes), HK_NULL },
	{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1Padded,m_flags), HK_NULL }
};
const hkClass hkClassEnumVersion1PaddedClass(
    "hkClassEnum",
    HK_NULL, // parent
    sizeof(hkClassEnumVersion1Padded),
    HK_NULL,
    0, // interfaces
    HK_NULL,
    0, // enums
    reinterpret_cast<const hkClassMember*>(hkClassEnumVersion1Padded::Members),
    HK_COUNT_OF(hkClassEnumVersion1Padded::Members),
    HK_NULL // defaults
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
