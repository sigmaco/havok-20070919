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

// Large include
#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppUtility.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastOutput.h>

#include <Demos/DemoCommon/Utilities/GameUtils/Landscape/FlatLand.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

static int keysSame( hkpShapeKey* k0, hkpShapeKey* k1 )
{
	for( int i = 0; true; ++i )
	{
		if( (k0[i] == HK_INVALID_SHAPE_KEY) && (k1[i] == HK_INVALID_SHAPE_KEY) )
		{
			return 1;
		}
		else if ( k0[i] == k1[i] )
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
}

//
// raycast_tests method, actually does the ray tests
//
int MoppRaycastEpsilonTestMain(  )
{
	hkPseudoRandomGenerator randomGen(202);
	{		
		FlatLand flatLandServer;
		hkVector4 scaling( 100.0f, 100.0f, 100.0f );
		flatLandServer.setScaling( scaling );

		// Usually Mopps are not built at run time but preprocessed instead. We disable the performance warning
		bool wasEnabled = hkError::getInstance().isEnabled(0x6e8d163b); 
		hkError::getInstance().setEnabled(0x6e8d163b, false); // hkpMoppUtility.cpp:18
		hkpShape* shape = flatLandServer.createMoppShape();
		hkError::getInstance().setEnabled(0x6e8d163b, wasEnabled);

		// get the aabb
		hkAabb aabb;
		shape->getAabb( hkTransform::getIdentity(), 0.0f, aabb );

		//
		//	Test many random combinations
		//
		for (int i = 0; i < 2000; i++ )
		{
			//
			//	Find a raycast 
			//
			hkpShapeRayCastInput ray0;
			hkpShapeRayCastInput ray1;
			{
				ray0.m_from(0) = randomGen.getRandRange( aabb.m_min(0), aabb.m_max(0) );
				ray0.m_from(1) = aabb.m_min(1);
				ray0.m_from(2) = randomGen.getRandRange( aabb.m_min(2), aabb.m_max(2) );

				ray0.m_to(0) = randomGen.getRandRange( aabb.m_min(0), aabb.m_max(0) );
				ray0.m_to(1) = aabb.m_max(1);
				ray0.m_to(2) = randomGen.getRandRange( aabb.m_min(2), aabb.m_max(2) );

				ray1.m_from(0) = randomGen.getRandRange( aabb.m_min(0), aabb.m_max(0) );
				ray1.m_from(1) = aabb.m_min(1);
				ray1.m_from(2) = randomGen.getRandRange( aabb.m_min(2), aabb.m_max(2) );

				ray1.m_to(0) = randomGen.getRandRange( aabb.m_min(0), aabb.m_max(0) );
				ray1.m_to(1) = aabb.m_max(1);
				ray1.m_to(2) = randomGen.getRandRange( aabb.m_min(2), aabb.m_max(2) );
			}

			//
			//	Initial test
			//
			hkpShapeRayCastOutput out0;
			hkpShapeRayCastOutput out1;
			{

				shape->castRay( ray0, out0 );
				shape->castRay( ray1, out1 );

				if ( !out0.hasHit() || !out1.hasHit() )
				{
					continue;
				}
				
				if ( keysSame(out0.m_shapeKeys, out1.m_shapeKeys) )
				{
					continue;
				}
			}

			//
			//	Try to bring raycast 0 to raycast 1
			//
			for (int a = 0; a < 40; a++)
			{
				hkpShapeRayCastInput rayMid;
				hkpShapeRayCastOutput outMid;
				rayMid.m_from.setInterpolate4( ray0.m_from, ray1.m_from, 0.5f );
				rayMid.m_to.setInterpolate4( ray0.m_to, ray1.m_to, 0.5f );

				shape->castRay( rayMid, outMid );

				if (!outMid.hasHit() )
				{
					HK_TEST2( 0, "Raycast fall through the landscape" );
					break;
				}

				if ( keysSame(out0.m_shapeKeys, out1.m_shapeKeys) )
				{
					ray1 = rayMid;
				}
				else
				{
					ray0 = rayMid;
				}
			}
		}
		delete shape;
	}
	return 0;
}


//
// test registration
//
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(MoppRaycastEpsilonTestMain,     "Slow", "Test/Test/UnitTest/UnitTest/UnitTest/Collide/",     __FILE__     );

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
