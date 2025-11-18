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

extern const hkClass hkClassVersion1Class;
extern const hkClass hkClassVersion2Class;
extern const hkClass hkClassMemberVersion1Class;
extern const hkClass hkClassEnumVersion1Class;

class hkClassVersion1
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_HKCLASS, hkClassVersion1 );
		HK_DECLARE_REFLECTION();

	public:

		hkClassVersion1() { }

	protected:

		const char* m_name;
		const hkClass* m_parent;
		int m_objectSize;
		int m_numImplementedInterfaces;
		const class hkClassEnumVersion1* m_declaredEnums;
		int m_numDeclaredEnums;
		const class hkClassMember* m_declaredMembers;
		int m_numDeclaredMembers;
		hkBool m_hasVtable;
		char m_padToSizeOfClass[sizeof(void*) - sizeof(hkBool)];
};

class hkClassVersion2
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_HKCLASS, hkClassVersion2 );
		HK_DECLARE_REFLECTION();

	public:

		hkClassVersion2() { }

	protected:

		const char* m_name;
		const hkClass* m_parent;
		int m_objectSize;
		int m_numImplementedInterfaces;
		const class hkClassEnumVersion1* m_declaredEnums;
		int m_numDeclaredEnums;
		const class hkClassMember* m_declaredMembers;
		int m_numDeclaredMembers;
		void* m_defaults;
};

class hkClassMemberVersion1
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_HKCLASS, hkClassMemberVersion1);
		HK_DECLARE_REFLECTION();

	public:

		hkClassMemberVersion1() { }

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
		const hkClass* m_class;
		const hkClassEnumVersion1* m_enum;
		hkEnum<Type,hkUint8> m_type;
		hkEnum<Type,hkUint8> m_subtype;
		hkInt16 m_cArraySize;
		hkUint16 m_flags;
		hkUint16 m_offset;
};

class hkClassEnumVersion1
{
	public:

        HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_HKCLASS, hkClassEnumVersion1);
		HK_DECLARE_REFLECTION();

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
};

//
// Class hkClass
//
const hkInternalClassMember hkClassVersion1::Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1,m_name) },
	{ "parent", &hkClassVersion1Class, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion1,m_parent) },
	{ "objectSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1,m_objectSize) },
	{ "numImplementedInterfaces", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1,m_numImplementedInterfaces) },
	{ "declaredEnums", &hkClassEnumVersion1Class, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion1,m_declaredEnums) },
	{ "declaredMembers", &hkClassMemberVersion1Class, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion1,m_declaredMembers) },
	{ "hasVtable", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion1,m_hasVtable) }
};
const hkClass hkClassVersion1Class(
	"hkClass",
	HK_NULL, // parent
	sizeof(hkClassVersion1),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkClassVersion1::Members),
	HK_COUNT_OF(hkClassVersion1::Members), // members
	HK_NULL // defaults
	);
const hkInternalClassMember hkClassVersion2::Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2,m_name) },
	{ "parent", &hkClassVersion2Class, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion2,m_parent) },
	{ "objectSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2,m_objectSize) },
	{ "numImplementedInterfaces", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2,m_numImplementedInterfaces) },
	{ "declaredEnums", &hkClassEnumVersion1Class, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion2,m_declaredEnums) },
	{ "declaredMembers", &hkClassMemberVersion1Class, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassVersion2,m_declaredMembers) },
	{ "defaults", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassVersion2,m_defaults) }
};

const hkClass hkClassVersion2Class(
	"hkClass",
	HK_NULL, // parent
	sizeof(hkClassVersion2),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkClassVersion2::Members),
	HK_COUNT_OF(hkClassVersion2::Members), // members
	HK_NULL // defaults
	);


static const hkInternalClassEnumItem hkClassMemberVersion1TypeEnumItems[] =
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
	{32, "TYPE_MAX"}
};
static const hkInternalClassEnumItem hkClassMemberVersion1FlagsEnumItems[] =
{
	{1, "POINTER_OPTIONAL"},
	{2, "POINTER_VOIDSTAR"},
	{8, "ENUM_8"},
	{16, "ENUM_16"},
	{32, "ENUM_32"},
	{64, "ARRAY_RAWDATA"},
};
static const hkInternalClassEnumItem hkClassMemberVersion1RangeEnumItems[] =
{
	{0, "INVALID"},
	{1, "DEFAULT"},
	{2, "ABS_MIN"},
	{4, "ABS_MAX"},
	{8, "SOFT_MIN"},
	{16, "SOFT_MAX"},
	{32, "RANGE_MAX"},
};
static const hkInternalClassEnum hkClassMemberVersion1Enums[] = {
	{"Type", hkClassMemberVersion1TypeEnumItems, HK_COUNT_OF(hkClassMemberVersion1TypeEnumItems) },
	{"Flags", hkClassMemberVersion1FlagsEnumItems, HK_COUNT_OF(hkClassMemberVersion1FlagsEnumItems) },
	{"Range", hkClassMemberVersion1RangeEnumItems, HK_COUNT_OF(hkClassMemberVersion1RangeEnumItems) }
};
static const hkClassEnum* hkClassMemberVersion1TypeEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberVersion1Enums[0]);
static const hkClassEnum* hkClassMemberVersion1FlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberVersion1Enums[1]);
static const hkClassEnum* hkClassMemberVersion1RangeEnum = reinterpret_cast<const hkClassEnum*>(&hkClassMemberVersion1Enums[2]);

static hkInternalClassMember hkClassMemberVersion1Class_Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1,m_name) },
	{ "class", &hkClassVersion1Class, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1,m_class) },
	{ "enum", &hkClassEnumVersion1Class, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1,m_enum) },
	{ "type", HK_NULL, hkClassMemberVersion1TypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1,m_type) },
	{ "subtype", HK_NULL, hkClassMemberVersion1TypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1,m_subtype) },
	{ "cArraySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1,m_cArraySize) },
	{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1,m_flags) },
	{ "offset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassMemberVersion1,m_offset) }
};

const hkClass hkClassMemberVersion1Class(
	"hkClassMember",
	HK_NULL, // parent
	sizeof(hkClassMemberVersion1),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkClassMemberVersion1Enums),
	HK_COUNT_OF(hkClassMemberVersion1Enums), // enums
	reinterpret_cast<const hkClassMember*>(hkClassMemberVersion1Class_Members),
	HK_COUNT_OF(hkClassMemberVersion1Class_Members), // members
	HK_NULL // defaults
	);

const hkInternalClassMember hkClassEnumVersion1::Item::Members[] =
{
    { "value", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1::Item,m_value) },
    { "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1::Item,m_name) }
};
const hkClass hkClassEnumItemVersion1Class(
    "hkClassEnumItem",
    HK_NULL, // parent
    sizeof(hkClassEnumVersion1::Item),
    HK_NULL,
    0, // interfaces
    HK_NULL,
    0, // enums
    reinterpret_cast<const hkClassMember*>(hkClassEnumVersion1::Item::Members),
    HK_COUNT_OF(hkClassEnumVersion1::Item::Members),
    HK_NULL // defaults
    );      
const hkInternalClassMember hkClassEnumVersion1::Members[] =
{           
    { "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1,m_name) },
    { "items", &hkClassEnumItemVersion1Class, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClassEnumVersion1,m_items) }      
};
const hkClass hkClassEnumVersion1Class(
    "hkClassEnum",
    HK_NULL, // parent
    sizeof(hkClassEnumVersion1),
    HK_NULL,
    0, // interfaces
    HK_NULL,
    0, // enums
    reinterpret_cast<const hkClassMember*>(hkClassEnumVersion1::Members),
    HK_COUNT_OF(hkClassEnumVersion1::Members),
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
