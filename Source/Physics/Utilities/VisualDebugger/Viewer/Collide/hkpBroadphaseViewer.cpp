/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpBroadphaseViewer.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>

//#define HK_DISABLE_DEBUG_DISPLAY
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Visualize/hkProcessFactory.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpCollideDebugUtil.h>

int hkpBroadphaseViewer::m_tag = 0;

void HK_CALL hkpBroadphaseViewer::registerViewer()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkProcess* HK_CALL hkpBroadphaseViewer::create(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpBroadphaseViewer(contexts);
}

hkpBroadphaseViewer::hkpBroadphaseViewer(const hkArray<hkProcessContext*>& contexts)
: hkpWorldViewerBase( contexts )
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			hkpWorld* w = m_context->getWorld(i);
			w->markForWrite();
			w->addWorldPostSimulationListener( this );
			w->unmarkForWrite();
		}
	}
}

void hkpBroadphaseViewer::worldAddedCallback( hkpWorld* world)
{
	world->markForWrite();
	world->addWorldPostSimulationListener( this );
	world->unmarkForWrite();

}

void hkpBroadphaseViewer::worldRemovedCallback( hkpWorld* world)
{
	world->markForWrite();
	world->removeWorldPostSimulationListener( this );
	world->unmarkForWrite();
}

void hkpBroadphaseViewer::postSimulationCallback( hkpWorld* world )
{
	HK_TIMER_BEGIN("hkpBroadphaseViewer", this);

	hkVector4 dummy;	// MSVC6.0 alignment doesn't seem to work for the array below, so this
								// useless variable was necessary...
    //Had to switch to a simple hkArray, the inplace array caused an ICE on ps3-g++
	//hkInplaceArrayAligned16<hkAabb, 1024> allAabbs;
	hkArray<hkAabb> allAabbs(1024);
	allAabbs.setSizeUnchecked(1024);

	hkpBroadPhase* broadPhase = world->getBroadPhase();

	broadPhase->getAllAabbs( allAabbs );
	if(allAabbs.getSize() > m_broadPhaseDisplayGeometries.getSize())
	{
		m_broadPhaseDisplayGeometries.setSize(allAabbs.getSize());
	}

	hkArray<hkDisplayGeometry*> displayGeometries;
	displayGeometries.setSize(allAabbs.getSize());

	// create display geometries 
	for(int i = allAabbs.getSize()-1; i >= 0; i--)
	{
		m_broadPhaseDisplayGeometries[i].setExtents(allAabbs[i].m_min, allAabbs[i].m_max);
		displayGeometries[i] = &(m_broadPhaseDisplayGeometries[i]);
	}

	m_displayHandler->displayGeometry(displayGeometries, hkColor::RED, m_tag);

	HK_TIMER_END();
}

hkpBroadphaseViewer::~hkpBroadphaseViewer()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			hkpWorld* w = m_context->getWorld(i);
			w->markForWrite();
			w->removeWorldPostSimulationListener( this );
			w->unmarkForWrite();
		}
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
