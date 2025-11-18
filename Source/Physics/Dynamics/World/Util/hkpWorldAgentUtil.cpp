/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>

#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Physics/Collide/Dispatch/ContactMgr/hkpContactMgrFactory.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Collide/Agent/hkpCollisionAgent.h>
#include <Physics/Collide/Agent/ContactMgr/hkpContactMgr.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnTrack.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>
#include <Physics/Internal/Collide/Agent3/Machine/1n/hkpAgent1nTrack.h>
#include <Physics/Internal/Collide/Agent3/Machine/1n/hkpAgent1nMachine.h>

#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>
#include <Physics/Dynamics/World/Util/hkpWorldAgentUtil.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>

#include <Physics/Dynamics/World/Util/hkpWorldOperationQueue.h>


// If both pointers are the same & point to a fixed island -- return it.
static HK_FORCE_INLINE hkpSimulationIsland* getAnyNonFixedIsland( hkpSimulationIsland* islandA, hkpSimulationIsland* islandB)
{
	if (!islandA->isFixed())
	{
		return islandA;
	}
	if (!islandB->isFixed())
	{
		return islandB;
	}
	HK_ASSERT2(0x48af8302, islandA == islandB, "Internal error: two different fixed islands.");
	return islandA;
}


hkpAgentNnEntry* hkpWorldAgentUtil::addAgent( hkpLinkedCollidable* collA, hkpLinkedCollidable* collB, const hkpProcessCollisionInput& input )
{
	HK_ASSERT2(0Xad000710, !hkAgentNnMachine_FindAgent(collA, collB), "An agent already exists between the two collidables specified.");

	hkpEntity* entityA = static_cast<hkpEntity*>( collA->getOwner() );
	hkpEntity* entityB = static_cast<hkpEntity*>( collB->getOwner() );

	// Request island merge
	hkpWorldOperationUtil::mergeIslandsIfNeeded( entityA, entityB );

	//   Choose the island to add new agent to 
	//   merge might have been delayed
	hkpSimulationIsland* theIsland = getAnyNonFixedIsland(entityA->getSimulationIsland(), entityB->getSimulationIsland());
	HK_ACCESS_CHECK_WITH_PARENT( theIsland->m_world, HK_ACCESS_IGNORE, theIsland, HK_ACCESS_RW );


	//
	//	Get the agent type and flip information
	//
	int agentType;
	int isFlipped;
	hkAgentNnMachine_GetAgentType( collA, collB, input, agentType, isFlipped );
	if ( isFlipped )
	{
		hkAlgorithm::swap( collA, collB );
	}

	//
	// Attempt to create the mgr
	//
	hkpContactMgr* mgr;
	{
		hkpContactMgrFactory* factory = input.m_dispatcher->getContactMgrFactory( entityA->getMaterial().getResponseType(), entityB->getMaterial().getResponseType() );
		mgr = factory->createContactMgr( *collA, *collB, input );
	}

	//
	//	Create the final agent
	//
	hkpAgentNnTrack& track = theIsland->m_agentTrack;
	hkpAgentNnEntry* newAgent = hkAgentNnMachine_CreateAgent( track, collA, collB, agentType, input, mgr );



#	ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
	theIsland->isValid();
#	endif


	return newAgent;



//	// suspend agent
//	if (createSuspended)
//	{
//		// info: if entityA and entityB belong to to active/inactive islands, than whether the agent should/shouln't be created
//		//       only depends on which island we initially assign it to.
//		hkpWorldAgentUtil::suspendAgent(pair);
//	}
//
//	return pair;


}

void hkpWorldAgentUtil::removeAgent( hkpAgentNnEntry* agent )
{
	HK_ON_DEBUG( hkpSimulation* simulation = static_cast<hkpEntity*>( agent->m_collidable[0]->getOwner() )->getSimulationIsland()->getWorld()->m_simulation );
	HK_ON_DEBUG( simulation->assertThereIsNoCollisionInformationForAgent(agent) );

	// Remove hkCollisionPair / agent from hkpSimulationIsland
	hkpSimulationIsland* theIsland;
	hkpEntity* entityA = static_cast<hkpEntity*>( agent->m_collidable[0]->getOwner() );
	hkpEntity* entityB = static_cast<hkpEntity*>( agent->m_collidable[1]->getOwner() );
	hkpSimulationIsland* islandA = entityA->getSimulationIsland();
	hkpSimulationIsland* islandB = entityB->getSimulationIsland();

	if (islandA == islandB)
	{
		theIsland = islandA;
		theIsland->m_splitCheckRequested = true;
	}
	else if (entityA->isFixed())
	{
		// don't check whether the island is fixed, cause you'll get a cache miss on the fixed island :-/
		theIsland = islandB;
	}
	else if (entityB->isFixed())
	{
		theIsland = islandA;
	}
	else
	{
		// This should happen only when you add and remove an agent between entities moving one after another (and belonging to two different islands)
		// in a way that their aabbs overlap in-between collision detection run for each of the islands.

		theIsland = getIslandFromAgentEntry(agent, islandA, islandB);

		// we have those, because we may still have a merge request for those entities in the pendingOperation queue
		//  and this is faster than going through the pendingOperations list. And we are too lazy.
		entityA->getSimulationIsland()->m_splitCheckRequested = true;
		entityB->getSimulationIsland()->m_splitCheckRequested = true;
	}
	HK_ACCESS_CHECK_WITH_PARENT( theIsland->m_world, HK_ACCESS_IGNORE, theIsland, HK_ACCESS_RW );


	hkpAgentNnTrack& track = theIsland->m_agentTrack;
	hkpCollisionDispatcher* dispatch = theIsland->getWorld()->getCollisionDispatcher();

	hkpContactMgr* mgr = agent->m_contactMgr;
	hkAgentNnMachine_DestroyAgent( track, agent, dispatch, *theIsland );
	mgr->cleanup();

#	ifdef HK_ENABLE_EXTENSIVE_WORLD_CHECKING
	theIsland->isValid();
#	endif

	//HK_INTERNAL_TIMER_END_LIST();

}

void hkpWorldAgentUtil::removeAgentAndItsToiEvents ( hkpAgentNnEntry* agent )
{
	hkpSimulation* simulation = static_cast<hkpEntity*>( agent->m_collidable[0]->getOwner() )->getSimulationIsland()->getWorld()->m_simulation;
	simulation->removeCollisionInformationForAgent( agent );

	hkpWorldAgentUtil::removeAgent( agent );
}

hkpSimulationIsland* hkpWorldAgentUtil::getIslandFromAgentEntry( hkpAgentNnEntry* entry, hkpSimulationIsland* candidateA, hkpSimulationIsland* candidateB)
{
	// just iterate over sectors of the shorter track
	hkBool searchIsleA = candidateA->m_agentTrack.m_sectors.getSize() <= candidateB->m_agentTrack.m_sectors.getSize();
	hkpSimulationIsland* isleToSearch = searchIsleA ? candidateA : candidateB;

	hkBool sectorFound = false;
	hkArray<hkpAgentNnSector*>& sectors = isleToSearch->m_agentTrack.m_sectors;
	for (int i = 0; i < sectors.getSize(); i++)
	{
		hkpAgentNnSector* sector = sectors[i];
		if (sector->getBegin() <= entry && entry < sector->getEnd() )
		{
			sectorFound = true;
			break;
		}
	}

	// if the agent is not there, then it's in the other track -- just remove it with hkAgentNnMachine_
	return (searchIsleA ^ sectorFound) ? candidateB : candidateA;
}



HK_FORCE_INLINE static hkpAgentData* getAgentData( hkpAgentNnEntry* entry)
{
	hkAgent3::StreamCommand command = hkAgent3::StreamCommand(entry->m_streamCommand);
	if ( command == hkAgent3::STREAM_CALL_WITH_TIM)
	{
		return hkAddByteOffset<hkpAgentData>( entry, hkSizeOf( hkpAgentNnMachineTimEntry ) );
	}
	else
	{
		return hkAddByteOffset<hkpAgentData>( entry, hkSizeOf( hkpAgentNnMachinePaddedEntry ) );
	}
}

void hkpWorldAgentUtil::updateEntityShapeCollectionFilter( hkpEntity* entity, hkpCollisionInput& collisionInput )
{
	HK_ACCESS_CHECK_OBJECT( entity->getWorld(), HK_ACCESS_RW );
	hkpLinkedCollidable* collidable = entity->getLinkedCollidable();
	for (int i = 0; i < collidable->m_collisionEntries.getSize(); i++)
	{
		hkpAgentNnEntry* entry = collidable->m_collisionEntries[i].m_agentEntry;

		hkAgent3::UpdateFilterFunc func = collisionInput.m_dispatcher->getAgent3UpdateFilterFunc(entry->m_agentType);
		if (func)
		{
				// this cast is allowed, as the nn-machine only works between entities
			hkpEntity* entityA = static_cast<hkpEntity*>(entry->getCollidableA()->getOwner());
			hkpEntity* entityB = static_cast<hkpEntity*>(entry->getCollidableB()->getOwner());
			hkpSimulationIsland* island = (entityA->isFixed() )? entityB->getSimulationIsland(): entityA->getSimulationIsland();

			hkpAgentData* agentData = getAgentData(entry);
			func(entry, agentData, *entry->getCollidableA(), *entry->getCollidableB(), collisionInput, entry->m_contactMgr, *island);
		}
	}
}

void hkpWorldAgentUtil::invalidateTim( hkpEntity* entity, hkpCollisionInput& collisionInput )
{
	hkpLinkedCollidable* collidable = entity->getLinkedCollidable();
	for (int i = 0; i < collidable->m_collisionEntries.getSize(); i++)
	{
		hkpAgentNnEntry* entry = collidable->m_collisionEntries[i].m_agentEntry;
		hkAgentNnMachine_InvalidateTimInAgent( entry, collisionInput );
	}
}

void hkpWorldAgentUtil::warpTime( hkpSimulationIsland* island, hkTime oldTime, hkTime newTime, hkpCollisionInput& collisionInput )
{
	HK_ACCESS_CHECK_WITH_PARENT( island->m_world, HK_ACCESS_RO, island, HK_ACCESS_RW );
	HK_FOR_ALL_AGENT_ENTRIES_BEGIN(island->m_agentTrack, entry)
	{
		hkAgentNnMachine_WarpTimeInAgent(entry, oldTime, newTime, collisionInput );
	}
	HK_FOR_ALL_AGENT_ENTRIES_END;
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
