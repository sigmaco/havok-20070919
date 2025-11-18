/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Filter/Group/hkpGroupFilter.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Physics/Utilities/Collide/Filter/GroupFilter/hkpGroupFilterUtil.h>

void hkpGroupFilterUtil::disableCollisionsBetweenConstraintBodies( const hkpConstraintInstance*const* constraints, int numConstraints, int groupFilterSystemGroup)
{
	int subSystemId = 0;
	HK_ASSERT2( 0xf021d53a, numConstraints < 31, "The groupfilter allows a maximum of 32 subids"  );
	for (int i =0; i < numConstraints; i++ )
	{
		hkpRigidBody* bA = constraints[i]->getRigidBodyA();
		hkpRigidBody* bB = constraints[i]->getRigidBodyB();

		if ( !bA || !bA->getCollidable()->getShape() || !bB || !bB->getCollidable()->getShape())
		{
			HK_WARN( 0xf021ad34, "disableCollisionsBetweenConstraintBodies does not work with the hkpWorld::getFixedRigidBody()");
			continue;
		}
		HK_ASSERT2( 0xf021f43e, HK_NULL == bA->getWorld() && HK_NULL == bB->getWorld(), "You cannot call this utility after you added the rigid bodies to the world" );


		int subIdA = hkpGroupFilter::getSubSystemIdFromFilterInfo( bA->getCollidable()->getCollisionFilterInfo() );
		int subIdB = hkpGroupFilter::getSubSystemIdFromFilterInfo( bB->getCollidable()->getCollisionFilterInfo() );

		int ignoreA = hkpGroupFilter::getSubSystemDontCollideWithFromFilterInfo( bA->getCollidable()->getCollisionFilterInfo() );
		int ignoreB = hkpGroupFilter::getSubSystemDontCollideWithFromFilterInfo( bB->getCollidable()->getCollisionFilterInfo() );

		int layerA = hkpGroupFilter::getLayerFromFilterInfo( bA->getCollidable()->getCollisionFilterInfo() );
		int layerB = hkpGroupFilter::getLayerFromFilterInfo( bB->getCollidable()->getCollisionFilterInfo() );

			// assign subsystem ids
		if ( !subIdA ){ subIdA = subSystemId++; }
		if ( !subIdB ){ subIdB = subSystemId++; }

		if ( !ignoreA )
		{
			ignoreA = subIdB;
		}
		else
		{
			HK_ASSERT2( 0xf01a2e3f, !ignoreB, "The constraints you passed in do not form a hierarchy or are not sorted by a hierarchy" );
			ignoreB = subIdA;
		}

		bA->setCollisionFilterInfo( hkpGroupFilter::calcFilterInfo( layerA, groupFilterSystemGroup, subIdA, ignoreA ) );
		bB->setCollisionFilterInfo( hkpGroupFilter::calcFilterInfo( layerB, groupFilterSystemGroup, subIdB, ignoreB ) );

	}
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
