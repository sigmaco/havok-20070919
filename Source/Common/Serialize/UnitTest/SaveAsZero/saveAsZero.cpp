/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Serialize/UnitTest/SaveAsZero/saveAsZero.h>

#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileWriter.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileReader.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileReader.h>

template <typename Reader, typename Writer>
static void test()
{
	TestZero zero;
	HK_TEST( zero.m_value8 != 0 );
	HK_TEST( zero.m_value16 != 0 );
	HK_TEST( zero.m_value32 != 0 );
	HK_TEST( zero.m_zero8 != 0 );
	HK_TEST( zero.m_zero16 != 0 );
	HK_TEST( zero.m_zero32 != 0 );

	hkArray<char> buf;

	{
		hkOstream os(buf);
		Writer writer;
		writer.setContents( &zero, TestZeroClass );
		hkPackfileWriter::Options options;
		writer.save( os.getStreamWriter(), options );
	}

	hkOstream("dump.txt").write( buf.begin(), buf.getSize() );

	{
		hkIstream is(buf.begin(), buf.getSize());
		Reader reader;
		reader.loadEntireFile( is.getStreamReader() );
		TestZero* zp = (TestZero*)reader.getContents( "TestZero" );

		HK_TEST( zero.m_value8 == zp->m_value8 );
		HK_TEST( zero.m_value16 == zp->m_value16 );
		HK_TEST( zero.m_value32 == zp->m_value32 );
		HK_TEST( zp->m_zero8 == 0 );
		HK_TEST( zp->m_zero16 == 0 );
		HK_TEST( zp->m_zero32 == 0 );
	}
}

static int SaveAsZero()
{
	test<hkBinaryPackfileReader,hkBinaryPackfileWriter>();
	test<hkXmlPackfileReader,hkXmlPackfileWriter>();
	return 0;
}

template <typename Reader, typename Writer>
static void test2()
{
	TestArrayNulls testObj;
	{
		hkArray<TestArrayNulls*>& arr = testObj.m_array;
		HK_TEST( arr[0] == HK_NULL );
		HK_TEST( arr[1] == &testObj );
		HK_TEST( arr[2] == HK_NULL );
		HK_TEST( arr[3] == HK_NULL );
		HK_TEST( arr[4] == &testObj );
		HK_TEST( arr[5] == HK_NULL );
	}

	hkArray<char> buf;

	{
		hkOstream os(buf);
		Writer writer;
		writer.setContents( &testObj, TestArrayNullsClass );
		hkPackfileWriter::Options options;
		writer.save( os.getStreamWriter(), options );
	}

	hkOstream("dump.txt").write( buf.begin(), buf.getSize() );

	{
		hkIstream is(buf.begin(), buf.getSize());
		Reader reader;
		reader.loadEntireFile( is.getStreamReader() );
		TestArrayNulls* readObj = (TestArrayNulls*)reader.getContents( "TestArrayNulls" );

		hkArray<TestArrayNulls*>& arr = readObj->m_array;
		HK_TEST( arr[0] == HK_NULL );
		HK_TEST( arr[1] == readObj );
		HK_TEST( arr[2] == HK_NULL );
		HK_TEST( arr[3] == HK_NULL );
		HK_TEST( arr[4] == readObj );
		HK_TEST( arr[5] == HK_NULL );
	}
}

static int TestArrayNulls_HVK3369()
{
	test2<hkBinaryPackfileReader,hkBinaryPackfileWriter>();
	test2<hkXmlPackfileReader,hkXmlPackfileWriter>();
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(SaveAsZero, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );
HK_TEST_REGISTER(TestArrayNulls_HVK3369, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );


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
