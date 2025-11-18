/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/World/hkpPhysicsSystem.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/World/hkpPhysicsSystem.h>



// External pointer and enum types
extern const hkClass hkpActionClass;
extern const hkClass hkpConstraintInstanceClass;
extern const hkClass hkpPhantomClass;
extern const hkClass hkpRigidBodyClass;

//
// Class hkpPhysicsSystem
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpPhysicsSystem);
const hkInternalClassMember hkpPhysicsSystem::Members[] =
{
	{ "rigidBodies", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpPhysicsSystem,m_rigidBodies), HK_NULL },
	{ "constraints", &hkpConstraintInstanceClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpPhysicsSystem,m_constraints), HK_NULL },
	{ "actions", &hkpActionClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpPhysicsSystem,m_actions), HK_NULL },
	{ "phantoms", &hkpPhantomClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpPhysicsSystem,m_phantoms), HK_NULL },
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPhysicsSystem,m_name), HK_NULL },
	{ "userData", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPhysicsSystem,m_userData), HK_NULL },
	{ "active", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPhysicsSystem,m_active), HK_NULL }
};
namespace
{
	struct hkpPhysicsSystem_DefaultStruct
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
		_hkBool m_active;
	};
	const hkpPhysicsSystem_DefaultStruct hkpPhysicsSystem_Default =
	{
		{-1,-1,-1,-1,-1,-1,HK_OFFSET_OF(hkpPhysicsSystem_DefaultStruct,m_active)},
		true
	};
}
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpPhysicsSystemClass;
const hkClass hkpPhysicsSystemClass(
	"hkpPhysicsSystem",
	&hkReferencedObjectClass, // parent
	sizeof(hkpPhysicsSystem),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPhysicsSystem::Members),
	HK_COUNT_OF(hkpPhysicsSystem::Members),
	&hkpPhysicsSystem_Default,
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
