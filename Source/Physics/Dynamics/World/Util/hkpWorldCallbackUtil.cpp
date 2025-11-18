/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/World/Util/hkpWorldCallbackUtil.h>
#include <Physics/Dynamics/World/hkpWorld.h>

#include <Physics/Dynamics/Action/hkpActionListener.h>
#include <Physics/Dynamics/Entity/hkpEntityListener.h>
#include <Physics/Dynamics/Entity/hkpEntityActivationListener.h>
#include <Physics/Dynamics/Phantom/hkpPhantomListener.h>
#include <Physics/Dynamics/Constraint/hkpConstraintListener.h>
#include <Physics/Dynamics/World/Listener/hkpWorldDeletionListener.h>
#include <Physics/Dynamics/World/Listener/hkpIslandActivationListener.h>
#include <Physics/Dynamics/World/Listener/hkpWorldPostCollideListener.h>
#include <Physics/Dynamics/World/Listener/hkpWorldPostSimulationListener.h>
#include <Physics/Dynamics/World/Listener/hkpWorldPostIntegrateListener.h>
#include <Physics/Dynamics/World/Listener/hkpIslandPostCollideListener.h>
#include <Physics/Dynamics/World/Listener/hkpIslandPostIntegrateListener.h>
#include <Physics/Dynamics/Constraint/Contact/hkpContactImpulseLimitBreachedListener.h>
#include <Physics/Dynamics/Collide/hkpCollisionListener.h>

#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Common/Base/Monitor/hkMonitorStream.h>

static inline void HK_CALL cleanupNullPointers( hkArray<void*>& cleanupArray )
{
	for (int i = cleanupArray.getSize() - 1; i >= 0; i-- )
	{
		if ( cleanupArray[i] == HK_NULL )
		{
			cleanupArray.removeAtAndCopy(i);
		}
	}
}

static inline void HK_CALL cleanupNullPointers( hkSmallArray<void*>& cleanupArray )
{
	for (int i = cleanupArray.getSize() - 1; i >= 0; i-- )
	{
		if ( cleanupArray[i] == HK_NULL )
		{
			cleanupArray.removeAtAndCopy(i);
		}
	}
}

void HK_CALL hkpWorldCallbackUtil::fireActionAdded( hkpWorld* world, hkpAction* action )
{
	hkArray<hkpActionListener*>& listen = world->m_actionListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if (listen[i] != HK_NULL)
		{
			HK_TIME_CODE_BLOCK("actAddCb", world);
			listen[i]->actionAddedCallback( action );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}

void HK_CALL hkpWorldCallbackUtil::fireActionRemoved( hkpWorld* world, hkpAction* action )
{
	hkArray<hkpActionListener*>& listen = world->m_actionListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if (listen[i] != HK_NULL)
		{
			HK_TIME_CODE_BLOCK("actRemCb", world);
			listen[i]->actionRemovedCallback( action );	
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );

}

void HK_CALL hkpWorldCallbackUtil::fireEntityAdded( hkpWorld* world, hkpEntity* entity ) 
{
	hkArray<hkpEntityListener*>& listen = world->m_entityListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if (listen[i] != HK_NULL)
		{
			HK_TIME_CODE_BLOCK("entAddCb", entity);
			listen[i]->entityAddedCallback( entity );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}


void HK_CALL hkpWorldCallbackUtil::fireEntityRemoved( hkpWorld* world, hkpEntity* entity ) 
{
	hkArray<hkpEntityListener*>& listen = world->m_entityListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if ( listen[i] != HK_NULL )
		{
			HK_TIME_CODE_BLOCK("entRemCb", entity);
			listen[i]->entityRemovedCallback( entity );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );

}

void HK_CALL hkpWorldCallbackUtil::fireEntityShapeSet( hkpWorld* world, hkpEntity* entity ) 
{
	hkArray<hkpEntityListener*>& listen = world->m_entityListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if (listen[i] != HK_NULL)
		{
			HK_TIME_CODE_BLOCK("setShapeCb", world);
			listen[i]->entityShapeSetCallback( entity );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}

void HK_CALL hkpWorldCallbackUtil::firePhantomAdded( hkpWorld* world, hkpPhantom* Phantom ) 
{
	hkArray<hkpPhantomListener*>& listen = world->m_phantomListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if (listen[i] != HK_NULL)
		{
			HK_TIME_CODE_BLOCK("phntAddCb", Phantom);
			listen[i]->phantomAddedCallback( Phantom );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}


void HK_CALL hkpWorldCallbackUtil::firePhantomRemoved( hkpWorld* world, hkpPhantom* Phantom ) 
{
	hkArray<hkpPhantomListener*>& listen = world->m_phantomListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if ( listen[i] != HK_NULL )
		{
			HK_TIME_CODE_BLOCK("phntRemCb", Phantom);
			listen[i]->phantomRemovedCallback( Phantom );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );

}

void HK_CALL hkpWorldCallbackUtil::firePhantomShapeSet( hkpWorld* world, hkpPhantom* Phantom ) 
{
	hkArray<hkpPhantomListener*>& listen = world->m_phantomListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if (listen[i] != HK_NULL)
		{
			HK_TIME_CODE_BLOCK("setShapeCb", world);
			listen[i]->phantomShapeSetCallback( Phantom );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}

void HK_CALL hkpWorldCallbackUtil::fireConstraintAdded( hkpWorld* world, hkpConstraintInstance* constraint ) 
{
	hkArray<hkpConstraintListener*>& listen = world->m_constraintListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if ( listen[i] != HK_NULL )
		{
			HK_TIME_CODE_BLOCK("conAddCb", world);
			listen[i]->constraintAddedCallback( constraint );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}

void HK_CALL hkpWorldCallbackUtil::fireConstraintRemoved( hkpWorld* world, hkpConstraintInstance* constraint ) 
{
	hkArray<hkpConstraintListener*>& listen = world->m_constraintListeners;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if ( listen[i] != HK_NULL )
		{
			HK_TIME_CODE_BLOCK("conRemCb", world);
			listen[i]->constraintRemovedCallback( constraint );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}


void HK_CALL hkpWorldCallbackUtil::fireContactPointAdded( hkpWorld* world, hkpContactPointAddedEvent& event)
{
	hkArray<hkpCollisionListener*>& listen = world->m_collisionListeners;
	event.m_callbackFiredFrom = HK_NULL;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if ( listen[i] != HK_NULL )
		{
			HK_TIME_CODE_BLOCK("cpAddCb", world);
			listen[i]->contactPointAddedCallback( event );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}
void HK_CALL hkpWorldCallbackUtil::fireContactPointConfirmed( hkpWorld* world, hkpContactPointConfirmedEvent& event)
{
	hkArray<hkpCollisionListener*>& listen = world->m_collisionListeners;
	event.m_callbackFiredFrom = HK_NULL;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if ( listen[i] != HK_NULL )
		{
			HK_TIME_CODE_BLOCK("cpConfCb", world);
			listen[i]->contactPointConfirmedCallback( event );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}

void HK_CALL hkpWorldCallbackUtil::fireContactPointRemoved( hkpWorld* world, hkpContactPointRemovedEvent& event )
{
	hkArray<hkpCollisionListener*>& listen = world->m_collisionListeners;
    event.m_callbackFiredFrom = HK_NULL;
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if ( listen[i] != HK_NULL )
		{
			HK_TIME_CODE_BLOCK("cpRemCb", world);
			listen[i]->contactPointRemovedCallback( event );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}

void HK_CALL hkpWorldCallbackUtil::fireContactProcess( hkpWorld* world, hkpContactProcessEvent& event )
{
	hkArray<hkpCollisionListener*>& listen = world->m_collisionListeners;
    event.m_callbackFiredFrom = HK_NULL;    
	for (int i = listen.getSize()-1; i>=0; i-- )
	{
		if ( listen[i] != HK_NULL )
		{
			HK_TIME_CODE_BLOCK("cpProcCb", world);
			listen[i]->contactProcessCallback( event );
		}
	}
	hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
	cleanupNullPointers( cleanupArray );
}

void HK_CALL hkpWorldCallbackUtil::fireWorldDeleted( hkpWorld* world )
{
	{
		hkArray<hkpWorldDeletionListener*>& listen = world->m_worldDeletionListeners;
		for (int i = listen.getSize()-1; i>=0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("worldDelCb", world);
				listen[i]->worldDeletedCallback( world );
			}
		}
	//	HK_ASSERT2(0x387ea930,  listen.getSize() == 0, "A hkpWorldDeletionListener did not call hkpWorld::removeSimulationListener during a worldDeletedCallback() callback");
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}
}

void HK_CALL hkpWorldCallbackUtil::fireIslandActivated( hkpWorld* world, hkpSimulationIsland* island )
{
	// The function needs to be locked, because it references a specific island which might get removed during execution of this function.
	world->lockCriticalOperations();
	{
		hkArray<hkpIslandActivationListener*>& listen = world->m_islandActivationListeners;
		for ( int i = listen.getSize() - 1; i >= 0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("islActCb", island);
				listen[i]->islandActivatedCallback( island );
			}
		}

		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );

	}
	{
		for (int i = 0; i < island->getEntities().getSize(); ++i)
		{
			hkpEntity* entity = island->getEntities()[i];
			if ( entity->m_extendedListeners) 	 
			{
				hkSmallArray<hkpEntityActivationListener*>& listen = entity->m_extendedListeners->m_activationListeners;

				for ( int j = listen.getSize() - 1; j >= 0; j-- )
				{
					if ( listen[j] != HK_NULL )
					{
						HK_TIME_CODE_BLOCK("entActCb", island);
						listen[j]->entityActivatedCallback( island->getEntities()[i] );
					}
				}

				hkSmallArray<void*>& cleanupArray = reinterpret_cast<hkSmallArray<void*>&>(listen);
				cleanupNullPointers( cleanupArray );
			}
			
		}
	}
	world->unlockAndAttemptToExecutePendingOperations();
}


void HK_CALL hkpWorldCallbackUtil::fireIslandDeactivated( hkpWorld* world, hkpSimulationIsland* island )
{
	// The function needs to be locked, because it references a specific island which might get removed during execution of this function.
	world->lockCriticalOperations();
	{
		hkArray<hkpIslandActivationListener*>& listen = world->m_islandActivationListeners;
		for ( int i = listen.getSize() - 1; i >= 0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("islDeacCb", world);
				listen[i]->islandDeactivatedCallback( island );
			}
		}
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}
	{
		for (int i = 0; i < island->getEntities().getSize(); ++i)
		{
			hkpEntity* entity = island->getEntities()[i];
			if ( entity->m_extendedListeners ) 	 
			{ 	 
				hkSmallArray<hkpEntityActivationListener*>& listen = entity->m_extendedListeners->m_activationListeners;

				for ( int j = listen.getSize() - 1; j >= 0; j-- )
				{
					if ( listen[j] != HK_NULL )
					{
						HK_TIME_CODE_BLOCK("entDeacCb", world);
						listen[j]->entityDeactivatedCallback( island->getEntities()[i] );
					}
				}
			
				hkSmallArray<void*>& cleanupArray = reinterpret_cast<hkSmallArray<void*>&>(listen);
				cleanupNullPointers( cleanupArray );
			}
			
		}
	}
	world->unlockAndAttemptToExecutePendingOperations();
}


void HK_CALL hkpWorldCallbackUtil::firePostSimulationCallback( hkpWorld* world )
{
	{
		hkArray<hkpWorldPostSimulationListener*>& listen = world->m_worldPostSimulationListeners;
		for (int i = listen.getSize()-1; i>=0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("postSimCb", world);
				listen[i]->postSimulationCallback( world );
			}
		}
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}
}


void HK_CALL hkpWorldCallbackUtil::firePostIntegrateCallback( hkpWorld* world, const hkStepInfo& info )
{
	{
		hkArray<hkpWorldPostIntegrateListener*>& listen = world->m_worldPostIntegrateListeners;
		for (int i = listen.getSize()-1; i>=0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("postIntCb", world);
				listen[i]->postIntegrateCallback( world, info );
			}
		}
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}
}

void HK_CALL hkpWorldCallbackUtil::firePostCollideCallback( hkpWorld* world, const hkStepInfo& info )
{
	{
		hkArray<hkpWorldPostCollideListener*>& listen = world->m_worldPostCollideListeners;
		for (int i = listen.getSize()-1; i>=0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("postCollCb", world);
				listen[i]->postCollideCallback( world, info );
			}
		}
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}
}


void HK_CALL hkpWorldCallbackUtil::fireIslandPostIntegrateCallback( hkpWorld* world, hkpSimulationIsland* island, const hkStepInfo& info )
{
	{
		hkArray<hkpIslandPostIntegrateListener*>& listen = world->m_islandPostIntegrateListeners;
		for (int i = listen.getSize()-1; i>=0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("postIntCb", island);
				listen[i]->postIntegrateCallback( island, info );
			}
		}
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}

}

void HK_CALL hkpWorldCallbackUtil::fireIslandPostCollideCallback( hkpWorld* world, hkpSimulationIsland* island, const hkStepInfo& info )
{
	{
		hkArray<hkpIslandPostCollideListener*>& listen = world->m_islandPostCollideListeners;
		for (int i = listen.getSize()-1; i>=0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("postCollCb", island);
				listen[i]->postCollideCallback( island, info );
			}
		}
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}
}

void HK_CALL hkpWorldCallbackUtil::fireContactImpulseLimitBreached( hkpWorld* world, const hkpContactImpulseLimitBreachedListenerInfo* breachedContacts, int numBreachedContacts  )
{
	{
		hkArray<hkpContactImpulseLimitBreachedListener*>& listen = world->m_contactImpulseLimitBreachedListeners;
		for (int i = listen.getSize()-1; i>=0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("impLimitCb", world);
				listen[i]->contactImpulseLimitBreachedCallback( breachedContacts, numBreachedContacts );
			}
		}
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}
}

void HK_CALL hkpWorldCallbackUtil::fireInactiveEntityMoved( hkpWorld* world, hkpEntity* entity)
{
	{
		hkArray<hkpWorldPostSimulationListener*>& listen = world->m_worldPostSimulationListeners;
		for (int i = listen.getSize()-1; i>=0; i-- )
		{
			if ( listen[i] != HK_NULL )
			{
				HK_TIME_CODE_BLOCK("entMvdCb", entity);
				listen[i]->inactiveEntityMovedCallback(entity);
			}
		}
		hkArray<void*>& cleanupArray = reinterpret_cast<hkArray<void*>&>(listen);
		cleanupNullPointers( cleanupArray );
	}
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
