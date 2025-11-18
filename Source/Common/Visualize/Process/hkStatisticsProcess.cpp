/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>

#include <Common/Base/System/Stopwatch/hkStopwatch.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>
#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>

#include <Common/Visualize/hkProcessFactory.h>
#include <Common/Visualize/hkProcessContext.h>
#include <Common/Visualize/Process/hkStatisticsProcess.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>
#include <Common/Visualize/Serialize/hkObjectSerialize.h>
#include <Common/Visualize/Serialize/hkDisplaySerializeOStream.h>

int hkStatisticsProcess::m_tag = 0;

hkProcess* HK_CALL hkStatisticsProcess::create(const hkArray<hkProcessContext*>& contexts)
{
	return new hkStatisticsProcess(contexts); // doesn't require a context (the monitors are global)
}

void HK_CALL hkStatisticsProcess::registerProcess()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkStatisticsProcess::hkStatisticsProcess(const hkArray<hkProcessContext*>& contexts)
: hkProcess( true) /* user selectable */
{
	// grab the data from the monitors

	hkMonitorStreamFrameInfo frameInfo;
	frameInfo.m_heading = HK_NULL;

	// XX:  make VDB client able to actively choose timers.
#ifdef HK_PLATFORM_PS2
	// take the first two.. whatever they are. Change this to report dcache etc. 
	frameInfo.m_absoluteTimeCounter = hkMonitorStreamFrameInfo::ABSOLUTE_TIME_TIMER_1;
	frameInfo.m_indexOfTimer0 = 0;
	frameInfo.m_indexOfTimer1 = 1;
	frameInfo.m_timerFactor0 = 0;
	frameInfo.m_timerFactor1 =  1e3f / 300e6f; //millisecs
#else
	frameInfo.m_absoluteTimeCounter = hkMonitorStreamFrameInfo::ABSOLUTE_TIME_TIMER_0;
	frameInfo.m_indexOfTimer0 = 0; // just the one timer.
	frameInfo.m_indexOfTimer1 = 1;
	frameInfo.m_timerFactor0 = 1e3f / float(hkStopwatch::getTicksPerSecond()); //millisecs
	frameInfo.m_timerFactor1 = 1.0f;
#endif

	// info on what is in the stream:
	{
		hkArray<hkObjectSerialize::GlobalFixup> globalFixups;
		hkArrayStreamWriter infoWriter(&m_infoBuffer, hkArrayStreamWriter::ARRAY_BORROW);
		hkObjectSerialize::writeObject( &infoWriter, hkStructureLayout::MsvcWin32LayoutRules, 0x1, &frameInfo, hkMonitorStreamFrameInfoClass, globalFixups);
		HK_ASSERT2(0x54e4565e, globalFixups.getSize() == 0, "Monitor Stream Info should not have external ptrs!");
	}

	// keep the contexts
	// Any one of which could provide the per thread timers
	m_contexts = contexts;
}

hkStatisticsProcess::~hkStatisticsProcess()
{

}

#if 0 

static void _checkStringMap( const char* frameStart, const char* frameEnd, const hkPointerMap<const void*, const char*>& map )
{
	// if the data came from a different endian machine, we need to run through it and do a quick swap on
	// data that is > byte sized.

	char* current = const_cast<char*>( frameStart );
	char* end = const_cast<char*>( frameEnd );
	while(current < end) // for all frames
	{
		hkMonitorStream::Command* command = reinterpret_cast<hkMonitorStream::Command*>(current);

		if (hkUlong(command->m_commandAndMonitor) < 10)
		{
			int* elfId = (int*)command;
			current = (char*)(elfId + 1);
			continue;
		}

		const char* dummy;

		// Replace char* with pointer to loaded string
		hkResult res = map.get( command->m_commandAndMonitor, &dummy ); 
		if ( res == HK_FAILURE )
		{
			HK_WARN(0x032154, "Got an unknown string in the command stream. Abortring.");
			return;
		}

		
		switch(command->m_commandAndMonitor[0])
		{
		case 'T': // timer begin
		case 'E': // timer end
		case 'S': // split list
		case 'l': // list end
			{
				hkMonitorStream::TimerCommand* timerCommand = reinterpret_cast<hkMonitorStream::TimerCommand*>( current );
				current = (char*)(timerCommand + 1);
				break;
			}

		case 'L': // timer list begin
			{
				hkMonitorStream::TimerBeginListCommand* timerCommand = reinterpret_cast<hkMonitorStream::TimerBeginListCommand*>( current );
				current = (char*)(timerCommand + 1);
				
				HK_ON_DEBUG( hkResult res2 = ) map.get( timerCommand->m_nameOfFirstSplit, &dummy ); 
				HK_ASSERT(0,res2 != HK_FAILURE);
				break;
			}

		case 'M':
			{
				hkMonitorStream::AddValueCommand* serializedCommand = reinterpret_cast<hkMonitorStream::AddValueCommand*>( current );
				current = (char*)(serializedCommand + 1);
				break;
			}
		case 'P':
		case 'p':
			{
				hkMonitorStream::Command* serializedCommand = reinterpret_cast<hkMonitorStream::Command*>( current );
				current = (char*)(serializedCommand + 1);
				break;
			}

		case 'F':	// new frame
		case 'N':	// nop, skip command
			{
				hkMonitorStream::Command* com = reinterpret_cast<hkMonitorStream::Command*>(current);
				current = (char*)(com + 1);
				break;
			}
		
		default:
			HK_ASSERT2(0x3f2fecd9, 0, "Inconsistent Monitor capture data" ); return;
		}
	}
}

#endif

void hkStatisticsProcess::step(hkReal frameTimeInMs)
{
	if (!m_outStream)
		return; // nothing to write to

	hkArray<hkObjectSerialize::GlobalFixup> globalFixups;

	// see if we have any per thread timers:
	hkArray<const char*> starts;
	hkArray<const char*> ends;
	for (int ci=0; ci < m_contexts.getSize(); ++ci)
	{	
		if (m_contexts[ci]->m_monitorStreamBegins.getSize() > 0)
		{
			starts =  m_contexts[ci]->m_monitorStreamBegins;
			ends = m_contexts[ci]->m_monitorStreamEnds;
			break;
		}
	}

	if (starts.getSize() == 0)
	{
		// data to send (raw mon stream)
		hkMonitorStream& stream = hkMonitorStream::getInstance();
		char* monStreamBegin = stream.getStart();
		char* monStreamEnd = stream.getEnd();
		starts.pushBack(monStreamBegin);
		ends.pushBack(monStreamEnd);
	}

	
	// build a string map for the stream (the whole set of monitors as they should all 
	// share a good few strings)
	m_strBuffer.setSize(0);
	int totalMonLen = 0;
	{
		hkPointerMap<const void*, const char*> strPtrMap;
		hkMonitorStreamStringMap strMap;

		// for all threads
		for (int ms=0; ms < starts.getSize(); ++ms)
		{
			hkMonitorStreamAnalyzer::extractStringMap(starts[ms], ends[ms], strPtrMap);
			totalMonLen += static_cast<int>( ends[ms] - starts[ms] ); 
		}

		// convert hash table into a compact array
		for (hkPointerMap<void*, char*>::Iterator itr = strPtrMap.getIterator(); strPtrMap.isValid(itr); itr = strPtrMap.getNext(itr) )
		{
			hkMonitorStreamStringMap::StringMap& newEntry = strMap.m_map.expandOne();
			newEntry.m_id = reinterpret_cast<hkUint64>( strPtrMap.getKey(itr) ); // id (ptr on Server)
			newEntry.m_string = strPtrMap.getValue(itr); // string
		}

	//	for (int mss=0; mss < starts.getSize(); ++mss)
	//	{
	//		_checkStringMap( starts[mss], ends[mss], strPtrMap );
	//	}

		// save to a buffer
		hkArrayStreamWriter strWriter(&m_strBuffer, hkArrayStreamWriter::ARRAY_BORROW);
		hkObjectSerialize::writeObject( &strWriter, hkStructureLayout::MsvcWin32LayoutRules, 0x1, &strMap, hkMonitorStreamStringMapClass, globalFixups);
		HK_ASSERT2(0x15456e56, globalFixups.getSize() == 0, "String Map should not have external ptrs!");
	}

	if (totalMonLen < 1)
		return;

	// have the info stream already from the ctor
	
	// work out full packet size
	int numStreams = starts.getSize();
	int infoBufSize = m_infoBuffer.getSize();
	int strBufSize = m_strBuffer.getSize();
	const int packetSize = 1 /*command id*/ + (totalMonLen + (4 * numStreams /*stream len*/) + 4/*num streams*/) + (strBufSize + 4/*len int*/) + (infoBufSize + 4/*len int*/);

	m_outStream->write32u(packetSize);
	m_outStream->write8u(hkStatisticsProcess::HK_SEND_STATISTICS_DUMP);

		// The frame info 
	m_outStream->write32(infoBufSize);
	if (infoBufSize > 0)
		m_outStream->writeRaw(m_infoBuffer.begin(), infoBufSize);
	
		// The string map
	m_outStream->write32(strBufSize);
	if (strBufSize > 0)
		m_outStream->writeRaw(m_strBuffer.begin(), strBufSize);

		// The large data stream(s):
		// num streams * [streamlen, stream data]
	m_outStream->write32(numStreams);
	for (int si=0; si < numStreams; ++si)
	{
		int monLen = static_cast<int>( ends[si] - starts[si] ); 
		m_outStream->write32(monLen);
		if (monLen > 0)
			m_outStream->writeRaw(starts[si], monLen);
	}
}



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
