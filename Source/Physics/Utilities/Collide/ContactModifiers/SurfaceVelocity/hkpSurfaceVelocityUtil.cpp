/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Collide/ContactModifiers/SurfaceVelocity/hkpSurfaceVelocityUtil.h>
#include <Physics/Dynamics/Collide/hkpResponseModifier.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>

hkpSurfaceVelocityUtil::hkpSurfaceVelocityUtil(hkpRigidBody* body, const hkVector4& surfaceVelocityWorld)
{
	this->addReference();

	m_rigidBody = body;
	m_surfaceVelocity = surfaceVelocityWorld;

	m_rigidBody->addCollisionListener( this );
	m_rigidBody->addEntityListener( this );


	m_rigidBody->getCollidableRw()->m_forceCollideOntoPpu |= hkpCollidable::FORCE_PPU_MODIFIER_REQUEST;
}


// The hkpCollisionListener interface implementation
void hkpSurfaceVelocityUtil::contactPointAddedCallback(hkpContactPointAddedEvent& event)
{
	hkpRigidBody *bodyA = hkGetRigidBody(event.m_bodyA->getRootCollidable());
	hkpRigidBody *bodyB = hkGetRigidBody(event.m_bodyB->getRootCollidable());

	hkpDynamicsContactMgr* mgr = event.m_internalContactMgr;
	if ( !mgr )
	{
		mgr = bodyA->findContactMgrTo(bodyB);
	}

	if ( !mgr )
	{
		return;
	}

	hkpConstraintInstance* instance = mgr->getConstraintInstance();
	if ( !instance )
	{
		return;
	}

	hkpResponseModifier::setSurfaceVelocity( mgr, m_rigidBody, *event.m_collisionOutput->m_constraintOwner, m_surfaceVelocity );
}

// The hkpCollisionListener interface implementation
void hkpSurfaceVelocityUtil::contactProcessCallback( hkpContactProcessEvent& event)
{
}

hkpSurfaceVelocityUtil::~hkpSurfaceVelocityUtil()
{
	if( m_rigidBody )
	{
		m_rigidBody->removeCollisionListener( this );
		m_rigidBody->removeEntityListener( this );
	}
}

void hkpSurfaceVelocityUtil::entityDeletedCallback( hkpEntity* entity )
{
	HK_ASSERT(0x24a5384b, entity == m_rigidBody);
	entity->removeCollisionListener( this );
	entity->removeEntityListener( this );
	m_rigidBody = HK_NULL;
	removeReference();
}

void hkpSurfaceVelocityUtil::setSurfaceVelocity( const hkVector4& velWorld )
{
	// performance abort if new velocity equals old velocity
	if ( m_surfaceVelocity.equals3(velWorld, 0.0f) )
	{
		return;
	}

	m_surfaceVelocity = velWorld;

	// iterate over all contact managers and update the modifiers' surface velocity value
	{
		hkpLinkedCollidable& collidableEx = *m_rigidBody->getLinkedCollidable();
		for (int i = 0; i < collidableEx.m_collisionEntries.getSize(); i++)
		{
			hkpAgentNnEntry* entry = collidableEx.m_collisionEntries[i].m_agentEntry;
			HK_ASSERT(0xafff008e, entry->m_contactMgr != HK_NULL);

			hkpDynamicsContactMgr* contactManager = static_cast<hkpDynamicsContactMgr*>(entry->m_contactMgr);

			hkpConstraintInstance* instance = contactManager->getConstraintInstance();
			if ( instance && instance->m_internal )
			{
				hkpSimulationIsland* island = instance->getSimulationIsland();
				hkpResponseModifier::setSurfaceVelocity(contactManager, m_rigidBody, *island, m_surfaceVelocity);
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
