/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Collide/ContactModifiers/MassChanger/hkpCollisionMassChangerUtil.h>
#include <Physics/Dynamics/Collide/hkpResponseModifier.h>
#include <Physics/Dynamics/Entity/hkpRigidBodyCinfo.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

	/// Will call setRelativeMasses() in hkpResponseModifier
	/// this allows an object to interact differently with one object than with another
	/// (ie it may appear to be fixed to one object, and not to another)
	/// This is an entity listener, with 2 rigidbodies used to decide when to 
	/// change the mass and what to change it to. You may implement a world listener
	/// and a look-up table to change the response of any object in contact with any
	/// other object.
hkpCollisionMassChangerUtil::hkpCollisionMassChangerUtil( hkpRigidBody* bodyA, hkpRigidBody* bodyB, float inverseMassA, float inverseMassB )
{
	m_bodyA = bodyA;
	m_bodyB = bodyB;

	m_inverseMassA = inverseMassA;
	m_inverseMassB = inverseMassB;

	m_bodyA->addCollisionListener( this );
	m_bodyA->addEntityListener( this );

	this->addReference();


	bodyA->getCollidableRw()->m_forceCollideOntoPpu |= hkpCollidable::FORCE_PPU_MODIFIER_REQUEST;
}

hkpCollisionMassChangerUtil::~hkpCollisionMassChangerUtil()
{
	if(m_bodyA)
	{
		m_bodyA->removeCollisionListener( this );
		m_bodyA->removeEntityListener( this );
	}
}


void hkpCollisionMassChangerUtil::contactPointAddedCallback( hkpContactPointAddedEvent& event )
{
	if ( static_cast<hkpEntity*>(event.m_bodyA->getRootCollidable()->getOwner())->getMaterial().getResponseType() != hkpMaterial::RESPONSE_SIMPLE_CONTACT )
	{
		return;
	}
	if ( static_cast<hkpEntity*>(event.m_bodyB->getRootCollidable()->getOwner())->getMaterial().getResponseType() != hkpMaterial::RESPONSE_SIMPLE_CONTACT )
	{
		return;
	}

	hkpRigidBody* bodyA = static_cast<hkpRigidBody*>(event.m_bodyA->getRootCollidable()->getOwner());
	hkpRigidBody* bodyB = static_cast<hkpRigidBody*>(event.m_bodyB->getRootCollidable()->getOwner());

	// The bodies could be in either order so we have to check both cases
	if ( ( ( bodyA == m_bodyA ) && (bodyB == m_bodyB ) ) ||
		( ( bodyB == m_bodyA) && (bodyA == m_bodyB ) ) )
	{
		hkpResponseModifier::setInvMassScalingForContact( event.m_internalContactMgr, m_bodyA, m_bodyB, *event.m_collisionOutput->m_constraintOwner.val(), m_inverseMassA, m_inverseMassB );
	}
}

// The hkpCollisionListener interface implementation
void hkpCollisionMassChangerUtil::contactProcessCallback( hkpContactProcessEvent& event)
{
}

void hkpCollisionMassChangerUtil::entityDeletedCallback( hkpEntity* entity )
{
	HK_ASSERT2(0x76abe9fb, entity == m_bodyA, "hkpCollisionMassChangerUtil received an unexpected entity deleted callback");
	entity->removeCollisionListener( this );
	entity->removeEntityListener( this );
	m_bodyA = HK_NULL;
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
