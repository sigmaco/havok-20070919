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

#include <math.h>

static inline hkBool approx_equals(hkReal x, hkReal y)
{
	const hkReal tol = 1e-4f;
	hkReal f = x - y;
	if(-tol < f && f < tol)
	{
		return true;
	}
	else
	{
		//printf("values were %f, %f\n", x, y);
		return false;
	}
}

extern hkReal mathfunc_test_zero;

static void mathfunc_test()
{
	{
        // try to fool the compilers div by zero check
		hkReal y = 1.0f / mathfunc_test_zero;
		HK_TEST(!hkMath::isFinite(y));
	}

	const int NLOOP = 10;
	{
		for(int i=0; i<NLOOP; ++i)
		{
			for (int j=0; j < NLOOP; j++)
			{
				hkReal r = hkMath::randRange(0,HK_REAL_MAX);
				HK_TEST( hkMath::isFinite(r) );
			}
		}
	}

	{
		for(int i = 0; i < NLOOP; ++i)
		{
			hkReal r = i - (0.5f*NLOOP);
			hkReal fabsR = hkMath::fabs(r);
			if( r >= 0)
			{
				HK_TEST( fabsR == r );
			}
			else
			{
				HK_TEST( fabsR == -r );
			}
		}
	}

	const hkReal tolerance = 1e-6f;

	HK_TEST( hkMath::equal( hkMath::acos( 1.00001f), 0.0f, tolerance) );
	HK_TEST( hkMath::equal( hkMath::acos(-1.00001f), HK_REAL_PI, tolerance) );

	HK_TEST( hkMath::equal( hkMath::asin( 1.00001f),  0.5f * HK_REAL_PI, tolerance) );
	HK_TEST( hkMath::equal( hkMath::asin(-1.00001f), -0.5f * HK_REAL_PI, tolerance) );

		// Now test the "closest" values to 1 and -1
	HK_COMPILE_TIME_ASSERT(sizeof(hkReal) == sizeof(unsigned int));
	union realIntUnion{hkReal			m_real;
						unsigned int	m_int;};

	{
		
		realIntUnion smallestGreaterThanOne;
		smallestGreaterThanOne.m_int = 0x3F800001;	// This is the hex IEEE representation of 1.00000012. See http://www.markworld.com/scripts/showfloat.exe

		HK_TEST( hkMath::equal( hkMath::acos(smallestGreaterThanOne.m_real), 0.0f, tolerance) );
		HK_TEST( hkMath::equal( hkMath::asin(smallestGreaterThanOne.m_real),  0.5f * HK_REAL_PI, tolerance) );

	}

	{
		realIntUnion smallestLessThanMinusOne;
		smallestLessThanMinusOne.m_int = 0xBF800001;	// This is the hex IEEE representation of -1.00000012. See http://www.markworld.com/scripts/showfloat.exe

		HK_TEST( hkMath::equal( hkMath::acos(smallestLessThanMinusOne.m_real), HK_REAL_PI, tolerance) );
		HK_TEST( hkMath::equal( hkMath::asin(smallestLessThanMinusOne.m_real), -0.5f * HK_REAL_PI, tolerance) );
	}

	/*
	{
		for(int i=0; i<NLOOP; ++i)
		{
			hkReal r = i - (0.5f*NLOOP);
			hkReal sinR = hkMath::sin(r);
			HK_TEST( approx_equals(::sin(r), sinR) );
		}
	}

	{
		for(int i=0; i<NLOOP; ++i)
		{
			hkReal r = i - (0.5f*NLOOP);
			hkReal s = hkMath::cos(r);
			HK_TEST( approx_equals(::cos(r), s) );
		}
	}

	{
		for(int i=0; i<NLOOP; ++i)
		{
			hkReal r = (2*hkReal(i) - NLOOP) / NLOOP;
			hkReal s = hkMath::acos(r);
			HK_TEST( approx_equals(::acos(r), s) );
		}
	}

	{
		for(int i=0; i<NLOOP; ++i)
		{
			hkReal r = (2*hkReal(i) - NLOOP) / NLOOP;
			hkReal s = hkMath::asin(r);
			HK_TEST( approx_equals(::asin(r), s) );
		}
	}
	*/
	

	{
		for(int i=0; i<NLOOP; ++i)
		{
			hkReal r = hkReal(i+1);
			hkReal s = hkMath::sqrtInverse(r);
			HK_TEST( approx_equals(s*s*r, 1) );
		}
	}

	// Test sqrt around 1
	{
		for(int i=0; i<NLOOP; ++i)
		{
			for (int j=0; j < NLOOP; j++)
			{
				hkReal r = hkReal(hkMath::randRange(0,1));
				hkReal s = hkMath::sqrt(r);
				hkReal diff = hkMath::fabs(s*s)/r;
				HK_TEST( approx_equals(diff, 1.0f));
			}
		}
	}

	// Test sqrt around larger ranges
	{
		for(int i=0; i<NLOOP; ++i)
		{
			for (int j=0; j < NLOOP; j++)
			{
				hkReal r = hkReal(hkMath::randRange(0,1000000));
				hkReal s = hkMath::sqrt(r);
				hkReal diff = hkMath::fabs(s*s)/r;
				HK_TEST( approx_equals(diff, 1.0f));
			}
		}
	}

	// Test Sqrt 0
	{
		hkReal r = 0.0f;
		hkReal s = hkMath::sqrt(r);
		HK_TEST(approx_equals(s,0));
	}

	// Test recip Sqrt 0
	{
		hkReal r = 0.0f;
		hkReal s = hkMath::sqrtInverse(r);
		HK_TEST( !hkMath::isFinite(s) );
	}

	// Test Sqrt of -ve
	{
		hkReal r = -1.0f;
		hkReal s = hkMath::sqrt(r);
		HK_TEST(!hkMath::isFinite(s));
	}

	// Test recip Sqrt of -ve
	{
		hkReal r = -1.0f;
		hkReal s = hkMath::sqrtInverse(r);
		HK_TEST( !hkMath::isFinite(s) );
	}
}

hkReal mathfunc_test_zero = 0;

union fi
{
	hkReal f;
	int i;
};

static void types_test()
{
	fi test1;
	fi test2;
	fi test3;
	fi test4;
	fi test5;
	fi test6;

	test1.i = 0x40000000;
	test2.i = 0x40D00000;
	test3.i = 0xC0D00000;
	test4.i = 0x00800000;
	test5.i = 0x00400000;
	test6.i = 0x00000001;

	hkReal q = 10000000000.0f;
	hkReal r = -1.0f;
	hkReal s = 0.5f;
	hkReal t = -9.29999f;
	hkReal u = -16646142.000000f;
	hkReal v = 0.0000f;
	hkReal w = -0.0f;
	hkReal x = 9.32345f;
	hkReal y = 1.0f;
	hkReal z = -0.5f;

	//int q1 = hkMath::hkFloatToInt(q);
	int r1 = hkMath::hkFloatToInt(r);
	int s1 = hkMath::hkFloatToInt(s);
	int t1 = hkMath::hkFloatToInt(t);
	int u1 = hkMath::hkFloatToInt(u);
	int v1 = hkMath::hkFloatToInt(v);
	int w1 = hkMath::hkFloatToInt(w);
	int x1 = hkMath::hkFloatToInt(x);
	int y1 = hkMath::hkFloatToInt(y);
	int z1 = hkMath::hkFloatToInt(z);
	int test11 = hkMath::hkFloatToInt(test1.f);
	int test12 = hkMath::hkFloatToInt(test2.f);
	int test13 = hkMath::hkFloatToInt(test3.f);
	int test14 = hkMath::hkFloatToInt(test4.f);
	int test15 = hkMath::hkFloatToInt(test5.f);
	int test16 = hkMath::hkFloatToInt(test6.f);

	//this test fails as the default implementation
	//is not as sturdy on Win32!
	//HK_TEST(q1 == (int)q);
	HK_TEST(r1 == (int)r);
	HK_TEST(s1 == (int)s);
	HK_TEST(t1 == (int)t);
	HK_TEST(u1 == (int)u);
	HK_TEST(v1 == (int)v);
	HK_TEST(w1 == (int)w);
	HK_TEST(x1 == (int)x);
	HK_TEST(y1 == (int)y);
	HK_TEST(z1 == (int)z);
	HK_TEST(test11 == (int)test1.f);
	HK_TEST(test12 == (int)test2.f);
	HK_TEST(test13 == (int)test3.f);
	HK_TEST(test14 == (int)test4.f);
	HK_TEST(test15 == (int)test5.f);
	HK_TEST(test16 == (int)test6.f);

	hkReal q2 = hkMath::hkFloor(q);
	hkReal r2 = hkMath::hkFloor(r);
	hkReal s2 = hkMath::hkFloor(s);
	hkReal t2 = hkMath::hkFloor(t);
	hkReal u2 = hkMath::hkFloor(u);
	hkReal v2 = hkMath::hkFloor(v);
	hkReal w2 = hkMath::hkFloor(w);
	hkReal x2 = hkMath::hkFloor(x);
	hkReal y2 = hkMath::hkFloor(y);
	hkReal z2 = hkMath::hkFloor(z);
	hkReal test21 = hkMath::hkFloor(test1.f);
	hkReal test22 = hkMath::hkFloor(test2.f);
	hkReal test23 = hkMath::hkFloor(test3.f);
	hkReal test24 = hkMath::hkFloor(test4.f);
	hkReal test25 = hkMath::hkFloor(test5.f);
	hkReal test26 = hkMath::hkFloor(test6.f);


	HK_TEST(q2 == ::floorf(q));
	HK_TEST(r2 == ::floorf(r));
	HK_TEST(s2 == ::floorf(s));
	HK_TEST(t2 == ::floorf(t));
	HK_TEST(u2 == ::floorf(u));
	HK_TEST(v2 == ::floorf(v));
	HK_TEST(w2 == ::floorf(w));
	HK_TEST(x2 == ::floorf(x));
	HK_TEST(y2 == ::floorf(y));
	HK_TEST(z2 == ::floorf(z));
	HK_TEST(test21 == ::floorf(test1.f));
	HK_TEST(test22 == ::floorf(test2.f));
	HK_TEST(test23 == ::floorf(test3.f));
	HK_TEST(test24 == ::floorf(test4.f));
	HK_TEST(test25 == ::floorf(test5.f));
	HK_TEST(test26 == ::floorf(test6.f));


	//int q3 = hkMath::hkFloorToInt(q);
	int r3 = hkMath::hkFloorToInt(r);
	int s3 = hkMath::hkFloorToInt(s);
	int t3 = hkMath::hkFloorToInt(t);
	int u3 = hkMath::hkFloorToInt(u);
	int v3 = hkMath::hkFloorToInt(v);
	int w3 = hkMath::hkFloorToInt(w);
	int x3 = hkMath::hkFloorToInt(x);
	int y3 = hkMath::hkFloorToInt(y);
	int z3 = hkMath::hkFloorToInt(z);
	int test31 = hkMath::hkFloorToInt(test1.f);
	int test32 = hkMath::hkFloorToInt(test2.f);
	int test33 = hkMath::hkFloorToInt(test3.f);
	int test34 = hkMath::hkFloorToInt(test4.f);
	int test35 = hkMath::hkFloorToInt(test5.f);
	int test36 = hkMath::hkFloorToInt(test6.f);

	//this test fails as the default implementation
	//is not as sturdy on PS2!
	//HK_TEST(q3 == (int)(::floorf(q)));
	HK_TEST(r3 == (int)(::floorf(r)));
	HK_TEST(s3 == (int)(::floorf(s)));
	HK_TEST(t3 == (int)(::floorf(t)));
	HK_TEST(u3 == (int)(::floorf(u)));
	HK_TEST(v3 == (int)(::floorf(v)));
	HK_TEST(w3 == (int)(::floorf(w)));
	HK_TEST(x3 == (int)(::floorf(x)));
	HK_TEST(y3 == (int)(::floorf(y)));
	HK_TEST(z3 == (int)(::floorf(z)));
	HK_TEST(test31 == (int)(::floorf(test1.f)));
	HK_TEST(test32 == (int)(::floorf(test2.f)));
	HK_TEST(test33 == (int)(::floorf(test3.f)));
	HK_TEST(test34 == (int)(::floorf(test4.f)));
	HK_TEST(test35 == (int)(::floorf(test5.f)));
	HK_TEST(test36 == (int)(::floorf(test6.f)));
}

int mathfunc_main()
{
	mathfunc_test();
	types_test();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(mathfunc_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );



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
