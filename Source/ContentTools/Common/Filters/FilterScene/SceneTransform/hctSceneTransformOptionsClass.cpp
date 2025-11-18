/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'ContentTools/Common/Filters/FilterScene/SceneTransform/hctSceneTransformOptions.h'
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <ContentTools/Common/Filters/FilterScene/SceneTransform/hctSceneTransformOptions.h>



//
// Enum hctSceneTransformOptions::Preset
//
static const hkInternalClassEnumItem hctSceneTransformOptionsPresetEnumItems[] =
{
	{0, "IDENTITY"},
	{1, "MIRROR_X"},
	{2, "MIRROR_Y"},
	{3, "MIRROR_Z"},
	{4, "SCALE_FEET_TO_METERS"},
	{5, "SCALE_INCHES_TO_METERS"},
	{6, "SCALE_CMS_TO_METERS"},
	{7, "CUSTOM"},
	{8, "PRESET_MAX_ID"},
};
static const hkInternalClassEnum hctSceneTransformOptionsEnums[] = {
	{"Preset", hctSceneTransformOptionsPresetEnumItems, 9, HK_NULL, 0 }
};
extern const hkClassEnum* hctSceneTransformOptionsPresetEnum = reinterpret_cast<const hkClassEnum*>(&hctSceneTransformOptionsEnums[0]);

//
// Class hctSceneTransformOptions
//
HK_REFLECTION_DEFINE_SIMPLE(hctSceneTransformOptions);
static const hkInternalClassMember hctSceneTransformOptionsClass_Members[] =
{
	{ "preset", HK_NULL, hctSceneTransformOptionsPresetEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hctSceneTransformOptions,m_preset), HK_NULL },
	{ "applyToNodes", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctSceneTransformOptions,m_applyToNodes), HK_NULL },
	{ "applyToBuffers", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctSceneTransformOptions,m_applyToBuffers), HK_NULL },
	{ "applyToLights", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctSceneTransformOptions,m_applyToLights), HK_NULL },
	{ "applyToCameras", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctSceneTransformOptions,m_applyToCameras), HK_NULL },
	{ "flipWinding", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctSceneTransformOptions,m_flipWinding), HK_NULL },
	{ "matrix", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctSceneTransformOptions,m_matrix), HK_NULL }
};
namespace
{
	struct hctSceneTransformOptions_DefaultStruct
	{
		int s_defaultOffsets[7];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkInt8 /* hkEnum<Preset, hkInt8> */ m_preset;
		_hkBool m_applyToNodes;
		_hkBool m_applyToBuffers;
		_hkBool m_applyToLights;
		_hkBool m_applyToCameras;
	};
	const hctSceneTransformOptions_DefaultStruct hctSceneTransformOptions_Default =
	{
		{HK_OFFSET_OF(hctSceneTransformOptions_DefaultStruct,m_preset),HK_OFFSET_OF(hctSceneTransformOptions_DefaultStruct,m_applyToNodes),HK_OFFSET_OF(hctSceneTransformOptions_DefaultStruct,m_applyToBuffers),HK_OFFSET_OF(hctSceneTransformOptions_DefaultStruct,m_applyToLights),HK_OFFSET_OF(hctSceneTransformOptions_DefaultStruct,m_applyToCameras),-1,-1},
		hctSceneTransformOptions::IDENTITY,true,true,true,true
	};
}
extern const hkClass hctSceneTransformOptionsClass;
const hkClass hctSceneTransformOptionsClass(
	"hctSceneTransformOptions",
	HK_NULL, // parent
	sizeof(hctSceneTransformOptions),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hctSceneTransformOptionsEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hctSceneTransformOptionsClass_Members),
	HK_COUNT_OF(hctSceneTransformOptionsClass_Members),
	&hctSceneTransformOptions_Default,
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
