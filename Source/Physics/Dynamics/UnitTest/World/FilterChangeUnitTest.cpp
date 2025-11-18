/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Dynamics/hkpDynamics.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Filter/Group/hkpGroupFilter.h>
#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>



struct UpdateFilterMyWorld
{
	UpdateFilterMyWorld(){ m_world = HK_NULL; }
	~UpdateFilterMyWorld(){ m_world->markForWrite(); delete m_world; }
	
	hkpAabbPhantom* m_phantomA;
	hkpAabbPhantom* m_phantomB;
	hkpRigidBody*  m_bodyA;
	hkpRigidBody*  m_bodyB;
	hkpGroupFilter* m_groupFilter;
	hkpWorld*      m_world;
};

// creates a world with a filter which disables layer 1 against 1
static void createWorldWith3Objects(int layer, UpdateFilterMyWorld& out)
{
	// create world
	{
		hkpWorldCinfo info;
		out.m_groupFilter = new hkpGroupFilter();
		out.m_groupFilter->disableCollisionsBetween( 1, 1);
		info.m_collisionFilter = out.m_groupFilter;
		out.m_world = new hkpWorld( info );
		out.m_world->lock();
		out.m_groupFilter->removeReference();

		hkpAgentRegisterUtil::registerAllAgents( out.m_world->getCollisionDispatcher() );
	}

	// create a simple sphere
	hkpSphereShape* shape = new hkpSphereShape( 1.0f );

	//
	hkAabb aabb;
	shape->getAabb( hkTransform::getIdentity(), 0.0f, aabb );
	out.m_phantomA = new hkpAabbPhantom( aabb, hkpGroupFilter::calcFilterInfo(layer) );
	out.m_phantomB = new hkpAabbPhantom( aabb, hkpGroupFilter::calcFilterInfo(layer) );

	out.m_world->addPhantom( out.m_phantomA )->removeReference();
	out.m_world->addPhantom( out.m_phantomB )->removeReference();

	hkpRigidBodyCinfo cinfo;
	cinfo.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo(layer);
	cinfo.m_shape = shape;
	cinfo.m_motionType= hkpMotion::MOTION_DYNAMIC;
	cinfo.m_mass = 1.0f;
	cinfo.m_inertiaTensor.setIdentity();

	out.m_bodyA = new hkpRigidBody( cinfo );
	out.m_bodyB = new hkpRigidBody( cinfo );
	
	out.m_world->addEntity( out.m_bodyA )->removeReference();
	out.m_world->addEntity( out.m_bodyB )->removeReference();

	shape->removeReference();

	out.m_world->unlock();
}

static inline int countAgents( hkpRigidBody* body )
{
	return body->getLinkedCollidable()->m_collisionEntries.getSize();
}

static inline int countObjects( hkpAabbPhantom* phantom )
{
	return phantom->getOverlappingCollidables().getSize();
}

static void updateFilterOnEntityWithPhantom()
{
	{
		UpdateFilterMyWorld w;
		createWorldWith3Objects(2, w);

		w.m_world->lock();

		w.m_groupFilter->disableCollisionsBetween(1,2);
		w.m_bodyA->setCollisionFilterInfo( 1 );

		w.m_world->updateCollisionFilterOnEntity( w.m_bodyA, HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK, HK_UPDATE_COLLECTION_FILTER_IGNORE_SHAPE_COLLECTIONS );

		HK_TEST( countAgents(w.m_bodyA) == 0 );
		HK_TEST( countAgents(w.m_bodyB) == 0 );
		HK_TEST( countObjects( w.m_phantomA ) == 2 );
		HK_TEST( countObjects( w.m_phantomB ) == 2 );

		w.m_world->unlock();
	}
	{
		UpdateFilterMyWorld w;
		createWorldWith3Objects(2, w);

		w.m_world->lock();

		w.m_groupFilter->disableCollisionsBetween(1,2);
		w.m_bodyA->setCollisionFilterInfo( 1 );

		w.m_world->updateCollisionFilterOnEntity( w.m_bodyA, HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY, HK_UPDATE_COLLECTION_FILTER_IGNORE_SHAPE_COLLECTIONS );

		HK_TEST( countAgents(w.m_bodyA) == 0 );
		HK_TEST( countAgents(w.m_bodyB) == 0 );
		HK_TEST( countObjects( w.m_phantomA ) == 3 );
		HK_TEST( countObjects( w.m_phantomB ) == 3 );

		w.m_world->unlock();
	}
}

static int FilterChangeUnitTest_main()
{
	updateFilterOnEntityWithPhantom();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(FilterChangeUnitTest_main, "Fast", "Physics/Test/UnitTest/Dynamics/", __FILE__     );

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
