/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Memory/PlattformUtils/Spu/SpuStack/hkSpuStack.h>
#include <Common/Base/Memory/PlattformUtils/Spu/SpuDmaCache/hkSpu4WayCache.h>

#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Collide/Filter/Group/hkpGroupFilter.h>
#include <Physics/Dynamics/Collide/Callback/Dispatch/hkpSpuCollisionCallbackUtil.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/Simulation/Multithreaded/Spu/hkpSpuConfig.h>
#include <Physics/Dynamics/Collide/Callback/Dispatch/hkpCollideCallbackDispatcher.h>
#include <Physics/Utilities/Destruction/BrakeOffParts/hkpBreakOffPartsUtil.h>
#include <Physics/Utilities/Destruction/BrakeOffParts/hkpBreakOffPartsUtilSpu.inl>


void hkSpuCollisionCallbackUtil::registerSpuFunctions()
{
	registerCallbackFunctions( contactPointAddedEvent, contactPointProcessEvent, contactPointRemovedEvent, shapeContainerIsCollisionEnabled, shapeContainer2IsCollisionEnabled, numShapeKeyHitsLimitBrached );
}


void hkSpuCollisionCallbackUtil::writeBackEvent(hkpEntity* entity, const Event& event)
{
	hkSpuCollisionCallbackUtil* utilOnPpu = entity->m_spuCollisionCallback.m_util;

	int eventSize = event.m_size;

	// get the ppu address for the next free event and increase it on ppu by this event's size
	void* nextFreeEventOnPpu	= (void*)(hkUlong(hkSpuDmaManager::atomicExchangeAdd((hkUint32*)&utilOnPpu->m_nextFreeEvent, eventSize)));
	void* endOfBuffer			= hkAddByteOffset(&utilOnPpu->m_events[0], entity->m_spuCollisionCallback.m_capacity*16);

	// only write anything if we have at least 16 bytes available
	if ( nextFreeEventOnPpu < endOfBuffer )
	{

		// if the new event will not fit into the remaining free buffer in the utility we will simply write back its 'header' (i.e. the first 16 bytes which include the
		// event's total size). This will serve as an end marker while processing the event on the ppu.
		if ( hkAddByteOffset(nextFreeEventOnPpu, eventSize) > endOfBuffer )
		{
			HK_ASSERT(0xaf35ef12, (hkUlong(endOfBuffer) - hkUlong(nextFreeEventOnPpu)) >= 16);
			eventSize = 16;
		}

		// write back event to previous free event address (using the default dma group)
		{
			hkSpuDmaManager::putToMainMemory        (nextFreeEventOnPpu, &event, eventSize, hkSpuDmaManager::WRITE_NEW);
			HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT(nextFreeEventOnPpu, &event, eventSize);
		}
	}
}


extern hkpEntity* g_spuCollisionEventsEntityAOnPpu;
extern hkpEntity* g_spuCollisionEventsEntityBOnPpu;
extern hkpEntity* g_spuCollisionEventsEntityAOnSpu;
extern hkpEntity* g_spuCollisionEventsEntityBOnSpu;
extern hkpDynamicsContactMgr* g_spuCollisionEventsContactMgrOnPpu;

inline void setEntities( hkpEntity* entityA, hkpEntity* entityB, hkSpuCollisionCallbackUtil::Event& event)
{
	bool flipped = g_spuCollisionEventsEntityAOnSpu != entityA;
	if (flipped)
	{
		event.m_entityA				= g_spuCollisionEventsEntityBOnPpu;
		event.m_entityB				= g_spuCollisionEventsEntityAOnPpu;
	}
	else
	{
		event.m_entityA				= g_spuCollisionEventsEntityAOnPpu;
		event.m_entityB				= g_spuCollisionEventsEntityBOnPpu;
	}
}

// This function is only called from hkFireContactPointAddedCallback() during a callback event on SPU.
void hkSpuCollisionCallbackUtil::contactPointAddedEvent(hkpEntity* entityA, hkpEntity* entityB, hkpContactPointAddedEvent& eventIn)
{
	//
	//	Do the break off parts check
	//
	if ( hkUlong(entityA->m_breakOffPartsUtil) | hkUlong(entityB->m_breakOffPartsUtil) )
	{
		hkpBreakOffPartsUtil::LimitContactImpulseUtil::contactPointAddedCallbackSpu( entityA, entityB, eventIn );
	}


	//
	// immediately abort if none of the entities have a callback utility registered
	//
	if ( 0 == (hkUlong(entityA->m_spuCollisionCallback.m_util) | hkUlong(entityB->m_spuCollisionCallback.m_util)) )
	{
		return;
	}

	//
	// only write event if at least one of the callback utilities has the flag for contactPointAdded events set
	//
	int addedBitA;
	int addedBitB;
	{
		addedBitA = entityA->m_spuCollisionCallback.m_eventFilter & hkpEntity::SPU_SEND_CONTACT_POINT_ADDED;
		addedBitB = entityB->m_spuCollisionCallback.m_eventFilter & hkpEntity::SPU_SEND_CONTACT_POINT_ADDED;
		if ( 0 == (addedBitA | addedBitB) )
		{
			return;
		}
	}

	//
	// only write event if at least one matching bit is set in both filters
	//
	{
		if ( !(entityA->m_spuCollisionCallback.m_userFilter & entityB->m_spuCollisionCallback.m_userFilter) )
		{
			return;
		}
	}


	//
	// setup the local event data
	//
	ContactPointAddedEvent event;
	{
		event.m_size				= sizeof(ContactPointAddedEvent);
		event.m_type				= Event::CONTACT_POINT_ADDED;
		setEntities( entityA, entityB, event );
		event.m_projectedVelocity	= eventIn.m_projectedVelocity;
		event.m_contactPoint		= *eventIn.m_contactPoint;
		event.m_shapeKeyA			= eventIn.m_bodyA->getShapeKey();
		event.m_shapeKeyB			= eventIn.m_bodyB->getShapeKey();

		event.m_contactMgr			= g_spuCollisionEventsContactMgrOnPpu;
		event.m_contactId			= hkContactPointId(-1);
		if (!eventIn.isToi())
		{
			event.m_contactId		= eventIn.asManifoldEvent().m_contactPointId;
		}
	}

	//
	// write back the event into the event queues on ppu
	//
	{
		if ( entityA->m_spuCollisionCallback.m_util && addedBitA )
		{
			hkSpuCollisionCallbackUtil::writeBackEvent(entityA, event);
		}
		if ( entityB->m_spuCollisionCallback.m_util && entityB->m_spuCollisionCallback.m_util != entityA->m_spuCollisionCallback.m_util && addedBitB )
		{
			hkSpuCollisionCallbackUtil::writeBackEvent(entityB, event);
		}
		hkSpuDmaManager::waitForDmaCompletion(); // wait for default dma group
	}
}


// This function is only called from hkFireContactProcessCallback() during a callback event on SPU.
void hkSpuCollisionCallbackUtil::contactPointProcessEvent(hkpEntity* entityA, hkpEntity* entityB, hkpContactProcessEvent& eventIn)
{
	//
	// immediately abort of none of the entities have a callback utility registered
	//
	if ( 0 == (hkUlong(entityA->m_spuCollisionCallback.m_util) | hkUlong(entityB->m_spuCollisionCallback.m_util)) )
	{
		return;
	}

	//
	// only write event if at least one of the callback utilities has the flag for contactPointProcess events set
	//
	int processBitA;
	int processBitB;
	{
		processBitA = entityA->m_spuCollisionCallback.m_eventFilter & hkpEntity::SPU_SEND_CONTACT_POINT_PROCESS;
		processBitB = entityB->m_spuCollisionCallback.m_eventFilter & hkpEntity::SPU_SEND_CONTACT_POINT_PROCESS;
		if ( 0 == (processBitA | processBitB) )
		{
			return;
		}
	}

	//
	// only write event if at least one matching bit is set in both filters
	//
	{
		if ( !(entityA->m_spuCollisionCallback.m_userFilter & entityB->m_spuCollisionCallback.m_userFilter) )
		{
			return;
		}
	}

	//
	// setup the local event data
	//
	ContactPointProcessEvent* event;
	{
		hkpProcessCollisionData* collisionData = eventIn.m_collisionData;
		int numContactPoints = collisionData->getNumContactPoints();

		// allocate a temporary copy of the event data on the local spu stack
		int sizeOfEventData = sizeof(ContactPointProcessEvent) + (numContactPoints-1) * sizeof(ContactPointProcessEvent::ContactPoint);
		event = reinterpret_cast<ContactPointProcessEvent*>( hkSpuStack::getInstance().allocateStack( HK_NEXT_MULTIPLE_OF(128, sizeOfEventData), "hkSpuCollisionCallbackUtil::ContactPointProcessEvent") );

		//
		// fill in the event data
		//
		{
			event->m_size				= hkUint16(sizeOfEventData);
			event->m_type				= Event::CONTACT_POINT_PROCESS;
			event->m_entityA			= g_spuCollisionEventsEntityAOnPpu;
			event->m_entityB			= g_spuCollisionEventsEntityBOnPpu;
			event->m_contactMgr			= g_spuCollisionEventsContactMgrOnPpu;
			event->m_numContactPoints	= numContactPoints;
			{
				hkpProcessCdPoint* cpSrc  = &collisionData->m_contactPoints[0];
				hkContactPoint*	  cpDest = &event->m_contactPoints[0];
				for (int i = 0; i < numContactPoints; i++)
				{
					cpDest[0] = cpSrc->m_contact;
					cpDest->getPosition().setInt24W(cpSrc->m_contactPointId);
					cpSrc  = hkAddByteOffset(cpSrc,  sizeof(hkpProcessCdPoint));
					cpDest = hkAddByteOffset(cpDest, sizeof(ContactPointProcessEvent::ContactPoint));
				}
			}
		}
	}

	//
	// write back the event into the event queues on ppu
	//
	{
		if ( entityA->m_spuCollisionCallback.m_util && processBitA )
		{
			hkSpuCollisionCallbackUtil::writeBackEvent(entityA, *event);
		}
		if ( entityB->m_spuCollisionCallback.m_util && entityB->m_spuCollisionCallback.m_util != entityA->m_spuCollisionCallback.m_util && processBitB )
		{
			hkSpuCollisionCallbackUtil::writeBackEvent(entityB, *event);
		}
		hkSpuDmaManager::waitForDmaCompletion(); // wait for default dma group
	}

	// free the temporary copy of the event data
	hkSpuStack::getInstance().deallocateStack(event);
}


// This function is only called from hkFireContactPointRemovedCallback() during a callback event on SPU.
void hkSpuCollisionCallbackUtil::contactPointRemovedEvent(hkpEntity* entityA, hkpEntity* entityB, hkpContactPointRemovedEvent& eventIn)
{
	//
	// immediately abort of none of the entities have a callback utility registered
	//
	if ( 0 == (hkUlong(entityA->m_spuCollisionCallback.m_util) | hkUlong(entityB->m_spuCollisionCallback.m_util)) )
	{
		return;
	}

	//
	// only write event if at least one of the callback utilities has the flag for contactPointRemoved events set
	//
	int removedBitA;
	int removedBitB;
	{
		removedBitA = entityA->m_spuCollisionCallback.m_eventFilter & hkpEntity::SPU_SEND_CONTACT_POINT_REMOVED;
		removedBitB = entityB->m_spuCollisionCallback.m_eventFilter & hkpEntity::SPU_SEND_CONTACT_POINT_REMOVED;
		if ( 0 == (removedBitA | removedBitB) )
		{
			return;
		}
	}

	//
	// only write event if at least one matching bit is set in both filters
	//
	{
		if ( !(entityA->m_spuCollisionCallback.m_userFilter & entityB->m_spuCollisionCallback.m_userFilter) )
		{
			return;
		}
	}

	//
	// setup the local event data
	//
	ContactPointRemovedEvent event;
	{
		event.m_size			= sizeof(ContactPointRemovedEvent);
		event.m_type			= Event::CONTACT_POINT_REMOVED;
		event.m_entityA			= g_spuCollisionEventsEntityAOnPpu;
		event.m_entityB			= g_spuCollisionEventsEntityBOnPpu;
		event.m_contactMgr		= g_spuCollisionEventsContactMgrOnPpu;
		event.m_contactPointId	= eventIn.m_contactPointId;
	}

	//
	// write back the event into the event queues on ppu
	//
	{
		if ( entityA->m_spuCollisionCallback.m_util && removedBitA )
		{
			hkSpuCollisionCallbackUtil::writeBackEvent(entityA, event);
		}
		if ( entityB->m_spuCollisionCallback.m_util && entityB->m_spuCollisionCallback.m_util != entityA->m_spuCollisionCallback.m_util && removedBitB )
		{
			hkSpuCollisionCallbackUtil::writeBackEvent(entityB, event);
		}
		hkSpuDmaManager::waitForDmaCompletion(); // wait for default dma group
	}
}


hkBool HK_CALL hkSpuCollisionCallbackUtil::shapeContainerIsCollisionEnabled(const hkpProcessCollisionInput* input, const hkpCdBody* bodyA, const hkpCdBody* bodyB, const HK_SHAPE_CONTAINER* shapeCollectionB, hkpShapeKey shapeKeyB)
{
	//
	// we currently bring in a full cache line of hkpCollisionFilter data; this might cause an out-of-bounds access error on ppu
	//
	// sf.todo.aa bring in the filter at the beginning of the agent job
	const hkpCollisionFilter* filterOnPpu = static_cast<const hkpCollisionFilter*>(input->m_filter.val());
	const hkpCollisionFilter* filter = reinterpret_cast<const hkpCollisionFilter*> ( g_SpuCollideUntypedCache->getFromMainMemory(filterOnPpu, HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE) );

	//
	// handle group filters
	//
	if ( filter->m_type == hkpCollisionFilter::HK_FILTER_GROUP )
	{
		const hkpGroupFilter* groupFilter = static_cast<const hkpGroupFilter*>( filter );
		return groupFilter->hkpGroupFilter::isCollisionEnabled( *input, *bodyA, *bodyB, *shapeCollectionB, shapeKeyB );
	}
	return true;
}

hkBool HK_CALL hkSpuCollisionCallbackUtil::shapeContainer2IsCollisionEnabled(const hkpProcessCollisionInput* input, const hkpCdBody* bodyA, const hkpCdBody* bodyB, const HK_SHAPE_CONTAINER* shapeCollectionA, const HK_SHAPE_CONTAINER* shapeCollectionB, hkpShapeKey shapeKeyA, hkpShapeKey shapeKeyB)
{
	//
	// we currently bring in a full cache line of hkpCollisionFilter data; this might cause an out-of-bounds access error on ppu
	//
	const hkpCollisionFilter* filterOnPpu = static_cast<const hkpCollisionFilter*>(input->m_filter.val());
	const hkpCollisionFilter* filter = reinterpret_cast<const hkpCollisionFilter*> ( g_SpuCollideUntypedCache->getFromMainMemory(filterOnPpu, HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE) );

	//
	// handle group filters
	//
	if ( filter->m_type == hkpCollisionFilter::HK_FILTER_GROUP )
	{
		const hkpGroupFilter* groupFilter = static_cast<const hkpGroupFilter*>( filter );
		return groupFilter->hkpGroupFilter::isCollisionEnabled( *input, *bodyA, *bodyB, *shapeCollectionA, *shapeCollectionB, shapeKeyA, shapeKeyB );
	}
	return true;
}

int HK_CALL hkSpuCollisionCallbackUtil::numShapeKeyHitsLimitBrached( const hkpProcessCollisionInput* input, 
											   const hkpCdBody* bodyA, const hkpCdBody* bodyB, 
											   const hkpBvTreeShape* bvTreeShapeB, hkAabb& aabb,
											   hkpShapeKey* shapeKeysInOut,
											   int shapeKeysCapacity)
{
	// Default: do nothing. Return all shapes back.
	return shapeKeysCapacity;
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
