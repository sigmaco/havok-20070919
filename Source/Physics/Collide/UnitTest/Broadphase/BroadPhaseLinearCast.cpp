/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
 // Large include

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>

#include <Physics/Internal/Collide/BroadPhase/3AxisSweep/hkp3AxisSweep.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseHandlePair.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseCastCollector.h>

#include <Physics/Collide/Agent/Util/Null/hkpNullAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/Gjk/hkpGskConvexConvexAgent.h>
#include <Physics/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h>
#include <Physics/Collide/Query/CastUtil/hkpLinearCastInput.h>
#include <Physics/Collide/Agent/hkpCollisionAgentConfig.h>

#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

class MyFlagCollector: public hkpBroadPhaseCastCollector
{
public:
	MyFlagCollector(){ m_hasHit = false; }
	virtual	hkReal addBroadPhaseHandle( const hkpBroadPhaseHandle* broadphaseHandle, int castIndex )
	{
		m_hasHit = true;
		return 0.0f;
	}

	hkBool m_hasHit;

};

static void HK_CALL testLinearPatch( hkPseudoRandomGenerator& rndGen, hkpBroadPhase& broadPhase, hkpCollisionDispatcher& dispatcher, hkReal worldSize )
{
	//
	// add a single random object to the broadphase
	//

	hkAabb aabb;

	hkReal size = hkMath::min2( 1.0f, worldSize );

#define RL rndGen.getRandRange( -size, 0 )
#define RH(i) rndGen.getRandRange( aabb.m_min(i), size )

	aabb.m_min.set( RL, RL, RL );
	aabb.m_max.set( RH(0), RH(1), RH(2) );

	aabb.m_max.setNeg4( aabb.m_min );

	hkpBroadPhaseHandle object;

	hkArray<hkpBroadPhaseHandlePair> newPairsOut;

	broadPhase.lock();
	broadPhase.addObject( &object, aabb, newPairsOut );
	broadPhase.unlock();

	//
	// create a shape with the same dimensions
	//
	hkVector4 extents; extents.setSub4( aabb.m_max, aabb.m_min );
	extents.mul4( 0.5f );

	hkpBoxShape boxShape( extents, 0.0f );
	hkVector4 center; center.setInterpolate4( aabb.m_max, aabb.m_min, 0.5f );

	//
	// create a query shape
	//
	hkVector4 queryExtents;	rndGen.getRandomVector11(queryExtents);
	queryExtents.setAbs4( queryExtents );
	hkpBoxShape queryShape( queryExtents, 0.0f );

	hkMotionState ms;
	ms.getTransform().setIdentity();
	hkpCollidable collA( &queryShape, &ms );


	hkpCollisionAgentConfig collisionAgentConfig;
	collisionAgentConfig.m_iterativeLinearCastEarlyOutDistance = 0.0f;
	hkpLinearCastCollisionInput input;
	input.m_dispatcher = &dispatcher;
	input.m_filter = HK_NULL;
	input.m_config = &collisionAgentConfig;



	//
	//	Perform a series of random linear casts
	//	
	for (int i = 0; i < 20; i++ )
	{
		hkVector4 from;  rndGen.getRandomVector11( from );
		hkVector4 to;	 rndGen.getRandomVector11( to );
		if ( worldSize < 0.5f )
		{
			to.setNeg4( from );	// make sure we always hit this object
		}

		ms.getTransform().setTranslation( from );
		//
		// check the shape Linearcast
		//
		static int c = 0;
		if ( ++c == 4251 )
		{
			c = c;
		}

		hkBool shapeHits = false;
		{

			hkpClosestCdPointCollector collector;
			hkpClosestCdPointCollector startCollector;

			hkMotionState msB;
			msB.getTransform().setIdentity();
			msB.getTransform().setTranslation( center );
			
			hkpCollidable collB( &boxShape, &msB );

			hkVector4 path; path.setSub4( to, from );
			input.setPathAndTolerance( path, 0.0f );



			hkpGskConvexConvexAgent::staticLinearCast( collA, collB, input, collector, &startCollector );

			//
			//	If we have penetration than hit
			//
			if ( startCollector.hasHit() && startCollector.getHitContact().getDistance() < 0 )
			{
				shapeHits = true;
			}
			
			if ( collector.hasHit() )
			{
				shapeHits = true;
			}
		}

		if ( !shapeHits )
		{
			continue;
		}

		//
		//	Now our broadphase also must return a hit
		//

		MyFlagCollector collector;

		hkpBroadPhase::hkpCastAabbInput ci;

		ci.m_from = from;
		ci.m_to = to;
		ci.m_halfExtents = queryExtents;

		broadPhase.lock();
		broadPhase.castAabb( ci, collector );
		broadPhase.unlock();

		if ( rndGen.getCurrent() == 0x0900786d)
		{
			// this test does not hit because of numerical accuracy problems
			continue;
		}

		HK_TEST2( collector.m_hasHit, "At iteration: " << c );
	}
}

int broadphaseLinearcast_main()
{
	hkpCollisionDispatcher dispatcher(hkpNullAgent::createNullAgent, HK_NULL);

	hkRegisterAlternateShapeTypes( &dispatcher );
	hkpGskConvexConvexAgent::registerAgent( &dispatcher );

	hkReal worldSize  = 100000.001f;
	hkPseudoRandomGenerator rndGen(101);
	

	hkReal minWorldSize = 0.001f;

	const hkBool temporarilyExcludeLowerRangeFromUnitTest = true;
	if (temporarilyExcludeLowerRangeFromUnitTest) 
	{
		minWorldSize = 2.0f; // some internal numerical consistency checks fail when using smaller broadphase size
	}

	while( worldSize > minWorldSize ) 
	{
		worldSize *= 0.99f;
		hkVector4 worldMax; worldMax.setAll( worldSize );
		hkVector4 worldMin; worldMin.setNeg4( worldMax );
		{
			hkpBroadPhase* broadPhase = hk3AxisSweep16CreateBroadPhase( worldMin, worldMax, 4 );
			testLinearPatch( rndGen, *broadPhase, dispatcher, worldSize );
			broadPhase->markForWrite();
			delete broadPhase;
		}
		{
			hkpBroadPhase* broadPhase = hk3AxisSweep32CreateBroadPhase( worldMin, worldMax, 4 );
			testLinearPatch( rndGen, *broadPhase, dispatcher, worldSize );
			broadPhase->markForWrite();
			delete broadPhase;
		}
	}
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(broadphaseLinearcast_main, "Slow", "Physics/Test/UnitTest/Collide/", __FILE__     );


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
