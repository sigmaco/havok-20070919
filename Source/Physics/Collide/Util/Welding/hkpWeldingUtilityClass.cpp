/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Collide/Util/Welding/hkpWeldingUtility.h'
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Collide/Util/Welding/hkpWeldingUtility.h>



//
// Enum hkpWeldingUtility::WeldingType
//
static const hkInternalClassEnumItem hkpWeldingUtilityWeldingTypeEnumItems[] =
{
	{0, "WELDING_TYPE_ANTICLOCKWISE"},
	{4, "WELDING_TYPE_CLOCKWISE"},
	{5, "WELDING_TYPE_TWO_SIDED"},
	{6, "WELDING_TYPE_NONE"},
};

//
// Enum hkpWeldingUtility::SectorType
//
static const hkInternalClassEnumItem hkpWeldingUtilitySectorTypeEnumItems[] =
{
	{1, "ACCEPT_0"},
	{0, "SNAP_0"},
	{2, "REJECT"},
	{4, "SNAP_1"},
	{3, "ACCEPT_1"},
};

//
// Enum hkpWeldingUtility::NumAngles
//
static const hkInternalClassEnumItem hkpWeldingUtilityNumAnglesEnumItems[] =
{
	{31, "NUM_ANGLES"},
};
static const hkInternalClassEnum hkpWeldingUtilityEnums[] = {
	{"WeldingType", hkpWeldingUtilityWeldingTypeEnumItems, 4, HK_NULL, 0 },
	{"SectorType", hkpWeldingUtilitySectorTypeEnumItems, 5, HK_NULL, 0 },
	{"NumAngles", hkpWeldingUtilityNumAnglesEnumItems, 1, HK_NULL, 0 }
};
extern const hkClassEnum* hkpWeldingUtilityWeldingTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWeldingUtilityEnums[0]);
extern const hkClassEnum* hkpWeldingUtilitySectorTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWeldingUtilityEnums[1]);
extern const hkClassEnum* hkpWeldingUtilityNumAnglesEnum = reinterpret_cast<const hkClassEnum*>(&hkpWeldingUtilityEnums[2]);

//
// Class hkpWeldingUtility
//
HK_REFLECTION_DEFINE_SIMPLE(hkpWeldingUtility);
extern const hkClass hkpWeldingUtilityClass;
const hkClass hkpWeldingUtilityClass(
	"hkpWeldingUtility",
	HK_NULL, // parent
	sizeof(hkpWeldingUtility),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpWeldingUtilityEnums),
	3, // enums
	HK_NULL,
	0,
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
