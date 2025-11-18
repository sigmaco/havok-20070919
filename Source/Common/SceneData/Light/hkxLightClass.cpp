/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Light/hkxLight.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Light/hkxLight.h>



//
// Enum hkxLight::LightType
//
static const hkInternalClassEnumItem hkxLightLightTypeEnumItems[] =
{
	{0, "POINT_LIGHT"},
	{1, "DIRECTIONAL_LIGHT"},
	{2, "SPOT_LIGHT"},
};
static const hkInternalClassEnum hkxLightEnums[] = {
	{"LightType", hkxLightLightTypeEnumItems, 3, HK_NULL, 0 }
};
extern const hkClassEnum* hkxLightLightTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkxLightEnums[0]);

//
// Class hkxLight
//
HK_REFLECTION_DEFINE_SIMPLE(hkxLight);
static const hkInternalClassMember hkxLightClass_Members[] =
{
	{ "type", HK_NULL, hkxLightLightTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkxLight,m_type), HK_NULL },
	{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxLight,m_position), HK_NULL },
	{ "direction", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxLight,m_direction), HK_NULL },
	{ "color", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxLight,m_color), HK_NULL },
	{ "angle", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxLight,m_angle), HK_NULL }
};
extern const hkClass hkxLightClass;
const hkClass hkxLightClass(
	"hkxLight",
	HK_NULL, // parent
	sizeof(hkxLight),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkxLightEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkxLightClass_Members),
	HK_COUNT_OF(hkxLightClass_Members),
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
