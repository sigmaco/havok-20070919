/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Visualize/hkVisualize.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

#include <Common/Visualize/Shape/hkDisplayCylinder.h>

hkDisplayCylinder::hkDisplayCylinder( const hkVector4& top, const hkVector4& bottom, hkReal radius, int numSides , int numHeightSegments )
:  hkDisplayGeometry(HK_DISPLAY_CYLINDER), 
   m_numSides(numSides), m_numHeightSegments(numHeightSegments)
{
	m_top = top;
	m_bottom = bottom;
	m_radius = radius; 
}

/*static hkBool isOutward( hkGeometry::Triangle& t, hkArray<hkVector4>& verts )
{
	hkVector4 e0; e0.setSub4( verts[t.m_b], verts[t.m_a] );
	hkVector4 e1; e1.setSub4( verts[t.m_c], verts[t.m_a] );
	hkVector4 c; c.setCross( e0, e1 );
	return c.dot3(verts[t.m_a]) > 0;	
}*/


void hkDisplayCylinder::buildGeometry()
{
	//
	// Draw triangles in a right-hand axes space in CCW direction
	//

	int& heightSegments = m_numHeightSegments;
	int& sideSegments   = m_numSides;

	//
	// Generate points in the order: bottom, top & then around the axis
	//
	{
		//
		// Setup basic helper variables
		//
		hkReal height;
		{
			hkVector4 segment;
			segment.setSub4(m_top, m_bottom);
			height = segment.length3();
		}

		// center point on the base of the cylinder
		//const hkVector4 base( 0.0f, 0.0f, -height/2 ); 
		const hkVector4& base = m_bottom;
		// axis lies along OZ + the lenght of a single heightSegment
		hkVector4 axis;
		axis.setSub4(m_top, m_bottom);
		axis.mul4( 1.0f / heightSegments );

		hkVector4 unitAxis = axis;
		unitAxis.normalize3();
		//( 0.0f, 0.0f, 1.0f );
		// vector perpendicular to the axis of the clinder; choose OX
		hkVector4 radius;
		{
			hkVector4 tmp;
			if ( hkMath::fabs(unitAxis(0)) > 0.5f )
			{
				tmp = hkQuadReal0100;
			}
			else if ( hkMath::fabs(unitAxis(1)) > 0.5f )
			{
				tmp = hkQuadReal0010;
			}
			else if ( hkMath::fabs(unitAxis(2)) > 0.5f )
			{
				tmp = hkQuadReal1000;
			}
			else
			{
				// cant be
			}
			radius.setCross(unitAxis, tmp);
			radius.normalize3();
			radius.mul4(m_radius);
		}
		// quaternion used to rotate radius to generate next set of (axis aligned) points
		hkQuaternion stepQuat( unitAxis, HK_REAL_PI * 2.0f / sideSegments );
		hkQuaternion currQuat( unitAxis, 0 );

		m_geometry = new hkGeometry;

		*(m_geometry->m_vertices.expandBy(1)) = base;
		{
			hkVector4 axisEnd;
			axisEnd.setMul4((hkReal)heightSegments, axis);
			axisEnd.add4(base);
			*(m_geometry->m_vertices.expandBy(1)) = axisEnd;
		}

		// Generate all points on the side of the cylinder
		for (int s = 0; s < sideSegments; ++s)
		{
			hkVector4 point;
			{
				// Set start position at the bottom of the cylinder
				hkVector4 modRadius;
				modRadius.setRotatedDir(currQuat, radius);
				point.setAdd4(base, modRadius);
			}

			// loop for heightSegments and add one extra ending after the loop
			for (int h = 0; h < heightSegments; ++h)
			{
				*(m_geometry->m_vertices.expandBy(1)) = point;
				point.add4(axis);
			}
			*(m_geometry->m_vertices.expandBy(1)) = point;

			hkQuaternion tmp = currQuat;
			currQuat.setMul(tmp, stepQuat);
		}
		// The above loop does one unneeded quat multiplication at the end.
	}

	//
	// Generate triangle indices
	//

	{
		// Store number of vertices in every column along the cylinder axis
		const int vertColLen = heightSegments + 1;
		const int allVertsCnt = 2 + sideSegments * (1 + heightSegments);
		// Store indices to the first two triangles; 
		// then increase all by the same number to get following triangles
		int indices[4] = { 2+0,
		                   2+vertColLen,
						   2+1,
		                   2+vertColLen+1
		                 };

		// Generate trinagles on cylinder side
		for (int s = 0; s < sideSegments; ++s)
		{
			for (int h = 0; h < heightSegments; ++h)
			{
				m_geometry->m_triangles.expandBy(1)->set(indices[0], indices[1], indices[2]);
				m_geometry->m_triangles.expandBy(1)->set(indices[2], indices[1], indices[3]);
				++indices[0];
				++indices[1];
				++indices[2];
				++indices[3];
			}
			// Increase indices again, since we have one less triangles/segments then vertices in a column
			++indices[0];
			++indices[1];
			++indices[2];
			++indices[3];
			if (indices[3] >= allVertsCnt)
			{
				indices[1] += 2 - allVertsCnt;
				indices[3] += 2 - allVertsCnt;
			}
		}

		// Generate both bases
		for (int base = 0; base < 2; ++base)
		{
			int start = 2 + (base ? heightSegments : 0);
			for (int s = 0; s < sideSegments; ++s)
			{
				int next = start + vertColLen;
				if (next >= allVertsCnt)
				{
					next += 2 - allVertsCnt;
				}

				if (base)
				{
					m_geometry->m_triangles.expandBy(1)->set(base, start, next );
				}
				else
				{
					m_geometry->m_triangles.expandBy(1)->set(base, next, start );
				}
				start = next;
			}
		}
	}

	// Done

}


void hkDisplayCylinder::getWireframeGeometry(hkArray<hkVector4>& lines)
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
