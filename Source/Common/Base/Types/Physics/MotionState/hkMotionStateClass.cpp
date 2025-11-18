/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Base/Types/Physics/MotionState/hkMotionState.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Base/Types/Physics/MotionState/hkMotionState.h>



// External pointer and enum types
extern const hkClass hkSweptTransformClass;

//
// Class hkMotionState
//
HK_REFLECTION_DEFINE_SIMPLE(hkMotionState);
const hkInternalClassMember hkMotionState::Members[] =
{
	{ "transform", HK_NULL, HK_NULL, hkClassMember::TYPE_TRANSFORM, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_transform), HK_NULL },
	{ "sweptTransform", &hkSweptTransformClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_sweptTransform), HK_NULL },
	{ "deltaAngle", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_deltaAngle), HK_NULL },
	{ "objectRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_objectRadius), HK_NULL },
	{ "linearDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_linearDamping), HK_NULL },
	{ "angularDamping", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_angularDamping), HK_NULL },
	{ "maxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_maxLinearVelocity), HK_NULL },
	{ "maxAngularVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_maxAngularVelocity), HK_NULL },
	{ "deactivationClass", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkMotionState,m_deactivationClass), HK_NULL }
};
extern const hkClass hkMotionStateClass;
const hkClass hkMotionStateClass(
	"hkMotionState",
	HK_NULL, // parent
	sizeof(hkMotionState),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkMotionState::Members),
	HK_COUNT_OF(hkMotionState::Members),
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
