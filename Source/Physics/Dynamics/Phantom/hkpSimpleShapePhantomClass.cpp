/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Phantom/hkpSimpleShapePhantom.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Phantom/hkpSimpleShapePhantom.h>



// External pointer and enum types
extern const hkClass hkpCollidableClass;
extern const hkClass hkpSimpleShapePhantomCollisionDetailClass;

//
// Class hkpSimpleShapePhantom::CollisionDetail
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpSimpleShapePhantom,CollisionDetail);
static const hkInternalClassMember hkpSimpleShapePhantom_CollisionDetailClass_Members[] =
{
	{ "collidable", &hkpCollidableClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpSimpleShapePhantom::CollisionDetail,m_collidable), HK_NULL }
};
const hkClass hkpSimpleShapePhantomCollisionDetailClass(
	"hkpSimpleShapePhantomCollisionDetail",
	HK_NULL, // parent
	sizeof(hkpSimpleShapePhantom::CollisionDetail),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSimpleShapePhantom_CollisionDetailClass_Members),
	HK_COUNT_OF(hkpSimpleShapePhantom_CollisionDetailClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSimpleShapePhantom
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpSimpleShapePhantom);
const hkInternalClassMember hkpSimpleShapePhantom::Members[] =
{
	{ "collisionDetails", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpSimpleShapePhantom,m_collisionDetails), HK_NULL }
};
extern const hkClass hkpShapePhantomClass;

extern const hkClass hkpSimpleShapePhantomClass;
const hkClass hkpSimpleShapePhantomClass(
	"hkpSimpleShapePhantom",
	&hkpShapePhantomClass, // parent
	sizeof(hkpSimpleShapePhantom),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSimpleShapePhantom::Members),
	HK_COUNT_OF(hkpSimpleShapePhantom::Members),
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
