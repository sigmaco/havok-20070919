/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKBASE_HKBASETYPES_H
#define HKBASE_HKBASETYPES_H

//
// compiler
//

#if defined(_MSC_VER)
#	define HK_COMPILER_MSVC
#elif defined(__SNC__)
#	define HK_COMPILER_SNC
#elif defined(__GNUC__)
#	define HK_COMPILER_GCC
#elif defined(__MWERKS__)
#	define HK_COMPILER_MWERKS
#elif defined(__INTEL_COMPILER)
#	define HK_COMPILER_INTEL
#else
#	error Could not detect compiler
#endif

//
// architecture
//

#if defined(__i386__) || defined(_M_IX86)
#	define HK_ARCH_IA32
#	define HK_ENDIAN_LITTLE 1
#	define HK_ENDIAN_BIG	0
#	define HK_POINTER_SIZE 4
#elif defined(_M_AMD64) || defined(_M_X64)
#	define HK_ARCH_X64
#	define HK_ENDIAN_LITTLE 1
#	define HK_ENDIAN_BIG	0
#	define HK_POINTER_SIZE 8
#elif defined( R3000 ) || defined( __R4000__ )
#	define HK_ARCH_PSP
#	define HK_ENDIAN_LITTLE 1
#	define HK_ENDIAN_BIG	0
#	define HK_POINTER_SIZE 4
#elif (!defined( R3000 )) && (!defined( __R4000__ )) && (defined( __mips__ ) || defined( __MIPS__ ))
#	define HK_ARCH_PS2
#	define HK_ENDIAN_LITTLE 1
#	define HK_ENDIAN_BIG	0
#	define HK_POINTER_SIZE 4
#elif defined(_PPC_) || defined(__POWERPC__) || defined(_M_PPC) || defined(_M_PPCBE) || defined(GEKKO)
#	define HK_ARCH_PPC
#	define HK_ENDIAN_LITTLE 0
#	define HK_ENDIAN_BIG	1
#	define HK_POINTER_SIZE 4
#elif defined(__PPU__) && defined(__CELLOS_LV2__)
#	define HK_ARCH_PS3
#	define HK_ENDIAN_LITTLE 0
#	define HK_ENDIAN_BIG	1
#elif defined(__SPU__) && defined(__CELLOS_LV2__)
#	define HK_ARCH_PS3SPU
#	define HK_ENDIAN_LITTLE 0
#	define HK_ENDIAN_BIG	1
#else
#	error Could not autodetect target architecture
#endif

#if defined(HK_ARCH_PS3) || defined(HK_ARCH_PS3SPU)
# include <sdk_version.h>
# define HK_CELL_SDK_VERSION CELL_SDK_VERSION
# if ( HK_CELL_SDK_VERSION < 0x080000 )
#	  define HK_POINTER_SIZE 8 // Caution: On SPU the pointer size is 4, but usually where this is used pointers will be "shadows" from the PPU
#	else
#	  define HK_POINTER_SIZE 4
#	endif
#endif
//
// platform
//

#if defined(_XBOX)
#   if defined(HK_ARCH_PPC)
#	  define HK_PLATFORM_XBOX360
#	else
#	  define HK_PLATFORM_XBOX
#   endif
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(__APPLE_CC__)
#	if defined( HK_ARCH_IA32 )
#		define HK_PLATFORM_MAC386
#	elif defined( HK_ARCH_PPC )
#		define HK_PLATFORM_MACPPC
#	else
#		error Mac platform undefined
#	endif
#	define HK_PLATFORM_IS_CONSOLE 0
#elif defined(_WIN32)
#	define HK_PLATFORM_WIN32
#	if defined(_WIN64)
#		define HK_PLATFORM_X64
#	endif
#	define HK_PLATFORM_IS_CONSOLE 0
#elif (!defined( R3000 )) && (!defined( __R4000__ )) && (defined( __mips__ ) || defined( __MIPS__ ))
#	define HK_PLATFORM_PS2
#	define HK_PS2
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(__unix__)
#	define HK_PLATFORM_UNIX
#	define HK_PLATFORM_IS_CONSOLE 0
#elif defined(GEKKO) || defined(__PPCGEKKO__) //Also have custom added HK_REVOLUTION compiler switch
#	define HK_PLATFORM_GC
#if defined(RVL_OS)
#	define HK_PLATFORM_RVL
#endif
#	define HK_PLATFORM_IS_CONSOLE 1

#elif defined( R3000 ) || defined( __R4000__ )
#	define HK_PLATFORM_PSP
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(__PPU__) && defined(__CELLOS_LV2__)
#	define HK_PLATFORM_PS3
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(__SPU__) && defined(__CELLOS_LV2__)
#	define HK_PLATFORM_PS3SPU
#	define HK_PLATFORM_SPU
#	define HK_PLATFORM_IS_CONSOLE 1
#else
#	error Could not autodetect target platform.
#endif

//
// types
//

/// hkReal is the default floating point type.
typedef float  hkReal;
/// hkFloat is provided if floats are explicitly required.
typedef float  hkFloat32;
/// hkDouble is provided if doubles are explicit required.
typedef double hkDouble64;


/// Signed 8 bit integer
typedef signed char		hkChar;
/// Signed 8 bit integer
typedef signed char		hkInt8;
/// Signed 16 bit integer
typedef signed short	hkInt16;
/// Signed 32 bit integer
typedef signed int		hkInt32;

/// Unsigned 8 bit integer
typedef unsigned char	hkUchar;
/// Unsigned  8 bit integer
typedef unsigned char	hkUint8;
/// Unsigned  16 bit integer
typedef unsigned short	hkUint16;
/// Unsigned  32 bit integer
typedef unsigned int	hkUint32;

/// An integer type guaranteed to be the same size as a pointer.
#if defined(HK_ARCH_PS2)
	typedef unsigned int hkUlong;
#elif defined(HK_ARCH_PSP)
	typedef unsigned int hkUlong;
#elif defined(HK_ARCH_X64)
	typedef unsigned __int64 hkUlong;
#elif defined(HK_COMPILER_MSVC) && (_MSC_VER >= 1300)
	typedef unsigned long __w64 hkUlong; // VC7.0 or higher, 64bit warnings
#else
	typedef unsigned long hkUlong;
#endif


#define HK_CPU_PTR( A ) A

typedef void* hk_va_list;

/// a simple success/failure enum.
enum hkResult
{
	HK_SUCCESS = 0,
	HK_FAILURE = 1
};

#if defined( HK_PLATFORM_PS3SPU) 
#	include <spu_intrinsics.h>
#endif

//
// useful macros
//

#if  defined(DEBUG) || defined(_DEBUG)
#	undef HK_DEBUG
#	define HK_DEBUG
#	define hkDebug 1
#else
#	define hkDebug 0
#endif

#if defined(HK_ARCH_IA32)
#	if defined(HK_COMPILER_MSVC)
#		define HK_BREAKPOINT(ID) __asm { int 3 }
#	elif defined(HK_COMPILER_GCC)
#		define HK_BREAKPOINT(ID) asm("int $3");
#	else
#		error unknown asm syntax
#	endif
#elif defined(HK_PLATFORM_PS3)
#	define HK_BREAKPOINT(ID) 	__asm__ volatile ( "tw 31,1,1" )
#elif defined(HK_PLATFORM_PS3SPU)
#	define HK_BREAKPOINT(ID) __asm__ volatile ("ai $0, %0, 0\n\tstopd $0,$0,$0" : : "r"(ID) );
#elif defined(HK_PLATFORM_XBOX360)
#	define HK_BREAKPOINT(ID) __debugbreak();
#else
#	define HK_BREAKPOINT(ID) ((*((int*)0)) = ID)
#endif

#define HK_NULL 0

// use the compiler friendly but programmer ugly version for release only
#ifdef HK_DEBUG
#	define HK_MULTILINE_MACRO_BEGIN	do {
#	define HK_MULTILINE_MACRO_END		} while(0)
#else
#	define HK_MULTILINE_MACRO_BEGIN	if(1) {
#	define HK_MULTILINE_MACRO_END		} else
#endif

/// Note that ALIGNMENT must be a power of two for this to work.
/// Note: to use this macro you must cast your pointer to a byte pointer or to an integer value.
#define HK_NEXT_MULTIPLE_OF(ALIGNMENT, VALUE)  ( ((VALUE) + ((ALIGNMENT)-1)) & (~((ALIGNMENT)-1)) )

/// The offset of a member within a structure
#define HK_OFFSET_OF(CLASS,MEMBER) int(reinterpret_cast<hkUlong>(&(reinterpret_cast<CLASS*>(16)->MEMBER))-16)

/// A check for whether the offset of a member within a structure is as expected
#define HK_OFFSET_EQUALS(CLASS,MEMBER,OFFSET) (HK_OFFSET_OF(CLASS,MEMBER)==OFFSET)

/// Join two preprocessor tokens, even when a token is itself a macro.
#define HK_PREPROCESSOR_JOIN_TOKEN(A,B) HK_PREPROCESSOR_JOIN_TOKEN2(A,B)
#define HK_PREPROCESSOR_JOIN_TOKEN2(A,B) HK_PREPROCESSOR_JOIN_TOKEN3(A,B)
#define HK_PREPROCESSOR_JOIN_TOKEN3(A,B) A##B

/// Creates an uninitialized buffer large enough for object of type TYPE to fit in while aligned to ALIGN boundary. Creates a pointer VAR to this aligned address.
#define HK_DECLARE_ALIGNED_LOCAL_PTR( TYPE, VAR, ALIGN  )											\
	const int VAR ## BufferSize = ALIGN + sizeof(TYPE);												\
	char VAR ## Buffer[VAR ## BufferSize];															\
	TYPE* VAR = reinterpret_cast<TYPE*>( HK_NEXT_MULTIPLE_OF(ALIGN, hkUlong( VAR ## Buffer )) );	\


//
// compiler specific settings
//


	// *************************************
	//			GCC and SN
	// *************************************
#if defined(HK_COMPILER_GCC) || defined(HK_COMPILER_SNC)
#   if defined(__GNUC_PATCHLEVEL__)
#   	define HK_COMPILER_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 +__GNUC_PATCHLEVEL__)
#	else
#		define HK_COMPILER_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100)
#   endif
#	define HK_RESTRICT __restrict
#	if defined( HK_COMPILER_SNC ) && !( defined( HK_PLATFORM_GC ) || !defined( HK_PLATFORM_PS2 ) )
#		define HK_VERY_UNLIKELY(EXPR) __builtin_expect((EXPR),0)
#		define HK_VERY_LIKELY(EXPR) __builtin_expect((EXPR),1)
#	endif
#	if (HK_COMPILER_GCC_VERSION >= 40000)
#		undef HK_OFFSET_OF
#		define HK_OFFSET_OF(CLASS,MEMBER) __builtin_offsetof(CLASS,MEMBER)
#	elif ( HK_COMPILER_GCC_VERSION >= 30400 ) && !defined( HK_COMPILER_SNC )
#		undef HK_OFFSET_OF
#		define HK_OFFSET_OF(CLASS,MEMBER) (__offsetof__(reinterpret_cast<long>(&reinterpret_cast<CLASS*>(16)->MEMBER)-16))
#	endif
#	if ( HK_COMPILER_GCC_VERSION >= 40000 ) && !defined( HK_COMPILER_SNC )
#		undef HK_OFFSET_EQUALS
#		define HK_OFFSET_EQUALS(C,M,O) true
#	endif
#	define HK_ALIGN(DECL, ALIGNMENT) DECL __attribute__((aligned(ALIGNMENT)))
#	define HK_ALIGN16(DECL) DECL __attribute__((aligned(16)))
#	define HK_ALIGN128(DECL) DECL __attribute__((aligned(128)))
#	if defined( HK_PLATFORM_PSP ) && defined( HK_COMPILER_SNC )
#		define HK_CLASSALIGN(DECL, ALIGNMENT) DECL
#	else
#		define HK_CLASSALIGN(DECL, ALIGNMENT) HK_ALIGN(DECL, ALIGNMENT)
#	endif
#	define HK_CLASSALIGN16(DECL) HK_ALIGN16(DECL)
#   if defined(HK_PLATFORM_PS2)
	    typedef unsigned long hkUint64;	// long is 64 bits on PS2
	    typedef long hkInt64;
		typedef int hkInt128 __attribute__ ((mode (TI)));
		typedef unsigned int hkUint128 __attribute__ ((mode (TI)));
#   elif defined(HK_PLATFORM_PS3)
#     if ( HK_CELL_SDK_VERSION < 0x080000 )
		    typedef unsigned long hkUint64;
		    typedef long hkInt64;
#     else
		    typedef unsigned long long hkUint64;
		    typedef long long hkInt64;
#     endif
#   elif defined(HK_PLATFORM_PS3SPU)
		typedef unsigned long long hkUint64;
		typedef long long hkInt64;
#   else
	    typedef unsigned long long hkUint64;
	    typedef long long hkInt64;
#   endif
#	if defined(HK_PLATFORM_GC)
		typedef hkUint64 hkSystemTime; // GameCube Time ticks are 64 bit
#	else
		typedef long hkSystemTime;
#	endif
#	if defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_MACPPC) || ( defined(HK_PLATFORM_PS3) && ( HK_CELL_SDK_VERSION < 0x080000 ) ) || defined (HK_PLATFORM_PS3SPU)
		typedef unsigned long hk_size_t;
#	else
		typedef unsigned hk_size_t;
#	endif
#	if defined(HK_ARCH_IA32) && HK_COMPILER_GCC_VERSION >= 30100
#		define HK_COMPILER_HAS_INTRINSICS_IA32
#	endif
#	if defined(HK_ARCH_PS2) && HK_COMPILER_GCC_VERSION >= 30003 && !defined(HK_COMPILER_SNC)
#		define HK_COMPILER_HAS_INTRINSICS_PS2
#	endif
#	define HK_FORCE_INLINE inline
// calling convention
#	define HK_CALL
#	define HK_FAST_CALL


	// *************************************
	//			MICROSOFT and INTEL
	// *************************************
#elif defined(HK_COMPILER_MSVC) || defined(HK_COMPILER_INTEL)
#	define HK_COMPILER_SUPPORTS_PCH
#	define HK_COMPILER_MSVC_VERSION _MSC_VER
#	define HK_COMPILER_INTEL_VERSION _MSC_VER
#	if (_MSC_VER >= 1400) // 2005 only
#		define HK_RESTRICT __restrict
#	else
#		define HK_RESTRICT 
#	endif
#	pragma warning( disable : 4786 ) // Debug tuncated to 255:
#	pragma warning( disable : 4530 ) // C++ Exception handler used but not enabled:(used in <xstring>)
#	if defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360) || defined(HK_PLATFORM_WIN32)
#		define HK_ALIGN(DECL, ALIGNMENT) __declspec(align(ALIGNMENT)) DECL
#		define HK_ALIGN16(DECL) __declspec(align(16)) DECL
#		define HK_ALIGN128(DECL) __declspec(align(128)) DECL
#		define HK_FORCE_INLINE __forceinline
#		define HK_CLASSALIGN(DECL, ALIGNMENT) HK_ALIGN(DECL, ALIGNMENT)
#		define HK_CLASSALIGN16(DECL) HK_ALIGN16(DECL)
#	elif defined(HK_PLATFORM_UNIX)
#		define HK_ALIGN(DECL, ALIGNMENT) DECL __attribute__((aligned(ALIGNMENT)))
#		define HK_ALIGN16(DECL) DECL __attribute__((aligned(16)))
#		define HK_ALIGN128(DECL) DECL __attribute__((aligned(128)))
#		define HK_FORCE_INLINE inline
#		define HK_CLASSALIGN(DECL, ALIGNMENT) HK_ALIGN(DECL, ALIGNMENT)
#		define HK_CLASSALIGN16(DECL) HK_ALIGN16(DECL)
#	else
#		error "fix the alignment on this platform"
#	endif
#	if defined(HK_ARCH_IA32)
		typedef unsigned __int64 hkUint64;
		typedef __int64 hkInt64;
		typedef long hkSystemTime;
#		if defined(HK_COMPILER_MSVC) && (_MSC_VER >= 1300)
			typedef unsigned __w64 hk_size_t; // VC7.0 or higher, 64bit warnings
#		else
			typedef unsigned hk_size_t;
#		endif
#		define HK_COMPILER_HAS_INTRINSICS_IA32
#	elif defined( HK_ARCH_PPC )
		typedef unsigned __int64 hkUint64;
		typedef __int64 hkInt64;
		typedef unsigned hk_size_t;
		typedef __int64 hkSystemTime; // 64bit time
#		define HK_COMPILER_HAS_INTRINSICS_PPC
#	elif defined(HK_ARCH_X64)
		typedef unsigned __int64 hkUint64;
		typedef __int64 hkInt64;
		typedef __int64 hkSystemTime;
		typedef unsigned __int64 hk_size_t;
#		define HK_COMPILER_HAS_INTRINSICS_IA32
#	else
#		error No defs for this architecture
#	endif
// calling convention
#	define HK_CALL __cdecl
#	define HK_FAST_CALL __fastcall

	// *************************************
	//			METROWERKS
	// *************************************
#elif defined(HK_COMPILER_MWERKS)
#	define HK_ALIGN(DECL, ALIGNMENT) DECL __attribute__((aligned(ALIGNMENT)))
#	define HK_ALIGN16(DECL) DECL __attribute__((aligned(16)))
#	define HK_ALIGN128(DECL) DECL __attribute__((aligned(128)))
#	define HK_CLASSALIGN(DECL, ALIGNMENT) DECL
#	define HK_CLASSALIGN16(DECL) DECL
#   if defined(HK_PLATFORM_PS2)
		typedef unsigned long hkUint64;	// long is 64 bits on PS2
		typedef long hkInt64;
#   endif
#	if defined(HK_PLATFORM_PSP)
		typedef unsigned long long hkUint64;	// long long is 64 bits on PSP
		typedef long long hkInt64;
#	endif
#   if defined(HK_PLATFORM_PS2) || defined(HK_PLATFORM_PSP)
		typedef long hkSystemTime;
		typedef unsigned hk_size_t;
		typedef __int128 hkInt128;
		typedef unsigned __int128 hkUint128;
#   else
		typedef unsigned long long hkUint64;
		typedef long long hkInt64;
#		if defined(HK_PLATFORM_GC)
			typedef hkUint64 hkSystemTime; // GameCube Time ticks are 64 bit
#		else
			typedef unsigned long hkSystemTime;
#		endif
		typedef unsigned long hk_size_t;
#   endif
#	define HK_FORCE_INLINE inline
// calling convention
#	define HK_CALL
#	define HK_FAST_CALL

#else
#	error Unknown compiler
#endif // compilers

#if defined(HK_PLATFORM_PS3) || defined(HK_PLATFORM_PS3SPU) || defined(HK_SIMULATE_SPU_DMA_ON_CPU)
#	define HK_PLATFORM_HAS_SPU
#	define HK_ON_PLATFORM_HAS_SPU(code) code
#else
#	define HK_ON_PLATFORM_HAS_SPU(code)
#endif

#if defined(HK_PLATFORM_PS3) || defined(HK_PLATFORM_WIN32) || defined(HK_PLATFORM_XBOX360) || defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_MACPPC) || defined(HK_PLATFORM_UNIX)
#	define HK_PLATFORM_MULTI_THREAD
#endif

#if defined(HK_PLATFORM_PS3) || defined(HK_PLATFORM_PS3SPU)
#	define HK_ALWAYS_INLINE __attribute__((always_inline)) inline
#	if !defined (HK_DEBUG)
#		define HK_LOCAL_INLINE inline
#	else
#		define HK_LOCAL_INLINE
#	endif
#	define HK_ASM_SEP(a) __asm("#*****" a )
#else
#	define HK_ALWAYS_INLINE HK_FORCE_INLINE
#	define HK_LOCAL_INLINE HK_FORCE_INLINE
#	define HK_ASM_SEP(a) 
#endif

#if defined(HK_PLATFORM_SPU) 
#	define HK_NOSPU_VIRTUAL 
#else
#	define HK_NOSPU_VIRTUAL virtual
#endif

#ifndef HK_RESTRICT
#	define HK_RESTRICT
#endif
#ifndef HK_VERY_UNLIKELY
#	define HK_VERY_UNLIKELY(EXPR) EXPR
#	define HK_VERY_LIKELY(EXPR) EXPR
#endif

typedef hkUint16 hkObjectIndex;
typedef hkReal hkTime;

#define HK_INVALID_OBJECT_INDEX 0xffff


HK_FORCE_INLINE hkInt32 HK_CALL hkPointerToInt32( const void* ptr )
{
	return static_cast<int>( hkUlong(ptr) );
}

/// get the byte offset of B - A, as a full ulong.
HK_FORCE_INLINE hkUlong HK_CALL hkGetByteOffset( const void* base, const void* pntr)
{
	return hkUlong(pntr) - hkUlong(base);
}

/// get the byte offset of B - A, as an int (64bit issues, so here for easy code checks)
HK_FORCE_INLINE int HK_CALL hkGetByteOffsetInt( const void* base, const void* pntr)
{
	return static_cast<int>( hkGetByteOffset( base, pntr ) );
}

/// get the byte offset of B - A, as a full 64bit hkUint64.
HK_FORCE_INLINE hkUint32 HK_CALL hkGetByteOffsetCpuPtr( const HK_CPU_PTR(void*) base, const HK_CPU_PTR(void*) pntr)
{
	return hkUint32(hkUlong((HK_CPU_PTR(const char*))(pntr) - (HK_CPU_PTR(const char*))(base)));
}

template <typename TYPE>
HK_ALWAYS_INLINE TYPE* HK_CALL hkAddByteOffset( TYPE* base, hkUlong offset )
{
	return reinterpret_cast<TYPE*>( reinterpret_cast<char*>(base) + offset );
}

template <typename TYPE>
HK_ALWAYS_INLINE TYPE HK_CALL hkAddByteOffsetCpuPtr( TYPE base, hkUlong offset )
{
	return reinterpret_cast<TYPE>( reinterpret_cast<char*>(base) + offset );
}

template <typename TYPE>
HK_ALWAYS_INLINE const TYPE* HK_CALL hkAddByteOffsetConst( const TYPE* base, hkUlong offset )
{
	return reinterpret_cast<const TYPE*>( reinterpret_cast<const char*>(base) + offset );
}

template <typename TYPE>
HK_ALWAYS_INLINE TYPE HK_CALL hkAddByteOffsetCpuPtrConst( TYPE base, hkUlong offset )
{
	return reinterpret_cast<const TYPE>( reinterpret_cast<const char*>(base) + offset );
}

	/// If you have a pair of pointers and you have one pointer, than this function allows you to quickly get the other pointer of the pair.
template <typename TYPE>
HK_ALWAYS_INLINE TYPE* HK_CALL hkSelectOther( TYPE* a, TYPE* pairA, TYPE* pairB )
{
	return reinterpret_cast<TYPE*>( hkUlong(a) ^ hkUlong(pairA) ^ hkUlong(pairB) );
}

HK_FORCE_INLINE hkUint32 hkNextPowerOf2(hkUint32 in) 
{
	in -= 1;

	in |= in >> 16;
	in |= in >> 8;
	in |= in >> 4;
	in |= in >> 2;
	in |= in >> 1;

	return in + 1; 
}

#define hkSizeOf(A) int(sizeof(A))

#define HK_REFLECTION_CLASSFILE_DESTINATION(PATH)
#define HK_REFLECTION_CLASSFILE_HEADER(PATH)
#define HK_DECLARE_REFLECTION() \
	static const struct hkInternalClassMember Members[]; \
	struct DefaultStruct

class hkClass;

/// A generic object with metadata.
struct hkVariant
{
	void* m_object;
	const hkClass* m_class;
};

	/// False is zero, true is _any_ non-zero value.
	/// Thus comparisons like bool32 == true will not work as expected.
typedef int hkBool32;

	/// A wrapper to store a hkBool in one byte, regardless of compiler options.
class hkBool
{
	public:

		inline hkBool()
		{
		}

		inline hkBool(bool b)
		{
			m_bool = static_cast<char>(b);
		}

		inline operator bool() const
		{
			return m_bool != 0;
		}

		inline hkBool& operator=(bool e)
		{
			m_bool = static_cast<char>(e);
			return *this;
		}

		inline hkBool operator==(bool e) const
		{
			return static_cast<int>(m_bool) == static_cast<int>(e);
		}

		inline hkBool operator!=(bool e) const
		{
			return static_cast<int>(m_bool) != static_cast<int>(e);
		}

	private:
		char m_bool;
};

    /// A wrapper to store a float in 16 bit. This is a non ieee representation.
    /// Basically we simply chop off the last 16 bits. That means the whole floating point range
    /// will be supported, but only with 7 bit precision
class hkHalf
{
    public:
    
	    inline hkHalf(){   }
    
	    inline hkHalf(const float& f)
	    {
		    int t = ((const int*)&f)[0];
		    m_value = hkInt16(t>>16);
	    }
    
	    inline hkHalf& operator=(const float& f)
	    {
		    int t = ((const int*)&f)[0];
		    m_value = hkInt16(t>>16);
		    return *this;
	    }
    
	    inline operator float() const
	    {
		    union
		    {
			    int i;
			    float f;
		    } u;
		    u.i = (m_value <<16);
		    return u.f;
	    }
    
    private:
	    hkInt16 m_value;
};

#define HK_UFLOAT8_MAX_VALUE 256
extern "C"
{
	extern const hkReal hkUFloat8_intToReal[HK_UFLOAT8_MAX_VALUE];
}

	/// A wrapper to store an unsigned float into 8 bit. 
	/// This has a reduced range. Basically the encoding
	/// uses a table holding an exponential function.
	/// The error is roughly 7%
class hkUFloat8
{
public:
	enum { MAX_VALUE = HK_UFLOAT8_MAX_VALUE };

	// the minimum value to encode which is non zero
#define hkUFloat8_eps 0.01f

	// the maximum value to encode
#define hkUFloat8_maxValue 1000000.0f

	inline hkUFloat8(){		}

	inline hkUFloat8& operator=(const float& fv)
	{
		// binary search. We are using integer compare, as we always have positive values in the array
		hkInt32 f = *(int*)&fv;
		hkInt32* minf = (hkInt32*)&hkUFloat8_intToReal[0];
		hkInt32* maxf = (hkInt32*)&hkUFloat8_intToReal[MAX_VALUE];
		hkInt32* midf = (hkInt32*)&hkUFloat8_intToReal[MAX_VALUE/2];

		for (int i = 6; i>=0; i--)
		{
			if ( f > midf[0]){		minf = midf;	}	else	{	maxf = midf;	}
			midf = (hkInt32*)(  (hkUlong(minf)>>1) + (hkUlong(maxf)>>1) );
		}

		if ( f > midf[0])
		{
			midf++;
		}

		hkUlong fi = midf - (hkInt32*)(&hkUFloat8_intToReal[0]);
		m_value = hkUint8(fi);
		return *this;
	}

	inline hkUFloat8(const float f)
	{
		*this = f;
	}


	inline operator float() const
	{
		return hkUFloat8_intToReal[m_value];
	}

public:
	hkUint8 m_value;
};

// A lookup table for converting unsigned char to float
// useful for avoiding LHS

extern "C"
{
	extern const hkReal hkUInt8ToReal[256];
}

	/// A wrapper to store an enum with explicit size.
template<typename ENUM, typename STORAGE>
class hkEnum
{
	public:

		hkEnum()
		{
		}

		hkEnum(ENUM e)
		{
			m_storage = static_cast<STORAGE>(e);
		}

		operator ENUM() const
		{
			return static_cast<ENUM>(m_storage);
		}
		void operator=(ENUM e)
		{
			m_storage = static_cast<STORAGE>(e);
		}
		hkBool operator==(ENUM e) const
		{
			return m_storage == static_cast<STORAGE>(e);
		}
		hkBool operator!=(ENUM e) const
		{
			return m_storage != static_cast<STORAGE>(e);
		}

	private:

		STORAGE m_storage;
};

	/// A wrapper to store bitfield with an with explicit size.
template<typename BITS, typename STORAGE>
class hkFlags
{
	public:

		hkFlags()
		{
		}

		hkFlags(STORAGE s)
		{
			m_storage = s;
		}

		void clear()
		{
			m_storage = 0;
		}
		void setAll( STORAGE s )
		{
			m_storage = s;
		}

		void orWith( STORAGE s )
		{
			m_storage |= s;
		}

		void andWith( STORAGE s )
		{
			m_storage &= s;
		}

		STORAGE get() const
		{
			return m_storage;
		}

		STORAGE get( STORAGE mask ) const
		{
			return m_storage & mask;
		}

		bool anyIsSet( STORAGE mask ) const
		{
			return (m_storage & mask) != 0;
		}
		
		bool allAreSet( STORAGE mask ) const
		{
			return (m_storage & mask) == mask;
		}

		bool operator==( const hkFlags& f ) const
		{
			return f.m_storage == m_storage;
		}

		bool operator!=( const hkFlags& f ) const
		{
			return f.m_storage != m_storage;
		}

	private:

		STORAGE m_storage;
};

#if defined(HK_PLATFORM_PS3SPU) 
	template <typename TYPE> struct hkSpuStorage {}; // default is error
	template <typename TYPE> struct hkSpuStorage<TYPE*> { typedef vec_uint4 StorageType; typedef unsigned PromoteType;  };
	template <> struct hkSpuStorage<void*> { typedef vec_uint4 StorageType; typedef unsigned PromoteType; };
	template <> struct hkSpuStorage<int> { typedef vec_int4 StorageType; typedef int PromoteType; };
	template <> struct hkSpuStorage<unsigned> { typedef vec_uint4 StorageType; typedef unsigned PromoteType; };
	template <> struct hkSpuStorage<float> { typedef vec_float4 StorageType; typedef float PromoteType; };
	template <> struct hkSpuStorage<hkBool> { typedef vec_int4 StorageType; typedef hkBool PromoteType; };
	
#	define HK_PADSPU_PROMOTE(e) spu_promote( (typename hkSpuStorage<TYPE>::PromoteType)(e), 0 )
#	define HK_PADSPU_EXTRACT(e) (TYPE)spu_extract( e, 0 )

#else
#	define HK_PADSPU_PROMOTE(e) e
#	define HK_PADSPU_EXTRACT(e) e
#endif

	/// wrapper class for variables in structures. 
	/// Basically on the ps3 spu, the spu can only poorly
	/// access non aligned members. This class give each variable
	/// 16 bytes, thereby dramatically decreasing code size and cpu overhead
template <typename TYPE>
class hkPadSpu
{
	public:

		HK_FORCE_INLINE hkPadSpu() {}

		HK_FORCE_INLINE hkPadSpu(TYPE e)
			: m_storage( HK_PADSPU_PROMOTE(e) )
		{
		}

		HK_FORCE_INLINE void operator=(TYPE e)
		{
			m_storage = HK_PADSPU_PROMOTE(e);
		}

		HK_FORCE_INLINE TYPE val() const
		{
			return HK_PADSPU_EXTRACT(m_storage);
		}

		HK_FORCE_INLINE TYPE operator->() const
		{
			return HK_PADSPU_EXTRACT(m_storage);
		}

		HK_FORCE_INLINE operator TYPE() const
		{
			return val();
		}

	private:

#	if defined(HK_PLATFORM_PS3SPU) 
		typename hkSpuStorage<TYPE>::StorageType m_storage;
#	elif defined(HK_PLATFORM_HAS_SPU)
		HK_ALIGN16(TYPE m_storage);
		hkUchar m_pad[ 16-sizeof(TYPE) ];
#	else
		TYPE m_storage;
#	endif
};

#if defined(HK_PLATFORM_SPU) 
// use our hkPadSpu on spu only
#	define HK_PAD_ON_SPU(TYPE) hkPadSpu<TYPE>
// some macros to nicefy code
#	define HK_ON_CPU(code)
#	define HK_ON_SPU(code) code
#else
#	define HK_PAD_ON_SPU(TYPE) TYPE
#	define HK_ON_CPU(code) code
#	define HK_ON_SPU(code)
#endif

#define HK_HINT_SIZE16(A) hkInt16(A)

struct hkCountOfBadArgCheck
{
	class ArgIsNotAnArray;
	template<typename T> static ArgIsNotAnArray isArrayType(const T*, const T* const*);
	static int isArrayType(const void*, const void*);
};

	/// Returns the number of elements in the C array.
#define HK_COUNT_OF(x) ( \
	0 * sizeof( reinterpret_cast<const ::hkCountOfBadArgCheck*>(x) ) + \
	0 * sizeof( ::hkCountOfBadArgCheck::isArrayType((x), &(x)) ) + \
	sizeof(x) / sizeof((x)[0]) ) 

#if defined(HK_PLATFORM_PS3SPU)
	extern hkUlong g_spuLowestStack;
#	define HK_SPU_INIT_STACK_SIZE_TRACE()   { int reference = 0; g_spuLowestStack = hkUlong(&reference); }
#	define HK_SPU_UPDATE_STACK_SIZE_TRACE() { int reference = 0; if ( hkUlong(&reference) < g_spuLowestStack ) g_spuLowestStack = hkUlong(&reference); }
#	define HK_SPU_OUTPUT_STACK_SIZE_TRACE() { int reference = 0; hkUlong stackSize = hkUlong(&reference) - g_spuLowestStack; static hkUlong maxStackSize = 0; if ( stackSize > maxStackSize ) { maxStackSize = stackSize; HK_SPU_DEBUG_PRINTF(("Maximum real stack size on spu: %d\n", stackSize)); } }
	// Place a marker just after the static data section
#	define HK_SPU_BSS_GUARD_INIT()		{ extern char* _end; *(unsigned int *)&_end = 0x4323e345; }
	// Check marker at end of static data section to see if the stack has grown into it
#	define HK_SPU_BSS_GUARD_CHECK()		{ extern char* _end; if ( *((unsigned int *)&_end) != 0x4323e345) { __asm ("stop"); } }
#else
#	define HK_SPU_INIT_STACK_SIZE_TRACE()
#	define HK_SPU_UPDATE_STACK_SIZE_TRACE()
#	define HK_SPU_OUTPUT_STACK_SIZE_TRACE()
#	define HK_SPU_BSS_GUARD_INIT()
#	define HK_SPU_BSS_GUARD_CHECK()
#endif

#endif // HKBASE_HKBASETYPES_H

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
