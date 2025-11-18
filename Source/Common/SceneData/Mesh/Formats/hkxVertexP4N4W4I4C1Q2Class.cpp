/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Mesh/Formats/hkxVertexP4N4W4I4C1Q2.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Mesh/Formats/hkxVertexP4N4W4I4C1Q2.h>



//
// Class hkxVertexP4N4W4I4C1Q2
//
HK_REFLECTION_DEFINE_SIMPLE(hkxVertexP4N4W4I4C1Q2);
static const hkInternalClassMember hkxVertexP4N4W4I4C1Q2Class_Members[] =
{
	{ "position", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxVertexP4N4W4I4C1Q2,m_position), HK_NULL },
	{ "normal", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxVertexP4N4W4I4C1Q2,m_normal), HK_NULL },
	{ "weights", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxVertexP4N4W4I4C1Q2,m_weights), HK_NULL },
	{ "indices", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxVertexP4N4W4I4C1Q2,m_indices), HK_NULL },
	{ "diffuse", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxVertexP4N4W4I4C1Q2,m_diffuse), HK_NULL },
	{ "qu", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxVertexP4N4W4I4C1Q2,m_qu), HK_NULL },
	{ "qv", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxVertexP4N4W4I4C1Q2,m_qv), HK_NULL }
};
extern const hkClass hkxVertexP4N4W4I4C1Q2Class;
const hkClass hkxVertexP4N4W4I4C1Q2Class(
	"hkxVertexP4N4W4I4C1Q2",
	HK_NULL, // parent
	sizeof(hkxVertexP4N4W4I4C1Q2),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkxVertexP4N4W4I4C1Q2Class_Members),
	HK_COUNT_OF(hkxVertexP4N4W4I4C1Q2Class_Members),
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
