/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// This checks the mopp 
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>
#include <Common/Base/Types/Geometry/Sphere/hkSphere.h>

#include <Physics/Collide/Agent/Collidable/hkpCollidable.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>

#include <Physics/Internal/Collide/Gjk/Continuous/hkpContinuousGsk.h>
#include <Physics/Collide/Agent/hkpCollisionQualityInfo.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Collide/Agent/hkpProcessCollisionOutput.h>
#include <Physics/Internal/Collide/Gjk/hkpGsk.h>

#include <Physics/Collide/Agent/ConvexAgent/Gjk/hkpPredGskfAgent.h>

#include <Physics/Collide/Dispatch/ContactMgr/hkpNullContactMgr.h>

#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

#include <Physics/Dynamics/Constraint/hkpConstraintOwner.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

static hkpConvexShape* buildConvexBox( const hkVector4& pos, const hkVector4& ext )
{
	hkpBoxShape box( ext, 0.0f);
	hkSphere sphereBuffer[8];
	const hkSphere* spheres = box.getCollisionSpheres( sphereBuffer );
	spheres = &sphereBuffer[0];
	for ( int i = 0; i < 8; i++)
	{
		sphereBuffer[i].getPositionAndRadius().add4( pos );
	}

	hkStridedVertices stridedVerts;
	{
		stridedVerts.m_numVertices = 8;
		stridedVerts.m_striding = sizeof(hkSphere);
		stridedVerts.m_vertices = &sphereBuffer[0].getPositionAndRadius()(0);
	}

	hkArray<hkVector4> planeEquations;
	hkGeometry geom;

	hkpGeometryUtility::createConvexGeometry( stridedVerts, geom, planeEquations );

	{
		stridedVerts.m_numVertices = geom.m_vertices.getSize();
		stridedVerts.m_striding = sizeof(hkVector4);
		stridedVerts.m_vertices = &(geom.m_vertices[0](0));
	}

	hkpConvexShape *shape = new hkpConvexVerticesShape(stridedVerts, planeEquations);
	return shape;
}

/*
static hkpConvexShape* buildGroundBox(  )
{
	hkVector4 smallExtents( 10.f, 10.f,  0.5f );
	hkVector4 smallPos    (    0,    0,  -.5f );
	hkpConvexShape* shape = buildConvexBox( smallPos, smallExtents );
	return shape;
}
*/
class hkAcceptToiContactMgr: public hkpNullContactMgr
{
	public:
		ToiAccept addToi( const hkpCdBody& a, const hkpCdBody& b, const hkpProcessCollisionInput& input, hkpProcessCollisionOutput& output, hkTime toi, hkContactPoint& cp, const hkpGskCache* gskCache, hkReal& projectedVelocity, hkpContactPointProperties& properties )
		{
			return TOI_ACCEPT;
		}
};

static void ContinuousGskTest_callGsk( hkStepInfo& stepInfo, hkpCollidable& bodyA, hkpCollidable& bodyB, hkpProcessCollisionOutput& output )
{
	hkMotionState* msA = const_cast<hkMotionState*>(bodyA.getMotionState());
	hkMotionState* msB = const_cast<hkMotionState*>(bodyB.getMotionState());

	if ( !bodyA.getShape())
	{
		hkVector4 smallExtents, smallPos;
		smallExtents.set( 0.5f, 0.5f, 0.5f );
		smallPos.set( .5f, .5f, .5f );
		hkpConvexShape* shape = buildConvexBox( smallPos, smallExtents );
		shape->setRadius(0.0f);
		bodyA.setShape( shape );
		msA->m_objectRadius = 2.0f;
		bodyA.m_allowedPenetrationDepth = 1.0f;
	}

	if ( !bodyB.getShape())
	{
		hkVector4 bigExtents, bigPos; 
		bigExtents.set( 1.9f, 1.9f,  .1f );
		bigPos.set( 0.f,  0.f, -.2f );
		hkpConvexShape* shape = buildConvexBox( bigPos, bigExtents );
		shape->setRadius(0.1f);
		bodyB.setShape( shape );
		msB->m_objectRadius = 2.0f;
		bodyB.m_allowedPenetrationDepth = 1.0f;
	}

	{
		hkpCollisionQualityInfo qi;
		qi.m_createContact = -0.001f;
		qi.m_keepContact = 0.1f;
		qi.m_manifoldTimDistance = 0.0f;
		qi.m_minExtraSeparation = -0.05f;
		qi.m_minSeparation = -0.05f;
		qi.m_toiSeparation = -0.01f;
		qi.m_toiExtraSeparation = -0.01f;
		qi.m_minSafeDeltaTime = 1e-4f;
		qi.m_maxContraintViolation = 0.0f;
		qi.m_minToiDeltaTime = HK_REAL_EPSILON * 2.0f;
		qi.m_toiAccuracy = -0.1f * qi.m_toiSeparation;
		qi.m_useContinuousPhysics = true;

		hkpProcessCollisionInput input;
		input.m_collisionQualityInfo = &qi;
		input.m_config = HK_NULL;
		input.m_dispatcher = HK_NULL;
		input.m_dynamicsInfo = HK_NULL;
		input.m_filter = HK_NULL;
		input.m_stepInfo = hkStepInfo( hkTime(1.0f), hkTime(1.1f) );
		input.m_tolerance = 1.0f;

		hkAcceptToiContactMgr contactMgr;
		hkpCollisionAgent* agent = hkpPredGskfAgent::createPredGskfAgent( bodyA, bodyB, input, &contactMgr);

		output.reset();
		agent->processCollision( bodyA, bodyB, input, output );

		hkpConstraintOwner constraintOwner;
		agent->cleanup(constraintOwner);
	}
}

// this function tests, whether the GSK manifold returns the same
// information as GSK 
static void ContinuousGskTest0_RecalcContact()
{
	hkPseudoRandomGenerator random(10);
	hkTransform wTa;
	hkTransform wTb;

	hkVector4 extents; extents .set( 0.5f, 0.5f, 0.5f );
	hkpBoxShape box( extents );

	for ( int i = 0; i < 1000.0f; i++)
	{
		random.getRandomVector11(wTa.getTranslation());
		wTa.getTranslation().mul4(3.0f);
		random.getRandomVector11(wTb.getTranslation());
		wTb.getTranslation().mul4(3.0f);

		hkQuaternion rA; random.getRandomRotation( rA );
		wTa.getRotation().set(rA);

		hkQuaternion rB; random.getRandomRotation( rB );
		wTb.getRotation().set(rB);

		hkTransform aTb; aTb.setMulInverseMul(wTa, wTb);
		hkpGskCache cache; cache.init(&box, &box, aTb);
			
		hkpGsk gsk; gsk.init( &box, &box, cache);

		hkVector4 seperatingNormalA;
		hkVector4  pointA;
		gsk.getClosestFeature( &box, &box, aTb, seperatingNormalA );
		gsk.getClosestPointAinA( seperatingNormalA, pointA );


		hkVector4 point2A;
		hkVector4 support2A;
		hkGskRecalcContact( gsk, seperatingNormalA, point2A, support2A );
			
		HK_TEST( point2A.equals3(pointA));
		HK_TEST( support2A.equals4(seperatingNormalA));

		
	}
}


// small box dropping straight on a big box
static void ContinuousGskTest1_02Linear_0Angular_PfHit()
{
	hkStepInfo stepInfo( hkTime(1.0f), hkTime(1.1f) );

	hkMotionState smallMs;	smallMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
	hkMotionState bigMs;	bigMs.initMotionState  ( hkVector4::getZero(), hkQuaternion::getIdentity() );
	{
		
		hkVector4 smallPos0, smallPos1;
		smallPos0.set( 0, 0,  0.1f );
		smallPos1.set( 0, 0, -0.1f );
		hkSweptTransformUtil::warpToPosition( smallPos0, smallMs );
		hkSweptTransformUtil::keyframeMotionState( stepInfo, smallPos1, hkQuaternion::getIdentity(), smallMs );
	}

	hkpCollidable bodyA( HK_NULL, &smallMs );
	hkpCollidable bodyB( HK_NULL, &bigMs );

	hkpProcessCollisionOutput output(HK_NULL);
	ContinuousGskTest_callGsk( stepInfo, bodyA, bodyB,output ); 
	HK_TEST( hkMath::equal( output.m_toi.m_time, 1.0550001f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_seperatingVelocity, -2.00f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_contactPoint.getNormal()(2), 1.f ) );
}


// small box rotating over ground not hitting at all
static void ContinuousGskTest2_0Linear_1Angular_PfMiss()
{
	hkStepInfo stepInfo( hkTime(1.0f), hkTime(1.1f) );
	hkMotionState smallMs;
	{
		smallMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
		
		hkQuaternion smallRot0; smallRot0.setIdentity();
		hkQuaternion smallRot1; smallRot1.m_vec.set( .0f, -1.f, 0, 1.0f ); smallRot1.normalize();

		hkSweptTransformUtil::warpToPosition( hkVector4::getZero(), smallMs );
		hkSweptTransformUtil::keyframeMotionState( stepInfo, hkVector4::getZero(), smallRot1, smallMs );
	}
	
	hkMotionState bigMs;	bigMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );

	hkpCollidable bodyA( HK_NULL, &smallMs );
	hkpCollidable bodyB( HK_NULL, &bigMs );

	hkpProcessCollisionOutput output(HK_NULL);
	ContinuousGskTest_callGsk( stepInfo, bodyA, bodyB,output ); 
	HK_TEST( output.m_toi.m_time > 10.0f );
}

// small box rotating over ground
static void ContinuousGskTest3_0Linear_2Angular_PfHit()
{
	hkStepInfo stepInfo( hkTime(1.0f), hkTime(1.1f) );
	hkMotionState smallMs;
	{
		smallMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
		
		hkQuaternion smallRot0; smallRot0.setIdentity();
		hkQuaternion smallRot1; smallRot1.m_vec.set( .0f, -3.0f, 0, 1.0f ); smallRot1.normalize();

		hkSweptTransformUtil::warpToPosition( hkVector4::getZero(), smallMs );
		hkSweptTransformUtil::keyframeMotionState( stepInfo, hkVector4::getZero(), smallRot1, smallMs );
	}
	
	hkMotionState bigMs;	bigMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );

	hkpCollidable bodyA( HK_NULL, &smallMs );
	hkpCollidable bodyB( HK_NULL, &bigMs );

	hkpProcessCollisionOutput output(HK_NULL);
	ContinuousGskTest_callGsk( stepInfo, bodyA, bodyB,output ); 
	HK_TEST( hkMath::equal( output.m_toi.m_time, 1.0621974f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_seperatingVelocity, -24.979649f, 0.01f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_contactPoint.getNormal()(2), 1.f ) );
}



// small box sliding just missing a big box
static void ContinuousGskTest4_1Linear_0Angular_PPSlide()
{
	hkStepInfo stepInfo( hkTime(1.0f), hkTime(1.1f) );

	hkMotionState smallMs;		smallMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
	hkMotionState bigMs;	bigMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
	{
		
		hkVector4 smallPos0, smallPos1;
		smallPos0.set( 2.0f, 0, 1.f);
		smallPos1.set( 2.0f, 0,-1.f);
		hkSweptTransformUtil::warpToPosition( smallPos0, smallMs );
		hkSweptTransformUtil::keyframeMotionState( stepInfo, smallPos1, hkQuaternion::getIdentity(), smallMs );
	}

	hkpCollidable bodyA( HK_NULL, &smallMs );
	hkpCollidable bodyB( HK_NULL, &bigMs );

	hkpProcessCollisionOutput output(HK_NULL);
	ContinuousGskTest_callGsk( stepInfo, bodyA, bodyB,output ); 
	HK_TEST( output.m_toi.m_time > 10.0f );
}


// small box dropping rotating over the edge of another edge
// it results in lot's of internal iterations, as the distance is small, the rotating box
// constantly violates the separating plane criteria
static void ContinuousGskTest5_01Linear_2Angular_PPSlide()
{

	hkStepInfo stepInfo( hkTime(1.0f), hkTime(1.1f) );
	hkMotionState smallMs;
	{
		smallMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
		smallMs.m_objectRadius = 2.0f;
		
		hkVector4 smallPos0, smallPos1;
		smallPos0.set( 2.0f, 0,  0.1f);
		smallPos1.set( 2.0f, 0, -0.1f);
		hkQuaternion smallRot0; smallRot0.setIdentity();
		hkQuaternion smallRot1; smallRot1.m_vec.set( 0, .8f, 0, 1.0f ); smallRot1.normalize();

		hkSweptTransformUtil::warpToPosition( smallPos0, smallMs );
		hkSweptTransformUtil::keyframeMotionState( stepInfo, smallPos1, smallRot1, smallMs );
	}
	
	hkMotionState bigMs;	bigMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );

	hkpCollidable bodyA( HK_NULL, &smallMs );
	hkpCollidable bodyB( HK_NULL, &bigMs );

	hkpProcessCollisionOutput output(HK_NULL);
	ContinuousGskTest_callGsk( stepInfo, bodyA, bodyB,output ); 
	HK_TEST( output.m_toi.m_time > 10.0f );
}


// small box dropping rotating over the edge of another edge and just hitting it
static void ContinuousGskTest6_01Linear_2Angular_PPHit()
{

	hkStepInfo stepInfo( hkTime(1.0f), hkTime(1.1f) );
	hkMotionState smallMs;
	{
		smallMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
		
		hkVector4 smallPos0, smallPos1;
		smallPos0.set( 1.9f, 0, 0.00f );
		smallPos1.set( 2.0f, 0, -0.1f );
		hkQuaternion smallRot0; smallRot0.setIdentity();
		hkQuaternion smallRot1; smallRot1.m_vec.set( 0, .8f, 0, 1.0f ); smallRot1.normalize();

		hkSweptTransformUtil::warpToPosition( smallPos0, smallMs );
		hkSweptTransformUtil::keyframeMotionState( stepInfo, smallPos1, smallRot1, smallMs );
	}
	
	hkMotionState bigMs;	bigMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );

	hkpCollidable bodyA( HK_NULL, &smallMs );
	hkpCollidable bodyB( HK_NULL, &bigMs );

	hkpProcessCollisionOutput output(HK_NULL);
	ContinuousGskTest_callGsk( stepInfo, bodyA, bodyB,output ); 
	HK_TEST( hkMath::equal( output.m_toi.m_time, 1.01f, 0.001f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_seperatingVelocity, -0.9f, 0.01f ) );
	// <todo fix next test
	// HK_TEST( hkMath::equal( output.m_toi.m_contactPoint.getNormal()(0), 0.10f, 0.002f ) );
}



// small box dropping rotating over the edge of another edge and just hitting it
static void ContinuousGskTest7_01Linear_2Angular_EEHit()
{
	hkStepInfo stepInfo( hkTime(1.0f), hkTime(1.1f) );
	hkMotionState smallMs;
	{
		smallMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
		smallMs.m_objectRadius = 2.0f;
		
		hkVector4 smallPos0; smallPos0.set( 2.0f, 0,  0.00f);
		hkVector4 smallPos1; smallPos1.set( 2.0f, 0,  0.00f);
		hkQuaternion smallRot0; smallRot0.setIdentity();
		hkQuaternion smallRot1; smallRot1.m_vec.set( 0.0f, 2.0f, 0, 1.0f ); smallRot1.normalize();

		hkSweptTransformUtil::warpToPosition( smallPos0, smallMs );
		hkSweptTransformUtil::keyframeMotionState( stepInfo, smallPos1, smallRot1, smallMs );
	}
	
	hkMotionState bigMs;	bigMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );

	hkpCollidable bodyA( HK_NULL, &smallMs );
	hkpCollidable bodyB( HK_NULL, &bigMs );

	hkpProcessCollisionOutput output(HK_NULL);
	ContinuousGskTest_callGsk( stepInfo, bodyA, bodyB,output ); 
	HK_TEST( hkMath::equal( output.m_toi.m_time, 1.07f, 0.001f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_seperatingVelocity, -7.04f, 0.01f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_contactPoint.getNormal()(2), -0.0088f, 0.03f ) );
}




// small box dropping rotating over ground
// The first point will just miss the big plane,
// check the .doc file
static void ContinuousGskTest9_0Linear_05Angular_PfJustHit2()
{

	hkStepInfo stepInfo( hkTime(1.0f), hkTime(1.1f) );
	hkMotionState smallMs;
	{
		smallMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );
		
		hkVector4 smallPos0; smallPos0.set( 0, 0,  1.0f);
		hkVector4 smallPos1; smallPos1.set( 0, 0,  1.0f);
		hkQuaternion smallRot0; smallRot0.setIdentity();
		hkQuaternion smallRot1; smallRot1.m_vec.set( -1.0f, 0, 0, 0.5f ); smallRot1.normalize();

		hkSweptTransformUtil::warpToPosition( smallPos0, smallMs );
		hkSweptTransformUtil::keyframeMotionState( stepInfo, smallPos1, smallRot1, smallMs );
	}
	
	hkMotionState bigMs;	bigMs.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );

	hkpCollidable bodyA( HK_NULL, &smallMs );
	hkpCollidable bodyB( HK_NULL, &bigMs );

	hkpProcessCollisionOutput output(HK_NULL);
	ContinuousGskTest_callGsk( stepInfo, bodyA, bodyB,output ); 
	HK_TEST( hkMath::equal( output.m_toi.m_time, 1.0694717f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_seperatingVelocity, -21.91f, 0.01f ) );
	HK_TEST( hkMath::equal( output.m_toi.m_contactPoint.getNormal()(2), 1.0f ) );
}


// We will need these shapes.
	
int ContinuousGskTest_main()
{
	ContinuousGskTest0_RecalcContact();
	ContinuousGskTest1_02Linear_0Angular_PfHit();
	ContinuousGskTest2_0Linear_1Angular_PfMiss();
	ContinuousGskTest4_1Linear_0Angular_PPSlide();
	ContinuousGskTest5_01Linear_2Angular_PPSlide();
#if 0
	// <os.todo> these test fail on xbox360 and win32
	ContinuousGskTest3_0Linear_2Angular_PfHit();
	ContinuousGskTest6_01Linear_2Angular_PPHit();
	ContinuousGskTest7_01Linear_2Angular_EEHit();
	ContinuousGskTest9_0Linear_05Angular_PfJustHit2();
#endif
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(ContinuousGskTest_main, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
