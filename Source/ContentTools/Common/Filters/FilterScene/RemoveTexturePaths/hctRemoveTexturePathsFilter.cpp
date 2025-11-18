/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>

#include <ContentTools/Common/Filters/FilterScene/RemoveTexturePaths/hctRemoveTexturePathsFilter.h>

#include <Common/Serialize/Util/Xml/hkXmlParser.h>
#include <Common/Base/System/Io/Reader/Memory/hkMemoryStreamReader.h>
#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>

#include <Common/SceneData/Material/hkxMaterial.h>
#include <Common/SceneData/Material/hkxTextureFile.h>

#include <tchar.h>

#include <ContentTools/Common/Filters/FilterScene/RemoveTexturePaths/hctRemoveTexturePathsOptions.h>

hctRemoveTexturePathsFilterDesc g_removeTexturePathsDesc;

hctRemoveTexturePathsFilter::hctRemoveTexturePathsFilter(const hctFilterManagerInterface* owner)
:	hctFilterInterface (owner),
	m_optionsDialog(NULL)
{
}

hctRemoveTexturePathsFilter::~hctRemoveTexturePathsFilter()
{

}

void hctRemoveTexturePathsFilter::process( hkRootLevelContainer& data, bool batchMode )
{
	// Find the scene in the root level container
	hkxScene* scenePtr = reinterpret_cast<hkxScene*>( data.findObjectByType( hkxSceneClass.getName() ) );
	if (scenePtr == HK_NULL)
	{
		HK_WARN_ALWAYS(0xabbaa5f0, "No scene data found");
		return;
	}
	hkxScene& scene = *scenePtr;

	// Pre process our paths into a set of lower case strs.. 
	// XX TODO: don't have to do this in process, move to setoptions etc.
	hkObjectArray< hkString > lowerCasePaths;
	if (scene.m_numMaterials >= 0)
	{
		int curChar = 0;
		const char* paths = m_paths.cString();
		while ( paths[curChar] )
		{
			int endChar = curChar;
			while (paths[endChar] && paths[endChar] != ';')
				endChar++;

			hkString* str = lowerCasePaths.expandBy(1);
			*str = hkString(&paths[curChar], endChar - curChar).asLowerCase();
			curChar = paths[endChar]? endChar + 1 : endChar;
		}
	}

	// we don't need to regsiter any classes as we are not adding any extra types
	// that are not 'known' already.

	// Find all our textures
	for (int cim = 0; cim < scene.m_numExternalTextures; ++cim)
	{
		hkxTextureFile* curTexture = scene.m_externalTextures[cim];
            		
		// for each path, if that path is contained in the filename, remove the longest perhaps?
		// or can we assume the paths don't overlap. 
		// For now, just take out only:
		int bestPathIndex = -1;
		int longestPath = 0;
	
		hkString pathAsStr = hkString(curTexture->m_filename).asLowerCase();
		for (int cp=0; cp < lowerCasePaths.getSize(); ++cp)
		{
			hkString& lowerCasePath = lowerCasePaths[cp];
			int pl = lowerCasePath.getLength();

			const char* ss = hkString::strStr( pathAsStr.cString(), lowerCasePath.cString() );
			
			if (ss && ( ss == pathAsStr.cString() ))// have a strstr and it is at the start
			{
				if (longestPath < pl)
				{
					longestPath = pl;
					bestPathIndex = cp;
				}
			}
		}

		if (longestPath > 0)
		{
			hkString newPath( &curTexture->m_filename[longestPath], pathAsStr.getLength() - longestPath);
			int pathLen = newPath.getLength() + 1; // null term too.
			// no need to dealloc old str as the scene manages it
			curTexture->m_filename = hkAllocateChunk<char>(pathLen, HK_MEMORY_CLASS_EXPORT);
			hkString::memCpy( curTexture->m_filename, newPath.cString(), pathLen );
		}
	}// all external textures
}

void hctRemoveTexturePathsFilter::setOptions( const void* optionData, int optionDataSize, unsigned int version) 
{
	// Check if the options have been saved as raw data.
	if ( version < HCT_FILTER_VERSION(1,1,1) )
	{
		// just a string with all the paths in it..
		m_paths = hkString( (const char*) optionData, optionDataSize );
		return;
	}
	else if (version != g_removeTexturePathsDesc.getFilterVersion())
	{
		HK_WARN_ALWAYS( 0xabba65ae, "The " << g_removeTexturePathsDesc.getShortName() << " option data was of an incompatible version and could not be loaded." );
		return;
	}

	// Get the options from the XML data.
	if ( hctFilterUtils::readOptionsXml( optionData, optionDataSize, m_optionsBuf, hctRemoveTexturePathsOptionsClass ) == HK_SUCCESS )
	{
		hctRemoveTexturePathsOptions *options;
		options = reinterpret_cast<hctRemoveTexturePathsOptions*>( m_optionsBuf.begin() );

		m_paths = hkString( options->m_texturePaths );
	}
	else
	{
		HK_WARN_ALWAYS( 0xabba4753, "The XML for the " << g_removeTexturePathsDesc.getShortName() << " option data could not be loaded." );
		return;
	}
}

int hctRemoveTexturePathsFilter::getOptionsSize() const
{
	hctRemoveTexturePathsOptions options;
	options.m_texturePaths = (char*) m_paths.cString();

	hctFilterUtils::writeOptionsXml(hctRemoveTexturePathsOptionsClass, &options, m_optionsBuf, g_removeTexturePathsDesc.getShortName() );
	return m_optionsBuf.getSize();
}

void hctRemoveTexturePathsFilter::getOptions(void* optionData) const
{
	hkString::memCpy( optionData, m_optionsBuf.begin(), m_optionsBuf.getSize() );
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
