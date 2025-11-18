/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>

#include <Physics/Collide/Dispatch/BroadPhase/hkpNullBroadPhaseListener.h>

void hkpNullBroadPhaseListener::addCollisionPair( hkpTypedBroadPhaseHandlePair& pair ) 
{ 
	HK_ASSERT2(0x39058a90, 0, "A broad phase pair has been created for which no handler has been registered" ); 
}

void hkpNullBroadPhaseListener::removeCollisionPair( hkpTypedBroadPhaseHandlePair& pair ) 
{ 
	HK_ASSERT2(0x1cb5bb15, 0, "A broad phase pair has been deleted for which no handler has been registered" ); 
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
