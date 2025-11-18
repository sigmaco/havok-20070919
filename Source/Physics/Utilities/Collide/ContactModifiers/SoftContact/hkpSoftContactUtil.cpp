/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Collide/ContactModifiers/SoftContact/hkpSoftContactUtil.h>
#include <Physics/Dynamics/Collide/hkpResponseModifier.h>
#include <Physics/Dynamics/Entity/hkpRigidBodyCinfo.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

hkpSoftContactUtil::hkpSoftContactUtil( hkpRigidBody* bodyA, hkpRigidBody* optionalBodyB, hkReal forceScale, hkReal maxAccel )
{
	m_bodyA = bodyA;
	m_bodyB = optionalBodyB;

	m_bodyA->addCollisionListener( this );
	m_bodyA->addEntityListener( this );

	m_forceScale = forceScale;
	m_maxAcceleration = maxAccel;

	this->addReference();


	bodyA->getCollidableRw()->m_forceCollideOntoPpu |= hkpCollidable::FORCE_PPU_MODIFIER_REQUEST;
}

hkpSoftContactUtil::~hkpSoftContactUtil()
{
	if(m_bodyA)
	{
		m_bodyA->removeCollisionListener( this );
		m_bodyA->removeEntityListener( this );
	}
}



void hkpSoftContactUtil::contactPointAddedCallback( hkpContactPointAddedEvent& event )
{
	hkpConstraintInstance* instance = event.m_internalContactMgr->getConstraintInstance();
	if ( !instance )
	{
		return;
	}


	hkpRigidBody* bodyA = static_cast<hkpRigidBody*>(event.m_bodyA->getRootCollidable()->getOwner());
	hkpRigidBody* bodyB = static_cast<hkpRigidBody*>(event.m_bodyB->getRootCollidable()->getOwner());

	hkpRigidBody* b = (m_bodyB)? m_bodyB : hkSelectOther( m_bodyA, bodyA, bodyB );

	// The bodies could be in either order so we have to check both cases
	if ( ( (bodyA == m_bodyA) && (bodyB == b) ) ||
		 ( (bodyB == m_bodyA) && (bodyA == b) ) )
	{
		hkpResponseModifier::setImpulseScalingForContact( event.m_internalContactMgr, bodyA, bodyB, *event.m_collisionOutput->m_constraintOwner.val(), m_forceScale, m_maxAcceleration );
	}
}

// The hkpCollisionListener interface implementation
void hkpSoftContactUtil::contactProcessCallback( hkpContactProcessEvent& event)
{
}

void hkpSoftContactUtil::entityDeletedCallback( hkpEntity* entity )
{
	HK_ASSERT2(0x76abe9fb, entity == m_bodyA, "hkpSoftContactUtil received an unexpected entity deleted callback");
	entity->removeCollisionListener( this );
	entity->removeEntityListener( this );
	m_bodyA = HK_NULL;
	m_bodyB = HK_NULL;

	this->removeReference();
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
