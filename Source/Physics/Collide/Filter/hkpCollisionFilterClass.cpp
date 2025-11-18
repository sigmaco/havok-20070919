/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Filter/hkpCollisionFilter.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Filter/hkpCollisionFilter.h>



//
// Enum hkpCollisionFilter::hkpFilterType
//
static const hkInternalClassEnumItem hkpCollisionFilterhkpFilterTypeEnumItems[] =
{
	{0, "HK_FILTER_UNKNOWN"},
	{1, "HK_FILTER_NULL"},
	{2, "HK_FILTER_GROUP"},
	{3, "HK_FILTER_LIST"},
	{4, "HK_FILTER_CUSTOM"},
	{5, "HK_FILTER_PAIR"},
	{6, "HK_FILTER_CONSTRAINT"},
};
static const hkInternalClassEnum hkpCollisionFilterEnums[] = {
	{"hkpFilterType", hkpCollisionFilterhkpFilterTypeEnumItems, 7, HK_NULL, 0 }
};
extern const hkClassEnum* hkpCollisionFilterhkpFilterTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpCollisionFilterEnums[0]);

//
// Class hkpCollisionFilter
//

static const hkInternalClassMember hkpCollisionFilterClass_Members[] =
{
	{ "type", HK_NULL, hkpCollisionFilterhkpFilterTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT32, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpCollisionFilter,m_type), HK_NULL },
	{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkpCollisionFilter,m_pad), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpCollisionFilterClass;
const hkClass hkpCollisionFilterClass(
	"hkpCollisionFilter",
	&hkReferencedObjectClass, // parent
	sizeof(hkpCollisionFilter),
	HK_NULL,
	4, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpCollisionFilterEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpCollisionFilterClass_Members),
	HK_COUNT_OF(hkpCollisionFilterClass_Members),
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
