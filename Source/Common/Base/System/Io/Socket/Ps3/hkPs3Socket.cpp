/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/Ps3/hkPs3Socket.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>

#include <types.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/time.h> // for timeval for select()
#include <sys/select.h> // fd_ structs and select()
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netex/ifctl.h>
#include <netex/net.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netex/libnetctl.h>
#include <sysutil/sysutil_common.h>
#include <sys/timer.h>

#if HK_CELL_SDK_VERSION >= 0x090000
#	include <cell/sysmodule.h>
#endif

#include <unistd.h>
#include <Common/Base/Fwd/hkcstdio.h>
#include <Common/Base/Fwd/hkcstring.h>
using namespace std; // memset used without :: in FD_SET

#define closesocket socketclose
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

// Use a ./network.conf with similar to the following to allow
// you to change the havok net usage without rebuilding

#define	ETHERNET
//#define	ETHERNET_WITH_STATIC_IP
//#define	ETHERNET_WITH_PPPOE

#if defined(ETHERNET)
static char g_defaultPS3NetSettings[] =
	"type nic\n"
	"my_name \"HavokPS3VDB\"\n"	// "my_name \"MAC:00:04:1f:01:02:03\"\n"
	"dhcp\n"
	"\n"
	"vendor \"SCE\"\n"
	"product \"Gigabit Ethernet\"\n"
	"phy_config auto\n";
#endif
#if defined(ETHERNET_WITH_STATIC_IP)
static char g_defaultPS3NetSettings[] =
	"type nic\n"
	"my_name \"my_hostname1\"\n"	// my name
	"address 192.168.75.10\n"	// address
	"netmask 255.255.255.0\n"	// netmask
	"nameserver add 192.168.75.2\n"	// nameserver
	"route add default gw 192.168.75.1\n"	// route
	"\n"
	"vendor \"SCE\"\n"
	"product \"Gigabit Ethernet\"\n"
	"phy_config auto\n";
#endif
#if defined(ETHERNET_WITH_PPPOE)
static char g_defaultPS3NetSettings[] =
	"type ppp\n"
	"my_name \"my_hostname1\"\n"	// my name
	"device_type nic\n"
	"-dhcp\n"
	"auth_name \"" "your name" "\"\n"	// your name
	"auth_key \"" "your password" "\"\n"	// your password
	"peer_name \"*\"\n"
	"-want.prc_nego\n"
	"-want.acc_nego\n"
	"-want.accm_nego\n"
	"want.dns1_nego\n"
	"want.dns2_nego\n"
	"allow.auth chap/pap\n"
	"pppoe\n"
	"mtu 1454\n"
	"route add default gw 0.0.0.1\n"
	"\n"
	"vendor \"SCE\"\n"
	"product \"Gigabit Ethernet\"\n"
	"phy_config auto\n";
#endif

void HK_CALL hkPs3NetworkInit()
{

#if HK_CELL_SDK_VERSION >= 0x090000

		// Load the PRXs for the network
		int32_t prx_ret = cellSysmoduleLoadModule(CELL_SYSMODULE_NET);
		if( prx_ret < CELL_OK )
		{
			fprintf( stderr, "cellSysmoduleLoadModule failed, CELL_SYSMODULE_NET : %#x\n", prx_ret );
		}

	//	prx_ret = cellSysmoduleLoadModule(CELL_SYSMODULE_NETCTL);
	//	if( prx_ret < CELL_OK )
	//	{
	//		fprintf( stderr, "cellSysmoduleLoadModule failed, CELL_SYSMODULE_NETCTL : %#x\n", prx_ret );
	//	}

#endif

		if ( sys_net_initialize_network() == 0 )
		{
			// look for network.conf file in current working dir

			int ret;

//090: Not required:
#if HK_CELL_SDK_VERSION < 0x090000
			hkIstream confFile("network.conf");
			
			char* settings = g_defaultPS3NetSettings;
			if (confFile.isOk() && confFile.getStreamReader()->seekTellSupported())
			{
				confFile.getStreamReader()->seek(0, hkStreamReader::STREAM_END);
				int len = confFile.getStreamReader()->tell();
				confFile.getStreamReader()->seek(0, hkStreamReader::STREAM_SET);
				if (len > 0)
				{
					settings = hkAllocate<char>(len+1, HK_MEMORY_CLASS_BASE);
					confFile.read(settings, len);
					settings[len] = '\0'; // null terminate..
					// remove any \r\n as it may have been saved on PC (change to just \n)
					for (int ci=0; ci < len; ++ci)
					{
						if (settings[ci] == '\r')
							settings[ci] = ' ';
					}
					HK_REPORT("Read Havok network settings from ./network.conf :");
					HK_REPORT(settings);
				}
			}
			
			if (settings == g_defaultPS3NetSettings)
			{
				HK_WARN(0x0, "No  ./network.conf  file found, using default (DHCP etc) network settings in hkBase/stream/impl/hkPs3Socket.cpp instead.");
			}

			ret = cellSysutilInit();
			if (ret < 0) {
				printf("cellSysutilInit() failed(0x%08X)\n", ret);
			}
#endif

			ret = cellNetCtlInit();
			if (ret < 0) {
				printf("cellNetCtlInit() failed(0x%08X)\n", ret);
			}

			int state;
			for (;;) {
				ret = cellNetCtlGetState(&state);
				if (ret < 0) {
					printf("cellNetCtlGetState() failed(0x%08X)\n", ret);
				}
				if (state == CELL_NET_CTL_STATE_IPObtained) {
					break;
				}
				sys_timer_usleep(500 * 1000);
			}

//090: Not required:
#if HK_CELL_SDK_VERSION < 0x090000
			if (settings != g_defaultPS3NetSettings)
			{
				hkDeallocate<char>(settings);
			}
#endif

		}
		else
		{
			HK_WARN(0x0, "Could not bring up network. Check you have plugged a cable into the proper PS3 Gigabit network port (not the Host port) and that the settings are correct (network.conf, or statically in hkBase).");
		}

}

void HK_CALL hkPs3NetworkQuit()
{
	cellNetCtlTerm();

#if HK_CELL_SDK_VERSION >= 0x090000

	// Load the PRXs for the network
	int32_t prx_ret = cellSysmoduleLoadModule(CELL_SYSMODULE_NET);
	if( prx_ret < CELL_OK )
	{
		fprintf( stderr, "cellSysmoduleLoadModule failed, CELL_SYSMODULE_NET : %#x\n", prx_ret );
	}

	prx_ret = cellSysmoduleLoadModule(CELL_SYSMODULE_NETCTL);
	if( prx_ret < CELL_OK )
	{
		fprintf( stderr, "cellSysmoduleLoadModule failed, CELL_SYSMODULE_NETCTL : %#x\n", prx_ret );
	}
#else
	cellSysutilShutdown();
#endif

	sys_net_finalize_network();
}

hkPs3Socket::hkPs3Socket(socket_t s)
	: m_socket(s)
{
	if ( m_socket == INVALID_SOCKET )
	{
		createSocket();
	}
}

hkBool hkPs3Socket::isOk() const
{
	return m_socket != INVALID_SOCKET;
}

void hkPs3Socket::close()
{
	if(m_socket != INVALID_SOCKET)
	{
		::closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

hkResult hkPs3Socket::createSocket()
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

hkPs3Socket::~hkPs3Socket()
{
	close();
}


int hkPs3Socket::read(void* buf, int nbytes)
{
	if(m_socket != INVALID_SOCKET)
	{
		int n = ::recv(m_socket, static_cast<char*>(buf), nbytes, 0);
		if (n <= 0 || n == SOCKET_ERROR)
		{
			HK_WARN(0x4bb09a0f, "Read fail! Was the receiving end of socket closed?");
			close();	
		}
		else
			return n;
	}
	return 0;
}

int hkPs3Socket::write( const void* buf, int nbytes)
{
	if(m_socket != INVALID_SOCKET)
	{
		int n = ::send(m_socket, static_cast<const char*>(buf), nbytes, 0);
		if(n <= 0 || n == SOCKET_ERROR )
		{
			HK_WARN(0x4cb4c0c7, "Socket send fail! Was the receiving end of socket closed?");
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

hkResult hkPs3Socket::connect(const char* servername, int portNumber)
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
			// TODO: hostname lookup

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
		HK_WARN(0x46d25e96, "Cannot connect to server!");
		close();
		return HK_FAILURE;
	}
	return HK_SUCCESS;
}

hkResult hkPs3Socket::listen(int port)
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

	// Display network info.
	sys_net_show_ifconfig();

	return HK_SUCCESS;
}

hkSocket* hkPs3Socket::pollForNewClient()
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
		int numHits = ::socketselect(maxFd, &readFds, HK_NULL, &exceptFds, &t); // Changed from ::select to ::socketselect in 0.5.0

		if( (numHits > 0) && FD_ISSET(m_socket, &readFds) )
		{
			struct sockaddr_in from;
			socklen_t fromlen = sizeof(from);

			socket_t s = static_cast<socket_t>( ::accept(m_socket, (struct sockaddr*)&from, &fromlen) );

			hkString rs;
			rs.printf("Socket got connection from [%lx:%d]\n", from.sin_addr, ntohs(from.sin_port));
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

				return new hkPs3Socket(s);
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
