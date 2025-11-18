/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpInactiveContactPointViewer.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Internal/Collide/Agent3/Machine/Nn/hkpAgentNnMachine.h>
#include <Common/Visualize/hkProcessFactory.h>
#include <Common/Visualize/Type/hkColor.h>

int hkpInactiveContactPointViewer::s_tag = 0;

void HK_CALL hkpInactiveContactPointViewer::registerViewer()
{
	s_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkProcess* HK_CALL hkpInactiveContactPointViewer::create(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpInactiveContactPointViewer(contexts);
}

hkpInactiveContactPointViewer::hkpInactiveContactPointViewer(const hkArray<hkProcessContext*>& contexts)
: hkpContactPointViewer( contexts, hkColor::GREEN )
{
}

const hkArray<hkpSimulationIsland*>& hkpInactiveContactPointViewer::getIslands(hkpWorld* world) const
{
	return world->getInactiveSimulationIslands();
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
