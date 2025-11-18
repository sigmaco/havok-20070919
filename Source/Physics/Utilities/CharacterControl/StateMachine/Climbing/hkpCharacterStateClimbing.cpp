/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>
#include <Physics/Utilities/CharacterControl/StateMachine/Climbing/hkpCharacterStateClimbing.h>

#include <Physics/Dynamics/World/hkpWorld.h>

#include <Physics/Utilities/CharacterControl/StateMachine/Util/hkpCharacterMovementUtil.h>

	// Return the state type
hkpCharacterStateType hkpCharacterStateClimbing::getType() const 
{
	return HK_CHARACTER_CLIMBING;
}
 
void hkpCharacterStateClimbing::change(hkpCharacterContext& context, const hkpCharacterInput& input, hkpCharacterOutput& output)
{
	//
	// Check if at the ladder
	//
	if (!input.m_atLadder)
	{
		context.setState(HK_CHARACTER_IN_AIR, input, output);
		return;
	}

	//
	// Check if I should jump
	//
	if (input.m_wantJump)
	{
		// When climbing we'll simply push away from the ladder
		output.m_velocity.addMul4( input.m_characterGravity.length3(), input.m_surfaceNormal );
		context.setState( HK_CHARACTER_IN_AIR, input, output );
		return;
	}
}

	// Process the user input - causes state transitions etc.
void hkpCharacterStateClimbing::update(hkpCharacterContext& context, const hkpCharacterInput& input, hkpCharacterOutput& output)
{
	//
	// Move character relative to the surface we're standing on
	//
	{
		hkpCharacterMovementUtil::hkpMovementUtilInput muInput;
		muInput.m_gain = 1.0f;
		muInput.m_forward = input.m_forward;
		muInput.m_up = input.m_surfaceNormal;
		muInput.m_surfaceNormal = input.m_surfaceNormal;
		muInput.m_currentVelocity = input.m_velocity;
		muInput.m_desiredVelocity.set( input.m_inputUD * 10, input.m_inputLR * 10, -0.1f ); //-0.1 attract toward the ladder
		muInput.m_maxVelocityDelta = 100.0f;
		muInput.m_surfaceVelocity = input.m_surfaceVelocity;

		hkpCharacterMovementUtil::calculateMovement(muInput, output.m_velocity);

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
