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
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpMidphaseViewer.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>

//#define HK_DISABLE_DEBUG_DISPLAY
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Visualize/hkProcessFactory.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpCollideDebugUtil.h>

int hkpMidphaseViewer::m_tag = 0;

void HK_CALL hkpMidphaseViewer::registerViewer()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkProcess* HK_CALL hkpMidphaseViewer::create(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpMidphaseViewer(contexts);
}

hkpMidphaseViewer::hkpMidphaseViewer(const hkArray<hkProcessContext*>& contexts)
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

void hkpMidphaseViewer::worldAddedCallback( hkpWorld* world)
{
	world->markForWrite();
	world->addWorldPostSimulationListener( this );
	world->unmarkForWrite();

}

void hkpMidphaseViewer::worldRemovedCallback( hkpWorld* world)
{
	world->markForWrite();
	world->removeWorldPostSimulationListener( this );
	world->unmarkForWrite();
}

void hkpMidphaseViewer::postSimulationCallback( hkpWorld* world )
{
	HK_TIMER_BEGIN("hkpMidphaseViewer", this);

	m_broadPhaseDisplayGeometries.clear();

	const hkArray<hkpSimulationIsland*>* islands = &world->getActiveSimulationIslands();
	for (int z = 0; z < 2; z++)
	{
		for(int i = 0; i < islands->getSize(); i++)
		{
			const hkArray<hkpEntity*>& entities = (*islands)[i]->getEntities();
			for (int e = 0; e < entities.getSize(); e++)
			{
				const hkpCollidable::BoundingVolumeData& bvData = entities[e]->getCollidable()->m_boundingVolumeData;

				hkAabbUint32* aabbs = bvData.m_childShapeAabbs;
				if (aabbs)
				{
					for (int c = 0; c < int(bvData.m_numChildShapeAabbs); c++, aabbs++)
					{
						hkAabbUint32 tmpInt;
						hkAabb tmp;
						hkpCollisionInput::Aabb32Info& aabb32Info = world->getCollisionInput()->m_aabb32Info;
						hkVector4Util::uncompressExpandedAabbUint32(*aabbs, tmpInt);
						hkVector4Util::convertAabbFromUint32(tmpInt, aabb32Info.m_bitOffsetLow, aabb32Info.m_bitScale, tmp);

						hkDisplayAABB* disp = m_broadPhaseDisplayGeometries.expandBy(1);
						disp->setExtents(tmp.m_min, tmp.m_max);
					}
				}
			}
		}

		// Switch island array
		islands = &world->getInactiveSimulationIslands();
	}

	const int numObjs = m_broadPhaseDisplayGeometries.getSize();
	hkArray<hkDisplayGeometry*> displayGeometries(numObjs);
	m_broadPhaseDisplayGeometries.setSize(numObjs);

	hkDisplayGeometry** dg = displayGeometries.begin();
	hkDisplayAABB* dispAabb = m_broadPhaseDisplayGeometries.begin();
	for (int i = 0; i < numObjs; i++)
	{
		*(dg++) = dispAabb++;
	}

	m_displayHandler->displayGeometry(displayGeometries, hkColor::ORANGE, m_tag);

	HK_TIMER_END();
}

hkpMidphaseViewer::~hkpMidphaseViewer()
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
