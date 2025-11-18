/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>

#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>

#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandlePair.h>
#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/Util/hkpWorldAgentUtil.h>

#include <Physics/Dynamics/World/Util/BroadPhase/hkpEntityEntityBroadPhaseListener.h>

hkpEntityEntityBroadPhaseListener::hkpEntityEntityBroadPhaseListener( hkpWorld* world)
{
	m_world = world;
}

void hkpEntityEntityBroadPhaseListener::addCollisionPair( hkpTypedBroadPhaseHandlePair& pair )
{
	hkpLinkedCollidable* collA = static_cast<hkpLinkedCollidable*>( static_cast<hkpTypedBroadPhaseHandle*>(pair.m_a)->getOwner() );
	hkpLinkedCollidable* collB = static_cast<hkpLinkedCollidable*>( static_cast<hkpTypedBroadPhaseHandle*>(pair.m_b)->getOwner() );

	// check for disabled collisions, especially landscape = landscape ones
	hkpProcessCollisionInput* input = m_world->getCollisionInput();
	{
		hkpCollidableQualityType qt0 = collA->getQualityType();
		hkpCollidableQualityType qt1 = collB->getQualityType();
		hkChar collisionQuality = input->m_dispatcher->getCollisionQualityIndex( qt0, qt1 );
		if ( collisionQuality == hkpCollisionDispatcher::COLLISION_QUALITY_INVALID )
		{
			return;
		}
		hkpCollisionQualityInfo* origInfo = input->m_dispatcher->getCollisionQualityInfo( collisionQuality );
		input->m_createPredictiveAgents = origInfo->m_useContinuousPhysics;
	}
	hkpWorldAgentUtil::addAgent(collA, collB, *input);
}


void hkpEntityEntityBroadPhaseListener::removeCollisionPair( hkpTypedBroadPhaseHandlePair& pair )
{
	hkpLinkedCollidable* collA = static_cast<hkpLinkedCollidable*>( static_cast<hkpTypedBroadPhaseHandle*>(pair.m_a)->getOwner() );
	hkpLinkedCollidable* collB = static_cast<hkpLinkedCollidable*>( static_cast<hkpTypedBroadPhaseHandle*>(pair.m_b)->getOwner() );

	hkpAgentNnEntry* entry = hkAgentNnMachine_FindAgent(collA, collB);

	if (entry)
	{
		hkpWorldAgentUtil::removeAgent(entry);
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
