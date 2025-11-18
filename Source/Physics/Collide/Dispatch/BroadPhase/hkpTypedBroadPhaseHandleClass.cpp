/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandle.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandle.h>



//
// Class hkpTypedBroadPhaseHandle
//
HK_REFLECTION_DEFINE_SIMPLE(hkpTypedBroadPhaseHandle);
const hkInternalClassMember hkpTypedBroadPhaseHandle::Members[] =
{
	{ "type", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTypedBroadPhaseHandle,m_type), HK_NULL },
	{ "ownerOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpTypedBroadPhaseHandle,m_ownerOffset), HK_NULL },
	{ "objectQualityType", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTypedBroadPhaseHandle,m_objectQualityType), HK_NULL },
	{ "collisionFilterInfo", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpTypedBroadPhaseHandle,m_collisionFilterInfo), HK_NULL }
};
extern const hkClass hkpBroadPhaseHandleClass;

extern const hkClass hkpTypedBroadPhaseHandleClass;
const hkClass hkpTypedBroadPhaseHandleClass(
	"hkpTypedBroadPhaseHandle",
	&hkpBroadPhaseHandleClass, // parent
	sizeof(hkpTypedBroadPhaseHandle),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpTypedBroadPhaseHandle::Members),
	HK_COUNT_OF(hkpTypedBroadPhaseHandle::Members),
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
