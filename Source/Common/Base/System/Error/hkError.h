/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKBASE_HKERROR_H
#define HKBASE_HKERROR_H


/// Class with static methods to provide hooks to error reporting functions
/// You can redirect all asserts, errors and warnings by setting the handlers
/// at run time. Asserts and Warnings are only compiled into debug builds.
/// Errors are compiled in all builds. See hkDefaultError.h for a sample implementation
/// of the handlers.
class hkError : public hkSingleton<hkError>
{
	public:

		enum Message
		{
			MESSAGE_REPORT,
			MESSAGE_WARNING,
			MESSAGE_ASSERT,
			MESSAGE_ERROR
		};

			/// displayMessage is used for asserts
		virtual int message(Message m, int id, const char* description, const char* file, int line) = 0;

			/// Enables/disables diagnostic by id.
		virtual void setEnabled( int id, hkBool enabled ) = 0;

			/// Enables/disables diagnostic by id.
		virtual hkBool isEnabled( int id ) = 0;

			/// Force all diagnostics to be enabled.
		virtual void enableAll() = 0;

			/// Begin a new report section
		virtual void sectionBegin(int id, const char* sectionName) {}

			/// End the current report section
		virtual void sectionEnd() {}
};

#if !defined(HK_PLATFORM_PS3SPU)
class hkErrStream : public hkOstream
{
	public:
		hkErrStream( void* buf, int bufSize );
};
typedef void (HK_CALL *hkErrorReportFunction)(const char* s, void* errorReportObject);
#endif

namespace hkCompileError
{
	template <bool b> struct COMPILE_ASSERTION_FAILURE;
	template <> struct COMPILE_ASSERTION_FAILURE<true>{ };
}

// compile time asserts and errors are always enabled
// Note: Use this only in c++ files, not header files.
#define HK_COMPILE_TIME_ASSERT(a) enum { HK_PREPROCESSOR_JOIN_TOKEN(compile_time_assert_, __LINE__) \
										= sizeof(hkCompileError::COMPILE_ASSERTION_FAILURE<bool(a)>) }

#define HK_REPORT_SECTION_BEGIN(id, name)	hkError::getInstance().sectionBegin(id, name);

#define HK_REPORT_SECTION_END()				hkError::getInstance().sectionEnd();



// asserts and warnings may be compiled out
#if !defined (HK_PLATFORM_PS3SPU)

#	define HK_WARN_ALWAYS(id, TEXT)		HK_MULTILINE_MACRO_BEGIN																						\
										char assertBuf[512];																							\
										hkErrStream ostr(assertBuf, sizeof(assertBuf));																	\
										ostr << TEXT;																									\
										hkError::getInstance().message(hkError::MESSAGE_WARNING, id, assertBuf, __FILE__, __LINE__);					\
										HK_MULTILINE_MACRO_END

#	define HK_ERROR(id, TEXT)			HK_MULTILINE_MACRO_BEGIN																						\
										char assertBuf[512];																							\
										hkErrStream ostr(assertBuf,sizeof(assertBuf));																	\
										ostr << TEXT;																									\
										hkError::getInstance().message(hkError::MESSAGE_ERROR, id, assertBuf, __FILE__, __LINE__);						\
										HK_MULTILINE_MACRO_END

#	define HK_REPORT(TEXT)				HK_MULTILINE_MACRO_BEGIN																						\
										char reportBuf[512];																							\
										hkErrStream ostr(reportBuf,sizeof(reportBuf));																	\
										ostr << TEXT;																									\
										hkError::getInstance().message(hkError::MESSAGE_REPORT, -1, reportBuf, __FILE__, __LINE__);						\
										HK_MULTILINE_MACRO_END

#	if defined HK_DEBUG // NOSPU + DEBUG

#		define HK_ASSERT(id, a)			HK_MULTILINE_MACRO_BEGIN 																						\
										if ( !(a) )																										\
										{																												\
											if( hkError::getInstance().message(hkError::MESSAGE_ASSERT, id, #a,__FILE__,__LINE__) )						\
											{																											\
												HK_BREAKPOINT(0);																						\
											}																											\
										}																												\
										HK_MULTILINE_MACRO_END

#		define HK_ASSERT2(id, a, TEXT)	HK_MULTILINE_MACRO_BEGIN 																						\
										if ( !(a) )																										\
										{																												\
											char assertBuf[512];																						\
											hkErrStream ostr(assertBuf, sizeof(assertBuf));																\
											ostr << #a << "\n";																							\
											ostr << TEXT;																								\
											if( hkError::getInstance().message(hkError::MESSAGE_ASSERT, id, assertBuf,__FILE__, __LINE__) )				\
											{																											\
												HK_BREAKPOINT(0);																						\
											}																											\
										}																												\
										HK_MULTILINE_MACRO_END

#		define HK_WARN(id, TEXT)		HK_WARN_ALWAYS (id, TEXT)

#		define HK_WARN_ONCE(id, TEXT)	HK_MULTILINE_MACRO_BEGIN																						\
										if ( hkError::getInstance().isEnabled(id) )																									\
										{																												\
											char assertBuf[512];																						\
											hkErrStream ostr( assertBuf, sizeof(assertBuf) );															\
											ostr << TEXT;																								\
											hkError::getInstance().getInstance().message(hkError::MESSAGE_WARNING, id, assertBuf, __FILE__, __LINE__);	\
											hkError::getInstance().setEnabled(id, false); 																								\
										}																												\
										HK_MULTILINE_MACRO_END


#		define HK_ON_DEBUG(CODE)		CODE

#	else	// NOSPU + RELEASE

#		define HK_WARN(id, a)				//nothing
#		define HK_WARN_ONCE(id, a)			//nothing
#		define HK_ASSERT(id, a)				//nothing 
#		define HK_ASSERT2(id, a, TEXT)		//nothing 
#		define HK_ON_DEBUG(CODE)
#	endif	

#else // defined (HK_PLATFORM_PS3SPU)

#	include <sys/spu_event.h>
#	define HK_ERROR_FORWARD(what,id,text) sys_spu_thread_send_event( 31+what, hkUlong(0), id )

#	define HK_WARN_ALWAYS(id, TEXT)	HK_ERROR_FORWARD( hkError::MESSAGE_WARNING, id, hkUlong(0) )

#	define HK_ERROR(id, TEXT)		HK_MULTILINE_MACRO_BEGIN \
										HK_ERROR_FORWARD( hkError::MESSAGE_ERROR, id, hkUlong(0) ); \
										HK_BREAKPOINT(id);				\
										HK_MULTILINE_MACRO_END

#	define HK_REPORT(TEXT)			HK_ERROR_FORWARD( hkError::MESSAGE_REPORT, 0, hkUlong(TEXT) )

#	if defined (HK_DEBUG) // SPU+DEBUG

#		define HK_ASSERT(id, a)			HK_MULTILINE_MACRO_BEGIN 			\
										if ( !(a) )							\
										{									\
											HK_ERROR_FORWARD( hkError::MESSAGE_ASSERT, id, hkUlong(0) ); \
											HK_BREAKPOINT(id);				\
										}									\
										HK_MULTILINE_MACRO_END

#		define HK_ASSERT2(id, a, TEXT)	HK_ASSERT(id,a)

#		define HK_WARN(id, TEXT)		HK_ERROR_FORWARD( hkError::MESSAGE_WARNING, id, hkUlong(0) )

#		define HK_WARN_ONCE(id, TEXT)	HK_MULTILINE_MACRO_BEGIN			\
										static hkBool shown = false;		\
										if ( !shown )						\
										{									\
											HK_WARN(id,TEXT);				\
										}									\
										HK_MULTILINE_MACRO_END

#		define HK_ON_DEBUG(CODE)		CODE

#	else // SPU+RELEASE

#		define HK_WARN(id, a)				//nothing
#		define HK_WARN_ONCE(id, a)			//nothing
#		define HK_ASSERT(id, a)				//nothing 
#		define HK_ASSERT2(id, a, TEXT)		//nothing 
#		define HK_ON_DEBUG(CODE)
#   endif 

#endif

#define HK_CHECK_ALIGN16(ADDR) HK_ASSERT(0xff00ff00, (hkUlong(ADDR) & 0xf) == 0 )

#endif // HKBASE_HKERROR_H


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
