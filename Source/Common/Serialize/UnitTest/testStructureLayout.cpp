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
#include <Common/Serialize/Util/hkStructureLayout.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Serialize/UnitTest/PlatformClassList.h>

static void testLayouts(const hkClass*const* origClasses, const hkClass*const* computedClasses, const char* testType)
{
	const hkClass* const* origp = origClasses;
	const hkClass* const* compp = computedClasses;
	while(*origp!= HK_NULL && *compp != HK_NULL)
	{
		const hkClass* orig = *origp;
		const hkClass* comp = *compp;

		if( orig->getFlags().get(hkClass::FLAGS_NOT_SERIALIZABLE) == 0 )
		{
			hkString desc;
			HK_TEST( orig->getNumMembers() == comp->getNumMembers() );
			for( int i = 0; i < orig->getNumMembers(); ++i )
			{
				int origOff = orig->getMember(i).getOffset();
				int compOff = comp->getMember(i).getOffset();
				
				if( origOff != compOff )
				{
					desc.printf("%s: %s %i %i %i %s\n", orig->getName(), testType, i, origOff, compOff, orig->getMember(i).getName());
				}
				HK_TEST2( origOff == compOff, desc.cString() );
			}
		}
		
		++origp;
		++compp;
	}
	HK_TEST( *origp == HK_NULL && *compp == HK_NULL );
}

static int testStructureLayout()
{
	// compiled in are same as computed
	{
		PlatformClassList classes( hkBuiltinTypeRegistry::StaticLinkedClasses );		
		classes.computeOffsets( hkStructureLayout::HostLayoutRules );
		testLayouts( hkBuiltinTypeRegistry::StaticLinkedClasses, classes.m_copies.begin(), "native vs computed" );
	}

	// test layouts compatible
	{
		hkStructureLayout::LayoutRules rulesBase = { 4,0,0,0 };
		hkStructureLayout::LayoutRules rulesXX = { 4,0,0,0 };
		PlatformClassList classesBase( hkBuiltinTypeRegistry::StaticLinkedClasses );
		PlatformClassList classesXX( hkBuiltinTypeRegistry::StaticLinkedClasses );

		// 4000 == 4001 == 4010 == 4011
		for( int endian = 0; endian < 2; ++endian )
		{
			rulesBase.m_littleEndian = hkUint8(endian);
			classesBase.computeOffsets( rulesBase );

			for( int variant = 0; variant < 4; ++variant )
			{
				rulesXX.m_littleEndian = hkUint8(endian);
				rulesXX.m_emptyBaseClassOptimization = hkUint8(variant & 1);
				rulesXX.m_reusePaddingOptimization = hkUint8(variant >> 1);
				classesXX.computeOffsets( rulesXX );

				testLayouts( classesBase.m_copies.begin(), classesXX.m_copies.begin(), "4xxx compatible" );
			}
		}
	}

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(testStructureLayout, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
