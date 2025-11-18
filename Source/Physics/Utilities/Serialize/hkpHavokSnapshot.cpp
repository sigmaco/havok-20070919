/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/System/Io/Reader/hkStreamReader.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/hkBase.h>
#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>
#include <Physics/Utilities/Serialize/hkpHavokSnapshot.h>

#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileReader.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileReader.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileWriter.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Physics/Collide/Shape/Compound/Collection/StorageMesh/hkpStorageMeshShape.h>
#include <Physics/Collide/Shape/Compound/Collection/StorageExtendedMesh/hkpStorageExtendedMeshShape.h>
#include <Physics/Collide/Shape/HeightField/StorageSampledHeightField/hkpStorageSampledHeightFieldShape.h>

hkpPhysicsData* HK_CALL hkpHavokSnapshot::load(hkStreamReader* reader, hkPackfileReader::AllocatedData** allocatedData)
{
	HK_ASSERT2(0x74de3808, reader, "Null hkStreamReader pointer was passed to hkpHavokSnapshot::load");
	HK_ASSERT2(0x54c68870, allocatedData, "Null hkPackfileReader::AllocatedData pointer was passed to hkpHavokSnapshot::load");

	// Fail quickly if null pointers were given
	if ( (!reader) || (!allocatedData) )
	{
		return HK_NULL;
	}

	hkLoader loader;
	hkRootLevelContainer* container = loader.load( reader );

	if (!container)
	{
		HK_WARN(0x764219fe, "Could not load a hkRootLevelContainer from given stream.");
		return HK_NULL;
	}

	// first search by type
	hkpPhysicsData* data = static_cast<hkpPhysicsData*>( container->findObjectByType( hkpPhysicsDataClass.getName()) );
	if(data == HK_NULL)
	{
		// failing that, by variant name.
		const char* byName[] = { "SnapshotSave", "hkpPhysicsData", HK_NULL };
		for( int i = 0; byName[i] != HK_NULL; ++i )
		{
			data = static_cast<hkpPhysicsData*>( container->findObjectByName( byName[i] ) );
			if( data )
			{
				break;
			}
		}
	}
	
	if(data != HK_NULL)
	{
		*allocatedData = loader.m_loadedData[0];
		(*allocatedData)->addReference();
	}

	return data;
}

hkpHavokSnapshot::ConvertListener::~ConvertListener()
{
	for( int i = 0; i < m_objects.getSize(); ++i )
	{
		delete m_objects[i];
	}
}

void hkpHavokSnapshot::ConvertListener::addObjectCallback( ObjectPointer& p, ClassPointer& k )
{
	if( hkpMeshShapeClass.isSuperClass(*k) && k != &hkpStorageMeshShapeClass )
	{
		const hkpMeshShape* mesh = static_cast<const hkpMeshShape*>(p);
		hkpStorageMeshShape* storage = new hkpStorageMeshShape(mesh);
		m_objects.pushBack(storage);

		p = storage;
		k = &hkpStorageMeshShapeClass;
	}
	if( hkpExtendedMeshShapeClass.isSuperClass(*k) && k != &hkpStorageExtendedMeshShapeClass )
	{
		const hkpExtendedMeshShape* mesh = static_cast<const hkpExtendedMeshShape*>(p);
		hkpStorageExtendedMeshShape* storage = new hkpStorageExtendedMeshShape(mesh);
		m_objects.pushBack(storage);

		p = storage;
		k = &hkpStorageExtendedMeshShapeClass;
	}
	else if( hkpSampledHeightFieldShapeClass.isSuperClass(*k) && k != &hkpStorageSampledHeightFieldShapeClass )
	{
		const hkpSampledHeightFieldShape* sampled = static_cast<const hkpSampledHeightFieldShape*>(p);
		hkpShape* storage = new hkpStorageSampledHeightFieldShape(sampled);
		m_objects.pushBack(storage);

		p = storage;
		k = &hkpStorageSampledHeightFieldShapeClass;
	}
	else if( hkpRigidBodyClass.isSuperClass(*k) )
	{
		const hkpRigidBody* body = static_cast<const hkpRigidBody*>(p);
		if( hkpWorld* world = body->getWorld() )
		{
			if( world->getFixedRigidBody() == body )
			{
				p = HK_NULL;
				k = HK_NULL;
			}
		}
	}
}


hkBool HK_CALL hkpHavokSnapshot::save(const hkpWorld* world, hkStreamWriter* writer, hkBool binaryFormat, const hkStructureLayout::LayoutRules* targetLayout, bool saveContactPoints)
{
	// Note: because hkpPhysicsData adds a ref to all rbs in the world, and removes the ref
	// on destruction, we have to:
	// Mark the world for write
	// Cast away the const of the world, so we can do this
	// Scope the hkPhysics data so that it goes out of scope and removes refs while the world
	// is still marked for write

	HK_ASSERT2(0x4bb93313, world, "Null hkpWorld pointer passed to hkpHavokSnapshot::save.");
	HK_ASSERT2(0x23ec02e2, writer, "Null hkStreamWriter passed to hkpHavokSnapshot::save.");

	// Fail if any null pointers were given
	if ( (!world) || (!writer) )
	{
		return false;
	}

	hkpWorld* mutableWorld = const_cast<hkpWorld*>(world);
	hkBool ret;
	mutableWorld->markForWrite();
	{
		// Make a data struct to contain the world info.
		hkpPhysicsData data;
		data.populateFromWorld( mutableWorld, saveContactPoints );

		ret = save( &data, writer, binaryFormat, targetLayout );
	}
	mutableWorld->unmarkForWrite();

	return ret;
}

hkBool HK_CALL hkpHavokSnapshot::save( const hkpPhysicsData* data, hkStreamWriter* writer, hkBool binaryFormat, const hkStructureLayout::LayoutRules* targetLayout)
{
	// Add this to our root level container object
	return saveUnderRootLevel(data, hkpPhysicsDataClass, writer, binaryFormat, targetLayout); 
}

hkBool HK_CALL hkpHavokSnapshot::saveUnderRootLevel( const void* data, const hkClass& dataClass, hkStreamWriter* writer, hkBool binaryFormat, const hkStructureLayout::LayoutRules* targetLayout )
{
	//assume data is the raw data, so create a named variant out of it
	hkRootLevelContainer::NamedVariant genericData(const_cast<char *>(dataClass.getName()), const_cast<void *>(data), &dataClass);

	hkRootLevelContainer container;
	container.m_numNamedVariants = 1;
	container.m_namedVariants = &genericData;

	return save(&container, hkRootLevelContainerClass, writer, binaryFormat, targetLayout);
}

hkBool HK_CALL hkpHavokSnapshot::save(
	const void* data,
	const hkClass& dataClass,
	hkStreamWriter* writer,
	hkBool binaryFormat,
	const hkStructureLayout::LayoutRules* targetLayout,
	hkPackfileWriter::AddObjectListener* userListener )
{
	bool res = false;
	if (writer)
	{
		// Make an appropriate writer
		hkPackfileWriter* pw;
		if (binaryFormat)
			pw = new hkBinaryPackfileWriter;
		else
			pw = new hkXmlPackfileWriter;

		ConvertListener defaultConvertListener;
		hkPackfileWriter::AddObjectListener* convertListener = userListener
			? userListener
			: static_cast<hkPackfileWriter::AddObjectListener*>(&defaultConvertListener);

		// Set the top level struct
 		pw->setContents(data, dataClass, convertListener);
		
		// Save it.
		hkPackfileWriter::Options o;
		union { hkUint32 i; char c[4]; } u;
		u.c[0] = 's'; u.c[1] = 'n'; u.c[2] = 'a'; u.c[3] = 'p';
		o.m_userTag = u.i;
		if (targetLayout)
			o.m_layout = hkStructureLayout( *targetLayout );

		res = pw->save( writer, o ) == HK_SUCCESS;
		pw->removeReference();
	}

	return res;
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
