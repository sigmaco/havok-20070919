/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>



//
// Enum hkMultiThreadCheck::AccessType
//
static const hkInternalClassEnumItem hkMultiThreadCheckAccessTypeEnumItems[] =
{
	{0, "HK_ACCESS_IGNORE"},
	{1, "HK_ACCESS_RO"},
	{2, "HK_ACCESS_RW"},
};

//
// Enum hkMultiThreadCheck::ReadMode
//
static const hkInternalClassEnumItem hkMultiThreadCheckReadModeEnumItems[] =
{
	{0, "THIS_OBJECT_ONLY"},
	{1, "RECURSIVE"},
};
static const hkInternalClassEnum hkMultiThreadCheckEnums[] = {
	{"AccessType", hkMultiThreadCheckAccessTypeEnumItems, 3, HK_NULL, 0 },
	{"ReadMode", hkMultiThreadCheckReadModeEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* hkMultiThreadCheckAccessTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkMultiThreadCheckEnums[0]);
extern const hkClassEnum* hkMultiThreadCheckReadModeEnum = reinterpret_cast<const hkClassEnum*>(&hkMultiThreadCheckEnums[1]);

//
// Class hkMultiThreadCheck
//
HK_REFLECTION_DEFINE_SIMPLE(hkMultiThreadCheck);
const hkInternalClassMember hkMultiThreadCheck::Members[] =
{
	{ "threadId", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkMultiThreadCheck,m_threadId), HK_NULL },
	{ "markCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkMultiThreadCheck,m_markCount), HK_NULL },
	{ "markBitStack", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkMultiThreadCheck,m_markBitStack), HK_NULL }
};
extern const hkClass hkMultiThreadCheckClass;
const hkClass hkMultiThreadCheckClass(
	"hkMultiThreadCheck",
	HK_NULL, // parent
	sizeof(hkMultiThreadCheck),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkMultiThreadCheckEnums),
	2, // enums
	reinterpret_cast<const hkClassMember*>(hkMultiThreadCheck::Members),
	HK_COUNT_OF(hkMultiThreadCheck::Members),
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
