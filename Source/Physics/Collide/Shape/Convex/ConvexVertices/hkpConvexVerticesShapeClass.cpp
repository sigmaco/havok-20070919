/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>



// External pointer and enum types
extern const hkClass hkpConvexVerticesShapeFourVectorsClass;

//
// Class hkpConvexVerticesShape::FourVectors
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpConvexVerticesShape,FourVectors);
static const hkInternalClassMember hkpConvexVerticesShape_FourVectorsClass_Members[] =
{
	{ "x", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConvexVerticesShape::FourVectors,m_x), HK_NULL },
	{ "y", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConvexVerticesShape::FourVectors,m_y), HK_NULL },
	{ "z", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConvexVerticesShape::FourVectors,m_z), HK_NULL }
};
const hkClass hkpConvexVerticesShapeFourVectorsClass(
	"hkpConvexVerticesShapeFourVectors",
	HK_NULL, // parent
	sizeof(hkpConvexVerticesShape::FourVectors),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpConvexVerticesShape_FourVectorsClass_Members),
	HK_COUNT_OF(hkpConvexVerticesShape_FourVectorsClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpConvexVerticesShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpConvexVerticesShape);
const hkInternalClassMember hkpConvexVerticesShape::Members[] =
{
	{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConvexVerticesShape,m_aabbHalfExtents), HK_NULL },
	{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConvexVerticesShape,m_aabbCenter), HK_NULL },
	{ "rotatedVertices", &hkpConvexVerticesShapeFourVectorsClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpConvexVerticesShape,m_rotatedVertices), HK_NULL },
	{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpConvexVerticesShape,m_numVertices), HK_NULL },
	{ "planeEquations", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, HK_OFFSET_OF(hkpConvexVerticesShape,m_planeEquations), HK_NULL }
};
extern const hkClass hkpConvexShapeClass;

extern const hkClass hkpConvexVerticesShapeClass;
const hkClass hkpConvexVerticesShapeClass(
	"hkpConvexVerticesShape",
	&hkpConvexShapeClass, // parent
	sizeof(hkpConvexVerticesShape),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpConvexVerticesShape::Members),
	HK_COUNT_OF(hkpConvexVerticesShape::Members),
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
