/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>

#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Physics/Dynamics/Phantom/hkpPhantomType.h>
#include <Physics/Dynamics/Phantom/hkpSimpleShapePhantom.h>
#include <Physics/Collide/Agent/hkpCollisionInput.h>
#include <Physics/Collide/Agent/Query/hkpLinearCastCollisionInput.h>
#include <Physics/Collide/Agent/Query/hkpCdPointCollector.h>
#include <Physics/Collide/Agent/Query/hkpCdBodyPairCollector.h>
#include <Physics/Collide/Agent/hkpCollisionAgent.h>
#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Physics/Collide/Query/CastUtil/hkpLinearCastInput.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Physics/Dynamics/World/hkpWorld.h>
	
hkpSimpleShapePhantom::hkpSimpleShapePhantom(	 const hkpShape* shape, const hkTransform& transform, hkUint32 collisionFilterInfo )
:	hkpShapePhantom( shape, transform )
{
	m_collidable.setCollisionFilterInfo( collisionFilterInfo );
}

// N.B. Setting the shape of a hkpShapePhantom with setShapeFastUnsafe() while it is in the world is very dangerous!
// If any hkCachingShapePhantoms are also in the world and overlap with this phantom, they will not be
// notified of the shape change, and their cached agents will become invalid.
// You should remove this phantom from the world, change the shape, then re-add.
//hkWorldOperation::Result hkpSimpleShapePhantom::setShapeFastUnsafe( hkpShape* shape )
//{
//	hkpWorld* world = getWorld();
//	hkWorldOperation::Result baseResult;
//	if (world)
//	{
//		//world->blockExecutingPendingOperations(true);
//		set collidable's shape directly from this f.//baseResult = hkpShapePhantom::setShape(shape);
//		//world->blockExecutingPendingOperations(false);
//	}
//	else
//	{
//		baseResult = hkpShapePhantom::setShape(shape);
//	}
//
//	if (baseResult == hkWorldOperation::DONE && world)
//	{	
//		// Update the aabb. This is allowable if you know *for certain* that it will not
//		// corrupt any hkCachingShapePhantoms.
//
//		hkAabb aabb;
//		hkReal halfTolerance = 0.5f * m_world->getCollisionInput()->getTolerance();
//		shape->getAabb( m_motionState.getTransform(), halfTolerance, aabb );
//
//		world->lockCriticalOperations();
//		updateBroadPhase( aabb );
//		world->unlockAndAttemptToExecutePendingOperations();
//	}
//
//	return baseResult;
//}

hkpSimpleShapePhantom::~hkpSimpleShapePhantom()
{

}

hkpPhantomType hkpSimpleShapePhantom::getType() const
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RO );
	return HK_PHANTOM_SIMPLE_SHAPE;
}

// hkpPhantom clone functionality
hkpPhantom* hkpSimpleShapePhantom::clone() const
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RO );
	const hkpCollidable* c = getCollidable();
	hkpSimpleShapePhantom* ssp = new hkpSimpleShapePhantom(c->getShape(), m_motionState.getTransform(), c->getCollisionFilterInfo() );
	
	// stuff that isn 't in the ctor (the array of listeners (not ref counted etc, assume clone wants the same list to start with)
	ssp->m_overlapListeners = m_overlapListeners;
	ssp->m_phantomListeners = m_phantomListeners;

	ssp->copyProperties( this );
	
	return ssp;
}

void hkpSimpleShapePhantom::setPositionAndLinearCast( const hkVector4& position, const hkpLinearCastInput& input, hkpCdPointCollector& castCollector, hkpCdPointCollector* startCollector )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RW, this, HK_ACCESS_RW );

	HK_ASSERT2(0x2FE9081E, m_world != HK_NULL, "hkpSimpleShapePhantom has not been added to an hkpWorld.");

	m_motionState.getTransform().setTranslation( position );

	hkAabb aabb;
	hkVector4 path;

	//
	//	calculate the correct aabb and update the broadphase
	//
	{
		hkReal halfTolerance = 0.5f * m_world->getCollisionInput()->getTolerance();
		m_collidable.getShape()->getAabb( m_motionState.getTransform(), halfTolerance + input.m_startPointTolerance, aabb );

		path.setSub4( input.m_to, position );
		hkVector4 zero; zero.setZero4();
		hkVector4 pathMin; pathMin.setMin4( zero, path );
		hkVector4 pathMax; pathMax.setMax4( zero, path );

		aabb.m_min.add4( pathMin );
		aabb.m_max.add4( pathMax );
		updateBroadPhase( aabb );
	}

	//
	//	Setup the linear cast input
	//
	hkpLinearCastCollisionInput lcInput;
	{
		lcInput.set( *m_world->getCollisionInput() );
		lcInput.setPathAndTolerance( path, input.m_startPointTolerance );
		lcInput.m_maxExtraPenetration = input.m_maxExtraPenetration;
	}

	
	//
	//	Do the cast
	//
	{
		hkpCollisionDispatcher* dispatcher = m_world->getCollisionDispatcher();
		for ( int i = m_collisionDetails.getSize() - 1; i >= 0; i-- )
		{
			CollisionDetail& det = m_collisionDetails[i];
			hkpShapeType typeB = det.m_collidable->getShape()->getType();

			hkpCollisionDispatcher::LinearCastFunc linearCast = dispatcher->getLinearCastFunc( m_collidable.getShape()->getType(), typeB );
			linearCast( m_collidable, *det.m_collidable, lcInput, castCollector, startCollector );
		}
	}
}

void hkpSimpleShapePhantom::getClosestPoints( hkpCdPointCollector& collector, const hkpCollisionInput* input )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RO );
	HK_ASSERT2(0x2fe9081e, m_world != HK_NULL, "hkpSimpleShapePhantom has not been added to an hkpWorld."); 
	if (!input)
	{
		input = m_world->getCollisionInput();
	}
	hkpCollisionDispatcher* dispatcher = input->m_dispatcher;
	for ( int i = m_collisionDetails.getSize() - 1; i >= 0; i-- )
	{
		CollisionDetail& det = m_collisionDetails[i];
		hkpShapeType typeB = det.m_collidable->getShape()->getType();

		hkpCollisionDispatcher::GetClosestPointsFunc getClosestPointsFunc = dispatcher->getGetClosestPointsFunc( m_collidable.getShape()->getType(), typeB );
		(*getClosestPointsFunc)( m_collidable, *det.m_collidable, *input, collector );
	}
}
	
void hkpSimpleShapePhantom::getPenetrations( hkpCdBodyPairCollector& collector, const hkpCollisionInput* input )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_RO, this, HK_ACCESS_RO );
	HK_ASSERT2(0x13b152a4, m_world != HK_NULL, "hkpSimpleShapePhantom has not been added to an hkpWorld."); 
	if (!input)
	{
		input = m_world->getCollisionInput();
	}
	hkpCollisionDispatcher* dispatcher = input->m_dispatcher;
	for ( int i = m_collisionDetails.getSize() - 1; i >= 0; i-- )
	{
		CollisionDetail& det = m_collisionDetails[i];
		hkpShapeType typeB = det.m_collidable->getShape()->getType();

		hkpCollisionDispatcher::GetPenetrationsFunc getPenetrationsFunc = dispatcher->getGetPenetrationsFunc( m_collidable.getShape()->getType(), typeB );
		(*getPenetrationsFunc)( m_collidable, *det.m_collidable, *input, collector );
		if ( collector.getEarlyOut() )
		{
			break;
		}
	}
}

hkBool hkpSimpleShapePhantom::isOverlappingCollidableAdded( hkpCollidable* collidable )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RO );
	for( int i = 0; i<m_collisionDetails.getSize(); i++ )
	{
		if( m_collisionDetails[i].m_collidable == collidable )
		{
			return true;
		}
	}
	return false;
}

void hkpSimpleShapePhantom::addOverlappingCollidable( hkpCollidable* collidable )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW );

	if ( collidable->getShape() != HK_NULL )
	{
		hkpCollidableAccept accept = fireCollidableAdded( collidable );

		if ( accept == HK_COLLIDABLE_ACCEPT  )
		{
			CollisionDetail& det = m_collisionDetails.expandOne();
			det.m_collidable = collidable;
		}
	}
}

void hkpSimpleShapePhantom::removeOverlappingCollidable( hkpCollidable* collidable )
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW );

	if ( collidable->getShape() != HK_NULL )
	{
		//
		//	We are not checking the filter, so our implementation is a little bit
		//  forgiving, if people change filters on the fly
		//
		for ( int i = m_collisionDetails.getSize() - 1; i >= 0; i-- )
		{
			if ( m_collisionDetails[i].m_collidable == collidable )
			{
				fireCollidableRemoved( collidable, true );
				m_collisionDetails.removeAt( i );
				return;
			}
		}
		fireCollidableRemoved( collidable, false );
	}
}

void hkpSimpleShapePhantom::calcStatistics( hkStatisticsCollector* collector ) const
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RO );
	collector->beginObject("SimplePhantm", collector->MEMORY_INSTANCE, this);
	hkpPhantom::calcStatistics(collector);
	collector->addArray("OverlapPtr", collector->MEMORY_RUNTIME, m_collisionDetails);
	collector->endObject();
}

void hkpSimpleShapePhantom::deallocateInternalArrays()
{
	HK_ACCESS_CHECK_WITH_PARENT( m_world, HK_ACCESS_IGNORE, this, HK_ACCESS_RW );
	// Need to deallocate any arrays that are 0 size
	// else warn user that they should call the in place destructor

	// Collision Details
	if (m_collisionDetails.getSize() == 0)
	{
		m_collisionDetails.clearAndDeallocate();
	}
	else
	{
		HK_WARN(0x234f224e, "Phantom at address " << this << " has non-zero m_collisionDetails array.\nPlease call in-place destructor to deallocate.\n");
	}

	hkpShapePhantom::deallocateInternalArrays();
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
