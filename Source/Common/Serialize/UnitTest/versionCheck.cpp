/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Serialize/Util/hkVersionCheckingUtils.h>
#include <Common/Compat/hkHavokAllClasses.h>
#include <Common/Compat/hkHavokAllClassUpdates.h>

namespace 
{
	struct NullStream : public hkStreamWriter
	{
		int write(const void* buf, int nbytes)	{ return nbytes; }
		hkBool isOk() const { return true; }
	};
}

static int versioningCheck()
{

#	define HK_HAVOK_CLASSES_VERSION(A,V) hkVersionUtil::recomputeClassMemberOffsets( hkHavok##A##Classes::Classes, V );
#	include <Common/Compat/hkHavokVersionClasses.h>
#	undef HK_HAVOK_CLASSES_VERSION

	NullStream dummy;
	hkOstream nullOutput(&dummy);

	hkResult res;
	hkError::getInstance().setEnabled(0x786cb087, false);
#	define HK_CLASS_UPDATE_INFO(OLD,NEW) \
	res = hkVersionCheckingUtils::verifyUpdateDescription( nullOutput, hkHavok##OLD##Classes ::Classes, hkCompat_hk##OLD##_hk##NEW ::hkVersionUpdateDescription, hkVersionCheckingUtils::IGNORE_REMOVED ); \
	HK_TEST2( res == HK_SUCCESS, #OLD" -> "#NEW );
#	include <Common/Compat/hkCompatVersions.h>
#	undef HK_CLASS_UPDATE_INFO

	hkError::getInstance().setEnabled(0x786cb087, true);
	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(versioningCheck, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
