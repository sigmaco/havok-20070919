/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_CONVEX_VERTICES_SHAPE_H
#define HK_COLLIDE2_CONVEX_VERTICES_SHAPE_H

#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>
#include <Common/Base/Types/Geometry/hkStridedVertices.h>

extern const hkClass hkpConvexVerticesShapeClass;

/// You can use this shape class to create a convex geometric object by specifying a set of vertices. 
/// Specify the vertices in the shape's local space. You must also provide the planes of the convex hull, which
/// can be computed using hkpGeometryUtility::createConvexGeometry function (see the ConvexVerticesShapeApi for example).
class hkpConvexVerticesShape : public hkpConvexShape
{
	public:

		// 4 vectors stored transposed in the "columns" not the rows
		struct FourVectors
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpConvexVerticesShape::FourVectors );
			HK_DECLARE_REFLECTION();

			hkVector4 m_x;
			hkVector4 m_y;
			hkVector4 m_z;
		};

	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_GET_SIZE_FOR_SPU(hkpConvexVerticesShape);

			/// Construct the shape from the given vertices and matching plane equations.
			/// These are plane equations of the convex hull and can be generated
			/// using the hkpGeometryUtility::createConvexGeometry method. 
			/// This constructor makes an internal copy of the vertices.
			/// You should take care of not passing in unnecessary vertices, e.g. inner vertices or
			/// duplicated vertices. hkpGeometryUtility::createConvexGeometry will also give
			/// you back a clean list of vertices to use. See our Havok demos
		hkpConvexVerticesShape(const hkStridedVertices& vertsIn, const hkArray<hkVector4>& planeEquations, hkReal radius = hkConvexShapeDefaultRadius);

			/// Create from precomputed data.
			/// Note that numVertices is the actual number of vertices, not the
			/// number of FourVectors structures.
		hkpConvexVerticesShape( FourVectors* rotatedVertices, int numVertices,
				hkVector4* planes, int numPlanes,
				const hkAabb& aabb, hkReal radius = hkConvexShapeDefaultRadius );

			/// The hkpConvexVerticesShape stores the vertices in optimized form.
			/// This function will retrieve them into the vertices array.
			/// It copies the vertices so is able to be a const method.
		void getOriginalVertices( hkArray<hkVector4>& vertices ) const;

			/// Returns the plane equations passed into the constructor
		const hkArray<hkVector4>& getPlaneEquations() const;

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

			// hkpConvexShape interface implementation
		void getFirstVertex(hkVector4& v) const;


		//
		// hkpShape implementation
		//
		
			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerSimulationFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerCollideQueryFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerGetAabbFunction( ShapeFuncs& sf );

		virtual void calcStatistics( hkStatisticsCollector* collector) const;

		void copyVertexData(const float* vertexIn, int byteStriding, int numVertices);

	protected:

		hkVector4	m_aabbHalfExtents;
		hkVector4	m_aabbCenter;

		// hkInplaceArray<FourVectors, 3> m_rotatedVertices;
		hkArray<struct FourVectors> m_rotatedVertices;
		hkInt32		m_numVertices;

		hkArray<hkVector4>	m_planeEquations;

	public:

		hkpConvexVerticesShape( hkFinishLoadedObjectFlag flag ) : hkpConvexShape(flag), m_rotatedVertices(flag), m_planeEquations(flag) { m_type = HK_SHAPE_CONVEX_VERTICES; }
};


#endif // HK_COLLIDE2_CONVEX_VERTICES_SHAPE_H

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
