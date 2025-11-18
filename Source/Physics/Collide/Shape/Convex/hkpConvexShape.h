/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_CONVEX_SHAPE_H
#define HK_COLLIDE2_CONVEX_SHAPE_H

#include <Physics/Collide/Shape/HeightField/hkpSphereRepShape.h>

class hkpCdVertex;
extern const hkClass hkpConvexShapeClass;

extern hkReal hkConvexShapeDefaultRadius;

#define HK_W_NOT_SET_TO_VERTEX_ID "The function getSupportingVertex did not set the .w component of the supporting vertex to the vertex id using set3asUin16"
	/// An interface shape class that allows its implementations to work with GJK. It also holds an extra radius to allow for shells around objects.
class hkpConvexShape : public hkpSphereRepShape
{
	public:		

		HK_DECLARE_REFLECTION();

			/// The GJK interface. It can use the vertexId, which is initialized with 0.
			/// but it has to set the vertexId and it has to set the .w component of supportingVertexOut to the
			/// vertex id using hkVector4::setInt24W
		HK_FORCE_INLINE void getSupportingVertex( hkVector4Parameter direction, hkpCdVertex& supportingVertexOut ) const;

			/// convert an array of input vertex id as returned by getSupportingVertex into an array of vertices
			/// The .w component of the vertices out has to be set to the vertex id using hkVector4::setInt24W
		HK_FORCE_INLINE void convertVertexIdsToVertices( const hkpVertexId* ids, int numIds, hkpCdVertex* vertixArrayOut) const ;
		
			/// Returns the first vertex of this shape. This is only used for initialization of collision detection data.
			/// it has to set the .w component of v to the vertex id using hkVector4::setInt24W
		virtual void getFirstVertex(hkVector4& v) const = 0;

			/// Gets the extra radius.
			/// The radius is used to create a thin "shell" around the object that is used as the shape's surface for collision detection purposes. 
			/// This can improve performance, as calculations for shapes that are actually interpenetrating are much more time-consuming than for interpenetrating shells.
		inline hkReal getRadius() const;

			/// Sets the extra radius
		inline void setRadius(hkReal radius);


		enum WeldResult
		{
			WELD_RESULT_REJECT_CONTACT_POINT,
			WELD_RESULT_ACCEPT_CONTACT_POINT_MODIFIED,
			WELD_RESULT_ACCEPT_CONTACT_POINT_UNMODIFIED
		};

			/// Called internally to "weld" contact points. This is only called for convex objects that are in a shape collection.
		HK_FORCE_INLINE hkpConvexShape::WeldResult weldContactPoint(	hkpVertexId* featurePoints, hkUint8& numFeaturePoints, 
																	hkVector4& contactPointWs, const hkTransform* thisObjTransform, 
																	const hkpConvexShape* collidingShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut ) const;
		
			/// This function returns the center point of the convex object.  This is used for welding calculations.
		HK_FORCE_INLINE void getCentre( hkVector4& centreOut ) const;


		//
		// hkpShape implementation
		//

			/// This is an implementation of the hkpShape::getMaximumProjection() function using getSupportingVertex.
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;

			/// This implementation of the callback driven castRay uses the data driven castRay function
			/// Implementation notes: For all convex shapes except hkSphere and hkCapsule the radius of the shape will be ignored.
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

	protected:
#if !defined(HK_PLATFORM_SPU)
			/// The GJK interface. It can use the vertexId, which is initialized with 0.
			/// but it has to set the vertexId and it has to set the .w component of supportingVertexOut to the
			/// vertex id using hkVector4::setInt24W
		virtual void getSupportingVertexImpl( hkVector4Parameter direction, hkpCdVertex& supportingVertexOut ) const = 0;

			/// convert an array of input vertex id as returned by getSupportingVertex into an array of vertices
			/// The .w component of the vertices out has to be set to the vertex id using hkVector4::setInt24W
		virtual void convertVertexIdsToVerticesImpl( const hkpVertexId* ids, int numIds, hkpCdVertex* vertixArrayOut) const = 0;
#endif

		HK_SPU_VIRTUAL_DECLSPEC(int) HK_WELD_CONTACT_POINT_FUNCTION;
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_CENTRE_FUNCTION;

	protected:

			// The protected constructor which must be supplied with a type and a radius
		inline hkpConvexShape( hkpShapeType type, hkReal radius );

		hkReal m_radius;

	public:

		hkpConvexShape( hkFinishLoadedObjectFlag flag ) : hkpSphereRepShape(flag) { m_type = HK_SHAPE_CONVEX; }

};

#include <Physics/Collide/Shape/Convex/hkpConvexShape.inl>

#endif // HK_COLLIDE2_CONVEX_SHAPE_H


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
