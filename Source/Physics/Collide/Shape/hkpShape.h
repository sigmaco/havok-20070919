/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_SHAPE_H
#define HK_COLLIDE2_SHAPE_H

#include <Common/Base/hkBase.h>
#include <Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Physics/Collide/Shape/hkpShapeType.h>
#include <Physics/Collide/Shape/Convex/hkpCdVertex.h>

class hkAabb;
struct hkpShapeRayCastInput;
struct hkpShapeRayCastOutput;
class hkpRayHitCollector;
class hkpCdBody;
class hkpShapeContainer;
class hkSphere;

enum {  HK_SHAPE_BUFFER_ALIGNMENT = 16,	HK_SHAPE_BUFFER_SIZE = 256 };
typedef HK_ALIGN16( char ShapeBuffer[HK_SHAPE_BUFFER_SIZE] );	// <ng.todo.aa	duplicating typedef in hkpShapeContainer

typedef hkUint16 hkpVertexId;
typedef hkUint32 hkpShapeKey;
#define HK_INVALID_SHAPE_KEY 0xffffffff
#define HK_INVALID_VERTEX_ID 0xffff




#define HK_DECLARE_GET_SIZE_FOR_SPU(CLASS) int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const { return sizeof(*this); }

#if defined (HK_PLATFORM_SPU)
# define HK_SHAPE_CONTAINER hkpShape
#else
# define HK_SHAPE_CONTAINER hkpShapeContainer
#endif

extern const hkClass hkpShapeClass;
class hkpConvexShape;

/// The base class for narrow phase collision detection objects.
/// All narrow phase collision detection is performed between pairs of hkpShape objects by creating appropriate hkpCollisionAgent objects.
/// An hkpShape can be a simple shape such as a box or sphere, a shape with additional transform information,
/// or a compound shape made up of simpler hkShapes. hkpShape instances can be shared within or even between 
/// rigid bodies. See the hkpShape subclasses for more details.
class hkpShape : public hkReferencedObject
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CDINFO);

			/// Sets the user data to 0
			/// Sets the type to the specified type
		HK_FORCE_INLINE hkpShape( hkpShapeType type );

			/// Gets the hkpShape type. This is used by the collision dispatcher to dispatch between pairs of shapes
		HK_FORCE_INLINE hkpShapeType getType() const;

			/// Gets the AABB for the hkpShape given a local to world transform and an extra tolerance.
			/// 
			/// Forwards to getAabbImpl()
		HK_FORCE_INLINE void getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const;

			/// Support for creating bounding volume hierarchies of shapes.
			/// This function returns the maximal extent of a shape along a given direction. 
			/// It is not the same as hkpConvexShape::getSupportingVertex, because the extent does not have to be exact, it just has to at least
			/// contain the shape. It is for the purposes of creating bounding volumes around the shape ( mid-phase ) rather than exact collision
			/// detection (narrow-phase).
			/// The default implementation of this function uses the aabb of the shape. For custom shapes, you can get a better fit.
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;

			/// Get the user data for the shape (initialized to 0)
		inline hkUlong getUserData() const;

			/// Set the user data of the shape: This is a real user data and not used by the engine otherwise.
			/// If you are interested in triangle indices, you can retrieve this information from the hkpCdBody
			/// during most callbacks.
		inline void setUserData( hkUlong data );
		
			/// Finds the closest intersection between the shape and a ray defined in the shape's local space, starting at fromLocal, ending at toLocal.
			/// This is data driven, and places the results in hkpShapeRayCastOutput
			/// Implementation notes: For all convex shapes except hkSphere and hkCapsule the radius of the shape will be ignored.
		HK_FORCE_INLINE hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output ) const;
	
			/// Finds the closest intersection between the shape and a ray defined in the shape's local space, starting at fromLocal, ending at toLocal.
			/// This is a callback driven raycast. For each hit found, the hkpRayHitCollector receives a callback with the hit info.
			/// Implementation notes: For all convex shapes except hkSphere and hkCapsule the radius of the shape will be ignored.
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const = 0;

			/// Query if the shape supports the container interface.
			/// Returns a pointer to the interface if the shape does has one or more child shapes.
			/// Otherwise returns null.
		virtual const hkpShapeContainer* getContainer() const { return HK_NULL; }


#if defined (HK_PLATFORM_SPU)
		inline hkUint32 getCollisionFilterInfo( hkpShapeKey key ) const;
		inline const hkpShape* getChildShape( hkpShapeKey key, ShapeBuffer& buffer ) const;
#endif
			// Returns the size of the shape class. The default implementation returns -1 which will force the shape onto the PPU.
		struct CalcSizeForSpuInput
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShape::CalcSizeForSpuInput );

			bool m_midphaseAgent3Registered;
			bool m_isFixedOrKeyframed;
		};

		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const { return -1; }

	protected:	

#if !defined(HK_PLATFORM_SPU)
		virtual void getAabbImpl( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const = 0;
		virtual hkBool castRayImpl( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output ) const = 0;
#endif
	public:

			static void HK_CALL resetShapeFunctions();
			//
			//	A hand coded vtable replacement, needed to run code on the spu
			//

			typedef void (HK_CALL *GetSupportingVertexFunc)        (const void* thisObj, hkVector4Parameter direction, hkpCdVertex &supportVertex );
			typedef void (HK_CALL *ConvertVertexIdsToVerticesFunc)	(const void* thisObj, const hkpVertexId* ids, int numIds, class hkpCdVertex* verticesOut );
			typedef int (HK_CALL *WeldContactPointFunc)	(const void* thisObj, hkpVertexId* featurePoints, hkUint8& numFeaturePoints, hkVector4& contactPointWs, const hkTransform* thisObjTransform, const hkpConvexShape* collidingShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut );

			typedef void (HK_CALL *GetCentreFunc)	(const void* thisObj, hkVector4& centreOut );

			typedef int  (HK_CALL *GetNumCollisionSpheresFunc)		(const void* thisObj );
			typedef const hkSphere* (HK_CALL *GetCollisionSpheresFunc)(const void* thisObj, hkSphere* sphereBuffer );

			typedef void (HK_CALL *GetAabbFunc)					(const void* thisObj, const hkTransform& localToWorld, hkReal tolerance, hkAabb& out );
			typedef hkBool (HK_CALL *CastRayFunc) (const void* thisObj, const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output );

			typedef const hkpShape* (HK_CALL *GetChildShapeFunc) (const void* thisObj, hkpShapeKey key, ShapeBuffer& buffer );
			typedef hkUint32 (HK_CALL *GetCollisionFilterInfoFunc) (const void* thisObj, hkpShapeKey key );


			struct ShapeFuncs
			{
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShape::ShapeFuncs );

				hkPadSpu<GetSupportingVertexFunc>			m_getSupportingVertexFunc;
				hkPadSpu<ConvertVertexIdsToVerticesFunc>	m_convertVertexIdsToVertices;
				hkPadSpu<WeldContactPointFunc>				m_weldContactPointFunc;
				hkPadSpu<GetCentreFunc>						m_getCentreFunc;
				hkPadSpu<GetNumCollisionSpheresFunc>		m_getNumCollisionSpheresFunc;
				hkPadSpu<GetCollisionSpheresFunc>			m_getCollisionSpheresFunc;
				hkPadSpu<GetAabbFunc>						m_getAabbFunc;
				hkPadSpu<CastRayFunc>						m_castRay;
				hkPadSpu<GetChildShapeFunc>					m_getChildShapeFunc;
				hkPadSpu<GetCollisionFilterInfoFunc>		m_getCollisionFilterInfoFunc;
			};

			// helper functions to be used with the hkpCollisionDispatcher
			struct ShapeFuncs2
			{
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShape::ShapeFuncs2 );

				HK_ALIGN( GetSupportingVertexFunc	m_getSupportingVertexFunc, 64);
				ConvertVertexIdsToVerticesFunc		m_convertVertexIdsToVertices;
				WeldContactPointFunc				m_weldContactPointFunc;
				GetCentreFunc						m_getCentreFunc;
				GetNumCollisionSpheresFunc			m_getNumCollisionSpheresFunc;
				GetCollisionSpheresFunc				m_getCollisionSpheresFunc;
				GetAabbFunc							m_getAabbFunc;
				CastRayFunc							m_castRay;
				GetChildShapeFunc					m_getChildShapeFunc;
				GetCollisionFilterInfoFunc			m_getCollisionFilterInfoFunc;
			};
	public:
#if defined(HK_PLATFORM_SPU)
		static HK_FORCE_INLINE ShapeFuncs2& getShapeFunctions( int shapeId )
		{
			 HK_ASSERT2( 0xf0345465, unsigned(shapeId) < HK_SHAPE_MAX_ID_SPU, "Your shape type is not supported on SPU" );
			 return m_shapeFunctions[shapeId];
		 }

		static void setShapeFunctions( int shapeId, ShapeFuncs& funcs );
	private:
		static ShapeFuncs2 m_shapeFunctions[ HK_SHAPE_MAX_ID_SPU ];
#endif

	public:

		hkUlong m_userData;

	public:
		hkEnum< ::hkpShapeType, hkUint32> m_type; //+nosave

	public:

		hkpShape( class hkFinishLoadedObjectFlag flag ) { m_type = HK_SHAPE_INVALID; }
};

// 
#ifdef HK_PLATFORM_SPU
	#define HK_SPU_VIRTUAL_DECLSPEC(RETURN_TYPE) static RETURN_TYPE HK_CALL
	#define HK_GET_THIS_PTR thisObjParam

	#define HK_GET_SUPPORTING_VERTEX_FUNCTION getSupportingVertexImpl( const void* thisObjParam, hkVector4Parameter direction, hkpCdVertex& supportingVertexOut )
	#define HK_CONVERT_VERTEX_IDS_TO_VERTICES_FUNCTION convertVertexIdsToVerticesImpl(const void* thisObjParam, const hkpVertexId* ids, int numIds, hkpCdVertex* verticesOut)
	#define HK_WELD_CONTACT_POINT_FUNCTION weldContactPointImpl(const void* thisObjParam, hkpVertexId* featurePoints, hkUint8& numFeaturePoints, hkVector4& contactPointWs, const hkTransform* thisObjTransform, const hkpConvexShape* collidingShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut )
	#define HK_GET_CENTRE_FUNCTION getCentreImpl( const void* thisObjParam, hkVector4& centreOut )

	#define HK_GET_NUM_COLLISION_SPHERES_FUNCTION getNumCollisionSpheresImpl(const void* thisObjParam )
	#define HK_GET_COLLISION_SPHERES_FUNCTION getCollisionSpheresImpl(const void* thisObjParam, hkSphere* sphereBuffer )

	#define HK_GET_AABB_FUNCTION getAabbImpl( const void* thisObjParam, const hkTransform& localToWorld, hkReal tolerance, hkAabb& out )
	#define HK_RAYCAST_FUNCTION castRayImpl( const void* thisObjParam, const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results )

	#define HK_GET_CHILD_SHAPE_FUNCTION getChildShapeImpl( const void* thisObjParam, hkpShapeKey key, ShapeBuffer& buffer  )
	#define HK_GET_COLLISION_FILTER_INFO_FUNCTION getCollisionFilterInfoImpl( const void* thisObjParam, hkpShapeKey key )
#else
	#define HK_SPU_VIRTUAL_DECLSPEC(RETURN_TYPE) virtual RETURN_TYPE
	#define HK_GET_THIS_PTR this

	#define HK_GET_SUPPORTING_VERTEX_FUNCTION getSupportingVertexImpl( hkVector4Parameter direction, hkpCdVertex& supportingVertexOut) const
	#define HK_CONVERT_VERTEX_IDS_TO_VERTICES_FUNCTION convertVertexIdsToVerticesImpl(const hkpVertexId* ids, int numIds, hkpCdVertex* verticesOut) const
	#define HK_WELD_CONTACT_POINT_FUNCTION weldContactPointImpl( hkpVertexId* featurePoints, hkUint8& numFeaturePoints, hkVector4& contactPointWs, const hkTransform* thisObjTransform, const hkpConvexShape* collidingShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut ) const

	#define HK_GET_CENTRE_FUNCTION getCentreImpl( hkVector4& centreOut ) const

	#define HK_GET_NUM_COLLISION_SPHERES_FUNCTION getNumCollisionSpheresImpl( ) const
	#define HK_GET_COLLISION_SPHERES_FUNCTION getCollisionSpheresImpl(hkSphere* sphereBuffer ) const

	#define HK_GET_AABB_FUNCTION getAabbImpl( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const
	#define HK_RAYCAST_FUNCTION castRayImpl( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const

	#define HK_GET_CHILD_SHAPE_FUNCTION getChildShape( hkpShapeKey key, ShapeBuffer& buffer ) const
	#define HK_GET_COLLISION_FILTER_INFO_FUNCTION getCollisionFilterInfo( hkpShapeKey key ) const

#endif

#include <Physics/Collide/Shape/hkpShape.inl>

#endif // HK_COLLIDE2_SHAPE_H

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
