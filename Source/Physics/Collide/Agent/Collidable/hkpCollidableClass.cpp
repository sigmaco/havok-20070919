/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Agent/Collidable/hkpCollidable.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Agent/Collidable/hkpCollidable.h>



// External pointer and enum types
extern const hkClass hkAabbUint32Class;
extern const hkClass hkpCollidableBoundingVolumeDataClass;
extern const hkClass hkpTypedBroadPhaseHandleClass;

//
// Enum hkpCollidable::ForceCollideOntoPpuReasons
//
static const hkInternalClassEnumItem hkpCollidableForceCollideOntoPpuReasonsEnumItems[] =
{
	{1, "FORCE_PPU_USER_REQUEST"},
	{2, "FORCE_PPU_SHAPE_REQUEST"},
	{4, "FORCE_PPU_MODIFIER_REQUEST"},
};
static const hkInternalClassEnum hkpCollidableEnums[] = {
	{"ForceCollideOntoPpuReasons", hkpCollidableForceCollideOntoPpuReasonsEnumItems, 3, HK_NULL, 0 }
};
extern const hkClassEnum* hkpCollidableForceCollideOntoPpuReasonsEnum = reinterpret_cast<const hkClassEnum*>(&hkpCollidableEnums[0]);

//
// Class hkpCollidable::BoundingVolumeData
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpCollidable,BoundingVolumeData);
static const hkInternalClassMember hkpCollidable_BoundingVolumeDataClass_Members[] =
{
	{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkpCollidable::BoundingVolumeData,m_min), HK_NULL },
	{ "expansionMin", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkpCollidable::BoundingVolumeData,m_expansionMin), HK_NULL },
	{ "expansionShift", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCollidable::BoundingVolumeData,m_expansionShift), HK_NULL },
	{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkpCollidable::BoundingVolumeData,m_max), HK_NULL },
	{ "expansionMax", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkpCollidable::BoundingVolumeData,m_expansionMax), HK_NULL },
	{ "padding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCollidable::BoundingVolumeData,m_padding), HK_NULL },
	{ "numChildShapeAabbs", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCollidable::BoundingVolumeData,m_numChildShapeAabbs), HK_NULL },
	{ "childShapeAabbs", &hkAabbUint32Class, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpCollidable::BoundingVolumeData,m_childShapeAabbs), HK_NULL }
};
const hkClass hkpCollidableBoundingVolumeDataClass(
	"hkpCollidableBoundingVolumeData",
	HK_NULL, // parent
	sizeof(hkpCollidable::BoundingVolumeData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpCollidable_BoundingVolumeDataClass_Members),
	HK_COUNT_OF(hkpCollidable_BoundingVolumeDataClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpCollidable
//
HK_REFLECTION_DEFINE_SIMPLE(hkpCollidable);
const hkInternalClassMember hkpCollidable::Members[] =
{
	{ "ownerOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpCollidable,m_ownerOffset), HK_NULL },
	{ "forceCollideOntoPpu", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCollidable,m_forceCollideOntoPpu), HK_NULL },
	{ "shapeSizeOnSpu", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpCollidable,m_shapeSizeOnSpu), HK_NULL },
	{ "broadPhaseHandle", &hkpTypedBroadPhaseHandleClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCollidable,m_broadPhaseHandle), HK_NULL },
	{ "boundingVolumeData", &hkpCollidableBoundingVolumeDataClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCollidable,m_boundingVolumeData), HK_NULL },
	{ "allowedPenetrationDepth", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpCollidable,m_allowedPenetrationDepth), HK_NULL }
};
extern const hkClass hkpCdBodyClass;

extern const hkClass hkpCollidableClass;
const hkClass hkpCollidableClass(
	"hkpCollidable",
	&hkpCdBodyClass, // parent
	sizeof(hkpCollidable),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpCollidableEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpCollidable::Members),
	HK_COUNT_OF(hkpCollidable::Members),
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
