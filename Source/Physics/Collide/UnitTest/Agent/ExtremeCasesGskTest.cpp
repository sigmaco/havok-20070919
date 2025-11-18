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
 // Large include
#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Collide/Agent/ConvexAgent/Gjk/hkpGskfAgent.h>
#include <Physics/Collide/Agent/hkpCollisionInput.h>
#include <Physics/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h>
#include <Physics/Collide/Query/Collector/BodyPairCollector/hkpFlagCdBodyPairCollector.h>
#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>

#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>



	// Check various configurations, both penetrating and non-penetrating.
int ExtremeCasesGskTest()
{
	//
	//	Create a sphere and a triangle 
	//
	hkMotionState ms;
	hkpTriangleShape triangleShape;
	hkpSphereShape sphereShape( 1.0f );
	hkpCollidable sphereBody( &sphereShape, &ms, 0 );
	hkpCollidable triangleBody( &triangleShape, &ms, 0 );
	{
		ms.getTransform().setIdentity();


		hkVector4 va; va.set( 0.f,-1.f, 0.f);
		hkVector4 vb; vb.set( 0.f, 1.f, 1.f );
		hkVector4 vc; vc.set( 0.f, 1.f,-1.f);

		triangleShape.setVertex( 0, va );
		triangleShape.setVertex( 1, vb );
		triangleShape.setVertex( 2, vc );
	}

	//
	//	Query the system
	//
	{
		hkpCollisionInput input;
		input.m_tolerance = 1.f;

		hkpClosestCdPointCollector collector;
		hkpGskfAgent::staticGetClosestPoints( sphereBody, triangleBody, input, collector );
		HK_TEST( collector.hasHit() );
	}
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(ExtremeCasesGskTest, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );


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
