/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Dynamics/hkpDynamics.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Dynamics/World/Listener/hkpWorldPostCollideListener.h>

// simpler test which did not cause a failure when it should have
class MyPostCollideListener : public hkReferencedObject, public hkpWorldPostCollideListener
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO);

		MyPostCollideListener(hkpRigidBody* bodyToRemove)
			: m_bodyToRemove(bodyToRemove)
		{
			HK_ASSERT2(0x3b6fa2f6, bodyToRemove != HK_NULL, "You must supply a valid hkpRigidBody pointer to the constructor!");
		}

		virtual void postCollideCallback( hkpWorld* world, const hkStepInfo& stepInfo )
		{
			world->removeEntity(m_bodyToRemove);
			world->addEntity(m_bodyToRemove);
			world->removeWorldPostCollideListener(this);
		}

	private:
		hkpRigidBody* m_bodyToRemove;
};

static void postcollisioncallback_removal()
{
	// create world
	hkpWorld* world;
	{
		hkpWorldCinfo info;
		world = new hkpWorld( info );
		world->lock();
	}

	// create bodies
	hkpRigidBody* bodyA;
	{
		// create shape
		hkVector4 fixedBoxSize; fixedBoxSize.set(5.0f, .5f , 5.0f );
		hkpBoxShape* fixedBoxShape = new hkpBoxShape( fixedBoxSize , 0 );

		// create rigid body info
		hkpRigidBodyCinfo info;
		info.m_shape = fixedBoxShape;
		info.m_motionType = hkpMotion::MOTION_FIXED;
		info.m_position.set(0.0f, -1.0f, 0.0f);

		bodyA = new hkpRigidBody(info);

		// release handle to shape
		fixedBoxShape->removeReference();
	}

	// create the post collisiton listener that will attempt to delete the rigid body
	MyPostCollideListener* pdlA = new MyPostCollideListener(bodyA);

	// see bodies can be removed from a post collision callback?
	{
		world->addEntity(bodyA);
		world->addWorldPostCollideListener(pdlA);
		world->unlock();
		world->stepDeltaTime(0.16f);
		world->lock();
	}
	
	// cleanup
	{
		pdlA->removeReference();
		bodyA->removeReference();
		world->removeReference();
	}
}

static int addremove_main()
{
	postcollisioncallback_removal();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(addremove_main, "Fast", "Physics/Test/UnitTest/Dynamics/", __FILE__     );

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
