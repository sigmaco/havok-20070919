/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Utilities/Collide/Filter/pair/hkpPairCollisionFilter.h>


#if !defined(HK_PLATFORM_SPU)

hkpPairCollisionFilter::hkpPairCollisionFilter(const hkpCollisionFilter* childFilter) : m_childFilter(childFilter)
{
	m_type = HK_FILTER_PAIR;

	if ( m_childFilter ) 
	{
		m_childFilter->addReference();
	}
}

hkpPairCollisionFilter::~hkpPairCollisionFilter()
{
	if ( m_childFilter ) 
	{
		m_childFilter->removeReference();
	}
}

#endif


#if !defined(HK_PLATFORM_SPU)

hkBool hkpPairCollisionFilter::isCollisionEnabled( const hkpEntity* entityA, const hkpEntity* entityB ) const
{
	if ( !entityA || !entityB ) return true;

	PairFilterKey key;
	calcKey(entityA, entityB, key);

	if ( m_disabledPairs.hasKey(key.m_combined) )
	{
		return false;
	}
	else
	{
		return true;
	}
}


hkBool hkpPairCollisionFilter::isCollisionEnabled( const hkpCollidable& collidableA, const hkpCollidable& collidableB ) const
{
	// If child filter already decides to not collide the two collidables we will accept that.
	if ( m_childFilter && !m_childFilter->isCollisionEnabled(collidableA,collidableB) )
	{
		return false;
	}

	// Otherwise we will check if this pair has been explicitly flagged to not collide.
	const hkpEntity* entityA = hkGetRigidBody( &collidableA );
	const hkpEntity* entityB = hkGetRigidBody( &collidableB );
	return isCollisionEnabled( entityA, entityB );
}


hkBool hkpPairCollisionFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const hkpShapeContainer& bContainer, hkpShapeKey bKey  ) const
{	
	return !m_childFilter || m_childFilter->isCollisionEnabled (input, a, b, bContainer, bKey);
}

hkBool hkpPairCollisionFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const HK_SHAPE_CONTAINER& containerShapeA, const HK_SHAPE_CONTAINER& containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB ) const
{
	return !m_childFilter || m_childFilter->isCollisionEnabled (input, a, b, containerShapeA, containerShapeB, keyA, keyB);
}

hkBool hkpPairCollisionFilter::isCollisionEnabled( const hkpShapeRayCastInput& aInput, const hkpShape& shape, const hkpShapeContainer& bContainer, hkpShapeKey bKey ) const
{	
	return !m_childFilter || m_childFilter->isCollisionEnabled (aInput, shape, bContainer, bKey);
}


hkBool hkpPairCollisionFilter::isCollisionEnabled( const hkpWorldRayCastInput& a, const hkpCollidable& collidableB ) const
{	
	return !m_childFilter || m_childFilter->isCollisionEnabled (a, collidableB);
}


int hkpPairCollisionFilter::enableCollisionsBetween(const hkpEntity* entityA, const hkpEntity* entityB)
{
	HK_ASSERT2(0xaf25142e, entityA && entityB, "You cannot pass in HK_NULL for an entity.");
#if defined(HK_DEBUG)
	if ( entityA->getWorld() )
	{
		HK_ACCESS_CHECK_OBJECT( entityA->getWorld(), HK_ACCESS_RW );
	}
#endif

	PairFilterKey key;
	calcKey(entityA, entityB, key);

	hkUint64 value = m_disabledPairs.getWithDefault(key.m_combined, 0);
	if ( value == 0 ) return 0;
	value--;

	// If the counter is still positive, update it. Otherwise remove the entry.
	if ( value > 0 )
	{
		m_disabledPairs.insert(key.m_combined, value);
	}
	else
	{
		m_disabledPairs.remove(key.m_combined);
	}

	return (int)value;
}


int hkpPairCollisionFilter::disableCollisionsBetween(const hkpEntity* entityA, const hkpEntity* entityB)
{
	HK_ASSERT2(0xaf25142f, entityA && entityB, "You cannot pass in HK_NULL for an entity.");
#if defined(HK_DEBUG)
	if ( entityA->getWorld() )
	{
		HK_ACCESS_CHECK_OBJECT( entityA->getWorld(), HK_ACCESS_RW );
	}
#endif

	PairFilterKey key;
	calcKey(entityA, entityB, key);

	hkUint64 value = m_disabledPairs.getWithDefault(key.m_combined, 0);
	value++;

	m_disabledPairs.insert(key.m_combined, value);

	return (int)value;
}

#endif

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
