/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


// This test code is related to the folloing issues:
//
// HVK-1074 hkVector4.normalize ASSERT is too conservative
// HVK-1483 Box-Sphere CD raises assert HVK-1074 for case of sphere centre near surface of box.
// HVK-1583 hkpSphereCapsuleAgent::staticGetClosestPoints() asserts incorrectly
//
// In the case of HVK-1074, the code is commented out - it doesn't perform a test, it just helps
// extract some useful info about how accurately vectors get normalized.
//
// For the other two, it confirms that these asserts no longer get raised by the change in
// the assert tolerance from REAL_EPSILON to 1e-16
//
// hkSimdReal hkVector4::normalizeWithLength3()
// 0x6fe84a9b
// Raised by testSphereAndBox,

// void hkVector4::normalize3()
// 0x475d86b1
// Raised by testSphereAndCapsule
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/SphereCapsule/hkpSphereCapsuleAgent.h>

#include <Physics/Collide/Agent/hkpCollisionInput.h>

#include <Physics/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h>

#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>

#include <Demos/DemoCommon/Utilities/GameUtils/GameUtils.h>




void testBodies(const hkpClosestCdPointCollector& collector)
{
		// We expect a hit (ie. closest pair) since we tested with a large tolerance 
	HK_TEST(collector.hasHit() == true);

		// We also expect the normal to be vertical (by the way we positioned both cases)
	hkVector4 up(0,1,0);
	HK_TEST(collector.getHit().m_contact.getNormal().dot3(up) > 1 - 1e-6f);

	const hkContactPoint& pt = collector.getHitContact();

	// getPosition() returns a point on B by convention
	const hkVector4 pointOnBInWorld   = pt.getPosition();

	// normal goes from B to A by convention
	const hkVector4 normalBtoAInWorld = pt.getNormal();

	// pointOnA = pointOnB + dist * normalBToA
	hkVector4 pointOnAInWorld;
	pointOnAInWorld.setAddMul4(pointOnBInWorld, normalBtoAInWorld, pt.getDistance());
		
}


void testSphereAndBox(hkReal epsilon) 
{	
	hkpRigidBody* sphereBody;
	hkpRigidBody* boxBody;

	//
	// Create a sphere
	//
	{
		hkVector4 pos;
		pos.set(0, 0.5f + epsilon, 0);
		sphereBody = GameUtils::createSphere(1.0f, 1.0f, pos);
	}

	//
	// Create a box
	//
	{
		hkVector4 pos; pos.set(0,0,0);
		hkVector4 size; size.set(1,1,1);
		boxBody = GameUtils::createBox(size, 1, pos);
	}

	hkpCollisionInput input;
	input.m_tolerance = 100.0f;

	// Use a hkpClosestCdPointCollector class to gather the results of our query.
	hkpClosestCdPointCollector collector;

	hkpSphereBoxAgent::staticGetClosestPoints( *sphereBody->getCollidable(), *boxBody->getCollidable(), input, collector );

	testBodies(collector);

	sphereBody->removeReference();
	boxBody->removeReference();

}



	// Here we run with a random rotation (and translation) to see if we can induce an assert due
	// to numerical roundoff error.
	// We run from an 'exact' case but rotate and translate to try and force the algorithm through a path where
	// it normalizes a small vector. If we hack in code which checks these cases in the actual algorithm,
	// and set globals accordingly, we get an idea of the minimum length which occurs *in practice*.
void runSphereAndBoxRandom() 
{	
//	hkcout << "Starting runSphereAndBoxRandom\n";

	hkpRigidBody* sphereBody;
	hkpRigidBody* boxBody;

	//
	// Create a sphere
	//
	{
		hkVector4 pos;
		pos.set(0, 0.5f, 0);
		sphereBody = GameUtils::createSphere(1.0f, 1.0f, pos);
	}

	//
	// Create a box
	//
	{
		hkVector4 pos; pos.set(0,0,0);
		hkVector4 size; size.set(1,1,1);
		boxBody = GameUtils::createBox(size, 1, pos);
	}



	hkpCollisionInput input;
	input.m_tolerance = 100.0f;

	const int numiters = 1000;
	for(int i=0; i < numiters; i++)
	{
// 		if( i % (numiters/10) == 0)
// 		{
// 			hkcout << i / (numiters/10) * 10 << "%\n";
// 		}

		hkVector4 axis; axis.set(hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1) );
		axis.normalize3();
		hkQuaternion rot; rot.setAxisAngle(axis, hkMath::randRange(0, HK_REAL_PI * 0.5f));

		const hkReal posRange = 10.0f;
		hkVector4 pos(hkMath::randRange(-posRange,posRange), hkMath::randRange(-posRange,posRange), hkMath::randRange(-posRange,posRange) );

		hkTransform t(rot, pos);
		{
			hkTransform t2;	t2.setMul( t, sphereBody->getTransform());
			hkQuaternion q2;q2.setMul( rot, sphereBody->getRotation() );
			q2.normalize();

			sphereBody->setPositionAndRotation(t2.getTranslation(), q2);
		}
		{
			hkTransform t2;	t2.setMul( t, boxBody->getTransform()  );
			hkQuaternion q2;q2.setMul( rot, boxBody->getRotation() );
			q2.normalize();

			boxBody->setPositionAndRotation(t2.getTranslation(), q2);
		}


		// Use a hkpClosestCdPointCollector class to gather the results of our query.
		hkpClosestCdPointCollector collector;

		hkpSphereBoxAgent::staticGetClosestPoints( *sphereBody->getCollidable(), *boxBody->getCollidable(), input, collector );

	}


	sphereBody->removeReference();
	boxBody->removeReference();

//	hkcout << "Done runSphereAndBoxRandom\n";

}




	// Here we do the same as the function above, but we start off with the bodies separate, then *using the results of the
	// staticGetClosestPoints call* we put the bodies exactly 'in contact'. This gives a more comprehensive test.
void runSphereAndBoxRandom2() 
{	
//	hkcout << "Starting runSphereAndBoxRandom\n";

	hkpRigidBody* sphereBody;
	hkpRigidBody* boxBody;

	//
	// Create a sphere
	//
	{
		hkVector4 pos;

					// Position somewhere inside a cube, but far from origin
		const hkReal range = 7.0f;
		do
		{
			pos.set(hkMath::randRange(-range, range), hkMath::randRange(-range, range), hkMath::randRange(-range, range));
		}while(pos.length3() < 6.0f);


		sphereBody = GameUtils::createSphere(1.0f, 1.0f, pos);
	}

	//
	// Create a box
	//
	{
		hkVector4 pos; pos.set(0,0,0);
		hkVector4 size; size.set(1,1,1);
		boxBody = GameUtils::createBox(size, 1, pos);
	}



	hkpCollisionInput input;
	input.m_tolerance = 100.0f;

	const int numiters = 10000;
	for(int i=0; i < numiters; i++)
	{
		if( i % (numiters/10) == 0)
		{
//			hkcout << i / (numiters/10) * 10 << "%\n";
		}

		hkVector4 axis;	axis.set(hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1) );
		axis.normalize3();

		hkQuaternion rot;
		rot.setAxisAngle(axis, hkMath::randRange(0, HK_REAL_PI * 0.5f));

		const hkReal posRange = 10.0f;
		hkVector4 pos(hkMath::randRange(-posRange,posRange), hkMath::randRange(-posRange,posRange), hkMath::randRange(-posRange,posRange) );

		hkTransform t(rot, pos);
		{
			hkTransform t2;	t2.setMul( t, sphereBody->getTransform());
			hkQuaternion q2;q2.setMul( rot, sphereBody->getRotation() );
			q2.normalize();

			sphereBody->setPositionAndRotation(t2.getTranslation(), q2);
		}
		{
			hkTransform t2;	t2.setMul( t, boxBody->getTransform()  );
			hkQuaternion q2;q2.setMul( rot, boxBody->getRotation() );
			q2.normalize();

			boxBody->setPositionAndRotation(t2.getTranslation(), q2);
		}



		// Use a hkpClosestCdPointCollector class to gather the results of our query.
		hkpClosestCdPointCollector collector;

		hkpSphereBoxAgent::staticGetClosestPoints( *sphereBody->getCollidable(), *boxBody->getCollidable(), input, collector );

			// Now slide sphere towards box
		hkVector4 normal = collector.getHit().m_contact.getNormal();
		normal.mul4(collector.getHit().m_contact.getDistance() + 1.0f);

		pos = sphereBody->getPosition();
		pos.sub4(normal);
		sphereBody->setPosition(pos);

		collector.reset();

			// And test again
		hkpSphereBoxAgent::staticGetClosestPoints( *sphereBody->getCollidable(), *boxBody->getCollidable(), input, collector );

	}


	sphereBody->removeReference();
	boxBody->removeReference();

//	hkcout << "Done runSphereAndBoxRandom\n";

}

void testSphereAndCapsule(hkReal epsilon) 
{	
	hkpRigidBody* sphereBody;
	hkpRigidBody* capsuleBody;

	
	//
	// Create a sphere
	//
	{ 
		hkVector4 pos; 
	//	pos.set(0,0.0000001f,0); 
		pos.set(0, epsilon, 0);
		sphereBody = GameUtils::createSphere(1.0f, 1.0f, pos); 
	} 


	//
	// Create a capsule
	//
	{ 
		// End points for the capsule 
		hkVector4 A(  1.2f, 0.f, 0.f); 
		hkVector4 B( -1.2f, 0.f, 0.f); 

		// Radius for the capsule 
		hkReal radius = 1.0f; 

		hkpCapsuleShape* shape = new hkpCapsuleShape(A, B, radius); 

		// Set up construction info for this rigid body 
		hkpRigidBodyCinfo ci; 

		ci.m_motionType = hkpMotion::MOTION_FIXED; 
	
		ci.m_shape = shape; 
		ci.m_position.set(0,0,0); 

		capsuleBody = new hkpRigidBody(ci); 

		// Remove our reference to the shape 
		shape->removeReference(); 
	} 


	hkpCollisionInput input;
	input.m_tolerance = 100.0f;

	// Use a hkpClosestCdPointCollector class to gather the results of our query.
	hkpClosestCdPointCollector collector;

	hkpSphereCapsuleAgent::staticGetClosestPoints( *sphereBody->getCollidable(), *capsuleBody->getCollidable(), input, collector );
  
	testBodies(collector);

	sphereBody->removeReference();
	capsuleBody->removeReference();

}



	// Here we run with a random rotation (and translation) to see if we can induce an assert due
	// to numerical roundoff error.
	// We run from an 'exact' case but rotate and translate to try and force the algorithm through a path where
	// it normalizes a small vector. If we hack in code which checks these cases in the actual algorithm,
	// and set globals accordingly, we get an idea of the minimum length which occurs *in practice*.
void runSphereAndCapsuleRandom() 
{	
//	hkcout << "Starting runSphereAndCapsuleRandom\n";
		
	hkpRigidBody* sphereBody;
	hkpRigidBody* capsuleBody;

	
	//
	// Create a sphere
	//
	{ 
		hkVector4 pos; 
		pos.set(0, 0, 0);
		sphereBody = GameUtils::createSphere(1.0f, 1.0f, pos); 
	} 


	//
	// Create a capsule
	//
	{ 
		// End points for the capsule 
		hkVector4 A( 0.f, 1.2f, 0.f); 
		hkVector4 B( 0.f,-1.2f, 0.f); 

		// Radius for the capsule 
		hkReal radius = 1.0f; 

		hkpCapsuleShape* shape = new hkpCapsuleShape(A, B, radius); 

		// Set up construction info for this rigid body 
		hkpRigidBodyCinfo ci; 

		ci.m_motionType = hkpMotion::MOTION_FIXED; 
	
		ci.m_shape = shape; 
		ci.m_position.set(0,0,0); 

		capsuleBody = new hkpRigidBody(ci); 

		// Remove our reference to the shape 
		shape->removeReference(); 
	} 


	hkpCollisionInput input;
	input.m_tolerance = 100.0f;

	const int numiters = 10000;
	for(int i=0; i < numiters; i++)
	{
		if( i % (numiters/10) == 0)
		{
//			hkcout << i / (numiters/10) * 10 << "%\n";
		}


		hkVector4 axis; axis.set(hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1) );
		axis.normalize3();
		hkQuaternion rot; rot.setAxisAngle(axis, hkMath::randRange(0, HK_REAL_PI * 0.5f));

		const hkReal posRange = 10.0f;
		hkVector4 pos(hkMath::randRange(-posRange,posRange), hkMath::randRange(-posRange,posRange), hkMath::randRange(-posRange,posRange) );


		hkTransform t(rot, pos);
		{
			hkTransform t2;	t2.setMul( t, sphereBody->getTransform());
			hkQuaternion q2;q2.setMul( rot, sphereBody->getRotation() );
			q2.normalize();

			sphereBody->setPositionAndRotation(t2.getTranslation(), q2);
		}
		{
			hkTransform t2;	t2.setMul( t, capsuleBody->getTransform()  );
			hkQuaternion q2;q2.setMul( rot, capsuleBody->getRotation() );
			q2.normalize();

			capsuleBody->setPositionAndRotation(t2.getTranslation(), q2);
		}


		// Use a hkpClosestCdPointCollector class to gather the results of our query.
		hkpClosestCdPointCollector collector;

		hkpSphereCapsuleAgent::staticGetClosestPoints( *sphereBody->getCollidable(), *capsuleBody->getCollidable(), input, collector );


	//	testBodies(collector);	// Not checking normal is straight up etc.
	}

	sphereBody->removeReference();
	capsuleBody->removeReference();

//	hkcout << "Done runSphereAndCapsuleRandom\n";

}


		// Here we do the same as the function above, but we start off with the bodies separate, then *using the results of the
	// staticGetClosestPoints call* we put the bodies exactly 'in contact'. This gives a more comprehensive test.

void runSphereAndCapsuleRandom2() 
{	
//	hkcout << "Starting runSphereAndCapsuleRandom\n";
		
	hkpRigidBody* sphereBody;
	hkpRigidBody* capsuleBody;

	
	//
	// Create a sphere
	//
	{ 
		hkVector4 pos; 

			// Position somewhere inside a cube, but far from origin
		const hkReal range = 7.0f;
		do
		{
			pos.set(hkMath::randRange(-range, range), hkMath::randRange(-range, range), hkMath::randRange(-range, range));
		}while(pos.length3() < 6.0f);

		sphereBody = GameUtils::createSphere(1.0f, 1.0f, pos); 
	} 


	//
	// Create a capsule
	//
	{ 
		// End points for the capsule 
		hkVector4 A( 0.f, 1.2f, 0.f); 
		hkVector4 B( 0.f,-1.2f, 0.f); 

		// Radius for the capsule 
		hkReal radius = 1.0f; 

		hkpCapsuleShape* shape = new hkpCapsuleShape(A, B, radius); 

		// Set up construction info for this rigid body 
		hkpRigidBodyCinfo ci; 

		ci.m_motionType = hkpMotion::MOTION_FIXED; 
	
		ci.m_shape = shape; 
		ci.m_position.set(0,0,0); 

		capsuleBody = new hkpRigidBody(ci); 

		// Remove our reference to the shape 
		shape->removeReference(); 
	} 


	hkpCollisionInput input;
	input.m_tolerance = 100.0f;

	const int numiters = 10000;
	for(int i=0; i < numiters; i++)
	{
		if( i % (numiters/10) == 0)
		{
//			hkcout << i / (numiters/10) * 10 << "%\n";
		}


		hkVector4 axis; axis.set(hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1) );
		axis.normalize3();
		hkQuaternion rot; rot.setAxisAngle(axis, hkMath::randRange(0, HK_REAL_PI * 0.5f));

		const hkReal posRange = 10.0f;
		hkVector4 pos(hkMath::randRange(-posRange,posRange), hkMath::randRange(-posRange,posRange), hkMath::randRange(-posRange,posRange) );

		hkTransform t(rot, pos);
		{
			hkTransform t2;	t2.setMul( t, sphereBody->getTransform());
			hkQuaternion q2;q2.setMul( rot, sphereBody->getRotation() );
			q2.normalize();

			sphereBody->setPositionAndRotation(t2.getTranslation(), q2);
		}
		{
			hkTransform t2;	t2.setMul( t, capsuleBody->getTransform()  );
			hkQuaternion q2;q2.setMul( rot, capsuleBody->getRotation() );
			q2.normalize();

			capsuleBody->setPositionAndRotation(t2.getTranslation(), q2);
		}


		// Use a hkpClosestCdPointCollector class to gather the results of our query.
		hkpClosestCdPointCollector collector;

		hkpSphereCapsuleAgent::staticGetClosestPoints( *sphereBody->getCollidable(), *capsuleBody->getCollidable(), input, collector );


			// Now slide sphere towards capsule
		hkVector4 normal = collector.getHit().m_contact.getNormal();
		normal.mul4(collector.getHit().m_contact.getDistance() + 2.0f);

		pos = sphereBody->getPosition();
		pos.sub4(normal);
		sphereBody->setPosition(pos);

		collector.reset();

			// And test again
		hkpSphereCapsuleAgent::staticGetClosestPoints( *sphereBody->getCollidable(), *capsuleBody->getCollidable(), input, collector );
	}

	sphereBody->removeReference();
	capsuleBody->removeReference();

//	hkcout << "Done runSphereAndCapsuleRandom\n";

}


	// Here we check a large amount of vectors of length 'epsilon' to ensure they get normalized OK
void testNormalizationOfVectors(hkReal epsilon, hkReal tolerance)
{
//	hkcout << "Starting testNormalizationOfVectors\n";

	hkVector4 v;
	const int numiters = 10000;
	for(int i=0; i < numiters; i++)
	{
		if( i % (numiters/10) == 0)
		{
//			hkcout << i / (numiters/10) * 10 << "%\n";
		}

		v.set(hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1) );
		v.normalize3();
		v.mul4(epsilon);

		{
			hkVector4 v2 = v;
			v2.normalize3();
			HK_TEST(hkMath::fabs(v2.length3() - hkSimdReal(1)) < tolerance);
		}
		{
			hkVector4 v2 = v;
			v2.normalizeWithLength3();
			HK_TEST(hkMath::fabs(v2.length3() - hkSimdReal(1)) < tolerance);
		}

		v.set(hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1) );
		v.normalize4();
		v.mul4(epsilon);
		{
			hkVector4 v2 = v;
			v2.normalize4();
			HK_TEST(hkMath::fabs(v2.length4() - hkSimdReal(1)) <  tolerance);
		}
		{
			hkVector4 v2 = v;
			v2.normalizeWithLength4();
			HK_TEST(hkMath::fabs(v2.length4() - hkSimdReal(1)) < tolerance);
		}


	
	}

//	hkcout << "Starting testNormalizationOfVectors\n";

}

	// Here we check a large amount of vectors of length 'epsilon' to ensure they get normalized OK to within "tolerance" of 1.0f
hkReal evaluateAccuracyOfNormalizationOfVectors(hkReal epsilon, hkReal tolerance)
{
//	hkcout << "Starting evaluateAccuracyOfNormalizationOfVectors\n";

	hkVector4 v;
	const int numiters = 10000;
	
	int failures = 0;
	int successes = 0;
	for(int i=0; i < numiters; i++)
	{
		if( i % (numiters/10) == 0)
		{
	//		hkcout << i / (numiters/10) * 10 << "%\n";
		}

		v.set(hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1) );
		v.normalize3();
		v.mul4(epsilon);

		{	
				// Code completely unwrapped here because I had problems with MW debuggger lying to me.
			hkVector4 v1 = v;
			v1.normalize3();
			hkReal l1 = v1.length3();
			hkReal dif1 = l1 - 1;
			if(hkMath::fabs(dif1) <  tolerance)
			{
				successes++;
			}
			else
			{
				failures++;
			}
		}
		{
			hkVector4 v2 = v;
			v2.normalizeWithLength3();
			hkReal l2 = v2.length3();
			hkReal dif2 = l2 - 1;
			hkReal fdif2 = hkMath::fabs(dif2);
			if(fdif2 <  tolerance)
			{
				successes++;
			}
			else
			{
				failures++;
			}
		}

		v.set(hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1), hkMath::randRange(-1,1) );
		v.normalize4();
		v.mul4(epsilon);
		{
			hkVector4 v3 = v;
			v3.normalize4();
			hkReal l3 = v3.length4();
			hkReal dif3 = l3 - 1;
			if(hkMath::fabs(dif3) < tolerance)
			{
				successes++;
			}
			else
			{
				failures++;
			}
		}
		{
			hkVector4 v4 = v;
			v4.normalizeWithLength4();
			hkReal l4 = v4.length4();
			hkReal dif4 = l4 - 1;
			if(hkMath::fabs(dif4) <  tolerance)
			{
				successes++;
			}
			else
			{
				failures++;
			}
		}


	
	}

//	hkcout << "Done evaluateAccuracyOfNormalizationOfVectors\n";
	const hkReal sr = hkReal(successes);
	const hkReal fr = hkReal(failures);
	const hkReal srfr = sr + fr;
	const hkReal ratio = sr / srfr;
	return ratio;

}


	// These are the globals which can be used by the commented out tests.
	// You need to add code to the relevant agents to pull ou this info,
	// and then you need to disable the asserts to let the normalize fail if 
	// it wants to.
hkReal g_minSB = 100.0f;
hkReal g_minSC = 100.0f;

int ConservativeAssertBugsTest()
{
		// If we use 1e-7 here this is the smallest difference we can actually *force* in a non trivial way
		// into the algorithms so that the old assert appears. Smaller differences get lost due to precision roundoff, 
		// and never make it down into the normalize code!
	testSphereAndBox(1e-7f);
	testSphereAndCapsule(1e-5f);

			// This should pass on both PC (non-SIMD) and GC.
	testNormalizationOfVectors(2e-16f, 1e-6f);


	// The code beloe helps examine issues related to:
	// HVK-1074 hkVector4.normalize ASSERT is too conservative
	// It also confirms that the new assert doesn't get raised in 'practical' uses of the algorithms.
	
	runSphereAndBoxRandom2();
	runSphereAndCapsuleRandom2();
	

		// Running this while hacking out the length of the vectors *Actually* normalized inside the algorithms
		// produces vectors of length:
		//
		//  PC (non-SIMD)	GC
		//		5e-8		6e-8
		// *at worst*.
		// ie. we expect such data to come up in real-game data. Since this would fail the old asserts
		// (which checked against HK_REAL_EPSILON which is 1.19209e-007) we needed to chaneg the assert value.
		// By the evidence above, a value of 1e-18 or thereabouts should not couses problems with real-world data...
	runSphereAndBoxRandom(); 
		// Running this while hacking out the length of the vectors *Actually* normalized inside the algorithms
		// produces vectors of length
		//
		//  PC (non-SIMD)  GC
		//		3e-9		1e-8
		// *at worst*.
	runSphereAndCapsuleRandom();
	


	/*
			// Used these to check how small we could get vectors into the following algorithms...
	hkcout << "Worst length for SphereBox * 1e6: " << g_minSB* 1e6 << "\n";
	hkcout << "Worst length for SphereCapsule * 1e6:: " << g_minSC* 1e6 << "\n";
	*/
	


	/*
		// Check how accurate normalization is (disable asserts) on various platforms.
	{
		// hkSimdReal hkVector4::normalizeWithLength3()
		hkError::getInstance().setEnabled(0x6fe84a9b, false);
		
		// inline void hkVector4::normalize3()
		hkError::getInstance().setEnabled(0x475d86b1, false);

			// hkSimdReal hkVector4::normalizeWithLength4()
		hkError::getInstance().setEnabled(0x309314d9, false);
		
		// inline void hkVector4::normalize4()
		hkError::getInstance().setEnabled(0x21c8ab2a, false);

	
		hkReal tol = 1e-6f;	// Can change this too!
		hkReal t15 = evaluateAccuracyOfNormalizationOfVectors(1e-15, tol);
		hkReal t16 = evaluateAccuracyOfNormalizationOfVectors(1e-16, tol);
		hkReal t17 = evaluateAccuracyOfNormalizationOfVectors(1e-17, tol);
		hkReal t18 = evaluateAccuracyOfNormalizationOfVectors(1e-18, tol);
		hkReal t19 = evaluateAccuracyOfNormalizationOfVectors(1e-19, tol);		
	}
	*/
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(ConservativeAssertBugsTest,     "ConservativeAssertBugsTest", "Test/Test/UnitTest/UnitTest/UnitTest/Collide/",     __FILE__     );


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
