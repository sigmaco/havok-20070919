/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Common/Serialize/UnitTest/Parser/HeaderParser.h'
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Serialize/UnitTest/Parser/HeaderParser.h>



// External pointer and enum types
extern const hkClass HeaderParserintClass;

//
// Enum HeaderParser::NestedEnum
//
static const hkInternalClassEnumItem HeaderParserNestedEnumEnumItems[] =
{
	{0, "VALUE_ZERO"},
};
static const hkInternalClassEnum HeaderParserEnums[] = {
	{"NestedEnum", HeaderParserNestedEnumEnumItems, 1, HK_NULL, 0 }
};
extern const hkClassEnum* HeaderParserNestedEnumEnum = reinterpret_cast<const hkClassEnum*>(&HeaderParserEnums[0]);

//
// Class HeaderParser
//
HK_REFLECTION_DEFINE_SIMPLE(HeaderParser);
static const hkInternalClassMember HeaderParserClass_Members[] =
{
	{ "charBuf", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(HeaderParser,m_charBuf), HK_NULL },
	{ "vertices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_INT32, 0, 0, HK_OFFSET_OF(HeaderParser,m_vertices), HK_NULL },
	{ "noSaveVertices", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(HeaderParser,m_noSaveVertices), HK_NULL },
	{ "enum", HK_NULL, HeaderParserNestedEnumEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(HeaderParser,m_enum), HK_NULL }
};
extern const hkClass HeaderParserClass;
const hkClass HeaderParserClass(
	"HeaderParser",
	HK_NULL, // parent
	sizeof(HeaderParser),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(HeaderParserEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(HeaderParserClass_Members),
	HK_COUNT_OF(HeaderParserClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Enum HeaderParser2::NestedEnum
//
static const hkInternalClassEnumItem HeaderParser2NestedEnumEnumItems[] =
{
	{0, "VALUE_ZERO"},
};
static const hkInternalClassEnum HeaderParser2Enums[] = {
	{"NestedEnum", HeaderParser2NestedEnumEnumItems, 1, HK_NULL, 0 }
};
extern const hkClassEnum* HeaderParser2NestedEnumEnum = reinterpret_cast<const hkClassEnum*>(&HeaderParser2Enums[0]);

//
// Class HeaderParser2
//
HK_REFLECTION_DEFINE_SIMPLE(HeaderParser2);
static const hkInternalClassMember HeaderParser2Class_Members[] =
{
	{ "enum2", HK_NULL, HeaderParser2NestedEnumEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(HeaderParser2,m_enum2), HK_NULL }
};
extern const hkClass HeaderParser2Class;
const hkClass HeaderParser2Class(
	"HeaderParser2",
	HK_NULL, // parent
	sizeof(HeaderParser2),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(HeaderParser2Enums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(HeaderParser2Class_Members),
	HK_COUNT_OF(HeaderParser2Class_Members),
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
