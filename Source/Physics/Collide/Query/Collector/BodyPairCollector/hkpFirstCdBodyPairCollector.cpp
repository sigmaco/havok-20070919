/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>

#include <Physics/Collide/Query/Collector/BodyPairCollector/hkpFirstCdBodyPairCollector.h>

void hkpFirstCdBodyPairCollector::addCdBodyPair( const hkpCdBody& bodyA, const hkpCdBody& bodyB )
{
	HK_ASSERT2(0xf07634ad, m_earlyOut==false, "Warning: Internal inefficiency, this has early outted you shouldn't be getting more hits");

	m_cdBodyPair.m_rootCollidableA = bodyA.getRootCollidable();
	m_cdBodyPair.m_shapeKeyA = bodyA.getShapeKey();

	m_cdBodyPair.m_rootCollidableB = bodyB.getRootCollidable();
	m_cdBodyPair.m_shapeKeyB = bodyB.getShapeKey();

	m_earlyOut = true;
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
