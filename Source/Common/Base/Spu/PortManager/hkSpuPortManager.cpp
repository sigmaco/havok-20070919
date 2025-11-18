/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/PortManager/hkSpuPortManager.h>
#include <Common/Base/Memory/PlattformUtils/Spu/hkSpuMemoryInternal.h>

// Some spu ports are hardcoded because there's no code to
// do the connect on ppu and upload the dynamically used port
// to the spu.
#define BIT(A) (hkUint64(1) << hkSpuHelperThread::A)
static hkUint64 s_portsInUse = \
	BIT(HELP_TYPE_SYSTEM_PRINTF) |
	BIT(HELP_TYPE_MEMORY_SERVICE) |
	BIT(HELP_TYPE_PRINTF) |
    BIT(HELP_TYPE_FORWARD_REPORT) |
    BIT(HELP_TYPE_FORWARD_WARNING) |
    BIT(HELP_TYPE_FORWARD_ASSERT) |
    BIT(HELP_TYPE_FORWARD_ERROR);
#undef BIT
static hkSpuPortManager* s_head;
static hkBool32 s_spusHaveStarted;

hkSpuPortManager::hkSpuPortManager()
	: m_eventQueue(0), m_spuPort(hkUint32(PORT_UNALLOCATED)), m_next(s_head)
{
	s_head = this;
	allocateSpuPort(hkUint32(PORT_AUTO));
}

hkSpuPortManager::~hkSpuPortManager()
{
	HK_ASSERT2(0x17116d65, s_spusHaveStarted==false, "Spu must be stopped before ports are destroyed");
	s_portsInUse &= ~(hkUint64(1) << m_spuPort);
	for( hkSpuPortManager** cur = &s_head; cur[0] != HK_NULL; cur = &(cur[0]->m_next) )
	{
		if( cur[0] == this )
		{
			cur[0] = this->m_next;
			break;
		}
	}
}

void hkSpuPortManager::setEventQueue(hkUint32 eventQueue)
{
	m_eventQueue = eventQueue;
}

hkUint32 hkSpuPortManager::allocateSpuPort(hkUint32 spuPort)
{
	HK_ASSERT2(0x17116d64, s_spusHaveStarted==false, "Ports must be allocated before the spus start");
	HK_ASSERT2(0x17116d65, m_spuPort==PORT_UNALLOCATED, "Ports has already been allocated");

	if( spuPort == PORT_AUTO )
	{
		hkUint64 bit = 1;
		for( int port = 0; port < 64; ++port )
		{
			if( (s_portsInUse & bit) == 0 )
			{
				spuPort = port;
				break;
			}
			bit <<= 1;
		}
		HK_ASSERT2(0, spuPort != PORT_AUTO, "failed to get spu port");	
	}
	HK_ASSERT2(0, ( (hkUint64(1)<<spuPort) & s_portsInUse) == 0, "port in use");	
	s_portsInUse |= hkUint64(1) << spuPort;
	return m_spuPort = spuPort;
}

hkUint32 hkSpuPortManager::getSpuPort() const
{
	HK_ASSERT(0, m_spuPort < 64 );
	HK_ASSERT(0, s_portsInUse & (hkUint64(1)<<m_spuPort) );
	return m_spuPort;
}

hkSpuPortManager* hkSpuPortManager::getFirst()
{
	return s_head;
}

hkResult hkSpuPortManager::dontUsePorts( hkUint64 mask )
{
	hkUint64 conflict = mask & s_portsInUse;
	HK_ASSERT2(0x1d2e4660, conflict==0,	"Some reserved ports are already in use, try calling earlier.");
	s_portsInUse |= mask;
	return conflict ? HK_FAILURE: HK_SUCCESS;
}

void hkSpuPortManager::setSpuStarted( hkBool32 started )
{
	s_spusHaveStarted = started;
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
