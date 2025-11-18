/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'ContentTools/Common/SceneExport/AttributeSelection/hctAttributeSelection.h'
#include <ContentTools/Common/SceneExport/hctSceneExport.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <ContentTools/Common/SceneExport/AttributeSelection/hctAttributeSelection.h>



// External pointer and enum types
extern const hkClass hctAttributeSelectionClass;

//
// Class hctAttributeSelectionDatabase
//
HK_REFLECTION_DEFINE_SIMPLE(hctAttributeSelectionDatabase);
static const hkInternalClassMember hctAttributeSelectionDatabaseClass_Members[] =
{
	{ "attributeAdditions", &hctAttributeSelectionClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hctAttributeSelectionDatabase,m_attributeAdditions), HK_NULL },
	{ "attributeRemovals", &hctAttributeSelectionClass, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hctAttributeSelectionDatabase,m_attributeRemovals), HK_NULL }
};
extern const hkClass hctAttributeSelectionDatabaseClass;
const hkClass hctAttributeSelectionDatabaseClass(
	"hctAttributeSelectionDatabase",
	HK_NULL, // parent
	sizeof(hctAttributeSelectionDatabase),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hctAttributeSelectionDatabaseClass_Members),
	HK_COUNT_OF(hctAttributeSelectionDatabaseClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hctAttributeSelection
//
HK_REFLECTION_DEFINE_SIMPLE(hctAttributeSelection);
static const hkInternalClassMember hctAttributeSelectionClass_Members[] =
{
	{ "typeName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctAttributeSelection,m_typeName), HK_NULL },
	{ "subTypeName", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctAttributeSelection,m_subTypeName), HK_NULL },
	{ "attributeNames", HK_NULL, HK_NULL, hkClassMember::TYPE_SIMPLEARRAY, hkClassMember::TYPE_CSTRING, 0, 0, HK_OFFSET_OF(hctAttributeSelection,m_attributeNames), HK_NULL }
};
const hkClass hctAttributeSelectionClass(
	"hctAttributeSelection",
	HK_NULL, // parent
	sizeof(hctAttributeSelection),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hctAttributeSelectionClass_Members),
	HK_COUNT_OF(hctAttributeSelectionClass_Members),
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
