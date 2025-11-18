/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/ConstraintSolver/Constraint/Contact/hkpSimpleContactConstraintInfo.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/ConstraintSolver/Constraint/Contact/hkpSimpleContactConstraintInfo.h>
HK_REFLECTION_CLASSFILE_HEADER("Physics/ConstraintSolver/Constraint/Contact/hkpSimpleContactConstraintInfo.h");



//
// Class hkpSimpleContactConstraintDataInfo
//
HK_REFLECTION_DEFINE_NONVIRTUAL(hkpSimpleContactConstraintDataInfo);
static const hkInternalClassMember hkpSimpleContactConstraintDataInfoClass_Members[] =
{
	{ "flags", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::ALIGN_16, HK_OFFSET_OF(hkpSimpleContactConstraintDataInfo,m_flags), HK_NULL },
	{ "index", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimpleContactConstraintDataInfo,m_index), HK_NULL },
	{ "data", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 7, 0, HK_OFFSET_OF(hkpSimpleContactConstraintDataInfo,m_data), HK_NULL }
};
extern const hkClass hkpSimpleContactConstraintDataInfoClass;
const hkClass hkpSimpleContactConstraintDataInfoClass(
	"hkpSimpleContactConstraintDataInfo",
	HK_NULL, // parent
	sizeof(hkpSimpleContactConstraintDataInfo),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpSimpleContactConstraintDataInfoClass_Members),
	HK_COUNT_OF(hkpSimpleContactConstraintDataInfoClass_Members),
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
