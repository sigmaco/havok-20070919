/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Vehicle/DriverInput/Default/hkpVehicleDefaultAnalogDriverInput.h>

hkpVehicleDefaultAnalogDriverInput::hkpVehicleDefaultAnalogDriverInput()
{
	// deviceStatus
	m_slopeChangePointX = 0;
	m_initialSlope = 0;
	m_deadZone = 0;
	m_autoReverse = false;
}

hkpVehicleDriverInputStatus* hkpVehicleDriverInputAnalogStatus::clone() const
{
	hkpVehicleDriverInputAnalogStatus* r = new hkpVehicleDriverInputAnalogStatus;
	*r = *this;
	return r;
}

//void hkpVehicleDefaultAnalogDriverInput::init( const hkpVehicleInstance* vehicle )
//{
//	// The vehicle stores all cached data needed.
//}


hkReal hkpVehicleDefaultAnalogDriverInput::calcAcceleratorInput( const hkReal deltaTime ,const hkpVehicleInstance* vehicle, const hkpVehicleDriverInputAnalogStatus* deviceStatus, FilteredDriverInputOutput& input) const
{
	const hkBool currently_reversing = vehicle->m_isReversing;

	const hkReal device_input_y =
		(currently_reversing && m_autoReverse) ? - deviceStatus->m_positionY : deviceStatus->m_positionY ;

	if (device_input_y>0) return 0.0f;

	const hkReal acc_pedal = -1.0f * device_input_y;

	return acc_pedal;
}

hkReal hkpVehicleDefaultAnalogDriverInput::calcBrakeInput( const hkReal deltaTime, 
																const hkpVehicleInstance* vehicle, 
																const hkpVehicleDriverInputAnalogStatus* deviceStatus, 
																FilteredDriverInputOutput& FilteredDriverInputOutputOut ) const
{
	const hkBool currently_reversing = vehicle->m_isReversing;

	const hkReal device_input_y =
		(currently_reversing && m_autoReverse) ? - deviceStatus->m_positionY : deviceStatus->m_positionY ;

	if (device_input_y<0) return 0.0f;

	const hkReal brake_pedal = device_input_y;

	return brake_pedal;
}

hkReal hkpVehicleDefaultAnalogDriverInput::calcSteeringInput(	const hkReal deltaTime, 
																	const hkpVehicleInstance* vehicle, 
																	const hkpVehicleDriverInputAnalogStatus* deviceStatus, 
																	FilteredDriverInputOutput& FilteredDriverInputOutputOut )	const
{
	const hkReal joystick_input = deviceStatus->m_positionX;

    const hkReal abs_joystick_input = hkMath::fabs(joystick_input);

	// Dead Zone
	if (abs_joystick_input < m_deadZone)
	{
		return 0.0f;
	}

	// else First Slope

	const hkReal input_sign = (joystick_input > 0.0f) ? 1.0f : -1.0f;

    if(abs_joystick_input < m_slopeChangePointX)
	{
		const hkReal abs_steering = ( abs_joystick_input - m_deadZone) * (m_initialSlope);

		const hkReal steering = input_sign * abs_steering;

		return steering;
    }

	// else Second Slope
	{
		// These two values could be cached
		const hkReal slopeChangePointY = ( m_slopeChangePointX - m_deadZone) * m_initialSlope;
		const hkReal secondSlope       = (1.0f - slopeChangePointY ) / ( (1.0f - m_deadZone) - (m_slopeChangePointX - m_deadZone) );

		const hkReal abs_steering = slopeChangePointY + secondSlope * (abs_joystick_input - m_slopeChangePointX);

		const hkReal steering = input_sign * abs_steering;

		return steering;
	}
}

hkBool hkpVehicleDefaultAnalogDriverInput::calcTryingToReverse(	const hkReal deltaTime, 
																		const hkpVehicleInstance* vehicle, 
																		const hkpVehicleDriverInputAnalogStatus* deviceStatus, 
																		FilteredDriverInputOutput& FilteredDriverInputOutputOut)
{
	// If we are not in autoreverse mode, then reverse only happens when the driver hits the Reverse Button
	if (!m_autoReverse) 
	{
		return deviceStatus->m_reverseButtonPressed;
	}

	hkVector4 vec_vel = vehicle->getChassis()->getLinearVelocity();
	const hkReal lin_vel = vec_vel.length3();//.fastLength();
	const hkBool currently_reversing = vehicle->m_isReversing;
	const hkBool not_moving = (lin_vel < (5.0f / 3.6f)); // Almost stopped (move float to BP)
	const hkBool brake_pressed = deviceStatus->m_positionY > 0.1f;

	// If the break is pressed and we are moving
	if( (brake_pressed) && (lin_vel > HK_REAL_EPSILON) )
	{
		// Check if the car is going backwards
		hkVector4 for_dir_ls = vehicle->m_data->m_chassisOrientation.getColumn(1);

		hkTransform chassis_trans = vehicle->getChassis()->getTransform();
		hkVector4 for_dir_ws;
		for_dir_ws._setRotatedDir(chassis_trans.getRotation(), for_dir_ls);

		vec_vel.normalize3();
		for_dir_ws.normalize3();

		hkReal val = vec_vel.dot3(for_dir_ws);

		// If the car is going backwards then we should be in reversing.
		if(val < HK_REAL_EPSILON)
		{
			return true;
		}
	}

	// If we are reversing and moving we keep reversing
	// If we are reversing but stopped we keep reversing if the brake is pressed
	// If we are reversing, stopped and no brake is pressed, we don't reverse any more
	if (currently_reversing)
	{
		if (not_moving)
		{
			return brake_pressed;
		}

		// comment out the following else block if you want proper reversing on moving plattforms
		else
		{
			return true;
		}
	}

	// If we are not reversing, we start reversing only if we are stopped and pressing the brake
	if (not_moving && brake_pressed)
		return true;

	return false;
}

void hkpVehicleDefaultAnalogDriverInput::calcDriverInput( const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInputStatus* deviceStatus, FilteredDriverInputOutput& filteredInputOut )
{
	const hkpVehicleDriverInputAnalogStatus* analogDeviceStatus = (const hkpVehicleDriverInputAnalogStatus*)(deviceStatus);
	filteredInputOut.m_acceleratorPedalInput = calcAcceleratorInput( deltaTime, vehicle, analogDeviceStatus, filteredInputOut );
	filteredInputOut.m_brakePedalInput = calcBrakeInput( deltaTime, vehicle, analogDeviceStatus, filteredInputOut );
	filteredInputOut.m_steeringWheelInput = calcSteeringInput( deltaTime, vehicle, analogDeviceStatus, filteredInputOut );
	filteredInputOut.m_handbrakeOn = analogDeviceStatus->m_handbrakeButtonPressed;
	filteredInputOut.m_tryingToReverse = calcTryingToReverse( deltaTime, vehicle, analogDeviceStatus, filteredInputOut );
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
