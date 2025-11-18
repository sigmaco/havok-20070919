/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Common/hkpProperty.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Common/hkpProperty.h>



// External pointer and enum types
extern const hkClass hkpPropertyValueClass;

//
// Class hkpPropertyValue
//
HK_REFLECTION_DEFINE_SIMPLE(hkpPropertyValue);
static const hkInternalClassMember hkpPropertyValueClass_Members[] =
{
	{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT64, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPropertyValue,m_data), HK_NULL }
};
const hkClass hkpPropertyValueClass(
	"hkpPropertyValue",
	HK_NULL, // parent
	sizeof(hkpPropertyValue),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPropertyValueClass_Members),
	HK_COUNT_OF(hkpPropertyValueClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpProperty
//
HK_REFLECTION_DEFINE_SIMPLE(hkpProperty);
static const hkInternalClassMember hkpPropertyClass_Members[] =
{
	{ "key", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpProperty,m_key), HK_NULL },
	{ "alignmentPadding", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpProperty,m_alignmentPadding), HK_NULL },
	{ "value", &hkpPropertyValueClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpProperty,m_value), HK_NULL }
};
extern const hkClass hkpPropertyClass;
const hkClass hkpPropertyClass(
	"hkpProperty",
	HK_NULL, // parent
	sizeof(hkpProperty),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPropertyClass_Members),
	HK_COUNT_OF(hkpPropertyClass_Members),
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
