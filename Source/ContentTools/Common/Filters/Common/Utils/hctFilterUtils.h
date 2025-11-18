/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HAVOK_FILTER_UTILS__H
#define HAVOK_FILTER_UTILS__H

#include <ContentTools/Common/Filters/Common/Filter/hctFilterDescriptor.h>

	/// A collection of useful utility methods for the filters and exporters
class hctFilterUtils
{
	public:		
			
			/// Get the position of the cinfo data (i.e. not the local fixups) in the options data block.
		static void* interpretOptions( void* data );

			/// Write the options data to memory. A pointer to the data is returned.
		static void* writeOptionsXml( const hkClass& klass, const void* data, hkArray<char>& buffer, const char* filterName );

			/// Read the options data from memory.
		static hkResult readOptionsXml ( const void* optionData, const int optionDataSize, hkArray<char>& buffer, const hkClass klass );

			/// Create a complete copy of an entire filter set,
			/// so that processing does not affect the original data.
		static void* deepCopyObject ( const class hctFilterClassRegistry& classReg, const void* obj, const hkClass* klass, hkArray<char>& storage);
		
			/// Create an array using the items listed in the delimited string.
		static void createArrayFromDelimitedString( hkObjectArray<hkString>& buf, const char* delimitedString, const char delimiter );

			/// Create a single string from the given array of strings, using "delimiter" to split the strings.
		static void createDelimitedStringFromArray( const hkObjectArray<hkString>& array, const char* delimiter, hkString& delimitedStringOut);

			/// Returns the path to the specified asset file. It does so by looking for an hkxEnvironment in the asset and otherwise
			/// by looking at the asset name in the hkxScene object.
		static void getAssetFolder( const hkRootLevelContainer& rootLevelContainer, hkString& assetFolderOut );

			/// Given a filename, it detects whether it is relative or not to the asset path, and in that case
			/// it preppends it.
		static void getFullPath ( const hkRootLevelContainer& rootLevelContainer, const char* userPath, hkString& fullPathOut);

			/// Get the path to the specified file relative to the specified asset path.
		static void getReducedFilename( const char* fname, const hkString& assetPath, hkString& reducedName );

			/// Looks for an hkxEnvironment inside the given contents, and queries for the given variable. If not present,
			/// it will try to use data in hkxScene. Returns HK_NULL if no environment was found or the variable is undefined.
		static const char* getEnvironmentVariable (const hkRootLevelContainer& contents, const char* variable);

			/// Given an hkxEnvironment and an input string, it returns (through outputString) the string with all substrings 
			/// of the form \$(name) replaced by its corresponding value in the environment. Returns true if all substitutions
			/// suceeded, false otherwise.
		static bool replaceVariables (const class hkxEnvironment& environment, const char* inputString, hkString& outputString, hkBool useOSEnvironment = false);

			/// Converts a category code to its string representation
		static const char* filterCategoryToString( hctFilterDescriptor::FilterCategory c );

};

#endif // HAVOK_FILTER_UTILS__H

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
