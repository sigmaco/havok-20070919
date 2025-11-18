/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Utilities/Dynamics/EntityContactCollector/hkpEntityContactCollector.h>
#include <Physics/Collide/Agent/hkpProcessCdPoint.h>
#include <Physics/Collide/Agent/hkpProcessCollisionOutput.h>
#include <Physics/Collide/Agent/Collidable/hkpCollidable.h>
#include <Physics/Dynamics/Entity/hkpEntity.h>
		

hkpEntityContactCollector::~hkpEntityContactCollector()
{
	while( m_entities.getSize() )
	{
		removeFromEntity( m_entities[0] );
	}
}

void hkpEntityContactCollector::flipContactPoints( hkpRigidBody* body )
{
	for (int i = 0; i < m_contactPoints.getSize(); i++ )
	{
		ContactPoint& cp = m_contactPoints[i];
		if ( cp.m_bodyB == body ) 
		{
			cp.m_point.flip();
			cp.m_bodyB = cp.m_bodyA;
			cp.m_bodyA = body;
		}
	}
}

void hkpEntityContactCollector::reset()
{
	m_contactPoints.clear();
}

void hkpEntityContactCollector::contactPointAddedCallback( hkpContactPointAddedEvent& event)
{
}

void hkpEntityContactCollector::contactPointRemovedCallback( hkpContactPointRemovedEvent& event)
{
}

void hkpEntityContactCollector::contactPointConfirmedCallback( hkpContactPointConfirmedEvent& event)
{
}


void hkpEntityContactCollector::addToEntity( hkpEntity* entity )
{
	entity->addCollisionListener( this );
	entity->addEntityListener( this );
	m_entities.pushBack(entity);
}

void hkpEntityContactCollector::removeFromEntity( hkpEntity* entity )
{
	HK_ASSERT2(0x1d933c54,  m_entities.indexOf( entity ) != -1, "Trying to remove a contact collector from an entity to which it has not been added");
	m_entities.removeAt( m_entities.indexOf( entity ) );
	entity->removeCollisionListener( this );
	entity->removeEntityListener( this );
}


void hkpEntityContactCollector::contactProcessCallback( hkpContactProcessEvent& event)
{
	int numNewPoints = event.m_collisionData->getNumContactPoints();
	ContactPoint* cp = m_contactPoints.expandBy( numNewPoints );
	for (int i = 0; i < numNewPoints; i++ )
	{
		hkpProcessCdPoint& ccp = event.m_collisionData->m_contactPoints[i];
		cp->m_bodyA = static_cast<hkpRigidBody*>(event.m_collidableA->getOwner());
		cp->m_bodyB = static_cast<hkpRigidBody*>(event.m_collidableB->getOwner());
		cp->m_point = ccp.m_contact;
		cp++;
	}
	HK_ASSERT2(0x2cc4eae6,  m_contactPoints.getSize() < 1024, "Warning: Too many contact points gathered, are you sure you called hkpEntityContactCollector::reset() every frame ??" );
}


void hkpEntityContactCollector::entityDeletedCallback( hkpEntity* entity )
{
	removeFromEntity( entity );
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
