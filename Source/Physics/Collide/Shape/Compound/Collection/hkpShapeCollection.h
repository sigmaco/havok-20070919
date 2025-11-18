/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_SHAPE_COLLECTION_H
#define HK_COLLIDE2_SHAPE_COLLECTION_H

#include <Physics/Collide/Shape/hkpShape.h>
#include <Physics/Collide/Shape/hkpShapeContainer.h>

extern hkReal hkConvexShapeDefaultRadius;

extern const hkClass hkpShapeCollectionClass;

	/// An interface to a collection of Shapes, each of which can be identified using a hkpShapeKey.
class hkpShapeCollection : public hkpShape, public hkpShapeContainer
{		
	public:

		//+abstract(1)

		HK_DECLARE_REFLECTION();

			/// Empty constructor
		hkpShapeCollection( hkpShapeType type );

		hkpShapeCollection( hkFinishLoadedObjectFlag flag ) : hkpShape(flag) { m_type = HK_SHAPE_COLLECTION; }

			//
			// hkpShape interface
			//

			/// Implements the castRay function. Note that for shape collections with many sub-shapes this
			/// function can be very slow. It is better to use a hkpBvTreeShape::castRay instead
		virtual hkBool castRayImpl( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;
	
			/// Note: the default implementation call hkpShape::castRay( ..., hkpShapeRayCastOutput& results )
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

			/// Gets the AABB for the hkpShape given a local to world transform and an extra tolerance.
			/// This default implementation is rather slow and just iterates over all children
 		virtual void getAabbImpl( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const;

			/// Support for creating bounding volume hierarchies of shapes.
			/// This default implementation is rather slow and just iterates over all children
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;

		virtual void calcStatistics( hkStatisticsCollector* collector) const;

#if !defined(HK_PLATFORM_SPU)
		virtual const hkpShapeContainer* getContainer() const;

		HK_FORCE_INLINE bool isWeldingEnabled() const { return !m_disableWelding; }

#endif

	public:


			/// A flag to allow you to disable the deprecated welding. This is set automatically for a mesh when you call
			/// computeWeldingInfo
		hkBool m_disableWelding;
};

#endif // HK_COLLIDE2_SHAPE_COLLECTION_H

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
