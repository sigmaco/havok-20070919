/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpToiContactPointViewer.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Visualize/hkProcessFactory.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Physics/Collide/Agent/hkpProcessCollisionData.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>


int hkpToiContactPointViewer::s_tag = 0;

void HK_CALL hkpToiContactPointViewer::registerViewer()
{
	s_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkProcess* HK_CALL hkpToiContactPointViewer::create(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpToiContactPointViewer(contexts);
}


int hkpToiContactPointViewer::getProcessTag(void)
{
	return s_tag;
}

hkpToiContactPointViewer::hkpToiContactPointViewer(const hkArray<hkProcessContext*>& contexts)
: hkpWorldViewerBase(contexts)
{
}

void hkpToiContactPointViewer::init()
{
	for (int i=0; m_context && i < m_context->getNumWorlds(); ++i)
	{
		worldAddedCallback( m_context->getWorld(i));
	}
}

hkpToiContactPointViewer::~hkpToiContactPointViewer()
{
	for (int i=0; m_context && i < m_context->getNumWorlds(); ++i)
	{
		worldRemovedCallback( m_context->getWorld(i));
	}
}

void hkpToiContactPointViewer::worldAddedCallback( hkpWorld* w)
{
	w->markForWrite();;
	w->addCollisionListener(this);
	w->unmarkForWrite();
}

void hkpToiContactPointViewer::worldRemovedCallback( hkpWorld* w)
{
	w->markForWrite();;
	w->removeCollisionListener(this);
	w->unmarkForWrite();
}

static void hkToiContactPointViewer_displayArrow( hkDebugDisplayHandler* handler, const hkVector4& from, const hkVector4& dir, int color, int tag  )
{
	// Check that we have a valid direction
	if (dir.lengthSquared3() > HK_REAL_EPSILON)
	{
		HK_TIME_CODE_BLOCK("ToiDisplayArrow", HK_NULL);

		hkVector4 to; to.setAdd4( from, dir );
		hkVector4 ort; hkVector4Util::calculatePerpendicularVector( dir, ort );
		ort.normalize3();
		hkVector4 ort2; ort2.setCross( dir, ort );

		ort.mul4( dir.length3() );

		const hkReal c = 0.85f;
		hkVector4 p; p.setInterpolate4( from, to, c );
		hkVector4 p0; p0.setAddMul4( p, ort, 1.0f - c );
		hkVector4 p1; p1.setAddMul4( p, ort, -(1.0f - c) );

		handler->displayLine( from, to, color, tag );
		handler->displayLine( to, p0, color, tag );
		handler->displayLine( to, p1, color, tag );
	}
}

void hkpToiContactPointViewer::contactProcessCallback( hkpContactProcessEvent& event )
{
	if (event.m_collisionData->hasToi())
	{
		hkContactPoint& contact = event.m_collisionData->getToiContactPoint();
		hkToiContactPointViewer_displayArrow(m_displayHandler, contact.getPosition(), contact.getNormal(), hkColor::RED, s_tag);
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
