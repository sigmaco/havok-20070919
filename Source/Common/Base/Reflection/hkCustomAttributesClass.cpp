/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Base/Reflection/hkCustomAttributes.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Base/Reflection/hkCustomAttributes.h>



// External pointer and enum types
extern const hkClass hkCustomAttributesAttributeClass;

//
// Class hkCustomAttributes::Attribute
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkCustomAttributes,Attribute);
static const hkInternalClassMember hkCustomAttributes_AttributeClass_Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkCustomAttributes::Attribute,m_name), HK_NULL },
	{ "value", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkCustomAttributes::Attribute,m_value), HK_NULL }
};
const hkClass hkCustomAttributesAttributeClass(
	"hkCustomAttributesAttribute",
	HK_NULL, // parent
	sizeof(hkCustomAttributes::Attribute),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkCustomAttributes_AttributeClass_Members),
	HK_COUNT_OF(hkCustomAttributes_AttributeClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkCustomAttributes
//
HK_REFLECTION_DEFINE_SIMPLE(hkCustomAttributes);
const hkInternalClassMember hkCustomAttributes::Members[] =
{
	{ "attributes", &hkCustomAttributesAttributeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkCustomAttributes,m_attributes), HK_NULL }
};
extern const hkClass hkCustomAttributesClass;
const hkClass hkCustomAttributesClass(
	"hkCustomAttributes",
	HK_NULL, // parent
	sizeof(hkCustomAttributes),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkCustomAttributes::Members),
	HK_COUNT_OF(hkCustomAttributes::Members),
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
