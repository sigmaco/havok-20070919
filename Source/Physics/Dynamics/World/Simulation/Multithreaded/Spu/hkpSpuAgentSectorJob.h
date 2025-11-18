/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_AGENT_SECTOR_JOB_H
#define HK_SPU_AGENT_SECTOR_JOB_H


#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>

class hkpMultiThreadedSimulation;
class hkCollisionDispatcherPpu;
struct hkpMultithreadedSimulationJobData;

class hkpSpuCollideUtil
{
	public:

		static void HK_CALL getDispatcherFromMainMemoryAndFixIt(void* weldingTableOnPpu, hkCollisionDispatcherPpu* dispatcherInMainMemory, hkpCollisionDispatcher* localDispatcher);

	protected:

		static void HK_CALL fixDispatcherFunctionPointer(hkpCollisionDispatcher* dispatcher, hkpShapeType shapeTypeA, hkpShapeType shapeTypeB, hkpCollisionDispatcher::Agent3Funcs& replacementFunction);
};


hkJobQueue::JobStatus HK_CALL hkSpuAgentSectorJob(		  hkpProcessCollisionInput&			collisionInput,
														  hkJobQueue&						jobQueue,
													const hkpMultithreadedSimulationJobData&	jobData,
														  hkJobQueue::JobQueueEntry&		nextJobOut );


#endif // HK_SPU_AGENT_SECTOR_JOB_H

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
