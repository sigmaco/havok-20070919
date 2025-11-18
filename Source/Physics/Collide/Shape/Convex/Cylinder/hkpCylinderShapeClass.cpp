/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>



//
// Enum hkpCylinderShape::VertexIdEncoding
//
static const hkInternalClassEnumItem hkpCylinderShapeVertexIdEncodingEnumItems[] =
{
	{7, "VERTEX_ID_ENCODING_IS_BASE_A_SHIFT"},
	{6, "VERTEX_ID_ENCODING_SIN_SIGN_SHIFT"},
	{5, "VERTEX_ID_ENCODING_COS_SIGN_SHIFT"},
	{4, "VERTEX_ID_ENCODING_IS_SIN_LESSER_SHIFT"},
	{15/*0x0f*/, "VERTEX_ID_ENCODING_VALUE_MASK"},
};
static const hkInternalClassEnum hkpCylinderShapeEnums[] = {
	{"VertexIdEncoding", hkpCylinderShapeVertexIdEncodingEnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkpCylinderShapeVertexIdEncodingEnum = reinterpret_cast<const hkClassEnum*>(&hkpCylinderShapeEnums[0]);

//
// Class hkpCylinderShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpCylinderShape);
const hkInternalClassMember hkpCylinderShape::Members[] =
{
	{ "cylRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCylinderShape,m_cylRadius), HK_NULL },
	{ "cylBaseRadiusFactorForHeightFieldCollisions", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCylinderShape,m_cylBaseRadiusFactorForHeightFieldCollisions), HK_NULL },
	{ "vertexA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCylinderShape,m_vertexA), HK_NULL },
	{ "vertexB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCylinderShape,m_vertexB), HK_NULL },
	{ "perpendicular1", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCylinderShape,m_perpendicular1), HK_NULL },
	{ "perpendicular2", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCylinderShape,m_perpendicular2), HK_NULL }
};
namespace
{
	struct hkpCylinderShape_DefaultStruct
	{
		int s_defaultOffsets[6];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkReal m_cylBaseRadiusFactorForHeightFieldCollisions;
	};
	const hkpCylinderShape_DefaultStruct hkpCylinderShape_Default =
	{
		{-1,HK_OFFSET_OF(hkpCylinderShape_DefaultStruct,m_cylBaseRadiusFactorForHeightFieldCollisions),-1,-1,-1,-1},
		0.8f
	};
}
extern const hkClass hkpConvexShapeClass;

extern const hkClass hkpCylinderShapeClass;
const hkClass hkpCylinderShapeClass(
	"hkpCylinderShape",
	&hkpConvexShapeClass, // parent
	sizeof(hkpCylinderShape),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpCylinderShapeEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpCylinderShape::Members),
	HK_COUNT_OF(hkpCylinderShape::Members),
	&hkpCylinderShape_Default,
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
