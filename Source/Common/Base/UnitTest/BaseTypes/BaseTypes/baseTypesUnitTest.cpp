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
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>
#include <Common/Base/Types/hkBaseTypes.h>

static void baseTypes_halfTest()
{
	hkPseudoRandomGenerator random(1);
	{
		for (int i =0; i < 1000; i++)
		{
			hkReal x = random.getRandRange( -HK_REAL_MAX*0.5f, HK_REAL_MAX*0.5f );
			hkReal maxError = hkMath::fabs(x * 0.01f);
			hkHalf half = x;
			hkReal uncompressed = half;
			HK_TEST( hkMath::equal(uncompressed, x, maxError));
		}
	}
	{
		for (int i =0; i < 1000; i++)
		{
			hkReal x = random.getRandRange( -100.0f, 100.0f );
			hkReal maxError = hkMath::fabs(x * 0.01f);
			hkHalf half = x;
			hkReal uncompressed = half;
			HK_TEST( hkMath::equal(uncompressed, x, maxError));
		}
	}
	{
		for (int i =0; i < 1000; i++)
		{
			hkReal x = random.getRandRange( -0.001f, 0.001f );
			hkReal maxError = hkMath::fabs(x * 0.01f);
			hkHalf half = x;
			hkReal uncompressed = half;
			HK_TEST( hkMath::equal(uncompressed, x, maxError));
		}
	}
}





static void baseTypes_ufloat8Test()
{
	hkPseudoRandomGenerator random(1);
	{
		for (int i =0; i < 1000; i++)
		{
			hkReal x = random.getRandRange( 0, hkUFloat8_maxValue );
			hkReal maxError = hkMath::max2( hkUFloat8_eps, hkMath::fabs(x * 0.1f) );
			hkUFloat8 half = x;
			hkReal uncompressed = half;
			HK_TEST( hkMath::equal(uncompressed, x, maxError));
		}
	}
	{
		for (int i =0; i < 1000; i++)
		{
			hkReal x = random.getRandRange( 0.0f, 100.0f );
			hkReal maxError = hkMath::max2( hkUFloat8_eps, hkMath::fabs(x * 0.1f) );
			hkUFloat8 half = x;
			hkReal uncompressed = half;
			HK_TEST( hkMath::equal(uncompressed, x, maxError));
		}
	}
	{
		for (int i =0; i < 1000; i++)
		{
			hkReal x = random.getRandRange( 0.0, 0.1f );
			hkReal maxError = hkMath::max2( hkUFloat8_eps, hkMath::fabs(x * 0.1f) );
			hkUFloat8 half = x;
			hkReal uncompressed = half;
			HK_TEST( hkMath::equal(uncompressed, x, maxError));
		}
	}
}

int baseTypes_main()
{
	baseTypes_halfTest();
	baseTypes_ufloat8Test();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(baseTypes_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
