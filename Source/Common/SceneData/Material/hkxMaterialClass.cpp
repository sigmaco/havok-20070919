/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Material/hkxMaterial.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Material/hkxMaterial.h>



// External pointer and enum types
extern const hkClass hkxMaterialClass;
extern const hkClass hkxMaterialTextureStageClass;

//
// Enum hkxMaterial::TextureType
//
static const hkInternalClassEnumItem hkxMaterialTextureTypeEnumItems[] =
{
	{0, "TEX_UNKNOWN"},
	{1, "TEX_DIFFUSE"},
	{2, "TEX_REFLECTION"},
	{3, "TEX_BUMP"},
	{4, "TEX_NORMAL"},
	{5, "TEX_DISPLACEMENT"},
};
static const hkInternalClassEnum hkxMaterialEnums[] = {
	{"TextureType", hkxMaterialTextureTypeEnumItems, 6, HK_NULL, 0 }
};
extern const hkClassEnum* hkxMaterialTextureTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkxMaterialEnums[0]);

//
// Class hkxMaterial::TextureStage
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkxMaterial,TextureStage);
static const hkInternalClassMember hkxMaterial_TextureStageClass_Members[] =
{
	{ "texture", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxMaterial::TextureStage,m_texture), HK_NULL },
	{ "usageHint", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxMaterial::TextureStage,m_usageHint), HK_NULL }
};
const hkClass hkxMaterialTextureStageClass(
	"hkxMaterialTextureStage",
	HK_NULL, // parent
	sizeof(hkxMaterial::TextureStage),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkxMaterial_TextureStageClass_Members),
	HK_COUNT_OF(hkxMaterial_TextureStageClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkxMaterial
//
HK_REFLECTION_DEFINE_SIMPLE(hkxMaterial);
static const hkInternalClassMember hkxMaterialClass_Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxMaterial,m_name), HK_NULL },
	{ "stages", &hkxMaterialTextureStageClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkxMaterial,m_stages), HK_NULL },
	{ "diffuseColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxMaterial,m_diffuseColor), HK_NULL },
	{ "ambientColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxMaterial,m_ambientColor), HK_NULL },
	{ "specularColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxMaterial,m_specularColor), HK_NULL },
	{ "emissiveColor", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxMaterial,m_emissiveColor), HK_NULL },
	{ "subMaterials", &hkxMaterialClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxMaterial,m_subMaterials), HK_NULL },
	{ "extraData", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxMaterial,m_extraData), HK_NULL }
};
extern const hkClass hkxAttributeHolderClass;

const hkClass hkxMaterialClass(
	"hkxMaterial",
	&hkxAttributeHolderClass, // parent
	sizeof(hkxMaterial),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkxMaterialEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkxMaterialClass_Members),
	HK_COUNT_OF(hkxMaterialClass_Members),
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
