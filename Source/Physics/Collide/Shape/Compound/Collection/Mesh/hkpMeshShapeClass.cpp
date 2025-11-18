/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Compound/Collection/Mesh/hkpMeshShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Compound/Collection/Mesh/hkpMeshShape.h>



// External pointer and enum types
extern const hkClass hkpMeshMaterialClass;
extern const hkClass hkpMeshShapeSubpartClass;
extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;

//
// Enum hkpMeshShape::IndexStridingType
//
static const hkInternalClassEnumItem hkpMeshShapeIndexStridingTypeEnumItems[] =
{
	{0, "INDICES_INVALID"},
	{1, "INDICES_INT16"},
	{2, "INDICES_INT32"},
	{3, "INDICES_MAX_ID"},
};

//
// Enum hkpMeshShape::MaterialIndexStridingType
//
static const hkInternalClassEnumItem hkpMeshShapeMaterialIndexStridingTypeEnumItems[] =
{
	{0, "MATERIAL_INDICES_INVALID"},
	{1, "MATERIAL_INDICES_INT8"},
	{2, "MATERIAL_INDICES_INT16"},
	{3, "MATERIAL_INDICES_MAX_ID"},
};
static const hkInternalClassEnum hkpMeshShapeEnums[] = {
	{"IndexStridingType", hkpMeshShapeIndexStridingTypeEnumItems, 4, HK_NULL, 0 },
	{"MaterialIndexStridingType", hkpMeshShapeMaterialIndexStridingTypeEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* hkpMeshShapeIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpMeshShapeEnums[0]);
extern const hkClassEnum* hkpMeshShapeMaterialIndexStridingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpMeshShapeEnums[1]);

//
// Class hkpMeshShape::Subpart
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpMeshShape,Subpart);
static const hkInternalClassMember hkpMeshShape_SubpartClass_Members[] =
{
	{ "vertexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpMeshShape::Subpart,m_vertexBase), HK_NULL },
	{ "vertexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_vertexStriding), HK_NULL },
	{ "numVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_numVertices), HK_NULL },
	{ "indexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpMeshShape::Subpart,m_indexBase), HK_NULL },
	{ "stridingType", HK_NULL, hkpMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_stridingType), HK_NULL },
	{ "materialIndexStridingType", HK_NULL, hkpMeshShapeIndexStridingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_materialIndexStridingType), HK_NULL },
	{ "indexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_indexStriding), HK_NULL },
	{ "flipAlternateTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_flipAlternateTriangles), HK_NULL },
	{ "numTriangles", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_numTriangles), HK_NULL },
	{ "materialIndexBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpMeshShape::Subpart,m_materialIndexBase), HK_NULL },
	{ "materialIndexStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_materialIndexStriding), HK_NULL },
	{ "materialBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpMeshShape::Subpart,m_materialBase), HK_NULL },
	{ "materialStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_materialStriding), HK_NULL },
	{ "numMaterials", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_numMaterials), HK_NULL },
	{ "triangleOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape::Subpart,m_triangleOffset), HK_NULL }
};
namespace
{
	struct hkpMeshShapeSubpart_DefaultStruct
	{
		int s_defaultOffsets[15];
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
	const hkpMeshShapeSubpart_DefaultStruct hkpMeshShapeSubpart_Default =
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpMeshShapeSubpart_DefaultStruct,m_triangleOffset)},
		-1
	};
}
const hkClass hkpMeshShapeSubpartClass(
	"hkpMeshShapeSubpart",
	HK_NULL, // parent
	sizeof(hkpMeshShape::Subpart),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpMeshShape_SubpartClass_Members),
	HK_COUNT_OF(hkpMeshShape_SubpartClass_Members),
	&hkpMeshShapeSubpart_Default,
	HK_NULL, // attributes
	0
	);

//
// Class hkpMeshShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpMeshShape);
const hkInternalClassMember hkpMeshShape::Members[] =
{
	{ "scaling", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape,m_scaling), HK_NULL },
	{ "numBitsForSubpartIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape,m_numBitsForSubpartIndex), HK_NULL },
	{ "subparts", &hkpMeshShapeSubpartClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpMeshShape,m_subparts), HK_NULL },
	{ "weldingInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT16, 0, 0, HK_OFFSET_OF(hkpMeshShape,m_weldingInfo), HK_NULL },
	{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpMeshShape,m_weldingType), HK_NULL },
	{ "radius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMeshShape,m_radius), HK_NULL },
	{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkpMeshShape,m_pad), HK_NULL }
};
namespace
{
	struct hkpMeshShape_DefaultStruct
	{
		int s_defaultOffsets[7];
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
	const hkpMeshShape_DefaultStruct hkpMeshShape_Default =
	{
		{-1,-1,-1,-1,HK_OFFSET_OF(hkpMeshShape_DefaultStruct,m_weldingType),-1,-1},
		hkpWeldingUtility::WELDING_TYPE_NONE
	};
}
extern const hkClass hkpShapeCollectionClass;

extern const hkClass hkpMeshShapeClass;
const hkClass hkpMeshShapeClass(
	"hkpMeshShape",
	&hkpShapeCollectionClass, // parent
	sizeof(hkpMeshShape),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpMeshShapeEnums),
	2, // enums
	reinterpret_cast<const hkClassMember*>(hkpMeshShape::Members),
	HK_COUNT_OF(hkpMeshShape::Members),
	&hkpMeshShape_Default,
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
