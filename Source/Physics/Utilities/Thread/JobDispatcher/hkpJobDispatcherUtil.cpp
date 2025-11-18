/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>

#include <Physics/Collide/Query/Multithreaded/hkpCollisionJobs.h>
#include <Physics/Collide/Query/Multithreaded/Cpu/hkpCpuPairGetClosestPointsJob.h>

#include <Physics/Utilities/Thread/JobDispatcher/hkpJobDispatcherUtil.h>


hkpJobDispatcherUtil::hkpJobDispatcherUtil(ProcessJobFunc defaultFunc)
{
	{
		for (int i=0; i<MAX_JOB_FUNCS; i++)
		{
			m_jobFuncs[i] = defaultFunc;
		}
	}
}


void hkpJobDispatcherUtil::registerProcessFunc(int jobId, ProcessJobFunc func)
{
	HK_ASSERT2(0xaf3526ea, jobId < int(MAX_JOB_FUNCS), "You can only register a maximum of MAX_JOB_FUNCS.");

	m_jobFuncs[jobId] = func;
}


hkJobQueue::JobStatus HK_CALL hkpJobDispatcherUtil::defaultProcessJobFunc( hkJobQueue::ThreadType threadType, hkpProcessCollisionInput& input, hkJobQueue& jobQueue, hkJobQueue::JobQueueEntry& jobInOut )
{
	return jobQueue.finishJobAndGetNextJob( threadType, &jobInOut, jobInOut, 0, hkJobQueue::WAIT_FOR_NEXT_JOB );
}


hkJobQueue::JobStatus hkpJobDispatcherUtil::processNextJob(hkJobQueue::ThreadType threadType, hkpProcessCollisionInput& input, hkJobQueue& jobQueue)
{
	hkJobQueue::JobQueueEntry job;

	hkJobQueue::JobStatus jobStatus = hkJobQueue::NO_JOBS_AVAILABLE;

	if ( jobQueue.getNextJob(threadType, job) == hkJobQueue::GOT_NEXT_JOB )
	{
		jobStatus = hkJobQueue::GOT_NEXT_JOB;

		//HK_ON_DETERMINISM_CHECKS_ENABLED(hkCheckDeterminismUtil::Fuid jobFuid);

		while ( jobStatus == hkJobQueue::GOT_NEXT_JOB )
		{
			hkJobHelperBaseClass& collisionQueryJob = reinterpret_cast<hkJobHelperBaseClass&>(job);

 			//HK_ON_DETERMINISM_CHECKS_ENABLED(jobFuid = dynamicsJob.getFuid());
 			//HK_ON_DETERMINISM_CHECKS_ENABLED(hkCheckDeterminismUtil::registerAndStartJob(jobFuid));

			if ( collisionQueryJob.m_jobType > MAX_JOB_FUNCS )
			{
				HK_ASSERT2(0xafe1a255, 0, "Invalid job type. ID exceeds allowed MAX_JOB_FUNCS.");
			}
			else
			{
				// Note: Each job is responsible for getting the next job from the job queue.
				// The 'job' parameter passed into each job function gets overwritten inside
				// the function with the 'next job to be processed'.
				jobStatus = m_jobFuncs[collisionQueryJob.m_jobType]( threadType, input, jobQueue, job );
			}

			//HK_ON_DETERMINISM_CHECKS_ENABLED(hkCheckDeterminismUtil::finishJob(jobFuid));
		}
	}

	return jobStatus;
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
