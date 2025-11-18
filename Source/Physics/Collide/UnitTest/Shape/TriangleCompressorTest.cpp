/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Physics/Collide/Util/hkpTriangleCompressor.h>
#include <Physics/Collide/Shape/Compound/Collection/Mesh/hkpMeshShape.h>

#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>

#define NUM_VERTICES 4
#define NUM_TRIANGLES 2

//
// createMeshShape
//
static hkpMeshShape* createMeshShape( hkVector4* vertices, hkUint16 numVertices, hkUint16* indices, hkUint16 numIndices )
{
	// create vertices
	vertices[0].set( 1.0f, 0.0f, 1.0f );
	vertices[1].set(-1.0f, 0.0f, 1.0f );
	vertices[2].set( 1.0f, 0.0f,-1.0f );
	vertices[3].set(-1.0f, 0.0f,-1.0f );

	// create the first non-degenerate triangle (0,1,2)
	indices[0] = 0;	
	indices[1] = 1;	
	indices[2] = 2;	
	indices[3] = 3;	

	// create shapes
	hkpMeshShape* meshShape = new hkpMeshShape();
	{
		hkVector4 tmp; tmp.set(20.0f, 20.0f, 20.0f);
		meshShape->setScaling( tmp );
	}
	{
		hkpMeshShape::Subpart part;

		part.m_vertexBase = &(vertices[0](0));
		part.m_vertexStriding = sizeof(hkVector4);
		part.m_numVertices = NUM_VERTICES;

		part.m_indexBase = indices;
		part.m_indexStriding = sizeof( hkUint16 );
		part.m_numTriangles = NUM_TRIANGLES;
		part.m_stridingType = hkpMeshShape::INDICES_INT16;

		meshShape->addSubpart( part );
	}

	return meshShape;
}

/*
hkUint8 data[66]= {
	-63,-96,0,0,0,0,0,0,
	-63,-96,0,0,4,2,0,-63,
	58,32,0,-96,0,0,0,0,
	58,32,0,-96,0,0,0,0,
	-1,-1,0,0,-1,-1,0,0,
	0,0,-1,-1,-1,-1,0,0,
	0,0,0,0,0,0,0,0,
	0,1,2,1,2,3,0,0,
	0,0,};
*/

int TriangleCompressorTest_test()
{
	hkVector4 verts[NUM_VERTICES];
	hkUint16 indices[ NUM_TRIANGLES * 3];

	hkpMeshShape* mesh = createMeshShape(verts, NUM_VERTICES, indices, NUM_TRIANGLES * 3);

	const int numTriangles = mesh->getNumChildShapes();
	hkLocalBuffer<hkpTriangleShape> triangles( numTriangles );
	for (int i=0; i < numTriangles ; i++)
	{
		hkpShapeCollection::ShapeBuffer buffer;
		triangles[i] = *(hkpTriangleShape*)mesh->getChildShape( i, buffer );
	}

	int size = hkpTriangleCompressor::getCompressedSize( triangles.begin(), numTriangles, HK_NULL);
	char * data = hkAllocate<char>(size, HK_MEMORY_CLASS_DEMO );
	hkpTriangleCompressor::compress( triangles.begin(), numTriangles, HK_NULL, data);

	for (int i=0; i < numTriangles ; i++)
	{
		hkpShapeCollection::ShapeBuffer buffer;
		hkpTriangleShape* triangle = (hkpTriangleShape*)mesh->getChildShape( i, buffer );
		hkpTriangleShape decompressedTriangle;
		hkpTriangleCompressor::getTriangleShape( decompressedTriangle, i, data );

		HK_TEST( triangle->getVertex( 0 ).equals3( decompressedTriangle.getVertex(0) ) );
		HK_TEST( triangle->getVertex( 1 ).equals3( decompressedTriangle.getVertex(1) ) );
		HK_TEST( triangle->getVertex( 2 ).equals3( decompressedTriangle.getVertex(2) ) );
	}

	hkDeallocate(data);
	delete mesh;
	return 0;
}


//
// test registration
//
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(TriangleCompressorTest_test, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );

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
