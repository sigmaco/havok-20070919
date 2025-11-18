/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Physics/Collide/Util/hkpTriangleUtil.h>
#include <Physics/Internal/Collide/Util/hkpCollideTriangleUtil.h>

// Make sure that if a triangle passes isDegenerate, it will not fail in closestPointTriangle

static int degenerate_triangles()
{
	// Three cases

	// Needles:
	// A-----------------------B
	// C
	// Caps:
	//       _____C______
	// A-----------------------B
	// Inbetweenies: (mixture of above)

	hkVector4 startPos[3];
	{
		startPos[0].set( 0,0,0 ); // L
		startPos[1].set( 1,0,0 ); // _|
		startPos[2].set( .5f,0,0 ); // ^
	}

	for( int testType = 0; testType < 3; ++testType )
	{
		for( int scale = 1; scale < 10000; scale*= 10)
		{
			hkVector4 v[3];
			v[1].set(0,0,0);
			v[0].set(hkReal(scale),0,0);
			v[2] = startPos[testType];
			v[2](0) *= scale;
			
			const int end = 1;
			const int ntest = 1000;
			for( int i = 0; i < 1000; ++i )
			{
				v[2](2) = (i*end)/hkReal(ntest);
				
				bool isDegenerate = hkpTriangleUtil::isDegenerate(v[0],v[1],v[2]);
				if( isDegenerate == false )
				{
					{
						hkpCollideTriangleUtil::ClosestPointTriangleCache cache;
						hkpCollideTriangleUtil::setupClosestPointTriangleCache(v, cache);

						//HK_TEST2( setupFailed==false, "test " << testType << " scale " << scale << " iteration " << i << " deg " << isDegenerate << " fail " << setupFailed );
					}
				}
			}
		}
	}

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(degenerate_triangles, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
