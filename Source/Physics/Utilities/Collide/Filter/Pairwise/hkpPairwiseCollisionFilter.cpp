/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/Agent/Collidable/hkpCollidable.h>
#include <Physics/Dynamics/Entity/hkpEntity.h>
#include <Physics/Utilities/Collide/Filter/Pairwise/hkpPairwiseCollisionFilter.h>

hkpPairwiseCollisionFilter::hkpPairwiseCollisionFilter()
{
	HK_WARN_ONCE(0xaf351fe4, "hkpPairwiseCollisionFilter is deprecated, please switch to hkutilities/collide/filter/pair/hkpPairCollisionFilter instead. hkpPairwiseCollisionFilter will be removed for the final 5.0 release.");
}

hkpPairwiseCollisionFilter::~hkpPairwiseCollisionFilter()
{
	// remove self as listener from any entities.
	for ( int i = 0; i < m_disabledPairs.getSize(); ++i )
	{
		if ( m_disabledPairs[i].m_a->getEntityListeners().indexOf(this) >= 0 )
		{
			m_disabledPairs[i].m_a->removeEntityListener( this );
		}
		if ( m_disabledPairs[i].m_b->getEntityListeners().indexOf(this) >= 0 )
		{
			m_disabledPairs[i].m_b->removeEntityListener( this );
		}
	}
}

void hkpPairwiseCollisionFilter::disableCollisionPair(hkpEntity* a, hkpEntity* b)
{
	CollisionPair pair(a, b);
	if (m_disabledPairs.indexOf(pair) > 0)
	{
		HK_ASSERT2(0x3839c853, 0, "Collision pair already disabled");
	}
	else
	{
		m_disabledPairs.pushBack(pair);

		// add to 'entityA's listeners if this filter is not there
		if ( a->getEntityListeners().indexOf(this) < 0 )
		{
			a->addEntityListener(this);
		}

		// add to 'entityA's listeners if this filter is not there
		if ( b->getEntityListeners().indexOf(this) < 0 )
		{
			b->addEntityListener(this);
		}
	}
}

void hkpPairwiseCollisionFilter::enableCollisionPair(hkpEntity* a, hkpEntity* b)
{
	CollisionPair pair(a, b);

	int idx = m_disabledPairs.indexOf(pair);
	if (idx < 0)
	{
		HK_ASSERT2(0x33e5b4fc, 0, "Collision pair already enabled");
	}
	else
	{
		m_disabledPairs.removeAt(idx);
		{
			// remove from 'entityA's listeners if this filter is there
			const hkSmallArray<hkpEntityListener*>& listeners = a->getEntityListeners();
			int i = listeners.indexOf(this);
			if (i >= 0)
			{
				a->removeEntityListener(this);
			}
		}

		{
			// remove from 'entityB's listeners if this filter is there
			const hkSmallArray<hkpEntityListener*>& listeners = b->getEntityListeners();
			int i = listeners.indexOf(this);
			if (i >= 0)
			{
				 b->removeEntityListener(this);
			}
		}
	}
}

hkBool hkpPairwiseCollisionFilter::isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const
{
	hkpEntity* entityA = static_cast<hkpEntity*>(a.getOwner());
	hkpEntity* entityB = static_cast<hkpEntity*>(b.getOwner());
	CollisionPair pair(entityA, entityB);
	return m_disabledPairs.indexOf(pair) < 0;
}


hkBool hkpPairwiseCollisionFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const hkpShapeContainer& bContainer, hkpShapeKey bKey  ) const
{
	return true;
}

hkBool hkpPairwiseCollisionFilter::isCollisionEnabled( const hkpShapeRayCastInput& aInput, const hkpShape& shape, const hkpShapeContainer& bContainer, hkpShapeKey bKey ) const 
{
	return true;
}

hkBool hkpPairwiseCollisionFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& collectionBodyA, const hkpCdBody& collectionBodyB, const HK_SHAPE_CONTAINER& containerShapeA, const HK_SHAPE_CONTAINER& containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB ) const
{
	return true;
}

hkBool hkpPairwiseCollisionFilter::isCollisionEnabled( const hkpWorldRayCastInput& aInput, const hkpCollidable& collidableB ) const
{
	return true;
}



void hkpPairwiseCollisionFilter::entityRemovedCallback(hkpEntity* entity)
{
	// temporary implementation - iterate through the internal array

	int i = 0;
	while (i < m_disabledPairs.getSize())
	{
		const hkpEntity* entityA = m_disabledPairs[i].m_a;
		const hkpEntity* entityB = m_disabledPairs[i].m_b;

		if ( (entityA == entity) || (entityB == entity) )
		{
			// entity has been deleted - remove pair that references it
			m_disabledPairs.removeAt(i);
		}
		else
		{
			i++;
		}
	}	
	entity->removeEntityListener( this );
}

void hkpPairwiseCollisionFilter::entityDeletedCallback( hkpEntity* entity )
{
}

int hkpPairwiseCollisionFilter::getNumDisabledPairs() const
{
	const int numPairs = m_disabledPairs.getSize();
	return numPairs;
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
