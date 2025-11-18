/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>

#include <Physics/Dynamics/Phantom/hkpPhantomType.h>
#include <Physics/Dynamics/Phantom/hkpShapePhantom.h>
#include <Physics/Collide/Agent/hkpCollisionInput.h>
#include <Physics/Collide/Agent/Query/hkpLinearCastCollisionInput.h>
#include <Physics/Collide/Agent/Query/hkpCdPointCollector.h>
#include <Physics/Collide/Agent/hkpCollisionAgent.h>
#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>
#include <Physics/Dynamics/World/Util/hkpWorldOperationQueue.h>
#include <Physics/Dynamics/World/Util/hkpWorldCallbackUtil.h>

hkpShapePhantom::hkpShapePhantom( const hkpShape* shape, const hkTransform& transform )
	: hkpPhantom( shape )
{
	HK_ASSERT2(0xad65bbd5, m_collidable.getShape(), "hkShapePhantoms must be created with non-null shapes.");
	
	hkpCollidable* collidable = getCollidableRw();
	
	collidable->setMotionState( &m_motionState );

	// Note that tims are disabled. (The default motion state constructor disables tims).

	m_motionState.getTransform() = transform;
}

hkMotionState* hkpShapePhantom::getMotionState()
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RO );
	return &m_motionState;
}




void hkpShapePhantom::setTransform( const hkTransform& transform )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RW, this, HK_ACCESS_RW );
	// re: HVK-2304 check for normalised Tr in hkpShapePhantom::setTransform
	HK_ASSERT2(0xad6bd8ad, transform.getRotation().isOrthonormal(), "The rotation of the transform passed to hkpShapePhantom::setTransform() is not orthonormal.");
	m_motionState.getTransform() = transform;

	if ( m_world != HK_NULL )
	{
		hkAabb aabb;
		hkReal halfTolerance = 0.5f * m_world->getCollisionInput()->getTolerance();
		m_collidable.getShape()->getAabb( transform, halfTolerance, aabb );
		updateBroadPhase( aabb );
	}
}

void hkpShapePhantom::setPosition( const hkVector4& position, hkReal extraTolerance )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RW, this, HK_ACCESS_RW );
	m_motionState.getTransform().setTranslation( position );

	if (m_world != HK_NULL)
	{
		hkAabb aabb;
		hkReal halfTolerance = 0.5f * m_world->getCollisionInput()->getTolerance();
		m_collidable.getShape()->getAabb( m_motionState.getTransform(), halfTolerance + extraTolerance, aabb );
		updateBroadPhase( aabb );
	}
}


// Get the current aabb
void hkpShapePhantom::calcAabb( hkAabb& aabb )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RO );
	HK_ASSERT2(0xad65bbd4, m_collidable.getShape(), "hkShapePhantoms must be created with non-null shapes.");
	HK_ASSERT2(0x525a9acd,  m_world, "You can only call calcAabb, after the phantom has been added to the world");
	hkReal halfTolerance = 0.5f * m_world->getCollisionInput()->getTolerance();
	m_collidable.getShape()->getAabb( m_motionState.getTransform(), halfTolerance, aabb );
}

void hkpShapePhantom::deallocateInternalArrays()
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW );
	// Need to deallocate any arrays that are 0 size
	// else warn user that they should call the in place destructor

	// No arrays are allocated, just pass on to parent.
	hkpPhantom::deallocateInternalArrays();
}

hkWorldOperation::Result hkpShapePhantom::setShape( const hkpShape* shape )
{
	HK_ASSERT2(0x2005c7ff, shape, "Cannot setShape to NULL.");

	if (m_world && m_world->areCriticalOperationsLocked())
	{
		hkWorldOperation::SetWorldObjectShape op;
		op.m_worldObject = this;
		op.m_shape = shape;

		m_world->queueOperation(op);
		return hkWorldOperation::POSTPONED;
	}

	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RW );

	if (m_world)
	{
		m_world->lockCriticalOperations();
		hkpWorldOperationUtil::removePhantomBP(m_world, this);
	}

	// Shape replacement
	{
		// Handle reference counting here.
		shape->addReference();
		if (getCollidable()->getShape())
		{
			getCollidable()->getShape()->removeReference();
		}
		getCollidableRw()->setShape(shape);
		
	}

	// Callbacks called before the phantom is added back to the broadphase -- world's first, phantom's second
	if (m_world)
	{
		hkpWorldCallbackUtil::firePhantomShapeSet( m_world, this );
	}
	this->firePhantomShapeSet();

	if (m_world)
	{
		hkpWorldOperationUtil::addPhantomBP(m_world, this);
		m_world->unlockAndAttemptToExecutePendingOperations();
	}

	return hkWorldOperation::DONE;
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
