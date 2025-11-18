/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/Bsd/hkBsdSocket.h>

// Windows
#if defined(HK_PLATFORM_WIN32)

#	include <winsock.h>
#	pragma comment(lib,"wsock32.lib")
	typedef int socklen_t;
	HK_COMPILE_TIME_ASSERT( sizeof(hkBsdSocket::socket_t) == sizeof(SOCKET) );

// Xbox
#elif defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360)

#	include <Xtl.h>
#	ifdef HK_ARCH_PPC
#		include <winsockx.h>
#	endif
	typedef int socklen_t;
	HK_COMPILE_TIME_ASSERT( sizeof(hkBsdSocket::socket_t) == sizeof(SOCKET) );

// Normal BSD socket:
#else 
#	include <sys/types.h>
#	include <sys/time.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <netinet/tcp.h>
#	include <arpa/inet.h>
#	include <unistd.h>
#	include <netdb.h>
#	include <Common/Base/Fwd/hkcstring.h>
#	define closesocket close
#	define INVALID_SOCKET (-1)
#	define SOCKET_ERROR (-1)
#endif


static hkBool g_defaultPlatformInitOnce = false;
void HK_CALL hkBsdNetworkInit()
{
	if( !g_defaultPlatformInitOnce )
	{
#		if defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360)
		{
			// Initialize the network stack.
			// XNetStartup( NULL );  // This is the default startup
			XNetStartupParams xnsp;
			ZeroMemory(&xnsp, sizeof(xnsp));
			xnsp.cfgSizeOfStruct = sizeof(xnsp);
			xnsp.cfgFlags = XNET_STARTUP_BYPASS_SECURITY;

			/*INT iResult = */XNetStartup( &xnsp );
		}
#		endif

#		if defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360) || defined(HK_PLATFORM_WIN32)
		{
			// initialize win sockets
			const int WSAVERSION = 0x202; // winsock version
			WSADATA wsaData;
			if(WSAStartup(WSAVERSION,&wsaData) == SOCKET_ERROR)
			{
				HK_ERROR(0x321825f8, "(Windows)WSAStartup failed with error!");
			}
		}
#endif

		g_defaultPlatformInitOnce = true;
	}
}

void HK_CALL hkBsdNetworkQuit()
{

}

hkBsdSocket::hkBsdSocket(socket_t s)
	: m_socket(s)
{
	if ( m_socket == INVALID_SOCKET )
	{
		createSocket();
	}
}

hkBool hkBsdSocket::isOk() const
{
	return m_socket != INVALID_SOCKET;
}

void hkBsdSocket::close()
{
	if(m_socket != INVALID_SOCKET)
	{
		::closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

hkResult hkBsdSocket::createSocket()
{
	close();
	m_socket = static_cast<socket_t>( ::socket(AF_INET, SOCK_STREAM, 0) );
	if(m_socket == INVALID_SOCKET)
	{
		HK_WARN(0x3b98e883, "Error creating socket!");
		return HK_FAILURE;
	}
	return HK_SUCCESS;
}

hkBsdSocket::~hkBsdSocket()
{
	close();
}


int hkBsdSocket::read(void* buf, int nbytes)
{
	if(m_socket != INVALID_SOCKET)
	{
		int n = ::recv(m_socket, static_cast<char*>(buf), nbytes, 0);
		if (n <= 0 || n == SOCKET_ERROR)
		{
#ifdef HK_PLATFORM_WIN32 // might be non blocking
			if ( WSAGetLastError() == WSAEWOULDBLOCK )
				return 0; // don't close, as async
#endif
				// have to remove the warning as this warning allocates memory which breaks the SPU simulator
			//HK_WARN(0x4bb09a0f, "Read fail! Was the receiving end of socket closed?");
			close();	
		}
		else
			return n;
	}
	return 0;
}

int hkBsdSocket::write( const void* buf, int nbytes)
{
	if(m_socket != INVALID_SOCKET)
	{
		int n = ::send(m_socket, static_cast<const char*>(buf), nbytes, 0);
		if(n <= 0 || n == SOCKET_ERROR )
		{
#ifdef HK_PLATFORM_WIN32 // might be non blocking 
			int werror = WSAGetLastError();
			if ( werror == WSAEWOULDBLOCK )
				return 0; // don't close, is async 
#endif
				// We have to disable the warn as it breaks the SPU simulator
			//HK_WARN(0x4cb4c0c7, "Socket send fail! Was the receiving end of socket closed?");
			close();	
		}
		else
		{
			return n;
		}
	}
	return 0;
}

static hkBool HK_CALL hkIsDigit(int c)
{
	return c >= '0' && c <= '9';
}

hkResult hkBsdSocket::connect(const char* servername, int portNumber)
{

	// find the address of the server
	struct sockaddr_in server;
	{
		hkString::memSet(&server,0,sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons( (unsigned short)portNumber);

		if(hkIsDigit(servername[0]))
		{
			//server.sin_addr.S_un.S_addr = inet_addr(servername);
			server.sin_addr.s_addr = ::inet_addr(servername);
		}
		else
		{
#			if defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360)
				HK_ERROR(0, "Hostname lookup not supported on xbox");
#			endif

#			if defined(HK_PLATFORM_WIN32) || defined(HK_PLATFORM_UNIX)
				struct hostent* hp;
				hp = ::gethostbyname(servername);

				if(hp)
				{
					hkString::memCpy(&(server.sin_addr),hp->h_addr,hp->h_length);
				}
				else
				{
					HK_WARN(0x1f2dd0e8, "Invalid server address!");
					return HK_FAILURE;
				}
#			endif
		}
	}

	if( m_socket == INVALID_SOCKET )
	{
		if (createSocket() != HK_SUCCESS )
		{
			return HK_FAILURE;
		}
	}

	if(::connect(m_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
#ifdef HK_PLATFORM_WIN32
		// may be an aync socket
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return HK_SUCCESS;
		}
#endif

		HK_WARN(0x46d25e96, "Cannot connect to server!");
		close();
		return HK_FAILURE;
	}
	return HK_SUCCESS;
}

hkResult hkBsdSocket::asyncSelect(void* notificationHandle, hkUint32 message, SOCKET_EVENTS events)
{
#ifdef HK_PLATFORM_WIN32
	hkUint32 wsaEvents = (events & SOCKET_CAN_READ? FD_READ : 0) |
		(events & SOCKET_CAN_WRITE? FD_WRITE : 0) |
		(events & SOCKET_CONNECT? FD_CONNECT : 0) |
		(events & SOCKET_CLOSED? FD_CLOSE : 0);	

	if( WSAAsyncSelect( m_socket, (HWND)notificationHandle, message, wsaEvents ) != 0)
	{
		return HK_FAILURE;
	}

/*	if (events==0) // want no events.. so has to be non blocking (has to be after reset of select)
	{
		unsigned long nbState = 0; // 0 == blocking
		if ( ::ioctlsocket(m_socket, FIONBIO, &nbState ) != 0 )
		{
			switch( WSAGetLastError() )
			{
			case WSANOTINITIALISED:
				hkcout << "1"; break;
			case WSAENETDOWN:
				hkcout << "2"; break;
			case WSAEINPROGRESS:
				hkcout << "3"; break;
			case WSAENOTSOCK:
				hkcout << "4"; break;
			case WSAEFAULT:
				hkcout << "5"; break;

			}
			return HK_FAILURE;
		}
	}
*/		
	return HK_SUCCESS;
#else
	return HK_FAILURE;
#endif
}

hkResult hkBsdSocket::listen(int port)
{
	if( createSocket() != HK_SUCCESS)
	{
		return HK_FAILURE;
	}

	// bind to specified port
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons( (unsigned short)port );

	union
	{
		int reuseAddress;
		char data[1];
	} option;
	option.reuseAddress = 1;
	setsockopt ( m_socket, SOL_SOCKET, SO_REUSEADDR, &option.data[0], sizeof(option) );

	if( ::bind(m_socket,(struct sockaddr*)&local,sizeof(local) ) == SOCKET_ERROR )
	{
		HK_WARN(0x661cf90d, "Error binding to socket!");
		close();
		return HK_FAILURE;
	}

	// put the server socket into a listening state
	if( ::listen(m_socket,2) == SOCKET_ERROR )
	{
		HK_WARN(0x14e1a0f9, "Error listening to socket!");
		close();
		return HK_FAILURE;
	}

	// At this point we should try and report which set of IPs we are listening on
	// As this host machine can have multiple interfaces and multiple IPs, it will
	// chose its host IP based on the actual connection it recvs. Thus we should 
	// enumerate all possibilities and report them so that the user knows the valid IPs
	hkString addrString;

#ifdef HK_PLATFORM_WIN32
	
	// Winsock addition to BSD sockets:
	char tn[256];
	gethostname(tn,256); // will normally return just the windows name of the machine, which is fine
	addrString = tn;

#elif defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360)
	
	// Get the Xbox IP
	XNADDR xnHostAddr;
	DWORD dwStatus;
	do
	{
		// Repeat while pending; OK to do other work in this loop
		dwStatus = XNetGetTitleXnAddr( &xnHostAddr );
	} while( dwStatus == XNET_GET_XNADDR_PENDING );

	// Error checking
	if( dwStatus == XNET_GET_XNADDR_NONE )
		xnHostAddr.ina.s_addr = 0;

	if (xnHostAddr.ina.s_addr)
	{
		addrString.printf("%d.%d.%d.%d",xnHostAddr.ina.S_un.S_un_b.s_b1,
										xnHostAddr.ina.S_un.S_un_b.s_b2,
										xnHostAddr.ina.S_un.S_un_b.s_b3,
										xnHostAddr.ina.S_un.S_un_b.s_b4);
	}
	else if (xnHostAddr.inaOnline.s_addr)
	{
		addrString.printf("%d.%d.%d.%d",xnHostAddr.inaOnline.S_un.S_un_b.s_b1,
										xnHostAddr.inaOnline.S_un.S_un_b.s_b2,
										xnHostAddr.inaOnline.S_un.S_un_b.s_b3,
										xnHostAddr.inaOnline.S_un.S_un_b.s_b4);
	}
	else 
		addrString = "unknown";
#endif

	HK_REPORT("Listening on host[" << addrString << "] port " << port);
	return HK_SUCCESS;
}

hkSocket* hkBsdSocket::pollForNewClient()
{
	HK_ASSERT2( 0x73993156, m_socket != INVALID_SOCKET, "");

	// poll the listener socket for new client sockets
	if( m_socket != INVALID_SOCKET )
	{
		fd_set readFds;
		FD_ZERO(&readFds);
		FD_SET(m_socket, &readFds);

		fd_set exceptFds;
		FD_ZERO(&exceptFds);
		FD_SET(m_socket, &exceptFds);


		// see if there is and client trying to connect

		socket_t maxFd = m_socket + 1;
		timeval t = {0, 0};	// no wait time -- i.e. non blocking select
		int numHits = ::select(maxFd, &readFds, HK_NULL, &exceptFds, &t);

		if( (numHits > 0) && FD_ISSET(m_socket, &readFds) )
		{
			struct sockaddr_in from;
			socklen_t fromlen = sizeof(from);

			socket_t s = static_cast<socket_t>( ::accept(m_socket, (struct sockaddr*)&from, &fromlen) );

			hkString rs;
#if !defined(HK_PLATFORM_XBOX) && !defined(HK_PLATFORM_XBOX360) 
			rs.printf("Socket got connection from [%s:%d]\n", inet_ntoa(
from.sin_addr), ntohs(from.sin_port));
#else
			rs.printf("Socket got connection from [%lx:%d]\n", from.sin_addr, ntohs(from.sin_port));
#endif
			HK_REPORT(rs);

			if(s == INVALID_SOCKET)
			{
				HK_WARN(0x774fad25, "Error accepting a connection!");
			}
			else
			{
				// Add the current connection to the servers list
				unsigned int optval = 1;
				::setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char *)&optval, sizeof (unsigned int));

				return new hkBsdSocket(s);
			}
		}
		else if(numHits == SOCKET_ERROR)
		{
			HK_WARN(0x3fe16171, "select() error");
		}
	}

	return HK_NULL;
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
