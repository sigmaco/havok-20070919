/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Util/hkStructureLayout.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Serialize/UnitTest/PlatformClassList.h>

static int getSizeInBytes( const hkClassMember& member, int bytesInPointer )
{
	int nelem = member.getCstyleArraySize() ? member.getCstyleArraySize() : 1;
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
		case hkClassMember::TYPE_ULONG:
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
		case hkClassMember::TYPE_STRUCT:
		{
			return member.getSizeInBytes();
		}
		case hkClassMember::TYPE_CSTRING:
		case hkClassMember::TYPE_POINTER:
		case hkClassMember::TYPE_FUNCTIONPOINTER:
		{
			return bytesInPointer * nelem;
		}
		case hkClassMember::TYPE_ARRAY:
		{
			return bytesInPointer==4 ? 12 : 16;
		}
		case hkClassMember::TYPE_SIMPLEARRAY:
		{
			return bytesInPointer==4 ? 8 : 12;
		}
		case hkClassMember::TYPE_HOMOGENEOUSARRAY:
		{
			return bytesInPointer==4 ? 12 : 20;
		}
		case hkClassMember::TYPE_VARIANT:
		{
			return 2*bytesInPointer * nelem;
		}
		case hkClassMember::TYPE_ZERO:
		{
			hkInternalClassMember m = {
				member.getName(),
				&member.getStructClass(),
				HK_NULL,
				static_cast<hkInt8>(member.getSubType()),
				hkClassMember::TYPE_VOID,
				static_cast<hkInt16>(member.getCstyleArraySize()),
				static_cast<hkInt16>(member.getFlags().get()),
				0,
				HK_NULL
			};
			return getSizeInBytes( reinterpret_cast<hkClassMember&>(m), bytesInPointer);
		}
		case hkClassMember::TYPE_INPLACEARRAY:
		case hkClassMember::TYPE_VOID:
		case hkClassMember::TYPE_MAX:
		default:
		{
			HK_ASSERT(0,0);
		}
	}
	return 1;
}

static void showClassOffsets(
	const hkClass* topClass,
	int bytesInPointer,
	hkOstream& out )
{
	int startOffset = 0;
	hkArray<const hkClass*> hierarchy;
	{
		const hkClass* k = topClass;
		while(k)
		{
			hierarchy.insertAt(0,k);
			k = k->getParent();
		}
	}

	int memberIndex = 0;
	for( int hierIndex = 0; hierIndex < hierarchy.getSize(); ++hierIndex )
	{
		const hkClass* k = hierarchy[hierIndex];
		
		for( int i = 0; i < k->getNumDeclaredInterfaces(); ++i )
		{
			out.printf("M%i,%i,%s,%s\n", startOffset+bytesInPointer*i, bytesInPointer, "Vtable", "Vtable");
		}
		{
			for( int i = 0; i < k->getNumDeclaredMembers(); ++i )
			{
				const hkClassMember& m = k->getDeclaredMember(i);
				char buf[1024]; m.getTypeName(buf, sizeof(buf));
				out.printf("M%i,%i,%s,%s\n", m.getOffset(), getSizeInBytes(m, bytesInPointer), m.getName(), buf);
				memberIndex += 1;
			}
		}
		startOffset = k->getObjectSize(); // maybe not for m_reusePaddingOptimization
	}
}

static hkString getOutputFileName(const hkStructureLayout::LayoutRules& target)
{
	const hkStructureLayout::LayoutRules& host = hkStructureLayout::HostLayoutRules;
	hkString s;
	s.printf("offsets.t%i%i%i%i.h%i%i%i%i.txt",
		target.m_bytesInPointer, target.m_littleEndian,
		target.m_reusePaddingOptimization, target.m_emptyBaseClassOptimization,
		host.m_bytesInPointer, host.m_littleEndian,
		host.m_reusePaddingOptimization, host.m_emptyBaseClassOptimization );
	return s;
}

static void showClassListOffsets(const hkClass*const* classes, int bytesInPointer, hkOstream& out )
{
	const hkClass* const* kp = classes;
	while(*kp != HK_NULL)
	{
		const hkClass* k = *kp;
		out.printf("*%s,%i\n", k->getName(), k->getObjectSize() );
		showClassOffsets(k, bytesInPointer, out );
		++kp;
	}
}

static int showOffsets()
{
	PlatformClassList classes( hkBuiltinTypeRegistry::StaticLinkedClasses );

	for( int i = 0; i < 16; ++i )
	{
		// set up rules for this target
		hkStructureLayout::LayoutRules rules =
		{
			(i & 1) ? 4 : 8,
			(i & 2) ? 1 : 0,
			(i & 4) ? 1 : 0,
			(i & 8) ? 1 : 0,
		};
		classes.computeOffsets( rules );

		// dump to file
		hkString fname = getOutputFileName( rules );
		hkOstream out(fname.cString());
		showClassListOffsets( classes.m_copies.begin(), rules.m_bytesInPointer, out );
	}

	// dump host
	{
		hkString fname;
		const hkStructureLayout::LayoutRules& host = hkStructureLayout::HostLayoutRules;
		fname.printf("offsets.t____.h%i%i%i%i.txt",
			host.m_bytesInPointer, host.m_littleEndian,
			host.m_reusePaddingOptimization, host.m_emptyBaseClassOptimization );
		hkOstream out(fname.cString());
		showClassListOffsets( hkBuiltinTypeRegistry::StaticLinkedClasses, host.m_bytesInPointer, out );
	}
	
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(showOffsets, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
