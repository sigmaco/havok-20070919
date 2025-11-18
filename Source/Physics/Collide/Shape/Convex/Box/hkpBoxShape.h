/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_BOX_SHAPE_H
#define HK_COLLIDE2_BOX_SHAPE_H

#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>

extern const hkClass hkpBoxShapeClass;

/// A simple box shape centered around the origin.
class hkpBoxShape : public hkpConvexShape
{
	public:	

		HK_DECLARE_REFLECTION();

		HK_DECLARE_GET_SIZE_FOR_SPU(hkpBoxShape);

			/// Creates a box with the given half extents ( An (X by Y by Z) box has the half-extents (X/2, Y/2, Z/2) ).
		hkpBoxShape( const hkVector4& halfExtents, hkReal radius = hkConvexShapeDefaultRadius );

		/// Gets the half extents ( An (X by Y by Z) box has the half-extent (X/2, Y/2, Z/2) ).
		inline const hkVector4& getHalfExtents() const;

			/// Sets the half extents. Note that changing the half extents will not wake up sleeping objects.
		void setHalfExtents(const hkVector4& halfExtents);

		
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


			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerSimulationFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerCollideQueryFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerGetAabbFunction( ShapeFuncs& sf );

		
		virtual void calcStatistics( hkStatisticsCollector* collector) const;


	protected:

		hkVector4 m_halfExtents;


	public:
		~hkpBoxShape();

		hkpBoxShape( hkFinishLoadedObjectFlag flag ) : hkpConvexShape(flag) { m_type = HK_SHAPE_BOX; }

};


#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.inl>

#endif // HK_COLLIDE2_BOX_SHAPE_H

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
