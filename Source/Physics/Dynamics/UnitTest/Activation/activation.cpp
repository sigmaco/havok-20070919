/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Dynamics/hkpDynamics.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

// Test that applying forces and vecs activates a body

static void deactivate(hkpRigidBody* rb, hkpWorld* w)
{
	HK_TEST2( rb->isActive(), "Rigid body was not active." );
	rb->setLinearVelocity(hkVector4::getZero());
	rb->setAngularVelocity(hkVector4::getZero());
	rb->deactivate();
	w->unlock();
	w->stepDeltaTime(0.016f);
	w->lock();
	HK_ASSERT(0x67e3b9cd,  rb->isActive() == false );
}

static int activation_main()
{
	hkpWorld::IgnoreForceMultithreadedSimulation ignoreForceMultithreaded;

	hkpRigidBody* rigidBody = HK_NULL;
//	hkpRigidBody* base = HK_NULL;
	hkpWorld* world = HK_NULL;

	// Create the world.
	{
		hkpWorldCinfo info;
		
		// Set gravity to zero so body floats.
		info.m_gravity.setZero4();
		info.setBroadPhaseWorldSize( 100.0f );
		world = new hkpWorld(info);
		world->lock();
	}

	// Create the shape and a rigid body to view it.
	{
		// Data specific to this shape.
		hkVector4 halfExtents; halfExtents.set(1.0f, 1.0f, 1.0f);
		
		hkpBoxShape* shape = new hkpBoxShape(halfExtents, 0 );
		hkpRigidBodyCinfo rigidBodyInfo;
		rigidBodyInfo.m_shape = shape;
		rigidBodyInfo.m_position.setZero4();
		rigidBodyInfo.m_angularDamping = 0.0f;
		rigidBodyInfo.m_linearDamping = 0.0f;
		rigidBodyInfo.m_inertiaTensor.setIdentity();
		rigidBodyInfo.m_mass = 1;
		rigidBodyInfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;

		rigidBody = new hkpRigidBody(rigidBodyInfo);
		world->addEntity(rigidBody);

		rigidBodyInfo.m_position.set( 0, -5, 0);
		rigidBodyInfo.m_mass = 0;
		rigidBodyInfo.m_inertiaTensor.setZero();
		rigidBodyInfo.m_motionType = hkpMotion::MOTION_FIXED;

	//	base = new hkpRigidBody(rigidBodyInfo);
	//	world->addEntity(base);

		shape->removeReference();
	}

	// test that the functions work as advertised.
	{
		hkStepInfo stepInfo( hkTime(0.0f), hkTime(0.1f) );
		hkVector4 vec; vec.set(1,1,1);
		hkQuaternion rot; rot.setIdentity();
		hkTransform trans; trans.setIdentity();

		deactivate(rigidBody, world);
		rigidBody->setPosition(vec);
		
		deactivate(rigidBody, world);
		rigidBody->setRotation(rot);

		deactivate(rigidBody, world);
		rigidBody->setPositionAndRotation(vec, rot);

		deactivate(rigidBody, world);
		rigidBody->setTransform(trans);


		deactivate(rigidBody, world);
		rigidBody->setLinearVelocity(vec);

		deactivate(rigidBody, world);
		rigidBody->setAngularVelocity(vec);

		deactivate(rigidBody, world);
		rigidBody->applyPointImpulse(vec, vec);

		
		deactivate(rigidBody, world);
		rigidBody->applyForce(stepInfo.m_deltaTime, vec);

		deactivate(rigidBody, world);
		rigidBody->applyForce(stepInfo.m_deltaTime, vec);

		deactivate(rigidBody, world);
		rigidBody->applyTorque(stepInfo.m_deltaTime, vec);

		deactivate(rigidBody, world);
	}


	
	// clean up
	{
		rigidBody->removeReference();
		world->removeReference();
	}
	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(activation_main, "Fast", "Physics/Test/UnitTest/Dynamics/", __FILE__     );

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
