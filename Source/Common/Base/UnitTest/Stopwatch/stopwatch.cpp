/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/System/Stopwatch/hkStopwatch.h>

//#include <math.h>

static unsigned fib(unsigned n)
{
	if (n==0)
		return 1;

	if (n==1)
		return 1;

	return fib(n-1) + fib(n-2);
}

void stopwatch_test()
{
	{
		// Single stopwatch accuracy
		if(0)
				// disabled - breaks too easily
		{
			const int testIterations = 10;
			const int computeIters = 10;	// Don't go much higher!

			for (int iters = 0; iters < testIterations; iters++)
			{
				hkStopwatch sw;
				volatile int x;
				int i;

				x = fib(10); // fill $I cache

				sw.start();
				for(i = 0; i < computeIters; ++i) 
				{
					x = fib(i) + x; // assume running time is reasonably constant.
				}
				sw.stop();
				hkReal time0 = sw.getElapsedSeconds();

				sw.reset();
				sw.start();
				for (int j=0; j < 10; j++)
				{
					for(i = 0; i < computeIters ; ++i)
					{
						x = fib(i) + x;
					}
				}

				sw.stop();
				hkReal time1 = sw.getElapsedSeconds();

				hkReal ratio = time1/time0;

				HK_TEST2( ratio >= 9 && ratio <= 11, "times were " << time0 << ' ' << time1 << " ratio " << ratio );
			}
		}
		// Multiple stopwatch accuracy
		{
			const int testIterations = 10;
			const int computeIters = 100;
			hkReal ratio = 100;

			for (int iters = 0; iters < testIterations; iters++)
			{
				hkStopwatch sw1;
				hkStopwatch sw2;
				volatile unsigned x;
				int i;

				x = fib(10); // fill $I cache

				sw1.start();
				for(i = 0; i < computeIters; ++i) 
				{
					x = fib(i) + x; // assume running time is reasonably constant.				
				}
				sw1.stop();
				hkReal time0 = sw1.getElapsedSeconds();

				sw2.start();
				for (int j=0; j < 10; j++)
				{
					for(i = 0; i < computeIters ; ++i)
					{
						x = fib(i) + x;
					}
				}
				sw2.stop();
				hkReal time1 = sw2.getElapsedSeconds();

				hkReal thisRatio = time1/time0;
				if(thisRatio < ratio)
				{
					ratio = thisRatio;
				}
			}
			//HK_TEST2( ratio >= 9.9 && ratio <= 10.1, " ratio " << ratio );
		}
	}
}

int stopwatch_main()
{
	

	stopwatch_test();
	
		
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(stopwatch_main,     "Broken", "Test/Test/UnitTest/UnitTest/UnitTest/Base/",     __FILE__    );



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
