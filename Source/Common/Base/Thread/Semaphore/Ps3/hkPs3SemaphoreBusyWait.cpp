/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Thread/Semaphore/hkSemaphoreBusyWait.h>
#include <cell/atomic.h>
#include <cell/error.h>

//#define HK_DEBUG_PRINTF

#if defined(HK_PLATFORM_SPU)
#	if defined(HK_DEBUG_PRINTF)
#		include <spu_printf.h>
#		define SPU_PRINTF(A)  _spu_call_event_va_arg A
#		define PPU_PRINTF(A)
#	endif
#	include <sys/spu_event.h>
	HK_ALIGN( hkUint32 hkSemaphoreBusyWait::m_cacheLine[128/4], 128 );
#	define HK_ATOMIC_READ32(ea) cellAtomicLockLine32(&m_cacheLine[0], hkUlong(ea))
#	define HK_ATOMIC_STORE_OK_32(ea,val) (cellAtomicStoreConditional32(&m_cacheLine[0], hkUlong(ea), val)==0)
#else
#	if defined(HK_DEBUG_PRINTF)
#		include <Common/Base/Fwd/hkcstdio.h>
#		define PPU_PRINTF(A) std::printf A
#		define SPU_PRINTF(A)
#	endif
#	include <sys/event.h>
#	define HK_ATOMIC_READ32(ea) cellAtomicLockLine32(ea)
#	define HK_ATOMIC_STORE_OK_32(ea,val) (cellAtomicStoreConditional32(ea, val)==0)
#endif

#if !defined(HK_DEBUG_PRINTF)
#	define SPU_PRINTF(A)
#	define PPU_PRINTF(A)
#endif

#ifdef HK_DEBUG
#	define CHECK_RETURN() if(ret != CELL_OK) HK_BREAKPOINT(0)
#else
#	define CHECK_RETURN() // can't use ret as ret not dfefined in some funcs below to be used outside of HK_ON_DEBUG
#endif

#if !defined(HK_PLATFORM_SPU)

hkSemaphoreBusyWait::hkSemaphoreBusyWait( int initialCount, int maxCount )
{
	HK_ASSERT( 0x39023981, maxCount >= 1 &&  initialCount >= 0 && initialCount <= maxCount && maxCount <= 0xffff ); 

	m_semphoreValue = initialCount | (m_spuPortManager.getSpuPort() << 24);
	m_semaphore = &m_semphoreValue;
	PPU_PRINTF(("PPU:create(%i,%i):%x\n", initialCount, maxCount, m_semphoreValue));
	{
		int ret;

		sys_event_queue_attribute_t queue_attr = { SYS_SYNC_FIFO, SYS_PPU_QUEUE, "hkSem" };
		sys_event_queue_t eventQueue;
		ret = sys_event_queue_create( &eventQueue, &queue_attr, SYS_EVENT_QUEUE_LOCAL, 50 ); //XXX
		CHECK_RETURN();
		m_spuPortManager.setEventQueue( eventQueue );

		ret = sys_event_port_create( &m_ppuEventPort, SYS_EVENT_PORT_LOCAL, SYS_EVENT_PORT_NO_NAME );
		CHECK_RETURN();
		ret = sys_event_port_connect_local(m_ppuEventPort, eventQueue);
		CHECK_RETURN();
	}
}

hkSemaphoreBusyWait::~hkSemaphoreBusyWait()
{
	HK_ON_DEBUG(int ret);
	HK_ON_DEBUG(ret =) sys_event_port_disconnect(m_ppuEventPort);
	CHECK_RETURN();
	HK_ON_DEBUG(ret =) sys_event_port_destroy(m_ppuEventPort); 
	CHECK_RETURN();
	HK_ON_DEBUG(ret =) sys_event_queue_destroy(m_spuPortManager.getEventQueue(), 0);
	CHECK_RETURN();
}

void hkSemaphoreBusyWait::acquire()
{
	PPU_PRINTF(("PPU>acq %x\n", HK_ATOMIC_READ32(m_semaphore)));
	while(1)
	{
		hkUint32 orig = HK_ATOMIC_READ32(m_semaphore);
		hkUint32 semCount = orig & 0xffff;
		hkUint32 portAndWaiters = orig & 0xffff0000;
		if( semCount != 0 )
		{
			if( HK_ATOMIC_STORE_OK_32( m_semaphore, orig - 1 ) )
			{
				PPU_PRINTF(("PPU<acq %x\n", m_semphoreValue));
				return;
			}
		}
		else if( HK_ATOMIC_STORE_OK_32(m_semaphore, portAndWaiters + (1<<16)) )
		{
			sys_event_t event;
			PPU_PRINTF(("PPU:acq>block %x\n", m_semphoreValue));
			int ret = sys_event_queue_receive(m_spuPortManager.getEventQueue(), &event, 0 );
			//if( event.source != (orig >> 24) ) HK_BREAKPOINT(2);
			if( ret != CELL_OK ) HK_BREAKPOINT(1);
			PPU_PRINTF(("PPU:acq<block %x\n", m_semphoreValue));
		}
	}
}

void hkSemaphoreBusyWait::release(int count)
{
	int wakeUps;
	hkUint32 orig;
	hkUint32 updated;
	PPU_PRINTF(("PPU>rel %x\n", m_semphoreValue));
	SPU_PRINTF( (EVENT_PRINTF_PORT<<EVENT_PORT_SHIFT,"SPU>rel %x\n", HK_ATOMIC_READ32( m_semaphore )) );
	do
	{
		orig = HK_ATOMIC_READ32( m_semaphore );
		if( (orig & 0xffff) > 10 ) HK_BREAKPOINT(1);
		int sleepers = (orig >> 16) & 0xff;
		wakeUps = sleepers > count ? count : sleepers;
		updated = orig + count - (wakeUps<<16);
	} while( HK_ATOMIC_STORE_OK_32(m_semaphore, updated) == 0 );

	PPU_PRINTF(("PPU<rel %x %iwakeups\n", m_semphoreValue, wakeUps));
	SPU_PRINTF( (EVENT_PRINTF_PORT<<EVENT_PORT_SHIFT,"SPU<rel %x\n", updated ));

	if( wakeUps > 1 ) HK_BREAKPOINT(0);
	while( wakeUps-- )
	{
		int ret = sys_event_port_send( m_ppuEventPort, 0,0,0 );
		CHECK_RETURN();
	}
}

#endif

void hkSemaphoreBusyWait::acquire(hkSemaphoreBusyWait* semaphoreOnPpu)
{
#if !defined(HK_PLATFORM_PS3SPU)
	semaphoreOnPpu->acquire();
#else
	hkUint32 savedEventMask = spu_read_event_mask();
	spu_write_event_mask(0);
	if (__builtin_expect(spu_stat_event_status(), 1))
	{
		hkUint32 ch = spu_read_event_status();
		spu_write_event_ack(ch);
	}
	spu_write_event_mask(MFC_LLR_LOST_EVENT);

	SPU_PRINTF( (EVENT_PRINTF_PORT<<EVENT_PORT_SHIFT, "SPU>acq %x\n", HK_ATOMIC_READ32(semaphoreOnPpu) ));
	hkUint32 orig;
	while(1)
	{
		orig = HK_ATOMIC_READ32( semaphoreOnPpu );
		hkUint32 semCount = orig & 0xffff;
		if( semCount != 0 )	
		{
			if( HK_ATOMIC_STORE_OK_32( semaphoreOnPpu, orig - 1 ) )
			{
				SPU_PRINTF( (EVENT_PRINTF_PORT<<EVENT_PORT_SHIFT,"SPU<acq %x\n", orig-1) );
				spu_write_event_mask(savedEventMask);
				return;
			}
		}
		else // block until sem touched
		{
			SPU_PRINTF( (EVENT_PRINTF_PORT<<EVENT_PORT_SHIFT,"SPU:acq>block %x\n", orig) );
			hkUint32 ch = spu_read_event_status(); 
			spu_write_event_ack(ch);
			SPU_PRINTF( (EVENT_PRINTF_PORT<<EVENT_PORT_SHIFT,"SPU:acq<block %x\n", orig) );
		}
	}
#endif
}

void hkSemaphoreBusyWait::release(hkSemaphoreBusyWait* semaphoreOnPpu, int count)
{
#if !defined(HK_PLATFORM_PS3SPU)
	semaphoreOnPpu->release(count);
#else
	int wakeUps;
	hkUint32 orig;
	hkUint32 updated;
	do
	{
		orig = HK_ATOMIC_READ32( semaphoreOnPpu );
		if( (orig & 0xffff) > 1000 ) HK_BREAKPOINT(1);
		int sleepers = (orig >> 16) & 0xff;
		wakeUps = sleepers > count ? count : sleepers;
		updated = orig + count - (wakeUps<<16);
	} while( HK_ATOMIC_STORE_OK_32(semaphoreOnPpu, updated) == 0 );

	if( wakeUps > 1 ) HK_BREAKPOINT(0);
	while( wakeUps-- )
	{
		hkUint32 spuPort = (orig >> 24) & 0xff;
		SPU_PRINTF( (EVENT_PRINTF_PORT<<EVENT_PORT_SHIFT,"SPU<port %x\n", spuPort ));
		HK_ON_DEBUG(int ret =) sys_spu_thread_send_event(spuPort, spuPort, 0);
		CHECK_RETURN();
	}
#endif
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
