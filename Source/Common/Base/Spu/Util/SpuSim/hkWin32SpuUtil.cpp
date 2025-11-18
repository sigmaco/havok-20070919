/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Util/hkSpuUtil.h>
#include <Common/Base/Memory/Memory/hkMemory.h>

#ifdef HK_SIMULATE_SPU_DMA_ON_CPU
#include <Common/SpuSimulator/hkSpuSimulator.h>
#endif

#	define MAX_NUM_SPU_THREADS 6

#ifdef HK_SIMULATE_SPU_DMA_ON_CPU

	hkSpuUtil::hkSpuUtil()
	{
		m_spuSimulatorServer = HK_NULL;
		m_numActiveSpursTasks = -1;
	}

	hkSpuUtil::~hkSpuUtil()
	{
		delete m_spuSimulatorServer;
	}

	void hkSpuUtil::initSpursTaskset( int numSpus, hkSpuTaskSetParams& params, HK_CELL_SPURS* unusedSpursPtr )
	{
		HK_ASSERT( 0x1289ea74, numSpus <= MAX_NUM_SPU_THREADS);

		m_spuSimulatorServer = new hkSpuSimulator::Server( 5788 );

		while( true )
		{
			int numClients = m_spuSimulatorServer->getNumClients();
			if ( numClients ==  MAX_NUM_SPU_THREADS )
			{
				break;
			}
			m_spuSimulatorServer->pollForNewClient();
			m_spuSimulatorServer->refreshClientList();

			int numNewClients = m_spuSimulatorServer->getNumClients();
			if ( numNewClients < numSpus )
			{
				continue;
			}

			// search for extra already started clients
			if ( numNewClients != numClients )
			{
				// continue searching for clients as long as we have found a new client
				continue;
			}
				// if we cannot find any more clients break
			break;
		}
	}

	void hkSpuUtil::startSpursTask( hkSpuTaskParams& params, void* elf )
	{
		m_spuSimulatorServer->runClientTask( (hkSpuTaskParams&)params, (int)(hkUlong)elf );
	}

	void hkSpuUtil::setDefaultSpursTaskAndParams( hkArray<hkSpuTaskParams>& spuParams,  void* elf)
	{
		m_defaultParams			= spuParams;
		m_numActiveSpursTasks	= spuParams.getSize();
		m_defaultElf			= elf;
	}

	void hkSpuUtil::startDefaultSpursTasks( )
	{
		HK_ASSERT2(0xfeaeaf96, m_numActiveSpursTasks >= 0, "You must call setDefaultSpursTaskAndParams() before calling startDefaultSpursTasks() ");
		HK_ASSERT2(0xaf3fe1d3, m_numActiveSpursTasks <= m_defaultParams.getSize(), "Cannot start more spurs tasks than m_defaultParams available. Try decreasing the number of active spurs tasks with setNumActiveSpursTasks() or increase the number of default parameter task sets when calling setDefaultSpursTaskAndParams().");
		for (int i = 0; i < m_numActiveSpursTasks; ++i )
		{
			startSpursTask(m_defaultParams[i], m_defaultElf );
		}
	}

	void hkSpuUtil::startSpursTasks( hkArray<hkSpuTaskParams>* spuParams, void* elfAddress )
	{
		if ( !spuParams )
		{
			HK_ASSERT2(0xaf3fe1d4, m_numActiveSpursTasks >= 0, "You must call setDefaultSpursTaskAndParams() before calling startSpursTasks() with spuParams == HK_NULL.");
			HK_ASSERT2(0xaf3fe1d1, m_numActiveSpursTasks <= m_defaultParams.getSize(), "Cannot start more spurs tasks than m_defaultParams available. Try decreasing the number of active spurs tasks with setNumActiveSpursTasks() or increase the number of default parameter task sets when calling setDefaultSpursTaskAndParams().");
			spuParams = &m_defaultParams;
		}
#if defined(HK_DEBUG)
		else
		{
			HK_ASSERT2(0xaf3fe1d2, m_numActiveSpursTasks <= spuParams->getSize(), "Cannot start more spurs tasks than spuParams available. Try decreasing the number of active spurs tasks with setNumActiveSpursTasks() or increase the number of 'spuParams' passed into startSpursTasks().");
		}
#endif

		hkArray<hkSpuTaskParams>& paramsArray = *spuParams;
		{
			for (int i = 0; i < m_numActiveSpursTasks; i++ )
			{
				startSpursTask(paramsArray[i], elfAddress );
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



	void hkSpuUtil::quitSpursTaskset()
	{
		delete m_spuSimulatorServer;
		m_spuSimulatorServer = HK_NULL;
	}


	void hkSpuUtil::initSpuThreadGroup( int numSpus )
	{
		HK_ASSERT( 0x1289ea74, numSpus <= MAX_NUM_SPU_THREADS);

		m_spuSimulatorServer = new hkSpuSimulator::Server( 5788 );

		while( m_spuSimulatorServer->getNumClients() < numSpus )
		{
			m_spuSimulatorServer->pollForNewClient();
			m_spuSimulatorServer->refreshClientList();
		}

	}

	void hkSpuUtil::startSpuThread( hkSpuTaskParams& params, char* spuProg )
	{
		m_spuSimulatorServer->runClientTask( (hkSpuTaskParams&)params, (int)(hkUlong)spuProg );
	}

	void hkSpuUtil::quitSpuThreadGroup()
	{
		delete m_spuSimulatorServer;
		m_spuSimulatorServer = HK_NULL;
	}

#else

	hkSpuUtil::hkSpuUtil()
	{
	}

	hkSpuUtil::~hkSpuUtil()
	{
	}

	void hkSpuUtil::initSpursTaskset( int numSpus, hkSpuTaskSetParams& params, HK_CELL_SPURS* unusedSpursPtr )
	{
	}

	void hkSpuUtil::startSpursTask( hkSpuTaskParams& params, void* elf)
	{
	}

	void hkSpuUtil::setDefaultSpursTaskAndParams( hkArray<hkSpuTaskParams>& spuParams,  void* elf )
	{
	}

	void hkSpuUtil::startDefaultSpursTasks( )
	{
	}

	void hkSpuUtil::startSpursTasks( hkArray<hkSpuTaskParams>* spuParams, void* elfAddress )
	{
	}

	int hkSpuUtil::getNumActiveSpursTasks()
	{
		return 0;
	}

	void hkSpuUtil::setNumActiveSpursTasks( int num )
	{

	}

	void hkSpuUtil::quitSpursTaskset()
	{
	}

	void hkSpuUtil::initSpuThreadGroup( int numSpus )
	{
	}

	void hkSpuUtil::startSpuThread( hkSpuTaskParams& params, char* spuProg )
	{
	}

	void hkSpuUtil::quitSpuThreadGroup()
	{
	}
#endif


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
