/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_BASE_SPU_UTIL_H
#define HK_BASE_SPU_UTIL_H

#if defined (HK_PLATFORM_PS3)
	#include <sys/spu_thread.h>
	#include <cell/spurs.h>
	#define HK_CELL_SPURS CellSpurs
#else
	typedef hkUint32 sys_event_queue_t;
	#define HK_CELL_SPURS void
#endif


namespace hkSpuSimulator
{
	class Server;
}

struct hkSpuTaskParams
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuTaskParams );

	void* m_param0;
	void* m_param1;
	void* m_param2;
	void* m_param3;
};

struct hkSpuTaskSetParams
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuTaskSetParams );

	void* m_param0;
	void* m_param1;
};


enum hkSpuSimulatorTasks
{
	HK_TASK_INVALID = 0,
	HK_TASK_PHYSICS_SIMULATE,
	HK_THREAD_PHYSICS_SIMULATE,
	HK_TASK_COLLISION_QUERY,
	HK_TASK_ANIMATION
};

struct hkSpuMemoryBin;

	/// Wrapper class for running spus
class hkSpuUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_UTILITIES, hkSpuUtil);

			///
		hkSpuUtil();

			// This calls quitSpursTaskset or quitSpuThreadGroup as appropriate
		~hkSpuUtil();

		//
		// Simple Spurs wrapper
		//

			/// You must initialize a CellSpurs instance before calling this function.
			/// Use this function to initialize the Havok spurs taskset.
		void initSpursTaskset( int numSpus, hkSpuTaskSetParams& params, HK_CELL_SPURS* spurs );

			/// You must call initSpursTaskset before calling this function.
			/// Use this function to quit the Havok spurs taskset.
		void quitSpursTaskset( );


			/// Start SPURS task, given params and an elf
		void startSpursTask( hkSpuTaskParams& params, void* elf = HK_NULL );

			/// Set a default task, with parameters, and number of tasks to start, for callbacks from the multithread util
			/// This sets the number of default tasks to the size of the spuParams array
		void setDefaultSpursTaskAndParams( hkArray<hkSpuTaskParams>& spuParams,  void* elf );

			/// Start the set of default tasks, for callbacks from the multithread util
		void startDefaultSpursTasks( );

			/// Start the spurs tasks with the supplied .elf and parameter set.
			/// If spuParams is set to HK_NULL, m_defaultParams will be used instead. 
		void startSpursTasks( hkArray<hkSpuTaskParams>* spuParams, void* elfAddress );

			/// Set the number of spurs tasks to start during the next 'start(Default)SpursTasks()'.
		void setNumActiveSpursTasks( int num );

			/// Returns the number of active spurs tasks.
		int getNumActiveSpursTasks();


		//
		// Simple Spu thread wrapper
		//
			
			/// Init thread group with number of required spus
		void initSpuThreadGroup( int numSpus );

			/// Start a thread.  This must be called as many times as the numSpus parameter passed into initSpuThreadGroup.
			/// The final time this is called, the thread group is actually started.
		void startSpuThread( hkSpuTaskParams& params, char* spuProg );

			/// Quit the thread group
		void quitSpuThreadGroup();

			///
		void* getMemoryBins();

			///
		hkUint32 getHelperEventQueue();

	public:

#if defined (HK_PLATFORM_PS3)

		// SPURS
		CellSpurs*					m_spurs;
		CellSpursTaskset*			m_taskset;

		hkBool						m_spursInitialized;

		// SPU threads
		sys_spu_thread_group_t		m_groupId;				// SPU thread group ID 
		sys_spu_image				m_spuThreadImg;
		sys_spu_thread_t			m_spuThreadIds[6];
		int							m_spuThreadCounter;
		int							m_numSpuThreads;
		hkMemory*					m_memory;
		sys_event_queue_t			m_queueToHelperThread;
		sys_ppu_thread_t			m_helperThreadId;
		hkSpuMemoryBin*				m_bins;

#elif defined (HK_SIMULATE_SPU_DMA_ON_CPU)

		hkSpuSimulator::Server*		m_spuSimulatorServer;

#endif

		hkArray<hkSpuTaskParams>	m_defaultParams;
		int							m_numActiveSpursTasks;
		void*						m_defaultElf;
};



#endif // HK_BASE_SPU_UTIL_H

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
