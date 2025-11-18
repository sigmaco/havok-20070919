/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Common/hkpProperty.h>

#include <Common/Base/Container/StringMap/hkStringMap.h>


// used to map the property name specified by the user into a property key

void HK_CALL hkpProperty::mapStringToKey( const char* string, hkUint32& keyOut )
{
	hkUint32 hash = 0;
	for( int i = 0; string[i] != HK_NULL; ++i )
	{
		hash = 31 * hash + string[i];
	}
	keyOut = hash & (hkUint32(-1)>>1); // reserve -1 for empty
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
