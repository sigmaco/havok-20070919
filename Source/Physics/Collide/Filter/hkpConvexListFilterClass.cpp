/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Filter/hkpConvexListFilter.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Filter/hkpConvexListFilter.h>



//
// Enum hkpConvexListFilter::ConvexListCollisionType
//
static const hkInternalClassEnumItem hkpConvexListFilterConvexListCollisionTypeEnumItems[] =
{
	{0, "TREAT_CONVEX_LIST_AS_NORMAL"},
	{1, "TREAT_CONVEX_LIST_AS_LIST"},
	{2, "TREAT_CONVEX_LIST_AS_CONVEX"},
};
static const hkInternalClassEnum hkpConvexListFilterEnums[] = {
	{"ConvexListCollisionType", hkpConvexListFilterConvexListCollisionTypeEnumItems, 3, HK_NULL, 0 }
};
extern const hkClassEnum* hkpConvexListFilterConvexListCollisionTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpConvexListFilterEnums[0]);

//
// Class hkpConvexListFilter
//

extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpConvexListFilterClass;
const hkClass hkpConvexListFilterClass(
	"hkpConvexListFilter",
	&hkReferencedObjectClass, // parent
	sizeof(hkpConvexListFilter),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpConvexListFilterEnums),
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
