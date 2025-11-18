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

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Dynamics/Action/hkpUnaryAction.h>
#include <Physics/Dynamics/Action/hkpBinaryAction.h>

#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics/Dynamics/Constraint/Bilateral/BallAndSocket/hkpBallAndSocketConstraintData.h>

#include <Physics/Dynamics/Constraint/Bilateral/LimitedHinge/hkpLimitedHingeConstraintData.h>
#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>

// Test for: When not using simulation islands: removing the last dynamic body from the world and then adding a new one.
//           Will the active island be destroyed upon the removal of the last body ?
static void removalOfLastBodyWhenNotUsingSimulationIslands()
{
	// create world
	hkpWorld* world;
	{
		hkpWorldCinfo info;
		info.m_enableSimulationIslands = false;
		info.m_enableDeactivation = false;
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
		info.m_motionType = hkpMotion::MOTION_DYNAMIC;
		info.m_position.set(0.0f, -1.0f, 0.0f);

		bodyA = new hkpRigidBody(info);

		// release handle to shape
		fixedBoxShape->removeReference();
	}

	// Test
	{
		world->addEntity(bodyA);
		world->stepDeltaTime(0.16f);
		world->removeEntity(bodyA);
		//world->stepDeltaTime(0.16f);
		world->addEntity(bodyA);
		world->unlock();
		world->stepDeltaTime(0.16f);
		world->lock();
	}

	// cleanup
	{
		bodyA->removeReference();
		world->removeReference();
	}
}


static void settingMassOfFixedObjects()
{
	// create world
	hkpWorld* world;
	{
		hkpWorldCinfo info;
		info.m_enableSimulationIslands = false;
		info.m_enableDeactivation = false;
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
		info.m_motionType = hkpMotion::MOTION_DYNAMIC;
		info.m_position.set(0.0f, -1.0f, 0.0f);

		bodyA = new hkpRigidBody(info);

		// release handle to shape
		fixedBoxShape->removeReference();
	}

	// Test: this test must cause an assert if enabled
	if(0)
	{
		world->addEntity(bodyA);
		bodyA->setMotionType(hkpMotion::MOTION_FIXED);
		//bodyA->setMass(10.0f);
	}

	// cleanup
	{
		bodyA->removeReference();
		world->removeReference();
	}
}

// HVK-2068: crash in setMotionType
static void hvk2068()
{
	// create world
	hkpWorld* world;
	{
		hkpWorldCinfo info;
		info.m_enableDeactivation = false;
		world = new hkpWorld( info );
		world->lock();

		hkpAgentRegisterUtil::registerAllAgents((world->getCollisionDispatcher()));
	}

//	create a series of rigid bodies (boxes)
//		- with motion type BOX_INERTIA
//		- if it's pertinent DEACTIVATE_NEVER). 
#define NUM_BODIES 5
	hkpRigidBody* body[NUM_BODIES+1];
	{
		for (int i = 0; i < NUM_BODIES+1; i++)
		{
			// create rigid body info
			hkpRigidBodyCinfo info;
			{
				hkVector4 halfExt; halfExt.set(5.0f, .5f , 5.0f );
				info.m_shape = new hkpBoxShape( halfExt , 0 );
			}
			info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
			info.m_rigidBodyDeactivatorType = hkpRigidBodyDeactivator::DEACTIVATOR_NEVER;
			info.m_position.set(i * 12.0f, 0.0f, 0.0f);

			body[i] = new hkpRigidBody(info);
			info.m_shape->removeReference();
		
			if (i < NUM_BODIES)
			{
				world->addEntity(body[i]);
				body[i]->removeReference();
			}
			else
			{
				body[i]->setPosition( body[2]->getPosition() );
			}
		}
	}

//	next, create a powered hinge between each box and its neighbor
	hkpConstraintInstance* constraint[NUM_BODIES-1];
	for(int ni = 0; ni < NUM_BODIES - 1; ni++)
	{
		hkpLimitedHingeConstraintData* data = new hkpLimitedHingeConstraintData();
		data->setMotorActive(HK_NULL, true);
		{
			hkVector4 axis; axis.set(0.f, 0.f, 1.f);
			data->setInWorldSpace( body[ni]->getTransform(), body[ni+1]->getTransform(), body[ni]->getPosition(), axis );
		}
		constraint[ni] = new hkpConstraintInstance(body[ni], body[ni+1], data);
		data->removeReference();

		world->addConstraint(constraint[ni]);
		constraint[ni]->removeReference();
	}

	//pick one of the non-end boxes and remove both of the hinge constraints attached to it from the world


	world->removeConstraint(constraint[1]);
	world->removeConstraint(constraint[2]);

	//remove the box from the world
	world->removeEntity(body[2]);

	//create a new box in the same fashion as the others (BOX_INERTIA, etc...)
	// done
	world->addEntity(body[NUM_BODIES]);
	body[NUM_BODIES]->removeReference();

	//create two powered hinge constraints one for each neighbor of the new box.
	hkpConstraintInstance* newConstraint[2];
	for(int ci = 0; ci < 2; ci++)
	{
		hkpLimitedHingeConstraintData* data = new hkpLimitedHingeConstraintData();
		data->setMotorActive(HK_NULL, true);
		if (ci == 0)
		{
			hkVector4 axis; axis.set(0.f, 0.f, 1.f);
			data->setInWorldSpace( body[ci+1]->getTransform(), body[NUM_BODIES]->getTransform(), body[ci+1]->getPosition(), axis );
			newConstraint[ci] = new hkpConstraintInstance(body[ci+1], body[NUM_BODIES], data);
		}
		else		
		{
			hkVector4 axis; axis.set(0.f, 0.f, 1.f);
			data->setInWorldSpace( body[NUM_BODIES]->getTransform(), body[ci+1+1]->getTransform(), body[NUM_BODIES]->getPosition(), axis );
			newConstraint[ci] = new hkpConstraintInstance(body[NUM_BODIES], body[ci+1+1], data);
		}
		data->removeReference();
		world->addConstraint(newConstraint[ci]);
		newConstraint[ci]->removeReference();
	}

	//set all of the boxes motion type to RIGID
	for (int ri = 0; ri < NUM_BODIES + 1; ri++)
	{
		if (ri != 2)
		{
			body[ri]->setMotionType(hkpMotion::MOTION_FIXED);
		}
	}

	//set all of the boxes motion type to BOX_INERTIA
	for (int bi = 0; bi < NUM_BODIES + 1; bi++)
	{
		if (bi != 2)
		{
			body[bi]->setMotionType(hkpMotion::MOTION_BOX_INERTIA);
		}
	}


	//that should cause the crash I am getting. That's as minimal as I can get it.

	// cleanup
	world->removeReference();
}

static int EntityManagement_main()
{
	hkpWorld::IgnoreForceMultithreadedSimulation ignoreForceMultithreaded;
	removalOfLastBodyWhenNotUsingSimulationIslands();
	settingMassOfFixedObjects();
	hvk2068();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(EntityManagement_main, "Fast", "Physics/Test/UnitTest/Dynamics/", __FILE__     );

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
