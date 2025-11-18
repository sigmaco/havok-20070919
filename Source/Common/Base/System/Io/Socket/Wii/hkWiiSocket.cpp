/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/Wii/hkWiiSocket.h>

#include <Hio2If.c>


///////////////////////////////////////////////////////////////////////////////
//
//  HIO2IF event callback
//

// synchronization flags
bool	hkWiiSocket::bReceivePossible = FALSE; //static
bool	hkWiiSocket::bSendPossible    = TRUE;  //static

// HIO2IF ID
static HIO2IF_ID myHIO2IF_ID = HIO2IF_INVALID_ID;
static BOOL	hioAsync = FALSE;

void hkWiiSocket::setReceivePossible( bool val ) //static
{
	bReceivePossible = val;
}
		
void hkWiiSocket::setSendPossible( bool val ) //static
{
	bSendPossible = val;
}

bool hkWiiSocket::receivePossible()
{
	return bReceivePossible;
}
		
bool hkWiiSocket::sendPossible()
{
	return bSendPossible;
}

static void	myEventCallback(HIO2IF_ID id, HIO2IF_EVENT event)
{
	switch ( event )
	{
		// connection established
		case HIO2IF_EVENT_CONNECT:		
		{
			OSReport("EVENT CONNECT\n");
		}
		break;
		
		// connection released
		case HIO2IF_EVENT_DISCONNECT:	
		{
			OSReport("EVENT DISCONNECT\n");
			HIO2IFClose(myHIO2IF_ID);
		}
		break;
		
		case HIO2IF_EVENT_RECEIVED:		
		{
			hkWiiSocket::setReceivePossible(true);		
		}
		break;
		
		case HIO2IF_EVENT_SEND_POSSIBLE:		
		{	
			hkWiiSocket::setSendPossible(true);
		}
		break;
			
		default:
			break;
	} 
}

//
///////////////////////////////////////////////////////////////////////////////

static int deviceCount;
static hkBool g_WiiNetworkInitOnce = false;
static bool startHIO2Network();


static hkBool openChannel()
{
	HIO2IF_RESULT result = HIO2IFOpen( HIO2IFGetDevice(0), HIO2IF_MODE_RDWR, myEventCallback, &myHIO2IF_ID );
	
	if (result == HIO2IF_RESULT_ERROR)
	{
		HK_ERROR(0x321826a3, "Wii HIO2IF networking error: HIO2IFOpen() failed!");
		return false;
	}
	
	if (result == HIO2IF_RESULT_FATAL)
	{
		HK_ERROR(0x321826a3, "Wii HIO2IF networking fatal error: HIO2IFOpen() failed!");
		return false;
	}		
	
	//henceforth, isConnected() tells us if the PC interface is talking to hkWiiSocket
	return true;
}


bool startHIO2Network()
{
	// host I/O initialization	
	if ( HIO2IF_FAILED(HIO2IFInit()) ) 
	{
		HK_ERROR(0x321826a1, "Wii HIO2IF networking error: HIO2IFInit() failed");
		return false;
	}
		
	// gets the number of listed devices
	deviceCount = HIO2IFGetDeviceCount();

	if (deviceCount < 1)
	{
		HK_ERROR(0x321826a3, "Wii HIO2IF networking error: no device connected!");
		return false;
	}

	if ( openChannel() )
	{
		OSReport("HIO2 sees that the USB connection is available, but not yet connected\n");
	 	return true;	
	}
	
	return false;
}


static inline
BOOL	isConnected(void)
{
	return ( HIO2IFIsConnected(myHIO2IF_ID) );
}


// HIO2 needs to be re-initialized each time we get a new connection,
// e.g. when a new demo starts. So there is not really a one-time network
// initialization phase.
void HK_CALL hkWiiNetworkInit()
{
	if ( !g_WiiNetworkInitOnce )
	{
		if ( isConnected() ) 
		{
			hkWiiNetworkQuit();
		}
		
		if ( startHIO2Network() )
		{
			g_WiiNetworkInitOnce = true;
		}
	}
}


void HK_CALL hkWiiNetworkQuit()
{
	HIO2IFExit();
}


hkWiiSocket::hkWiiSocket(int s)
	:m_socket(s)
{
	// set the 'default' synchronization state
	setReceivePossible(false);
	setSendPossible(true);
	
} 


hkWiiSocket::~hkWiiSocket()
{
	close();
}


void hkWiiSocket::close()
{
	HIO2IFClose(myHIO2IF_ID);
	
	hkWiiNetworkQuit();
	
	// open a fresh connection immediately to prepare for re-connection attempt
	startHIO2Network();
}


hkResult hkWiiSocket::listen(int port)
{	
	// does nothing here
	return HK_SUCCESS;
}


// If the Wii interface crashes (or is killed), the disconnection 
// notification may never come in which case we will hang here waiting for permission
// to read or write. Therefore we wait for a period TIMEOUT (long enough that
// a hang is (almost) certain) and then disconnect. 

const float TIMEOUT = 60.0f; // in seconds
 
void hkWiiSocket::startTimeout()
{
	m_timeout.reset();
	m_timeout.start();
}

hkBool hkWiiSocket::timedOut()
{
	if ( m_timeout.getElapsedSeconds() > TIMEOUT )
	{
		close();
		return true;
	}
	return false;
}

hkBool hkWiiSocket::isOk() const
{
	return ( (m_socket != INVALID_WII_SOCKET) && isConnected() );
}


// Polls the status of the mailbox until it has been read
void hkWiiSocket::waitForMailbox()
{
	bool mailboxRead = false;
	startTimeout();

	while( !mailboxRead && isOk() && !timedOut() )
	{
		u32 stat;
		HIO2IFReadStatus(myHIO2IF_ID, &stat);
		mailboxRead = !(stat & HIO2_STATUS_RX);
	}
	
	if ( !isOk() )
	{
		OSReport("lost connection\n");
	}
} 


// Extract n bytes from the front of the queue, and copy them into buff onwards
static void _extractBytesFromQueue( int n, void* buff, hkQueue<unsigned char>& m_readQueue )
{
	int nDeQueued = 0;
	unsigned char* b = static_cast<unsigned char*>( buff );
	unsigned char c;
	
	do
	{	
		m_readQueue.dequeue(c);
		hkString::memCpy(b, &c, 1);	
		b++; nDeQueued++;
	}
	while( nDeQueued < n );
}
  
// Add n bytes starting at buff to the back of the queue 
static void _addBytesToBuffer( int n, void* buff, hkQueue<unsigned char>& m_readQueue )
{
	int nQueued = 0;
	unsigned char* b = static_cast<unsigned char*>( buff );
	
	do
	{
		m_readQueue.enqueue(*b);	
		b++; nQueued++;
	}
	while( nQueued < n );
}
  
  
// This reads from the wii-vdb interface, which sends the vdb command stream
// in the form of 32 byte hkWiiCommandPackets.

// Each call to read() will read at most one command packet, extract the data, and return
// the number of data bytes contained in the packet. If more than one packet's worth of
// data is to be read, the stream reader will have to make multiple calls to read().

// Since on reading a packet we can get up to 30 bytes of data, if read() asks for less than 30 bytes
// we may need to buffer the rest of the data to return on subsequent calls to read. Buffering is done using hkQueue.

int hkWiiSocket::read(void* buf, int nbytes)
{ 
	if (m_socket == INVALID_WII_SOCKET || nbytes == 0) return 0;

	int nRead = 0;
	HIO2IF_RESULT result;
	
	// packet data size is 2 bytes less than the packet size, due to 2 byte size field
	static int packet_data_size = sizeof(hkWiiCommandPacket) - 2;
	
	// restrict to only reading packet_data_size bytes at once
	if (nbytes > packet_data_size) nbytes = packet_data_size;

	// do we have enough in the buffer to return already?
	if (m_readQueue.getSize() >= nbytes)
	{	 
		_extractBytesFromQueue( nbytes, buf, m_readQueue );
		return nbytes; 
	}
  
	// otherwise first exhaust the buffer
	if (m_readQueue.getSize() > 0)
	{
		nRead = m_readQueue.getSize();
		_extractBytesFromQueue( m_readQueue.getSize(), buf, m_readQueue );
	} 
	
	// shift pointer to output buffer along if necessary
	unsigned char* W = static_cast<unsigned char*>( buf ) + nRead;
	 
	 // will be at least 1 byte left to read now
	int nLeftToRead = nbytes - nRead; 
	int nTotal = 0;
	
	// block until we can read a packet or got disconnected/timed out
	startTimeout();
	while ( isOk() && !timedOut() )
	{
		if ( receivePossible() ) 
		{
			// read a packet from the shared buffer
			setReceivePossible(false);
			result = HIO2IFRead(myHIO2IF_ID, PC2NNGC_ADDR, &recvBuffer, sizeof(recvBuffer), hioAsync);   
			if ( HIO2IF_FAILED(result) ) 
			{
				HK_ERROR(0x321826d3, "Wii HIO2IF networking error: HIO2IFRead() failed!");
				return 0;
			}
				
			// block until mailbox is read by the PC (to ensure the read notification is not missed)
			waitForMailbox();	
				
			// need to byte swap the 2-byte size field into little-endian order	
			hkIArchive recvArchive( &recvBuffer.size, 2 );
			int nGot = recvArchive.read16u();

			// if we got more data in the packet than we asked for, buffer the excess
			int excessBytes = nGot - nLeftToRead;
			if (excessBytes > 0)
			{
				// copy the packet data to the output
				hkString::memCpy(W, recvBuffer.data, nLeftToRead);
				 
				// append any excess data in the packet into the local buffer
				_addBytesToBuffer( excessBytes, recvBuffer.data + nLeftToRead, m_readQueue );
				nTotal = nRead + nLeftToRead;
			}
			
			// otherwise, just return everything we got
			else
			{
				// copy the packet data to the output
				hkString::memCpy(W, recvBuffer.data, nGot);
				nTotal = nRead + nGot;
			}
			
			break;
		}	
	}
	 
	return nTotal;
}


// Each call to write() will write at most one hkWiiDataPacket's worth of data, and return
// the number of bytes sent. If more than one packet's worth of
// data is to be sent, the stream reader will have to make multiple calls to write().
 
int hkWiiSocket::write( const void* buf, int nbytes)
{ 
	if (m_socket == INVALID_WII_SOCKET || nbytes == 0) return 0;

	int nSent = 0;
	HIO2IF_RESULT result;
	
	// packet data size is 2 bytes less than the packet size, due to 2 byte size field
	static int packet_data_size = sizeof(hkWiiDataPacket) - 2;
	 
	// block until we can write a packet, or got disconnected/timed out
	startTimeout();
	while ( isOk() && !timedOut()  )
	{ 
		if ( sendPossible() ) 
		{
			if (nbytes>packet_data_size) nbytes = packet_data_size;
			
			// use hkOArchive to byte swap the 2-byte size field
			hkOArchive sendArchive( &sendBuffer.size, 2 );
			sendArchive.write16u( (hkUint16)nbytes );
		
			// copy the data into the packet
			hkString::memCpy(sendBuffer.data, buf, nbytes);
		
			// Write to the shared buffer. Only write a multiple of 32 bytes which is 
			// just large enough to contain the data of sendBuffer.size bytes
			int multiple = (nbytes + 1)/32 + 1;
			 
			setSendPossible(false);
			result = HIO2IFWrite(myHIO2IF_ID, NNGC2PC_ADDR, &sendBuffer, 32 * multiple, hioAsync);
			if ( HIO2IF_FAILED(result) ) 
			{
				HK_ERROR(0x321826e3, "Wii HIO2IF networking error: HIO2IFWrite() failed!");
				return 0;	
			}
			
			// block until mailbox is read by the PC (to ensure the write notification is not missed)
			waitForMailbox();	

			nSent = nbytes;
		
			break;
		}
	}
	
	return nSent;
}
 

hkResult hkWiiSocket::connect(const char* servername, int portNumber)
{
	//For vdb, socket does not need to connect to anything - it just listens for connections
	//from the PC side

	return HK_SUCCESS;
}


// We create separate server and connection sockets as in unix sockets, even though this is not
// needed in HIO2, since the server code assumes it
hkSocket* hkWiiSocket::pollForNewClient()
{
	if ( !isConnected() ) 
	{
		m_socket = INVALID_WII_SOCKET;
				
		// This makes HIO2IF poll for a new connection from the PC side
		HIO2IFSync();	
		
		return NULL; 
	}
	
	// if connected
	else
	{
		// if just connected
		if ( m_socket == INVALID_WII_SOCKET )
		{
			m_socket = VALID_WII_SOCKET;
				
			return new hkWiiSocket(VALID_WII_SOCKET);			
		}
		
		// no more than one active client connection is available	
		else
		{
			return NULL;
		}
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
