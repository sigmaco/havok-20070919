/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>

#include <Physics/Dynamics/Entity/hkpEntity.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/Util/hkpWorldAgentUtil.h>

#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>

#include <Physics/Utilities/Collide/Filter/constraint/hkpConstraintCollisionFilter.h>


#if !defined(HK_PLATFORM_SPU)

hkpConstraintCollisionFilter::hkpConstraintCollisionFilter(const hkpCollisionFilter* childFilter) : hkpPairCollisionFilter(childFilter) 
{
	m_type = HK_FILTER_CONSTRAINT;
}

hkpConstraintCollisionFilter::~hkpConstraintCollisionFilter()
{
}

#endif


#if !defined(HK_PLATFORM_SPU)

void hkpConstraintCollisionFilter::updateFromWorld(hkpWorld* world)
{
	m_disabledPairs.clear();

	{
		// The first iteration will process all active islands.
		const hkArray<hkpSimulationIsland*>* islands = &world->getActiveSimulationIslands();

		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < islands->getSize(); i++ )
			{
				hkpSimulationIsland* island = (*islands)[i];
				for (int b = 0; b < island->getEntities().getSize(); b++ )
				{
					hkpEntity* body =  island->getEntities()[b];

					int numConstraints = body->getNumConstraints();
					{
						for (int c = 0; c < numConstraints; c++)
						{
							constraintAddedCallback(body->getConstraint(c));
						}
					}
				}
			}

			// The second iteration will process all inactive islands.
			islands = &world->getInactiveSimulationIslands();
		}
	}
}


void hkpConstraintCollisionFilter::constraintAddedCallback( hkpConstraintInstance* constraint )
{
	if ( constraint && (constraint->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_CONTACT) )
	{
		hkpEntity* entityA = constraint->getEntityA();
		hkpEntity* entityB = constraint->getEntityB();
		int count = disableCollisionsBetween(entityA, entityB);

		// Only remove the agent if this was the first constraint.
		if ( count == 1 )
		{
			// Check if there is an agent connecting the two bodies, if so remove the agent
			hkpAgentNnEntry* entry = hkAgentNnMachine_FindAgent( constraint->getEntityA()->getLinkedCollidable(), constraint->getEntityB()->getLinkedCollidable() );

			if (entry)
			{
				hkpWorldAgentUtil::removeAgentAndItsToiEvents(entry);
			}
		}
	}
}


void hkpConstraintCollisionFilter::constraintRemovedCallback( hkpConstraintInstance* constraint )
{
	if ( constraint && (constraint->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_CONTACT) )
	{
		hkpEntity* entityA = constraint->getEntityA();
		hkpEntity* entityB = constraint->getEntityB();
		enableCollisionsBetween(entityA, entityB);
	}
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
