/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/Psp/hkPspSocket.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>

#include <Common/Base/Fwd/hkcstdio.h>
#include <Common/Base/Fwd/hkcstring.h>

// psp devkit headers
#include <kernel.h>

#include <pspnet.h>
#include <psperror.h>
#include <pspnet_error.h>
#include <pspnet_inet.h>
#include <pspnet_resolver.h>
#include <pspnet_apctl.h>

#include <pspnet/sys/socket.h>
#include <pspnet/sys/select.h>

#include <pspnet/netinet/in.h>
#include <pspnet/netinet/tcp.h>
#include <pspnet/netinet/tcp_var.h>
#include <pspnet/netinet/udp_var.h>
#include <pspnet/netinet/tcp_fsm.h>
#include <pspnet_apctl.h>
#include <pspnet_ap_dialog_dummy.h>
#include <wlan.h>
#include <utility/utility_module.h>

// SCE_PSPNET_RESOLVER_NTOA_BUFSIZE_MAX defined in
// pspnet_resolver.h since version 2.0.0
// Check for SCE_PSPNET_RESOLVER_NTOA_BUFSIZE_MAX definition
// and define when needed for compatibility.
#ifndef SCE_PSPNET_RESOLVER_NTOA_BUFSIZE_MAX
#	define SCE_PSPNET_RESOLVER_NTOA_BUFSIZE_MAX 768
#endif

using namespace std; // memset used without :: in FD_SET

#define HK_PSP_INVALID_SOCKET (-1)
#define HK_PSP_SOCKET_ERROR (-1)

#define HK_PSP_WARN(id, msg, errno) \
	{\
		hkString errStr;\
		errStr.printf("0x%x", errno);\
		HK_WARN(id, msg << errStr);\
	}
#define HK_PSP_REPORT(msg, errno) \
	{\
		hkString errStr;\
		errStr.printf("0x%x", errno);\
		HK_REPORT(msg << errStr);\
	}

#define HK_PSPNET_POOLSIZE (128 * 1024)
#define HK_CALLOUT_TPL 40
#define HK_NETINTR_TPL 40
#define HK_SCE_APCTL_HANDLER_STACKSIZE (1024 * 1)
#define HK_SCE_APCTL_STACKSIZE (SCE_NET_APCTL_LEAST_STACK_SIZE + HK_SCE_APCTL_HANDLER_STACKSIZE)
#define HK_SCE_APCTL_PRIO 48
#define HK_RESOLVER_TIMEOUT (5 * 1000 * 1000)
#define HK_RESOLVER_RETRY 5
#define HK_AP_DIALOG_DUMMY_WAIT_TIME (1000 * 1000)

#define HK_PSP_DEVKIT_PATH "host0:/usr/local/psp/devkit/"
#define HK_PSP_MODULE_PATH HK_PSP_DEVKIT_PATH "module/"
#define HK_PSP_PSPNET_AP_DIALOG_DUMMY_PRX HK_PSP_MODULE_PATH "pspnet_ap_dialog_dummy.prx"

#define HK_PSP_MAX_TCPCB_NUM 20

namespace hkPspSocketContext
{
	enum
	{
		HK_PSP_APCTL_FLAG_CONNECTED = 0x01,
		HK_PSP_APCTL_FLAG_DISCONNECTED = 0x02
	};
	static int sPspApctlFlag;
	static int sPspApctrlHandlerID;
	static SceUID sPspNetApDialogDummyModID = -1;

	static int loadDialogDummyModule()
	{
		int ret;
		int mresult;

		ret = ::sceKernelLoadModule(HK_PSP_PSPNET_AP_DIALOG_DUMMY_PRX, 0, NULL);
		if( SCE_ERROR_ISSUCCEEDED(ret) )
		{
			sPspNetApDialogDummyModID = SceUID(ret);
			ret = ::sceKernelStartModule(sPspNetApDialogDummyModID, 0, 0, &mresult, NULL);
			if( SCE_ERROR_ISFAILED(ret) )
			{
				::sceKernelUnloadModule(sPspNetApDialogDummyModID);
				sPspNetApDialogDummyModID = -1;
			}
		}
		return ret;
	}

	static int unloadDialogDummyModule()
	{
		int ret = 0;
		if( sPspNetApDialogDummyModID != -1 )
		{
			ret = ::sceKernelStopModule(sPspNetApDialogDummyModID, 0, NULL, NULL, NULL);
		}
		if ( SCE_ERROR_ISSUCCEEDED(ret) )
		{
			::sceKernelUnloadModule(sPspNetApDialogDummyModID);
			sPspNetApDialogDummyModID = -1;
		}
		return ret;
	}

	int loadPspNetworkModules()
	{
		int ret = 0;

		//HK_REPORT("Load SCE_UTILITY_MODULE_NET_COMMON.");
		ret = sceUtilityLoadModule(SCE_UTILITY_MODULE_NET_COMMON);
		if( SCE_ERROR_ISFAILED(ret) )
		{
			HK_PSP_WARN(0, "sceUtilityLoadModule(SCE_UTILITY_MODULE_NET_COMMON) failed, ", ret);
			return ret;
		}

		//HK_REPORT("Load SCE_UTILITY_MODULE_NET_INET.");
		ret = sceUtilityLoadModule(SCE_UTILITY_MODULE_NET_INET);
		if( SCE_ERROR_ISFAILED(ret) )
		{
			HK_PSP_WARN(0, "sceUtilityLoadModule(SCE_UTILITY_MODULE_NET_INET) failed, ", ret);
			return ret;
		}

		//HK_REPORT("Load pspnet_ap_dialog_dummy.prx.");
		// Load pspnet_ap_dialog_dummy.prx
		ret = loadDialogDummyModule();
		if( SCE_ERROR_ISFAILED(ret) )
		{
			HK_PSP_WARN(0, "sceKernelLoadModule(HK_PSP_PSPNET_AP_DIALOG_DUMMY_PRX) failed, ", ret);
		}

		return ret;
	}

	int unloadPspNetworkModules()
	{
		hkString out;
		int ret = 0;

		// Unload pspnet_ap_dialog_dummy.prx
		ret = unloadDialogDummyModule();
		if( SCE_ERROR_ISFAILED(ret) )
		{
			HK_PSP_WARN(0, "sceKernelUnloadModule(HK_PSP_PSPNET_AP_DIALOG_DUMMY_PRX) failed, ", ret);
			return ret;
		}

		ret = sceUtilityUnloadModule(SCE_UTILITY_MODULE_NET_INET);
		if( SCE_ERROR_ISFAILED(ret) )
		{
			HK_PSP_WARN(0, "sceUtilityUnloadModule(SCE_UTILITY_MODULE_NET_INET) failed, ", ret);
			return ret;
		}

		ret = sceUtilityUnloadModule(SCE_UTILITY_MODULE_NET_COMMON);
		if( SCE_ERROR_ISFAILED(ret) )
		{
			HK_PSP_WARN(0, "sceUtilityUnloadModule(SCE_UTILITY_MODULE_NET_COMMON) failed, ", ret);
		}

		return ret;
	}

	static void pspApctlHandler(int prevState, int newState, int event, int errorCode, void *arg)
	{
		(void)prevState;
		(void)arg;

		if( newState == SCE_NET_APCTL_STATE_IPObtained )
		{
			sPspApctlFlag |= HK_PSP_APCTL_FLAG_CONNECTED;
		}
		else
		{
			if( newState == SCE_NET_APCTL_STATE_Disconnected )
			{
				if( event == SCE_NET_APCTL_EVENT_DISCONNECT_REQ )
				{
					sPspApctlFlag |= HK_PSP_APCTL_FLAG_DISCONNECTED;
				}
				if( (sPspApctlFlag & HK_PSP_APCTL_FLAG_CONNECTED)
					&& event == SCE_NET_APCTL_EVENT_ERROR )
				{
					HK_PSP_WARN(0, "Error happened while connecting or disconnecting, ", errorCode);
				}
				sPspApctlFlag &= ~HK_PSP_APCTL_FLAG_CONNECTED;
			}
		}
	}

#	define HK_PSP_LOAD_CONF(ID, CODE, ENTRY) \
	{ \
		int ret = ::sceUtilityGetNetParam(ID, CODE, ENTRY); \
		if (SCE_ERROR_ISFAILED(ret)) \
		{ \
			HK_PSP_WARN(0, "sceUtilityGetNetParam("#CODE"), ", ret); \
			return ret; \
		} \
	}

	static int loadConfiguration(const char* confName, struct SceNetApDialogDummyParam& apConfParamOut )
	{
		union SceUtilityNetParamEntry entry;
		int confID;
		int ret;

		if (confName && confName[0])
		{
			confID = -1;
			do
			{
				ret = sceUtilityGetNetParam(++confID, SCE_UTILITY_NET_PARAM_CODE_CNF_NAME, &entry);
			} while (SCE_ERROR_ISSUCCEEDED(ret) && (hkString::strCmp(entry.cnf_name, confName) != 0));

			if ( SCE_ERROR_ISSUCCEEDED(ret) )
			{
				HK_REPORT("Configuration ID:" << confID << "\nConfiguration name: " << entry.cnf_name);
			}
			else
			{
				HK_PSP_WARN(0, "sceUtilityGetNetParam() failed, ", ret);
				return ret;
			}
		}
		else
		{
			ret = sceUtilityGetNetParamLatestID(&confID);
			if ( ret < 0 )
			{
				HK_PSP_WARN(0, "sceUtilityGetNetParamLatestID() failed, ", ret);
				return ret;
			}
		}
		/* set */
		hkString::memSet(&apConfParamOut, 0, sizeof(struct SceNetApDialogDummyParam));

		HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_SSID, &entry);
		HK_REPORT("SSID: " << entry.ssid);
		hkString::strCpy(apConfParamOut.ssid, entry.ssid);

		HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_AUTH_PROTO, &entry);
		apConfParamOut.auth_proto = entry.auth_proto;

		if (apConfParamOut.auth_proto == SCE_UTILITY_NET_PARAM_AUTH_PROTO_WEP64
			|| apConfParamOut.auth_proto == SCE_UTILITY_NET_PARAM_AUTH_PROTO_WEP128)
		{
			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_WEP_KEY, &entry);
			hkString::strCpy(apConfParamOut.wep_key, entry.wep_key);
		}

		HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_HOW_TO_SET_IP, &entry);
		apConfParamOut.how_to_set_ip = entry.how_to_set_ip;

		if (apConfParamOut.how_to_set_ip == SCE_UTILITY_NET_PARAM_HOW_TO_SET_IP_STATIC)
		{
			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_IP_ADDRESS, &entry);
			hkString::strCpy(apConfParamOut.ip_opt.static_ip.ip_address, entry.ip_address);

			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_NETMASK, &entry);
			hkString::strCpy(apConfParamOut.ip_opt.static_ip.netmask, entry.netmask);

			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_DEFAULT_ROUTE, &entry);
			hkString::strCpy(apConfParamOut.ip_opt.static_ip.default_route, entry.default_route);
		}

		if (apConfParamOut.how_to_set_ip == SCE_UTILITY_NET_PARAM_HOW_TO_SET_IP_PPPOE)
		{
			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_AUTH_NAME, &entry);
			hkString::strCpy(apConfParamOut.ip_opt.pppoe.auth_name, entry.auth_name);

			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_AUTH_KEY, &entry);
			hkString::strCpy(apConfParamOut.ip_opt.pppoe.auth_key, entry.auth_key);
		}

		HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_DNS_FLAG, &entry);
		apConfParamOut.dns_flag = entry.dns_flag;

		if (apConfParamOut.dns_flag == SCE_UTILITY_NET_PARAM_DNS_FLAG_MANUAL)
		{
			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_PRIMARY_DNS, &entry);
			hkString::strCpy(apConfParamOut.primary_dns, entry.primary_dns);

			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_SECONDARY_DNS, &entry);
			hkString::strCpy(apConfParamOut.secondary_dns, entry.secondary_dns);
		}

		HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_HTTP_PROXY_FLAG, &entry);
		apConfParamOut.http_proxy_flag = entry.http_proxy_flag;

		if (apConfParamOut.http_proxy_flag == SCE_UTILITY_NET_PARAM_HTTP_PROXY_FLAG_ON)
		{
			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_HTTP_PROXY_SERVER, &entry);
			hkString::strCpy(apConfParamOut.http_proxy_server, entry.http_proxy_server);

			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_HTTP_PROXY_PORT, &entry);
			apConfParamOut.http_proxy_port = entry.http_proxy_port;
		}

		HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_8021X_TYPE, &entry);
		apConfParamOut.auth_8021x_type = entry.auth_8021x_type;

		if (apConfParamOut.auth_8021x_type == SCE_UTILITY_NET_PARAM_8021X_EAP_MD5)
		{
			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_8021X_AUTH_NAME, &entry);
			hkString::strCpy(apConfParamOut.auth_8021x_opt.eap_md5.auth_name, entry.auth_8021x_auth_name);

			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_8021X_AUTH_KEY, &entry);
			hkString::strCpy(apConfParamOut.auth_8021x_opt.eap_md5.auth_key, entry.auth_8021x_auth_key);
		}
		if (apConfParamOut.auth_proto == SCE_UTILITY_NET_PARAM_AUTH_PROTO_WPAPSK_TKIP
			|| apConfParamOut.auth_proto == SCE_UTILITY_NET_PARAM_AUTH_PROTO_WPAPSK_AES)
		{
			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_WPA_KEY_TYPE, &entry);
			apConfParamOut.wpa_key_type = entry.wpa_key_type;

			HK_PSP_LOAD_CONF(confID, SCE_UTILITY_NET_PARAM_CODE_WPA_KEY, &entry);
			hkString::strCpy(apConfParamOut.wpa_key, entry.wpa_key);
		}

		return confID;
	}

	static void displayPspNetworkStatus()
	{
		const char *const tcpstates[] = {
			"CLOSED",	"LISTEN",	"SYN_SENT",	"SYN_RCVD",
				"ESTABLISHED",	"CLOSE_WAIT",	"FIN_WAIT_1",	"CLOSING",
				"LAST_ACK",	"FIN_WAIT_2",	"TIME_WAIT",
		};
		int num, n;
		struct SceNetInetTcpcbstat *ts;
		char buf[sizeof("XXX.XXX.XXX.XXX") + 1];
		hkString out;
		hkString printOut;
		out = "\n";
		out += "Active Internet connections (including servers)\n";
		printOut.printf("%-5s %-6s %-6s %-22s %-22s %s\n",
			"Proto", "Recv-Q", "Send-Q", "Local Address", "Foreign Address", "State");
		out += printOut;

		/* tcpcb */
		struct SceNetInetTcpcbstat thead[HK_PSP_MAX_TCPCB_NUM];
		ts = thead;
		num = HK_PSP_MAX_TCPCB_NUM * sizeof(struct SceNetInetTcpcbstat);
		::sceNetInetGetTcpcbstat(&num, ts);
		if(num != 0)
		{
			for (; ts != NULL; ts = ts->next) {
				printOut.printf("%-5s %-6d %-6d ",
					"tcp",
					ts->ts_so_rcv_sb_cc,
					ts->ts_so_snd_sb_cc);
				out += printOut;
				n = 0;
				if (ts->ts_inp_laddr.s_addr == SCE_NET_INET_INADDR_ANY)
				{
					++n;
					out += "*";
				}
				else
				{
					printOut.printf("%s", sceNetInetInetNtop(SCE_NET_INET_AF_INET, &ts->ts_inp_laddr, buf, sizeof(buf)));
					n += printOut.getLength();
					out += printOut;
				}
				if (ts->ts_inp_lport == 0)
				{
					n += 2;
					out += ":*";
				}
				else
				{
					printOut.printf(":%d", sceNetNtohs(ts->ts_inp_lport));
					n += printOut.getLength();
					out += printOut;
				}
				printOut.printf("%*s ", 22 - n, "");
				out += printOut;

				n = 0;
				if (ts->ts_inp_faddr.s_addr == SCE_NET_INET_INADDR_ANY)
				{
					n += 1;
					out += "*";
				}
				else
				{
					printOut.printf("%s", sceNetInetInetNtop(SCE_NET_INET_AF_INET, &ts->ts_inp_faddr, buf, sizeof(buf)));
					n += printOut.getLength();
					out += printOut;
				}
				if (ts->ts_inp_fport == 0)
				{
					n += 2;
					out += ":*";
				}
				else
				{
					printOut.printf(":%d", sceNetNtohs(ts->ts_inp_fport));
					n += printOut.getLength();
					out += printOut;
				}
				printOut.printf("%*s ", 22 - n, "");
				out += printOut;

				if (ts->ts_t_state < 0 || ts->ts_t_state >= SCE_NET_INET_TCP_NSTATES)
					printOut.printf("%d", ts->ts_t_state);
				else
					printOut.printf("%s", tcpstates[ts->ts_t_state]);
				out += printOut;
				out += "\n";
			}
		}
		HK_REPORT(out);
	}

} // namespace hkPspSocketContext

void HK_CALL hkPspNetworkInit()
{
	struct SceNetApDialogDummyParam apDialogDummyParam;
	char confName[SCE_UTILITY_NET_PARAM_CNF_NAME_LEN];

	if (SCE_ERROR_ISFAILED(hkPspSocketContext::loadPspNetworkModules()))
	{
		HK_ASSERT2(0, false, "Failed to load network libraries.");
		return;
	}

	// Use a ./pspnetwork.conf with similar to the following to allow
	// you to change the havok net usage without rebuilding

	// look for pspnetwork.conf file in current working dir
	// and set network parameters
	{
		hkIstream confFile("pspnetwork.conf");

		if (confFile.isOk() && confFile.getStreamReader()->seekTellSupported())
		{
			confFile.getStreamReader()->seek(0, hkStreamReader::STREAM_END);
			int len = confFile.getStreamReader()->tell();
			confFile.getStreamReader()->seek(0, hkStreamReader::STREAM_SET);
			if (len > 0 && len < SCE_UTILITY_NET_PARAM_CNF_NAME_LEN)
			{
				confFile.read(confName, len);
				confName[len] = '\0'; // null terminate.
				HK_REPORT("Read Havok network settings from ./pspnetwork.conf : " << confName);
			}
		}
		else
		{
			HK_REPORT("Try to use last used network configuration.");
			confName[0] = 0;
		}
		hkPspSocketContext::loadConfiguration(confName, apDialogDummyParam);
	}
	hkPspSocketContext::sPspApctrlHandlerID = -1;

	if ( SCE_ERROR_ISSUCCEEDED(::sceNetInit(HK_PSPNET_POOLSIZE, HK_CALLOUT_TPL, 0, HK_NETINTR_TPL, 0))
		&& SCE_ERROR_ISSUCCEEDED(::sceNetInetInit())
		&& SCE_ERROR_ISSUCCEEDED(::sceNetResolverInit())
		&& SCE_ERROR_ISSUCCEEDED(::sceNetApctlInit(HK_SCE_APCTL_STACKSIZE, HK_SCE_APCTL_PRIO))
		&& ::sceWlanGetSwitchState() == SCE_WLAN_SWITCH_STATE_ON
		&& SCE_ERROR_ISSUCCEEDED(::sceNetApDialogDummyInit()))
	{
		hkPspSocketContext::sPspApctlFlag = 0;
		hkPspSocketContext::sPspApctrlHandlerID = ::sceNetApctlAddHandler(hkPspSocketContext::pspApctlHandler, NULL);
		HK_ASSERT2(0, SCE_ERROR_ISSUCCEEDED(hkPspSocketContext::sPspApctrlHandlerID), "Cannot setup application handler for network.");
		int res = ::sceNetApDialogDummyConnect(&apDialogDummyParam);
		if (SCE_ERROR_ISFAILED(res))
		{
			HK_PSP_WARN(0, "Failed to make an AP network connection with " << (confName[0] ? confName : "last used") << " configuration. " << "Make sure the wireless LAN switch has been turned off. ", res);
		}
		struct SceNetApDialogDummyStateInfo apDialogDummyState;
		do
		{
			res = ::sceNetApDialogDummyGetState(&apDialogDummyState);
			if (SCE_ERROR_ISFAILED(res))
			{
				HK_PSP_REPORT("Failed to join network or obtain IP address with " << (confName[0] ? confName : "last used") << " configuration, ", apDialogDummyState.error_code);
				break;
			}
			else
			{
				if ( apDialogDummyState.state != SceNetApDialogDummyState_Connected
					&& apDialogDummyState.state != SceNetApDialogDummyState_Disconnected )
				{
					::sceKernelDelayThread(2 * HK_AP_DIALOG_DUMMY_WAIT_TIME);
				}
			}
		} while( apDialogDummyState.state != SceNetApDialogDummyState_Connected
				&& apDialogDummyState.state != SceNetApDialogDummyState_Disconnected );

		union SceNetApctlInfo apctlInfo;
		res = ::sceNetApctlGetInfo(SCE_NET_APCTL_INFO_IP_ADDRESS, &apctlInfo);
		if (SCE_ERROR_ISFAILED(res))
		{
			HK_PSP_REPORT("Failed to obtain IP address, ", res);
		}
		else
		{
			HK_REPORT("Obtained IP address: " << apctlInfo.ip_address);
		}
	}
	else
	{
		HK_PSP_WARN(0, "Network initialization has failed. Make sure that wireless LAN switch has been turned on. ", ::sceNetInetGetErrno());
	}
}

void HK_CALL hkPspNetworkQuit()
{
	if( hkPspSocketContext::sPspApctlFlag & hkPspSocketContext::HK_PSP_APCTL_FLAG_CONNECTED )
	{
		hkPspSocketContext::sPspApctlFlag &= ~hkPspSocketContext::HK_PSP_APCTL_FLAG_DISCONNECTED;
		if( SCE_ERROR_ISFAILED(::sceNetApctlDisconnect()) )
		{
			HK_PSP_WARN(0, "Error attempting to disconnect, ", ::sceNetInetGetErrno());
		}
		while((hkPspSocketContext::sPspApctlFlag & hkPspSocketContext::HK_PSP_APCTL_FLAG_DISCONNECTED) == 0)
		{
			::sceKernelDelayThread(HK_AP_DIALOG_DUMMY_WAIT_TIME);
		}
	}

	::sceNetApDialogDummyTerm();
	if( 0 <= hkPspSocketContext::sPspApctrlHandlerID )
		::sceNetApctlDelHandler(hkPspSocketContext::sPspApctrlHandlerID);
	::sceNetApctlTerm();
	::sceNetResolverTerm();
	::sceNetInetTerm();
	::sceNetTerm();

	hkPspSocketContext::unloadPspNetworkModules();

	HK_REPORT("Network connections are closed down and libraries are unloaded.");
}

hkPspSocket::hkPspSocket(socket_t s)
: m_socket(s)
{
	if ( m_socket == HK_PSP_INVALID_SOCKET )
	{
		createSocket();
	}
}

hkBool hkPspSocket::isOk() const
{
	return m_socket != HK_PSP_INVALID_SOCKET;
}

void hkPspSocket::close()
{
	if( m_socket != HK_PSP_INVALID_SOCKET )
	{
		// Close both the reading and writing of socket sid
		if( SCE_ERROR_ISFAILED(::sceNetInetShutdown(m_socket, SCE_NET_INET_SHUT_RDWR)) )
		{
			HK_PSP_WARN(0, "sceNetInetShutdown() failed, ", ::sceNetInetGetErrno());
		}
		::sceNetInetClose(m_socket);
		m_socket = HK_PSP_INVALID_SOCKET;
	}
}

hkResult hkPspSocket::createSocket()
{
	close();
	m_socket = static_cast<socket_t>( ::sceNetInetSocket(SCE_NET_INET_AF_INET, SCE_NET_INET_SOCK_STREAM, 0) );
	if(m_socket == HK_PSP_INVALID_SOCKET)
	{
		HK_WARN(0x3b98e883, "Error creating socket!");
		return HK_FAILURE;
	}
	return HK_SUCCESS;
}

hkPspSocket::~hkPspSocket()
{
	close();
}

int hkPspSocket::read(void* buf, int nbytes)
{
	if(m_socket != HK_PSP_INVALID_SOCKET)
	{
		int n = ::sceNetInetRecv(m_socket, static_cast<char*>(buf), nbytes, 0);
		if (n <= 0 || n == HK_PSP_SOCKET_ERROR)
		{
			HK_WARN(0x4bb09a0f, "Read fail! Was the receiving end of socket closed?");
			close();	
		}
		else
			return n;
	}
	return 0;
}

int hkPspSocket::write( const void* buf, int nbytes)
{
	if(m_socket != HK_PSP_INVALID_SOCKET)
	{
		int n = ::sceNetInetSend(m_socket, static_cast<const char*>(buf), nbytes, 0);
		if(n <= 0 || n == HK_PSP_SOCKET_ERROR )
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

hkResult hkPspSocket::connect(const char* servername, int portNumber)
{
	// find the address of the server
	struct SceNetInetSockaddrIn server;
	{
		hkString::memSet(&server,0,sizeof(server));
		server.sin_family = SCE_NET_INET_AF_INET;
		server.sin_addr.s_addr = ::sceNetInetInetAddr(servername);
		if( (unsigned int)-1 == server.sin_addr.s_addr )
		{
			// hostname lookup
			int resolverID;
			char resNtoA[SCE_PSPNET_RESOLVER_NTOA_BUFSIZE_MAX];
			SceSize bufSize = sizeof(resNtoA);
			if( ::sceNetResolverCreate(&resolverID, resNtoA, bufSize) < 0 )
			{
				return HK_FAILURE;
			}
			if( ::sceNetResolverStartNtoA(resolverID, servername, &server.sin_addr, HK_RESOLVER_TIMEOUT, HK_RESOLVER_RETRY) < 0 )
			{
				return HK_FAILURE;
			}
			::sceNetResolverDelete(resolverID);
		}
		server.sin_port = ::sceNetHtons(portNumber);
	}

	if( m_socket == HK_PSP_INVALID_SOCKET )
	{
		if (createSocket() != HK_SUCCESS )
		{
			return HK_FAILURE;
		}
	}

	if(::sceNetInetConnect(m_socket, (const struct SceNetInetSockaddr*)(&server), sizeof(server)) == HK_PSP_SOCKET_ERROR)
	{
		HK_WARN(0x46d25e96, "Cannot connect to server!");
		close();
		return HK_FAILURE;
	}
	return HK_SUCCESS;
}

hkResult hkPspSocket::listen(int port)
{
	HK_REPORT("hkPspSocket::listen(), socket == "<< m_socket<<", port == " << port);
	if( m_socket == HK_PSP_INVALID_SOCKET )
	{
		return HK_FAILURE;
	}

	// bind to specified port
	struct SceNetInetSockaddrIn local;
	local.sin_family = SCE_NET_INET_AF_INET;
	local.sin_addr.s_addr = SCE_NET_INET_INADDR_ANY;
	local.sin_port = ::sceNetHtons( port );

	union
	{
		int reuseAddress;
		char data[1];
	} option;
	option.reuseAddress = 1;
	if( ::sceNetInetSetsockopt( m_socket, SCE_NET_INET_SOL_SOCKET, SCE_NET_INET_SO_REUSEADDR, &option.data[0], sizeof(option) ) < 0 )
	{
		HK_PSP_REPORT("Cannot set socket option - REUSEADDR, ", ::sceNetInetGetErrno());
	}

	if( ::sceNetInetBind( m_socket, (const struct SceNetInetSockaddr*)(&local), sizeof(local) ) < 0 )
	{
		HK_PSP_WARN(0x661cf90d, "Error binding to socket! ", ::sceNetInetGetErrno());
		close();
		return HK_FAILURE;
	}

	// put the server socket into a listening state
	if( ::sceNetInetListen( m_socket, 2 ) < 0 )
	{
		HK_PSP_WARN(0x14e1a0f9, "Error listening to socket! ", ::sceNetInetGetErrno());
		close();
		return HK_FAILURE;
	}

	// Display network info.
	hkPspSocketContext::displayPspNetworkStatus();
	return HK_SUCCESS;
}

hkSocket* hkPspSocket::pollForNewClient()
{
	HK_ASSERT2( 0x73993156, m_socket != HK_PSP_INVALID_SOCKET, "");

	// poll the listener socket for new client sockets
	if( m_socket != HK_PSP_INVALID_SOCKET )
	{
		SceNetInetFdSet readFds;
		SceNetInetFD_ZERO(&readFds);
		SceNetInetFD_SET(m_socket, &readFds);

		SceNetInetFdSet exceptFds;
		SceNetInetFD_ZERO(&exceptFds);
		SceNetInetFD_SET(m_socket, &exceptFds);

		// see if there is and client trying to connect

		socket_t maxFd = m_socket + 1;
		SceNetInetTimeval t = {0, 0};	// no wait time -- i.e. non blocking select
		int numHits = ::sceNetInetSelect(maxFd, &readFds, HK_NULL, &exceptFds, &t); // Changed from ::select to ::socketselect in 0.5.0

		if( (numHits > 0) && SceNetInetFD_ISSET(m_socket, &readFds) )
		{
			struct SceNetInetSockaddrIn from;
			SceNetInetSocklen_t fromlen = sizeof(from);

			socket_t s = static_cast<socket_t>( ::sceNetInetAccept(m_socket, (struct SceNetInetSockaddr*)&from, &fromlen) );

			hkString rs;
			rs.printf("Socket got connection from [%lx:%d]\n", from.sin_addr, ::sceNetNtohs(from.sin_port));
			HK_REPORT(rs);

			if( s == HK_PSP_INVALID_SOCKET )
			{
				HK_PSP_WARN(0x774fad25, "Error accepting a connection! ", ::sceNetInetGetErrno());
			}
			else
			{
				// Add the current connection to the servers list
				unsigned int optval = 1;
				::sceNetInetSetsockopt(s, SCE_NET_INET_IPPROTO_TCP, SCE_NET_INET_TCP_NODELAY, (char *)&optval, sizeof (unsigned int));

				return new hkPspSocket(s);
			}
		}
		else if(numHits == HK_PSP_SOCKET_ERROR)
		{
			HK_PSP_WARN(0x3fe16171, "select() failed, ", ::sceNetInetGetErrno());
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
