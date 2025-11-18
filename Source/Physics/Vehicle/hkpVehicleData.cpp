/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/hkpVehicleData.h>
#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Physics/ConstraintSolver/Vehiclefriction/hkpVehicleFrictionSolver.h>

hkpVehicleData::hkpVehicleData()
{
	m_numWheels = 0;
	m_chassisOrientation.setZero();
	m_torqueRollFactor = 0.0f;
	m_torquePitchFactor = 0.0f;
	m_torqueYawFactor = 1.0f;
	m_extraTorqueFactor = 0.0f;
	m_maxVelocityForPositionalFriction = 10.0f;
	m_chassisUnitInertiaYaw = 1.0f;
	m_chassisUnitInertiaRoll = 1.0f;
	m_chassisUnitInertiaPitch = 1.0f;
	m_frictionEqualizer = 0.0f;
	m_normalClippingAngle = 0.1f;
	// m_wheelParams
	// m_wheelsAxle
	// m_numWheelsPerAxle
	m_chassisFrictionInertiaInvDiag.setZero4();
	m_gravity.setZero4();
	m_alreadyInitialised = false;
	m_maxFrictionSolverMassRatio = 30.0f;
}

void hkpVehicleData::init( const hkArray<struct hkpVehicleSuspension::SuspensionWheelParameters>& suspensionWheelParams, hkpRigidBody* chassis)
{
	// This initialisation should be called only once.
	HK_ASSERT( 0x0, !m_alreadyInitialised );
	m_alreadyInitialised = true;	

	//
	// Check that data is consistent, in particular that every array that should contain
	// as many elements as there are wheels actually does.
	//
	HK_ASSERT( 0x0, m_numWheels > 0 );
	HK_ASSERT( 0x0, m_wheelParams.getSize() == m_numWheels );

	// Check if the chassis coordinate space defines a valid rotation (check if it's determinant
	// is not zero)
#ifdef HK_DEBUG
	hkReal determinant;
	{
		hkVector4 r0; r0.setCross( m_chassisOrientation.getColumn(1), m_chassisOrientation.getColumn(2) );
		determinant = m_chassisOrientation.getColumn(0).dot3(r0);
	}
	HK_ASSERT2( 0x65456786, hkMath::fabs(determinant) > HK_REAL_EPSILON * 100, " Please specify a non-zero rotation for the chassis orientation system.");
#endif


	
	//
	// Wheels
	//
	


	// 1) Count the number of axles
	int w_it;
	int newNumAxles = 0;
	for (w_it=0; w_it< m_numWheels; w_it++)
	{
		const int wheel_axle = m_wheelParams[w_it].m_axle;
		if ( ( wheel_axle + 1 ) > newNumAxles)
		{
			newNumAxles = wheel_axle + 1;
		}
	}	

	if(newNumAxles > m_numWheelsPerAxle.getSize()) // need to resize?
	{
		m_numWheelsPerAxle.setSize(newNumAxles);
	}

	// 2) Count the number of wheels on each axle
	for (int ax_it=0; ax_it<m_numWheelsPerAxle.getSize(); ax_it++)
	{
		m_numWheelsPerAxle[ax_it] = 0;
	}

	for (w_it=0; w_it<m_numWheels; w_it++)
	{
		const int wheel_axle = m_wheelParams[w_it].m_axle;
		m_numWheelsPerAxle[wheel_axle]++;
	}

	//
	//	Create a special friction inertia
	//
	{  // set diagonal of rot inertia tensor for normal stuff
		hkMatrix3 matrix;
		matrix.setIdentity();
		hkVector4 y,r,p;

		y.setAbs4( m_chassisOrientation.getColumn(0) );
		r.setAbs4( m_chassisOrientation.getColumn(1) );
		p.setAbs4( m_chassisOrientation.getColumn(2) );


		hkVector4 unitDiagonal;
		HK_ASSERT2(0x5adbef9e,  m_torqueYawFactor != 0.0f, "m_torqueYawFactor cannot be zero! Leave at default or change value.");
		unitDiagonal.setMul4( m_torqueYawFactor   / m_chassisUnitInertiaYaw,   y);
		unitDiagonal.addMul4( m_torqueRollFactor  / m_chassisUnitInertiaRoll,  r);
		unitDiagonal.addMul4( m_torquePitchFactor / m_chassisUnitInertiaPitch, p);
		unitDiagonal(3) = 1.0f;

		m_chassisFrictionInertiaInvDiag.setMul4( 1.0f / chassis->getMass(), unitDiagonal);
	}

	{
		hkpVehicleFrictionDescription::Cinfo ci;
		ci.m_chassisCenterOfMass = chassis->getCenterOfMassLocal();


		const hkRotation& t= chassis->getTransform().getRotation();

		{
			const hkVector4& invIn = m_chassisFrictionInertiaInvDiag;
			hkMatrix3 in;
			in.getColumn(0).setMul4( invIn(0), t.getColumn(0) );
			in.getColumn(1).setMul4( invIn(1), t.getColumn(1) );
			in.getColumn(2).setMul4( invIn(2), t.getColumn(2) );
			ci.m_chassisFrictionInertiaInv.setMulInverse( in , t );
		}
		ci.m_chassisMassInv = chassis->getMassInv();

		// Check that this is the value of the forward direction
		ci.m_directionUp.setAbs4( m_chassisOrientation.getColumn(0) );
		ci.m_directionFront.setAbs4( m_chassisOrientation.getColumn(1) );
		ci.m_directionRight.setAbs4( m_chassisOrientation.getColumn(2) );

		ci.m_frictionEqualizer = m_frictionEqualizer;
		{
			for (int a = 0; a < 2; a++ )
			{
				ci.m_wheelAxleAngularInertia[a] = 0.0f;
			}
			for (int i = 0 ; i < m_numWheels; i++ )
			{
				int axle = m_wheelParams[i].m_axle;
				ci.m_wheelRadius[axle]  = m_wheelParams[i].m_radius;
				ci.m_wheelPosition[axle].setAddMul4( suspensionWheelParams[i].m_hardpointCs , 
					suspensionWheelParams[i].m_directionCs,
					suspensionWheelParams[i].m_length );
				ci.m_wheelAxleAngularInertia[axle] += m_wheelParams[i].m_radius * m_wheelParams[i].m_mass;
			}
		}
		hkVehicleFrictionDescriptionInitValues(ci , m_frictionDescription );
	}
}

void hkpVehicleData::calcStatistics( hkStatisticsCollector* collector ) const
{
	collector->beginObject( HK_NULL, collector->MEMORY_SHARED,  this );
	collector->addArray( "WheelParams", collector->MEMORY_SHARED, m_wheelParams );
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
