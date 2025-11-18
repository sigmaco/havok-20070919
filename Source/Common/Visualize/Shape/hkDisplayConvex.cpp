/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/Shape/hkDisplayConvex.h>

hkDisplayConvex::hkDisplayConvex(hkGeometry* geom)
:	hkDisplayGeometry(HK_DISPLAY_CONVEX)
{
	m_geometry = geom;
}


void hkDisplayConvex::buildGeometry()
{
  // Do nothing since geometry was passed in	
}


void hkDisplayConvex::getWireframeGeometry(hkArray<hkVector4>& lines)
{
    // This effectively means the lines will be drawn twice
	// but to filter out unique edges would be pretty costly
		
	if(m_geometry != HK_NULL)
	{
		long v[3];
	
		for(int i = m_geometry->m_triangles.getSize()-1; i >= 0;  i--)
		{
			v[0] = m_geometry->m_triangles[i].m_a;
			v[1] = m_geometry->m_triangles[i].m_b;
			v[2] = m_geometry->m_triangles[i].m_c;
			
			lines.pushBack(m_geometry->m_vertices[ v[0] ]);
			lines.pushBack(m_geometry->m_vertices[ v[1] ]);

			lines.pushBack(m_geometry->m_vertices[ v[0] ]);
			lines.pushBack(m_geometry->m_vertices[ v[2] ]);			

			lines.pushBack(m_geometry->m_vertices[ v[1] ]);
			lines.pushBack(m_geometry->m_vertices[ v[2] ]);
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
