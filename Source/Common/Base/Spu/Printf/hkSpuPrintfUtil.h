/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_PRINTF_UTIL_H
#define HK_SPU_PRINTF_UTIL_H

#if !defined (HK_PLATFORM_PS3SPU)
class hkSpuLog : public hkSingleton<hkSpuLog>
{
	public:
		virtual void print( const char* fmt, ...);
};
#endif

// Some printf defines used for internal debugging

	// Enable printfs from SPU
//#define HK_ENABLED_SPU_DEBUG_PRINTFS


// Enable printfs if simulating SPU on CPU
//#define HK_VIEW_SPU_DEBUG_PRINTFS_ON_CPU

#define HK_PRINTF_PORT 9

#if defined(HK_PLATFORM_PS3SPU)
#	if defined(HK_ENABLED_SPU_DEBUG_PRINTFS)
#		include <sys/spu_event.h>
		extern "C" {	extern int _spu_call_event_va_arg(uint32_t _spup, const char *fmt, ...);	}
#		define hk_spu_printf(fmt, args...) _spu_call_event_va_arg(HK_PRINTF_PORT<<EVENT_PORT_SHIFT, fmt, ## args)
#		define HK_SPU_DEBUG_PRINTF(A) hk_spu_printf A
#	else
#		define HK_SPU_DEBUG_PRINTF(A)  
#	endif
#else
	#if defined (HK_VIEW_SPU_DEBUG_PRINTFS_ON_CPU)
		#	include <stdio.h>
		#	define HK_SPU_DEBUG_PRINTF(A) hkSpuLog::getInstance().print A
	#else
#		define HK_SPU_DEBUG_PRINTF(A) 
#	endif
#endif


#endif // HK_SPU_PRINTF_UTIL_H


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
