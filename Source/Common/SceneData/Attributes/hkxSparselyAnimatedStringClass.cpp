/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Attributes/hkxSparselyAnimatedString.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Attributes/hkxSparselyAnimatedString.h>



// External pointer and enum types
extern const hkClass hkxSparselyAnimatedStringStringTypeClass;

//
// Class hkxSparselyAnimatedString::StringType
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkxSparselyAnimatedString,StringType);
static const hkInternalClassMember hkxSparselyAnimatedString_StringTypeClass_Members[] =
{
	{ "string", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkxSparselyAnimatedString::StringType,m_string), HK_NULL }
};
const hkClass hkxSparselyAnimatedStringStringTypeClass(
	"hkxSparselyAnimatedStringStringType",
	HK_NULL, // parent
	sizeof(hkxSparselyAnimatedString::StringType),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkxSparselyAnimatedString_StringTypeClass_Members),
	HK_COUNT_OF(hkxSparselyAnimatedString_StringTypeClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkxSparselyAnimatedString
//
HK_REFLECTION_DEFINE_SIMPLE(hkxSparselyAnimatedString);
static const hkInternalClassMember hkxSparselyAnimatedStringClass_Members[] =
{
	{ "strings", &hkxSparselyAnimatedStringStringTypeClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkxSparselyAnimatedString,m_strings), HK_NULL },
	{ "times", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, HK_OFFSET_OF(hkxSparselyAnimatedString,m_times), HK_NULL }
};
extern const hkClass hkxSparselyAnimatedStringClass;
const hkClass hkxSparselyAnimatedStringClass(
	"hkxSparselyAnimatedString",
	HK_NULL, // parent
	sizeof(hkxSparselyAnimatedString),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkxSparselyAnimatedStringClass_Members),
	HK_COUNT_OF(hkxSparselyAnimatedStringClass_Members),
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
