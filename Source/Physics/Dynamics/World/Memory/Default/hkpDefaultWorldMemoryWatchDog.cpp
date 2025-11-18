/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/World/Memory/Default/hkpDefaultWorldMemoryWatchDog.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/Entity/hkpEntity.h>


hkpDefaultWorldMemoryWatchDog::hkpDefaultWorldMemoryWatchDog( hkInt32 minMemoryAvailable) : hkWorldMemoryAvailableWatchDog(minMemoryAvailable)
{
}


void hkpDefaultWorldMemoryWatchDog::removeObjectsFromIsland( hkpSimulationIsland* island, hkInt32 currentAutoRemoveLevel, hkInt32 targetMemoryAvailable, int& maxFoundAutoRemoveLevelOut )
{
		//
		//	Iterate over all objects in an island and remove all the once with a autoRemoveLevel greater
		//	or equal currentAutoRemoveLevel
		//  For all other objects record the maximum m_autoRemoveLevel
		//
	hkMemory& mem = hkMemory::getInstance();
	for (int i = island->m_entities.getSize() - 1; i >= 0; i--)
	{
		hkpEntity* entity = island->m_entities[i];
		if (entity->m_autoRemoveLevel >= currentAutoRemoveLevel)
		{
			island->m_world->removeEntity(entity);

				// enable the below code if you want to stop immediately after enough memory is free
				// else all objects of the same autoremove level will be removed
            if ( mem.hasMemoryAvailable(targetMemoryAvailable)) { return; }
		}
		else
		{
			maxFoundAutoRemoveLevelOut = hkMath::max2( maxFoundAutoRemoveLevelOut, int(entity->m_autoRemoveLevel) );
		}
	}
}

	//
	// Free enough memory by remove objects from the physics
	//
void hkpDefaultWorldMemoryWatchDog::freeMemory( hkpWorld* world )
{
		// If the world is locked, removing an entity will not free memory but just put a
		// command on the world command queue, so this would be useless
	HK_ASSERT( 0xf0546523, !world->areCriticalOperationsLocked() );

	hkInt32 targetMemoryAvailable = m_minMemoryAvailable;

		// The overall maximum of the autoremove level of the objects not removed.
		// This is used in case we have to reduce the autoremove level
	int maxFoundAutoRemoveLevel = 0;

		//	Iterate over all islands several times until we have freed enough memory
		//  Each time we drop the currentAutoRemoveLevel
		//  As we have active and inactive islands we append both arrays:
		//		Positive numbers indicate an island in the active simulation island array
		//		negative numbers indicate a deactive simulation island
	for ( int currentAutoRemoveLevel = 0x7f; currentAutoRemoveLevel > 0; currentAutoRemoveLevel = maxFoundAutoRemoveLevel)
	{
		maxFoundAutoRemoveLevel = 0;
		const hkArray<hkpSimulationIsland*>& activeIslands = world->getActiveSimulationIslands();
		const hkArray<hkpSimulationIsland*>& inactiveIslands = world->getInactiveSimulationIslands();

		for ( int currentIsland = activeIslands.getSize()-1; currentIsland >= -inactiveIslands.getSize(); currentIsland-- )
		{
				// check for overflow. This can happen if several islands are removed at once
			if ( currentIsland >=  activeIslands.getSize())
			{
				currentIsland = activeIslands.getSize()-1;
				if ( currentIsland < -inactiveIslands.getSize())
				{
					HK_ASSERT2( 0xf032de45, 0, "No islands left to remove objects from" );
					return;
				}
			}

			hkpSimulationIsland* island = (currentIsland>=0) ? activeIslands[currentIsland] : inactiveIslands[-currentIsland-1];

				//	Remove objects and calculate the maxAutoRemove level for the non removed objects
			removeObjectsFromIsland( island, currentAutoRemoveLevel, targetMemoryAvailable, maxFoundAutoRemoveLevel );

			if (hkMemory::getInstance().hasMemoryAvailable(targetMemoryAvailable))
			{
				return;
			}
		}
	}
}



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
