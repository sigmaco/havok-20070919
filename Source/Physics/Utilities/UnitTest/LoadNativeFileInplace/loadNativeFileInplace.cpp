/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileReader.h>
#include <Common/Serialize/Util/hkNativePackfileUtils.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>
#include <Physics/Utilities/Serialize/hkpHavokSnapshot.h>
#include <Common/Serialize/Version/hkVersionUtil.h>

static int loadNativeFileInplace()
{
	hkArray<char> buf;
	{
		// Load XML packfile file (do versioning if required) into the buffer to simulate native binary packfile
		// Open a stream to read the file
		hkIstream infile("Common/Api/Serialize/SimpleLoad/Resources/simple.xml");
		HK_ASSERT( 0x215d080c, infile.isOk() );
		hkXmlPackfileReader reader;
		hkOstream nativeFile(buf);
		reader.loadEntireFile(infile.getStreamReader());
		if( hkVersionUtil::updateToCurrentVersion( reader, hkVersionRegistry::getInstance() ) != HK_SUCCESS )
		{
			HK_WARN_ALWAYS(0, "Couldn't update version, skipping.\n");
		}
		// Get the top level object in the file
		hkRootLevelContainer* container = static_cast<hkRootLevelContainer*>( reader.getContents( hkRootLevelContainerClass.getName() ) );
		HK_ASSERT2(0xa6451543, container != HK_NULL, "Could not load root level obejct" );

		hkBool success = hkpHavokSnapshot::save(container, hkRootLevelContainerClass, nativeFile.getStreamWriter(), true);
		
		HK_ASSERT(0, success == true);

		// Now we have native packfile data in the 'buf' variable.
	}

	int bufferSize = hkNativePackfileUtils::getRequiredBufferSize( buf.begin(), buf.getSize() );
	hkArray<char> dataBuffer;
	dataBuffer.reserveExactly(bufferSize);
	HK_ON_DEBUG( hkRootLevelContainer* container = static_cast<hkRootLevelContainer*>)
		(hkNativePackfileUtils::load(buf.begin(), buf.getSize(), dataBuffer.begin(), dataBuffer.getCapacity()));
	HK_ASSERT2(0xa6451543, container != HK_NULL, "Could not load root level obejct" );
	HK_ON_DEBUG(hkpPhysicsData* physicsData = static_cast<hkpPhysicsData*>( container->findObjectByType( hkpPhysicsDataClass.getName() ) ));
	HK_ASSERT2(0xa6451544, physicsData != HK_NULL, "Could not find physics data in root level object" );

	hkNativePackfileUtils::unload(dataBuffer.begin(), dataBuffer.getCapacity());
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(loadNativeFileInplace, "Native", "Physics/Test/UnitTest/Utilities/", __FILE__     );

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
