/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_BUILD_ACCUMULATORS_JOB_H
#define HK_SPU_BUILD_ACCUMULATORS_JOB_H


#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Common/Base/Types/Physics/hkStepInfo.h>


hkJobQueue::JobStatus HK_CALL hkSpuBuildAccumulatorsJob(const hkStepInfo&					stepInfo, 
															  hkJobQueue&					jobQueue, 
															  hkJobQueue::JobQueueEntry&	jobInOut,
															  hkJobQueue::WaitStatus		waitStatus);


#endif // HK_SPU_BUILD_ACCUMULATORS_JOB_H

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
