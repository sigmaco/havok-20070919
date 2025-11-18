/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Compound/Collection/SimpleMesh/hkpSimpleMeshShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Compound/Collection/SimpleMesh/hkpSimpleMeshShape.h>



// External pointer and enum types
extern const hkClass hkpSimpleMeshShapeTriangleClass;
extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;

//
// Class hkpSimpleMeshShape::Triangle
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpSimpleMeshShape,Triangle);
static const hkInternalClassMember hkpSimpleMeshShape_TriangleClass_Members[] =
{
	{ "a", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape::Triangle,m_a), HK_NULL },
	{ "b", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape::Triangle,m_b), HK_NULL },
	{ "c", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape::Triangle,m_c), HK_NULL },
	{ "weldingInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape::Triangle,m_weldingInfo), HK_NULL }
};
const hkClass hkpSimpleMeshShapeTriangleClass(
	"hkpSimpleMeshShapeTriangle",
	HK_NULL, // parent
	sizeof(hkpSimpleMeshShape::Triangle),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSimpleMeshShape_TriangleClass_Members),
	HK_COUNT_OF(hkpSimpleMeshShape_TriangleClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSimpleMeshShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpSimpleMeshShape);
static const hkInternalClassMember hkpSimpleMeshShapeClass_Members[] =
{
	{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VECTOR4, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape,m_vertices), HK_NULL },
	{ "triangles", &hkpSimpleMeshShapeTriangleClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape,m_triangles), HK_NULL },
	{ "materialIndices", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape,m_materialIndices), HK_NULL },
	{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape,m_radius), HK_NULL },
	{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpSimpleMeshShape,m_weldingType), HK_NULL }
};
namespace
{
	struct hkpSimpleMeshShape_DefaultStruct
	{
		int s_defaultOffsets[5];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkUint8 /* hkEnum<hkpWeldingUtility::WeldingType, hkUint8> */ m_weldingType;
	};
	const hkpSimpleMeshShape_DefaultStruct hkpSimpleMeshShape_Default =
	{
		{-1,-1,-1,-1,HK_OFFSET_OF(hkpSimpleMeshShape_DefaultStruct,m_weldingType)},
		hkpWeldingUtility::WELDING_TYPE_NONE
	};
}
extern const hkClass hkpShapeCollectionClass;

extern const hkClass hkpSimpleMeshShapeClass;
const hkClass hkpSimpleMeshShapeClass(
	"hkpSimpleMeshShape",
	&hkpShapeCollectionClass, // parent
	sizeof(hkpSimpleMeshShape),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSimpleMeshShapeClass_Members),
	HK_COUNT_OF(hkpSimpleMeshShapeClass_Members),
	&hkpSimpleMeshShape_Default,
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
