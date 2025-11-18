/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Utilities/Constraint/Chain/hkpPoweredChainMapper.h'
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Utilities/Constraint/Chain/hkpPoweredChainMapper.h>



// External pointer and enum types
extern const hkClass hkpConstraintChainInstanceClass;
extern const hkClass hkpConstraintInstanceClass;
extern const hkClass hkpEntityClass;
extern const hkClass hkpPoweredChainDataClass;
extern const hkClass hkpPoweredChainMapperLinkInfoClass;
extern const hkClass hkpPoweredChainMapperTargetClass;

//
// Class hkpPoweredChainMapper::Target
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpPoweredChainMapper,Target);
static const hkInternalClassMember hkpPoweredChainMapper_TargetClass_Members[] =
{
	{ "chain", &hkpPoweredChainDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpPoweredChainMapper::Target,m_chain), HK_NULL },
	{ "infoIndex", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainMapper::Target,m_infoIndex), HK_NULL }
};
const hkClass hkpPoweredChainMapperTargetClass(
	"hkpPoweredChainMapperTarget",
	HK_NULL, // parent
	sizeof(hkpPoweredChainMapper::Target),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPoweredChainMapper_TargetClass_Members),
	HK_COUNT_OF(hkpPoweredChainMapper_TargetClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPoweredChainMapper::LinkInfo
//
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(hkpPoweredChainMapper,LinkInfo);
static const hkInternalClassMember hkpPoweredChainMapper_LinkInfoClass_Members[] =
{
	{ "firstTargetIdx", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainMapper::LinkInfo,m_firstTargetIdx), HK_NULL },
	{ "numTargets", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpPoweredChainMapper::LinkInfo,m_numTargets), HK_NULL },
	{ "limitConstraint", &hkpConstraintInstanceClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpPoweredChainMapper::LinkInfo,m_limitConstraint), HK_NULL }
};
const hkClass hkpPoweredChainMapperLinkInfoClass(
	"hkpPoweredChainMapperLinkInfo",
	HK_NULL, // parent
	sizeof(hkpPoweredChainMapper::LinkInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPoweredChainMapper_LinkInfoClass_Members),
	HK_COUNT_OF(hkpPoweredChainMapper_LinkInfoClass_Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	0
	);

//
// Class hkpPoweredChainMapper
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpPoweredChainMapper);
static const hkInternalClassMember hkpPoweredChainMapperClass_Members[] =
{
	{ "links", &hkpPoweredChainMapperLinkInfoClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpPoweredChainMapper,m_links), HK_NULL },
	{ "targets", &hkpPoweredChainMapperTargetClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpPoweredChainMapper,m_targets), HK_NULL },
	{ "chains", &hkpConstraintChainInstanceClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpPoweredChainMapper,m_chains), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpPoweredChainMapperClass;
const hkClass hkpPoweredChainMapperClass(
	"hkpPoweredChainMapper",
	&hkReferencedObjectClass, // parent
	sizeof(hkpPoweredChainMapper),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpPoweredChainMapperClass_Members),
	HK_COUNT_OF(hkpPoweredChainMapperClass_Members),
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
