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

//sort of checks inverse too
static void mul_inverse_equals()
{
	//make up a space
	hkMatrix4 the_identity;
	the_identity.setIdentity();

	hkVector4 rand_first_row; rand_first_row.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
	rand_first_row.normalize3();
	hkVector4 rand_second_row;
	hkVector4Util::calculatePerpendicularVector( rand_first_row, rand_second_row);
	rand_second_row.normalize3();

	hkVector4 rand_third_row;
	rand_third_row.setCross( rand_first_row, rand_second_row );

	hkVector4 rand_forth_row; rand_forth_row.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01(), 1.0f );

	hkMatrix4 rand_mat4;
	rand_mat4.setRows( rand_first_row, rand_second_row, rand_third_row, rand_forth_row );

	hkMatrix4 rand_inverse( rand_mat4 );
	rand_inverse.invert( 0.001f );

	hkMatrix4 should_be_identity;
	should_be_identity.setMul( rand_mat4, rand_inverse );
	HK_TEST( should_be_identity.isApproximatelyEqual( the_identity ) );

	should_be_identity.setMulInverse( rand_mat4, rand_mat4 );
	HK_TEST( should_be_identity.isApproximatelyEqual( the_identity ) );
}

static void mul()
{
	// make up a result matrix
	hkMatrix4 the_result;
	hkVector4 c0; c0.set(2.25f, 2.25f, 2.25f); 
	hkVector4 c1; c1.set(2.625f, 2.625f, 2.625f); 
	hkVector4 c2; c2.set(2.85f, 2.85f, 2.85f);
	hkVector4 c3; c3.set(1.5f, 3, 4.5f, 6);
	the_result.setCols(c0, c1, c2, c3);

	// make up a test matrix for ::mul
	hkMatrix4 test_matrix;
	hkVector4 cc0; cc0.set(1.5f, 1.5f, 1.5f);
	hkVector4 cc1; cc1.set(1.75f, 1.75f, 1.75f);
	hkVector4 cc2; cc2.set(1.9f, 1.9f, 1.9f);
	hkVector4 cc3; cc3.set(1,2,3,4);
	test_matrix.setCols(cc0, cc1, cc2, cc3);

	test_matrix.mul(1.5f);
	HK_TEST( test_matrix.isApproximatelyEqual(the_result, 0.0f));
}

static void set_mul()
{
	// make up a result matrix
	hkMatrix4 the_result;
	hkVector4 c0; c0.set(2.25f, 2.25f, 2.25f); 
	hkVector4 c1; c1.set(2.625f, 2.625f, 2.625f); 
	hkVector4 c2; c2.set(2.85f, 2.85f, 2.85f);
	hkVector4 c3; c3.set(1.5f, 3, 4.5f, 6);
	the_result.setCols(c0, c1, c2, c3);

	// make up a test matrix for ::setmul
	hkMatrix4 the_source;
	hkVector4 cc0; cc0.set(1.5f, 1.5f, 1.5f);
	hkVector4 cc1; cc1.set(1.75f, 1.75f, 1.75f);
	hkVector4 cc2; cc2.set(1.9f, 1.9f, 1.9f);
	hkVector4 cc3; cc3.set(1,2,3,4);
	the_source.setCols(cc0, cc1, cc2, cc3);

	hkMatrix4 test_matrix;
	test_matrix.setMul( 1.5f, the_source );

	HK_TEST( test_matrix.isApproximatelyEqual(the_result, 0.0f));
}

static void bugs_fixed()
{
	hkMatrix4 randomMatrix;
	hkVector4 c0; c0.set(hkMath::rand01(), hkMath::rand01(), hkMath::rand01(), hkMath::rand01()); 
	hkVector4 c1; c1.set(hkMath::rand01(), hkMath::rand01(), hkMath::rand01(), hkMath::rand01()); 
	hkVector4 c2; c2.set(hkMath::rand01(), hkMath::rand01(), hkMath::rand01(), hkMath::rand01()); 
	hkVector4 c3; c3.set(hkMath::rand01(), hkMath::rand01(), hkMath::rand01(), hkMath::rand01()); 
	randomMatrix.setCols(c0, c1, c2, c3);

	// HVK-3599 : setTranspose didn't really transpose
	{
		hkMatrix4 copy = randomMatrix;
		copy.transpose();
		copy.transpose();
		HK_TEST(copy.isApproximatelyEqual(randomMatrix,0.0f));

		copy.setTranspose(randomMatrix);
		copy.transpose();
		HK_TEST(copy.isApproximatelyEqual(randomMatrix,0.0f));

		copy = randomMatrix;
		copy.transpose();
		hkMatrix4 copy2; copy2.setTranspose(copy);
		HK_TEST(copy2.isApproximatelyEqual(randomMatrix,0.0f));
	}	
}

static void vector_ops()
{
	// vector multiplication - arbitrary values (not a transformation)
	{
		hkMatrix4 arbitraryMatrix;
		hkVector4 r0; r0.set( 1, 2, 3, 4);
		hkVector4 r1; r1.set( 5, 6, 7, 8);
		hkVector4 r2; r2.set( 9,10,11,12);
		hkVector4 r3; r3.set(13,14,15,16);
		arbitraryMatrix.setRows(r0,r1,r2,r3);

		HK_TEST(!arbitraryMatrix.isTransformation());

		hkVector4 arbitraryVector;
		arbitraryVector.set(10,20,30,40);

		hkVector4 result;
		arbitraryMatrix.multiplyVector(arbitraryVector, result);

		HK_TEST(result.equals4(hkVector4(300,700,1100,1500)));
	}

	// transformation of positions and directions
	{
		hkMatrix4 aTransform;
		hkVector4 r0; r0.set(-2, 0, 0, 1);
		hkVector4 r1; r1.set( 0, 0, 1, 2);
		hkVector4 r2; r2.set( 0, 3, 0, 3);
		hkVector4 r3; r3.set( 0, 0, 0, 1);
		aTransform.setRows(r0,r1,r2,r3);

		HK_TEST(aTransform.isTransformation());

		hkVector4 aVector;
		aVector.set(10,20,30,40); // the 40 should be ignored

		hkVector4 result;
		aTransform.transformPosition(aVector, result);

		HK_TEST(result.equals4(hkVector4(-19,32,63,1)));

		aTransform.transformDirection(aVector, result);

		HK_TEST(result.equals4(hkVector4(-20,30,60,0)));
	}
}

int matrix4_main()
{
	mul_inverse_equals();
	mul();
	set_mul();
	bugs_fixed();
	vector_ops();
	return 0;
}

//void ___1() { }
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(matrix4_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
