/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/SceneExport/hctSceneExport.h> // PCH
#include <ContentTools/Common/SceneExport/Userchannel/hctUserChannelUtil.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/Channels/hkxVertexSelectionChannel.h>
#include <Common/SceneData/Mesh/Channels/hkxVertexFloatDataChannel.h>
#include <Common/SceneData/Mesh/Channels/hkxTriangleSelectionChannel.h>

// Add a new user channel to the mesh
void hctUserChannelUtil::addGlobalChannel (const hctUserChannelUtil::GlobalChannel& globalChannel)
{
	m_globalChannels.pushBack(globalChannel);
}

// Register a new section in the mesh and provide a map between indices in the section and indices in the original mesh
void hctUserChannelUtil::registerSection (const hctUserChannelUtil::SectionToGlobalMap& sectionMap)
{
	m_sectionMaps.pushBack(sectionMap);
}

const char* _trackedStrDup (hctFilterMemoryTracker* memory, const char*str)
{
	char *copy = (char*) memory->allocate((hkString::strLen(str)+1), HK_MEMORY_CLASS_EXPORT);
	hkString::strCpy(copy, str);
	return copy;
}

// do the work
void hctUserChannelUtil::storeChannelsInMesh (hkxMesh* theMesh,  class hctFilterMemoryTracker* memory)
{
	if (theMesh->m_numSections != m_sectionMaps.getSize())
	{
		HK_WARN_ALWAYS(0xabba0000, "Internal error - inconsistent number of mesh sections");
		return;
	}

	const int numChannels = m_globalChannels.getSize();

	if ((theMesh->m_numSections == 0) || (numChannels == 0))
	{
		// Nothing to do
		return;
	}


	// Initialize the arrays
	{
		// Channel info array in hkxmesh
		theMesh->m_numUserChannelInfos = numChannels;
		theMesh->m_userChannelInfos = (hkxMesh::UserChannelInfo*) ( memory->alignedAllocate( sizeof(char*), sizeof(hkxMesh::UserChannelInfo) * numChannels, HK_MEMORY_CLASS_EXPORT) );
		hkString::memSet(theMesh->m_userChannelInfos, 0, sizeof(hkxMesh::UserChannelInfo)*numChannels);

		// Userchannels (variants) in each section
		for (int si=0; si<theMesh->m_numSections; si++)
		{
			hkxMeshSection* section = theMesh->m_sections[si];
			section->m_numUserChannels = numChannels;
			section->m_userChannels = (hkVariant*)( memory->alignedAllocate( sizeof(char*), sizeof(hkVariant)*numChannels, HK_MEMORY_CLASS_EXPORT) );
			hkString::memSet(section->m_userChannels, 0, sizeof(hkVariant) * numChannels);
		}
	}

	// Now, process each channel
	for (int ci=0; ci<m_globalChannels.getSize(); ci++)
	{
		const hctUserChannelUtil::GlobalChannel& channel = m_globalChannels[ci];

		// Process each section
		for (int si=0; si<theMesh->m_numSections; si++)
		{
			switch (channel.m_channelType)
			{
				case CT_VERTEX_SELECTION:
					{
						processVertexSelection (memory, ci, si, theMesh);
						break;
					}
				case CT_FACE_SELECTION:
					{
						processFaceSelection(memory, ci, si, theMesh);
						break;
					}
				case CT_VERTEX_FLOAT:
					{
						processVertexFloatData(memory, ci, si, theMesh);
						break;
					}
				default:
					{
						HK_ASSERT(0xabbae66d, "Unsupported mesh channel type");
						continue;
					}
			}

		}

		// And set the channel info
		theMesh->m_userChannelInfos[ci].m_name = _trackedStrDup(memory, channel.m_channelName.cString());
		theMesh->m_userChannelInfos[ci].m_className = _trackedStrDup(memory, theMesh->m_sections[0]->m_userChannels[ci].m_class->getName());
	}

}

void hctUserChannelUtil::processVertexSelection (class hctFilterMemoryTracker* memory, int channelNumber, int sectionNumber, hkxMesh* theMesh) const
{
	const hctUserChannelUtil::GlobalChannel& channel = m_globalChannels[channelNumber];
	const hkxMeshSection* section = theMesh->m_sections[sectionNumber];			
	const SectionToGlobalMap& sectionMap = m_sectionMaps[sectionNumber];
	hkVariant& sectionChannel = section->m_userChannels[channelNumber];

	hkxVertexSelectionChannel* selectionChannel = (hkxVertexSelectionChannel*)( memory->alignedAllocate( sizeof(char*), sizeof(hkxVertexSelectionChannel), HK_MEMORY_CLASS_EXPORT) );

	hkArray<hkInt32> sectionIndices;
	for (int i=0; i<channel.m_channelData.getSize(); i++)
	{
		int selectedGlobalVertexIndex = channel.m_channelData[i].m_index;

		// Now see if that vertex is selected in this section (it could be many times)
		for (int j=0; j<sectionMap.m_sectionVertexIdToGlobalVertexId.getSize(); j++)
		{
			if (sectionMap.m_sectionVertexIdToGlobalVertexId[j] == selectedGlobalVertexIndex)
			{
				sectionIndices.pushBack(j);
			}
		}
	}
	
	// Copy the array
	const int numSelVerts = sectionIndices.getSize();
	selectionChannel->m_numSelectedVertices = numSelVerts;
	selectionChannel->m_selectedVertices = 	(hkInt32*) (memory->allocate(sizeof(hkInt32) * numSelVerts, HK_MEMORY_CLASS_EXPORT));
	hkString::memCpy(selectionChannel->m_selectedVertices, sectionIndices.begin(), numSelVerts*sizeof(hkInt32));

	sectionChannel.m_class = &hkxVertexSelectionChannelClass;
	sectionChannel.m_object = selectionChannel;
}

void hctUserChannelUtil::processFaceSelection (class hctFilterMemoryTracker* memory, int channelNumber, int sectionNumber, hkxMesh* theMesh) const
{
	const hctUserChannelUtil::GlobalChannel& channel = m_globalChannels[channelNumber];
	const hkxMeshSection* section = theMesh->m_sections[sectionNumber];			
	const SectionToGlobalMap& sectionMap = m_sectionMaps[sectionNumber];
	hkVariant& sectionChannel = section->m_userChannels[channelNumber];

	hkxTriangleSelectionChannel* selectionChannel = (hkxTriangleSelectionChannel*)( memory->alignedAllocate( sizeof(char*), sizeof(hkxTriangleSelectionChannel), HK_MEMORY_CLASS_EXPORT) );

	hkArray<hkInt32> sectionIndices;
	for (int i=0; i<channel.m_channelData.getSize(); i++)
	{
		int selectedGlobalFaceIndex = channel.m_channelData[i].m_index;

		// Now see if that vertex is selected in this section (it could be many times)
		for (int j=0; j<sectionMap.m_sectionTriangleIdToGlobalFaceId.getSize(); j++)
		{
			if (sectionMap.m_sectionTriangleIdToGlobalFaceId[j] == selectedGlobalFaceIndex)
			{
				sectionIndices.pushBack(j);
			}
		}
	}

	// Copy the array
	const int numSelTriangles = sectionIndices.getSize();
	selectionChannel->m_numSelectedTriangles = numSelTriangles;
	selectionChannel->m_selectedTriangles = (hkInt32*) (memory->allocate(sizeof(hkInt32) * numSelTriangles, HK_MEMORY_CLASS_EXPORT));
	hkString::memCpy(selectionChannel->m_selectedTriangles, sectionIndices.begin(), numSelTriangles*sizeof(hkInt32));

	sectionChannel.m_class = &hkxTriangleSelectionChannelClass;
	sectionChannel.m_object = selectionChannel;
}

void hctUserChannelUtil::processVertexFloatData (class hctFilterMemoryTracker* memory, int channelNumber, int sectionNumber, hkxMesh* theMesh) const
{
	const hctUserChannelUtil::GlobalChannel& channel = m_globalChannels[channelNumber];
	const hkxMeshSection* section = theMesh->m_sections[sectionNumber];			
	const SectionToGlobalMap& sectionMap = m_sectionMaps[sectionNumber];
	hkVariant& sectionChannel = section->m_userChannels[channelNumber];

	hkxVertexFloatDataChannel* floatChannel = (hkxVertexFloatDataChannel*)( memory->alignedAllocate( sizeof(char*), sizeof(hkxVertexFloatDataChannel), HK_MEMORY_CLASS_EXPORT) );
	hkString::memSet(floatChannel, 0, sizeof(hkxVertexFloatDataChannel));

	hkArray<float> sectionFloats;
	for (int i=0; i<sectionMap.m_sectionVertexIdToGlobalVertexId.getSize(); i++)
	{
		const int globalIdx = sectionMap.m_sectionVertexIdToGlobalVertexId[i];
		const float value = channel.m_channelData[globalIdx].m_float;
		sectionFloats.pushBack(value);
	}

	// Copy the array
	const int numFloats = sectionFloats.getSize();
	floatChannel->m_numPerVertexFloats = numFloats;
	floatChannel->m_perVertexFloats = (float*) (memory->allocate(sizeof(float) * numFloats, HK_MEMORY_CLASS_EXPORT));
	hkString::memCpy(floatChannel->m_perVertexFloats, sectionFloats.begin(), numFloats*sizeof(float));

	sectionChannel.m_class = &hkxVertexFloatDataChannelClass;
	sectionChannel.m_object = floatChannel;

}

void hctUserChannelUtil::clear()
{
	m_globalChannels.clear();
	m_sectionMaps.clear();
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
