/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Entity/hkpRigidBodyDeactivator.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Entity/hkpRigidBodyDeactivator.h>



//
// Enum hkpRigidBodyDeactivator::DeactivatorType
//
static const hkInternalClassEnumItem hkpRigidBodyDeactivatorDeactivatorTypeEnumItems[] =
{
	{0, "DEACTIVATOR_INVALID"},
	{1, "DEACTIVATOR_NEVER"},
	{2, "DEACTIVATOR_SPATIAL"},
	{3, "DEACTIVATOR_MAX_ID"},
};
static const hkInternalClassEnum hkpRigidBodyDeactivatorEnums[] = {
	{"DeactivatorType", hkpRigidBodyDeactivatorDeactivatorTypeEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* hkpRigidBodyDeactivatorDeactivatorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpRigidBodyDeactivatorEnums[0]);

//
// Class hkpRigidBodyDeactivator
//

extern const hkClass hkpEntityDeactivatorClass;

extern const hkClass hkpRigidBodyDeactivatorClass;
const hkClass hkpRigidBodyDeactivatorClass(
	"hkpRigidBodyDeactivator",
	&hkpEntityDeactivatorClass, // parent
	sizeof(hkpRigidBodyDeactivator),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpRigidBodyDeactivatorEnums),
	1, // enums
	HK_NULL,
	0,
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
