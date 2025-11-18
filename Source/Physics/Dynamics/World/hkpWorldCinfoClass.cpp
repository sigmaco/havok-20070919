/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/World/hkpWorldCinfo.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/World/hkpWorldCinfo.h>



// External pointer and enum types
extern const hkClass hkAabbClass;
extern const hkClass hkWorldMemoryAvailableWatchDogClass;
extern const hkClass hkpCollisionFilterClass;
extern const hkClass hkpConvexListFilterClass;

//
// Enum hkpWorldCinfo::SolverType
//
static const hkInternalClassEnumItem hkpWorldCinfoSolverTypeEnumItems[] =
{
	{0, "SOLVER_TYPE_INVALID"},
	{1, "SOLVER_TYPE_2ITERS_SOFT"},
	{2, "SOLVER_TYPE_2ITERS_MEDIUM"},
	{3, "SOLVER_TYPE_2ITERS_HARD"},
	{4, "SOLVER_TYPE_4ITERS_SOFT"},
	{5, "SOLVER_TYPE_4ITERS_MEDIUM"},
	{6, "SOLVER_TYPE_4ITERS_HARD"},
	{7, "SOLVER_TYPE_8ITERS_SOFT"},
	{8, "SOLVER_TYPE_8ITERS_MEDIUM"},
	{9, "SOLVER_TYPE_8ITERS_HARD"},
	{10, "SOLVER_TYPE_MAX_ID"},
};

//
// Enum hkpWorldCinfo::SimulationType
//
static const hkInternalClassEnumItem hkpWorldCinfoSimulationTypeEnumItems[] =
{
	{0, "SIMULATION_TYPE_INVALID"},
	{1, "SIMULATION_TYPE_DISCRETE"},
	{2, "SIMULATION_TYPE_CONTINUOUS"},
	{3, "SIMULATION_TYPE_MULTITHREADED"},
};

//
// Enum hkpWorldCinfo::ContactPointGeneration
//
static const hkInternalClassEnumItem hkpWorldCinfoContactPointGenerationEnumItems[] =
{
	{0, "CONTACT_POINT_ACCEPT_ALWAYS"},
	{1, "CONTACT_POINT_REJECT_DUBIOUS"},
	{2, "CONTACT_POINT_REJECT_MANY"},
};

//
// Enum hkpWorldCinfo::BroadPhaseBorderBehaviour
//
static const hkInternalClassEnumItem hkpWorldCinfoBroadPhaseBorderBehaviourEnumItems[] =
{
	{0, "BROADPHASE_BORDER_ASSERT"},
	{1, "BROADPHASE_BORDER_FIX_ENTITY"},
	{2, "BROADPHASE_BORDER_REMOVE_ENTITY"},
	{3, "BROADPHASE_BORDER_DO_NOTHING"},
};
static const hkInternalClassEnum hkpWorldCinfoEnums[] = {
	{"SolverType", hkpWorldCinfoSolverTypeEnumItems, 11, HK_NULL, 0 },
	{"SimulationType", hkpWorldCinfoSimulationTypeEnumItems, 4, HK_NULL, 0 },
	{"ContactPointGeneration", hkpWorldCinfoContactPointGenerationEnumItems, 3, HK_NULL, 0 },
	{"BroadPhaseBorderBehaviour", hkpWorldCinfoBroadPhaseBorderBehaviourEnumItems, 4, HK_NULL, 0 }
};
extern const hkClassEnum* hkpWorldCinfoSolverTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldCinfoEnums[0]);
extern const hkClassEnum* hkpWorldCinfoSimulationTypeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldCinfoEnums[1]);
extern const hkClassEnum* hkpWorldCinfoContactPointGenerationEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldCinfoEnums[2]);
extern const hkClassEnum* hkpWorldCinfoBroadPhaseBorderBehaviourEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldCinfoEnums[3]);

//
// Class hkpWorldCinfo
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpWorldCinfo);
static const hkInternalClassMember hkpWorldCinfoClass_Members[] =
{
	{ "gravity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_gravity), HK_NULL },
	{ "broadPhaseQuerySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_broadPhaseQuerySize), HK_NULL },
	{ "contactRestingVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_contactRestingVelocity), HK_NULL },
	{ "broadPhaseBorderBehaviour", HK_NULL, hkpWorldCinfoBroadPhaseBorderBehaviourEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_broadPhaseBorderBehaviour), HK_NULL },
	{ "broadPhaseWorldAabb", &hkAabbClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_broadPhaseWorldAabb), HK_NULL },
	{ "collisionTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_collisionTolerance), HK_NULL },
	{ "collisionFilter", &hkpCollisionFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_collisionFilter), HK_NULL },
	{ "convexListFilter", &hkpConvexListFilterClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_convexListFilter), HK_NULL },
	{ "expectedMaxLinearVelocity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_expectedMaxLinearVelocity), HK_NULL },
	{ "sizeOfToiEventQueue", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_sizeOfToiEventQueue), HK_NULL },
	{ "expectedMinPsiDeltaTime", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_expectedMinPsiDeltaTime), HK_NULL },
	{ "memoryWatchDog", &hkWorldMemoryAvailableWatchDogClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_memoryWatchDog), HK_NULL },
	{ "broadPhaseNumMarkers", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_broadPhaseNumMarkers), HK_NULL },
	{ "contactPointGeneration", HK_NULL, hkpWorldCinfoContactPointGenerationEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_contactPointGeneration), HK_NULL },
	{ "solverTau", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_solverTau), HK_NULL },
	{ "solverDamp", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_solverDamp), HK_NULL },
	{ "solverIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_solverIterations), HK_NULL },
	{ "solverMicrosteps", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_solverMicrosteps), HK_NULL },
	{ "forceCoherentConstraintOrderingInSolver", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_forceCoherentConstraintOrderingInSolver), HK_NULL },
	{ "snapCollisionToConvexEdgeThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_snapCollisionToConvexEdgeThreshold), HK_NULL },
	{ "snapCollisionToConcaveEdgeThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_snapCollisionToConcaveEdgeThreshold), HK_NULL },
	{ "enableToiWeldRejection", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_enableToiWeldRejection), HK_NULL },
	{ "enableDeprecatedWelding", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_enableDeprecatedWelding), HK_NULL },
	{ "iterativeLinearCastEarlyOutDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_iterativeLinearCastEarlyOutDistance), HK_NULL },
	{ "iterativeLinearCastMaxIterations", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_iterativeLinearCastMaxIterations), HK_NULL },
	{ "highFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_highFrequencyDeactivationPeriod), HK_NULL },
	{ "lowFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_lowFrequencyDeactivationPeriod), HK_NULL },
	{ "deactivationNumInactiveFramesSelectFlag0", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_deactivationNumInactiveFramesSelectFlag0), HK_NULL },
	{ "deactivationNumInactiveFramesSelectFlag1", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_deactivationNumInactiveFramesSelectFlag1), HK_NULL },
	{ "deactivationIntegrateCounter", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_deactivationIntegrateCounter), HK_NULL },
	{ "shouldActivateOnRigidBodyTransformChange", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_shouldActivateOnRigidBodyTransformChange), HK_NULL },
	{ "deactivationReferenceDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_deactivationReferenceDistance), HK_NULL },
	{ "toiCollisionResponseRotateNormal", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_toiCollisionResponseRotateNormal), HK_NULL },
	{ "enableDeactivation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_enableDeactivation), HK_NULL },
	{ "simulationType", HK_NULL, hkpWorldCinfoSimulationTypeEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_simulationType), HK_NULL },
	{ "enableSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_enableSimulationIslands), HK_NULL },
	{ "minDesiredIslandSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_minDesiredIslandSize), HK_NULL },
	{ "processActionsInSingleThread", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_processActionsInSingleThread), HK_NULL },
	{ "frameMarkerPsiSnap", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorldCinfo,m_frameMarkerPsiSnap), HK_NULL }
};
namespace
{
	struct hkpWorldCinfo_DefaultStruct
	{
		int s_defaultOffsets[39];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		_hkVector4 m_gravity;
		hkInt32 m_broadPhaseQuerySize;
		hkReal m_collisionTolerance;
		hkReal m_expectedMaxLinearVelocity;
		int m_sizeOfToiEventQueue;
		hkReal m_expectedMinPsiDeltaTime;
		hkReal m_solverDamp;
		hkInt32 m_solverIterations;
		hkInt32 m_solverMicrosteps;
		hkReal m_snapCollisionToConvexEdgeThreshold;
		hkReal m_snapCollisionToConcaveEdgeThreshold;
		hkReal m_iterativeLinearCastEarlyOutDistance;
		hkInt32 m_iterativeLinearCastMaxIterations;
		hkReal m_highFrequencyDeactivationPeriod;
		hkReal m_lowFrequencyDeactivationPeriod;
		_hkBool m_shouldActivateOnRigidBodyTransformChange;
		hkReal m_deactivationReferenceDistance;
		hkReal m_toiCollisionResponseRotateNormal;
		_hkBool m_enableDeactivation;
		_hkBool m_enableSimulationIslands;
		hkUint32 m_minDesiredIslandSize;
		_hkBool m_processActionsInSingleThread;
		hkReal m_frameMarkerPsiSnap;
	};
	const hkpWorldCinfo_DefaultStruct hkpWorldCinfo_Default =
	{
		{HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_gravity),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_broadPhaseQuerySize),-1,-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_collisionTolerance),-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_expectedMaxLinearVelocity),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_sizeOfToiEventQueue),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_expectedMinPsiDeltaTime),-1,-1,-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_solverDamp),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_solverIterations),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_solverMicrosteps),-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_snapCollisionToConvexEdgeThreshold),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_snapCollisionToConcaveEdgeThreshold),-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_iterativeLinearCastEarlyOutDistance),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_iterativeLinearCastMaxIterations),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_highFrequencyDeactivationPeriod),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_lowFrequencyDeactivationPeriod),-1,-1,-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_shouldActivateOnRigidBodyTransformChange),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_deactivationReferenceDistance),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_toiCollisionResponseRotateNormal),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_enableDeactivation),-1,HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_enableSimulationIslands),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_minDesiredIslandSize),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_processActionsInSingleThread),HK_OFFSET_OF(hkpWorldCinfo_DefaultStruct,m_frameMarkerPsiSnap)},
		{0,-9.8f,0},1024,.1f,200,250,1.0f/30.0f,.6f,4,1,.524f,0.698f,.01f,20,.2f,10,true,0.02f,0.2f,true,true,64,true,.0001f
	};
}
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpWorldCinfoClass;
const hkClass hkpWorldCinfoClass(
	"hkpWorldCinfo",
	&hkReferencedObjectClass, // parent
	sizeof(hkpWorldCinfo),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpWorldCinfoEnums),
	4, // enums
	reinterpret_cast<const hkClassMember*>(hkpWorldCinfoClass_Members),
	HK_COUNT_OF(hkpWorldCinfoClass_Members),
	&hkpWorldCinfo_Default,
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
