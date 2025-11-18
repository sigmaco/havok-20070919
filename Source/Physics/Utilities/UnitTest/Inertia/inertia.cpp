/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// This file QAs the "new" Inertia Tensor code for Havok2. The "new" code covers functionality to determine
// Inertia Tensors for:
// Spheres
// Boxes
// "Solid" Geometries (assumed to be closed)
// Meshes ("Shells") i.e a union of traingles with a user supplied thickness (does not have to be closed/connected)
// Point clouds (treated as point masses)
//
// Compound bodies consisting of pairs of (Inertia Tensor, Transform) structures.

// Dependencies: hbase, hkcollide, hkmath, hkdynamics, hkgeometry2, hkgeometryutil2
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/hkBase.h>

//XXX Large include:


#include <Common/Base/Math/Linear/hkMathStream.h>

#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

#include <Common/Base/Types/Geometry/hkGeometry.h>

// For shape tests
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Collide/Shape/Misc/Bv/hkpBvShape.h>
#include <Physics/Collide/Shape/Misc/MultiSphere/hkpMultiSphereShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Misc/MultiRay/hkpMultiRayShape.h>
#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

#include <Physics/Dynamics/Entity/hkpRigidBodyCinfo.h>

	// Used to create the Mopp 'code' object
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppUtility.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

// In inertiahelper.cpp
void HK_CALL getWeirdCompoundTransformShapeMassProperties(hkBool useDuplicates, hkpMassProperties& result);
hkpConvexVerticesShape* HK_CALL getBoxConvexVerticesShape(hkVector4 &halfExtents);
void HK_CALL getRandomConvexVertices(hkArray<hkVector4> &vertices,  int numVerts, int seed = 123123);
hkpConvexVerticesShape* HK_CALL getRandomConvexVerticesShape(int numVerts, int seed = 123123);
hkGeometry* HK_CALL getCapsuleGeometry(const hkVector4& start, const hkVector4& end, hkReal radius,  int thetaSamples, int phiSamples, int heightSamples);


/////////////////////////////////////////////////////////////////////////////////////
// Replace this with your own code if you like

/////////////////////////////////////////////////////////////////////////////////////
void raiseBroken()
{
	//HK_TEST(0 && "Comparison of values in Inertia Tensor test failed\n");
	//hkcout << "TEST FAILED\n";
}




/////////////////////////////////////////////////////////////////////////////////////
// These three methods allow testing of reals, vectors matrices against each other.
/////////////////////////////////////////////////////////////////////////////////////
void confirmEqual(hkReal a, hkReal b, hkReal tolerance)
{
	hkReal dif = hkMath::fabs(a - b);
	
	if(dif > tolerance)
	{
		raiseBroken();
	}
	
	HK_TEST(dif <= tolerance);
}

void confirmEqual(hkVector4& v, hkVector4& u, hkReal tolerance)
{
	confirmEqual(v(0), u(0), tolerance);
	confirmEqual(v(1), u(1), tolerance);
	confirmEqual(v(2), u(2), tolerance);
}

void confirmEqual(hkMatrix3& m, hkMatrix3& n, hkReal tolerance)
{
	confirmEqual(m.getColumn(0), n.getColumn(0), tolerance);
	confirmEqual(m.getColumn(1), n.getColumn(1), tolerance);
	confirmEqual(m.getColumn(2), n.getColumn(2), tolerance);
}



/////////////////////////////////////////////////////////////////////////////////////

void setMassPropertiesToRandomNonsense(hkpMassProperties& massProperties);



hkMatrix3 getBoxInertiaTensor(hkVector4& halfSize, hkReal mass);
hkQuaternion getQuaternion(hkReal angle, hkReal x, hkReal y, hkReal z);
void transformNasty(hkTransform& t, const hkTransform& nasty);


// 
void checkSphereVol()
{
	hkVector4 zeroVector4;
	zeroVector4.setZero4();

	// Sphere
	hkReal radius = 1.3f;
	hkReal mass = 7.0f;
	hkpMassProperties massProperties;
	setMassPropertiesToRandomNonsense(massProperties);
	hkpInertiaTensorComputer::computeSphereVolumeMassProperties(radius, mass, massProperties);

	// The mass is 'mass!'
	confirmEqual(massProperties.m_mass, mass, 1e-3f);

	// Now the volume is 4/3/PI/r^3
	confirmEqual(massProperties.m_volume, 4/3.0f * HK_REAL_PI * radius *radius * radius, 1e-3f);

	// The com is (0,0,0)
	confirmEqual(massProperties.m_centerOfMass, zeroVector4, 1e-3f);

	// The IT
	hkMatrix3 it;
	it.setDiagonal(mass * radius * radius * 0.4f,mass * radius * radius * 0.4f,mass * radius * radius * 0.4f);
	confirmEqual(massProperties.m_inertiaTensor, it, 1e-3f);

}

//
void checkSphereSurface()
{
	hkVector4 zeroVector4;
	zeroVector4.setZero4();

	// Sphere
	hkReal radius = 1.3f;
	hkReal mass = 7.0f;
		// Thickness is measured "inwards", ie. 0 thickness => completely hollow, and
		// thickness = radius => completely solid, so set to just under radius, and compare
		// to the "volume" calculataion.
	hkReal thickness = 1.29999f;	
	hkpMassProperties massProperties;
	setMassPropertiesToRandomNonsense(massProperties);
	hkpInertiaTensorComputer::computeSphereSurfaceMassProperties(radius, mass, thickness, massProperties);

		// Compare against sphere
	hkpMassProperties otherProperties;
	setMassPropertiesToRandomNonsense(otherProperties);
	hkpInertiaTensorComputer::computeSphereVolumeMassProperties(radius, mass, otherProperties);

	confirmEqual(massProperties.m_mass, otherProperties.m_mass, 1e-3f);
	confirmEqual(massProperties.m_volume, otherProperties.m_volume, 1e-3f);
	confirmEqual(massProperties.m_centerOfMass, zeroVector4, 1e-3f);
	confirmEqual(massProperties.m_inertiaTensor, otherProperties.m_inertiaTensor, 1e-3f);

}

// 
void checkBoxVol()
{
	hkVector4 zeroVector4;
	zeroVector4.setZero4();

	// Box
	hkVector4 halfSize(2.3f, 1.7f, .9f);
	hkReal mass = 7.0f;
	hkpMassProperties massProperties;
	setMassPropertiesToRandomNonsense(massProperties);
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfSize, mass, massProperties);

	// The mass is 'mass!'
	confirmEqual(massProperties.m_mass, mass, 1e-3f);

	// Now the volume 
	confirmEqual(massProperties.m_volume, 8.0f * halfSize(0) * halfSize(1) * halfSize(2) , 1e-3f);

	// The com is (0,0,0)
	confirmEqual(massProperties.m_centerOfMass, zeroVector4, 1e-3f);

	// The IT can be got from a scaled unit cube IT
	hkMatrix3 it = getBoxInertiaTensor(halfSize, mass);
	confirmEqual(massProperties.m_inertiaTensor, it, 1e-3f);
	
}

//
void checkBoxSurface()
{


	hkVector4 zeroVector4;
	zeroVector4.setZero4();

	// Box, say 2x2x2 with 1x1x1 hole in it, so density = 1.0f say
	hkVector4 halfSize(1.0f, 1.0f, 1.0f);
	hkReal mass = 7.0f;
		// Thickness is measured "inwards",
	hkReal thickness = 0.5f;	

	hkpMassProperties massProperties;
	setMassPropertiesToRandomNonsense(massProperties);
	hkpInertiaTensorComputer::computeBoxSurfaceMassProperties(halfSize, mass, thickness, massProperties);

	hkVector4 halfSizeCube(0.5f, 0.5f, 0.5f);

	// Compare to solid - solid
	hkpMassProperties bigProperties;
	setMassPropertiesToRandomNonsense(bigProperties);
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfSize, 8.0f, bigProperties);

	hkpMassProperties smallProperties;
	setMassPropertiesToRandomNonsense(smallProperties);
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfSizeCube, 1.0f, smallProperties);


		// The mass is 'mass!'
	confirmEqual(massProperties.m_mass, mass, 1e-3f);

	// Now the volume 
	confirmEqual(massProperties.m_volume, 8.0f - 1.0f , 1e-3f);

	// The com is (0,0,0)
	confirmEqual(massProperties.m_centerOfMass, zeroVector4, 1e-3f);

	// The IT can be got from a scaled unit cube IT
	hkMatrix3 it = bigProperties.m_inertiaTensor;
	it.sub(smallProperties.m_inertiaTensor);
	confirmEqual(massProperties.m_inertiaTensor, it, 1e-3f);

}

// Check triangle-based mass properties code
void checkTriangle()
{
	hkArray<hkVector4> vertices;

	// Let's build a "right triangle" like this:
	/*

	Triangle is:

	(0,1)
	|\
	|  \
	|    \
	|______\ (1,0)

	// See checkHull() for derivation of the correct integrals. We'll check both a "zero" thickness, and a "non-zero" thickness,
	// as different algorithms are used for each.

	*/

	// Thickness = 0.0f;
	{
		vertices.setSize(3);

		vertices[0] = hkVector4(0, 0 ,0);
		vertices[1] = hkVector4(0, 1, 0);
		vertices[2] = hkVector4(1, 0 ,0);


		hkReal mass = 1.0f;
		hkpMassProperties massProperties;
		setMassPropertiesToRandomNonsense(massProperties);
		hkpInertiaTensorComputer::computeTriangleSurfaceMassProperties(vertices[0], vertices[1], vertices[2], mass, 0.0f, massProperties);

			// The mass is 'mass!'
		confirmEqual(massProperties.m_mass, mass, 1e-3f);

		// Now the volume 
		confirmEqual(massProperties.m_volume, 0.0f , 1e-3f);

		// The com is (0.3333,0.33333, 0.0)
		hkVector4 com(1.0f/3.0f, 1.0f/3.0f, 0.0f);
		confirmEqual(massProperties.m_centerOfMass, com, 1e-3f);

		// The IT is calculated using the integrals derived in checkHull()
		hkReal xx = mass/6.0f;
		hkReal yy = mass/6.0f;
		hkReal zz = 0.0f;

		hkReal xy = -mass /12;
		hkReal xz = 0.0f;
		hkReal yz = 0.0f;


		hkMatrix3 testIT;
		testIT.setDiagonal(yy + zz, xx + zz, xx + yy);
		testIT(0,1) = testIT(1,0) = xy;
		testIT(0,2) = testIT(2,0) = xz;	
		testIT(1,2) = testIT(2,1) = yz;

				// Now can test this constructed one against the (shifted) computed one
		hkpInertiaTensorComputer::shiftInertiaToCom( com, mass, testIT);
		confirmEqual(massProperties.m_inertiaTensor, testIT, 1e-3f);

	}

	// Thickness = 1.3f;
	{
		
		hkReal thickness = 1.3f;
			// Thickness applies/expands triangle in "both" directions by thickness/2, so the "base" triangle is in the z = thickness/2 plane.
		vertices[0] = hkVector4(0, 0 , thickness * 0.5f);
		vertices[1] = hkVector4(0, 1,  thickness * 0.5f);
		vertices[2] = hkVector4(1, 0 , thickness * 0.5f);

		
		hkReal mass = 1.0f;
		hkpMassProperties massProperties;
		setMassPropertiesToRandomNonsense(massProperties);
		hkpInertiaTensorComputer::computeTriangleSurfaceMassProperties(vertices[0], vertices[1], vertices[2], mass, thickness, massProperties);

			// The mass is 'mass!'
		confirmEqual(massProperties.m_mass, mass, 1e-3f);

		// Now the volume 
		confirmEqual(massProperties.m_volume, 0.5f * thickness , 1e-3f);

		// The com is (0.3333,0.33333,  0.5 * thickness)
		hkVector4 com(1.0f/3.0f, 1.0f/3.0f,  0.5f * thickness);
		confirmEqual(massProperties.m_centerOfMass, com, 1e-3f);

		// The IT is calculated using the above integrals

		hkReal xx = mass/6.0f;
		hkReal yy = mass/6.0f;
		hkReal zz = mass * thickness * thickness * (1.0f/3.0f);

		hkReal xy = -mass /12;
		hkReal xz = -mass * thickness/6;


		hkMatrix3 testIT;
		testIT.setDiagonal(yy + zz, xx + zz, xx + yy);
		testIT(0,1) = testIT(1,0) = xy;
		testIT(0,2) = testIT(2,0) = xz;	
		testIT(1,2) = testIT(2,1) = xz; // By symmetry, yz = xz

						// Now can test this constructed one against the (shifted) computed one
		hkpInertiaTensorComputer::shiftInertiaToCom( com, mass, testIT);
		confirmEqual(massProperties.m_inertiaTensor, testIT, 1e-3f);

	}
	
}


// Check hull-based mass properties code
void checkHull()
{
	hkArray<hkVector4> vertices;

	// Let's build a "right triangle prism" like this:
	/*

	Triangle is:

	(0,1)
	|\
	|  \
	|    \
	|______\ (1,0)

	And we'll add three verts in the z=0 plane, and three in the z=1 plane	
  
	*/
	vertices.setSize(6);

	hkReal thickness = 1.0f;
	vertices[0] = hkVector4(0, 0 ,0);
	vertices[1] = hkVector4(0, 1, 0);
	vertices[2] = hkVector4(1, 0 ,0);
	vertices[3] = hkVector4(0, 0 , thickness);
	vertices[4] = hkVector4(0, 1,  thickness);
	vertices[5] = hkVector4(1, 0 , thickness);

	// Clearly, centre of mass is at (0.3333, 0.33333, 0.5) (centroid of triangle, shifted 0.5 down the z-axis

	// However, not so clearly, the inertia tensor can be calculated using the facts that:
	//
	// 1. Inertia tensor (around centre of mass) "shifted" away from centre of mass gives the actual
	//		intergrals of x^2 + y^2, -xy etc. in the original space, and these are a lot
	//		easier to compute in closed form:
	// 2. Let I(foo) be the triple inegral over the volume of foo, then I(x^2) = I(y^2) (by symmetry) = 
	/*
		// The third part of the integral is collapses to just a multiplier T, where T = thickness of prism

		/ 1  / 1-x	
		|    |
	  T	|    |      y^2 dx dy     * rho
		|    |
		/ 0  / 0

	  	/ 1  	
		|                   1-x
	= T	|         | y^3 / 3  |   dx     * rho
		|                    0
		/ 0  
	
	  // Change basis, let q = 1-x
	
	  	/ 0  	
		|                 
	=-T	|       z^3 /3  dz   * rho
		|                   
		/ 1 
		
	= T/12  * rho

	// And rho = mass/ (vol) = mass / (0.5*T) = 2M/T
	// so the result is I(x^2) = I(z^2) = mass/6

	*/

	// 3. I(z^2) = A * (integral z^2) where A is the intregral over x,y = Area of Triangle = 0.5
	//		so I(z^2) = T^3 / 3 * 0.5 * rho = mass * T^2 / 3
	//		ie. I(z^2) = mass * T^2 / 3

	// 4. I(-xy) =
	/*
		
		/ 1  / 1-x	
		|    |
	  T	|    |      -xy dx dy     * rho
		|    |
		/ 0  / 0

	  	/ 1  	
		|                     1-x
	= T	|         | -xy^2 / 2  |   dx     * rho
		|                      0
		/ 0  


	  	/ 1  	
		|                 
	= T	|        -x(1-x)^2 /2   dx     * rho
		|         
		/ 0  

	  		/ 1  	
			|                 
	=  -T/2	|        x - 2x^2 + x^3   dx     * rho
			|         
			/ 0  
	
 	  		 	
			                                    1
	=  -T/2	|   x^2 / 2  - x^3 * 2/3 + x^4 / 4  |     * rho
			                                    0


	=  -T/24 * rho
			
	=  -M/12


	*/

	// 5. I(-xz) = I(-yz) (by symmetry) =

	/*
			/ 1  / 1-x	
			|    |
	-T^2 /2	|    |      x dx dy     * rho
			|    |
			/ 0  / 0

				/ 1  
				|        1-x
	= -T^2 /2	|    | xy | dx      * rho
				|         0
				/ 0  


				/ 1  
				|        
	= -T^2 /2	|     x - x^2  dx      * rho
				|         
				/ 0  

				 
				                    1
	= -T^2 /2	| x^2 / 2 - x^3 / 3 |      * rho
				                    0

	= -T^2 /2	 1/6      * rho

	= -T^2 /12	 * rho

	= -TM/6

	*/



	hkReal mass = 1.0f;
	hkpMassProperties massProperties;
	setMassPropertiesToRandomNonsense(massProperties);

	// Disable the 'don't compute hull at runtime' warning.
	hkBool oldValue = hkError::getInstance().isEnabled(0x34df5494);
	hkError::getInstance().setEnabled(0x34df5494, false);
	hkpInertiaTensorComputer::computeVertexHullVolumeMassProperties(&(vertices[0](0)), sizeof(hkVector4), vertices.getSize(), mass, massProperties);
	hkError::getInstance().setEnabled(0x34df5494, oldValue);

		// The mass is 'mass!'
	confirmEqual(massProperties.m_mass, mass, 1e-3f);

	// Now the volume 
	confirmEqual(massProperties.m_volume, 0.5f * thickness , 1e-3f);

	// The com is (0.3333,0.33333, 0.5f * thickness)
	hkVector4 com(1.0f/3.0f, 1.0f/3.0f, 0.5f * thickness);
	confirmEqual(massProperties.m_centerOfMass, com, 1e-3f);

	// The IT is calculated using the above integrals

	hkReal xx = mass/6.0f;
	hkReal yy = mass/6.0f;
	hkReal zz = mass * thickness * thickness * (1.0f/3.0f);

	hkReal xy = -mass /12;
	hkReal xz = -mass * thickness/6;


	hkMatrix3 testIT;
	testIT.setDiagonal(yy + zz, xx + zz, xx + yy);
	testIT(0,1) = testIT(1,0) = xy;
	testIT(0,2) = testIT(2,0) = xz;	
	testIT(1,2) = testIT(2,1) = xz; // By symmetry, yz = xz

		// Now can test this constructed one against the (shifted) computed on
	hkpInertiaTensorComputer::shiftInertiaFromCom( massProperties.m_centerOfMass, mass, massProperties.m_inertiaTensor);
	confirmEqual(massProperties.m_inertiaTensor, testIT, 1e-3f);

}



// test computeVertexCloudMassProperties()
void checkPointCloud()
{
	// We'll use a set of uniformly distributed points inside:
	// 1. a sphere (we know analytical result) and also
	// 2. a pyramid (we can use convex hull version to compare against)

	if(1)
	{
		// 
		hkReal radius = 1.7f;
		hkReal mass = 1.3f;

		hkArray<hkVector4> vertices;

		// distributed inside tri
		int side = 40;
		{
			hkReal d = 1.0f/side;
			hkReal dOver2 = d * 0.5f;
			for(int i=0;i<side;i++)
			{
				for(int j=0;j<side;j++)
				{
					for(int k=0;k<side;k++)
					{
					
							// x,y,z set to be in range -0.5 -> 0.5 (actually at the centre of
							// each cube, so actually -0.5f + dOver2 -> 0.5f - dOver2 
						hkReal x = i/(hkReal) (side) - 0.5f + dOver2;
						hkReal y = j/(hkReal) (side) - 0.5f + dOver2;
						hkReal z = k/(hkReal) (side) - 0.5f + dOver2;
					
							// If inside the sphere of radius 0.5f
						if(x*x + y*y + z*z < .25f)
						{
							x *= 2*radius;
							y *= 2*radius;
							z *= 2*radius;
							vertices.pushBack(hkVector4(x, y, z));
						}
					}
				}
			}
		}


		hkpMassProperties massProperties;
		setMassPropertiesToRandomNonsense(massProperties);
		hkpInertiaTensorComputer::computeVertexCloudMassProperties(&(vertices[0](0)), sizeof(hkVector4), vertices.getSize(), mass, massProperties);


		// The mass is 'mass!'
		confirmEqual(massProperties.m_mass, mass, 1e-3f);

		// Now the volume is 4/3/PI/r^3, but the computeVertexCloudMassProperties() method can't compute this
		// for obvious reasons.

		// The com is (0,0,0)
		hkVector4 zeroVector4;
		zeroVector4.setZero4();
		confirmEqual(massProperties.m_centerOfMass, zeroVector4, 1e-2f);

		// The IT
		hkMatrix3 it;
		it.setDiagonal(mass * radius * radius * 0.4f,mass * radius * radius * 0.4f,mass * radius * radius * 0.4f);
		confirmEqual(massProperties.m_inertiaTensor, it, 1e-2f);

	}


	if(1)
	{

		hkReal mass = 3.6f;
	
			// Create pyramid with vertices on the unit square (0,0,0) (1,0,0) (0,0,1) (1,0,1) in the x-z plane
			// and also (0,1,0).
		hkArray<hkVector4> vertices;

		hkReal xSize = 1.0f;
		hkReal ySize = 1.0f;
		hkReal zSize = 1.0f;

		// distributed inside pyramid
		int side = 100;
		{
			hkReal d = 1.0f/side;
			hkReal dOver2 = d * 0.5f;
			for(int i=0;i<side;i++)
			{
				for(int j=0;j<side;j++)
				{
					for(int k=0;k<side;k++)
					{
					
							// x,y,z set to be in range -0.5 -> 0.5 (actually at the centre of
							// each cube, so actually -0.5f + dOver2 -> 0.5f - dOver2 
						hkReal x = i/(hkReal) (side) - 0.5f + dOver2;
						hkReal y = j/(hkReal) (side) - 0.5f + dOver2;
						hkReal z = k/(hkReal) (side) - 0.5f + dOver2;

							// shift to positive octant
						x += 0.5f;
						y += 0.5f;
						z += 0.5f;

						x *= xSize;
						y *= ySize;
						z *= zSize;

							// Add jitter
						x += hkMath::randRange(-0.5f/side, 0.5f/side);
						y += hkMath::randRange(-0.5f/side, 0.5f/side);
						z += hkMath::randRange(-0.5f/side, 0.5f/side);

					
							// If inside the pyramid (bounded by x+y=1 and z+y=1 planes).
						if( ( x+y <= 1.0f) && (z+y <= 1.0f))
						{
							vertices.pushBack(hkVector4(x, y, z));
						}
					}
				}
			}
		}


		hkpMassProperties massProperties;
		setMassPropertiesToRandomNonsense(massProperties);
		hkpInertiaTensorComputer::computeVertexCloudMassProperties(&(vertices[0](0)), sizeof(hkVector4), vertices.getSize(), mass, massProperties);

		// Actual object can be computed using hull
		{
			vertices.setSize(5);

			vertices[0] = hkVector4(0, 0, 0);
			vertices[1] = hkVector4(1, 0, 0);
			vertices[2] = hkVector4(1, 0, 1);
			vertices[3] = hkVector4(0, 0, 1);
			vertices[4] = hkVector4(0, 1, 0);

			hkpMassProperties massPropertiesActual;
			setMassPropertiesToRandomNonsense(massPropertiesActual);
			hkpInertiaTensorComputer::computeVertexHullVolumeMassProperties(&(vertices[0](0)), sizeof(hkVector4), vertices.getSize(), mass, massPropertiesActual);

		
			confirmEqual(massProperties.m_mass, mass, 1e-3f);
			confirmEqual(massProperties.m_centerOfMass, massPropertiesActual.m_centerOfMass ,1e-2f);
			confirmEqual(massProperties.m_inertiaTensor, massPropertiesActual.m_inertiaTensor ,1e-2f);


		}

	}
	
}

// test computeSkinMassProperties
void checkSkin()
{
	// Hmm, rather hard to test this one. Let's construct a set of triangle which covers a 
	// pyramid volume:
	// Pyramid has vertices (0,0,0) (1,0,0) (0,0,1) (1,0,1) in the x-z plane
	// and also (0,1,0).


	// Actual object can be computed using hull
	hkReal mass = 1.6f;

	// subdivide pyramid
	// At height y, verts are (0,y,0) (0, y, 1-y) (1-y, y, 0), (1-y, y, 1-y)

	hkGeometry* geom = new hkGeometry;
	int subdiv = 150;
	int numVerts = 0;

	for(int i = 0; i < subdiv; i++)
	{
		hkReal y = i / (hkReal) (subdiv) + 0.5f / (hkReal) (subdiv);
		geom->m_vertices.pushBack( hkVector4(0,y,0) );
		geom->m_vertices.pushBack( hkVector4(0, y, 1-y) );
		geom->m_vertices.pushBack( hkVector4(1-y, y,0) );
		geom->m_vertices.pushBack( hkVector4(1-y, y, 1-y) );
		
		geom->m_triangles.expandBy(1)->set(numVerts, numVerts + 1, numVerts + 3);
		geom->m_triangles.expandBy(1)->set(numVerts, numVerts + 3, numVerts + 2);

		numVerts +=4;

	}


	hkpMassProperties massProperties;
	setMassPropertiesToRandomNonsense(massProperties);
	hkpInertiaTensorComputer::computeGeometrySurfaceMassProperties(geom, 1.0f/(hkReal)subdiv, true, mass, massProperties);

	delete geom;

	
	
	{
		hkArray<hkVector4> vertices;
		vertices.setSize(5);

		vertices[0] = hkVector4(0, 0, 0);
		vertices[1] = hkVector4(1, 0, 0);
		vertices[2] = hkVector4(1, 0, 1);
		vertices[3] = hkVector4(0, 0, 1);
		vertices[4] = hkVector4(0, 1, 0);

		hkpMassProperties massPropertiesActual;
		setMassPropertiesToRandomNonsense(massPropertiesActual);
		hkpInertiaTensorComputer::computeVertexHullVolumeMassProperties(&(vertices[0](0)), sizeof(hkVector4), vertices.getSize(), mass, massPropertiesActual);

	
		confirmEqual(massProperties.m_mass, mass, 1e-3f);
		confirmEqual(massProperties.m_centerOfMass, massPropertiesActual.m_centerOfMass ,1e-2f);
		confirmEqual(massProperties.m_inertiaTensor, massPropertiesActual.m_inertiaTensor ,1e-2f);


	}
	


}

//
void checkCompound()
{
	// The nice thing about our Geometry-based IT code is that it doesn't require the geometry to be
	// connected. Thus we can test the result for a compound body against the result for a "single" geometry
	// composed of the union of the bits. Tadah.

	// First let's create a suitably "nasty" geometry. We'll then use three copies of this to create the 
	// compound one. We'll use a "random"ish tetrahedron


	hkGeometry* geom = new hkGeometry;

	geom->m_vertices.pushBack( hkVector4(0,2,0) );
	geom->m_vertices.pushBack( hkVector4(-4.3f, .7f, 2) );
	geom->m_vertices.pushBack( hkVector4(3,1,-2.2f) );
	geom->m_vertices.pushBack( hkVector4(-0.7f, -2.3f, 0.9f) );
		
	geom->m_triangles.expandBy(1)->set(1, 0, 2);
	geom->m_triangles.expandBy(1)->set(3, 2, 0);
	geom->m_triangles.expandBy(1)->set(1, 3, 0);
	geom->m_triangles.expandBy(1)->set(3, 1, 2);

	hkReal mass = 1.3f;
	{
		hkpMassProperties massPropertiesSingle;
		setMassPropertiesToRandomNonsense(massPropertiesSingle);
		massPropertiesSingle.m_mass = mass * 0.5f;	// Split evenly between two bodies (then since equal volume => equal density)
		hkpInertiaTensorComputer::computeGeometryVolumeMassProperties(geom, massPropertiesSingle.m_mass, massPropertiesSingle);

	//	hkcout << massPropertiesSingle.m_centerOfMass << "\n";
	//	hkcout << massPropertiesSingle.m_inertiaTensor << "\n";

		// Create compound body (array of hkMassElements) AND compound Geometry (merge two geometries)
		
		// Create two (pos,rot) pairs
		hkVector4 p0(1.2f, 0.7f, -0.8f);
		hkQuaternion q0 = getQuaternion(-1.2f, 2,6,19);
		hkVector4 p1(.2f, -1.5f, 0.32421f);
		hkQuaternion q1 = getQuaternion(.4325f, 3,-1,-5);

		// Create two Transforms from the above
		hkTransform t0(q0, p0);
		hkTransform t1(q1, p1);


		// HERE WE CALCULATE THE COMPOUND INERTIA TENSOR
		hkArray<hkpMassElement> massElements;
		massElements.pushBack(hkpMassElement(massPropertiesSingle, t0));
		massElements.pushBack(hkpMassElement(massPropertiesSingle, t1));

		hkpMassProperties massPropertiesCompound;
		setMassPropertiesToRandomNonsense(massPropertiesCompound);
		hkpInertiaTensorComputer::combineMassProperties(massElements, massPropertiesCompound);

	
		// HERE WE CALCULATE THE MERGED INERTIA TENSOR

		// Need to construct geom as merge of the other two:
		
		hkGeometry* mergedGeom = new hkGeometry;

		int i;
		for( i = 0 ; i < geom->m_vertices.getSize(); i++)
		{
			hkVector4 vert;
			vert.setTransformedPos(t0, geom->m_vertices[i]);
			mergedGeom->m_vertices.pushBack(vert);
		}

		for(i = 0 ; i < geom->m_triangles.getSize(); i++)
		{
			hkGeometry::Triangle t = geom->m_triangles[i];
			mergedGeom->m_triangles.pushBack(t);
		}

		for( i = 0 ; i < geom->m_vertices.getSize(); i++)
		{
			hkVector4 vert;
			vert.setTransformedPos(t1, geom->m_vertices[i]);
			mergedGeom->m_vertices.pushBack(vert);
		}

		for(i = 0 ; i < geom->m_triangles.getSize(); i++)
		{
			const int offset = geom->m_triangles.getSize();
			hkGeometry::Triangle t = geom->m_triangles[i];
			t.set(t.m_a + offset, t.m_b + offset, t.m_c + offset);
			mergedGeom->m_triangles.pushBack(t);
		}

		hkpMassProperties massPropertiesMerged;
		setMassPropertiesToRandomNonsense(massPropertiesMerged);
		massPropertiesMerged.m_mass = mass;
		hkpInertiaTensorComputer::computeGeometryVolumeMassProperties(mergedGeom, massPropertiesMerged.m_mass, massPropertiesMerged);


		confirmEqual(massPropertiesCompound.m_mass, massPropertiesMerged.m_mass, 1e-3f);
		confirmEqual(massPropertiesCompound.m_centerOfMass, massPropertiesMerged.m_centerOfMass ,1e-3f);
		confirmEqual(massPropertiesCompound.m_inertiaTensor, massPropertiesMerged.m_inertiaTensor ,1e-3f);
		confirmEqual(massPropertiesCompound.m_volume, massPropertiesMerged.m_volume ,1e-3f);

		delete mergedGeom;


	}

	delete geom;
}

// This checks the higher-level "shape-based" class
void checkBoxShape()
{
	hkpMassProperties exactResult;
	hkVector4 halfExtents(2.3f, 0.7353f, 0.67976f);	
	hkReal mass = 1.3f;

	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfExtents, mass, exactResult);

	hkpRigidBodyCinfo compoundInfo;
	{
		hkpBoxShape b(halfExtents);	// Note: We use HALF-extents for boxes
		hkpInertiaTensorComputer::setShapeVolumeMassProperties(&b, mass, compoundInfo);
	}

	confirmEqual(compoundInfo.m_mass, exactResult.m_mass, 1e-3f);
	confirmEqual(compoundInfo.m_centerOfMass, exactResult.m_centerOfMass ,1e-3f);
	confirmEqual(compoundInfo.m_inertiaTensor, exactResult.m_inertiaTensor ,1e-3f);
}

// This checks the higher-level "shape-based" class
void checkSphereShape()
{
	hkpMassProperties exactResult;
	hkReal radius = 4.76f;
	hkReal mass = 1.3f;

	hkpInertiaTensorComputer::computeSphereVolumeMassProperties(radius, mass, exactResult);

	hkpRigidBodyCinfo compoundInfo;
	{
		hkpSphereShape s(radius);
		hkpInertiaTensorComputer::setShapeVolumeMassProperties(&s, mass, compoundInfo);
	}

	confirmEqual(compoundInfo.m_mass, exactResult.m_mass, 1e-3f);
	confirmEqual(compoundInfo.m_centerOfMass, exactResult.m_centerOfMass ,1e-3f);
	confirmEqual(compoundInfo.m_inertiaTensor, exactResult.m_inertiaTensor ,1e-3f);
}

// This checks the higher-level "shape-based" class
void checkCompoundShape()
{
	hkArray<hkpShape*> shapesForDeletion;

	hkReal mass = 150.0f;

	hkpMassProperties exactResult;
	hkpRigidBodyCinfo compoundInfo;

	// We'll build a 1*2*4 box out of smaller boxes, and check the resultant compound inertia tensor.
	// We'll also Transform the shapes (in Local space) in a nasty way to confirm that the code works
	// in general.
	// We'll also use a mixture of explicit BOXES and CONVEXVERTICESSHAPES (8 vertices used to make a box)

		// Construct "nasty" Transform;
	hkTransform nasty;
	hkVector4 p(.75f, -.3f, 1.9f);
	nasty.setTranslation(p);
	hkQuaternion q = getQuaternion(0.7f, .45f, 0.8f, -1.3f);
	nasty.setRotation(q);

	
	{
		hkVector4 halfExtents(1*0.5f, 2*0.5f, 4*0.5f);	

		hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfExtents, mass, exactResult);

		// transform result to "nasty" space.
		exactResult.m_inertiaTensor.changeBasis(nasty.getRotation());
		exactResult.m_centerOfMass.setTransformedPos(nasty, exactResult.m_centerOfMass);
	}

		// We'll build the box from a 1*2*2, a 1*1*2, a 1*1*1 and two 0.5*1*1s.
		// A bit like this:
	/*
		                       ____
		                     /    /|
		                   /    /  |
		                 /    /    |
		               /    /      |
		             /    /        |
		           / ---/          |
		         /    / |         /
	           /    /   |       /
		     /    /     |     /
		   /    /     / |   /
		 /____/     /   | /
		|    |    /|    /
		|    |  /  |  / 
		|____|/    |/
		|  | |    /
		|  | |  /
		|  | |/
		 ----
	*/
	{
		hkArray<hkpShape*> shapeArray;

		// 1*2*2
		{
			hkVector4 halfExtents(0.5,1,1);
			hkpBoxShape* b = new hkpBoxShape(halfExtents, 0 );	// Note: We use HALF-extents for boxes
			shapesForDeletion.pushBack(b);	

			hkTransform t;
			t.setIdentity();
			hkVector4 trans = hkVector4(0,0,-1);
			t.setTranslation( trans );
			transformNasty(t, nasty);
			
			hkpTransformShape* boxTrans = new hkpTransformShape( b, t );

			shapesForDeletion.pushBack(boxTrans);	
			shapeArray.pushBack(boxTrans);	
		}
		
		// 1*1*2
		{
			hkVector4 halfExtents(0.5,0.5,1);
		//	hkpBoxShape* b = new hkpBoxShape(halfExtents, 0 );	// Note: We use HALF-extents for boxes
			hkpConvexVerticesShape* b = getBoxConvexVerticesShape(halfExtents);
			shapesForDeletion.pushBack(b);

			hkTransform t;
			t.setIdentity();
			hkVector4 trans = hkVector4(0,0.5,1);
			t.setTranslation( trans );
			transformNasty(t, nasty);
			
			hkpTransformShape* boxTrans = new hkpTransformShape( b, t );

			shapesForDeletion.pushBack(boxTrans);	
			shapeArray.pushBack(boxTrans);	
		}

		// 1*1*1
		{
			hkVector4 halfExtents(0.5,0.5,0.5);
			hkpBoxShape* b = new hkpBoxShape(halfExtents, 0 );	// Note: We use HALF-extents for boxes
			shapesForDeletion.pushBack(b);	

			hkTransform t;
			t.setIdentity();
			hkVector4 trans = hkVector4(0,-0.5,0.5);
			t.setTranslation( trans );

			transformNasty(t, nasty);
			
			hkpTransformShape* boxTrans = new hkpTransformShape( b, t );

			shapesForDeletion.pushBack(boxTrans);	
			shapeArray.pushBack(boxTrans);	
		}

		// 0.5*1*1
		{
			hkVector4 halfExtents(0.25,0.5,0.5);
		//	hkpBoxShape* b = new hkpBoxShape(halfExtents, 0 );	// Note: We use HALF-extents for boxes
			hkpConvexVerticesShape* b = getBoxConvexVerticesShape(halfExtents);
			shapesForDeletion.pushBack(b);

			hkTransform t;
			t.setIdentity();
			hkVector4 trans = hkVector4(0.25,-0.5,1.5);
			t.setTranslation( trans );

			transformNasty(t, nasty);

			hkpTransformShape* boxTrans = new hkpTransformShape( b, t );
			shapesForDeletion.pushBack(boxTrans);	

			shapeArray.pushBack(boxTrans);	
		}

		// 0.5*1*1
		{
			hkVector4 halfExtents(0.25,0.5,0.5);
			hkpBoxShape* b = new hkpBoxShape(halfExtents, 0 );	// Note: We use HALF-extents for boxes
			shapesForDeletion.pushBack(b);	

			hkTransform t;
			t.setIdentity();
			hkVector4 trans = hkVector4(-0.25,-0.5,1.5);
			t.setTranslation( trans );

			transformNasty(t, nasty);
			
			hkpTransformShape* boxTrans = new hkpTransformShape( b, t );
			shapesForDeletion.pushBack(boxTrans);

			shapeArray.pushBack(boxTrans);	
		}
		

			
		hkpListShape* listShape = new hkpListShape(&shapeArray[0], shapeArray.getSize());
		shapesForDeletion.pushBack(listShape);	// // Remember this, and we'll remove reference later
		compoundInfo.m_shape = listShape;

		//
		// Create the rigid body 
		//

		compoundInfo.m_mass = mass;
		hkpInertiaTensorComputer::setShapeVolumeMassProperties(compoundInfo.m_shape, compoundInfo.m_mass, compoundInfo);

	}

	
	confirmEqual(compoundInfo.m_mass, exactResult.m_mass, 1e-3f);
	confirmEqual(compoundInfo.m_centerOfMass, exactResult.m_centerOfMass ,1e-3f);
	confirmEqual(compoundInfo.m_inertiaTensor, exactResult.m_inertiaTensor ,1e-3f);

	// delete shapes
	for(int i = 0; i< shapesForDeletion.getSize(); i++)
	{
		shapesForDeletion[i]->removeReference();
	}

}

	// Check the functionality of hkpInertiaTensorComputer::computeShapeVolumeMassProperties()
	// (which calls hkpInertiaTensorComputer::computeRecursiveShapeVolumeMassProperties(), which does the tricky bit)
	// for shapes which are not of base type ie.
	// HK_SHAPE_BV, HK_SHAPE_MULTI_SPHERE, HK_SHAPE_BV_TREE, HK_SHAPE_UTILITY_CONVEX_SWEEP
void checkCompoundShape2()
{
	// Check HK_SHAPE_BV
	{
		// Use some other shape with a BV. Check that it works.
		hkArray<hkVector4> vertices;
		getRandomConvexVertices(vertices, 10, 4137);


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

		hkpConvexVerticesShape* childShape = new hkpConvexVerticesShape(stridedVerts, planeEquations);


		hkVector4 halfExtents(2.3f, 0.7353f, 0.67976f);	
		hkpBoxShape* boxShape = new hkpBoxShape(halfExtents, 0 );	// Note: We use HALF-extents

		
		hkpBvShape bvShape( boxShape, childShape );
		childShape->removeReference();
		boxShape->removeReference();


		hkReal mass = 1.23f;

		hkpMassProperties result1, result2;
		setMassPropertiesToRandomNonsense(result1);
		setMassPropertiesToRandomNonsense(result2);

		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(&bvShape, mass, result1);
		hkpInertiaTensorComputer::computeVertexHullVolumeMassProperties(&(vertices[0](0)), sizeof(hkVector4), vertices.getSize(), mass, result2);


		confirmEqual(result1.m_mass, result2.m_mass, 1e-3f);
		confirmEqual(result1.m_volume, result2.m_volume, 1e-3f);
		confirmEqual(result1.m_centerOfMass, result2.m_centerOfMass ,1e-3f);
		confirmEqual(result1.m_inertiaTensor, result2.m_inertiaTensor ,1e-3f);	
	
	}

	// Check HK_SHAPE_UTILITY_CONVEX_SWEEP

//	{
//		// Use some other shape with a Convex Sweep Shape. Check that it works.
//		hkArray<hkVector4> vertices;
//		getRandomConvexVertices(vertices, 10, 4137);
//
//		hkStridedVertices stridedVerts;
//		hkArray<hkVector4> planeEquations;
//		hkGeometry geom;
//		{
//			stridedVerts.m_numVertices = vertices.getSize();
//			stridedVerts.m_striding = sizeof(hkVector4);
//			stridedVerts.m_vertices = &(vertices[0](0));
//		}
//
//		// Usually plane equations should be precomputed off line. We disable the performance warning
//		bool wasEnabled = hkError::getInstance().isEnabled(0x34df5494);
//		hkError::getInstance().setEnabled(0x34df5494, false); //hkpGeometryUtility.cpp:26
//		hkpGeometryUtility::createConvexGeometry( stridedVerts, geom, planeEquations );
//		hkError::getInstance().setEnabled(0x34df5494, wasEnabled); //hkpGeometryUtility.cpp:26
//
//		{
//			stridedVerts.m_numVertices = geom.m_vertices.getSize();
//			stridedVerts.m_striding = sizeof(hkVector4);
//			stridedVerts.m_vertices = &(geom.m_vertices[0](0));
//		}
//
//		hkpConvexVerticesShape* childShape = new hkpConvexVerticesShape(stridedVerts, planeEquations);
//
//		hkConvexSweepShapeCinfo sweepShapeInfo;
//		sweepShapeInfo.m_childShape = childShape;
//		hkConvexSweepShape sweepShape( sweepShapeInfo );
//		childShape->removeReference();
//		
//		hkReal mass = 1.23f;
//
//		hkpMassProperties result1, result2;
//		setMassPropertiesToRandomNonsense(result1);
//		setMassPropertiesToRandomNonsense(result2);
//
//		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(&sweepShape, mass, result1);
//		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(childShape, mass, result2);
//
//		confirmEqual(result1.m_mass, result2.m_mass, 1e-3f);
//		confirmEqual(result1.m_volume, result2.m_volume, 1e-3f);
//		confirmEqual(result1.m_centerOfMass, result2.m_centerOfMass ,1e-3f);
//		confirmEqual(result1.m_inertiaTensor, result2.m_inertiaTensor ,1e-3f);	
//
//	}
	
	// Check HK_SHAPE_MULTI_SPHERE
	{
		const int numSpheres = 5;
		hkArray<hkVector4> centres;
		getRandomConvexVertices(centres, numSpheres, 2143);
		int i;
		for(i = 0; i <  numSpheres; i++)
		{
			centres[i](3) = 1.7f;	// set radius;
		}
		hkpMultiSphereShape multiSphereShape(centres.begin(), numSpheres);


		hkReal mass = 1.23f;

		hkpMassProperties result1, result2;
		setMassPropertiesToRandomNonsense(result1);
		setMassPropertiesToRandomNonsense(result2);

		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(&multiSphereShape, mass, result1);

		hkArray<hkpMassElement> massElements;


		hkReal massPerSphere = mass/centres.getSize();
		for(i = 0; i <  numSpheres; i++)
		{
			centres[i](3) = 0.0f;
			hkTransform t;
			t.setIdentity();
			t.setTranslation(centres[i]);

			hkpMassProperties massPropertiesSingle;
			hkpInertiaTensorComputer::computeSphereVolumeMassProperties(1.7f, massPerSphere, massPropertiesSingle);
			massElements.pushBack(hkpMassElement(massPropertiesSingle, t));
		}
		hkpInertiaTensorComputer::combineMassProperties(massElements, result2);


		confirmEqual(result1.m_mass, result2.m_mass, 1e-3f);
		confirmEqual(result1.m_volume, result2.m_volume, 1e-3f);
		confirmEqual(result1.m_centerOfMass, result2.m_centerOfMass ,1e-3f);
		confirmEqual(result1.m_inertiaTensor, result2.m_inertiaTensor ,1e-3f);			
	}

	// HK_SHAPE_BV_TREE
	{
		hkArray<hkpShape*> shapeArray;

		
		hkpConvexVerticesShape* shape1 = getRandomConvexVerticesShape(16, 231);
		hkpConvexVerticesShape* shape2 = getRandomConvexVerticesShape(13, 86107);

		shapeArray.pushBack(shape1);
		shapeArray.pushBack(shape2);


		hkpListShape* listShape = new hkpListShape(shapeArray.begin(), shapeArray.getSize());
			// Remove reference since the listShape now "owns" the hkConvexVerticesShapes.
		shape1->removeReference();
		shape2->removeReference();
	

		hkpMoppCompilerInput moppInput;
		moppInput.setAbsoluteFitToleranceOfTriangles(0.1f);
		// Usually Mopps are not built at run time but preprocessed instead. We disable the performance warning
		bool wasEnabled1 = hkError::getInstance().isEnabled(0x6e8d163b); 
		hkError::getInstance().setEnabled(0x6e8d163b, false); // hkpMoppUtility.cpp:18
		bool wasEnabled2 = hkError::getInstance().isEnabled(0x7dd65995); 
		hkError::getInstance().setEnabled(0x7dd65995, false); // hkThreadMemory ""The system has requested a heap allocation on stack overflow"
		hkpMoppCode* code = hkpMoppUtility::buildCode(listShape, moppInput);
		hkError::getInstance().setEnabled(0x6e8d163b, wasEnabled1);
		hkError::getInstance().setEnabled(0x7dd65995, wasEnabled2);

		hkpMoppBvTreeShape* moppBVTreeShape = new hkpMoppBvTreeShape(listShape, code);
			// Remove references since the MoppBvTreeShape now "owns" the listShape and code
		code->removeReference();
		listShape->removeReference();
		
		// Compare the BVTree version to just a "normal" listshape version

		hkReal mass = 5.23f;
		
		hkpMassProperties result1, result2;
		setMassPropertiesToRandomNonsense(result1);
		setMassPropertiesToRandomNonsense(result2);

		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(listShape, mass, result1);
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(moppBVTreeShape, mass, result2);


		confirmEqual(result1.m_mass, result2.m_mass, 1e-3f);
		confirmEqual(result1.m_volume, result2.m_volume, 1e-3f);
		confirmEqual(result1.m_centerOfMass, result2.m_centerOfMass ,1e-3f);
		confirmEqual(result1.m_inertiaTensor, result2.m_inertiaTensor ,1e-3f);	

		delete moppBVTreeShape;

	}
}

void checkComputeShapeVolumeMassProperties()
{
	// To do this we construct a coumpound body consisting of several types of primitives (shapes)
	// in several different positions, but with duplicates in exacly the same positions. Thus we can
	// eg. set up either a single box of mass 2.6 at a given pos/rot OR
	// set up two boxes of mass 1.3 as the same pos/rot.
	// The two ways we then compute the inertia tensor are:
	// 1. Create 3 (one for spheres, one for boxes, one for a convexvertices shape) "heavy"
	//		shapes, call computeShapeVolumeMassProperties(), and store results in a massProperties for each,
	//		then use combineMassProperties() to combine them.
	//
	// 2. Create a compound shape ("list" shape) of several "light" primitives, with duplicates as descibed above
	//		and total mass = sum of primitives masses, and call setShapeVolumeMassProperties() which
	//		*recursively* combines all shape mass properties to get a final mass properties.
	//
	// We can then compare results.
	// N.B. Because setShapeVolumeMassProperties() assumes UNIFORM DENSITY, we have to take care to add
	// primitives which have mass set to maintain this denisty (Actually density assumed to be 1.0, so 
	// mass = volume for each primitive).

	hkpMassProperties result1, result2;

	getWeirdCompoundTransformShapeMassProperties(true, result1);
	getWeirdCompoundTransformShapeMassProperties(false, result2);

	confirmEqual(result1.m_mass, result2.m_mass, 1e-3f);
	confirmEqual(result1.m_centerOfMass, result2.m_centerOfMass ,1e-3f);
	confirmEqual(result1.m_inertiaTensor, result2.m_inertiaTensor ,1e-3f);

}

void checkSimplifyITOriented()
{
	hkMatrix3 it;

	hkVector4 r0(4,1,2);
	hkVector4 r1(1,3,0);
	hkVector4 r2(2,0,5);
	it.setRows(r0, r1, r2);

	hkpInertiaTensorComputer::simplifyInertiaTensorToOrientedParticle(it);

	hkMatrix3 orientedIt;
	orientedIt.setDiagonal(5, 5, 5);

	confirmEqual(it, orientedIt, 1e-6f);

}

void checkZeroMassBug()
{
	// See http://wiki.telekinesys/DevrelTracker/2204/1.
	// Should get assert if mass <=0, not just <0!

	hkArray<hkpMassElement> elements;
	hkpMassElement elt;
	elt.m_properties.m_centerOfMass.setZero4();
	elt.m_properties.m_inertiaTensor.setIdentity();
	elt.m_properties.m_mass = 0.0f;	// This is what should cause stuff to break. 
	elt.m_properties.m_volume = 1.0f;	
	elt.m_transform.setIdentity();

	elements.pushBack(elt);

	hkpMassProperties result; 
	hkpInertiaTensorComputer::combineMassProperties(elements, result);	// This will raise an assert

	hkVector4 e(1,2,3);
	hkpInertiaTensorComputer::computeBoxSurfaceMassProperties(e, 0.0f, 0.1f, result);	// So will this

}

void checkGivenLineSegment(const hkVector4& start, const hkVector4& end, const hkReal radius)
{	
	// Line segment
	hkReal mass = 7.0f;
	hkpMassProperties massProperties;
	setMassPropertiesToRandomNonsense(massProperties);
	hkpInertiaTensorComputer::computeCapsuleVolumeMassProperties(start, end, radius, mass, massProperties);

	
			// Compare against a geometry created from start, end, radius
	const int thetaSamples = 100;
	const int phiSamples = 100;
	const int heightSamples = 100;
	hkpMassProperties geometryApproximationProperties;
	setMassPropertiesToRandomNonsense(geometryApproximationProperties);
	hkGeometry* geom = getCapsuleGeometry(start, end, radius, thetaSamples, phiSamples, heightSamples);
	hkpInertiaTensorComputer::computeGeometryVolumeMassProperties(geom, mass, geometryApproximationProperties);
	delete geom;

		// Now there's some error here because of the approximation, but it should be small.
		// For the cylinder above, with 0.1 should be ample.
	confirmEqual(massProperties.m_mass, geometryApproximationProperties.m_mass, 1e-1f);
	confirmEqual(massProperties.m_volume, geometryApproximationProperties.m_volume, 1e-1f);
	confirmEqual(massProperties.m_centerOfMass, geometryApproximationProperties.m_centerOfMass, 1e-1f);
	confirmEqual(massProperties.m_inertiaTensor, geometryApproximationProperties.m_inertiaTensor, 1e-1f);


		// May as well check the "computeShapeVolumeMassProperties" version as well
	setMassPropertiesToRandomNonsense(massProperties);
	hkpCapsuleShape lineSegment(start, end, radius);
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(&lineSegment, mass, massProperties);

			// For the cylinder above, with 0.1 should be ample.
	confirmEqual(massProperties.m_mass, geometryApproximationProperties.m_mass, 1e-1f);
	confirmEqual(massProperties.m_volume, geometryApproximationProperties.m_volume, 1e-1f);
	confirmEqual(massProperties.m_centerOfMass, geometryApproximationProperties.m_centerOfMass, 1e-1f);
	confirmEqual(massProperties.m_inertiaTensor, geometryApproximationProperties.m_inertiaTensor, 1e-1f);

}


// We check here by creating an actual *geometry* (approximation) of the capsule, then using
// computeGeometryVolumeMassProperties().
void checkLineSegment()
{
	{
			// Check a "random" cyliner
		hkVector4 uglyStart(10,7,8);
		hkVector4 uglyEnd(13,4,-3);

		checkGivenLineSegment(uglyStart, uglyEnd, 1.3f);
		checkGivenLineSegment(uglyStart, uglyEnd, 0.01f);	// Check also with very small radius
	}

	{
			// Check one aligned with "canonical cylinder space" which takes a differeent path though the calculation
		hkVector4 canonicalStart(0,0,0);
		hkVector4 canonicalEnd(0,0,10);

		checkGivenLineSegment(canonicalStart, canonicalEnd, 1.3f);
		checkGivenLineSegment(canonicalStart, canonicalEnd, 0.01f);	// Check also with very small radius
	}

	{
			// Check reversed case 
		hkVector4 flippedCanonicalStart(0,0,10);
		hkVector4 flippedCanonicalEnd(0,0,0);

		checkGivenLineSegment(flippedCanonicalStart, flippedCanonicalEnd, 1.3f);
		checkGivenLineSegment(flippedCanonicalStart, flippedCanonicalEnd, 0.01f);	// Check also with very small radius
	}

	{
			// Check case height nearly =0. 
			// NB Radius is NOT allowed to be 0!
		hkVector4 zeroHeightStart(0,0,0);
		hkVector4 zeroHeightEnd( 0,0,HK_REAL_EPSILON);

		checkGivenLineSegment(zeroHeightStart, zeroHeightEnd, 1.3f);
		checkGivenLineSegment(zeroHeightStart, zeroHeightEnd, 0.01f);	// Check also with very small radius
	}

}

// Check the recursiveshape computation where one of the "subshapes" has zero volume.
// This hsould work OK, it should be ignored.
void checkZeroVolumeSubShape()
{

	hkpMassProperties exactResult;
	hkpRigidBodyCinfo compoundInfo;

	
	hkArray<hkpShape*> shapesForDeletion;

	

		// Create a "transformed box" shape
	hkpTransformShape* boxTrans;
	{
		hkVector4 halfExtents(0.5547f, 1.0235f, 3.43124f);
		hkpBoxShape* b = new hkpBoxShape(halfExtents, 0 );	// Note: We use HALF-extents for boxes
		shapesForDeletion.pushBack(b);	

		// Construct "nasty" Transform;
		hkTransform nasty;
		hkVector4 p(.75f, -.3f, 1.9f);
		nasty.setTranslation(p);
		hkQuaternion q = getQuaternion(0.7f, .45f, 0.8f, -1.3f);
		nasty.setRotation(q);

		boxTrans = new hkpTransformShape( b, nasty );

		shapesForDeletion.pushBack(boxTrans);	
	}

		// Create first "zero volume" shape,
	hkpTriangleShape* tri;
	{
		hkVector4 v0(-10,0,7);
		hkVector4 v1(6,5,-4);
		hkVector4 v2(2,3,0);

		tri = new hkpTriangleShape();
		shapesForDeletion.pushBack(tri);	
		tri->setVertex(0, v0);
		tri->setVertex(1, v1);
		tri->setVertex(2, v2);

		tri->setRadius(0.0f);
	}

		// Create second "zero volume" shape,
	hkpMultiRayShape* multiRay;
	{
		hkArray<hkpMultiRayShape::Ray> rays;
		for(int i=0; i< 10; i++)
		{
			hkpMultiRayShape::Ray r;
			r.m_start.set(hkReal(i+1.0f), hkReal(i*i), hkReal(i*i*i));
			rays.pushBack(r);		
		}

		multiRay = new hkpMultiRayShape(rays.begin(), rays.getSize());
		shapesForDeletion.pushBack(multiRay);	
	}




	// Now we try three things:
	// 1. Just the tranformed box shape
	// 2. The tranformed box shape and the zero volume shape
	// 3. The zero volume shape and the tranformed box shape (ordered differently, so parsed differently!)


	const hkReal mass = 7.3f;
	hkpMassProperties correctMassProperties;
	setMassPropertiesToRandomNonsense(correctMassProperties);
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxTrans, mass, correctMassProperties);

	// We try this for both a zero thickness triangle, and a multiray shape


		// box, then tri
	{
		hkArray<hkpShape*> shapeArray;
		shapeArray.pushBack(boxTrans);
		shapeArray.pushBack(tri);
		
		hkpListShape* listShape = new hkpListShape(&shapeArray[0], shapeArray.getSize());
		shapesForDeletion.pushBack(listShape);

		hkpMassProperties result;
		setMassPropertiesToRandomNonsense(result);
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(listShape, mass, result);


		confirmEqual(correctMassProperties.m_mass, result.m_mass, 1e-3f);
		confirmEqual(correctMassProperties.m_volume, result.m_volume, 1e-3f);
		confirmEqual(correctMassProperties.m_centerOfMass, result.m_centerOfMass ,1e-3f);
		confirmEqual(correctMassProperties.m_inertiaTensor, result.m_inertiaTensor ,1e-3f);	
	}

		// tri, then box
	{
		hkArray<hkpShape*> shapeArray;
		shapeArray.pushBack(tri);
		shapeArray.pushBack(boxTrans);
		
		hkpListShape* listShape = new hkpListShape(&shapeArray[0], shapeArray.getSize());
		shapesForDeletion.pushBack(listShape);

		hkpMassProperties result;
		setMassPropertiesToRandomNonsense(result);
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(listShape, mass, result);


		confirmEqual(correctMassProperties.m_mass, result.m_mass, 1e-3f);
		confirmEqual(correctMassProperties.m_volume, result.m_volume, 1e-3f);
		confirmEqual(correctMassProperties.m_centerOfMass, result.m_centerOfMass ,1e-3f);
		confirmEqual(correctMassProperties.m_inertiaTensor, result.m_inertiaTensor ,1e-3f);	
	}

		// box, then ray
	{
		hkArray<hkpShape*> shapeArray;
		shapeArray.pushBack(boxTrans);
		shapeArray.pushBack(multiRay);
		
		hkpListShape* listShape = new hkpListShape(&shapeArray[0], shapeArray.getSize());
		shapesForDeletion.pushBack(listShape);

		hkpMassProperties result;
		setMassPropertiesToRandomNonsense(result);
			// Disable the 'HK_SHAPE_MULTI_RAY has no volume, mass properties ignored' warning.
		hkBool oldValue = hkError::getInstance().isEnabled(0x57ca2117);
		hkError::getInstance().setEnabled(0x57ca2117, false);
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(listShape, mass, result);
		hkError::getInstance().setEnabled(0x57ca2117, oldValue);


		confirmEqual(correctMassProperties.m_mass, result.m_mass, 1e-3f);
		confirmEqual(correctMassProperties.m_volume, result.m_volume, 1e-3f);
		confirmEqual(correctMassProperties.m_centerOfMass, result.m_centerOfMass ,1e-3f);
		confirmEqual(correctMassProperties.m_inertiaTensor, result.m_inertiaTensor ,1e-3f);	
	}

		// ray then box
	{
		hkArray<hkpShape*> shapeArray;
		shapeArray.pushBack(multiRay);
		shapeArray.pushBack(boxTrans);
		
		hkpListShape* listShape = new hkpListShape(&shapeArray[0], shapeArray.getSize());
		shapesForDeletion.pushBack(listShape);

		hkpMassProperties result;
		setMassPropertiesToRandomNonsense(result);
			// Disable the 'HK_SHAPE_MULTI_RAY has no volume, mass properties ignored' warning.
		hkBool oldValue = hkError::getInstance().isEnabled(0x57ca2117);
		hkError::getInstance().setEnabled(0x57ca2117, false);
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(listShape, mass, result);
		hkError::getInstance().setEnabled(0x57ca2117, oldValue);


		confirmEqual(correctMassProperties.m_mass, result.m_mass, 1e-3f);
		confirmEqual(correctMassProperties.m_volume, result.m_volume, 1e-3f);
		confirmEqual(correctMassProperties.m_centerOfMass, result.m_centerOfMass ,1e-3f);
		confirmEqual(correctMassProperties.m_inertiaTensor, result.m_inertiaTensor ,1e-3f);	
	}
		

		// delete shapes
	for(int i = 0; i< shapesForDeletion.getSize(); i++)
	{
		shapesForDeletion[i]->removeReference();
	}

	

}

/////////////////////////////////////////////////////////////////////////////////////
int inertia_main()
{
	checkSphereVol();
	checkSphereSurface();
	checkBoxVol();
	checkBoxSurface();
	checkTriangle();
	checkHull();
	checkPointCloud();
	checkSkin();
	//checkCompound(); // This test asserts because one of the two algorithms used performs some 'degenerated inertias' correction while the other one doesn't; that is correct but could be adapted in the future
		

	checkBoxShape();
	checkSphereShape();
	checkSphereShape();
	checkCompoundShape();
	checkCompoundShape2();

	checkComputeShapeVolumeMassProperties();

	checkSimplifyITOriented();

//	checkZeroMassBug();	// Can't actually run this in demo framework as it checks for an assert!

	checkLineSegment();

	checkZeroVolumeSubShape();

	return 0;

}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(inertia_main, "Slow", "Physics/Test/UnitTest/Utilities/", __FILE__     );


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
