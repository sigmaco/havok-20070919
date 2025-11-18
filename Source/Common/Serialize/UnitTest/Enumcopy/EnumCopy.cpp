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
#include <Common/Serialize/Copier/hkObjectCopier.h>
#include <Common/Serialize/Serialize/hkRelocationInfo.h>
#include <Common/Serialize/UnitTest/Enumcopy/EnumCopy.h>
#include <Common/Base/System/Io/OArchive/hkOArchive.h>

static int EnumCopy()
{
	Original original;
	original.m_value8 = Original::VALUE_FIRST;
	original.m_value16 = Original::VALUE_SECOND;
	original.m_value32 = Original::VALUE_THIRD;
	// These lines intentionally produce warnings.
	original.m_valueBad0 = Original::VALUE_ONLY_IN_ORIGINAL;
	original.m_valueBad1 = (Original::Value)Modified::VALUE_ONLY_IN_MODIFIED;
		
	extern const hkClass ModifiedClass;
	extern const hkClass OriginalClass;

	hkArray<char> buf;
	hkOArchive oa(buf);
	hkObjectCopier copier( hkStructureLayout::HostLayoutRules, hkStructureLayout::HostLayoutRules );
	hkRelocationInfo reloc;
	copier.copyObject( &original, OriginalClass, oa.getStreamWriter(), ModifiedClass, reloc);

	Modified* mod = reinterpret_cast<Modified*>(buf.begin());
	HK_TEST( mod->m_value8 == Modified::VALUE_FIRST );
	HK_TEST( mod->m_value16 == Modified::VALUE_SECOND);
	HK_TEST( mod->m_value32 == Modified::VALUE_THIRD );
	HK_TEST( mod->m_valueBad0 == 0 );
	HK_TEST( mod->m_valueBad1 == 0 );

	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(EnumCopy, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
