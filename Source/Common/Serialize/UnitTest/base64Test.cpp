/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Serialize/Xml/hkXmlObjectReader.h>
#include <Common/Serialize/Serialize/Xml/hkXmlObjectWriter.h>

static const char asciiData[] = "This is the original data!!!";
static const char base64Data[] = "VGhpcyBpcyB0aGUgb3JpZ2luYWwgZGF0YSEhIQA=";

/*
** These tests check that the ascii<->base64 routines for the xml serializer
** work and are platform-independant
*/

int base64Test_main()
{
	// We work including the zero at the end of the ascii data
	const int asciiLen = hkString::strLen(asciiData)+1;
	const int base64Len = hkString::strLen(base64Data);

	// Test 1 : conversion from ASCII into base64
	{
		hkArray<char> result;
		hkOstream out(result);

		hkResult res = hkXmlObjectWriter::base64write(out.getStreamWriter(), asciiData, asciiLen );

		// We test the output is what we expected
		HK_TEST( res == HK_SUCCESS );
		HK_TEST( result.getSize() == base64Len );
		HK_TEST( hkString::strNcmp(base64Data, result.begin(), base64Len) == 0 );
	}

	// Test 2 : conversion from base64 into ASCII
	{
		hkIstream base64stream(base64Data, sizeof(base64Data));

		char asciiResult[50];
		hkResult res = hkXmlObjectReader::base64read( base64stream.getStreamReader(), asciiResult, sizeof(asciiData) );

		// We test the output is the original, including the ending 0
		HK_TEST( res == HK_SUCCESS );
		HK_TEST(hkString::strCmp(asciiData, asciiResult)==0);
	}

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(base64Test_main, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
