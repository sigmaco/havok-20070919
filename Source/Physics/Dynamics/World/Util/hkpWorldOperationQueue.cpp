/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Dynamics/hkpDynamics.h>

#include <Common/Base/hkBase.h>
#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Common/Base/Algorithm/Sort/hkSort.inl>

#include <Physics/Dynamics/World/Util/hkpWorldOperationQueue.h>
#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/Phantom/hkpPhantom.h>

#include <Physics/Dynamics/World/Simulation/hkpSimulation.h>

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Physics/Dynamics/Action/hkpAction.h>


#define HK_FORGIVE_FAULTY_OPERATIONS


HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::AddEntity             ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::RemoveEntity          ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::SetRigidBodyMotionType) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::AddEntityBatch        ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::RemoveEntityBatch     ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::AddConstraint         ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::RemoveConstraint      ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::AddAction             ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::RemoveAction          ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::MergeIslands          ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::AddPhantom            ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::RemovePhantom         ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::AddPhantomBatch       ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::RemovePhantomBatch    ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::UpdateFilterOnEntity  ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::UpdateFilterOnPhantom ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::UpdateFilterOnWorld   ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::ReintegrateAndRecollideEntityBatch   ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::UpdateMovedBodyInfo   ) <= sizeof(hkWorldOperation::BiggestOperation) );

HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::SetRigidBodyPositionAndRotation) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::SetRigidBodyLinearVelocity     ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::SetRigidBodyAngularVelocity    ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::ApplyRigidBodyLinearImpulse    ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::ApplyRigidBodyPointImpulse     ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::ApplyRigidBodyAngularImpulse   ) <= sizeof(hkWorldOperation::BiggestOperation) );

HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::AddReference          ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::RemoveReference       ) <= sizeof(hkWorldOperation::BiggestOperation) );

HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::ActivateRegion        ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::ActivateEntity        ) <= sizeof(hkWorldOperation::BiggestOperation) );
HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::DeactivateEntity      ) <= sizeof(hkWorldOperation::BiggestOperation) );

HK_COMPILE_TIME_ASSERT( sizeof(hkWorldOperation::UserCallbackOperation ) <= sizeof(hkWorldOperation::BiggestOperation) );





hkpWorldOperationQueue::hkpWorldOperationQueue(hkpWorld* world) : m_queueOperationCriticalSection(4000)
{ 
	m_world = world; 
	m_storeIslandMergesOnSeparateList = false;
}

hkpWorldOperationQueue::~hkpWorldOperationQueue()
{
}

inline static void addReferenceTo( hkReferencedObject* obj)      { obj->addReference(); }
inline static void removeReferenceFrom( hkReferencedObject* obj) { obj->removeReference(); }

void hkpWorldOperationQueue::queueOperation(const hkWorldOperation::BaseOperation& operation )
{
	m_queueOperationCriticalSection.enter();
	hkWorldOperation::BaseOperation& op = m_pending.expandOne();
	m_world->m_pendingOperationsCount++;

#ifdef HK_DEBUG_MULTI_THREADING
	if (    m_world && m_world->m_simulationType == hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED
		&& (m_world->m_multiThreadCheck.m_threadId == hkMultiThreadCheck::MARKED_RO ||
			m_world->m_multiThreadCheck.m_threadId == hkMultiThreadCheck::UNMARKED   )         )
	{
		HK_WARN_ONCE( 0xf0e546a, "CriticalOperation executed. If you are running the physic on multiple threads, this results in a non deterministic simulation" ); 
	}
#endif


	hkString::memCpy4(&op, &operation, sizeof(hkWorldOperation::BiggestOperation)/4);


	// ADD REFERENCE TO REFERENCE COUNTED BODIES -- LATER REMOVE IT UPON COMPLETION
	
	switch(op.m_type)
	{
		case hkWorldOperation::ENTITY_ADD:
		{
			hkWorldOperation::AddEntity& cop = static_cast<hkWorldOperation::AddEntity&>(op);
			addReferenceTo(cop.m_entity);
			break;
		}
		case hkWorldOperation::ENTITY_REMOVE:
		{
			hkWorldOperation::RemoveEntity& cop = static_cast<hkWorldOperation::RemoveEntity&>(op);
			addReferenceTo(cop.m_entity);
			break;
		}
		case hkWorldOperation::RIGIDBODY_SET_MOTION_TYPE: 
		{
			hkWorldOperation::SetRigidBodyMotionType& cop = static_cast<hkWorldOperation::SetRigidBodyMotionType&>(op);
			addReferenceTo(cop.m_rigidBody);
			break;
		}

		case hkWorldOperation::WORLD_OBJECT_SET_SHAPE:
		{
			hkWorldOperation::SetWorldObjectShape& cop = static_cast<hkWorldOperation::SetWorldObjectShape&>(op);
			addReferenceTo(cop.m_worldObject);
			// The addReference call below is not thread-safe !!!!!!!!
			cop.m_shape->addReference();
			break;
		}

		case hkWorldOperation::ENTITY_BATCH_ADD:
		{
			hkWorldOperation::AddEntityBatch& cop = static_cast<hkWorldOperation::AddEntityBatch&>(op);
			cop.m_entities = hkAllocateChunk<hkpEntity*>(cop.m_numEntities, HK_MEMORY_CLASS_DYNAMICS);
			const hkWorldOperation::AddEntityBatch& coperation = static_cast<const hkWorldOperation::AddEntityBatch&>(operation);
			hkString::memCpy(cop.m_entities, coperation.m_entities, sizeof(hkpEntity*) * coperation.m_numEntities);
			hkpEntity** e = cop.m_entities;
			hkpEntity** eEnd = e + cop.m_numEntities;
			while (e < eEnd)
			{
				addReferenceTo( (e++)[0] );
			}
			break;
		}
		case hkWorldOperation::ENTITY_BATCH_REMOVE:
		{
			hkWorldOperation::RemoveEntityBatch& cop = static_cast<hkWorldOperation::RemoveEntityBatch&>(op);
			cop.m_entities = hkAllocateChunk<hkpEntity*>(cop.m_numEntities, HK_MEMORY_CLASS_DYNAMICS);
			const hkWorldOperation::RemoveEntityBatch& coperation = static_cast<const hkWorldOperation::RemoveEntityBatch&>(operation);
			hkString::memCpy(cop.m_entities, coperation.m_entities, sizeof(hkpEntity*) * coperation.m_numEntities);
			hkpEntity** e = cop.m_entities;
			hkpEntity** eEnd = e + cop.m_numEntities;
			while (e < eEnd)
			{
				addReferenceTo( (e++)[0] );
			}
			break;
		}
		case hkWorldOperation::CONSTRAINT_ADD:
		{
			hkWorldOperation::AddConstraint& cop = static_cast<hkWorldOperation::AddConstraint&>(op);
			addReferenceTo(cop.m_constraint);
			break;
		}

		case hkWorldOperation::CONSTRAINT_REMOVE:
		{
			hkWorldOperation::RemoveConstraint& cop = static_cast<hkWorldOperation::RemoveConstraint&>(op);
			addReferenceTo(cop.m_constraint);
			break;
		}

		case hkWorldOperation::ACTION_ADD:
		{
			hkWorldOperation::AddAction& cop = static_cast<hkWorldOperation::AddAction&>(op);
			addReferenceTo(cop.m_action);
			break;
		}

		case hkWorldOperation::ACTION_REMOVE:
		{
			hkWorldOperation::RemoveAction& cop = static_cast<hkWorldOperation::RemoveAction&>(op);
			addReferenceTo(cop.m_action);
			break;
		}

		// Internal:
		case hkWorldOperation::ISLAND_MERGE:
		{
			hkWorldOperation::MergeIslands& cop = static_cast<hkWorldOperation::MergeIslands&>(op);
			addReferenceTo(cop.m_entities[0]);
			addReferenceTo(cop.m_entities[1]);
			if (m_storeIslandMergesOnSeparateList)
			{
				m_islandMerges.pushBack(static_cast<hkWorldOperation::BiggestOperation&>(op));
				m_pending.popBack();
			}
			break;
		}

		// Phantoms:
		case hkWorldOperation::PHANTOM_ADD:
		{
			hkWorldOperation::AddPhantom& cop = static_cast<hkWorldOperation::AddPhantom&>(op);
			addReferenceTo(cop.m_phantom);
			break;
		}
		case hkWorldOperation::PHANTOM_REMOVE:
		{
			hkWorldOperation::RemovePhantom& cop = static_cast<hkWorldOperation::RemovePhantom&>(op);
			addReferenceTo(cop.m_phantom);
			break;
		}
		case hkWorldOperation::PHANTOM_BATCH_ADD:
		{
			hkWorldOperation::AddPhantomBatch& cop = static_cast<hkWorldOperation::AddPhantomBatch&>(op);

			cop.m_phantoms = hkAllocateChunk<hkpPhantom*>(cop.m_numPhantoms, HK_MEMORY_CLASS_DYNAMICS);
			const hkWorldOperation::AddPhantomBatch& coperation = static_cast<const hkWorldOperation::AddPhantomBatch&>(operation);
			hkString::memCpy(cop.m_phantoms, coperation.m_phantoms, sizeof(hkpPhantom*) * coperation.m_numPhantoms);
			hkpPhantom** p = cop.m_phantoms;
			hkpPhantom** pEnd = p + cop.m_numPhantoms;
			while (p < pEnd)
			{
				addReferenceTo( (p++)[0] );
			}
			break;
		}
		case hkWorldOperation::PHANTOM_BATCH_REMOVE:
		{
			hkWorldOperation::RemovePhantomBatch& cop = static_cast<hkWorldOperation::RemovePhantomBatch&>(op);

			cop.m_phantoms = hkAllocateChunk<hkpPhantom*>(cop.m_numPhantoms, HK_MEMORY_CLASS_DYNAMICS);
			const hkWorldOperation::RemovePhantomBatch& coperation = static_cast<const hkWorldOperation::RemovePhantomBatch&>(operation);
			hkString::memCpy(cop.m_phantoms, coperation.m_phantoms, sizeof(hkpPhantom*) * coperation.m_numPhantoms);
			hkpPhantom** p = cop.m_phantoms;
			hkpPhantom** pEnd = p + cop.m_numPhantoms;
			while (p < pEnd)
			{
				addReferenceTo( (p++)[0] );
			}

			break;
		}

		// Broadphase updates

		case hkWorldOperation::ENTITY_UPDATE_BROAD_PHASE:
		{
			hkWorldOperation::UpdateEntityBP& cop = static_cast<hkWorldOperation::UpdateEntityBP&>(op);
			addReferenceTo( cop.m_entity );
			break;
		}

		case hkWorldOperation::PHANTOM_UPDATE_BROAD_PHASE:  //updateBroadPhase
		{
			hkWorldOperation::UpdatePhantomBP& cop = static_cast<hkWorldOperation::UpdatePhantomBP&>(op);
			const hkWorldOperation::UpdatePhantomBP& coperation = static_cast<const hkWorldOperation::UpdatePhantomBP&>(operation);
			addReferenceTo( cop.m_phantom );
			cop.m_aabb = new hkAabb(coperation.m_aabb->m_min, coperation.m_aabb->m_max);
			break;
		}


		// Filters:
		case hkWorldOperation::UPDATE_FILTER_ENTITY:
		{
			hkWorldOperation::UpdateFilterOnEntity& cop = static_cast<hkWorldOperation::UpdateFilterOnEntity&>(op);
			addReferenceTo( cop.m_entity );
			break;
		}
		case hkWorldOperation::UPDATE_FILTER_PHANTOM:
		{
			hkWorldOperation::UpdateFilterOnPhantom& cop = static_cast<hkWorldOperation::UpdateFilterOnPhantom&>(op);
			addReferenceTo( cop.m_phantom );
			break;
		}
		case hkWorldOperation::UPDATE_FILTER_WORLD:
		{
			break;
		}

		case hkWorldOperation::ENTITY_BATCH_REINTEGRATE_AND_RECOLLIDE:
		{
			hkWorldOperation::ReintegrateAndRecollideEntityBatch& cop = static_cast<hkWorldOperation::ReintegrateAndRecollideEntityBatch&>(op);
			cop.m_entities = hkAllocateChunk<hkpEntity*>(cop.m_numEntities, HK_MEMORY_CLASS_DYNAMICS);
			const hkWorldOperation::ReintegrateAndRecollideEntityBatch& coperation = static_cast<const hkWorldOperation::ReintegrateAndRecollideEntityBatch&>(operation);
			hkString::memCpy(cop.m_entities, coperation.m_entities, sizeof(hkpEntity*) * coperation.m_numEntities);
			hkpEntity** e = cop.m_entities;
			hkpEntity** eEnd = e + cop.m_numEntities;
			while (e < eEnd)
			{
				addReferenceTo( (e++)[0] );
			}
			
			break;
		}

		case hkWorldOperation::UPDATE_MOVED_BODY_INFO:
		{
			hkWorldOperation::UpdateMovedBodyInfo& cop = static_cast<hkWorldOperation::UpdateMovedBodyInfo&>(op);
			addReferenceTo( cop.m_entity );
			break;
		}

		case hkWorldOperation::RIGIDBODY_SET_POSITION_AND_ROTATION:
		{
			hkWorldOperation::SetRigidBodyPositionAndRotation& cop = static_cast<hkWorldOperation::SetRigidBodyPositionAndRotation&>(op);
			addReferenceTo( cop.m_rigidBody );
			break;
		}
		case hkWorldOperation::RIGIDBODY_SET_LINEAR_VELOCITY:
		{
			hkWorldOperation::SetRigidBodyLinearVelocity& cop = static_cast<hkWorldOperation::SetRigidBodyLinearVelocity&>(op);
			addReferenceTo( cop.m_rigidBody );
			break;
		}
		case hkWorldOperation::RIGIDBODY_SET_ANGULAR_VELOCITY:
		{
			hkWorldOperation::SetRigidBodyAngularVelocity& cop = static_cast<hkWorldOperation::SetRigidBodyAngularVelocity&>(op);
			addReferenceTo( cop.m_rigidBody );
			break;
		}
		case hkWorldOperation::RIGIDBODY_APPLY_LINEAR_IMPULSE:
		{
			hkWorldOperation::ApplyRigidBodyLinearImpulse& cop = static_cast<hkWorldOperation::ApplyRigidBodyLinearImpulse&>(op);
			addReferenceTo( cop.m_rigidBody );
			break;
		}
		case hkWorldOperation::RIGIDBODY_APPLY_POINT_IMPULSE:
		{
			hkWorldOperation::ApplyRigidBodyPointImpulse& cop = static_cast<hkWorldOperation::ApplyRigidBodyPointImpulse&>(op);
			addReferenceTo( cop.m_rigidBody);
			break;
		}
		case hkWorldOperation::RIGIDBODY_APPLY_ANGULAR_IMPULSE:
		{
			hkWorldOperation::ApplyRigidBodyAngularImpulse& cop = static_cast<hkWorldOperation::ApplyRigidBodyAngularImpulse&>(op);
			addReferenceTo( cop.m_rigidBody);
			break;
		}

		case hkWorldOperation::WORLD_OBJECT_ADD_REFERENCE:
		{
			hkWorldOperation::AddReference& cop = static_cast<hkWorldOperation::AddReference&>(op);
			addReferenceTo( cop.m_worldObject );
			m_pending.popBack();
			m_world->m_pendingOperationsCount--;
			break;
		}
		case hkWorldOperation::WORLD_OBJECT_REMOVE_REFERENCE:
		{
			hkWorldOperation::RemoveReference& cop = static_cast<hkWorldOperation::RemoveReference&>(op);
			HK_ASSERT2(0xad67ddbb, cop.m_worldObject->getReferenceCount() > 1, "Error. Deleting a hkpWorldObject which is still in hkpWorld.");
			removeReferenceFrom( cop.m_worldObject );
			m_pending.popBack();
			m_world->m_pendingOperationsCount--;
			break;
		}

		case hkWorldOperation::ACTIVATE_REGION:
		{
			break;
		}
		case hkWorldOperation::ACTIVATE_ENTITY:
		{
			hkWorldOperation::ActivateEntity& cop = static_cast<hkWorldOperation::ActivateEntity&>(op);
			addReferenceTo( cop.m_entity );
			break;
		}
		case hkWorldOperation::DEACTIVATE_ENTITY:
		{
			hkWorldOperation::DeactivateEntity& cop = static_cast<hkWorldOperation::DeactivateEntity&>(op);
			addReferenceTo( cop.m_entity );
			break;
		}


		case hkWorldOperation::USER_CALLBACK:
		{
			hkWorldOperation::UserCallbackOperation& cop = static_cast<hkWorldOperation::UserCallbackOperation&>(op);
			addReferenceTo( cop.m_userCallback );
			break;
		}

		default:
			HK_ASSERT2(0xf0ff0062,0, "Unknown/invalid operation type");
		break;
	}

	m_queueOperationCriticalSection.leave();
}


	// to guarantee deterministic order, we simply order the constraint by the unique id of the linked entities.
static hkBool islandLess( const hkWorldOperation::BiggestOperation& a, const hkWorldOperation::BiggestOperation& b )
{
	const hkWorldOperation::MergeIslands& mia = reinterpret_cast<const hkWorldOperation::MergeIslands&>( a );
	const hkWorldOperation::MergeIslands& mib = reinterpret_cast<const hkWorldOperation::MergeIslands&>( b );

	HK_ASSERT2(0xad6ae78d, mia.m_entities[0]->getWorld() && mia.m_entities[1]->getWorld()
						&& mib.m_entities[0]->getWorld() && mib.m_entities[1]->getWorld(), "Internal error: all entities in the hkWorldOperation::MergeIslands are expected to be still in the world.");

	// We delay querying of entity[1] islands to avoid unnecesary cache misses
	const hkUint32 islandZeroIdx0 = mia.m_entities[0]->getSimulationIsland()->m_storageIndex;
	const hkUint32 islandZeroIdx1 = mib.m_entities[0]->getSimulationIsland()->m_storageIndex;

	return 	 (     islandZeroIdx0 <  islandZeroIdx1
			|| (   islandZeroIdx0 == islandZeroIdx1
				&& mia.m_entities[1]->getSimulationIsland()->m_storageIndex < mib.m_entities[1]->getSimulationIsland()->m_storageIndex ) );
}

void hkpWorldOperationQueue::executeAllPending()
{
	HK_ASSERT(0Xad000100, m_pending.getSize() || m_islandMerges.getSize());
	HK_ASSERT2(0xad005002, !m_world->areCriticalOperationsLocked() && !m_world->m_blockExecutingPendingOperations, "Attempting to execute pending operations while the world is still hkpWorld::areCriticalOperationsLocked() or blocked by hkpWorld::m_blockExecutingPendingOperations.");

	{
		// Process the separate list of island merges first
		if (m_islandMerges.getSize())
		{
			// Sort island merges
			hkAlgorithm::quickSort(m_islandMerges.begin(), m_islandMerges.getSize(), islandLess );

			m_pending.insertAt(0, m_islandMerges.begin(), m_islandMerges.getSize());
			m_islandMerges.clear();
		}
	}

	hkArray<hkWorldOperation::BiggestOperation> stolenPending;
	stolenPending.swap( m_pending );
	HK_ON_DEBUG( hkpDebugInfoOnPendingOperationQueues::addNextPendingOperationQueue(m_world, &stolenPending); );
	m_world->m_pendingOperationQueueCount++;

	for (int i = 0; i < stolenPending.getSize(); i++)
	{
		HK_ON_DEBUG( hkpDebugInfoOnPendingOperationQueues::updateNextPendingOperationIndex(m_world, i+1); );
	
		hkWorldOperation::BaseOperation& op = stolenPending[i];

		switch(op.m_type)
		{
			case hkWorldOperation::ENTITY_ADD:
			{
				hkWorldOperation::AddEntity& cop = static_cast<hkWorldOperation::AddEntity&>(op);
				if (cop.m_entity->getWorld() == HK_NULL)
				{
					m_world->addEntity(cop.m_entity, cop.m_activation);
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a0, "Attempting to add an entity twice)");
				}
#				ifndef HK_FORGIVE_FAULTY_OPERATIONS
					HK_ASSERT2(0xf0ff009e, cop.m_entity->getWorld() == m_world, "Entity not properly added to _this_ world.");
#				endif
				removeReferenceFrom( cop.m_entity );
				break;
			}
			case hkWorldOperation::ENTITY_REMOVE:
			{
				hkWorldOperation::AddEntity& cop = static_cast<hkWorldOperation::AddEntity&>(op);
				if (cop.m_entity->getWorld() == m_world)
				{
					m_world->removeEntity(cop.m_entity);
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a1, "Attempting to remove an entity twice)");
					
				}
				HK_ASSERT2(0xf0ff009f, cop.m_entity->getWorld() == HK_NULL, "Warning: have you removed an entity and then immediately added it to another world in a callback ?");
				removeReferenceFrom( cop.m_entity );
				break;
			}
			case hkWorldOperation::RIGIDBODY_SET_MOTION_TYPE: 
			{
				hkWorldOperation::SetRigidBodyMotionType& cop = static_cast<hkWorldOperation::SetRigidBodyMotionType&>(op);
				cop.m_rigidBody->setMotionType(cop.m_motionType, cop.m_activation, cop.m_collisionFilterUpdateMode);
				removeReferenceFrom( cop.m_rigidBody );
				break;
			}

			case hkWorldOperation::WORLD_OBJECT_SET_SHAPE:
			{
				hkWorldOperation::SetWorldObjectShape& cop = static_cast<hkWorldOperation::SetWorldObjectShape&>(op);
				cop.m_worldObject->setShape(cop.m_shape);
				removeReferenceFrom( cop.m_worldObject );
				// The removeReference call below is not thread-safe !!!!!!
				cop.m_shape->removeReference();
				break;
			}

			case hkWorldOperation::ENTITY_BATCH_ADD:
			{
				// warning: no check is done whether the entities have already been added to the world
				hkWorldOperation::AddEntityBatch& cop = static_cast<hkWorldOperation::AddEntityBatch&>(op);
				m_world->addEntityBatch(cop.m_entities, cop.m_numEntities, cop.m_activation);

				hkpEntity** e = cop.m_entities;
				hkpEntity** eEnd = e + cop.m_numEntities;
				while (e < eEnd)
				{
					removeReferenceFrom( (e++)[0] );
				}
				// Deallocate cop.m_entities array.
				hkDeallocateChunk<hkpEntity*>(cop.m_entities, cop.m_numEntities, HK_MEMORY_CLASS_DYNAMICS);
				break;
			}
			case hkWorldOperation::ENTITY_BATCH_REMOVE:
			{
				// warning: no check is done whether the entities have already been removed from the world
				hkWorldOperation::RemoveEntityBatch& cop = static_cast<hkWorldOperation::RemoveEntityBatch&>(op);
				m_world->removeEntityBatch(cop.m_entities, cop.m_numEntities);

				hkpEntity** e = cop.m_entities;
				hkpEntity** eEnd = e + cop.m_numEntities;
				while (e < eEnd)
				{
					removeReferenceFrom( (e++)[0] );
				}
				//delete cop.m_entities;
				hkDeallocateChunk<hkpEntity*>(cop.m_entities, cop.m_numEntities, HK_MEMORY_CLASS_DYNAMICS);
				break;
			}
			case hkWorldOperation::CONSTRAINT_ADD:
			{
				hkWorldOperation::AddConstraint& cop = static_cast<hkWorldOperation::AddConstraint&>(op);
				if (cop.m_constraint->getOwner() == HK_NULL)
				{
#					ifdef HK_FORGIVE_FAULTY_OPERATIONS
						if ( cop.m_constraint->getEntityA()->getWorld() == m_world && cop.m_constraint->getEntityB()->getWorld() == m_world )
#					endif // HK_ENABLE_EXTENSIVE_WORLD_CHECKING
						{
							m_world->addConstraint(cop.m_constraint);
						}
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a2, "Attempting to add a constraint twice)");
				}
#				ifndef HK_FORGIVE_FAULTY_OPERATIONS
					HK_ASSERT2(0xf0ff00a6, cop.m_constraint->getOwner() && static_cast<hkpSimulationIsland*>(cop.m_constraint->getOwner())->getWorld() == m_world, "Problems with adding a constraint: Probable cause: or attempting to add the same constraint to two worlds immediately.");
#				endif // !HK_ENABLE_EXTENSIVE_WORLD_CHECKING
				removeReferenceFrom( cop.m_constraint );
				break;
			}
			case hkWorldOperation::CONSTRAINT_REMOVE:
			{
				hkWorldOperation::RemoveConstraint& cop = static_cast<hkWorldOperation::RemoveConstraint&>(op);
				if (cop.m_constraint->getOwner() != HK_NULL)
				{
					m_world->removeConstraint(cop.m_constraint);
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a3, "Attempting to remove a constraint twice)");
				}

				cop.m_constraint->removeReference();
				break;
			}

			case hkWorldOperation::ACTION_ADD:
			{
				hkWorldOperation::AddAction& cop = static_cast<hkWorldOperation::AddAction&>(op);
				if (cop.m_action->getWorld() == HK_NULL)
				{
#					ifdef HK_FORGIVE_FAULTY_OPERATIONS
						hkBool allActionsInWorld = true;
						hkArray<hkpEntity*> actionEntities;
						cop.m_action->getEntities(actionEntities);
						for (int k = 0; k < actionEntities.getSize(); k++)
						{
							if (actionEntities[k]->getWorld() != m_world)
							{
								allActionsInWorld = false;
								break;
							}
						}
						if (allActionsInWorld)
#					endif // HK_FORGIVE_FAULTY_OPERATIONS
						{
							m_world->addAction(cop.m_action);
						}
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00d2, "Attempting to add an action twice)");
				}
#				ifndef HK_FORGIVE_FAULTY_OPERATIONS
					HK_ASSERT2(0xf0ff00a6, cop.m_action->getOwner() && static_cast<hkpSimulationIsland*>(cop.m_action->getOwner())->getWorld() == m_world, "Problems with adding a action: Probable cause: or attempting to add the same action to two worlds immediately. Or phantom ");
#				endif // !HK_ENABLE_EXTENSIVE_WORLD_CHECKING
				cop.m_action->removeReference();
				break;
			}
			case hkWorldOperation::ACTION_REMOVE:
			{
				hkWorldOperation::RemoveAction& cop = static_cast<hkWorldOperation::RemoveAction&>(op);
				if (cop.m_action->getSimulationIsland() != HK_NULL)
				{
					m_world->removeAction(cop.m_action);
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a3, "Attempting to remove a action twice)");
				}

				cop.m_action->removeReference();
				break;
			}

			// Internal:
			case hkWorldOperation::ISLAND_MERGE:
			{
				hkWorldOperation::MergeIslands& cop = static_cast<hkWorldOperation::MergeIslands&>(op);
				if ( cop.m_entities[0]->getWorld() == m_world && cop.m_entities[1]->getWorld() == m_world)
				{
					// a body may have got pinned, if so then simply ignore the merge
					hkpWorldOperationUtil::mergeIslandsIfNeeded(cop.m_entities[0], cop.m_entities[1]);
				}
				removeReferenceFrom( cop.m_entities[0] );
				removeReferenceFrom( cop.m_entities[1] );
				break;
			}

			// Phantoms:

			case hkWorldOperation::PHANTOM_ADD:
			{
				hkWorldOperation::AddPhantom& cop = static_cast<hkWorldOperation::AddPhantom&>(op);
				if (cop.m_phantom->getWorld() == HK_NULL)
				{
					m_world->addPhantom(cop.m_phantom);
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a0, "Attempting to add a phantom twice)");
				}
#				ifndef HK_FORGIVE_FAULTY_OPERATIONS
					HK_ASSERT2(0xf0ff009e, cop.m_phantom->getWorld() == m_world, "Phantom not properly added to _this_ world.");
#				endif
				removeReferenceFrom( cop.m_phantom );
				break;
			}
			case hkWorldOperation::PHANTOM_REMOVE:
			{
				hkWorldOperation::RemovePhantom& cop = static_cast<hkWorldOperation::RemovePhantom&>(op);
				if (cop.m_phantom->getWorld() == m_world)
				{
					m_world->removePhantom(cop.m_phantom);
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a1, "Attempting to remove a phantom twice)");
					
				}
				HK_ASSERT2(0xf0ff009f, cop.m_phantom->getWorld() == HK_NULL, "Warning: have you removed a phantom and then immediately added it to another world in a callback ?");
				removeReferenceFrom( cop.m_phantom );
				break;
			}
			case hkWorldOperation::PHANTOM_BATCH_ADD:
			{
				// warning: no check is done whether the phantoms have already been added to the world
				hkWorldOperation::AddPhantomBatch& cop = static_cast<hkWorldOperation::AddPhantomBatch&>(op);
				m_world->addPhantomBatch(cop.m_phantoms, cop.m_numPhantoms);

				hkpPhantom** p = cop.m_phantoms;
				hkpPhantom** pEnd = p + cop.m_numPhantoms;
				while (p < pEnd)
				{
					removeReferenceFrom( (p++)[0] );
				}
				//delete cop.m_phantoms;
				hkDeallocateChunk<hkpPhantom*>(cop.m_phantoms, cop.m_numPhantoms, HK_MEMORY_CLASS_DYNAMICS);
				break;
			}
			case hkWorldOperation::PHANTOM_BATCH_REMOVE:
			{
				// warning: no check is done whether the phantoms have already been removed from the world
				hkWorldOperation::RemovePhantomBatch& cop = static_cast<hkWorldOperation::RemovePhantomBatch&>(op);
				m_world->removePhantomBatch(cop.m_phantoms, cop.m_numPhantoms);

				hkpPhantom** p = cop.m_phantoms;
				hkpPhantom** pEnd = p + cop.m_numPhantoms;
				while (p < pEnd)
				{
					removeReferenceFrom( (p++)[0] );
				}
				//delete cop.m_phantoms;
				hkDeallocateChunk<hkpPhantom*>(cop.m_phantoms, cop.m_numPhantoms, HK_MEMORY_CLASS_DYNAMICS);
				break;
			}

			case hkWorldOperation::ENTITY_UPDATE_BROAD_PHASE:
			{
				hkWorldOperation::UpdateEntityBP& cop = static_cast<hkWorldOperation::UpdateEntityBP&>(op);

				if (cop.m_entity->getWorld() == m_world)
				{
					hkpWorldOperationUtil::updateEntityBP(m_world, cop.m_entity);
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a1, "Attempting to update broad phase of an entity which was removed from the world)");
				}
				cop.m_entity->removeReference();
				break;
			}


			case hkWorldOperation::PHANTOM_UPDATE_BROAD_PHASE: 
			{
				hkWorldOperation::UpdatePhantomBP& cop = static_cast<hkWorldOperation::UpdatePhantomBP&>(op);

				if (cop.m_phantom->getWorld() == m_world)
				{
					cop.m_phantom->updateBroadPhase(*cop.m_aabb);
				}
				else
				{
					HK_WARN_ONCE(0xf0ff00a1, "Attempting to update broad phase of a phantom which was removed from the world)");
				}
				removeReferenceFrom( cop.m_phantom );
				delete cop.m_aabb;
				break;
			}


			// Filters:
			case hkWorldOperation::UPDATE_FILTER_ENTITY:
			{
				hkWorldOperation::UpdateFilterOnEntity& cop = static_cast<hkWorldOperation::UpdateFilterOnEntity&>(op);
				if (cop.m_entity->getWorld() == m_world)
				{
					m_world->updateCollisionFilterOnEntity(cop.m_entity, cop.m_collisionFilterUpdateMode, cop.m_updateShapeCollections);
				}
				else
				{
					HK_ASSERT2(0xf0ff00a4,cop.m_entity->getWorld() == HK_NULL, "Warning: have you removed an entity and then immediately added it to another world in a callback ?");
				}
				removeReferenceFrom( cop.m_entity );
				break;
			}
			case hkWorldOperation::UPDATE_FILTER_PHANTOM:
			{
				hkWorldOperation::UpdateFilterOnPhantom& cop = static_cast<hkWorldOperation::UpdateFilterOnPhantom&>(op);
				if (cop.m_phantom->getWorld() == m_world)
				{
					m_world->updateCollisionFilterOnPhantom(cop.m_phantom, cop.m_updateShapeCollections);
				}
				else
				{
					HK_ASSERT2(0xf0ff00a5,cop.m_phantom->getWorld() == HK_NULL, "Warning: have you removed an phantom and then immediately added it to another world in a callback ?");
				}
				removeReferenceFrom( cop.m_phantom );
				break;
			}

			case hkWorldOperation::UPDATE_FILTER_WORLD:
			{
				hkWorldOperation::UpdateFilterOnWorld& cop = static_cast<hkWorldOperation::UpdateFilterOnWorld&>(op);
				m_world->updateCollisionFilterOnWorld(cop.m_collisionFilterUpdateMode, cop.m_updateShapeCollections);
				break;
			}

			case hkWorldOperation::UPDATE_MOVED_BODY_INFO:
			{
				hkWorldOperation::UpdateMovedBodyInfo& cop = static_cast<hkWorldOperation::UpdateMovedBodyInfo&>(op);
				hkpRigidBody::updateBroadphaseAndResetCollisionInformationOfWarpedBody(cop.m_entity) ;
				removeReferenceFrom( cop.m_entity );
				break;
			}

			case hkWorldOperation::RIGIDBODY_SET_POSITION_AND_ROTATION:
			{
				hkWorldOperation::SetRigidBodyPositionAndRotation& cop = static_cast<hkWorldOperation::SetRigidBodyPositionAndRotation&>(op);
				cop.m_rigidBody->setPositionAndRotation( cop.m_positionAndRotation[0], reinterpret_cast<hkQuaternion&>(cop.m_positionAndRotation[1]) );
				hkDeallocateChunk<hkVector4>( cop.m_positionAndRotation, 2, HK_MEMORY_CLASS_DYNAMICS );
				removeReferenceFrom( cop.m_rigidBody );
				break;
			}

			case hkWorldOperation::RIGIDBODY_SET_LINEAR_VELOCITY:
			{
				hkWorldOperation::SetRigidBodyLinearVelocity& cop = static_cast<hkWorldOperation::SetRigidBodyLinearVelocity&>(op);
				hkVector4 velocity; velocity.set( cop.m_linearVelocity[0], cop.m_linearVelocity[1], cop.m_linearVelocity[2] );
				cop.m_rigidBody->setLinearVelocity( velocity );
				removeReferenceFrom( cop.m_rigidBody );

				break;
			}
			case hkWorldOperation::RIGIDBODY_SET_ANGULAR_VELOCITY:
			{
				hkWorldOperation::SetRigidBodyAngularVelocity& cop = static_cast<hkWorldOperation::SetRigidBodyAngularVelocity&>(op);
				hkVector4 velocity; velocity.set( cop.m_angularVelocity[0], cop.m_angularVelocity[1], cop.m_angularVelocity[2] );
				cop.m_rigidBody->setAngularVelocity( velocity );
				removeReferenceFrom( cop.m_rigidBody );
				break;
			}
			case hkWorldOperation::RIGIDBODY_APPLY_LINEAR_IMPULSE:
			{
				hkWorldOperation::ApplyRigidBodyLinearImpulse& cop = static_cast<hkWorldOperation::ApplyRigidBodyLinearImpulse&>(op);
				hkVector4 impulse; impulse.set( cop.m_linearImpulse[0], cop.m_linearImpulse[1], cop.m_linearImpulse[2] );
				cop.m_rigidBody->applyLinearImpulse( impulse );
				removeReferenceFrom( cop.m_rigidBody );
				break;
			}
			case hkWorldOperation::RIGIDBODY_APPLY_POINT_IMPULSE:
			{
				hkWorldOperation::ApplyRigidBodyPointImpulse& cop = static_cast<hkWorldOperation::ApplyRigidBodyPointImpulse&>(op);
				hkVector4& point = cop.m_pointAndImpulse[0];
				hkVector4& impulse = cop.m_pointAndImpulse[1];
				cop.m_rigidBody->applyPointImpulse( impulse, point );
				hkDeallocateChunk<hkVector4>( cop.m_pointAndImpulse, 2, HK_MEMORY_CLASS_DYNAMICS );
				removeReferenceFrom( cop.m_rigidBody );
				break;
			}
			case hkWorldOperation::RIGIDBODY_APPLY_ANGULAR_IMPULSE:
			{
				hkWorldOperation::ApplyRigidBodyAngularImpulse& cop = static_cast<hkWorldOperation::ApplyRigidBodyAngularImpulse&>(op);
				hkVector4 impulse; impulse.set( cop.m_angularImpulse[0], cop.m_angularImpulse[1], cop.m_angularImpulse[2] );
				cop.m_rigidBody->applyAngularImpulse( impulse );
				removeReferenceFrom( cop.m_rigidBody );
				break;
			}

			case hkWorldOperation::ACTIVATE_REGION:
			{
				hkWorldOperation::ActivateRegion& cop = static_cast<hkWorldOperation::ActivateRegion&>(op);
				hkAabb& aabb = *cop.m_aabb;
				m_world->activateRegion(aabb);
				hkDeallocateChunk<hkAabb>(cop.m_aabb, 1, HK_MEMORY_CLASS_DYNAMICS);
				break;
			}
			case hkWorldOperation::ACTIVATE_ENTITY:
			{
				hkWorldOperation::ActivateEntity& cop = static_cast<hkWorldOperation::ActivateEntity&>(op);
				cop.m_entity->activate();
				removeReferenceFrom( cop.m_entity );
				break;
			}
			case hkWorldOperation::DEACTIVATE_ENTITY:
			{
				hkWorldOperation::DeactivateEntity& cop = static_cast<hkWorldOperation::DeactivateEntity&>(op);
				HK_ASSERT2(0xad367838, cop.m_entity->getWorld() == m_world || cop.m_entity->getWorld() == HK_NULL, "Deactivating an entity in a different world, than that in which the deactivation function was initally called.");
				if (cop.m_entity->getWorld() == m_world)
				{
					cop.m_entity->deactivate();
				}
				removeReferenceFrom( cop.m_entity );
				break;
			}

			case hkWorldOperation::ENTITY_BATCH_REINTEGRATE_AND_RECOLLIDE:
			{
				// warning: no check is done whether the entities have already been added to the world
				hkWorldOperation::ReintegrateAndRecollideEntityBatch& cop = static_cast<hkWorldOperation::ReintegrateAndRecollideEntityBatch&>(op);
				m_world->m_simulation->reintegrateAndRecollideEntities(cop.m_entities, cop.m_numEntities, m_world, hkpWorld::ReintegrationRecollideMode(cop.m_mode));

				hkpEntity** e = cop.m_entities;
				hkpEntity** eEnd = e + cop.m_numEntities;
				while (e < eEnd)
				{
					removeReferenceFrom( (e++)[0] );
				}
				//delete cop.m_entities;
				hkDeallocateChunk<hkpEntity*>(cop.m_entities, cop.m_numEntities, HK_MEMORY_CLASS_DYNAMICS);
				break;
			}

			case hkWorldOperation::USER_CALLBACK:
			{
				hkWorldOperation::UserCallbackOperation& cop = static_cast<hkWorldOperation::UserCallbackOperation&>(op);
				cop.m_userCallback->worldOperationUserCallback(cop.m_userData);
				removeReferenceFrom( cop.m_userCallback);
				break;
			}

		default:
			HK_ASSERT2(0xf0ff0063,0, "Unknown/invalid operation type");
			break;
		}

		HK_ASSERT2(0xad005001, !m_world->areCriticalOperationsLocked() && !m_world->m_blockExecutingPendingOperations, "An operation executed from the pending list did not properly set hkpWorld::areCriticalOperationsLocked() or hkpWorld::m_blockExecutingPendingOperations state to its initial value");

		//
		//	Recurse if we have new pending operations
		//
		if ( m_pending.getSize() )
		{
			HK_ASSERT2(0xadbc6bec, 0, "Internal inconsistency. Should be safe to ignore. One of critical operations did not execute pending operation at its end.");
			executeAllPending();
		}
		
	}	// for all pendings
	
	HK_ON_DEBUG( hkpDebugInfoOnPendingOperationQueues::removeLastPendingOperationQueue(m_world, &stolenPending); );
	stolenPending.swap( m_pending );
	m_pending.clear();
	m_world->m_pendingOperationQueueCount--;
}



#ifdef HK_DEBUG

void HK_CALL hkpDebugInfoOnPendingOperationQueues::init(hkpWorld* world)
{
	HK_ASSERT2(0, world->m_pendingOperations != HK_NULL, "Internal: Just checking");
	world->m_pendingOperationQueues = new hkpDebugInfoOnPendingOperationQueues(&world->m_pendingOperations->m_pending);
}

void HK_CALL hkpDebugInfoOnPendingOperationQueues::cleanup(hkpWorld* world)
{
	HK_ASSERT2(0, world->m_pendingOperationQueues && world->m_pendingOperationQueues->m_prevQueue == HK_NULL, "Internal error: upon world deletion all pending operations should have been processed and only the initial pendingQueue should be still allocated.");
	HK_ASSERT2(0, world->m_pendingOperationQueues->m_nextPendingOperationIndex >= world->m_pendingOperationQueues->m_pending->getSize(), "Internal error: upon world deletion all pending operations should have been processed and only the initial pendingQueue should be still allocated.");
	HK_ASSERT2(0, world->m_pendingOperationQueues->m_pending->getSize() == 0, "Internal error: upon world deletion all pending operations should have been processed and only the initial pendingQueue should be still allocated.");
	delete world->m_pendingOperationQueues;
	world->m_pendingOperationQueues = HK_NULL;
}

void HK_CALL hkpDebugInfoOnPendingOperationQueues::updateNextPendingOperationIndex(hkpWorld* world, int index)
{
	hkpDebugInfoOnPendingOperationQueues* queue = world->m_pendingOperationQueues;
	queue = hkpDebugInfoOnPendingOperationQueues::getLastQueue(queue);
	// there must be at least 2 queue infos now
	HK_ASSERT(0, queue->m_prevQueue);
	HK_ASSERT2(0, queue->m_prevQueue->m_nextPendingOperationIndex < index, "Internal: just checking");
	queue->m_prevQueue->m_nextPendingOperationIndex = index;
}

void HK_CALL hkpDebugInfoOnPendingOperationQueues::addNextPendingOperationQueue(hkpWorld* world, hkArray<hkWorldOperation::BiggestOperation>* tmpOldPending)
{
	hkpDebugInfoOnPendingOperationQueues* queue = world->m_pendingOperationQueues;
	queue = hkpDebugInfoOnPendingOperationQueues::getLastQueue(queue);

	HK_ASSERT(0, queue->m_nextQueue == HK_NULL);
	HK_ASSERT2(0, queue->m_pending == &world->m_pendingOperations->m_pending, "Internal: checking whether current m_pending (operations) array is properly recoginzed by debug code.");
	queue->m_nextQueue = new hkpDebugInfoOnPendingOperationQueues(&world->m_pendingOperations->m_pending);
	queue->m_pending = tmpOldPending;
	queue->m_nextQueue->m_prevQueue = queue;
}

	// tmpOldPending -- is passed for assert only
void HK_CALL hkpDebugInfoOnPendingOperationQueues::removeLastPendingOperationQueue(hkpWorld* world, hkArray<hkWorldOperation::BiggestOperation>* tmpOldPending)
{
	hkpDebugInfoOnPendingOperationQueues* queue = world->m_pendingOperationQueues;
	queue = hkpDebugInfoOnPendingOperationQueues::getLastQueue(queue);
	
	HK_ASSERT(0, queue->m_pending->getSize() == 0);
	HK_ASSERT(0, queue->m_prevQueue->m_nextPendingOperationIndex == queue->m_prevQueue->m_pending->getSize());
	queue->m_prevQueue->m_nextPendingOperationIndex = 0;


	HK_ASSERT2(0, queue->m_prevQueue->m_pending == tmpOldPending, "Internal: checking whether current m_pending (operations) array is properly recoginzed by debug code.");
	queue->m_prevQueue->m_nextQueue = HK_NULL;
	queue->m_prevQueue->m_pending = &world->m_pendingOperations->m_pending;
	delete queue;
}

int HK_CALL hkpDebugInfoOnPendingOperationQueues::getNumPendingOperationQueues(hkpWorld* world)
{
	hkpDebugInfoOnPendingOperationQueues* queue = world->m_pendingOperationQueues;
	queue = hkpDebugInfoOnPendingOperationQueues::getLastQueue(queue);

	int numQueues = 0;
	while(queue != HK_NULL)
	{
		numQueues++;
		queue = queue->m_prevQueue;
	}

	return numQueues;
}

// more functions for querying 

// Searching through pending lists:
//   gotoTheLastOne
//   start from the nextPendingOperationIndex and process till end
//     goto previousQueue and repeat
//   while previousQueue != HK_NULL

const hkWorldOperation::BaseOperation* hkpDebugInfoOnPendingOperationQueues::findFirstPendingIslandMerge(hkpWorld* world, hkpSimulationIsland* isleA, hkpSimulationIsland* isleB)
{
	HK_ASSERT(0, world == isleA->m_world && world == isleB->m_world);

	hkpDebugInfoOnPendingOperationQueues* queue = world->m_pendingOperationQueues;
	queue = hkpDebugInfoOnPendingOperationQueues::getLastQueue(queue);

	while(queue != HK_NULL)
	{
		for (int i = queue->m_nextPendingOperationIndex; i < queue->m_pending->getSize(); i++)
		{
			hkWorldOperation::BaseOperation& op = queue->m_pending->operator[](i);
			if (op.m_type == hkWorldOperation::ISLAND_MERGE)
			{
				hkWorldOperation::MergeIslands& cop = static_cast<hkWorldOperation::MergeIslands&>(op);
				hkpSimulationIsland* refA = cop.m_entities[0]->getSimulationIsland();
				hkpSimulationIsland* refB = cop.m_entities[1]->getSimulationIsland();
				if (refA == isleA && refB == isleB){ return &op; }
				if (refA == isleB && refB == isleA){ return &op; }
			}
		
		}
		queue = queue->m_prevQueue;
	}

	return HK_NULL;
}

const hkBool hkpDebugInfoOnPendingOperationQueues::areEmpty(hkpWorld* world)
{
	hkpDebugInfoOnPendingOperationQueues* queue = world->m_pendingOperationQueues;
	queue = hkpDebugInfoOnPendingOperationQueues::getLastQueue(queue);

	while(queue != HK_NULL)
	{
		if ( queue->m_nextPendingOperationIndex < queue->m_pending->getSize())
		{
			return false;
		}
		queue = queue->m_prevQueue;
	}

	return true;

}
#endif // HK_DEBUG

/*
* Havok SDK - CLIENT RELEASE, BUILD(#20070919)
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
