/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Serialize/hkSerialize.h>


#include <Common/Visualize/hkProcess.h>
#include <Common/Visualize/hkCommandRouter.h>
#include <Common/Visualize/Serialize/hkDisplaySerializeIStream.h>

void hkCommandRouter::registerProcess(hkProcess* handler)
{
	hkUint8* commands = HK_NULL;
	int numCommands = 0;
	handler->getConsumableCommands(commands, numCommands);	

	for (int c = 0; c < numCommands; ++c)
	{
		hkUint8 cmd = commands[c];
		m_commandMap.insert( cmd, handler );
	}
}

void hkCommandRouter::unregisterProcess(hkProcess* handler)
{
	hkUint8* commands = HK_NULL;
	int numCommands = 0;
	handler->getConsumableCommands(commands, numCommands);	
	for (int c = 0; c < numCommands; ++c)
	{
		hkUint8 cmd = commands[c];
		m_commandMap.remove( cmd );
	}
}

hkBool hkCommandRouter::consumeCommands(hkDisplaySerializeIStream* stream)
{
	hkUint8 command;
	hkProcess* handler;
	do
	{
		// read 8bytes from the tcp/ip buffer and make endian safe:
		// XXX: this is blocking on our conoles etc.. so requires a COMMAND_STEP in
		// order to return from this func..

		command = stream->read8u();

		// get the appropriate command handler
		if (command != COMMAND_ACK)
		{
			if ( (m_commandMap.get( command, &handler ) == HK_SUCCESS) && handler )
			{
				// call consume on it
				HK_ASSERT2(0x7ce319b1, handler->m_inStream == stream, "VDB CommandRouter: Something gone astray with the inout streams.." );
				handler->consumeCommand(command);
			}
			else 
			{
				// XXXXX Hack for older mouse picking in the client
				hkVector4 t;
				if (command == 0xB0) 
				{
					stream->readQuadVector4(t);
					stream->read64u();
				}
				else if (command == 0xB1)
				{
					stream->readQuadVector4(t);
				}
				hkString str;
				str.printf("VDB: Found a command (%x) with no handler. Could corrupt the stream.", int(command) );
				HK_WARN( 0xfdf334d, str.cString() );
			}
		}
	}
	while(stream->isOk() && (command != COMMAND_ACK));

	return true;
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
