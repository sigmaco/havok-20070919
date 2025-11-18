/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpSimulationIslandViewer.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Physics/Collide/Shape/hkpShape.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/Entity/hkpEntity.h>

//#define HK_DISABLE_DEBUG_DISPLAY
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpCollideDebugUtil.h>
#include <Common/Visualize/hkProcessFactory.h>

int hkpSimulationIslandViewer::m_tag = 0;

hkProcess* HK_CALL hkpSimulationIslandViewer::create(const hkArray<hkProcessContext*>& contexts )
{
	return new hkpSimulationIslandViewer(contexts);
}

void HK_CALL hkpSimulationIslandViewer::registerViewer()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkpSimulationIslandViewer::hkpSimulationIslandViewer( const hkArray<hkProcessContext*>& contexts )
: hkpWorldViewerBase(contexts),
	m_showActiveIslands(true),
	m_showInactiveIslands(true)
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			hkpWorld* world = m_context->getWorld(i);
			world->markForWrite();
			world->addWorldPostSimulationListener( this );
			world->unmarkForWrite();
		}
	}
}

hkpSimulationIslandViewer::~hkpSimulationIslandViewer()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i )
		{
			hkpWorld* world = m_context->getWorld(i);
			world->markForWrite();
			world->removeWorldPostSimulationListener(this);
			world->unmarkForWrite();
		}
	}
}

void hkpSimulationIslandViewer::worldAddedCallback( hkpWorld* world )
{
	world->markForWrite();
		world->addWorldPostSimulationListener( this );
	world->unmarkForWrite();
}

void hkpSimulationIslandViewer::worldRemovedCallback( hkpWorld* world )
{
	world->markForWrite();
		world->removeWorldPostSimulationListener( this );
	world->unmarkForWrite();
}

void hkpSimulationIslandViewer::postSimulationCallback( hkpWorld* world )
{
	HK_TIMER_BEGIN("hkpSimulationIslandViewer", this);

	//	hkprintf("island display...\n");
	if (m_showActiveIslands)
	{
		const hkArray<hkpSimulationIsland*>& islands = world->getActiveSimulationIslands();
		if(islands.getSize() > m_activeIslandDisplayGeometries.getSize())
		{
			m_activeIslandDisplayGeometries.setSize(islands.getSize());
		}

		hkArray<hkDisplayGeometry*> displayGeometries;
		displayGeometries.setSize(islands.getSize());

		hkArray<hkAabb> islandAabbs;
		islandAabbs.setSize(islands.getSize());

		for ( int i = 0; i < islands.getSize(); ++i )
		{
			const hkArray<hkpEntity*>& entities = islands[i]->getEntities();

			islandAabbs[i].m_max.setAll(-HK_REAL_MAX);
			islandAabbs[i].m_min.setAll(HK_REAL_MAX);

			// Create one aabb about all the entities.
			hkAabb aabb;

			hkVector4 minExtent;
			hkVector4 maxExtent;	
			maxExtent.setAll(-HK_REAL_MAX);
		    minExtent.setAll(HK_REAL_MAX);

			for ( int j = 0; j < entities.getSize(); ++j )
			{
				const hkpCollidable* c = entities[j]->getCollidable();

				// hkpCollidable may not have an hkpShape.
				if (c->getShape() != HK_NULL)
				{
					world->getBroadPhase()->getAabb( c->getBroadPhaseHandle(), aabb );
					maxExtent.setMax4( maxExtent, aabb.m_max );
					minExtent.setMin4( minExtent, aabb.m_min );
				}
			}

			m_activeIslandDisplayGeometries[i].setExtents(minExtent, maxExtent);
			displayGeometries[i] = &m_activeIslandDisplayGeometries[i];
		}

		m_displayHandler->displayGeometry(displayGeometries, hkColor::BLUE, m_tag);
	}

	if (m_showInactiveIslands)
	{
		const hkArray<hkpSimulationIsland*>& islands = world->getInactiveSimulationIslands();
	
		if(islands.getSize() > m_inactiveIslandDisplayGeometries.getSize())
		{
			m_inactiveIslandDisplayGeometries.setSize(islands.getSize());
		}

		hkArray<hkDisplayGeometry*> displayGeometries;
		displayGeometries.setSize(islands.getSize());

		for ( int i = 0; i < islands.getSize(); ++i )
		{
			const hkArray<hkpEntity*>& entities = islands[i]->getEntities();

			// Create one aabb about all the entities.
			hkAabb aabb;

			hkVector4 minExtent;
			hkVector4 maxExtent;	
			maxExtent.setAll(-HK_REAL_MAX);
		    minExtent.setAll(HK_REAL_MAX);

			for ( int j = 0; j < entities.getSize(); ++j )
			{
				const hkpCollidable* c = entities[j]->getCollidable();

				// hkpCollidable may not have an hkpShape.
				if (c->getShape() != HK_NULL)
				{
					world->getBroadPhase()->getAabb( c->getBroadPhaseHandle(), aabb );
					maxExtent.setMax4( maxExtent, aabb.m_max );
					minExtent.setMin4( minExtent, aabb.m_min );
				}
			}

			m_inactiveIslandDisplayGeometries[i].setExtents(minExtent, maxExtent);
			displayGeometries[i] = &m_inactiveIslandDisplayGeometries[i];
		}

		m_displayHandler->displayGeometry(displayGeometries, hkColor::GREEN, m_tag);

	}

	HK_TIMER_END();

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
