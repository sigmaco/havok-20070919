/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/SceneExport/hctSceneExport.h> // PCH
#include <ContentTools/Common/SceneExport/AttributeSelection/hctAttributeSelectionUtil.h>

#include <Common/Base/System/Io/IStream/hkIStream.h>

#include <Common/Base/Reflection/hkClassEnum.h>
#include <Common/Base/Reflection/hkClass.h>

#include <Common/Serialize/Packfile/Xml/hkXmlPackfileWriter.h>
#include <Common/Base/Reflection/Registry/hkClassNameRegistry.h>
#include <Common/Serialize/Version/hkVersionUtil.h>
#include <ContentTools/Common/SceneExport/AttributeProcessing/hctAttributeDescription.h>

hkBool hctAttributeSelectionUtil::init (  hctFilterMemoryTracker* memoryTracker )
{
	// We need a memory tracker for any future allocations/deallocations
	m_trackedMemory = memoryTracker;

	m_database.m_numAttributeAdditions = 0;
	m_database.m_attributeAdditions = NULL;

	m_database.m_numAttributeRemovals = 0;
	m_database.m_attributeRemovals = NULL;

	return true;
}

hctAttributeSelectionUtil::~hctAttributeSelectionUtil()
{
	{
		for ( int i=0; i<m_packfileReaders.getSize(); i++)
		{
			delete m_packfileReaders[i];
		}
	}
	{
		for ( int i=0; i<m_newAttributeSelections.getSize(); i++ )
		{
			delete[] m_newAttributeSelections[i];
		}
	}
}

hkBool hctAttributeSelectionUtil::loadAttributeSelections( const char* attributeSelectionPath )
{
	hkClassNameRegistry cn;
	cn.registerClass(&hctAttributeSelectionClass);
	cn.registerClass(&hctAttributeSelectionDatabaseClass);

	// look for all files in the path with starting with hk and ending in xml

	WIN32_FIND_DATA FindFileData;
	HANDLE hFindHandle;
	hkString databasePath = attributeSelectionPath ;
	databasePath += "\\hct*.xml";
	hFindHandle = FindFirstFile( TEXT( databasePath.cString() ), &FindFileData);
	bool finished = (hFindHandle == INVALID_HANDLE_VALUE);
	while( !finished )
	{
		hkString xmlName = attributeSelectionPath;
		xmlName += "\\";
		xmlName += FindFileData.cFileName;

		hkIstream file(xmlName.cString());
		if (file.isOk())
		{
			hkXmlPackfileReader* reader = new hkXmlPackfileReader();
			m_packfileReaders.pushBack(reader);

			reader->loadEntireFileWithRegistry( file.getStreamReader(), &cn );

			hkVersionUtil::updateToCurrentVersion( *reader, hkVersionRegistry::getInstance() );

			hctAttributeSelectionDatabase* db = (hctAttributeSelectionDatabase*) reader->getContents( hctAttributeSelectionDatabaseClass.getName() );
			if (db)
			{
				mergeAttributeSelectionDatabase(*db);
			}

		}

		// get next xml file:
		if (FindNextFile( hFindHandle, &FindFileData ) == 0) // zero == error
		{
			finished = true;
			FindClose(hFindHandle);
		}
	}

	return true;
}

void hctAttributeSelectionUtil::mergeAttributeSelectionDatabase (const hctAttributeSelectionDatabase& newDatabase)
{
	// Merge additions array
	mergeAttributeSelectionArray (	newDatabase.m_numAttributeAdditions, newDatabase.m_attributeAdditions,
									m_database.m_numAttributeAdditions, m_database.m_attributeAdditions);

	// Merge removalss array
	mergeAttributeSelectionArray (	newDatabase.m_numAttributeRemovals, newDatabase.m_attributeRemovals,
									m_database.m_numAttributeRemovals, m_database.m_attributeRemovals);
}

void hctAttributeSelectionUtil::mergeAttributeSelectionArray (const int& otherArraySize, const hctAttributeSelection* otherArray, int& currentArraySizeRef, hctAttributeSelection* &currentArrayRef )
{
	if (otherArraySize==0) return;

	const int oldSize = currentArraySizeRef;
	const int newSize = oldSize + otherArraySize;

	hctAttributeSelection* newArray = new hctAttributeSelection [ newSize ];
	m_newAttributeSelections.pushBack(newArray);

	if (oldSize>0)
	{
		// copy old contents
		hkString::memCpy(newArray, currentArrayRef, sizeof(hctAttributeSelection) * oldSize);
	}

	// Copy new contents
	hkString::memCpy(newArray+oldSize, otherArray, sizeof(hctAttributeSelection) * otherArraySize);

	currentArrayRef = newArray;
	currentArraySizeRef = newSize;

}

static bool _stringMatch (const char* pattern, const char* string)
{
	hkString patternStr(pattern); patternStr = patternStr.asLowerCase();
	hkString userStr(string); userStr = userStr.asLowerCase();

	for (int ci=0; ci<userStr.getLength(); ci++)
	{
		if (ci>=patternStr.getLength()) return false;

		if (patternStr[ci]=='*') return true;

		if (patternStr[ci]!=userStr[ci]) return false;
	}

	// case of "blah*" and "blah" -> true
	if ((patternStr.getLength()==userStr.getLength()+1) && (patternStr[userStr.getLength()]=='*'))
	{
		return true;
	}

	// Different lengths -> false
	if (patternStr.getLength()!=userStr.getLength())
	{
		return false;
	}

	return true;
}

hkBool hctAttributeSelectionUtil::matchAttributeSelection (const char* typeName, const char* subTypeName, const char* attributeName, const hctAttributeSelection& selection ) const
{
	if (typeName && !_stringMatch(selection.m_typeName, typeName))
	{
		return false;
	}

	if (subTypeName && !_stringMatch(selection.m_subTypeName, subTypeName))
	{
		return false;
	}

	if (attributeName)
	{
		bool match = false;
		for (int ai=0; ai<selection.m_numAttributeNames; ai++)
		{
			if (_stringMatch(selection.m_attributeNames[ai], attributeName))
			{
				match = true;
				break;
			}
		}

		if (!match) return false;
	}

	// We matched everything
	return true;
}

hctAttributeSelectionUtil::UserAction hctAttributeSelectionUtil::filterAttribute (const char* typeName, const char* subTypeName, const char* attributeName) const
{
	UserAction result = USER_UNDEFINED;

	// Additions
	for (int i=0; i<m_database.m_numAttributeAdditions; i++)
	{
		const hctAttributeSelection& userSelection = m_database.m_attributeAdditions[i];

		if (matchAttributeSelection(typeName, subTypeName, attributeName, userSelection))
		{
			result = USER_ADD;
			break;
		}
	}

	// Removals - take precedence over additions so they are processed after
	for (int i=0; i<m_database.m_numAttributeRemovals; i++)
	{
		const hctAttributeSelection& userSelection = m_database.m_attributeRemovals[i];

		// For removals, we only want to return USER_REMOVE for NULL entries if we match all entries
		const char* rTypeName = typeName ? typeName : "*";
		const char* rSubtTypeName = subTypeName ? subTypeName : "*";
		const char* rAttrName = attributeName ? attributeName : "*";

		if (matchAttributeSelection(rTypeName, rSubtTypeName, rAttrName, userSelection))
		{
			result = USER_REMOVE;
			break;
		}
	}

	return result;
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
