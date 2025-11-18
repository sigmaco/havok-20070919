/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Query/Multithreaded/hkpCollisionJobs.h>

#include <Physics/Dynamics/World/hkpWorld.h>

#if defined (HK_PLATFORM_HAS_SPU)
#	include <Physics/Collide/Query/Multithreaded/Spu/hkpSpuConfig.h>
#	include <Physics/Internal/Collide/BroadPhase/3AxisSweep/hkp3AxisSweep.h>
#endif


// Assert that the different job type ids do not overlap. This is only part of all the asserts. Search for [0xaf15e231] to see all places where this is done.
HK_COMPILE_TIME_ASSERT( (int)hkpCollisionQueryJob::COLLISION_QUERY_JOB_END <= (int)hkJobHelperBaseClass::HK_ANIMATION_JOB_BASE );


// ===============================================================================================================================================================================================
//  SHAPE RAYCAST
// ===============================================================================================================================================================================================

// Size of hkpShapeRayCastCommand seems to have increased. Think about reducing the maximum job granularity to avoid having to use getFromMainMemoryLarge() when bringing in the commands on SPU.
HK_COMPILE_TIME_ASSERT( (int)hkpShapeRayCastJob::MAXIMUM_NUMBER_OF_COMMANDS_PER_TASK * sizeof(hkpShapeRayCastCommand) <= 0x4000 );


#if !defined(HK_PLATFORM_SPU)
hkJobQueue::JobType hkpShapeRayCastJob::getJobType()
{
#if defined (HK_PLATFORM_HAS_SPU)
	{
		for (int commandIdx = 0; commandIdx < m_numCommands; commandIdx++)
		{
			const hkpShapeRayCastCommand* command = &m_commandArray[commandIdx];
			{
				for (int collidableIdx = 0; collidableIdx < command->m_numCollidables; collidableIdx++)
				{
					if ( command->m_collidables[collidableIdx]->m_forceCollideOntoPpu != 0 )
					{
						HK_WARN_ONCE(0xaf15e144, "There's at least one shape in the job that is not supported on the SPU. The job has to therefore move to the PPU. Performance loss likely. Consider moving the unsupported shape(s) into a separate job.");
						return hkJobQueue::JOB_TYPE_CPU;
					}
				}
			}
		}
	}

	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#else
	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#endif
}
#endif


// ===============================================================================================================================================================================================
//  WORLD RAYCAST
// ===============================================================================================================================================================================================

// Size of hkpWorldRayCastCommand seems to have increased. Think about reducing the maximum job granularity to avoid having to use getFromMainMemoryLarge() when bringing in the commands on SPU.
HK_COMPILE_TIME_ASSERT( (int)hkpWorldRayCastJob::MAXIMUM_NUMBER_OF_COMMANDS_PER_TASK * sizeof(hkpWorldRayCastCommand) <= 0x4000 );


#if !defined(HK_PLATFORM_SPU)
hkJobQueue::JobType hkpWorldRayCastJob::getJobType()
{
#if defined (HK_PLATFORM_HAS_SPU)
	if ( m_broadphase->getType() != hkpBroadPhase::BROADPHASE_16BIT )
	{
		HK_WARN_ONCE(0xaf35e144, "Only 16bit broadphase supported on SPU. Moving job onto PPU. Performance loss likely.");
		return hkJobQueue::JOB_TYPE_CPU;
	}

	const hkp3AxisSweep* broadphase = reinterpret_cast<const hkp3AxisSweep*>( m_broadphase );

	int totalStackMemNeededByBroadphaseOnSpu;
	{
		int sizeBroadphaseNodesArray = HK_NEXT_MULTIPLE_OF(16, broadphase->m_nodes.getSize() * sizeof(hkp3AxisSweep::hkpBpNode));
		int sizeXAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(16, broadphase->m_axis[0].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		int sizeYAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(16, broadphase->m_axis[1].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		int sizeZAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(16, broadphase->m_axis[2].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		totalStackMemNeededByBroadphaseOnSpu = sizeBroadphaseNodesArray + sizeXAxisEndPointsArray + sizeYAxisEndPointsArray + sizeZAxisEndPointsArray;
	}

	if ( totalStackMemNeededByBroadphaseOnSpu <= HK_SPU_COLLIDE_MOPP_CACHE_SIZE )
	{
		return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
	}
	else
	{
		HK_WARN_ONCE(0xaf35e143, "Broadphase too big to fit into SPU stack buffer. Moving job onto PPU. Performance loss likely.");
		return hkJobQueue::JOB_TYPE_CPU;
	}
#else
	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#endif
}
#endif


// ===============================================================================================================================================================================================
//  PAIR LINEAR CAST
// ===============================================================================================================================================================================================

// Size of hkpPairLinearCastCommand has to be a multiple of 16.
#if !defined(HK_COMPILER_MWERKS)
HK_COMPILE_TIME_ASSERT( (sizeof(hkpPairLinearCastCommand) & 0xf) == 0 );
#endif


#if !defined(HK_PLATFORM_SPU)
hkJobQueue::JobType hkpPairLinearCastJob::getJobType()
{
#if defined (HK_PLATFORM_HAS_SPU)
	{
		for (int commandIdx = 0; commandIdx < m_numCommands; commandIdx++)
		{
			const hkpPairLinearCastCommand* command = &m_commandArray[commandIdx];
			if ( command->m_collidableA->m_forceCollideOntoPpu != 0 || command->m_collidableB->m_forceCollideOntoPpu != 0 )
			{
				HK_WARN_ONCE(0xaf15e142, "There's at least one shape in the job that is not supported on the SPU. The job has to therefore move to the PPU. Performance loss likely. Consider moving the unsupported shape(s) into a separate job.");
				return hkJobQueue::JOB_TYPE_CPU;
			}
		}
	}

	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#else
	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#endif
}
#endif


// ===============================================================================================================================================================================================
//  WORLD LINEAR CAST
// ===============================================================================================================================================================================================

// Size of hkpWorldLinearCastCommand seems to have increased. Think about reducing the maximum job granularity to avoid having to use getFromMainMemoryLarge() when bringing in the commands on SPU.
HK_COMPILE_TIME_ASSERT( (int)hkpWorldLinearCastJob::MAXIMUM_NUMBER_OF_COMMANDS_PER_TASK * sizeof(hkpWorldLinearCastCommand) <= 0x4000 );


#if !defined(HK_PLATFORM_SPU)
hkJobQueue::JobType hkpWorldLinearCastJob::getJobType()
{
#if defined (HK_PLATFORM_HAS_SPU)
	if ( m_broadphase->getType() != hkpBroadPhase::BROADPHASE_16BIT )
	{
		HK_WARN_ONCE(0xaf35e144, "Only 16bit broadphase supported on SPU. Moving job onto PPU. Performance loss likely.");
		return hkJobQueue::JOB_TYPE_CPU;
	}

	const hkp3AxisSweep* broadphase = reinterpret_cast<const hkp3AxisSweep*>( m_broadphase );

	int totalStackMemNeededByBroadphaseOnSpu;
	{
		int sizeBroadphaseNodesArray = HK_NEXT_MULTIPLE_OF(16, broadphase->m_nodes.getSize() * sizeof(hkp3AxisSweep::hkpBpNode));
		int sizeXAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(16, broadphase->m_axis[0].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		int sizeYAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(16, broadphase->m_axis[1].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		int sizeZAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(16, broadphase->m_axis[2].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		totalStackMemNeededByBroadphaseOnSpu = sizeBroadphaseNodesArray + sizeXAxisEndPointsArray + sizeYAxisEndPointsArray + sizeZAxisEndPointsArray;
	}

	if ( totalStackMemNeededByBroadphaseOnSpu > HK_SPU_COLLIDE_MOPP_CACHE_SIZE )
	{
		HK_WARN_ONCE(0xaf35e143, "Broadphase too big to fit into SPU stack buffer. Moving job onto PPU. Performance loss likely.");
		return hkJobQueue::JOB_TYPE_CPU;
	}

	{
		for (int commandIdx = 0; commandIdx < m_numCommands; commandIdx++)
		{
			const hkpWorldLinearCastCommand* command = &m_commandArray[commandIdx];
			if ( command->m_collidable->m_forceCollideOntoPpu != 0 )
			{
				HK_WARN_ONCE(0xaf15e143, "There's at least one shape in the job that is not supported on the SPU. The job has to therefore move to the PPU. Performance loss likely. Consider moving the unsupported shape(s) into a separate job.");
				return hkJobQueue::JOB_TYPE_CPU;
			}
		}
	}

	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#else
	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#endif
}
#endif


// ===============================================================================================================================================================================================
//  MOPP AABB
// ===============================================================================================================================================================================================


// ===============================================================================================================================================================================================
//  PAIR GET CLOSEST POINTS
// ===============================================================================================================================================================================================

// Size of hkpPairGetClosestPointsCommand has to be a multiple of 16.
#if !defined(HK_COMPILER_MWERKS)
HK_COMPILE_TIME_ASSERT( (sizeof(hkpPairGetClosestPointsCommand) & 0xf) == 0 );
#endif


#if !defined(HK_PLATFORM_SPU)
hkJobQueue::JobType hkpPairGetClosestPointsJob::getJobType()
{
#if defined (HK_PLATFORM_HAS_SPU)
	{
		for (int commandIdx = 0; commandIdx < m_numCommands; commandIdx++)
		{
			const hkpPairGetClosestPointsCommand* command = &m_commandArray[commandIdx];
			if ( command->m_collidableA->m_forceCollideOntoPpu != 0 || command->m_collidableB->m_forceCollideOntoPpu != 0 )
			{
				HK_WARN_ONCE(0xaf15e141, "There's at least one shape in the job that is not supported on the SPU. The job has to therefore move to the PPU. Performance loss likely. Consider moving the unsupported shape(s) into a separate job.");
				return hkJobQueue::JOB_TYPE_CPU;
			}
		}
	}

	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#else
	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#endif
}
#endif


// ===============================================================================================================================================================================================
//  WORLD GET CLOSEST POINTS
// ===============================================================================================================================================================================================

#if !defined(HK_PLATFORM_SPU)
hkJobQueue::JobType hkpWorldGetClosestPointsJob::getJobType()
{
#if defined (HK_PLATFORM_HAS_SPU)
	if ( m_broadphase->getType() != hkpBroadPhase::BROADPHASE_16BIT )
	{
		HK_WARN_ONCE(0xaf35e145, "Only 16bit broadphase supported on SPU. Moving job onto PPU. Performance loss likely.");
		return hkJobQueue::JOB_TYPE_CPU;
	}

	const hkp3AxisSweep* broadphase = reinterpret_cast<const hkp3AxisSweep*>( m_broadphase );

	int totalStackMemNeededByBroadphaseOnSpu;
	{
		int sizeBroadphaseNodesArray = HK_NEXT_MULTIPLE_OF(128, broadphase->m_nodes.getSize() * sizeof(hkp3AxisSweep::hkpBpNode));
		int sizeXAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(128, broadphase->m_axis[0].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		int sizeYAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(128, broadphase->m_axis[1].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		int sizeZAxisEndPointsArray  = HK_NEXT_MULTIPLE_OF(128, broadphase->m_axis[2].m_endPoints.getSize() * sizeof(hkp3AxisSweep::hkpBpEndPoint));
		totalStackMemNeededByBroadphaseOnSpu = sizeBroadphaseNodesArray + sizeXAxisEndPointsArray + sizeYAxisEndPointsArray + sizeZAxisEndPointsArray;
	}

	if ( totalStackMemNeededByBroadphaseOnSpu > HK_SPU_COLLIDE_MOPP_CACHE_SIZE )
	{
		HK_WARN_ONCE(0xaf35e142, "Broadphase too big to fit into SPU stack buffer. Moving job onto PPU. Performance loss likely.");
		return hkJobQueue::JOB_TYPE_CPU;
	}

	{
		for (int commandIdx = 0; commandIdx < m_numCommands; commandIdx++)
		{
			const hkpWorldGetClosestPointsCommand* command = &m_commandArray[commandIdx];
			if ( command->m_collidable->m_forceCollideOntoPpu != 0 )
			{
				HK_WARN_ONCE(0xaf15e143, "There's at least one shape in the job that is not supported on the SPU. The job has to therefore move to the PPU. Performance loss likely. Consider moving the unsupported shape(s) into a separate job.");
				return hkJobQueue::JOB_TYPE_CPU;
			}
		}
	}

	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#else
	return hkJobQueue::JOB_TYPE_HINT_SPU_CQ;
#endif
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
