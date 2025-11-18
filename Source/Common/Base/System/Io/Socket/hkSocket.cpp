/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Socket/hkSocket.h>

#if defined(HK_PLATFORM_PS2)

// PS2 (Inet and EEnet supported)
#	include <Common/Base/System/Io/Socket/Ps2/hkPs2Socket.h>
	static hkSocket* HK_CALL hkSocketCreate()
	{
		return new hkPs2Socket();
	}

	void (HK_CALL *hkSocket::s_platformNetInit)() = hkPs2NetworkInit;
	void (HK_CALL *hkSocket::s_platformNetQuit)() = hkPs2NetworkQuit;

#elif defined(HK_PLATFORM_PSP)

// PSP not currently supported 
#	include <Common/Base/System/Io/Socket/Psp/hkPspSocket.h>
	static hkSocket* HK_CALL hkSocketCreate()
	{
		return new hkPspSocket();
	}

	void (HK_CALL *hkSocket::s_platformNetInit)() = hkPspNetworkInit;
	void (HK_CALL *hkSocket::s_platformNetQuit)() = hkPspNetworkQuit;
	
#elif defined(HK_PLATFORM_PS3)

// PS3 socket implementation
#	include <Common/Base/System/Io/Socket/Ps3/hkPs3Socket.h>
	static hkSocket* HK_CALL hkSocketCreate()
	{
		return new hkPs3Socket();
	}

	void (HK_CALL *hkSocket::s_platformNetInit)() = hkPs3NetworkInit;
	void (HK_CALL *hkSocket::s_platformNetQuit)() = hkPs3NetworkQuit;

#elif defined(HK_PLATFORM_GC)

// GameCube not supported 
	static hkSocket* HK_CALL hkSocketCreate()
	{
		HK_WARN(0x1f65b352, "No socket implementation for this platform");
		return HK_NULL;
	}

	void (HK_CALL *hkSocket::s_platformNetInit)() = HK_NULL;
	void (HK_CALL *hkSocket::s_platformNetQuit)() = HK_NULL;

#else

// General BSD socket support (UNIX, Windows, Mac, Xbox etc)
#	include <Common/Base/System/Io/Socket/Bsd/hkBsdSocket.h>
	static hkSocket* HK_CALL hkSocketCreate()
	{
		return new hkBsdSocket();
	}

	void (HK_CALL *hkSocket::s_platformNetInit)() = hkBsdNetworkInit;
	void (HK_CALL *hkSocket::s_platformNetQuit)() = hkBsdNetworkQuit;

#endif

hkBool hkSocket::s_platformNetInitialized = false;

hkSocket* (HK_CALL *hkSocket::create)() = hkSocketCreate;

hkSocket::hkSocket()
{
	m_reader.m_socket = this;
	m_writer.m_socket = this;

	if (s_platformNetInitialized == false && s_platformNetInit)
	{
		s_platformNetInit();
		s_platformNetInitialized = true;
	}
}

int hkSocket::ReaderAdapter::read( void* buf, int nbytes )
{
	char* cbuf = static_cast<char*>(buf);
	int size = 0;
	while( size < nbytes )
	{
		int r = m_socket->read(cbuf+size, nbytes-size);
		size += r;
		if( r == 0 )
		{
			return size;
		}
	}
	return nbytes;
}

hkBool hkSocket::ReaderAdapter::isOk() const
{
	return m_socket->isOk();
}

int hkSocket::WriterAdapter::write( const void* buf, int nbytes )
{
	const char* cbuf = static_cast<const char*>(buf);
	int size = 0;
	while( size < nbytes )
	{
		int w = m_socket->write(cbuf+size, nbytes-size);
		size += w;
		if( w == 0 )
		{
			return size;
		}
	}
	return nbytes;
	
}

hkBool hkSocket::WriterAdapter::isOk() const
{
	return m_socket->isOk();
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
