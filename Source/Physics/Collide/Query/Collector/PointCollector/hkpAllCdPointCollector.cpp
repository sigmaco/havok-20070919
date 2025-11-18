/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Query/Collector/PointCollector/hkpAllCdPointCollector.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

void hkpAllCdPointCollector::addCdPoint( const hkpCdPoint& event ) 
{
	hkpRootCdPoint& hit = m_hits.expandOne();

	hit.m_contact = event.m_contact;
	hit.m_rootCollidableA = event.m_cdBodyA.getRootCollidable();
	hit.m_shapeKeyA = event.m_cdBodyA.getShapeKey();

	hit.m_rootCollidableB = event.m_cdBodyB.getRootCollidable();
	hit.m_shapeKeyB = event.m_cdBodyB.getShapeKey();
}


void hkpAllCdPointCollector::sortHits( ) 
{
	hkSort( m_hits.begin(), m_hits.getSize() );
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
