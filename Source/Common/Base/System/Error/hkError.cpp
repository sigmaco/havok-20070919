/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Writer/Buffered/hkBufferedStreamWriter.h>

hkErrStream::hkErrStream( void* buf, int bufSize )
: hkOstream( (hkStreamWriter*)HK_NULL)
{
	int sizeOfWriter = HK_NEXT_MULTIPLE_OF(16,sizeof(hkBufferedStreamWriter));
	void* p = ((char*)buf) + bufSize - sizeOfWriter;
	m_writer = new (p) hkBufferedStreamWriter(buf, bufSize - sizeOfWriter, true);
	m_writer->addReference();
}

extern void HK_CALL hkRemoveReferenceError(const hkReferencedObject*, const char* why);

void HK_CALL hkRemoveReferenceError(const hkReferencedObject* o, const char* why)
{
	HK_ERROR(0x2c66f2d8, "Reference count error on object " << (const void*)(o)
			<< " with ref count of " << o->getReferenceCount()
			<< " in " << why << ".\n"
			<< " * Are you calling delete instead of removeReference?\n"
			<< " * Have you called removeReference too many times?\n"
			<< " * Is this a valid object?\n"
			<< " * Do you have more than 32768 references? (unlikely)\n");
}

extern "C" void HK_CALL hkErrorMessage( const char* c );

void HK_CALL hkErrorMessage( const char* c )
{
	HK_ERROR(0x2636fe25, c);
}

#ifdef HK_COMPILER_MSVC  // VC7.0 can't handle template<> etc when any usage of hkError has come before this specialization
	hkError* hkSingleton<hkError>::s_instance = HK_NULL;
#else
	HK_SINGLETON_MANUAL_IMPLEMENTATION(hkError);
#endif


/* Asserts Id's for use with HK_ASSERT2
 * Pick an ID, use it and delete it from the list below
0x31ccb005
0x71c02c92
0x73dfc212
0x3a703f7d
0x6228b053
0x435a6908
0x741c06bb
0x3aa3eb74
0x5205b95e
0x64211c2f
0x72e45941
0x3dd1224e
0x15d88f55
0x3e8bde6d
0x6b865439
0x4e9c6766
0x64e6b9e9
0x67bdda88
0x7aae506e
0x5b88be29
0x6526dca6
0x3f13921f
0x48dcbb8c
0x3e38c22a
0x264b4fd2
0x3f508c6a
0x3674bb07
0x2a8bea89
0x4de62416
0x24d7574b
0x36c0c6fa
0x43ce8784
0x6176ed91
0x38ed1dba
0x6ca16f47
0x73190553
0x3f021f7d
0x194de3e7
0x1dedb579
0x6330489e
0x7f334001
0x540a6d83
0x20731b63
0x4b301733
0x793171a3
0x71c72fe7
0x4bfebf3b
0x2bba698c
0x24d08fc5
0x3c6f9e3a
0x134537c5
0x37454e10
0x79151c48
0x46aefcee
0x6da2f7a4
0x49d68b49
0x1d43773f
0x6aaa3e45
0x2f8ed7a5
0x204b0cb1
0x431b0733
0x401d4c68
0x626a4d83
0x5c23eac4
0x23920168
0x6efea2c2
0x530b238a
0x19e27e5b
0x3f87b09b
0x5f3aec86
0x40e705bb
0x6ce1a31a
0x454f15be
0x28a82990
0x573eb88a
0x4b54a832
0x509aa12b
0x359adce1
0x5d8d1f8e
0x6b24907c
0x1510f60a
0x3488bc81
0x104bb97c
0x1791c2c5
0x42385842
0x2bb3b28a
0x689f6258
0x64b3435c
0x5a0550b6
0x5b21634b
0x55831ae0
0x73a3d963
0x7df92210
0x2434dfd1
0x5fb9d262
0x4d25db6b
0x5cf4e82e
0x47437964
0x5c899323
0x490c5426
0x77c65f00
0x3fcd0fa9
0x547df244
0x7e96cb35
0x386d70eb
0x59edacb8
0x1e826709
0x3b524c54
0x47a929c1
0x48e613dc
0x413aabf4
0x5847a362
0x5ca41662
0x3c22ad1f
0x2c9b6e21
0x389d9041
0x639adf26
0x4d5b8621
0x40f4ea17
0x2c65c15a
0x55e10a7e
0x5cd88668
0x1dfeb511
0x381c0ddb
0x4deeac5b
0x49084017
0x3b082fa1
0x3b51aa2d
0x62a75e63
0x70d90357
0x24e633b3
0x34ae765a
0x5c8a9815
0x1d15a9f5
0x27b96adb
0x5521725a
0x5c8bb60f
0x16d3be86
0x3f79ed31
0x5fe59c18
0x657174ff
0x2a6ad8df
0x7ed82591
0x6569eafd
0x7e9ce7c5
0x21be44cd
0x1a6ebbda
0x21d19edd
0x5093baad
0x408e84c7
0x2f718942
0x5e934d90
0x676ea00a
0x63482c0a
0x146e7204
0x5010d60b
0x1b87e64c
0x7f47a720
0x58f928ef
0x4fda0b4a
0x3f0d4bf8
0x1d5e9937
0x29207d08
0x6355856a
0x43f8b298
0x3de773d2
0x40278ffe
0x171c2cbf
0x5b6c0e14
0x7d35e963
0x466e2a78
0x260e0e21
0x62cbb960
0x36118e94
0x3acc5348
0x33d3d86a
0x54977d10
0x4feabbef
0x60e69fa0
0x717e5c65
0x758787be
0x7ba85d07
0x609df4f7
0x5171afef
0x41ec41cd
0x158fdfb3
0x3f8f9bcd
0x714e3ed1
0x3e7c1972
0x6f49f943
0x7584cd60
0x32285b9a
0x21007592
0x3d3a1de9
0x5162a830
0x154482c3
0x18e0f831
0x795fdb22
0x25255085
0x35cdf721
0x1bb0e50a
0x71d72904
0x4e712ad9
0x3a3ade52
0x7ace191c
*/



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
