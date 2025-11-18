/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Convex/PackedConvexVertices/hkpPackedConvexVerticesShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Convex/PackedConvexVertices/hkpPackedConvexVerticesShape.h>



// External pointer and enum types
extern const hkClass hkpPackedConvexVerticesShapeFourVectorsClass;

//
// Class hkpPackedConvexVerticesShape::FourVectors
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpPackedConvexVerticesShape,FourVectors);
static const hkInternalClassMember hkpPackedConvexVerticesShape_FourVectorsClass_Members[] =
{
	{ "x", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape::FourVectors,m_x), HK_NULL },
	{ "y", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape::FourVectors,m_y), HK_NULL },
	{ "z", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape::FourVectors,m_z), HK_NULL }
};
const hkClass hkpPackedConvexVerticesShapeFourVectorsClass(
	"hkpPackedConvexVerticesShapeFourVectors",
	HK_NULL, // parent
	sizeof(hkpPackedConvexVerticesShape::FourVectors),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPackedConvexVerticesShape_FourVectorsClass_Members),
	HK_COUNT_OF(hkpPackedConvexVerticesShape_FourVectorsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPackedConvexVerticesShape::Vector4IntW
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpPackedConvexVerticesShape,Vector4IntW);
static const hkInternalClassMember hkpPackedConvexVerticesShape_Vector4IntWClass_Members[] =
{
	{ "x", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpPackedConvexVerticesShape::Vector4IntW,m_x), HK_NULL },
	{ "y", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape::Vector4IntW,m_y), HK_NULL },
	{ "z", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape::Vector4IntW,m_z), HK_NULL },
	{ "w", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape::Vector4IntW,m_w), HK_NULL }
};
extern const hkClass hkpPackedConvexVerticesShapeVector4IntWClass;
const hkClass hkpPackedConvexVerticesShapeVector4IntWClass(
	"hkpPackedConvexVerticesShapeVector4IntW",
	HK_NULL, // parent
	sizeof(hkpPackedConvexVerticesShape::Vector4IntW),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPackedConvexVerticesShape_Vector4IntWClass_Members),
	HK_COUNT_OF(hkpPackedConvexVerticesShape_Vector4IntWClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPackedConvexVerticesShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpPackedConvexVerticesShape);
static const hkInternalClassMember hkpPackedConvexVerticesShapeClass_Members[] =
{
	{ "planeEquations", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape,m_planeEquations), HK_NULL },
	{ "aabbMin", &hkpPackedConvexVerticesShapeVector4IntWClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape,m_aabbMin), HK_NULL },
	{ "aabbExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape,m_aabbExtents), HK_NULL },
	{ "vertices", &hkpPackedConvexVerticesShapeFourVectorsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, hkpPackedConvexVerticesShape::BUILTIN_FOUR_VECTORS, 0, HK_OFFSET_OF(hkpPackedConvexVerticesShape,m_vertices), HK_NULL }
};
extern const hkClass hkpConvexShapeClass;

extern const hkClass hkpPackedConvexVerticesShapeClass;
const hkClass hkpPackedConvexVerticesShapeClass(
	"hkpPackedConvexVerticesShape",
	&hkpConvexShapeClass, // parent
	sizeof(hkpPackedConvexVerticesShape),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPackedConvexVerticesShapeClass_Members),
	HK_COUNT_OF(hkpPackedConvexVerticesShapeClass_Members),
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
