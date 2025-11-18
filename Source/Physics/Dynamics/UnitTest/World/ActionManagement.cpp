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

#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Filter/Group/hkpGroupFilter.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Dynamics/Action/hkpUnaryAction.h>
#include <Physics/Dynamics/Action/hkpBinaryAction.h>

#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics/Dynamics/Constraint/Bilateral/BallAndSocket/hkpBallAndSocketConstraintData.h>


class ActionManagementSampleAction : public hkpUnaryAction
{
public:
	ActionManagementSampleAction(hkpRigidBody* body) : hkpUnaryAction(body) {}
	void applyAction( const hkStepInfo& stepInfo ) {}
	hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const { return HK_NULL; }
};

class ActionManagementSampleBinaryAction : public hkpBinaryAction
{
public:
	ActionManagementSampleBinaryAction(hkpRigidBody* body1, hkpRigidBody* body2) : hkpBinaryAction(body1, body2) {}
	void applyAction( const hkStepInfo& stepInfo ) {}
	hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const { return HK_NULL; }
};

// Test for HVK-1174: Crash when action is added then removed from a fixed entity
static void addActionToFixedEntity()
{
	// create world
	hkpWorld* world;
	{
		hkpWorldCinfo info;
		world = new hkpWorld( info );
		world->lock();
	}

	// create bodies
	hkpRigidBody* bodyA;
	{
		// create shape
		hkVector4 fixedBoxSize; fixedBoxSize.set(5.0f, .5f , 5.0f );
		hkpBoxShape* fixedBoxShape = new hkpBoxShape( fixedBoxSize , 0 );

		// create rigid body info
		hkpRigidBodyCinfo info;
		info.m_shape = fixedBoxShape;
		info.m_motionType = hkpMotion::MOTION_FIXED;
		info.m_position.set(0.0f, -1.0f, 0.0f);

		bodyA = new hkpRigidBody(info);

		// release handle to shape
		fixedBoxShape->removeReference();
	}

	// Create action
	ActionManagementSampleAction* action = new ActionManagementSampleAction(bodyA);


	// Test
	{
		world->addEntity(bodyA);
		world->addAction(action);
		world->removeEntity(bodyA);

		world->unlock();
		world->stepDeltaTime(0.16f);
		world->lock();
	}
	
	// cleanup
	{
		bodyA->removeReference();
		action->removeReference();
		world->removeReference();
	}
}

// Test for HVK-2100: hkpWorld::motionStateChangeDynamicToFixedRemove () doesn't check m_entityActions/m_entityConstrints arrays correctly
static void settingMotionTypeAfterRemovingActionsOrConstraints()
{
	// create world
	hkpWorld* world;
	{
		hkpWorldCinfo info;
		world = new hkpWorld( info );
		world->lock();

		hkpGroupFilter* filter = new hkpGroupFilter();
		filter->disableCollisionsUsingBitfield(hkUint32(-2), hkUint32(-2));
		world->setCollisionFilter( filter );
		filter->removeReference();
	}

	// create bodies
	hkpRigidBody* bodies[2];

	for (int b = 0; b < 2; b++)
	{
		// create shape
		hkVector4 fixedBoxSize; fixedBoxSize.set(5.0f, .5f , 5.0f );
		hkpBoxShape* fixedBoxShape = new hkpBoxShape( fixedBoxSize , 0 );

		// create rigid body info
		hkpRigidBodyCinfo info;
		info.m_shape = fixedBoxShape;
		info.m_motionType = hkpMotion::MOTION_DYNAMIC;
		info.m_position.set(0.0f, b?-1.0f:1.0f, 0.0f);
		info.m_collisionFilterInfo = hkpGroupFilter::calcFilterInfo( 1 );
		hkpInertiaTensorComputer::setShapeVolumeMassProperties(info.m_shape, 1.0f, info);
		bodies[b] = new hkpRigidBody(info);

		// release handle to shape
		fixedBoxShape->removeReference();
	}

	// Create action
	ActionManagementSampleBinaryAction* action = new ActionManagementSampleBinaryAction(bodies[0], bodies[1]);

	// Create constraints (taken from BallAndSocketConstraint demo)
	hkpConstraintInstance* constraint;
	{
		hkpBallAndSocketConstraintData* bs;
		{

			// Create the constraint
			bs = new hkpBallAndSocketConstraintData(); 

			// Set the pivot
			hkVector4 pivot; pivot.set(0,0,0);
			bs->setInWorldSpace(bodies[0]->getTransform(), bodies[1]->getTransform(), pivot);
			constraint = new hkpConstraintInstance(bodies[0], bodies[1], bs);
			bs->removeReference();
		}

	}

	{
		// Test 1 -- removing action & constraint when world is unlocked

		// Initialize
		world->addEntity(bodies[0]);
		world->addEntity(bodies[1]);
		world->addAction(action);
		world->addConstraint(constraint);
		world->unlock();
		world->stepDeltaTime(0.16f);
		world->lock();

		// Remove actions & constraints + call motionTypeChange dynamic <-> fixed
		world->removeAction(action);
		world->removeConstraint(constraint);
		bodies[0]->setMotionType(hkpMotion::MOTION_FIXED);
		world->unlock();
		world->stepDeltaTime(0.16f);
		world->lock();


		// Test 2 -- removing action & constraint when world is locked

		bodies[0]->setMotionType(hkpMotion::MOTION_DYNAMIC);
		world->unlock();
		world->stepDeltaTime(0.16f);
		world->lock();
		world->addAction(action);
		world->addConstraint(constraint);
		world->unlock();
		world->stepDeltaTime(0.16f);
		world->lock();

		world->lockCriticalOperations();
		world->removeAction(action);
		world->removeConstraint(constraint);
		bodies[0]->setMotionType(hkpMotion::MOTION_FIXED);
		world->unlockAndAttemptToExecutePendingOperations();
		world->unlock();
		world->stepDeltaTime(0.16f);
		world->lock();
	}

	// cleanup
	{
		bodies[0]->removeReference();
		bodies[1]->removeReference();
		action->removeReference();
		constraint->removeReference();
		world->removeReference();
	}
}


static int ActionManagement_main()
{
	hkpWorld::IgnoreForceMultithreadedSimulation ignoreForceMultithreaded;
	addActionToFixedEntity();
	settingMotionTypeAfterRemovingActionsOrConstraints();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(ActionManagement_main, "Fast", "Physics/Test/UnitTest/Dynamics/", __FILE__     );

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
