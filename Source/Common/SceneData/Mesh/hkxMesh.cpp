/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/SceneData/hkSceneData.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/hkxVertexFormat.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>

void hkxMesh::collectVertexPositions (hkArray<hkVector4>& verticesOut) const
{
	for (int si=0; si < m_numSections; ++si)
	{
		hkxMeshSection* section = m_sections[si];
		hkxVertexBuffer* vertices = section->m_vertexBuffer;
		char* data = (char*)( vertices->m_vertexData );
		int stride = vertices->m_format->m_stride;;
		int posOffset = vertices->m_format->m_positionOffset;
		int bufOffset = verticesOut.getSize();

		verticesOut.setSize(bufOffset + vertices->m_numVertexData);
		for (int vi=0; vi < vertices->m_numVertexData; ++vi)
		{
			float* pos = (float*)( data + posOffset );
			hkVector4 vert; vert.set(pos[0], pos[1],pos[2]);

			verticesOut[vi + bufOffset] = vert;

			data += stride;
		}
	}
}

void hkxMesh::constructGeometry(hkGeometry& geometryOut) const
{
	geometryOut.m_triangles.clear();
	geometryOut.m_vertices.clear();

	for (int si=0; si < m_numSections; ++si)
	{
		int indexOffset = geometryOut.m_vertices.getSize();

		hkGeometry sectionGeometry;
		m_sections[si]->constructGeometry(sectionGeometry);

		// Increment indices for added geometries
		for (int t=0; t<sectionGeometry.m_triangles.getSize(); t++)
		{
			sectionGeometry.m_triangles[t].m_a += indexOffset;
			sectionGeometry.m_triangles[t].m_b += indexOffset;
			sectionGeometry.m_triangles[t].m_c += indexOffset;
		}

		// Merge arrays
		geometryOut.m_vertices.insertAt(indexOffset, sectionGeometry.m_vertices.begin(), sectionGeometry.m_vertices.getSize());
		geometryOut.m_triangles.insertAt(geometryOut.m_triangles.getSize(), sectionGeometry.m_triangles.begin(), sectionGeometry.m_triangles.getSize());
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
