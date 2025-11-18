/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/ConstraintSolver/Simplex/hkpSimplexSolver.h>

#include <Physics/Collide/Agent/ContactMgr/hkpContactMgr.h>
#include <Physics/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnTrack.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>

// Includes for mass modifier
#include <Physics/Dynamics/Collide/hkpCollisionListener.h>
#include <Physics/Dynamics/Entity/hkpEntityListener.h>
#include <Physics/Dynamics/Collide/hkpResponseModifier.h>

#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>

// Enable this to see manifold planes.
#ifdef HK_DEBUG
#define DEBUG_CHARACTER_RIGIDBODY
#endif

#ifdef DEBUG_CHARACTER_RIGIDBODY
#include <Common/Visualize/hkDebugDisplay.h>
static void debugContactPoint(hkContactPoint& cp);
static void debugGround(const hkVector4& position, const hkpSurfaceInfo& ground);
#endif

/// A listener class used to change a mass of rigid body character during collision with other dynamic rigid bodies and
/// to restrain movement on very steep planes. Instances of this listener is registered with a hkpCharacterRigidBody.

/// The first usage is the modification of a mass of rigid body character during collision with dynamic objects in the scene.
/// This approach allows continuous regulation of "maximal force (power)" of character during interaction with other dynamics objects.
/// (Modification factor decreases the mass of rigid body during response calculation)
/// Modification factor is calculated in every step in contactProcessCallback() using the following formulas
///
///  - Calculate angle alpha between contact normal and current acceleration
///  - Calculate current force applied to interaction object as F = mass*acceleration*cos(alpha)
///  - If (F > Fmax) calculate mass modification factor
///  - Apply mass modification factor to impulse calculation using hkpResponseModifier::setInvMassScalingForContact()
///
/// The acceleration is calculated as difference between the required output velocity from state machine and current
/// velocity of rigid body divided by timestep.
///
/// The second usage is the addition of extra contact points to avoid movement of character on "steep" plane. "Steep" plane is defined
/// by m_maxSlope parameter. It's a angle between UP direction and normal of the plane. So vertical plane has PI/2 (90 Deg) and horizontal plane 0.
/// Default value is PI/3 (60 Deg).

class hkCharacterRigidBodyCollisionListener : public hkReferencedObject, public hkpCollisionListener
{

	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CHARACTER);


		hkCharacterRigidBodyCollisionListener( hkReal maxForce, hkReal maxSlopeCos, const hkVector4& up)
		{
			m_maxForce = maxForce;
			m_maxSlopeCos = maxSlopeCos;
			m_up = up;

			m_acceleration.setZero4();
		}

		// The hkpCollisionListener interface implementation
		void contactPointAddedCallback(	hkpContactPointAddedEvent& event )
		{
			// For non TOI contacts, check the slope, and if it is greater than the max slope, add in another vertical contact point
			if (!event.isToi())
			{
				if ( event.m_internalContactMgr->getType() == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR )
				{
					// Get some allocated data in the contact point properties to store the ID of the new contact point
					hkpSimpleConstraintContactMgr* mgr = (hkpSimpleConstraintContactMgr*)event.m_internalContactMgr;

					HK_ASSERT(0x097a8654, event.m_callbackFiredFrom == mgr->m_constraint.getEntityA() || event.m_callbackFiredFrom == mgr->m_constraint.getEntityB() );
					int idx = event.m_callbackFiredFrom== mgr->m_constraint.getEntityA() ? 0 : 1;
					const hkpSimpleContactConstraintAtom* atom = mgr->getAtom();
					hkUint32& id = event.m_contactPointProperties->getExtendedUserData( atom, idx, 0);
					id = HK_INVALID_CONTACT_POINT;

					const hkReal surfaceVerticalComponent = event.m_contactPoint->getNormal().dot3(m_up);

					if ( surfaceVerticalComponent > 0.01f && surfaceVerticalComponent < m_maxSlopeCos )
					{
						hkContactPoint cp;
						cp.setPosition( event.m_contactPoint->getPosition() );
						cp.setSeparatingNormal( event.m_contactPoint->getSeparatingNormal() );
						cp.getSeparatingNormal().addMul4(-surfaceVerticalComponent, m_up);
						cp.getSeparatingNormal().normalize3();
						cp.setDistance( 0 );

						int index = event.m_internalContactMgr->addContactPoint( *event.m_bodyA, *event.m_bodyB, *event.m_collisionInput, *event.m_collisionOutput, HK_NULL, cp );
						if (index != HK_INVALID_CONTACT_POINT)
						{
							// Note - as addContactPoint may have resized the atom we have to go to the atom again to get the right user data location
							// We must also fix up the event data structure for any later callbacks

							const hkpSimpleContactConstraintAtom* atom = mgr->getAtom();
							hkpManifoldPointAddedEvent& manifoldEvent = (hkpManifoldPointAddedEvent&)event;
							event.m_contactPointProperties = atom->getContactPointPropertiesStream( mgr->m_contactConstraintData.m_idMgrA.getValueAt(manifoldEvent.m_contactPointId) )->asProperties();
							hkUint32& newIndex = event.m_contactPointProperties->getExtendedUserData( atom, idx, 0);
							newIndex = index;
						}
					}
				}
			}
		}

			/// No implementation.
		void contactPointConfirmedCallback( hkpContactPointConfirmedEvent& event){}


			/// Remove extra vertical contact points
		void contactPointRemovedCallback( hkpContactPointRemovedEvent& event )
		{
			if (!event.isToi())
			{
				hkpSimpleConstraintContactMgr* mgr = (hkpSimpleConstraintContactMgr*)event.m_internalContactMgr;
				HK_ASSERT(0x097a8654, event.m_callbackFiredFrom == mgr->m_constraint.getEntityA() || event.m_callbackFiredFrom == mgr->m_constraint.getEntityB() );
				int idx = event.m_callbackFiredFrom == mgr->m_constraint.getEntityA() ? 0 : 1;
				const hkpSimpleContactConstraintAtom* atom = mgr->getAtom();
				hkUint32& id = event.m_contactPointProperties->getExtendedUserData( atom, idx, 0);

				if ((hkContactPointId)id != HK_INVALID_CONTACT_POINT)
				{
					event.m_internalContactMgr->removeContactPoint( (hkContactPointId)id,  *event.m_constraintOwner );

					// Need to fix up the event structure
					event.m_contactPointProperties = atom->getContactPointPropertiesStream( mgr->m_contactConstraintData.m_idMgrA.getValueAt(event.m_contactPointId) )->asProperties();

				}
			}
		}


		/// Called just after all collision detection between 2 rigid bodies has been executed.
		/// Callback frequency is set to zero (no delay, method is called each step).
	void contactProcessCallback( hkpContactProcessEvent& event )
	{
			//
			// For all vertical "Max slope" contacts, manage the updates of their positions and directions
			//

			hkpSimpleConstraintContactMgr* mgr = (hkpSimpleConstraintContactMgr*)event.m_internalContactMgr;
			HK_ASSERT(0x097a8654, event.m_callbackFiredFrom == mgr->m_constraint.getEntityA() || event.m_callbackFiredFrom == mgr->m_constraint.getEntityB() );
			int idx = event.m_callbackFiredFrom == mgr->m_constraint.getEntityA() ? 0 : 1;
			const hkpSimpleContactConstraintAtom* atom = mgr->getAtom();

			for(int i = 0; i < event.m_collisionData->getNumContactPoints(); i++ )
			{
				hkUint32& id = event.m_contactPointProperties[i]->getExtendedUserData( atom, idx, 0);
				if ( (hkContactPointId)id != HK_INVALID_CONTACT_POINT )
				{
					hkContactPoint& cp = *mgr->getContactPoint( (hkContactPointId)id );
					cp.setPosition( event.m_collisionData->m_contactPoints[i].m_contact.getPosition() );
					cp.setSeparatingNormal( event.m_collisionData->m_contactPoints[i].m_contact.getSeparatingNormal() );
					const hkReal surfaceVerticalComponent = event.m_collisionData->m_contactPoints[i].m_contact.getNormal().dot3(m_up);
					cp.getSeparatingNormal().addMul4(-surfaceVerticalComponent, m_up);
					cp.getSeparatingNormal().normalize3();
					cp.setDistance( 0 );
				}
			}


			//
			// Scale contact points using the mass modifier
			//

			hkSimdReal mul;

			hkpRigidBody* bodyA;
			hkpRigidBody* bodyB;

			// Contact normal goes from bodyB to bodyA. (most of the shapes, except sphere)
			// Change direction (direction away from character)
			if (event.m_callbackFiredFrom->getCollidable() == event.m_collidableA)
			{
				bodyA = hkGetRigidBody(event.m_collidableA);
				bodyB = hkGetRigidBody(event.m_collidableB);
				mul = -1.0f;
			}
			else
			{
				bodyA = hkGetRigidBody(event.m_collidableB);
				bodyB = hkGetRigidBody(event.m_collidableA);
				mul = 1.0f;
			}

			// The bodies could be in either order so we have to check both cases
			hkReal factor = 1.0f;

			// Calculate major contact normal as average of all normals
			hkVector4 normal; normal.setZero4();
			hkVector4 contactPoint; contactPoint.setZero4();

			for(int i = 0; i < event.m_collisionData->getNumContactPoints(); i++ )
			{
				normal.add4(event.m_collisionData->m_contactPoints[i].m_contact.getNormal());
				contactPoint.add4(event.m_collisionData->m_contactPoints[i].m_contact.getPosition());
			}
			normal.mul4(mul);
			normal.normalize3();
			contactPoint.mul4(1.0f/event.m_collisionData->getNumContactPoints());

			// Do for all dynamic bodies
			if ( !bodyB->isFixedOrKeyframed() )
			{
				factor = calculateFactor(bodyA,bodyB,normal);

				hkpResponseModifier::setInvMassScalingForContact( event.m_internalContactMgr, bodyA, bodyB, *event.m_collisionData->m_constraintOwner.val(), factor, 1.0f );
			}

		}


			/// Calculate mass modification factor from current acceleration
		hkReal calculateFactor(const hkpRigidBody* rbA, const hkpRigidBody* rbB, hkVector4& contactNormal )
		{

			// alpha is angle between contact normal and current acceleration
			// F = m * (v - vold)*cos(alpha)/timestep

			hkReal factor = 1.0f;

			hkReal currentForce = contactNormal.dot3(m_acceleration);
			currentForce *= (rbA->getMass());

			if (currentForce > m_maxForce)
			{
				// factor modifies inverse mass !
				factor = currentForce/m_maxForce;
			}

			return factor;

		}

			/// Set current acceleration
		void setAcceleration(const hkVector4& newAcc);

			/// Set max allowed interaction force
		void setMaxForce(const hkReal newMaxForce);

	private:

		hkVector4 m_up;
		hkVector4 m_acceleration;
		hkReal	m_maxForce;
		hkReal m_maxSlopeCos;

};


void hkCharacterRigidBodyCollisionListener::setAcceleration(const hkVector4& newAcc)
{
	m_acceleration = newAcc;
}

void hkCharacterRigidBodyCollisionListener::setMaxForce(const hkReal newMaxForce)
{
	m_maxForce = newMaxForce;
}

hkpCharacterRigidBody::hkpCharacterRigidBody(const hkpCharacterRigidBodyCinfo& info )
{
	HK_ASSERT2(0x79d50ec9,  !(&info == HK_NULL), "No info defined");
	HK_ASSERT2(0x79d51ec9,  !(info.m_shape == HK_NULL), "No shape for character defined");
	HK_ASSERT2(0x79d52ec9,  info.m_up.isOk3(), "Up direction incorrectly defined");

	hkpRigidBodyCinfo ci;

	// Set rigid body character shape (usually capsule)
	ci.m_shape = info.m_shape;

	// Set rigid body mass (Default is 100 kg)
	// Remember that all max acceleration and max force are very depended on the mass of character
	ci.m_mass = info.m_mass;

	// Set friction (Default is no friction)
	ci.m_friction = info.m_friction;

	// Set init position and rotation
	ci.m_position = info.m_position;
	ci.m_rotation = info.m_rotation;

	// Set collision filter info
	ci.m_collisionFilterInfo = info.m_collisionFilterInfo;
	ci.m_numUserDatasInContactPointProperties = 1;

	// Set restitution no restitution
	ci.m_restitution = 0.0f;

	// Set maximal velocity (Default is 20 m/s)
	// Help to predict unexpected movement (extreme acceleration, character fired out)
	// Remember: Depended on maxWalkSpeed (Influence to if you want to jump and run simultanously)
	// Increase it in the case of character on fast moving platforms
	ci.m_maxLinearVelocity = info.m_maxLinearVelocity;

	// Set maximal allowed penetration
	// Problems in combination jump+walk state:
	// [long jump + contact (one frame) + small jump (about 10 frames - continues dynamics)]
	// Increase to m_allowedPenetrationDepth = 0.02 helps, but smooth stairs behaviour is gone!
	//ci.m_allowedPenetrationDepth = 0.0f;

	ci.m_motionType = hkpMotion::MOTION_CHARACTER;
	ci.m_qualityType = HK_COLLIDABLE_QUALITY_CHARACTER;

	// By setting the  ProcessContactCallbackDelay to 0 we will receive callbacks for
	// any collisions processed for this body every frame (simulation step), i.e. the delay between
	// any such callbacks is 0 frames. Important for proper function of Mass Modifier
	ci.m_processContactCallbackDelay = 0;


	// Create rigid body of character
	m_character = new hkpRigidBody(ci);

	// Set to zero inverse local inertia to avoid proxy rotations. Must be done after rigid body creation!
	hkMatrix3 zeroInvInertia; zeroInvInertia.setZero();
	m_character->setInertiaInvLocal(zeroInvInertia);


	// Set rigid body to default transparent red color
	m_character->addProperty(HK_PROPERTY_DEBUG_DISPLAY_COLOR, info.m_vdbColor);

	// Values used for check support

	// Set down direction
	m_down.setNeg3(info.m_up);
	HK_ASSERT2(0x79d58ec9,  hkMath::equal(m_down.length3(), 1.0f), "checkSupport down direction should be normalized");

	// Set max slope cosine
	// It is a angle between UP and horizontal plane ???
	m_maxSlopeCosine = hkMath::cos(info.m_maxSlope);

	// Set number of user planes
	m_userPlanes = info.m_userPlane;

	// Set additional parameters for simplex solver
	m_maxSpeedForSimplexSolver = info.m_maxSpeedForSimplexSolver;
	m_penetrationRecoverySpeed = info.m_penetrationRecoverySpeed;

	// Create and register rigid body listener instance
	m_characterCollisionListener = new hkCharacterRigidBodyCollisionListener(info.m_maxForce, m_maxSlopeCosine, info.m_up);
	m_character->addCollisionListener(m_characterCollisionListener);


}

hkpCharacterRigidBody::~hkpCharacterRigidBody()
{
	m_character->removeCollisionListener(m_characterCollisionListener);
	m_characterCollisionListener->removeReference();

	m_character->removeProperty(HK_PROPERTY_DEBUG_DISPLAY_COLOR);
	m_character->removeReference();

}

void hkpCharacterRigidBody::checkSupport(const hkStepInfo& stepInfo, hkpSurfaceInfo& ground )
{

	HK_TIMER_BEGIN("checkSupport", HK_NULL);

	hkLocalArray<hkpSurfaceConstraintInfo> constraints( 20 );

	hkArray<hkpLinkedCollidable::CollisionEntry>& entries = m_character->getLinkedCollidable()->m_collisionEntries;

	for (int i = 0; i< entries.getSize(); ++i)
	{
		hkpContactMgr* mgr = entries[i].m_agentEntry->m_contactMgr;

		if (mgr->m_type == hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR)
		{

			hkpSimpleConstraintContactMgr* constraintMgr = reinterpret_cast<hkpSimpleConstraintContactMgr*>(mgr);

			// Loop over all contact points
			for (int j = 0; j < constraintMgr->m_contactConstraintData.getNumContactPoints(); ++j)
			{

				const int cpId = constraintMgr->m_contactConstraintData.getContactPointIdAt(j);

				hkpSurfaceConstraintInfo& constraint = constraints.expandOne();
				hkContactPoint& contactPoint = constraintMgr->m_contactConstraintData.getContactPoint(cpId);

#ifdef DEBUG_CHARACTER_RIGIDBODY
				debugContactPoint(contactPoint);
#endif

				//Extract Surface Constraint Info (normal, velocity, priority)
				{
					// count collidables order (normal from A to B or from B to A)
					hkSimdReal mul = entries[i].m_agentEntry->getCollidableA() == m_character->getCollidable() ? 1.0f : -1.0f;

					constraint.m_plane.setMul4( mul, contactPoint.getSeparatingNormal());
					constraint.m_plane(3) = contactPoint.getSeparatingNormal()(3);

					// Assume this is a low priority surface
					constraint.m_priority = 0;

					// Assume the velocity of this surface is 0
					constraint.m_velocity.setZero4();


					// Moving keyframed bodies
					hkpRigidBody* body = hkGetRigidBody(entries[i].m_partner);

					if (body)
					{
						// Extract point velocity

						// HVK-1871. This code gets the point velocity at the collision, based on how far
						// the object actually travelled, rather than the velocity result of the constraint solver.
						// (i.e. the value got from getPointVelocity)
						// When a heavy force pushes a rigid body into a fixed rigid body these values can diverge,
						// which can cause the character controller to penetrate the moving rigid body, as it sees
						// an incorrectly moving plane.

						// Note, this means that velocities will be one frame behind, so for accelerating platforms
						// (HVK-1477) (i.e. For keyframed or fixed objects) we just take the velocity, to make sure the
						// character does not sink in.
						if (body->isFixedOrKeyframed())
						{
							body->getPointVelocity(contactPoint.getPosition(), constraint.m_velocity);

						}
						else
						{
							// Problematic behaviour if collided with small body fired out (fast rotating)
							// See asymetric character demo
							//hkVector4 linVel;
							//hkVector4 angVel;
							//hkSweptTransformUtil::getVelocity(*body->getRigidMotion()->getMotionState(), linVel, angVel);
							//hkVector4 relPos; relPos.setSub4( contactPoint.getPosition(), body->getCenterOfMassInWorld() );
							// vel in contact point = velCG + omega x relPos;
							//constraint.m_velocity.setCross( angVel, relPos);
							//constraint.m_velocity.add4( linVel );
						}


						// Move the plane by the velocity, based on the timeTravelled HVK-1477
						//constraint.m_plane(3) -= static_cast<hkReal>(constraint.m_velocity.dot3(constraint.m_plane)) * timeTravelled;
						//constraint.m_plane(3) -= static_cast<hkReal>(constraint.m_velocity.dot3(constraint.m_plane)) * 0;


						// Extract priority
						// - Static objects have highest priority
						// - Then keyframed
						// - Then dynamic
						if (body->getMotionType() == hkpMotion::MOTION_FIXED)
						{
							constraint.m_priority = 2;
						}

						if (body->getMotionType() == hkpMotion::MOTION_KEYFRAMED)
						{
							constraint.m_priority = 1;
						}

					}

					// If penetrating we add extra velocity to push the character back out
					if ( constraint.m_plane(3) < -HK_REAL_EPSILON)
					{
						hkVector4 contactPointNormal; contactPointNormal.setMul4(mul, contactPoint.getSeparatingNormal());
						constraint.m_velocity.addMul4(-constraint.m_plane(3) * m_penetrationRecoverySpeed, contactPointNormal);
						constraint.m_plane(3) = 0.f;
					}

				}

				// TODO:
				// addMaxSlopePlane( m_maxSlopeCosine, m_up, i, constraints);

			}

		}

	}

	// Resize array if it is now too small to accommodate the user planes.
	if (constraints.getCapacity() - constraints.getSize() < m_userPlanes )
	{
		constraints.reserve(constraints.getSize() + m_userPlanes);
	}

	// Interactions array - this is the output of the simplex solver
	hkLocalArray<hkpSurfaceConstraintInteraction> interactions(constraints.getSize() + m_userPlanes);

	// Stored velocities - used to remember surface velocities to give the correct output surface velocity
	hkLocalArray<hkVector4> storedVelocities( constraints.getSize() + m_userPlanes );

	//
	//	Test Direction
	//
	hkpSimplexSolverInput input;
	hkpSimplexSolverOutput output;
	{
		input.m_position.setZero4();
		input.m_constraints = constraints.begin();
		input.m_numConstraints = constraints.getSize();
		input.m_velocity = m_down;
		input.m_deltaTime = stepInfo.m_deltaTime;
		input.m_minDeltaTime = stepInfo.m_deltaTime;
		input.m_upVector.setNeg3(m_down);
		input.m_maxSurfaceVelocity.setAll( m_maxSpeedForSimplexSolver );

		output.m_planeInteractions = interactions.begin();

		// Allow the user to do whatever they wish with the surface constraints
		//fireConstraintsProcessed( m_manifold, input );

		// Set the sizes of the arrays to be correct
		storedVelocities.setSize(input.m_numConstraints);
		interactions.setSize(input.m_numConstraints);
		constraints.setSize(input.m_numConstraints);

		// Remove velocities and friction to make this a query of the static geometry
		for (int i = 0; i < input.m_numConstraints; ++i )
		{
			storedVelocities[i] = constraints[i].m_velocity;
			constraints[i].m_velocity.setZero4();
		}

		hkSimplexSolverSolve( input, output );

	}

	ground.m_surfaceVelocity.setZero4();
	ground.m_surfaceNormal.setZero4();
	ground.m_surfaceMotionType = hkpMotion::MOTION_FIXED;

	if ( output.m_velocity.equals3( m_down ) )
	{
		ground.m_supportedState = hkpSurfaceInfo::UNSUPPORTED;
	}
	else
	{

		if ( output.m_velocity.lengthSquared3() < .001f )
		{
			ground.m_supportedState = hkpSurfaceInfo::SUPPORTED;
		}
		else
		{

			output.m_velocity.normalize3();
			hkReal angleSin = output.m_velocity.dot3(m_down);

			hkReal cosSqr = 1 - angleSin * angleSin;

			if (cosSqr < (m_maxSlopeCosine*m_maxSlopeCosine) )
			{
				ground.m_supportedState = hkpSurfaceInfo::SLIDING;
			}
			else
			{
				ground.m_supportedState = hkpSurfaceInfo::SUPPORTED;
			}
		}

	}

	if ( ground.m_supportedState != hkpSurfaceInfo::UNSUPPORTED )
	{
		hkInt32 numTouching = 0;

		for (int i=0; i < input.m_numConstraints; i++)
		{
			// If we touched this plane and it supports our direction
			if ((interactions[i].m_touched) && hkReal(constraints[i].m_plane.dot3(m_down)) < -0.08f)
			{
				ground.m_surfaceNormal.add4( constraints[i].m_plane );
				ground.m_surfaceVelocity.add4( storedVelocities[i] );
				numTouching++;

				// if at least one of surfaces is dynamic (lowest priority)
				if (constraints[i].m_priority == 0)
				{
					ground.m_surfaceMotionType = hkpMotion::MOTION_DYNAMIC;
				}
			}
		}

		if (numTouching > 0)
		{
			ground.m_surfaceNormal.normalize3();
			ground.m_surfaceVelocity.mul4(1.f / numTouching);
		}
		else
		{
			ground.m_supportedState = hkpSurfaceInfo::UNSUPPORTED;
		}

#ifdef DEBUG_CHARACTER_RIGIDBODY
		debugGround(m_character->getPosition(),ground);
#endif

	}

	HK_TIMER_END();

}

hkpRigidBody* hkpCharacterRigidBody::getRigidBody() const
{
	return m_character;
}

void hkpCharacterRigidBody::setLinearAccelerationToMassModifier(const hkVector4& newAcc)
{
	m_characterCollisionListener->setAcceleration(newAcc);
}

void hkpCharacterRigidBody::setLinearVelocity(const hkVector4& newVel)
{
	m_character->setLinearVelocity(newVel);
}

const hkVector4& hkpCharacterRigidBody::getLinearVelocity() const
{
	return m_character->getLinearVelocity();
}

void hkpCharacterRigidBody::setAngularVelocity(const hkVector4& newAVel)
{
	m_character->setAngularVelocity(newAVel);
}

const hkVector4& hkpCharacterRigidBody::getAngularVelocity() const
{
	return m_character->getAngularVelocity();
}

const hkVector4& hkpCharacterRigidBody::getPosition() const
{
	return m_character->getPosition();
}

#ifdef DEBUG_CHARACTER_RIGIDBODY

// This color represent the contact point
const hkInt32 HK_DEBUG_CONTACT_POINT_COLOR = hkColor::WHITE;

// Planes in this color represent the contact point plane
const hkInt32 HK_DEBUG_CONTACT_PLANE_COLOR = hkColor::WHITESMOKE;

static void debugContactPoint(hkContactPoint& cp)
{
	// Display contact point
	HK_DISPLAY_STAR(cp.getPosition(),0.2f,HK_DEBUG_CONTACT_POINT_COLOR);

	// Display contact plane
	hkVector4 plane = cp.getNormal();
	plane(3) = 0.0f;
	hkVector4 pos = cp.getPosition();
	HK_DISPLAY_PLANE(plane, pos, 0.5f, HK_DEBUG_CONTACT_PLANE_COLOR);
}

// This color represent the normal of dynamic surface
const hkInt32 HK_DEBUG_SURFACE_DYNAMIC_COLOR = hkColor::GREEN;

// This color represent the normal of fixed or keyframed surface
const hkInt32 HK_DEBUG_SURFACE_NONDYNAMIC_COLOR = hkColor::YELLOWGREEN;

// This color represent the surface velocity
const hkInt32 HK_DEBUG_SURFACE_VELOCITY_COLOR = hkColor::YELLOW;

static void debugGround(const hkVector4& position, const hkpSurfaceInfo& ground)
{
	// Display surface normal in center
	if (ground.m_surfaceMotionType == hkpMotion::MOTION_DYNAMIC)
	{
		HK_DISPLAY_ARROW( position, ground.m_surfaceNormal, HK_DEBUG_SURFACE_DYNAMIC_COLOR);
	}
	else
	{
		HK_DISPLAY_ARROW( position, ground.m_surfaceNormal, HK_DEBUG_SURFACE_NONDYNAMIC_COLOR);
	}

	// Display surface velocity
	HK_DISPLAY_ARROW( position, ground.m_surfaceVelocity,HK_DEBUG_SURFACE_VELOCITY_COLOR);

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
