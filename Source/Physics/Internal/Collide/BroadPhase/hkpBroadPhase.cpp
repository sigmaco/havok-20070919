/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Internal/hkpInternal.h>

#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>



hkpBroadPhase::hkpBroadPhase()
{
	m_criticalSection = HK_NULL;
	m_multiThreadCheck.disableChecks();
}

void hkpBroadPhase::enableMultiThreading(int spinCountForCriticalSection)
{
	if (!m_criticalSection)	
	{
		m_criticalSection = new hkCriticalSection(spinCountForCriticalSection);
		m_multiThreadCheck.enableChecks();
	}
}

hkpBroadPhase::~hkpBroadPhase()
{
	if ( m_criticalSection )
	{
		delete m_criticalSection;
		m_criticalSection = HK_NULL;
	}
}

void hkpBroadPhase::lockImplementation()
{
	m_criticalSection->enter();
	markForWrite();
}

void hkpBroadPhase::unlockImplementation()
{
	unmarkForWrite();
	m_criticalSection->leave();
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
