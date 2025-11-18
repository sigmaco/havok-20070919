/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_TRIANGLE_SHAPE_H
#define HK_COLLIDE2_TRIANGLE_SHAPE_H

#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>
#include <Physics/Collide/Util/Welding/hkpWeldingUtility.h>

extern const hkClass hkpTriangleShapeClass;

class hkpGskCache;

/// A triangle shape with its details stored as an hkGeometry::Triangle.
/// This shape is typically created at runtime, for example from the hkpMeshShape. You should use the hkpMeshShape, or
/// a variant on it to store a permanent collection of triangles.
class hkpTriangleShape : public hkpConvexShape
{
	public:

		HK_DECLARE_REFLECTION();

		HK_DECLARE_GET_SIZE_FOR_SPU(hkpTriangleShape);

#if !defined(HK_PLATFORM_SPU)
			/// Default constructor
		HK_FORCE_INLINE hkpTriangleShape( hkReal radius = hkConvexShapeDefaultRadius, hkUint16 weldingInfo = 0, hkpWeldingUtility::WeldingType type = hkpWeldingUtility::WELDING_TYPE_NONE);
		
			/// Constructor that sets the points of the triangle.
		HK_FORCE_INLINE hkpTriangleShape(const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, hkReal radius = hkConvexShapeDefaultRadius );
#endif

			/// Get a pointer to the vertices of the triangle.
			/// Returns the hkGeometry::Triangle.
		HK_FORCE_INLINE const hkVector4* getVertices() const;

			/// Get a non const reference to a vertex.
			/// The parameter "i" must be 0, 1 or 2
		HK_FORCE_INLINE hkVector4& getVertex(int i);

			/// Get a const reference to a vertex.
			/// The parameter "i" must be 0, 1 or 2
		HK_FORCE_INLINE const hkVector4& getVertex(int i) const;

			/// Set a vertex
			/// The parameter "i" must be 0, 1 or 2
		HK_FORCE_INLINE void setVertex(int i, const hkVector4& vertex);
		
			//
			// Welding Info
			//

			/// Get the welding info for this triangle
		HK_FORCE_INLINE hkUint16 getWeldingInfo() const;

			/// Set the welding info for this triangle
		HK_FORCE_INLINE void setWeldingInfo( hkUint16 info );



			/// Get the welding type for the triangle
		HK_FORCE_INLINE hkpWeldingUtility::WeldingType getWeldingType() const;

			/// Set the welding type for the triangle
		HK_FORCE_INLINE void setWeldingType( hkpWeldingUtility::WeldingType type );


		HK_FORCE_INLINE bool isExtruded() const;

		HK_FORCE_INLINE const hkVector4& getExtrusion() const;

		HK_FORCE_INLINE void setExtrusion( const hkVector4& extrusion );



		//
		// hkpConvexShape implementation
		//

			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_SUPPORTING_VERTEX_FUNCTION;

			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_CONVERT_VERTEX_IDS_TO_VERTICES_FUNCTION;

			// hkpConvexShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(int) HK_WELD_CONTACT_POINT_FUNCTION;

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
		

			//	hkpConvexShape interface implementation.
		virtual void getFirstVertex(hkVector4& v) const;

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


	protected:

		hkUint16 m_weldingInfo; //+default(0)
		hkEnum<hkpWeldingUtility::WeldingType, hkUint8> m_weldingType; // +default(hkpWeldingUtility::WELDING_TYPE_NONE)
		hkUint8 m_isExtruded;

		hkVector4 m_vertexA; 
		hkVector4 m_vertexB;
		hkVector4 m_vertexC;

		hkVector4 m_extrusion;

	public:

		void setType() { m_type = HK_SHAPE_TRIANGLE; }
		hkpTriangleShape( hkFinishLoadedObjectFlag flag ) : hkpConvexShape( flag ) { m_type = HK_SHAPE_TRIANGLE; }

};

#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.inl>

#endif // HK_COLLIDE2_TRIANGLE_SHAPE_H


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
