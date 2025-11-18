/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Utilities/Dynamics/SaveContactPoints/hkpSerializedAgentNnEntry.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Utilities/Dynamics/SaveContactPoints/hkpSerializedAgentNnEntry.h>



// External pointer and enum types
extern const hkClass hkContactPointClass;
extern const hkClass hkpAgent1nSectorClass;
extern const hkClass hkpEntityClass;
extern const hkClass hkpSerializedSubTrack1nInfoClass;
extern const hkClass hkpSerializedTrack1nInfoClass;
extern const hkClass hkpSimpleContactConstraintAtomClass;

//
// Class hkpSerializedTrack1nInfo
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpSerializedTrack1nInfo);
static const hkInternalClassMember hkpSerializedTrack1nInfoClass_Members[] =
{
	{ "sectors", &hkpAgent1nSectorClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpSerializedTrack1nInfo,m_sectors), HK_NULL },
	{ "subTracks", &hkpSerializedSubTrack1nInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpSerializedTrack1nInfo,m_subTracks), HK_NULL }
};
const hkClass hkpSerializedTrack1nInfoClass(
	"hkpSerializedTrack1nInfo",
	HK_NULL, // parent
	sizeof(hkpSerializedTrack1nInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSerializedTrack1nInfoClass_Members),
	HK_COUNT_OF(hkpSerializedTrack1nInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpSerializedSubTrack1nInfo
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpSerializedSubTrack1nInfo);
static const hkInternalClassMember hkpSerializedSubTrack1nInfoClass_Members[] =
{
	{ "sectorIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedSubTrack1nInfo,m_sectorIndex), HK_NULL },
	{ "offsetInSector", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedSubTrack1nInfo,m_offsetInSector), HK_NULL }
};

const hkClass hkpSerializedSubTrack1nInfoClass(
	"hkpSerializedSubTrack1nInfo",
	&hkpSerializedTrack1nInfoClass, // parent
	sizeof(hkpSerializedSubTrack1nInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSerializedSubTrack1nInfoClass_Members),
	HK_COUNT_OF(hkpSerializedSubTrack1nInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Enum hkpSerializedAgentNnEntry::SerializedAgentType
//
static const hkInternalClassEnumItem hkpSerializedAgentNnEntrySerializedAgentTypeEnumItems[] =
{
	{0, "INVALID_AGENT_TYPE"},
	{1, "BOX_BOX_AGENT3"},
	{2, "CAPSULE_TRIANGLE_AGENT3"},
	{3, "PRED_GSK_AGENT3"},
	{4, "PRED_GSK_CYLINDER_AGENT3"},
	{5, "CONVEX_LIST_AGENT3"},
	{6, "LIST_AGENT3"},
	{7, "BV_TREE_AGENT3"},
	{8, "COLLECTION_COLLECTION_AGENT3"},
};
static const hkInternalClassEnum hkpSerializedAgentNnEntryEnums[] = {
	{"SerializedAgentType", hkpSerializedAgentNnEntrySerializedAgentTypeEnumItems, 9, HK_NULL, 0 }
};
extern const hkClassEnum* hkpSerializedAgentNnEntrySerializedAgentTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpSerializedAgentNnEntryEnums[0]);

//
// Class hkpSerializedAgentNnEntry
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpSerializedAgentNnEntry);
static const hkInternalClassMember hkpSerializedAgentNnEntryClass_Members[] =
{
	{ "bodyA", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_bodyA), HK_NULL },
	{ "bodyB", &hkpEntityClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_bodyB), HK_NULL },
	{ "bodyAId", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_bodyAId), HK_NULL },
	{ "bodyBId", HK_NULL, HK_NULL, hkClassMember::TYPE_ULONG, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_bodyBId), HK_NULL },
	{ "useEntityIds", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_useEntityIds), HK_NULL },
	{ "agentType", HK_NULL, hkpSerializedAgentNnEntrySerializedAgentTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_agentType), HK_NULL },
	{ "atom", &hkpSimpleContactConstraintAtomClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_atom), HK_NULL },
	{ "propertiesStream", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_propertiesStream), HK_NULL },
	{ "contactPoints", &hkContactPointClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_contactPoints), HK_NULL },
	{ "cpIdMgr", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_cpIdMgr), HK_NULL },
	{ "nnEntryData", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, HK_AGENT3_AGENT_SIZE, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_nnEntryData), HK_NULL },
	{ "trackInfo", &hkpSerializedTrack1nInfoClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_trackInfo), HK_NULL },
	{ "endianCheckBuffer", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 4, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_endianCheckBuffer), HK_NULL },
	{ "version", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSerializedAgentNnEntry,m_version), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpSerializedAgentNnEntryClass;
const hkClass hkpSerializedAgentNnEntryClass(
	"hkpSerializedAgentNnEntry",
	&hkReferencedObjectClass, // parent
	sizeof(hkpSerializedAgentNnEntry),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpSerializedAgentNnEntryEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hkpSerializedAgentNnEntryClass_Members),
	HK_COUNT_OF(hkpSerializedAgentNnEntryClass_Members),
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
