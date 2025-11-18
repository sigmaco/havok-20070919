/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>



// External pointer and enum types
extern const hkClass hkpListShapeChildInfoClass;
extern const hkClass hkpShapeClass;

//
// Class hkpListShape::ChildInfo
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpListShape,ChildInfo);
static const hkInternalClassMember hkpListShape_ChildInfoClass_Members[] =
{
	{ "shape", &hkpShapeClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpListShape::ChildInfo,m_shape), HK_NULL },
	{ "collisionFilterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpListShape::ChildInfo,m_collisionFilterInfo), HK_NULL },
	{ "shapeSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpListShape::ChildInfo,m_shapeSize), HK_NULL },
	{ "numChildShapes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpListShape::ChildInfo,m_numChildShapes), HK_NULL }
};
const hkClass hkpListShapeChildInfoClass(
	"hkpListShapeChildInfo",
	HK_NULL, // parent
	sizeof(hkpListShape::ChildInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpListShape_ChildInfoClass_Members),
	HK_COUNT_OF(hkpListShape_ChildInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpListShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpListShape);
static const hkInternalClassMember hkpListShapeClass_Members[] =
{
	{ "childInfo", &hkpListShapeChildInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpListShape,m_childInfo), HK_NULL },
	{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpListShape,m_aabbHalfExtents), HK_NULL },
	{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpListShape,m_aabbCenter), HK_NULL },
	{ "enabledChildren", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 8, 0, HK_OFFSET_OF(hkpListShape,m_enabledChildren), HK_NULL }
};
extern const hkClass hkpShapeCollectionClass;

extern const hkClass hkpListShapeClass;
const hkClass hkpListShapeClass(
	"hkpListShape",
	&hkpShapeCollectionClass, // parent
	sizeof(hkpListShape),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpListShapeClass_Members),
	HK_COUNT_OF(hkpListShapeClass_Members),
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
