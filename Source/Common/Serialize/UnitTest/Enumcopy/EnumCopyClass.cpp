/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Serialize/UnitTest/Enumcopy/EnumCopy.h'
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/UnitTest/Enumcopy/EnumCopy.h>



//
// Enum Original::Value
//
static const hkInternalClassEnumItem OriginalValueEnumItems[] =
{
	{1, "VALUE_FIRST"},
	{2, "VALUE_SECOND"},
	{3, "VALUE_THIRD"},
	{4, "VALUE_ONLY_IN_ORIGINAL"},
};
static const hkInternalClassEnum OriginalEnums[] = {
	{"Value", OriginalValueEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* OriginalValueEnum = reinterpret_cast<const hkClassEnum*>(&OriginalEnums[0]);

//
// Class Original
//
HK_REFLECTION_DEFINE_SIMPLE(Original);
static const hkInternalClassMember OriginalClass_Members[] =
{
	{ "value8", HK_NULL, OriginalValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(Original,m_value8), HK_NULL },
	{ "value16", HK_NULL, OriginalValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT16, 0, 0, HK_OFFSET_OF(Original,m_value16), HK_NULL },
	{ "value32", HK_NULL, OriginalValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(Original,m_value32), HK_NULL },
	{ "valueBad0", HK_NULL, OriginalValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(Original,m_valueBad0), HK_NULL },
	{ "valueBad1", HK_NULL, OriginalValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(Original,m_valueBad1), HK_NULL }
};
extern const hkClass OriginalClass;
const hkClass OriginalClass(
	"Original",
	HK_NULL, // parent
	sizeof(Original),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(OriginalEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(OriginalClass_Members),
	HK_COUNT_OF(OriginalClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Enum Modified::Value
//
static const hkInternalClassEnumItem ModifiedValueEnumItems[] =
{
	{111, "VALUE_FIRST"},
	{156, "VALUE_SECOND"},
	{123, "VALUE_THIRD"},
	{99, "VALUE_ONLY_IN_MODIFIED"},
};
static const hkInternalClassEnum ModifiedEnums[] = {
	{"Value", ModifiedValueEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* ModifiedValueEnum = reinterpret_cast<const hkClassEnum*>(&ModifiedEnums[0]);

//
// Class Modified
//
HK_REFLECTION_DEFINE_SIMPLE(Modified);
static const hkInternalClassMember ModifiedClass_Members[] =
{
	{ "padpad", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 10, 0, HK_OFFSET_OF(Modified,m_padpad), HK_NULL },
	{ "value8", HK_NULL, ModifiedValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(Modified,m_value8), HK_NULL },
	{ "value16", HK_NULL, ModifiedValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT16, 0, 0, HK_OFFSET_OF(Modified,m_value16), HK_NULL },
	{ "value32", HK_NULL, ModifiedValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(Modified,m_value32), HK_NULL },
	{ "valueBad0", HK_NULL, ModifiedValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(Modified,m_valueBad0), HK_NULL },
	{ "valueBad1", HK_NULL, ModifiedValueEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(Modified,m_valueBad1), HK_NULL }
};
extern const hkClass ModifiedClass;
const hkClass ModifiedClass(
	"Modified",
	HK_NULL, // parent
	sizeof(Modified),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(ModifiedEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(ModifiedClass_Members),
	HK_COUNT_OF(ModifiedClass_Members),
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
