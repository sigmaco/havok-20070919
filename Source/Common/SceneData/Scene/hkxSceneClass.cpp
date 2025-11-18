/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Scene/hkxScene.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Scene/hkxScene.h>



// External pointer and enum types
extern const hkClass hkxCameraClass;
extern const hkClass hkxLightClass;
extern const hkClass hkxMaterialClass;
extern const hkClass hkxMeshClass;
extern const hkClass hkxNodeClass;
extern const hkClass hkxNodeSelectionSetClass;
extern const hkClass hkxSkinBindingClass;
extern const hkClass hkxTextureFileClass;
extern const hkClass hkxTextureInplaceClass;

//
// Class hkxScene
//
HK_REFLECTION_DEFINE_SIMPLE(hkxScene);
static const hkInternalClassMember hkxSceneClass_Members[] =
{
	{ "modeller", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxScene,m_modeller), HK_NULL },
	{ "asset", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxScene,m_asset), HK_NULL },
	{ "sceneLength", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxScene,m_sceneLength), HK_NULL },
	{ "rootNode", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkxScene,m_rootNode), HK_NULL },
	{ "selectionSets", &hkxNodeSelectionSetClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxScene,m_selectionSets), HK_NULL },
	{ "cameras", &hkxCameraClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxScene,m_cameras), HK_NULL },
	{ "lights", &hkxLightClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxScene,m_lights), HK_NULL },
	{ "meshes", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxScene,m_meshes), HK_NULL },
	{ "materials", &hkxMaterialClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxScene,m_materials), HK_NULL },
	{ "inplaceTextures", &hkxTextureInplaceClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxScene,m_inplaceTextures), HK_NULL },
	{ "externalTextures", &hkxTextureFileClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxScene,m_externalTextures), HK_NULL },
	{ "skinBindings", &hkxSkinBindingClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxScene,m_skinBindings), HK_NULL },
	{ "appliedTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX3, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxScene,m_appliedTransform), HK_NULL }
};
namespace
{
	struct hkxScene_DefaultStruct
	{
		int s_defaultOffsets[13];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		_hkMatrix3 m_appliedTransform;
	};
	const hkxScene_DefaultStruct hkxScene_Default =
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkxScene_DefaultStruct,m_appliedTransform)},
		{1,0,0,0,0,1,0,0,0,0,1,0}
	};
}
extern const hkClass hkxSceneClass;
const hkClass hkxSceneClass(
	"hkxScene",
	HK_NULL, // parent
	sizeof(hkxScene),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkxSceneClass_Members),
	HK_COUNT_OF(hkxSceneClass_Members),
	&hkxScene_Default,
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
