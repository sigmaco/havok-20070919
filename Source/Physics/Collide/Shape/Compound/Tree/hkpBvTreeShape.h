/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_BV_TREE_SHAPE_H
#define HK_COLLIDE2_BV_TREE_SHAPE_H

#include <Physics/Collide/Shape/hkpShape.h>
#include <Physics/Collide/Shape/hkpShapeContainer.h>
#include <Physics/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Common/Base/Types/Geometry/Sphere/hkSphere.h>

class hkpShapeCollection;

extern const hkClass hkpBvTreeShapeClass;

	// The maximum number of keys returned by a single queryAabb query. Must be a power of 2
#if !defined(HK_PLATFORM_SPU)
	enum { HK_MAX_NUM_HITS_PER_AABB_QUERY = 4096 };
#else
	enum { HK_MAX_NUM_HITS_PER_AABB_QUERY = 1024 };
#endif

/// An hkpBvTreeShape adds bounding volume tree information to an hkpShapeCollection, such as an hkpMeshShape.
/// This is an abstract base class. See hkpMoppBvTreeShape for an implementation.
///
/// <b>What does the bounding volume tree do?</b><br>
///
/// A bounding volume tree is useful in situations where you need to check for collisions between a moving object
/// and a large static geometry, such as a landscape. <br> \n
/// The shapes that make up the landscape are hierarchically grouped in
/// a binary bounding volume tree.
/// At every node in the tree there exists a bounding polytope, which encapsulates all 
/// of its children. The top-level bounding volume contains the entire landscape, while
/// the nodes on the leaf levels encapsulate one geometric primitive, normally a
/// triangle. The fit of this bounding volume can be perfect (as in some AABB trees), or can 
/// have an extra margin/tolerance built in (e.g. MOPP):\n\n\n
/// <center><img src="pix/twoTriangles.gif"></center>\n
///
/// Instead of checking whether the moving object is colliding with each of the triangles in the landscape in turn,
/// which would be extremely time-consuming, the bounding box of the moving object
/// is checked against the bounding volume tree - first, whether it is intersecting with the top-level bounding volume, then with
/// any of its child bounding volumes, and so on until the check reaches the leaf nodes. A list of any potentially colliding triangles
/// is then passed to the narrow phase collision detection. You can think of
/// the bounding volume tree as a filter to the narrow phase collision
/// detection system.<br>
class hkpBvTreeShape: public hkpShape
{
	public:
		
		HK_DECLARE_REFLECTION();

			/// Creates an hkpBvTreeShape with the specified hkpShapeCollection.
		inline hkpBvTreeShape( hkpShapeType type );

			/// Returns the hkpShapeKey for all shapes in the hkpShapeCollection that intersect with the obb (defined by obbTransform and obbExtent).
		virtual void queryObb( const hkTransform& obbTransform, const hkVector4& obbExtent, hkReal tolerance, hkArray< hkpShapeKey >& hits ) const = 0;

			/// Returns the hkpShapeKey for all shapes in the hkpShapeCollection that intersect with the AABB
		virtual void queryAabb( const hkAabb& aabb, hkArray<hkpShapeKey>& hits ) const = 0;

			/// Populates the preallocated hits buffer with shape keys, returns the number of actual hits which may be greater than maxNumKeys
			/// The hits array should be able to hold maxNumKeys keys. On SPU this is no more than HK_MAX_NUM_HITS_PER_AABB_QUERY
		virtual hkUint32 queryAabb( const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) const = 0;

		virtual const hkpShapeContainer* getContainer() const = 0;
		
	public:

		hkpBvTreeShape( hkFinishLoadedObjectFlag flag ) : hkpShape(flag) { m_type = HK_SHAPE_BV_TREE; }
};


#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShape.inl>

#endif // HK_COLLIDE2_BV_TREE_SHAPE_H

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
