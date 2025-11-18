/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/SceneData/Attributes/hkxSparselyAnimatedBool.h'
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/SceneData/Attributes/hkxSparselyAnimatedBool.h>



//
// Class hkxSparselyAnimatedBool
//
HK_REFLECTION_DEFINE_SIMPLE(hkxSparselyAnimatedBool);
static const hkInternalClassMember hkxSparselyAnimatedBoolClass_Members[] =
{
	{ "bools", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_BOOL, 0, 0, HK_OFFSET_OF(hkxSparselyAnimatedBool,m_bools), HK_NULL },
	{ "times", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_REAL, 0, 0, HK_OFFSET_OF(hkxSparselyAnimatedBool,m_times), HK_NULL }
};
extern const hkClass hkxSparselyAnimatedBoolClass;
const hkClass hkxSparselyAnimatedBoolClass(
	"hkxSparselyAnimatedBool",
	HK_NULL, // parent
	sizeof(hkxSparselyAnimatedBool),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkxSparselyAnimatedBoolClass_Members),
	HK_COUNT_OF(hkxSparselyAnimatedBoolClass_Members),
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
