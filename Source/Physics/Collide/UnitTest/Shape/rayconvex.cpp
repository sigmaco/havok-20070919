/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastOutput.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>

#include <Physics/Utilities/Collide/hkpShapeGenerator.h>
//#include <hkgeometryutil2/hkGeometryUtil2.h>
#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#define NTEST	10000

//#define MAX_BOX	900.f
//#define MED_BOX	850.f
//#define MIN_BOX 800.f

#define MAX_BOX	500.f
#define MED_BOX	200.f
#define MIN_BOX 100.f


// Testing the ray(segment) cast on convex objects against
// rayTriangle, for random convex objects (convex hull of a random point cloud)

// Current Test Issues:
// Precondition: make sure the 'from' starts 'out' of the primitive, else the result is undefined !
// What is the tested range ?
// Convex hull (qhull) generation makes the testing relatively 'slow'
// memleaks

int rayconvex_main()
{

	int numvert=4;

	for (int n = 0; n < NTEST; n++ )
	{
		hkVector4 minbox;
		minbox.set(
			hkMath::randRange(MIN_BOX,MED_BOX),
			hkMath::randRange(MIN_BOX,MED_BOX),
			hkMath::randRange(MIN_BOX,MED_BOX));

		hkVector4 maxbox;
		maxbox.set(
			hkMath::randRange(MED_BOX,MAX_BOX),
			hkMath::randRange(MED_BOX,MAX_BOX),
			hkMath::randRange(MED_BOX,MAX_BOX));
#define FIXED_FROM_TO
#ifdef FIXED_FROM_TO
		hkpShapeRayCastInput rc_input;
		rc_input.m_from.set(1000.f,1000.f,1000.f);
		rc_input.m_to.set(1.f,2.f,3.f);
#else
		hkVector4 from(
			hkMath::randRange(-MAX_BOX,MAX_BOX),
			hkMath::randRange(-MAX_BOX,MAX_BOX),
			hkMath::randRange(-MAX_BOX,MAX_BOX));
		hkVector4 to(
			hkMath::randRange(-MAX_BOX,MAX_BOX),
			hkMath::randRange(-MAX_BOX,MAX_BOX),
			hkMath::randRange(-MAX_BOX,MAX_BOX));
	
#endif	//FIXED_FROM

		
		

		int i;
		hkpShapeRayCastOutput rayResults;
		
		hkArray<hkVector4> verts(numvert);
		for(i = 0; i < numvert; ++i)
		{
			for(int j = 0; j < 3; ++j)
			{
				verts[i](j) = hkMath::randRange( minbox(j), maxbox(j) );
			}
		}

		hkpConvexVerticesShape* shape;
		hkArray<hkVector4> planeEquations;
		hkGeometry geom;
		{
			hkStridedVertices str_verts;
			str_verts.m_vertices = &( verts[0](0) );
			str_verts.m_numVertices = verts.getSize();
			str_verts.m_striding = sizeof(hkVector4);

			hkpGeometryUtility::createConvexGeometry( str_verts, geom, planeEquations );
			{
				str_verts.m_numVertices = geom.m_vertices.getSize();
				str_verts.m_striding = sizeof(hkVector4);
				str_verts.m_vertices = &(geom.m_vertices[0](0));
			}

			shape = new hkpConvexVerticesShape(str_verts, planeEquations);
		}		
		
		int hit  = shape->castRay( rc_input, rayResults );
		int hitalternative = 0;

		hkpShapeRayCastOutput triangleResults;

		for (i=0;i<geom.m_triangles.getSize();i++)
		{
			hkGeometry::Triangle ind = geom.m_triangles[i];
			hkpTriangleShape triangle(
				geom.m_vertices[ind.m_a],
				geom.m_vertices[ind.m_b],
				geom.m_vertices[ind.m_c]);
			
			int trianglehit = triangle.castRay( rc_input, triangleResults );
			if (trianglehit)
			{
				//only replace resulting point if closest
				hitalternative=1;
			}
		}
		
		hkBool testguard = (hit == hitalternative);
		HK_TEST2(testguard ,"boolean test iteration " << n);
		if (testguard && hit)
		{
			HK_TEST2(  hkMath::fabs(rayResults.m_hitFraction - triangleResults.m_hitFraction) < 1e-4f, "mindist test iteration " << n);
		}
		
	}
	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(rayconvex_main, "UNKNOWN", "Physics/Test/UnitTest/Collide/", __FILE__  );


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
