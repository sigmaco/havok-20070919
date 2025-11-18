/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>

#include <Common/Serialize/Packfile/Xml/hkXmlPackfileWriter.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileReader.h>
#include <Physics/Collide/Shape/Convex/PackedConvexVertices/hkpPackedConvexVerticesShape.h>
#include <Common/Serialize/UnitTest/serializeUtilities.h>

extern const hkClass hkpPackedConvexVerticesShapeClass;

static hkpPackedConvexVerticesShape* makeShape()
{   
	hkStridedVertices verts;
	verts.m_numVertices = 8;
	verts.m_striding = 12;
	// a cube
	static const hkReal vertices[] = {  2.0f, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 4.0f, 2.0f, 0.0f, 2.0f, 2.0f, 0.0f, 
									    2.0f, 0.0f, 2.0f, 4.0f, 0.0f, 2.0f, 4.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f  };
	
	verts.m_vertices = &vertices[0];   

	hkArray<hkVector4> planeEquations(3);
	planeEquations[0].set(1.0f, .0f, .0f, 2.0f);
	planeEquations[1].set(.0f, 1.0f, .0f, 2.0f);
	planeEquations[2].set(.0f, .0f, 1.0f, 2.0f);

	return new hkpPackedConvexVerticesShape(verts, planeEquations, 1.0f);
}

// returns HK_FAILURE if the shapes are different
static hkResult compareShapes(const hkpPackedConvexVerticesShape& shapeA, const hkpPackedConvexVerticesShape& shapeB)
{
	// check if the two shapes have the same number of vertices 
	hkBool res = ( ( shapeA.m_aabbMin.equals4( shapeB.m_aabbMin, 1e-7f )!=0 )&&
				   ( shapeA.m_aabbMin.getInt24W() == shapeB.m_aabbMin.getInt24W() )
				 );

	// check plane equations
	res = res && ( shapeA.m_planeEquations.getSize() == shapeB.m_planeEquations.getSize() );
	for(int i=0; (i<shapeA.m_planeEquations.getSize()) && res ; ++i)
	{
		res = res && ( shapeA.m_planeEquations[i](0) == shapeB.m_planeEquations[i](0) );
		res = res && ( shapeA.m_planeEquations[i](1) == shapeB.m_planeEquations[i](1) );
		res = res && ( shapeA.m_planeEquations[i](2) == shapeB.m_planeEquations[i](2) );
	}

	// check AABB extents
	res = res && (shapeA.m_aabbExtents.equals4(shapeB.m_aabbExtents, 1e-7f)!=0);

	// check vertices
	for(int i=0; (i<hkpPackedConvexVerticesShape::BUILTIN_FOUR_VECTORS) && res; ++i)
	{
		for(int j=0; (j<4) && res; ++j)
		{
			res = res && shapeA.m_vertices[i].m_x[j] == shapeB.m_vertices[i].m_x[j];
			res = res && shapeA.m_vertices[i].m_y[j] == shapeB.m_vertices[i].m_y[j];
			res = res && shapeA.m_vertices[i].m_z[j] == shapeB.m_vertices[i].m_z[j];
		}
	}

	// check radius and user data (inherited data)
	res = res && (shapeA.getRadius() == shapeB.getRadius());
	res = res && (shapeA.m_userData == shapeB.m_userData);

	return (res)? HK_SUCCESS : HK_FAILURE;
}


int PackedShapeSerializeTest()
{
	hkpPackedConvexVerticesShape* shape = makeShape();

	serializeTest<hkXmlPackfileReader, hkXmlPackfileWriter, hkpPackedConvexVerticesShape>(*shape, hkpPackedConvexVerticesShapeClass, &compareShapes);

	shape->removeReference();

	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(PackedShapeSerializeTest, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );


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
