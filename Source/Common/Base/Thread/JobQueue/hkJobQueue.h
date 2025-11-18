/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_BASE_THREAD_JOB_QUEUE_H
#define HK_BASE_THREAD_JOB_QUEUE_H

#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Thread/Semaphore/hkSemaphoreBusyWait.h>

#include <Common/Base/Container/Queue/hkQueue.h>


// This struct is just a sort of dummy, i.e. no job struct actually ever derives from it. It is simply used to cast any arbitrary job
// to a common base so that its m_jobType can be accessed. Note that for this to work, every job has to be 16-byte aligned and have its
// 16bit job type as the first member!
struct hkJobHelperBaseClass
{
	public:

		enum hkJobBaseId
		{
			HK_DYNAMICS_JOB_BASE		=   0,
			HK_COLLISION_JOB_BASE		=  30,
			HK_COLLISION_QUERY_JOB_BASE	=  40,
			HK_ANIMATION_JOB_BASE		=  60,
			HK_END_JOB_BASE				=  80		// just a marker marking the end of the available job id range
		};

		HK_ALIGN16( hkObjectIndex m_jobType );
};


//
// Data to transfer per atomic call
//

	/// This class implements a job queue with all necessary locking and waiting
class hkJobQueue
{
	public:

		enum Rules
		{
			NO_SPU_AVAILABLE,
			SPU_AVAILABLE_AND_PPU_CAN_TAKE_SPU_TASKS,
			SPU_AVAILABLE_AND_PPU_CANNOT_TAKE_SPU_TASKS
		};

		void setJobQueryRules( Rules rules );

			/// The basic struct stored in the job queue
		struct JobQueueEntry
		{
			HK_ALIGN16(hkUchar m_data[128]);
		};

		struct DynamicData
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, DynamicData );

				// The number of jobs which are currently processed (this is both spu and ppu jobs)
			HK_ALIGN16(int m_numActiveJobs);

				// The number of threads waiting for jobs using the m_waitSemaphore
			int m_numCpuThreadsWaitingForJobs;
			int m_numSpuThreadsWaitingForJobs;

			hkQueue< JobQueueEntry > m_jobQueue[4];
		};


		//
		// Enums to specify job types
		//

			/// Types of job that can be placed on and retrieved from the job queue
		enum JobType
		{
			JOB_TYPE_CPU			= 0,
			JOB_TYPE_CPU_BROADPHASE	= 1,	// only the second thread can focus on broadphase jobs
#if defined (HK_PLATFORM_HAS_SPU)
			JOB_TYPE_SPU			= 2,
			JOB_TYPE_HINT_SPU		= 2,
			JOB_TYPE_SPU_CD			= 3,
			JOB_TYPE_HINT_SPU_CD	= 3,
			JOB_TYPE_SPU_CQ			= 3,	// CQ stands for Collision Query
			JOB_TYPE_HINT_SPU_CQ	= 3,
			JOB_TYPE_MAX			= 4,
#else
			JOB_TYPE_HINT_SPU		= 0,
			JOB_TYPE_HINT_SPU_CD	= 0,
			JOB_TYPE_HINT_SPU_CQ	= 0,	// CQ stands for Collision Query
			JOB_TYPE_MAX			= 2,
#endif

		};

			/// Types of threads that can place jobs on and retrieve jobs from the job queue
		enum ThreadType
		{
			THREAD_TYPE_CPU				= JOB_TYPE_CPU,
			THREAD_TYPE_CPU_BROADPHASE	= JOB_TYPE_CPU_BROADPHASE,
#if defined (HK_PLATFORM_HAS_SPU)
			THREAD_TYPE_SPU				= JOB_TYPE_SPU,
			THREAD_TYPE_SPU_CD			= JOB_TYPE_SPU_CD,
			THREAD_TYPE_SPU_CQ			= JOB_TYPE_SPU_CQ,
#endif
			THREAD_TYPE_MAX,
			THREAD_TYPE_INVALID			= -1,
		};

			/// Whether a job is placed at the front or the end of its appropriate queue
		enum JobPriority
		{
			JOB_HIGH_PRIORITY,
			JOB_LOW_PRIORITY,
		};


		//
		// Callback functions used from within critical sections
		//

			/// The result from JobPopFunc
		enum JobPopFuncResult
		{
				/// Set to this if the function is taking the element off the queue
			POP_QUEUE_ENTRY,
				/// Set to this if the function has modified the element, and left it on the queue
			DO_NOT_POP_QUEUE_ENTRY 
		};

		typedef JobPopFuncResult (HK_CALL *JobPopFunc)( hkJobQueue& queue, hkJobQueue::DynamicData* data, JobQueueEntry& jobIn, JobQueueEntry& jobOut );

		enum JobCreationStatus
		{
			JOB_CREATED,
			NO_JOB_CREATED
		};

		struct JobQueueEntryInput
		{
			hkPadSpu<hkUint32>	m_jobThreadType;	// JobType
			hkPadSpu<hkUint32>	m_jobPriority;		// JobPriority
			JobQueueEntry		m_job;
		};

		typedef JobCreationStatus (HK_CALL *FinishJobFunc)( hkJobQueue& queue, DynamicData* data, const JobQueueEntry& jobIn, JobQueueEntryInput& newJobCreatedOut );


	public:
#if defined(HK_PLATFORM_SPU)
	private:
#endif
			/// Note: this class should only ever be constructed on a CPU. If running on an SPU it must be dma'd into an
			/// appropriately sized 128 byte aligned local store buffer.
		 hkJobQueue(hkSemaphoreBusyWait* cpuWaitSemaphore, hkSemaphoreBusyWait* taskCompletionSemaphore, hkSemaphoreBusyWait* spuWaitSemaphore);
		~hkJobQueue();

	public:

		//
		// Runtime functions
		//

			/// Adds a new job to the queue for a given priority and job thread type.
		void addJob( JobQueueEntry& job, JobPriority priority, JobType type );


			/// A flag to tell getNextJob what to do if no job is immediately available
		enum WaitStatus
		{
			WAIT_FOR_NEXT_JOB,
			DO_NOT_WAIT_FOR_NEXT_JOB
		};

			/// Whether a getNextJob call got another job or not
		enum JobStatus
		{
			GOT_NEXT_JOB,
			NO_JOBS_AVAILABLE,
			JOBS_AVAILABLE_BUT_NOT_FOR_CURRENT_ELF,
			ALL_JOBS_FINISHED
		};

			/// Gets a new job. Note: this function should only be called at the start of the main loop.
			/// If you can you should call addAndGetNextJob
		JobStatus getNextJob( ThreadType threadType, JobQueueEntry& job, WaitStatus waitStatus = WAIT_FOR_NEXT_JOB );


		//
		// Compound functions
		//

			/// Call this when one job is finished and you are not calling addJobAndGetNextJob
		JobStatus finishJobAndGetNextJob( ThreadType threadType, const JobQueueEntry* oldJob, JobQueueEntry& jobOut, void* params = HK_NULL, WaitStatus waitStatus = WAIT_FOR_NEXT_JOB );

			/// Finishes a job and gets a new one
			/// This is faster than calling addJob and getNextJob separately, because it can do the
			/// entire operation in one critical section, rather than two critical sections.
		JobStatus addJobAndGetNextJob( JobType jobThreadType, JobPriority priority, ThreadType threadType, JobQueueEntry& jobInOut, WaitStatus waitStatus = WAIT_FOR_NEXT_JOB );

		void setSpuQueueCapacity(int queueCapacity);

	public:
			// Check if a thread is waiting for a job on a semaphore.
			// If one thread is, release the semaphore
		void releaseOneWaitingThread( JobType jobThreadType, DynamicData* data  );

			// Check if a thread with the given threadType is waiting for a job on a semaphore.
			// If one thread is, release the semaphore
		HK_FORCE_INLINE void checkQueueAndReleaseOneWaitingThread( ThreadType threadType, DynamicData* data  );

		HK_FORCE_INLINE JobStatus findNextJob(ThreadType threadType, JobQueueEntry& jobOut, DynamicData* data );
		
		HK_FORCE_INLINE hkBool allQueuesEmpty( DynamicData* data );

		DynamicData* lockQueue( char* dynamicDataStorage );
		void unlockQueue( char* dynamicDataStorage );

	protected:
			// Call this to release all waiting threads
		void releaseWaitingThreads(DynamicData* data);

	public:

		HK_ALIGN( hkCriticalSection m_criticalSection, 64 );

			//
			// Data to transfer once
			//
		HK_CPU_PTR(DynamicData*) m_data;

			//
			// Static, locally set data
			//

		struct JobQueryRule
		{
			hkUint8 m_numJobTypesAvailable;
			hkEnum<JobType, hkUint8> m_jobTypeOrder[JOB_TYPE_MAX];
		};

		JobQueryRule m_jobQueryRules[JOB_TYPE_MAX];

		JobPopFunc m_jobPopFunc; 
		FinishJobFunc m_finishJobFunc;

			// this userdata is pointing to hkpWorld if the queue is used by havok physics
		hkUlong m_userData; // +default(0)

		hkSemaphoreBusyWait* m_cpuWaitSemaphore;
		hkSemaphoreBusyWait* m_taskCompletionSemaphore;
		hkSemaphoreBusyWait* m_spuWaitSemaphore;
};


#endif // HK_BASE_THREAD_JOB_QUEUE_H

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
