/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/hkBase.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

#include <Physics/Dynamics/Entity/hkpRigidBodyCinfo.h>

#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>


void HK_CALL getWeirdCompoundTransformShapeMassProperties(hkBool useDuplicates, hkpMassProperties& result)
{
	int i;

	// Build a coumpound body.
	// If useDuplicates, fake different mass "primitives" by duplicating 
	// them. eg. addPrim(mass=5) => add 5 prims(mass=1) !

		// These parameters specify the wibbly size. The main (body) sphere has the radius defined
		// below. The arms have size 'boxSize'. 
	hkReal radius = 1.0f;
	hkVector4 boxSize( 1.0f, 2.0f, 3.0f);


	// We've got 3 shapes (sphere, box, convexvertices)
	int num0 = 5;
	int num1 = 2;
	int num2 = 4;

		// Work out total mass given that each is of uniform unit density, hence has mass = density * volume
		// ie. mass = volume.
		// volume (sphere) = 4/3 PI = 4.18879020478
		// volume (box) = 6
		// volume (thingy) = 7.65268

	hkReal totalMass = hkReal(num0 * 4.18879020478f + num1 * 6 + num2 * 7.65268f);

	
	/////////////////////////////////////////
	///////////// SHAPES ////////////////////
	/////////////////////////////////////////
	hkpSphereShape* sphere = new hkpSphereShape(radius);

	hkVector4 halfExtents(boxSize(0) * 0.5f, boxSize(1) * 0.5f, boxSize(2) * 0.5f);
	hkpBoxShape* cube1 = new hkpBoxShape(halfExtents, 0 );	// Note: We use HALF-extents for boxes

	hkArray<hkVector4> vertices;
	//
	// Create the vertices array
	//
	int numSides = 5;
	hkReal radius2 = 1.1f;
	for(i = 0 ; i < numSides; i++)
	{
		hkTransform t;
		t.setIdentity();
		hkVector4 trans = hkVector4(radius2, 0, 0);

		hkReal angle = HK_REAL_PI * 2 * i / (hkReal) numSides;
		hkVector4 axis(0, 0, 1);
		hkQuaternion q(axis, angle);
		trans.setRotatedDir(q, trans);

		hkVector4 v = trans;
		v(2) = -1.0f;
		vertices.pushBack(v);
		v(2) = 1.0f;
		v(0) *= 1.3f;
		v(1) *= 1.3f;
		vertices.pushBack(v);
		
	}

	hkStridedVertices stridedVerts;
	hkArray<hkVector4> planeEquations;
	hkGeometry geom;
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

	hkpConvexVerticesShape* shape = new hkpConvexVerticesShape(stridedVerts, planeEquations);


	/////////////////////////////////////////
	///////////// BODY  ////////////////////
	/////////////////////////////////////////
	hkpRigidBodyCinfo compoundInfo;


	hkArray<hkpShape*> shapeArray;


	
	
	for(i = 0; i < (useDuplicates?num0:1) ; i++)
	{

		hkTransform t;
		hkVector4 v(-5,1,2);
		v.normalize3();
		hkQuaternion r(v, -0.746f);
		hkVector4 trans = hkVector4(1.231f, -0.325f, 0.93252f);
		t.setRotation(r);
		t.setTranslation( trans );
		
		hkpTransformShape* sphereTrans = new hkpTransformShape( sphere, t );

		shapeArray.pushBack(sphereTrans);	
	}
	

	
	for(i = 0; i < (useDuplicates?num1:1); i++)
	{
		hkTransform t;
		hkVector4 v(3,2,1.1324f);
		v.normalize3();
		hkQuaternion r(v, 0.446f);
		hkVector4 trans = hkVector4(.325f, .4363f,-.86427654f);
		t.setRotation(r);
		t.setTranslation( trans );
		
		hkpTransformShape* cube1Trans = new hkpTransformShape( cube1, t );

		shapeArray.pushBack(cube1Trans);	
	}
	
	
	

	for(i = 0; i < (useDuplicates?num2:1); i++)
	{
		hkTransform t;
		hkVector4 v(.5f, 0.4f, .9f);
		v.normalize3();
		hkQuaternion r(v, 1.2f);
		hkVector4 trans = hkVector4(-.435f, -0.5f, -0.2f);
		t.setRotation(r);
		t.setTranslation( trans );

		hkpTransformShape* convexTrans = new hkpTransformShape( shape, t );

		shapeArray.pushBack(convexTrans);	
	}
	
	




	


	// Now we can create the compound body as a hkpListShape
	
	hkpListShape* listShape = new hkpListShape(&shapeArray[0], shapeArray.getSize());
	compoundInfo.m_shape = listShape;

	sphere->removeReference();
	cube1->removeReference();
	shape->removeReference();

	for (i = 0; i < shapeArray.getSize(); ++i)
	{
		shapeArray[i]->removeReference();
	}



	//
	// Create the rigid body 
	//

	compoundInfo.m_mass = totalMass;
	hkMatrix3 m;
		// Fake an inertia tensor using a cube of side 'radius'

	if(useDuplicates)
	{
		hkpInertiaTensorComputer::setShapeVolumeMassProperties(compoundInfo.m_shape, compoundInfo.m_mass, compoundInfo);
	}
	else
	{
		hkArray<hkpMassElement> elements;

		// Construct compound inertia tensor from 3 "primitives"
		hkpMassElement massElement;
		massElement.m_transform.setIdentity();

			// Actually change order so we DEFINITELY do different calculations than are done for
			// the call above.
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(listShape->getChildShapeInl(0), num0*4.18879020478f, massElement.m_properties);
		elements.pushBack(massElement);

		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(listShape->getChildShapeInl(1), num1*6.0f, massElement.m_properties);
		elements.pushBack(massElement);

		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(listShape->getChildShapeInl(2), num2*7.65268f, massElement.m_properties);
		elements.pushBack(massElement);

		hkpMassProperties massProperties;
		hkpInertiaTensorComputer::combineMassProperties(elements, massProperties);

		compoundInfo.m_centerOfMass = massProperties.m_centerOfMass;
		compoundInfo.m_inertiaTensor = massProperties.m_inertiaTensor;
		compoundInfo.m_mass = massProperties.m_mass;
		
	}

	result.m_centerOfMass = compoundInfo.m_centerOfMass;
	result.m_mass = compoundInfo.m_mass;
	result.m_inertiaTensor =  compoundInfo.m_inertiaTensor;


	listShape->removeReference();
}


	// Create a "box" shape with 8 vertices.
hkpConvexVerticesShape* HK_CALL getBoxConvexVerticesShape(hkVector4 &halfExtents)
{
	hkArray<hkVector4> vertices;

	vertices.setSize(8);

	vertices[0] = hkVector4(halfExtents(0), halfExtents(1) ,halfExtents(2));
	vertices[1] = hkVector4(halfExtents(0), halfExtents(1) ,-halfExtents(2));
	vertices[2] = hkVector4(halfExtents(0), -halfExtents(1) ,halfExtents(2));
	vertices[3] = hkVector4(halfExtents(0), -halfExtents(1) ,-halfExtents(2));
	vertices[4] = hkVector4(-halfExtents(0), halfExtents(1) ,halfExtents(2));
	vertices[5] = hkVector4(-halfExtents(0), halfExtents(1) ,-halfExtents(2));
	vertices[6] = hkVector4(-halfExtents(0), -halfExtents(1) ,halfExtents(2));
	vertices[7] = hkVector4(-halfExtents(0), -halfExtents(1) ,-halfExtents(2));


	hkStridedVertices stridedVerts;
	hkArray<hkVector4> planeEquations;
	hkGeometry geom;
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

	hkpConvexVerticesShape* shape = new hkpConvexVerticesShape(stridedVerts, planeEquations);

	return shape;
}

	// Create a "random" set of vertices.
void HK_CALL getRandomConvexVertices(hkArray<hkVector4> &vertices, int numVerts, int seed = 123123)
{
	vertices.setSize(numVerts);

	for(int i = 0; i < numVerts; i++)
	{
		seed = 1664525L*seed+1013904223L;
		hkReal x = (seed & 0x7fff)*(1.0f/(0x7fff));
		seed = 1664525L*seed+1013904223L;
		hkReal y = (seed & 0x7fff)*(1.0f/(0x7fff));
		seed = 1664525L*seed+1013904223L;
		hkReal z = (seed & 0x7fff)*(1.0f/(0x7fff));
		vertices[i] = hkVector4(x, y ,z);		
	}
}

	// Create a "random" hkpConvexVerticesShape
hkpConvexVerticesShape* HK_CALL getRandomConvexVerticesShape(int numVerts, int seed = 123123)
{
	hkArray<hkVector4> vertices;
	vertices.setSize(numVerts);

	for(int i = 0; i < numVerts; i++)
	{
		seed = 1664525L*seed+1013904223L;
		hkReal x = (seed & 0x7fff)*(1.0f/(0x7fff));
		seed = 1664525L*seed+1013904223L;
		hkReal y = (seed & 0x7fff)*(1.0f/(0x7fff));
		seed = 1664525L*seed+1013904223L;
		hkReal z = (seed & 0x7fff)*(1.0f/(0x7fff));
		vertices[i] = hkVector4(x, y ,z);		
	}

	hkStridedVertices stridedVerts;
	hkArray<hkVector4> planeEquations;
	hkGeometry geom;
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

	hkpConvexVerticesShape* shape = new hkpConvexVerticesShape(stridedVerts, planeEquations);

	return shape;

}




void HK_CALL setMassPropertiesToRandomNonsense(hkpMassProperties& massProperties)
{
	massProperties.m_centerOfMass.set(-123.123f, 456.456f, 99999.0f);
	massProperties.m_mass = -1.0f;
	massProperties.m_volume = -1.0f;
	massProperties.m_inertiaTensor.setDiagonal(-1.0f, -2.0f, -3.0f);
}


hkMatrix3 HK_CALL getBoxInertiaTensor(hkVector4& halfSize, hkReal mass)
{
	hkReal alpha = halfSize(0) * 2.0f;
	hkReal beta = halfSize(1) * 2.0f;
	hkReal gamma = halfSize(2) * 2.0f;

	hkReal ixx = 1.0f / 6.0f;
	hkReal iyy = 1.0f / 6.0f;
	hkReal izz = 1.0f / 6.0f;


	hkReal ixxP = ( (beta*beta) *  (ixx - iyy + izz) * 0.5f )
					+ (   (gamma*gamma) * (ixx + iyy - izz) * 0.5f );

	hkReal iyyP = ( (alpha*alpha) * (-ixx + iyy + izz) * 0.5f)
					+ ( (gamma*gamma) * (ixx + iyy - izz) * 0.5f );

	hkReal izzP = ( (alpha*alpha) * (-ixx + iyy + izz) * 0.5f )
					+ (  (beta*beta) * (ixx - iyy + izz) * 0.5f );

	hkMatrix3 m;
	m.setIdentity();

	m(0,0) = ixxP * mass;
	m(1,1) = iyyP * mass;
	m(2,2) = izzP * mass;
	
	return m;
}

hkQuaternion HK_CALL getQuaternion(hkReal angle, hkReal x, hkReal y, hkReal z)
{
	hkQuaternion q;
	hkVector4 axis(x,y,z);
	axis.normalize3();
	q.setAxisAngle(axis, angle);
	return q;
}

void HK_CALL transformNasty(hkTransform& t, const hkTransform& nasty)
{
	hkTransform foo;
	foo.setMul(nasty, t);
	t = foo;
}



hkGeometry* HK_CALL getCapsuleGeometry(const hkVector4& start, const hkVector4& end, hkReal radius,  int thetaSamples, int phiSamples, int heightSamples)
{
	hkArray<hkVector4> verts;

		// Create "transform" from start, end.
	hkTransform capsuleToLocal;
	

	hkVector4 axis;
	axis.setSub4(end, start);
	hkReal height = axis.length3();
	if(height > 0.0f)
	{
		axis.normalize3();

		// find a quat which rotates (1,0,0) to axis
		hkVector4 canonicalZ(0,0,1);
		if(hkMath::fabs(axis.dot3(canonicalZ)) < 1 - 1e-5f)
		{
			hkVector4 rotAxis;
			rotAxis.setCross(canonicalZ, axis);
			rotAxis.normalize3();

			hkReal rotAngle = hkMath::acos(axis.dot3(canonicalZ));

			hkQuaternion q(rotAxis, rotAngle);
			capsuleToLocal.setRotation(q);
		}
		else
		{
			capsuleToLocal.setIdentity();	
		}

	}
	else
	{
		capsuleToLocal.setIdentity();
	}

			// Now recenter
	{
		hkVector4 toCentre;
		toCentre.setAdd4(start, end);
		toCentre.mul4(0.5f);
		capsuleToLocal.setTranslation(toCentre);
	}
	
	


	// We'll sweep around the axis of the deflector, from top to bottom, using the original
	// sample directions and data to define the vertices. We'll tessellate in the obvious way.
	// N.B. Top and bottom vertices are added to cap the object. These are calculated as the 
	// average of the surrounding vertices, hence will be slightly flattened.

	int i,j;

	hkVector4 vert;

	hkVector4 bottomInGeom = hkVector4(0,0,-height/2);
	hkVector4 topInGeom = hkVector4(0,0,height/2);
	hkVector4 axisInGeom;
	axisInGeom.setSub4(topInGeom, bottomInGeom);
	hkVector4 axisNInGeom = hkVector4(0,0,1);
	hkVector4 normalInGeom = hkVector4(1,0,0);
	hkVector4 binormalInGeom = hkVector4(0,-1,0);

	verts.reserveExactly(2 * phiSamples * thetaSamples + 2 + (heightSamples-2) * thetaSamples);

		///////////////////// GET TOP VERTICES ///////////////////
	hkArray<hkVector4> topverts;
	for (i = phiSamples-1 ; i >= 0; i--)
	{
		hkQuaternion qTop(binormalInGeom, hkReal(i) / phiSamples * HK_REAL_PI * .5f);
		hkVector4 topElevation;
		topElevation.setRotatedDir(qTop, normalInGeom);

		hkQuaternion qBottom(binormalInGeom, -hkReal(i) / phiSamples * HK_REAL_PI * .5f);
		hkVector4 bottomElevation;
		bottomElevation.setRotatedDir(qBottom, normalInGeom);

		for (j = 0; j < thetaSamples; j++)
		{
			hkQuaternion rotationTop(axisNInGeom, hkReal(j) / thetaSamples * HK_REAL_PI * 2);			
			hkVector4 topDirection;
			topDirection.setRotatedDir(rotationTop, topElevation);

			hkReal dist = radius;
			vert.setAddMul4(topInGeom, topDirection, dist);

			vert.setTransformedPos(capsuleToLocal, vert);

				// Temporarily store since we'll need these to calculate "top" vertx.
			topverts.pushBack(vert);

		}
	}

	vert = hkVector4(0, 0 ,height*0.5f + radius);
	vert.setTransformedPos(capsuleToLocal, vert);

		// Push back top vertex, and then the rest
	verts.pushBack(vert);
	for(i = 0; i < (phiSamples)*thetaSamples; i++)
	{
		verts.pushBack(topverts[i]);
	}

	
		///////////////////// GET MIDDLE VERTICES ///////////////////
	for (j = heightSamples-2; j >= 1; j--)
	{
	
		for (i = 0; i < thetaSamples; i++)
		{	
		//
		// Calculate direction vector for this angle
		//

			hkQuaternion q(axisNInGeom, hkReal(i) / thetaSamples * HK_REAL_PI * 2);
			hkVector4 direction;
			direction.setRotatedDir(q, normalInGeom);
			
			hkVector4 startx;
			startx.setAddMul4(bottomInGeom, axisInGeom, hkReal(j) / hkReal(heightSamples - 1));

			hkReal dist = radius;

			vert.setAddMul4(startx, direction, dist);

			vert.setTransformedPos(capsuleToLocal, vert);

			verts.pushBack(vert);

		}
	}

 


		///////////////////// GET BOTTOM VERTICES ///////////////////
	for (i = 0; i < phiSamples; i++)
	{
		hkQuaternion qTop(binormalInGeom, hkReal(i) / phiSamples * HK_REAL_PI * .5f);
		hkVector4 topElevation;
		topElevation.setRotatedDir(qTop, normalInGeom);

		hkQuaternion qBottom(binormalInGeom, -hkReal(i) / phiSamples * HK_REAL_PI * .5f);
		hkVector4 bottomElevation;
		bottomElevation.setRotatedDir(qBottom, normalInGeom);

		for (j = 0; j < thetaSamples; j++)
		{
			hkQuaternion rotationBottom(axisNInGeom, hkReal(j) / thetaSamples * HK_REAL_PI * 2);			
			hkVector4 bottomDirection;
			bottomDirection.setRotatedDir(rotationBottom, bottomElevation);

			hkReal dist = radius;

			vert.setAddMul4(bottomInGeom, bottomDirection, dist);
			vert.setTransformedPos(capsuleToLocal, vert);
			verts.pushBack(vert);

		}
	}

	
	vert.set(0, 0 , -(height*0.5f + radius));
	vert.setTransformedPos(capsuleToLocal, vert);

		// Push back bottom vertex
	verts.pushBack(vert);


	
	///////////////////// CONSTRUCT FACE DATA ///////////////////

	hkGeometry* geom = new hkGeometry;
	geom->m_vertices = verts;
	// Right, num samples AROUND axis is thetaSamples.

	// First off, we have thetaSamples worth of faces connected to the top
	int currentBaseIndex = 1;

	hkGeometry::Triangle tr;
	for (i = 0; i < thetaSamples; i++)
	{
		tr.m_a = 0;
		tr.m_b = currentBaseIndex + i;
		tr.m_c = currentBaseIndex + (i+1)%(thetaSamples);
		geom->m_triangles.pushBack(tr);
	}

	// Next we have phi-1 + height-1 + phi-1 lots of thetaSamples*2 worth of faces connected to the previous row
	for(j = 0; j < 2*(phiSamples-1) + heightSamples-1; j++)
	{
		for (i = 0; i < thetaSamples; i++)
		{
			tr.m_a = currentBaseIndex + i;
			tr.m_b = currentBaseIndex + thetaSamples + i;
			tr.m_c = currentBaseIndex + thetaSamples + (i+1)%(thetaSamples);

			geom->m_triangles.pushBack(tr);

			tr.m_b = currentBaseIndex + i;
			tr.m_a = currentBaseIndex + (i+1)%(thetaSamples);
			tr.m_c = currentBaseIndex + thetaSamples + (i+1)%(thetaSamples);
		
			geom->m_triangles.pushBack(tr);
		
		}
		currentBaseIndex += thetaSamples;

	}

	// Finally, we have thetaSamples worth of faces connected to the bottom
	for (i = 0; i < thetaSamples; i++)
	{
		tr.m_b = currentBaseIndex + i;
		tr.m_a = currentBaseIndex + (i+1)%(thetaSamples);
		tr.m_c = currentBaseIndex + thetaSamples;
		geom->m_triangles.pushBack(tr);
	}

	return geom;
}


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
