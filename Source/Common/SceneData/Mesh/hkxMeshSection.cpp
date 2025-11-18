/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/SceneData/hkSceneData.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/hkxIndexBuffer.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Mesh/hkxVertexFormat.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>


/// Returns the total number of triangles in all index buffers
hkUint32 hkxMeshSection::getNumTriangles () const
{
	hkUint32 nTriangles = 0;
	
	for (int n=0; n<m_numIndexBuffers; n++)
	{
		hkxIndexBuffer* ibuffer = m_indexBuffers[n];

		nTriangles += ibuffer->getNumTriangles();
	}
	
	return nTriangles;
}

/// Explore the index buffers for the indices of the triIndex'th triangle
void hkxMeshSection::getTriangleIndices (hkUint32 triIndex, hkUint32& indexAOut, hkUint32& indexBOut, hkUint32& indexCOut) const
{
	hkUint32 nTriangles = 0;	
	for (int n=0; n<m_numIndexBuffers; n++)
	{
		hkxIndexBuffer* ibuffer = m_indexBuffers[n];
		hkUint32 nBuffer = ibuffer->getNumTriangles();
	
		if ( triIndex < nTriangles + nBuffer )
		{
			ibuffer->getTriangleIndices( triIndex-nTriangles, indexAOut, indexBOut, indexCOut );
			return;
		}
	
		nTriangles += nBuffer;
	}
}

void hkxMeshSection::collectVertexPositions (hkArray<hkVector4>& verticesOut) const
{
	char* data = (char*)( m_vertexBuffer->m_vertexData );
	int stride = m_vertexBuffer->m_format->m_stride;;
	int posOffset = m_vertexBuffer->m_format->m_positionOffset;

	verticesOut.setSize(m_vertexBuffer->m_numVertexData);
	for (int vi=0; vi < m_vertexBuffer->m_numVertexData; ++vi)
	{
		float* pos = (float*)( data + posOffset );
		hkVector4 vert; vert.set(pos[0], pos[1],pos[2]);

		verticesOut[vi] = vert;

		data += stride;
	}
}

void hkxMeshSection::constructGeometry (struct hkGeometry& geometryOut)
{
	collectVertexPositions(geometryOut.m_vertices);

	// Now, check the index buffer
	for (int ib=0; ib<m_numIndexBuffers; ++ib)
	{
		hkxIndexBuffer* ibuffer = m_indexBuffers[ib];

		const int numIndices = ibuffer->m_indices16 ? ibuffer->m_numIndices16 : ibuffer->m_numIndices32;

		int index = 0;

		while (index<numIndices)
		{
			hkGeometry::Triangle newTriangle;

			switch (ibuffer->m_indexType)
			{
			case hkxIndexBuffer::INDEX_TYPE_TRI_LIST:
				{

					newTriangle.m_a = ibuffer->m_indices16 ? ibuffer->m_indices16[index] : ibuffer->m_indices32[index];
					newTriangle.m_b = ibuffer->m_indices16 ? ibuffer->m_indices16[index+1] : ibuffer->m_indices32[index+1];
					newTriangle.m_c = ibuffer->m_indices16 ? ibuffer->m_indices16[index+2] : ibuffer->m_indices32[index+2];

					index += 3;
					break;
				}
			case hkxIndexBuffer::INDEX_TYPE_TRI_STRIP:
				{
					if (index<2)
					{
						index++;
						continue;
					}

					if (index==2)
					{
						newTriangle.m_a = ibuffer->m_indices16 ? ibuffer->m_indices16[0] : ibuffer->m_indices32[0];
						newTriangle.m_b = ibuffer->m_indices16 ? ibuffer->m_indices16[1] : ibuffer->m_indices32[1];
						newTriangle.m_c = ibuffer->m_indices16 ? ibuffer->m_indices16[2] : ibuffer->m_indices32[2];						

						index ++;
						break;
					}

					const hkGeometry::Triangle &previousTriangle = geometryOut.m_triangles[geometryOut.m_triangles.getSize()-1];

					newTriangle.m_a = previousTriangle.m_c;
					newTriangle.m_b = previousTriangle.m_b;
					newTriangle.m_c = ibuffer->m_indices16 ? ibuffer->m_indices16[index] : ibuffer->m_indices32[index];

					index ++;
					break;
				}
			default:
				{
					HK_WARN_ALWAYS(0xabbaa883, "Unsupported index buffer type - Ignoring");
					index = numIndices;
					continue;
				}
			}

			geometryOut.m_triangles.pushBack(newTriangle);

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
