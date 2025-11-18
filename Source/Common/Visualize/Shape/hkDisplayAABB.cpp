/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/Shape/hkDisplayAABB.h>


hkDisplayAABB::hkDisplayAABB(const hkVector4& min, const hkVector4& max)
:	hkDisplayGeometry(HK_DISPLAY_AABB),
	m_minExtent(min),
	m_maxExtent(max)
{
}

hkDisplayAABB::hkDisplayAABB()
:	hkDisplayGeometry(HK_DISPLAY_AABB)
{
	m_minExtent.setZero4();
	m_maxExtent.setZero4();
}



void hkDisplayAABB::setExtents(const hkVector4& min, const hkVector4& max)
{
	m_minExtent = min;
	m_maxExtent = max;
}


void hkDisplayAABB::buildGeometry()
{
	// build triangle hkGeometry
	m_geometry = new hkGeometry;

	m_geometry->m_vertices.expandBy(1)->set(m_minExtent(0),m_minExtent(1),m_minExtent(2));
	m_geometry->m_vertices.expandBy(1)->set(m_minExtent(0),m_minExtent(1),m_maxExtent(2));
	m_geometry->m_vertices.expandBy(1)->set(m_maxExtent(0),m_minExtent(1),m_maxExtent(2));
	m_geometry->m_vertices.expandBy(1)->set(m_maxExtent(0),m_minExtent(1),m_minExtent(2));
	m_geometry->m_vertices.expandBy(1)->set(m_minExtent(0),m_maxExtent(1),m_minExtent(2));
	m_geometry->m_vertices.expandBy(1)->set(m_minExtent(0),m_maxExtent(1),m_maxExtent(2));
	m_geometry->m_vertices.expandBy(1)->set(m_maxExtent(0),m_maxExtent(1),m_maxExtent(2));
	m_geometry->m_vertices.expandBy(1)->set(m_maxExtent(0),m_maxExtent(1),m_minExtent(2));	

	// tris are CCW order -  is this right?
	m_geometry->m_triangles.expandBy(1)->set(0,3,1);
	m_geometry->m_triangles.expandBy(1)->set(1,3,2);
	m_geometry->m_triangles.expandBy(1)->set(2,6,5);
	m_geometry->m_triangles.expandBy(1)->set(5,1,2);
	m_geometry->m_triangles.expandBy(1)->set(5,6,4);
	m_geometry->m_triangles.expandBy(1)->set(4,6,7);
	m_geometry->m_triangles.expandBy(1)->set(7,3,0);
	m_geometry->m_triangles.expandBy(1)->set(0,4,7);
	m_geometry->m_triangles.expandBy(1)->set(0,1,4);
	m_geometry->m_triangles.expandBy(1)->set(4,1,5);
	m_geometry->m_triangles.expandBy(1)->set(2,3,6);
	m_geometry->m_triangles.expandBy(1)->set(6,3,7);

	/*int bytessaved = */
}

const hkVector4& hkDisplayAABB::getMinExtent()
{
	return m_minExtent;
}


const hkVector4& hkDisplayAABB::getMaxExtent()
{
	return m_maxExtent;
}

void hkDisplayAABB::getWireframeGeometry(hkArray<hkVector4>& lines)
{
	lines.setSize(24);
	
	lines[0].set(m_minExtent(0),m_minExtent(1),m_minExtent(2));
	lines[1].set(m_minExtent(0),m_maxExtent(1),m_minExtent(2));

	lines[2].set(m_minExtent(0),m_minExtent(1),m_minExtent(2));
	lines[3].set(m_minExtent(0),m_minExtent(1),m_maxExtent(2));

	lines[4].set(m_minExtent(0),m_minExtent(1),m_minExtent(2));
	lines[5].set(m_maxExtent(0),m_minExtent(1),m_minExtent(2));

	lines[6].set(m_maxExtent(0),m_maxExtent(1),m_maxExtent(2));
	lines[7].set(m_maxExtent(0),m_maxExtent(1),m_minExtent(2));

	lines[8].set(m_maxExtent(0),m_maxExtent(1),m_maxExtent(2));
	lines[9].set(m_minExtent(0),m_maxExtent(1),m_maxExtent(2));

	lines[10].set(m_maxExtent(0),m_maxExtent(1),m_maxExtent(2));
	lines[11].set(m_maxExtent(0),m_minExtent(1),m_maxExtent(2));

	lines[12].set(m_minExtent(0),m_maxExtent(1),m_minExtent(2));
	lines[13].set(m_maxExtent(0),m_maxExtent(1),m_minExtent(2));

	lines[14].set(m_minExtent(0),m_maxExtent(1),m_minExtent(2));
	lines[15].set(m_minExtent(0),m_maxExtent(1),m_maxExtent(2));

	lines[16].set(m_maxExtent(0),m_maxExtent(1),m_minExtent(2));
	lines[17].set(m_maxExtent(0),m_minExtent(1),m_minExtent(2));

	lines[18].set(m_minExtent(0),m_maxExtent(1),m_maxExtent(2));
	lines[19].set(m_minExtent(0),m_minExtent(1),m_maxExtent(2));

	lines[20].set(m_minExtent(0),m_minExtent(1),m_maxExtent(2));
	lines[21].set(m_maxExtent(0),m_minExtent(1),m_maxExtent(2));

	lines[22].set(m_maxExtent(0),m_minExtent(1),m_maxExtent(2));
	lines[23].set(m_maxExtent(0),m_minExtent(1),m_minExtent(2));
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
