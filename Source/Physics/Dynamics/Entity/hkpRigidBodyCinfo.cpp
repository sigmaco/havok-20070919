/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

hkpRigidBodyCinfo::hkpRigidBodyCinfo()
{
	m_position.setZero4();
	m_rotation.setIdentity();
	m_linearVelocity.setZero4();
	m_angularVelocity.setZero4();
	m_inertiaTensor.setDiagonal(1.0f, 1.0f, 1.0f);
	m_centerOfMass.setZero4();
	m_mass = 1.0f;
	m_linearDamping = 0.0f;
	m_angularDamping = 0.05f;
	m_friction = 0.5f;
	m_restitution = 0.4f;
	m_maxLinearVelocity = 200.0f;
	m_maxAngularVelocity = 200.0f;
	m_allowedPenetrationDepth = -1.0f;
	m_motionType = hkpMotion::MOTION_DYNAMIC;
	m_rigidBodyDeactivatorType = hkpRigidBodyDeactivator::DEACTIVATOR_SPATIAL;
	m_solverDeactivation = SOLVER_DEACTIVATION_LOW;
	m_qualityType = HK_COLLIDABLE_QUALITY_INVALID;
	m_collisionResponse = hkpMaterial::RESPONSE_SIMPLE_CONTACT;
	m_processContactCallbackDelay = 0xffff;
	m_collisionFilterInfo = 0;
	m_shape = HK_NULL;
	m_autoRemoveLevel = 0;
	m_numUserDatasInContactPointProperties = 0;
	m_forceCollideOntoPpu = false;
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
