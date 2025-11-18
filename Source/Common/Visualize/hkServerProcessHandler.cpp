/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/hkProcess.h>
#include <Common/Visualize/hkServerProcessHandler.h>
#include <Common/Visualize/hkVisualDebuggerDebugOutput.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>
#include <Common/Visualize/Serialize/hkDisplaySerializeIStream.h>
#include <Common/Visualize/Serialize/hkDisplaySerializeOStream.h>

int hkServerProcessHandler::m_tag = 0;

hkServerProcessHandler::hkServerProcessHandler(hkArray<hkProcessContext*>& contexts, hkStreamReader* inStream, hkStreamWriter* outStream)
: hkProcess(false)
{
	m_commandRouter.registerProcess(this);
	m_contexts = contexts;

	// The hkProcess base class. The streams will  be the master streams for all sub-spawned processes
	m_inStream = inStream? new hkDisplaySerializeIStream(inStream) : HK_NULL;
	m_outStream = outStream? new hkDisplaySerializeOStream(outStream) : HK_NULL;	
	m_displayHandler = new hkServerDebugDisplayHandler(m_outStream);
	m_processHandler = this;
}

hkServerProcessHandler::~hkServerProcessHandler()
{
	for (int pi = 0; pi < m_processList.getSize(); ++pi)
	{
		delete m_processList[pi];
	}

	if (m_inStream) delete m_inStream;
	if (m_outStream) delete m_outStream;
	if (m_displayHandler) delete m_displayHandler;
}

static hkUint8 _cmds[] = { hkProcessHandler::HK_CREATE_PROCESS, hkProcessHandler::HK_DELETE_PROCESS }; 

void hkServerProcessHandler::getConsumableCommands( hkUint8*& commands, int& numCommands )
{
	commands = _cmds;
	numCommands = 2;
}

void hkServerProcessHandler::consumeCommand( hkUint8 command )
{
	switch (command)
	{
	case HK_CREATE_PROCESS:
		{
			int id = m_inStream->read32();
			if(m_inStream->isOk())
				createProcess(id);
		}
		break;

	case HK_DELETE_PROCESS:
		{
			int id = m_inStream->read32();
			if(m_inStream->isOk())
				deleteProcess(id);
		}
		break;
	}
}



// This function returns a new instance of a process specified by name
// NB: The caller must look after the cleanup of the returned Process instance
hkResult hkServerProcessHandler::createProcess(int id)
{
	int curIndex = findProcessByTag(id);
	if (curIndex >= 0)
		return HK_SUCCESS; // already created and running for this client
		
	hkProcess* p = hkProcessFactory::getInstance().createProcess( id, m_contexts );
	if (p)
	{
		p->m_inStream = m_inStream;
		p->m_outStream = m_outStream;
		p->m_processHandler = this;
		p->m_displayHandler = m_displayHandler;
		p->init();

		m_processList.pushBack(p);
		m_commandRouter.registerProcess(p); // may or may not have any commands to register
		return HK_SUCCESS;
	}
	else
	{
		return HK_FAILURE;
	}
}

int hkServerProcessHandler::findProcessByTag(int tag)
{
	int np = m_processList.getSize();
	for (int i=0; i < np; ++i)
	{
		if (m_processList[i]->getProcessTag() == tag)
			return i;
	}
	return -1;
}

hkResult hkServerProcessHandler::deleteProcess(int id)
{
	int index = findProcessByTag(id);
	if (index >=0)
	{
		hkProcess* p = m_processList[index]; 
		m_processList.removeAt(index);
		m_commandRouter.unregisterProcess(p);
		delete p;
	}
	else
	{
		HK_WARN( 0xfe452761, "VDB: Process scheduler could not find process to delete.");
	}
	return HK_SUCCESS;
}

hkResult hkServerProcessHandler::registerProcess(const char* name, int id)
{
	int length = hkString::strLen( name );
	if (length > 65535)	length = 65535;

	m_outStream->write32(1+4+2+length); // packet size

	// send command headder
	m_outStream->write8u(hkProcessHandler::HK_REGISTER_PROCESS);
	// send id
	m_outStream->write32(id);
	// send length (and truncate if necessary)
	
	m_outStream->write16u((unsigned short)length);
	// send the actual string data
	m_outStream->writeRaw(name, length);

	return HK_SUCCESS;
}

hkResult hkServerProcessHandler::registerAllAvailableProcesss()
{
	// send a list of all the viewers over to the client
	const hkObjectArray<hkProcessFactory::ProcessIdPair>& factoryProcessList=
		hkProcessFactory::getInstance().m_name2creationFunction;

	for(int i = 0; i < factoryProcessList.getSize(); i++)
	{
		//HK_VISUAL_DEBUGGER_INFO(1, "Registering process  " << factoryProcessList[i].m_name.cString() << "[" << i << "]" << " with new client");
		registerProcess(factoryProcessList[i].m_name.cString(), i);
	}

	return HK_SUCCESS;
}

hkResult hkServerProcessHandler::selectProcess(int id)
{
	m_outStream->write32(1+4); // packet size

	// send command headder
	m_outStream->write8u(hkProcessHandler::HK_SELECT_PROCESS);
	// send id
	m_outStream->write32(id);

	return HK_SUCCESS;
}

void hkServerProcessHandler::step( hkReal frameTimeInMs )
{
	// Step the Processes
	int np = m_processList.getSize();

	// As a process can delete itself, we can just 
	// iter in reverse to prevent overrun
	for (int i=np-1; i >= 0; --i)
	{
		m_processList[i]->step( frameTimeInMs );
	}

	// Interpret commands (after the process step so that Processes like the plugin
	// handlers have time to create processes, that in turn may be required for a new command
	if (m_inStream)
	{
		m_commandRouter.consumeCommands(m_inStream);
	}
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
