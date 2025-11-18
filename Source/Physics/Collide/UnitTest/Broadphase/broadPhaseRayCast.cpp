/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Physics/Collide/Agent/Collidable/hkpCollidable.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastOutput.h>
#include <Physics/Internal/Collide/BroadPhase/3AxisSweep/hkp3AxisSweep.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseHandlePair.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseCastCollector.h>


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

static void HK_CALL testRayPatch( hkPseudoRandomGenerator& rndGen, hkpBroadPhase& broadPhase, hkReal worldSize )
{
	broadPhase.lock();

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

	broadPhase.addObject( &object, aabb, newPairsOut );

	//
	// create a shape with the same dimensions
	//
	hkVector4 extents; extents.setSub4( aabb.m_max, aabb.m_min );
	extents.mul4( 0.5f );

	hkpBoxShape boxShape( extents, 0.0f );
	hkVector4 center; center.setInterpolate4( aabb.m_max, aabb.m_min, 0.5f );


	//
	//	Perform a series of random raycasts
	//	
	for (int i = 0; i < 20; i++ )
	{
		hkVector4 from;  rndGen.getRandomVector11( from );
		hkVector4 to;	 rndGen.getRandomVector11( to );

		const hkReal scaledWorldSize = worldSize * 0.99f;
		for (int c = 0; c < 3; c++)
		{
			from(c) = hkMath::clamp(from(c), -scaledWorldSize, scaledWorldSize);
			to(c) = hkMath::clamp(to(c), -scaledWorldSize, scaledWorldSize);
		}

		if ( worldSize < 0.5f )
		{
			to.setNeg4( from );	// make sure we always hit this object
		}

		//
		// check the shape raycast
		//
		hkBool shapeHits;
		{
			hkpShapeRayCastInput input;
			input.m_from.setSub4( from, center );
			input.m_to.setSub4( to, center );

			hkpShapeRayCastOutput output;

			shapeHits = boxShape.castRay( input, output );
		}

		if ( !shapeHits )
		{
			continue;
		}

		//
		//	Now our broadphase also must return a hit
		//
		static int ci = 0;
		if ( ++ci == 2610 )
		{
			ci = ci;
		}

		MyFlagCollector collector;

		hkpBroadPhase::hkpCastRayInput rayInput;
		rayInput.m_from = from;
		rayInput.m_toBase = &to;
		broadPhase.castRay( rayInput, &collector, 0 );

		HK_TEST2( collector.m_hasHit, "At iteration: " << ci );
	}

	broadPhase.unlock();
}

int broadphaseRaycast_main()
{
	{
		hkPseudoRandomGenerator rndGen(101);
		for ( hkReal worldSize  = 100000.001f; worldSize > 0.001f; worldSize *= 0.99f )
		{
			hkVector4 worldMax; worldMax.setAll( worldSize );
			hkVector4 worldMin; worldMin.setNeg4( worldMax );
			{
				hkpBroadPhase* broadPhase = hk3AxisSweep16CreateBroadPhase( worldMin, worldMax, 4 );
				testRayPatch( rndGen, *broadPhase, worldSize );
				broadPhase->markForWrite();
				delete broadPhase;
			}
		}
	}
	{
		hkPseudoRandomGenerator rndGen(101);
		for ( hkReal worldSize  = 1000.001f; worldSize > 0.001f; worldSize *= 0.99f )
		{
			hkVector4 worldMax; worldMax.setAll( worldSize );
			hkVector4 worldMin; worldMin.setNeg4( worldMax );
			{
				hkpBroadPhase* broadPhase = hk3AxisSweep32CreateBroadPhase( worldMin, worldMax, 4 );
				testRayPatch( rndGen, *broadPhase, worldSize );
				broadPhase->markForWrite();
				delete broadPhase;
			}
		}
	}
	return 0;
}



#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(broadphaseRaycast_main, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );


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
