/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_DISPATCH_JOBS_H
#define HK_SPU_DISPATCH_JOBS_H


#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Common/Base/Spu/Util/hkSpuUtil.h>

struct hkpMultithreadedSimulationJobData;

enum hkpSimulateElfType
{
	HK_INTEGRATE_ELF,
	HK_COLLIDE_ELF,
	HK_EXIT_ELF
};

//
// Main line functions for SPU elfs
//

hkpSimulateElfType HK_CALL hkSpuCollide( const hkSpuTaskParams& taskParams, char* stackBuffer, int stackBufferSize );

hkpSimulateElfType HK_CALL hkSpuIntegrate( const hkSpuTaskParams& taskParams, char* stackBuffer, int stackBufferSize );

//
// Process job functions 
//

hkJobQueue::JobStatus HK_CALL hkSpuProcessNextJob(			  hkJobQueue&						queue, 
														const hkpMultithreadedSimulationJobData*	jobData, 
															  hkJobQueue::WaitStatus			waitStatusIn);



hkJobQueue::JobStatus HK_CALL hkSpuProcessIntegrateJobs(	  hkJobQueue&						queue, 
														const hkpMultithreadedSimulationJobData*	jobData, 
															  hkJobQueue::WaitStatus			waitStatusIn);



hkJobQueue::JobStatus HK_CALL hkSpuProcessCollideJobs(		  hkJobQueue&						queue, 
														const hkpMultithreadedSimulationJobData*	jobData, 
															  hkJobQueue::WaitStatus			waitStatusIn);


//
// Functions just used for the PC SPU simulator
//
void HK_CALL hkSpursSimulate( const hkSpuTaskParams& taskParams, char* stackBuffer, int stackBufferSize );

void HK_CALL hkSpuThreadSimulate( const hkSpuTaskParams& taskParams, char* stackBuffer, int stackBufferSize );


#endif // HK_SPU_DISPATCH_JOBS_H

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
