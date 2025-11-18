/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>
#include <Physics/Vehicle/hkpVehicleInstance.h>

#include <Common/Base/Monitor/hkMonitorStream.h> 
#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h> 
#include <Physics/Dynamics/Motion/Util/hkpRigidMotionUtil.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Motion/Rigid/hkpBoxMotion.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/Motion/Rigid/hkpFixedRigidMotion.h>

#include <Physics/Vehicle/Brake/hkpVehicleBrake.h>
#include <Physics/Vehicle/Engine/hkpVehicleEngine.h>
#include <Physics/Vehicle/TyreMarks/hkpTyremarksInfo.h>
#include <Physics/Vehicle/Steering/hkpVehicleSteering.h>
#include <Physics/Vehicle/Suspension/hkpVehicleSuspension.h>
#include <Physics/Vehicle/DriverInput/hkpVehicleDriverInput.h>
#include <Physics/Vehicle/AeroDynamics/hkpVehicleAerodynamics.h>
#include <Physics/Vehicle/Transmission/hkpVehicleTransmission.h>
#include <Physics/Vehicle/WheelCollide/hkpVehicleWheelCollide.h>
#include <Physics/Vehicle/VelocityDamper/hkpVehicleVelocityDamper.h>

#include <Physics/ConstraintSolver/Vehiclefriction/hkpVehicleFrictionSolver.h>

hkpVehicleInstance::hkpVehicleInstance( hkpRigidBody* chassis ) :
	hkpUnaryAction(chassis)
{
	m_data = HK_NULL;
	m_driverInput = HK_NULL;
	m_steering = HK_NULL;
	m_engine = HK_NULL;
	m_transmission = HK_NULL;
	m_brake = HK_NULL;
	m_suspension = HK_NULL;
	m_aerodynamics = HK_NULL;
	m_wheelCollide = HK_NULL;
	m_tyreMarks = HK_NULL;
	m_velocityDamper = HK_NULL;
	m_deviceStatus = HK_NULL;
}

void hkpVehicleInstance::setChassis ( hkpRigidBody* chassis )
{
	setEntity(chassis);
}

void hkpVehicleInstance::WheelInfo::init()
{
	hkVector4 up; up = hkQuadReal0100;
	m_contactPoint.set( hkVector4::getZero(), up, 1);
	
	m_contactFriction = 0.0f;
	m_contactBody = HK_NULL;
	m_contactShapeKey = hkpShapeKey(-1);
	m_rayEndPointWs.setZero4();

	m_hardPointWs.setZero4();
	m_rayEndPointWs.setZero4();
	m_currentSuspensionLength = 0.0f;
	m_suspensionDirectionWs.setZero4();
	
	m_spinAxisCs.setZero4();
	m_spinAxisWs.setZero4();
	m_spinAxisCs.set(1.0f, 0.0f, 0.0f);
	m_steeringOrientationCs.setIdentity();

	m_spinVelocity = 0.0f;
	m_spinAngle = 0.0f;
	m_skidEnergyDensity = 0.0f;
	m_sideForce = 0.0f;
	m_forwardSlipVelocity = 0.0f;
	m_sideSlipVelocity = 0.0f;
}

hkpVehicleInstance::~hkpVehicleInstance()
{
	m_data->removeReference();
	m_driverInput->removeReference();
	m_steering->removeReference();
	m_engine->removeReference();
	m_transmission->removeReference();
	m_brake->removeReference();
	m_suspension->removeReference();
	m_aerodynamics->removeReference();
	m_wheelCollide->removeReference();
	m_velocityDamper->removeReference();
	m_deviceStatus->removeReference();

	// Tyremarks are an optional component
	if(m_tyreMarks != HK_NULL)
	{
		m_tyreMarks->removeReference();
	}
}


void hkpVehicleInstance::init()
{
	// The initialization of the data modifies the chassis
	if (!m_data->m_alreadyInitialised)
	{
		m_data->init( m_suspension->m_wheelParams, getChassis());
	}

	//
	//	Create an inertia matrix for normal vehicle operation
	//

	{  // set diagonal of rot inertia tensor for normal stuff
		hkVector4 y,r,p;

		y.setAbs4( m_data->m_chassisOrientation.getColumn(0) );
		r.setAbs4( m_data->m_chassisOrientation.getColumn(1) );
		p.setAbs4( m_data->m_chassisOrientation.getColumn(2) );

		hkVector4 unitDiagonal;
		unitDiagonal.setMul4(m_data->m_chassisUnitInertiaYaw,   y);
		unitDiagonal.addMul4(m_data->m_chassisUnitInertiaRoll,  r);
		unitDiagonal.addMul4(m_data->m_chassisUnitInertiaPitch, p);

		hkVector4 diagonal; diagonal.setMul4( getChassis()->getMass(), unitDiagonal);

		hkMatrix3 matrix;
		matrix.setIdentity();
		matrix.setDiagonal(diagonal(0),diagonal(1),diagonal(2));

		getChassis()->setMass( getChassis()->getMass() );
		getChassis()->setInertiaLocal(matrix);

		// check that we have the correct inertia type for our chassis
		HK_ASSERT2(0x5c819b4e, (getChassis()->getMotionType() == hkpMotion::MOTION_BOX_INERTIA) || (getChassis()->getMotionType() == hkpMotion::MOTION_THIN_BOX_INERTIA), "Vehicle chassis MUST be of type hkpRigidBodyCinfo::MOTION_BOX_INERTIA or hkpRigidBodyCinfo::MOTION_THIN_BOX_INERTIA");
	}

	m_wheelsInfo.setSize( m_data->m_numWheels );
	{ for (int i=0;i<m_wheelsInfo.getSize();i++) { m_wheelsInfo[i].init(); } }


	m_isFixed.setSize( m_data->m_numWheels );
	{ for (int i=0;i<m_isFixed.getSize();i++) { m_isFixed[i] = false; } }
	m_wheelsTimeSinceMaxPedalInput = 0.0f;

	m_mainSteeringAngle = 0.0f;
	m_wheelsSteeringAngle.setSize( m_data->m_numWheels );
	{ for (int i=0;i<m_wheelsSteeringAngle.getSize();i++) { m_wheelsSteeringAngle[i] = 0.0f; } }
	
	// engine
	m_torque = 0.0f;
	m_rpm = 0.0f;

	// transmission
	m_isReversing = false;
	m_currentGear = 0;
	m_delayed = false;
	m_clutchDelayCountdown = 0.0f;

	// wheel collide
	m_wheelCollide->init( this );

	// ensure that any components that should not be shared aren't.
	HK_ASSERT2(0x4e34565e, !m_wheelCollide->m_alreadyUsed, "The wheelCollide component cannot be shared between different vehicle instances.");
	m_wheelCollide->m_alreadyUsed = true;
}


void hkpVehicleInstance::handleFixedGroundAccum( hkpRigidBody* ground, hkpVelocityAccumulator& accum )
{
	accum.setFixed();
}

void hkpVehicleInstance::updateWheelsHardPoints(const hkTransform &car_transform)
{
	// Chassis status : From the Rigid Body itself
	HK_INTERNAL_TIMER_BEGIN("updateWheelsHardPoints", HK_NULL);

	//
	//	Copy data into the wheels info
	//
	for (int w_it=0; w_it < m_data->m_numWheels; w_it ++)
	{
		WheelInfo &wheel_info = m_wheelsInfo[ w_it ];

		wheel_info.m_suspensionDirectionWs.setRotatedDir( car_transform.getRotation(), m_suspension->m_wheelParams[w_it].m_directionCs );
		wheel_info.m_hardPointWs.setTransformedPos(  car_transform, m_suspension->m_wheelParams[w_it].m_hardpointCs);

		const hkVector4& start_ws = wheel_info.m_hardPointWs;

		const hkReal    spr_length = m_suspension->m_wheelParams[w_it].m_length;
		const hkReal	wheel_radius = m_data->m_wheelParams[w_it].m_radius;

		wheel_info.m_rayEndPointWs.setAddMul4( start_ws, wheel_info.m_suspensionDirectionWs, spr_length + wheel_radius);
	}

	HK_INTERNAL_TIMER_END();
}

// Apply action method
void hkpVehicleInstance::applyAction(const hkStepInfo& stepInfo)
{
	const hkReal deltaTime = stepInfo.m_deltaTime;

	HK_USER_TIMER_BEGIN("Vehicle", this);
	HK_INTERNAL_TIMER_BEGIN_LIST( "vehicle" , "hardpointWs" );
	
		//
		//	Copy data into the wheels info
		//
	const hkTransform &car_transform = getChassis()->getTransform();

		// we are updating the hard points again, as the vehicle might have been
		// moved by hand;
	updateWheelsHardPoints(car_transform);

	hkpVehicleWheelCollide::CollisionDetectionWheelOutput* cdInfo = hkAllocateStack<hkpVehicleWheelCollide::CollisionDetectionWheelOutput>( m_data->m_numWheels);
	{
		HK_INTERNAL_TIMER_SPLIT_LIST("raycast");
		{
			m_wheelCollide->collideWheels( deltaTime, this, cdInfo );

			//
			// Copy back data to the wheelInfo that the user may be interested in.
			//
			for ( int w_it = 0 ; w_it < m_wheelsInfo.getSize() ; w_it++ )
			{
				m_wheelsInfo[w_it].m_currentSuspensionLength = cdInfo[w_it].m_currentSuspensionLength;
				m_wheelsInfo[w_it].m_contactPoint = cdInfo[w_it].m_contactPoint;
				m_wheelsInfo[w_it].m_contactFriction = cdInfo[w_it].m_contactFriction;
				m_wheelsInfo[w_it].m_contactBody = cdInfo[w_it].m_contactBody;
				m_wheelsInfo[w_it].m_contactShapeKey = cdInfo[w_it].m_contactShapeKey;
			}
		}


		// Update of the wheels angle / velocity  using friction information for graphics display
		// (nothing to do with raycasting now)
		// ========================================================================================
		HK_INTERNAL_TIMER_SPLIT_LIST("wheels angle");

		for (int w_it=0; w_it<m_data->m_numWheels; w_it++)
		{
			//
			// Spin angle calculation are done later inside ground test to take account of 
			// surface velocity 
			// 

			WheelInfo &wheel_info = m_wheelsInfo[ w_it ];// note is non-const &

			//
			// Steering and wheel position 
			//
			{
				const hkReal steering_angle = m_wheelsSteeringAngle[w_it];

				// setAxisAngle version optimized for small angles
				hkQuaternion steering_rotation;
				{
					hkReal halfAngle = 0.5f * steering_angle;
					hkReal sinHalf = halfAngle;
					steering_rotation.m_vec.setMul4(sinHalf, m_suspension->m_wheelParams[w_it].m_directionCs);
					steering_rotation.m_vec(3) = 1;
					steering_rotation.m_vec.normalize4();
				}
				wheel_info.m_steeringOrientationCs = steering_rotation;
				wheel_info.m_spinAxisCs = m_data->m_chassisOrientation.getColumn(2);

				hkVector4 spin_axis_cs;
				spin_axis_cs.setRotatedDir(wheel_info.m_steeringOrientationCs, wheel_info.m_spinAxisCs);

				wheel_info.m_spinAxisWs.setRotatedDir(car_transform.getRotation(), spin_axis_cs);
			}
		}
	}

	HK_INTERNAL_TIMER_SPLIT_LIST("components");

	    //
	    // Driver Input
	    //
	hkpVehicleDriverInput::FilteredDriverInputOutput filteredDriverInputInfo;
	{
		{
			filteredDriverInputInfo.m_tryingToReverse = m_tryingToReverse;
			m_driverInput->calcDriverInput( deltaTime, this, m_deviceStatus, filteredDriverInputInfo );
			m_tryingToReverse = filteredDriverInputInfo.m_tryingToReverse;
		}
	}

		//
		//	Steering
		//
	hkpVehicleSteering::SteeringAnglesOutput steeringInfo;
	{
		steeringInfo.m_mainSteeringAngle = m_mainSteeringAngle;
		steeringInfo.m_wheelsSteeringAngle.setSize( m_wheelsSteeringAngle.getSize() );
		{
			for ( int i = 0 ; i < m_wheelsSteeringAngle.getSize() ; i++ )
			{
				steeringInfo.m_wheelsSteeringAngle[i] = m_wheelsSteeringAngle[i];
			}
		}
		m_steering->calcSteering( deltaTime, this, filteredDriverInputInfo, steeringInfo );

		m_mainSteeringAngle = steeringInfo.m_mainSteeringAngle;
		{
			for ( int i = 0 ; i < m_wheelsSteeringAngle.getSize() ; i++ )
			{
				m_wheelsSteeringAngle[i] = steeringInfo.m_wheelsSteeringAngle[i];
			}
		}
	}

		//
		//	Transmission
		//
	hkpVehicleTransmission::TransmissionOutput transmissionInfo;
	{
		transmissionInfo.m_numWheelsTramsmittedTorque = m_data->m_numWheels;
		transmissionInfo.m_wheelsTransmittedTorque = hkAllocateStack<hkReal>( transmissionInfo.m_numWheelsTramsmittedTorque);
		transmissionInfo.m_isReversing = m_isReversing;
		transmissionInfo.m_currentGear = m_currentGear;
		transmissionInfo.m_delayed = m_delayed;
		transmissionInfo.m_clutchDelayCountdown = m_clutchDelayCountdown;
		m_transmission->calcTransmission( deltaTime, this, transmissionInfo );
		m_isReversing = transmissionInfo.m_isReversing;
		m_currentGear = transmissionInfo.m_currentGear;
		m_delayed = transmissionInfo.m_delayed;
		m_clutchDelayCountdown = transmissionInfo.m_clutchDelayCountdown;
	}

		//
		//	Engine
		//
	hkpVehicleEngine::EngineOutput engineInfo;
	{
		engineInfo.m_rpm = m_rpm;
		engineInfo.m_torque = m_torque;
		m_engine->calcEngineInfo( deltaTime, this, filteredDriverInputInfo, transmissionInfo, engineInfo );
		m_rpm = engineInfo.m_rpm;
		m_torque = engineInfo.m_torque;
	}

		//
		// copy the brake cache data to the output structure
		//
	hkpVehicleBrake::WheelBreakingOutput wheelBreakingInfo;
	{
		wheelBreakingInfo.m_isFixed.setSize( m_isFixed.getSize() );
		wheelBreakingInfo.m_brakingTorque.setSize( m_isFixed.getSize() );
		{
			for (int i = 0 ; i < m_isFixed.getSize() ; i++ )
			{
				wheelBreakingInfo.m_isFixed[i] = m_isFixed[i];
			}
		}
		wheelBreakingInfo.m_wheelsTimeSinceMaxPedalInput = m_wheelsTimeSinceMaxPedalInput;

		m_brake->calcBreakingInfo( deltaTime, this, filteredDriverInputInfo, wheelBreakingInfo );

		// copy back the brake cache data
		{
			for (int i = 0 ; i < wheelBreakingInfo.m_isFixed.getSize() ; i++ )
			{
				m_isFixed[i] = wheelBreakingInfo.m_isFixed[i];
			}
			m_wheelsTimeSinceMaxPedalInput = wheelBreakingInfo.m_wheelsTimeSinceMaxPedalInput;
		}
	}

		//
		//	Suspension forces
		//
	hkInplaceArray<hkReal,16> suspensionForces; 	suspensionForces.setSize(m_data->m_numWheels);
	{
		m_suspension->calcSuspension( deltaTime, this, cdInfo, suspensionForces.begin() );
	}


	hkpVehicleAerodynamics::AerodynamicsDragOutput aerodynamicsDragInfo;
	{
		m_aerodynamics->calcAerodynamics( deltaTime, this, aerodynamicsDragInfo );
	}


	HK_INTERNAL_TIMER_SPLIT_LIST("simulate");

	
	//
	// doSimulationStep
	//
	
	{
		// To implement vehicles with more than two axles, they should be considered to
		// have only two axles, where one axles has the steering wheels and the other axle
		// has the rest of them
		HK_ASSERT(0x606560c5, m_data->m_numWheelsPerAxle.getSize() == 2);


		// Aerodynamics 
		// ================================================================================================================
		{
			const hkVector4& aero_force_ws  = aerodynamicsDragInfo.m_aerodynamicsForce;
			const hkVector4& aero_torque_ws = aerodynamicsDragInfo.m_aerodynamicsTorque;

			hkReal dtime = deltaTime;
			hkVector4 aeroimp;    aeroimp.setMul4( dtime, aero_force_ws);
			hkVector4 aeroAngImp; aeroAngImp.setMul4( dtime, aero_torque_ws);

			hkpMotion* chassis = getChassis()->getRigidMotion();

			aeroimp.addMul4( dtime * chassis->getMass(), m_data->m_gravity );

			//
			//	Apply gravity now, do not wait for the integrator
			//
			hkVector4 negGravity; negGravity.setMul4( -chassis->getMass(), m_data->m_gravity );
			chassis->applyForce( deltaTime, negGravity );
			chassis->applyLinearImpulse(aeroimp);
			chassis->applyAngularImpulse(aeroAngImp);
		}

		// Before applying the friction solver, we call the external controllers
		if ( m_velocityDamper != HK_NULL )
		{
			m_velocityDamper->applyVelocityDamping(deltaTime, *this);
		}

		// ================================================================================================================
		// Per Wheel Behaviors
		// ================================================================================================================
		hkpVehicleFrictionSolverParams frictionParams;
		for (int i = 0; i < 2; i++)
		{
			frictionParams.m_axleParams[i].initialize();
		}

		hkReal estimatedCarVelocity = getChassis()->getLinearVelocity().length3();

		hkpRigidBody *groundBody[2] = { HK_NULL, HK_NULL };

		for (int w_it = 0 ; w_it < m_data->m_numWheels ; w_it++)
		{
			const int axle = m_data->m_wheelParams[w_it].m_axle;

			const WheelInfo&	 wheel_info		= m_wheelsInfo[w_it];

			const hkVector4& spin_axis_ws = wheel_info.m_spinAxisWs;

			// Suspension forces
			// ==============================================================================================================
			const hkReal suspension_force = suspensionForces[w_it];
			{
				hkVector4 susp_impulse_ws;	susp_impulse_ws.setMul4( deltaTime * suspension_force, cdInfo[w_it].m_contactPoint.getNormal() );

				if (suspension_force > 0)
				{
					getChassis()->applyPointImpulse(susp_impulse_ws, wheel_info.m_hardPointWs );
				}

				hkpRigidBody* ground = cdInfo[w_it].m_contactBody;
				if (ground != HK_NULL)
				{

					// HVK-962: Vehicle force feedback parameter needs asserts
					// -------------------------------------------------------
					// Negative values should likely not be allowed. Similarly, 
					// very large values are probably not appropriate. 
					//	We may also want to add an assert at the point that a massive chassis vs 
					// lightweight object interaction might occur, or add some extra inverse 
					// sliding scale factor that will account for differences in masses. I.e.: 

					//  1. When object mass / chassis mass >= 1.0f 
					//	use m_wheelsForceFeedbackMultiplier. 

					//	2. As object mass / chassis mass -> 0.0f 
					//	use m_maxContactBodyAcceleration to limit the maximum acceleration 

					HK_ASSERT2( 0x38521c64, m_data->m_wheelParams[w_it].m_forceFeedbackMultiplier >= 0.0f, "Negative values are not allowed for the force feedback multiplier");

					if ( m_data->m_wheelParams[w_it].m_forceFeedbackMultiplier > 20.0f )
					{
						HK_WARN_ONCE(0x5582dad2, "The force feedback multiplier value is large - the forces being applied to objects the vehicle runs over will be clipped.");
					}

					hkReal mul = -m_data->m_wheelParams[w_it].m_forceFeedbackMultiplier;
					susp_impulse_ws.setMul4(mul, susp_impulse_ws);


					// Limit the (linear) acceleration according to the m_maxContactBodyAcceleration
					// a = velocity change / time = ( 1/m * impulse )/deltaTime --> impulse = mda

					hkReal mda = m_data->m_wheelParams[w_it].m_maxContactBodyAcceleration * ground->getMass() * deltaTime;

					if ( mda * mda < susp_impulse_ws.lengthSquared3() )
					{
						// Set the inpulse to be correct according to this acceleration
						susp_impulse_ws.normalize3(); 
						hkReal multiplier = m_data->m_wheelParams[w_it].m_maxContactBodyAcceleration * ground->getMass() * deltaTime;
						susp_impulse_ws.setMul4( multiplier, susp_impulse_ws );
					}

					// Apply impulse to rigid body in contact with wheel aka 'ground' in most cases. 
					// In this case we directly ignore any multithreaded issues and directly go to the motion (bypassing all checks)
					// this is not deterministic in a mt environment, but at least it works
					ground->getRigidMotion()->applyPointImpulse(susp_impulse_ws,wheel_info.m_hardPointWs);

					// search for the ground with the highest mass
					if ( (!groundBody[axle]) || ground->getMassInv() < groundBody[axle]->getMassInv()  )
					{
						groundBody[axle] = ground;
					}
				}
			}			

			// Engine & Brake Torque
			// ===============================================================================================================
			hkReal total_linear_force = 0.0f;
			{
				const hkReal total_torque = wheelBreakingInfo.m_brakingTorque[ w_it ] + transmissionInfo.m_wheelsTransmittedTorque[ w_it ];
				total_linear_force = total_torque / m_data->m_wheelParams[w_it].m_radius;
			}

			// Axle-Dependant Friction parameters
			// ===================================================================================================================
			const hkVector4 &contact_ws     = cdInfo[w_it].m_contactPoint.getPosition();
			const hkVector4 &surf_normal_ws = cdInfo[w_it].m_contactPoint.getNormal();
			hkVector4 forward_ws;		forward_ws.setCross(surf_normal_ws, spin_axis_ws);
			if ( hkReal( forward_ws.lengthSquared3()) < HK_REAL_EPSILON )
			{
				forward_ws.setCross( spin_axis_ws, m_wheelsInfo[w_it].m_suspensionDirectionWs );
			}
			forward_ws.normalize3();

			hkVector4 constraint_normal_ws;	constraint_normal_ws.setCross(forward_ws,surf_normal_ws);

			hkpVehicleFrictionSolverAxleParams &axle_params = frictionParams.m_axleParams[axle];

			// using wheel_importance is very flaky !
			// please don't use it
			//#define USE_IMPORTANCE
#ifdef USE_IMPORTANCE
			const hkReal wheel_importance = suspension_force + 0.01f;
#else
			const hkReal wheel_importance = 1.0f / m_data->m_numWheelsPerAxle[axle];
#endif

			// Use friction of wheel and landscape
			const hkReal contactFriction = cdInfo[w_it].m_contactFriction;
			const hkReal frictionFactor = wheel_importance * contactFriction;

			axle_params.m_contactPointWs.addMul4( wheel_importance, contact_ws );
			axle_params.m_constraintNormalWs.add4( constraint_normal_ws);
			axle_params.m_forwardDirWs.add4( forward_ws);
			axle_params.m_frictionCoefficient			+= frictionFactor * m_data->m_wheelParams[w_it].m_friction ;
			axle_params.m_viscosityFrictionCoefficient	+= frictionFactor * m_data->m_wheelParams[w_it].m_viscosityFriction;
			axle_params.m_maxFrictionCoefficient		+= frictionFactor * m_data->m_wheelParams[w_it].m_maxFriction;
			axle_params.m_wheelDownForce				+= suspension_force;
			axle_params.m_forwardForce					+= total_linear_force;
			axle_params.m_wheelFixed				    = axle_params.m_wheelFixed || m_isFixed[w_it];
			axle_params.m_slipVelocityFactor			+= wheel_importance* m_data->m_wheelParams[w_it].m_slipAngle * estimatedCarVelocity;

		} // (end for each wheel)


		// More Friction Parameters
		// =========================================================
		hkpVelocityAccumulator groundAccum[2];
		hkpVelocityAccumulator groundAccumAtIntegration[2];
		{
			frictionParams.m_maxVelocityForPositionalFriction = m_data->m_maxVelocityForPositionalFriction;
			for (int ax_it=0; ax_it<m_data->m_numWheelsPerAxle.getSize(); ax_it++)
			{
				hkpVehicleFrictionSolverAxleParams &axle_params = frictionParams.m_axleParams[ax_it];
				axle_params.m_constraintNormalWs.normalize3();
				axle_params.m_forwardDirWs.normalize3();
	#ifdef USE_IMPORTANCE
				const hkReal inv_total_importance = 1.0f / (axle_params.m_wheelDownForce + 0.01f * m_data->m_numWheelsPerAxle[ax_it]);
				axle_params.m_contactPoint.m_position.   mul4(inv_total_importance);
				axle_params.m_frictionCoefficient.       mul4(inv_total_importance);
				axle_params.m_viscosityFrictionCoefficient *= inv_total_importance;
				axle_params.m_slipVelocityFactor           *= inv_total_importance;
				axle_params.m_maxFrictionCoefficient       *= inv_total_importance;
				HK_ASSERT2(0x681e3abc,  axle_params.m_maxFrictionCoefficient > 0.0f, "New wheel parameter 'maxFriction' (since version 2.2.1) not set" );
	#endif
				hkpRigidBody* ground = groundBody[ax_it];
				axle_params.m_groundObject = & groundAccum[ax_it];
				axle_params.m_groundObjectAtLastIntegration = &groundAccum[ax_it];

				if ( !ground  )
				{
					groundAccum[ax_it].setFixed();
				}
				else if ( ground->isFixed() )
				{
					handleFixedGroundAccum( ground, groundAccum[ax_it] );
				}
				else if ( ax_it > 0 && ground == groundBody[0] )
				{
					axle_params.m_groundObject = frictionParams.m_axleParams[0].m_groundObject;
					axle_params.m_groundObjectAtLastIntegration = frictionParams.m_axleParams[0].m_groundObjectAtLastIntegration;
				}
				else
				{
					hkpMotion* motion = ground->getRigidMotion();
					hkRigidMotionUtilApplyForcesAndBuildAccumulators( stepInfo, &motion, 1, 0, &groundAccum[ax_it] );

					// If the vehicle is much heavier than the object it collides with (and/or the wheels slip due to the object's friction)
					// the wheel can end up with a very high slip velocity that it then fails to recover from,
					// here we clip relative masses to maxMassRatio:1 if necessary
					const hkReal chassisMassInv = getChassis()->getRigidMotion()->getMassInv();
					const hkReal groundMassInv  = motion->getMassInv();
					hkReal maxMassRatio = m_data->m_maxFrictionSolverMassRatio;
					if ( chassisMassInv * maxMassRatio < groundMassInv)
					{
						// Scale mass by f to get masses to be 1:maxMassRatio (car:body) so scale inverse masses by inverse of this
						hkReal massRatio = chassisMassInv / groundMassInv;
						hkReal f = massRatio * maxMassRatio;
						groundAccum[ax_it].m_invMasses.mul4( f );
					}

					const hkMotionState* ms = motion->getMotionState();
					hkVector4 linVel;
					hkVector4 angVel;
					hkSweptTransformUtil::getVelocity( *ms, linVel, angVel );

					groundAccumAtIntegration[ax_it] = groundAccum[ax_it];
					axle_params.m_groundObjectAtLastIntegration = &groundAccumAtIntegration[ax_it];
					groundAccumAtIntegration[ax_it].m_angularVel._setRotatedDir( groundAccum[ax_it].getCoreFromWorldMatrix(), angVel );
					groundAccumAtIntegration[ax_it].m_linearVel  = linVel;
				}
			}
		}

		//	Prepare rigid body data for the friction solver
		// =========================================================
		{
			hkpRigidBody* chassis = getChassis();
			hkpMotion* motion = chassis->getRigidMotion();
			hkRigidMotionUtilApplyForcesAndBuildAccumulators( stepInfo, &motion, 1, 0, &frictionParams.m_chassis );

			const hkMotionState* ms = getChassis()->getRigidMotion()->getMotionState();
			hkVector4 linVel;
			hkVector4 angVel;
			hkSweptTransformUtil::getVelocity( *ms, linVel, angVel );

			// override the inertia matrix in local space
			frictionParams.m_chassis.m_invMasses = m_data->m_chassisFrictionInertiaInvDiag;
			frictionParams.m_chassisAtLastIntegration = frictionParams.m_chassis;
			frictionParams.m_chassisAtLastIntegration.m_angularVel.setRotatedDir( frictionParams.m_chassis.getCoreFromWorldMatrix(), angVel );
			frictionParams.m_chassisAtLastIntegration.m_linearVel = linVel;
			}

		// fast turn torque
		// =========================================================
		if ( m_data->m_extraTorqueFactor )
		{
			hkReal f = m_mainSteeringAngle * m_data->m_extraTorqueFactor * deltaTime;
			hkVector4 localDv; localDv.setMul4( f, m_data->m_chassisOrientation.getColumn(0) );
			localDv.mul4( m_data->m_chassisFrictionInertiaInvDiag );
			frictionParams.m_chassis.m_angularVel.add4(localDv );
		}



		// WE APPLY THE FRICTION SOLVER
		// =================================================================================
		{
			hkpVehicleStepInfo vehStepInfo;
			vehStepInfo.m_deltaTime = stepInfo.m_deltaTime;
			vehStepInfo.m_invDeltaTime = stepInfo.m_invDeltaTime;
			hkVehicleFrictionApplyVehicleFriction( vehStepInfo, m_data->m_frictionDescription, frictionParams, m_frictionStatus );
		}

		// write back results
		// =================================================================================
		{
			//
			//	Apply the force on the vehicle
			//
			{
				hkpMotion* chassis = getChassis()->getRigidMotion();

				hkVector4 angVelWs; angVelWs._setMul3( chassis->getTransform().getRotation(), frictionParams.m_chassis.m_angularVel);
				chassis->setAngularVelocity( angVelWs );
				chassis->setLinearVelocity(  frictionParams.m_chassis.m_linearVel );
			}

			//
			// Apply the force on the ground objects
			//
			for (int ax_it=0; ax_it<m_data->m_numWheelsPerAxle.getSize(); ax_it++)
			{
				hkpVehicleFrictionSolverAxleParams &axle_params = frictionParams.m_axleParams[ax_it];
				if ( groundBody[ax_it] && !groundBody[ax_it]->isFixed() )
				{
					if ( (ax_it==0)  || (groundBody[0] != groundBody[1]))
					{
						hkpMotion* motion = groundBody[ax_it]->getRigidMotion();
						hkVector4 angVelWs; angVelWs._setRotatedInverseDir( axle_params.m_groundObject->getCoreFromWorldMatrix(), axle_params.m_groundObject->m_angularVel);
						hkVector4 linVelWs = axle_params.m_groundObject->m_linearVel;

						//
						// Clip angular velocity
						//
						{
								hkVector4 maxVelChange; maxVelChange.setAll3( deltaTime * 10.0f );

								hkVector4 oldVel = motion->getAngularVelocity();
								hkVector4 diff;   diff.setSub4( angVelWs, oldVel );
								diff.setMin4( diff, maxVelChange );
								maxVelChange.setNeg4( maxVelChange );
								diff.setMax4( diff, maxVelChange );
								angVelWs.setAdd4( oldVel, diff );
							}

						//
						// Clip linear velocity
						//
						{
							hkVector4 maxVelChange; maxVelChange.setAll3( deltaTime * 10.0f );

							hkVector4 oldVel = motion->getLinearVelocity();
							hkVector4 diff;   diff.setSub4( linVelWs, oldVel );
							diff.setMin4( diff, maxVelChange );
							maxVelChange.setNeg4( maxVelChange );
							diff.setMax4( diff, maxVelChange );
							linVelWs.setAdd4( oldVel, diff );
						}

						motion->setAngularVelocity( angVelWs );
						motion->setLinearVelocity(  linVelWs );
					}
				}
			}
		}

		// Now, we update the friction (skid) information on the wheels
		// Only do skidmarks if the wheel is driving an a fixed object
		// =================================================================================
		{
			for (int w_it=0; w_it< m_data->m_numWheels; w_it++)
			{
				WheelInfo &wheel_info = m_wheelsInfo[w_it];

				const int axle = m_data->m_wheelParams[w_it].m_axle;

				hkpVehicleFrictionStatus::AxisStatus& astat = m_frictionStatus.m_axis[axle];

				wheel_info.m_skidEnergyDensity = ( (cdInfo[w_it].m_contactBody != HK_NULL) && (cdInfo[w_it].m_contactBody->isFixed()) ) ?  astat.m_skid_energy_density : 0.0f;
				wheel_info.m_sideForce = astat.m_side_force;
				wheel_info.m_sideSlipVelocity = astat.m_side_slip_velocity;
				wheel_info.m_forwardSlipVelocity = astat.m_forward_slip_velocity;

				//
				// JF: Moved wheel spin angle to here to factor in relative surface vel
				//

				hkVector4 forward_ws;	forward_ws.setRotatedDir( car_transform.getRotation(), m_data->m_chassisOrientation.getColumn(1) );

				const hkReal chassis_lin_vel = getChassis()->getLinearVelocity().dot3(forward_ws);

				if ( ! m_isFixed[w_it] )
				{
					const hkReal virt_wheel_velocity = chassis_lin_vel + wheel_info.m_forwardSlipVelocity;

					hkReal surface_relative_wheel_vel = virt_wheel_velocity;

					if( groundBody[axle] )
					{
						const hkVector4 linVelWs = frictionParams.m_axleParams[axle].m_groundObject->m_linearVel;
                        surface_relative_wheel_vel = virt_wheel_velocity - static_cast<hkReal>(linVelWs.dot3( forward_ws ));
					}
					
					const hkReal spin_velocity = ( surface_relative_wheel_vel ) / (m_data->m_wheelParams[w_it].m_radius);
					wheel_info.m_spinVelocity = spin_velocity;
					const hkReal current_angle = wheel_info.m_spinAngle;
					const hkReal delta_angle = spin_velocity * deltaTime;

					wheel_info.m_spinAngle = current_angle + delta_angle;
				}
				else
				{
					wheel_info.m_spinVelocity = 0.0f;
				}
			}
		}
	}

	HK_INTERNAL_TIMER_END_LIST();
	HK_USER_TIMER_END();

	// Deallocate all spaces allocated at the start of this function in reverse order
	hkDeallocateStack( transmissionInfo.m_wheelsTransmittedTorque );
	hkDeallocateStack( cdInfo );
}



// Calculate the current position and rotation of a wheel for the graphics engine
void hkpVehicleInstance::calcCurrentPositionAndRotation( const hkpRigidBody* chassis, const hkpVehicleSuspension* suspension, int wheelNo, hkVector4& posOut, hkQuaternion& rotOut )
{
	WheelInfo& wi = m_wheelsInfo[wheelNo];

	//
	//	concatenate the matrices for the wheels: todo: move to update graphics, allows for LOD levels
	//
	{
		const hkReal spin_angle = wi.m_spinAngle;
		const hkQuaternion spin_rotation( wi.m_spinAxisCs, -spin_angle);

		const hkQuaternion& chassis_orientation = chassis->getRotation();
		hkQuaternion tmp;	tmp.setMul(chassis_orientation,wi.m_steeringOrientationCs);
		rotOut.setMul(tmp,spin_rotation);		
	}


	const hkReal suspLen = hkMath::max2( 0.0f, wi.m_currentSuspensionLength );
	posOut._setTransformedPos(	chassis->getTransform(), suspension->m_wheelParams[wheelNo].m_hardpointCs);
	posOut.addMul4( suspLen, wi.m_suspensionDirectionWs );
}


hkReal hkpVehicleInstance::calcRPM() const
{
	return m_rpm;
}


// Two speed calculations for the camera
hkReal hkpVehicleInstance::calcKMPH() const
{
	const hkReal vel_ms = getChassis()->getLinearVelocity().length3();
	const hkReal vel_kmh = vel_ms / 1000.0f * 3600.0f;

	return vel_kmh;
}

hkReal hkpVehicleInstance::calcMPH() const
{
	const hkReal vel_ms = getChassis()->getLinearVelocity().length3();
	const hkReal vel_mph = vel_ms / 1609.3f * 3600.0f;

	return vel_mph;
}

void hkpVehicleInstance::getPhantoms( hkArray<hkpPhantom*>& phantomsOut )
{
	m_wheelCollide->getPhantoms( phantomsOut );
}

hkpAction* hkpVehicleInstance::clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const
{ 
	hkpRigidBody* newChassis = (hkpRigidBody*) newEntities[0];
	hkpVehicleInstance* newV = new hkpVehicleInstance( newChassis );
	*newV = *this;

	newV->setWorld(HK_NULL);
	newV->setSimulationIsland(HK_NULL);

	// referenced already in constructor above
	newV->m_entity = newChassis;

	// Wheel collide can't be shared (phantoms etc based on the chassis)
	newV->m_wheelCollide = m_wheelCollide->clone( newPhantoms );
	newV->m_wheelCollide->m_alreadyUsed = true;

	// Clone the device status so the vehicles can move individually.
	newV->m_deviceStatus = this->m_deviceStatus->clone();

	// All the rest can be shared
	newV->m_data->addReference();
	newV->m_driverInput->addReference();
	newV->m_steering->addReference();
	newV->m_engine->addReference();
	newV->m_transmission->addReference();
	newV->m_brake->addReference();
	newV->m_suspension->addReference();
	newV->m_aerodynamics->addReference();
	newV->m_velocityDamper->addReference(); 

	// Tyremarks are an optional componant
	if(m_tyreMarks != HK_NULL)
	{
		newV->m_tyreMarks->addReference();
	}

	return newV;
}


void hkpVehicleInstance::calcStatistics( hkStatisticsCollector* collector ) const
{
	collector->beginObject( "Vehicle", collector->MEMORY_INSTANCE,  this );

	collector->addArray( "WheelInfo", collector->MEMORY_INSTANCE, m_wheelsInfo );
	collector->addArray( "WheelInfo", collector->MEMORY_INSTANCE, m_wheelsSteeringAngle );
	collector->addArray( "WheelInfo", collector->MEMORY_INSTANCE, m_isFixed );

	collector->addChildObject( "Data", collector->MEMORY_SHARED, m_data );
	collector->addChildObject( "DriverInput", collector->MEMORY_SHARED, m_driverInput);
	collector->addChildObject( "Steering", collector->MEMORY_SHARED, m_steering);
	collector->addChildObject( "Engine", collector->MEMORY_SHARED, m_engine);
	collector->addChildObject( "Transmission", collector->MEMORY_SHARED, m_transmission);
	collector->addChildObject( "Brake", collector->MEMORY_SHARED, m_brake);
	collector->addChildObject( "Suspension", collector->MEMORY_SHARED, m_suspension);
	collector->addChildObject( "Aerodynamics", collector->MEMORY_SHARED, m_aerodynamics);
	if(m_tyreMarks != HK_NULL)
	{
		collector->addChildObject( "Tyremarks", collector->MEMORY_SHARED, m_tyreMarks);
	}
	collector->addChildObject( "VelDamper", collector->MEMORY_SHARED, m_velocityDamper);
	collector->endObject();
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
