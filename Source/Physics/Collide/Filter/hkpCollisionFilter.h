/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_COLLISION_FILTER_H
#define HK_COLLIDE2_COLLISION_FILTER_H

#include <Common/Base/Object/hkReferencedObject.h>
#include <Physics/Collide/Filter/hkpCollidableCollidableFilter.h>
#include <Physics/Collide/Filter/hkpRayCollidableFilter.h>
#include <Physics/Collide/Filter/hkpShapeCollectionFilter.h>
#include <Physics/Collide/Shape/Query/hkpRayShapeCollectionFilter.h>

extern const hkClass hkpCollisionFilterClass;

class hkpBvTreeShape;


	/// This class inherits from all four collision filters. These are all the filters used by the system.
	/// Typically you inherit from this, to provide an adaptor to a collision filter with some unified behavior. 
	/// See hkpGroupFilter for an example of this.
class hkpCollisionFilter :	public hkReferencedObject,
						public hkpCollidableCollidableFilter,
						public hkpShapeCollectionFilter,
						public hkpRayShapeCollectionFilter,
						public hkpRayCollidableFilter
{

	public:

			// note that only filters of type HK_FILTER_GROUP will be executed on spu currently
		enum hkpFilterType
		{
			HK_FILTER_UNKNOWN		= 0,
			HK_FILTER_NULL			= 1,
			HK_FILTER_GROUP			= 2,
			HK_FILTER_LIST			= 3,
			HK_FILTER_CUSTOM		= 4,
			HK_FILTER_PAIR			= 5,
			HK_FILTER_CONSTRAINT	= 6,
		};

	public:

		HK_DECLARE_REFLECTION();

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO );

		hkpCollisionFilter() { m_type = HK_FILTER_UNKNOWN; }

			/// Checks two collidables 
		virtual hkBool isCollisionEnabled( const hkpCollidable& a, const hkpCollidable& b ) const = 0;

			/// hkpShapeCollectionFilter interface forwarding
		virtual	hkBool isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const HK_SHAPE_CONTAINER& bContainer, hkpShapeKey bKey  ) const = 0;

			/// hkpShapeCollectionFilter interface forwarding
		virtual hkBool isCollisionEnabled( const hkpCollisionInput& input, const hkpCdBody& collectionBodyA, const hkpCdBody& collectionBodyB, const HK_SHAPE_CONTAINER& containerShapeA, const HK_SHAPE_CONTAINER& containerShapeB, hkpShapeKey keyA, hkpShapeKey keyB ) const = 0;

			/// Default hkpShapeCollectionFilter interface implementation
		virtual int numShapeKeyHitsLimitBreached( const hkpCollisionInput& input, 
															const hkpCdBody& bodyA, const hkpCdBody& bodyB, 
															const hkpBvTreeShape* bvTreeShapeB, hkAabb& aabb,
															hkpShapeKey* shapeKeysInOut,
															int shapeKeysCapacity) const 
		{
			HK_WARN(0xad87baca, "Critical peformance warning: hkpBvTreeShape::queryAabb() returned more than 4K hkpShapeKey hits. All shapes above 4K are dropped. Consider implementing a custom handler for this case.");
			// Default: no action.
			return shapeKeysCapacity;
		}

			/// hkpRayShapeCollectionFilter interface forwarding
		virtual hkBool isCollisionEnabled( const hkpShapeRayCastInput& aInput, const hkpShape& bShape, const HK_SHAPE_CONTAINER& bContainer, hkpShapeKey bKey ) const = 0;

			/// hkpRayCollidableFilter interface forwarding
		virtual hkBool isCollisionEnabled( const hkpWorldRayCastInput& a, const hkpCollidable& collidableB ) const = 0;

	public:

		typedef hkEnum<hkpFilterType,hkUint32> FilterType; // comma not allowed in HK_ALIGN macro
		HK_ALIGN16(FilterType m_type);
		hkUint32 m_pad[3];
};



#endif // HK_COLLIDE2_COLLISION_FILTER_H

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
