/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

struct hkSpuMemoryBin
{
#	if defined(__SPU__)
		typedef vec_uint4 quad;
#	else
		typedef void* quad[4];
#	endif

		///
	struct Main
	{
			// Bits showing which elements have valid pointers (1)
			// or are empty (0).
			// MSB overflowMutex(1 bit), signal state (7 bits),
			// reserved(8 bits)
			// reserved(1 bit), pointers(7 bits),
			// overflow(8 bits) LSB
		hkUint32 control;
			// This is a mutex which must be acquired before accessing the overflow area.
			//hkUint32 overflowLock;
		hkUint32 _pad[3];
			// The main storage area.
		quad pointers[7];
	};

		// First 128 bytes
	Main main;
		// Second 128 bytes
	quad overflow[8];
}; //256 bytes

#include <../../spu/include/sys/spu_event.h>
namespace hkSpuHelperThread
{
    enum HelpType
    {
		HELP_TYPE_SYSTEM_PRINTF = EVENT_PRINTF_PORT,
	    HELP_TYPE_FIRST = 10,
	    HELP_TYPE_MEMORY_SERVICE = HELP_TYPE_FIRST, // 10
	    HELP_TYPE_PRINTF, // 11
	    HELP_TYPE_FORWARD_REPORT, // 12
	    HELP_TYPE_FORWARD_WARNING, // 13
	    HELP_TYPE_FORWARD_ASSERT, // 14
	    HELP_TYPE_FORWARD_ERROR, // 15
	    HELP_TYPE_LAST
    };
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
