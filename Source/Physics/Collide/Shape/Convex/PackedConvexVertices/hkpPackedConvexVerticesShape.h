/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_PACKED_CONVEX_VERTICES_SHAPE_H
#define HK_COLLIDE2_PACKED_CONVEX_VERTICES_SHAPE_H

#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>
#include <Common/Base/Types/Geometry/hkStridedVertices.h>

extern const hkClass hkpPackedConvexVerticesShapeClass;

/// You can use this shape class to create a convex geometric object by specifying a set of vertices. 
/// Specify the vertices in the shape's local space. You must also provide the planes of the convex hull, which
/// can be computed using hkpGeometryUtility::createConvexGeometry function (see the ConvexVerticesShapeApi for example).
class hkpPackedConvexVerticesShape : public hkpConvexShape
{
	public:

		HK_DECLARE_REFLECTION();
		//HK_DECLARE_GET_SIZE_FOR_SPU(hkpPackedConvexVerticesShape);

			/// Construct the shape from the given vertices.
		hkpPackedConvexVerticesShape(hkStridedVertices vertsIn, const hkArray<hkVector4>& planeEquations, hkReal radius = hkConvexShapeDefaultRadius);

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

		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;

		void compressVertexData(const float* vertexIn, int byteStriding, int numVertices );

		// 4 vectors stored transposed in the "columns" not the rows
		struct FourVectors
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpPackedConvexVerticesShape::FourVectors );
			HK_DECLARE_REFLECTION();
			hkUint8 m_x[4];
			hkUint8 m_y[4];
			hkUint8 m_z[4];
		};

		class Vector4IntW 
		{
		public:
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpPackedConvexVerticesShape::Vector4IntW );
			HK_DECLARE_REFLECTION();

			HK_ALIGN16(hkReal m_x); 
			hkReal m_y; 
			hkReal m_z; 
			hkUint32 m_w; 
		}; 

	public:   

		enum { BUILTIN_FOUR_VECTORS=16 };   

		//parent //20
		hkArray<hkVector4> m_planeEquations; // 32
		// 48 // aabbMin int24.w -> numVertices         
		hkVector4 m_aabbMin; //+overridetype(class Vector4IntW) 
		hkVector4 m_aabbExtents; // 64 // .w -> unused
		struct FourVectors m_vertices[hkpPackedConvexVerticesShape::BUILTIN_FOUR_VECTORS]; // 256
	
	public:

		hkpPackedConvexVerticesShape( hkFinishLoadedObjectFlag flag ) : hkpConvexShape(flag), m_planeEquations(flag) { m_type = HK_SHAPE_PACKED_CONVEX_VERTICES; }
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
