/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Writer/Crc32/hkCrc32StreamWriter.h>

hkCrc32StreamWriter::hkCrc32StreamWriter(hkUint32 startCrc)
	: m_crc32(startCrc ^ hkUint32(-1))
{
}

hkBool hkCrc32StreamWriter::isOk() const
{
	return true;
}

inline hkUint32 calcPermute(hkUint32 p)
{
	for( int i = 0; i < 8; ++i )
	{
		if( p & 1 )
		{
			p = 0xedb88320 ^ (p >> 1);
		}
		else
		{
			p = p >> 1;
		}
	}
	return p;
}

int hkCrc32StreamWriter::write(const void* ptr, int nbytes)
{
	const hkUint8* buf = static_cast<const hkUint8*>(ptr);
	hkUint32 crc = m_crc32;
	for( int n = 0; n < nbytes; ++n)
	{
		hkUint32 permute = calcPermute( (crc ^ buf[n]) & 0xff );
		crc = permute ^ (crc >> 8);
	}
	m_crc32 = crc;
	return nbytes;
}

hkUint32 hkCrc32StreamWriter::getCrc32() const
{
	return m_crc32 ^ hkUint32(-1);
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
