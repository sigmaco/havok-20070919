/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef INC_0x42c2ed99
#define INC_0x42c2ed99
#include <Common/Base/hkBase.h>

#define hkTaggedUnion enum
#define hkTaggedUnionItem(EVALUE, KLASS) EVALUE

//class/struct
hkTaggedUnion hkSimpleUnion3
{
	hkTaggedUnionItem(SIMPLE_TYPE_ONE = 1 , hkTypeOne),
	hkTaggedUnionItem(SIMPLE_TYPE_TWO, hkTypeTwo),
	hkTaggedUnionItem(SIMPLE_HIGH_START = 100, HK_NULL),
	hkTaggedUnionItem(SIMPLE_AFTER_GAP = SIMPLE_HIGH_START, hkAfterGap),
	hkTaggedUnionItem(SIMPLE_TYPE_MAX, HK_NULL)
};

// Stream Members - don't have to be in the same file

struct hkTypeOne
{
	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkTypeOne );
	hkTypeOne() : m_type(SIMPLE_TYPE_ONE) {}
	hkEnum< ::hkSimpleUnion3, hkUint32> m_type;
	float m_h;
};

struct hkTypeTwo
{
	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkTypeTwo );
	hkTypeTwo() : m_type(SIMPLE_TYPE_TWO) {}
	hkEnum< ::hkSimpleUnion3, hkUint32> m_type;
	float m_f;
	int m_g;
};

struct hkAfterGap
{
	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkAfterGap );
	hkAfterGap() : m_type(SIMPLE_AFTER_GAP) {}
	hkEnum< ::hkSimpleUnion3, hkUint32> m_type;
	float m_f;
	int m_g;
	hkInt8 m_b[16];
};

extern const hkClass hkTypeOneClass;
extern const hkClass hkTypeTwoClass;
extern const hkClass hkHighTwoClass;

#endif // INC_0x42c2ed99

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
