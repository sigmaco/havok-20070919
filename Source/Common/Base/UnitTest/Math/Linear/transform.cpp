/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Math/Linear/hkMathStream.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>

//sort of checks inverse too
static void is_identity()
{
	//make up a space
	
	hkVector4 rand_first_row; rand_first_row.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
	rand_first_row.normalize3();
	hkVector4 rand_second_row;
	hkVector4Util::calculatePerpendicularVector( rand_first_row, rand_second_row);
	rand_second_row.normalize3();

	hkVector4 rand_third_row;
	rand_third_row.setCross( rand_first_row, rand_second_row );

	hkRotation rand_rotation;
	rand_rotation.setRows( rand_first_row, rand_second_row, rand_third_row );

	hkVector4 rand_translation; rand_translation.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );

	hkTransform rand_transform( rand_rotation, rand_translation );
	hkTransform rand_inverse;
	rand_inverse.setInverse( rand_transform );

	hkTransform should_be_identity;
	should_be_identity.setMul( rand_transform, rand_inverse );
	HK_TEST( should_be_identity.isApproximatelyEqual( hkTransform::getIdentity() ) );

	should_be_identity.setMulMulInverse( rand_transform, rand_transform );
	HK_TEST( should_be_identity.isApproximatelyEqual( hkTransform::getIdentity() ) );

	should_be_identity.setMulInverseMul( rand_transform, rand_transform );
	HK_TEST( should_be_identity.isApproximatelyEqual( hkTransform::getIdentity() ) );
}

static void sweptTransformTest()
{
	hkMotionState ms0;
	ms0.initMotionState( hkVector4::getZero(), hkQuaternion::getIdentity() );

	hkVector4 mc; mc.set( 1,2,3 );
	hkSweptTransformUtil::setCentreOfRotationLocal( mc, ms0 );

	hkQuaternion q; q.setAxisAngle( hkTransform::getIdentity().getColumn(1), 1.0f );

	hkSweptTransformUtil::warpToRotation( q, ms0 );

	HK_TEST( ms0.getTransform().getTranslation().equals3( hkVector4::getZero()));
}

int transform_main()
{
	sweptTransformTest();
	is_identity();
	return 0;
}

//void ___1() { }
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(transform_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
