/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

const char helloworld[] = "Hello world!\n";
const char HELLOWORLD[] = "HELLO WORLD!\n";
const char hello[] = "Hello";
const char world[] = "world!\n";

static int string_main()
{
	{
		hkString s;
		HK_TEST(s.cString()[0] == 0);
		HK_TEST(s.getLength() == 0);
	}
	{
		hkString s(helloworld);
		HK_TEST(s[0]=='H');
		HK_TEST(s.getLength() == sizeof(helloworld) - 1);

		HK_TEST(s.beginsWith(hello));
		hkString hello2(hello);
		HK_TEST(s.beginsWith(hello2));

		HK_TEST(s.endsWith(world));
		hkString world2(world);
		HK_TEST(s.endsWith(world2));

		HK_TEST(s.indexOf('l') == 2 );
		HK_TEST(s.indexOf('!') == 11);

		HK_TEST( s.asUpperCase() == HELLOWORLD );
		HK_TEST( s.asUpperCase() == hkString(HELLOWORLD) );

		hkString t(HELLOWORLD);
		HK_TEST( t.asLowerCase() != s);
		HK_TEST( t.asLowerCase() == hkString(helloworld).asLowerCase() );

		HK_TEST( s.compareToIgnoreCase(t)==0 );

		HK_TEST( s.substr(3,5) == "lo wo");
		
		HK_TEST( hkString("apples").compareTo("oranges") < 0 );
		HK_TEST( hkString("apples").compareTo("apples") == 0 );
		HK_TEST( hkString("bananas").compareTo("apples") > 0 );

		HK_TEST( hkString("apples").compareTo(hkString("oranges")) < 0 );
		HK_TEST( hkString("apples").compareTo(hkString("apples")) == 0 );
		HK_TEST( hkString("bananas").compareTo(hkString("apples")) > 0 );

		HK_TEST( hkString("the")+" fat"+" cat" == "the fat cat" );

		hkString u("one");
		u += "two";
		u += "three";
		HK_TEST( u == "onetwothree" );
	}
	{
		hkString s(helloworld);
		HK_TEST( s.replace('o', 'X', hkString::REPLACE_ONE) == "HellX world!\n" );
		HK_TEST( s.replace('o', 'X', hkString::REPLACE_ALL) == "HellX wXrld!\n" );
		HK_TEST( s.replace('o', 'X'                       ) == "HellX wXrld!\n" );
	}
	{
		hkString s("Lo! hello, hello!");
		HK_TEST( s.replace("lo", "[0123]", hkString::REPLACE_ONE) == "Lo! hel[0123], hello!" );
		HK_TEST( s.replace("lo", "[0123]", hkString::REPLACE_ALL) == "Lo! hel[0123], hel[0123]!" );
		HK_TEST( s.replace("lo", "[0123]"                       ) == "Lo! hel[0123], hel[0123]!" );
	}
	{
		hkString s("Lo! hello, hello!");
		HK_TEST( s.substr(0,3) == "Lo!");
		HK_TEST( s.substr(4,5) == "hello");
	}

	{
		// standard
		HK_TEST( hkString::atoi("123") == 123);
		HK_TEST( hkString::atoi("-123") == -123);

		// Unary + is allowed
		HK_TEST( hkString::atoi("+123") == 123);

		// Whitespace
		HK_TEST( hkString::atoi(" 123") == 123);
		HK_TEST( hkString::atoi("  123") == 123);
		HK_TEST( hkString::atoi("\t123") == 123);
		HK_TEST( hkString::atoi("\t\t123") == 123);

		// Garbage allowed at end
		HK_TEST( hkString::atoi("123BAD") == 123);

		// Uber test
		HK_TEST( hkString::atoi("  \t  \t +123BAD") == 123);

	}

	{
		// standard
		HK_TEST( 0			== hkString::atof( "0" ) );
		HK_TEST( 5			== hkString::atof( "5" ) );
		HK_TEST( -5			== hkString::atof( "-5" ) );
		HK_TEST( 0			== hkString::atof( "0.0" ) );
		HK_TEST( 5.05f - hkString::atof( "5.05" ) < 1e-6f);
		HK_TEST( 5.0f		== hkString::atof( "5." ) );
		HK_TEST( -0.5f		== hkString::atof( "-.5" ) );
		HK_TEST( -0.5f		== hkString::atof( "-0.5" ) );
		HK_TEST( 5.5f		== hkString::atof( "5.5" ) );
		HK_TEST( -5.5f		== hkString::atof( "-5.5" ) );
		HK_TEST( 500000.0f	== hkString::atof( "5e5" ) );
		HK_TEST( 500000.0f	== hkString::atof( "5E5" ) );
		HK_TEST( 0.0f		== hkString::atof( "0.0e5" ) ); 
		HK_TEST( 500000.0f	== hkString::atof( "5.e5" ) );
		HK_TEST( 50000.0f	== hkString::atof( ".5e5" ) );
		HK_TEST( -550000.0f == hkString::atof( "-5.5e5" ) );
//			HK_TEST( 0.001f > hkMath::fabs( 5e-5f - hkString::atof( "5e-5" ) ) );
//			HK_TEST( 0.001f > hkMath::fabs( 5e-5f - hkString::atof( "5E-5" ) ) );
//			HK_TEST( 0.001f > hkMath::fabs( -5e-5f - hkString::atof( "-5e-5" ) ) );
//			HK_TEST( 0.001f > hkMath::fabs( -5e-5f - hkString::atof( "-5E-5" ) ) );
//			HK_TEST( 0.001f > hkMath::fabs( 5e-5f - hkString::atof( "5.0e-5" ) ) );
//			HK_TEST( 0.001f > hkMath::fabs( 5e-6f - hkString::atof( "0.5e-5" ) ) );
//			HK_TEST( 0.001f > hkMath::fabs( -5.5e-5f - hkString::atof( "-5.5e-5" ) ) );
		
		// error really but does return result
		HK_TEST( 0			== hkString::atof( "" ) );
//			These tests seem to be invalid.
//			HK_TEST( 0.001f > hkMath::fabs( -5.5e-5f - hkString::atof( "-5.-5e-5" ) ) ); 
//			HK_TEST( -550000.0f == hkString::atof( "-5.-5e5" ) ); 
//			HK_TEST( -5.5f		== hkString::atof( "-5.-5" ) );
	}

	{
		char string1[] = "a";
		char string2[] = "AB";
		HK_TEST( hkString::strCasecmp(string1, string2) == -1 );
		HK_TEST( hkString::strCasecmp(string2, string1) == 1 );

		char string3[] = "ab";
		char string4[] = "AB";
		HK_TEST( hkString::strCasecmp(string3, string4) == 0 );
		HK_TEST( hkString::strCasecmp(string4, string3) == 0 );
	}
	{
		char string1[] = "ab";
		char string2[] = "ABC";
		int n = 1;
		HK_TEST( hkString::strNcasecmp(string1, string2, n) == 0 );
		HK_TEST( hkString::strNcasecmp(string2, string1, n) == 0 );

		n = 2;
		HK_TEST( hkString::strNcasecmp(string1, string2, n) == 0 );
		HK_TEST( hkString::strNcasecmp(string2, string1, n) == 0 );		

		n = 3;
		HK_TEST( hkString::strNcasecmp(string1, string2, n) == -1 );
		HK_TEST( hkString::strNcasecmp(string2, string1, n) == 1 );		

		n = 4;
		HK_TEST( hkString::strNcasecmp(string1, string2, n) == -1 );
		HK_TEST( hkString::strNcasecmp(string2, string1, n) == 1 );
	}
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(string_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
