/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Serialize/Packfile/Binary/hkPackfileHeader.h'
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/Packfile/Binary/hkPackfileHeader.h>



//
// Class hkPackfileHeader
//
HK_REFLECTION_DEFINE_SIMPLE(hkPackfileHeader);
static const hkInternalClassMember hkPackfileHeaderClass_Members[] =
{
	{ "magic", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkPackfileHeader,m_magic), HK_NULL },
	{ "userTag", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkPackfileHeader,m_userTag), HK_NULL },
	{ "fileVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkPackfileHeader,m_fileVersion), HK_NULL },
	{ "layoutRules", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, HK_OFFSET_OF(hkPackfileHeader,m_layoutRules), HK_NULL },
	{ "numSections", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkPackfileHeader,m_numSections), HK_NULL },
	{ "contentsSectionIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkPackfileHeader,m_contentsSectionIndex), HK_NULL },
	{ "contentsSectionOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkPackfileHeader,m_contentsSectionOffset), HK_NULL },
	{ "contentsClassNameSectionIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkPackfileHeader,m_contentsClassNameSectionIndex), HK_NULL },
	{ "contentsClassNameSectionOffset", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkPackfileHeader,m_contentsClassNameSectionOffset), HK_NULL },
	{ "contentsVersion", HK_NULL, HK_NULL, hkClassMember::TYPE_CHAR, hkClassMember::TYPE_VOID, 16, 0, HK_OFFSET_OF(hkPackfileHeader,m_contentsVersion), HK_NULL },
	{ "pad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkPackfileHeader,m_pad), HK_NULL }
};
extern const hkClass hkPackfileHeaderClass;
const hkClass hkPackfileHeaderClass(
	"hkPackfileHeader",
	HK_NULL, // parent
	sizeof(hkPackfileHeader),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkPackfileHeaderClass_Members),
	HK_COUNT_OF(hkPackfileHeaderClass_Members),
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
