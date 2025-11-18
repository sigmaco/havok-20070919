/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef INC_VERSION_H
#define INC_VERSION_H

#define HCT_VERSION_MAJOR 5
#define HCT_VERSION_MINOR 1
#define HCT_VERSION_POINT 0
#define HCT_VERSION_BUILD 1
#define HCT_CURRENT_VERSION_STRING		"5.1.0.1 (5.1.0 Release)"
#define HCT_CURRENT_VERSION_UNICODE		L"5.1.0.1 (5.1.0 Release)"

#define HCT_MAKE_VERSION(major, minor ,point, build) ( ((major) << 24) | ((minor) << 16) | ((point)<<8) | (build) )
#define HCT_CURRENT_VERSION HCT_MAKE_VERSION( HCT_VERSION_MAJOR, HCT_VERSION_MINOR, HCT_VERSION_POINT, HCT_VERSION_BUILD )

#define HCT_IS_MAJOR_COMPATIBLE(thisVer, otherVer) ( (thisVer & ~0x0ffffff) == (otherVer & ~0x0ffffff) )
#define HCT_IS_MINOR_COMPATIBLE(thisVer, otherVer) ( (thisVer & ~0x0ffff) == (otherVer & ~0x0ffff) )
#define HCT_IS_POINT_COMPATIBLE(thisVer, otherVer) ( (thisVer & ~0x0ff) == (otherVer & ~0x0ff) )

#endif // INC_VERSION_H


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
