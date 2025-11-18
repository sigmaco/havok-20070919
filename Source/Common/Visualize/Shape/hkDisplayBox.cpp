/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/Shape/hkDisplayBox.h>

hkDisplayBox::hkDisplayBox(const hkVector4& halfExtents)
:	hkDisplayGeometry(HK_DISPLAY_BOX),
	m_halfExtents(halfExtents)
{
	m_halfExtents = halfExtents;
}

hkDisplayBox::hkDisplayBox()
:	hkDisplayGeometry(HK_DISPLAY_BOX)
{
	m_halfExtents.setZero4();	
}

void hkDisplayBox::setParameters(const hkVector4& halfExtents, const hkTransform& t)
{
	m_halfExtents = halfExtents;
	m_transform = t;
}

/*
8
0.000000 1.000000 1.000000 
1.000000 1.000000 1.000000 
1.000000 0.000000 1.000000 
0.000000 0.000000 1.000000 
0.000000 1.000000 0.000000 
1.000000 1.000000 0.000000 
1.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 
12
3 3 2 1 
3 3 1 0 
3 6 7 4 
3 6 4 5 
3 4 7 3 
3 4 3 0 
3 2 6 5 
3 2 5 1 
3 7 6 2 
3 7 2 3 
3 1 5 4 
3 1 4 0 
*/
void hkDisplayBox::buildGeometry()
{
	m_geometry = new hkGeometry;

	m_geometry->m_vertices.expandBy(1)->set(-m_halfExtents(0), m_halfExtents(1), m_halfExtents(2));
	m_geometry->m_vertices.expandBy(1)->set(m_halfExtents(0), m_halfExtents(1), m_halfExtents(2));
	m_geometry->m_vertices.expandBy(1)->set(m_halfExtents(0), -m_halfExtents(1), m_halfExtents(2));
	m_geometry->m_vertices.expandBy(1)->set(-m_halfExtents(0), -m_halfExtents(1), m_halfExtents(2));
	m_geometry->m_vertices.expandBy(1)->set(-m_halfExtents(0), m_halfExtents(1), -m_halfExtents(2));
	m_geometry->m_vertices.expandBy(1)->set(m_halfExtents(0), m_halfExtents(1), -m_halfExtents(2));
	m_geometry->m_vertices.expandBy(1)->set(m_halfExtents(0), -m_halfExtents(1), -m_halfExtents(2));
	m_geometry->m_vertices.expandBy(1)->set(-m_halfExtents(0), -m_halfExtents(1), -m_halfExtents(2));

	for (int i=0; i < m_geometry->m_vertices.getSize(); i++)
	{
		m_geometry->m_vertices[i].setTransformedPos( m_transform, m_geometry->m_vertices[i] );
	}

	m_geometry->m_triangles.expandBy(1)->set(3, 2, 1);
	m_geometry->m_triangles.expandBy(1)->set(3, 1, 0);
	m_geometry->m_triangles.expandBy(1)->set(6, 7, 4);
	m_geometry->m_triangles.expandBy(1)->set(6, 4, 5);
	m_geometry->m_triangles.expandBy(1)->set(4, 7, 3);
	m_geometry->m_triangles.expandBy(1)->set(4, 3, 0);
	m_geometry->m_triangles.expandBy(1)->set(2, 6, 5);
	m_geometry->m_triangles.expandBy(1)->set(2, 5, 1);
	m_geometry->m_triangles.expandBy(1)->set(7, 6, 2);
	m_geometry->m_triangles.expandBy(1)->set(7, 2, 3);
	m_geometry->m_triangles.expandBy(1)->set(1, 5, 4);
	m_geometry->m_triangles.expandBy(1)->set(1, 4, 0);

	/*int bytessaved =*/
}


void hkDisplayBox::getWireframeGeometry(hkArray<hkVector4>& lines)
{
	lines.setSize(24);

	hkVector4 points[8];

	// points 
	{
		for (int i = 0; i < 8; i++)
		{
			hkVector4 v = m_halfExtents;
			if ( i & 1 )	v(0) *= -1.0f;
			if ( i & 2 )	v(1) *= -1.0f;
			if ( i & 4 )	v(2) *= -1.0f;
			points[i].setTransformedPos(m_transform, v);
		}
	}

	// edges
	
	{
		int k = 0;
		for (int i = 0; i < 8; i++)
		{
			for ( int bit = 1; bit < 8; bit <<= 1 )
			{
				int j = i ^ bit;

				if ( i < j )
				{
					lines[k++] = points[i];
					lines[k++] = points[j];
				}
			}
		}
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
