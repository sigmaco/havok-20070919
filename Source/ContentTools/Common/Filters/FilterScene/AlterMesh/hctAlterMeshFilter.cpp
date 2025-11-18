/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>
#include <ContentTools/Common/Filters/FilterScene/AlterMesh/hctAlterMeshFilter.h>

#include <Common/Base/System/Io/Reader/Memory/hkMemoryStreamReader.h>
#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>

#include <Common/SceneData/Graph/hkxNode.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Mesh/hkxVertexFormat.h>
#include <Common/SceneData/Mesh/hkxIndexBuffer.h>

hctAlterMeshFilterDesc g_alterMeshDesc;

hctAlterMeshFilter::hctAlterMeshFilter(const hctFilterManagerInterface* owner)
:	hctFilterInterface (owner),
	m_optionsDialog(NULL)
{
	m_options.m_removeIndices = true;
}
	
hctAlterMeshFilter::~hctAlterMeshFilter()
{

}

void hctAlterMeshFilter::setOptions(const void* optionData, int optionDataSize, unsigned int version)
{	
	// Check if the options have been saved as raw data.
	if ( version < HCT_FILTER_VERSION(1,0,1) )
	{
		hkString::memCpy( &m_options, optionData, optionDataSize );
		return;
	}
	else if ( version != g_alterMeshDesc.getFilterVersion() )
	{
		HK_WARN_ALWAYS( 0xabba7ade, "The " << g_alterMeshDesc.getShortName() << " option data was of an incompatible version and could not be loaded." );
		return;
	}

	// Get the options from the XML data.
	if ( hctFilterUtils::readOptionsXml( optionData, optionDataSize, m_optionsBuf, hctAlterMeshOptionsClass ) == HK_SUCCESS )
	{
		hctAlterMeshOptions* options = reinterpret_cast<hctAlterMeshOptions*>( m_optionsBuf.begin() );

		m_options.m_removeIndices = options->m_removeIndices;
	}
	else
	{
		HK_WARN_ALWAYS( 0xabba482b, "The XML for the " << g_alterMeshDesc.getShortName() << " option data could not be loaded." );
		return;
	}
}

int hctAlterMeshFilter::getOptionsSize() const
{
	hctFilterUtils::writeOptionsXml( hctAlterMeshOptionsClass, &m_options, m_optionsBuf, g_alterMeshDesc.getShortName() );
	return m_optionsBuf.getSize();
}

void hctAlterMeshFilter::getOptions(void* optionData) const
{
	// can memcpy as the options have no strings, char* etc.
	hkString::memCpy( optionData, m_optionsBuf.begin(), m_optionsBuf.getSize() );
}

inline hkInt16 _getIndex16( hkxIndexBuffer* ib, int i )
{
	return (hkInt16)(ib->m_vertexBaseOffset + ( ib->m_indices16? ib->m_indices16[i] : i )); 
}

inline hkInt32 _getIndex32( hkxIndexBuffer* ib, int i )
{
	return (hkInt32)(ib->m_vertexBaseOffset + ( ib->m_indices32? ib->m_indices32[i] : i )); 
}

void hctAlterMeshFilter::process( hkRootLevelContainer& data, bool batchMode )
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

	// Remove Index Buffers 
	// It removes the indices, but leaves the index buffer as they contain the triangle storage (list, strip, etc)
	// so become an offset into the vb instead of a buffer itself.
	if (m_options.m_removeIndices)
	{
		for (int i=0; i < scene.m_numMeshes; ++i)
		{
		
			hkxMesh* curMesh = scene.m_meshes[i];
			for (int j=0; j < curMesh->m_numSections; ++j)
			{
				hkxMeshSection* section = curMesh->m_sections[j];
				hkxVertexBuffer* origVB = section->m_vertexBuffer;
				if (!origVB) continue; // dodgy

				int unwoundVerts = 0;
				bool trivialBuffers = true;
				int ib;
				for (ib=0; ib < section->m_numIndexBuffers; ++ib)
				{
					unwoundVerts += section->m_indexBuffers[ib]->m_length;
					trivialBuffers &= (section->m_indexBuffers[ib]->m_indices16 == HK_NULL) && (section->m_indexBuffers[ib]->m_indices32 == HK_NULL);
				}

				if (trivialBuffers || (unwoundVerts < 1)) // all tivial (no actual indices) or no buffers at all
					continue; // next section

				// allocate enough space for all the verts
				int vertexSize = origVB->m_format->m_stride;
				char* origVbuf = (char*) origVB->m_vertexData;
				char* vbuf = (char*)( sceneMemory.alignedAllocate(16, vertexSize * unwoundVerts, HK_MEMORY_CLASS_EXPORT) );
				char* curVertex = vbuf;
				int curVertexIndex = 0;
				for (ib=0; ib < section->m_numIndexBuffers; ++ib)
				{
					hkxIndexBuffer* indexBuf = section->m_indexBuffers[ib];
					bool sixteenBit = (indexBuf->m_indices16 != HK_NULL);
					unsigned int numI = section->m_indexBuffers[ib]->m_length;
					for (hkUint32 ci=0; ci < numI; ++ci)
					{
						char* origVert = origVbuf + (( sixteenBit? _getIndex16(indexBuf, ci) : _getIndex32(indexBuf, ci) ) * vertexSize );
						hkString::memCpy(curVertex, origVert, vertexSize); // copy the vert
						curVertex += vertexSize;
					}

					indexBuf->m_vertexBaseOffset = curVertexIndex;
					curVertexIndex += numI;
					indexBuf->m_indices16 = HK_NULL; // previous owner will deallocate old buf
					indexBuf->m_numIndices16 = 0; 
					indexBuf->m_indices32 = HK_NULL; // previous owner will deallocate old buf
					indexBuf->m_numIndices32 = 0; 
				}

				// set the vb ptrs
				section->m_vertexBuffer->m_vertexData = vbuf; // previous owner will deallocate old buf
				section->m_vertexBuffer->m_numVertexData = unwoundVerts;
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
