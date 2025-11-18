/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>

#include <Physics/Utilities/Collide/Filter/ConstrainedSystem/hkpConstrainedSystemFilter.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Physics/Dynamics/Constraint/hkpConstraintData.h>

#include <Physics/Dynamics/World/Util/hkpWorldAgentUtil.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>

#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhaseHandlePair.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseDispatcher.h>
#include <Physics/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandlePair.h>

#include <Physics/Collide/Filter/Null/hkpNullCollisionFilter.h>

hkpConstrainedSystemFilter::hkpConstrainedSystemFilter (const hkpCollisionFilter* otherFilter) : m_otherFilter (otherFilter) 
{ 
	HK_WARN_ONCE(0xaf351fe4, "hkpConstrainedSystemFilter is deprecated, please switch to hkutilities/collide/filter/pair/hkpConstraintCollisionFilter instead. hkpConstrainedSystemFilter will be removed for the final 5.0 release.");

	if (m_otherFilter) 
	{
		m_otherFilter->addReference();
	}
}

hkpConstrainedSystemFilter::~hkpConstrainedSystemFilter()
{
	if (m_otherFilter) 
	{
		m_otherFilter->removeReference();
	}
}

hkBool hkpConstrainedSystemFilter::isCollisionEnabled( const hkpCollidable& a, const hkpCollidable& b ) const
{
	hkpRigidBody* rigidBodyA = hkGetRigidBody(&a);
	hkpRigidBody* rigidBodyB = hkGetRigidBody(&b);

	if (m_otherFilter && !m_otherFilter->isCollisionEnabled(a,b))
	{
		return false;
	}

	if (! rigidBodyA || ! rigidBodyB)
	{
		return true;
	}

	// Look for the rigid body (thisRigidBody) with fewer constraints
	// (that way the loop below is faster)
	
	const hkBool isABigger = (rigidBodyA->getNumConstraints() > rigidBodyB->getNumConstraints());
	const hkpRigidBody* thisRigidBody = isABigger ? rigidBodyB : rigidBodyA;
	const hkpRigidBody* otherRigidBody = isABigger ? rigidBodyA : rigidBodyB; 

	const int numConstraints = thisRigidBody->getNumConstraints();

	for (int c = 0; c < numConstraints; c++)
	{
		const hkpConstraintInstance* constraint = thisRigidBody->getConstraint(c);

		if ((constraint) &&
			(constraint->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_CONTACT) && 
			(
				(constraint->getEntityA()==(hkpEntity*)otherRigidBody)  || 
				(constraint->getEntityB()==(hkpEntity*)otherRigidBody) 
			))
		{
			return false;
		}
	}

	return true;
}

hkBool hkpConstrainedSystemFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const hkpShapeContainer& bContainer, hkpShapeKey bKey  ) const  
{	
	return !m_otherFilter || m_otherFilter->isCollisionEnabled (input, a, b, bContainer, bKey);
}

// hkpShapeCollectionFilter interface forwarding
hkBool hkpConstrainedSystemFilter::isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& collectionBodyA, const hkpCdBody& collectionBodyB, const HK_SHAPE_CONTAINER& containerShapeA, const HK_SHAPE_CONTAINER& containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB ) const
{
	return !m_otherFilter || m_otherFilter->isCollisionEnabled (input, collectionBodyA, collectionBodyB, containerShapeA, containerShapeB, keyA, keyB);
}


hkBool hkpConstrainedSystemFilter::isCollisionEnabled( const hkpShapeRayCastInput& aInput, const hkpShape& shape, const hkpShapeContainer& bContainer, hkpShapeKey bKey ) const  
{	
	return !m_otherFilter || m_otherFilter->isCollisionEnabled (aInput, shape, bContainer, bKey);
}

hkBool hkpConstrainedSystemFilter::isCollisionEnabled( const hkpWorldRayCastInput& a, const hkpCollidable& collidableB ) const  
{	
	return !m_otherFilter || m_otherFilter->isCollisionEnabled (a, collidableB);
}


void hkpConstrainedSystemFilter::constraintAddedCallback( hkpConstraintInstance* constraint )
{
	if (constraint->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_CONTACT)
	{
		// Check if there is an agent connecting the two bodies, if so remove the agent
		hkpAgentNnEntry* entry = hkAgentNnMachine_FindAgent( constraint->getEntityA()->getLinkedCollidable(), constraint->getEntityB()->getLinkedCollidable() );

		if (entry)
		{
			hkpWorldAgentUtil::removeAgentAndItsToiEvents(entry);
		}
	}
}

void hkpConstrainedSystemFilter::constraintRemovedCallback( hkpConstraintInstance* constraint )
{
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
