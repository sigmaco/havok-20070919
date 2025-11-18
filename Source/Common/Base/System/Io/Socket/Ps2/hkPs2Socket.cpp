/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/Ps2/hkPs2Socket.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

// Paths to our setup on memory card 0. Setup by netgui2, encoded.
const char* hkPs2Socket::s_combination = "Combination1";
const char* hkPs2Socket::s_netDbAbsolutePath = "mc0:/BWNETCNF/BWNETCNF";


hkPs2Socket::hkPs2Socket(int s)
	: m_socket(s)
{
	if ( m_socket == INVALID_SOCKET )
	{
		createSocket();
	}
} 

hkBool hkPs2Socket::isOk() const
{
	return m_socket != INVALID_SOCKET;
}

hkPs2Socket::~hkPs2Socket()
{
	close();
}

#if defined(HK_PS2_USING_EENET_SOCKETS) && defined(HK_PS2_USING_INET_SOCKETS)

#pragma warning("You must define only one of EENet or INet usage in hkPs2Socket.h")

#elif defined(HK_PS2_USING_INET_SOCKETS)

#	include <Common/Base/System/Io/Socket/Ps2/hkPs2InetSocket.cxx>

#elif defined(HK_PS2_USING_EENET_SOCKETS)

#	include <Common/Base/System/Io/Socket/Ps2/hkPs2EENetSocket.cxx>

#else

#pragma warning("You must define either EENet or INet usage in hkPs2Socket.h")

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
