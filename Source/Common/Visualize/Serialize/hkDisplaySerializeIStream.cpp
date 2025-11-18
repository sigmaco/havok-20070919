/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/Serialize/hkDisplaySerializeIStream.h>

// Definitions of more complex types
#include <Common/Base/Types/Geometry/hkGeometry.h>
#include <Common/Visualize/Shape/hkDisplayConvex.h>
#include <Common/Visualize/Shape/hkDisplaySphere.h>
#include <Common/Visualize/Shape/hkDisplayBox.h>
#include <Common/Visualize/Shape/hkDisplayAABB.h>
#include <Common/Visualize/Shape/hkDisplayCone.h>
#include <Common/Visualize/Shape/hkDisplaySemiCircle.h>
#include <Common/Visualize/Shape/hkDisplayPlane.h>
#include <Common/Visualize/Shape/hkDisplayCapsule.h>
#include <Common/Visualize/Shape/hkDisplayCylinder.h>

hkDisplaySerializeIStream::hkDisplaySerializeIStream(hkStreamReader* reader)
	: hkIArchive(reader)
{
}

void hkDisplaySerializeIStream::readQuadVector4(hkVector4& v)
{
	readArrayFloat32(&v(0), 3);
	v(3) = 0.0f;	// initialize element that is not transmitted
}

void hkDisplaySerializeIStream::readTransform(hkTransform& t)
{
//	readFloats(&t.getRotation().getColumn(0)(0), 16);

//*
	// get the position
	hkVector4 position;
	readArrayFloat32(&position(0), 3);
	position(3) = 1.0f;

	// get the orientation
	hkQuaternion orientation;
	readArrayFloat32(const_cast<hkReal*>(&orientation(0)), 4);

	// setup the transform
	t.setTranslation(position);
	t.setRotation(orientation);
//*/
}

void hkDisplaySerializeIStream::readTriangle(hkGeometry::Triangle& ti)
{
	ti.m_a = read32();
	ti.m_b = read32();
	ti.m_c = read32();
}

void hkDisplaySerializeIStream::readGeometry(hkGeometry& g)
{
	// extract the array of vertices
	{
		int numVertices = read32();

		for(int i = 0; i < numVertices; i++)
		{
			readQuadVector4(*g.m_vertices.expandBy(1));
		}
	}

	// extract the array of triangle indicies
	{
		int numTriangles = read32();

		for(int i = 0; i < numTriangles; i++)
		{
			readTriangle(*g.m_triangles.expandBy(1));
		}
	}

}

void hkDisplaySerializeIStream::readDisplayGeometry(hkDisplayGeometry*& dg)
{
	// grab the type information
	char t_asChar = read8();
	hkDisplayGeometryType t = (hkDisplayGeometryType)t_asChar;

	// for grabbing the transform
	hkTransform transform; 


	// grab the specific information partaining to this geometry
	switch(t)
	{
		case HK_DISPLAY_CONVEX:
			{
				readTransform(transform);
				// read in the geometry
				hkGeometry* geometry = new hkGeometry();
				readGeometry(*geometry);

				dg = new hkDisplayConvex(geometry);
				dg->getTransform() = transform;
			}
			break;

		case HK_DISPLAY_SPHERE:
			{
				readTransform(transform);
				// read in the sphere and the x and y tesslation resolutions
				hkReal radius = readFloat32();

				hkVector4 position;	
				readQuadVector4(position);
				hkSphere sphere(position, radius);

				int xRes = read32();
				int yRes = read32();

				dg = new hkDisplaySphere(sphere, xRes, yRes);
				dg->getTransform() = transform;
			}
			break;

		case HK_DISPLAY_CAPSULE:
			{
				readTransform(transform);
				hkReal radius = readFloat32();

				hkVector4 top;
				readQuadVector4( top );
				hkVector4 bottom;
				readQuadVector4( bottom );

				int numSides = read32();
				int numHeightSegments = read32();

				dg = new hkDisplayCapsule( top, bottom, radius, numSides, numHeightSegments );
				dg->getTransform() = transform;
			}
			break;

		case HK_DISPLAY_CYLINDER:
			{
				readTransform(transform);
				hkReal radius = readFloat32();

				hkVector4 top;
				readQuadVector4( top );
				hkVector4 bottom;
				readQuadVector4( bottom );

				int numSides = read32();
				int numHeightSegments = read32();

				dg = new hkDisplayCylinder( top, bottom, radius, numSides, numHeightSegments );
				dg->getTransform() = transform;
			}
			break;

		case HK_DISPLAY_BOX:
			{
				readTransform(transform);
				hkVector4 halfExtents; readQuadVector4(halfExtents);

				dg = new hkDisplayBox(halfExtents);
				dg->getTransform() = transform;
			}
			break;

		case HK_DISPLAY_AABB:
			{
				// no transform for this type
				hkVector4 minExtent; 
				hkVector4 maxExtent; 
				readQuadVector4(minExtent);
				readQuadVector4(maxExtent);
				dg = new hkDisplayAABB(minExtent, maxExtent);
			}
			break;

		case HK_DISPLAY_CONE:
			{
				hkVector4 position;
				hkVector4 axis;
				hkReal angle;
				hkReal height;
				int numSegments;

				readQuadVector4(position);
				readQuadVector4(axis);
				angle = readFloat32();
				height = readFloat32();
				numSegments = read32();

				dg = new hkDisplayCone(angle,height,numSegments,axis,position);
			}
			break;
	
		case HK_DISPLAY_SEMICIRCLE:
			{
				//hkDisplaySemiCircle* dsemi = static_cast<hkDisplaySemiCircle*>(dg);
				hkVector4 center;
				hkVector4 normal;
				hkVector4 perp;
				hkReal radius;
				hkReal thetaMin;
				hkReal thetaMax;
				int numSegments;

				readQuadVector4(center);
				readQuadVector4(normal);
				readQuadVector4(perp);
				radius = readFloat32();
				thetaMin = readFloat32();
				thetaMax = readFloat32();
				numSegments = read32();
				
				dg = new hkDisplaySemiCircle(center, normal, perp, 
											 thetaMin, thetaMax, radius,
											 numSegments);
			}
			break;

		case HK_DISPLAY_PLANE:
			{
				//hkDisplayPlane* dplane = static_cast<hkDisplayPlane*>(dg);
				hkVector4 center;
				hkVector4 normal;
				hkVector4 perpToNormal;
				hkReal extent;

				readQuadVector4(center);
				readQuadVector4(normal);
				readQuadVector4(perpToNormal);
				extent = readFloat32(); //XX should be 3 extents but need to change protocol to add it.
				hkVector4 extent3; extent3.setAll3(extent);
				dg = new hkDisplayPlane(normal, perpToNormal, center, extent3);
			}
			break;

		default:
			HK_ASSERT2(0x4739a00e, 0, "Display stream corrupt or unsupported display geometry revieved!");
	}
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
