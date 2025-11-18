/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_CAPSULE_SHAPE_H
#define HK_COLLIDE2_CAPSULE_SHAPE_H

#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>

extern const hkClass hkpCapsuleShapeClass;

	/// A capsule defined by two points and a radius.
	/// The points are stored internally as hkSpheres, each point being the center of one of the
	/// end spheres of the capsule.
class hkpCapsuleShape : public hkpConvexShape
{
	public:

		HK_DECLARE_REFLECTION();

			/// For raycasting, the part of the shape hit.
		enum RayHitType
		{
			HIT_CAP0,
			HIT_CAP1,
			HIT_BODY,
		};

			/// Creates a new hkpCapsuleShape using the specified points and radius
		hkpCapsuleShape( const hkVector4& vertexA,const hkVector4& vertexB, hkReal radius );

			/// Gets the pointer to the first vertex. This casts the corresponding hkSphere (m_vertexA) to a hkVector4*.
			/// You can then index by 0 or 1, to get the first or second vertex respectively.
		inline const hkVector4* getVertices() const;

			/// Gets a vertex given an index "i". "i" can be 0 or 1. This casts the corresponding hkSphere to a hkVector4.
		HK_FORCE_INLINE const hkVector4& getVertex(int i) const;

			/// Sets a vertex given an index "i". "i" can be 0 or 1.
		HK_FORCE_INLINE void setVertex(int i, const hkVector4& position );

		//
		// hkpConvexShape implementation 
		//


			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_SUPPORTING_VERTEX_FUNCTION;

			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_CONVERT_VERTEX_IDS_TO_VERTICES_FUNCTION;

			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_CENTRE_FUNCTION;


		HK_DECLARE_GET_SIZE_FOR_SPU(hkpCapsuleShape);
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

			/// hkpConvexShape interface implementation.
			/// Returns the first vertex of this shape. This is only used for initialization of collision detection data.
		virtual void getFirstVertex(hkVector4& v) const;
			


			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerSimulationFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerCollideQueryFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerGetAabbFunction( ShapeFuncs& sf );


		virtual void calcStatistics( hkStatisticsCollector* collector) const;

	public:

		static void HK_CALL closestPointLineSeg( const hkVector4& A, const hkVector4& B, const hkVector4& B2, hkVector4& pt );
		static void HK_CALL closestInfLineSegInfLineSeg( const hkVector4& A, const hkVector4& dA, const hkVector4& B, const hkVector4& dB, hkReal& distSquared, hkReal& t, hkReal &u, hkVector4& p, hkVector4& q );

	protected:

		// The line's first point. 
		hkVector4  m_vertexA;

		// The line's second point. 
		hkVector4  m_vertexB;

	public:

		hkpCapsuleShape( hkFinishLoadedObjectFlag flag ) : hkpConvexShape(flag) { m_type = HK_SHAPE_CAPSULE; }

};

#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.inl>

#endif // HK_COLLIDE2_CAPSULE_SHAPE_H

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
