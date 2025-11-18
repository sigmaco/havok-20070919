/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

#include <Common/Visualize/Shape/hkDisplayCapsule.h>

hkDisplayCapsule::hkDisplayCapsule( const hkVector4& top, const hkVector4& bottom, hkReal radius, int numSides , int numHeightSegments )
:  hkDisplayGeometry(HK_DISPLAY_CAPSULE), 
   m_numSides(numSides), m_numHeightSegments(numHeightSegments)
{
	m_top = top;
	m_bottom = bottom;
	m_radius = radius; 
}

#if defined(HK_PLATFORM_XBOX360)
#pragma optimize("",off)
#endif
void hkDisplayCapsule::buildGeometry()
{
	const hkVector4& start = m_top;
	const hkVector4& end = m_bottom;
	const hkReal radius = m_radius;

	const int heightSamples	= m_numHeightSegments;
	const int thetaSamples	= m_numSides;
	const int phiSamples	= thetaSamples >> 1;

	hkArray<hkVector4> verts;

		// Create "transform" from start, end.
	hkTransform capsuleToLocal;
	

	hkVector4 axis;
	axis.setSub4(end, start);
	hkReal height = axis.length3();
	if(height > 0.0f)
	{
		axis.normalize3();

		hkVector4 canonicalZ; canonicalZ = hkQuadReal0010;
		if(hkMath::fabs(axis.dot3(canonicalZ)) < 1 - 1e-5f)
		{
			hkRotation rotation;
			hkVector4& col0 = rotation.getColumn(0);
			hkVector4& col1 = rotation.getColumn(1);
			hkVector4& col2 = rotation.getColumn(2);

			col2 = axis;
			col1.setCross( col2, canonicalZ); 
			col1.normalize3();
			col0.setCross( col1, col2 );
			capsuleToLocal.setRotation(rotation);
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

			// Now recentre
	{
		hkVector4 toCentre;
		toCentre.setAdd4(start, end);
		toCentre.mul4(0.5f);
		capsuleToLocal.setTranslation(toCentre);
	}
	
	


	// We'll sweep aound the axis of the deflector, from top to bottom, using the original
	// sample directions and data to defien the vertices. We'll tessellate in the obvious way.
	// N.B. Top and bottom vertices are added to cap the object. 

	int i,j;

	hkVector4 vert;

	hkVector4 bottomInGeom; bottomInGeom.set(0,0,-height/2);
	hkVector4 topInGeom; topInGeom.set(0,0,height/2);
	hkVector4 axisInGeom;
	axisInGeom.setSub4(topInGeom, bottomInGeom);
	hkVector4 axisNInGeom; axisNInGeom.set(0,0,1);
	hkVector4 normalInGeom; normalInGeom.set(1,0,0);
	hkVector4 binormalInGeom; binormalInGeom.set(0,-1,0);

	// top capsule = phiSamples (segments) = phiSamples + 1 vert rings but top ring is vert so phiSamples * thetaSamples + 1 verts
	// This contains the top ring of the cylinder, top cap = phiSamples rings of faces
	// bottom capsule = phiSamples (segments) = phiSamples + 1 rings but bottom ring is vert so phiSamples * thetaSamples + 1 verts
	// This contains the bottom ring of the cylinder, bottom cap = phiSamples rings of faces
	// cylinder body = heightSamples (segments) = heightSamples + 1 vert rings but bottom and top caps already create 2 so (heightSamples -1) * thetaSamples verts
	// cylinder body = heightSamples rings of faces
	// total number of face rings = 2 * phiSamples + heightSamples
	verts.reserveExactly(2 * phiSamples * thetaSamples + 2 + (heightSamples-1) * thetaSamples);

	//
	// GET TOP VERTICES
	//

	vert.set(0, 0 ,height*0.5f + radius);
	vert.setTransformedPos(capsuleToLocal, vert);
	verts.pushBack(vert);

	for (i = phiSamples-1 ; i >= 0; i--)
	{
		hkQuaternion qTop(binormalInGeom, hkReal(i) / phiSamples * HK_REAL_PI * .5f);
		hkVector4 topElevation;
		topElevation.setRotatedDir(qTop, normalInGeom);

		for (j = 0; j < thetaSamples; j++)
		{
			hkQuaternion rotationTop(axisNInGeom, hkReal(j) / thetaSamples * HK_REAL_PI * 2);			
			hkVector4 topDirection;
			topDirection.setRotatedDir(rotationTop, topElevation);

			hkReal dist = radius;
			vert.setAddMul4(topInGeom, topDirection, dist);

			vert.setTransformedPos(capsuleToLocal, vert);

			//push back the rest of the vertices
			verts.pushBack(vert);

		}
	}

	//
	// GET MIDDLE VERTICES
	//
	for (j = heightSamples-1; j > 0; j--)
	{
	
		for (i = 0; i < thetaSamples; i++)
		{	
		//
		// Calculate direction vector for this angle
		//

			hkQuaternion q(axisNInGeom, hkReal(i) / thetaSamples * HK_REAL_PI * 2);
			hkVector4 direction;
			direction.setRotatedDir(q, normalInGeom);
			
			hkVector4 s;
			s.setAddMul4(bottomInGeom, axisInGeom, hkReal(j) / hkReal(heightSamples));

			hkReal dist = radius;

			vert.setAddMul4(s, direction, dist);

			vert.setTransformedPos(capsuleToLocal, vert);

			verts.pushBack(vert);

		}
	}

 
	//
	// GET BOTTOM VERTICES
	//
	for (i = 0; i < phiSamples; i++)
	{
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

	//
	// CONSTRUCT FACE DATA
	//
	hkGeometry* geom = new hkGeometry;
	geom->m_vertices = verts;
	// Transform all the points by m_transform.
	// TODO: take all these calcs out of these functions, and put into graphics handler
	// currently what comes out is wrong - i.e. a differenc graphics handler might assume
	// the transform should be taken into account, so it would be doubly counted.
	{
		for ( int vi = 0; vi < geom->m_vertices.getSize(); ++vi )
		{
			geom->m_vertices[vi].setTransformedPos(m_transform, geom->m_vertices[vi]);
		}
	}

	// Right, num samples AROUND axis is thetaSamples.

	// First off, we have thetaSamples worth of faces connected to the top
	hkGeometry::Triangle tr;

	int currentBaseIndex = 1;
	for (i = 0; i < thetaSamples; i++)
	{
		tr.m_a = 0;
		tr.m_b = currentBaseIndex + i;
		tr.m_c = currentBaseIndex + (i+1)%(thetaSamples);

		geom->m_triangles.pushBack(tr);
	}

	
	// Next we have phi-1 + height + phi-1 lots of thetaSamples*2 worth of faces connected to the previous row
	for(j = 0; j < 2*(phiSamples-1) + heightSamples; j++)
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
	
	

	m_geometry = geom;
}
#if defined(HK_PLATFORM_XBOX360)
#pragma optimize("",on)
#endif


void hkDisplayCapsule::getWireframeGeometry(hkArray<hkVector4>& lines)
{
	//TODO
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
