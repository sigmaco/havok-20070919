/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Base/Reflection/Attributes/hkAttributes.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Base/Reflection/Attributes/hkAttributes.h>



//
// Class hkRangeRealAttribute
//
HK_REFLECTION_DEFINE_SIMPLE(hkRangeRealAttribute);
static const hkInternalClassMember hkRangeRealAttributeClass_Members[] =
{
	{ "absmin", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRangeRealAttribute,m_absmin), HK_NULL },
	{ "absmax", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRangeRealAttribute,m_absmax), HK_NULL },
	{ "softmin", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRangeRealAttribute,m_softmin), HK_NULL },
	{ "softmax", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRangeRealAttribute,m_softmax), HK_NULL }
};
extern const hkClass hkRangeRealAttributeClass;
const hkClass hkRangeRealAttributeClass(
	"hkRangeRealAttribute",
	HK_NULL, // parent
	sizeof(hkRangeRealAttribute),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkRangeRealAttributeClass_Members),
	HK_COUNT_OF(hkRangeRealAttributeClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkRangeInt32Attribute
//
HK_REFLECTION_DEFINE_SIMPLE(hkRangeInt32Attribute);
static const hkInternalClassMember hkRangeInt32AttributeClass_Members[] =
{
	{ "absmin", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRangeInt32Attribute,m_absmin), HK_NULL },
	{ "absmax", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRangeInt32Attribute,m_absmax), HK_NULL },
	{ "softmin", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRangeInt32Attribute,m_softmin), HK_NULL },
	{ "softmax", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRangeInt32Attribute,m_softmax), HK_NULL }
};
extern const hkClass hkRangeInt32AttributeClass;
const hkClass hkRangeInt32AttributeClass(
	"hkRangeInt32Attribute",
	HK_NULL, // parent
	sizeof(hkRangeInt32Attribute),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkRangeInt32AttributeClass_Members),
	HK_COUNT_OF(hkRangeInt32AttributeClass_Members),
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
