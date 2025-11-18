/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Version/hkVersionUtil.h>

#include <Common/Base/Config/hkConfigVersion.h>
#include <Common/Base/Reflection/hkClassMemberAccessor.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Base/System/Io/Writer/Buffered/hkBufferedStreamWriter.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Serialize/Copier/hkObjectCopier.h>
#include <Common/Serialize/Serialize/hkRelocationInfo.h>
#include <Common/Base/Reflection/Registry/hkClassNameRegistry.h>
#include <Common/Serialize/Version/hkObjectUpdateTracker.h>
#include <Common/Serialize/Util/hkVersionCheckingUtils.h>
#include <Common/Serialize/Packfile/hkPackfileReader.h>
#include <Common/Serialize/Util/hkRenamedClassNameRegistry.h>
#include <Common/Serialize/Util/hkSerializeLog.h>

const char* hkVersionUtil::getCurrentVersion()
{
	return HAVOK_SDK_VERSION_STRING;
}

const hkVersionUtil::ClassAction* hkVersionUtil::UpdateDescription::findActionForClass( const hkClass& classIn ) const
{
	// we match all names in the hierarchy
	hkStringMap<const hkClass*> hierarchyNames;
	{
		const hkClass* c = &classIn;
		while(  c != HK_NULL )
		{
			hierarchyNames.insert(c->getName(), c);
			c = c->getParent();
		}
	}
		
	// the first match for any base class wins
	const hkVersionUtil::ClassAction* action = this->actions;
	for( ; action->oldClassName != HK_NULL; ++action )
	{
		if( const hkClass* c = hierarchyNames.getWithDefault( action->oldClassName, HK_NULL ) )
		{
//			HK_ON_DEBUG(hkUint32 loadedSig = c->getSignature());
//			HK_ASSERT( 0x786cb087, (action->versionFlags & VERSION_REMOVED) || loadedSig == action->oldSignature );
			return action;
		}
	}
	return HK_NULL;
}

static void* copyObjects(
	const hkArray<hkVariant>& objectsIn,
	hkArray<hkVariant>& objectsOut,
	const hkArray<int>& objectIndices,
	hkObjectUpdateTracker& tracker )
{
	hkArray<char> buffer;
	hkOstream out(buffer);
	hkRelocationInfo relocations;
	hkPointerMap<const void*, int> overrides;

	for( int objectIndexIndex = 0; objectIndexIndex < objectIndices.getSize(); ++objectIndexIndex )
	{
		int objectIndex = objectIndices[objectIndexIndex];
		const hkVariant& oldVariant = objectsIn[objectIndex];

		hkObjectCopier copier( hkStructureLayout::HostLayoutRules, hkStructureLayout::HostLayoutRules );
		const hkClass* newClass = objectsOut[objectIndex].m_class;
		objectsOut[objectIndex].m_object = (void*)static_cast<hkUlong>(buffer.getSize()); // offset - convert to ptr later.

		overrides.insert( oldVariant.m_object, buffer.getSize() );

		copier.copyObject(oldVariant.m_object, *oldVariant.m_class,
			out.getStreamWriter(), *newClass,
			relocations );
	}

	if( buffer.getSize() ) // some versioning was done
	{
		char* versioned = hkAllocateChunk<char>( buffer.getSize(), HK_MEMORY_CLASS_EXPORT );
		tracker.addChunk(versioned, buffer.getSize(), HK_MEMORY_CLASS_EXPORT );
		hkString::memCpy( versioned, buffer.begin(), buffer.getSize() );

		// object pointers were actually stored as offsets because of resizing
		for( int objectIndexIndex = 0; objectIndexIndex < objectIndices.getSize(); ++objectIndexIndex )
		{
			int objectIndex = objectIndices[objectIndexIndex];
			hkVariant& v = objectsOut[objectIndex];
			v.m_object = versioned + hkUlong(v.m_object);
		}

		hkArray<hkRelocationInfo::Local>& local = relocations.m_local;
		for( int localIndex = 0; localIndex < local.getSize(); ++localIndex )
		{
			*(void**)(versioned + local[localIndex].m_fromOffset) = versioned + local[localIndex].m_toOffset;
		}
		hkArray<hkRelocationInfo::Global>& global = relocations.m_global;
		for( int globalIndex = 0; globalIndex < global.getSize(); ++globalIndex )
		{
			void* p = global[globalIndex].m_toAddress;
			void* from = versioned + global[globalIndex].m_fromOffset;
			tracker.objectPointedBy( p, from );
		}
		return versioned;
	}
	return HK_NULL;
}

void hkVersionUtil::renameMember( hkVariant& oldObj, const char* oldName, hkVariant& newObj, const char* newName )
{
	hkClassMemberAccessor oldMember(oldObj, oldName);
	hkClassMemberAccessor newMember(newObj, newName);
	if( oldMember.isOk() && newMember.isOk() )
	{
		HK_ASSERT(0x2912efc3, oldMember.getClassMember().getSizeInBytes() == newMember.getClassMember().getSizeInBytes() );
		hkString::memCpy( newMember.asRaw(), oldMember.asRaw(), newMember.getClassMember().getSizeInBytes() );
	}
}

void hkVersionUtil::copyDefaults( void* obj, const hkClass& oldClass, const hkClass& newClass )
{
	hkBufferedStreamWriter writer( obj, newClass.getObjectSize(), false );
	for( int memIndex = 0; memIndex < newClass.getNumMembers(); ++memIndex )
	{
		const hkClassMember& newMem = newClass.getMember(memIndex);
		if( oldClass.getMemberByName(newMem.getName()) == HK_NULL )
		{
			writer.seek( newMem.getOffset(), hkStreamWriter::STREAM_SET );
			newClass.getDefault( memIndex, &writer );
		}
	}
}

void hkVersionUtil::recomputeClassMemberOffsets( hkClass*const* classes, int classVersion )
{
	HK_ASSERT(0x67b28c08, classVersion > 0);
	hkClass::updateMetadataInplace( const_cast<hkClass**>(classes), classVersion );

	hkStructureLayout layout;
	hkPointerMap<const hkClass*, int> classesDone;
	for( int i = 0; classes[i] != HK_NULL; ++i )
	{
		layout.computeMemberOffsetsInplace( *classes[i], classesDone );
	}
}

static void updateVariantInternal( void* variantPtr, int n, const hkClassNameRegistry& reg )
{
	hkVariant* v = static_cast<hkVariant*>(variantPtr);
	for( int i = 0; i < n; ++i )
	{
		if( v[i].m_class )
		{
			v[i].m_class = reg.getClassByName( v[i].m_class->getName() );
		}
	}
}

void hkVersionUtil::updateVariantClassPointers( void* obj, const hkClass& klass, hkClassNameRegistry& reg, int numObj )
{
	for( int objIndex = 0; objIndex < numObj; ++objIndex )
	{
		for( int memberIndex = 0; memberIndex < klass.getNumMembers(); ++memberIndex )
		{
			const hkClassMember& member = klass.getMember(memberIndex);
			hkClassMemberAccessor maccess(obj, &member);
			switch( member.getType() )
			{
				case hkClassMember::TYPE_VARIANT:
				{
					int nelem = member.getCstyleArraySize() ? member.getCstyleArraySize() : 1;
					updateVariantInternal( maccess.asRaw(), nelem, reg );
					break;
				}
				case hkClassMember::TYPE_ARRAY:
				case hkClassMember::TYPE_SIMPLEARRAY:
				{
					hkClassMemberAccessor::SimpleArray& array = maccess.asSimpleArray();
					if( member.getSubType() == hkClassMember::TYPE_VARIANT )
					{
						updateVariantInternal( array.data, array.size, reg );
					}
					else if( member.getSubType() == hkClassMember::TYPE_STRUCT )
					{
						const hkClass& sclass = member.getStructClass();
						updateVariantClassPointers( array.data, sclass, reg, array.size );
					}
					break;
				}
				case hkClassMember::TYPE_STRUCT:
				{
					int nelem = member.getCstyleArraySize() ? member.getCstyleArraySize() : 1;
					const hkClass& sclass = member.getStructClass();
					updateVariantClassPointers( maccess.asRaw(), sclass, reg, nelem );
					break;
				}
				default:
				{
					// skip over all other types
				}
			}
		}
		obj = hkAddByteOffset( obj, klass.getObjectSize() );
	}
}

namespace
{
	struct ActionFromClassName : public hkStringMap<const hkVersionUtil::ClassAction*>
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, ActionFromClassName);
		ActionFromClassName(
			const hkVersionUtil::UpdateDescription& desc,
			hkArray<hkVariant>& v,
			hkArray<int>& objectEditIndicesOut )
		{
			for( int i = 0; i < v.getSize(); ++i )
			{
				const hkClass* klass = v[i].m_class;
				const hkVersionUtil::ClassAction* action = HK_NULL;
				if( this->get(klass->getName(), &action) != HK_SUCCESS )
				{
					action = desc.findActionForClass(*klass);
					this->insert( klass->getName(), action );
				}
				if( action )
				{
					objectEditIndicesOut.pushBack(i);
				}
			}
		}
	};	
}
//
// These update* functions would be more naturally placed in hkVersionRegistry, but
// we place them here so that if versioning is not used, the linker can strip all this
// code and the support functions.
//

hkResult hkVersionUtil::updateSingleVersion(
	hkArray<hkVariant>& objectsInOut,
	hkObjectUpdateTracker& tracker,
	const UpdateDescription& updateDescription )
{
	hkRenamedClassNameRegistry newClassFromOldName( updateDescription.renames, updateDescription.newClassList->getClasses() );

	// indices of objects which need to be versioned
	hkArray<int> objectEditIndices;
	ActionFromClassName actionFromClassName( updateDescription, objectsInOut, objectEditIndices );

	// additionally some objects need to be copied
	hkArray<int> objectCopyIndices;
	hkArray<int> removedIndices;
	// save a copy of old objects
	hkArray<hkVariant> oldObjects;
	oldObjects = objectsInOut;
	{
		hkArray<int> withVariantIndices;
		for( int editIndexIndex = 0; editIndexIndex < objectEditIndices.getSize(); ++editIndexIndex )
		{
			int editIndex = objectEditIndices[editIndexIndex];
			const char* oldClassName = objectsInOut[editIndex].m_class->getName();
			const ClassAction* action = actionFromClassName.getWithDefault(oldClassName, HK_NULL);
			HK_ASSERT(0x3b5dbb52, action != HK_NULL );
			const hkClass* newClass = newClassFromOldName.getClassByName( oldClassName );
			
			if( action->versionFlags & VERSION_REMOVED )
			{
				HK_ASSERT(0x41ea0ee9, newClass == HK_NULL );
				hkVariant& v = objectsInOut[editIndex];
				tracker.removeFinish( v.m_object );
				removedIndices.pushBack( editIndex );
			}
			else
			{
				objectsInOut[editIndex].m_class = newClass;
				HK_ASSERT2( 0x29b61c04, newClass != HK_NULL, "Class '" << oldClassName << "' needs to be copied but I can't find it");

				if( action->versionFlags & VERSION_MANUAL )
				{
					// manual
				}
				else if( action->versionFlags & VERSION_COPY )
				{
					objectCopyIndices.pushBack(editIndex);
				}
				else if( action->versionFlags & VERSION_INPLACE )
				{
					hkVariant& v = oldObjects[editIndex];
					hkVersionUtil::copyDefaults( v.m_object, *v.m_class, *newClass );
					tracker.removeFinish( v.m_object );
					tracker.addFinish( v.m_object, newClass->getName() );
				}

				if( action->versionFlags & VERSION_VARIANT )
				{
					withVariantIndices.pushBack( editIndex );
				}

				if( hkString::strCmp(newClass->getName(),oldClassName) != 0 )
				{
					hkVariant& v = oldObjects[editIndex];
					tracker.removeFinish( v.m_object );
					tracker.addFinish( v.m_object, newClass->getName() );
				}
			}
		}

		copyObjects( oldObjects, objectsInOut, objectCopyIndices, tracker );

		for( int withVariantIndexIndex = 0; withVariantIndexIndex < withVariantIndices.getSize(); ++withVariantIndexIndex)
		{
			int withVariantIndex = withVariantIndices[withVariantIndexIndex];
			hkVariant& v = objectsInOut[withVariantIndex];
			updateVariantClassPointers( v.m_object, *v.m_class, newClassFromOldName );
		}
	}

	// Catch any renamed classes which weren't edited above
	{
		int SENTINEL = objectsInOut.getSize()+1;
		int editIndexIndex = 0;
		int nextEdited = objectEditIndices.getSize() ? objectEditIndices[editIndexIndex] : SENTINEL;
		for( int i = 0; i < objectsInOut.getSize(); ++i )
		{
			if( i < nextEdited )
			{
				hkVariant& v = objectsInOut[i];
				if( const char* newName = newClassFromOldName.getRename( v.m_class->getName() ) )
				{
					const hkClass* c = newClassFromOldName.getClassByName( v.m_class->getName() );
					v.m_class = c;
					tracker.removeFinish( v.m_object );
					tracker.addFinish( v.m_object, newName );
				}
			}
			else if ( i == nextEdited )
			{
				editIndexIndex += 1;
				nextEdited = editIndexIndex < objectEditIndices.getSize()
					? objectEditIndices[editIndexIndex]
					: SENTINEL;
			}
			else
			{
				HK_ASSERT(0,0);
			}
		}
	}

	// Call the version functions
	{
		for( int editIndexIndex = 0; editIndexIndex < objectEditIndices.getSize(); ++editIndexIndex )
		{
			int editIndex = objectEditIndices[editIndexIndex];
			hkVariant& oldObj = oldObjects[editIndex];
			hkVariant& newObj = objectsInOut[editIndex];
			const ClassAction* action = actionFromClassName.getWithDefault( oldObj.m_class->getName(), HK_NULL );
			HK_ASSERT(0x138c549f, action != HK_NULL );
			if( action != HK_NULL && action->versionFunc != HK_NULL )
			{
				(action->versionFunc)( oldObj, newObj, tracker );	
			}
		}
	}

	// update all objects to point to new versions
	{
		for( int copyIndexIndex = 0; copyIndexIndex < objectCopyIndices.getSize(); ++copyIndexIndex )
		{
			int copyIndex = objectCopyIndices[copyIndexIndex];
			tracker.replaceObject(
				oldObjects[copyIndex].m_object,
				objectsInOut[copyIndex].m_object,
				objectsInOut[copyIndex].m_class );
		}
		for( int removeIndexIndex = removedIndices.getSize()-1; removeIndexIndex >= 0; --removeIndexIndex )
		{
			int removeIndex = removedIndices[removeIndexIndex];
			HK_WARN(0x651f7aa5, "removing deprecated object of type " << oldObjects[removeIndex].m_class->getName());
			tracker.replaceObject( oldObjects[removeIndex].m_object, HK_NULL, HK_NULL );
			objectsInOut.removeAt( removeIndex );
		}
	}

	return HK_SUCCESS;
}

hkResult HK_CALL hkVersionUtil::updateBetweenVersions(
	hkArray<hkVariant>& objectsInOut,
	hkObjectUpdateTracker& tracker,
	const hkVersionRegistry& reg,
	const char* fromVersion,
	const char* toVersion )
{
	toVersion = toVersion ? toVersion : getCurrentVersion();

	hkArray<const hkVersionRegistry::Updater*> updatePath;
	if( reg.getVersionPath(fromVersion, toVersion, updatePath ) == HK_SUCCESS )
	{
		HK_SERIALIZE_LOG(("\nTrace(func=\"hkVersionUtil::updateBetweenVersions()\", fromVersion=\"%s\", toVersion=\"%s\")\n", fromVersion, toVersion));
		for( int pathIndex = 0; pathIndex < updatePath.getSize(); ++pathIndex )
		{
			updatePath[pathIndex]->updateFunction( objectsInOut, tracker );
		}

		return HK_SUCCESS;
	}
	else
	{
		HK_WARN( 0x394c3ad7, "No version path from " << fromVersion << " to " << getCurrentVersion() );
		return HK_FAILURE;
	}
}

hkResult HK_CALL hkVersionUtil::updateToCurrentVersion(
	hkPackfileReader& reader,
	const hkVersionRegistry& reg )
{
	const char* originalVersion = reader.getContentsVersion();
	if( hkString::strCmp( originalVersion, getCurrentVersion() ) != 0 )
	{
		hkArray<hkVariant>& loadedObjects = reader.getLoadedObjects();
		if( loadedObjects.getSize() )
		{
			if( hkVersionUtil::updateBetweenVersions(
				loadedObjects,
				reader.getUpdateTracker(),
				reg,
				originalVersion,
				getCurrentVersion() ) == HK_SUCCESS )
			{
				reader.setContentsVersion( getCurrentVersion() );
				return HK_SUCCESS;
			}
		}
		return HK_FAILURE; // getContents or update failed
	}
	return HK_SUCCESS; // already latest version
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
