/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Vehicle/Engine/Default/hkpVehicleDefaultEngine.h>

hkpVehicleDefaultEngine::hkpVehicleDefaultEngine()
{
	m_minRPM = 1000.0f;
	m_optRPM = 4000.0f;
	m_maxRPM = 6000.0f;
	m_maxTorque = 800.0f;
	m_torqueFactorAtMinRPM = 1.0f;
	m_torqueFactorAtMaxRPM = 1.0f;
	m_resistanceFactorAtMinRPM = 0.0f;
	m_resistanceFactorAtOptRPM = 0.0f;
	m_resistanceFactorAtMaxRPM = 0.0f;
	m_clutchSlipRPM = 2000.0f;
}


void hkpVehicleDefaultEngine::calcEngineInfo( const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& filteredDriverInputInfo, const hkpVehicleTransmission::TransmissionOutput& transmissionInfo, EngineOutput& engineOutput )
{

	//
	// Calc RPM
	//

	engineOutput.m_rpm = transmissionInfo.m_transmissionRPM;

	const hkReal driver_acc = filteredDriverInputInfo.m_acceleratorPedalInput;

	if ( engineOutput.m_rpm < m_minRPM )
	{
		const hkReal clutchSlipRPM = m_clutchSlipRPM;
		hkReal rpm = driver_acc * clutchSlipRPM;
		const hkReal slopeChangePointX = 0.5f * m_minRPM;
		if ( engineOutput.m_rpm < slopeChangePointX )
		{
			engineOutput.m_rpm = m_minRPM + rpm;
		}
		else
		{
			engineOutput.m_rpm = m_minRPM + rpm * (engineOutput.m_rpm - slopeChangePointX) / (m_minRPM - slopeChangePointX);
		}
	}


	//
	// Calc Torque
	//

	hkReal torque;
	hkReal resistance;
	{
		const hkReal dx = engineOutput.m_rpm - m_optRPM; // how far from optimum

	
		if ( dx < 0  )
		{
			const hkReal inv_dmin = 1.0f / ( m_minRPM - m_optRPM );
			const hkReal resistanceSlope_OptToMin = ( m_resistanceFactorAtMinRPM - m_resistanceFactorAtOptRPM ) * inv_dmin;
			const hkReal torqueParFactor_OptToMin = ( m_torqueFactorAtMinRPM - 1.0f ) * inv_dmin * inv_dmin;

			resistance = m_maxTorque * (dx *      resistanceSlope_OptToMin + m_resistanceFactorAtOptRPM);
			torque =     m_maxTorque * (dx * dx * torqueParFactor_OptToMin + 1.0f);

			const hkReal transmission_rpm = transmissionInfo.m_transmissionRPM;

			if (  transmission_rpm < m_minRPM ) // check for very slow speeds and scale down resistance
			{
				resistance *= transmission_rpm / m_minRPM; 
			}
		}
		else if ( engineOutput.m_rpm < m_maxRPM)
		{
			const hkReal inv_dmax = 1.0f / ( m_maxRPM - m_optRPM );
			const hkReal resistanceSlope_OptToMax = ( m_resistanceFactorAtMaxRPM - m_resistanceFactorAtOptRPM ) * inv_dmax;
			const hkReal torqueParFactor_OptToMax = ( m_torqueFactorAtMaxRPM - 1.0f ) * inv_dmax * inv_dmax;


			resistance = m_maxTorque * (dx * resistanceSlope_OptToMax + m_resistanceFactorAtOptRPM);
			torque =     m_maxTorque * (dx * dx * torqueParFactor_OptToMax + 1.0f);
		}
		else
		{  // max rpm exceeded
			engineOutput.m_rpm = m_maxRPM;
			torque = 0.0f;
			resistance = m_resistanceFactorAtMaxRPM * m_maxTorque;
		}
	}

	engineOutput.m_torque = torque * driver_acc - resistance;
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
