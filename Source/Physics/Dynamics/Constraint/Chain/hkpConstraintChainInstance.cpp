/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Constraint/Chain/hkpConstraintChainInstance.h>
#include <Physics/Dynamics/Constraint/Chain/hkpConstraintChainInstanceAction.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>

hkpConstraintChainInstance::hkpConstraintChainInstance(hkpConstraintChainData* data)
: hkpConstraintInstance(PRIORITY_PSI)
{
	HK_ASSERT2(0xad675544, data->getType() >= hkpConstraintData::BEGIN_CONSTRAINT_CHAIN_TYPES, "You're passing a non-chain-constraint data to a hkpConstraintChainInstance's ctor.");

	m_data = data;
	data->addReference();

	m_entities[0] = HK_NULL;
	m_entities[1] = HK_NULL;

	m_action = new hkpConstraintChainInstanceAction(this);
}


void hkpConstraintChainInstance::addEntity(hkpEntity* entity) 
{
	HK_ASSERT2(0xad6d5d44, m_owner == HK_NULL, "Cannot add entities when constraint chain is added to the world");
	
	if (m_chainedEntities.getSize() < 2 )
	{
		const int idx = m_chainedEntities.getSize();
		HK_ASSERT2(0xad6888d0, m_entities[idx] ==  HK_NULL || m_entities[idx] == entity, "First or second entity added is different from that passed in the hkpConstraintChainInstance's constructor.");
		if (m_entities[idx] == HK_NULL)
		{
			m_entities[idx] = entity;
			entity->addReference();
		}
	}

	m_chainedEntities.pushBack( entity );
	entity->addReference();
}

hkpConstraintChainInstance::~hkpConstraintChainInstance()
{
	for (int i = 0; i < m_chainedEntities.getSize(); i++)
	{
		m_chainedEntities[i]->removeReference();
	}

	HK_ASSERT2(0xad78dd33, m_action->getWorld() == HK_NULL && m_action->getReferenceCount() == 1, "hkpConstraintChainInstanceAction's lifetime cannot exceed that of its hkpConstraintChainInstance.");
	m_action->removeReference();
}

void hkpConstraintChainInstance::entityRemovedCallback(hkpEntity* entity)
{
	// before checkin, make sure that this assert is ok ?
	HK_ASSERT2(0xad6777dd, m_owner != HK_NULL, "internal error.");

	HK_ASSERT2(0xad4bd4d3, entity->getWorld(), "Internal error: entity passed in hkpConstraintInstance::entityRemovedCallback is already removed from the world (Constraints must be removed first).");
	hkpWorld* world = entity->getWorld();

	world->lockCriticalOperations();
	{
		// Adding constraint chain's action
		world->removeActionImmediately(m_action);

		// info: locking done in the hkpWorldOperationUtil function
		hkpWorldOperationUtil::removeConstraintFromCriticalLockedIsland(world, this);

	}
	world->unlockAndAttemptToExecutePendingOperations();
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
