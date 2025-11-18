/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// This checks the sphere-triangle agent, both the linearCast() and getPenetrations() methods.
#include <Physics/Collide/hkpCollide.h>


#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>

#include <Physics/Collide/Agent/ConvexAgent/BoxBox/hkpBoxBoxAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/Gjk/hkpGskBaseAgent.h>
#include <Physics/Collide/Agent/hkpCollisionInput.h>
#include <Physics/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h>

#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>


static void HK_CALL testClosestPointWithBigDistance()
{
	//
	//	Create two boxes
	//
	hkMotionState msA;
	hkMotionState msB;

	hkVector4 extents; extents.set(1,1,1);

	hkpBoxShape shapeA( extents );
	hkpBoxShape shapeB( extents );

	hkpCollidable bodyA( &shapeA, &msA, 0 );
	hkpCollidable bodyB( &shapeB, &msB, 0 );
	{
		msA.getTransform().setIdentity();

		msB.getTransform().setIdentity();

		msB.getTransform().getTranslation().set( .0f, .0f, 10.0f );
	}

	//
	//	Query the system several times
	//
	hkPseudoRandomGenerator random(50);
	for (int i = 0; i < 100; i++)
	{
		hkpCollisionInput input;
		input.m_tolerance = 10.f;
		random.getRandomRotation( msB.getTransform().getRotation() ); 

		hkpClosestCdPointCollector collector;
		hkpBoxBoxAgent::staticGetClosestPoints( bodyA, bodyB, input, collector );
		if ( !collector.hasHit() )
		{
			HK_TEST( collector.hasHit() );
		}
	}
}

static void HK_CALL testGskOnVerySmallBoxes()
{
	//
	//	Create two boxes
	//
	hkMotionState msA;
	hkMotionState msB;

	const hkReal edgeLen = 0.001f;
	hkVector4 extents; extents.setAll3( edgeLen );
	hkpBoxShape shapeA( extents );
	hkpBoxShape shapeB( extents );

	hkpCollidable bodyA( &shapeA, &msA, 0 );
	hkpCollidable bodyB( &shapeB, &msB, 0 );
	{
		msA.getTransform().setIdentity();

		msB.getTransform().setIdentity();

		msB.getTransform().getTranslation().set( .0f, .0f, 2.0f * edgeLen );
	}

	//
	//	Query the system several times
	//
	hkPseudoRandomGenerator random(50);
	for (int i = 0; i < 100; i++)
	{
		hkpCollisionInput input;
		input.m_tolerance = 10.f;
		random.getRandomRotation( msB.getTransform().getRotation() ); 

		hkpClosestCdPointCollector collector;
		hkpGskBaseAgent::staticGetClosestPoints( bodyA, bodyB, input, collector );
		if ( !collector.hasHit() )
		{
			HK_TEST( collector.hasHit() );
		}
		else
		{
			const hkContactPoint& cp = collector.getHitContact();
			if ( cp.getNormal()(2) > 0.0f )
			{
				HK_TEST( cp.getNormal()(2) < 0.0f );
			}
		}
	}
}


	// Check various configurations, both penetrating and non-penetrating.
int BoxBoxTest()
{
	testClosestPointWithBigDistance();
	testGskOnVerySmallBoxes();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(BoxBoxTest, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );


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
