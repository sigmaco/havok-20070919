/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>

#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/Base/Algorithm/UnionFind/hkUnionFind.h>
#include <Common/Base/DebugUtil/DeterminismUtil/hkCheckDeterminismUtil.h>

#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseHandle.h>

#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseDispatcher.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandlePair.h>
#include <Physics/Collide/Filter/hkpCollisionFilter.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Internal/Collide/Agent3/Machine/1n/hkpAgent1nTrack.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>

#include <Physics/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpLinkedCollidable.h>
#include <Physics/Dynamics/Entity/Util/hkpEntityAabbUtil.h>

#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>
#include <Physics/Dynamics/World/Util/hkpWorldOperationQueue.h>
#include <Physics/Dynamics/World/Util/hkpWorldConstraintUtil.h>
#include <Physics/Dynamics/World/Util/hkpWorldAgentUtil.h>
#include <Physics/Dynamics/World/Util/hkpWorldCallbackUtil.h>

#include <Physics/Dynamics/World/Simulation/hkpSimulation.h>
#include <Physics/Internal/Dynamics/World/Simulation/Continuous/hkpContinuousSimulation.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Dynamics/Motion/Rigid/hkpFixedRigidMotion.h>
#include <Physics/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>
#include <Physics/Dynamics/Motion/Util/hkpRigidMotionUtil.h>

#include <Physics/Dynamics/World/Util/hkpNullAction.h>
#include <Physics/Dynamics/Phantom/hkpPhantom.h>




void HK_CALL hkpWorldOperationUtil::sortBigIslandToFront( hkpWorld* world, hkpSimulationIsland* island )
{
	HK_ASSERT(0x3ada00c7,  island->m_isInActiveIslandsArray);
	int storageIndex = island->m_storageIndex;
	if ( storageIndex == 0)
	{
		return;
	}

	world->getActiveSimulationIslands(); // for access check
	hkArray<hkpSimulationIsland*>& activeIslands = world->m_activeSimulationIslands;
	hkpSimulationIsland* other = activeIslands[0];
	if ( island->getEntities().getSize() > other->getEntities().getSize())
	{
		island->m_storageIndex = 0;
		other->m_storageIndex = hkObjectIndex(storageIndex);
		activeIslands[0] = island;
		activeIslands[storageIndex] = other;
	}
}


void hkpWorldOperationUtil::updateEntityBP( hkpWorld* world, hkpEntity* entity )
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RW, entity, HK_ACCESS_RW );
	HK_ASSERT(0, world == entity->m_world);
	// postponed operations

	if ( world->areCriticalOperationsLocked() )
	{
		hkWorldOperation::UpdateEntityBP op;
		op.m_entity = entity;
		world->queueOperation(op);
		return;
	}


	hkpCollidable* collidable = entity->getCollidableRw();
	const hkpShape* shape = collidable->getShape();

	world->lockCriticalOperations();

	HK_ON_DEBUG( world->m_simulation->assertThereIsNoCollisionInformationForEntities(&entity, 1, world) );

	if (shape)
	{
		// add the shape to the broad phase and merge islands as necessary

		hkLocalArray< hkpBroadPhaseHandlePair > newPairs( world->m_broadPhaseQuerySize );
		hkLocalArray< hkpBroadPhaseHandlePair > delPairs( world->m_broadPhaseQuerySize );

		hkAabbUint32 aabb32;

		//
		// Calculate AABB if not yet done (e.g. no IntegrateMotion job was processed yet or (on PS3) the shape was not allowed to go onto SPU).
		//
		if ( !collidable->m_boundingVolumeData.isValid() )
		{
			hkEntityAabbUtil::entityBatchRecalcAabb(world->getCollisionInput(), &entity, 1);
		}

		// Copy the already calculated AABB into our local copy.
		const hkAabbUint32& tmp = collidable->m_boundingVolumeData.getAabbUint32();
		hkVector4Util::uncompressExpandedAabbUint32(tmp, aabb32);

		hkpBroadPhaseHandle* bph = static_cast<hkpBroadPhaseHandle*>(collidable->getBroadPhaseHandle());
		world->m_broadPhase->updateAabbsUint32( &bph, &aabb32, 1, newPairs, delPairs );

		if ( newPairs.getSize() + delPairs.getSize() > 0)
		{
			hkpTypedBroadPhaseDispatcher::removeDuplicates(newPairs, delPairs);
			world->m_broadPhaseDispatcher->removePairs( static_cast<hkpTypedBroadPhaseHandlePair*>(delPairs.begin()), delPairs.getSize() );
			world->m_broadPhaseDispatcher->addPairs(    static_cast<hkpTypedBroadPhaseHandlePair*>(newPairs.begin()), newPairs.getSize(), world->getCollisionFilter() );
		}

	}

	world->unlockAndAttemptToExecutePendingOperations();
}




void hkpWorldOperationUtil::addEntityBP( hkpWorld* world, hkpEntity* entity )
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RW, entity, HK_ACCESS_RW );
	hkpCollidable* c = entity->getCollidableRw();
	const hkpShape* shape = c->getShape();

	if (shape)
	{
		// add the shape to the broad phase and merge islands as necessary
		hkLocalArray< hkpBroadPhaseHandlePair > pairsOut( world->m_broadPhaseQuerySize );

		hkEntityAabbUtil::entityBatchRecalcAabb(world->getCollisionInput(), &entity, 1);

		hkAabbUint32 aabb32 = entity->getCollidable()->m_boundingVolumeData.getAabbUint32();

		world->m_broadPhase->addObject( c->getBroadPhaseHandle(), aabb32, pairsOut );

		if (pairsOut.getSize() > 0)
		{
			world->m_broadPhaseDispatcher->addPairs( static_cast<hkpTypedBroadPhaseHandlePair*>(&pairsOut[0]), pairsOut.getSize(), world->getCollisionFilter() );
		}
	}
}


void hkpWorldOperationUtil::addPhantomBP( hkpWorld* world, hkpPhantom* phantom)
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RW, phantom, HK_ACCESS_RW );
	// Broadphase
	hkLocalArray< hkpBroadPhaseHandlePair > newPairs( world->m_broadPhaseQuerySize );
	
	hkAabb aabb;
	phantom->calcAabb( aabb );
	world->m_broadPhase->addObject( phantom->getCollidableRw()->getBroadPhaseHandle(), aabb, newPairs );

	// check for changes
	if ( newPairs.getSize() != 0 )
	{
		world->m_broadPhaseDispatcher->addPairs( static_cast<hkpTypedBroadPhaseHandlePair*>(&newPairs[0]), newPairs.getSize(), world->getCollisionFilter() );
	}
}


void hkpWorldOperationUtil::addEntitySI( hkpWorld* world, hkpEntity* entity, hkpEntityActivation initialActivationState)
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RW, entity, HK_ACCESS_RW );
	entity->setWorld( world );

	if ( entity->isFixed() )
	{
		world->m_fixedIsland->internalAddEntity( entity );
		return;
	}
#if defined(HK_DEBUG)
	if ( entity->getMotion()->getType() == hkpMotion::MOTION_STABILIZED_BOX_INERTIA || entity->getMotion()->getType() == hkpMotion::MOTION_STABILIZED_SPHERE_INERTIA )
	{
		HK_WARN(0xf0234345, "hkpMotion::MOTION_STABILIZED_BOX_INERTIA and hkpMotion::MOTION_STABILIZED_SPHERE_INERTIA are deprecated" );
	}
#endif

	hkpSimulationIsland* newIsland;
	if (world->m_wantSimulationIslands)
	{

		bool wantActive = initialActivationState == HK_ENTITY_ACTIVATION_DO_ACTIVATE;
		hkArray<hkpSimulationIsland*>& islands = (wantActive) ? world->m_activeSimulationIslands : world->m_inactiveSimulationIslands;

		if ( wantActive)
		{

			// search an island where we can add ourselfs to
			int islandIndex = islands.getSize();
			int listIndexToCheck = hkMath::max2( 0, islandIndex-10 ); // 10 is just an estimate
			while(--islandIndex >= listIndexToCheck)
			{
				hkpSimulationIsland* islandToMerge = islands[islandIndex];
				int islandSize = estimateIslandSize( islandToMerge->m_entities.getSize()+1, islandToMerge->m_numConstraints+3 );
				if ( islandToMerge->m_active != false && canIslandBeSparse( world, islandSize )	)
				{
					newIsland = islands.back();
					newIsland->m_sparseEnabled = true;
					newIsland->internalAddEntity(entity);
					return;
				}
			}
		}
		else if (!world->m_wantDeactivation)
		{
			HK_WARN(0xad000500, "Adding inactive entities while world.m_wantDeactivation == false" );
		}


		{
			newIsland = new hkpSimulationIsland(world);
			newIsland->m_active = wantActive;
			newIsland->m_isInActiveIslandsArray = wantActive;
			newIsland->m_storageIndex = (hkObjectIndex)islands.getSize();
			newIsland->m_splitCheckFrameCounter = hkUchar(newIsland->m_storageIndex);
			islands.pushBack(newIsland);
		}

	}
	else
	{
		HK_ASSERT2(0x71c02c92, initialActivationState == HK_ENTITY_ACTIVATION_DO_ACTIVATE, "Error: Cannot add a deactivated entity when hkpWorld::m_wantSimulationIslands == false." );
		const hkArray<hkpSimulationIsland*>& activeIslands = world->getActiveSimulationIslands();
		newIsland = activeIslands[0];
	}
	newIsland->internalAddEntity(entity);
	newIsland->m_splitCheckFrameCounter = hkUchar(entity->m_uid);
	HK_ON_DETERMINISM_CHECKS_ENABLED( newIsland->m_uTag = entity->m_uid );
}



void hkpWorldOperationUtil::removeEntityBP( hkpWorld* world, hkpEntity* entity )
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RW, entity, HK_ACCESS_RW );

	hkpCollidable* c = entity->getCollidableRw();
	if ( c->getShape() != HK_NULL )
	{
		// Remove all TOI contact points before calling entity-removed callbacks
		world->m_simulation->resetCollisionInformationForEntities(&entity, 1, world, true);

		hkLocalArray< hkpBroadPhaseHandlePair > pairsOut( world->m_broadPhaseQuerySize );

		world->m_broadPhase->removeObject( c->getBroadPhaseHandle(), pairsOut );

		if (pairsOut.getSize() > 0)
		{
			world->m_broadPhaseDispatcher->removePairs( static_cast<hkpTypedBroadPhaseHandlePair*>(&pairsOut[0]), pairsOut.getSize() );
		}
	}
}

void hkpWorldOperationUtil::removePhantomBP( hkpWorld* world, hkpPhantom* phantom)
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RW, phantom, HK_ACCESS_RW );
	//
	//	remove pairs
	//
	{
		hkLocalArray< hkpBroadPhaseHandlePair > removedPairs( world->m_broadPhaseQuerySize );
		world->m_broadPhase->removeObject( phantom->getCollidableRw()->getBroadPhaseHandle(), removedPairs );

		// check for changes
		if ( removedPairs.getSize() != 0 )
		{
			world->m_broadPhaseDispatcher->removePairs( static_cast<hkpTypedBroadPhaseHandlePair*>(&removedPairs[0]), removedPairs.getSize() );
		}
	}
}

void hkpWorldOperationUtil::removeEntitySI( hkpWorld* world, hkpEntity* entity )
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RW, entity, HK_ACCESS_RW );
		// Set world to NULL
	entity->setWorld( HK_NULL );

	hkpSimulationIsland* simIsland = entity->getSimulationIsland();
	// fire the events while the entities simulation island is still valid

	simIsland->internalRemoveEntity( entity );

	// remove the simulation island if it is inactive and has no more entities
	if ( ( !simIsland->isFixed() ) && ( simIsland->m_entities.getSize() == 0 ) && world->m_wantSimulationIslands)
	{
		removeIsland( world, simIsland );
		delete simIsland;
	}
#	if defined (HK_ENABLE_DETERMINISM_CHECKS)
	else
	{
		HK_ASSERT2(0xad875cdd, simIsland->m_entities.getSize() || (!world->m_maintenanceMgr), "Island cannot be empty. With the exeption of ~hkpWorld.");
		if (simIsland->m_entities.getSize())
		{
			simIsland->m_uTag = simIsland->m_entities[0]->getUid();
		}
		else
		{
			simIsland->m_uTag = hkUint32(-1);
		}
	}
#	endif
}


void hkpWorldOperationUtil::removeAttachedActionsFromFixedIsland( hkpWorld* world, hkpEntity* entity, hkArray<hkpAction*>& actionsToBeMoved )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	//
	// We are adding the entity to a new dynamic island from the fixed island.
	//

	//
	//	Moving actions from the fixed island to the moving island
	//
	{

		// Check if any of the entity's actions are on the fixed island's list
		for( int i = 0; i< entity->getNumActions(); i++ )
		{
			hkpAction* action= entity->getAction( i );

			if (action->getSimulationIsland() == world->m_fixedIsland)
			{
				actionsToBeMoved.pushBack(action);
				action->addReference();
				world->m_fixedIsland->removeAction( action);
				world->m_fixedIsland->m_actionListCleanupNeeded = true;
				HK_ASSERT2(0, world->m_fixedIsland->m_active == world->m_fixedIsland->m_isInActiveIslandsArray, "Internal: just checking.");
				putIslandOnDirtyList(world, world->m_fixedIsland);
			}

		}
	}	
}


void hkpWorldOperationUtil::removeAttachedActionsFromDynamicIsland( hkpWorld* world, hkpEntity* entity, hkArray<hkpAction*>& actionsToBeMoved )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	//
	// We are removing the entity from a dynamic island and adding it to the fixed island.
	// Check constraints and actions to see if they also need to be moved to the fixed island.
	//

	hkpSimulationIsland* island = entity->getSimulationIsland(); // HK_NULL;
	HK_ASSERT(0xf0ff0065, island);

	hkInplaceArray<hkpEntity*,16> actionEntities;

	{
		// Check if any of the actions need to be moved to the fixed island.
		for(int i = 0; i < entity->getNumActions(); i++ )
		{
			hkpAction* action = entity->getAction(i);

			action->getEntities( actionEntities );

			hkBool moveAction = true;

			for( int j = 0; j < actionEntities.getSize(); j++ )
			{
				// set moveAction to TRUE if: all other entities attached to the action (besides the one being moved to the fixed island) are fixed
				if( !actionEntities[j]->isFixed() && ( actionEntities[j] != entity ) )
				{
					moveAction = false;
					break;
				}
			}

			if( moveAction )
			{
				actionsToBeMoved.pushBack(action);
				action->addReference();

				HK_ASSERT(0XAD000350, action->getSimulationIsland() == island);

				// remove it from the dynamic island
				island->removeAction( action );
				island->m_actionListCleanupNeeded = true;
				putIslandOnDirtyList(world, island);

			}
		}
	}
}


void hkpWorldOperationUtil::addActionsToEntitysIsland( hkpWorld* world, hkpEntity* entity, hkArray<hkpAction*>& actionsToBeMoved )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	//
	// 	Check constraints and actions and move them and merge islands as necessary.
	//

	hkpSimulationIsland* entitySI = entity->getSimulationIsland();

	hkInplaceArray<hkpEntity*,16> attachedEntities;

	for (int i = 0; i < actionsToBeMoved.getSize(); i++)
	{
		hkpAction* action = actionsToBeMoved[i];
		
		if (entitySI != world->m_fixedIsland)
		{
			// moving to dynamic island


			entitySI->addAction(action);
			action->removeReference();
			//action->setSimulationIsland(entitySI);

			// See if we can merge islands (due to actions)
			attachedEntities.clear();
			action->getEntities( attachedEntities );

			{
				for( int j = 0; j<attachedEntities.getSize(); j++ )
				{
					if( !attachedEntities[j]->isFixed() && ( attachedEntities[j] != entity ) )
					{
						hkpWorldOperationUtil::mergeIslandsIfNeeded( attachedEntities[j], entity );
					}
				}
			}

		}
		else
		{
			// processing fixed island

			// Add the action to the fixed island
			world->m_fixedIsland->addAction( action );
			action->removeReference();
			// Set the fixed island to be the action's island
			//action->setSimulationIsland( world->m_fixedIsland ); done

		}
	}
}


void hkpWorldOperationUtil::removeIsland( hkpWorld* world, hkpSimulationIsland* island )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	if (!island->m_isInActiveIslandsArray )
	{
		world->m_inactiveSimulationIslands[island->m_storageIndex] = world->m_inactiveSimulationIslands[world->m_inactiveSimulationIslands.getSize() - 1];
		world->m_inactiveSimulationIslands[island->m_storageIndex]->m_storageIndex = island->m_storageIndex;
		world->m_inactiveSimulationIslands.popBack();
	}
	else
	{
		world->getActiveSimulationIslands(); // for access checks
		hkArray<hkpSimulationIsland*>& activeIslands = world->m_activeSimulationIslands;

		activeIslands[island->m_storageIndex] = activeIslands.back();
		activeIslands[island->m_storageIndex]->m_storageIndex = island->m_storageIndex;
		activeIslands.popBack();
	}

	removeIslandFromDirtyList(world, island);
	
}


void hkpWorldOperationUtil::addConstraintToCriticalLockedIsland( hkpWorld* world, hkpConstraintInstance* constraint  )
{
	HK_ASSERT2(0xad000103, constraint->getOwner() == HK_NULL, "Error: you are trying to add a constraint, that has already been added to some world");
	HK_ASSERT2(0xf0ff0066, constraint->getEntityA()->getWorld() == world && constraint->getEntityB()->getWorld() == world, "One of the constraint's entities has been already removed from the world (or has not been added yet?).");


	// world locking is not thread safe.
	// so we check for existing locks and use them
	HK_ASSERT( 0xf0ee3234, world->areCriticalOperationsLocked() );
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->getEntityA()->getSimulationIsland(), HK_ACCESS_RW);
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->getEntityB()->getSimulationIsland(), HK_ACCESS_RW);

	hkpWorldConstraintUtil::addConstraint(     world, constraint );
	hkpWorldCallbackUtil::fireConstraintAdded( world, constraint );

#if defined(HK_ENABLE_EXTENSIVE_WORLD_CHECKING) && (HK_CONFIG_THREAD != HK_CONFIG_MULTI_THREADED)
	constraint->getMasterEntity()->getSimulationIsland()->isValid();
#endif
}

void hkpWorldOperationUtil::removeConstraintFromCriticalLockedIsland( hkpWorld* world, hkpConstraintInstance* constraint )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RO );
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->getEntityA()->getSimulationIsland(), HK_ACCESS_RW);
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->getEntityB()->getSimulationIsland(), HK_ACCESS_RW);

	HK_ASSERT2(0x6c6f226b, constraint->getOwner() && static_cast<hkpSimulationIsland*>(constraint->getOwner())->getWorld() == world, "Trying to remove a constraint, that has not been added to the world or was added to a different world.");

	HK_ASSERT( 0xf0ee3234, world->areCriticalOperationsLockedUnchecked() );

	if (world->m_constraintListeners.getSize())
	{
		hkpWorldCallbackUtil::fireConstraintRemoved( world, constraint );
	}
	hkpWorldConstraintUtil::removeConstraint( constraint );

#if defined(HK_ENABLE_EXTENSIVE_WORLD_CHECKING) && (HK_CONFIG_THREAD != HK_CONFIG_MULTI_THREADED)
	constraint->getEntityA()->getSimulationIsland()->isValid();
	constraint->getEntityB()->getSimulationIsland()->isValid();
#endif

}

hkpConstraintInstance* hkpWorldOperationUtil::addConstraintImmediately( hkpWorld* world, hkpConstraintInstance* constraint, FireCallbacks fireCallbacks  )
{
	HK_ASSERT2(0xad000103, constraint->getOwner() == HK_NULL, "Error: you are trying to add a constraint, that has already been added to some world");
	HK_ASSERT2(0xf0ff0066, constraint->getEntityA()->getWorld() == world && constraint->getEntityB()->getWorld() == world, "One of the constraint's entities has been already removed from the world (or has not been added yet?).");

	HK_ASSERT( 0xf0ee3234, !world->areCriticalOperationsLocked() );

// 		// world locking is not thread safe.
// 		// so we check for existing locks and use them
// 	if ( world->areCriticalOperationsLocked() )
// 	{
// 		HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->getEntityA()->getSimulationIsland(), HK_ACCESS_RW);
// 		HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->getEntityB()->getSimulationIsland(), HK_ACCESS_RW);
// 
// 		hkpWorldConstraintUtil::addConstraint( world, constraint );
// 		if (fireCallbacks)
// 		{
// 			hkpWorldCallbackUtil::fireConstraintAdded( world, constraint );
// 		}
// #	ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
// 		island->isValid();
// #	endif
// 	}
// 	else
	{
		HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
		world->lockCriticalOperations();
		hkpWorldConstraintUtil::addConstraint( world, constraint );
		if (fireCallbacks)
		{
			hkpWorldCallbackUtil::fireConstraintAdded( world, constraint );
		}
#	ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
		hkpSimulationIsland* island = static_cast<hkpSimulationIsland*>(constraint->getOwner());
		island->isValid();
#	endif
		world->unlockAndAttemptToExecutePendingOperations();
	}



	return constraint;
}


void hkpWorldOperationUtil::removeConstraintImmediately( hkpWorld* world, hkpConstraintInstance* constraint, FireCallbacks fireCallbacks )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RO );
	HK_ASSERT2(0x6c6f226b, constraint->getOwner() && static_cast<hkpSimulationIsland*>(constraint->getOwner())->getWorld() == world, "Trying to remove a constraint, that has not been added to the world or was added to a different world.");

	hkpSimulationIsland* island = static_cast<hkpSimulationIsland*>(constraint->getOwner());
	island->m_splitCheckRequested = true;

		// world locking is not thread safe.
		// so we check for existing locks and use them
	//HK_ASSERT( 0xf0ee3234, !world->areCriticalOperationsLocked() );
	if ( world->areCriticalOperationsLockedUnchecked() )
	{
		if (fireCallbacks && world->m_constraintListeners.getSize())
		{
			hkpWorldCallbackUtil::fireConstraintRemoved( world, constraint );
		}
		hkpWorldConstraintUtil::removeConstraint( constraint );
#	ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
		island->isValid();
#	endif
	}
	else
	{
		HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
		world->lockCriticalOperations();
		if (fireCallbacks && world->m_constraintListeners.getSize())
		{
			hkpWorldCallbackUtil::fireConstraintRemoved( world, constraint );
		}
		hkpWorldConstraintUtil::removeConstraint( constraint );
#	ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
		island->isValid();
#	endif
		world->unlockAndAttemptToExecutePendingOperations();
	}
	
	return;
}

//
//	Find all groups which are inactive
//
static HK_FORCE_INLINE void findInactiveGroups( const hkUnionFind& checker, const hkArray<hkpEntity*>& entities, const hkpWorld* world, int numGroups, hkFixedArray<int>& isActive )
{
	{ for (int i =0 ; i < numGroups; i++){ isActive[i] = 0; }	}
	const hkUint8* worldSelectFlags = world->m_dynamicsStepInfo.m_solverInfo.m_deactivationNumInactiveFramesSelectFlag;
	{
		for (int i =0 ; i < entities.getSize(); i++ )
		{
			hkpEntity* entity = entities[i];
			hkCheckDeterminismUtil::checkMt(entity->m_motion.getNumInactiveFramesMt(0, worldSelectFlags[0]));
			hkCheckDeterminismUtil::checkMt(entity->m_motion.getNumInactiveFramesMt(1, worldSelectFlags[1]));
			int inactiveFrames = hkMath::max2( entity->m_motion.getNumInactiveFramesMt(0, worldSelectFlags[0]), entity->m_motion.getNumInactiveFramesMt(1, worldSelectFlags[1]) );
			if (inactiveFrames <= hkpMotion::NUM_INACTIVE_FRAMES_TO_DEACTIVATE)
			{
				int group = checker.m_parents[i];
				isActive[group] = 1;
			}
		}
	}
}

// reindex all groups using the following criteria:
// group 0: all active subgroups merged (if any)
//       1..n: all deactive subgroups not merged 
static HK_FORCE_INLINE void identifyDeactivatedSubgroups( hkUnionFind& checker, const hkArray<hkpEntity*>& entities, const hkpWorld* world, hkArray<int>& groupsSizes, hkFixedArray<hkChar>& groupSparse )
{
	HK_ASSERT( 0xf0323f89, entities.getSize() == checker.m_numNodes );
	HK_ASSERT( 0xf04df223, groupSparse.getSizeDebug() >= groupsSizes.getSize()+1 );	// we need an extra element at the end to keep the algorithm simple and fast
	int numOriginalGroups = groupsSizes.getSize();

	hkLocalBuffer<int> isActive( numOriginalGroups );
	findInactiveGroups( checker, entities, world, numOriginalGroups, isActive );
	//
	//	Regroup data. Group 0 is the active group, the other groups are inactive
	//
	int numOutputGroups = 1;	// the first group is the active group

	//
	//	build reindex array so that we get the desired group layout
	//
	int* reindex = isActive.begin();
	groupSparse[0] = true;
	{
		for (int i = 0; i < numOriginalGroups; i++)
		{
			if ( isActive[i] )
			{
				reindex[i] = 0;
			}
			else
			{
				reindex[i] = numOutputGroups;
				groupSparse[numOutputGroups] = false;
				numOutputGroups++;
			}
		}
	}
	{
		// check whether we have only deactivated groups
		if ( numOutputGroups > numOriginalGroups )
		{
			groupSparse[0] = false;
			return;
		}
	}
	checker.reindex( isActive, numOutputGroups, groupsSizes );
}


//
//	Calculate whether a group is active and estimate the size for each constraint for the solver
//
static HK_FORCE_INLINE void findInactiveGroupsAndEstimateSolverSize( const hkUnionFind& checker, const hkArray<hkpEntity*>& entities, int numGroups, hkFixedArray<int>& isActive, hkFixedArray<int>& sizes, hkUint8* deactivationNumInactiveFramesSelectFlag )
{
	hkCheckDeterminismUtil::checkMt(deactivationNumInactiveFramesSelectFlag[0]);
	hkCheckDeterminismUtil::checkMt(deactivationNumInactiveFramesSelectFlag[1]);

	for (int i =0 ; i < entities.getSize(); i++ )
	{
		hkpEntity* entity = entities[i];
		int group = checker.m_parents[i];

		int inactiveFrames = hkMath::max2( entity->m_motion.getNumInactiveFramesMt(0, deactivationNumInactiveFramesSelectFlag[0]), entity->m_motion.getNumInactiveFramesMt(1, deactivationNumInactiveFramesSelectFlag[1]) );
		hkCheckDeterminismUtil::checkMt(entity->m_uid);
		hkCheckDeterminismUtil::checkMt(entity->m_motion.getNumInactiveFramesMt(0, deactivationNumInactiveFramesSelectFlag[0]));
		hkCheckDeterminismUtil::checkMt(entity->m_motion.getNumInactiveFramesMt(1, deactivationNumInactiveFramesSelectFlag[1]));
		if (inactiveFrames <= hkpMotion::NUM_INACTIVE_FRAMES_TO_DEACTIVATE)
		{
			isActive[group] = 1;
		}
		int size = hkpWorldOperationUtil::estimateIslandSize( 1, entity->getConstraintMasters().getSize() );
		sizes[group] += size;
	}
}

static HK_FORCE_INLINE void estimateSolverSize( const hkUnionFind& checker, const hkArray<hkpEntity*>& entities, int numGroups, hkFixedArray<int>& isActive, hkFixedArray<int>& sizes )
{
	{
		for (int i =0 ; i < entities.getSize(); i++ )
		{
			hkpEntity* entity = entities[i];
			int group = checker.m_parents[i];
			isActive[group] = 1;
			int size = hkpWorldOperationUtil::estimateIslandSize( 1, entity->getConstraintMasters().getSize() );
			sizes[group] += size;
		}
	}
}


	// try to group the potential children into reasonable chunks  
	// basic idea: deactivated subgroups do not get merged
	//             merge active groups as long as the combined size still allows for a sparse island
static HK_FORCE_INLINE void mergeSmallSubgroups( hkpWorld* world, hkUnionFind& checker, const hkArray<hkpEntity*>& entities, hkArray<int>& groupsSizes, hkFixedArray<hkChar>& groupSparse )
{
	HK_ASSERT( 0xf0323f89, entities.getSize() == checker.m_numNodes );
	HK_ASSERT( 0xf0323f89, entities.getSize() == checker.m_numNodes );
	int numOriginalGroups = groupsSizes.getSize();

		// the constraint size for each group (-1 if group is inactive and -2 if group is already processed)
	hkLocalBuffer<int> sizes   ( numOriginalGroups );
	hkLocalBuffer<int> isActive( numOriginalGroups );

	{ for (int i =0 ; i < numOriginalGroups; i++){ isActive[i] = 0; sizes[i] = 0; }	}

	if ( world->m_wantDeactivation )
	{
		findInactiveGroupsAndEstimateSolverSize( checker, entities, numOriginalGroups, isActive,sizes,world->m_dynamicsStepInfo.m_solverInfo.m_deactivationNumInactiveFramesSelectFlag );
	}
	else
	{
		estimateSolverSize( checker, entities, numOriginalGroups, isActive,sizes );
	}

		// we only want to use sizes for the final decision.
		// Therefor set the sizes of deactivated groups to -1
	{
		for (int i=0; i < numOriginalGroups; i++)
		{
			if ( !isActive[i]  )
			{
				sizes[i] = -1;
			}
		}
	}


	// try to merge groups. groups taken get a size of -2
	int numOutputGroups = 0;	// the first group is the active group
	int* reindex = isActive.begin();

	// we can merge groups if none of the partners can deactivate and the combined size is still ok
	{
		int extraSize = hkpWorldOperationUtil::estimateIslandSize( 10, 10 );

		for (int i=0; i < numOriginalGroups; i++)
		{
			int groupSize = sizes[i];
			if ( groupSize == -2){ continue; } // group taken already

			int groupId = numOutputGroups++;
			groupSparse[groupId] = false;
			reindex[i] = groupId;

			if ( groupSize < 0)	{ continue; }  // do not merge inactive groups

				// look for other groups we can merge into this one
			for (int j = i+1; j < numOriginalGroups; j++)
			{
				if ( !hkpWorldOperationUtil::canIslandBeSparse(world, groupSize + extraSize) )
				{
					// our current groups is already close to the size limit. Just stop.
					// If we do not do this we might end up wasting lots of CPU 
					// ( Imagine 1000 single objects. Every group being full will still scan the remaining objects resulting in a full n*n algorithm)
					break;
				}
				{
					int otherSize = sizes[j];
					if ( otherSize < 0 )
					{
						// group taken or inactive (->cannot be merged)
						continue;
					}
					if ( hkpWorldOperationUtil::canIslandBeSparse( world, groupSize + otherSize) )
					{
						// merge groups
						groupSparse[groupId] = true;	// now it's no longer fully connected
						reindex[j] = groupId;
						groupSize += otherSize;
						sizes[j] = -2;
					}
				}
			}
		}
	}
	checker.reindex( isActive, numOutputGroups, groupsSizes );
}

void hkpWorldOperationUtil::splitSimulationIsland( hkpSimulationIsland* currentIsland, hkpWorld* world, hkArray<hkpSimulationIsland*>& newIslandsOut, hkArray<hkpEntity*>* oldEntitiesOut )
{
	HK_ON_DETERMINISM_CHECKS_ENABLED( hkCheckDeterminismUtil::checkMt(currentIsland->m_uTag) );
	hkCheckDeterminismUtil::checkMt(currentIsland->m_entities.getSize());

	//
	// Do a union find on the edges (created by actions, constraints, and collision pairs) of the island
	// if there is more than connected group, create new islands accordingly, and add the entities to the
	// islands.
	//
	hkLocalBuffer<int> entityInfo(currentIsland->m_entities.getSize());

	hkFixedArray<int>* fixedArray = &entityInfo;

	hkUnionFind checker( *fixedArray, currentIsland->m_entities.getSize() );

		// this tries to find independent subgroups within the island
	hkBool isConnected = currentIsland->isFullyConnected( checker );

	if ( isConnected )
	{
		currentIsland->m_sparseEnabled = false;
		return;
	}

		// this will hold the size of each independent subgroup
	hkInplaceArray<int,32> groupsSizes; checker.assignGroups( groupsSizes );

		// this will hold the information whether a final subgroup will be fully connected
	hkLocalBuffer<hkChar> groupSparse( groupsSizes.getSize()+1 );


	//
	//	now based on different requirements regroup the existing subgroups
	//  synchronize the lower code with hkpEntity::deactivate
	//
	if ( currentIsland->m_sparseEnabled )
	{
		if ( world->m_wantDeactivation )
		{
			// resort groups: group 0 will be active (if active objects exist), the other groups will hold inactive groups
			identifyDeactivatedSubgroups( checker, currentIsland->m_entities, world, groupsSizes, groupSparse );
			if ( groupsSizes.getSize() == 1 )
			{
				// no need to split a single group. This can only happen if all subgroups are active, otherwise the isConnected check a few lines above will have returned
				return;
			}
		}
		else
		{
			return;	// no need to split a sparse island if we have no deactivation
		}
	}
	else
	{
		if ( world->m_minDesiredIslandSize != 0 )
		{
			// only allow for sparseEnabled islands if the world says this is allowed 
			mergeSmallSubgroups( world, checker, currentIsland->m_entities, groupsSizes, groupSparse );
		}
		else
		{
			hkString::memSet(groupSparse.begin(), 0, groupsSizes.getSize()+1 ); 
		}
	}

		//
		// resort so that biggest group is at index zero
		//
	{
		int index = checker.moveBiggestGroupToIndexZero( groupsSizes );
		hkChar h = groupSparse[0];
		groupSparse[0] = groupSparse[index];
		groupSparse[index] = h;

	}

	int biggestGroupSize = groupsSizes[0];
	int numAllEntities   = currentIsland->getEntities().getSize();

	//
	//	Create all our islands
	//
	int numNewIslands = groupsSizes.getSize();
	if (numNewIslands == 1)
	{
		return;
	}

	hkLocalBuffer<hkpSimulationIsland*> islands( numNewIslands );
	{
		currentIsland->m_sparseEnabled = groupSparse[0] != 0;
		hkCheckDeterminismUtil::checkMt(currentIsland->m_sparseEnabled);

		hkBool active = currentIsland->isActive();
		islands[0] = currentIsland;
		for ( int j = 1; j < numNewIslands; j++)
		{
			hkpSimulationIsland* newIsland = new hkpSimulationIsland( world );
			newIsland->m_active = true;
			newIsland->m_isInActiveIslandsArray = true;
			newIsland->m_sparseEnabled = groupSparse[j] != 0;
			hkCheckDeterminismUtil::checkMt(groupSparse[j]);

			newIsland->m_storageIndex = hkObjectIndex(newIslandsOut.getSize());
			newIslandsOut.pushBack( newIsland );
			islands[j] = newIsland;
			int numEntitiesCapacity = groupsSizes[j];
#if defined(HK_PLATFORM_HAS_SPU)
				// make sure we allocate at least 16 bytes to force the memory to be aligned on a 16 byte boundary.
			numEntitiesCapacity = hkMath::max2( 4, numEntitiesCapacity );
#endif
			newIsland->m_entities.reserveExactly( numEntitiesCapacity );

#ifdef HK_DEBUG_MULTI_THREADING
			newIsland->m_inIntegrateJob = currentIsland->m_inIntegrateJob;
			if ( currentIsland->m_multiThreadCheck.isMarkedForWrite() )
			{
				newIsland->markForWrite();
			}
#endif
		}
	}

	//
	//	Now iterate through our entities and redistribute them
	//
	{	
		// we do a small trick, we simply remember the old entities array and clear it,
		// however we can still access the old members as long as we do not override them
		hkpEntity** oldEntities = currentIsland->m_entities.begin();
		int oldSize = currentIsland->getEntities().getSize();

			// if requested export our old entity array 
		if ( oldEntitiesOut )
		{
			currentIsland->m_entities.swap(*oldEntitiesOut);
			currentIsland->m_entities.clear();
			currentIsland->m_entities.reserveExactly(groupsSizes[0]);
		}
		else
		{
			currentIsland->m_entities.clear();
		}

		for ( int e = 0; e < oldSize; e++ )
		{
			hkpSimulationIsland* newIsland = islands[entityInfo[e]];

			hkpEntity* entity = oldEntities[e];

			entity->m_simulationIsland = newIsland;
			entity->m_storageIndex = (hkObjectIndex)newIsland->m_entities.getSize();
			newIsland->m_entities.pushBackUnchecked(entity);

			//
			//	Update the constraint info
			//
			if ( currentIsland != newIsland )
			{
				hkConstraintInternal* ci = entity->m_constraintsMaster.begin();
				for (int j = 0; j < entity->m_constraintsMaster.getSize(); ci++, j++)
				{
					hkpConstraintInfo info;
					ci->getConstraintInfo(info);
					info.m_maxSizeOfSchema = currentIsland->m_constraintInfo.m_maxSizeOfSchema;
					currentIsland->m_numConstraints--;
					currentIsland->subConstraintInfo( ci->m_constraint, info );

					newIsland->m_numConstraints++;
					ci->m_constraint->setOwner( newIsland );
					newIsland    ->addConstraintInfo( ci->m_constraint, info );
				}
			}
		}
	}



	//
	// If new islands have been created, go through the actions, constraints and collision pairs
	// of the current island, and move them to the correct new islands.
	// Also remove any entities from the current island which have been added to a new island above.
	//
	{
		// update actions
		const hkpSimulationIsland* fixedIsland = world->getFixedIsland();

		hkpAction** oldActions = currentIsland->m_actions.begin();
		int oldActionSize = currentIsland->m_actions.getSize();
		currentIsland->m_actions.clear();

		for ( int j = 0; j < oldActionSize ; j++)
		{
			hkpAction* action = oldActions[j];

			if (action != hkpNullAction::getNullAction())
			{
				//
				// First update the island pointer in the action with the first moving entity's island
				//
				hkpSimulationIsland* movingIsland = HK_NULL;
				{
					hkInplaceArray<hkpEntity*, 16> entities;
					action->getEntities(entities);

					for ( int k = 0; k < entities.getSize(); ++k )
					{
						movingIsland = entities[k]->getSimulationIsland();
						if ( movingIsland != fixedIsland )
						{
							break;
						}
					}
					HK_ASSERT(0x4287f3f7,  movingIsland != HK_NULL );
				}
				action->setSimulationIsland( movingIsland );
				movingIsland->m_actions.pushBack(action);
			}
		}
	}

// BEGIN MOD - HVK-4616
	world->lockForIslandSplit( currentIsland );
// END MOD - HVK-4616
	//
	// Now redistribute the collision detection information
	//
	int entitiesInSmallerGroups = numAllEntities - biggestGroupSize;
	if ( entitiesInSmallerGroups * 8 < numAllEntities )
	{
		// just copy each individual agent entry if the number of objects to move is small
		hkpAgentNnTrack& track = currentIsland->m_agentTrack;
		for ( int sectorIndex = 0; sectorIndex < track.m_sectors.getSize(); sectorIndex++ )		
		{																						
			hkpAgentNnSector* currentSector = track.m_sectors[sectorIndex];			
			hkpAgentNnEntry* entry          = currentSector->getBegin();							

			for( ; entry < hkAddByteOffset( currentSector->getBegin(), track.getSectorSize( sectorIndex ));  )			
			{
				hkpSimulationIsland* newIsland = static_cast<hkpEntity*>(entry->getCollidableA()->getOwner())->getSimulationIsland();
				if ( newIsland->isFixed() )
				{
					newIsland = static_cast<hkpEntity*>( entry->getCollidableB()->getOwner() )->getSimulationIsland();
				}
				if ( newIsland == currentIsland )
				{
					entry = hkAddByteOffset( entry, entry->m_size );
				}
				else
				{
					hkUlong entryOffset = hkGetByteOffset( currentSector, entry );
					hkAgentNnMachine_CopyAndRelinkAgentEntry( newIsland->m_agentTrack, entry);
					hkAgentNnMachine_InternalDeallocateEntry( track, entry );
					if ( sectorIndex >= track.m_sectors.getSize() )
					{
						break;
					}

					// update new entry as our old current sector might have been deleted
					currentSector = track.m_sectors[sectorIndex];
					entry = hkAddByteOffset( currentSector->getBegin(), entryOffset);
				}
			}
		}
	}
	else
		// do a complete distribution of agents
	{
		hkpAgentNnTrack track;

		if (currentIsland->m_agentTrack.m_sectors.getSize() == 1)
		{
			track.m_sectors.pushBackUnchecked(currentIsland->m_agentTrack.m_sectors[0]);
			currentIsland->m_agentTrack.m_sectors.clear();
		}
		else if (currentIsland->m_agentTrack.m_sectors.getSize() > 1)
		{
#if !defined(HK_PLATFORM_HAS_SPU)
			track.m_sectors.reserveExactly(2);	// make sure we do not have an inplace array
			HK_ASSERT( 0xf0322345, track.m_sectors.begin() != &track.m_sectors.m_storage[0]);
#endif
			track.m_sectors.swap( currentIsland->m_agentTrack.m_sectors );
		}
#if !defined(HK_PLATFORM_HAS_SPU)
		hkAlgorithm::swap( track.m_bytesUsedInLastSector, currentIsland->m_agentTrack.m_bytesUsedInLastSector);
#else
		hkAlgorithm::swap( track.m_ppuBytesUsedInLastSector, currentIsland->m_agentTrack.m_ppuBytesUsedInLastSector);
		hkAlgorithm::swap( track.m_spuBytesUsedInLastSector, currentIsland->m_agentTrack.m_spuBytesUsedInLastSector);
		hkAlgorithm::swap( track.m_spuNumSectors	       , currentIsland->m_agentTrack.m_spuNumSectors);
#endif
		{																							
			for ( int sectorIndex = 0; sectorIndex < track.m_sectors.getSize(); sectorIndex++ )		
			{																						
				hkpAgentNnSector* currentSector = track.m_sectors[sectorIndex];			
				hkpAgentNnEntry* entry = currentSector->getBegin();							
				hkpAgentNnEntry* endEntry =  hkAddByteOffset( entry, track.getSectorSize( sectorIndex ) );

				for( ; entry < endEntry; entry = hkAddByteOffset( entry, entry->m_size ) )			
				{
					hkpSimulationIsland* newIsland = static_cast<hkpEntity*>(entry->getCollidableA()->getOwner())->getSimulationIsland();
					if ( newIsland->isFixed() )
					{
						newIsland = static_cast<hkpEntity*>( entry->getCollidableB()->getOwner() )->getSimulationIsland();
					}
					hkAgentNnMachine_CopyAndRelinkAgentEntry(newIsland->m_agentTrack, entry);
				}

				hkThreadMemory::getInstance().deallocateChunk( currentSector, HK_AGENT3_SECTOR_SIZE, HK_MEMORY_CLASS_CDINFO );
			}
			track.m_sectors.clear();
		}
	}

// BEGIN MOD - HVK-4616
	world->unlockForIslandSplit( currentIsland );
// END MOD - HVK-4616
	
	currentIsland->m_agentTrack.m_sectors.optimizeCapacity(4);

	// Assign splitCheckFrameCounter -- needed for deterministic simulation
	HK_ASSERT(0xad8766dd, currentIsland == islands[0]);
	for (int i = 1; i < numNewIslands; i++)
	{
		HK_ASSERT(0xad8766dd, currentIsland != islands[i]);
		islands[i]->m_splitCheckFrameCounter = currentIsland->m_splitCheckFrameCounter + hkUchar(i);
	}

#	if defined (HK_ENABLE_DETERMINISM_CHECKS)
	hkCheckDeterminismUtil::checkMt(numNewIslands);
	hkCheckDeterminismUtil::checkMt(currentIsland->m_uTag);
	HK_ASSERT2(0xad7644dd, numNewIslands < (1 << 16), "");

	for (int i = 1; i < numNewIslands; i++)
	{
		HK_ASSERT(0xad8766dd, currentIsland != islands[i]);
		islands[i]->m_uTag = currentIsland->m_uTag + ((i+1)<<16);
		hkCheckDeterminismUtil::checkMt(islands[i]->m_uTag);
	}
#	endif


#if defined(HK_ENABLE_EXTENSIVE_WORLD_CHECKING)
	{
		currentIsland->markAllEntitiesReadOnly();
		currentIsland->isValid();
		currentIsland->unmarkAllEntitiesReadOnly();
	}
#endif
}

void hkpWorldOperationUtil::splitSimulationIsland( hkpWorld* world, hkpSimulationIsland* currentIsland )
{
#ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
	currentIsland->isValid();
#endif
	bool useActiveIslands = currentIsland->m_isInActiveIslandsArray;
	hkArray<hkpSimulationIsland*>& simulationIslands = useActiveIslands
		? const_cast<hkArray<hkpSimulationIsland*>&>(world->getActiveSimulationIslands())
		: world->m_inactiveSimulationIslands;


	// The island could be empty (the user could have removed all its entities) so delete it if it is.
	HK_ASSERT2(0xad000192, currentIsland->getEntities().getSize(), "Internal error: any empty islands should have been removed in removeEntitySI.");

	currentIsland->m_splitCheckRequested = false;
	{
		int oldSize = simulationIslands.getSize();

		splitSimulationIsland(currentIsland, world, simulationIslands );

		hkBool active = currentIsland->isActive();

		// update deactivation status for new islands
#	if defined(HK_ENABLE_DETERMINISM_CHECKS)
		HK_ASSERT(0xad7644dd, (simulationIslands.getSize()-oldSize) < (1 << 8));
		for ( int j = oldSize, i = 0; j < simulationIslands.getSize(); j++, i++)
#	else
		for ( int j = oldSize; j < simulationIslands.getSize(); j++)
#	endif
		{
			hkpSimulationIsland* newIsland = simulationIslands[j];
			newIsland->m_active					= useActiveIslands;
			newIsland->m_isInActiveIslandsArray = useActiveIslands;
			if (useActiveIslands && !active)
			{
				// the current island is already marked for deactivation
				// mark new islands for deactivation accordingly
				hkpWorldOperationUtil::markIslandInactive( world, newIsland );
			}
			newIsland->m_splitCheckFrameCounter = hkUchar(currentIsland->m_splitCheckFrameCounter - oldSize + j);
			HK_ON_DETERMINISM_CHECKS_ENABLED( newIsland->m_uTag = currentIsland->m_uTag + ((i+1)<<8) );
		}
	}
}

void hkpWorldOperationUtil::splitSimulationIslands( hkpWorld* world )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	// make sure all merges are processed earlier
	HK_ASSERT(0XAD000083, !world->m_pendingOperationsCount);

	// only split islands if we want simulation islands
	if (!world->m_wantSimulationIslands)
	{
		return;
	}

	hkArray<hkpSimulationIsland*>& simulationIslands = const_cast<hkArray<hkpSimulationIsland*>&>(world->getActiveSimulationIslands());
	int originalSize = simulationIslands.getSize();

	for (int i = originalSize - 1; i >= 0; --i)
	{
		hkpSimulationIsland* currentIsland = simulationIslands[i];
		if (!currentIsland->m_splitCheckRequested)
		{
			continue;
		}
		splitSimulationIsland( world, currentIsland );
	}

	// check all the new simulation islands are valid
#	ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
	{
		for (int r = originalSize; r < simulationIslands.getSize(); ++r)
		{
			simulationIslands[r]->isValid();
		}
	}
#	endif
}




void hkpWorldOperationUtil::mergeIslands(hkpWorld* world, hkpEntity* entityA, hkpEntity* entityB)
{
	hkpSimulationIsland* islandA = entityA->getSimulationIsland();
	hkpSimulationIsland* islandB = entityB->getSimulationIsland();

	HK_ASSERT(0xf0ff0067, islandA != islandB);

	if ( world->areCriticalOperationsLocked() )
	{
		hkWorldOperation::MergeIslands op;
		op.m_entities[0] = entityA;
		op.m_entities[1] = entityB;

		world->queueOperation(op);
		return;
	}
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	internalMergeTwoIslands( world, islandA, islandB );
}


hkpSimulationIsland* hkpWorldOperationUtil::internalMergeTwoIslands( hkpWorld* world, hkpSimulationIsland* islandA, hkpSimulationIsland* islandB )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	HK_ASSERT(0x21dd55c1, world->m_wantSimulationIslands);
	HK_INTERNAL_TIMER_BEGIN("MergeIsle", this);

	HK_ASSERT(0xf0ff0068, islandA != islandB);

	HK_ASSERT2(0x63082c41,  (islandA != world->m_fixedIsland) && (islandB != world->m_fixedIsland), "Internal error: an island-merge-request executed for which at least one of the entities is fixed");
	if ( islandA->m_entities.getSize() <= islandB->m_entities.getSize() )
	{
		// we need this check so that our islands are deterministic
		if ( islandA->m_entities.getSize() < islandB->m_entities.getSize() || islandA->m_storageIndex > islandB->m_storageIndex)
		{
			hkAlgorithm::swap( islandA, islandB );
		}
	}
	{
		hkCheckDeterminismUtil::checkSt(islandA->m_storageIndex);
		hkCheckDeterminismUtil::checkSt(islandB->m_storageIndex);
		hkCheckDeterminismUtil::checkSt(islandA->getEntities().getSize());
		hkCheckDeterminismUtil::checkSt(islandB->getEntities().getSize());
		{	for (int i=0; i < islandA->getEntities().getSize(); i++ ){ hkCheckDeterminismUtil::checkSt( islandA->getEntities()[i]->m_uid); } }
		{	for (int i=0; i < islandB->getEntities().getSize(); i++ ){ hkCheckDeterminismUtil::checkSt( islandB->getEntities()[i]->m_uid); } }
	}


	world->lockCriticalOperations();

	//hkBool activate = islandA->m_active || islandB->m_active;
	hkBool activate = islandA->m_isInActiveIslandsArray || islandB->m_isInActiveIslandsArray;
	hkBool finalActiveState = islandA->isActive() || islandB->isActive();
	if (activate)
	{
		if (!islandA->m_isInActiveIslandsArray)
		{
			HK_ASSERT(0xf0ff0069, islandB->m_isInActiveIslandsArray);
			islandA->m_active = true;
			internalActivateIsland(world, islandA);

			islandA->m_highFrequencyDeactivationCounter = islandB->m_highFrequencyDeactivationCounter;
			islandA->m_lowFrequencyDeactivationCounter  = islandB->m_lowFrequencyDeactivationCounter;
		}
		else if (!islandB->m_isInActiveIslandsArray)
		{
			HK_ASSERT(0xf0ff0069, islandA->m_isInActiveIslandsArray);
			islandB->m_active = true;
			internalActivateIsland(world, islandB);

			// islandA has correct high/low-frequency deactivation counters
		}
		else
		{
			islandA->m_highFrequencyDeactivationCounter = hkMath::min2(islandA->m_highFrequencyDeactivationCounter, islandB->m_highFrequencyDeactivationCounter);
			islandA->m_lowFrequencyDeactivationCounter  = hkMath::min2(islandA->m_lowFrequencyDeactivationCounter,  islandB->m_lowFrequencyDeactivationCounter );
		}
	}
	islandA->m_sparseEnabled |= islandB->m_sparseEnabled;

	// Called first so that we can remove any duplicate collision pairs and delete their mgr/agent
// BEGIN MOD - HVK-4616
	world->lockForIslandSplit(islandA);
	islandB->markForWrite();
// END MOD - HVK-4616
	hkAgentNnMachine_AppendTrack(islandA->m_agentTrack, islandB->m_agentTrack);
// BEGIN MOD - HVK-4616
	islandB->unmarkForWrite();
	world->unlockForIslandSplit(islandA);
// END MOD - HVK-4616

	// copy entities, and update entity owners
	{
		hkObjectIndex insertIndex = (hkObjectIndex)islandA->m_entities.getSize();

		islandA->m_entities.setSize(islandA->m_entities.getSize() + islandB->m_entities.getSize());

		for (int i = 0; i < islandB->m_entities.getSize(); ++i, insertIndex++)
		{
			islandA->m_entities[insertIndex] = islandB->m_entities[i];
			islandB->m_entities[i]->m_simulationIsland = islandA;
			islandB->m_entities[i]->m_storageIndex = insertIndex;
		}
	}

	// copy actions
	{
		int insertIndex = islandA->m_actions.getSize();

		islandA->m_actions.setSize(islandA->m_actions.getSize() + islandB->m_actions.getSize());

		for (int i = 0; i < islandB->m_actions.getSize(); ++i)
		{
			if (islandB->m_actions[i] != hkpNullAction::getNullAction())
			{
				islandA->m_actions[insertIndex] = islandB->m_actions[i];
				islandA->m_actions[insertIndex]->setSimulationIsland(islandA);
				insertIndex++;
			}
		}
		islandA->m_actions.setSize(insertIndex);
	}

	// update constraint owners of constraints B (masters only)
	{
		for (int e = 0; e < islandB->m_entities.getSize(); ++e)
		{
			hkpEntity* entity = islandB->m_entities[e];
			hkConstraintInternal* ci = entity->m_constraintsMaster.begin();
			for ( int c = entity->m_constraintsMaster.getSize()-1; c>= 0; ci++, c--)
			{
				hkpConstraintInstance* constraint = ci->m_constraint;
				constraint->setOwner( islandA );
			}
		}
		islandA->mergeConstraintInfo( *islandB );
		islandA->m_numConstraints += islandB->m_numConstraints;
		islandB->m_numConstraints = 0;
	}

	{
		hkArray<hkpSimulationIsland*>* arrayToRemoveFrom;
		hkObjectIndex indexToRemoveAt;
		HK_ASSERT2(0xf0ff00a7, !(activate && !islandA->m_isInActiveIslandsArray), "Internal error");

		{
			if (islandB->m_isInActiveIslandsArray)
			{
				// remove islandB from active
				arrayToRemoveFrom = &world->m_activeSimulationIslands;
				indexToRemoveAt = (hkObjectIndex)islandB->getStorageIndex();

			}
			else
			{
				// remove islandB from inactive 
				arrayToRemoveFrom = &world->m_inactiveSimulationIslands;
				indexToRemoveAt = (hkObjectIndex)islandB->getStorageIndex();
			}
		}

		{
			// removing island from islandsArray
			// input; array to remove from
			//        island to remove / index to remove at
			HK_ASSERT2(0x69b9e470, (*arrayToRemoveFrom)[indexToRemoveAt] == islandA ||
								   (*arrayToRemoveFrom)[indexToRemoveAt] == islandB,   "internal error");

			if (indexToRemoveAt < arrayToRemoveFrom->getSize() - 1)
			{
				// conditional, as we don't want to overwrite the newly assigned m_storageIndex of islandA (see: case (1))
				(*arrayToRemoveFrom)[indexToRemoveAt] = (*arrayToRemoveFrom)[arrayToRemoveFrom->getSize() - 1];
				(*arrayToRemoveFrom)[indexToRemoveAt]->m_storageIndex = indexToRemoveAt;
			}
			(*arrayToRemoveFrom).popBack();
		}
	}

	// Properly copy/update state flags of the merged island
	islandA->m_splitCheckRequested = islandA->m_splitCheckRequested || islandB->m_splitCheckRequested;
	islandA->m_actionListCleanupNeeded = islandA->m_actionListCleanupNeeded || islandB->m_actionListCleanupNeeded;
	islandA->m_active = finalActiveState;

	if (islandB->m_dirtyListIndex != HK_INVALID_OBJECT_INDEX) // done in putIslandOnDirtyIsland: && islandA->m_dirtyListIndex == HK_INVALID_OBJECT_INDEX)
	{
		putIslandOnDirtyList(world, islandA);
	}


	HK_ASSERT(0xf0ff0071, islandA->m_active == islandA->m_isInActiveIslandsArray || islandA->m_dirtyListIndex != HK_INVALID_OBJECT_INDEX);


#ifdef HK_DEBUG
	islandB->m_entities.clear();
	islandB->m_actions.clear();
#endif

	removeIslandFromDirtyList(world, islandB);
	delete islandB;

	if ( islandA->m_isInActiveIslandsArray )
	{
		sortBigIslandToFront( world, islandA );
	}

#	ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
	islandA->isValid();
#	endif
	HK_INTERNAL_TIMER_END();

	world->unlockAndAttemptToExecutePendingOperations();

	return islandA;
}



void hkpWorldOperationUtil::validateWorld( hkpWorld* world )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RO );
	{
		const hkArray<hkpSimulationIsland*>& activeIslands = world->getActiveSimulationIslands();

		for (int i = activeIslands.getSize()-1; i>=0; i--)
		{
			activeIslands[i]->isValid();
		}
	}
	{
		for (int i = world->m_inactiveSimulationIslands.getSize()-1; i>=0; i--)
		{
			world->m_inactiveSimulationIslands[i]->isValid();
		}
	}
	{
		world->m_fixedIsland->isValid();
	}
}

void HK_CALL hkpWorldOperationUtil::setRigidBodyMotionType( hkpRigidBody* body, hkpMotion::MotionType newState, hkpEntityActivation initialActivationState, hkpUpdateCollisionFilterOnEntityMode collisionFilterUpdateMode)
{ 
	HK_ACCESS_CHECK_OBJECT( body->getWorld(), HK_ACCESS_RW );
	// Info on the assert: if unchecked, this causes an error later on, when collision filter is updated on the body,
	// and that causes agent-creation function to crash, when it is given a collidable which doesn't have a shape assigned (as it is
	// with the _FixedBody_).
	HK_ASSERT2(0xad4848b3, !body->getWorld() || body->getWorld()->getFixedRigidBody() != body, "Cannot call setMotionType for hkpWorld::getFixedRigidBody.");

	hkpMotion::MotionType oldState = body->getMotionType();

	// "do nothing" conditions, e.g. can't set original keyframed bodies to dynamic 
	if ( oldState == newState ) 
	{
		return;
	}

	bool newStateNeedsInertia = ( newState != hkpMotion::MOTION_FIXED ) && (newState != hkpMotion::MOTION_KEYFRAMED );
	bool oldStateNeedsInertia = ( oldState != hkpMotion::MOTION_FIXED ) && (oldState != hkpMotion::MOTION_KEYFRAMED );

#ifdef HK_DEBUG
	{
		bool qualityTypeIsFixedOrKeyframedOrKeyframedReporting = (body->getCollidable()->getQualityType() == HK_COLLIDABLE_QUALITY_FIXED || body->getCollidable()->getQualityType() == HK_COLLIDABLE_QUALITY_KEYFRAMED || body->getCollidable()->getQualityType() == HK_COLLIDABLE_QUALITY_KEYFRAMED_REPORTING);
		if (oldStateNeedsInertia == qualityTypeIsFixedOrKeyframedOrKeyframedReporting)
		{
			HK_WARN(0xad4bb4de, "Old quality type doesn't correspond to the old motionType. DO NOT call entity->getCollidable()->setQualityType(HK_COLLIDABLE_QUALITY_chosen_type) before the call to hkpRigidBody::setMotionType(). Quality type changes are now handled by setMotionType internally. ");
			HK_WARN(0xad4bb4de, "This is important as the default collision filtering relies on qualityTypes of bodies (and filters out fixed-fixed, fixed-keyframed, keyframed-keyframed interactions). Also further asserts may be fired when processing TOI events for bodies with such inconsistent motion-quality types settings.");
		}
	}
#endif // HK_DEBUG

	if ( (newStateNeedsInertia && (!oldStateNeedsInertia)) && static_cast<hkpKeyframedRigidMotion*>(body->getMotion())->m_savedMotion == HK_NULL)
	{
		HK_ASSERT2(0x7585f7ab, false, "Attempting to change hkpRigidBody's hkMotionType to a dynamic type. This cannot be performed for bodies which were not initially constructed as dynamic." );
		// do nothing.
		return;
	}

	//adds an extra reference for the scope of this function
	body->addReference();

	hkpWorld* world = body->getWorld();

	bool changeBetweenFixedAndNonFixed = ( oldState == hkpMotion::MOTION_FIXED ) != ( newState == hkpMotion::MOTION_FIXED );
	if( world && changeBetweenFixedAndNonFixed )
	{

			// An array for any constraints that need to be moved to and from the fixed island.
		hkInplaceArray<hkpConstraintInstance*,16> constraintsToBeMoved;
		hkInplaceArray<hkpAction*,16>             actionsToBeMoved;
		hkpAgentNnTrack                           agentsToBeMoved;

		// need to block critical operations executed from within filter update and merge islands
		world->blockExecutingPendingOperations(true);

		world->allowCriticalOperations(false);

		// to be simplified
		hkpWorldOperationUtil::removeAttachedConstraints( body, constraintsToBeMoved );

   		if ( newState != hkpMotion::MOTION_FIXED )
		{
			hkpWorldOperationUtil::removeAttachedActionsFromFixedIsland( world, body, actionsToBeMoved ); //ToDynamicIsland
		}
		else
		{
			hkpWorldOperationUtil::removeAttachedActionsFromDynamicIsland( world, body, actionsToBeMoved ); //ToFixedIsland
		}

		// remove all the agents .
		removeAttachedAgentsConnectingTheEntityAndAFixedPartnerEntityPlus( body->getSimulationIsland()->m_agentTrack, body, agentsToBeMoved, newState);

		if (oldState != hkpMotion::MOTION_FIXED && body->m_simulationIsland->m_entities.getSize() > 2)
		{
			body->m_simulationIsland->m_splitCheckRequested = true;
		}
		
		hkpWorldOperationUtil::removeEntitySI(world, body);
	

		// ^-- above: removing stuff from old island
		{
			// Replace rigid motion object in the body.
			hkpWorldOperationUtil::replaceMotionObject(body, newState, newStateNeedsInertia, oldStateNeedsInertia, world);
		}
		// ,-- below: adding stuff to new island


		hkpWorldOperationUtil::addEntitySI(world, body, initialActivationState);
		hkpWorldOperationUtil::addActionsToEntitysIsland(world, body, actionsToBeMoved );

		world->allowCriticalOperations(true);

		for ( int i = 0; i < constraintsToBeMoved.getSize();i++)
		{
			hkpConstraintInstance* constraint = constraintsToBeMoved[i];

			// merge islands performed here:
			hkpWorldOperationUtil::addConstraintImmediately(world, constraint, hkpWorldOperationUtil::DO_NOT_FIRE_CALLBACKS_AND_SUPPRESS_EXECUTION_OF_PENDING_OPERATIONS );

			constraint->removeReference();
		}

		// Append all moved agents to the track of the new island
		{

			// And do not forget to merge islands (if motion type changed from fixed to dynamic)
			if (newState != hkpMotion::MOTION_FIXED)
			{
				// We have to go through the whole list of collisionPartners of the entity and check for necessary merges.
				
				hkArray<hkpLinkedCollidable::CollisionEntry>& collisionEntries = body->getLinkedCollidable()->m_collisionEntries;
				for (int i = 0; i < collisionEntries.getSize(); i++)
				{
					hkpRigidBody* otherBody = static_cast<hkpRigidBody*>(collisionEntries[i].m_partner->getOwner());
					hkpWorldOperationUtil::mergeIslandsIfNeeded(body, otherBody);
				}

			}

			hkAgentNnMachine_AppendTrack(body->getSimulationIsland()->m_agentTrack, agentsToBeMoved);
		}

		// update sweptTransform
		if (newState == hkpMotion::MOTION_FIXED)
		{
			hkMotionState* ms = body->getRigidMotion()->getMotionState();
				// have event time here...........
			hkSweptTransformUtil::freezeMotionState(world->m_dynamicsStepInfo.m_stepInfo.m_startTime, *ms);

			world->lockCriticalOperations();
			// invalidate TIMs + remove TOI events
			// <todo> rename this function:
			world->m_simulation->resetCollisionInformationForEntities(reinterpret_cast<hkpEntity**>(&body), 1, world );
			// create discrete Aabb
			hkpSimulation::collideEntitiesBroadPhaseDiscrete(reinterpret_cast<hkpEntity**>(&body), 1, world);
			// update graphics !
			hkpWorldCallbackUtil::fireInactiveEntityMoved(body->m_world, body);
			world->unlockCriticalOperations();
		}

		// Destroy or create agents (according to new quality type)
		world->updateCollisionFilterOnEntity(body, collisionFilterUpdateMode, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS);

		// ?? ignore agents -- don't warptime

		world->blockExecutingPendingOperations(false);
		world->attemptToExecutePendingOperations();
	}
	else // 	if( world && changeBetweenFixedAndNonFixed )
	{
		// Replace rigid motion object in the body.
		hkpWorldOperationUtil::replaceMotionObject(body, newState, newStateNeedsInertia, oldStateNeedsInertia, world);

		// When changing from dynamic to key-framed motion, we remove TOI events (because keyframed-keyframed & keyframed-fixed TOI's are not allowed).
		// We don't do that when changing from keyframed to dynamic motion.
		// When changing from/to fixed motion, TOI events are removed by calls to entityRemoveSI().
		if (world)
		{
			// Destroy or create agents (according to new quality type). This also removes Toi events.
			world->updateCollisionFilterOnEntity(body, collisionFilterUpdateMode, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS);
		}
	}

	body->removeReference();
}


	// this is meant to be only used with hkpRigidBody::setMotionType
void HK_CALL hkpWorldOperationUtil::removeAttachedConstraints( hkpEntity* entity, hkArray<hkpConstraintInstance*>& removedConstraints )
{
	hkpWorld*  world = entity->getWorld();
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );

	// master constraints
	{
		hkSmallArray<hkConstraintInternal>& constraints = entity->m_constraintsMaster;

		for (int i = constraints.getSize()-1; i >= 0; i--)
		{
			hkpConstraintInstance* constraint = constraints[i].m_constraint;
			constraint->addReference();
			hkpWorldOperationUtil::removeConstraintImmediately( world, constraint, hkpWorldOperationUtil::DO_NOT_FIRE_CALLBACKS_AND_SUPPRESS_EXECUTION_OF_PENDING_OPERATIONS );
			removedConstraints.pushBack( constraint );
		}
	}

	// slave constraints
	{
		hkArray<hkpConstraintInstance*>& constraints = entity->m_constraintsSlave;

		for (int i = constraints.getSize()-1; i >= 0; i--)
		{
			hkpConstraintInstance* constraint = constraints[i];
			constraint->addReference();
			hkpWorldOperationUtil::removeConstraintImmediately( world, constraint, hkpWorldOperationUtil::DO_NOT_FIRE_CALLBACKS_AND_SUPPRESS_EXECUTION_OF_PENDING_OPERATIONS );
			removedConstraints.pushBack( constraint );
		}
	}
}


void HK_CALL hkpWorldOperationUtil::removeAttachedAgentsConnectingTheEntityAndAFixedPartnerEntityPlus( hkpAgentNnTrack& trackToScan, hkpEntity* entity, hkpAgentNnTrack& agentsRemoved, hkpMotion::MotionType newMotionType)
{
	HK_ACCESS_CHECK_OBJECT( entity->getWorld(), HK_ACCESS_RW );
	// remove those agents which link to another fixed body

	HK_ASSERT(0, &trackToScan == &entity->m_simulationIsland->m_agentTrack); // that's just what it's ment for.

	// also assert that any non-fixed island is presently in the same simulation island
	for (int i = 0; i < entity->getLinkedCollidable()->m_collisionEntries.getSize(); i++)
	{
		hkpLinkedCollidable::CollisionEntry& entry = entity->getLinkedCollidable()->m_collisionEntries[i];

		hkpRigidBody* otherBody = static_cast<hkpRigidBody*>(entry.m_partner->getOwner());

		if (otherBody->isFixed())
		{
			// If the other entity is fixed, then we move the agentEntry together with the entity -- easy.

			hkpAgentNnEntry* oldAgentEntry = entry.m_agentEntry;

			hkAgentNnMachine_CopyAndRelinkAgentEntry(agentsRemoved, oldAgentEntry);
			hkAgentNnMachine_InternalDeallocateEntry(trackToScan, oldAgentEntry);
		}
		else
		{
			// Info: During broadphase we have the world locked. We still create agents 'asynchronously' (in relation to all
			// hkWorldOperations) there for agents may, and do connect different islands here.

			// Now, if we're just changing to fixed state then we need to make sure this agent stays in the partner entiti's island.
			if (newMotionType == hkpMotion::MOTION_FIXED)
			{
				hkpSimulationIsland* islandOfAgent = hkpWorldAgentUtil::getIslandFromAgentEntry(entry.m_agentEntry, entity->m_simulationIsland, otherBody->m_simulationIsland);
				if (islandOfAgent == entity->m_simulationIsland)
				{
					// Need to move the agent to the other island now
					hkpAgentNnEntry* oldAgentEntry = entry.m_agentEntry;

					hkAgentNnMachine_CopyAndRelinkAgentEntry(otherBody->m_simulationIsland->m_agentTrack, entry.m_agentEntry);
					
					hkAgentNnMachine_InternalDeallocateEntry(trackToScan, oldAgentEntry);
				}
			}

			// If we're changing from fixed -- we don't care -- it's in dynamic already, and we'll get a merge request soon.
		}
	}
}

static HK_FORCE_INLINE hkBool less_hkSimulationIslandPtr( const hkpSimulationIsland* a, const hkpSimulationIsland* b )
{
	if (b == HK_NULL) { return false; }
	if (a == HK_NULL) { return true; }
	return a->m_entities[0]->getUid() < b->m_entities[0]->getUid();
}

void HK_CALL hkpWorldOperationUtil::cleanupDirtyIslands( hkpWorld* world )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );

	hkSort(world->m_dirtySimulationIslands.begin(), world->m_dirtySimulationIslands.getSize(), less_hkSimulationIslandPtr );

	// Info:
	// Dirty islands list is processed by popping the last element. This way it may freely expand and shrink
	// (due to operations performed in activation/deactivation callbacks) and no locking is required.
	while (world->m_dirtySimulationIslands.getSize())
	{
		hkpSimulationIsland* island = world->m_dirtySimulationIslands.back();
		world->m_dirtySimulationIslands.popBack();

		// Process if island was not deleted.
		if (island)
		{
			island->m_dirtyListIndex = HK_INVALID_OBJECT_INDEX;

#			if defined HK_ENABLE_EXTENSIVE_WORLD_CHECKING
				island->isValid();
#			endif 

			// Info:
			// Actions are claned-up first, as that fires no callbacks.
			// Activation/Deactivation is performed at the end, as this fires callbacks which may delete the island.
			// It may also modify the m_dirtySimulationIslands list.

			//
			// Clean up actions if requested
			//
			if (island->m_actionListCleanupNeeded)
			{
				hkArray<hkpAction*>& actions = island->m_actions;

				int freeSlot = -1;
				int a = 0;
				for ( ; a < actions.getSize(); a++)
				{
					if (actions[a] == hkpNullAction::getNullAction())
					{
						freeSlot = a;
						a++;
						break;
					}
				}

				for ( ; a < actions.getSize(); a++)
				{
					if (actions[a] != hkpNullAction::getNullAction())
					{
						actions[freeSlot++] = actions[a];
					}
				}

				if (freeSlot != -1)
				{
					actions.setSize(freeSlot);
				}
				island->m_actionListCleanupNeeded = false;
			}

			//
			// Activate or Deactivate islands
			//
			if (island->m_active != island->m_isInActiveIslandsArray)
			{
				// After the next line the island pointer is unsafe.
				if ( island->m_active )
				{
					internalActivateIsland(world, island);
				}
				else
				{
					internalDeactivateIsland(world, island);
				}
			}

		}
	}
}


void hkpWorldOperationUtil::internalActivateIsland( hkpWorld* world, hkpSimulationIsland* island)
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	HK_ASSERT(0x3ada00c7,  island->m_active && !island->m_isInActiveIslandsArray);
	HK_ASSERT(0xf0381288, world->m_wantSimulationIslands );
	HK_ASSERT(0xf0ff0073, !island->isFixed());

	world->m_inactiveSimulationIslands[island->m_storageIndex] = world->m_inactiveSimulationIslands[world->m_inactiveSimulationIslands.getSize() - 1];
	world->m_inactiveSimulationIslands[island->m_storageIndex]->m_storageIndex = island->m_storageIndex;
	world->m_inactiveSimulationIslands.popBack();

	world->m_activeSimulationIslands.pushBack( island );
	island->m_storageIndex = hkObjectIndex(world->m_activeSimulationIslands.getSize() - 1);

	island->m_isInActiveIslandsArray = true;

	// To ensure that a entity is never deactivated immediately after
	// calling forceActivate(...) we 'reset' the time stamps for the island.
	island->m_timeSinceLastHighFrequencyCheck = 0.f;
	island->m_timeSinceLastLowFrequencyCheck = 0.f;

	//for all entities: update sweptTransform
	{
		for (int e = 0; e < island->m_entities.getSize(); e++)
		{
			hkpRigidBody* body = static_cast<hkpRigidBody*>(island->m_entities[e]);
			hkMotionState* ms = body->getRigidMotion()->getMotionState();
			hkSweptTransformUtil::setTimeInformation(hkTime(0.0f), 0.0f, *ms);

			// Initialize activation data
			hkpMotion* motion = body->getRigidMotion();

			motion->m_deactivationNumInactiveFrames[0] = 0;
			motion->m_deactivationNumInactiveFrames[1] = 0;

			hkUint8* deactFlags = world->m_dynamicsStepInfo.m_solverInfo.m_deactivationNumInactiveFramesSelectFlag;
			motion->setWorldSelectFlagsNeg(deactFlags[0], deactFlags[1], world->m_dynamicsStepInfo.m_solverInfo.m_deactivationIntegrateCounter);

			//m_deactivationRefPosition(3) ??
		}
	}

	//for all agents: warpTime
	hkpWorldAgentUtil::warpTime(island, island->m_timeOfDeactivation, world->m_dynamicsStepInfo.m_stepInfo.m_startTime, *world->m_collisionInput);

	sortBigIslandToFront( world, island );

	// removing from dirty array done outside
	hkpWorldCallbackUtil::fireIslandActivated( world, island );
}

void hkpWorldOperationUtil::internalDeactivateIsland( hkpWorld* world, hkpSimulationIsland* island)
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	HK_ASSERT( 0xf0381287, world->m_wantSimulationIslands );
	HK_ASSERT(0x6f1641eb,  !island->m_active && island->m_isInActiveIslandsArray);

	// recheck motions for fast velocities
	{
		hkpEntity*const* bodies = island->getEntities().begin();
		int numBodies = island->getEntities().getSize();
		bool canDeactivate = hkRigidMotionUtilCanDeactivateFinal( world->m_dynamicsStepInfo.m_stepInfo, (hkpMotion*const*)bodies, numBodies, HK_OFFSET_OF(hkpEntity, m_motion));
		if ( !canDeactivate )
		{
			island->m_active = true;
			return;
		}
	}


	world->m_inactiveSimulationIslands.pushBack( island );

	world->m_activeSimulationIslands[island->m_storageIndex] = world->m_activeSimulationIslands[world->m_activeSimulationIslands.getSize() - 1];
	world->m_activeSimulationIslands[island->m_storageIndex]->m_storageIndex = island->m_storageIndex;
	world->m_activeSimulationIslands.popBack();

	island->m_storageIndex = hkObjectIndex(world->m_inactiveSimulationIslands.getSize() - 1);
	island->m_isInActiveIslandsArray = false;

	// store time of deactivation to validate TIM information in agents upon island reactivation
	// note: this is world->m_dynamicsStepInfo.m_stepInfo.m_startTime before integration, it therefore refers to t1 of all
	//       hkSweptTransforms
	island->m_timeOfDeactivation = world->m_dynamicsStepInfo.m_stepInfo.m_startTime;

	// Backstep all bodies to the time of deactivation 
	// and  copy t0 := t1
	{
		for (int e = 0; e < island->m_entities.getSize(); e++)
		{
			hkpRigidBody* body = static_cast<hkpRigidBody*>(island->m_entities[e]);
			hkMotionState* ms = body->getRigidMotion()->getMotionState();
			hkSweptTransformUtil::freezeMotionState(island->m_timeOfDeactivation, *ms);

		
			//hkpWorldOperationUtil::updateEntityBP(world, body);

			// Reference rigidMotion directly to avoid re-activation.
			body->getRigidMotion()->setLinearVelocity ( hkVector4::getZero() );
			body->getRigidMotion()->setAngularVelocity( hkVector4::getZero() );
		}
	}

	// removing from dirty array done outside
	hkpWorldCallbackUtil::fireIslandDeactivated( world, island );

	world->checkDeterminism();

}

void hkpWorldOperationUtil::markIslandInactive( hkpWorld* world, hkpSimulationIsland* island )
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	island->m_active = false;	
	putIslandOnDirtyList(world, island);
}

void hkpWorldOperationUtil::markIslandInactiveMt( hkpWorld* world, hkpSimulationIsland* island )
{
	HK_ASSERT2( 0xf02184ed, !world->m_multiThreadCheck.isMarkedForWrite(), "You can only call this function when the engine is in multithreaded mode");
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RO );

	island->m_active = false;
	world->m_islandDirtyListCriticalSection->enter();
		// the next code is identical to putIslandOnDirtyList with the checks removed
	if (island->m_dirtyListIndex == HK_INVALID_OBJECT_INDEX)
	{
		island->m_dirtyListIndex = hkObjectIndex(world->m_dirtySimulationIslands.getSize());
		world->m_dirtySimulationIslands.pushBack(island);
	}
	world->m_islandDirtyListCriticalSection->leave();
}


void hkpWorldOperationUtil::markIslandActive( hkpWorld* world, hkpSimulationIsland* island )
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, island, HK_ACCESS_RW );
	island->m_active = true;
	island->m_lowFrequencyDeactivationCounter = 0;
	island->m_highFrequencyDeactivationCounter = 0;
	putIslandOnDirtyList(world, island);
}

void hkpWorldOperationUtil::removeIslandFromDirtyList( hkpWorld* world, hkpSimulationIsland* island)
{
	HK_ACCESS_CHECK_OBJECT( world, HK_ACCESS_RW );
	HK_ASSERT(0xf0ff0076, world == island->getWorld());
	if (island->m_dirtyListIndex != HK_INVALID_OBJECT_INDEX)
	{
		// Referenced to deleted islands are replaced with HK_NULLs.
		world->m_dirtySimulationIslands[island->m_dirtyListIndex] = HK_NULL;
		island->m_dirtyListIndex = HK_INVALID_OBJECT_INDEX;
	}
}

	// Only used in setMotionType
void hkpWorldOperationUtil::replaceMotionObject(hkpRigidBody* body, hkpMotion::MotionType newState, hkBool newStateNeedsInertia, hkBool oldStateNeedsInertia, hkpWorld* world )
{
	HK_ACCESS_CHECK_OBJECT( body->getWorld(), HK_ACCESS_RW );
	if ( newStateNeedsInertia )
	{
		// cases:
		// - dynamic   -> dynamic
		// - keyframed -> dynamic
		// - fixed     -> dynamic

		// Restore a previously backed-up copy of dynamic motion
		if (!oldStateNeedsInertia)
		{
			// cases:
			// - keyframed -> dynamic
			// - fixed     -> dynamic

			hkpKeyframedRigidMotion* keyframedMotion = static_cast<hkpKeyframedRigidMotion*> (body->getMotion());
			hkpMaxSizeMotion* savedMotion = keyframedMotion->m_savedMotion;

			HK_ASSERT2(0xad675ddd, savedMotion, "Cannot change a fixed or keyframed body into a dynamic body if it has not been initially created as dynamic.");

			// copy selected data from current (keyframed) motion to saved motion
			keyframedMotion->getMotionStateAndVelocitiesAndDeactivationType( savedMotion );
			hkCheckDeterminismUtil::checkMt(savedMotion->getNumInactiveFrames(0));
			hkCheckDeterminismUtil::checkMt(savedMotion->getNumInactiveFrames(1));
			savedMotion->m_deactivationNumInactiveFrames[0] = 0;
			savedMotion->m_deactivationNumInactiveFrames[1] = 0;

			body->setQualityType( hkpCollidableQualityType(keyframedMotion->m_savedQualityTypeIndex) );

			// copy saved motion (incl. above data) back to current motion
			hkString::memCpy16NonEmpty(&body->m_motion, savedMotion, sizeof(hkpMaxSizeMotion)>>4);
			hkString::memSet( hkAddByteOffset(&body->m_motion, sizeof(hkpMotion)), 0, sizeof(hkpMaxSizeMotion)-sizeof(hkpMotion));

			savedMotion->removeReference();

			// try to allocate memory for bounding volume data (i.e. child shape AABB caching)
			body->setCachedShapeData(world, body->getCollidable()->getShape());
		}

		// Replace the current general dynamic motion with a more 'specialized' motion
		if ( body->m_motion.getType() != newState && newState != hkpMotion::MOTION_DYNAMIC )
		{
				// copy everything, including vtable pointer
			hkpMaxSizeMotion oldMotion;	hkString::memCpy16NonEmpty(&oldMotion, &body->m_motion, sizeof(hkpMaxSizeMotion)>>4);
			hkMatrix3 inertiaLocal;
			static_cast<hkpMotion&>(body->m_motion).getInertiaLocal( inertiaLocal );

			hkMotionState* ms = oldMotion.getMotionState();
			hkpRigidBody::createDynamicRigidMotion( newState, oldMotion.getPosition(), oldMotion.getRotation(), oldMotion.getMass(), inertiaLocal, oldMotion.getCenterOfMassLocal(), ms->m_maxLinearVelocity, ms->m_maxAngularVelocity, &body->m_motion );
			hkpMotion* newMotion = &body->m_motion;

			// newMotion->m_motionState->m_objectRadius is assigned below. (Just like ..->m_maxLinearVelocity and ..->m_maxAngularVelocity)
			oldMotion.getMotionStateAndVelocitiesAndDeactivationType( newMotion );

			newMotion->setLinearDamping(  oldMotion.getLinearDamping() );
			newMotion->setAngularDamping( oldMotion.getAngularDamping() );
		}
	}
	else // not newStateNeedsInertia
	{
		// cases:
		// - dynamic   -> keyframed
		// - dynamic   -> fixed
		// - keyframed -> fixed
		// - fixed     -> keyframed

			// copy everything, including vtable pointer
		hkpMaxSizeMotion oldMotion;	hkString::memCpy16NonEmpty( &oldMotion, &body->m_motion, sizeof(hkpMaxSizeMotion)>>4);

		hkpKeyframedRigidMotion* newMotion;
		if ( newState == hkpMotion::MOTION_FIXED )
		{
			// cases:
			// - dynamic   -> fixed
			// - keyframed -> fixed

			newMotion = new (&body->m_motion) hkpFixedRigidMotion( body->getPosition(), body->getRotation() );

			// Copy motion state 
			newMotion->m_motionState = oldMotion.m_motionState;

			// copy deactivation counter (holds deactivation type)
			// (velocities and m_deactivationNumInactiveFrames are zeroed by the constructor)
			newMotion->m_deactivationIntegrateCounter = oldMotion.m_deactivationIntegrateCounter;

			// freeze swept transform
			if (oldMotion.m_motionState.getSweptTransform().getInvDeltaTime() != 0.0f)
			{
				// This is a fixed state so we reset hkMotionState transform and both transforms stored in the hkSweptTransform to the same value.
				hkReal freezeTime = world ? world->getCurrentTime() : oldMotion.m_motionState.getSweptTransform().getBaseTime() + 1.0f / oldMotion.m_motionState.getSweptTransform().getInvDeltaTime();
				hkSweptTransformUtil::freezeMotionState(freezeTime, newMotion->m_motionState );
			}
		}
		else
		{
			// cases:
			// - dynamic -> keyframed
			// - fixed   -> keyframed

			newMotion = new (&body->m_motion) hkpKeyframedRigidMotion( body->getPosition(), body->getRotation() );

			// Copy motion state information from the old motion
			oldMotion.getMotionStateAndVelocitiesAndDeactivationType(newMotion);
		}

		// Manage the backed-up, stored dynamic motion. And assign the newMotion to the body.
		if (oldStateNeedsInertia)
		{
			// cases:
			// - dynamic -> keyframed
			// - dynamic -> fixed

			// Store current/old dynamic motion in the new keyframed/fixed motion
			hkpMaxSizeMotion* savedOldMotion = new hkpMaxSizeMotion();

			// we need to backup the motion container's 'hkReferencedObject' members so that we can restore them after copying the old motion into the container
			hkUint16 memSizeAndFlagsBackup = savedOldMotion->m_memSizeAndFlags;

				// override all members including vtable (sadly this includes the reference count)
			hkString::memCpy16NonEmpty( savedOldMotion, &oldMotion, sizeof(hkpMaxSizeMotion)>>4);

			savedOldMotion->m_memSizeAndFlags = memSizeAndFlagsBackup;
			// manually set the reference counter to 1!
			savedOldMotion->m_referenceCount  = 1;

			newMotion->m_savedMotion = savedOldMotion;
			newMotion->m_savedQualityTypeIndex = hkUint16(body->getCollidable()->getQualityType());

			// deallocate memory for bounding volume data (i.e. child shape AABB caching)
			body->setCachedShapeData(world, body->getCollidable()->getShape());
		}
		else
		{
			// cases:
			// - keyframed -> fixed
			// - fixed     -> keyframed

			hkpKeyframedRigidMotion* oldKeyframedMotion = static_cast<hkpKeyframedRigidMotion*> (&oldMotion);

			// Preserve saved dynamic motion of old motion in the new keyframed/fixed motion
			newMotion->setStoredMotion(oldKeyframedMotion->m_savedMotion);
			newMotion->m_savedQualityTypeIndex = oldKeyframedMotion->m_savedQualityTypeIndex;
		}
		body->m_solverData = 0;
		body->setQualityType( newState == hkpMotion::MOTION_FIXED ? HK_COLLIDABLE_QUALITY_FIXED : HK_COLLIDABLE_QUALITY_KEYFRAMED );
	}

	body->m_collidable.setMotionState( body->getRigidMotion()->getMotionState()); 

	if (world)
	{
		hkpSolverInfo& solverInfo = world->m_dynamicsStepInfo.m_solverInfo;
		hkUint8* deactFlags = solverInfo.m_deactivationNumInactiveFramesSelectFlag;
		body->getMotion()->setWorldSelectFlagsNeg(deactFlags[0], deactFlags[1], solverInfo.m_deactivationIntegrateCounter);
	}

	HK_ASSERT2(0xad56bccd, body->m_collidable.m_allowedPenetrationDepth > 0.0f, "Incorrect motion after a call to setMotionType." );
	HK_ASSERT2(0xad56bcce, body->getRigidMotion()->m_motionState.m_objectRadius > 0.0f, "Incorrect motion after a call to setMotionType." );

}

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
