/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_SERIALIZE_VERSIONUTIL_H
#define HK_SERIALIZE_VERSIONUTIL_H

#include <Common/Serialize/Version/hkVersionRegistry.h>

class hkObjectUpdateTracker;
class hkClassNameRegistry;
class hkPackfileReader;

/// Versioning utility functions and structures.
namespace hkVersionUtil
{
		/// Get the current sdk version as written in packfiles.
	const char* HK_CALL getCurrentVersion();

		/// Copies the old named member to the new named member.
		/// The members must have identical sizes.
	void HK_CALL renameMember( hkVariant& oldObj, const char* oldName, hkVariant& newObj, const char* newName );

		/// Copy defaults for new members.
		/// For each member in newClass which is not in oldClass and which
		/// has a specified default, copy it in into obj.
	void HK_CALL copyDefaults( void* obj, const hkClass& oldClass, const hkClass& newClass );

		/// Find variants in obj and update their class pointers.
		/// For each variant member in obj, update its class to the class
		/// from the given registry.
		/// ie. obj.m_variant.m_class = reg.getClassByName( obj.m_variant.m_class->getName() )
	void HK_CALL updateVariantClassPointers( void* obj, const hkClass& klass, hkClassNameRegistry& reg, int numObj=1 );

		/// Signature of the generic version functions.
	typedef void (HK_CALL *VersionFunc)(hkVariant& obj, hkVariant& newObj, hkObjectUpdateTracker& tracker);

		/// Specifies how the versioning should be handled.
	enum VersionFlags
	{
			/// The object is neither copied, nor defaults applied.
		VERSION_MANUAL = 1<<1,
			/// The object can be updated in place and has defaults applied.
		VERSION_INPLACE = 1<<2,
			///	The object is copied and defaults applied.
		VERSION_COPY = 1<<3,
			/// The object is to be removed and all references to it nullified.
		VERSION_REMOVED = 1<<4,
			/// The object contains a variant.
		VERSION_VARIANT = 1<<5
	};

	struct ClassRename
	{
		const char* oldName;
		const char* newName;

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SERIALIZE, ClassRename );
	};

		/// Describes the versioning changes for a single type.
	struct ClassAction
	{
			/// Signature before updating.
		hkUint32 oldSignature;
			/// Signature after updating.
		hkUint32 newSignature;
			/// How should the type be versioned.
		int /*VersionFlags*/ versionFlags;
			/// The class name as it appears in the old version.
		const char* oldClassName;
			/// Custom function to call or HK_NULL.
		VersionFunc versionFunc;

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SERIALIZE, ClassAction );
	};

	struct UpdateDescription
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SERIALIZE, UpdateDescription );

			/// Null or null-terminated list of renames.
		const ClassRename* renames;

			/// Null or null terminated list of actions 
		const ClassAction* actions;

			/// New versions of classes.
		hkVersionRegistry::ClassList* newClassList;

			/// Find the 
		const hkVersionUtil::ClassAction* findActionForClass( const hkClass& classIn ) const;
	};

		/// Utility function to recompute member offsets.
	void HK_CALL recomputeClassMemberOffsets( hkClass*const* classes, int classVersion );

		/// Low level interface to versioning.
		/// Apply the updateDescriptions to each object in objectsInOut.
		/// Note that the size and ordering of objectsInOut may change.
	hkResult HK_CALL updateSingleVersion(
		hkArray<hkVariant>& objectsInOut,
		hkObjectUpdateTracker& tracker,
		const UpdateDescription& updateDescription );

		/// Search for and apply a sequence of updates.
		/// Given fromVersion and toVersion, search for a sequence
		/// of updates which will convert between them. Calls
		/// updateSingleVersion for each step in the sequence.
	hkResult HK_CALL updateBetweenVersions(
		hkArray<hkVariant>& objectsInOut,
		hkObjectUpdateTracker& tracker,
		const hkVersionRegistry& reg,
		const char* fromVersion,
		const char* toVersion = HK_NULL );

		/// Update the packfile contents to the latest version in reg.
		/// Usually the the hkVersionRegistry singleton is used for reg.
		/// Updating will fail if a binary packfile has been stripped of its
		/// table of contents. Xml packfiles can always be updated.
	hkResult HK_CALL updateToCurrentVersion(
		hkPackfileReader& reader,
		const hkVersionRegistry& reg );
}

#endif // HK_SERIALIZE_VERSIONUTIL_H

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
