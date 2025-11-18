/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

#include <Common/Base/Types/Geometry/hkGeometry.h>


// Remove identical vertices and triangles from a given hkGeometry.

void hctFilterGeometryUtils::weldMeshShapeVertices (struct hkGeometry& meshGeometry)
{
	hkArray<int> remap;
	weldMeshShapeVertices (meshGeometry, remap);
}


// Remove identical vertices and triangles from a given hkGeometry.
// Also return an hkArray<int> containing the map from original vertex indices into new ones.

void hctFilterGeometryUtils::weldMeshShapeVertices (struct hkGeometry& meshGeometry, hkArray<int>& remapOut)
{
	const int originalNumVertices = meshGeometry.m_vertices.getSize();

	// Construct a map from old indices into new indices
	for (int i=0; i<originalNumVertices; i++)
	{
		remapOut.pushBack(i);
	}
	
	// Compare vertices and build map
	for (int i=0; i<originalNumVertices-1; i++)
	{
		const int iRemap = remapOut[i];
		const hkVector4& original = meshGeometry.m_vertices[iRemap];

		for (int j=i+1; j<originalNumVertices; j++)
		{
			const int jRemap = remapOut[j];

			// Already compared and switched
			if (jRemap==iRemap) continue;

			const hkVector4& other = meshGeometry.m_vertices[jRemap];

			if (original.equals3(other))
			{
				// Remap this vertex
				remapOut[j] = iRemap;

				// Remove the duplicate
				meshGeometry.m_vertices.removeAtAndCopy(jRemap);

				// Remap the subsequent vertices
				for (int k=0; k<originalNumVertices; k++)
				{
					if (remapOut[k]>jRemap)
					{
						remapOut[k]--;
					}
				}
			}

		}
	}

	// Rebuild triangle lists
	for (int i=0; i<meshGeometry.m_triangles.getSize(); i++)
	{
		hkGeometry::Triangle& triangle = meshGeometry.m_triangles[i];

		triangle.m_a = remapOut[triangle.m_a];
		triangle.m_b = remapOut[triangle.m_b];
		triangle.m_c = remapOut[triangle.m_c];
	}
	
	// Remove duplicated triangles
	for (int i=0; i<meshGeometry.m_triangles.getSize()-1; i++)
	{
		const hkGeometry::Triangle& original = meshGeometry.m_triangles[i];
		for (int j=meshGeometry.m_triangles.getSize()-1; j>i; j--)
		{
			const hkGeometry::Triangle& other = meshGeometry.m_triangles[j];

			if ( (original.m_a == other.m_a) && (original.m_b == other.m_b) && (original.m_c == other.m_c))
			{
				meshGeometry.m_triangles.removeAtAndCopy(j);
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
