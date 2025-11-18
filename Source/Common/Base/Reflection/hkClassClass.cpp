/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Base/Reflection/hkClass.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Base/Reflection/hkClass.h>



// External pointer and enum types
extern const hkClass hkClassClass;
extern const hkClass hkClassEnumClass;
extern const hkClass hkClassMemberClass;
extern const hkClass hkCustomAttributesClass;

//
// Enum hkClass::SignatureFlags
//
static const hkInternalClassEnumItem hkClassSignatureFlagsEnumItems[] =
{
	{1, "SIGNATURE_LOCAL"},
};

//
// Enum hkClass::FlagValues
//
static const hkInternalClassEnumItem hkClassFlagValuesEnumItems[] =
{
	{0, "FLAGS_NONE"},
	{1, "FLAGS_NOT_SERIALIZABLE"},
};
static const hkInternalClassEnum hkClassEnums[] = {
	{"SignatureFlags", hkClassSignatureFlagsEnumItems, 1, HK_NULL, 0 },
	{"FlagValues", hkClassFlagValuesEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* hkClassSignatureFlagsEnum = reinterpret_cast<const hkClassEnum*>(&hkClassEnums[0]);
extern const hkClassEnum* hkClassFlagValuesEnum = reinterpret_cast<const hkClassEnum*>(&hkClassEnums[1]);

//
// Class hkClass
//
HK_REFLECTION_DEFINE_SIMPLE(hkClass);
const hkInternalClassMember hkClass::Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClass,m_name), HK_NULL },
	{ "parent", &hkClassClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClass,m_parent), HK_NULL },
	{ "objectSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClass,m_objectSize), HK_NULL },
	{ "numImplementedInterfaces", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClass,m_numImplementedInterfaces), HK_NULL },
	{ "declaredEnums", &hkClassEnumClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClass,m_declaredEnums), HK_NULL },
	{ "declaredMembers", &hkClassMemberClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkClass,m_declaredMembers), HK_NULL },
	{ "defaults", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkClass,m_defaults), HK_NULL },
	{ "attributes", &hkCustomAttributesClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkClass,m_attributes), HK_NULL },
	{ "flags", HK_NULL, hkClassFlagValuesEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkClass,m_flags), HK_NULL },
	{ "describedVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkClass,m_describedVersion), HK_NULL }
};
const hkClass hkClassClass(
	"hkClass",
	HK_NULL, // parent
	sizeof(hkClass),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkClassEnums),
	2, // enums
	reinterpret_cast<const hkClassMember*>(hkClass::Members),
	HK_COUNT_OF(hkClass::Members),
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
