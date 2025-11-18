/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Dynamics/SuspendInactiveAgents/hkpSuspendInactiveAgentsUtil.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Internal/Collide/Agent3/hkpAgent3.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>
#include <Physics/Collide/Filter/hkpCollisionFilter.h>

#include <Physics/Collide/Agent/Collidable/hkpCdBody.h>

hkpSuspendInactiveAgentsUtil::hkpSuspendInactiveAgentsUtil(hkpWorld* world, OperationMode mode, InitContactsMode initContactsMode )
:	m_world(world), m_mode(mode), m_initContactsMode(initContactsMode)
{
	addReference();
	world->addWorldDeletionListener( this );
	world->addIslandActivationListener( this );
}

hkpSuspendInactiveAgentsUtil::~hkpSuspendInactiveAgentsUtil()
{
	if ( m_world )
	{
		m_world->removeWorldDeletionListener( this );
		m_world = HK_NULL;
	}
}
		
namespace {

	class NeverCollideFilter : public hkpCollisionFilter
	{
		virtual hkBool isCollisionEnabled( const hkpCollidable& a, const hkpCollidable& b ) const { return false; }
		virtual	hkBool isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const hkpShapeContainer& bContainer, hkpShapeKey bKey  ) const { return false; }
		virtual hkBool isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& collectionBodyA, const hkpCdBody& collectionBodyB, const HK_SHAPE_CONTAINER& containerShapeA, const HK_SHAPE_CONTAINER& containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB ) const { return false; }
		virtual hkBool isCollisionEnabled( const hkpShapeRayCastInput& aInput, const hkpShape& shape, const hkpShapeContainer& bContainer, hkpShapeKey bKey ) const { return false; }
		virtual hkBool isCollisionEnabled( const hkpWorldRayCastInput& a, const hkpCollidable& collidableB ) const { return false; }
	};

	class Clear1nTracksFilter : public hkpCollisionFilter
	{ 
	public:
		Clear1nTracksFilter( const hkpCollisionFilter* filter ) : m_originalFilter(filter) { HK_ASSERT2(0xad7865dd, m_originalFilter, "Original filter must be specified."); m_originalFilter->addReference(); }

		~Clear1nTracksFilter() { m_originalFilter->removeReference(); }

		virtual hkBool isCollisionEnabled( const hkpCollidable& a, const hkpCollidable& b ) const 
		{
			HK_ASSERT2(0xad78d6a0, false, "This function should be never called."); return true;
		}

		virtual hkBool isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const hkpShapeContainer& bCollection, hkpShapeKey bKey  ) const  
		{	
			if ( b.getShape()->getType() == HK_SHAPE_MOPP 
			  || b.getShape()->getType() == HK_SHAPE_BV_TREE 
			  || b.getShape()->getType() == HK_SHAPE_MOPP_EMBEDDED )
			{
				return false;
			}
			return m_originalFilter->isCollisionEnabled (input, a, b, bCollection, bKey);
		}

		virtual hkBool isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const HK_SHAPE_CONTAINER& containerShapeA, const HK_SHAPE_CONTAINER& containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB ) const
		{
			if (   a.getShape()->getType() == HK_SHAPE_MOPP 
				|| a.getShape()->getType() == HK_SHAPE_BV_TREE 
				|| a.getShape()->getType() == HK_SHAPE_MOPP_EMBEDDED )
			{
				return false;
			}
			if (   b.getShape()->getType() == HK_SHAPE_MOPP 
				|| b.getShape()->getType() == HK_SHAPE_BV_TREE 
				|| b.getShape()->getType() == HK_SHAPE_MOPP_EMBEDDED )
			{
				return false;
			}
			return m_originalFilter->isCollisionEnabled (input, a, b, containerShapeA, containerShapeB, keyA, keyB );
		}

		virtual hkBool isCollisionEnabled( const hkpShapeRayCastInput& aInput, const hkpShape& shape, const hkpShapeContainer& bContainer, hkpShapeKey bKey ) const  
		{	
			HK_ASSERT2(0xad78d6a0, false, "This function should be never called."); return true;
		}

		virtual hkBool isCollisionEnabled( const hkpWorldRayCastInput& a, const hkpCollidable& collidableB ) const  
		{	
			HK_ASSERT2(0xad78d6a0, false, "This function should be never called."); return true;
		}

	protected:
		const hkpCollisionFilter* m_originalFilter;
	};
}

void hkpSuspendInactiveAgentsUtil::islandDeactivatedCallback( hkpSimulationIsland* island )
{
	// This is only called from hkpWorldOperationUtil::cleanupDirtyIslands.
	HK_ACCESS_CHECK_OBJECT( island->getWorld(), HK_ACCESS_RW );
	HK_ASSERT2( 0xad7899de, island->getWorld()->areCriticalOperationsLocked(), "Critical operations are expected to be locked.");

	NeverCollideFilter neverCollideFilter;
	Clear1nTracksFilter clear1nTracksFilter(m_world->getCollisionFilter());

	hkpCollisionInput input = *m_world->getCollisionInput();
	switch(m_mode)
	{
		case SUSPEND_ALL_COLLECTION_AGENTS: input.m_filter = &neverCollideFilter; break;
		case SUSPEND_1N_AGENT_TRACKS:       input.m_filter = &clear1nTracksFilter; break;
	}

	HK_FOR_ALL_AGENT_ENTRIES_BEGIN(island->m_agentTrack, entry)
	{
		hkAgentNnMachine_UpdateShapeCollectionFilter( entry, input, *island );
	}
	HK_FOR_ALL_AGENT_ENTRIES_END;
}

void hkpSuspendInactiveAgentsUtil::islandActivatedCallback( hkpSimulationIsland* island )
{
	// This is only called from hkpWorldOperationUtil::cleanupDirtyIslands and from the engine, e.g. during island merges.
	// This is not safe is the updateShapeCollectioFilter would remove any agents.

	HK_ACCESS_CHECK_OBJECT( island->getWorld(), HK_ACCESS_RW );
	HK_ASSERT2( 0xad7899df, island->getWorld()->areCriticalOperationsLocked(), "Critical operations are expected to be locked.");

	hkpCollisionInput input = *m_world->getCollisionInput();

	if (m_mode == SUSPEND_ALL_COLLECTION_AGENTS)
	{
		HK_FOR_ALL_AGENT_ENTRIES_BEGIN(island->m_agentTrack, entry)
		{
			hkAgentNnMachine_UpdateShapeCollectionFilter( entry, input, *island );
		}
		HK_FOR_ALL_AGENT_ENTRIES_END;
	}

	if (m_initContactsMode == INIT_CONTACTS_FIND)
	{
		m_world->findInitialContactPoints( island->m_entities.begin(), island->m_entities.getSize() );
	}
}

void hkpSuspendInactiveAgentsUtil::worldDeletedCallback( hkpWorld* world )
{
	world->removeWorldDeletionListener( this );
	m_world = HK_NULL;
	removeReference();
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
