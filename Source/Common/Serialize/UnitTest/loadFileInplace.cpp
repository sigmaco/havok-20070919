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
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileReader.h>
#include <Common/Serialize/Version/hkVersionUtil.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/Version/hkVersionRegistry.h>
#include <Common/Serialize/Util/hkStructureLayout.h>

static int loadFileInplace()
{
	hkStructureLayout l;
	hkString assetFile;
	assetFile.printf("resources/Showcase/gdc2005/animations/hkDie_L%d%d%d%d.hkx", 
		hkStructureLayout::HostLayoutRules.m_bytesInPointer,
		hkStructureLayout::HostLayoutRules.m_littleEndian? 1 : 0,
		hkStructureLayout::HostLayoutRules.m_reusePaddingOptimization? 1 : 0,
		hkStructureLayout::HostLayoutRules.m_emptyBaseClassOptimization? 1 : 0);

	hkIfstream is(assetFile.cString());
	hkBinaryPackfileReader breader;
	hkArray<char> buf;
	int nread = 1;
	while( nread )
	{
		const int CSIZE = 8192;
		char* b = buf.expandBy( CSIZE );
		nread = is.read( b, CSIZE );
		buf.setSize( buf.getSize() + nread - CSIZE );
	}
	breader.loadEntireFileInplace( buf.begin(), buf.getSize() );
	HK_TEST( hkString::strCmp(breader.getContentsClassName(), "hkRootLevelContainer") == 0 );

	hkVersionUtil::updateToCurrentVersion( breader, hkVersionRegistry::getInstance() );
	HK_TEST( hkString::strCmp(breader.getContentsClassName(), "hkRootLevelContainer") == 0 );

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(loadFileInplace, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
