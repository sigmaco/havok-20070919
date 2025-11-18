/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_CPU_AGENT_SECTOR_JOB_H
#define HK_CPU_AGENT_SECTOR_JOB_H


#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

#include <Physics/Dynamics/World/Simulation/Multithreaded/hkpDynamicsJobQueueUtils.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>
#include <Physics/Dynamics/World/Simulation/Multithreaded/hkpMultithreadedSimulation.h>


hkJobQueue::JobStatus HK_CALL hkCpuAgentSectorJob(	hkpMtThreadStructure&		tl,
													hkJobQueue&					jobQueue,
													hkJobQueue::JobQueueEntry&	nextJobOut );


HK_FORCE_INLINE void HK_CALL hkCpuProcessAgentHelperFunc(	hkpAgentNnEntry*					entry,
										 const hkpProcessCollisionInput&	input,
										 hkpProcessCollisionOutput&		processOutput,
										 hkpMultiThreadedSimulation*		simulation )
{
	hkpCollidable* collA = entry->getCollidableA();
	hkpCollidable* collB = entry->getCollidableB();

	{
		input.m_collisionQualityInfo = input.m_dispatcher->getCollisionQualityInfo( entry->m_collisionQualityIndex );
		input.m_createPredictiveAgents = input.m_collisionQualityInfo->m_useContinuousPhysics;

		processOutput.reset();

		hkAgentNnMachine_ProcessAgent( entry, input, processOutput, entry->m_contactMgr );

		if ( !processOutput.isEmpty() )
		{
			entry->m_contactMgr->processContact( *collA, *collB, input, processOutput );
		}

		if ( processOutput.hasToi() )
		{
			HK_ASSERT( 0xf0324354, input.m_stepInfo.m_startTime <= processOutput.m_toi.m_time );
			HK_ASSERT2(0xad8765dd, processOutput.m_toi.m_time >= simulation->getCurrentTime(), "Generating a TOI event before hkpWorld->m_currentTime.");

			hkCriticalSectionLock lock( &simulation->m_toiQueueCriticalSection );
			simulation->addToiEvent(processOutput, *entry );
		}
	}
}

#endif // HK_CPU_AGENT_SECTOR_JOB_H

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
