/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Motion/hkpMotion.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Motion/hkpMotion.h>



// External pointer and enum types
extern const hkClass hkMotionStateClass;
extern const hkClass hkpMaxSizeMotionClass;

//
// Enum hkpMotion::MotionType
//
static const hkInternalClassEnumItem hkpMotionMotionTypeEnumItems[] =
{
	{0, "MOTION_INVALID"},
	{1, "MOTION_DYNAMIC"},
	{2, "MOTION_SPHERE_INERTIA"},
	{3, "MOTION_STABILIZED_SPHERE_INERTIA"},
	{4, "MOTION_BOX_INERTIA"},
	{5, "MOTION_STABILIZED_BOX_INERTIA"},
	{6, "MOTION_KEYFRAMED"},
	{7, "MOTION_FIXED"},
	{8, "MOTION_THIN_BOX_INERTIA"},
	{9, "MOTION_CHARACTER"},
	{10, "MOTION_MAX_ID"},
};
static const hkInternalClassEnum hkpMotionEnums[] = {
	{"MotionType", hkpMotionMotionTypeEnumItems, 11, HK_NULL, 0 }
};
extern const hkClassEnum* hkpMotionMotionTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpMotionEnums[0]);

//
// Class hkpMotion
//

static const hkInternalClassMember hkpMotionClass_Members[] =
{
	{ "type", HK_NULL, hkpMotionMotionTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpMotion,m_type), HK_NULL },
	{ "deactivationIntegrateCounter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMotion,m_deactivationIntegrateCounter), HK_NULL },
	{ "deactivationNumInactiveFrames", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkpMotion,m_deactivationNumInactiveFrames), HK_NULL },
	{ "motionState", &hkMotionStateClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMotion,m_motionState), HK_NULL },
	{ "inertiaAndMassInv", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMotion,m_inertiaAndMassInv), HK_NULL },
	{ "linearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMotion,m_linearVelocity), HK_NULL },
	{ "angularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMotion,m_angularVelocity), HK_NULL },
	{ "deactivationRefPosition", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkpMotion,m_deactivationRefPosition), HK_NULL },
	{ "deactivationRefOrientation", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkpMotion,m_deactivationRefOrientation), HK_NULL },
	{ "savedMotion", &hkpMaxSizeMotionClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpMotion,m_savedMotion), HK_NULL },
	{ "savedQualityTypeIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpMotion,m_savedQualityTypeIndex), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpMotionClass;
const hkClass hkpMotionClass(
	"hkpMotion",
	&hkReferencedObjectClass, // parent
	sizeof(hkpMotion),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpMotionEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpMotionClass_Members),
	HK_COUNT_OF(hkpMotionClass_Members),
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
