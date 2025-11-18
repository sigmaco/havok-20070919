/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/World/hkpWorldObject.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/World/hkpWorldObject.h>


//
// Global
//

//
// Enum ::Result
//
static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldObjectResultEnumItems[] =
{
	{0, "POSTPONED"},
	{1, "DONE"},
};
static const hkInternalClassEnum Physics_Dynamics_World_hkpWorldObjectEnums[] = {
	{"Result", Physics_Dynamics_World_hkpWorldObjectResultEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* ResultEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldObjectEnums[0]);

// External pointer and enum types
extern const hkClass hkMultiThreadCheckClass;
extern const hkClass hkpLinkedCollidableClass;
extern const hkClass hkpPropertyClass;
extern const hkClass hkpWorldClass;

//
// Enum hkpWorldObject::BroadPhaseType
//
static const hkInternalClassEnumItem hkpWorldObjectBroadPhaseTypeEnumItems[] =
{
	{0, "BROAD_PHASE_INVALID"},
	{1, "BROAD_PHASE_ENTITY"},
	{2, "BROAD_PHASE_PHANTOM"},
	{3, "BROAD_PHASE_BORDER"},
	{4, "BROAD_PHASE_MAX_ID"},
};
static const hkInternalClassEnum hkpWorldObjectEnums[] = {
	{"BroadPhaseType", hkpWorldObjectBroadPhaseTypeEnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hkpWorldObjectBroadPhaseTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldObjectEnums[0]);

//
// Class hkpWorldObject
//

const hkInternalClassMember hkpWorldObject::Members[] =
{
	{ "world", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorldObject,m_world), HK_NULL },
	{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldObject,m_userData), HK_NULL },
	{ "collidable", &hkpLinkedCollidableClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldObject,m_collidable), HK_NULL },
	{ "multiThreadCheck", &hkMultiThreadCheckClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldObject,m_multiThreadCheck), HK_NULL },
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldObject,m_name), HK_NULL },
	{ "properties", &hkpPropertyClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpWorldObject,m_properties), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpWorldObjectClass;
const hkClass hkpWorldObjectClass(
	"hkpWorldObject",
	&hkReferencedObjectClass, // parent
	sizeof(hkpWorldObject),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpWorldObjectEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpWorldObject::Members),
	HK_COUNT_OF(hkpWorldObject::Members),
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
