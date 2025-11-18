/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>
#include <Common/Base/System/Io/Reader/Memory/hkMemoryStreamReader.h>

#include <Common/Serialize/Serialize/Xml/hkXmlObjectWriter.h>
#include <Common/Serialize/Serialize/Xml/hkXmlObjectReader.h>
#include <Common/Serialize/Packfile/Binary/hkPackfileHeader.h>
#include <Common/Serialize/Packfile/Binary/hkPackfileSectionHeader.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileReader.h>
#include <Common/Serialize/Packfile/Binary/hkPackfileSectionHeader.h>
#include <Common/Serialize/Serialize/Platform/hkPlatformObjectWriter.h>
#include <Common/Serialize/Serialize/hkRelocationInfo.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Serialize/Util/Xml/hkXmlParser.h>

#include <Common/SceneData/Scene/hkxScene.h>
#include <Common/SceneData/Scene/hkxSceneUtils.h>
#include <Common/SceneData/Environment/hkxEnvironment.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>

#include <shlwapi.h>

void* hctFilterUtils::interpretOptions( void* data )
{
	// Relocations:
	int* curInt = reinterpret_cast<int*>( data );

	// num local fixups
	int numLocal = *( curInt++ );

	// start of the cinfo data
	char* dataBegin = ((char*)data) + sizeof(int) + sizeof(int)*2*numLocal;
	for (int nl =0; nl < numLocal; ++nl)
	{
		int srcOff = *(curInt++);
		if (srcOff >=0 )
		{
			int dstOff = *(curInt++);
			*(hkUlong*)(dataBegin+srcOff) = hkUlong(dataBegin+dstOff);
		}
	}
	return dataBegin;
}

void* hctFilterUtils::writeOptionsXml( const hkClass& klass, const void* data, hkArray<char>& buffer, const char* filterName )
{
	buffer.clear();
	hkArrayStreamWriter wr( &buffer, hkArrayStreamWriter::ARRAY_BORROW );
	
	hkXmlObjectWriter::SequentialNameFromAddress namer;
	hkXmlObjectWriter xmlWriter(namer);
	xmlWriter.adjustIndent( 1 );

	xmlWriter.writeObjectWithElement( &wr, data, klass, filterName );

	// Return the location of the data.
	return buffer.begin(); 
}

hkResult hctFilterUtils::readOptionsXml( const void* optionData, const int optionDataSize, hkArray<char>& buffer, const hkClass klass )
{
	hkXmlParser parser;
	hkXmlObjectReader xmlReader( &parser );

	hkIstream optionStream( optionData, optionDataSize );
	HK_ASSERT( 0x5469fae1, optionStream.isOk() );

	hkStreamReader* reader = optionStream.getStreamReader();

	hkRelocationInfo ri;

	if ( xmlReader.readObject( reader, buffer, klass, ri ) == HK_SUCCESS )
	{
		ri.applyLocalAndGlobal( buffer.begin() );
		return HK_SUCCESS;
	}

	return HK_FAILURE;
}

void* hctFilterUtils::deepCopyObject(const hctFilterClassRegistry& classReg,
											const void* obj, const hkClass* klass,
											hkArray<char>& storage)
{
	// EXP-698 : Temporarily disable warnings regarding non-registered structs
	const bool wasEnabled = hkError::getInstance().isEnabled(0x4e34ea5f);
	hkError::getInstance().setEnabled(0x4e34ea5f, false);

	void* retObj = HK_NULL;
	hkBinaryPackfileWriter pw;
	pw.setContentsWithRegistry(obj, *klass, &classReg.getVtableRegistry() );

	hkBinaryPackfileWriter::Options o;
	o.m_userTag = 0x0;
	o.m_writeMetaInfo = true; // no need to copy class info?

	hkArray<char> localStorage;
	hkArrayStreamWriter asw(&localStorage, hkArrayStreamWriter::ARRAY_BORROW);
	if ( pw.save( &asw, o ) == HK_SUCCESS )
	{
		hkBinaryPackfileReader pr;
		hkMemoryStreamReader msr(localStorage.begin(), localStorage.getSize(), hkMemoryStreamReader::MEMORY_INPLACE );

		// Load the file header
		hkUint32 totalBufferSize = 0;
		hkPackfileHeader header;
		if ( pr.loadFileHeader(&msr, &header) == HK_SUCCESS )
		{
			hkArray<hkPackfileSectionHeader> sectionHeaders;
			sectionHeaders.setSize( header.m_numSections );
			if ( pr.loadSectionHeadersNoSeek(&msr, sectionHeaders.begin() ) == HK_SUCCESS)
			{
				// Load the sections manually
				int s;
				for (s=0; s < pr.getNumSections(); s++)
				{
					// Grab the section header
					const hkPackfileSectionHeader& sHeader = pr.getSectionHeader( s );
					totalBufferSize += sHeader.m_endOffset;
				}			
				storage.setSize(totalBufferSize);
				totalBufferSize = 0;
				for (s=0; s < pr.getNumSections(); s++)
				{
					const hkPackfileSectionHeader& sHeader = pr.getSectionHeader( s );
					// Load the section (fixes up local fixups)
					if (sHeader.m_endOffset > 0) // can't deref 'storage[totalBufferSize]'' if last section is size 0 say 
					{
						if (pr.loadSection( &msr, s, &storage[totalBufferSize] ) == HK_FAILURE )
						{
							totalBufferSize = 0;
							break;
						}
						totalBufferSize += sHeader.m_endOffset;
					}
				}
			}
		}

		// Do global fixups
		if (totalBufferSize > 0)
		{
			pr.fixupGlobalReferences();
			retObj = pr.getContentsWithRegistry( klass->getName(), &classReg.getTypeInfoRegistry());
		}
		else
		{
			storage.setSize(0);
		}
		pr.getAllocatedData()->disableDestructors();
	}

	hkError::getInstance().setEnabled(0x4e34ea5f, wasEnabled);

	return retObj; 
}

void hctFilterUtils::createArrayFromDelimitedString( hkObjectArray<hkString>& buf, const char* delimitedString, const char delimiter )
{
	buf.setSize( 0 );

	int curCh = 0;
	int prevCh = 0;

	while ( delimitedString && delimitedString[curCh] )
	{
		prevCh = curCh;
		while ( delimitedString[curCh] && ( delimitedString[curCh] != delimiter ) )
		{
			curCh++;
		}
		if ( curCh > prevCh )
		{
			hkString* str = buf.expandBy(1);
			*str = hkString( &( delimitedString[prevCh] ), curCh - prevCh );
		}
		if ( delimitedString[curCh] )
		{
			curCh++;
		}
	}
}

	/// Create a single string from the given array of strings, using "delimiter" to split the strings.
void hctFilterUtils::createDelimitedStringFromArray( const hkObjectArray<hkString>& array, const char* delimiter, hkString& delimitedStringOut)
{
	delimitedStringOut = "";

	for (int i=0; i<array.getSize(); i++)
	{
		delimitedStringOut += array[i];
		delimitedStringOut += delimiter;
	}
}

void hctFilterUtils::getAssetFolder (const hkRootLevelContainer& rootLevelContainer, hkString& assetFolderOut )
{
	// Look for the asset folder environment variable if we have it
	const char* assetFolder = getEnvironmentVariable(rootLevelContainer, "assetFolder");

	if (assetFolder)
	{
		assetFolderOut = assetFolder;
	}
	else
	{
		assetFolderOut = "";
	}
}

const char* hctFilterUtils::getEnvironmentVariable (const hkRootLevelContainer& contents, const char* variable)
{
	// Find the environment in the root level container
	hkxEnvironment tempEnvironment;
	hkxEnvironment* environmentPtr = HK_NULL;
	{
		environmentPtr = reinterpret_cast<hkxEnvironment*>( contents.findObjectByType( hkxEnvironmentClass.getName() ) );

		// If no environment is found, use a temporary one
		if (!environmentPtr)
		{
			environmentPtr = &tempEnvironment;

			// If we have a scene, fill the environment with it
			hkxScene* scenePtr = reinterpret_cast<hkxScene*>( contents.findObjectByType( hkxSceneClass.getName() ) );
			if (scenePtr)
			{
				hkxSceneUtils::fillEnvironmentFromScene(*scenePtr, tempEnvironment);
			}
		}
	}

	return environmentPtr->getVariableValue(variable);
}

void hctFilterUtils::getFullPath ( const hkRootLevelContainer& rootLevelContainer, const char* userPath, hkString& fullPathOut)
{
	hkString userPathStr (userPath);

	hkString assetFolder;
	getAssetFolder( rootLevelContainer, assetFolder);

	// No asset folder? return the user path as given
	if (assetFolder.getLength()==0) 
	{
		fullPathOut = userPathStr;
		return;
	}

	// purely relative? just add asset path
	if (userPathStr.beginsWith(".")) 
	{
		fullPathOut = assetFolder + userPathStr;
		return;
	}

	// a root offset? add the start (drive) of asset path
	if (assetFolder.getLength()>=2 && (userPathStr.beginsWith("\\") || userPathStr.beginsWith("/")) ) 
	{
		hkString driveLetter = assetFolder.substr(0,2);
		fullPathOut = driveLetter + userPathStr;
		return;
	}

	// might either be a absolute path (starts with drive) or a normal filename (then add asset path)
	if ( (userPathStr.getLength() > 4) && !hkString::strChr(userPathStr.substr(0,2).cString(), ':'))
	{
		// normal filename (has not got a : in the first 2 entries (or rather [1]), add asset path
		fullPathOut = assetFolder + userPathStr;
		return;
	}

	// must be absolute or something we don't handle wrt to paths
	fullPathOut = userPathStr;

	return;
}


void hctFilterUtils::getReducedFilename( const char* fname, const hkString& assetPath, hkString& reducedName )
{
	// Take m_assetPath out of fname
	char rel[MAX_PATH];

	hkString assetPathLessLast( assetPath.cString(), assetPath.getLength() > 0? assetPath.getLength() - 1 : 0 );

	if ( PathFileExists( assetPathLessLast.cString() ) && 
		 PathRelativePathTo( rel, assetPathLessLast.cString(), FILE_ATTRIBUTE_DIRECTORY, fname, FILE_ATTRIBUTE_NORMAL) )
	{
		reducedName = rel;
	}
	else
	{
		reducedName = fname; // ah well...
	}
}

const char* hctFilterUtils::filterCategoryToString( hctFilterDescriptor::FilterCategory c )
{
	switch (c)
	{
		case hctFilterDescriptor::HK_CATEGORY_CORE: return "Core"; 
		case hctFilterDescriptor::HK_CATEGORY_COLLISION_DEPRECATED: return "Collision"; 
		case hctFilterDescriptor::HK_CATEGORY_PHYSICS: return "Physics"; 
		case hctFilterDescriptor::HK_CATEGORY_FX_PHYSICS_DEPRECATED: return "FX";
		case hctFilterDescriptor::HK_CATEGORY_ANIMATION: return "Animation"; 
		case hctFilterDescriptor::HK_CATEGORY_GRAPHICS: return "Graphics"; 
		case hctFilterDescriptor::HK_CATEGORY_USER: return "User"; 
		default: return "Unknown"; 
	}

}


/*static*/ bool hctFilterUtils::replaceVariables (const hkxEnvironment& environment, const char* inputString, hkString& outputString, hkBool useOSEnvironment)
{
	outputString = hkString(inputString);

	bool everythingOk = true;

	// Check any $ symbols in the string.
	int dollarIndex = outputString.indexOf( '$' );
	while( dollarIndex != -1 )
	{
		const int bracketIndex1 = outputString.indexOf( '(', dollarIndex );
		const int bracketIndex2 = outputString.indexOf( ')', bracketIndex1 );

		if( ( bracketIndex1 == dollarIndex+1 ) && ( bracketIndex2 > bracketIndex1 ) )
		{
			hkString variableString;
			hkString replacementString;
			bool doReplace = false;

			variableString = outputString.substr( dollarIndex, bracketIndex2+1 - dollarIndex );
			
			const hkString varName = variableString.substr(2, variableString.getLength()-3);

			const char* varValue = environment.getVariableValue(varName.cString());

			if (varValue)
			{
				replacementString = varValue;
				doReplace = true;
			}
			else if (useOSEnvironment)
			{
				// Try OS environment variables too
				const char* envVarValue = getenv( varName.cString() );

				if (envVarValue)
				{
					replacementString = envVarValue;
					doReplace = true;
				}
			}

			if (doReplace)
			{
				outputString = outputString.substr( 0, dollarIndex ) 
						+ replacementString 
						+ outputString.substr( dollarIndex + variableString.getLength() );
										
			}
			else
			{
				HK_WARN_ALWAYS(0xabba8dc2, "Couldn't replace variable "<<variableString);
				everythingOk = false;
			}
		}

		dollarIndex = outputString.indexOf( '$', dollarIndex + 1 );

	}

	return everythingOk;
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
