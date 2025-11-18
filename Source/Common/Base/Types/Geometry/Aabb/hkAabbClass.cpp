/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Base/Types/Geometry/Aabb/hkAabb.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>



//
// Class hkAabb
//
HK_REFLECTION_DEFINE_SIMPLE(hkAabb);
static const hkInternalClassMember hkAabbClass_Members[] =
{
	{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkAabb,m_min), HK_NULL },
	{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkAabb,m_max), HK_NULL }
};
extern const hkClass hkAabbClass;
const hkClass hkAabbClass(
	"hkAabb",
	HK_NULL, // parent
	sizeof(hkAabb),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkAabbClass_Members),
	HK_COUNT_OF(hkAabbClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkAabbUint32
//
HK_REFLECTION_DEFINE_SIMPLE(hkAabbUint32);
static const hkInternalClassMember hkAabbUint32Class_Members[] =
{
	{ "min", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkAabbUint32,m_min), HK_NULL },
	{ "expansionMin", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkAabbUint32,m_expansionMin), HK_NULL },
	{ "expansionShift", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkAabbUint32,m_expansionShift), HK_NULL },
	{ "max", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkAabbUint32,m_max), HK_NULL },
	{ "expansionMax", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 3, 0, HK_OFFSET_OF(hkAabbUint32,m_expansionMax), HK_NULL },
	{ "sortIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkAabbUint32,m_sortIndex), HK_NULL }
};
extern const hkClass hkAabbUint32Class;
const hkClass hkAabbUint32Class(
	"hkAabbUint32",
	HK_NULL, // parent
	sizeof(hkAabbUint32),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkAabbUint32Class_Members),
	HK_COUNT_OF(hkAabbUint32Class_Members),
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
