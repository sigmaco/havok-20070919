/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Dynamics/hkpDynamics.h>


#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpWorld.h>

#include <Physics/Utilities/Collide/Filter/pair/hkpPairCollisionFilter.h>
#include <Common/Base/UnitTest/hkUnitTest.h>

static int hkPairwiseCollisionTest_main()
{
	int test = 1;
	hkpWorld* world;
	//
	// Create the world
	//
	{
		hkpWorldCinfo info;
		world = new hkpWorld( info );
		world->lock();
	}



	hkpPairCollisionFilter* filter;
	{
		filter = new hkpPairCollisionFilter();
		world->setCollisionFilter( filter );
		filter->removeReference();
	}

	//
	// Create bodies
	//
	hkpRigidBody* bodyA;
	hkpRigidBody* bodyB;
	hkpRigidBody* bodyC;
	{
		hkpRigidBodyCinfo info;
		hkVector4 fixedBoxSize; fixedBoxSize.set(5.0f, .5f , 5.0f );
		hkpBoxShape* fixedBoxShape = new hkpBoxShape( fixedBoxSize , 0 );
		info.m_shape = fixedBoxShape;
		info.m_motionType = hkpMotion::MOTION_FIXED;
		info.m_position.set(0.0f, -1.0f, 0.0f);

		// Create fixed box
		bodyA = new hkpRigidBody(info);
		bodyB = new hkpRigidBody(info);
		bodyC = new hkpRigidBody(info);
		fixedBoxShape->removeReference();
		world->addEntity(bodyA);
		world->addEntity(bodyB);
		world->addEntity(bodyC);
	}

	HK_TEST2(filter->isCollisionEnabled( *bodyA->getCollidable(), *bodyB->getCollidable()), " collision pair should be enabled ");
	HK_TEST2(filter->isCollisionEnabled( *bodyB->getCollidable(), *bodyC->getCollidable()), " collision pair should be enabled ");

	filter->disableCollisionsBetween( bodyA, bodyB);
	filter->enableCollisionsBetween( bodyA, bodyB);
	filter->disableCollisionsBetween(bodyB, bodyC);

	HK_TEST2( filter->isCollisionEnabled( *bodyA->getCollidable(),  *bodyB->getCollidable()), " collision pair should be enabled ");

	HK_TEST2(!filter->isCollisionEnabled( *bodyB->getCollidable(), *bodyC->getCollidable() ),  " collision pair should be disabled " );

	bodyA->removeReference();
	bodyB->removeReference();
	bodyC->removeReference();

	world->removeReference();

	return test;
}
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(hkPairwiseCollisionTest_main, "Fast", "Physics/Test/UnitTest/Dynamics/", __FILE__     );

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
