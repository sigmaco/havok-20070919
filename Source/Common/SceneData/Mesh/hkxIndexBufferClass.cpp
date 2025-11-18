/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Mesh/hkxIndexBuffer.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Mesh/hkxIndexBuffer.h>



//
// Enum hkxIndexBuffer::IndexType
//
static const hkInternalClassEnumItem hkxIndexBufferIndexTypeEnumItems[] =
{
	{0, "INDEX_TYPE_INVALID"},
	{1, "INDEX_TYPE_TRI_LIST"},
	{2, "INDEX_TYPE_TRI_STRIP"},
	{3, "INDEX_TYPE_TRI_FAN"},
	{4, "INDEX_TYPE_MAX_ID"},
};
static const hkInternalClassEnum hkxIndexBufferEnums[] = {
	{"IndexType", hkxIndexBufferIndexTypeEnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkxIndexBufferIndexTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkxIndexBufferEnums[0]);

//
// Class hkxIndexBuffer
//
HK_REFLECTION_DEFINE_SIMPLE(hkxIndexBuffer);
static const hkInternalClassMember hkxIndexBufferClass_Members[] =
{
	{ "indexType", HK_NULL, hkxIndexBufferIndexTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkxIndexBuffer,m_indexType), HK_NULL },
	{ "indices16", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkxIndexBuffer,m_indices16), HK_NULL },
	{ "indices32", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_UINT32, 0, 0, HK_OFFSET_OF(hkxIndexBuffer,m_indices32), HK_NULL },
	{ "vertexBaseOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxIndexBuffer,m_vertexBaseOffset), HK_NULL },
	{ "length", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxIndexBuffer,m_length), HK_NULL }
};
extern const hkClass hkxIndexBufferClass;
const hkClass hkxIndexBufferClass(
	"hkxIndexBuffer",
	HK_NULL, // parent
	sizeof(hkxIndexBuffer),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkxIndexBufferEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkxIndexBufferClass_Members),
	HK_COUNT_OF(hkxIndexBufferClass_Members),
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
