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
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/UnitTest/Binaryreader/hkSomeObject.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Base/Reflection/hkTypeInfo.h>

int hkSomeObject::m_numInstances;

extern const hkTypeInfo hkSomeObjectTypeInfo;

static int binaryPackfileReader()
{
	static hkBool32 registered = 0;
	if( registered == false )
	{
		hkBuiltinTypeRegistry::getInstance().addType( const_cast<hkTypeInfo*>(&hkSomeObjectTypeInfo), const_cast<hkClass*>(&hkSomeObjectClass) );
		registered = true;
	}
	hkArray<char> buf;
	const char sectionName[] = "second";
	{
		HK_TEST( hkSomeObject::m_numInstances == 0 );
		hkSomeObject obj3;
		hkSomeObject obj2(&obj3);
		hkSomeObject obj1(&obj2);

		hkBinaryPackfileWriter writer;
		writer.addSection(sectionName);
		writer.setSectionForPointer(&obj2, sectionName);

		writer.setContents( &obj1, hkSomeObjectClass );

		writer.addExport(&obj1, "ex1");
		writer.addExport(&obj2, "exported2");
		writer.addImport(&obj3, "i");

		hkOstream outfile( buf );
		hkPackfileWriter::Options options;
		options.m_writeMetaInfo = false;
		writer.save( outfile.getStreamWriter(), options );
		HK_TEST( hkSomeObject::m_numInstances == 3 );
	}
	{
		hkBinaryPackfileReader reader;
		hkIstream infile(buf.begin(), buf.getSize());
		reader.loadEntireFile( infile.getStreamReader() );
		HK_TEST( hkSomeObject::m_numInstances == 0 );
		hkSomeObject* root = (hkSomeObject*)reader.getContents("hkSomeObject");
				
		HK_TEST( hkSomeObject::m_numInstances == 2 );
		HK_TEST( root->m_next != HK_NULL );

		hkArray<hkResource::Export> exports0;
		hkArray<hkResource::Import> imports0;
		reader.getPackfileData()->getImportsExports( imports0, exports0 );
		HK_TEST( exports0.getSize() == 2 );
		HK_TEST( imports0.getSize() == 1 );

		reader.unloadSection( 1 );
		reader.fixupGlobalReferences();

		hkArray<hkResource::Export> exports1;
		hkArray<hkResource::Import> imports1;
		reader.getPackfileData()->getImportsExports( imports1, exports1 );
		HK_TEST( exports1.getSize() == 1 );
		HK_TEST( imports1.getSize() == 0 );

		HK_TEST( hkSomeObject::m_numInstances == 1 );
		HK_TEST( root->m_next == HK_NULL );
	}
	HK_TEST( hkSomeObject::m_numInstances == 0 );
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(binaryPackfileReader, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
