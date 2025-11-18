/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppEmbeddedShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppEmbeddedShape.h>



// External pointer and enum types
extern const hkClass hkpMeshMaterialClass;
extern const hkClass hkpMoppCodeReindexedTerminalClass;
extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;

//
// Class hkpMoppEmbeddedShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpMoppEmbeddedShape);
const hkInternalClassMember hkpMoppEmbeddedShape::Members[] =
{
	{ "aabbHalfExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_aabbHalfExtents), HK_NULL },
	{ "aabbCenter", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_aabbCenter), HK_NULL },
	{ "triangleExtrusion", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_triangleExtrusion), HK_NULL },
	{ "childRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_childRadius), HK_NULL },
	{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_weldingType), HK_NULL },
	{ "materialBase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_materialBase), HK_NULL },
	{ "materialStriding", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_materialStriding), HK_NULL },
	{ "numMaterials", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_numMaterials), HK_NULL },
	{ "reindexedTerminals", &hkpMoppCodeReindexedTerminalClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpMoppEmbeddedShape,m_reindexedTerminals), HK_NULL }
};
namespace
{
	struct hkpMoppEmbeddedShape_DefaultStruct
	{
		int s_defaultOffsets[9];
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
	const hkpMoppEmbeddedShape_DefaultStruct hkpMoppEmbeddedShape_Default =
	{
		{-1,-1,-1,-1,HK_OFFSET_OF(hkpMoppEmbeddedShape_DefaultStruct,m_weldingType),-1,-1,-1,-1},
		hkpWeldingUtility::WELDING_TYPE_NONE
	};
}
extern const hkClass hkMoppBvTreeShapeBaseClass;

extern const hkClass hkpMoppEmbeddedShapeClass;
const hkClass hkpMoppEmbeddedShapeClass(
	"hkpMoppEmbeddedShape",
	&hkMoppBvTreeShapeBaseClass, // parent
	sizeof(hkpMoppEmbeddedShape),
	HK_NULL,
	1, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpMoppEmbeddedShape::Members),
	HK_COUNT_OF(hkpMoppEmbeddedShape::Members),
	&hkpMoppEmbeddedShape_Default,
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
