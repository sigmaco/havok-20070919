/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Serialize/UnitTest/Roundtrip/RoundTrip.h'
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/UnitTest/Roundtrip/RoundTrip.h>



//
// Enum hkRoundTrip::FlagBits
//
static const hkInternalClassEnumItem hkRoundTripFlagBitsEnumItems[] =
{
	{1, "BIT_X"},
	{2, "BIT_Y"},
	{4, "BIT_Z"},
	{5, "BIT_XZ"},
};
static const hkInternalClassEnum hkRoundTripEnums[] = {
	{"FlagBits", hkRoundTripFlagBitsEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* hkRoundTripFlagBitsEnum = reinterpret_cast<const hkClassEnum*>(&hkRoundTripEnums[0]);

//
// Class hkRoundTrip
//
HK_REFLECTION_DEFINE_SIMPLE(hkRoundTrip);
static const hkInternalClassMember hkRoundTripClass_Members[] =
{
	{ "flags0", HK_NULL, hkRoundTripFlagBitsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(hkRoundTrip,m_flags0), HK_NULL },
	{ "flags1", HK_NULL, hkRoundTripFlagBitsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(hkRoundTrip,m_flags1), HK_NULL },
	{ "flags2", HK_NULL, hkRoundTripFlagBitsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(hkRoundTrip,m_flags2), HK_NULL },
	{ "flags3", HK_NULL, hkRoundTripFlagBitsEnum, hkClassMember::TYPE_FLAGS, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(hkRoundTrip,m_flags3), HK_NULL }
};
extern const hkClass hkRoundTripClass;
const hkClass hkRoundTripClass(
	"hkRoundTrip",
	HK_NULL, // parent
	sizeof(hkRoundTrip),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkRoundTripEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkRoundTripClass_Members),
	HK_COUNT_OF(hkRoundTripClass_Members),
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
