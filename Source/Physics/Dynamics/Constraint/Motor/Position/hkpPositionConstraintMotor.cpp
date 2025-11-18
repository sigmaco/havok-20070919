/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Constraint/Motor/Position/hkpPositionConstraintMotor.h>
#include <Physics/ConstraintSolver/Constraint/hkpConstraintQueryIn.h>

HK_COMPILE_TIME_ASSERT( sizeof(hkpPositionConstraintMotor) <= sizeof(hkpMaxSizeConstraintMotor) );
#if ( HK_POINTER_SIZE == 4 )
HK_COMPILE_TIME_ASSERT( sizeof(hkpMaxSizeConstraintMotor) == 48 );
#endif

hkpPositionConstraintMotor::hkpPositionConstraintMotor( hkReal currentPosition )
: hkpLimitedForceConstraintMotor()
{
	m_type = TYPE_POSITION;
	setMaxForce(1e6f);
	m_tau = 0.8f;
	m_damping = 1.0f;
	m_constantRecoveryVelocity = 1.0f;
	m_proportionalRecoveryVelocity = 2.0f;
}

hkpConstraintMotor* hkpPositionConstraintMotor::clone() const
{
	hkpPositionConstraintMotor* pcm = new hkpPositionConstraintMotor( *this );
	return pcm;
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
