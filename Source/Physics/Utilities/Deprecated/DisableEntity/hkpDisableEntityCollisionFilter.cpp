/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/Agent/Collidable/hkpCollidable.h>
#include <Physics/Dynamics/Entity/hkpEntity.h>
#include <Physics/Utilities/Deprecated/DisableEntity/hkpDisableEntityCollisionFilter.h>

hkpDisableEntityCollisionFilter::hkpDisableEntityCollisionFilter()
{
	HK_WARN(0x1e56ab3c, "hkpDisableEntityCollisionFilter is deprecated, please do not use");
}

hkpDisableEntityCollisionFilter::~hkpDisableEntityCollisionFilter()
{
	// remove self as listener from any entities.

	for ( int i = 0; i < m_disabledEntities.getSize(); i++ )
	{
		if ( m_disabledEntities[i]->getEntityListeners().indexOf(this) >= 0 )
		{
			m_disabledEntities[i]->removeEntityListener( this );
		}
	}
}

hkBool hkpDisableEntityCollisionFilter::isCollisionEnabled(const hkpCollidable& a,const hkpCollidable& b) const
{
	for (int i=0; i < m_disabledEntities.getSize(); i++)
	{
		const hkpCollidable* stored_collidable = m_disabledEntities[i]->getCollidable();
		if ((stored_collidable == &a) || (stored_collidable == &b))
		{
			return false;
		}
	}
	return true;
}


hkBool hkpDisableEntityCollisionFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const hkpShapeContainer& bContainer, hkpShapeKey bKey  ) const
{
	return true;
}

hkBool hkpDisableEntityCollisionFilter::isCollisionEnabled( const hkpShapeRayCastInput& aInput, const hkpShape& shape, const hkpShapeContainer& bContainer, hkpShapeKey bKey ) const
{
	return true;
}

hkBool hkpDisableEntityCollisionFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& collectionBodyA, const hkpCdBody& collectionBodyB, const HK_SHAPE_CONTAINER& containerShapeA, const HK_SHAPE_CONTAINER& containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB ) const
{
	return true;
}


hkBool hkpDisableEntityCollisionFilter::isCollisionEnabled( const hkpWorldRayCastInput& a, const hkpCollidable& collidableB ) const
{
	return true;
}


hkBool hkpDisableEntityCollisionFilter::addEntityToFilter( hkpEntity* new_entity)
{
	if (!new_entity)
	{
		return false;
	}
	for (int i=0; i < m_disabledEntities.getSize(); i++)
	{
		if (m_disabledEntities[i] == new_entity)
		{
			return false;
		}
	}
	m_disabledEntities.pushBack(new_entity);

	// add to 'new_entity's listeners if this filter is not there
	if ( new_entity->getEntityListeners().indexOf(this) < 0 )
	{
		new_entity->addEntityListener(this);
	}
	return true;
}

hkBool hkpDisableEntityCollisionFilter::removeEntityFromFilter( hkpEntity* new_entity)
{
	if (!new_entity)
	{
		return false;
	}
	int i = 0;
	while (i < m_disabledEntities.getSize())
	{
		const hkpEntity* stored_entity = m_disabledEntities[i];
		
		if (stored_entity == new_entity)
		{
			m_disabledEntities.removeAt(i);
			return true;
		}
		else
		{
			i++;
		}
	}	
	return false;
}

void hkpDisableEntityCollisionFilter::entityRemovedCallback(hkpEntity* entity)
{
	if (entity)
	{
		removeEntityFromFilter(entity);
		entity->removeEntityListener( this );
	}
}

void hkpDisableEntityCollisionFilter::entityDeletedCallback( hkpEntity* entity )
{
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
