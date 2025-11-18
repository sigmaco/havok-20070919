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
	hkMatrix3 the_identity;
	the_identity.setIdentity();

	hkVector4 rand_first_row; rand_first_row.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
	rand_first_row.normalize3();
	hkVector4 rand_second_row;
	hkVector4Util::calculatePerpendicularVector( rand_first_row, rand_second_row);
	rand_second_row.normalize3();

	hkVector4 rand_third_row;
	rand_third_row.setCross( rand_first_row, rand_second_row );

	hkMatrix3 rand_mat3;
	rand_mat3.setRows( rand_first_row, rand_second_row, rand_third_row );

	hkMatrix3 rand_inverse( rand_mat3);
	rand_inverse.invert( 0.001f );

	hkMatrix3 should_be_identity;
	should_be_identity.setMul( rand_mat3, rand_inverse );
	HK_TEST( should_be_identity.isApproximatelyEqual( the_identity ) );

	hkRotation rand_rot;
	hkVector4 rows[3];
	rand_mat3.getRows( rows[0], rows[1], rows[2] );
	rand_rot.setRows( rows[0], rows[1], rows[2] );
	should_be_identity.setMulInverse( rand_mat3, rand_rot );
	HK_TEST( should_be_identity.isApproximatelyEqual( the_identity ) );

	rand_mat3.mul( rand_inverse );
	HK_TEST( rand_mat3.isApproximatelyEqual( the_identity ) );
}

static void mul()
{
	// make up a result matrix
	hkMatrix3 the_result;
	hkVector4 c0; c0.set(2.25f, 2.25f, 2.25f); 
	hkVector4 c1; c1.set(2.625f, 2.625f, 2.625f); 
	hkVector4 c2; c2.set(2.85f, 2.85f, 2.85f);
	the_result.setCols(c0, c1, c2);

	// make up a test matrix for ::mul
	hkMatrix3 test_matrix;
	hkVector4 cc0; cc0.set(1.5f, 1.5f, 1.5f);
	hkVector4 cc1; cc1.set(1.75f, 1.75f, 1.75f);
	hkVector4 cc2; cc2.set(1.9f, 1.9f, 1.9f);
	test_matrix.setCols(cc0, cc1, cc2);

	test_matrix.mul(1.5f);
	HK_TEST( test_matrix.isApproximatelyEqual(the_result, 0.0f));
}

static void set_mul()
{
	// make up a result matrix
	hkMatrix3 the_result;
	hkVector4 c0; c0.set(2.25f, 2.25f, 2.25f); 
	hkVector4 c1; c1.set(2.625f, 2.625f, 2.625f); 
	hkVector4 c2; c2.set(2.85f, 2.85f, 2.85f);
	the_result.setCols(c0, c1, c2);
	
	// make up a test matrix for ::setmul
	hkMatrix3 the_source;
	hkVector4 cc0; cc0.set(1.5f, 1.5f, 1.5f);
	hkVector4 cc1; cc1.set(1.75f, 1.75f, 1.75f);
	hkVector4 cc2; cc2.set(1.9f, 1.9f, 1.9f);
	the_source.setCols(cc0, cc1, cc2);
	
	hkMatrix3 test_matrix;
	test_matrix.setMul( 1.5f, the_source );
	
	HK_TEST( test_matrix.isApproximatelyEqual(the_result, 0.0f));
}

int matrix3_main()
{
	mul_inverse_equals();
	mul();
	set_mul();
	return 0;
}

//void ___1() { }
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(matrix3_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
