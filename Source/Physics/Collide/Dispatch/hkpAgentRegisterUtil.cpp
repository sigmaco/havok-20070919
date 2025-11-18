/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>

//#include <hkcollide/agent/gjk/hkpGskConvexConvexAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/Gjk/hkpGskfAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/Gjk/hkpPredGskfAgent.h>

#include <Physics/Collide/Agent/ConvexAgent/BoxBox/hkpBoxBoxAgent.h>
#include <Physics/Collide/Agent/MiscAgent/Bv/hkpBvAgent.h>
#include <Physics/Collide/Agent/CompoundAgent/BvTree/hkpBvTreeAgent.h>
#include <Physics/Collide/Agent/CompoundAgent/BvTreeStream/hkpMoppBvTreeStreamAgent.h>

#include <Physics/Collide/Agent/CompoundAgent/BvTree/hkpMoppAgent.h>
#include <Physics/Collide/Agent/MiscAgent/Phantom/hkpPhantomAgent.h>
#include <Physics/Collide/Agent/HeightFieldAgent/hkpHeightFieldAgent.h>
//#include <hkcollide/agent/tripatch/hkpTriPatchAgent.h>

#include <Physics/Collide/Agent/ConvexAgent/SphereSphere/hkpSphereSphereAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/SphereCapsule/hkpSphereCapsuleAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/SphereTriangle/hkpSphereTriangleAgent.h>

#include <Physics/Collide/Agent/ConvexAgent/CapsuleCapsule/hkpCapsuleCapsuleAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/CapsuleTriangle/hkpCapsuleTriangleAgent.h>
#include <Physics/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>
#include <Physics/Collide/Agent/Deprecated/MultiSphereTriangle/hkpMultiSphereTriangleAgent.h>
#include <Physics/Collide/Agent/MiscAgent/MultirayConvex/hkpMultiRayConvexAgent.h>

#include <Physics/Collide/Agent/MiscAgent/Transform/hkpTransformAgent.h>
#include <Physics/Collide/Agent/CompoundAgent/List/hkpListAgent.h>
#include <Physics/Collide/Agent/Deprecated/ConvexList/hkpConvexListAgent.h>
#include <Physics/Collide/Agent/CompoundAgent/ShapeCollection/hkpShapeCollectionAgent.h>
#include <Physics/Collide/Agent/Deprecated/MultiSphere/hkpMultiSphereAgent.h>

#include <Physics/Collide/Agent/CompoundAgent/BvTreeStream/hkpBvTreeStreamAgent.h>
#include <Physics/Collide/Dispatch/Agent3Bridge/hkpAgent3Bridge.h>

#include <Physics/Internal/Collide/Agent3/PredGskAgent3/hkpPredGskAgent3.h>
#include <Physics/Internal/Collide/Agent3/PredGskCylinderAgent3/hkpPredGskCylinderAgent3.h>
#include <Physics/Internal/Collide/Agent3/CapsuleTriangle/hkpCapsuleTriangleAgent3.h>
#include <Physics/Internal/Collide/Agent3/BoxBox/hkpBoxBoxAgent3.h>
#include <Physics/Internal/Collide/Agent3/List3/hkpListAgent3.h>
#include <Physics/Internal/Collide/Agent3/ConvexList3/hkpConvexListAgent3.h>
#include <Physics/Internal/Collide/Agent3/BvTree3/hkpBvTreeAgent3.h>
#include <Physics/Internal/Collide/Agent3/CollectionCollection3/hkpCollectionCollectionAgent3.h>


void HK_CALL hkpAgentRegisterUtil::_registerBvTreeAgents(hkpCollisionDispatcher* dis)
{
	// hkpBvTreeAgent gets special treatment, as it overrides several
	// hkpBvAgent entries, which will cause an assert 
	dis->setEnableChecks( false );

	// Register bvTree against everything, and bvTree vs bvTree special case to create a bvTree agent for the larger tree
	hkpBvTreeAgent::registerAgent(dis);

	// Register mopp against everything (already done), and mopp vs mopp special case (using size of mopp code) to create a bvTree agent for the larger tree
	// Also replaces the linear cast static function for mopp
	hkpMoppAgent::registerAgent(dis);

	// Register stream bvtree for bvTree against convex objects			
	hkpBvTreeStreamAgent::registerAgent(dis);

	// Replaces the linear cast static function for mopp
	hkpMoppBvTreeStreamAgent::registerAgent(dis);

	hkBvTreeAgent3::registerAgent3(dis);

	dis->setEnableChecks( true );
}

void HK_CALL hkpAgentRegisterUtil::_registerListAgents( hkpCollisionDispatcher* dis)
{
	// Register list agent against everything else (overrides shape collection agent)
	hkpListAgent::registerAgent( dis );

	// Register the convex list for hkConvexList shapes against convex shapes
	// This dispatches to a special dispatch function in hkpConvexListAgent for hkpConvexShape vs hkpConvexListShape
	// The convex list shape can be treated as a list, a convex list, or a convex object selected on a per
	// collision basis - see the dispatch function for details.
	hkpConvexListAgent::registerAgent( dis );
	hkConvexListAgent3::registerAgent3( dis );


	// This dispatches to a special dispatch function in bvTreeStream for hkpBvTreeShape vs hkpConvexListShape
	// The convex list shape can be treated as a list, a convex list, or a convex object selected on a per
	// collision basis - see the dispatch function for details.
	//		hkpBvTreeStreamAgent::registerConvexListAgent(dis);
	hkpHeightFieldAgent::registerAgent( dis );

	hkListAgent3::registerAgent3(dis);
}


void HK_CALL hkpAgentRegisterUtil::_registerTerminalAgents( hkpCollisionDispatcher* dis)
{

	//
	//	Default Convex - convex agents
	//
	{
		hkpPredGskfAgent::registerAgent(dis);
		hkPredGskAgent3::registerAgent3( dis );
	}

	//
	//	Special agents
	//
	{
		//
		//	Some old style agents which are not supported on the spu
		//  (unlikely we will port some agent3 over later (only if sony adds more memory to the spu))
		//
#if !defined(HK_PLATFORM_HAS_SPU)

		hkPredGskCylinderAgent3::registerAgent3( dis );

		// Warning: The box-box agent fail for small object (say 3cm in size).
		hkpBoxBoxAgent::registerAgent(dis);
		hkBoxBoxAgent3::registerAgent3(dis);

		hkpSphereSphereAgent::registerAgent(dis);
		hkpSphereCapsuleAgent::registerAgent(dis);

		// As the hkpSphereTriangleAgent does not weld, we have use the hkPredGskAgent3 agent for agent3 streams
		hkpSphereTriangleAgent::registerAgent2(dis);

		hkpSphereBoxAgent::registerAgent(dis);
		/**/	hkpCapsuleCapsuleAgent::registerAgent(dis);

		hkpCapsuleTriangleAgent::registerAgent(dis);
		hkCapsuleTriangleAgent3::registerAgent3( dis );	// could be ported
		hkpMultiSphereTriangleAgent::registerAgent(dis);
		hkpMultiRayConvexAgent::registerAgent(dis);
		hkpBvTreeStreamAgent::registerMultiRayAgent(dis);
#else 

		//hkpSphereSphereAgent::registerAgent2(dis);	// there are not that many sphere-sphere situations and GSK is pretty fast with spheres, so we disable sphere-sphere for the time being

		hkpSphereTriangleAgent::registerAgent2(dis);
		hkpCapsuleTriangleAgent::registerAgent2(dis);
#endif
	}
}


// Register agents
void HK_CALL hkpAgentRegisterUtil::registerAllAgents(hkpCollisionDispatcher* dis)
{

	hkRegisterAlternateShapeTypes(dis);

	//
	//	Warning: order of registering agents is important, later entries override earlier entries
	//


	//
	//	Unary agents handling secondary type
	//
	{
		hkpBvAgent::registerAgent(dis);
		hkpMultiSphereAgent::registerAgent( dis );
	}

	_registerBvTreeAgents(dis);

	//
	//	Our new midphase agent
	//
	{
		dis->setEnableChecks( false );		// This will override the shape collection vs bvTree (used to be set to bvTree), to be hkpShapeCollectionAgent
		hkpShapeCollectionAgent::registerAgent(dis);
		dis->setEnableChecks( true );
	}
	
	_registerListAgents( dis );

	{
		dis->setEnableChecks( false );
		hkpCollectionCollectionAgent3::registerAgent3(dis); 
		dis->setEnableChecks( true );
	}

	hkpTransformAgent::registerAgent(dis);	
	hkpPhantomAgent::registerAgent(dis);

	_registerTerminalAgents( dis );

	//dis->debugPrintTable();
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
