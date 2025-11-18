/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_SPHERE_SHAPE_H
#define HK_COLLIDE2_SPHERE_SHAPE_H

#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>

extern const hkClass hkpSphereShapeClass;

/// The hkpSphereShape class is a utility class for storing information representing a basic
/// sphere shape. Note that the functions for getting and setting the radius are in the hkpConvexShape base class.
/// Thus a sphere shape need not hold any data, it is simply an implicit point at the origin with a radius.
class hkpSphereShape : public hkpConvexShape
{
	public:

		HK_DECLARE_REFLECTION();

		HK_DECLARE_GET_SIZE_FOR_SPU(hkpSphereShape);

			/// Creates an arbitrary sphere with given radius.
		hkpSphereShape(hkReal radius);

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
			

		virtual void calcStatistics( hkStatisticsCollector* collector) const;

	
			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerSimulationFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU for raycasting and linear casting
		static void HK_CALL registerCollideQueryFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerGetAabbFunction( ShapeFuncs& sf );

	public:

		hkpSphereShape( hkFinishLoadedObjectFlag flag ) : hkpConvexShape(flag) { m_type = HK_SHAPE_SPHERE; }

		hkUint32 m_pad16[3]; //+nosave
};

#endif // HK_COLLIDE2_SPHERE_SHAPE_H

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
