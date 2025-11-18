/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Vehicle/Steering/Default/hkpVehicleDefaultSteering.h>

hkpVehicleDefaultSteering::hkpVehicleDefaultSteering()
{
	m_maxSteeringAngle = 0;
	m_maxSpeedFullSteeringAngle = 0;
	// m_doesWheelSteer
}

void hkpVehicleDefaultSteering::calcMainSteeringAngle( const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& filteredInfoOutput, SteeringAnglesOutput& steeringOutput )
{
	const hkReal input_value = filteredInfoOutput.m_steeringWheelInput;

	steeringOutput.m_mainSteeringAngle = input_value * m_maxSteeringAngle;

	// Calculate the velocity of the car.
	const hkTransform &car_transform = vehicle->getChassis()->getTransform();
	const hkVector4& forward_cs = vehicle->m_data->m_chassisOrientation.getColumn(1);

	//const hkVector4 forward_ws = car_transform.getTransformedDir(forward_cs);
	hkVector4 forward_ws;
	forward_ws.setRotatedDir(car_transform.getRotation(),forward_cs);

	const hkReal chassis_lin_vel = vehicle->getChassis()->getLinearVelocity().dot3(forward_ws);

	if (chassis_lin_vel > m_maxSpeedFullSteeringAngle)
	{
		// Clip steering angle.
		const hkReal s_factor = m_maxSpeedFullSteeringAngle / chassis_lin_vel;
		steeringOutput.m_mainSteeringAngle = steeringOutput.m_mainSteeringAngle  * s_factor * s_factor;
	}
}

void hkpVehicleDefaultSteering::calcSteering( const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& filteredInfoOutput, SteeringAnglesOutput& steeringOutput )
{
	// Calculate main steering angle
	calcMainSteeringAngle( deltaTime, vehicle, filteredInfoOutput, steeringOutput );

	// Set to 0 for wheels that do not steer
	for (int w_it = 0; w_it < m_doesWheelSteer.getSize(); w_it++) 
	{
		if (m_doesWheelSteer[w_it])
		{
			steeringOutput.m_wheelsSteeringAngle[w_it] = steeringOutput.m_mainSteeringAngle;
		}
		else
		{
			steeringOutput.m_wheelsSteeringAngle[w_it] = 0.0f;
		}
	}
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
