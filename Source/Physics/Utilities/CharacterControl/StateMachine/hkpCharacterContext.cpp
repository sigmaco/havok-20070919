/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterStateManager.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterContext.h>


hkpCharacterContext::hkpCharacterContext(const hkpCharacterStateManager* Manager, hkpCharacterStateType initialState)
: m_stateManager(Manager) , 
  m_currentState(initialState), 
  m_previousState(initialState)
{
	m_characterType = HK_CHARACTER_PROXY;

	m_filterEnable = true;
	
	m_maxLinearVelocity = 20.0f;

	m_maxLinearAcceleration = 625.0f;

	m_gain = 1.0f;

	m_stateManager->addReference();

}

hkpCharacterContext::~hkpCharacterContext()
{
	m_stateManager->removeReference();
}

hkpCharacterStateType hkpCharacterContext::getState() const
{
	return m_currentState;
}

void hkpCharacterContext::setState(hkpCharacterStateType state, const hkpCharacterInput& input, hkpCharacterOutput& output )
{
	hkpCharacterStateType prevState = m_currentState;

	HK_ASSERT2(0x6d4abe44, m_stateManager->getState(state) != HK_NULL , "Bad state transition to " << state << ". Has this state been registered?");

	// Leave the old state
	m_stateManager->getState(m_currentState)->leaveState(*this, state, input, output);

	// Transition to the new state
	m_currentState = state;

	// Enter the new state
	m_stateManager->getState(m_currentState)->enterState(*this, prevState, input, output);

}

void hkpCharacterContext::update(const hkpCharacterInput& input, hkpCharacterOutput& output)
{
	// Give sensible initialized values for output
	output.m_velocity = input.m_velocity;
	
	// ORIGINAL IMPLEMENTATION
	//m_stateManager->getState(m_currentState)->update(*this, input, output);

	// NEW IMPLEMENTATION A
	// Do state transition logic
	// m_stateManager->getState(m_currentState)->change(*this, input, output);
	// Do update with potential new state (straight after the state transition )
	// m_stateManager->getState(m_currentState)->update(*this, input, output);

	// NEW IMPLEMENTATION B
	// Do state transition logic
	m_stateManager->getState(m_currentState)->change(*this, input, output);
	// Do update with potential new state (skip one frame - similar to original implementation)
	if (m_currentState == m_previousState)
	{
		m_stateManager->getState(m_currentState)->update(*this, input, output);		
	}
	
	m_previousState = m_currentState;

	// Enable only for character rigid body
	// In a case of character collision with dynamic rigid body
	// add velocity which represent the effect of gravity in direction of ground normal
	if (m_characterType == HK_CHARACTER_RIGIDBODY)
	{
		if (m_currentState == HK_CHARACTER_ON_GROUND)
		{
			if ( (input.m_surfaceMotionType != hkpMotion::MOTION_FIXED) && (input.m_surfaceMotionType != hkpMotion::MOTION_KEYFRAMED) )
			{
				hkSimdReal deltaTime = hkSimdReal(input.m_stepInfo.m_deltaTime);
				output.m_velocity.addMul4(deltaTime*input.m_surfaceNormal.dot3(input.m_characterGravity), input.m_surfaceNormal);
			}
		}		
	}
	
	// Apply output velocity filtering
	if (m_filterEnable)
	{
		// limit output velocity
		const hkReal currentVel = output.m_velocity.length3();
		if (currentVel > m_maxLinearVelocity)
		{
			hkReal cv; cv = m_maxLinearVelocity/currentVel;	

			output.m_velocity.mul4(cv);
		}
	
		// limit maximal linear acceleration and smooth velocity
		hkVector4 currentAcceleration; currentAcceleration.setSub4(output.m_velocity, input.m_velocity);
		hkReal invDt = input.m_stepInfo.m_invDeltaTime;
		currentAcceleration.mul4(invDt);
		
		hkReal ca; ca = hkReal(currentAcceleration.length3())/m_maxLinearAcceleration;
		
		output.m_velocity = input.m_velocity;

		if ( (ca > 1.0f) && !(m_currentState == HK_CHARACTER_JUMPING))
		{
			output.m_velocity.addMul4(m_gain*input.m_stepInfo.m_deltaTime/ca,currentAcceleration);		
		}
		else
		{
			output.m_velocity.addMul4(m_gain*input.m_stepInfo.m_deltaTime,currentAcceleration);
		}
	}	

}

void hkpCharacterContext::setFilterEnable(const hkBool status)
{
	m_filterEnable = status;
}

void hkpCharacterContext::setFilterParameters(const hkReal gain, const hkReal maxVelocity, const hkReal maxAcceleration)
{
	m_gain = gain;
	
	m_maxLinearVelocity = maxVelocity;

	m_maxLinearAcceleration = maxAcceleration;
}

void hkpCharacterContext::setCharacterType(const CharacterType newType)
{
	m_characterType = newType;
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
