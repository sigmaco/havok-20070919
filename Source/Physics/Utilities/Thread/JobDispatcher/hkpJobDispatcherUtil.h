/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_UTILITIES2_JOB_DISPATCHER_UTIL_H
#define HK_UTILITIES2_JOB_DISPATCHER_UTIL_H


#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>


class hkpJobDispatcherUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_UTILITIES, hkpJobDispatcherUtil);

		enum
		{
			MAX_JOB_FUNCS = hkJobHelperBaseClass::HK_END_JOB_BASE
		};

		typedef hkJobQueue::JobStatus (HK_CALL *ProcessJobFunc)( hkJobQueue::ThreadType threadType, hkpProcessCollisionInput& input, hkJobQueue& jobQueue, hkJobQueue::JobQueueEntry& jobInOut );

	private:

			// This default job function will only pop the job from the queue.
		static hkJobQueue::JobStatus HK_CALL defaultProcessJobFunc( hkJobQueue::ThreadType threadType, hkpProcessCollisionInput& input, hkJobQueue& jobQueue, hkJobQueue::JobQueueEntry& jobInOut );

	public:

			/// All job ids are preset with the default function passed into the constructor.
		hkpJobDispatcherUtil( ProcessJobFunc defaultFunc = defaultProcessJobFunc );

			/// Register a (custom) user function for the supplied job id.
		void registerProcessFunc( int jobId, ProcessJobFunc func );

			/// This function will process jobs from the queue until the queue is empty, then return.
		hkJobQueue::JobStatus processNextJob( hkJobQueue::ThreadType threadType, hkpProcessCollisionInput& input, hkJobQueue& jobQueue );

	private:

			// An array that maps jobIds (= offsets into array) to job functions. All functions are preset to the default function which is passed to the constructor.
		ProcessJobFunc m_jobFuncs[MAX_JOB_FUNCS];
};


#endif // HK_UTILITIES2_JOB_DISPATCHER_UTIL_H

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
