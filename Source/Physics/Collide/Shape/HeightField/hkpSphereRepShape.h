/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_COLLISION_SPHERES_SHAPE_H
#define HK_COLLIDE2_COLLISION_SPHERES_SHAPE_H

#include <Physics/Collide/Shape/hkpShape.h>

extern const hkClass hkpSphereShapeClass;
class hkSphere;

#define HK_GET_COLLISION_SPHERE_BUFFER_SIZE 64

/// This interface produces a set of spheres that represent a very simplified version of the objects surface.
/// Note: This interface's function is used by hkpHeightFieldShape implementations
class hkpSphereRepShape : public hkpShape
{
	public:

		HK_DECLARE_REFLECTION();

			/// Get information about the call getCollisionSpheres
		HK_FORCE_INLINE int getNumCollisionSpheres( )  const;

			/// Gets a set of spheres representing a simplified shape. For instance, a box could return its eight corners.
		HK_FORCE_INLINE const hkSphere* getCollisionSpheres( hkSphere* sphereBuffer ) const;

	protected:
#if !defined(HK_PLATFORM_SPU)
		virtual int getNumCollisionSpheresImpl( )  const = 0;
		virtual const hkSphere* getCollisionSpheresImpl( hkSphere* sphereBuffer ) const = 0;
#endif
	public:

		hkpSphereRepShape( hkpShapeType type ) : hkpShape( type ) {}

		hkpSphereRepShape( hkFinishLoadedObjectFlag flag ) : hkpShape(flag) { m_type = HK_SHAPE_SPHERE_REP; }

};

#include <Physics/Collide/Shape/HeightField/hkpSphereRepShape.inl>

#endif // HK_COLLIDE2_COLLISION_SPHERES_SHAPE_H

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
