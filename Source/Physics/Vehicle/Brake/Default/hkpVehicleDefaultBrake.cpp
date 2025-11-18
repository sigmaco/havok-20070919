/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Vehicle/Brake/Default/hkpVehicleDefaultBrake.h>

hkpVehicleDefaultBrake::hkpVehicleDefaultBrake()
{
	// m_wheelBrakingProperties
	m_wheelsMinTimeToBlock = 0;
}


void hkpVehicleDefaultBrake::calcBreakingInfo( const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& filteredDriverInfo, WheelBreakingOutput& breakingInfo )
{
	const hkReal user_pedal       = filteredDriverInfo.m_brakePedalInput; 
	const hkBool user_handbraking   = filteredDriverInfo.m_handbrakeOn;

	hkBool wheelsShouldBlock = false;
	{
		for (int w_it=0; w_it < vehicle->m_data->m_numWheels; w_it++)
		{
			// HANDBRAKE
			{
				breakingInfo.m_isFixed[w_it] = hkBool(user_handbraking & m_wheelBrakingProperties[w_it].m_isConnectedToHandbrake);
			}

			// WHEEL BLOCKING
			if (user_pedal > m_wheelBrakingProperties[w_it].m_minPedalInputToBlock)
			{
				wheelsShouldBlock = true;
			}


			// NORMAL (PEDAL) BRAKE
			{
				const hkpVehicleInstance::WheelInfo& wheel_info	= vehicle->m_wheelsInfo[w_it];
				const hkReal spin_speed = wheel_info.m_spinVelocity;
				const hkReal wheelMass = vehicle->m_data->m_wheelParams[w_it].m_mass;
				const hkReal radius = vehicle->m_data->m_wheelParams[w_it].m_radius;

				HK_ASSERT2(0xad45dee3, deltaTime > HK_REAL_EPSILON, "Non-zero deltaTime required for hkpVehicleDefaultBrake::calcBreakingInfo.");
				// Info: Why taking invDt? -- Calculate the maximum force, which doesn't make the vehicle change its direction of motion.
				hkReal braking_force = - (spin_speed * radius) * (wheelMass * (1.0f / deltaTime)); 
				hkReal braking_torque = braking_force * radius;

				const hkReal max_torque =  m_wheelBrakingProperties[w_it].m_maxBreakingTorque * user_pedal;

				if (  hkMath::fabs(braking_torque) > max_torque )
				{   // fast speed, use max_torque
					braking_torque = (braking_torque > 0.0f)? max_torque : - max_torque;
				}
				breakingInfo.m_brakingTorque[w_it] = braking_torque;
			}
		}
	}

	if ( wheelsShouldBlock )
	{
		if (breakingInfo.m_wheelsTimeSinceMaxPedalInput >= m_wheelsMinTimeToBlock)
		{
			for (int w_it=0; w_it<vehicle->m_data->m_numWheels; w_it++)
			{
				if ( user_pedal > m_wheelBrakingProperties[w_it].m_minPedalInputToBlock )
				{
					breakingInfo.m_isFixed[w_it] = true;
				}
			}
		}
		else
		{
			breakingInfo.m_wheelsTimeSinceMaxPedalInput += deltaTime;
		}
	}	
	else
	{
		breakingInfo.m_wheelsTimeSinceMaxPedalInput = 0.0f;
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
