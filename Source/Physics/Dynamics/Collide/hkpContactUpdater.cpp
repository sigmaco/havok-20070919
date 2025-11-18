/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Collide/hkpContactUpdater.h>
#include <Physics/Dynamics/Entity/hkpEntity.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Collide/hkpDynamicsContactMgr.h>
#include <Physics/Collide/Agent/hkpCollisionAgent.h>
#include <Physics/ConstraintSolver/Constraint/Contact/hkpContactPointProperties.h>
#include <Physics/Internal/Collide/Agent3/hkpAgent3.h>

void HK_CALL hkpContactUpdater::defaultFrictionUpdateCallback( hkpContactUpdateEvent& event )
{
	for ( int j = 0; j < event.m_contactPointIds.getSize(); ++j )
	{
		hkpContactPointProperties* prop = event.m_contactMgr.getContactPointProperties(event.m_contactPointIds[j]);

		const hkpMaterial& materialA = static_cast<hkpEntity*>(event.m_collidableA.getOwner())->getMaterial();
		const hkpMaterial& materialB = static_cast<hkpEntity*>(event.m_collidableB.getOwner())->getMaterial();

		prop->setFriction( hkpMaterial::getCombinedFriction( materialA.getFriction(), materialB.getFriction() ) );

	}
}

static inline void fireIslandContacts( hkpEntity* entity, hkpSimulationIsland* island, hkpContactUpdater::ContactUpdateCallback cb )
{
	hkpLinkedCollidable& collidableEx = *entity->getLinkedCollidable();
	for (int i = 0; i < collidableEx.m_collisionEntries.getSize(); i++)
	{
		hkpAgentNnEntry* entry = collidableEx.m_collisionEntries[i].m_agentEntry;

		HK_ASSERT(0xf0ff008e, entry->m_contactMgr != HK_NULL);

		hkpCollidable* collA = entry->getCollidableA();
		hkpCollidable* collB = entry->getCollidableB();
		hkpContactUpdateEvent event( static_cast<hkpDynamicsContactMgr&>(*entry->m_contactMgr), *collA, *collB);

		event.m_contactMgr.getAllContactPointIds(event.m_contactPointIds);
		event.m_callbackFiredFrom = entity;

		cb( event );
	}
}

void hkpContactUpdater::updateContacts( hkpEntity* entity, hkpContactUpdater::ContactUpdateCallback cb )
{
	HK_ASSERT2(0x76d83a81, entity->getWorld() != HK_NULL, "You are trying to update contact points for a rigid body which has not been added to the world");
	HK_ASSERT(0x59c69847, entity->getSimulationIsland() != HK_NULL );
	
	if ( !entity->isFixed() )
	{
		fireIslandContacts( entity, entity->getSimulationIsland(), cb );
	}
	else
	{
		// have to go through ALL islands to update contacts to update a fixed body
		hkpWorld* world = entity->getWorld();
		{
			for ( int i = 0; i < world->getActiveSimulationIslands().getSize(); ++i )
			{
				fireIslandContacts( entity, world->getActiveSimulationIslands()[i], cb );
			}
		}
		{
			for ( int i = 0; i < world->getInactiveSimulationIslands().getSize(); ++i )
			{
				fireIslandContacts( entity, world->getInactiveSimulationIslands()[i], cb );
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
