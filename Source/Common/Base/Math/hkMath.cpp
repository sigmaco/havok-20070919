/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>

const hkQuadReal hkQuadReal0000 = HK_QUADREAL_CONSTANT(0,0,0,0);
const hkQuadReal hkQuadReal1111 = HK_QUADREAL_CONSTANT(1,1,1,1);
const hkQuadReal hkQuadReal1000 = HK_QUADREAL_CONSTANT(1,0,0,0);
const hkQuadReal hkQuadReal0100 = HK_QUADREAL_CONSTANT(0,1,0,0);
const hkQuadReal hkQuadReal0010 = HK_QUADREAL_CONSTANT(0,0,1,0);
const hkQuadReal hkQuadReal0001 = HK_QUADREAL_CONSTANT(0,0,0,1);
const hkQuadReal hkQuadReal3333 = HK_QUADREAL_CONSTANT(3,3,3,3);
const hkQuadReal hkQuadRealHalf = HK_QUADREAL_CONSTANT(0.5f,0.5f,0.5f,0.5f);
const hkQuadReal hkQuadRealMinusHalf = HK_QUADREAL_CONSTANT(-0.5f,-0.5f,-0.5f,-0.5f);

HK_COMPILE_TIME_ASSERT( sizeof( hkContactPoint ) == 32 );

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
