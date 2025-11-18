/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKBASE_HKDEBUGUTIL_CHECK_DETERMINISM_UTIL_H
#define HKBASE_HKDEBUGUTIL_CHECK_DETERMINISM_UTIL_H

// Uncomment the next line if you want to check the engine for determinism
//#define HK_ENABLE_DETERMINISM_CHECKS

#if defined (HK_ENABLE_DETERMINISM_CHECKS)
	#include <Common/Base/Thread/Thread/hkThreadLocalData.h>
	#include <Common/Base/System/Io/IStream/hkIStream.h>
	#include <Common/Base/System/Io/OStream/hkOStream.h>
#	define HK_ON_DETERMINISM_CHECKS_ENABLED(code) code
#else
#	define HK_ON_DETERMINISM_CHECKS_ENABLED(code)
#endif

extern struct hkCheckDeterminismUtil* g_checkDeterminismUtil;


class hkIstream;
class hkOstream;
class hkCriticalSection;




	/// This is a small helper class allowing to check the determinism of
	/// a system. Basically it works by running an application twice:
	/// First a binary logfile is created and the second time the system
	/// checks against this binary logfile.
struct hkCheckDeterminismUtil
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil );

			// <ag.todo.a> documentation here ..
			// Frame-unique ID
		struct Fuid
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil::Fuid );
			hkUint32 m_0, m_1, m_2, m_3;

			static Fuid& getZeroFuid();

			hkBool operator==(const Fuid& f)
			{
				return m_0 == f.m_0 && m_1 == f.m_1 && m_2 == f.m_2 && m_3 == f.m_3;
			}
			hkBool operator!=(const Fuid& f)
			{
				return m_0 != f.m_0 || m_1 != f.m_1 || m_2 != f.m_2 || m_3 != f.m_3;
			}
		};

		 hkCheckDeterminismUtil();
		~hkCheckDeterminismUtil();

		static hkCheckDeterminismUtil& getInstance() { HK_ASSERT2(0xad8655d2, g_checkDeterminismUtil, "Instance not created."); return *g_checkDeterminismUtil; }

		static void HK_CALL createInstance() { HK_ASSERT2(0xad8655d3, !g_checkDeterminismUtil, "Instance already created."); g_checkDeterminismUtil = new hkCheckDeterminismUtil(); }

		static void HK_CALL destroyInstance() { delete g_checkDeterminismUtil; g_checkDeterminismUtil = HK_NULL; }

			/// sets this utility to write mode. Call at startup of your test
			/// Make sure to call finish() at the end
		void startWriteMode(const char* filename = "hkDeterminismCheckfile.bin");

			/// sets this utility to check mode. Call at startup of your test
			/// Make sure to call finish() at the end
		void startCheckMode(const char* filename = "hkDeterminismCheckfile.bin");

		//
		// Registration functions used at the beginning and end of each hkpDynamicsJob.
		//

#	if defined (HK_ENABLE_DETERMINISM_CHECKS)
		/// check an array of objects from a single threaded section of your program
		template<typename TYPE>
		static HK_FORCE_INLINE void HK_CALL checkSt( TYPE* object, int numObjects = 1 ) { getInstance().checkImpl( object, sizeof( TYPE ) * numObjects ); }

		/// check a simple type object from a single threaded section of your program
		template<typename TYPE>
		static HK_FORCE_INLINE void HK_CALL checkSt( TYPE object ) { getInstance().checkImpl( &object, sizeof( TYPE )); }

		/// check an array of objects in a multi threaded environment
		template<typename TYPE>
		static HK_FORCE_INLINE void HK_CALL checkMt( TYPE* object, int numObjects = 1 ) { getInstance().checkImpl( object, sizeof(TYPE ) * numObjects ); }

		/// check a simple type object in a multi threaded environment
		template<typename TYPE>
		static HK_FORCE_INLINE void HK_CALL checkMt( TYPE object ) { getInstance().checkImpl( &object, sizeof(TYPE )); }

		static void HK_CALL initThread()							{ getInstance().initThreadImpl(); }
		static void HK_CALL quitThread()							{ getInstance().quitThreadImpl(); }
		static void HK_CALL workerThreadStartFrame(hkBool isPrimaryWorkerThread) { getInstance().workerThreadStartFrameImpl(isPrimaryWorkerThread); }
		static void HK_CALL workerThreadFinishFrame()				{ getInstance().workerThreadFinishFrameImpl(); }

		static void HK_CALL registerAndStartJob(Fuid& jobFuid)	{ getInstance().registerAndStartJobImpl(jobFuid); }
		static void HK_CALL finishJob(Fuid& jobFuid)				{ getInstance().finishJobImpl(jobFuid); }
		static void HK_CALL combineRegisteredJobs()					{ getInstance().combineRegisteredJobsImpl(); }
		static void HK_CALL extractRegisteredJobs()					{ getInstance().extractRegisteredJobsImpl(); }
		static void HK_CALL clearRegisteredJobs()					{ getInstance().clearRegisteredJobsImpl(); }
#	else
		template<typename TYPE> static HK_ALWAYS_INLINE void HK_CALL checkSt( TYPE* object, int numObjects = 1 ) { }
		template<typename TYPE> static HK_ALWAYS_INLINE void HK_CALL checkSt( TYPE object ) { }
		template<typename TYPE> static HK_ALWAYS_INLINE void HK_CALL checkMt( TYPE* object, int numObjects = 1 ) { }
		template<typename TYPE> static HK_ALWAYS_INLINE void HK_CALL checkMt( TYPE object ) { }

		static HK_ALWAYS_INLINE void HK_CALL initThread()							{  }
		static HK_ALWAYS_INLINE void HK_CALL quitThread()							{  }
		static HK_ALWAYS_INLINE void HK_CALL workerThreadStartFrame(hkBool isPrimaryWorkerThread){  }
		static HK_ALWAYS_INLINE void HK_CALL workerThreadFinishFrame()				{  }

		static HK_ALWAYS_INLINE void HK_CALL registerAndStartJob(Fuid& jobFuid)		{  }
		static HK_ALWAYS_INLINE void HK_CALL finishJob(Fuid& jobFuid)				{  }
		static HK_ALWAYS_INLINE void HK_CALL combineRegisteredJobs()				{  }
		static HK_ALWAYS_INLINE void HK_CALL extractRegisteredJobs()				{  }
		static HK_ALWAYS_INLINE void HK_CALL clearRegisteredJobs()					{  }
#	endif


		void initThreadImpl();
		void quitThreadImpl();
		void synchStreamsImpl();
		void workerThreadStartFrameImpl(hkBool isPrimaryWorkerThread);
		void workerThreadFinishFrameImpl();


		void  registerAndStartJobImpl(Fuid& jobFuid);
		void  finishJobImpl(Fuid& jobFuid);
		void  combineRegisteredJobsImpl();
		void  extractRegisteredJobsImpl();
		void  clearRegisteredJobsImpl();


		void checkImpl(const void* object, int size);

			/// Call this function at the end of your write/check run. This closes the open files
		void finish();

	public:

		enum Mode
		{
			MODE_IDLE,
			MODE_WRITE,
			MODE_COMPARE
		};
		Mode m_mode;

		hkBool m_inSingleThreadedCode;

		hkIstream* m_sharedInputStream;
		hkOstream* m_sharedOutputStream;

		hkIstream* m_primaryWorkerThreadInputStream;
		hkOstream* m_primaryWorkerThreadOutputStream;
		int m_primaryWorkerThreadJobInfoIdx;

		hkCriticalSection* m_shared;

		struct JobInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil::JobInfo );
			Fuid	  m_jobFuid;

				// This is the data. In multi threaded mode, the thread-local m_input/outputStreams connect to the corresponding hkArray.
				// This array is resizable, therefore it has to point to the data array.
			hkArray<char>* m_data; // for write

			hkBool		  m_isOpen;
		};

		hkArray<JobInfo> m_registeredJobs;

		hkBool m_writingStFromWorker;

};


#endif // HKBASE_HKDEBUGUTIL_CHECK_DETERMINISM_UTIL_H

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
