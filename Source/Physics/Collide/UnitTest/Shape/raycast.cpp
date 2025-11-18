/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
 // Large include
#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Collection/SimpleMesh/hkpSimpleMeshShape.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppUtility.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastOutput.h>

#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

//
// raycast_tests method, actually does the ray tests
//
void raycast_tests( const hkpShape* shape, const char* desciption, hkBool isConvex )
{
	// all rays are 0.5 units long
	
	// add a micro-meter tolerance
	const hkReal tolerance = 0.000001f;

	// ray outside cube
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f, 1.5f, 0.0f );
		ray.m_to  .set( 0.0f, 1.0f, 0.0f );

		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		HK_TEST2( output.hasHit() == false, desciption );
	}

	// ray penetrating cube, start outside cube
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f, 0.9f, 0.0f );
		ray.m_to  .set( 0.0f, 0.4f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		HK_TEST2( output.hasHit(), desciption );
		HK_TEST2( hkMath::fabs( output.m_hitFraction  - 0.8f) < tolerance, desciption  );
	}

	// ray outside cube, end touching surface
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f, 1.0f, 0.0f );
		ray.m_to  .set( 0.0f, 0.5f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		HK_TEST2( !output.hasHit(), desciption << ": ray outside cube, end touching surface" );
	}

	// ray outside cube, parallel to a face
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.5f, 1.5f, 0.0f );
		ray.m_to  .set( 0.5f, 1.0f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		HK_TEST2( !output.hasHit(), desciption << ":ray outside cube, parallel to a face" );
	}

	// ray inside cube, start touching surface
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f, 0.5f, 0.0f );
		ray.m_to  .set( 0.0f, 0.0f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		HK_TEST2( output.hasHit(), desciption << ":ray inside cube, start touching surface"  );
		if ( output.hasHit() )
		{
			HK_TEST2( hkMath::fabs( output.m_hitFraction  - 0.0f) < tolerance, desciption  );
		}
	}

	// zero length ray on the surface
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f, 0.5f, 0.0f );
		ray.m_to  .set( 0.0f, 0.5f, 0.0f );
		
		hkpShapeRayCastOutput output;

	
		if ( shape->getType() != HK_SHAPE_SPHERE )
		{
			shape->castRay( ray, output);
		}

		HK_TEST2( output.hasHit() == false, desciption );
	}

	// ray completely inside cube
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f, 0.25f, 0.0f );
		ray.m_to  .set( 0.0f,-0.25f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		HK_TEST2( output.hasHit() == false, desciption );
	}

	
	// ray inside cube, end touching surface
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f, 0.0f, 0.0f );
		ray.m_to  .set( 0.0f,-0.5f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		HK_TEST2( output.hasHit() == false, desciption );
	}



	// raycast penetrating cube, start inside cube
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f,-0.1f, 0.0f );
		ray.m_to  .set( 0.0f,-0.6f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		if ( isConvex )
		{
			HK_TEST2( output.hasHit() == false, desciption << ": startPenetrates endOutside does return a false hit" );
		}
		else
		{
			HK_TEST2( output.hasHit() , desciption << ": startPenetrates endOutside does not return a hit" );
			HK_TEST2( hkMath::fabs( output.m_hitFraction  - 0.8f) < tolerance, desciption  );
		}
	}

	// raycast outside cube, start touching cube
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f,-0.5f, 0.0f );
		ray.m_to  .set( 0.0f,-1.0f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		if ( isConvex )
		{
			HK_TEST2( output.hasHit() == false, desciption );
		}
		else
		{
			HK_TEST2( output.hasHit(), desciption );
			if (output.hasHit())
			{
				HK_TEST2( hkMath::fabs( output.m_hitFraction  - 0.0f) < tolerance, desciption  );
			}
		}
	}

	
	// start and end outside cube but penetrating it twice
	{
		hkpShapeRayCastInput ray;
		ray.m_from.set( 0.0f, 1.0f, 0.0f );
		ray.m_to  .set( 0.0f,-1.0f, 0.0f );
		
		hkpShapeRayCastOutput output;
		shape->castRay( ray, output );

		// only 1 hit is reported here as it always returns the closest hit
		HK_TEST2( output.hasHit(), desciption );
		HK_TEST2( hkMath::fabs( output.m_hitFraction  - 0.25f) < tolerance, desciption  );
	}
}


//
// createMoppShape helper method
//
static hkpMoppBvTreeShape* createMoppBvTreeShape( const hkVector4* vertices, const int numVertices,
										         const short* indices, const int numTriangles, const int indicesStride )
{
	// build storage mesh shape, will be owned by the MoppBVTreeShape
	hkpSimpleMeshShape* meshShape = new hkpSimpleMeshShape(0.0001f);
	
	meshShape->m_vertices.setSize(numVertices);
	meshShape->m_triangles.setSize(numTriangles);
	for ( int i = 0; i < numVertices; i++ )
	{
		meshShape->m_vertices[i] = vertices[i];
	}
	
	int curT = 0;
	const int numIndicesPerTriangle = indicesStride / sizeof( short );
	for ( unsigned int j = 0; curT < numTriangles; j += numIndicesPerTriangle )
	{
		meshShape->m_triangles[curT].m_a = indices[j];
		meshShape->m_triangles[curT].m_b = indices[j+1];
		meshShape->m_triangles[curT].m_c = indices[j+2];
		curT++;
	}

	// build MOPP code, will be owned by the MoppBVTreeShape
	hkpMoppCompilerInput mci;
	// Usually Mopps are not built at run time but preprocessed instead. We disable the performance warning
	bool wasEnabled = hkError::getInstance().isEnabled(0x6e8d163b); 
	hkError::getInstance().setEnabled(0x6e8d163b, false); // hkpMoppUtility.cpp:18
	hkpMoppCode* code = hkpMoppUtility::buildCode( meshShape , mci);
	hkError::getInstance().setEnabled(0x6e8d163b, wasEnabled);

	// build Mopp BV Tree shape
	hkpMoppBvTreeShape* moppShape = new hkpMoppBvTreeShape( meshShape, code );
	code->removeReference();
	meshShape->removeReference();

	// return our new shape
	return moppShape;
}


//
// createListOfTrianglesShape helper method
//
static hkpListShape* createListOfTrianglesShape( const hkVector4* vertices, const unsigned int numVertices,
											    const unsigned int numTriangles,
												const short* indices, const unsigned int numIndices, const unsigned int indicesStride )
{
	// create new triangle shapes
	hkArray<hkpShape*> triangles;
	for ( unsigned int i = 0; i < numIndices; i += ( indicesStride / sizeof( short ) ) )
	{
		triangles.pushBack( new hkpTriangleShape( vertices[indices[i]],
												 vertices[indices[i + 1]],
												 vertices[indices[i + 2]] ) );
	}

	// build list shape and add triangle shapes to it (copies triangle shapes)
	hkpListShape* listShape = new hkpListShape( triangles.begin(), triangles.getSize() );
	
	// clean up
	for ( unsigned int j = 0; j < numTriangles; j++ )
	{
		triangles[j]->removeReference();
	}
	triangles.clear();

	// return our new shape
	return listShape;
}


//
// Havok2 raycast test
//
int raycast_test()
{

	//
	// Create an axis aligned unit cube centred around the origin
	//
	const unsigned int numVertices = 8;
	hkVector4 halfExtents; halfExtents.set( 0.5f, 0.5f, 0.5f );

	hkVector4 vertices[numVertices]; 
	{
		vertices[0].set(-0.5, 0.5, 0.5);
		vertices[1].set( 0.5, 0.5, 0.5);
		vertices[2].set( 0.5,-0.5, 0.5);
		vertices[3].set(-0.5,-0.5, 0.5);
		vertices[4].set(-0.5, 0.5,-0.5);
		vertices[5].set( 0.5, 0.5,-0.5);
		vertices[6].set( 0.5,-0.5,-0.5);
		vertices[7].set(-0.5,-0.5,-0.5);
	}
	
	const unsigned int numVerticesPerTriangle = 3;
	const unsigned int numTriangles = 12;
	const unsigned int numIndices = numTriangles * numVerticesPerTriangle;
	const unsigned int indicesStride = numVerticesPerTriangle * sizeof( short );
	const short indices[numIndices] =
	{
		3,2,1,
		3,1,0,
		6,7,4,
		6,4,5,
		4,7,3,
		4,3,0,
		2,6,5,
		2,5,1,
		7,6,2,
		7,2,3,
		1,5,4,
		1,4,0
	};


	//
	// create shapes and test
	//
	const hkBool CONVEX = true;
	const hkBool CONCAVE = false;

	// MOPP BV tree shape
	{
		const hkpMoppBvTreeShape* moppBvTreeShape = createMoppBvTreeShape( vertices, numVertices, indices, numTriangles, indicesStride );
		raycast_tests( moppBvTreeShape, "MoppBvTreeShape", CONCAVE );
		moppBvTreeShape->removeReference();
	}

	
	// sphere
	{
		const hkReal radius = 0.5f;
		hkpSphereShape sphereShape( radius );
		raycast_tests( &sphereShape, "SphereShape", CONVEX );
	}

	// create list shape of triangle shapes, run test, delete it again
	{
		const hkpListShape* listOfTrianglesShape = createListOfTrianglesShape( vertices, numVertices, numTriangles, indices, numIndices, indicesStride );
		raycast_tests( listOfTrianglesShape, "ListOfTrianglesShape", CONCAVE);
		listOfTrianglesShape->removeReference();
	}

	// convex vertices shape
	{

		hkStridedVertices stridedVerts;
		hkArray<hkVector4> planeEquations;
		hkGeometry geom;
		{
			stridedVerts.m_numVertices = numVertices;
			stridedVerts.m_striding = sizeof(hkVector4);
			stridedVerts.m_vertices = &(vertices[0](0));
		}

		// Usually plane equations should be precomputed off line. We disable the performance warning
		bool wasEnabled = hkError::getInstance().isEnabled(0x34df5494);
		hkError::getInstance().setEnabled(0x34df5494, false); //hkpGeometryUtility.cpp:26
		hkpGeometryUtility::createConvexGeometry( stridedVerts, geom, planeEquations );
		hkError::getInstance().setEnabled(0x34df5494, wasEnabled); //hkpGeometryUtility.cpp:26

		{
			stridedVerts.m_numVertices = numVertices;
			stridedVerts.m_striding = sizeof(hkVector4);
			stridedVerts.m_vertices = &(vertices[0](0));
		}
		
		hkpConvexVerticesShape convexVerticesShape(stridedVerts, planeEquations);


		raycast_tests( &convexVerticesShape, "ConvexVerticesShape", CONVEX);
	}

	// implicit box shape
	{
		hkpBoxShape boxShape( halfExtents, 0 );
		raycast_tests( &boxShape, "BoxShape", CONVEX );
	}
	return 0;
}


//
// test registration
//
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(raycast_test, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
