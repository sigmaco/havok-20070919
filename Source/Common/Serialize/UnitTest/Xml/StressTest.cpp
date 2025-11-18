/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/UnitTest/Xml/hkStressTestCinfo.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>

#include <Common/Base/Reflection/Registry/hkTypeInfoRegistry.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileReader.h>
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>


//
// These are used for the class iterator (for casting pointers to get the size of arrays).
//
namespace
{
	template <typename T>
	struct DummyArray
	{
		T* data;
		int size;
		int capAndFlags;
	};

	struct DummyHomogeneousArray
	{
		hkClass* klass;
		void* data;
		int size;
		int capAndFlags;
	};
}


static hkBool testClass(
						const hkClass& klass, // class info for host
						const void* aCinfo, // cinfo data on first object
						const void* bCinfo // cinfo data on second object
);

static hkBool testClassMember(
							  const hkClassMember& member, // class info for host
							  const void* memberAddressA, // cinfo data on first object
							  const void* memberAddressB // cinfo data on second object
);



static int calcCArraySize( const hkClassMember& member )
{
	return (member.getCstyleArraySize()) ? member.getCstyleArraySize() : 1;
}

static void printError( const hkClassMember& member )
{
	//hkprintf ( "Member %s didn't serialize correctly.\n", member.getName() );
	HK_ASSERT(0x0,0);
}


static hkBool testClassMember(
		const hkClassMember& member, // class info for host
		const void* memberAddressA, // cinfo data on first object
		const void* memberAddressB // cinfo data on second object
		)
{
	hkBool memberOk = true;

	switch( member.getType() )
	{
		case hkClassMember::TYPE_BOOL:
		case hkClassMember::TYPE_CHAR:
		case hkClassMember::TYPE_INT8:
		case hkClassMember::TYPE_UINT8:
		case hkClassMember::TYPE_INT16:
		case hkClassMember::TYPE_UINT16:
		case hkClassMember::TYPE_INT32:
		case hkClassMember::TYPE_UINT32:
		case hkClassMember::TYPE_INT64:
		case hkClassMember::TYPE_UINT64:
		case hkClassMember::TYPE_REAL:
		case hkClassMember::TYPE_VECTOR4:
		case hkClassMember::TYPE_QUATERNION:
		case hkClassMember::TYPE_MATRIX3:
		case hkClassMember::TYPE_ROTATION:
		case hkClassMember::TYPE_QSTRANSFORM:
		case hkClassMember::TYPE_MATRIX4:
		case hkClassMember::TYPE_TRANSFORM:
		case hkClassMember::TYPE_ENUM:
		case hkClassMember::TYPE_FLAGS:
		{
			int size = member.getSizeInBytes();
			if ( hkString::memCmp( memberAddressA, memberAddressB, size) != 0 )
			{
				printError( member );
				return false;
			}
			break;
		}
		case hkClassMember::TYPE_ZERO:
		{
			//
			// All we need to check here is that everything in object b is zero.
			//

			int size = member.getSizeInBytes();
			hkLocalArray<char> zero(size);
			zero.setSize(size,0);

			for ( int i = 0 ; i < calcCArraySize( member ) ; ++i )
			{
				if ( hkString::memCmp(static_cast<const char*>(memberAddressB)+i*size, zero.begin(), size) != 0 )
				{
					printError( member );
					return false;
				}
			}
			break;
		}
		case hkClassMember::TYPE_POINTER:
		case hkClassMember::TYPE_FUNCTIONPOINTER:
		{
			const hkClass* mclass = &member.getStructClass();

			int size = member.getSizeInBytes();

			// This pointer could be a void*
			if ( mclass != HK_NULL )
			{
				for ( int i = 0 ; i < calcCArraySize( member ) ; ++i )
				{
					memberOk = testClass( *mclass,
							reinterpret_cast<const void*const*>(static_cast<const char*>(memberAddressA)+i*size),
							reinterpret_cast<const void*const*>(static_cast<const char*>(memberAddressB)+i*size) );

					if ( !memberOk)
					{
						printError( member );
						return false;
					}
				}
			}
			break;
		}
		case hkClassMember::TYPE_ARRAY:
		case hkClassMember::TYPE_SIMPLEARRAY:
		case hkClassMember::TYPE_INPLACEARRAY:
		{
			const DummyArray<char>* arrayA = (const DummyArray<char>*)memberAddressA;
			const DummyArray<char>* arrayB = (const DummyArray<char>*)memberAddressB;

			memberOk = (arrayA->size == arrayB->size);
			if (!memberOk)
			{
				printError( member );
				return false;
			}

			if( arrayA->size )
			{
				for( int i = 0; i < arrayA->size; ++i )
				{
					hkClassMember::Type elementType = member.getArrayType();
					switch( elementType  )
					{
						case hkClassMember::TYPE_BOOL:
						case hkClassMember::TYPE_CHAR:
						case hkClassMember::TYPE_INT8:
						case hkClassMember::TYPE_UINT8:
						case hkClassMember::TYPE_INT16:
						case hkClassMember::TYPE_UINT16:
						case hkClassMember::TYPE_INT32:
						case hkClassMember::TYPE_UINT32:
						case hkClassMember::TYPE_INT64:
						case hkClassMember::TYPE_UINT64:
						case hkClassMember::TYPE_REAL:
						case hkClassMember::TYPE_VECTOR4:
						case hkClassMember::TYPE_QUATERNION:
						case hkClassMember::TYPE_MATRIX3:
						case hkClassMember::TYPE_ROTATION:
						case hkClassMember::TYPE_QSTRANSFORM:
						case hkClassMember::TYPE_MATRIX4:
						case hkClassMember::TYPE_TRANSFORM:
						case hkClassMember::TYPE_ENUM:
						case hkClassMember::TYPE_FLAGS:
						{
							int elementSize = member.getArrayMemberSize();
							memberOk = memberOk && ( hkString::memCmp( arrayA->data+i*elementSize, arrayB->data+i*elementSize, elementSize ) == 0 );

							if ( !memberOk )
							{
								printError( member );
								return false;
							}
							break;
						}
						case hkClassMember::TYPE_POINTER:
						case hkClassMember::TYPE_FUNCTIONPOINTER:
						case hkClassMember::TYPE_STRUCT:
						{
							hkClass k = member.getStructClass();
							memberOk = memberOk && testClass( k, arrayA->data+i*k.getObjectSize(), arrayB->data+i*k.getObjectSize() );

							if ( !memberOk )
							{
								printError( member );
								return false;
							}
							break;
						}
						default:
						{
							HK_ASSERT2(0,0, "Unsupported classMember type.");
						}
					}
				}
			}

			if (!memberOk)
			{
				printError( member );
				return false;
			}
			break;
		}
		case hkClassMember::TYPE_STRUCT: // single struct
		{
			const hkClass& sclass = member.getStructClass();

			int size = sclass.getObjectSize();
			for ( int i = 0 ; i < calcCArraySize(member); ++i)
			{
				memberOk = memberOk && testClass( sclass, static_cast<const char*>(memberAddressA)+i*size, static_cast<const char*>(memberAddressB)+i*size );
			}
			break;
		}
		case hkClassMember::TYPE_VARIANT:
		{
			hkVariant* varA = const_cast<hkVariant*>( (const hkVariant*)memberAddressA );
			hkVariant* varB = const_cast<hkVariant*>( (const hkVariant*)memberAddressA );

			if ( hkString::strCmp( varA->m_class->getName(), varB->m_class->getName()) != 0 )
			{
				printError( member );
				return false;
			}

			int size = member.getSizeInBytes();
			for( int i = 0; i < calcCArraySize( member ); ++i )
			{
				testClass( *varA->m_class, static_cast<const char*>(memberAddressA)+i*size, static_cast<const char*>(memberAddressA)+i*size );
			}
			break;
		}
		default:
		{
			HK_ASSERT2(0x47f16424, 0, "missing case statement");
		}
	}

	if (!memberOk)
	{
		printError( member );
		return false;
	}
	return memberOk;
}


static hkBool testClass(
						const hkClass& klass, // class info for host
						const void* aCinfo, // cinfo data on first object
						const void* bCinfo // cinfo data on second object
						)
{
	for( int memberIdx = 0; memberIdx < klass.getNumMembers(); ++memberIdx )
	{
		const hkClassMember& member = klass.getMember( memberIdx );
		const void* memberAddressA = static_cast<const char*>(aCinfo) + member.getOffset();
		const void* memberAddressB = static_cast<const char*>(bCinfo) + member.getOffset();

		if (!testClassMember( member, memberAddressA, memberAddressB ))
		{
			return false;
		}
	}

	return true;
}


static bool CinfosEqual( const hkStressTestCinfo& a, const hkStressTestCinfo& b )
{

	// Iterate through the members of the hkStressTestCinfoClass
	testClass( hkStressTestCinfoClass, &a, &b );
	return true;
}



enum SerializerType
{
	Xml,
	Binary
};

static void test( SerializerType stype, hkStressTestCinfo& origInfo )
{
	hkTypeInfoRegistry loadRegistry;
	hkVtableClassRegistry saveRegistry;

	hkArray<char> tmpBuf;
	{
		hkOstream out(tmpBuf);
		hkBinaryPackfileWriter binWriter;
		hkPackfileWriter* writer = (hkPackfileWriter*)&binWriter;

		writer->setContents( &origInfo, hkStressTestCinfoClass );

		hkPackfileWriter::Options options;
		writer->save( out.getStreamWriter(), options);
	}

	{
		hkIstream in(tmpBuf.begin(), tmpBuf.getSize());
		hkBinaryPackfileReader binReader;
		hkPackfileReader* reader = (hkPackfileReader*)&binReader;

		reader->loadEntireFile(in.getStreamReader());
		hkStressTestCinfo* newInfo = (hkStressTestCinfo*)reader->getContents( hkStressTestCinfoClass.getName() );
		HK_TEST( newInfo != HK_NULL );

		// We now want to create a copy of the original info, to ensure that are no references in
		// the newInfo to the origInfo.  For example, if pointer was serialized as a hkUlong
		// and remained pointing back to the original info, this would not be detected if the origInfo
		// was still there.

		hkStressTestCinfo* newOrigInfo = new hkStressTestCinfo;
		hkString::memCpy( newOrigInfo, &origInfo, sizeof(hkStressTestCinfo));

		// wipe the original
		hkString::memSet( &origInfo, 0xcdcdcdcd, sizeof(hkStressTestCinfo) );

		HK_TEST( CinfosEqual( *newOrigInfo, *newInfo ) );

		// debug: print read cinfo as xml
		/*
		if( 0 && packet->getType() == hkPacket::OBJECT )
		{
			hkObjectPacket* opacket = static_cast<hkObjectPacket*>(packet);
			hkArray<char> buf;
			hkOstream os(buf);
			hkXmlSerializerWriter writer(os.getStreamWriter());
			writer.saveObjectPacket( *opacket );
			hkcout.write( buf.begin(), buf.getSize() );
			hkcout << '\n';
		}
		*/
	}
}

static int stresstestmain()
{
	//
	// This first test doesn't work straight off, since
	// default constructors are not created from the xml.
	//
	if(0)
	{
		hkStressTestCinfo info;
		test( Binary, info );
	}
	if(1)
	{
		// Put junk in the memory before using it.
		hkStressTestCinfo* info = new hkStressTestCinfo;
		hkString::memSet( info, 0xcdcdcdcd, sizeof(hkStressTestCinfo) );
		info = new(info) hkStressTestCinfo;

		++info->m_simpleReal;
		info->m_name = "<this> gets 'tricky' & \"trickier\"";
		info->m_metaSyntacticVariable = "quux";
		info->m_simpleEnum = hkStressTestCinfo::VAL_TWENTY;

		//
		info->m_arrayRealEmpty.pushBack(101);
		info->m_arrayRealEmpty.pushBack(103);

		info->m_arrayRealWithIntializer.clear();

		info->m_simpleCarrayRealEmpty[0] = 999;
		info->m_simpleCarrayRealEmpty[1] = 1001;
		info->m_simpleCarrayRealEmpty[2] = 1003;
		info->m_simpleCarrayRealEmpty[3] = 1005;
		info->m_simpleCarrayRealEmpty[4] = 1007;

		info->m_arrayStructEmpty.clear();
		hkStressTestCinfo::SimpleStruct ss;
		ss.m_key = 1; ss.m_value = 1;
		info->m_arrayStructEmpty.pushBack( ss );
		info->m_simpleStructCarray[0] = ss;
		ss.m_key = 2; ss.m_value = 3;
		info->m_arrayStructEmpty.pushBack( ss );
		info->m_simpleStructCarray[1] = ss;
		ss.m_key = 5; ss.m_value = 8;
		info->m_arrayStructEmpty.pushBack( ss );
		info->m_simpleStructCarray[2] = ss;
		ss.m_key = 13; ss.m_value = 21;
		info->m_arrayStructEmpty.pushBack( ss );
		info->m_simpleStructCarray[3] = ss;
		info->m_simpleStructCarray[4] = ss;
		info->m_simpleStructCarray[5] = ss;



		//
		// All pointers should be null'd.
		//

		info->m_optionalPtr = HK_NULL;

		info->m_simpleBoolPointer = HK_NULL;
		info->m_simpleCharPointer = HK_NULL;
		info->m_simpleInt8Pointer = HK_NULL;
		info->m_simpleUint8Pointer = HK_NULL;
		info->m_simpleInt16Pointer = HK_NULL;
		info->m_simpleUint16Pointer = HK_NULL;
		info->m_simpleInt32Pointer = HK_NULL;
		info->m_simpleUint32Pointer = HK_NULL;
		info->m_simpleInt64Pointer = HK_NULL;
		info->m_simpleUint64Pointer = HK_NULL;
		info->m_simpleRealPointer = HK_NULL;
		info->m_simpleVector4Pointer = HK_NULL;
		info->m_simpleQuaternionPointer = HK_NULL;
		info->m_simpleMatrix3Pointer = HK_NULL;
		info->m_simpleRotationPointer = HK_NULL;
		info->m_simpleMatrix4Pointer = HK_NULL;
		info->m_simpleTransformPointer = HK_NULL;

		info->m_simpleArray = HK_NULL;
		info->m_numSimpleArray = 0;

		//
		//  More complex structs and arrays of structs.
		//

		info->m_serializePointerAsZero = HK_NULL;

		// This should be serialized as an empty array.
		info->m_serializeArrayAsZero.pushBack(3);
		info->m_serializeArrayAsZero.pushBack(5);
		info->m_serializeArrayAsZero.pushBack(8);
		info->m_serializeArrayAsZero.pushBack(13);
		info->m_serializeArrayAsZero.pushBack(21);

		//info->m_structWithVtable.m_value = 34;
		//
		// A struct with arrays.
		//

		//info->m_structWithArrays.m_anArray.pushBack(55);
		//info->m_structWithArrays.m_anArray.pushBack(89);

		//hkChar* p; p = new hkChar;
		//info->m_structWithArrays.m_anArrayOfPointers.pushBack( p );
		//info->m_structWithArrays.m_anArrayOfPointers.pushBack( p );
		//info->m_structWithArrays.m_anArrayOfPointers.pushBack( p );
		//info->m_structWithArrays.m_anArrayOfPointers.pushBack( p );


		//hkStressTestCinfo::StructWithVtable* v = new hkStressTestCinfo::StructWithVtable;
		//v->m_newvalue = 144;
		//info->m_structWithArrays.m_anArrayOfStructs.pushBack( info->m_structWithVtable );

		test( Binary, *info );
	}

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif

//HK_TEST_REGISTER(stresstestmain,     "Fast", "Test/Test/UnitTest/UnitTest/UnitTest/Serialize/",     __FILE__    );

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
