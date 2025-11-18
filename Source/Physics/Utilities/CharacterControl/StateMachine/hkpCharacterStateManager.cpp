/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpCharacterStateManager.h>
		
hkpCharacterStateManager::hkpCharacterStateManager()
{
	for (int i=0; i < HK_CHARACTER_MAX_STATE_ID; i++)
	{
		m_registeredState[i] = HK_NULL;
	}
}

hkpCharacterStateManager::~hkpCharacterStateManager()
{
	for (int i=0; i < HK_CHARACTER_MAX_STATE_ID; i++)
	{
		if (m_registeredState[i] != HK_NULL)
		{
			m_registeredState[i]->removeReference();
			m_registeredState[i] = HK_NULL;
		}
	}
}

void hkpCharacterStateManager::registerState(hkpCharacterState* state, hkpCharacterStateType stateType)
{
	state->addReference();

	hkpCharacterState* oldState = m_registeredState[stateType];

	if (oldState != HK_NULL)
	{
		oldState->removeReference();
	}

	m_registeredState[stateType] = state; 
}

hkpCharacterState* hkpCharacterStateManager::getState(hkpCharacterStateType stateType) const
{
	return m_registeredState[stateType]; 
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
