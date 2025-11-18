/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Internal/hkpInternal.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/System/Stopwatch/hkStopwatch.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Types/Geometry/Sphere/hkSphere.h>

#include <Physics/Internal/Collide/Gjk/hkpGsk.h>
#include <Physics/Internal/Collide/Gjk/hkpGskCache.h>
#include <Physics/Utilities/Collide/hkpShapeGenerator.h>

#include <Physics/Internal/Collide/Gjk/hkpGjk.h>
#include <Physics/Internal/Collide/Gjk/hkpGjkCache.h>

#include <Physics/Internal/Collide/Gjk/Penetration/hkpWingedEdge.h>
#include <Physics/Internal/Collide/Gjk/Penetration/hkpConvexPenetrationUtil.h>
#include <Physics/Internal/Collide/Util/hkpCollideTriangleUtil.h>

#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>



extern "C" { void HK_CALL srand( unsigned int ); }


static void testGskCase( int index, const hkTransform& aTb, const hkpConvexShape* shapeA, const hkpConvexShape* shapeB  )
{
	hkStopwatch sw0;
	hkStopwatch sw1;
	hkStopwatch sw2;
	hkStopwatch sw3;

	hkpGskOut gjkOut;
	hkpGjkCache cache;
	

	//const int NLOOP = 10000;
	const int NLOOP = 1;

	{
		sw0.start();
		for(int j = 0; j < NLOOP; ++j)
		{
			cache.rSize = 0;
			hkpGjk::GJK( shapeA, shapeB, aTb, cache, gjkOut );
		}
		sw0.stop();
	}			


	hkpGsk gsk;
	hkpGskCache gskCache;
	hkVector4 separatingNormal;
	
	{
		sw1.start();
		for(int j = 0; j < NLOOP; ++j)
		{
			gskCache.init( shapeA, shapeB, aTb);
			gsk.init( shapeA, shapeB, gskCache );
			gsk.getClosestFeature( shapeA, shapeB, aTb, separatingNormal );
			gsk.checkForChangesAndUpdateCache( gskCache );
		}
		sw1.stop();
	}

	//
	//	Check repeating calls
	//
	if (NLOOP>1){
		cache.rSize = 0;
		hkpGjk::GJK( shapeA, shapeB, aTb, cache, gjkOut );

		sw2.start();
		for(int j = 0; j < NLOOP; ++j)
		{
			hkpGjk::GJK( shapeA, shapeB, aTb, cache, gjkOut );
		}
		sw2.stop();

		gskCache.init( shapeA, shapeB, aTb);
		gsk.init( shapeA, shapeB, gskCache );
		gsk.getClosestFeature( shapeA, shapeB, aTb, separatingNormal );
		gsk.checkForChangesAndUpdateCache( gskCache );

		{
			sw3.start();
			for(int j = 0; j < NLOOP; ++j)
			{
				gsk.init( shapeA, shapeB, gskCache );
				gsk.getClosestFeature( shapeA, shapeB, aTb, separatingNormal );
				gsk.checkForChangesAndUpdateCache( gskCache );
			}
			sw3.stop();
		}
	}

	//
	// check result timers
	//
	if ( NLOOP > 1){
		hkReal t0 = sw0.getSplitSeconds() * (1000000 / NLOOP);
		hkReal t1 = sw1.getSplitSeconds() * (1000000 / NLOOP);
		hkReal ratio = t0 / (t1 + 1e-15f);
		static hkReal average = 0.0f;
		if(average !=0 )
		{
			average = 0.1f * ratio + 0.9f * average;
		}
		else
		{
			average = ratio;
		}
		//hkprintf("%3i ", index );
		//hkprintf("%f\t%f\t%f\t%f			", t0, t1, ratio, average );
	}

	if( NLOOP > 1 )
	{
		hkReal t0 = sw2.getSplitSeconds() * (1000000 / NLOOP);
		hkReal t1 = sw3.getSplitSeconds() * (1000000 / NLOOP);
		hkReal ratio = t0 / (t1 + 1e-15f);
		static hkReal average = 0.0f;
		if(average!=0)
		{
			average = 0.1f * ratio + 0.9f * average;
		}
		else
		{
			average = ratio;
		}
		/*
		if (1)
		{
			hkprintf("%f\t%f\t%f\t%f\n", t0, t1, ratio, average );
		}
		else
		{
			hkprintf( "\n" );
		}
		*/
	}

	//
	//	Check correctness of results
	//
	if(1)
	{

		hkReal diff = gjkOut.m_distance - separatingNormal(3);
		if ( diff > 1e-2f )
		{
			char buf[256];

			hkString::sprintf( buf, "Good: GJK failure: GJK[%f] minus GSK[%f]  = %f at iteration %i",gjkOut.m_distance.val(), separatingNormal(3), diff, index );
		//	HK_TEST2( 0, buf );
		}

		if ( diff < -1e-2f )
		{
			char buf[256];
			hkString::sprintf(buf, "****: GSK failure: GJK[%f] minus GSK[%f]  = %f at iteration %i\n", gjkOut.m_distance.val(), separatingNormal(3), diff, index );
			HK_TEST2( 0, buf );
		}
	}


	//HK_ASSERT(0x71811130,  hkMath::fabs( diff ) < 1e-2f );
}

static void randBox(hkVector4& min, hkVector4& max, hkReal size, hkPseudoRandomGenerator* generator)
{
	min.setZero4();
	max.setZero4();
	for(int i=0; i<3; ++i)
	{
		hkReal x = generator->getRandRange(-size, size);
		hkReal y = generator->getRandRange(-size, size);
		if( x > y)
		{
			hkAlgorithm::swap( x, y );
		}
		min(i) = x;
		max(i) = y;
	}
}
/*
static void randVec(hkVector4& v)
{
	v.setZero4();
	for(int i=0; i<3; ++i)
	{
		v(i) = hkMath::randRange(-100, 100);
	}
}
*/

static int gskRandomCases()
{
	hkPseudoRandomGenerator generator(747);

	hkTransform aTb;
	aTb.getRotation().setIdentity();
	aTb.setTranslation( hkVector4::getZero() );
	{
		for(int i = 0; i < 5000; ++i)
		{
			//if ( (i % 100000) == 0){ hkprintf("%i\n",i); }

			generator.setSeed( i * 75 );

			//
			// 3 dimensional boxes overlapping
			//
			if (1)
			{
				hkTransform aTb2;
				hkVector4 axis; axis.set( .1f, .2f, .3f ); axis.normalize3();

				aTb2.getRotation().setAxisAngle( axis, generator.getRandRange( -1.0f, 1.0f ) );
				aTb2.setTranslation( hkVector4::getZero() );

				hkAabb boxA; randBox(boxA.m_min, boxA.m_max, 100.0f, &generator);
				hkAabb boxB; randBox(boxB.m_min, boxB.m_max, 100.0f, &generator);
				generator.setSeed( i * 75 );	hkpConvexShape* shapeA = hkpShapeGenerator::createRandomConvexVerticesShape(boxA.m_min, boxA.m_max, 24, &generator, hkpShapeGenerator::NO_PLANE_EQUATIONS );
				generator.setSeed( i * 1001 );	hkpConvexShape* shapeB = hkpShapeGenerator::createRandomConvexVerticesShape(boxB.m_min, boxB.m_max, 24, &generator, hkpShapeGenerator::NO_PLANE_EQUATIONS );
				testGskCase( i, aTb2, shapeA, shapeB );
				shapeA->removeReference();
				shapeB->removeReference();
			}
			i++;

			//
			// 3 dimensional boxes non ovelapping with tiny triangles
			//
			if (1)
			{
				hkAabb boxA; randBox(boxA.m_min, boxA.m_max, 100.0f, &generator);
				hkAabb boxB; randBox(boxB.m_min, boxB.m_max, 100.0f, &generator);
				const float tinyEdgeLen = .1f;
				boxA.m_min(1) -= boxA.m_max(1); boxA.m_max(1) = 0;
				boxB.m_max(1) -= boxB.m_min(1) - tinyEdgeLen*2; boxB.m_min(1) = tinyEdgeLen*2;
				generator.setSeed( i * 75 );	hkpConvexShape* shapeA = hkpShapeGenerator::createRandomConvexVerticesShapeWithThinTriangles(boxA.m_min, boxA.m_max, 24, tinyEdgeLen, &generator, hkpShapeGenerator::NO_PLANE_EQUATIONS );
				generator.setSeed( i * 1001 );	hkpConvexShape* shapeB = hkpShapeGenerator::createRandomConvexVerticesShapeWithThinTriangles(boxB.m_min, boxB.m_max, 24, tinyEdgeLen, &generator, hkpShapeGenerator::NO_PLANE_EQUATIONS );
				testGskCase( i, aTb, shapeA, shapeB );
				shapeA->removeReference();
				shapeB->removeReference();
			}
			i++;

			//
			//	Two flat objects, non overlapping
			//
			if (1)
			{
				const float gap = 0.1f;

				const float sizeA = 10.0f;
				const float thicknessA = 0.1f;

				hkAabb boxA;
				boxA.m_min.set( -sizeA, -thicknessA, -sizeA );
				boxA.m_max.set(  sizeA,        0.0f, sizeA );

				const float sizeB      = 100.0f;
				const float thicknessB = 0.1f;

				hkAabb boxB;
				boxB.m_min.set( -sizeB,	gap,             -sizeB );
				boxB.m_max.set(  sizeB, gap + thicknessB, sizeB );

				generator.setSeed( i * 75 );	hkpConvexShape* shapeA = hkpShapeGenerator::createRandomConvexVerticesShape(boxA.m_min, boxA.m_max, 24, &generator, hkpShapeGenerator::NO_PLANE_EQUATIONS );
				generator.setSeed( i * 1001 );	hkpConvexShape* shapeB = hkpShapeGenerator::createRandomConvexVerticesShape(boxB.m_min, boxB.m_max, 24, &generator, hkpShapeGenerator::NO_PLANE_EQUATIONS );
				testGskCase( i, aTb, shapeA, shapeB );
				shapeA->removeReference();
				shapeB->removeReference();
			}
			i++;
		}
	}

	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(gskRandomCases, "Fast", "Physics/Test/UnitTest/Internal/", __FILE__     );




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
