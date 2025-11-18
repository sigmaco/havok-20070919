/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Compound/Collection/ExtendedMeshShape/hkpExtendedMeshShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Compound/Collection/ExtendedMeshShape/hkpExtendedMeshShape.h>



// External pointer and enum types
extern const hkClass hkpConvexShapeClass;
extern const hkClass hkpExtendedMeshShapeShapesSubpartClass;
extern const hkClass hkpExtendedMeshShapeTrianglesSubpartClass;
extern const hkClass hkpMeshMaterialClass;
extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;

//
// Enum hkpExtendedMeshShape::IndexStridingType
//
static const hkInternalClassEnumItem hkpExtendedMeshShapeIndexStridingTypeEnumItems[] =
{
	{0, "INDICES_INVALID"},
	{1, "INDICES_INT16"},
	{2, "INDICES_INT32"},
	{3, "INDICES_MAX_ID"},
};

//
// Enum hkpExtendedMeshShape::MaterialIndexStridingType
//
static const hkInternalClassEnumItem hkpExtendedMeshShapeMaterialIndexStridingTypeEnumItems[] =
{
	{0, "MATERIAL_INDICES_INVALID"},
	{1, "MATERIAL_INDICES_INT8"},
	{2, "MATERIAL_INDICES_INT16"},
	{3, "MATERIAL_INDICES_MAX_ID"},
};

//
// Enum hkpExtendedMeshShape::SubpartType
//
static const hkInternalClassEnumItem hkpExtendedMeshShapeSubpartTypeEnumItems[] =
{
	{0, "SUBPART_TRIANGLES"},
	{1, "SUBPART_SHAPE"},
};
static const hkInternalClassEnum hkpExtendedMeshShapeEnums[] = {
	{"IndexStridingType", hkpExtendedMeshShapeIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
	{"MaterialIndexStridingType", hkpExtendedMeshShapeMaterialIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
	{"SubpartType", hkpExtendedMeshShapeSubpartTypeEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* hkpExtendedMeshShapeIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpExtendedMeshShapeEnums[0]);
extern const hkClassEnum* hkpExtendedMeshShapeMaterialIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpExtendedMeshShapeEnums[1]);
extern const hkClassEnum* hkpExtendedMeshShapeSubpartTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpExtendedMeshShapeEnums[2]);

//
// Class hkpExtendedMeshShape::Subpart
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpExtendedMeshShape,Subpart);
static const hkInternalClassMember hkpExtendedMeshShape_SubpartClass_Members[] =
{
	{ "type", HK_NULL, hkpExtendedMeshShapeSubpartTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::Subpart,m_type), HK_NULL },
	{ "materialIndexStridingType", HK_NULL, hkpExtendedMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::Subpart,m_materialIndexStridingType), HK_NULL },
	{ "materialStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::Subpart,m_materialStriding), HK_NULL },
	{ "materialIndexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpExtendedMeshShape::Subpart,m_materialIndexBase), HK_NULL },
	{ "materialIndexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::Subpart,m_materialIndexStriding), HK_NULL },
	{ "numMaterials", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::Subpart,m_numMaterials), HK_NULL },
	{ "materialBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpExtendedMeshShape::Subpart,m_materialBase), HK_NULL }
};
extern const hkClass hkpExtendedMeshShapeSubpartClass;
const hkClass hkpExtendedMeshShapeSubpartClass(
	"hkpExtendedMeshShapeSubpart",
	HK_NULL, // parent
	sizeof(hkpExtendedMeshShape::Subpart),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpExtendedMeshShape_SubpartClass_Members),
	HK_COUNT_OF(hkpExtendedMeshShape_SubpartClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpExtendedMeshShape::TrianglesSubpart
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpExtendedMeshShape,TrianglesSubpart);
static const hkInternalClassMember hkpExtendedMeshShape_TrianglesSubpartClass_Members[] =
{
	{ "numTriangleShapes", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_numTriangleShapes), HK_NULL },
	{ "vertexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_vertexBase), HK_NULL },
	{ "vertexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_vertexStriding), HK_NULL },
	{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_numVertices), HK_NULL },
	{ "extrusion", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_extrusion), HK_NULL },
	{ "indexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_indexBase), HK_NULL },
	{ "indexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_indexStriding), HK_NULL },
	{ "stridingType", HK_NULL, hkpExtendedMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_stridingType), HK_NULL },
	{ "flipAlternateTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_flipAlternateTriangles), HK_NULL },
	{ "triangleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::TrianglesSubpart,m_triangleOffset), HK_NULL }
};
namespace
{
	struct hkpExtendedMeshShapeTrianglesSubpart_DefaultStruct
	{
		int s_defaultOffsets[10];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		int m_triangleOffset;
	};
	const hkpExtendedMeshShapeTrianglesSubpart_DefaultStruct hkpExtendedMeshShapeTrianglesSubpart_Default =
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpExtendedMeshShapeTrianglesSubpart_DefaultStruct,m_triangleOffset)},
		-1
	};
}

const hkClass hkpExtendedMeshShapeTrianglesSubpartClass(
	"hkpExtendedMeshShapeTrianglesSubpart",
	&hkpExtendedMeshShapeSubpartClass, // parent
	sizeof(hkpExtendedMeshShape::TrianglesSubpart),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpExtendedMeshShape_TrianglesSubpartClass_Members),
	HK_COUNT_OF(hkpExtendedMeshShape_TrianglesSubpartClass_Members),
	&hkpExtendedMeshShapeTrianglesSubpart_Default,
	HK_NULL, // attributes
	0
	);

//
// Class hkpExtendedMeshShape::ShapesSubpart
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpExtendedMeshShape,ShapesSubpart);
static const hkInternalClassMember hkpExtendedMeshShape_ShapesSubpartClass_Members[] =
{
	{ "childShapes", &hkpConvexShapeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::ShapesSubpart,m_childShapes), HK_NULL },
	{ "offsetSet", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::ShapesSubpart,m_offsetSet), HK_NULL },
	{ "rotationSet", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::ShapesSubpart,m_rotationSet), HK_NULL },
	{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape::ShapesSubpart,m_transform), HK_NULL },
	{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 8, 0, HK_OFFSET_OF(hkpExtendedMeshShape::ShapesSubpart,m_pad), HK_NULL }
};

const hkClass hkpExtendedMeshShapeShapesSubpartClass(
	"hkpExtendedMeshShapeShapesSubpart",
	&hkpExtendedMeshShapeSubpartClass, // parent
	sizeof(hkpExtendedMeshShape::ShapesSubpart),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpExtendedMeshShape_ShapesSubpartClass_Members),
	HK_COUNT_OF(hkpExtendedMeshShape_ShapesSubpartClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpExtendedMeshShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpExtendedMeshShape);
const hkInternalClassMember hkpExtendedMeshShape::Members[] =
{
	{ "numBitsForSubpartIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_numBitsForSubpartIndex), HK_NULL },
	{ "scaling", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_scaling), HK_NULL },
	{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_aabbHalfExtents), HK_NULL },
	{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_aabbCenter), HK_NULL },
	{ "trianglesSubparts", &hkpExtendedMeshShapeTrianglesSubpartClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_trianglesSubparts), HK_NULL },
	{ "shapesSubparts", &hkpExtendedMeshShapeShapesSubpartClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_shapesSubparts), HK_NULL },
	{ "weldingInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_weldingInfo), HK_NULL },
	{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_weldingType), HK_NULL },
	{ "embeddedTrianglesSubpart", &hkpExtendedMeshShapeTrianglesSubpartClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_embeddedTrianglesSubpart), HK_NULL },
	{ "triangleRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpExtendedMeshShape,m_triangleRadius), HK_NULL },
	{ "pad16", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 3, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpExtendedMeshShape,m_pad16), HK_NULL }
};
namespace
{
	struct hkpExtendedMeshShape_DefaultStruct
	{
		int s_defaultOffsets[11];
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
	const hkpExtendedMeshShape_DefaultStruct hkpExtendedMeshShape_Default =
	{
		{-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpExtendedMeshShape_DefaultStruct,m_weldingType),-1,-1,-1},
		hkpWeldingUtility::WELDING_TYPE_NONE
	};
}
extern const hkClass hkpShapeCollectionClass;

extern const hkClass hkpExtendedMeshShapeClass;
const hkClass hkpExtendedMeshShapeClass(
	"hkpExtendedMeshShape",
	&hkpShapeCollectionClass, // parent
	sizeof(hkpExtendedMeshShape),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpExtendedMeshShapeEnums),
	3, // enums
	reinterpret_cast<const hkClassMember*>(hkpExtendedMeshShape::Members),
	HK_COUNT_OF(hkpExtendedMeshShape::Members),
	&hkpExtendedMeshShape_Default,
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
