/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_BASE_PS2_SOCKET_H
#define HK_BASE_PS2_SOCKET_H

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/hkSocket.h>

// Define ONE of the following and build hkbase agai.
// INet version of the PS2 sockets (for SCE libs 2.7.1 or higher). 
// Does not support non-blocking reads, runs on the IOP.
#define HK_PS2_USING_INET_SOCKETS

// EENet version of the PS2 sockets (for SCE libs 2.8.1 or higher). 
// Does support non-blocking reads, runs on mainly on the EE.
//#define HK_PS2_USING_EENET_SOCKETS

class hkPs2Socket : public hkSocket
{
	public:

		hkPs2Socket(int s=-1);

		virtual ~hkPs2Socket();

		virtual hkBool isOk() const;

		virtual void close();

		virtual int read( void* buf, int nbytes);

		virtual int write( const void* buf, int nbytes);

		// client

		virtual hkResult connect(const char* servername, int portNumber);

		// server

		hkResult listen(int port);
		hkSocket* pollForNewClient();

		static const char* s_combination;
		static const char* s_netDbAbsolutePath;

	protected:

		hkResult createSocket();
		int m_socket;
};


/// Platform INet or EENet init and quit.
/// One create, this socket impl will call the init() func below
/// It assumes that the required modules are loaded, but does
/// the rest of the INet Init, ctrl setup and the loading of the configuration.
/// If this is alredy done by your own code, and you don't want to make a 
/// new socket impl, just point these function ptrs to null or a function
/// that does the parts you don't. 
/// Init will be called just once, upon creation of the first socket
void HK_CALL hkPs2NetworkInit();

/// Currently quit is called by hkBaseSystem::quit, but you can call it directly 
/// when you know you don't want the network anymore ( hkSocket::s_platformNetQuit() )
void HK_CALL hkPs2NetworkQuit();

#endif // HK_BASE_PS2_SOCKET_H


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
