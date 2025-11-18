/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Dynamics/hkpDynamics.h>


#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Common/Base/Algorithm/UnionFind/hkUnionFind.h>

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>

#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseHandle.h>
#include <Physics/Collide/Shape/hkpShape.h>
#include <Physics/Collide/Agent/hkpProcessCollisionOutput.h>

#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseDispatcher.h>
#include <Physics/Collide/Dispatch/ContactMgr/hkpContactMgrFactory.h>
#include <Physics/Collide/Agent/hkpCollisionAgent.h>
#include <Physics/Collide/Agent/hkpProcessCollisionOutput.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>

#include <Physics/Collide/Filter/hkpCollisionFilter.h>

#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>
#include <Physics/Internal/Collide/Agent3/Machine/hkpAgentMachineUtil.h>

#include <Physics/Dynamics/Collide/hkpDynamicsContactMgr.h>
#include <Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h>

#include <Physics/Dynamics/Motion/hkpMotion.h>
#include <Physics/Dynamics/Constraint/Setup/hkpConstraintSolverSetup.h>

#include <Physics/Dynamics/Entity/Util/hkpEntityCallbackUtil.h>

#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/hkpWorld.h>

#include <Physics/Dynamics/World/Util/hkpWorldOperationQueue.h>
#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>


// used for backstepping
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/Action/hkpAction.h>
#include <Physics/Dynamics/World/Util/hkpNullAction.h>

#include <Physics/Dynamics/World/Util/hkpWorldAgentUtil.h>
#if HK_POINTER_SIZE==4
HK_COMPILE_TIME_ASSERT( sizeof( hkpSimulationIsland ) <= 180 );
#endif


hkpSimulationIsland::hkpSimulationIsland( hkpWorld* world ) 
:	m_world( world ),
	m_dirtyListIndex(HK_INVALID_OBJECT_INDEX),
	m_highFrequencyDeactivationCounter(0),
	m_lowFrequencyDeactivationCounter(0),
	m_splitCheckRequested(false),
	m_actionListCleanupNeeded (false),
	m_isInActiveIslandsArray(true),
	m_active(true),
	m_inIntegrateJob(false),
	m_timeSinceLastHighFrequencyCheck(0),
	m_timeSinceLastLowFrequencyCheck(0),
	m_timeOfDeactivation(-10.0f) // !! MUST BE DIFFERENT THAN DEFAULT TIME OF SEPARATING NORMAL OF AGENTS
{
	m_allowIslandLocking = false;
	m_constraintInfo.clear();
	m_numConstraints = 0;
	m_sparseEnabled = false;
#ifdef HK_PLATFORM_HAS_SPU
	// make sure we allocate at least 16 bytes to force the memory to be aligned on a 16 byte boundard.
	m_entities.reserve(4);
#endif
	HK_ON_DETERMINISM_CHECKS_ENABLED( m_uTag = hkUint32(-1) );
}

hkpSimulationIsland::~hkpSimulationIsland()
{
	HK_ASSERT2(0, m_dirtyListIndex == HK_INVALID_OBJECT_INDEX, "Island was not properly removed from the hkpWorld::m_dirtySimulationIsland list.");
	for (int i = 0; i < m_actions.getSize(); i++)
	{
		HK_ASSERT2(0xf0ff0093, m_actions[i] == hkpNullAction::getNullAction(), "Internal error: actions present in a simulation island upon its destruction.");	
	}
	HK_ASSERT(0xf0ff0023, m_numConstraints == 0 );
	HK_ASSERT2(0xf0ff0094, !m_entities.getSize(), "Internal error: entities present in a simulation island upon its destruction.");
	HK_ASSERT2(0xf0ff0095, !m_agentTrack.m_sectors.getSize(), "Internal error: agents present in a simulation island upon its destruction.");
}

void hkpSimulationIsland::internalAddEntity(hkpEntity* entity)
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RW );
	HK_ASSERT2(0x6cf66cf2,  entity->getSimulationIsland() == HK_NULL, "addEntity - entity already added to an island" );

	entity->m_simulationIsland = this;
	entity->m_storageIndex = (hkObjectIndex)m_entities.getSize();
	m_entities.pushBack(entity);
}

void hkpSimulationIsland::internalRemoveEntity(hkpEntity* entity)
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RW );
	HK_ASSERT2(0x42cea5f3,  entity->getSimulationIsland() == this, "removeEntity - entity not added to this island" );

	// remove the entity
	{
		HK_ASSERT2(0x74438d73,  m_entities.indexOf( entity ) == entity->m_storageIndex, "Internal error" );

		m_entities[entity->m_storageIndex] = m_entities[m_entities.getSize() - 1];
		m_entities[entity->m_storageIndex]->m_storageIndex = entity->m_storageIndex;
		m_entities.popBack();
	}

	entity->m_simulationIsland = HK_NULL;
	entity->m_storageIndex = HK_INVALID_OBJECT_INDEX;

	m_splitCheckRequested = true;
}



void hkpSimulationIsland::calcStatistics( hkStatisticsCollector* collector ) const
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RO );
	collector->beginObject( HK_NULL, collector->MEMORY_RUNTIME,  this );
	
	//
	// entities
	//
	{
		collector->addArray( "EntityPtrs", collector->MEMORY_RUNTIME, m_entities );
		for ( int i = 0; i < m_entities.getSize(); ++i )
		{
			hkpEntity* entity = m_entities[i];
			collector->addChildObject( "Entity", collector->MEMORY_INSTANCE, entity);

			//
			// constraints details
			//
			{
				collector->pushDir( "Constraints" );
				collector->addSmallArray("ConMstPtr", collector->MEMORY_RUNTIME, entity->m_constraintsMaster);
				collector->addArray("ConSlvPtr", collector->MEMORY_RUNTIME, entity->m_constraintsSlave);
				for ( int j = 0; j < entity->m_constraintsMaster.getSize(); ++j )
				{
					const hkpConstraintInstance* instance = entity->m_constraintsMaster[j].m_constraint;
					if (instance->getAllocatedSize() != 0)	{	collector->addChildObject( "ConInstance",	 collector->MEMORY_INSTANCE,  instance );	}	// <os.todo.aa move into collector

					const hkpConstraintData* data = entity->m_constraintsMaster[j].m_constraint->getData();
					if ( data->getAllocatedSize() != 0)		{	collector->addChildObject( "ConData", collector->MEMORY_SHARED, data );		}
				}
				collector->addArray( "Runtime",	 collector->MEMORY_ENGINE, entity->m_constraintRuntime );
				collector->popDir(  );
			}
		}
	}

	
	//
	// actions
	//
	{
		collector->addArray( "ActionPtrs", collector->MEMORY_RUNTIME, m_actions );
		for ( int i = 0; i < m_actions.getSize(); ++i )
		{
			collector->addChildObject( "Actions", collector->MEMORY_INSTANCE, m_actions[i] );
		}
	}

	//
	// agents
	//
	hkpAgentMachineUtil::calcNnStatisticsContactMgrsOnly(m_agentTrack, collector);

	collector->pushDir( "CollAgents" );
		hkpAgentMachineUtil::calcNnStatistics(m_agentTrack, *m_world->getCollisionInput(), collector);
	collector->popDir();

	collector->endObject();
}





static inline hkReal getClosestDist( hkpProcessCollisionOutput& result )
{
	hkReal closestDist = HK_REAL_MAX;

	for (int i = 0; i < result.getNumContactPoints(); ++i )
	{
		if ( result.m_contactPoints[i].m_contact.getDistance() < closestDist )
		{
			closestDist = result.m_contactPoints[i].m_contact.getDistance();
		}
	}

	return closestDist;

}



//
// Very simple backstepping - we backstep each entity as it collides. We do not recurse, or revisit each pair.
// Hence an object hitting a wall can hit objects the far side of the wall...
//


void hkpSimulationIsland::addAction( hkpAction* act )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RW );
	HK_ASSERT(0xf0ff0028, act->getSimulationIsland() == HK_NULL);

	m_actions.pushBack( act );
	act->setSimulationIsland(this);
}


void hkpSimulationIsland::removeAction( hkpAction* act )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RW );
	int actIdx = m_actions.indexOf( act );
	
	HK_ASSERT2(0x1aa2186f,  actIdx >= 0, "Action is unknown to the physics" );

	m_actions[actIdx] = hkpNullAction::getNullAction();
	//m_actions.removeAtAndCopy( actIdx );
	act->setSimulationIsland(HK_NULL);

	m_splitCheckRequested = true;	
	m_actionListCleanupNeeded = true;
}


hkBool hkpSimulationIsland::isFullyConnected( hkUnionFind& checkConnectivityOut )
{	
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RO );

	HK_ON_DEBUG( int numberOfAgents = 0);
	HK_ON_DEBUG( int numberOfConstraints = 0 );

	//
	// Check edges for collision pairs
	// info: interate over entities and their agent/partner lists 
	//
	{
		for (int e = 0; e < m_entities.getSize(); e++)
		{
			hkpLinkedCollidable* collidable = &m_entities[e]->m_collidable;
			for (int i = 0; i < collidable->m_collisionEntries.getSize(); i++)
			{
				HK_ON_DEBUG( numberOfAgents++);
				hkpLinkedCollidable* partnerCollidable = collidable->m_collisionEntries[i].m_partner;

				hkpEntity* partnerEntity = static_cast<hkpEntity*>(partnerCollidable->getOwner());
				if (!partnerEntity->isFixed())
				{
					int idx = partnerEntity->m_storageIndex;

					checkConnectivityOut.addEdge( e, idx );

					if ( checkConnectivityOut.isOneGroup() )
					{
						return true;
					}

				}
			}
		}
	}
	
	//
	// Check edges for constraints
	//
	{
		for ( int e = 0; e < m_entities.getSize(); e++)
		{
			hkpEntity* entity = m_entities[e];
			for ( int i = 0; i < entity->m_constraintsMaster.getSize(); ++i )
			{
				HK_ON_DEBUG( numberOfConstraints++);
				hkConstraintInternal* con = &entity->m_constraintsMaster[i];
				if ( !con->m_entities[0]->isFixed() && !con->m_entities[1]->isFixed())
				{
					int a = con->m_entities[0]->m_storageIndex;
					int b = con->m_entities[1]->m_storageIndex;
					checkConnectivityOut.addEdge( a, b );
					if ( checkConnectivityOut.isOneGroup() )
					{
						return true;
					}
				}
			}
		}
	}	

	
	//
	// Check edges for actions
	//
	{
		hkInplaceArray<hkpEntity*,10> actionEntities;
		for ( int i = 0; i < m_actions.getSize(); ++i )
		{
			if (m_actions[i] != hkpNullAction::getNullAction())
			{
				actionEntities.clear();
				m_actions[i]->getEntities( actionEntities );

				int j = 0;
				int firstUnfixed = -1;
				while ( (firstUnfixed == -1) && (j < actionEntities.getSize()) )
				{
					if (!actionEntities[j]->isFixed())
					{
						firstUnfixed = j;
					}
					j++;
				}
	
				for ( ; j < actionEntities.getSize(); ++j )
				{
					if (!actionEntities[j]->isFixed())
					{
						int a = actionEntities[firstUnfixed]->m_storageIndex;
						int b = actionEntities[j]->m_storageIndex;
	
						checkConnectivityOut.addEdge( a, b );
						if ( checkConnectivityOut.isOneGroup() )
						{
							return true;
						}
					}
				}
			}
		}
	}
	//HK_ON_DEBUG( HK_WARN_ALWAYS(0xf0323412, "Agents " << numberOfAgents << "  constraints:" <<numberOfConstraints ));

	return checkConnectivityOut.isOneGroup();
}

HK_FORCE_INLINE hkBool hkSimulationIsland_isSameIsland( hkpSimulationIsland*islandA, hkpSimulationIsland*islandB )
{
	if ( islandA == islandB )
	{
		return true;
	}

	HK_ASSERT( 0xf0458745, islandA->m_world == islandB->m_world );
	if ( islandA->isFixed())
	{
		return true;
	}
	if ( islandB->isFixed())
	{
		return true;
	}

	return false;
}

#if defined HK_DEBUG
hkBool hkSimulationIsland_isSameIslandOrToBeMerged( hkpWorld* world, hkpSimulationIsland*islandA, hkpSimulationIsland*islandB )
{
	if ( islandA == islandB )
	{
		return true;
	}

	HK_ASSERT( 0xf0458745, islandA->m_world == islandB->m_world );
	if ( islandA->isFixed())
	{
		return true;
	}
	if ( islandB->isFixed())
	{
		return true;
	}

	const hkWorldOperation::BaseOperation* op = hkpDebugInfoOnPendingOperationQueues::findFirstPendingIslandMerge(world, islandA, islandB);
	if (op)
	{
		return true;
	}
	return false;
}
#endif

void hkpSimulationIsland::isValid()
{
#ifdef HK_DEBUG
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RO );
	// check if dirty index is ok.
	HK_ASSERT(0, m_dirtyListIndex == HK_INVALID_OBJECT_INDEX || m_world->m_dirtySimulationIslands[m_dirtyListIndex] == this);

	if ( 0 )
	{
		if ( !isFixed() )
		{
			if ( m_isInActiveIslandsArray )
			{
				HK_ASSERT(0x2f4b5bff, m_world->getActiveSimulationIslands().indexOf(this) == m_storageIndex);
			}
			else
			{
				HK_ASSERT(0x6d89676a, m_world->getInactiveSimulationIslands().indexOf(this) == m_storageIndex);
			}
		}
	}

	// check the constraints
	{
		hkpConstraintInfo sumInfo; sumInfo.clear();
		{
			for ( int e = 0; e < m_entities.getSize(); e++)
			{
				hkpEntity* entity = m_entities[e];

				HK_ASSERT(0XAD000106, entity->getSimulationIsland() == this);

				{
					for ( int i = 0; i < entity->m_constraintsMaster.getSize(); ++i )
					{
						hkConstraintInternal* intern = &entity->m_constraintsMaster[i];

						hkpEntity* masterEntity = intern->getMasterEntity();
						hkpEntity* slaveEntity = intern->getSlaveEntity();

						HK_ASSERT(0x624a30ff, masterEntity->getSimulationIsland() == this);
						HK_ASSERT(0xad000700, intern->m_priority == intern->m_constraint->getPriority());

						if (slaveEntity->getWorld() == getWorld())
						{
							if ( (!slaveEntity->isFixed()) && slaveEntity->getSimulationIsland() != this )
							{
								HK_ASSERT2(0x23cdd060, hkSimulationIsland_isSameIslandOrToBeMerged( m_world, slaveEntity->getSimulationIsland(), this ), "Constraints connected to two islands, which are not going to be merged" );
							}
						}
						//else
						//{
						//	// todo correct the assert (need to make sure, that futher constraints that link removedEntites will be removed as well)
						//	// THIS ASSERT IS INVALID AND FIRES IN API/RIGIDBODYAPI/MOTIONCHANGE
						//	HK_ASSERT(0XAD000108, getWorld()->m_pendingOperations->findFirstPending(hkWorldOperation::CONSTRAINT_REMOVE, intern->m_constraint));
						//}
						//HK_ASSERT(0x3e2a6a83, intern->m_entities[1]->isFixed() || (intern->m_entities[1]->getSimulationIsland() == this));
						HK_ASSERT(0x3c719c12, slaveEntity->isFixed() || (masterEntity->getSimulationIsland() == this));

						{
							hkpConstraintData::ConstraintInfo info;
							intern->m_constraint->getData()->getConstraintInfo( info );

							if ( intern->m_constraint->m_constraintModifiers)
							{
								hkpModifierConstraintAtom::addAllModifierDataToConstraintInfo( intern->m_constraint->m_constraintModifiers, info ); 
							}

							sumInfo.add( info );
						}

						// check hkConstraintInternal->ConstraintSlave->Constraint->hkConstraintInternal->Constraint inter-points
						HK_ASSERT(0x3bd0155e,  masterEntity == entity);
						HK_ASSERT2(0x285d5d6d, intern->m_constraint->getInternal() == intern, "intern points to a wrong constraint");
						HK_ASSERT2(0x5052cc14, slaveEntity->m_constraintsSlave[intern->m_slaveIndex] == intern->m_constraint, "Constraint slave does not point to the right constraint");

						// start checks from: masters, slaves, island's constraints
					}
				}

				{
					for (int i = 0; i < entity->m_constraintsSlave.getSize(); i++)
					{
						hkpConstraintInstance* con = entity->m_constraintsSlave[i];
						hkConstraintInternal* intern = con->getInternal();

						hkpEntity* masterEntity = intern->getMasterEntity();
						hkpEntity* slaveEntity  = intern->getSlaveEntity();

						if (masterEntity->getWorld() == getWorld())
						{
							if ( (!masterEntity->isFixed()) && masterEntity->getSimulationIsland() != this )
							{
								HK_ASSERT2(0x23cdd060, hkSimulationIsland_isSameIslandOrToBeMerged( m_world, masterEntity->getSimulationIsland(), this ), "Constraints connected to two islands, which are not going to be merged" );
							}
						}
						//else
						//{
						//	// todo correct the assert (need to make sure, that futher constraints that link removedEntites will be removed as well)
						//	// THIS ASSERT IS INVALID AND MIGHT FIRE IN API/RIGIDBODYAPI/MOTIONCHANGE
						//	HK_ASSERT(0XAD000107, getWorld()->m_pendingOperations->findFirstPending(hkWorldOperation::CONSTRAINT_REMOVE, intern->m_constraint));
						//}
						
						HK_ASSERT(0x3bd0155e, slaveEntity == entity);
						HK_ASSERT2(0x49809ddf, intern->m_constraint->getInternal() == intern, "intern points to a wrong constraint");
						HK_ASSERT2(0x22bb9606, slaveEntity->m_constraintsSlave[intern->m_slaveIndex] == intern->m_constraint, "Constraint slave does not point to the right constraint");
					
					}
				}
			}
		}

		HK_ASSERT(0x471403ec,  this->m_constraintInfo.m_maxSizeOfSchema  >= sumInfo.m_maxSizeOfSchema );
		HK_ASSERT(0x6135edae,  this->m_constraintInfo.m_sizeOfSchemas    == sumInfo.m_sizeOfSchemas );
		HK_ASSERT(0x4a8cb6cf,  this->m_constraintInfo.m_numSolverResults == sumInfo.m_numSolverResults );
		HK_ASSERT(0x4a8cb6d0,  this->m_constraintInfo.m_numSolverElemTemps == sumInfo.m_numSolverElemTemps );
	}

	// Checks whether all entities connected via collisionAgnents belong to the same island, or are already pending on the to-be-merged list(, or are fixed).
	// Info: this doesn't work anymore with our implicit recursive pending list
//	{
//		HK_FOR_ALL_AGENT_ENTRIES_BEGIN(this->m_agentTrack, entry)
//		{
//			hkpEntity* entityA = static_cast<hkpEntity*>(entry->m_collidable[0]->getOwner());
//			hkpEntity* entityB = static_cast<hkpEntity*>(entry->m_collidable[1]->getOwner());
//
//
//			if ( !(entityA->isFixed() || entityA->getSimulationIsland() == this) ||
//				 !(entityB->isFixed() || entityB->getSimulationIsland() == this)  )
//			{
//				HK_ASSERT(0x23cdd060, m_world->m_pendingOperations->findFirstPendingIslandMerge(entityA->getSimulationIsland(), entityB->getSimulationIsland()));
//			}
//		
//		}
//		HK_FOR_ALL_AGENT_ENTRIES_END;
//	}



	// Verify that there is only one collisionEntry between any pair of entities 
	{
		for (int e = 0; e < this->m_entities.getSize(); e++)
		{
			hkpLinkedCollidable* collidable = this->m_entities[e]->getLinkedCollidable();

			hkArray<hkpLinkedCollidable::CollisionEntry>& entries = collidable->m_collisionEntries;

			for (int i = 0; i < entries.getSize(); i++)
			{
				hkpLinkedCollidable* partner = entries[i].m_partner;

				for (int j = i+1; j < entries.getSize(); j++)
				{
					HK_ASSERT2(0xf0ff0028, entries[j].m_partner != partner, "There are two top level agents between one pair of entities");
				}
			}

		}
	}


	// check the actions
	{
		if (!isFixed())
		{
			for ( int i = 0; i < m_actions.getSize(); ++i )
			{
				if (m_actions[i] != hkpNullAction::getNullAction())
				{
					hkArray<hkpEntity*> actionEntities;
					m_actions[i]->getEntities( actionEntities );

					HK_ASSERT(0x49414a00,  m_actions[i]->getSimulationIsland() == this || m_actions[i] == hkpNullAction::getNullAction());

					for ( int j = 0; j < actionEntities.getSize(); ++j )
					{
						HK_ASSERT(0x58f9423f, hkSimulationIsland_isSameIslandOrToBeMerged( m_world, actionEntities[j]->getSimulationIsland(), this ) );
					}
				}
			}
		}

		for (int e = 0; e < m_entities.getSize(); e++)
		{
			for (int a = 0; a < m_entities[e]->getNumActions(); a++)
			{
				hkpAction* action = m_entities[e]->getAction(a);
					// the action either is null, or was just removed from the island/world but still hangs on an entiti's actionList, 
				    //	or it must be properly assigned to an island
				HK_ASSERT(0xf0ff0029, action == hkpNullAction::getNullAction() || action->getWorld() != getWorld() || action->getSimulationIsland() == this);
				//HK_ASSERT(0xad000175, m_entities[e]->m_actions[a]);
			}
		}
	}


	hkAgentNnMachine_AssertTrackValidity(m_agentTrack);
#endif		
}



#if 0
hkBool hkpSimulationIsland::shouldDeactivateDeprecated( const hkStepInfo& stepInfo )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW );
	// NOTE: we could remember the last entity that reported active and check that first as an optimization.

	//
	// Check for deactivation
	//
	m_timeSinceLastHighFrequencyCheck += stepInfo.m_deltaTime;
	m_timeSinceLastLowFrequencyCheck += stepInfo.m_deltaTime;

	const hkBool highFreqCheck = m_timeSinceLastHighFrequencyCheck > m_world->getHighFrequencyDeactivationPeriod();
	const hkBool lowFreqCheck = m_timeSinceLastLowFrequencyCheck > m_world->getLowFrequencyDeactivationPeriod();

	if ( highFreqCheck )
	{
		m_timeSinceLastHighFrequencyCheck -= m_world->getHighFrequencyDeactivationPeriod();
		hkBool deactivate  = true;
		for ( int i = 0; i < m_entities.getSize(); ++i )
		{
			hkpEntity* entity = m_entities[i];
			if ( ( entity->getDeactivator() == HK_NULL ) ||	 ( !entity->getDeactivator()->shouldDeactivateHighFrequency( entity ) ) )
			{
				deactivate = false;
				continue;
			}
		}
		if ( deactivate )
		{
			if ( ++m_highFrequencyDeactivationCounter >= 5 )
			{
				m_highFrequencyDeactivationCounter = 0;
				return true;
			}
		}
		else
		{
			m_highFrequencyDeactivationCounter = 0;
		}
	}
	else if ( lowFreqCheck )
	{
		m_timeSinceLastLowFrequencyCheck -= m_world->getLowFrequencyDeactivationPeriod();
		hkBool deactivate = true;
		for ( int i = 0; i < m_entities.getSize(); ++i )
		{
			if ( ( m_entities[i]->getDeactivator() == HK_NULL ) || 
				 ( !m_entities[i]->getDeactivator()->shouldDeactivateLowFrequency( m_entities[i] ) ) )
			{
				deactivate = false;
				continue;
			}
		}
		if ( deactivate )
		{
			if ( ++m_lowFrequencyDeactivationCounter >= 5 )
			{
				m_lowFrequencyDeactivationCounter = 0;
				return true;
			}
		}
		else
		{
			m_lowFrequencyDeactivationCounter = 0;
		}
	}

	return false;
}
#endif

void hkpSimulationIsland::addConstraintToCriticalLockedIsland( hkpConstraintInstance* constraint )
{
	hkpWorldOperationUtil::addConstraintToCriticalLockedIsland( constraint->getEntityA()->getWorld(), constraint );
}

void hkpSimulationIsland::removeConstraintFromCriticalLockedIsland( hkpConstraintInstance* constraint )
{
	hkpWorldOperationUtil::removeConstraintFromCriticalLockedIsland( constraint->getEntityA()->getWorld(), constraint );
}

void hkpSimulationIsland::addCallbackRequest( hkpConstraintInstance* constraint, int request )
{
	HK_ACCESS_CHECK_OBJECT( constraint->getSimulationIsland()->getWorld(), HK_ACCESS_RW );
	constraint->m_internal->m_callbackRequest |= request;
}



void hkpSimulationIsland::mergeConstraintInfo( hkpSimulationIsland& other )
{
	m_constraintInfo.merge( other.m_constraintInfo );
}

void hkpSimulationIsland::markForWrite( )
{
#ifdef HK_DEBUG_MULTI_THREADING
	if ( !m_inIntegrateJob )
	{
		if ( m_world && m_world->m_modifyConstraintCriticalSection )
		{
			HK_ASSERT2( 0xf0213de, m_world->m_modifyConstraintCriticalSection->haveEntered(), "You cannot mark an island for write without having the m_world->m_modifyConstraintCriticalSection entered" );
		}
	}
	m_multiThreadCheck.markForWrite();
#endif
}

#ifdef HK_DEBUG_MULTI_THREADING
void hkpSimulationIsland::checkAccessRw()
{
	// If you get a crash here and you want to understand constraintOwner, you may want to read the reference manual for hkpResponseModifier
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW);
}
#endif

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
