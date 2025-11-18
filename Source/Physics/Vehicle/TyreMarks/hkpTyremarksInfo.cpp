/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/hkpVehicleInstance.h>
#include <Physics/Vehicle/TyreMarks/hkpTyremarksInfo.h>
#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>

hkpTyremarksWheel::hkpTyremarksWheel()
{
	m_numPoints = 0;
	m_currentPosition = 0;
	m_tyremarkPoints.clear();
}

void hkpTyremarksWheel::setNumPoints( int num_points )
{
	HK_ASSERT(0x0, num_points > 0 );
	m_numPoints = num_points;
	m_currentPosition = 0;

	for ( int i = 0 ; i < m_numPoints ; i++ )
	{
		hkpTyremarkPoint tyrePoint;
		m_tyremarkPoints.pushBack( tyrePoint );
	}
}

hkpTyremarkPoint::hkpTyremarkPoint()
{
	m_pointLeft.setZero4();
	m_pointRight.setZero4();
}

void hkpTyremarksInfo::calcStatistics( hkStatisticsCollector* collector ) const
{
	collector->beginObject( HK_NULL, collector->MEMORY_INSTANCE,  this );
	for ( int i = 0; i < m_tyremarksWheel.getSize(); i++)
	{
		const hkpTyremarksWheel* tm = m_tyremarksWheel[i];
		collector->addArray( "Points", collector->MEMORY_INSTANCE, tm->m_tyremarkPoints );
	}
	collector->endObject();
}


const hkpTyremarkPoint& hkpTyremarksWheel::getTyremarkPoint( int point) const
{
	const int index = ( m_currentPosition + point) % m_numPoints;
	// we add m_numPoints for the case m_currentPosition == point == 0
	// also due to the fact that we are using unsigned ints
	return m_tyremarkPoints[index];
}

hkReal hkpTyremarkPoint::getTyremarkStrength() const
{ 
	 return m_pointRight(3);
}

void hkpTyremarksWheel::addTyremarkPoint( hkpTyremarkPoint& point)
{
	const int previous_index = (m_currentPosition + m_numPoints - 1) % m_numPoints;

	const hkReal previous_strength = m_tyremarkPoints [previous_index].getTyremarkStrength();

	if ((point.getTyremarkStrength()==0.0f) && (previous_strength==0.0f)) 
	{
		return; // two tyremarks == 0.0f in a row, we can ignore this one;
	}

	m_tyremarkPoints[m_currentPosition] = point;
	
	m_currentPosition = ( m_currentPosition + 1 ) % m_numPoints;
}

hkpTyremarksInfo::hkpTyremarksInfo(const hkpVehicleData& data, int num_points)
{
	m_minTyremarkEnergy = 0;
	m_maxTyremarkEnergy = 0;

	m_tyremarksWheel.setSize( data.m_numWheels );
	for (int i = 0; i < m_tyremarksWheel.getSize() ; i++ )
	{
		hkpTyremarksWheel* tyremarksWheel = new hkpTyremarksWheel();
		tyremarksWheel->setNumPoints(num_points);
		m_tyremarksWheel[i] = tyremarksWheel;
	}
}

hkpTyremarksInfo::~hkpTyremarksInfo()
{
	for ( int sw_it = 0 ; sw_it < m_tyremarksWheel.getSize() ; sw_it++ )
	{
		m_tyremarksWheel[sw_it]->removeReference();
	}
}


void hkpTyremarksInfo::updateTyremarksInfo( hkReal timestep, const hkpVehicleInstance* vehicle )
{
	const hkTransform &car_transform = vehicle->getChassis()->getTransform();

	hkVector4 offset;
	offset.setMul4( timestep, vehicle->getChassis()->getLinearVelocity() ); 


	const hkVector4 &right_cs = vehicle->m_data->m_chassisOrientation.getColumn(2);
	hkVector4 right_ws;
	right_ws.setRotatedDir(car_transform.getRotation(),right_cs);

	int w_it;
	for (w_it=0; w_it< vehicle->m_data->m_numWheels; w_it++)
	{
		const hkpVehicleInstance::WheelInfo &wheel_info = vehicle->m_wheelsInfo[w_it];

		hkReal tyre_alpha = wheel_info.m_skidEnergyDensity;
		tyre_alpha -= m_minTyremarkEnergy;
		if (tyre_alpha > 0.0f)
		{
			tyre_alpha *= 255.0f / ( m_maxTyremarkEnergy - m_minTyremarkEnergy); // scaled between 0.0f and 255.0f

			if (tyre_alpha > 255.0f)
			{
				tyre_alpha = 255.0f;
			}
		}
		else
		{
			tyre_alpha = 0.0f;
		}

		const hkReal wheel_width = vehicle->m_data->m_wheelParams[w_it].m_width;
		const hkVector4 &contact_point_ws = vehicle->m_wheelsInfo[w_it].m_contactPoint.getPosition();
		const hkVector4 &normal_ws = vehicle->m_wheelsInfo[w_it].m_contactPoint.getNormal();

		hkVector4 a_little_up;
		a_little_up.setMul4(0.05f, normal_ws);

		hkVector4 point_ws;			point_ws.setAdd4( contact_point_ws, a_little_up);
		hkVector4 left;				left.setMul4( -0.5f * wheel_width, right_ws);
		hkVector4 point_left_ws; 	point_left_ws.setAdd4 ( point_ws, left);
		hkVector4 right;			right.setMul4( 0.5f * wheel_width, right_ws);
		hkVector4 point_right_ws;	point_right_ws.setAdd4( point_ws, right);

		point_left_ws.add4(offset);

		// this seems to cause an ICE in vc6
		//point_right_ws.add4(offset);
		point_right_ws(0) += offset(0);
		point_right_ws(3) += offset(3);

		hkpTyremarkPoint new_point;
		{
			new_point.m_pointLeft    = point_left_ws;
			new_point.m_pointLeft(3) = tyre_alpha;
			new_point.m_pointRight   = point_right_ws;
			new_point.m_pointRight(1) = point_right_ws.getSimdAt(1) + offset.getSimdAt(1);
			new_point.m_pointRight(2) = point_right_ws.getSimdAt(2) + offset.getSimdAt(2);

			new_point.m_pointRight(3) = tyre_alpha;
		}

		m_tyremarksWheel[w_it]->addTyremarkPoint(new_point);
	}
}


void hkpTyremarksInfo::getWheelTyremarksStrips( const hkpVehicleInstance* vehicle, int wheel, hkVector4 *strips_out) const
{

	const hkpTyremarksWheel &tyremarks_wheel = *m_tyremarksWheel[wheel];
	const int num_points = tyremarks_wheel.m_numPoints;

	for (int p_it=0; p_it< num_points; p_it++)
	{
		const hkpTyremarkPoint &tyre_point = tyremarks_wheel.getTyremarkPoint(p_it);

		strips_out [p_it * 2] = tyre_point.m_pointLeft;
		strips_out [p_it * 2 +1] = tyre_point.m_pointRight;
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
