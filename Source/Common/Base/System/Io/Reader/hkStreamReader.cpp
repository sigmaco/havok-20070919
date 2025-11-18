/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Reader/hkStreamReader.h>

int hkStreamReader::skip(int nbytes)
{
	char buf[512];
	int bytesLeft = nbytes;
	while( bytesLeft )
	{
		int n = read(buf, bytesLeft > hkSizeOf(buf) ? hkSizeOf(buf) : bytesLeft );
		if( n == 0 )
		{
			break;
		}

		bytesLeft -= n;
	}
	return nbytes - bytesLeft;
}

int hkStreamReader::readChar()
{
	char c;
	return read(&c,1) ? c : -1;
}

hkBool hkStreamReader::markSupported() const
{
	return false;
}

hkResult hkStreamReader::setMark(int markLimit)
{
	HK_ASSERT(0x37068014, 0);
	return HK_FAILURE;
}

hkResult hkStreamReader::rewindToMark()
{
    HK_ASSERT(0x61d14f0a, 0);
	return HK_FAILURE;
}

hkBool hkStreamReader::seekTellSupported() const
{
	return false;
}

hkResult hkStreamReader::seek(int offset, SeekWhence whence)
{
	HK_ASSERT(0x7a359c55, 0);
	return HK_FAILURE;
}

int hkStreamReader::tell() const
{
	HK_ASSERT(0x612f894c, 0);
	return -1;
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
