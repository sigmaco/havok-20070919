/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>

#include <ContentTools/Common/Filters/FilterScene/PlatformWriter/hctPlatformWriterFilter.h>
#include <ContentTools/Common/Filters/FilterScene/PlatformWriter/hctPlatformWriterOptions.h>

#include <Common/SceneData/Scene/hkxSceneUtils.h>

#include <Common/Serialize/Util/hkStructureLayout.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileWriter.h>
#include <Common/Base/Reflection/Registry/hkClassNameRegistry.h>

#include <Common/SceneData/Scene/hkxSceneUtils.h>
#include <Common/SceneData/Graph/hkxNode.h>

#include <Common/SceneData/Environment/hkxEnvironment.h>

hctPlatformWriterFilterDesc g_platformWriterDesc;

hctPlatformWriterFilter::hctPlatformWriterFilter(const hctFilterManagerInterface* owner)
:	hctFilterInterface (owner),
	m_optionsDialog(NULL)
{
	m_options.m_filename = HK_NULL;
	m_options.m_preset = hctPlatformWriterOptions::MSVC_WIN32;
	m_options.m_bytesInPointer = 4;
	m_options.m_littleEndian = 1;
	m_options.m_reusePaddingOptimized = 0;
	m_options.m_emptyBaseClassOptimized = 1;
	m_options.m_removeMetadata = false;
	m_options.m_saveEnvironmentData = false;
	m_options.m_userTag = 0;
}

hctPlatformWriterFilter::~hctPlatformWriterFilter()
{

}

// Storage for the custom layout rules.
/*static*/ hkStructureLayout::LayoutRules hctPlatformWriterFilter::m_customRules;

/*static*/ hctPlatformWriterFilter::OptionToLayoutEntry hctPlatformWriterFilter::m_optionToLayoutTable[] =
{
	{ OPTTYPE::XML,HK_NULL, "XML" },
	{ OPTTYPE::MSVC_WIN32,&(hkStructureLayout::MsvcWin32LayoutRules), "Win32 MSVC" },
	{ OPTTYPE::X360,&(hkStructureLayout::Xbox360LayoutRules), "Xbox 360" },
	{ OPTTYPE::GCC_PS3,&(hkStructureLayout::GccPs3LayoutRules), "PS3 GCC" },
	{ OPTTYPE::CW_WII,&(hkStructureLayout::CwWiiLayoutRules), "Wii CW" },
	{ OPTTYPE::MSVC_AMD64,&(hkStructureLayout::MsvcAmd64LayoutRules), "AMD64 MSVC" },
	{ OPTTYPE::MAC_PPC,&(hkStructureLayout::Gcc40MacPpcLayoutRules), "Mac PPC" },
	{ OPTTYPE::MAC_386,&(hkStructureLayout::Gcc40MacIntelLayoutRules), "Mac Intel 386" },
	{ OPTTYPE::CW_PS2,&(hkStructureLayout::CwPs2LayoutRules), "PS2 CW" },
	{ OPTTYPE::GCC32_PS2,&(hkStructureLayout::Gcc32Ps2LayoutRules), "PS2 GCC 3.2" },
	{ OPTTYPE::SN31_PS2,&(hkStructureLayout::Sn31Ps2LayoutRules), "PS2 SN 3.1" },
	{ OPTTYPE::SNC_PSP,&(hkStructureLayout::Sn10PspLayoutRules), "PSP SNC 1.0.x" },
	{ OPTTYPE::GCC151_PSP,&(hkStructureLayout::Gcc151PspLayoutRules), "PSP GCC 1.5.1" },
	{ OPTTYPE::CW_PSP,&(hkStructureLayout::CwPspLayoutRules), "PSP CW" },
	{ OPTTYPE::CW_GAMECUBE,&(hkStructureLayout::CwNgcLayoutRules), "GameCube CW" },
	{ OPTTYPE::SN393_GAMECUBE,&(hkStructureLayout::Sn393NgcLayoutRules), "GameCube SN 3.93" },
	{ OPTTYPE::MSVC_XBOX,&(hkStructureLayout::MsvcXboxLayoutRules), "Xbox" },
	{ OPTTYPE::GCC295_PS2,&(hkStructureLayout::Gcc295LinuxLayoutRules), "Linux GCC 2.95" },
	{ OPTTYPE::GCC33_PS2,&(hkStructureLayout::Gcc33LinuxLayoutRules), "Linux GCC 3.3" },
	{ OPTTYPE::CUSTOM, &(hctPlatformWriterFilter::m_customRules), "Custom..." }
};
/*static*/ int hctPlatformWriterFilter::m_optionToLayoutTableSize = sizeof(hctPlatformWriterFilter::m_optionToLayoutTable) / sizeof(hctPlatformWriterFilter::OptionToLayoutEntry);

/*static*/ int hctPlatformWriterFilter::findPreset( OPTTYPE::Preset p )
{
	int i=0;
	while ((i < m_optionToLayoutTableSize) && m_optionToLayoutTable[i].preset != p)
	{
		++i;
	}
	return i < m_optionToLayoutTableSize? i : 0; // default to win32 msvc
}

void hctPlatformWriterFilter::process( class hkRootLevelContainer& data, bool batchMode )
{
	// Find the environment in the root level container
	hkxEnvironment tempEnvironment;
	hkxEnvironment* environmentPtr = HK_NULL;
	bool prunedEnvironment = false;
	{
		environmentPtr = reinterpret_cast<hkxEnvironment*>( data.findObjectByType( hkxEnvironmentClass.getName() ) );

		// If no environemnt is found, use a temporary one
		if (!environmentPtr)
		{
			prunedEnvironment = true;
			environmentPtr = &tempEnvironment;

			// If we have a scene, fill the environment with ti
			hkxScene* scenePtr = reinterpret_cast<hkxScene*>( data.findObjectByType( hkxSceneClass.getName() ) );
			if (scenePtr)
			{
				hkxSceneUtils::fillEnvironmentFromScene(*scenePtr, tempEnvironment);
			}
		}
	}

	hkString err;
	int curPresetIndex = findPreset( m_options.m_preset );
	if ( (curPresetIndex >=0) && (curPresetIndex < m_optionToLayoutTableSize))
	{

		// If the filename hasn't been set, use the default.
		if( m_filename.getLength() == 0)
		{
			m_filename = hkString( ".\\$(asset)_$(configuration).hkx" );
		}

		hkString userFilename;
		const bool substitutionOk = hctFilterUtils::replaceVariables(*environmentPtr, m_filename.cString(), userFilename, true );

		if (!substitutionOk && prunedEnvironment)
		{
			HK_WARN_ALWAYS(0xabba9a9f, "No environment data (required for variable substitutions) found - possibly pruned.");
		}

		// Construct the full filename if the path seems to be relative
		hkString fullFilename;
		hctFilterUtils::getFullPath(data, userFilename.cString(), fullFilename);

		hkOstream f(fullFilename.cString());
		if ( f.isOk() )
		{
			hkPackfileWriter::Options o;
			o.m_userTag = m_options.m_userTag; // HKA-612
			o.m_writeMetaInfo = ! m_options.m_removeMetadata; // HKA-612

			hkPackfileWriter* pw = HK_NULL;
			if (m_optionToLayoutTable[curPresetIndex].preset != hctPlatformWriterOptions::XML)
			{
				pw = new hkBinaryPackfileWriter;
			}
			else
			{
				pw = new hkXmlPackfileWriter;
			}

			if (m_optionToLayoutTable[curPresetIndex].preset == hctPlatformWriterOptions::CUSTOM)
			{
				m_customRules.m_bytesInPointer = m_options.m_bytesInPointer;
				m_customRules.m_emptyBaseClassOptimization = m_options.m_emptyBaseClassOptimized;
				m_customRules.m_littleEndian = m_options.m_littleEndian;
				m_customRules.m_reusePaddingOptimization = m_options.m_reusePaddingOptimized;
			}

			// EXP-462
			// If we don't want to save the environment, go through the variants
			if (!m_options.m_saveEnvironmentData)
			{
				hkRootLevelContainer tempContainer;
				tempContainer.m_namedVariants = new hkRootLevelContainer::NamedVariant[data.m_numNamedVariants];
				tempContainer.m_numNamedVariants = 0;
				for (int i=0; i<data.m_numNamedVariants; i++)
				{
					if (hkString::strCmp(data.m_namedVariants[i].getTypeName(), hkxEnvironmentClass.getName())!=0) // not an environment
					{
						tempContainer.m_namedVariants[tempContainer.m_numNamedVariants++] = data.m_namedVariants[i];
					}
				}
				pw->setContentsWithRegistry(&tempContainer, hkRootLevelContainerClass, &m_filterManager->getFilterClassRegistry().getVtableRegistry() /*XX add versioning*/);
			}
			else
			{
				// Otherwise save everything
				pw->setContentsWithRegistry(&data, hkRootLevelContainerClass, &m_filterManager->getFilterClassRegistry().getVtableRegistry() /*XX add versioning*/);
			}


			if (m_optionToLayoutTable[curPresetIndex].layout)
			{
				o.m_layout =  *(m_optionToLayoutTable[curPresetIndex].layout);
			}

			hkResult res = pw->save( f.getStreamWriter(), o );
			pw->removeReference();

			if (res == HK_SUCCESS)
			{
				err.printf("Wrote layout for [%s] to file [%s].", m_optionToLayoutTable[curPresetIndex].label, fullFilename.cString());
				HK_REPORT( err.cString() );
			}
			else
			{
				err.printf("Could not write layout for [%s] to file [%s]. File may now be corrupt.", m_optionToLayoutTable[curPresetIndex].label, fullFilename.cString());
				HK_WARN_ALWAYS( 0xabba9832, err.cString() );
			}
		}
		else
		{
			err.printf("Could not create file [%s] to write to. Aborting.", fullFilename.cString());
			HK_WARN_ALWAYS( 0xabba9833, err.cString() );
		}
	}
	else
	{
		HK_WARN_ALWAYS( 0xabba4323, "Preset layout not valid. Aborting." );
	}
}


// process() is in the Dialog cpp so as to make use of the static lookup tables etc.

void hctPlatformWriterFilter::setOptions(const void* optionData, int optionDataSize, unsigned int version)
{
	hctPlatformWriterOptions* options;

	// Check if the options have been saved as raw data.
	if ( version < HCT_FILTER_VERSION(1,0,1) )
	{
		m_optionsBuf.setSize(optionDataSize);
		hkString::memCpy( m_optionsBuf.begin(), optionData, optionDataSize );
		options = (hctPlatformWriterOptions*)hctFilterUtils::interpretOptions(m_optionsBuf.begin());
	}
	else if ( version != g_platformWriterDesc.getFilterVersion() )
	{
		HK_WARN_ALWAYS( 0xabba4722, "The " << g_platformWriterDesc.getShortName() << " option data was of an incompatible version and could not be loaded." );
		return;
	}
	else
	{
		// Get the options from the XML data.
		if ( hctFilterUtils::readOptionsXml( optionData, optionDataSize, m_optionsBuf, hctPlatformWriterOptionsClass ) == HK_SUCCESS )
		{
			options = reinterpret_cast<hctPlatformWriterOptions*>( m_optionsBuf.begin() );
		}
		else
		{
			HK_WARN_ALWAYS( 0xabba7523, "The XML for the " << g_platformWriterDesc.getShortName() << " option data could not be loaded." );
			return;
		}
	}

	// the filename ptr will only be valid as long as the buf still is (until next write)
	// so we store the filename separately
	m_filename = options->m_filename;
	m_options = *options; // copy the main part.
}

int hctPlatformWriterFilter::getOptionsSize() const
{
	m_options.m_filename = (char*) m_filename.cString(); // so that the ptr is valid

	hctFilterUtils::writeOptionsXml(hctPlatformWriterOptionsClass, &m_options, m_optionsBuf, g_platformWriterDesc.getShortName() );
	return m_optionsBuf.getSize();
}

void hctPlatformWriterFilter::getOptions(void* optionData) const
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
