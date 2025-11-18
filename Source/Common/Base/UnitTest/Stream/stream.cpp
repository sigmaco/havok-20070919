/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Base/System/Io/IArchive/hkIArchive.h>
#include <Common/Base/System/Io/OArchive/hkOArchive.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>



#ifdef HK_PLATFORM_PS2
const char filename[] = "host0:testfile.txt";
#else
const char filename[] = "testfile.txt";
#endif

class FakeStreamWriter : public hkStreamWriter
{
	public:

		static int numInstance;

		FakeStreamWriter()
		{
			numInstance++;
		}
		~FakeStreamWriter()
		{
			numInstance--;
		}

		hkBool isOk() const { return true; }
		int write(const void* buf, int nbytes) { return 0; }
		void flush() { }
};
int FakeStreamWriter::numInstance;

template <typename T>
void testRead( const char* inString, T shouldBe )
{
	hkIstream is(inString, hkString::strLen(inString));
	T intVal;
	is >> intVal;
	HK_TEST2(intVal == shouldBe, "Got "<<intVal<<" should be "<<shouldBe);
	HK_TEST(is.isOk());
}


void istream_test()
{
	{
		/*
		FakeStreamWriter* f;
		{
			f = new FakeStreamWriter();
			hkOstream somestream(f);
			f->removeReference();
		}
		HK_TEST(FakeStreamWriter::numInstance==0);

		{
			f = new FakeStreamWriter();
			hkOstream somestream(f);
		}
		HK_TEST(FakeStreamWriter::numInstance==1);
		f->removeReference();
		HK_TEST(FakeStreamWriter::numInstance==0);
		*/
	}


	{
		testRead<int>("\n0x582\n", 0x582);
		testRead<int>("34", 34);
		testRead<int>("35 ", 35);
		testRead<int>("-1 ", -1);
		testRead<unsigned>("-1 ", unsigned(-1));
		testRead<unsigned>("0x00f ", 0xf);
		testRead<unsigned>("0712", 0712);
		testRead<hkInt32>("0xffffffff", -1);
		testRead<hkInt32>("4294967295", -1);
		testRead<hkInt32>("2147483647", hkUint32(-1)>>1);
		testRead<hkInt32>("-2147483647", -2147483647);
		testRead<hkUint64>("0xffffffffffffffff", hkUint64(-1) );
		testRead<hkInt64>("0xffffffffffffffff", -1 );
	}
	{
		/*
		hkOstream os(filename);

		if( HK_TEST( os.isOk() ) )
		{
			hkString sval("33 45.5 hello");
			os << sval;
			HK_TEST(os.isOk());
		}
		*/
	}

	{
		/*
		hkIstream is(filename);

		if( HK_TEST( is.isOk() ) )
		{
			int ival;
			is >> ival;
			HK_TEST(ival==33);
			HK_TEST(is.isOk());

			float fval;
			is >> fval;
						
			HK_TEST(fval==45.5);
			HK_TEST(is.isOk());

			hkString sval;
			is >> sval;
			HK_TEST(!is.isOk());	// Should have read to EOF
		}
		*/
	}

	{
		/*
		hkOstream os(filename);

		if( HK_TEST( os.isOk() ) )
		{
			hkString sval("Testing ");
			os << sval;
			HK_TEST(os.isOk());
		}
		*/
	}
	{
		hkArray<char> cbuf;
		hkOstream os(cbuf);

		HK_TEST( cbuf.getCapacity() >= 1 );
		HK_TEST( cbuf.begin()[0] == 0 );
		const char* testString = "hello world";
		os << testString;
		HK_TEST( hkString::strCmp( cbuf.begin(), testString) == 0 );
		HK_TEST( hkString::strLen( cbuf.begin() ) == hkString::strLen( testString ) );

		HK_TEST( os.getStreamWriter()->seek( 6, hkStreamWriter::STREAM_SET ) == HK_SUCCESS );
		os << "WORLD WORLD";
		HK_TEST( cbuf.begin()[ cbuf.getSize() ] == 0 );
	}
}


class FooStreambufFactory : public hkStreambufFactory
{
	public:

		FooStreambufFactory()			
		{
			m_orig = &hkStreambufFactory::getInstance();
			m_orig->addReference();
			hkStreambufFactory::replaceInstance(this);
		}

		~FooStreambufFactory()
		{
			hkStreambufFactory::replaceInstance(m_orig);
		}

		virtual hkStreamWriter* openConsole(StdStream s)
		{
			return 0;
		}

		virtual hkStreamReader* openReader(const char* name)
		{
			hkString path = "test/unittest/hkbase/stream/";
			path += name;
			return m_orig->openReader(path.cString());
		}

		virtual hkStreamWriter* openWriter(const char* name)
		{
			hkString path = "test/unittest/hkbase/stream/";
			path += name;
			return m_orig->openWriter(path.cString());
		}

		hkStreambufFactory* m_orig;
};

void streamcreate_test()
{
	{
		/*
		FooStreambufFactory factory;
		factory.addReference();
		
		hkIfstream is0("testfile.txt");
		HK_TEST(is0.isOk());
		hkIfstream is1("nonexistantfile.txt");
		HK_TEST(is1.isOk()==false);
		*/
	}	
}


//
// Tests archives
//
void archive_test()
{
	//
	// tests the hkIArchive and hkOArchive classes for binary input and output
	// In this case, file streams are created
	// first, some test data of each supported type is written to file.
	// Then the file is read back in and compared to the original.
	//
	{
		// output
		{
			/*
			hkOfArchive oa("testbindata.txt");
			
			// test data
			char c = 'a';
			unsigned char uc = 25;
			short s = -12345;
			unsigned short us = 12345;
			int i = -12345;
			unsigned int ui = 12345;
			long int li = -12345;
			unsigned long int uli = 12345;
			float f = -1.2345f;
			double d = -1.2345;

			// write
			oa.write8(c);
			
			oa.write8u(uc);
			
			oa.write16(s);
			
			oa.write16u(us);

			oa.write32(i);
			
			oa.write32u(ui);

			oa.write64(li);
			
			oa.write64u(uli);

			oa.writeFloat32(f);
			
			oa.writeDouble64(d);
			*/
		}
		
		// input
		{
			/*
			hkIfArchive ia("testbindata.txt");

			char c = ia.read8();
			HK_TEST(c == 'a');
	
			unsigned char uc = ia.read8u();
			HK_TEST(uc == 25);

			short s = ia.read16();
			HK_TEST(s == -12345);

			unsigned short us = ia.read16u();
			HK_TEST(us == 12345);

			int i = ia.read32();
			HK_TEST(i == -12345);

			unsigned int ui = ia.read32u();
			HK_TEST(ui == 12345);

			hkInt64 li = ia.read64();
			HK_TEST(li == -12345);

			hkUint64 uli = ia.read64u();
			HK_TEST(uli == 12345);

			float f = ia.readFloat32();
			HK_TEST(f == -1.2345f);

			double d = ia.readDouble64();
			HK_TEST(d == -1.2345);
			*/
		}
	}
}


int stream_main()
{
	
	
	istream_test();
	streamcreate_test();
	archive_test();

	
	
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(stream_main, "Fast", "Common/Test/UnitTest/Base/", __FILE__     );


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
