/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Packfile/Binary/hkPackfileSectionHeader.h>

namespace
{
	template <typename T>
	int extractAndAdvance( void* p, int& off )
	{
		T* tp = reinterpret_cast<T*>( static_cast<char*>(p) + off );
		off += sizeof(T);
		return *tp;
	}

	char* extractAndAdvanceString( void* p, int& off )
	{
		HK_ASSERT(0, (hkUlong(p)&3) == 0);
		HK_ASSERT(0, (off&3) == 0);
		char* ret = static_cast<char*>(p) + off;
		int i = 0; // skip string<null>{1}<pad>{0,3}
		for( ; ret[i] != 0; ++i ) { } // string body
		i += 1; // skip null
		for( ; (i&3) != 0; ++i ) { } // pad up to int32
		off += i;
		return ret;
	}
}

void hkPackfileSectionHeader::getExports( void* sectionBegin, hkArray<hkResource::Export>& exportsOut )
{
	void* exportsBase = hkAddByteOffset(sectionBegin, m_exportsOffset);
	for( int i = 0; i < getExportsSize(); /**/ )
	{
		int off = extractAndAdvance<hkInt32>(exportsBase, i);
		if( off == -1 )
		{
			break;
		}
		HK_ASSERT(0x4208950c, unsigned(off) < unsigned(getDataSize()) );
		char* name = extractAndAdvanceString(exportsBase, i);
		hkResource::Export& e = exportsOut.expandOne();
		e.name = name;
		e.data = hkAddByteOffset(sectionBegin, off);
	}
}

void hkPackfileSectionHeader::getImports( void* sectionBegin, hkArray<hkResource::Import>& importsOut )
{
	void* imports = hkAddByteOffset(sectionBegin, m_importsOffset);
	for( int i = 0; i < getImportsSize(); /**/ )
	{
		int off = extractAndAdvance<hkInt32>(imports, i);
		if( off == -1 )
		{
			break;
		}
		HK_ASSERT(0x3b2e4f83, unsigned(off) < unsigned(getDataSize()) );
		HK_ASSERT(0xd207ae6b, (off & (sizeof(void*)-1)) == 0 );
		char* name = extractAndAdvanceString(imports, i);
		hkResource::Import& imp = importsOut.expandOne();
		imp.name = name;
		imp.location = reinterpret_cast<void**>( hkAddByteOffset(sectionBegin, off) );
	}
}


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
