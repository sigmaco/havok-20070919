/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Action/hkpArrayAction.h>
#include <Physics/Dynamics/World/hkpWorld.h>

hkpArrayAction::hkpArrayAction(const hkArray<hkpEntity*>& entities, hkUlong userData)
: hkpAction( userData )
{
	m_entities = entities;
	_referenceBodies();
}



hkpArrayAction::~hkpArrayAction()
{
	for (int i = 0; i < m_entities.getSize(); i++)
	{
		hkpEntity* entity = m_entities[i];
		entity->removeReference();
	}
}


void hkpArrayAction::_referenceBodies()
{
	for (int i = 0; i < m_entities.getSize(); i++)
	{
		hkpEntity* entity = m_entities[i];
		entity->addReference();
	}
}

void hkpArrayAction::addEntity(hkpEntity* entity)
{
	m_entities.pushBack(entity);
	entity->addReference();
	if (getWorld())
	{
		getWorld()->attachActionToEntity(this, entity);
	}
}


void hkpArrayAction::getEntities( hkArray<hkpEntity*>& entitiesOut )
{
	entitiesOut = m_entities;
}


void hkpArrayAction::removeEntity(hkpEntity* entity)
{
	//find index,swap with last, and popback
	HK_ASSERT2(0x79de9e41, m_entities.indexOf(entity)>=0,"in removeEntity: entity not in ArrayAction");
	m_entities.removeAt(m_entities.indexOf(entity));
	//check whether the body was only added once
	HK_ASSERT2(0x79de9e41, m_entities.indexOf(entity)<0,"in removeEntity: multiple entries for the same entity found in ArrayAction");
	if (getWorld())
	{
		getWorld()->detachActionFromEntity(this, entity);
	}
	entity->removeReference();
}


void hkpArrayAction::entityRemovedCallback(hkpEntity* entity) 
{
	HK_ASSERT(0xad000227, getWorld());
	getWorld()->removeActionImmediately(this);
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
