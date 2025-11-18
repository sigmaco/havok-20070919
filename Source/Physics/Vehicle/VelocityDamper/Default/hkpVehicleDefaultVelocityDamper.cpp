/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/hkpVehicleInstance.h>

#include <Physics/Vehicle/VelocityDamper/Default/hkpVehicleDefaultVelocityDamper.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

hkpVehicleDefaultVelocityDamper::hkpVehicleDefaultVelocityDamper()
{
	m_normalSpinDamping = 0;
	m_collisionSpinDamping = 0;
	m_collisionThreshold = 1.0f;
}


// can't be const because of the changing of one of the members (unless you make that member mutable)
void hkpVehicleDefaultVelocityDamper::applyVelocityDamping(const hkReal deltaTime, hkpVehicleInstance& vehicle )
{
	hkpRigidBody*	chassis_motionstate = vehicle.getChassis();
	hkVector4 angularVel = chassis_motionstate->getAngularVelocity();
	const hkReal spinSqrd = angularVel.lengthSquared3();

	hkReal exp_time;
	if (spinSqrd > m_collisionThreshold * m_collisionThreshold)
	{
		exp_time = hkMath::max2( 0.0f, 1.0f - deltaTime * m_collisionSpinDamping );
	}
	else
	{
		exp_time = hkMath::max2( 0.0f, 1.0f - deltaTime * m_normalSpinDamping );
	}

	hkVector4 newAngVel; newAngVel.setMul4( exp_time, angularVel);
	
	chassis_motionstate ->setAngularVelocity( newAngVel);
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
