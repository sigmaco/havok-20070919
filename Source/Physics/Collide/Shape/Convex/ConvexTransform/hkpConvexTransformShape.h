/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_CONVEX_TRANSFORM_SHAPE_H
#define HK_COLLIDE2_CONVEX_TRANSFORM_SHAPE_H

#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>
#include <Physics/Collide/Shape/hkpShapeContainer.h>

extern const hkClass hkpConvexTransformShapeClass;

	/// An hkpConvexTransformShape contains an hkpShape and an additional transform for that shape. 
	///	This is useful, for instance, if you
	/// want to position child shapes correctly when constructing a compound shape.
	/// The advantage of using hkpConvexTransformShape over hkpTransformShape is that
	/// it does not require additional agents to be created, as the hkpConvexTransformShape is
	/// a convex shape and directly works with GSK.
	/// However, if you use the hkpConvexTransformShape wrapping an hkpBoxShape, no hkpBoxBoxAgent will be
	/// created, but the hkpGskfAgent.
	///
	/// For detailed information on SPU handling for this shape, see hkpConvexTranslateShape.h
class hkpConvexTransformShape : public hkpConvexShape
{
	public:

		HK_DECLARE_REFLECTION();

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CDINFO);

			/// Constructs a new convex transform shape.
		hkpConvexTransformShape(const hkpConvexShape* childShape, const hkTransform& transform);

#if !defined(HK_PLATFORM_SPU)
		hkpConvexTransformShape( class hkFinishLoadedObjectFlag flag ) : hkpConvexShape(flag), m_childShape(flag) { m_type = HK_SHAPE_CONVEX_TRANSFORM; }
#endif

			/// Sets the current transform.
			/// Don't do this once the shape is added to a world
			/// as the agents may have cached data dependent on it.
		void setTransform( const hkTransform& transform );


		//
		// hkpConvexShape implementation 
		//


			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_SUPPORTING_VERTEX_FUNCTION;

			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_CONVERT_VERTEX_IDS_TO_VERTICES_FUNCTION;

			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_CENTRE_FUNCTION;

		//
		// hkpSphereRepShape implementation
		//

			// hkpSphereRepShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(int) HK_GET_NUM_COLLISION_SPHERES_FUNCTION;

			// hkpSphereRepShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(const hkSphere*)	HK_GET_COLLISION_SPHERES_FUNCTION;

		//
		// hkpShape implementation
		//
			// hkpShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_AABB_FUNCTION;

			//	hkpShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(hkBool) HK_RAYCAST_FUNCTION;

			// hkpConvexShape interface implementation.
		virtual void getFirstVertex(hkVector4& v) const;

	

			/// Get the child shape.
		inline const hkpConvexShape* getChildShape() const;

			/// Gets the transform from the child shape's space to this transform shape's local space.
		inline hkTransform& getTransform();

			/// Gets the transform from the child shape's space to this transform shape's local space.
		inline const hkTransform& getTransform() const;


		//
		// hkpShape Implementation
		//

			//	hkpShape interface implementation.
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;
	

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerSimulationFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerCollideQueryFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerGetAabbFunction( ShapeFuncs& sf );

			//	hkpShape interface implementation.
		void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& parentCdBody, hkpRayHitCollector& collector ) const;

		virtual void calcStatistics( hkStatisticsCollector* collector) const;

		virtual const hkpShapeContainer* getContainer() const;
		
		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;

			// For internal use only
		inline void initializeSpu( const hkpConvexShape* childShape, const hkTransform& transform, hkReal radius );

	protected:

		void getChildShapeFromPpu() const;

	protected:

		class hkpSingleShapeContainer m_childShape;

			// 0 if the child shape is following this hkpConvexTransformShape consecutively in memory, the size of the child shape otherwise
		mutable int m_childShapeSize; // +nosave

		hkTransform m_transform;
};

#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.inl>

#endif // HK_COLLIDE2_CONVEX_TRANSFORM_SHAPE_H

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
