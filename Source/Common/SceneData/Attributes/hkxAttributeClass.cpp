/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Attributes/hkxAttribute.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Attributes/hkxAttribute.h>



//
// Enum hkxAttribute::Hint
//
static const hkInternalClassEnumItem hkxAttributeHintEnumItems[] =
{
	{0, "HINT_NONE"},
	{1, "HINT_IGNORE"},
	{2, "HINT_TRANSFORM"},
	{4, "HINT_SCALE"},
	{6, "HINT_TRANSFORM_AND_SCALE"},
	{8, "HINT_FLIP"},
};
static const hkInternalClassEnum hkxAttributeEnums[] = {
	{"Hint", hkxAttributeHintEnumItems, 6, HK_NULL, 0 }
};
extern const hkClassEnum* hkxAttributeHintEnum = reinterpret_cast<const hkClassEnum*>(&hkxAttributeEnums[0]);

//
// Class hkxAttribute
//
HK_REFLECTION_DEFINE_SIMPLE(hkxAttribute);
static const hkInternalClassMember hkxAttributeClass_Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxAttribute,m_name), HK_NULL },
	{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxAttribute,m_value), HK_NULL }
};
extern const hkClass hkxAttributeClass;
const hkClass hkxAttributeClass(
	"hkxAttribute",
	HK_NULL, // parent
	sizeof(hkxAttribute),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkxAttributeEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkxAttributeClass_Members),
	HK_COUNT_OF(hkxAttributeClass_Members),
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
