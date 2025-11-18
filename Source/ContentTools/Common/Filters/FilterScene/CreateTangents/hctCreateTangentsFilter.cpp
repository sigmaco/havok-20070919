/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>

#include <ContentTools/Common/Filters/FilterScene/CreateTangents/hctCreateTangentsFilter.h>
#include <ContentTools/Common/Filters/FilterScene/CreateTangents/hctCreateTangentsOptions.h>

#include <Common/SceneData/Graph/hkxNode.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Mesh/hkxIndexBuffer.h>
#include <Common/SceneData/Mesh/hkxVertexFormat.h>
#include <Common/SceneData/Mesh/Formats/hkxVertexP4N4C1T2.h>
#include <Common/SceneData/Mesh/Formats/hkxVertexP4N4W4I4C1Q2.h>
#include <Common/SceneData/Mesh/Formats/hkxVertexP4N4T4B4C1T2.h>
#include <Common/SceneData/Mesh/Formats/hkxVertexP4N4T4B4W4I4C1Q2.h>
#include <Common/SceneData/Mesh/Formats/hkxVertexP4N4T4B4W4I4Q4.h>

#include <ContentTools/Common/Filters/Common/Utils/hctFilterUtils.h>

#include <Common/Base/Math/Vector/hkVector4Util.h>

hctCreateTangentsFilterDesc g_createTangentsDesc;

hctCreateTangentsFilter::hctCreateTangentsFilter(const hctFilterManagerInterface* owner)
:	hctFilterInterface (owner),
	m_optionsDialog(NULL),
	m_splitVertices(false)
{
}

hctCreateTangentsFilter::~hctCreateTangentsFilter()
{

}

static void _createSimpleFormat( hkxVertexFormat* f, bool withVColor )
{
	// Normal plain format
	f->m_stride = sizeof(hkxVertexP4N4T4B4C1T2);
	f->m_positionOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4C1T2, m_position);
	f->m_normalOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4C1T2, m_normal);
	f->m_tangentOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4C1T2, m_tangent);
	f->m_binormalOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4C1T2, m_binormal);
	f->m_numBonesPerVertex = 0;
	f->m_boneIndexOffset = HK_VFMT_NOT_PRESENT;
	f->m_boneWeightOffset = HK_VFMT_NOT_PRESENT;
	f->m_numTextureChannels = 1; // otherwise 
	f->m_tFloatCoordOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4C1T2, m_u);
	f->m_tQuantizedCoordOffset = HK_VFMT_NOT_PRESENT;
	f->m_colorOffset = withVColor ? HK_OFFSET_OF(hkxVertexP4N4T4B4C1T2, m_diffuse) : HK_VFMT_NOT_PRESENT;
}

static void _createSkinnedFormat( hkxVertexFormat* f, bool withVColor )
{
	// Skinned format
	f->m_stride = sizeof(hkxVertexP4N4T4B4W4I4C1Q2);
	f->m_positionOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4C1Q2, m_position);
	f->m_normalOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4C1Q2, m_normal);
	f->m_tangentOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4C1Q2, m_tangent);
	f->m_binormalOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4C1Q2, m_binormal);
	f->m_numBonesPerVertex = 4;
	f->m_boneIndexOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4C1Q2, m_indices);
	f->m_boneWeightOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4C1Q2, m_weights);
	f->m_numTextureChannels = 1; // otherwise 
	f->m_tFloatCoordOffset = HK_VFMT_NOT_PRESENT;
	f->m_tQuantizedCoordOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4C1Q2, m_qu);
	f->m_colorOffset =  withVColor ? HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4C1Q2, m_diffuse) : HK_VFMT_NOT_PRESENT;
}

static void _CopyVertexData( const hkxMeshSection* section, const hkxVertexFormat* newFormat, char* newVB )
{
	const hkxVertexBuffer* vb = section->m_vertexBuffer;
	// To be copied / used
	char* posIn = ((char*)vb->m_vertexData) + vb->m_format->m_positionOffset;
	char* normIn = ((char*)vb->m_vertexData) + vb->m_format->m_normalOffset;
	char* colIn = (vb->m_format->m_colorOffset != HK_VFMT_NOT_PRESENT) ? ((char*)vb->m_vertexData) + vb->m_format->m_colorOffset : HK_NULL;
	char* uv0In = (vb->m_format->m_tFloatCoordOffset != HK_VFMT_NOT_PRESENT) ? ((char*)vb->m_vertexData) + vb->m_format->m_tFloatCoordOffset : HK_NULL;
	char* qv0In = (vb->m_format->m_tQuantizedCoordOffset != HK_VFMT_NOT_PRESENT) ? ((char*)vb->m_vertexData) + vb->m_format->m_tQuantizedCoordOffset : HK_NULL;
	char* uv1In = (uv0In && (vb->m_format->m_numTextureChannels > 1))? uv0In + sizeof(float)*2 : HK_NULL;
	char* qv1In = (qv0In && (vb->m_format->m_numTextureChannels > 1))? qv0In + sizeof(hkUint16)*2 : HK_NULL;
	char* wIn = (vb->m_format->m_boneWeightOffset != HK_VFMT_NOT_PRESENT) ? ((char*)vb->m_vertexData) + vb->m_format->m_boneWeightOffset : HK_NULL;
	char* idxIn = (vb->m_format->m_boneIndexOffset != HK_VFMT_NOT_PRESENT) ? ((char*)vb->m_vertexData) + vb->m_format->m_boneIndexOffset : HK_NULL;

	char* posOut = ((char*)newVB) + newFormat->m_positionOffset;
	char* normOut = ((char*)newVB) + newFormat->m_normalOffset;
	char* colOut = (newFormat->m_colorOffset != HK_VFMT_NOT_PRESENT) ? ((char*)newVB) + newFormat->m_colorOffset : HK_NULL;
	char* uv0Out = (newFormat->m_tFloatCoordOffset != HK_VFMT_NOT_PRESENT) ? ((char*)newVB) + newFormat->m_tFloatCoordOffset : HK_NULL;
	char* qv0Out = (newFormat->m_tQuantizedCoordOffset != HK_VFMT_NOT_PRESENT) ? ((char*)newVB) + newFormat->m_tQuantizedCoordOffset : HK_NULL;
	char* uv1Out = (uv0Out && (newFormat->m_numTextureChannels > 1))? uv0Out + sizeof(float)*2 : HK_NULL;
	char* qv1Out = (qv0Out && (newFormat->m_numTextureChannels > 1))? qv0Out + sizeof(hkUint16)*2 : HK_NULL;
	char* wOut = (newFormat->m_boneWeightOffset != HK_VFMT_NOT_PRESENT) ? ((char*)newVB) + newFormat->m_boneWeightOffset : HK_NULL; 
	char* idxOut = (newFormat->m_boneIndexOffset != HK_VFMT_NOT_PRESENT) ? ((char*)newVB) + newFormat->m_boneIndexOffset : HK_NULL;
	
	int strideIn = vb->m_format->m_stride;
	int strideOut = newFormat->m_stride;
	for (int vi=0; vi < vb->m_numVertexData; vi++)
	{
		// pos & norm
		*(hkVector4*)(posOut) = *(hkVector4*)(posIn);
		*(hkVector4*)(normOut) = *(hkVector4*)(normIn);
		posIn += strideIn;
		normIn += strideIn;
		posOut += strideOut;
		normOut += strideOut;

		// color
		if (colIn && colOut)
		{
			*(hkUint32*)(colOut) = *(hkUint32*)(colIn);
			colIn += strideIn;
			colOut += strideOut;
		}

		// Two sets of uv at most for now (aren't enough formats), and each can be of two types..
		if (uv0In && uv0Out) 
		{
			*(float*)(uv0Out) = *(float*)(uv0In); 
			*(float*)(uv0Out+4) = *(float*)(uv0In+4); 
			uv0In += strideIn;
			uv0Out += strideOut;
		}
		if (qv0In && qv0Out) 
		{
			*(hkUint16*)(qv0Out) = *(hkUint16*)(qv0In); 
			*(hkUint16*)(qv0Out+2) = *(hkUint16*)(qv0In+2); 
			qv0In += strideIn;
			qv0Out += strideOut;
		}
		if (uv1In && uv1Out) 
		{
			*(float*)(uv1Out) = *(float*)(uv1In); 
			*(float*)(uv1Out+4) = *(float*)(uv1In+4); 
			uv1In += strideIn;
			uv1Out += strideOut;
		}
		if (qv1In && qv1Out) 
		{
			*(hkUint16*)(qv1Out) = *(hkUint16*)(qv1In); 
			*(hkUint16*)(qv1Out+2) = *(hkUint16*)(qv1In+2); 
			qv1In += strideIn;
			qv1Out += strideOut;
		}

		// skinning
		if (wIn && wOut) 
		{
			*(hkUint32*)(wOut) = *(hkUint32*)(wIn); 
			wIn += strideIn;
			wOut += strideOut;
		}

		if (idxIn && idxOut)
		{
			*(hkUint32*)(idxOut) = *(hkUint32*)(idxIn); 
			idxIn += strideIn;
			idxOut += strideOut;
		}
	}
}

inline hkVector4& _vectByIndex( const char* data, int stride, int index )
{
	return *(hkVector4*)(data + stride*index);
}

inline float* _floatPtrByIndex( const char* data, int stride, int index )
{
	return (float*)(data + stride*index);
}


struct _TriangleTangentInfo
{
	hkxIndexBuffer* m_indexBuffer;
	int m_firstIndex;
	bool m_leftHanded;
	hkVector4 m_sVector;
	hkVector4 m_tVector;

	typedef unsigned short ThreeIndices[3];
	void getVertexIndices (ThreeIndices& vindexOut) const
	{
		unsigned short offset = (unsigned short) m_indexBuffer->m_vertexBaseOffset;

		if (m_indexBuffer->m_indices16)
		{
			vindexOut[0] = offset + m_indexBuffer->m_indices16[m_firstIndex];
			vindexOut[1] = offset + m_indexBuffer->m_indices16[m_firstIndex+1];
			vindexOut[2] = offset + m_indexBuffer->m_indices16[m_firstIndex+2];
		}
		else
		{
			vindexOut[0] = offset + (unsigned short) m_firstIndex;
			vindexOut[1] = vindexOut[0]+1;
			vindexOut[2] = vindexOut[0]+2;
		}
	}

	void setVertexIndices (const ThreeIndices& vindex)
	{
		unsigned short offset = (unsigned short) m_indexBuffer->m_vertexBaseOffset;

		if (m_indexBuffer->m_indices16)
		{
			m_indexBuffer->m_indices16[m_firstIndex] = vindex[0] - offset;
			m_indexBuffer->m_indices16[m_firstIndex+1] = vindex[1] - offset;
			m_indexBuffer->m_indices16[m_firstIndex+2] = vindex[2] - offset;
		}
		else
		{
			m_firstIndex = vindex[0] - offset;
		}

	}
};


static const hkReal gThreshold = -0.99f;

class _SplitVertexMap
{
	public:

		_SplitVertexMap()
		{

		}

		void findMirroredVertices (const hkArray<_TriangleTangentInfo>& triangles)
		{
			// Brute force approach by now
			for (int t1=0; t1<triangles.getSize(); t1++)
			{
				const _TriangleTangentInfo& tinfo1 = triangles[t1];
				unsigned short t1verts[3];
				tinfo1.getVertexIndices(t1verts);		

				for (int t2=t1+1; t2<triangles.getSize(); t2++)
				{
					const _TriangleTangentInfo& tinfo2 = triangles[t2];
					unsigned short t2verts[3];
					tinfo2.getVertexIndices(t2verts);		

					if (tinfo1.m_leftHanded != tinfo2.m_leftHanded)
					{
						// Candidate triangles (different handness)
						// Look for shared vertices
						for (int i1=0; i1<3; i1++)
						{
							for (int i2=0; i2<3; i2++)
							{
								if (t1verts[i1]==t2verts[i2])
								{
									const unsigned short originalVertex = t1verts[i1];

									// Shared vertex
									const int arrayPos = _findSplitVertex(originalVertex);
									if (arrayPos==-1) // New
									{
										SplitVertex splitVertex;
										splitVertex.m_originalIndex = originalVertex;
										splitVertex.m_leftHanded = tinfo1.m_leftHanded;
										splitVertex.m_mirroredTriangles.pushBack(t2);
										m_splitVertices.pushBack(splitVertex);
									}
									else
									{
										SplitVertex& splitVertex = m_splitVertices[arrayPos];

										if (tinfo1.m_leftHanded != splitVertex.m_leftHanded)
										{
											if (splitVertex.m_mirroredTriangles.indexOf(t1)==-1)
											{
												splitVertex.m_mirroredTriangles.pushBack(t1);
											}
										}	
										else
										{
											if (splitVertex.m_mirroredTriangles.indexOf(t2)==-1)
											{
												splitVertex.m_mirroredTriangles.pushBack(t2);
											}
										}
									}
								}
							}
						}

					}



				}
			}

			if (m_splitVertices.getSize()>0)
			{
				HK_REPORT("Splitting "<<m_splitVertices.getSize()<<" shared vertex(s)");
			}
			else
			{
				HK_REPORT("No vertices splitted");
			}

		}

		struct SplitVertex
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_EXPORT, SplitVertex );
			unsigned short m_originalIndex;
			hkArray<int> m_mirroredTriangles;
			bool m_leftHanded;

			SplitVertex () {}

			// we need an explicit copy constructor since the array's one is protected
			SplitVertex (const SplitVertex& other) 
			{

				m_originalIndex = other.m_originalIndex;
				m_mirroredTriangles = other.m_mirroredTriangles;
				m_leftHanded = other.m_leftHanded;
			}
		};

		hkObjectArray<SplitVertex> m_splitVertices;


	private:

		int _findSplitVertex (unsigned short originalIndex)
		{

			for (int i=0; i<m_splitVertices.getSize(); i++)
			{
				if (m_splitVertices[i].m_originalIndex == originalIndex) 
				{
					return i;
				}
			}

			return -1;
		}

};

static void _calculateTangentInfo ( const hkxMeshSection* meshSection , hkArray<_TriangleTangentInfo>& triangleInfoOut)
{
	// Temp storage:
	const hkxVertexBuffer* vb = meshSection->m_vertexBuffer;

	const char* vbDataIn = (char*)( vb->m_vertexData );

	const char* posIn = vbDataIn + vb->m_format->m_positionOffset;

	// XX: I take the 'last' map channel at the moment for computing the tangnets. Will create a dlg to spec or discover through materials. (the channel that mapps to a bump map / normal map etc)
	int uvOffset = (vb->m_format->m_numTextureChannels-1)*sizeof(float)*2;
	int qvOffset = (vb->m_format->m_numTextureChannels-1)*sizeof(hkUint16)*2;
	const char* uvIn = (vb->m_format->m_tFloatCoordOffset != HK_VFMT_NOT_PRESENT) ? vbDataIn + vb->m_format->m_tFloatCoordOffset + uvOffset: HK_NULL;
	const char* qvIn = (vb->m_format->m_tQuantizedCoordOffset != HK_VFMT_NOT_PRESENT) ? vbDataIn + vb->m_format->m_tQuantizedCoordOffset + qvOffset: HK_NULL;

	const int strideIn = vb->m_format->m_stride;
	const float quantizedUVMultipler = 1/3276.7f;  // as in the range [-10,10], quantized into a 16bit number for now.
	float w1[2]; 
	float w2[2]; 
	float w3[2]; 

	// For all triangles we know about:
	for (int pi=0; pi < meshSection->m_numIndexBuffers; ++pi)
	{
		const hkxIndexBuffer* ib = meshSection->m_indexBuffers[pi];
		if (ib->m_numIndices16 == 0)
			continue; // not handled yet (todo)

		const unsigned short* indices =  ib->m_indices16;
		const unsigned short vbOffset = (unsigned short)( ib->m_vertexBaseOffset );
		const int numIndices = ib->m_length;

		int curIndex = 0;			
		unsigned short curTri[3];

		if (ib->m_indexType == hkxIndexBuffer::INDEX_TYPE_TRI_STRIP)
		{
			// prime the strip
			curTri[1] = indices? indices[0] : (vbOffset);
			curTri[2] = indices? indices[1] : (vbOffset + 1);
			curIndex = 2;
		}

		while (curIndex < numIndices)
		{
			int firstIndex;
			if (ib->m_indexType == hkxIndexBuffer::INDEX_TYPE_TRI_LIST)
			{
				firstIndex = curIndex;
				curTri[0] = (unsigned short)( indices? indices[curIndex++] : (vbOffset + curIndex++) );
				curTri[1] = (unsigned short)( indices? indices[curIndex++] : (vbOffset + curIndex++) );
				curTri[2] = (unsigned short)( indices? indices[curIndex++] : (vbOffset + curIndex++) );
			}
			else // tri strip. TODO: Can optimise this perhaps as some verts already computed.
			{
				firstIndex = curIndex - 2;
				curTri[0] = curTri[1]; curTri[1] = curTri[2];
				curTri[2] = (unsigned short)( indices? indices[curIndex++] : (vbOffset + curIndex++) );
			}

			if ((curTri[0] == curTri[1]) ||
				(curTri[0] == curTri[2]) ||
				(curTri[1] == curTri[2]) )
				continue; // degenerate

			const hkVector4& v1 = _vectByIndex( posIn, strideIn, curTri[0]);
			const hkVector4& v2 = _vectByIndex( posIn, strideIn, curTri[1]);
			const hkVector4& v3 = _vectByIndex( posIn, strideIn, curTri[2]);

			// uv might not be in float form
			if (uvIn)
			{
				const float* uv1 = _floatPtrByIndex(uvIn, strideIn, curTri[0] );
				const float* uv2 = _floatPtrByIndex(uvIn, strideIn, curTri[1] );
				const float* uv3 = _floatPtrByIndex(uvIn, strideIn, curTri[2] );
				w1[0] = uv1[0]; w1[1] = uv1[1];
				w2[0] = uv2[0]; w2[1] = uv2[1];
				w3[0] = uv3[0]; w3[1] = uv3[1];
			}
			else 
			{
				const hkUint16* uv1 = (hkUint16*)_floatPtrByIndex(qvIn, strideIn, curTri[0] );
				const hkUint16* uv2 = (hkUint16*)_floatPtrByIndex(qvIn, strideIn, curTri[1] );
				const hkUint16* uv3 = (hkUint16*)_floatPtrByIndex(qvIn, strideIn, curTri[2] );
				w1[0] = uv1[0]*quantizedUVMultipler; w1[1] = uv1[1]*quantizedUVMultipler;
				w2[0] = uv2[0]*quantizedUVMultipler; w2[1] = uv2[1]*quantizedUVMultipler;
				w3[0] = uv3[0]*quantizedUVMultipler; w3[1] = uv3[1]*quantizedUVMultipler;
			}

			const hkSimdReal x1 = v2(0) - v1(0); //v2.x - v1.x;
			const hkSimdReal x2 = v3(0) - v1(0); //v3.x - v1.x;
			const hkSimdReal y1 = v2(1) - v1(1); //v2.y - v1.y;
			const hkSimdReal y2 = v3(1) - v1(1); //v3.y - v1.y;
			const hkSimdReal z1 = v2(2) - v1(2); //v2.z - v1.z;
			const hkSimdReal z2 = v3(2) - v1(2); //v3.z - v1.z;

			const hkSimdReal s1 = w2[0] - w1[0]; //w2.x - w1.x;
			const hkSimdReal s2 = w3[0] - w1[0]; //w3.x - w1.x;
			const hkSimdReal t1 = w2[1] - w1[1]; //w2.y - w1.y;
			const hkSimdReal t2 = w3[1] - w1[1]; //w3.y - w1.y;

			const hkSimdReal scale = (s1 * t2 - s2 * t1);
			const hkSimdReal r = hkMath::fabs(scale) > 0.0001f? hkSimdReal(1.0f) / scale : hkSimdReal(1.0f);

			hkVector4 sdir( (t2 * x1 - t1 * x2) * r,
				(t2 * y1 - t1 * y2) * r,
				(t2 * z1 - t1 * z2) * r );

			hkVector4 tdir( (s1 * x2 - s2 * x1) * r,
				(s1 * y2 - s2 * y1) * r,
				(s1 * z2 - s2 * z1) * r );

			const float threshold = 1e-10f;
			if (sdir.lengthSquared3()<threshold|| (tdir.lengthSquared3()<threshold))
			{
				// Constant U or V - ignore this triangle
				// Todo : count and report how many triangles ignored
				continue;
			}

			// normal
			hkVector4 normal;
			{
				hkVector4 edge1; edge1.setSub4(v2,v1);
				hkVector4 edge2; edge2.setSub4(v3,v1);
				normal.setCross(edge1, edge2);
			}

			normal.normalize3();
			sdir.normalize3();
			tdir.normalize3();

			hkVector4 sCrossT; sCrossT.setCross(sdir,tdir);

			_TriangleTangentInfo tinfo;
			tinfo.m_sVector = sdir;
			tinfo.m_tVector = tdir;
			float cross = sCrossT.dot3(normal);
			tinfo.m_leftHanded = cross<0.0f;
			tinfo.m_indexBuffer = meshSection->m_indexBuffers[pi];
			tinfo.m_firstIndex = firstIndex;
			triangleInfoOut.pushBack(tinfo);
		}
	}
}

static void _writeTangentData  ( const hkArray<_TriangleTangentInfo>& tangentInfo, hkxMeshSection* meshSection)
{
	const hkxVertexBuffer* vb = meshSection->m_vertexBuffer;
	hkArray<hkVector4> tan1(vb->m_numVertexData, hkVector4::getZero());
	hkArray<hkVector4> tan2(vb->m_numVertexData, hkVector4::getZero());

	const int stride = vb->m_format->m_stride;

	const char* vbDataIn = (const char*)( vb->m_vertexData );
	const char* normIn = vbDataIn + vb->m_format->m_normalOffset;

	char* vbDataOut = (char*)( vb->m_vertexData );
	char* tangentOut = vbDataOut + vb->m_format->m_tangentOffset;
	char* binormalOut = vbDataOut + vb->m_format->m_binormalOffset;

	// Add the tangents for each vertex
	{
		for (int tri=0; tri<tangentInfo.getSize(); tri++)
		{
			const _TriangleTangentInfo& tinfo = tangentInfo[tri];

			_TriangleTangentInfo::ThreeIndices triIndices;
			tinfo.getVertexIndices(triIndices);

			for (int tvert=0; tvert<3; tvert++)
			{
				tan1[ triIndices[tvert] ].add4( tinfo.m_sVector );
				tan2[ triIndices[tvert] ].add4( tinfo.m_tVector );
			}
		}
	}

	hkVector4 nDnt;
	hkVector4 nCt;

	for (int a = 0; a < vb->m_numVertexData; a++)
	{
		const hkVector4& n = _vectByIndex(normIn, stride, a);
		const hkVector4& t1 = tan1[a];
		const hkVector4& t2 = tan2[a];

		hkSimdReal nt1 = t1.lengthSquared3();
		hkSimdReal nt2 = t2.lengthSquared3();

		bool useT1 = nt1 > nt2;

		const hkVector4& t = ( useT1? t1 : t2 );
		const hkVector4& bt = ( useT1? t2 : t1 );

		hkVector4& tangent = _vectByIndex( useT1? tangentOut : binormalOut, stride, a);
		hkVector4& bitangent = _vectByIndex( useT1? binormalOut : tangentOut, stride, a);

		// Gram-Schmidt orthogonalize
		// tangent[a] = (t - n * (n * t)).Normalize();
		hkSimdReal nDt = n.dot3(t);
		nDnt.setMul4(nDt, n);
		tangent.setSub4(t, nDnt);
		hkSimdReal tlen = tangent.lengthSquared3();
		if (tlen < 1e-6f)
		{
			// EXP-525
			// The UV coordinates are constant so we can't create binormal/tangents based on them
			// Pick arbitrary orthogonal vectors
			hkVector4Util::calculatePerpendicularVector(n, tangent);
			bitangent.setCross(tangent,n);
		}
		else
		{
			tangent.mul4( hkMath::sqrtInverse(tlen) ); 
		}

		// Calculate handedness
		// tangent[a].w = (n % t * tan2[a] < 0.0F) ? -1.0F : 1.0F;
		nCt.setCross( n, t );
		hkSimdReal tw = nCt.dot3(bt);

		// Calculate the bitangent
		if (tw < 0)
		{
			bitangent.setCross( tangent, n );
		}
		else
		{
			bitangent.setCross( n, tangent );
		}
	}
}


hkxNode* _findFirstNodeRef( hkxNode* n, void* obj ); // defined the dialog cpp

static void _copyVertex (hkxVertexBuffer *vb, unsigned int indexFrom, unsigned int indexTo)
{
	const char* bufFrom = ((const char *) vb->m_vertexData) + indexFrom * vb->m_format->m_stride;
	char* bufTo = ((char *) vb->m_vertexData) + indexTo * vb->m_format->m_stride;

	hkString::memCpy(bufTo, bufFrom, vb->m_format->m_stride);
}

void hctCreateTangentsFilter::process( hkRootLevelContainer& data, bool batchMode )
{
	// EXP-370
	hkThreadMemory& sceneMemory = hkThreadMemory::getInstance();
	
	// Find the scene in the root level container
	hkxScene* scenePtr = reinterpret_cast<hkxScene*>( data.findObjectByType( hkxSceneClass.getName() ) );
	if (scenePtr == HK_NULL)
	{
		HK_WARN_ALWAYS(0xabbaa5f0, "No scene data found");
		return;
	}
	hkxScene& scene = *scenePtr;
	
	// The vertex formats which we may create as we need them
	hkxVertexFormat* tangentFormat = HK_NULL;
	hkxVertexFormat* simpleFormat = HK_NULL;
	hkxVertexFormat* skinFormat = HK_NULL;
	hkxVertexFormat* simpleFormatNoVColor = HK_NULL;
	hkxVertexFormat* skinFormatNoVColor = HK_NULL;
	
	// Find all meshes, and for those selected to be converted, add tangents and bi-tangents (aka bi-normals)
	for (int i=0; i < scene.m_numMeshes; ++i)
	{
		hkxMesh* mesh = scene.m_meshes[i];
		hkxNode* node = _findFirstNodeRef( scene.m_rootNode, mesh );

		if ( m_meshList.getSize() > 0 )
		{
			if (!node || !(node->m_name))
			{
				continue;
			}

			int j=0;
			for (; j < m_meshList.getSize(); ++j)
			{
				if (hkString::strCmp( node->m_name, m_meshList[j].cString()) == 0 )
				{
					break; // found
				}
			}

			if (j == m_meshList.getSize())
			{
				continue; // !found
			}
		}
		

		for (int s =0; s < mesh->m_numSections; ++s)
		{
			hkxMeshSection* section = mesh->m_sections[s];
			hkxVertexBuffer* vb = section->m_vertexBuffer;

			hkString title;
			if (node)
			{
				title.printf("Processing mesh \"%s\", section %d", node->m_name, s);
			}
			else
			{
				title.printf("Processign unnamed mesh, section %d", s);
			}
			HK_REPORT_SECTION_BEGIN(0xf1de98a2, title.cString());

			// If this section already has tangents then skip it
			if( (vb->m_format->m_binormalOffset != HK_VFMT_NOT_PRESENT)
				|| (vb->m_format->m_tangentOffset != HK_VFMT_NOT_PRESENT) )
			{
				HK_REPORT("*Tangent information already present, ignoring*");
				HK_REPORT_SECTION_END();
				continue;
			}
			
			// If the current format has no texture coords we can't create tangents
			if( (vb->m_format->m_tFloatCoordOffset == HK_VFMT_NOT_PRESENT)
				&& (vb->m_format->m_tQuantizedCoordOffset == HK_VFMT_NOT_PRESENT) )
			{
				HK_WARN_ALWAYS(0xabba98bb, "No UV texture coordinates found, can't generate tangents");
				HK_REPORT_SECTION_END();
				continue;
			}
			
			// Start by looking at tangent information for the current vertex buffer
			hkArray<_TriangleTangentInfo> tangentInfo;
			_calculateTangentInfo(section, tangentInfo);

			// Then look out for seams that need to be splitted (EXP-582)
			_SplitVertexMap splitVertexMap;
			
			if (m_splitVertices)
			{
				splitVertexMap.findMirroredVertices (tangentInfo);
			}

			const int numExtraVertices = splitVertexMap.m_splitVertices.getSize();


			// The format may already allow tangents. If so we allocate a new format
			// of the same type and fill in the tangent data, since we don't want to
			// affect unlisted meshes which share the same format

			const hkClass* newFormatKlass;
			hkxVertexFormat* newFormat = HK_NULL;

			const char* formatKlassName = vb->m_vertexDataClass->getName();
			const bool wantVColor = vb->m_format->m_colorOffset != HK_VFMT_NOT_PRESENT;

			bool needToCopyVertexBuffer = true;

			// P4N4T4B4W4I4Q4 - Already has space for tangents, but not being used
			if (hkString::strCmp( formatKlassName, hkxVertexP4N4T4B4W4I4Q4Class.getName() ) == 0 )
			{
				if( !tangentFormat )
				{
					tangentFormat = (hkxVertexFormat*)sceneMemory.alignedAllocate(16, sizeof(hkxVertexFormat), HK_MEMORY_CLASS_EXPORT);
					hkString::memCpy( tangentFormat, vb->m_format, sizeof(hkxVertexFormat) );
					tangentFormat->m_binormalOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4Q4, m_binormal);
					tangentFormat->m_tangentOffset = HK_OFFSET_OF(hkxVertexP4N4T4B4W4I4Q4, m_tangent);
				}
				newFormat = tangentFormat;
				newFormatKlass = &hkxVertexP4N4T4B4W4I4Q4Class;
				needToCopyVertexBuffer = numExtraVertices>0; // we only need duplication if the number of vertices is increased

			}
			else if (hkString::strCmp( formatKlassName, hkxVertexP4N4C1T2Class.getName() ) == 0 )
			{
				newFormatKlass = &hkxVertexP4N4T4B4C1T2Class;
				if (wantVColor)
				{
					if (!simpleFormat)
					{
						simpleFormat = (hkxVertexFormat*)sceneMemory.alignedAllocate(16, sizeof(hkxVertexFormat), HK_MEMORY_CLASS_EXPORT);
						_createSimpleFormat( simpleFormat, true );
					}
					newFormat = simpleFormat;
				}
				else
				{
					if (!simpleFormatNoVColor)
					{
						simpleFormatNoVColor = (hkxVertexFormat*)sceneMemory.alignedAllocate(16, sizeof(hkxVertexFormat), HK_MEMORY_CLASS_EXPORT);
						_createSimpleFormat( simpleFormatNoVColor, false );
					}
					newFormat = simpleFormatNoVColor;
				}
			}
			else if (hkString::strCmp( formatKlassName, hkxVertexP4N4W4I4C1Q2Class.getName() ) == 0)
			{
				newFormatKlass = &hkxVertexP4N4T4B4W4I4C1Q2Class;
				if (wantVColor)
				{
					if (!skinFormat)
					{
						skinFormat = (hkxVertexFormat*)sceneMemory.alignedAllocate(16, sizeof(hkxVertexFormat), HK_MEMORY_CLASS_EXPORT);
						_createSkinnedFormat( skinFormat, true );
					}
					newFormat = skinFormat;
				}
				else
				{
					if (!skinFormatNoVColor)
					{
						skinFormatNoVColor = (hkxVertexFormat*)sceneMemory.alignedAllocate(16, sizeof(hkxVertexFormat), HK_MEMORY_CLASS_EXPORT);
						_createSkinnedFormat( skinFormatNoVColor, false );
					}
					newFormat = skinFormatNoVColor;
				}
			}
			else 
			{
				continue; // not a known concrete class
			}


			if (needToCopyVertexBuffer)
			{
				const int originalNumberOfVertices = vb->m_numVertexData;
				const int newNumberOfVertices = originalNumberOfVertices + numExtraVertices;

				void* newVBData = sceneMemory.alignedAllocate(16, newFormat->m_stride * newNumberOfVertices, HK_MEMORY_CLASS_EXPORT);
				hkString::memSet(newVBData, 0, newFormat->m_stride * newNumberOfVertices);
				_CopyVertexData( section, newFormat, (char*)newVBData );
				vb->m_vertexData = newVBData; // whatever alloced the old vb will clean it up later.
				vb->m_format = newFormat;
				vb->m_vertexDataClass = newFormatKlass;

				for (int vi=0; vi<splitVertexMap.m_splitVertices.getSize(); vi++)
				{
					const _SplitVertexMap::SplitVertex& splitVertex = splitVertexMap.m_splitVertices[vi];
					const unsigned short oldIndex = splitVertex.m_originalIndex;
					const unsigned short newIndex = (unsigned short) (originalNumberOfVertices +  vi);

					_copyVertex(vb, oldIndex, newIndex);

					// Now replace the indices in the mirrored triangles
					for (int ti=0; ti<splitVertex.m_mirroredTriangles.getSize(); ti++)
					{
						_TriangleTangentInfo& mirroredTri = tangentInfo[splitVertex.m_mirroredTriangles[ti]];
						_TriangleTangentInfo::ThreeIndices originalIndices;
						mirroredTri.getVertexIndices(originalIndices);

						_TriangleTangentInfo::ThreeIndices newIndices;
						for (int j=0; j<3; j++)
						{
							if (originalIndices[j]==oldIndex)
							{
								newIndices[j] = newIndex;
							}
							else
							{
								newIndices[j] = originalIndices[j];
							}
						}

						mirroredTri.setVertexIndices(newIndices);
					}
				}

				vb->m_numVertexData = newNumberOfVertices;

			}
			else
			{
				vb->m_format = newFormat;
			}

			_writeTangentData(tangentInfo, section);

			HK_REPORT("Tangent information generated");

			HK_REPORT_SECTION_END();
		}

	}
}

void hctCreateTangentsFilter::setOptions( const void* optionData, int optionDataSize, unsigned int version ) 
{
	hctCreateTangentsOptions defaultOptions;
	hctCreateTangentsOptions* options = & defaultOptions;

	// Check if the options have been saved as raw data.
	if ( version < HCT_FILTER_VERSION(1,0,1) )
	{
		options->m_meshes = (char*)optionData;
	}
	else 
	{
		// Get the options from the XML data.
		if ( hctFilterUtils::readOptionsXml( optionData, optionDataSize, m_optionsBuf, hctCreateTangentsOptionsClass ) == HK_SUCCESS )
		{
			options = reinterpret_cast<hctCreateTangentsOptions*>( m_optionsBuf.begin() );
		}
		else
		{
			HK_WARN_ALWAYS( 0xabba75bb, "The XML for the " << g_createTangentsDesc.getShortName() << " option data could not be loaded." );
			return;
		}

		if ( version < HCT_FILTER_VERSION(1,0,2) )
		{
			options->m_splitVertices = false;
		}
	}

	m_splitVertices = options->m_splitVertices;

	// Set up the array of meshes to generate tangents and binormals for.
	hctFilterUtils::createArrayFromDelimitedString( m_meshList, options->m_meshes, ';' );
}

int hctCreateTangentsFilter::getOptionsSize() const
{
	hctCreateTangentsOptions options;

	hkString allMeshes;
	for ( int i = 0; i < m_meshList.getSize(); ++i )
	{
		allMeshes += m_meshList[i];
		allMeshes += ";";
	}
	options.m_meshes = const_cast<char*>( allMeshes.cString() );
	options.m_splitVertices = m_splitVertices;

	hctFilterUtils::writeOptionsXml( hctCreateTangentsOptionsClass, &options, m_optionsBuf, g_createTangentsDesc.getShortName() );

	return m_optionsBuf.getSize();
}

void hctCreateTangentsFilter::getOptions(void* optionData) const
{
	hkString::memCpy(optionData, m_optionsBuf.begin(), m_optionsBuf.getSize());
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
