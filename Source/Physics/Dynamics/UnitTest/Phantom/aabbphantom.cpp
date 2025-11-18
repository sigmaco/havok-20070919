/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Dynamics/hkpDynamics.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>
#include <Physics/Collide/Query/CastUtil/hkpLinearCastInput.h>
#include <Physics/Collide/Query/Collector/PointCollector/hkpAllCdPointCollector.h>

#include <Demos/DemoCommon/Utilities/GameUtils/GameUtils.h>

void linear_cast_test ( void )
{
	hkpWorldCinfo info;
	hkpWorld world(info);
	hkpAgentRegisterUtil::registerAllAgents(world.getCollisionDispatcher());

	for (hkUlong i=0; i<3; i++)
	{
		hkVector4 unit(1.0f, 1.0f, 1.0f);
		hkVector4 position(float(i) * 5.0f, 0, 0);
		hkpRigidBody* box = GameUtils::createBox(unit, 0.0f, position);
		box->setUserData(i);
		world.addEntity(box);
		box->removeReference();
	}

	hkVector4 pos(0, 0, 0);
	hkpRigidBody* sphere = GameUtils::createSphere(0.5f, 0.0f, pos);

	hkVector4 minaabb(-10, -10, -10);
	hkVector4 maxaabb( 50,  10,  10);
	hkAabb aabb(minaabb, maxaabb);
	hkpAabbPhantom* phantom = new hkpAabbPhantom(aabb);

	world.addPhantom(phantom);

	hkpLinearCastInput input;
	input.m_to.set(25,0,0);
	hkpAllCdPointCollector collector;
	hkpAllCdPointCollector startCollector;
	phantom->linearCast(sphere->getCollidable(), input,  collector, startCollector);

	HK_TEST2( startCollector.getHits().getSize() == 1,	"Initial Overlaps" );
	HK_TEST2( collector.getHits().getSize() == 2,		"Hits" );
}

int aabbphantom_main()
{
	linear_cast_test();
	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(aabbphantom_main,     "Fast", "Test/Test/UnitTest/UnitTest/UnitTest/Dynamics/",     __FILE__     );

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
