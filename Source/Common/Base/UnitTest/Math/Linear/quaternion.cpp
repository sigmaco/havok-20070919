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

#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

static void testDifference(hkQuaternion &a, hkQuaternion &b, hkReal eps)
{
		// We don't just check whether they are componentwise equal, we also check whether a = -b,
		// since (as rotations), the quaternions are also "the same".
	hkVector4 va = a.m_vec;
	hkVector4 vb = b.m_vec;

	hkReal r = va.dot4(vb);

	hkBool is1 = (hkMath::fabs(1.0f - r ) < eps);
	hkBool isMinus1 = (hkMath::fabs(-1.0f - r ) < eps);
	HK_TEST ( is1 || isMinus1);

}

static void checkMisc()
{
	hkVector4 axis; axis.set(-3,1,-0.5f);
	axis.normalize3();
	hkQuaternion q0(axis, -1.3f);
	hkVector4 x = q0.m_vec;
	hkQuaternion q1(x(0), x(1), x(2), x(3));
	HK_TEST( q0.m_vec.equals4(q1.m_vec) );

	hkQuaternion id0;
	id0.setIdentity();
	HK_TEST( id0.m_vec.equals4( hkQuaternion::getIdentity().m_vec ) );
}

static void checkMulMulInv()
{
	hkVector4 axis0; axis0.set(1,2,3);
	hkVector4 axis1; axis1.set(-3,1,-0.5f);

	axis0.normalize3();
	axis1.normalize3();

	hkQuaternion q0(axis0, 0.7f);
	hkQuaternion q1(axis1, -1.3f);

	hkQuaternion q0q1InvTest;
	q0q1InvTest.setMulInverse(q0, q1);

	hkQuaternion q0q1Inv;
	hkQuaternion q1Inv;
	q1Inv.setInverse(q1);
	q0q1Inv.setMul(q0, q1Inv);

	testDifference(q0q1InvTest, q0q1Inv, 1e-3f);
}

static void checkMul()
{
	hkVector4 axis0; axis0.set(1,2,3);
	hkVector4 axis1; axis1.set(-3,1,-0.5f);

	axis0.normalize3();
	axis1.normalize3();

	hkQuaternion q0(axis0, 0.7f);
	hkQuaternion q1(axis1, -1.3f);

	hkQuaternion q0q1;
	{

		// The naive way:
		// pq.m_real = p.m_real*q.m_real - p.m_imag.Dot(q.m_imag)
		// pq.m_imag = p.m_real*q.m_imag + q.m_real*p.m_imag + p.m_imag.Cross(q.m_imag)
		// uses  16 multiplications and 12 adds


		// A better way uses only 9 mults but 27 adds.
		// This way is implemented below:


		const hkReal temp_1 = (q0.getImag()(2)-q0.getImag()(1))	*	(q1.getImag()(1)-q1.getImag()(2));
		const hkReal temp_2 = (q0.getReal()+q0.getImag()(0))		*	(q1.getReal()+q1.getImag()(0));
		const hkReal temp_3 = (q0.getReal()-q0.getImag()(0))		*	(q1.getImag()(1)+q1.getImag()(2));
		const hkReal temp_4 = (q0.getImag()(2)+q0.getImag()(1))	*	(q1.getReal()-q1.getImag()(0));
		const hkReal temp_5 = (q0.getImag()(2)-q0.getImag()(0))	*	(q1.getImag()(0)-q1.getImag()(1));
		const hkReal temp_6 = (q0.getImag()(2)+q0.getImag()(0))	*	(q1.getImag()(0)+q1.getImag()(1));
		const hkReal temp_7 = (q0.getReal()+q0.getImag()(1))		*	(q1.getReal()-q1.getImag()(2));
		const hkReal temp_8 = (q0.getReal()-q0.getImag()(1))		*	(q1.getReal()+q1.getImag()(2));

		const hkReal temp_9 = temp_6 + temp_7 + temp_8;
		const hkReal temp_10 = (temp_5 + temp_9)*0.5f;

		hkQuadRealUnion v;
		v.r[0] = temp_2+temp_10-temp_9;
		v.r[1] = temp_3+temp_10-temp_8;
		v.r[2] = temp_4+temp_10-temp_7;
		v.r[3] = temp_1+temp_10-temp_6;
		q0q1.m_vec = v.q;
	}


	hkQuaternion q0q1Test;
	q0q1Test.setMul(q0, q1);

	testDifference(q0q1Test, q0q1, 1e-3f);
}


static void checkGetAxisStability(const hkVector4& axis, const hkReal angle)
{

//	if(angle >= 1e-6f)
	{
		hkQuaternion q(axis, angle); 

	//	hkVector4 a = q.m_vec;
	//	a.normalize3();

		hkVector4 axisTest;
		q.getAxis(axisTest); 

			// First check axis is normalized
		HK_TEST(axisTest.dot3(axis) > 1 - 1e-3f);

			// Then check it is "equal" to the original
		HK_TEST( hkMath::fabs(axisTest(0) - axis(0)) < 1e-3f);
		HK_TEST( hkMath::fabs(axisTest(1) - axis(1)) < 1e-3f);
		HK_TEST( hkMath::fabs(axisTest(2) - axis(2)) < 1e-3f);
	}
}

	// See Mantis 746
	// http://havok2bugs.telekinesys/view_bug_page.php?f_id=0000746
static void checkAngleAxis()
{
    {
    hkVector4 axis; axis.set(1,-2,3);
    axis.normalize3();

		// Test with small (+ve) angle. We expect to get the same angle/axis pair back.
	{
		hkReal angle = 0.7f;
		hkQuaternion q0(axis, angle);

		hkReal angleTest = q0.getAngle();

		hkVector4 axisTest;
		q0.getAxis(axisTest);


		HK_TEST( hkMath::fabs(angle - angleTest) < 1e-3f);
		HK_TEST( hkMath::fabs(axisTest(0) - axis(0)) < 1e-3f);
		HK_TEST( hkMath::fabs(axisTest(1) - axis(1)) < 1e-3f);
		HK_TEST( hkMath::fabs(axisTest(2) - axis(2)) < 1e-3f);
	}

		// Test with large (-ve) angle. We expect to get the negative angle/axis pair back.
		// Angle will always be in range 0-PI. If we pass in angle > PI, then angle will be returned as (-angle), ie. 2PI-angle
		// and axis will be flipped.
		// eg. Rot(1.5 PI, (1,0,0)) will return:
		// 0.5 PI as angle
		// (-1,0,0) as axis.		
	{
		hkReal angle = 3.7f;
		hkQuaternion q0(axis, angle);

		hkReal angleTest = q0.getAngle();

		hkVector4 axisTest;
		q0.getAxis(axisTest);

		angle = 2 * HK_REAL_PI - angle;
		axis.setNeg4(axis);


		HK_TEST( hkMath::fabs(angle - angleTest) < 1e-3f);
		HK_TEST( hkMath::fabs(axisTest(0) - axis(0)) < 1e-3f);
		HK_TEST( hkMath::fabs(axisTest(1) - axis(1)) < 1e-3f);
		HK_TEST( hkMath::fabs(axisTest(2) - axis(2)) < 1e-3f);
	}
	}


	// Check with very small angle: getAxis() should avoid numerically unstable calculations
	{
			// This is a "known" breaking cases for the previous algorithm:
			// Basically since a quaternion stores 
			// (Cos(theta/2), Sin(theta/2) * axis) 
			// the computation used to be: 
			// 1. getSinAngleOver2 as sqrt(1-CosAngleOver2) 
			// 2. Divide to get axis 
			// but when theta ~ 0, we're dividing numbers close to 0, and one of these is computed 
			// as sqrt(1-csqrd), hence already has error, so we get inaccurate results.
			// The new algorithm is to take the Sin(theta/2) * axis part and just normalize it,
		{
			hkVector4 axis; axis.set(1,0,0); 
			hkReal angle = 5e-4f; 

			checkGetAxisStability(axis, angle);

		}
		// Worst angle would be where sin(theta/2) ~ HK_REAL_EPSILON because we'd try and normalize
		// a vector of length ~ HK_REAL_EPSILON in that case. Such an angle would be:
		HK_ON_DEBUG( const hkReal worstAngle = hkMath::asin(HK_REAL_EPSILON) * 1.999f );
			// Comment in the next line to confirm an ASSERT will occur in DEBUG.
		//checkGetAxisStability(axis, worstAngle);

		// Check 100000 "random" (axis, angle) pairs, each angle chosen to be in range 1e-2 to 1e-6, by
		// fist picking "exponent" in range 2 to 6, then picking "mantissa"
		{
			hkPseudoRandomGenerator psrng(23527);

					// Get "exponent" in range 2-6
		
			for(int i = 0; i < 100000; i++)
			{

				hkUint32 exponent =  2 + psrng.getRandChar(5);
				hkReal scale = 1.0f;
				while(exponent--)
				{
					scale *= 0.1f;
				}
			

				hkReal angle = psrng.getRandReal01() * scale;
				while(angle < scale)
				{
					angle *= 10.0f;
				}

					// Sanity check
				HK_ASSERT(0x68500ee6, angle > worstAngle);

				hkVector4 axis; axis.set(psrng.getRandReal11(), psrng.getRandReal11(), psrng.getRandReal11());
				axis.normalize3();
	
				checkGetAxisStability(axis, angle);
			}
		}
	}

}

void checkShortestRotation()
{
	hkPseudoRandomGenerator psrng(23527);

	int i;
	for (i=0 ; i < 100; i++)
	{
		hkVector4 from, to;
		psrng.getRandomVector11( from );
		from.normalize3();
		psrng.getRandomVector11( to );
		to.normalize3();

		hkQuaternion q;
		q.setShortestRotation( from, to );

		hkVector4 result;
		result.setRotatedDir( q, from );

		HK_TEST( result.equals3( to ) );
	}

	// Test boundaries : to = from
	{
		hkVector4 from, to;
		psrng.getRandomVector11( from );
		from.normalize3();
		to = from;

		hkQuaternion q;
		q.setShortestRotation( from, to );

		hkVector4 result;
		result.setRotatedDir( q, from );

		HK_TEST( result.equals3( to ) );
	}

	// Test boundaries : to = -from
	{
		hkVector4 from, to;
		psrng.getRandomVector11( from );
		from.normalize3();
		to.setNeg4( from ) ;

		hkQuaternion q;
		q.setShortestRotation( from, to );

		hkVector4 result;
		result.setRotatedDir( q, from );

		HK_TEST( result.equals3( to ) );
	}

	// Try damped versions
	for (i=0 ; i < 100; i++)
	{
		hkVector4 from, to;
		psrng.getRandomVector11( from );
		from.normalize3();
		psrng.getRandomVector11( to );
		to.normalize3();

		hkVector4 result;
		hkQuaternion q;
		q.setShortestRotationDamped(1.0f, from, to );
		result.setRotatedDir( q, from );
		HK_TEST( result.equals3( to ) );

		q.setShortestRotationDamped(0.0f, from, to );
		result.setRotatedDir( q, from );
		HK_TEST( result.equals3( from ) );
	}
}

static void checkNormalize()
{
	if(0)
	for( int i = 0; i < 100; ++i)
	{
		hkRotation r;
		{
			// get 3 perp vectors
			hkVector4 a; a.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
			a.normalize3();
			hkVector4 b; b.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
			hkVector4 c; c.setCross(a,b);
			c.normalize3();
			b.setCross(c,a);
			b.normalize3();
			// add some error
			b.addMul4( i/10000.0f, c);
			b.addMul4( i/10000.0f, a);
			a.addMul4( i/10000.0f, b);
			r.setCols(a,b,c);

			HK_TEST2( r.isOrthonormal(1e-3f), "failed at" << i );
		}
		hkQuaternion q;
		q.set(r); // will assert if not orthonormal
	}
}
static int quaternion_main()
{
	checkMisc();
	checkMul();
	checkMulMulInv();
	checkAngleAxis();
	checkShortestRotation();
	checkNormalize();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(quaternion_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
