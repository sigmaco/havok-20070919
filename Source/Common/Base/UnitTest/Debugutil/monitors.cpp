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
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>

#ifdef HK_PLATFORM_PS2
# include <libpc.h>
#endif

/*
static void random_function()
{
	HK_TIMER_BEGIN("foo", 0);
	HK_TIMER_BEGIN("foo/bar/baz", 0);
	HK_TIMER_BEGIN("foo/bar", 0);

	HK_TIMER_BEGIN("haha", 0);
	HK_TIMER_END();

	HK_TIMER_END();
	HK_TIMER_END();
	HK_TIMER_END();
}
*/

/*/ Test hkStopwatch
static void stopwatch_test()
{
	hkStopwatch* timer = new hkStopwatch("10 Seconds");

	timer->start();
	hkUint64 ticks;
	do
	{
		ticks = timer->getElapsedTicks();
	}
	while( ticks < (hkStopwatch::getTicksPerSecond()) );
	timer->stop();
		
	timeTaken = (float)timer->getElapsedTicks() / hkStopwatch::getTicksPerSecond();
	hkprintf("Pause time: %f\n", timeTaken);
	timer->reset();

	delete timer;
}
//*/

static void init_quit_test()
{
	//hkBaseSystem::init();
	//random_function();
	//hkBaseSystem::quit();

	//hkBaseSystem::init();
	//random_function();
	//hkBaseSystem::quit();
}

static float time_something()
{
	float timeTaken = 0.0f;

	// use hkStopwatch to cause a known delay of 1 ms
	hkStopwatch* timer = new hkStopwatch("1 ms");

	// time the performance counter directly
	hkUint32 start0 = 0;
	hkUint32 total0 = 0;
	hkMonitorStream::TimerCommand t;
	t.setTime();
	start0 = t.m_time0;

	// time something
	HK_TIMER_BEGIN("1 ms", 0);
	{	
		timer->start();
		hkUint64 ticks;
		do
		{
			ticks = timer->getElapsedTicks();
		}
		while( ticks < (hkStopwatch::getTicksPerSecond() / 1000) );
		timer->stop();
	}
	HK_TIMER_END();

	timeTaken = (float)timer->getElapsedTicks() / hkStopwatch::getTicksPerSecond();

//	hkprintf("Pause time: %f seconds\n", timeTaken);
	timer->reset();

	// time the performance counter directly
	t.setTime();
	total0 = t.m_time0 - start0;
//	hkprintf("Actual Performance Counter Ticks: [%d %d]\n", total0, total1);

	delete timer;

	return timeTaken;
}


static hkMonitorStreamAnalyzer::Node* find_recursive(hkMonitorStreamAnalyzer::Node* node, const char* name)
{
	if(hkString::strCmp(node->m_name, name) == 0)
	{
		return node;
	}
	
	for(int i = 0; i < node->m_children.getSize(); i++)
	{
		hkMonitorStreamAnalyzer::Node* found = find_recursive(node->m_children[i], name);
		if(found != HK_NULL)
		{
			return found;
		}
	}

	return HK_NULL;
}

// tests the performance counters are correct and that they can be serialized
static void accuracy_and_serialization_test()
{
	hkMonitorStream::getInstance().resize(2000);

	hkMonitorStreamAnalyzer* mc = new hkMonitorStreamAnalyzer(20000);

	hkMonitorStreamAnalyzer* streaming_mc = new hkMonitorStreamAnalyzer(20000);

	hkMonitorStreamFrameInfo frameInfo;
	frameInfo.m_indexOfTimer0 = 0;
	frameInfo.m_indexOfTimer1 = 0;
	frameInfo.m_timerFactor0 = 1.0f;
	frameInfo.m_timerFactor1 = 1.0f;

	// Collect some statistics
	{
		for(int i = 0; i < 2; i++)
		{
#			ifdef HK_PLATFORM_PS2
				scePcStart( SCE_PC_CTE | SCE_PC_U0 | SCE_PC_U1 | SCE_PC0_ICACHE_MISS | SCE_PC1_CPU_CYCLE, 0, 0 );
#			endif

			time_something();	// similar to a: m_world->stepDeltaTime();

#			ifdef HK_PLATFORM_PS2
				scePcStop(  );
#			endif

			// capture the data
			hkMonitorStream& stream = hkMonitorStream::getInstance();
			mc->captureFrameDetails(stream.getStart(), stream.getEnd(), frameInfo );

			// export and recapture the data
			{
				hkMonitorStreamFrameInfo frameInfo2 = frameInfo;
				//mc->exportFrame( frameInfo2 );
				
				// this emulates the visual debuggers use of the statistics
				hkMonitorStream& s = hkMonitorStream::getInstance();
				streaming_mc->captureFrameDetails(s.getStart(), s.getEnd(), frameInfo2 );
			}

			// reset the internal timer buffer
			stream.reset();
		}
	}



	// Compare Summaries
	{
		// Summaries of original and serialized data should be identical
		// Should be able to repeat this on the same data, i.e. original data not 
		hkArray<char> output1;
		hkArray<char> output2;

		{
			hkOstream os1(output1);
			hkOstream os2(output2);
			mc->writeStatistics( os1 );
			streaming_mc->writeStatistics( os2 );
		}

		int size1 = output1.getSize();
		int size2 = output2.getSize();
		HK_TEST2( size1 == size2 &&	(hkString::memCmp( output1.begin(), output2.begin(), size1 ) == 0),
				"Analysis of serialized monitors should be identical to nonserialized monitors!");

	}

	// Check the actual values
	if (0)
	{
		hkArray<hkMonitorStreamAnalyzer::Node*> nodes;
		//mc->makeStatisticsTree(nodes);

		// iterate over all frames and 
		{
			float total = 0.0f;
			int numValues = 0;
			// skip the first frame is the are overheads which make the figures inaccurate
			for(int i = 1; i < nodes.getSize(); i++)
			{
				hkMonitorStreamAnalyzer::Node* node = nodes[i];
				hkMonitorStreamAnalyzer::Node* oneMs = find_recursive(node, "1 ms");

				// make sure the tree actually contains the monitor
				HK_TEST2(oneMs != HK_NULL, "Should be able to find a known monitor by name!");

				// now check that the value is in the ballpark of 100 microseconds

				/*
				float error = hkMath::fabs(valueInMicroseconds - 1000.0f);

				hkprintf("Value (us): %f\n", valueInMicroseconds);
				hkprintf("Error (us): %f\n", error);
				*/
				hkReal valueInMicroseconds = oneMs->m_value[0];

				// store the result for averaging
				total += hkMath::fabs(valueInMicroseconds - 1000.0f);
				numValues++;
			}
		
			// Get the average to smooth out the spikes
//			hkprintf("Average Error (us): %f\n", (total / numValues));
			HK_TEST2((total / numValues) < 50.0f, "Average value must be within 50 us of 1 ms (only 5% error allowed)!");
		}

		// cleanup nodes
		{
			for(int i = 0; i < nodes.getSize(); i++)
			{
				delete nodes[i];
				   // the node destructor will recursively delete all children
			}
		}
	}

	delete streaming_mc;
	delete mc;
} 


int monitors_main()
{
	init_quit_test();
//	stopwatch_test();
	
	
	accuracy_and_serialization_test();
	
	
	
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(monitors_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );



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
