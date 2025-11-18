/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Graph/hkxNode.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Graph/hkxNode.h>



// External pointer and enum types
extern const hkClass hkxNodeAnnotationDataClass;
extern const hkClass hkxNodeClass;

//
// Class hkxNode::AnnotationData
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkxNode,AnnotationData);
static const hkInternalClassMember hkxNode_AnnotationDataClass_Members[] =
{
	{ "time", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxNode::AnnotationData,m_time), HK_NULL },
	{ "description", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxNode::AnnotationData,m_description), HK_NULL }
};
const hkClass hkxNodeAnnotationDataClass(
	"hkxNodeAnnotationData",
	HK_NULL, // parent
	sizeof(hkxNode::AnnotationData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkxNode_AnnotationDataClass_Members),
	HK_COUNT_OF(hkxNode_AnnotationDataClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkxNode
//
HK_REFLECTION_DEFINE_SIMPLE(hkxNode);
static const hkInternalClassMember hkxNodeClass_Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxNode,m_name), HK_NULL },
	{ "object", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxNode,m_object), HK_NULL },
	{ "keyFrames", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_MATRIX4, 0, 0, HK_OFFSET_OF(hkxNode,m_keyFrames), HK_NULL },
	{ "children", &hkxNodeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkxNode,m_children), HK_NULL },
	{ "annotations", &hkxNodeAnnotationDataClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkxNode,m_annotations), HK_NULL },
	{ "userProperties", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxNode,m_userProperties), HK_NULL },
	{ "selected", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxNode,m_selected), HK_NULL }
};
extern const hkClass hkxAttributeHolderClass;

const hkClass hkxNodeClass(
	"hkxNode",
	&hkxAttributeHolderClass, // parent
	sizeof(hkxNode),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkxNodeClass_Members),
	HK_COUNT_OF(hkxNodeClass_Members),
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
