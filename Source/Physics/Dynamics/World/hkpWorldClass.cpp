/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Physics/Dynamics/World/hkpWorld.h'
#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Physics/Dynamics/World/hkpWorld.h>


//
// Global
//

//
// Enum ::hkpUpdateCollisionFilterOnWorldMode
//
static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpUpdateCollisionFilterOnWorldModeEnumItems[] =
{
	{0, "HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK"},
	{1, "HK_UPDATE_FILTER_ON_WORLD_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY"},
};

//
// Enum ::hkpUpdateCollisionFilterOnEntityMode
//
static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpUpdateCollisionFilterOnEntityModeEnumItems[] =
{
	{0, "HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK"},
	{1, "HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY"},
};

//
// Enum ::hkpEntityActivation
//
static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpEntityActivationEnumItems[] =
{
	{0, "HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE"},
	{1, "HK_ENTITY_ACTIVATION_DO_ACTIVATE"},
};

//
// Enum ::hkpUpdateCollectionFilterMode
//
static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpUpdateCollectionFilterModeEnumItems[] =
{
	{0, "HK_UPDATE_COLLECTION_FILTER_IGNORE_SHAPE_COLLECTIONS"},
	{1, "HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS"},
};

//
// Enum ::hkpThreadToken
//
static const hkInternalClassEnumItem Physics_Dynamics_World_hkpWorldhkpThreadTokenEnumItems[] =
{
	{0, "HK_THREAD_TOKEN_FIRST"},
	{1, "HK_THREAD_TOKEN_SECOND"},
	{2, "HK_THREAD_TOKEN_THIRD"},
	{3, "HK_THREAD_TOKEN_FORTH"},
	{4, "HK_THREAD_TOKEN_FIFTH"},
	{5, "HK_THREAD_TOKEN_SIXTH"},
};
static const hkInternalClassEnum Physics_Dynamics_World_hkpWorldEnums[] = {
	{"hkpUpdateCollisionFilterOnWorldMode", Physics_Dynamics_World_hkpWorldhkpUpdateCollisionFilterOnWorldModeEnumItems, 2, HK_NULL, 0 },
	{"hkpUpdateCollisionFilterOnEntityMode", Physics_Dynamics_World_hkpWorldhkpUpdateCollisionFilterOnEntityModeEnumItems, 2, HK_NULL, 0 },
	{"hkpEntityActivation", Physics_Dynamics_World_hkpWorldhkpEntityActivationEnumItems, 2, HK_NULL, 0 },
	{"hkpUpdateCollectionFilterMode", Physics_Dynamics_World_hkpWorldhkpUpdateCollectionFilterModeEnumItems, 2, HK_NULL, 0 },
	{"hkpThreadToken", Physics_Dynamics_World_hkpWorldhkpThreadTokenEnumItems, 6, HK_NULL, 0 }
};
extern const hkClassEnum* hkpUpdateCollisionFilterOnWorldModeEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[0]);
extern const hkClassEnum* hkpUpdateCollisionFilterOnEntityModeEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[1]);
extern const hkClassEnum* hkpEntityActivationEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[2]);
extern const hkClassEnum* hkpUpdateCollectionFilterModeEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[3]);
extern const hkClassEnum* hkpThreadTokenEnum = reinterpret_cast<const hkClassEnum*>(&Physics_Dynamics_World_hkpWorldEnums[4]);

// External pointer and enum types
extern const hkClass hkCriticalSectionClass;
extern const hkClass hkMultiThreadCheckClass;
extern const hkClass hkWorldMemoryAvailableWatchDogClass;
extern const hkClass hkpActionListenerClass;
extern const hkClass hkpBroadPhaseBorderClass;
extern const hkClass hkpBroadPhaseBorderListenerClass;
extern const hkClass hkpBroadPhaseClass;
extern const hkClass hkpCollisionDispatcherClass;
extern const hkClass hkpCollisionFilterClass;
extern const hkClass hkpCollisionListenerClass;
extern const hkClass hkpConstraintListenerClass;
extern const hkClass hkpContactImpulseLimitBreachedListenerClass;
extern const hkClass hkpConvexListFilterClass;
extern const hkClass hkpDebugInfoOnPendingOperationQueuesClass;
extern const hkClass hkpEntityEntityBroadPhaseListenerClass;
extern const hkClass hkpEntityListenerClass;
extern const hkClass hkpIslandActivationListenerClass;
extern const hkClass hkpIslandPostCollideListenerClass;
extern const hkClass hkpIslandPostIntegrateListenerClass;
extern const hkClass hkpMultithreadedSimulationJobDataClass;
extern const hkClass hkpPhantomBroadPhaseListenerClass;
extern const hkClass hkpPhantomClass;
extern const hkClass hkpPhantomListenerClass;
extern const hkClass hkpProcessCollisionInputClass;
extern const hkClass hkpRigidBodyClass;
extern const hkClass hkpSimulationClass;
extern const hkClass hkpSimulationIslandClass;
extern const hkClass hkpTypedBroadPhaseDispatcherClass;
extern const hkClass hkpWorldDeletionListenerClass;
extern const hkClass hkpWorldDynamicsStepInfoClass;
extern const hkClass hkpWorldMaintenanceMgrClass;
extern const hkClass hkpWorldOperationQueueClass;
extern const hkClass hkpWorldPostCollideListenerClass;
extern const hkClass hkpWorldPostIntegrateListenerClass;
extern const hkClass hkpWorldPostSimulationListenerClass;
extern const hkClassEnum* hkpWorldCinfoContactPointGenerationEnum;
extern const hkClassEnum* hkpWorldCinfoSimulationTypeEnum;

//
// Enum hkpWorld::ReintegrationRecollideMode
//
static const hkInternalClassEnumItem hkpWorldReintegrationRecollideModeEnumItems[] =
{
	{1, "RR_MODE_REINTEGRATE"},
	{2, "RR_MODE_RECOLLIDE_BROADPHASE"},
	{4, "RR_MODE_RECOLLIDE_NARROWPHASE"},
	{7, "RR_MODE_ALL"},
};

//
// Enum hkpWorld::MtAccessChecking
//
static const hkInternalClassEnumItem hkpWorldMtAccessCheckingEnumItems[] =
{
	{0, "MT_ACCESS_CHECKING_ENABLED"},
	{1, "MT_ACCESS_CHECKING_DISABLED"},
};
static const hkInternalClassEnum hkpWorldEnums[] = {
	{"ReintegrationRecollideMode", hkpWorldReintegrationRecollideModeEnumItems, 4, HK_NULL, 0 },
	{"MtAccessChecking", hkpWorldMtAccessCheckingEnumItems, 2, HK_NULL, 0 }
};
extern const hkClassEnum* hkpWorldReintegrationRecollideModeEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldEnums[0]);
extern const hkClassEnum* hkpWorldMtAccessCheckingEnum = reinterpret_cast<const hkClassEnum*>(&hkpWorldEnums[1]);

//
// Class hkpWorld
//
HK_REFLECTION_DEFINE_VIRTUAL(hkpWorld);
const hkInternalClassMember hkpWorld::Members[] =
{
	{ "simulation", &hkpSimulationClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpWorld,m_simulation), HK_NULL },
	{ "gravity", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_gravity), HK_NULL },
	{ "fixedIsland", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_fixedIsland), HK_NULL },
	{ "fixedRigidBody", &hkpRigidBodyClass, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_STRUCT, 0, 0, HK_OFFSET_OF(hkpWorld,m_fixedRigidBody), HK_NULL },
	{ "activeSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_activeSimulationIslands), HK_NULL },
	{ "inactiveSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_inactiveSimulationIslands), HK_NULL },
	{ "dirtySimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_dirtySimulationIslands), HK_NULL },
	{ "maintenanceMgr", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_maintenanceMgr), HK_NULL },
	{ "memoryWatchDog", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_memoryWatchDog), HK_NULL },
	{ "broadPhase", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_broadPhase), HK_NULL },
	{ "broadPhaseDispatcher", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_broadPhaseDispatcher), HK_NULL },
	{ "phantomBroadPhaseListener", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_phantomBroadPhaseListener), HK_NULL },
	{ "entityEntityBroadPhaseListener", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_entityEntityBroadPhaseListener), HK_NULL },
	{ "broadPhaseBorderListener", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_broadPhaseBorderListener), HK_NULL },
	{ "multithreadedSimulationJobData", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_multithreadedSimulationJobData), HK_NULL },
	{ "collisionInput", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_collisionInput), HK_NULL },
	{ "collisionFilter", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_collisionFilter), HK_NULL },
	{ "collisionDispatcher", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_collisionDispatcher), HK_NULL },
	{ "convexListFilter", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_convexListFilter), HK_NULL },
	{ "pendingOperations", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_pendingOperations), HK_NULL },
	{ "pendingOperationsCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_pendingOperationsCount), HK_NULL },
	{ "criticalOperationsLockCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_criticalOperationsLockCount), HK_NULL },
	{ "criticalOperationsLockCountForPhantoms", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_criticalOperationsLockCountForPhantoms), HK_NULL },
	{ "blockExecutingPendingOperations", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_blockExecutingPendingOperations), HK_NULL },
	{ "criticalOperationsAllowed", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_criticalOperationsAllowed), HK_NULL },
	{ "pendingOperationQueues", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_pendingOperationQueues), HK_NULL },
	{ "pendingOperationQueueCount", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_pendingOperationQueueCount), HK_NULL },
	{ "multiThreadCheck", &hkMultiThreadCheckClass, HK_NULL, hkClassMember::TYPE_STRUCT, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_multiThreadCheck), HK_NULL },
	{ "processActionsInSingleThread", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_processActionsInSingleThread), HK_NULL },
	{ "minDesiredIslandSize", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_minDesiredIslandSize), HK_NULL },
	{ "modifyConstraintCriticalSection", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_modifyConstraintCriticalSection), HK_NULL },
	{ "worldLock", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_worldLock), HK_NULL },
	{ "islandDirtyListCriticalSection", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_islandDirtyListCriticalSection), HK_NULL },
	{ "propertyMasterLock", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_propertyMasterLock), HK_NULL },
	{ "wantSimulationIslands", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_wantSimulationIslands), HK_NULL },
	{ "snapCollisionToConvexEdgeThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_snapCollisionToConvexEdgeThreshold), HK_NULL },
	{ "snapCollisionToConcaveEdgeThreshold", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_snapCollisionToConcaveEdgeThreshold), HK_NULL },
	{ "enableToiWeldRejection", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_enableToiWeldRejection), HK_NULL },
	{ "wantDeactivation", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_wantDeactivation), HK_NULL },
	{ "shouldActivateOnRigidBodyTransformChange", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_shouldActivateOnRigidBodyTransformChange), HK_NULL },
	{ "highFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_highFrequencyDeactivationPeriod), HK_NULL },
	{ "lowFrequencyDeactivationPeriod", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_lowFrequencyDeactivationPeriod), HK_NULL },
	{ "deactivationReferenceDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_deactivationReferenceDistance), HK_NULL },
	{ "toiCollisionResponseRotateNormal", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_toiCollisionResponseRotateNormal), HK_NULL },
	{ "simulationType", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT32, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_simulationType), HK_NULL },
	{ "lastEntityUid", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_lastEntityUid), HK_NULL },
	{ "phantoms", &hkpPhantomClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkpWorld,m_phantoms), HK_NULL },
	{ "actionListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_actionListeners), HK_NULL },
	{ "entityListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_entityListeners), HK_NULL },
	{ "phantomListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_phantomListeners), HK_NULL },
	{ "constraintListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_constraintListeners), HK_NULL },
	{ "worldDeletionListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_worldDeletionListeners), HK_NULL },
	{ "islandActivationListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_islandActivationListeners), HK_NULL },
	{ "worldPostSimulationListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_worldPostSimulationListeners), HK_NULL },
	{ "worldPostIntegrateListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_worldPostIntegrateListeners), HK_NULL },
	{ "worldPostCollideListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_worldPostCollideListeners), HK_NULL },
	{ "islandPostIntegrateListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_islandPostIntegrateListeners), HK_NULL },
	{ "islandPostCollideListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_islandPostCollideListeners), HK_NULL },
	{ "collisionListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_collisionListeners), HK_NULL },
	{ "contactImpulseLimitBreachedListeners", HK_NULL, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_contactImpulseLimitBreachedListeners), HK_NULL },
	{ "broadPhaseBorder", HK_NULL, HK_NULL, hkClassMember::TYPE_POINTER, hkClassMember::TYPE_VOID, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_broadPhaseBorder), HK_NULL },
	{ "broadPhaseExtents", HK_NULL, HK_NULL, hkClassMember::TYPE_VECTOR4, hkClassMember::TYPE_VOID, 2, 0, HK_OFFSET_OF(hkpWorld,m_broadPhaseExtents), HK_NULL },
	{ "broadPhaseNumMarkers", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_broadPhaseNumMarkers), HK_NULL },
	{ "sizeOfToiEventQueue", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_sizeOfToiEventQueue), HK_NULL },
	{ "broadPhaseQuerySize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_broadPhaseQuerySize), HK_NULL },
	{ "broadPhaseUpdateSize", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hkpWorld,m_broadPhaseUpdateSize), HK_NULL },
	{ "contactPointGeneration", HK_NULL, HK_NULL, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0|hkClassMember::SERIALIZE_IGNORED, HK_OFFSET_OF(hkpWorld,m_contactPointGeneration), HK_NULL }
};
extern const hkClass hkReferencedObjectClass;

extern const hkClass hkpWorldClass;
const hkClass hkpWorldClass(
	"hkpWorld",
	&hkReferencedObjectClass, // parent
	sizeof(hkpWorld),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hkpWorldEnums),
	2, // enums
	reinterpret_cast<const hkClassMember*>(hkpWorld::Members),
	HK_COUNT_OF(hkpWorld::Members),
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
