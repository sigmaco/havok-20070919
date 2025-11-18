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
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>

#include <Physics/Internal/Collide/Gjk/hkpGsk.h>



static void checkMultiplePenetrations()
{
//	hkVector4  highAndThin( 0.01f, 0.01f, .2f );
	hkVector4  highAndThin; highAndThin.set( 1.f, 1.f, 1.f );
	hkpBoxShape pole( highAndThin );

//	hkVector4  va(  1.0f, 0.f, -0.1f );
//	hkVector4  vb( -1.0f, 0.f, -0.1f );
//	hkVector4  vc( 0.f,  1.f, -0.1f );
//	hkVector4  vd( 0.f, -1.f, -0.1f );

	hkVector4  va; va.set( -20.0f, -20.f, 160.f );
	hkVector4  vb; vb.set( -20.0f,   3.f, 180.f );
	hkVector4  vc; vc.set(  0.f,     0.f, 160.f );
	hkVector4  vd; vd.set(  -40.f,   3.f, 180.f );

	hkpTriangleShape tri0( va, vb, vc );
	hkpTriangleShape tri1( va, vb, vd );

	const hkpConvexShape* shapesB[2] = { &tri0, &tri1 };

	hkContactPoint point0;
	hkContactPoint point1;
	hkContactPoint* points[2] = { &point0, &point1 };

	hkTransform transA; transA.setIdentity();
	transA.getColumn(0).set( -0.77185f,  -0.7028f,     0 );
	transA.getColumn(1).set(  0.707027f, -0.707185f,   0 );
	transA.getColumn(2).set(  0,        -0,        1.0f );
	transA.getColumn(3).set( -15.0006f, -20.5181f, 164.63f );

	hkTransform transB; transB.setIdentity();
	transB.getTranslation().set( 5, -2, 5 );

	hkTransform  aTb; aTb.setMulInverseMul( transA, transB );

	//hkResult didItWork = 
	hkCalcMultiPenetrationDepth( transA, &pole, &shapesB[0], 2, aTb, &points[0]  );


}


// We will need these shapes.
	
int MultiplePenetrationTest_main()
{
	checkMultiplePenetrations();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(MultiplePenetrationTest_main, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
