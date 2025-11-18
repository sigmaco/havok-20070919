/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'ContentTools/Common/Filters/FilterPhysics/OptimizeShapeHierarchy/hctOptimizeShapeHierarchyOptions.h'
#include <ContentTools/Common/Filters/FilterPhysics/hctFilterPhysics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <ContentTools/Common/Filters/FilterPhysics/OptimizeShapeHierarchy/hctOptimizeShapeHierarchyOptions.h>



//
// Enum hctOptimizeShapeHierarchyOptions::CollapseBehaviourOptionsType
//
static const hkInternalClassEnumItem hctOptimizeShapeHierarchyOptionsCollapseBehaviourOptionsTypeEnumItems[] =
{
	{0, "COLLAPSE_OPTIONS_INVALID"},
	{1, "COLLAPSE_OPTIONS_ALWAYS"},
	{2, "COLLAPSE_OPTIONS_NEVER"},
	{3, "COLLAPSE_OPTIONS_THRESHOLD"},
	{4, "COLLAPSE_OPTIONS_MAX_ID"},
};
static const hkInternalClassEnum hctOptimizeShapeHierarchyOptionsEnums[] = {
	{"CollapseBehaviourOptionsType", hctOptimizeShapeHierarchyOptionsCollapseBehaviourOptionsTypeEnumItems, 5, HK_NULL, 0 }
};
extern const hkClassEnum* hctOptimizeShapeHierarchyOptionsCollapseBehaviourOptionsTypeEnum = reinterpret_cast<const hkClassEnum*>(&hctOptimizeShapeHierarchyOptionsEnums[0]);

//
// Class hctOptimizeShapeHierarchyOptions
//
HK_REFLECTION_DEFINE_SIMPLE(hctOptimizeShapeHierarchyOptions);
static const hkInternalClassMember hctOptimizeShapeHierarchyOptionsClass_Members[] =
{
	{ "shareShapes", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctOptimizeShapeHierarchyOptions,m_shareShapes), HK_NULL },
	{ "collapseTransforms", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctOptimizeShapeHierarchyOptions,m_collapseTransforms), HK_NULL },
	{ "shareTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctOptimizeShapeHierarchyOptions,m_shareTolerance), HK_NULL },
	{ "collapseBehaviourType", HK_NULL, hctOptimizeShapeHierarchyOptionsCollapseBehaviourOptionsTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hctOptimizeShapeHierarchyOptions,m_collapseBehaviourType), HK_NULL },
	{ "collapseThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctOptimizeShapeHierarchyOptions,m_collapseThreshold), HK_NULL },
	{ "propagate", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctOptimizeShapeHierarchyOptions,m_propagate), HK_NULL },
	{ "permuteDetect", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctOptimizeShapeHierarchyOptions,m_permuteDetect), HK_NULL }
};
extern const hkClass hctOptimizeShapeHierarchyOptionsClass;
const hkClass hctOptimizeShapeHierarchyOptionsClass(
	"hctOptimizeShapeHierarchyOptions",
	HK_NULL, // parent
	sizeof(hctOptimizeShapeHierarchyOptions),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hctOptimizeShapeHierarchyOptionsEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hctOptimizeShapeHierarchyOptionsClass_Members),
	HK_COUNT_OF(hctOptimizeShapeHierarchyOptionsClass_Members),
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
