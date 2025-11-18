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
#include <Common/Base/Math/Linear/hkMathStream.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

//#define DOUT(A) hkcout << #A " = " << A << '\n'
#define DOUT(A) hkprintf(#A " = %i\n", A)
//#define DOUT(A) 

int vector3util_main()
{
	// test hkVector4Util::dot4_4vs4 and dot3_4vs4
	{
		hkPseudoRandomGenerator random(1337);
		hkVector4 a1; a1.set(random.getRandReal11(), random.getRandReal11(), random.getRandReal11(), random.getRandReal11());
		hkVector4 a2; a2.set(random.getRandReal11(), random.getRandReal11(), random.getRandReal11(), random.getRandReal11());
		hkVector4 a3; a3.set(random.getRandReal11(), random.getRandReal11(), random.getRandReal11(), random.getRandReal11());
		hkVector4 a4; a4.set(random.getRandReal11(), random.getRandReal11(), random.getRandReal11(), random.getRandReal11());

		hkVector4 b1; b1.set(random.getRandReal11(), random.getRandReal11(), random.getRandReal11(), random.getRandReal11());
		hkVector4 b2; b2.set(random.getRandReal11(), random.getRandReal11(), random.getRandReal11(), random.getRandReal11());
		hkVector4 b3; b3.set(random.getRandReal11(), random.getRandReal11(), random.getRandReal11(), random.getRandReal11());
		hkVector4 b4; b4.set(random.getRandReal11(), random.getRandReal11(), random.getRandReal11(), random.getRandReal11());

		hkVector4 dots3, dots4;
		hkVector4Util::dot4_4vs4(a1, b1, a2, b2, a3, b3, a4, b4, dots4);
		hkVector4Util::dot3_4vs4(a1, b1, a2, b2, a3, b3, a4, b4, dots3);

		HK_TEST( hkMath::equal(dots4(0), a1.dot4(b1)));
		HK_TEST( hkMath::equal(dots4(1), a2.dot4(b2)));
		HK_TEST( hkMath::equal(dots4(2), a3.dot4(b3)));
		HK_TEST( hkMath::equal(dots4(3), a4.dot4(b4)));

		HK_TEST( hkMath::equal(dots3(0), a1.dot3(b1)));
		HK_TEST( hkMath::equal(dots3(1), a2.dot3(b2)));
		HK_TEST( hkMath::equal(dots3(2), a3.dot3(b3)));
		HK_TEST( hkMath::equal(dots3(3), a4.dot3(b4)));

	}

	{
		{
			hkVector4 a; a.set( -5, -4, 2.3f, 100);
			hkVector4 b; b.set( -5, +.01f, -99.3f, 9);
			hkVector4 ab = a;
			hkVector4Util::mulSigns4(ab, b);
			//DOUT(a); DOUT(b); DOUT(ab);
			//DOUT(x); DOUT(b); DOUT(ab);
			HK_TEST(ab(0) > 0);
			HK_TEST(ab(1) < 0);
			HK_TEST(ab(2) < 0);
			HK_TEST(ab(3) > 0);
		}

		// zero offset, unit scale
		{
			hkVector4 offset;
			offset.setZero4();
			hkVector4 scale; scale.set(1,1,1,1);

			hkVector4 a; a.set( 0.99f, 110.49f, 100.89f, 65535.9f);
			hkIntUnion64 out;
			hkVector4Util::convertToUint16(a, offset, scale, out );

			//DOUT(out.u16[0]); DOUT(out.u16[1]); DOUT(out.u16[2]); DOUT(out.u16[3]);
			HK_TEST(out.u16[0] == 0);
			HK_TEST(out.u16[1] == 110);
			HK_TEST(out.u16[2] == 100);
			HK_TEST(out.u16[3] == 65535);
		}

		// nonzero offset, unit scale
		{
			hkVector4 offset; offset.set(-1005, -99, 9901, 32000);
			hkVector4 scale; scale.set(1,1,1,1);

			hkVector4 a; a.set( 1005, 199, 10000, 32000);
			hkIntUnion64 out;
			hkVector4Util::convertToUint16( a, offset, scale, out );

			//DOUT(out.u16[0]); DOUT(out.u16[1]); DOUT(out.u16[2]); DOUT(out.u16[3]);
			HK_TEST(out.u16[0] == 0);
			HK_TEST(out.u16[1] == 100);
			HK_TEST(out.u16[2] == 19901);
			HK_TEST(out.u16[3] == 64000);
		}

		// nonzero offset, nonunit scale
		{
			hkVector4 offset; offset.set(-2000, -10,  199, 32000);
			hkVector4 scale; scale.set(100.0f,    0.1000001f, -200.0f,  1.0f);

			hkVector4 a; a.set( 2000, 110, -399, 32000);
			hkIntUnion64 out;
			hkVector4Util::convertToUint16( a, offset, scale, out );

			//DOUT(out.u16[0]); DOUT(out.u16[1]); DOUT(out.u16[2]); DOUT(out.u16[3]);
			HK_TEST(out.u16[0] == 0);
			HK_TEST(out.u16[1] == 10);
			HK_TEST(out.u16[2] == 40000);
			HK_TEST(out.u16[3] == 64000);
		}
		
		// bad values
		{
			hkVector4 offset;
			offset.setZero4();
			hkVector4 scale; scale.set(1,1,1,1);

			hkVector4 a; a.set( -100.0f, -.01f, 65536.0f, 70000.0f);
			hkIntUnion64 out;
			hkVector4Util::convertToUint16(  a, offset, scale, out );

			//DOUT(out.u16[0]); DOUT(out.u16[1]); DOUT(out.u16[2]); DOUT(out.u16[3]);
			//HK_TEST(out.u16[0] == 0); TEST(out.u16[1] == 110); TEST(out.u16[2] == 100); TEST(out.u16[3] == 65535);
		}

		// bad values - clip them
		{
			hkVector4 min; min.set(0,0,0,0);
			hkVector4 max; max.set(65535,65535,65535,65535);

			hkVector4 offset;
			offset.setZero4();
			hkVector4 scale; scale.set(1,1,1,1);

			hkVector4 a; a.set( -100.0f, -0.10001f, 65536.0f, 70000.0f);
			hkIntUnion64 out;
			hkVector4Util::convertToUint16WithClip( a, offset, scale, min, max, out );

			//DOUT(out.u16[0]); DOUT(out.u16[1]); DOUT(out.u16[2]); DOUT(out.u16[3]);
			HK_TEST(out.u16[0] == 0);
			HK_TEST(out.u16[1] == 0);
			HK_TEST(out.u16[2] == 65535);
			HK_TEST(out.u16[3] == 65535);
		}

		// transform points
		{
			hkPseudoRandomGenerator random(1);
			for ( int i= 0; i < 100; i++ )
			{
				hkVector4 in;
				random.getRandomVector11( in );
				
				hkTransform t;
				hkRotation& r = t.getRotation();
				random.getRandomRotation( r );
				random.getRandomVector11( t.getTranslation() );

					// do it by hand
				hkVector4 ref3;	// rotation mult
				hkVector4 ref4;	// transform mult
				{
					hkReal v0 = in(0);
					hkReal v1 = in(1);
					hkReal v2 = in(2);
					//hkReal v3 = in(2);

					{
						hkVector4& d = ref3;
						d(0) = t(0,0)*v0 + t(0,1)*v1 + t(0,2)*v2;
						d(1) = t(1,0)*v0 + t(1,1)*v1 + t(1,2)*v2;
						d(2) = t(2,0)*v0 + t(2,1)*v1 + t(2,2)*v2;
						d(3) = t(3,0)*v0 + t(3,1)*v1 + t(3,2)*v2;
					}
					{
						hkVector4& d = ref4;
						d(0) = t(0,0)*v0 + t(0,1)*v1 + t(0,2)*v2 + t(0,3);
						d(1) = t(1,0)*v0 + t(1,1)*v1 + t(1,2)*v2 + t(1,3);
						d(2) = t(2,0)*v0 + t(2,1)*v1 + t(2,2)*v2 + t(2,3);
						d(3) = t(3,0)*v0 + t(3,1)*v1 + t(3,2)*v2 + t(3,3);
					}
				}

				// normal operation
				{
					hkVector4 test3; test3.setRotatedDir( r, in );
					hkVector4 test4; test4.setTransformedPos( t, in );
					HK_TEST( test3.equals3( ref3 ) );
					HK_TEST( test4.equals3( ref4 ) );

					hkVector4 o3; o3.setRotatedInverseDir( r, test3 );
					hkVector4 o4; o4.setTransformedInversePos( t, test4 );
					HK_TEST( o3.equals3( in ) );
					HK_TEST( o4.equals3( in ) );
				}

				// normal inline operation
				{
					hkVector4 test3; test3._setRotatedDir( r, in );
					hkVector4 test4; test4._setTransformedPos( t, in );
					HK_TEST( test3.equals3( ref3 ) );
					HK_TEST( test4.equals3( ref4 ) );

					hkVector4 o3; o3._setRotatedInverseDir( r, test3 );
					hkVector4 o4; o4._setTransformedInversePos( t, test4 );
					HK_TEST( o3.equals3( in ) );
					HK_TEST( o4.equals3( in ) );
				}

				// 
				{
					hkVector4 test3; test3._setMul4( r, in );
					hkVector4 test4; test4._setMul4xyz1( t, in );
					HK_TEST( test3.equals4( ref3 ) );
					HK_TEST( test4.equals4( ref4 ) );
				}

				// 
				{
					hkVector4 test3; test3._setMul3( r, in );
					HK_TEST( test3.equals3( ref3 ) );
				}


				// normal operation
				{
					hkVector4 test3; hkVector4Util::rotatePoints( r, &in, 1, &test3 );
					hkVector4 test4; hkVector4Util::transformPoints( t, &in, 1, &test4 );
					HK_TEST( test3.equals3( ref3 ) );
					HK_TEST( test4.equals3( ref4 ) );

					hkVector4 o3; hkVector4Util::rotateInversePoints( r, &test3, 1, &o3 );
					HK_TEST( o3.equals3( in ) );
				}

				// normal operation
				{
					hkVector4 test3; hkVector4Util::mul4xyz1Points(   t, &in, 1, &test3 );
					hkVector4 test4; hkVector4Util::transformSpheres( t, &in, 1, &test4 );
					HK_TEST( test3.equals4( ref4 ) );
					HK_TEST( test4.equals3( ref4 ) );
					HK_TEST( hkMath::equal( in(3), test4(3) ) );
				}

				// matrix operation
				{
					hkMatrix3 id; id.setMulInverse( r, r );
					HK_TEST( id.isApproximatelyEqual( hkTransform::getIdentity().getRotation() ) );
				}

				// matrix operation
				{
					hkRotation rr; rr.setMul( r, r );
					hkRotation r3; r3.setMul( r, rr );
					hkRotation rd; rd.setMulInverse( r3, rr );
					HK_TEST( r.isApproximatelyEqual( rd ) );
				}
			}
		}
	}
	{
		// test pack/unpack for quaternion
		hkPseudoRandomGenerator random(1);
		for (int i=0; i<1000; i++)
		{
			hkQuaternion q; 
			random.getRandomRotation( q );
			hkUint32 i32 = hkVector4Util::packQuaternionIntoInt32( q.m_vec );

			hkQuaternion ref; hkVector4Util::unPackInt32IntoQuaternion(i32, ref.m_vec);
			HK_TEST( ref.m_vec.equals4(q.m_vec, 0.01f));
		}
	}


	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(vector3util_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );

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
