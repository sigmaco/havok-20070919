/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Action/hkpUnaryAction.h>
#include <Physics/Dynamics/Entity/hkpEntity.h>
#include <Physics/Dynamics/World/hkpWorld.h>

hkpUnaryAction::hkpUnaryAction(hkpEntity* body, hkUlong userData )
: hkpAction( userData ), m_entity(body)
{
	if (m_entity != HK_NULL)
	{
		m_entity->addReference();
	}
	else
	{
		//	HK_WARN(0x4621e7da, "hkpUnaryAction: body is a NULL pointer");
	}
}

void hkpUnaryAction::entityRemovedCallback(hkpEntity* entity) 
{
	// Remove self from physics.
	if ( getWorld() != HK_NULL )
	{
		getWorld()->removeActionImmediately(this);
	}
}

hkpUnaryAction::~hkpUnaryAction()
{
	if (m_entity != HK_NULL)
	{
		m_entity->removeReference();
		m_entity = HK_NULL;
	}
}

// NB: Only intended to be called pre-simulation i.e. before the hkpUnaryAction is 
// added to an hkpWorld.
void hkpUnaryAction::setEntity(hkpEntity* entity)
{
	//HK_ASSERT2(0x76017ab2, getWorld() == HK_NULL, "This hkpUnaryAction is already added to an hkpWorld.");	
	HK_ASSERT2(0x5163bcc3, entity != HK_NULL, "entity is a NULL pointer. You can use hkpWorld::getFixedRigidBody().");	
	if(m_entity != HK_NULL)
	{
		HK_WARN(0x17aaa816, "m_entity is not NULL. This hkpUnaryAction already had an hkpEntity.");

		if (getWorld())
		{
			getWorld()->detachActionFromEntity(this, m_entity);
		}
		m_entity->removeReference();
		m_entity = HK_NULL;
	}

	m_entity = entity;
	m_entity->addReference();
	if (getWorld())
	{
		getWorld()->attachActionToEntity(this, m_entity);
	}
}

void hkpUnaryAction::getEntities( hkArray<hkpEntity*>& entitiesOut )
{
	entitiesOut.pushBack( m_entity );
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
