/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/SceneExport/hctSceneExport.h> // PCH
#include <ContentTools/Common/SceneExport/AttributeProcessing/hctAttributeProcessingUtil.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>

#include <Common/Base/Reflection/hkClassEnum.h>
#include <Common/Base/Reflection/hkClass.h>

#include <Common/Serialize/Packfile/Xml/hkXmlPackfileWriter.h>
#include <Common/Base/Reflection/Registry/hkClassNameRegistry.h>
#include <ContentTools/Common/SceneExport/AttributeProcessing/hctAttributeDescription.h>

#include <Common/SceneData/Attributes/hkxAttributeGroup.h>

#include <Common/Serialize/Version/hkVersionUtil.h>

#define TRACK_MEMORY_NEW(theType)					(theType *)m_trackedMemory->allocate(sizeof(theType), HK_MEMORY_CLASS_EXPORT)
#define TRACK_MEMORY_NEW_ARRAY(theType, size)		(theType *)m_trackedMemory->allocate(sizeof(theType)*size, HK_MEMORY_CLASS_EXPORT)
#define TRACK_MEMORY_DELETE(mem )					m_trackedMemory->deallocate(mem)

hkBool hctAttributeProcessingUtil::init (  hctFilterMemoryTracker* memoryTracker )
{
	// We need a memory tracker for any future allocations/deallocations
	m_trackedMemory = memoryTracker;

	m_database.m_numGroupDescriptions = 0;
	m_database.m_groupDescriptions = NULL;

	return true;
}

hctAttributeProcessingUtil::~hctAttributeProcessingUtil()
{
	{
		for ( int i=0; i<m_packfileReaders.getSize(); i++)
		{
			delete m_packfileReaders[i];
		}
	}
	{
		for ( int i=0; i<m_newGroupDescriptions.getSize(); i++ )
		{
			delete[] m_newGroupDescriptions[i];
		}
	}
	{
		for ( int i=0; i<m_newAttDescriptions.getSize(); i++ )
		{
			delete[] m_newAttDescriptions[i];
		}
	}
}

hkBool hctAttributeProcessingUtil::isEmpty () const
{
	int numAttributesDescribed = 0;

	for (int gIt=0; gIt<m_database.m_numGroupDescriptions; gIt++)
	{
		const hctAttributeGroupDescription& group = m_database.m_groupDescriptions[gIt];

		for (int aIt=0; aIt<group.m_numAttributeDescriptions; aIt++)
		{
			numAttributesDescribed++;
		}
	}

	return (numAttributesDescribed == 0 );
}

hkBool hctAttributeProcessingUtil::loadAttributeDescriptions ( const char* attributeDescriptionPath )
{
	hkClassNameRegistry cn;
	cn.registerClass(&hctAttributeDescriptionClass);
	cn.registerClass(&hctAttributeGroupDescriptionClass);
	cn.registerClass(&hctAttributeDescriptionDatabaseClass);

	// look for all files in attributeDescriptionPath with starting with hk and ending in xml (hctAttributeProcessingUtil.xml is the default master desc)
	WIN32_FIND_DATA FindFileData;
	HANDLE hFindHandle;
	hkString databasePath = attributeDescriptionPath ;
	databasePath += "\\hct*.xml";
	hFindHandle = FindFirstFile( TEXT( databasePath.cString() ), &FindFileData);
	bool finished = (hFindHandle == INVALID_HANDLE_VALUE);
	while( !finished )
	{
		hkString xmlName = attributeDescriptionPath;
		xmlName += "\\";
		xmlName += FindFileData.cFileName;

		hkIstream file(xmlName.cString());
		if (file.isOk())
		{
			hkXmlPackfileReader* reader = new hkXmlPackfileReader();
			m_packfileReaders.pushBack(reader);

			reader->loadEntireFileWithRegistry( file.getStreamReader(), &cn );

			hkVersionUtil::updateToCurrentVersion( *reader, hkVersionRegistry::getInstance() );

			hctAttributeDescriptionDatabase* db = (hctAttributeDescriptionDatabase*) reader->getContents( hctAttributeDescriptionDatabaseClass.getName() );
			if (db)
			{
				mergeAttributeDescriptionDatabase(*db);
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

void hctAttributeProcessingUtil::mergeAttributeDescriptionDatabase (const hctAttributeDescriptionDatabase& newDatabase)
{
	for (int i=0; i<newDatabase.m_numGroupDescriptions; i++)
	{
		const hctAttributeGroupDescription& newGroupDesc = newDatabase.m_groupDescriptions[i];

		bool found = false;

		for (int j=0; j<m_database.m_numGroupDescriptions; j++)
		{
			hctAttributeGroupDescription& currentGroupDesc = m_database.m_groupDescriptions[j];

			if (hkString::strCmp(newGroupDesc.m_name, currentGroupDesc.m_name) == 0)
			{
				mergeAttributeGroupDescriptions(newGroupDesc, currentGroupDesc);
			}
		}

		if (!found)
		{
			// New attribute group description
			hctAttributeGroupDescription* newArray = new hctAttributeGroupDescription [m_database.m_numGroupDescriptions + 1];
			m_newGroupDescriptions.pushBack(newArray);
			if (m_database.m_groupDescriptions)
			{
				hkString::memCpy(newArray, m_database.m_groupDescriptions, sizeof (hctAttributeGroupDescription) * m_database.m_numGroupDescriptions);
			}
			m_database.m_groupDescriptions = newArray;
			m_database.m_groupDescriptions [ m_database.m_numGroupDescriptions++ ] = newGroupDesc;
		}
	}
}

void hctAttributeProcessingUtil::mergeAttributeGroupDescriptions (const hctAttributeGroupDescription& newGroupDesc, hctAttributeGroupDescription& currentGroupDesc)
{
	for (int i=0; i<newGroupDesc.m_numAttributeDescriptions; i++)
	{
		const hctAttributeDescription& newAttDesc = newGroupDesc.m_attributeDescriptions[i];

		bool found = false;

		for (int j=0; j<currentGroupDesc.m_numAttributeDescriptions; j++)
		{
			hctAttributeDescription& currentAttDesc = currentGroupDesc.m_attributeDescriptions[j];

			if (hkString::strCmp(newAttDesc.m_name, currentAttDesc.m_name) == 0)
			{
				mergeAttributeDescriptions(newAttDesc, currentAttDesc);
			}
		}

		if (!found)
		{
			// New attribute group description
			hctAttributeDescription* newArray = new hctAttributeDescription [currentGroupDesc.m_numAttributeDescriptions + 1];
			m_newAttDescriptions.pushBack(newArray);
			if (currentGroupDesc.m_attributeDescriptions)
			{
				hkString::memCpy(newArray, currentGroupDesc.m_attributeDescriptions, sizeof (hctAttributeDescription) * currentGroupDesc.m_numAttributeDescriptions);
			}
			currentGroupDesc.m_attributeDescriptions = newArray;
			currentGroupDesc.m_attributeDescriptions [ currentGroupDesc.m_numAttributeDescriptions++ ] = newAttDesc;
		}
	}

}

void hctAttributeProcessingUtil::mergeAttributeDescriptions (const hctAttributeDescription& newAttDesc, hctAttributeDescription& currentAttDesc)
{
	// Non-defaults win
	if ( currentAttDesc.m_enabledBy == HK_NULL)
	{
		currentAttDesc.m_enabledBy = newAttDesc.m_enabledBy;
	}

	if ( currentAttDesc.m_forcedType == hctAttributeDescription::LEAVE )
	{
		currentAttDesc.m_forcedType = newAttDesc.m_forcedType;
		currentAttDesc.m_enum = newAttDesc.m_enum;
	}

	if ( currentAttDesc.m_floatScale == 0.0f )
	{
		currentAttDesc.m_floatScale = newAttDesc.m_floatScale;
	}

	// We do a bitwise OR with the hint
	currentAttDesc.m_hint = (hctAttributeDescription::Hint) ( (int) currentAttDesc.m_hint | (int) newAttDesc.m_hint );
}


void hctAttributeProcessingUtil::processAttributeGroup (hkxAttributeGroup& attrGroup)
{
	const char* groupName = attrGroup.m_name;
	if( !groupName )
	{
		return;
	}

	// Get the attribute group description. Will be NULL if not present in the XML.
	hctAttributeGroupDescription* attrGroupDesc = m_database.findAttributeDescriptionGroupByName( groupName );

	hkArray<hkxAttribute> newAttributes;
	// Start by copying the attributes to the new array
	{
		for (int i=0; i<attrGroup.m_numAttributes; ++i)
		{
			newAttributes.pushBack(attrGroup.m_attributes[i]);
		}
	}


	// 1 - Merge _X,_Y,_Z to vector
	mergeXYZToVector (newAttributes);

	// 2 - Scale floats
	scaleFloats (newAttributes, attrGroupDesc);

	// 3 - Use Force types
	enforceTypes (newAttributes, attrGroupDesc);

	// 4 - Merge _Trans,_Rot to matrix3  (doesn't depend on desc directly, but type may have changed in theory in prev pass)
	mergeTransAndRotToMatrix (newAttributes);

	// 5 - Check pairs of attributes ("name", "changeName").
	// Removes "name" depending on the value of "changeName". Always removes "changeName"
	enforceChangePairs (newAttributes);

	// 6 - Remove using "enabled by" property (deprecated by the above)
	enforceEnabledBy (newAttributes, attrGroupDesc);

	// 7 - Enforce Hints
	enforceHints (newAttributes, attrGroupDesc);

	// Deallocate current attribute list
	TRACK_MEMORY_DELETE (attrGroup.m_attributes);

	// Copy new list over
	attrGroup.m_attributes = TRACK_MEMORY_NEW_ARRAY(hkxAttribute, newAttributes.getSize());
	hkString::memCpy(attrGroup.m_attributes, newAttributes.begin(), newAttributes.getSize()*sizeof(hkxAttribute));
	attrGroup.m_numAttributes = newAttributes.getSize();
}


void hctAttributeProcessingUtil::scaleFloats (hkArray<hkxAttribute>& attributes, const struct hctAttributeGroupDescription* attrGroupDesc)
{
	if (!attrGroupDesc)
	{
		// No further instructions, leave it as it is
		return;
	}

	for( int i=0; i<attributes.getSize(); ++i )
	{
		// The attribute is not in the database? do nothing
		hctAttributeDescription *attrDesc = attrGroupDesc->findAttributeDescriptionByName(attributes[i].m_name);
		if (!attrDesc)
		{
			continue;
		}

		// The scale is 0.0 (not defined) >? do nothing
		if (attrDesc->m_floatScale == 0.0f)
		{
			continue;
		}

		const hkClass* attrClass = attributes[i].m_value.m_class;

		// Float attributes : scale
		if (attrClass == &hkxAnimatedFloatClass )
		{
			hkxAnimatedFloat* animatedFloat = reinterpret_cast<hkxAnimatedFloat*> (attributes[i].m_value.m_object);

			for (int f=0; f<animatedFloat->m_numFloats; f++)
			{
				animatedFloat->m_floats[f] *= attrDesc->m_floatScale;
			}
		}

		// Vector attributes (euler) : scale
		if (attrClass == &hkxAnimatedVectorClass )
		{
			hkxAnimatedVector* animatedVector = reinterpret_cast<hkxAnimatedVector*> (attributes[i].m_value.m_object);

			for (int v=0; v<animatedVector->m_numVectors; v++)
			{
				animatedVector->m_vectors[v].mul4(attrDesc->m_floatScale);
			}
		}

	}
}

void hctAttributeProcessingUtil::mergeXYZToVector (hkArray<hkxAttribute>& attributes)
{
	for( int i=0; i<attributes.getSize(); ++i )
	{
		// Get base name if any (look for underscore)
		hkString basename( attributes[i].m_name );
		int li = basename.lastIndexOf( '_' );
		if( li == -1 ) continue;

		basename = basename.substr(0, li);

		// Search for translation/rotation pairs
		int xIndex = -1;
		int yIndex = -1;
		int zIndex = -1;

		for( int k=i; k<attributes.getSize(); ++k )
		{
			if( ( basename + "_X" ).compareToIgnoreCase( attributes[k].m_name ) == 0 )
			{
				xIndex = k;
			}
			else if( ( basename + "_Y" ).compareToIgnoreCase( attributes[k].m_name ) == 0 )
			{
				yIndex = k;
			}
			else if ( (basename + "_Z").compareToIgnoreCase(attributes[k].m_name) == 0)
			{
				zIndex = k;
			}
		}

		// One of the attributes should be this one; otherwise continue
		if ((xIndex!=i) && (yIndex!=i) && (zIndex!=i))
		{
			continue;
		}

		// Process the pairs
		if ( (xIndex>=0) && (yIndex>=0) && (zIndex>=0))
		{
			// Check the types
			if (attributes[xIndex].m_value.m_class != &hkxAnimatedFloatClass)
			{
				HK_REPORT("Attribute with _X postfix should be of type Float");
				continue;
			}

			if (attributes[yIndex].m_value.m_class != &hkxAnimatedFloatClass)
			{
				HK_REPORT("Attribute with _Y postfix should be of type Float");
				continue;
			}

			if (attributes[zIndex].m_value.m_class != &hkxAnimatedFloatClass)
			{
				HK_REPORT("Attribute with _Z postfix should be of type Float");
				continue;
			}

			hkxAnimatedFloat* animX = (hkxAnimatedFloat*) attributes[xIndex].m_value.m_object;
			hkxAnimatedFloat* animY = (hkxAnimatedFloat*) attributes[yIndex].m_value.m_object;
			hkxAnimatedFloat* animZ = (hkxAnimatedFloat*) attributes[zIndex].m_value.m_object;

			if ( (animX->m_numFloats != animY->m_numFloats ) || (animX->m_numFloats != animZ->m_numFloats) )
			{
				HK_REPORT("Mismatched number of animated elements in x/y/z attributes");
				continue;
			}

			// Build the animated matrix
			hkxAnimatedVector* animatedVector = TRACK_MEMORY_NEW(hkxAnimatedVector);
			{
				animatedVector->m_vectors = TRACK_MEMORY_NEW_ARRAY(hkVector4, animX->m_numFloats);
				animatedVector->m_numVectors = animX->m_numFloats;

				// Assume that if the floats were distances, this is a vector in space
				if ((animX->m_hint & hkxAttribute::HINT_SCALE) != 0)
				{
					animatedVector->m_hint = hkxAttribute::HINT_TRANSFORM_AND_SCALE;
				}
				else
				{
					animatedVector->m_hint = hkxAttribute::HINT_NONE;
				}

				for( int v=0; v<animatedVector->m_numVectors; ++v )
				{
					const hkReal x = animX->m_floats[v];
					const hkReal y = animY->m_floats[v];
					const hkReal z = animZ->m_floats[v];
					animatedVector->m_vectors[v].set(x,y,z);
				}
			}

			// Replace first hkx attribute with the vector
			{
				hkxAttribute& vectorAttribute = attributes[i];
				// Destroy the current name
				TRACK_MEMORY_DELETE(vectorAttribute.m_name);
				// Set the new name
				vectorAttribute.m_name = TRACK_MEMORY_NEW_ARRAY(char, basename.getLength());
				hkString::strCpy(vectorAttribute.m_name, basename.cString());
				// Set the type and object
				vectorAttribute.m_value.m_class = &hkxAnimatedVectorClass;
				vectorAttribute.m_value.m_object = animatedVector;
			}

			// Remove the other two attributes
			{
				// We are being overzealous and not assuming X,Y and Z are properly ordered...
				// We remove them backwards

				int rest1;
				int rest2;

				if ((zIndex<yIndex)&&(zIndex<xIndex))
				{
					rest1 = xIndex; rest2 = yIndex;
				}
				else if ((yIndex<zIndex)&&(yIndex<xIndex))
				{
					rest1 = zIndex; rest2 = xIndex;
				}
				else
				{
					rest1 = yIndex; rest2 = zIndex;
				}

				if (rest1>rest2)
				{
					attributes.removeAt(rest1);
					attributes.removeAt(rest2);
				}
				else
				{
					attributes.removeAt(rest2);
					attributes.removeAt(rest1);
				}

				// ToDo : properly deallocate memory of the removed attributes
			}
		}
	}
}

void hctAttributeProcessingUtil::mergeTransAndRotToMatrix(hkArray<hkxAttribute>& attributes)
{
	for( int i=0; i<attributes.getSize(); ++i )
	{
		// Get base name if any (loom for underscore)
		hkString basename( attributes[i].m_name );
		int li = basename.lastIndexOf( '_' );
		if( li == -1 ) continue;

		basename = basename.substr(0, li);

		// Search for translation/rotation pairs
		int translationIndex = -1;
		int rotationIndex = -1;

		for( int k=i; k<attributes.getSize(); ++k )
		{
			if( ( basename + "_Trans" ).compareToIgnoreCase( attributes[k].m_name ) == 0 )
			{
				translationIndex = k;
			}
			else if( ( basename + "_Rot" ).compareToIgnoreCase( attributes[k].m_name ) == 0 )
			{
				rotationIndex = k;
			}
		}

		// One of the attributes should be this one; otherwise continue
		if ((translationIndex!=i) && (rotationIndex!=i))
		{
			continue;
		}

		// Process the pairs
		if ( (translationIndex>=0) && (rotationIndex>=0) )
		{
			// Check the types
			if (attributes[translationIndex].m_value.m_class != &hkxAnimatedVectorClass)
			{
				HK_REPORT("Attribute with _Trans postfix should be of type Vector");
				continue;
			}

			if (attributes[rotationIndex].m_value.m_class != &hkxAnimatedQuaternionClass)
			{
				HK_REPORT("Attribute with _Rot postfix should be of type Vector. Use \"forceType\" to convert from Euler Angles.");
				continue;
			}

			hkxAnimatedVector* animTranslation = (hkxAnimatedVector*) attributes[translationIndex].m_value.m_object;
			hkxAnimatedQuaternion* animRotation = (hkxAnimatedQuaternion*) attributes[rotationIndex].m_value.m_object;

			if( animTranslation->m_numVectors != animRotation->m_numQuaternions )
			{
				HK_REPORT("Mismatched number of animated elements in trans/rot pair");
				continue;
			}


			// Build the animated matrix
			hkxAnimatedMatrix* animatedMatrix = TRACK_MEMORY_NEW(hkxAnimatedMatrix);
			{
				animatedMatrix->m_matrices = TRACK_MEMORY_NEW_ARRAY(hkMatrix4, animTranslation->m_numVectors);
				animatedMatrix->m_numMatrices = animTranslation->m_numVectors;
				animatedMatrix->m_hint = hkxAttribute::HINT_TRANSFORM_AND_SCALE;
				for( int m=0; m<animatedMatrix->m_numMatrices; ++m )
				{
					hkVector4 translation = animTranslation->m_vectors[m];
					hkQuaternion rotation = animRotation->m_quaternions[m];
					hkQsTransform qsTransform(translation, rotation);
					qsTransform.get4x4ColumnMajor((hkReal*)&animatedMatrix->m_matrices[m]);
				}
			}

			// Replace first hkx attribute with the matrix
			{
				hkxAttribute& matrixAttribute = attributes[i];
				// Destroy the current name
				TRACK_MEMORY_DELETE(matrixAttribute.m_name);
				// Set the new name
				matrixAttribute.m_name = TRACK_MEMORY_NEW_ARRAY(char, basename.getLength());
				hkString::strCpy(matrixAttribute.m_name, basename.cString());
				// Set the type and object
				matrixAttribute.m_value.m_class = &hkxAnimatedMatrixClass;
				matrixAttribute.m_value.m_object = animatedMatrix;
			}

			// Remove the second attribute
			{
				int secondAttrIdx = (translationIndex==i) ? rotationIndex : translationIndex;
				attributes.removeAt(secondAttrIdx);
				// ToDo : properly deallocate memory of the removed attribute
			}
		}
	}
}

inline int _findAttributeByName (const hkArray<hkxAttribute>& attributes, const char* name)
{
	for (int i=0; i<attributes.getSize(); ++i)
	{
		if (hkString::strCasecmp(attributes[i].m_name, name)==0)
		{
			return i;
		}
	}

	return -1;
}

inline const hkClass* _attrTypeToClass (hctAttributeDescription::ForcedType type)
{
	switch (type)
	{
		case hctAttributeDescription::FORCE_BOOL:
		{
			return &hkxSparselyAnimatedBoolClass;
		}
		case hctAttributeDescription::FORCE_INT:
		{
			return &hkxSparselyAnimatedIntClass;
		}
		case hctAttributeDescription::FORCE_ENUM:
		{
			return &hkxSparselyAnimatedEnumClass;
		}
		case hctAttributeDescription::FORCE_STRING:
		{
			return &hkxSparselyAnimatedStringClass;
		}
		case hctAttributeDescription::FORCE_FLOAT:
		{
			return &hkxAnimatedFloatClass;
		}
		case hctAttributeDescription::FORCE_VECTOR:
		{
			return &hkxAnimatedVectorClass;
		}
		case hctAttributeDescription::FORCE_MATRIX:
		{
			return &hkxAnimatedMatrixClass;
		}
		case hctAttributeDescription::FORCE_QUATERNION:
		{
			return &hkxAnimatedQuaternionClass;
		}
		default: // LEAVE
		{
			return HK_NULL;
		}
	}
}

void hctAttributeProcessingUtil::enforceTypes (hkArray<hkxAttribute>& attributes, const hctAttributeGroupDescription* attrGroupDesc)
{
	if (!attrGroupDesc)
	{
		// No instructions, leave it as it is
		return;
	}

	for (int i=0; i<attrGroupDesc->m_numAttributeDescriptions; ++i)
	{
		const hctAttributeDescription& attrDesc = attrGroupDesc->m_attributeDescriptions[i];

		const int attrIndex = _findAttributeByName (attributes, attrDesc.m_name);
		if (attrIndex<0)
		{
			continue;
		}

		const hkClass* currentAttrClass = attributes[attrIndex].m_value.m_class;
		const hkClass* desiredAttrClass = _attrTypeToClass(attrDesc.m_forcedType);

		if (!desiredAttrClass || (currentAttrClass == desiredAttrClass))
		{
			continue;
		}

		// Supported conversions

		// Vector (EULER) to Quaternion
		if ( (currentAttrClass == &hkxAnimatedVectorClass) && (desiredAttrClass == &hkxAnimatedQuaternionClass))
		{
			hkxAnimatedVector* oldAttribute = (hkxAnimatedVector*) attributes[attrIndex].m_value.m_object;
			hkxAnimatedQuaternion* newAttribute = convertEulerToQuaternion (oldAttribute);

			attributes[attrIndex].m_value.m_class = desiredAttrClass;
			attributes[attrIndex].m_value.m_object = newAttribute;

			continue;
		}

		// Matrix to Quaternion
		if ( (currentAttrClass == &hkxAnimatedMatrixClass) && (desiredAttrClass == &hkxAnimatedQuaternionClass))
		{
			hkxAnimatedMatrix* oldAttribute = (hkxAnimatedMatrix*) attributes[attrIndex].m_value.m_object;
			hkxAnimatedQuaternion* newAttribute = convertMatrixToQuaternion (oldAttribute);

			attributes[attrIndex].m_value.m_class = desiredAttrClass;
			attributes[attrIndex].m_value.m_object = newAttribute;

			continue;
		}

		// Int to Enum
		if ( (currentAttrClass == &hkxSparselyAnimatedIntClass) && (desiredAttrClass == &hkxSparselyAnimatedEnumClass) && (attrDesc.m_enum!=HK_NULL))
		{
			hkxSparselyAnimatedInt* oldAttribute = (hkxSparselyAnimatedInt*) attributes[attrIndex].m_value.m_object;
			hkxSparselyAnimatedEnum* newAttribute = convertIntToEnum (oldAttribute, attrDesc.m_enum);

			attributes[attrIndex].m_value.m_class = desiredAttrClass;
			attributes[attrIndex].m_value.m_object = newAttribute;

			continue;
		}

		// Enum To String
		if ( (currentAttrClass == &hkxSparselyAnimatedEnumClass) && (desiredAttrClass == &hkxSparselyAnimatedStringClass))
		{
			hkxSparselyAnimatedEnum* oldAttribute = (hkxSparselyAnimatedEnum*) attributes[attrIndex].m_value.m_object;
			hkxSparselyAnimatedString* newAttribute = convertEnumToString (oldAttribute);

			attributes[attrIndex].m_value.m_class = desiredAttrClass;
			attributes[attrIndex].m_value.m_object = newAttribute;

			continue;
		}

		// Int To String (requires enum definition)
		if ( (currentAttrClass == &hkxSparselyAnimatedIntClass) && (desiredAttrClass == &hkxSparselyAnimatedStringClass) && (attrDesc.m_enum!=HK_NULL))
		{
			hkxSparselyAnimatedInt* oldAttribute = (hkxSparselyAnimatedInt*) attributes[attrIndex].m_value.m_object;
			hkxSparselyAnimatedString* newAttribute = convertIntToString (oldAttribute, attrDesc.m_enum);

			attributes[attrIndex].m_value.m_class = desiredAttrClass;
			attributes[attrIndex].m_value.m_object = newAttribute;

			continue;
		}



		// Unsupported conversions
		// We leave Attribute untouched.. or should we remove it?
	}

}

void hctAttributeProcessingUtil::enforceChangePairs (hkArray<hkxAttribute>& attributes)
{
	for (int i=0; i<attributes.getSize(); ++i)
	{
		// Look for an attribute called changeNAME
		hkString changeName = hkString ("change") + hkString(attributes[i].m_name);

		int enablerAttrIndex = _findAttributeByName (attributes, changeName.cString());

		if (enablerAttrIndex<0)
		{
			// Not found? continue
			continue;
		}

		// Look whether we are enabling or not
		bool enabled = true;
		{
			if (attributes[enablerAttrIndex].m_value.m_class == &hkxSparselyAnimatedBoolClass)
			{
				hkxSparselyAnimatedBool* enabler = (hkxSparselyAnimatedBool*) attributes[enablerAttrIndex].m_value.m_object;
				enabled = enabler->m_bools[0];
			}
			else
			{
				if (attributes[enablerAttrIndex].m_value.m_class == &hkxSparselyAnimatedIntClass)
				{
					hkxSparselyAnimatedInt* enabler = (hkxSparselyAnimatedInt*) attributes[enablerAttrIndex].m_value.m_object;
					enabled = enabler->m_ints[0] != 0;
				}
			}
		}

		// No matter what, remove the enabler ("changeXXXX") attribute
		{
			// removeAtAndCopy keeps the order in the array
			attributes.removeAtAndCopy(enablerAttrIndex);

			// Ensure "i" is up-to-date
			if (enablerAttrIndex<i)
			{
				--i;
			}
		}

		// And, if it was set to false, remove this attribute as well
		if (!enabled)
		{
			// removeAtAndCopy keeps the order in the array
			attributes.removeAtAndCopy(i);
		}
	}
}

void hctAttributeProcessingUtil::enforceEnabledBy (hkArray<hkxAttribute>& attributes, const hctAttributeGroupDescription* attrGroupDesc)
{
	if (!attrGroupDesc)
	{
		// No further instructions, leave it as it is
		return;
	}

	for (int i=0; i<attrGroupDesc->m_numAttributeDescriptions; ++i)
	{
		const hctAttributeDescription& attrDesc = attrGroupDesc->m_attributeDescriptions[i];

		if (attrDesc.m_enabledBy== HK_NULL)
		{
			continue;
		}

		const int enablerAttrIndex = _findAttributeByName (attributes, attrDesc.m_enabledBy);
		if (enablerAttrIndex<0)
		{
			continue;
		}

		// Look whether we are enabling or not
		bool enabled = true;
		{
			if (attributes[enablerAttrIndex].m_value.m_class == &hkxSparselyAnimatedBoolClass)
			{
				hkxSparselyAnimatedBool* enabler = (hkxSparselyAnimatedBool*) attributes[enablerAttrIndex].m_value.m_object;
				enabled = enabler->m_bools[0];
			}
			else
			{
				if (attributes[enablerAttrIndex].m_value.m_class == &hkxSparselyAnimatedIntClass)
				{
					hkxSparselyAnimatedInt* enabler = (hkxSparselyAnimatedInt*) attributes[enablerAttrIndex].m_value.m_object;
					enabled = enabler->m_ints[0] != 0;
				}
			}
		}

		// If we are enabled, do nothing
		if (enabled)
		{
			continue;
		}

		// Otherwise remove the other attribute
		{
			const int attrIndex = _findAttributeByName (attributes, attrDesc.m_name);
			if (attrIndex<0)
			{
				continue;
			}

			// TODO : Destroy attribute data

			attributes.removeAt(attrIndex);
		}

	}
}

void hctAttributeProcessingUtil::enforceHints (hkArray<hkxAttribute>& attributes, const hctAttributeGroupDescription* attrGroupDesc)
{
	if (!attrGroupDesc)
	{
		// No instructions, leave it as it is
		return;
	}

	for (int i=0; i<attrGroupDesc->m_numAttributeDescriptions; ++i)
	{
		const hctAttributeDescription& attrDesc = attrGroupDesc->m_attributeDescriptions[i];

		const int attrIndex = _findAttributeByName (attributes, attrDesc.m_name);
		if (attrIndex<0)
		{
			continue;
		}

		const hkClass* attrClass = attributes[attrIndex].m_value.m_class;
		void* attributeObject = attributes[attrIndex].m_value.m_object;

		if (attrDesc.m_clearHints)
		{
			if (attrClass == &hkxAnimatedFloatClass)
			{
				((hkxAnimatedFloat*) attributeObject)->m_hint = hkxAttribute::HINT_NONE;
			}

			if (attrClass == &hkxAnimatedVectorClass)
			{
				((hkxAnimatedVector*) attributeObject)->m_hint = hkxAttribute::HINT_NONE;
			}

			if (attrClass == &hkxAnimatedMatrixClass)
			{
				((hkxAnimatedMatrix*) attributeObject)->m_hint = hkxAttribute::HINT_NONE;
			}
		}

		hctAttributeDescription::Hint desiredHint = attrDesc.m_hint;

		if (desiredHint==hctAttributeDescription::HINT_IGNORE)
		{
			// Remove attribute according to hint
			attributes.removeAt(attrIndex);
			continue;
		}

		// Otherwise, we do an OR of the hint flags
		// We need to cast to the right type though...

		if (attrClass == &hkxAnimatedFloatClass)
		{
			(int&) ((hkxAnimatedFloat*) attributeObject)->m_hint |= (int) desiredHint;
			continue;
		}

		if (attrClass == &hkxAnimatedVectorClass)
		{
			(int&) ((hkxAnimatedVector*) attributeObject)->m_hint |= (int) desiredHint;
			continue;
		}

		if (attrClass == &hkxAnimatedMatrixClass)
		{
			(int&) ((hkxAnimatedMatrix*) attributeObject)->m_hint |= (int) desiredHint;
			continue;
		}
	}
}

// Conversions
hkxAnimatedQuaternion* hctAttributeProcessingUtil::convertEulerToQuaternion(hkxAnimatedVector* animatedVector)
{
	hkxAnimatedQuaternion* animatedQuaternion = TRACK_MEMORY_NEW(hkxAnimatedQuaternion);

	const int numQuaternions = animatedVector->m_numVectors;
	animatedQuaternion->m_numQuaternions = numQuaternions;
	animatedQuaternion->m_quaternions = TRACK_MEMORY_NEW_ARRAY(hkQuaternion, numQuaternions);

	for (int i=0; i<numQuaternions; i++)
	{
		const hkReal vx = animatedVector->m_vectors[i](0);
		const hkReal vy = animatedVector->m_vectors[i](1);
		const hkReal vz = animatedVector->m_vectors[i](2);

		hkQuaternion qx( hkVector4(1,0,0), vx );
		hkQuaternion qy( hkVector4(0,1,0), vy );
		hkQuaternion qz( hkVector4(0,0,1), vz );

		// Create composite quaternion
		hkQuaternion& q = animatedQuaternion->m_quaternions[i];
		q.setMul( qz, qy );
		q.mul( qx );
	}

	// remove the array of vectors
	TRACK_MEMORY_DELETE(animatedVector->m_vectors);
	// remove the old attribute
	TRACK_MEMORY_DELETE(animatedVector);

	return animatedQuaternion;
}

hkxAnimatedQuaternion* hctAttributeProcessingUtil::convertMatrixToQuaternion (struct hkxAnimatedMatrix* animatedMatrix)
{
	hkxAnimatedQuaternion* animatedQuaternion = TRACK_MEMORY_NEW(hkxAnimatedQuaternion);

	const int numQuaternions = animatedMatrix->m_numMatrices;
	animatedQuaternion->m_numQuaternions = numQuaternions;
	animatedQuaternion->m_quaternions = TRACK_MEMORY_NEW_ARRAY(hkQuaternion, numQuaternions);

	for (int i=0; i<numQuaternions; i++)
	{
		hkMatrix4 mat = animatedMatrix->m_matrices[i];

		hkRotation rot;
		rot.setCols(mat.getColumn(0),mat.getColumn(1),mat.getColumn(2));

		animatedQuaternion->m_quaternions[i] = hkQuaternion(rot);
	}

	// remove the array of vectors
	TRACK_MEMORY_DELETE(animatedMatrix->m_matrices);
	// remove the old attribute
	TRACK_MEMORY_DELETE(animatedMatrix);

	return animatedQuaternion;
}

struct hkxSparselyAnimatedString* hctAttributeProcessingUtil::convertEnumToString (struct hkxSparselyAnimatedEnum* animatedEnum)
{
	return convertIntToString (animatedEnum, animatedEnum->m_type);
};

struct hkxSparselyAnimatedString* hctAttributeProcessingUtil::convertIntToString (struct hkxSparselyAnimatedInt* animatedInt, const class hkClassEnum* enumClass)
{
	hkxSparselyAnimatedString* animatedString = TRACK_MEMORY_NEW(hkxSparselyAnimatedString);

	const int numStrings = animatedInt->m_numInts;
	animatedString->m_numStrings = numStrings;
	animatedString->m_numTimes = numStrings;
	animatedString->m_times = animatedInt->m_times; // reuse the "times" array
	animatedString->m_strings = TRACK_MEMORY_NEW_ARRAY(hkxSparselyAnimatedString::StringType, numStrings);

	for (int i=0; i<numStrings; i++)
	{
		int value = animatedInt->m_ints[i];
		const char* name = HK_NULL;
		enumClass->getNameOfValue(value, &name);
		const int nameLen = hkString::strLen(name);
		animatedString->m_strings[i].m_string = TRACK_MEMORY_NEW_ARRAY(char, nameLen+1);
		hkString::strNcpy( animatedString->m_strings[i].m_string, name, nameLen+1); // no unicode safe
	}

	// remove array of ints
	TRACK_MEMORY_DELETE(animatedInt->m_ints);
	// remove old attribute
	TRACK_MEMORY_DELETE(animatedInt);

	return animatedString;

};


hkxSparselyAnimatedEnum* hctAttributeProcessingUtil::convertIntToEnum (hkxSparselyAnimatedInt* animatedInt, const hkClassEnum* enumClass)
{
	hkxSparselyAnimatedEnum* animatedEnum = TRACK_MEMORY_NEW(hkxSparselyAnimatedEnum);

	// We know animated enums inherit from animated int, so we can do a normal memcopy
	hkString::memCpy(animatedEnum, animatedInt, sizeof(hkxSparselyAnimatedInt));

	// and then fill the class enum pointer
	animatedEnum->m_type = enumClass;

	// We could check the enum range here...

	// remove the old attribute
	TRACK_MEMORY_DELETE(animatedInt);

	return animatedEnum;
}

void hctAttributeProcessingUtil::processAttributes (hkxAttributeHolder* attributeHolder)
{

	//
	// First, merge any groups with the same name
	//
	{
		// Use an array interface to make things easier
		hkArray<hkxAttributeGroup> groups(attributeHolder->m_attributeGroups, attributeHolder->m_numAttributeGroups, attributeHolder->m_numAttributeGroups);

		// We assume attribute groups are ordered hkX, hkX, hkXMerge, hkXMerge, hkX, hkxMerge..
		// That is, mergeable groups should always follow the group they should merge.
		for (int firstGroupIdx = 0; firstGroupIdx < groups.getSize(); firstGroupIdx++)
		{
			const hkxAttributeGroup& firstGroup = groups [firstGroupIdx];
			const hkString firstGroupName = hkString(firstGroup.m_name).asLowerCase();

			if (firstGroupName.endsWith("merge"))
			{
				HK_WARN_ALWAYS(0xabbaa6c9,"Cannot merge attribute group "<<firstGroup.m_name);
				continue;

			}
			for (int secondGroupIdx = firstGroupIdx+1; secondGroupIdx < groups.getSize(); secondGroupIdx++)
			{
				const hkxAttributeGroup& secondGroup = groups [secondGroupIdx];
				const hkString secondGroupName = hkString(secondGroup.m_name).asLowerCase();

				// We found another group of the same type, nothing to merge further on
				if (secondGroupName==firstGroupName)
				{
					break;
				}

				// Second group
				if (secondGroupName == (firstGroupName + "merge"))
				{
					hkxAttributeGroup newGroup;
					mergeTwoAttributeGroups(firstGroup, secondGroup, newGroup);

					groups[firstGroupIdx] = newGroup;
					groups.removeAtAndCopy(secondGroupIdx); //EXP-1144: removeAtAndCopy vs. removeAt
				}
			}
		}

		attributeHolder->m_numAttributeGroups = groups.getSize();
	}

	//
	// Second, process all the attribute groups
	//
	{
		const int numGroups = attributeHolder->m_numAttributeGroups;
		for( int i=0; i<numGroups; ++i )
		{
			processAttributeGroup( attributeHolder->m_attributeGroups[i] );
		}
	}
}

void hctAttributeProcessingUtil::mergeTwoAttributeGroups(const hkxAttributeGroup& groupOne, const hkxAttributeGroup& groupTwo, hkxAttributeGroup& mergedGroup)
{
	// Name : Should be the same, so take one and destroy other
	{
		mergedGroup.m_name = groupOne.m_name;
		TRACK_MEMORY_DELETE(groupTwo.m_name);
	}

	// Attributes: store them in an hkArray, then copy
	{
		hkArray<hkxAttribute> mergedAttributes;

		// We assume attributes are not duplicated inside a single group, but may be duplicated on each group
		// We start by merging the first group, comparing with second one, removing
		for (int firstAttrIdx=0; firstAttrIdx<groupOne.m_numAttributes; firstAttrIdx++)
		{
			hkxAttribute firstAttr = groupOne.m_attributes[firstAttrIdx];

			const char* attrName = firstAttr.m_name;

			int secondAttrIdx = groupTwo.findAttributeIndexByName(attrName);

			// We only add attributes if they are not in the second group
			if (secondAttrIdx<0)
			{
				mergedAttributes.pushBack(firstAttr);
			}
			else
			{
				// TODO: remove the attribute to save memory...
			}
		}

		// From the second group, we add all attributes
		for (int secondAttrIdx=0; secondAttrIdx<groupTwo.m_numAttributes; secondAttrIdx++)
		{
			hkxAttribute secondAttr = groupTwo.m_attributes[secondAttrIdx];
			mergedAttributes.pushBack(secondAttr);
		}

		// Copy attributes to new attribute group
		{
			mergedGroup.m_numAttributes = mergedAttributes.getSize();
			mergedGroup.m_attributes = TRACK_MEMORY_NEW_ARRAY(hkxAttribute, mergedGroup.m_numAttributes);
			const int numBytes = sizeof(hkxAttribute)*mergedGroup.m_numAttributes;
			hkString::memCpy(mergedGroup.m_attributes, mergedAttributes.begin(), numBytes);
		}

		// Deallocate previous arrays
		{
			TRACK_MEMORY_DELETE(groupOne.m_attributes);
			TRACK_MEMORY_DELETE(groupTwo.m_attributes);
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
