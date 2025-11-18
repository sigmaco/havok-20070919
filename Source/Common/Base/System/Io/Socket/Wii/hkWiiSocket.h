/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_BASE_WII_SOCKET_H
#define HK_BASE_WII_SOCKET_H

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/hkSocket.h>
#include <Common/Base/System/Io/IArchive/hkIArchive.h>
#include <Common/Base/System/Io/OArchive/hkOArchive.h>
#include <Common/Base/System/Stopwatch/hkStopwatch.h>
#include <Common/Base/Container/Queue/hkQueue.h>

#include <revolution.h>

class hkWiiSocket : public hkSocket
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS );

		typedef int socket_t;

		hkWiiSocket(int s=-1);

		virtual ~hkWiiSocket();

		virtual hkBool isOk() const;

		virtual void close();

		virtual int read( void* buf, int nbytes);

		virtual int write( const void* buf, int nbytes);

		// client

		virtual hkResult connect(const char* servername, int portNumber);

		// server

		hkResult listen(int port);
		hkSocket* pollForNewClient();

		static void setReceivePossible( bool val );
		static void setSendPossible( bool val );
		bool receivePossible();
		bool sendPossible();

	private:

		static bool	bReceivePossible;       
		static bool	bSendPossible;

	protected:

		void waitForMailbox();
		void startTimeout();
		hkBool timedOut();
		
		int m_socket;
		hkQueue<unsigned char> m_readQueue;
		hkStopwatch m_timeout;
	
};

/// Set up Wii network. Set hkSocket::s_platformNetInit to HK_NULL to prevent this being called
void HK_CALL hkWiiNetworkInit();

/// Set up Wii network. Set hkSocket::s_platformNetQuit to HK_NULL to prevent this being called
void HK_CALL hkWiiNetworkQuit();
 

#define INVALID_WII_SOCKET -1
#define VALID_WII_SOCKET    1


// We read VDB commands in units of one hkWiiCommandPacket, which is 32 bytes long since HIO2 allows 
// only a read/write of multiples of 32 bytes at a time.
// We write data from the Wii to the VDB as a hkWiiDataPacket, which contains a multiple
// of 32 bytes.
// Each packet consists of an unsigned 16 bit size (in little endian byte order), and a data buffer


//// - should be identical to corresponding section in hkWiiInterface.cpp - ////
//
// layout of 8Kb shared buffer:
// [ 0x0000, 0x1F9F ]  Wii-to-PC data packet, up to 8096 bytes
// [ 0x1FA0, 0x1FBF ]  empty, 32 bytes
// [ 0x1FC0, 0x1FDF ]  PC-to-Wii command packet, 32 bytes
// [ 0x1FE0, 0x1FFF ]  empty, 32 bytes

struct hkWiiCommandPacket
{
	u16 size;
	unsigned char data[30];
};
struct hkWiiDataPacket
{
	u16 size;
	unsigned char data[8094];
};

static hkWiiDataPacket     sendBuffer ATTRIBUTE_ALIGN(32);
static hkWiiCommandPacket  recvBuffer ATTRIBUTE_ALIGN(32);

#define	NNGC2PC_ADDR	0x0000					  
#define PC2NNGC_ADDR	0x1FC0 
//
//// - should be identical to corresponding section in hkWiiInterface.cpp (end) - ////


#endif // HK_BASE_WII_SOCKET_H


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
