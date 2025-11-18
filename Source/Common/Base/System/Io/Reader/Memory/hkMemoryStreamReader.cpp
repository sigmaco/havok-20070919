/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Reader/Memory/hkMemoryStreamReader.h>

hkMemoryStreamReader::hkMemoryStreamReader(const void* mem, int memSize, MemoryType mt)
	:	m_bufCurrent(0),
		m_bufSize(memSize),
		m_markPos(-1),
		m_memType(mt)
{
	if( m_memType == MEMORY_COPY )
	{
		m_buf = hkAllocate<char>( memSize, HK_MEMORY_CLASS_STREAM );
		hkString::memCpy( m_buf, mem, memSize );
	}
	else
	{
		m_buf = const_cast<char*>(static_cast<const char*>(mem));
	}
}

hkMemoryStreamReader::~hkMemoryStreamReader()
{
	if( m_memType == MEMORY_COPY || m_memType == MEMORY_TAKE )
	{
		hkDeallocate<char>(m_buf);
	}
}

int hkMemoryStreamReader::read(void* buf, int nbytes)
{
    if( isOk() )
    {
        int bytesAvailable = m_bufSize - m_bufCurrent;
        int nRead = nbytes < bytesAvailable ? nbytes : bytesAvailable;

        hkString::memCpy(buf, m_buf+m_bufCurrent, nRead );
        m_bufCurrent += nRead;
        if( nRead == 0 && nbytes != 0 )
        {
            m_bufCurrent = m_bufSize + 1; // past the end
        }

        return nRead;
    }
    return 0;
}

int hkMemoryStreamReader::skip(int nbytes)
{
    if( isOk() )
    {
        int bytesAvailable = m_bufSize - m_bufCurrent;
        int nRead = nbytes < bytesAvailable ? nbytes : bytesAvailable;
        m_bufCurrent += nRead;
        if( nRead == 0 && nbytes != 0 )
        {
            m_bufCurrent = m_bufSize + 1; // past the end
        }
        return nRead;
    }
    return 0;
}

hkBool hkMemoryStreamReader::isOk() const
{
    return m_bufCurrent != m_bufSize + 1;
}

hkBool hkMemoryStreamReader::markSupported() const
{
	return m_bufSize != 0;
}

hkResult hkMemoryStreamReader::setMark(int markLimit)
{
	m_markPos = m_bufCurrent;
	return HK_SUCCESS;
}

hkResult hkMemoryStreamReader::rewindToMark()
{
	if(m_markPos >= 0)
	{
		m_bufCurrent = m_markPos;
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

hkBool hkMemoryStreamReader::seekTellSupported() const
{
	return true;
}

hkResult hkMemoryStreamReader::seek(int relOffset, SeekWhence whence)
{
	int pos = -1;
	switch(whence)
	{
		case STREAM_SET:
			pos = relOffset;
			break;
		case STREAM_CUR:
			pos = m_bufCurrent + relOffset;
			break;
		case STREAM_END:
			pos = m_bufSize - relOffset;
			break;
	}
	hkResult ok = HK_SUCCESS;
	if(	pos < 0 )
	{
		pos = 0;
		ok = HK_FAILURE;
	}
	else if( pos > m_bufSize )
	{
		pos = m_bufSize;
		ok = HK_FAILURE;
	}
	m_bufCurrent = pos;
	return ok;
}

int hkMemoryStreamReader::tell() const
{
	return m_bufCurrent;
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
