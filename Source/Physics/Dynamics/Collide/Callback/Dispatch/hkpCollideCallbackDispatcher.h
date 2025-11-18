/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE_CALLBACK_DISPATCHER
#define HK_COLLIDE_CALLBACK_DISPATCHER

#include <Physics/Dynamics/Collide/hkpCollisionListener.h>
#include <Physics/Collide/Shape/hkpShape.h>

#if !defined (HK_PLATFORM_SPU)
# define HK_SHAPE_CONTAINER hkpShapeContainer
#else
# define HK_SHAPE_CONTAINER hkpShape
class hkpBvTreeShape;
#endif

	HK_FORCE_INLINE void HK_CALL hkFireContactPointAddedCallback   (hkpWorld*  world,  hkpEntity* entityA, hkpEntity* entityB, hkpContactPointAddedEvent& event);
	HK_FORCE_INLINE void HK_CALL hkFireContactProcessCallback      (hkpWorld*  world,  hkpEntity* entityA, hkpEntity* entityB, hkpContactProcessEvent& event);
	HK_FORCE_INLINE void HK_CALL hkFireContactPointRemovedCallback (hkpWorld*  world,  hkpEntity* entityA, hkpEntity* entityB, hkpContactPointRemovedEvent& event);

#if defined(HK_PLATFORM_SPU)

	typedef void (*hkFireContactPointAddedCallbackFunc)  (hkpEntity* entityA, hkpEntity* entityB, hkpContactPointAddedEvent&   event);
	typedef void (*hkFireContactProcessCallbackFunc)     (hkpEntity* entityA, hkpEntity* entityB, hkpContactProcessEvent&      event);
	typedef void (*hkFireContactPointRemovedCallbackFunc)(hkpEntity* entityA, hkpEntity* entityB, hkpContactPointRemovedEvent& event);
	typedef hkBool (*hkShapeContainerIsCollisionEnabled) (const hkpProcessCollisionInput* input, const hkpCdBody* bodyA, const hkpCdBody* collectionBodyB, const HK_SHAPE_CONTAINER* containerShapeB, hkpShapeKey keyB);
	typedef hkBool (*hkShapeContainer2IsCollisionEnabled) (const hkpProcessCollisionInput* input, const hkpCdBody* bodyA, const hkpCdBody* bodyB, const HK_SHAPE_CONTAINER* containerShapeA, const HK_SHAPE_CONTAINER* containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB);
	typedef int (*hkNumShapeKeyHitsLimitBreached) (const hkpProcessCollisionInput* input, const hkpCdBody* bodyA, const hkpCdBody* bodyB, const hkpBvTreeShape* bvTreeShapeB, hkAabb& aabb, hkpShapeKey* shapeKeysInOut, int shapeKeysCapacity);

	extern hkFireContactPointAddedCallbackFunc   g_FireContactPointAddedCallback;
	extern hkFireContactProcessCallbackFunc      g_FireContactProcessCallback;
	extern hkFireContactPointRemovedCallbackFunc g_FireContactPointRemovedCallback;
	extern hkShapeContainerIsCollisionEnabled    g_ShapeContainerIsCollisionEnabled;
	extern hkShapeContainer2IsCollisionEnabled   g_ShapeContainer2IsCollisionEnabled;
	extern hkNumShapeKeyHitsLimitBreached g_NumShapeKeyHitsLimitBreached;

		/// register your spu callback function with this function
	inline void registerCallbackFunctions(	hkFireContactPointAddedCallbackFunc addedFunc,
											hkFireContactProcessCallbackFunc processFunc,
											hkFireContactPointRemovedCallbackFunc removedFunc,
											hkShapeContainerIsCollisionEnabled filterFunc,
											hkShapeContainer2IsCollisionEnabled filter2Func,
											hkNumShapeKeyHitsLimitBreached numShapeKeyHitsLimitBrachedFunc)
	{
		g_FireContactPointAddedCallback		= addedFunc;
		g_FireContactProcessCallback		= processFunc;
		g_FireContactPointRemovedCallback	= removedFunc;
		g_ShapeContainerIsCollisionEnabled  = filterFunc;
		g_ShapeContainer2IsCollisionEnabled = filter2Func;
		g_NumShapeKeyHitsLimitBreached = numShapeKeyHitsLimitBrachedFunc;
	}
#endif

#include <Physics/Dynamics/Collide/Callback/Dispatch/hkpCollideCallbackDispatcher.inl>


#endif // HK_COLLIDE_CALLBACK_DISPATCHER

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
