/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>
#include <ContentTools/Common/Filters/FilterScene/FindInstances/hctFindInstancesFilter.h>

#include <Common/Base/System/Io/Reader/Memory/hkMemoryStreamReader.h>
#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>

#include <Common/SceneData/Graph/hkxNode.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Mesh/hkxVertexFormat.h>
#include <Common/SceneData/Skin/hkxSkinBinding.h>


hctFindInstancesFilterDesc g_findInstancesDesc;

hctFindInstancesFilter::hctFindInstancesFilter(const hctFilterManagerInterface* owner)
:	hctFilterInterface (owner)
{

}
	
hctFindInstancesFilter::~hctFindInstancesFilter()
{

}

static void _shallowMeshCompare( const hkxScene& scene, hkObjectArray< hkArray<hkxMesh*> >& setsOut )
{
	setsOut.clear();
	
    hkArray<hkxMesh*> remainingMeshes(scene.m_numMeshes);
	for( int i=0; i<scene.m_numMeshes; ++i )
	{
		remainingMeshes[i] = scene.m_meshes[i];
	}
	
	while( remainingMeshes.getSize() > 0 )
	{
		// Move the first mesh into a new set
		hkArray<hkxMesh*> set(1,remainingMeshes[0]);
		remainingMeshes.removeAt(0);
		
		// Look for any loosely matching meshes
		hkxMesh* meshA = set[0];
		for( int i=0; i<remainingMeshes.getSize(); ++i )
		{
			hkxMesh* meshB = remainingMeshes[i];
			
			// Skip if already instanced
			if( meshA == meshB ) continue;
			
			// Need same number of sections
			if( meshA->m_numSections != meshB->m_numSections ) continue;
			
			// Need same number of vertices in each section
			int k;
			for( k=0; k<meshA->m_numSections; ++k )
			{
				if( meshA->m_sections[k]->m_vertexBuffer->m_numVertexData
					!= meshB->m_sections[k]->m_vertexBuffer->m_numVertexData )
				{
					break;
				}
			}
			if( k != meshA->m_numSections )
			{
				continue;
			}
			
			// Store it in the set
			set.pushBack( meshB );
			remainingMeshes.removeAtAndCopy(i--);
		}
		
		// Need at least 2 matches
		if( set.getSize() >= 2 )
		{
			setsOut.pushBack( set );
		}
	}
}


static inline void _roundOff( float& val )
{
	float product = 100 * val;
	int whole = (int)product;
	float fraction = product - whole;
	if( 2*fraction >= 1 )
	{
		val = (whole + 1)/100.0f;
	}
	else
	{
		val = whole/100.0f;
	}
}

static void _roundOffMeshFloats( hkxMesh* mesh )
{
	for( int i=0; i<mesh->m_numSections; ++i )
	{
		hkxVertexBuffer* vb = mesh->m_sections[i]->m_vertexBuffer;
		hkxVertexFormat* vf = vb->m_format;
		
		// Gather a set of offsets to floating point values
		hkArray<int> floatOffsets;
		{
			if( vf->m_positionOffset != HK_VFMT_NOT_PRESENT )
			{
				for( int k=0; k<4; ++k ) floatOffsets.pushBack(vf->m_positionOffset+k);
			}
			if( vf->m_normalOffset != HK_VFMT_NOT_PRESENT )
			{
				for( int k=0; k<4; ++k ) floatOffsets.pushBack(vf->m_normalOffset+k);
			}
			if( vf->m_tangentOffset != HK_VFMT_NOT_PRESENT )
			{
				for( int k=0; k<4; ++k ) floatOffsets.pushBack(vf->m_tangentOffset+k);
			}
			if( vf->m_binormalOffset != HK_VFMT_NOT_PRESENT )
			{
				for( int k=0; k<4; ++k ) floatOffsets.pushBack(vf->m_binormalOffset+k);
			}
			if( vf->m_tFloatCoordOffset != HK_VFMT_NOT_PRESENT )
			{
				for( int k=0; k<2; ++k ) floatOffsets.pushBack(vf->m_tFloatCoordOffset+k);
			}
		}
		
		// Roundoff the floats for each vertex
		char* curPtr = (char*)vb->m_vertexData;
		const int stride = vf->m_stride;
		for( int j=0; j<vb->m_numVertexData; ++j, curPtr += stride )
		{
			for( int k=0; k<floatOffsets.getSize(); ++k )
			{
				_roundOff( *(float*)( curPtr + floatOffsets[k] ) );
			}
		}
		
		// Note: any mesh material should be instanced by the exporter already
		// so we don't need to go and roundoff the floats there
	}
}


static void _deepMeshCompare( const hkArray<hkxMesh*>& meshes, const hctFilterClassRegistry& classReg, hkObjectArray< hkArray<hkxMesh*> >& setsOut )
{
	setsOut.clear();
	
	// Deep copy each mesh in the set
	hkArray<char>* deepMeshData = new hkArray<char>[ meshes.getSize() ];
	hkArray<int> remainingIndices( meshes.getSize() );
	for( int i=0; i<meshes.getSize(); ++i )
	{
		hctFilterUtils::deepCopyObject( classReg, meshes[i], &hkxMeshClass, deepMeshData[i] );
		remainingIndices[i] = i;
	}
	
	// Find any subsets which have equal binary length
	hkObjectArray< hkArray<int> > subsets;
	while( remainingIndices.getSize() > 0 )
	{
		// Move first index into a new set
		hkArray<int> subset(1,remainingIndices[0]);
		remainingIndices.removeAt(0);
		
		// Look for other indices with same binary size
		hkArray<char>& dataA = deepMeshData[ subset[0] ];
		for( int i=0; i<remainingIndices.getSize(); ++i )
		{
			hkArray<char>& dataB = deepMeshData[ remainingIndices[i] ];
			if( dataA.getSize() != dataB.getSize() )
			{
				continue;
			}
			
			subset.pushBack( remainingIndices[i] );
			remainingIndices.removeAtAndCopy(i--);
		}
		
		// Need at least 2 matches
		if( subset.getSize() >= 2 )
		{
			subsets.pushBack( subset );
		}
	}
	
	// Deep compare the subsets
	for( int i=0; i<subsets.getSize(); ++i )
	{
		hkArray<int> subset;
		subset.insertAt( 0, subsets[i].begin(), subsets[i].getSize() );
		int binarySize = deepMeshData[ subset[0] ].getSize();
		
        // Fixup the data by extracting each mesh into a common memory space to equate pointers,
		// and rounding off float values to avoid numerical error
		hkArray<char> tempMeshData( binarySize );
        for( int j=0; j<subset.getSize(); ++j )
		{
			hkxMesh* mesh = (hkxMesh*)hctFilterUtils::deepCopyObject( classReg, meshes[subset[j]], &hkxMeshClass, tempMeshData );
			_roundOffMeshFloats( mesh );
			deepMeshData[ subset[j] ].clear();
			deepMeshData[ subset[j] ].insertAt( 0, tempMeshData.begin(), tempMeshData.getSize() );
		}
		
		// Gather any matching binary sets
		while( subset.getSize() > 0 )
		{
			int indexA = subset[0];
			hkArray<hkxMesh*> meshSet(1, meshes[indexA] );
			subset.removeAt(0);
			
			for( int j=0; j<subset.getSize(); ++j )
			{
				int indexB = subset[j];
				if( hkString::memCmp( (void*)deepMeshData[indexA].begin(), (void*)deepMeshData[indexB].begin(), binarySize ) == 0 )
				{
					meshSet.pushBack( meshes[indexB] );
					subset.removeAtAndCopy(j--);
				}
			}
			
			// Need at least 2 matches
			if( meshSet.getSize() >= 2 )
			{
				setsOut.pushBack( meshSet );
			}
		}
	}
	
	delete [] deepMeshData;
}


static void _updateAllInstancedMeshes( hkxNode* node, const hkPointerMap<hkxMesh*, hkxMesh*>& instanceMap )
{
	if( node->m_object.m_object && 
		hkString::strCmp( node->m_object.m_class->getName(), hkxMeshClass.getName() ) == 0 )
	{
		hkxMesh*& mesh = (hkxMesh*&)node->m_object.m_object;
		if( instanceMap.hasKey( mesh ) )
		{
			instanceMap.get( mesh, &mesh );
		}
	}
	
	for (int c=0; c < node->m_numChildren; ++c)
	{
		_updateAllInstancedMeshes( node->m_children[c], instanceMap );
	}
}

void hctFindInstancesFilter::process( hkRootLevelContainer& data, bool batchMode)
{
	// Find the scene in the root level container
	hkxScene* scenePtr = reinterpret_cast<hkxScene*>( data.findObjectByType( hkxSceneClass.getName() ) );
	if( scenePtr == HK_NULL )
	{
		HK_WARN_ALWAYS (0xabbaa5f1, "No scene data found");
		return;
	}
	hkxScene& scene = *scenePtr;
	

	// Create an instance map
	hkPointerMap<hkxMesh*, hkxMesh*> instanceMap;
	{
		// Shallow compare all meshes into loosely matching sets
		hkObjectArray< hkArray<hkxMesh*> > meshSets;
		_shallowMeshCompare( scene, meshSets );
		
		// Binary compare the elements in each subset
		for( int i=0; i<meshSets.getSize(); ++i )
		{
			hkObjectArray< hkArray<hkxMesh*> > meshSubsets;
			_deepMeshCompare( meshSets[i], m_filterManager->getFilterClassRegistry(), meshSubsets );
			
			for( int j=0; j<meshSubsets.getSize(); ++j )
			{
				// Map all instances to the first one
				hkArray<hkxMesh*>& instancedMeshes = meshSubsets[j];
				for( int k=1; k<instancedMeshes.getSize(); ++k )
				{
					instanceMap.insert( instancedMeshes[k], instancedMeshes[0] );
				}
			}
		}
	}
	
	// Update the scene data using the instance map
	if( instanceMap.getSize() > 0 )
	{
		// Alter any instanced meshes in the node graph
		_updateAllInstancedMeshes( scene.m_rootNode, instanceMap );

		// Alter any instanced meshes in the skin bindings
		for( int i=0; i<scene.m_numSkinBindings; ++i )
		{
			hkxMesh* mesh = scene.m_skinBindings[i]->m_mesh;
			if( instanceMap.hasKey( mesh ) )
			{
				instanceMap.get( mesh, &mesh );
			}
		}
		
		// Remove any instanced meshes from the scene container
		hkArray<hkxMesh*> meshes( scene.m_meshes, scene.m_numMeshes, scene.m_numMeshes );
		for( int i=0; i<meshes.getSize(); ++i )
		{
			if( instanceMap.hasKey( meshes[i] ) )
			{
				meshes.removeAtAndCopy(i--);
			}
		}
		scene.m_numMeshes = meshes.getSize();
		
		hkString str;
		str.printf( "%i duplicate meshes found and replaced by instances", instanceMap.getSize() );
		HK_REPORT( str );
	}
	else
	{
		HK_REPORT( "No duplicate meshes found" );
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
