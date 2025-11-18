/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
// Build configuration settings
// These are compile time settings for the libraries.
// Changing these values with compiled libs will not work,

// If this setting is changed you must rebuild all Havok libs

// EQSELECT: HK_CONFIG_SIMD, Choose to enable or disable simd instructions:
// This determines whether or not we use simd instructions.

#ifndef HK_BASE_CONFIGSIMD_H
#define HK_BASE_CONFIGSIMD_H

#define HK_CONFIG_SIMD_ENABLED 1 // Enabled
#define HK_CONFIG_SIMD_DISABLED 2 // Disabled

#if !defined(HKBASE_HKBASETYPES_H)
#	error hkbase/hkBase.h needs to be included before this file
#endif

#ifndef HK_CONFIG_SIMD

	// win32
#	if defined(HK_PLATFORM_WIN32)
#		if defined (HK_PLATFORM_X64) || defined(HK_SIMULATE_SPU_DMA_ON_CPU)
#			define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED
#		else
#			define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED
#		endif

	// AMD x64
#	elif defined(HK_ARCH_X64)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED

	// ps2
#	elif defined(HK_PLATFORM_PS2)
#		if defined(HK_COMPILER_MWERKS) || defined( HK_COMPILER_SNC )
#			define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED
#		else
#			define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED
#		endif

	// psp
#	elif defined(HK_PLATFORM_PSP)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED

	// ps3
#	elif defined(HK_PLATFORM_PS3)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED

	// ps3-spu
#	elif defined(HK_PLATFORM_PS3SPU)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED

	// xbox1
#	elif defined(HK_PLATFORM_XBOX)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED

	// x360
#	elif defined(HK_PLATFORM_XBOX360)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED

	// Gamecube
#	elif defined(HK_PLATFORM_GC)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED

	// Linux
#	elif defined(HK_PLATFORM_UNIX)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED

	// Mac
#	elif defined(HK_PLATFORM_MACPPC)
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED

#	elif defined(HK_PLATFORM_MAC386) 
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED
	// else
#	else
#   	error Unknown Platform
#		define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED
#	endif
#else // ifndef HK_CONFIG_SIMD
#	if (HK_CONFIG_SIMD != HK_CONFIG_SIMD_ENABLED) && (HK_CONFIG_SIMD != HK_CONFIG_SIMD_DISABLED)
#		error invalid config simd option
#	endif
#endif // ifndef HK_CONFIG_SIMD

#define HK_CONFIG_LE_BUILD 1 // Enabled
#define HK_CONFIG_LE_DISABLED 2 // Disabled

#define HK_CONFIG_LE HK_CONFIG_LE_DISABLED

#endif // HK_BASE_CONFIGSIMD_H

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
