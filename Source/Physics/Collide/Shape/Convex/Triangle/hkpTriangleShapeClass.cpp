/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>



// External pointer and enum types
extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum;

//
// Class hkpTriangleShape
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpTriangleShape);
const hkInternalClassMember hkpTriangleShape::Members[] =
{
	{ "weldingInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTriangleShape,m_weldingInfo), HK_NULL },
	{ "weldingType", HK_NULL, hkpWeldingUtilityWeldingTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpTriangleShape,m_weldingType), HK_NULL },
	{ "isExtruded", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTriangleShape,m_isExtruded), HK_NULL },
	{ "vertexA", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTriangleShape,m_vertexA), HK_NULL },
	{ "vertexB", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTriangleShape,m_vertexB), HK_NULL },
	{ "vertexC", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTriangleShape,m_vertexC), HK_NULL },
	{ "extrusion", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTriangleShape,m_extrusion), HK_NULL }
};
namespace
{
	struct hkpTriangleShape_DefaultStruct
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
	const hkpTriangleShape_DefaultStruct hkpTriangleShape_Default =
	{
		{-1,HK_OFFSET_OF(hkpTriangleShape_DefaultStruct,m_weldingType),-1,-1,-1,-1,-1},
		hkpWeldingUtility::WELDING_TYPE_NONE
	};
}
extern const hkClass hkpConvexShapeClass;

extern const hkClass hkpTriangleShapeClass;
const hkClass hkpTriangleShapeClass(
	"hkpTriangleShape",
	&hkpConvexShapeClass, // parent
	sizeof(hkpTriangleShape),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpTriangleShape::Members),
	HK_COUNT_OF(hkpTriangleShape::Members),
	&hkpTriangleShape_Default,
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
