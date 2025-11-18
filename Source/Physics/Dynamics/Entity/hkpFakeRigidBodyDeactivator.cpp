/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Entity/hkpFakeRigidBodyDeactivator.h>

enum hkpRigidBodyDeactivator::DeactivatorType hkpFakeRigidBodyDeactivator::getRigidBodyDeactivatorType() const 
{ 
	return hkpRigidBodyDeactivator::DEACTIVATOR_NEVER;
}

hkBool hkpFakeRigidBodyDeactivator::shouldDeactivateHighFrequency( const hkpEntity* entity )
{ 
	return false; 
}

hkBool hkpFakeRigidBodyDeactivator::shouldDeactivateLowFrequency( const hkpEntity* entity )
{ 
	return false; 
}

// Static member variable in hkpFakeRigidBodyDeactivator
hkpFakeRigidBodyDeactivator hkpFakeRigidBodyDeactivator::m_fakeRigidBodyDeactivator;

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
