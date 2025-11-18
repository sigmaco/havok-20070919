/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/Memory/Pool/hkPoolMemory.h>
#include <Common/Base/Monitor/Spu/hkSpuMonitorCache.h>
#include <Common/Base/Memory/PlattformUtils/Spu/SpuStack/hkSpuStack.h>
#include <Common/Base/Spu/Util/hkSpuUtil.h>

#include <Physics/Collide/Query/Multithreaded/Spu/hkpSpuConfig.h>
#include <Physics/Collide/Query/Multithreaded/Spu/hkpSpuCollisionQueryJobDispatcher.h>
#include <Physics/Collide/Query/Multithreaded/hkpCollisionJobs.h>
#include <Physics/Collide/Query/Multithreaded/hkpCollisionQueryJobData.h>

#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Collide/Shape/Convex/PackedConvexVertices/hkpPackedConvexVerticesShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Collection/ExtendedMeshShape/hkpExtendedMeshShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppEmbeddedShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>

#include <Physics/Collide/Query/Multithreaded/Spu/hkpSpuCollisionQuery.h>


static HK_ALIGN( char jobDataBuf[sizeof(hkpCollisionQueryJobData)], 128 );

static HK_ALIGN( char queueBuf[sizeof(hkJobQueue)], 128 );


void HK_CALL hkSpuCollisionQuery( const hkSpuTaskParams& taskParams, char* stackBuffer, int stackBufferSize )
{
	HK_SPU_INIT_STACK_SIZE_TRACE();

	const void* jobDataPpuAddress = taskParams.m_param0;
	const void* queueAddress = taskParams.m_param1;
	void* monitorCacheAddress = taskParams.m_param2;

	// Set up the SPU "stack". This should be as big as possible.
	hkSpuStack::getInstance().initMemory(stackBuffer, stackBufferSize);

	//
	//	shapes
	//
	{
		hkpShape						::resetShapeFunctions();

		hkpShape::ShapeFuncs reg;
		hkpBoxShape					::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_BOX,      reg );

		hkpTriangleShape			::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_TRIANGLE, reg );
		hkpSphereShape				::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_SPHERE,   reg );

		hkpCapsuleShape				::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_CAPSULE,  reg );
		hkpCylinderShape			::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_CYLINDER, reg );
		hkpListShape				::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_LIST				, reg );
		hkpConvexTranslateShape		::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_CONVEX_TRANSLATE	, reg );
		hkpConvexTransformShape		::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_CONVEX_TRANSFORM	, reg );
		hkpMoppEmbeddedShape		::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_MOPP_EMBEDDED		, reg );
		hkpMoppBvTreeShape			::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_MOPP				, reg );
		hkpExtendedMeshShape		::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_EXTENDED_MESH		, reg );
		hkpConvexVerticesShape		::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_CONVEX_VERTICES	, reg );
		hkpPackedConvexVerticesShape::registerCollideQueryFunctions( reg  ); hkpShape::setShapeFunctions( HK_SHAPE_PACKED_CONVEX_VERTICES, reg );
	}

	//
	// bring in some 'persistent' job data
	//
	hkpCollisionQueryJobData* jobData;
	{
		HK_CHECK_ALIGN16(jobDataPpuAddress);
		hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion( &jobDataBuf, (const void*)hkUlong(jobDataPpuAddress), sizeof(hkpCollisionQueryJobData), hkSpuDmaManager::READ_COPY );
		HK_SPU_DMA_PERFORM_FINAL_CHECKS( (const void*)hkUlong(jobDataPpuAddress), &jobDataBuf, sizeof(hkpCollisionQueryJobData));
		jobData = (hkpCollisionQueryJobData*)&jobDataBuf;
	}

	//
	// Dma the job queue
	//
	hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion( &queueBuf, (const void*)hkUlong(queueAddress), sizeof(hkJobQueue), hkSpuDmaManager::READ_COPY );
	hkSpuDmaManager::performFinalChecks( (const void*)hkUlong(queueAddress), &queueBuf, sizeof(hkJobQueue));
	hkJobQueue* queue = (hkJobQueue*)&queueBuf;

	// Initialize the monitors to point to the local buffers
	hkSpuMonitorCache::initMonitorsSpu( monitorCacheAddress, HK_ELF_TYPE_COLLISION_QUERY );

	// Process collision queries. This call will return once there are no jobs left on the queue.
	hkSpuProcessNextCollisionQueryJob( *queue, jobData, hkJobQueue::DO_NOT_WAIT_FOR_NEXT_JOB );

	// Make sure that all monitor data has been written back to ppu.
	hkSpuMonitorCache::finalizeMonitorsSpu( monitorCacheAddress );

	// Signal the ppu that this spu thread has finished.
	hkSemaphoreBusyWait::release(queue->m_taskCompletionSemaphore);
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
