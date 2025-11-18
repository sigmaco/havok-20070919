/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_BASE_PSP_SOCKET_H
#define HK_BASE_PSP_SOCKET_H

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/hkSocket.h>

class hkPspSocket : public hkSocket
{
public:
	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS );

	typedef int socket_t;

	hkPspSocket(socket_t s=socket_t(-1));

	virtual ~hkPspSocket();

	virtual hkBool isOk() const;

	virtual void close();

	virtual int read( void* buf, int nbytes);

	virtual int write( const void* buf, int nbytes);

	// client

	virtual hkResult connect(const char* servername, int portNumber);


	// server

	hkResult listen(int port);
	hkSocket* pollForNewClient();

protected:

	hkResult createSocket();

	socket_t m_socket;
};

/// Set up psp network. Set hkSocket::s_platformNetInit to HK_NULL to prevent this being called
void HK_CALL hkPspNetworkInit();

/// Set up psp network. Set hkSocket::s_platformNetQuit to HK_NULL to prevent this being called
void HK_CALL hkPspNetworkQuit();

#endif // HK_BASE_PSP_SOCKET_H


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
