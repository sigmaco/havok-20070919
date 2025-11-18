/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Internal/hkpInternal.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/hkBase.h>
#include <Common/Base/hkBase.h>

#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/hkpConvexShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Internal/Collide/Gjk/Penetration/hkpConvexPenetrationUtil.h>
#include <Physics/Internal/Collide/Gjk/hkpGjkCache.h>
#include <Physics/Internal/Collide/Gjk/hkpGsk.h>
#include <Physics/Internal/Collide/Gjk/hkpGjk.h>
#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

static hkReal scale = 1.0f;

hkpConvexVerticesShape* createCylinderConvexVerticesShape(hkReal radius, hkReal height, int numSegments)
{
	hkArray<hkVector4> vertices; vertices.reserve(1024*10);
	{
		hkReal segmentArcWidth = (1.0f / (hkReal)numSegments) * 2 * HK_REAL_PI; // in radians
		for(int i = 0; i < numSegments; i++)
		{
			hkVector4 v1;
			v1(1) = height * 0.5f;
			v1(0) = hkMath::cos(i * segmentArcWidth) * radius;
			v1(2) = hkMath::sin(i * segmentArcWidth) * radius;
			v1(3) = 0.0f;
			vertices.pushBack(v1);

			hkVector4 v2;
			v2(1) = height * -0.5f;
			v2(0) = hkMath::cos(i * segmentArcWidth) * radius;
			v2(2) = hkMath::sin(i * segmentArcWidth) * radius;
			v2(3) = 0.0f;
			vertices.pushBack(v2);
		}
	}
	
	
	
	hkArray<hkVector4> planeEquations;
	hkGeometry geom;

	hkStridedVertices stridedVerts;
	{
		stridedVerts.m_numVertices = vertices.getSize();
		stridedVerts.m_striding = sizeof(hkVector4);
		stridedVerts.m_vertices = &(vertices[0](0));
	}

	// Usually plane equations should be precomputed off line. We disable the performance warning
	bool wasEnabled = hkError::getInstance().isEnabled(0x34df5494);
	hkError::getInstance().setEnabled(0x34df5494, false); //hkpGeometryUtility.cpp:26
	hkpGeometryUtility::createConvexGeometry( stridedVerts, geom, planeEquations );
	hkError::getInstance().setEnabled(0x34df5494, wasEnabled); //hkpGeometryUtility.cpp:26

	

	{
		stridedVerts.m_numVertices = geom.m_vertices.getSize();
		stridedVerts.m_striding = sizeof(hkVector4);
		stridedVerts.m_vertices = &(geom.m_vertices[0](0));
	}

	return new hkpConvexVerticesShape(stridedVerts, planeEquations);
}

void pdtest(const char* name, hkpConvexShape* shapeA, hkpConvexShape* shapeB, hkTransform& btoa)
{
	hkpCdVertex pointsAinA[4]; // an empty cache
	hkpCdVertex pointsBinB[4]; // an empty cache
	hkpGskOut output;
	hkVector4 simplex[4];
	int simplexSize = 0;

	// call penetration depth directly
	hkpConvexPenetrationUtil penDepth; penDepth.init(shapeA, shapeB, btoa, 0.0001f, pointsAinA, pointsBinB, simplex, simplexSize );
	/*hkpGskStatus status =*/ penDepth.calculatePenetrationDepth(output);
//	HK_TEST2(status == HK_GSK_OK, name << "(" << scale << ",pd) " << output.m_distance);


	// call penetration depth through GJK (penetration depth may not be called)
	//hkpGjk::GJK(shapeA, shapeB, btoa, cache, output);
//	HK_TEST2(gjkStatus == HK_GSK_OK, name << "(" << scale << ",gjk) " << output.m_distance);
}

#define RANDNORM hkMath::randRange(-1.0f, 1.0f)

void pdcrashtest()
{
	scale = hkMath::randRange(0.01f, 0.2f);

	hkReal radiusA = 10.0f * scale;
	hkpConvexShape* shapeA =
		//new hkpBoxShape(hkVector4(7.5f, 5.0f, 7.5f), 0 );
		createCylinderConvexVerticesShape(radiusA, 10.f * scale, 32);

	hkReal radiusB = 2.5f * scale;
	hkpConvexShape* shapeB =
		//new hkpBoxShape(hkVector4(2.5f,0.5f,0.5f), 0 );
		createCylinderConvexVerticesShape(radiusB, 1.0f * scale, 3);

	hkTransform btoa;
	{
		// pick a random direction and orientation
		hkVector4 translation; translation.set(RANDNORM, RANDNORM, RANDNORM); 
		translation.normalize3();

		hkVector4 axis; axis.set(RANDNORM, RANDNORM, RANDNORM); 
		axis.normalize3();
		hkReal angle = hkMath::randRange(0.0f, 2.0f * HK_REAL_PI);
		hkRotation rotation; rotation.setAxisAngle(axis, angle);

		// translate along the direction such that the object are almost definately not interpenetrating
		translation.mul4(radiusA + radiusB);

		btoa.setRotation(rotation);
		btoa.setTranslation(translation);
	}


	// call GJK and translate so that the objects are just touching...(old GJK is less accurate than PD)
	hkVector4 normal;
	normal.setZero4();
	{
		hkpGjkCache cache; // an empty cache
		hkpGskOut output;

		hkpGskStatus status = hkpGjk::GJK(shapeA, shapeB, btoa, cache, output);
			// penetration depth may be called internally

		if(status == HK_GSK_OK)
		{
			normal = output.m_normalInA;
			hkVector4 start = output.m_pointAinA;
			hkVector4 end = output.m_pointAinA;

			hkVector4 distanceVectorInA = output.m_normalInA;
			distanceVectorInA.mul4(output.m_distance * -1.0f);
			//distanceVectorInA.sub4(output.m_normalInA);

			end.add4(distanceVectorInA);

			//hkVector4 end = output.m_pointBinB;
			//end.setTransformedPos(btoa, end);

			hkVector4 translation = btoa.getTranslation();
			translation.sub4(distanceVectorInA);
			btoa.setTranslation(translation);
		}
	}

	//
	// we have two random touching objects (though GJK can be wrong!) and a contact normal...
	//


	//
	// call the penetration algorithm with the objects touching
	//
	pdtest("Touching", shapeA, shapeB, btoa);

	//
	// make the objects penetrate by 1.0f unit
	//
	{
		hkVector4 translation = btoa.getTranslation();
		translation.add4(normal);
		btoa.setTranslation(translation);
	}

	// call the penetration with the objects penetrating
	pdtest("Penetrating", shapeA, shapeB, btoa);

	//
	// make the objects be separated by 1.0f unit
	//
	{
		hkVector4 translation = btoa.getTranslation();
		translation.sub4(normal);
		translation.sub4(normal);
		btoa.setTranslation(translation);
	}

	// call the penetration with the objects separated
	pdtest("Separating", shapeA, shapeB, btoa);

	delete shapeA;
	delete shapeB;

}


int pdcrashtest_main()
{
	for(int i = 0; i < 10/*000 00000*/; i++)
	{
		pdcrashtest();
	}
	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(pdcrashtest_main, "Fast", "Physics/Test/UnitTest/Internal/", __FILE__     );


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
