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
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>

#include <Common/Base/Reflection/hkClass.h>
#include <Common/Serialize/Packfile/Xml/hkXmlPackfileWriter.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>

class hkClass;
extern const hkClass hkClassArrayClass;

struct hkClassArray
{
	HK_DECLARE_REFLECTION();

	hkArray<const hkClass*> m_classes;
};

// Class hkClassArray
//
static const hkInternalClassMember hkClassArrayClass_Members[] =
{
	{ "classes", &hkClassClass, HK_NULL, hkClassMember::TYPE_ARRAY, hkClassMember::TYPE_POINTER, 0, 0, HK_OFFSET_OF(hkClassArray,m_classes), HK_NULL }
};

extern const hkClass hkClassArrayClass;
const hkClass hkClassArrayClass(
	"hkClassArray",
	HK_NULL, // parent
	sizeof(hkClassArray),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(hkClassArrayClass_Members),
	1, // members
	HK_NULL // defaults
	);

static void classDumpList(const hkClass*const* classes)
{
	hkClassArray carray;
	const hkClass* const* kp = classes;
	while(*kp != HK_NULL)
	{
		carray.m_classes.pushBack( *kp );
		++kp;
	}

	// Save it.
	hkXmlPackfileWriter xmlWriter;
	xmlWriter.setContents(&carray, hkClassArrayClass);

	hkOstream writer("ClassList.xml");
	hkPackfileWriter::Options o;
	//xmlWriter.save( writer.getStreamWriter(), o );
}

static int classDump()
{
	classDumpList( hkBuiltinTypeRegistry::StaticLinkedClasses );
	return 0;
}

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(classDump, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
