/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Filter/Group/hkpGroupFilter.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Internal/Collide/Agent3/BvTree3/hkpBvTreeAgent3.h>

#if !defined(HK_PLATFORM_SPU)

hkpGroupFilter::hkpGroupFilter()
{
	m_type = HK_FILTER_GROUP;
	// Initially enable all collision groups
	for (int i=0; i<32; i++)
	{
		m_collisionLookupTable[i] = 0xffffffff;
	}
	m_nextFreeSystemGroup = 0;
}

hkpGroupFilter::~hkpGroupFilter()
{
}
#else
HK_COMPILE_TIME_ASSERT(sizeof(hkpGroupFilter)==256);
#endif

hkBool hkpGroupFilter::isCollisionEnabled(hkUint32 infoA, hkUint32 infoB) const
{
	// If the objects are in the same system group, but not system group 0,
	// then the decision of whether to collide is based exclusively on the 
	// objects' SubSystemId and SubSystemDontCollideWith.
	// Otherwise, the decision is based exclusively on the objects' layers.

	hkUint32 zeroIfSameSystemGroup = (infoA^infoB) & 0xffff0000;

	// check for identical system groups
	if ( zeroIfSameSystemGroup == 0)
	{
		// check whether system group was set (nonzero)
		if ( (infoA & 0xffff0000) != 0 )
		{
			// check whether we allow collisions
			int idA = (infoA >> 5) & 0x1f;
			int dontCollideB = (infoB >> 10) & 0x1f;
			if ( idA == dontCollideB )
			{
				return false;
			}

			int idB = (infoB >> 5) & 0x1f;
			int dontCollideA = (infoA >> 10) & 0x1f;
			if ( idB == dontCollideA )
			{
				return false;
			}
			return true;
		}
	}

	// use the layers to decide
	hkUint32 f = 0x1f;
	hkUint32 layerBitsA = m_collisionLookupTable[ infoA & f ];
	hkUint32 layerBitsB = hkUint32(1 << (infoB & f));

	return 0 != (layerBitsA & layerBitsB);
}

#if !defined(HK_PLATFORM_SPU)
hkBool hkpGroupFilter::isCollisionEnabled( const hkpCollidable& a, const hkpCollidable& b ) const
{
	return isCollisionEnabled( a.getCollisionFilterInfo(), b.getCollisionFilterInfo() );
}
#endif

hkBool hkpGroupFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& collectionBodyA, const hkpCdBody& collectionBodyB, const HK_SHAPE_CONTAINER& containerShapeA, const HK_SHAPE_CONTAINER& containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB ) const
{
	hkUint32 infoA = containerShapeA.getCollisionFilterInfo( keyA );
	hkUint32 infoB = containerShapeB.getCollisionFilterInfo( keyB );
	return isCollisionEnabled( infoA, infoB );
}

hkBool hkpGroupFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const HK_SHAPE_CONTAINER& bContainer, hkpShapeKey bKey  ) const
{
	hkUint32 infoB = bContainer.getCollisionFilterInfo( bKey );
	hkUint32 infoA;
	if ( !a.getParent() )
	{
		infoA = a.getRootCollidable()->getCollisionFilterInfo();
	}
	else
	{ 
		// If a has a shape key, then two shape collection are colliding with each other,
		// in this case we have to try to reverse engineer the parent of a to get
		// the proper collision filter
		const hkpCdBody* p = a.getParent();
		const hkpCdBody* lastp = &a;
		while(1)
		{
			hkpShapeType t = p->getShape()->getType();

			if ( input.m_dispatcher->hasAlternateType( t, HK_SHAPE_COLLECTION ) )
			{
				const hkpShapeCollection* aCollection = static_cast<const hkpShapeCollection*>( p->getShape() );
				infoA = aCollection->getCollisionFilterInfo( lastp->getShapeKey() );
				break;
			}

			else if ( input.m_dispatcher->hasAlternateType( t, HK_SHAPE_BV_TREE ) )
			{
				const HK_SHAPE_CONTAINER* shapeContainer = hkBvTreeAgent3::getShapeContainerFrom(p);

				infoA = shapeContainer->getCollisionFilterInfo( lastp->getShapeKey() );
				break;
			}
			else if ( input.m_dispatcher->hasAlternateType( t, HK_SHAPE_MULTI_SPHERE ) )
			{
				infoA = a.getRootCollidable()->getCollisionFilterInfo();
				break;
			}
			else
			{
				// We disable filtering for convex list shapes, because we do not filter
				// the collisions in the get supporting vertex call, so the filtering will be inconsistent
				if (input.m_dispatcher->hasAlternateType( t, HK_SHAPE_CONVEX_LIST ) )
				{
					return true;
				}
			}

			lastp = p;
			p = p->getParent();
			HK_ASSERT2(0x23cd067c,  p, "m_shapeKey is set in hkpCdBody, but no hkpShapeCollection can be found as a parent");
			if ( p )
			{
				continue;
			}
				// parent of lastp is zero, therefor lastp is the root collidable
			infoA = reinterpret_cast<const hkpCollidable*>(lastp)->getCollisionFilterInfo();
			break;
		}
	}
	return isCollisionEnabled( infoA, infoB );
}


hkBool hkpGroupFilter::isCollisionEnabled( const hkpShapeRayCastInput& aInput, const hkpShape& bShape, const HK_SHAPE_CONTAINER& bContainer, hkpShapeKey bKey ) const 
{
	hkUint32 infoB = bContainer.getCollisionFilterInfo( bKey );
	return isCollisionEnabled( aInput.m_filterInfo, infoB );
}

hkBool hkpGroupFilter::isCollisionEnabled( const hkpWorldRayCastInput& aInput, const hkpCollidable& collidableB ) const
{
	return isCollisionEnabled( aInput.m_filterInfo, collidableB.getCollisionFilterInfo() );
}

#if !defined(HK_PLATFORM_SPU)

void hkpGroupFilter::enableCollisionsUsingBitfield(hkUint32 layerBitsA, hkUint32 layerBitsB)
{
	HK_ASSERT2(0x3c3a0084,  (layerBitsA|layerBitsB) != 0, "layer bits not set");
	for (int i=0; i< 32; i++)
	{
		int b = 1<<i;
		if ( b & layerBitsA )
		{
			m_collisionLookupTable[i] |= layerBitsB;
		}
		if ( b & layerBitsB )
		{
			m_collisionLookupTable[i] |= layerBitsA;
		}
	}
}

void hkpGroupFilter::enableCollisionsBetween(int layerA, int layerB )
{
	HK_ASSERT(0x66c2b6fd,  0 <= layerA && layerA < 32 );
	HK_ASSERT(0x5a285631,  0 <= layerB && layerB < 32 );

	m_collisionLookupTable[layerA] |= hkUint32(1 << layerB);
	m_collisionLookupTable[layerB] |= hkUint32(1 << layerA);
}

void hkpGroupFilter::disableCollisionsBetween(int layerA, int layerB )
{
	HK_ASSERT(0x2a168aec,  0 <= layerA && layerA < 32 );
	HK_ASSERT(0x234fb60b,  0 <= layerB && layerB < 32 );
	HK_ASSERT2(0x4ab45935,  layerA > 0, "You are not allowed to disable collision of layer 0");
	HK_ASSERT2(0x358c7ccd,  layerB > 0, "You are not allowed to disable collision of layer 0");

	m_collisionLookupTable[layerA] &= hkUint32(~(1 << layerB));
	m_collisionLookupTable[layerB] &= hkUint32(~(1 << layerA));
}

void hkpGroupFilter::disableCollisionsUsingBitfield(hkUint32 layerBitsA, hkUint32 layerBitsB)
{
	HK_ASSERT2(0x41c4fad2,  (layerBitsA|layerBitsB) != 0, "layer bits not set");
	HK_ASSERT2(0x49059b77,  (layerBitsA&1) == 0, "You are not allowed to disable collision of layer 0");
	HK_ASSERT2(0x371ca278,  (layerBitsB&1) == 0, "You are not allowed to disable collision of layer 0");
	for (int i=0; i< 32; i++)
	{
		int b = 1<<i;
		if ( b & layerBitsA )
		{
			m_collisionLookupTable[i] &= ~layerBitsB;
		}
		if ( b & layerBitsB )
		{
			m_collisionLookupTable[i] &= ~layerBitsA;
		}
	}
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
