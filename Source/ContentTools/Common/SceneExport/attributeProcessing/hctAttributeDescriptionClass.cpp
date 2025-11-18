/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'ContentTools/Common/SceneExport/AttributeProcessing/hctAttributeDescription.h'
#include <ContentTools/Common/SceneExport/hctSceneExport.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <ContentTools/Common/SceneExport/AttributeProcessing/hctAttributeDescription.h>



// External pointer and enum types
extern const hkClass hctAttributeDescriptionClass;
extern const hkClass hctAttributeGroupDescriptionClass;
extern const hkClass hkClassEnumClass;

//
// Enum hctAttributeDescription::ForcedType
//
static const hkInternalClassEnumItem hctAttributeDescriptionForcedTypeEnumItems[] =
{
	{0, "LEAVE"},
	{1, "FORCE_BOOL"},
	{2, "FORCE_INT"},
	{3, "FORCE_ENUM"},
	{4, "FORCE_FLOAT"},
	{5, "FORCE_STRING"},
	{6, "FORCE_VECTOR"},
	{7, "FORCE_MATRIX"},
	{8, "FORCE_QUATERNION"},
};

//
// Enum hctAttributeDescription::Hint
//
static const hkInternalClassEnumItem hctAttributeDescriptionHintEnumItems[] =
{
	{0, "HINT_NONE"},
	{1, "HINT_IGNORE"},
	{2, "HINT_TRANSFORM"},
	{4, "HINT_SCALE"},
	{6, "HINT_TRANSFORM_AND_SCALE"},
	{8, "HINT_FLIP"},
};
static const hkInternalClassEnum hctAttributeDescriptionEnums[] = {
	{"ForcedType", hctAttributeDescriptionForcedTypeEnumItems, 9, HK_NULL, 0 },
	{"Hint", hctAttributeDescriptionHintEnumItems, 6, HK_NULL, 0 }
};
extern const hkClassEnum* hctAttributeDescriptionForcedTypeEnum = reinterpret_cast<const hkClassEnum*>(&hctAttributeDescriptionEnums[0]);
extern const hkClassEnum* hctAttributeDescriptionHintEnum = reinterpret_cast<const hkClassEnum*>(&hctAttributeDescriptionEnums[1]);

//
// Class hctAttributeDescription
//
HK_REFLECTION_DEFINE_SIMPLE(hctAttributeDescription);
static const hkInternalClassMember hctAttributeDescriptionClass_Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctAttributeDescription,m_name), HK_NULL },
	{ "enabledBy", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctAttributeDescription,m_enabledBy), HK_NULL },
	{ "forcedType", HK_NULL, hctAttributeDescriptionForcedTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hctAttributeDescription,m_forcedType), HK_NULL },
	{ "enum", &hkClassEnumClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hctAttributeDescription,m_enum), HK_NULL },
	{ "hint", HK_NULL, hctAttributeDescriptionHintEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hctAttributeDescription,m_hint), HK_NULL },
	{ "clearHints", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctAttributeDescription,m_clearHints), HK_NULL },
	{ "floatScale", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctAttributeDescription,m_floatScale), HK_NULL }
};
const hkClass hctAttributeDescriptionClass(
	"hctAttributeDescription",
	HK_NULL, // parent
	sizeof(hctAttributeDescription),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hctAttributeDescriptionEnums),
	2, // enums
	reinterpret_cast<const hkClassMember*>(hctAttributeDescriptionClass_Members),
	HK_COUNT_OF(hctAttributeDescriptionClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hctAttributeGroupDescription
//
HK_REFLECTION_DEFINE_SIMPLE(hctAttributeGroupDescription);
static const hkInternalClassMember hctAttributeGroupDescriptionClass_Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctAttributeGroupDescription,m_name), HK_NULL },
	{ "attributeDescriptions", &hctAttributeDescriptionClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hctAttributeGroupDescription,m_attributeDescriptions), HK_NULL }
};
const hkClass hctAttributeGroupDescriptionClass(
	"hctAttributeGroupDescription",
	HK_NULL, // parent
	sizeof(hctAttributeGroupDescription),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hctAttributeGroupDescriptionClass_Members),
	HK_COUNT_OF(hctAttributeGroupDescriptionClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hctAttributeDescriptionDatabase
//
HK_REFLECTION_DEFINE_SIMPLE(hctAttributeDescriptionDatabase);
static const hkInternalClassMember hctAttributeDescriptionDatabaseClass_Members[] =
{
	{ "groupDescriptions", &hctAttributeGroupDescriptionClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hctAttributeDescriptionDatabase,m_groupDescriptions), HK_NULL }
};
extern const hkClass hctAttributeDescriptionDatabaseClass;
const hkClass hctAttributeDescriptionDatabaseClass(
	"hctAttributeDescriptionDatabase",
	HK_NULL, // parent
	sizeof(hctAttributeDescriptionDatabase),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hctAttributeDescriptionDatabaseClass_Members),
	HK_COUNT_OF(hctAttributeDescriptionDatabaseClass_Members),
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
