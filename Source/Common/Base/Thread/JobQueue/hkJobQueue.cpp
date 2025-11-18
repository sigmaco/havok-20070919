/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>

#if defined (HK_PLATFORM_SPU)
#	include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>
#	include <Common/Base/Monitor/Spu/hkSpuMonitorCache.h>
#endif

#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Common/Base/Monitor/hkMonitorStream.h>


/*
#include <stdio.h>
void printData(hkJobQueue::DynamicData& data)
{
	printf("\nJOB QUEUE DATA:\n");
	printf("data.m_numActiveJobs = %d\n", data.m_numActiveJobs);
	printf("data.m_numCpuThreadsWaitingForJobs = %d\n" , data.m_numCpuThreadsWaitingForJobs);
	printf("data.m_numSpuThreadsWaitingForJobs = %d\n" , data.m_numSpuThreadsWaitingForJobs);
	printf("data.m_jobQueue[0].m_elementsInUse = %d\n" , data.m_jobQueue[0].getSize());
	printf("data.m_jobQueue[1].m_elementsInUse = %d\n" , data.m_jobQueue[1].getSize());
	printf("data.m_jobQueue[1].m_capacity = %d\n" , data.m_jobQueue[1].getCapacity());
	printf("data.m_jobQueue[2].m_elementsInUse = %d\n" , data.m_jobQueue[2].getSize());
}
*/

HK_COMPILE_TIME_ASSERT(sizeof(hkJobQueue::DynamicData) < 128);


// Assert that the different job type ids do not overlap. This is only part of all the asserts. Search for [0xaf15e231] to see all places where this is done.
HK_COMPILE_TIME_ASSERT( (int)hkJobHelperBaseClass::HK_DYNAMICS_JOB_BASE        < (int)hkJobHelperBaseClass::HK_COLLISION_JOB_BASE       );
HK_COMPILE_TIME_ASSERT( (int)hkJobHelperBaseClass::HK_COLLISION_JOB_BASE       < (int)hkJobHelperBaseClass::HK_COLLISION_QUERY_JOB_BASE );
HK_COMPILE_TIME_ASSERT( (int)hkJobHelperBaseClass::HK_COLLISION_QUERY_JOB_BASE < (int)hkJobHelperBaseClass::HK_ANIMATION_JOB_BASE       );
HK_COMPILE_TIME_ASSERT( (int)hkJobHelperBaseClass::HK_ANIMATION_JOB_BASE       < (int)hkJobHelperBaseClass::HK_END_JOB_BASE             );


#if !defined(HK_PLATFORM_SPU)

void hkJobQueue::setJobQueryRules( Rules rules )
{
#if !defined(HK_PLATFORM_HAS_SPU)
	rules = NO_SPU_AVAILABLE;
#endif

	if ( rules == NO_SPU_AVAILABLE )
	{
									m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[0]                 = JOB_TYPE_CPU;
									m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[1]                 = JOB_TYPE_CPU_BROADPHASE;
									
									// if we have no spu, the first thread can never take broadphase jobs before all other integration jobs are finished;
									// otherwise it will endlessly wait in the broadphase job for the export job to be finished
		HK_ON_PLATFORM_HAS_SPU(		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[1]                 = JOB_TYPE_SPU );
		HK_ON_PLATFORM_HAS_SPU(		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[2]                 = JOB_TYPE_CPU_BROADPHASE );
		HK_ON_PLATFORM_HAS_SPU(		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[3]                 = JOB_TYPE_SPU_CD );
									m_jobQueryRules[THREAD_TYPE_CPU].m_numJobTypesAvailable				= JOB_TYPE_MAX;

									m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[0]                 = JOB_TYPE_CPU_BROADPHASE;
									m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[1]                 = JOB_TYPE_CPU;
		HK_ON_PLATFORM_HAS_SPU(		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[2] = JOB_TYPE_SPU);
		HK_ON_PLATFORM_HAS_SPU(		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[3] = JOB_TYPE_SPU_CD);
									m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_numJobTypesAvailable = JOB_TYPE_MAX;
	}
#if defined (HK_PLATFORM_HAS_SPU)
	else if ( rules ==	SPU_AVAILABLE_AND_PPU_CAN_TAKE_SPU_TASKS )
	{
		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[0]					= JOB_TYPE_CPU;
		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[1]					= JOB_TYPE_CPU_BROADPHASE;
		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[2]					= JOB_TYPE_SPU;
		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[3]					= JOB_TYPE_SPU_CD;
		m_jobQueryRules[THREAD_TYPE_CPU].m_numJobTypesAvailable				= JOB_TYPE_MAX;

		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[0]			= JOB_TYPE_CPU_BROADPHASE;
		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[1]			= JOB_TYPE_CPU;
		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[2]			= JOB_TYPE_HINT_SPU;
		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[3]			= JOB_TYPE_HINT_SPU_CD;
		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_numJobTypesAvailable		= JOB_TYPE_MAX;
	}
	else if ( rules ==	SPU_AVAILABLE_AND_PPU_CANNOT_TAKE_SPU_TASKS )
	{
		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[0]              = JOB_TYPE_CPU;
		m_jobQueryRules[THREAD_TYPE_CPU].m_jobTypeOrder[1]              = JOB_TYPE_CPU_BROADPHASE;
		m_jobQueryRules[THREAD_TYPE_CPU].m_numJobTypesAvailable			= 2;

		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[0]      = JOB_TYPE_CPU_BROADPHASE;
		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_jobTypeOrder[1]      = JOB_TYPE_CPU;
		m_jobQueryRules[THREAD_TYPE_CPU_BROADPHASE].m_numJobTypesAvailable = 2;
	}

	m_jobQueryRules[(int)THREAD_TYPE_SPU].m_numJobTypesAvailable = 1;
	m_jobQueryRules[(int)THREAD_TYPE_SPU].m_jobTypeOrder[0] = JOB_TYPE_SPU;
	m_jobQueryRules[(int)THREAD_TYPE_SPU].m_jobTypeOrder[1] = JOB_TYPE_SPU_CD;
	
	m_jobQueryRules[(int)THREAD_TYPE_SPU_CD].m_numJobTypesAvailable = 1;
	m_jobQueryRules[(int)THREAD_TYPE_SPU_CD].m_jobTypeOrder[0] = JOB_TYPE_SPU_CD;
	m_jobQueryRules[(int)THREAD_TYPE_SPU_CD].m_jobTypeOrder[1] = JOB_TYPE_SPU;

#endif
}

hkJobQueue::hkJobQueue(hkSemaphoreBusyWait* cpuWaitSemaphore, hkSemaphoreBusyWait* taskCompletionSemaphore, hkSemaphoreBusyWait* spuWaitSemaphore)	: m_criticalSection(0)
{
	m_data = new DynamicData();

	m_cpuWaitSemaphore			= cpuWaitSemaphore;
	m_taskCompletionSemaphore	= taskCompletionSemaphore;
	m_spuWaitSemaphore			= spuWaitSemaphore;

	m_data->m_numCpuThreadsWaitingForJobs = 0;
	m_data->m_numSpuThreadsWaitingForJobs = 0;
	m_data->m_numActiveJobs = 0;

	// Every time the queue is resized from the PPU, it will make sure enough free slots are available (which SPUs can then fill)
	// This capacity could be dynamically resized based on the number of elements in the SPU queue

	m_data->m_jobQueue[0].setCapacity(128);
	m_data->m_jobQueue[1].setCapacity(128);
	m_data->m_jobQueue[2].setCapacity(128);
	m_data->m_jobQueue[3].setCapacity(128);

	setJobQueryRules( NO_SPU_AVAILABLE );
}

hkJobQueue::~hkJobQueue()
{
#if !defined(HK_SIMULATE_SPU_DMA_ON_CPU)	
		// the simulator might wipe data if the spu had locked the job queue
	delete m_data;
#endif
}
#endif // !defined(HK_PLATFORM_SPU) 


#if defined (HK_PLATFORM_SPU)
extern HK_ALIGN(char hkJobQueue_dataStorage[128], 16);
#endif

HK_COMPILE_TIME_ASSERT(128 >= sizeof( hkJobQueue::DynamicData ) );


hkJobQueue::DynamicData* hkJobQueue::lockQueue( char* dynamicDataStorage )
{
	HK_CHECK_ALIGN16( dynamicDataStorage );

#if !defined(HK_PLATFORM_SPU)
	HK_ASSERT( 0xf03ef576, !m_criticalSection.haveEntered() );
	m_criticalSection.enter();
	return m_data;
#else
	hkCriticalSection::enter( m_criticalSection.m_this );
	hkSpuDmaManager::getFromMainMemory( dynamicDataStorage, m_data, sizeof(DynamicData), hkSpuDmaManager::READ_WRITE);
	// we cannot combine this call with the above function, as we are waiting for all dmas
	hkSpuDmaManager::waitForAllDmaCompletion();
	return (DynamicData*)dynamicDataStorage;
#endif
}

void hkJobQueue::unlockQueue( char* dynamicDataStorage )
{
	HK_CHECK_ALIGN16( dynamicDataStorage );

#if !defined (HK_PLATFORM_SPU)
	m_criticalSection.leave();
#else
	hkSpuDmaManager::putToMainMemoryAndWaitForCompletion( m_data, dynamicDataStorage, sizeof(DynamicData), hkSpuDmaManager::WRITE_BACK);
	HK_SPU_DMA_PERFORM_FINAL_CHECKS                     ( m_data, dynamicDataStorage, sizeof(DynamicData));
	hkCriticalSection::leave( m_criticalSection.m_this );
#endif
}


hkJobQueue::JobStatus hkJobQueue::getNextJob( ThreadType threadType, JobQueueEntry& job, WaitStatus waitStatus )
{ 
	return finishJobAndGetNextJob( threadType, HK_NULL, job, HK_NULL, waitStatus); 
}


// TODO - job status -> GetNextJobStatus
// JobType -> JobType
// Inl file
// remove hkpDynamicsJob

void hkJobQueue::releaseOneWaitingThread( JobType jobThreadType, DynamicData* data )
{
	// WARNING: THIS FUNCTION MUST ALWAYS BE CALLED WHEN THE MT CRITICAL SECTION IS LOCKED
	// TODO - add isLocked to critical section and add assert
#if defined(HK_PLATFORM_HAS_SPU)
	if ( ( jobThreadType == JOB_TYPE_SPU) || (jobThreadType == JOB_TYPE_SPU_CD ) )
	{
		if ( data->m_numSpuThreadsWaitingForJobs  )
		{
			data->m_numSpuThreadsWaitingForJobs--;
			hkSemaphoreBusyWait::release(m_spuWaitSemaphore);
		}
	}
	else
#endif
	{
		if ( data->m_numCpuThreadsWaitingForJobs  )
		{
			int numCpuJobs = data->m_jobQueue[JOB_TYPE_CPU].getSize() + data->m_jobQueue[JOB_TYPE_CPU_BROADPHASE].getSize();
			if ( numCpuJobs  )
			{
				data->m_numCpuThreadsWaitingForJobs--;
				hkSemaphoreBusyWait::release(m_cpuWaitSemaphore);
			}
		}
	}
}

void hkJobQueue::checkQueueAndReleaseOneWaitingThread( ThreadType threadType, DynamicData* data )
{
	// WARNING: THIS FUNCTION MUST ALWAYS BE CALLED WHEN THE MT CRITICAL SECTION IS LOCKED
	// TODO - add isLocked to critical section and add assert
#if defined(HK_PLATFORM_HAS_SPU)
	if ( (threadType == THREAD_TYPE_SPU) || (threadType == THREAD_TYPE_SPU_CD ) )
	{
		if ( !data->m_jobQueue[JOB_TYPE_SPU].isEmpty() || !data->m_jobQueue[JOB_TYPE_SPU_CD].isEmpty() )
		{
			if ( data->m_numSpuThreadsWaitingForJobs  )
			{
				data->m_numSpuThreadsWaitingForJobs--;
				hkSemaphoreBusyWait::release(m_spuWaitSemaphore);
				return;
			}
				// check if ppu can take spu jobs, and if so release a ppu thread
			if ( data->m_numCpuThreadsWaitingForJobs && m_jobQueryRules[THREAD_TYPE_CPU].m_numJobTypesAvailable==JOB_TYPE_MAX )
			{
				data->m_numCpuThreadsWaitingForJobs--;
				hkSemaphoreBusyWait::release(m_cpuWaitSemaphore);
				return;
			}
		}
		return;
	}
#endif
	{
		if ( data->m_numCpuThreadsWaitingForJobs )
		{
			int numCpuJobs = data->m_jobQueue[JOB_TYPE_CPU].getSize() + data->m_jobQueue[JOB_TYPE_CPU_BROADPHASE].getSize();
			if ( numCpuJobs  )
			{
				data->m_numCpuThreadsWaitingForJobs--;
				hkSemaphoreBusyWait::release(m_cpuWaitSemaphore);
			}
		}
	}
}


void hkJobQueue::addJob( JobQueueEntry& job, JobPriority priority, JobType jobThreadType )
{
	HK_ASSERT(0xf032e454, jobThreadType >= 0 && jobThreadType < 4 );

	HK_ALIGN(char dynamicDataStorage[128], 16);
	DynamicData* data = lockQueue( dynamicDataStorage );
	{
		// Add the jobEntry to the queue
		if ( priority == JOB_HIGH_PRIORITY )
		{
			data->m_jobQueue[jobThreadType].enqueueInFront( job );
		}
		else
		{
			data->m_jobQueue[jobThreadType].enqueue( job );
		}

		releaseOneWaitingThread( jobThreadType, data );
	}
	unlockQueue( dynamicDataStorage );
}


HK_FORCE_INLINE hkJobQueue::JobStatus hkJobQueue::findNextJob(ThreadType threadType, JobQueueEntry& jobOut, DynamicData* data)
{
	// WARNING: THIS FUNCTION MUST ALWAYS BE CALLED WHEN THE MT CRITICAL SECTION IS LOCKED
	// TODO - add isLocked to critical section and add assert

	// Check queues for a new job, starting with the queue matching the thread index
	JobQueryRule& myRules = m_jobQueryRules[threadType];

	for ( int i = 0; i < myRules.m_numJobTypesAvailable; i++)
	{
		hkQueue< JobQueueEntry >* queue = &data->m_jobQueue[myRules.m_jobTypeOrder[i]];

#if defined (HK_PLATFORM_HAS_SPU) && !defined(HK_PLATFORM_SPU)
		/*
		// if we enable this section we risk a deadlock if we disable the spus in our demos using m_numActiveSpus

		// we are on PPU here
		HK_ASSERT( 0xf0323454, threadType != THREAD_TYPE_SPU);

		// If the job is an SPU job, and there is an SPU waiting, let the SPU have it
		if ( ( myRules.m_jobTypeOrder[i] == JOB_TYPE_SPU ) )
		{
			// We are assuming here that the jobs are "single" jobs
			if (data->m_numSpuThreadsWaitingForJobs >= queue->getSize())
			{
				return NO_JOBS_AVAILABLE;
			}
		}
		if ( ( myRules.m_jobTypeOrder[i] == JOB_TYPE_SPU_CD ) )
		{
			// We are assuming here that the jobs are "single" jobs
			if (data->m_numSpuThreadsWaitingForJobs >= queue->getSize())
			{
				return NO_JOBS_AVAILABLE;
			}
		}
		*/
#endif

		if ( !queue->isEmpty() )
		{
			HK_ALIGN16(JobQueueEntry job);
			queue->dequeue(job);
			 
			if ( m_jobPopFunc(*this, data, job, jobOut) == DO_NOT_POP_QUEUE_ENTRY )
			{
				queue->enqueueInFront(job);
			}

			data->m_numActiveJobs++;
			return GOT_NEXT_JOB;
		}
	}
	return NO_JOBS_AVAILABLE;
}

HK_FORCE_INLINE hkBool hkJobQueue::allQueuesEmpty( hkJobQueue::DynamicData* data )
{
	int numJobs = data->m_jobQueue[JOB_TYPE_CPU].getSize() + data->m_jobQueue[JOB_TYPE_CPU_BROADPHASE].getSize();
#if defined(HK_PLATFORM_HAS_SPU)
	numJobs += data->m_jobQueue[JOB_TYPE_SPU].getSize();
	numJobs += data->m_jobQueue[JOB_TYPE_SPU_CD].getSize();
#endif
	return numJobs == 0;
}

hkJobQueue::JobStatus hkJobQueue::finishJobAndGetNextJob( ThreadType threadType, const JobQueueEntry* oldJob, JobQueueEntry& jobOut, void* params, WaitStatus waitStatus )
{
#if defined(HK_PLATFORM_SPU)
	hkSpuMonitorCache::dmaMonitorDataToMainMemorySpu(); // empty inline function if monitors are disabled
#endif

#if !defined(HK_PLATFORM_SPU)
	HK_TIME_CODE_BLOCK("GetNextJob", HK_NULL);
#endif
	HK_ASSERT(0xf032e454, threadType >= -1 && threadType < 4 );
	while(1)
	{
		HK_ALIGN(char dynamicDataStorage[128], 16);
		DynamicData* data = lockQueue( dynamicDataStorage );

		hkBool jobCreated = false;
		JobQueueEntryInput createdJob; 
		// If we have an old job, we need to check whether this old job just triggers a new job
		{
			if (oldJob)
			{
				if ( m_finishJobFunc( *this, data, *oldJob, createdJob ) == JOB_CREATED )
				{
					// Add the job to the queue
					if ( createdJob.m_jobPriority == JOB_HIGH_PRIORITY )
					{
						data->m_jobQueue[createdJob.m_jobThreadType].enqueueInFront( (const JobQueueEntry&)createdJob.m_job );
					}
					else
					{
						data->m_jobQueue[createdJob.m_jobThreadType].enqueue( (const JobQueueEntry&)createdJob.m_job );
					}
					jobCreated = true;
				}
					// if we finished a dummy job, simply return
				if ( threadType == THREAD_TYPE_INVALID)
				{
					checkQueueAndReleaseOneWaitingThread( hkJobQueue::ThreadType(createdJob.m_jobThreadType.val()), data);
					unlockQueue( dynamicDataStorage );
					return NO_JOBS_AVAILABLE;
				}
				data->m_numActiveJobs--;
				oldJob = 0;
			}
		}

		// Try to find another job from available job queues 
		JobStatus result = findNextJob( threadType, jobOut, data );

#if defined(HK_PLATFORM_HAS_SPU)
		// this function might spawn 2 new jobs: the add job and the find next job
		// Example:
		//    - enqueue() puts an spu job on the queue -> so we need to release a spu thread
		//    - findNextJob() gets and splits a job on the ppu -> so we need to release a ppu thread
		//    we only need to release 2 threads if the created job is on a different platform than the found job
		if ( jobCreated && createdJob.m_jobThreadType != hkUint32(JobType(threadType)) )
		{
			checkQueueAndReleaseOneWaitingThread( ThreadType(createdJob.m_jobThreadType.val()), data);
			jobCreated = false;
		}
#endif

		if (result == GOT_NEXT_JOB)
		{
			checkQueueAndReleaseOneWaitingThread( threadType, data);
			unlockQueue( dynamicDataStorage );
			return GOT_NEXT_JOB;
		}

		if ( (data->m_numActiveJobs == 0) && allQueuesEmpty( data ) )
		{
			releaseWaitingThreads(data);
			unlockQueue( dynamicDataStorage );
			return ALL_JOBS_FINISHED;
		}

		if ( waitStatus == DO_NOT_WAIT_FOR_NEXT_JOB )
		{
			unlockQueue( dynamicDataStorage );
			return NO_JOBS_AVAILABLE;
		}

#if defined (HK_PLATFORM_SPU)

		JobQueryRule& myRules = m_jobQueryRules[threadType];
		hkQueue< JobQueueEntry >* otherSpuQueue = &data->m_jobQueue[myRules.m_jobTypeOrder[1]];

		if ( !otherSpuQueue->isEmpty() )
		{
			unlockQueue( dynamicDataStorage );
			return JOBS_AVAILABLE_BUT_NOT_FOR_CURRENT_ELF;
		}
		else
		{
			// The queues are both empty, but there are active jobs, so wait to see if a new job appears
			data->m_numSpuThreadsWaitingForJobs++;
			unlockQueue( dynamicDataStorage );
			HK_TIMER_BEGIN("WaitForSignal",HK_NULL);
			hkSemaphoreBusyWait::acquire(m_spuWaitSemaphore);
			HK_TIMER_END();
		}

#else
		// The queues are both empty, but there are active jobs, so wait to see if a new job appears
		data->m_numCpuThreadsWaitingForJobs++;
		unlockQueue( dynamicDataStorage );
		HK_TIMER_BEGIN("WaitForSignal",HK_NULL);
		m_cpuWaitSemaphore->acquire();
		HK_TIMER_END();
#endif
	}
}

#if !defined(HK_PLATFORM_SPU)
hkJobQueue::JobStatus hkJobQueue::addJobAndGetNextJob( JobType jobThreadType, JobPriority priority, ThreadType threadType, JobQueueEntry& jobInOut, WaitStatus waitStatus )
{
	HK_ASSERT(0xf032e454, jobThreadType >= 0 && jobThreadType < JOB_TYPE_MAX );
	HK_ASSERT(0xf032e454, threadType    >= 0 && threadType    < THREAD_TYPE_MAX );

	HK_TIMER_BEGIN("GetNextJob",HK_NULL);
	
	bool firstTime = true;
	while (1)
	{
		HK_ALIGN(char dynamicDataStorage[128], 16);
		DynamicData* data = lockQueue( dynamicDataStorage );

		if (firstTime)
		{
			// Add the job to the queue
			if ( priority == JOB_HIGH_PRIORITY )
			{
				data->m_jobQueue[jobThreadType].enqueueInFront( jobInOut );
			}
			else
			{
				data->m_jobQueue[jobThreadType].enqueue( jobInOut );
			}
			data->m_numActiveJobs--;
		}

		// Try to find another job from available job queues 
		JobStatus result = findNextJob(threadType, jobInOut, data );

#if defined(HK_PLATFORM_HAS_SPU)
		// this function might spawn 2 new jobs: the add job and the find next job
		if ( firstTime && threadType != ThreadType(jobThreadType) )
		{
			checkQueueAndReleaseOneWaitingThread( ThreadType(jobThreadType), data);
		}
#endif
		firstTime = false;

		if (result == GOT_NEXT_JOB)
		{
			checkQueueAndReleaseOneWaitingThread( threadType, data);
			unlockQueue( dynamicDataStorage );
			HK_TIMER_END();
			return GOT_NEXT_JOB;
		}

		// If there are no active jobs and the queues are both empty so we must be finished
		// NOTE: allQueuesEmpty() is currently necessary for CPUs waiting on SPUs to finish jobs
		if ( ( (data->m_numActiveJobs == 0) && allQueuesEmpty( data ) ) )
		{
			releaseWaitingThreads(data);
			unlockQueue( dynamicDataStorage );
			HK_TIMER_END();
			return ALL_JOBS_FINISHED;
		}

		if ( waitStatus == DO_NOT_WAIT_FOR_NEXT_JOB )
		{
			unlockQueue( dynamicDataStorage );
			return NO_JOBS_AVAILABLE;
		}

#if defined (HK_PLATFORM_SPU)
		JobQueryRule& myRules = m_jobQueryRules[threadType];
		hkQueue< JobQueueEntry >* otherSpuQueue = &data->m_jobQueue[myRules.m_jobTypeOrder[1]];

		if ( !otherSpuQueue->isEmpty() )
		{
			unlockQueue( dynamicDataStorage );
			return JOBS_AVAILABLE_BUT_NOT_FOR_CURRENT_ELF;
		}
		else
		{
			// The queues are both empty, but there are active jobs, so wait to see if a new job appears
			data->m_numSpuThreadsWaitingForJobs++;
			unlockQueue( dynamicDataStorage );
			HK_TIMER_BEGIN("WaitForSignal",HK_NULL);
			m_spuWaitSemaphore.acquire();
			HK_TIMER_END();
		}
#else
		// The queues are both empty, but there are active jobs, so wait to see if a new job appears
		data->m_numCpuThreadsWaitingForJobs++;
		unlockQueue( dynamicDataStorage );
		HK_TIMER_BEGIN("WaitForSignal",HK_NULL);
		m_cpuWaitSemaphore->acquire();
#endif

		HK_TIMER_END();
	}
}
#endif

void hkJobQueue::releaseWaitingThreads(DynamicData* data)
{
	//DynamicData* data = lockQueue();
	// Release cpu threads
	{
		int numCpuJobs = data->m_numCpuThreadsWaitingForJobs;
		data->m_numCpuThreadsWaitingForJobs = 0;

		HK_ASSERT2( 0xf032dea1, data->m_jobQueue[0].isEmpty(), "Queue 0 not empty" );
		HK_ASSERT2( 0xf032dea1, data->m_jobQueue[1].isEmpty(), "Queue 1 not empty" );
		HK_ASSERT2( 0, data->m_numActiveJobs == 0, "Num active jobs is not 0" );
		
		for ( ;numCpuJobs > 0; numCpuJobs--)
		{
			hkSemaphoreBusyWait::release(m_cpuWaitSemaphore);
		}
	}

#if defined(HK_PLATFORM_HAS_SPU)
	// Release spu threads
	{
		int numSpuJobs = data->m_numSpuThreadsWaitingForJobs;
		data->m_numSpuThreadsWaitingForJobs = 0;
		HK_ASSERT2( 0xf032dea1, data->m_jobQueue[hkJobQueue::JOB_TYPE_SPU].isEmpty(), "Queue JOB_TYPE_SPU not empty" );
		
		for ( ; numSpuJobs > 0; numSpuJobs--)
		{
			hkSemaphoreBusyWait::release(m_spuWaitSemaphore);
		}
	}
#endif
	//unlockQueue();
}


#if !defined(HK_PLATFORM_SPU)

void hkJobQueue::setSpuQueueCapacity(int queueCapacity)
{
	{
		HK_ALIGN(char dynamicDataStorage[128], 16);
		lockQueue( dynamicDataStorage );
		m_data->m_jobQueue[THREAD_TYPE_CPU_BROADPHASE].setCapacity(queueCapacity);
		m_data->m_jobQueue[THREAD_TYPE_CPU].setCapacity(queueCapacity);
#if defined (HK_PLATFORM_HAS_SPU)
		m_data->m_jobQueue[THREAD_TYPE_SPU].setCapacity(queueCapacity);
		m_data->m_jobQueue[THREAD_TYPE_SPU_CD].setCapacity(queueCapacity);
#endif
		unlockQueue( dynamicDataStorage );
	}
}

#endif


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
