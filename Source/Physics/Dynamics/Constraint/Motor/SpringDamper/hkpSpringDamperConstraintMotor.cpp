/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Constraint/Motor/SpringDamper/hkpSpringDamperConstraintMotor.h>
#include <Physics/ConstraintSolver/Constraint/hkpConstraintQueryIn.h>

HK_COMPILE_TIME_ASSERT( sizeof(hkpSpringDamperConstraintMotor) <= sizeof(hkpMaxSizeConstraintMotor) );

hkpSpringDamperConstraintMotor::hkpSpringDamperConstraintMotor()
: hkpLimitedForceConstraintMotor()
{
	m_type = TYPE_SPRING_DAMPER;
	setMaxForce(1e6f);
	m_springConstant = 0.0f;
	m_springDamping = 0.0f;
}

// Construct a motor with the given properties.
hkpSpringDamperConstraintMotor::hkpSpringDamperConstraintMotor( hkReal springConstant, hkReal springDamping, hkReal maxForce )
: hkpLimitedForceConstraintMotor()
{
	m_type = TYPE_SPRING_DAMPER;
	setMaxForce(maxForce);
	m_springConstant = springConstant;
	m_springDamping = springDamping;
}

hkpConstraintMotor* hkpSpringDamperConstraintMotor::clone() const
{
	hkpSpringDamperConstraintMotor* sdcm = new hkpSpringDamperConstraintMotor( *this );
	return sdcm;
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
