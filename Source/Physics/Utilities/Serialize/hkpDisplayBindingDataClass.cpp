/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Utilities/Serialize/hkpDisplayBindingData.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Utilities/Serialize/hkpDisplayBindingData.h>



// External pointer and enum types
extern const hkClass hkpPhysicsSystemClass;
extern const hkClass hkpPhysicsSystemDisplayBindingClass;
extern const hkClass hkpRigidBodyClass;
extern const hkClass hkpRigidBodyDisplayBindingClass;
extern const hkClass hkxMeshClass;

//
// Class hkpRigidBodyDisplayBinding
//
HK_REFLECTION_DEFINE_SIMPLE(hkpRigidBodyDisplayBinding);
static const hkInternalClassMember hkpRigidBodyDisplayBindingClass_Members[] =
{
	{ "rigidBody", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpRigidBodyDisplayBinding,m_rigidBody), HK_NULL },
	{ "displayObject", &hkxMeshClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpRigidBodyDisplayBinding,m_displayObject), HK_NULL },
	{ "rigidBodyFromDisplayObjectTransform", HK_NULL, HK_NULL, hkClassMember::TYPE_MATRIX4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpRigidBodyDisplayBinding,m_rigidBodyFromDisplayObjectTransform), HK_NULL }
};
const hkClass hkpRigidBodyDisplayBindingClass(
	"hkpRigidBodyDisplayBinding",
	HK_NULL, // parent
	sizeof(hkpRigidBodyDisplayBinding),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpRigidBodyDisplayBindingClass_Members),
	HK_COUNT_OF(hkpRigidBodyDisplayBindingClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPhysicsSystemDisplayBinding
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpPhysicsSystemDisplayBinding);
static const hkInternalClassMember hkpPhysicsSystemDisplayBindingClass_Members[] =
{
	{ "bindings", &hkpRigidBodyDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpPhysicsSystemDisplayBinding,m_bindings), HK_NULL },
	{ "system", &hkpPhysicsSystemClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpPhysicsSystemDisplayBinding,m_system), HK_NULL }
};
const hkClass hkpPhysicsSystemDisplayBindingClass(
	"hkpPhysicsSystemDisplayBinding",
	HK_NULL, // parent
	sizeof(hkpPhysicsSystemDisplayBinding),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPhysicsSystemDisplayBindingClass_Members),
	HK_COUNT_OF(hkpPhysicsSystemDisplayBindingClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpDisplayBindingData
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpDisplayBindingData);
static const hkInternalClassMember hkpDisplayBindingDataClass_Members[] =
{
	{ "rigidBodyBindings", &hkpRigidBodyDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpDisplayBindingData,m_rigidBodyBindings), HK_NULL },
	{ "physicsSystemBindings", &hkpPhysicsSystemDisplayBindingClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpDisplayBindingData,m_physicsSystemBindings), HK_NULL }
};
extern const hkClass hkpDisplayBindingDataClass;
const hkClass hkpDisplayBindingDataClass(
	"hkpDisplayBindingData",
	HK_NULL, // parent
	sizeof(hkpDisplayBindingData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpDisplayBindingDataClass_Members),
	HK_COUNT_OF(hkpDisplayBindingDataClass_Members),
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
