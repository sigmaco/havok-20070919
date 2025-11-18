/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Actions/Motor/hkpMotorAction.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

hkpMotorAction::hkpMotorAction(hkpRigidBody* body, const hkVector4& axis, hkReal spinRate, hkReal gain) :
	hkpUnaryAction(body), m_axis(axis), m_spinRate(spinRate), m_gain(gain), m_active(true)
{
	m_axis.normalize4();
}


void hkpMotorAction::applyAction( const hkStepInfo& stepInfo )
{
	// Early exit if inactive.
	if (!m_active)
	{
		return;
	}

	hkpRigidBody* rb = static_cast<hkpRigidBody*>( m_entity );

	// Work out the current angular velocity in body space.
	const hkTransform& tr = rb->getTransform();
	hkVector4 curr;
	curr.setRotatedInverseDir(tr.getRotation(), rb->getAngularVelocity());
		
	// Calculate the difference between the desired spin rate and the current rate of spin
	// about the desired axis 'm_axis'.
	hkReal currentRate = m_axis.dot3(curr);
	hkReal diff(m_spinRate - currentRate);

	// Calculate the newTorque to apply based on the difference and the gain. The newTorque
	// should be proportional to each of difference, gain, and inertia
	// (to make the Action mass-independent).
	hkVector4 newTorque;
	newTorque.setMul4(diff * m_gain, m_axis);
	hkMatrix3 m;
	rb->getInertiaLocal(m);
	newTorque.setMul3(m, newTorque);

	newTorque.setRotatedDir(tr.getRotation(), newTorque);

	// Apply the new torque.
	rb->applyTorque(stepInfo.m_deltaTime, newTorque);
}

hkpAction* hkpMotorAction::clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const
{
	HK_ASSERT2(0xf5a8efca, newEntities.getSize() == 1, "Wrong clone parameters given to a motor action (needs 1 body).");
	if (newEntities.getSize() != 1) return HK_NULL;

	HK_ASSERT2(0x277857f0, newPhantoms.getSize() == 0, "Wrong clone parameters given to a motor action (needs 0 phantoms).");
	// should have no phantoms.
	if (newPhantoms.getSize() != 0) return HK_NULL;

	hkpMotorAction* ma = new hkpMotorAction( (hkpRigidBody*)newEntities[0], m_axis, m_spinRate, m_gain);
	ma->m_active = m_active;
	ma->m_userData = m_userData;

	return ma;
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
