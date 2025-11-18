/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/World/Simulation/hkpSimulation.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/World/Simulation/hkpSimulation.h>


//
// Global
//

//
// Enum ::hkpStepResult
//
static const hkInternalClassEnumItem Physics_Dynamics_World_Simulation_hkpSimulationhkpStepResultEnumItems[] =
{
	{0, "HK_STEP_RESULT_SUCCESS"},
	{1, "HK_STEP_RESULT_MEMORY_FAILURE_BEFORE_INTEGRATION"},
	{2, "HK_STEP_RESULT_MEMORY_FAILURE_DURING_COLLIDE"},
	{3, "HK_STEP_RESULT_MEMORY_FAILURE_DURING_TOI_SOLVE"},
};
static const hkInternalClassEnum Physics_Dynamics_World_Simulation_hkpSimulationEnums[] = {
	{"hkpStepResult", Physics_Dynamics_World_Simulation_hkpSimulationhkpStepResultEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* hkpStepResultEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_Simulation_hkpSimulationEnums[0]);

// External pointer and enum types
extern const hkClass hkpWorldClass;

//
// Enum hkpSimulation::FindContacts
//
static const hkInternalClassEnumItem hkpSimulationFindContactsEnumItems[] =
{
	{0, "FIND_CONTACTS_DEFAULT"},
	{1, "FIND_CONTACTS_EXTRA"},
};

//
// Enum hkpSimulation::LastProcessingStep
//
static const hkInternalClassEnumItem hkpSimulationLastProcessingStepEnumItems[] =
{
	{0, "INTEGRATE"},
	{1, "COLLIDE"},
};
static const hkInternalClassEnum hkpSimulationEnums[] = {
	{"FindContacts", hkpSimulationFindContactsEnumItems, 2, HK_NULL, 0 },
	{"LastProcessingStep", hkpSimulationLastProcessingStepEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* hkpSimulationFindContactsEnum = reinterpret_cast<const hkClassEnum*>(&hkpSimulationEnums[0]);
extern const hkClassEnum* hkpSimulationLastProcessingStepEnum = reinterpret_cast<const hkClassEnum*>(&hkpSimulationEnums[1]);

//
// Class hkpSimulation
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpSimulation);
const hkInternalClassMember hkpSimulation::Members[] =
{
	{ "world", &hkpWorldClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpSimulation,m_world), HK_NULL },
	{ "lastProcessingStep", HK_NULL, hkpSimulationLastProcessingStepEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpSimulation,m_lastProcessingStep), HK_NULL },
	{ "currentTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimulation,m_currentTime), HK_NULL },
	{ "currentPsiTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimulation,m_currentPsiTime), HK_NULL },
	{ "physicsDeltaTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimulation,m_physicsDeltaTime), HK_NULL },
	{ "simulateUntilTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimulation,m_simulateUntilTime), HK_NULL },
	{ "frameMarkerPsiSnap", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpSimulation,m_frameMarkerPsiSnap), HK_NULL },
	{ "previousStepResult", HK_NULL, hkpStepResultEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_UINT8, 0, 0, HK_OFFSET_OF(hkpSimulation,m_previousStepResult), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpSimulationClass;
const hkClass hkpSimulationClass(
	"hkpSimulation",
	&hkReferencedObjectClass, // parent
	sizeof(hkpSimulation),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpSimulationEnums),
	2, // enums
	reinterpret_cast<const hkClassMember*>(hkpSimulation::Members),
	HK_COUNT_OF(hkpSimulation::Members),
	HK_NULL, // defaults
	HK_NULL, // attributes
	hkClass::FLAGS_NOT_SERIALIZABLE
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
