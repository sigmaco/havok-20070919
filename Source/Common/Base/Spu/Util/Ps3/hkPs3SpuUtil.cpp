/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Util/hkSpuUtil.h>
#include <Common/Base/Spu/Printf/hkSpuPrintfUtil.h>
#include <Common/Base/Memory/Memory/hkMemory.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/PlattformUtils/Spu/hkSpuMemoryInternal.h>
#include <Common/Base/Monitor/Spu/hkSpuMonitorCache.h>
#include <Common/Base/Spu/PortManager/hkSpuPortManager.h>

//#include <stdio.h>
//#define PRINTF(A) printf A
#define PRINTF(A)
#define HK_ENABLED_SPU_DEBUG_PRINTFS
#define MAX_NUM_SPU_THREADS 6

#include <ppu_intrinsics.h>
#include <cell/spurs.h>
#include <cell/atomic.h>
#include <cell/spurs/lv2_event_queue.h>
#include <sys/event.h>
#include <sys/timer.h>
#include <sys/spu_initialize.h>
#include <sys/spu_thread.h>
#include <sys/ppu_thread.h>
#include <sys/spu_initialize.h>
#include <sys/spu_thread.h>
#include <sys/spu_thread_group.h>
#include <sys/spu_utility.h>
#include <sys/spu_image.h>

/* for spu_printf */
#include <stdio.h>		
#include <spu_printf.h>

#define HELPER_EVENT_PORT_TERMINATE 0xdead78
#define	HELPER_STACK_SIZE (1024 * 64)
#define HELPER_THREAD_PRIORITY 80

#define	SPURS_THREAD_GROUP_PRIORITY 250
#define SPURS_HANDLER_THREAD_PRIORITY 1

#define INVALID_GROUP_ID 0xffffffff
#define THREAD_GROUP_PRIORITY 100

static void memoryService( hkMemory* memory, hkSpuMemoryBin* bin, int blockSize )
{
	const hkUint32 LOCK_BIT = 1<<31; // Bit to lock the secondary area
	const hkUint32 FINISHED_MASK = ~(1<<30); // All done, I am going back to sleep

	while(1)
	{
		hkUint32 control = __lwarx(bin);
		hkUint32 available = control & 0x7fff;
		hkBool32 locked = control & LOCK_BIT;
		//PRINTF(("PPU iter a(%u) l(%u)\n", available, locked);

		if( locked )
		{
			continue;
		}
		if( available == 0 ) // empty
		{
			control ^= LOCK_BIT;
			if( __stwcx(bin, control) ) // lock overflow
			{
				//PRINTF(("PPU locked 0\n"));
				memory->allocateChunkBatch(bin->overflow[0], 8, blockSize ); //XXX constRowToSize
				__sync();
				do {
					control = __lwarx(bin) & FINISHED_MASK;
					control ^= (LOCK_BIT | 0x3);
				} while( __stwcx(bin, control) == 0 ); // release lock&bits
				PRINTF(("HELP get %p %p %p %p %p %p %p %p\n",
					bin->overflow[0][0], bin->overflow[0][1], bin->overflow[0][2], bin->overflow[0][3],
					bin->overflow[1][0], bin->overflow[1][1], bin->overflow[1][2], bin->overflow[1][3] ));
				break;
			}
			else
			{
				PRINTF(("PPU failed to lock 0\n"));
			}
		}
		else if( available == 0x7fff ) // full
		{
			control ^= LOCK_BIT;
			if( __stwcx(bin, control) ) // lock overflow
			{
				PRINTF(("PPU lock 1\n"));
				memory->deallocateChunkBatch(bin->overflow[0], 8, blockSize );
				__sync();
				do {
					control = __lwarx(bin) & FINISHED_MASK;
					control ^= (LOCK_BIT | 0x3);
				} while( __stwcx(bin, control) == 0 ); // release lock&bits
				PRINTF(("HELP put %p %p %p %p %p %p %p %p\n",
					bin->overflow[0][0], bin->overflow[0][1], bin->overflow[0][2], bin->overflow[0][3],
					bin->overflow[1][0], bin->overflow[1][1], bin->overflow[1][2], bin->overflow[1][3] ));
				break;
			}
			PRINTF(("PPU failed to lock 1\n"));
		}
		else if( __stwcx(bin, control & FINISHED_MASK) ) // woke up but no work to do. unblock waiting spu
		{
			PRINTF(("PPU no work?\n"));
			break; // neither full nor empty
		}
	}
}

static void hkSpuHelperThreadFunc(uint64_t threadArg)
{
	hkSpuUtil* spuUtil = reinterpret_cast<hkSpuUtil*>( hkUlong(threadArg) );
	hkThreadMemory threadMemory( spuUtil->m_memory, 0 );
	hkBaseSystem::initThread(&threadMemory);

	HK_COMPILE_TIME_ASSERT( sizeof(sys_event_queue_t) == sizeof(hkUlong) );

	while( 1 )
	{
		PRINTF(("PPU thread sleep\n"));
		sys_event_t event;
		HK_ON_DEBUG(int ret = )sys_event_queue_receive(spuUtil->m_queueToHelperThread, &event, SYS_NO_TIMEOUT);
		HK_ASSERT2(0, ret == CELL_OK, "sys_event_queue_receive failed: " << ret);
		PRINTF(("PPU thread wakeup\n"));
		hkUint32 eventPort = hkUint32(event.data2 >> 32);

		if( event.source == SYS_SPU_THREAD_EVENT_USER_KEY )
		{
			switch( hkSpuHelperThread::HelpType(eventPort) )
			{
				case hkSpuHelperThread::HELP_TYPE_MEMORY_SERVICE:
				{
					int rowIndex = int(event.data2);
					int blockSize = int(event.data3);
					hkSpuMemoryBin	* bin = &spuUtil->m_bins[rowIndex];
					memoryService(spuUtil->m_memory, bin, blockSize);
					break;
				}
				case hkSpuHelperThread::HELP_TYPE_PRINTF:
				{
					sys_spu_thread_t spu = event.data1;
					int sret = spu_thread_printf(spu, event.data3);
					int mret = sys_spu_thread_write_spu_mb(spu, sret);
					if(mret != CELL_OK)
					{
						printf ("sys_spu_thread_write_spu_mb failed (%d)\n", mret);
						sys_ppu_thread_exit(-1);
					}
					break;
				}
				case hkSpuHelperThread::HELP_TYPE_FORWARD_ASSERT:
				case hkSpuHelperThread::HELP_TYPE_FORWARD_ERROR:
				case hkSpuHelperThread::HELP_TYPE_FORWARD_WARNING:
				case hkSpuHelperThread::HELP_TYPE_FORWARD_REPORT:
				{
						const char* what[] = { "Assert", "Error", "Warning", "Report" };
						PRINTF(("SPU(id=0x%x) %s 0x%x\n", unsigned(event.data1), what[eventPort-hkSpuHelperThread::HELP_TYPE_FORWARD_ASSERT], unsigned(event.data3)));
				
					break;
				}
				default:
				{
					HK_BREAKPOINT(0); // Unknown event
				}
			}
		}
		else if( event.source == HELPER_EVENT_PORT_TERMINATE )
		{
			hkBaseSystem::clearThreadResources();
			sys_ppu_thread_exit(0);
		}
		else
		{
			HK_ASSERT(0,0);
		}
	}
}

static hkBool32 s_binsInUse;
static HK_ALIGN128( hkSpuMemoryBin s_bins[hkThreadMemory::MEMORY_MAX_ALL_ROW] );







/* Lv2 OS headers */
#include <sys/event.h>
#include <sys/spu_thread.h>
#include <sys/ppu_thread.h>
#include <spu_printf.h>

#include <cell/spurs.h>

#define	TERMINATING_PORT_NAME	0xFEE1DEAD

#define	STACK_SIZE	(1024 * 64)


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	typedef struct SampleUtilSpursPrintfService
	{
		CellSpurs*          spurs;
		sys_event_queue_t	equeue;
		sys_ppu_thread_t	spu_printf_handler;
		sys_event_port_t	terminating_port;
	} SampleUtilSpursPrintfService;

	int sampleSpursUtilSpuPrintfServiceInitialize(SampleUtilSpursPrintfService *service, CellSpurs*, int prio);
	int sampleSpursUtilSpuPrintfServiceFinalize(SampleUtilSpursPrintfService *service);


#ifdef __cplusplus
}
#endif /* __cplusplus */

static void
spu_printf_handler_entry(uint64_t arg)
{
	SampleUtilSpursPrintfService *service = (SampleUtilSpursPrintfService *)(uintptr_t)arg;
	int	ret;
	for (;;) {
		sys_spu_thread_t	spu;
		sys_event_t	event;

		ret = sys_event_queue_receive(service->equeue, &event, 0);

		if (event.source == TERMINATING_PORT_NAME) {
			printf ("Finalizing the spu printf handler\n");
			sys_ppu_thread_exit(0);
		}
		spu = event.data1;
		int sret = spu_thread_printf(spu, event.data3);
		ret = sys_spu_thread_write_spu_mb(spu, sret);
		if (ret) {
			printf ("sys_spu_thread_write_spu_mb failed (%d)\n", ret);
			sys_ppu_thread_exit(-1);
		}
	}
	/* never reach here */
	sys_ppu_thread_exit(0);
}

int
sampleSpursUtilSpuPrintfServiceInitialize(SampleUtilSpursPrintfService *service, CellSpurs* spurs, int prio)
{
	int	ret;
	service->spurs = spurs;

	/* create event_queue for printf */
	sys_event_queue_attribute_t	attr;
	sys_event_queue_attribute_initialize (attr);

	/* queue depth must be equal or greater than max_spu_threads */
	ret = sys_event_queue_create (&service->equeue, &attr, SYS_EVENT_QUEUE_LOCAL, 8);
	if (ret) {
		printf ("sys_event_queue_create failed (%d)\n", ret);
		return ret;
	}

	/* 		create ppu_thread for printf handling */
	ret = sys_ppu_thread_create (&service->spu_printf_handler, spu_printf_handler_entry,
		(uint64_t)(uintptr_t)service, prio, STACK_SIZE, SYS_PPU_THREAD_CREATE_JOINABLE, 
		"spu_printf_handler");
	if (ret) {
		printf ("sys_ppu_thread_create failed (%d)\n", ret);
		return ret;
	}

	/*
	* Create the terminating port. This port is used only in 
	* spu_printf_service_finalize().
	*/
	ret = sys_event_port_create(&service->terminating_port, SYS_EVENT_PORT_LOCAL, TERMINATING_PORT_NAME);
	if (ret) {
		printf ("spu_printf_server_initialize: sys_event_port_create failed %d\n", ret);
		return ret;
	}

	ret = sys_event_port_connect_local(service->terminating_port, service->equeue);
	if (ret) {
		printf ("spu_printf_server_initialize: sys_event_connect failed %d\n", ret);
		return ret;
	}

	/* connect to SPURS */
	uint8_t	port = HK_PRINTF_PORT;
	ret = cellSpursAttachLv2EventQueue (service->spurs, service->equeue, &port, 0);
	if (ret) {
		printf ("spu_printf_server_initialize: cellSpursAttachLv2EventQueue failed %d\n", ret);
		return ret;
	}
	return CELL_OK;
}

int
sampleSpursUtilSpuPrintfServiceFinalize(SampleUtilSpursPrintfService *service)
{
	int ret;
	uint64_t	exit_code;

	/*
	*
	*/
	ret = cellSpursDetachLv2EventQueue (service->spurs, HK_PRINTF_PORT);
	if (ret) {
		printf ("cellSpursDetachLv2EventQueue failed %d\n", ret);
		return ret;
	}

	/*
	* send event for temination.
	*/
	ret = sys_event_port_send (service->terminating_port, 0, 0, 0);
	if (ret) {
		printf ("sys_event_port_send failed %d\n", ret);
		return ret;
	}
	/*	wait for termination of the handler thread */
	ret = sys_ppu_thread_join (service->spu_printf_handler, &exit_code);
	if (ret) {
		printf("sys_ppu_thread_join failed %d\n", ret);
		return ret;
	}

	/* Disconnect and destroy the terminating port */
	ret = sys_event_port_disconnect(service->terminating_port);
	if (ret) {
		printf("sys_event_disconnect failed %d\n", ret);
		return ret;
	}
	ret = sys_event_port_destroy(service->terminating_port);
	if (ret) {
		printf("sys_event_port_destroy failed %d\n", ret);
		return ret;
	}	

	/*	clean event_queue for spu_printf */
	ret = sys_event_queue_destroy (service->equeue, 0);
	if (ret) {
		printf("sys_event_queue_destroy failed %d\n", ret);
		return ret;
	}

	return CELL_OK;
}

int sampleSpursUtilGetSecondaryPpuThreadPriority(int *prio)
{
	int ret;
	sys_ppu_thread_t my_ppu_thread_id;
	ret = sys_ppu_thread_get_id(&my_ppu_thread_id);
	if(ret){ 
		return ret; 
	}
	ret = sys_ppu_thread_get_priority(my_ppu_thread_id, prio);
	if(ret){ 
		return ret; 
	}
	*prio = *prio - 1;
	return 0;
}


hkSpuUtil::hkSpuUtil()
{
	// SPURS
	m_spursInitialized = false;

	// Thread groups
	m_groupId = INVALID_GROUP_ID;
	m_spuThreadCounter = 0;
	m_numSpuThreads = -1;

	m_numActiveSpursTasks = -1;

	//hkString::memSet(m_bins, 0, sizeof(m_bins));
	// maybe prefill some bins?
	m_memory = &hkMemory::getInstance();
	m_bins = s_bins;
	HK_ASSERT(0, s_binsInUse == false);
	s_binsInUse = true;

	// create event queue
	{
		sys_ppu_thread_t event_handle_thread;
		sys_event_queue_attribute_t queue_attr = { SYS_SYNC_FIFO, SYS_PPU_QUEUE, "memserv" };
		int ret = sys_event_queue_create(&m_queueToHelperThread, &queue_attr, SYS_EVENT_QUEUE_LOCAL, 10);
		if (ret)
		{
			HK_ERROR( 0xc37d7b1f, "sys_event_queue_create failed :" << ret);
		}
	}

	// create ppu helper thread
	{
		int ret = sys_ppu_thread_create(&m_helperThreadId, hkSpuHelperThreadFunc,
			hkUlong(this), HELPER_THREAD_PRIORITY, HELPER_STACK_SIZE,
			SYS_PPU_THREAD_CREATE_JOINABLE, "hkSpuUtil Helper");
		if (ret)
		{
			HK_ERROR( 0xc37d7b21, "sys_ppu_thread_create failed :" << ret);
		}
	}
}

hkSpuUtil::~hkSpuUtil()
{
	if ( m_spursInitialized )
	{
		quitSpursTaskset();
	}
	else if (m_groupId != INVALID_GROUP_ID )
	{
		quitSpuThreadGroup();
	}

	{
		// terminate helper thread, destroy the queue
		sys_event_port_t terminate_port;
		uint64_t event_handle_status;
		HK_ON_DEBUG(int ret);
		HK_ON_DEBUG(ret = )sys_event_port_create(&terminate_port, SYS_EVENT_PORT_LOCAL, HELPER_EVENT_PORT_TERMINATE);
		HK_ASSERT(0x11, ret == CELL_OK);
		HK_ON_DEBUG(ret = )sys_event_port_connect_local(terminate_port, m_queueToHelperThread );
		HK_ASSERT(0x11, ret == CELL_OK);
		HK_ON_DEBUG(ret = )sys_event_port_send(terminate_port, 0, 0, 0);
		HK_ASSERT(0x11, ret == CELL_OK);
		HK_ON_DEBUG(ret = )sys_event_port_disconnect(terminate_port);
		HK_ASSERT(0x11, ret == CELL_OK);	
		HK_ON_DEBUG(ret = )sys_event_port_destroy(terminate_port);
		HK_ASSERT(0x11, ret == CELL_OK);
		HK_ON_DEBUG(ret = )sys_ppu_thread_join(m_helperThreadId, &event_handle_status);
		HK_ASSERT(0x11, ret == CELL_OK);

		HK_ON_DEBUG(ret = )sys_event_queue_destroy(m_queueToHelperThread, 0);
		HK_ASSERT(0x11, ret == CELL_OK);

		for( int memRow = 0; memRow < hkThreadMemory::MEMORY_MAX_ALL_ROW; ++memRow )
		{
			hkSpuMemoryBin& bin = m_bins[memRow];
			if( bin.main.control )
			{
				int blockSize = hkThreadMemory::getInstance().rowToSize(memRow);
				void* collected[(7+8)*4];
				int numCollected = 0;
				// swap the control word so that 1<<X corresponds to pointers[X]
				HK_ASSERT(0, (bin.main.control & ~0x7fff) == 0 );
				int control = bin.main.control;
				control = (control>>7) | ((control&0xff)<<8);
				hkSpuMemoryBin::quad* qbase = reinterpret_cast<hkSpuMemoryBin::quad*>(&bin.main);

				for( int i = 1; i < 16; ++i )
				{
					if( control & (1 << i) )
					{
						hkSpuMemoryBin::quad& q = qbase[i];	
						for( int n = 0; n < 4 && q[n] != HK_NULL	; ++n )
						{
							PRINTF(("HELP clean %p\n", q[n]));
							collected[numCollected++] = q[n];
						}
					}
				}
				bin.main.control = 0;
				m_memory->deallocateChunkBatch(collected, numCollected, blockSize );
			}
		}
	}
	s_binsInUse = false;
}

static SampleUtilSpursPrintfService printfService;
void hkSpuUtil::initSpursTaskset( int numSpus, hkSpuTaskSetParams& params, CellSpurs* spurs )
{
	HK_ASSERT2( 0, m_groupId == INVALID_GROUP_ID, "You cannot initialize spurs if you have initialized thread groups");
	HK_ASSERT( 0, numSpus <= MAX_NUM_SPU_THREADS );
	HK_ASSERT( 0, !m_spursInitialized );

	m_spurs = spurs;
	m_spursInitialized = true;

	m_taskset = (CellSpursTaskset*)hkAlignedAllocate<char> ( CELL_SPURS_TASKSET_ALIGN, CELL_SPURS_TASKSET_SIZE , HK_MEMORY_CLASS_DEMO );
	uint8_t prios[8] =  { 1, 1, 1, 1, 1, 1, 1, 1 };

	uint64_t taskSetParams = (hkUint32)params.m_param0;
	taskSetParams = taskSetParams << 32;
	taskSetParams += (hkUint32)params.m_param1;

	int ret = cellSpursCreateTaskset( m_spurs, m_taskset, taskSetParams, prios, numSpus );

	if (ret)
	{
		HK_ERROR(0x73e432a3, "cellSpursCreateTaskset failed :" << ret);
	}

	// Attach the builtin ones - memory, error and printf
	for( int i = hkSpuHelperThread::HELP_TYPE_FIRST; i < hkSpuHelperThread::HELP_TYPE_LAST; ++i )
	{
		hkUint8 port = i;
		ret = cellSpursAttachLv2EventQueue (spurs, m_queueToHelperThread, &port, false);
		if (ret)
		{
			HK_ERROR(0xc37d7b1f, "cellSpursAttachLv2EventQueue failed: " << ret << ", hkSpuUtil unable to attach to (hard-coded) port " << int(port) );
		}
		else
		{
			HK_ON_DEBUG(HK_REPORT("cellSpursAttachLv2EventQueue succeeded.  Havok is attached to event queue port " << int(port) << ". Other assignments to this port with fail until Havok is detached from this port." ));
		}
	}

	// Attach the auto ones - hkSemaphoreBusyWait
	for( hkSpuPortManager* man = hkSpuPortManager::getFirst(); man != HK_NULL; man = man->getNext() )
	{
		hkUint8 port = man->getSpuPort();
		ret = cellSpursAttachLv2EventQueue (spurs, man->getEventQueue(), &port, false);
		if (ret)
		{
			HK_ERROR(0xc37d7b1f, "cellSpursAttachLv2EventQueue failed :" << ret << ", hkSpuUtil unable to attach to (auto) port " << int(port));
		}
		else
		{
			HK_ON_DEBUG(HK_REPORT("cellSpursAttachLv2EventQueue succeeded.  Havok is attached to event queue port " << int(port) << ". Other assignments to this port with fail until Havok is detached from this port." ));
		}
	}




	int ppu_thr_prio;
	ret = sampleSpursUtilGetSecondaryPpuThreadPriority(&ppu_thr_prio);
	HK_ASSERT2( 0xc37d7b1f, ret == CELL_OK, "sampleSpursUtilGetSecondaryPpuThreadPriority failed: " << ret);
	ret = sampleSpursUtilSpuPrintfServiceInitialize(&printfService, spurs, ppu_thr_prio); 
	HK_ASSERT2( 0xc37d7b1f, ret == CELL_OK, "sampleSpursUtilSpuPrintfServiceInitialize failed: " << ret);

	hkSpuPortManager::setSpuStarted( true );
}

void hkSpuUtil::startSpursTask( hkSpuTaskParams& params, void* elf )
{
	HK_ASSERT2(0x9545ff34, m_spursInitialized, "You must call startSpurs() before calling startTask()" );
	// create task (without context)
	CellSpursTaskId tid;
	int ret = cellSpursCreateTask(m_taskset, &tid, elf,	(void*)0, 0, (CellSpursTaskLsPattern*)0, (CellSpursTaskArgument*)(&params) );
	if (ret)
	{
		HK_ERROR(0x73e432a5, "cellSpursCreateTask failed :" << ret);
	}
}

void hkSpuUtil::quitSpursTaskset( )
{
	HK_ASSERT2(0x9545fe34, m_spursInitialized, "You must call initSpurs() before calling quitSpurs()" );

	// Shutdown taskset
	int ret = cellSpursShutdownTaskset( m_taskset );
	if (ret)
	{
		HK_ERROR(0x73e432b4, "cellSpursShutdownTaskset failed :" << ret);
	}

	// Join taskset
	ret = cellSpursJoinTaskset( m_taskset );
	if (ret)
	{
		HK_ERROR(0x73e432b2, "cellSpursJoinTaskset failed :" << ret);
	}

	for( hkSpuPortManager* man = hkSpuPortManager::getFirst(); man != HK_NULL; man = man->getNext() )
	{
		ret = cellSpursDetachLv2EventQueue( m_spurs, man->getSpuPort() );
		if (ret)
		{
			HK_ERROR(0xc37d7b1f, "cellSpursDetachLv2EventQueue failed: " << ret << ", hkSpuUtil unable to detach from port " << int(man->getSpuPort()) );
		}
	}
	for( int i = hkSpuHelperThread::HELP_TYPE_FIRST; i < hkSpuHelperThread::HELP_TYPE_LAST; ++i )
	{
		ret = cellSpursDetachLv2EventQueue( m_spurs, hkUint32(i) );
		if (ret)
		{
			HK_ERROR(0xc37d7b1f, "cellSpursDetachLv2EventQueue failed: " << ret << ", hkSpuUtil unable to detach from port " << i);
		}
	}
	hkSpuPortManager::setSpuStarted( false );
	m_spursInitialized = false;

	ret = sampleSpursUtilSpuPrintfServiceFinalize(&printfService);
	HK_ASSERT2( 0xc37d7b1f, ret == CELL_OK, "sampleSpursUtilSpuPrintfServiceFinalize failed: " << ret);

	hkAlignedDeallocate<char>( (char*)m_taskset );
}

//
// SPU threads
//


void hkSpuUtil::initSpuThreadGroup( int numSpus )
{
	HK_ASSERT(0, m_groupId == INVALID_GROUP_ID );
	HK_ASSERT(0, !m_spursInitialized );
	HK_ASSERT(0, numSpus <= MAX_NUM_SPU_THREADS);

	m_numSpuThreads	= numSpus;

	//
	// Create an SPU thread with id m_groupId
	// 
	{
		const char* group_name = "HavokGroup";
		sys_spu_thread_group_attribute_t group_attr;	// SPU thread m_groupId attribute

		group_attr.name = group_name;
		group_attr.nsize = hkString::strLen(group_attr.name) + 1;
		group_attr.type = SYS_SPU_THREAD_GROUP_TYPE_NORMAL;

		int ret = sys_spu_thread_group_create(&m_groupId, numSpus, THREAD_GROUP_PRIORITY, &group_attr);
		HK_ASSERT2(0x10294fa6,ret == CELL_OK, "sys_spu_thread_group_create failed:" << ret );
	}
}

void hkSpuUtil::startSpuThread( hkSpuTaskParams& params, char* spuProg )
{
	HK_ASSERT(0, m_groupId != INVALID_GROUP_ID );
	HK_ASSERT(0, m_spuThreadCounter < m_numSpuThreads );

	{
		int ret = sys_spu_image_open(&m_spuThreadImg, spuProg);
		HK_ASSERT2(0x102346fa, ret == CELL_OK, "sys_spu_thread_elf_loader failed:" << ret );
	}

	char threadName[100];
	hkString::sprintf( threadName, "SPU Thread %d", m_spuThreadCounter );


	sys_spu_thread_attribute_t threadAttr;	// SPU thread attribute 

	threadAttr.name = threadName;
	threadAttr.nsize = hkString::strLen(threadName) + 1;
	threadAttr.option = SYS_SPU_THREAD_OPTION_NONE;

	sys_spu_thread_argument_t threadParams;


	threadParams.arg1 = SYS_SPU_THREAD_ARGUMENT_LET_64((uint64_t)params.m_param0 );
	threadParams.arg2 = SYS_SPU_THREAD_ARGUMENT_LET_64((uint64_t)params.m_param1 );
	threadParams.arg3 = SYS_SPU_THREAD_ARGUMENT_LET_64((uint64_t)params.m_param2 );
	threadParams.arg4 = SYS_SPU_THREAD_ARGUMENT_LET_64((uint64_t)params.m_param3 );

	sys_spu_thread_t thread;

	{
		HK_ON_DEBUG( int ret = )sys_spu_thread_initialize(&thread, m_groupId, m_spuThreadCounter, &m_spuThreadImg, &threadAttr, &threadParams);
		HK_ASSERT2(0x675857ed,  ret == CELL_OK, "sys_spu_thread_initialize failed: " << ret);
		// Attach the builtin ones - memory, error and printf
		for( int i = hkSpuHelperThread::HELP_TYPE_FIRST; i < hkSpuHelperThread::HELP_TYPE_LAST; ++i )
		{
			HK_ON_DEBUG(ret =) sys_spu_thread_connect_event(thread, m_queueToHelperThread, SYS_SPU_THREAD_EVENT_USER, i);
			HK_ASSERT2(0xc37d7b1f, ret == CELL_OK, "sys_spu_thread_connect_event failed: " << ret);
		}

		// Attach the auto ones - hkSemaphoreBusyWait
		for( hkSpuPortManager* man = hkSpuPortManager::getFirst(); man != HK_NULL; man = man->getNext() )
		{
			HK_ON_DEBUG(ret =) sys_spu_thread_connect_event(thread, man->getEventQueue(), SYS_SPU_THREAD_EVENT_USER, man->getSpuPort());
			HK_ASSERT2(0xc37d7b1f, ret == CELL_OK, "sys_spu_thread_connect_event failed: " << ret);
		}
		hkSpuPortManager::setSpuStarted( true );
	}

	// If this is the last thread, start the thread group
	m_spuThreadIds[m_spuThreadCounter] = thread;
	m_spuThreadCounter++;
	if (m_spuThreadCounter == m_numSpuThreads )
	{
		HK_ON_DEBUG(int ret = )sys_spu_thread_group_start(m_groupId);
		HK_ASSERT2(0x67b8a7ed,  ret == CELL_OK, "sys_spu_thread_group_start failed: " << ret);
	}
}

void hkSpuUtil::quitSpuThreadGroup()
{
	// disconnect printf
	HK_ASSERT(0, m_groupId != INVALID_GROUP_ID );
	HK_ASSERT(0, m_spuThreadCounter == m_numSpuThreads );

	int ret;

	// send quit
	for( int tid = 0; tid < m_numSpuThreads; ++tid )
	{
		sys_spu_thread_set_spu_cfg( m_spuThreadIds[tid], 0 ); // overwrite mode
		sys_spu_thread_write_snr( m_spuThreadIds[tid], 0, 0xdeadf00d);
	}

	// wait for exit
	int cause, status;
	ret = sys_spu_thread_group_join(m_groupId, &cause, &status);
	HK_ASSERT2(0x67b8a7e2,  ret == CELL_OK, "sys_spu_thread_group_join failed: " << ret);

	for( int tIndex = 0; tIndex < m_spuThreadCounter; ++tIndex )
	{
		sys_spu_thread_t thread = m_spuThreadIds[tIndex];
		for( hkSpuPortManager* man = hkSpuPortManager::getFirst(); man != HK_NULL; man = man->getNext() )
		{
			HK_ON_DEBUG(ret =) sys_spu_thread_disconnect_event(thread, SYS_SPU_THREAD_EVENT_USER, man->getSpuPort() );
			HK_ASSERT2( 0xc37d7b1f, ret == CELL_OK, "sys_spu_thread_disconnect_event failed: " << ret);
		}
		for( int i = hkSpuHelperThread::HELP_TYPE_FIRST; i < hkSpuHelperThread::HELP_TYPE_LAST; ++i )
		{
			HK_ON_DEBUG(ret =) sys_spu_thread_disconnect_event(thread, SYS_SPU_THREAD_EVENT_USER, hkUint32(i) );
			HK_ASSERT2( 0xc37d7b1f, ret == CELL_OK, "sys_spu_thread_disconnect_event failed: " << ret);
		}
		hkSpuPortManager::setSpuStarted( false );
	}

	ret = sys_spu_thread_group_destroy(m_groupId);
	HK_ASSERT2(0x67b8a7e2,  ret == CELL_OK, "sys_spu_thread_group_destroy failed: " << ret);

	m_groupId = INVALID_GROUP_ID;
}

void hkSpuUtil::setDefaultSpursTaskAndParams( hkArray<hkSpuTaskParams>& spuParams,  void* elf)
{
	m_defaultParams			= spuParams;
	m_numActiveSpursTasks	= spuParams.getSize();
	m_defaultElf			= elf;
}

void hkSpuUtil::startDefaultSpursTasks( )
{
	HK_ASSERT2(0xfeaeaf95, m_numActiveSpursTasks >= 0, "You must call setDefaultSpursTaskAndParams() before calling startDefaultSpursTasks().");
	HK_ASSERT2(0xaf3fe1e3, m_numActiveSpursTasks <= m_defaultParams.getSize(), "Cannot start more spurs tasks than m_defaultParams available. Try decreasing the number of active spurs tasks with setNumActiveSpursTasks() or increase the number of default parameter task sets when calling setDefaultSpursTaskAndParams().");
	for (int i = 0; i < m_numActiveSpursTasks; ++i )
	{
		startSpursTask(m_defaultParams[i], m_defaultElf );
	}
}

void hkSpuUtil::startSpursTasks( hkArray<hkSpuTaskParams>* spuParams, void* elfAddress )
{
	if ( spuParams == HK_NULL )
	{
		HK_ASSERT2(0xaf3fe1e4, m_numActiveSpursTasks >= 0, "You must call setDefaultSpursTaskAndParams() before calling startSpursTasks() with spuParams == HK_NULL.");
		HK_ASSERT2(0xaf3fe1e1, m_numActiveSpursTasks <= m_defaultParams.getSize(), "Cannot start more spurs tasks than m_defaultParams available. Try decreasing the number of active spurs tasks with setNumActiveSpursTasks() or increase the number of default parameter task sets when calling setDefaultSpursTaskAndParams().");
		spuParams = &m_defaultParams;
	}
#if defined(HK_DEBUG)
	else
	{
		HK_ASSERT2(0xaf3fe1e2, m_numActiveSpursTasks <= spuParams->getSize(), "Cannot start more spurs tasks than spuParams available. Try decreasing the number of active spurs tasks with setNumActiveSpursTasks() or increase the number of 'spuParams' passed into startSpursTasks().");
	}
#endif

	hkArray<hkSpuTaskParams>& paramsArray = *spuParams;
	{
		for ( int i = 0; i < m_numActiveSpursTasks; i++ )
		{
			startSpursTask(paramsArray[i], elfAddress);
		}
	}
}

void hkSpuUtil::setNumActiveSpursTasks( int num )
{
	m_numActiveSpursTasks = num;
}

int hkSpuUtil::getNumActiveSpursTasks()
{
	return m_numActiveSpursTasks;
}

void* hkSpuUtil::getMemoryBins()
{
	return &m_bins[0];
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
