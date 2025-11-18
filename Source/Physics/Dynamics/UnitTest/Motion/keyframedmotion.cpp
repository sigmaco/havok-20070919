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
#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#define NTEST	10000

// Test that setPosition and setVelocity can be called on a keyframed body

int keyframedmotion_main()
{
	hkpWorld::IgnoreForceMultithreadedSimulation ignoreForceMultithreaded;

	hkpRigidBody* rigidBody;
	hkpWorld* world;

		// Create the world.
	{
		hkpWorldCinfo info;
		
		// Set gravity to zero so body floats.
		info.m_gravity.set(0.0f, -9.8f, 0.0f);	
		info.setBroadPhaseWorldSize( 100.0f );
		world = new hkpWorld(info);
		world->lock();
	}

	// Create the shape and a rigid body to view it.
	{
		// Data specific to this shape.
		hkVector4 halfExtents; halfExtents.set(1.0f, 1.0f, 1.0f);
		
		/////////////////// SHAPE CONSTRUCTION ////////////////
		hkpBoxShape* shape = new hkpBoxShape(halfExtents, 0 );
		///////////////////////////////////////////////////////


		// To illustrate using the shape, create a rigid body by first defining a template.
		hkpRigidBodyCinfo rigidBodyInfo;

		rigidBodyInfo.m_shape = shape;
		rigidBodyInfo.m_position.set(0.0f, 0.0f, 0.0f);
		rigidBodyInfo.m_angularDamping = 0.0f;
		rigidBodyInfo.m_linearDamping = 0.0f;

		// If we set this to true, the body is fixed, and no mass properties need to be computed.
		rigidBodyInfo.m_motionType = hkpMotion::MOTION_KEYFRAMED; //hkpMotion::MOTION_BOX_INERTIA;

		// If we need to compute mass properties, we'll do this using the hkpInertiaTensorComputer.
		if (rigidBodyInfo.m_motionType != hkpMotion::MOTION_FIXED)
		{
			hkReal mass = 10.0f;
			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfExtents, mass, massProperties);

			rigidBodyInfo.m_inertiaTensor = massProperties.m_inertiaTensor;
			rigidBodyInfo.m_centerOfMass = massProperties.m_centerOfMass;
			rigidBodyInfo.m_mass = massProperties.m_mass;			
		}	
			
			
		// Create a rigid body (using the template above).
		rigidBody = new hkpRigidBody(rigidBodyInfo);

		// Remove reference since the body now "owns" the Shape.
		shape->removeReference();

		// Finally add body so we can see it, and remove reference since the world now "owns" it.
		world->addEntity(rigidBody);
		rigidBody->removeReference();
	}


	// 
	// Step the simulation
	//
	hkReal time = 0.0f;

	time += 0.016f;
	world->unlock();
	world->stepDeltaTime( 0.016f );
	world->lock();


	// Check velocity is initialised to zero

	HK_TEST2( rigidBody->getLinearVelocity().equals3(hkVector4::getZero()), "Keyframed body initial velocity zero. "  );

	// Check setPosition() works 

	hkVector4 posabs; posabs.set( -1,-1,-1 );

	rigidBody->setPosition( posabs );

	// This sounds obvious but previously setPosition() was disabled for keyframed bodies! (caused an assert)
	HK_TEST2( rigidBody->getPosition().equals3( posabs ), "Set Keyframe body position. " );

	time += 0.016f;
	world->stepDeltaTime( 0.016f );

	HK_TEST2( rigidBody->getPosition().equals3( posabs ), "Set Keyframe body position. " );

	// Check setVelocity works
	hkVector4 lastDiff; lastDiff.set(0,0,0);
	hkVector4 velinc; velinc.set( 0.3f, 0.001f, 0.3f );

	while( time < 0.5f )
	{
		hkVector4 lastPos = rigidBody->getPosition();

		hkVector4 curvel = rigidBody->getLinearVelocity();
		curvel.add4( velinc );

		rigidBody->setLinearVelocity( curvel );

		time += 0.016f;
		world->stepDeltaTime( 0.016f );

		hkVector4 calcnewpos;
		calcnewpos.setAddMul4( lastPos, curvel, 0.016f );

		HK_TEST2( calcnewpos.equals3( rigidBody->getPosition() ), "Check Keyframe body integration. " );

		hkVector4 posWithoutVelChange = lastPos;
		posWithoutVelChange.add4( lastDiff );

		lastDiff.setSub4( rigidBody->getPosition(), lastPos );

		// Test that its velocity is changing, its position is changing and that
		// gravity is not affecting it. 

		// Need to include the case where the W component is also less.
		// ie. we accept both (NEG, NEG, NEG, NEG)  and (NEG, NEG, NEG, POS) as a valid result because we
		// don't care about the w component.
		hkVector4Comparison mask = posWithoutVelChange.compareLessThan4( rigidBody->getPosition() );
		HK_TEST2( mask.allAreSet(hkVector4Comparison::MASK_XYZ), "Keyframed body velocity changing. " );
	}

	world->removeReference();

	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(keyframedmotion_main, "Fast", "Physics/Test/UnitTest/Dynamics/", __FILE__     );

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
