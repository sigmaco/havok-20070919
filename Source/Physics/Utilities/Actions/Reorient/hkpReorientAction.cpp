/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Actions/Reorient/hkpReorientAction.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

hkpReorientAction::hkpReorientAction()
: hkpUnaryAction( HK_NULL ),
  m_strength(0), 
  m_damping(0)
{
	m_rotationAxis.setZero4();	
	m_upAxis.setZero4();		
}

hkpReorientAction::hkpReorientAction( hkpRigidBody* body,
										 const hkVector4& rotationAxis,
										 const hkVector4& upAxis,
										 hkReal strength,
										 hkReal damping )
: hkpUnaryAction( body )
{
	m_rotationAxis = rotationAxis;
	m_upAxis = upAxis;
	m_strength = strength;
	m_damping = damping;
}

void hkpReorientAction::applyAction( const hkStepInfo& stepInfo )
{
	// Move the world axis into body space
	hkpRigidBody* rb = static_cast<hkpRigidBody*>( m_entity );

	hkVector4 bodyUpAxis;		bodyUpAxis.setRotatedDir( rb->getRotation(), m_upAxis );
	hkVector4 bodyRotationAxis;	bodyRotationAxis.setRotatedDir( rb->getRotation(), m_rotationAxis );

	// Project the world up axis onto the plane that has
	// a normal the same as the body rotation axis.
	hkVector4 projectedUpAxis = m_upAxis;
	const hkReal distance = projectedUpAxis.dot3( bodyRotationAxis );
	projectedUpAxis.addMul4( -distance, bodyRotationAxis );
	projectedUpAxis.normalize3();

	// Get angle between the up axis of the rigid body
	// and the project world up axis.
	hkReal angle = hkMath::acos( bodyUpAxis.dot3( projectedUpAxis ) );

	// If we cross the rigid body up axis with the projected 
	// world up axis we should get a vector thats runs parallel 
	// to the bodies rotation axis. The sign of the value
	// representing the major axis of each vector should match.
	// When the signs don't match then the calculated rotation
	// axis runs in the opposite direction and we need to flip
	// the sign of the angle.
	hkVector4 calculatedRotationAxis; calculatedRotationAxis.setCross( bodyUpAxis, projectedUpAxis );
	hkReal cra	= calculatedRotationAxis( calculatedRotationAxis.getMajorAxis() );
	hkReal ra	= bodyRotationAxis( bodyRotationAxis.getMajorAxis() );
	if( !(hkMath::isNegative( cra ) == hkMath::isNegative( ra )) )
	{
		angle = -angle;
	}

	// Apply the orientating angular impulse including an angular
	// velocity damping factor.
	hkVector4 av; 
	av.setMul4( m_damping * stepInfo.m_invDeltaTime, rb->getAngularVelocity() );

	hkVector4 impulse; 
	impulse.setMul4( m_strength * angle * stepInfo.m_invDeltaTime, bodyRotationAxis );
	impulse.sub4( av );

	rb->applyAngularImpulse( impulse );
}

hkpAction* hkpReorientAction::clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const
{
	HK_ASSERT2(0xf578efca, newEntities.getSize() == 1, "Wrong clone parameters given to a reorient action (needs 1 body).");
	// should have two entities as we are a unary action.
	if (newEntities.getSize() != 1) return HK_NULL;

	HK_ASSERT2(0x2d353b28, newPhantoms.getSize() == 0, "Wrong clone parameters given to a reorient action (needs 0 phantoms).");
	// should have no phantoms.
	if (newPhantoms.getSize() != 0) return HK_NULL;

	hkpReorientAction* ra = new hkpReorientAction( (hkpRigidBody*)newEntities[0], m_rotationAxis, 
													m_upAxis, m_strength, m_damping );
	ra->m_userData = m_userData;
	return ra;
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
