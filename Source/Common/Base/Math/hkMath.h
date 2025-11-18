/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_MATH_MATH_H
#define HK_MATH_MATH_H

#include <Common/Base/Types/hkBaseTypes.h>
#include <Common/Base/Config/hkConfigSimd.h>

// Temporarily disable the alignment warning for AMD64
#if defined(HK_ARCH_X64)
#	pragma warning( disable: 4328 )
#endif

typedef float hkReal;

#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
#	if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
#		include <Common/Base/Math/Types/Sse/hkSseMathTypes.inl>
#	elif defined(HK_ARCH_PS2) // ps2 intrinsics or asm blocks
#		include <Common/Base/Math/Types/Ps2/hkPs2MathTypes.inl>
#		include <Common/Base/Math/Types/Ps2/hkPs2MathTypesCommon.inl>
#	elif defined(HK_PLATFORM_PSP )
#		error simd should be disabled
#	elif defined(HK_PLATFORM_XBOX360)
#		include <Common/Base/Math/Types/Xbox360/hkXbox360MathTypes.inl>
#	elif defined(HK_ARCH_PS3) || defined(HK_ARCH_PS3SPU)
#		include <Common/Base/Math/Types/Ps3/hkPs3MathTypes.inl>
#	else // simd
#		error Unknown platform for SIMD
#	endif
#else // not simd
#	include <Common/Base/Math/Types/Fpu/hkFpuMathTypes.inl>
#	if defined(HK_ARCH_PS2)
#		include <Common/Base/Math/Types/Ps2/hkPs2MathTypesCommon.inl>
#	elif defined (HK_PLATFORM_GC)
#		include <Common/Base/Math/Functions/Gc/hkGcMathFuncs.inl>	
#	elif defined(HK_PLATFORM_PSP) && defined( HK_COMPILER_GCC )
#		include <Common/Base/Math/Types/Psp/hkPspGccMathTypes.inl>
#	endif
#endif
#include <Common/Base/Math/Functions/hkFpuMathFuncs.inl>

extern const hkQuadReal hkQuadReal0000;
extern const hkQuadReal hkQuadReal1111;
extern const hkQuadReal hkQuadReal1000;
extern const hkQuadReal hkQuadReal0100;
extern const hkQuadReal hkQuadReal0010;
extern const hkQuadReal hkQuadReal0001;
extern const hkQuadReal hkQuadReal3333;
extern const hkQuadReal hkQuadRealHalf;
extern const hkQuadReal hkQuadRealMinusHalf;

class hkVector4;
class hkQuaternion;
class hkMatrix3;
class hkRotation;
class hkTransform;
class hkQsTransform;

#include <Common/Base/Math/Vector/hkVector4.h>
#include <Common/Base/Math/Quaternion/hkQuaternion.h>
#include <Common/Base/Math/Matrix/hkMatrix3.h>
#include <Common/Base/Math/Matrix/hkRotation.h>
#include <Common/Base/Math/Matrix/hkTransform.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransform.h>
#include <Common/Base/Math/QsTransform/hkQsTransform.h>
#include <Common/Base/Math/Matrix/hkMatrix4.h>

#if HK_CONFIG_LE == HK_CONFIG_LE_BUILD
#include <Common/Base/Math/Util/hkPhysicsLe.h>
#else
#define HK_PHYSICS_LE /* Using Physics le */
#endif

#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
#	if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
#		include <Common/Base/Math/Vector/Sse/hkSseVector4.inl>
#	elif defined(HK_COMPILER_HAS_INTRINSICS_PS2)
#		include <Common/Base/Math/Vector/Ps2/hkPs2Vector4.inl>
#	elif defined(HK_PS2)
		// to work around inlining issues, Ps2AsmVector4 is split into a and b parts
#		include <Common/Base/Math/Vector/Ps2/hkPs2AsmVector4a.inl>
#	elif defined( HK_PLATFORM_PSP )
#		error simd should be disabled
#	elif defined(HK_PLATFORM_XBOX360)
#		include <Common/Base/Math/Vector/Xbox360/hkXbox360Vector4.inl>
#	elif defined(HK_PLATFORM_PS3) || defined(HK_PLATFORM_PS3SPU)
#		include <Common/Base/Math/Vector/Ps3/hkPs3Vector4.inl>
#	else
#		error Dont know how to do simd on this platform
#	endif
#else // no SIMD
#	if defined(HK_PLATFORM_PSP) && defined(HK_COMPILER_GCC)
#		include <Common/Base/Math/Vector/Psp/Gcc/hkPspGccVector4.inl>
#		include <Common/Base/Math/Vector/Psp/Gcc/hkPspGccMatrix3.inl>
#	endif // PSP && GCC
#	include <Common/Base/Math/Vector/Fpu/hkFpuVector4.inl>
#endif // HK_CONFIG_SIMD


	// common implementations after inline definitions
#include <Common/Base/Math/Vector/hkVector4.inl>

#include <Common/Base/Math/Matrix/hkMatrix3.inl>
#include <Common/Base/Math/Quaternion/hkQuaternion.inl>
#include <Common/Base/Math/Matrix/hkTransform.inl>
#include <Common/Base/Math/Matrix/hkMatrix4.inl>

	// to work around inlining issues, Ps2AsmVector4 is split
#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED && !defined(HK_COMPILER_HAS_INTRINSICS_PS2) && defined(HK_PS2)
#	include <Common/Base/Math/Vector/Ps2/hkPs2AsmVector4b.inl>
#endif

#include <Common/Base/Math/QsTransform/hkQsTransform.inl>
#include <Common/Base/Math/SweptTransform/hkSweptTransform.inl>


#endif // HK_MATH_MATH_H


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
