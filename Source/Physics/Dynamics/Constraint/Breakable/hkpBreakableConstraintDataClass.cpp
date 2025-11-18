/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>



// External pointer and enum types
extern const hkClass hkpBreakableListenerClass;
extern const hkClass hkpBridgeAtomsClass;
extern const hkClass hkpConstraintDataClass;

//
// Class hkpBreakableConstraintData
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpBreakableConstraintData);
static const hkInternalClassMember hkpBreakableConstraintDataClass_Members[] =
{
	{ "atoms", &hkpBridgeAtomsClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBreakableConstraintData,m_atoms), HK_NULL },
	{ "constraintData", &hkpConstraintDataClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpBreakableConstraintData,m_constraintData), HK_NULL },
	{ "childRuntimeSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBreakableConstraintData,m_childRuntimeSize), HK_NULL },
	{ "childNumSolverResults", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT16, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBreakableConstraintData,m_childNumSolverResults), HK_NULL },
	{ "solverResultLimit", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBreakableConstraintData,m_solverResultLimit), HK_NULL },
	{ "removeWhenBroken", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBreakableConstraintData,m_removeWhenBroken), HK_NULL },
	{ "revertBackVelocityOnBreak", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpBreakableConstraintData,m_revertBackVelocityOnBreak), HK_NULL },
	{ "listener", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpBreakableConstraintData,m_listener), HK_NULL }
};

extern const hkClass hkpBreakableConstraintDataClass;
const hkClass hkpBreakableConstraintDataClass(
	"hkpBreakableConstraintData",
	&hkpConstraintDataClass, // parent
	sizeof(hkpBreakableConstraintData),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkpBreakableConstraintDataClass_Members),
	HK_COUNT_OF(hkpBreakableConstraintDataClass_Members),
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
