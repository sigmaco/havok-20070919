/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_INTEGRATE_MOTIONS_JOB_H
#define HK_SPU_INTEGRATE_MOTIONS_JOB_H


#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpu4WayCache.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Dynamics/World/Simulation/Multithreaded/Spu/hkpSpuConfig.h>
#include <Common/Base/Memory/PlattformUtils/Spu/SpuStack/hkSpuStack.h>

#include <Common/Base/Types/Physics/hkStepInfo.h>
#include <Physics/Dynamics/World/Simulation/Multithreaded/hkpMultithreadedSimulationJobData.h>


struct hkpSpuIntegrateMotionPipelineStageData
{

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ROOT, hkpSpuIntegrateMotionPipelineStageData );

	public:

		void init(int dmaGroup)
		{
			m_dmaGroup = dmaGroup;
		}

		HK_FORCE_INLINE hkpEntity* getEntity() { return reinterpret_cast<hkpEntity*>( &m_entityBuffer[0] ); }

	public:

		HK_ALIGN16( hkUchar m_entityBuffer[ HK_NEXT_MULTIPLE_OF(16, sizeof(hkpEntity)) ] );

		hkPadSpu<int>				m_dmaGroup;

		hkPadSpu<const hkpShape*>	m_shape;
		hkPadSpu<hkpMaxSizeMotion*>	m_motionOnPpu;
		hkPadSpu<hkpEntity*>			m_entityOnPpu;

};

struct hkpSpuIntegrateMotionPipelineTool
{

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ROOT, hkpSpuIntegrateMotionPipelineTool );

	public:

		void init(int baseDmaGroup)
		{
			{
			
				int shapeCacheBufferSize = m_shapeCache.initAndGetBufferSize(HK_SPU_MAXIMUM_SHAPE_SIZE, HK_SPU_AGENT_SECTOR_JOB_ROOT_SHAPE_NUM_CACHE_ROWS, hkSpuDmaManager::READ_COPY);
				void* shapeCacheBuffer = hkSpuStack::getInstance().allocateStack(shapeCacheBufferSize, "shape-cache buffer"); // See 0xaf5241e5.
				m_shapeCache.initBuffer(shapeCacheBuffer);
			}

			{
				int untypedCacheBufferSize = m_untypedCache.initAndGetBufferSize(HK_SPU_UNTYPED_CACHE_LINE_SIZE, HK_SPU_AGENT_SECTOR_JOB_UNTYPED_NUM_CACHE_ROWS, hkSpuDmaManager::READ_COPY);
				m_unalignedCacheStack = hkSpuStack::getInstance().allocateStack(untypedCacheBufferSize + HK_SPU_UNTYPED_CACHE_LINE_SIZE, "Untyped-cache buffer"); // See 0xaf5241e6.
				void* alignedCacheBuffer = (void*)HK_NEXT_MULTIPLE_OF(HK_SPU_UNTYPED_CACHE_LINE_SIZE, (hkUlong)m_unalignedCacheStack.val());
				m_untypedCache.initBuffer(alignedCacheBuffer);
			}

			m_stageData[0].init(baseDmaGroup+0);
			m_stageData[1].init(baseDmaGroup+1);
			m_stageData[2].init(baseDmaGroup+2);
			m_stageData[3].init(baseDmaGroup+3);
		}

		void exit()
		{
			{
				m_untypedCache.exit();
				hkSpuStack::getInstance().deallocateStack(m_unalignedCacheStack);
			}
			{
				m_shapeCache.exit();
				hkSpuStack::getInstance().deallocateStack(m_shapeCache.getBuffer());
			}
		}

	public:

		hkSpu4WayCache							m_untypedCache;
		hkSpu4WayCache							m_shapeCache;
		hkpSpuIntegrateMotionPipelineStageData	m_stageData[4];	// we use a 4-stage pipeline
		hkPadSpu<void*>							m_unalignedCacheStack;
};


	// returns the number of inactive frames
int HK_CALL hkSpuIntegrateMotionImpl(	const hkpSolverInfo&						solverInfo,
										const hkStepInfo&						stepInfo, 
										const hkpProcessCollisionInput&			collisionInput,
										const hkpMultithreadedSimulationJobData&	jobData,
										const hkpEntity*const*					entitiesBatchInMainMemory,
											  int								numEntities,
											  int								usedStackSizeToVerify,
											  hkpVelocityAccumulator*			accumulators);


hkJobQueue::JobStatus hkSpuIntegrateMotionJob(	const hkpSolverInfo&						info,
												const hkStepInfo&						stepInfo,
												const hkpProcessCollisionInput&			collisionInput,
												const hkpMultithreadedSimulationJobData&	jobData,
													  hkJobQueue&						jobQueue,
													  hkJobQueue::JobQueueEntry&		jobInOut,
													  hkJobQueue::WaitStatus			waitStatus);


#endif // HK_SPU_INTEGRATE_MOTIONS_JOB_H

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
