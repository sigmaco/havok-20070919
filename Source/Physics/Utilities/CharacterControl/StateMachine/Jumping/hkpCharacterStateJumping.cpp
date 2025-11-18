/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>
#include <Physics/Utilities/CharacterControl/StateMachine/Jumping/hkpCharacterStateJumping.h>
#include <Physics/Utilities/CharacterControl/StateMachine/Util/hkpCharacterMovementUtil.h>

#include <Physics/Dynamics/World/hkpWorld.h>

hkpCharacterStateJumping::hkpCharacterStateJumping()
{
	m_jumpHeight = 1.5f;
}

	// Return the state type
hkpCharacterStateType hkpCharacterStateJumping::getType() const 
{
	return HK_CHARACTER_JUMPING;
}
	/// Process the user input - causes state transition.
void hkpCharacterStateJumping::change(hkpCharacterContext& context, const hkpCharacterInput& input, hkpCharacterOutput& output)
{

}

	/// Process the user input - causes state actions.
void hkpCharacterStateJumping::update(hkpCharacterContext& context, const hkpCharacterInput& input, hkpCharacterOutput& output)
{
	//
	// Jump - v^2 = u^2 + 2 a s
	// At apex of jump v^2 = 0 so u = hkMath::sqrt(2 a s);
	//	
	if (m_jumpCounter == 0)
	{
		hkVector4 impulse = input.m_characterGravity;
		const hkReal	a = hkReal( impulse.normalizeWithLength3() );
		const hkReal	s = hkMath::fabs( m_jumpHeight );
		const hkReal	u = hkMath::sqrt( 2 * a * s );
		impulse.mul4( -u );

		hkVector4 relVelocity; relVelocity.setSub4( input.m_velocity, input.m_surfaceVelocity );
		hkReal curRelVel = relVelocity.dot3( input.m_up );

		if (curRelVel < u)
		{
			output.m_velocity.setAddMul4(input.m_velocity, input.m_up, u-curRelVel );
		}
	}

	if (m_jumpCounter == 1)
	{
		context.setState(HK_CHARACTER_IN_AIR, input, output);
	}
	m_jumpCounter++;
}

hkReal hkpCharacterStateJumping::getJumpHeight() const
{
	return m_jumpHeight;
}

void hkpCharacterStateJumping::setJumpHeight( hkReal jumpHeight )
{
	m_jumpHeight = jumpHeight;
}

void hkpCharacterStateJumping::enterState( hkpCharacterContext& context, hkpCharacterStateType prevState, const hkpCharacterInput& input, hkpCharacterOutput& output )
{
	m_jumpCounter = 0;
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
