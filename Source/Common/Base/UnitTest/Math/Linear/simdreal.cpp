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

static void simdreal_test()
{
#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED && !defined(HK_PLATFORM_PSP)
		{ // construct from float
			hkSimdReal s = 62;
			hkQuadRealUnion u;
			u.q = s.getQuad();
			HK_TEST(u.r[0] == 62);
		}

#if !defined(HK_PLATFORM_XBOX360)
		{ // construct from quad and cast to real
			hkQuadRealUnion u;
			u.r[0] = 1.1f;
			u.r[1] = 2.1f;
			u.r[2] = 3.1f;
			u.r[3] = 4.1f;
			hkSimdReal s(u.q);
			HK_TEST( hkReal(s)==1.1f );
		}
#endif

		{ // simple operators
			HK_TEST( hkMath::equal( hkSimdReal(0.5f) + hkSimdReal(1.5f),  2) );
			HK_TEST( hkMath::equal( hkSimdReal(0.5f) - hkSimdReal(1.5f), -1) );
			HK_TEST( hkMath::equal( hkSimdReal(0.5f) * hkSimdReal(1.5f), 0.75f) );
			HK_TEST( hkMath::equal( hkSimdReal(1.5f) / hkSimdReal(0.5f), 3) );
			HK_TEST( hkMath::equal( -hkSimdReal(2.5f), -2.5) );
		}

		{ // real times simdreal
			hkSimdReal r0 = 99.0f;
			hkSimdReal r1 = hkSimdReal(2.0f) * r0;
			HK_TEST( hkReal(r1) == 2*99);
		}


		{
			hkSimdReal sa = 1.0f;
			hkSimdReal sb = 10.0f;
			hkReal fa = 5.0f;
			hkSimdReal sc = sa - sb * hkSimdReal(fa);
			 
			HK_TEST( sc == 1.0f - 10.0f*5.0f );
			hkReal fb = hkReal(sc) * 2.0f;
			HK_TEST( fb == 2.0f*(1.0f - 10.0f*5.0f) );
		}
#endif
}

int simdreal_main()
{
	simdreal_test();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(simdreal_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );

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
