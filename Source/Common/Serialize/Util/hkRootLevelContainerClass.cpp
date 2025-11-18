/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Serialize/Util/hkRootLevelContainer.h'
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>



// External pointer and enum types
extern const hkClass hkRootLevelContainerNamedVariantClass;

//
// Class hkRootLevelContainer::NamedVariant
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkRootLevelContainer,NamedVariant);
const hkInternalClassMember hkRootLevelContainer::NamedVariant::Members[] =
{
	{ "name", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRootLevelContainer::NamedVariant,m_name), HK_NULL },
	{ "className", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRootLevelContainer::NamedVariant,m_className), HK_NULL },
	{ "variant", HK_NULL, HK_NULL, hkClassMember::TYPE_VARIANT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkRootLevelContainer::NamedVariant,m_variant), HK_NULL }
};
const hkClass hkRootLevelContainerNamedVariantClass(
	"hkRootLevelContainerNamedVariant",
	HK_NULL, // parent
	sizeof(hkRootLevelContainer::NamedVariant),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkRootLevelContainer::NamedVariant::Members),
	HK_COUNT_OF(hkRootLevelContainer::NamedVariant::Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkRootLevelContainer
//
HK_REFLECTION_DEFINE_SIMPLE(hkRootLevelContainer);
static const hkInternalClassMember hkRootLevelContainerClass_Members[] =
{
	{ "namedVariants", &hkRootLevelContainerNamedVariantClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkRootLevelContainer,m_namedVariants), HK_NULL }
};
extern const hkClass hkRootLevelContainerClass;
const hkClass hkRootLevelContainerClass(
	"hkRootLevelContainer",
	HK_NULL, // parent
	sizeof(hkRootLevelContainer),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkRootLevelContainerClass_Members),
	HK_COUNT_OF(hkRootLevelContainerClass_Members),
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
