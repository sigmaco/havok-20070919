/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Collide/Callback/Dispatch/hkpSpuCollisionCallbackUtil.h>
#include <Physics/Dynamics/World/hkpWorld.h>


hkSpuCollisionCallbackUtil* hkSpuCollisionCallbackUtil::createSpuCollisionCallbackUtil(int totalSizeOfUtil)
{
	HK_ASSERT2(0xaf351238, !(totalSizeOfUtil & 0xf), "Utility size has to be a multiple of 16.");
	HK_ASSERT2( 0xf032de45, totalSizeOfUtil < 0x100000, "The size of this utility is limited to 1mb." );

	hkSpuCollisionCallbackUtil* util = reinterpret_cast<hkSpuCollisionCallbackUtil*>( hkThreadMemory::getInstance().allocateChunk(totalSizeOfUtil, HK_MEMORY_CLASS_DYNAMICS) );
	new (util) hkSpuCollisionCallbackUtil();
	{
		util->m_referenceCount	= 1;
		util->m_memSizeAndFlags	= hkUint16(totalSizeOfUtil);
		util->m_capacity		= (totalSizeOfUtil - sizeof(hkSpuCollisionCallbackUtil) + sizeof(Event)) >> 4;
		util->m_nextFreeEvent	= &util->m_events[0];
	}

	return util;
}


void hkSpuCollisionCallbackUtil::fireCallbacks(hkpWorld* world, Callbacks* m_callbacks, ResetEventQueue resetFlag)
{
	HK_ACCESS_CHECK_OBJECT(world, HK_ACCESS_RW);

	Event* event = &m_events[0];

	hkUlong endOfBuffer = hkUlong(hkAddByteOffset(&m_events[0], m_capacity*16));

	while ( hkUlong(event) < hkUlong(m_nextFreeEvent) )
	{
		// We need to abort if the event is located exactly on the buffer's end. This can happen if the last event
		// did perfectly fit into the remaining buffer space. In that case this current event was never actually written
		// back from SPU while the m_nextFreeEvent pointer would still have been incremented (and thus the above
		// while() wouldn't have aborted yet). Note: The '>' check should never actually fire; it's just there for
		// safety reasons. ;)
		if ( hkUlong(event) >= endOfBuffer )
		{
			break;
		}

		HK_ASSERT2(0xaf4351fe, event->m_size > 0, "Event size should never be 0. Event queue data might be corrupted.");

		// we need to abort once we would spill over the buffer's end (as m_nextFreeEvent can point to memory
		// beyond the buffer's end!)
		if ( hkUlong(hkAddByteOffset(event, event->m_size)) > endOfBuffer )
		{
			HK_WARN_ONCE( 0xf0fe5676, "Buffer overflow in hkSpuCollisionCallbackUtil" );
			break;
		}

		if ( event->m_type == Event::CONTACT_POINT_ADDED )
		{
			ContactPointAddedEvent* cpae = static_cast<ContactPointAddedEvent*>( event );
			m_callbacks->contactPointAddedCallbackFromSpu(cpae);
		}
		else if ( event->m_type == Event::CONTACT_POINT_PROCESS )
		{
			ContactPointProcessEvent* cppe = static_cast<ContactPointProcessEvent*>( event );
			m_callbacks->contactPointProcessCallbackFromSpu(cppe);
		}
		else if ( event->m_type == Event::CONTACT_POINT_REMOVED )
		{
			ContactPointRemovedEvent* cpre = static_cast<ContactPointRemovedEvent*>( event );
			m_callbacks->contactPointRemovedCallbackFromSpu(cpre);
		}
#if defined(HK_DEBUG)
		else
		{
			HK_ASSERT2(0xaf4351fd, false, "Invalid event type. Event queue data might be corrupted.");
		}
#endif

		event = hkAddByteOffset(event, event->m_size);
	}

	// reset buffer
	if ( resetFlag == RESET_EVENT_QUEUE )
	{
		m_nextFreeEvent = &m_events[0];
	}
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
