/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Writer/Buffered/hkBufferedStreamWriter.h>

static const int BUFFER_ALIGNMENT = 64;
static const int BUFFER_BLOCK_SIZE = 512;

#define IS_POWER_OF_2(A) (((A)&((A)-1))==0)

HK_COMPILE_TIME_ASSERT( IS_POWER_OF_2(BUFFER_ALIGNMENT) );
HK_COMPILE_TIME_ASSERT( IS_POWER_OF_2(BUFFER_BLOCK_SIZE) );

hkBufferedStreamWriter::hkBufferedStreamWriter(hkStreamWriter* s, int bufSize)
	:	m_stream(s),
        m_ownBuffer(true)

{
	if (m_stream)
	{
		m_stream->addReference();
	}
	HK_ASSERT2( 0x68c094d2, bufSize % BUFFER_BLOCK_SIZE == 0, "block size needs to be a multiple of " << BUFFER_BLOCK_SIZE );
	m_buf = hkAlignedAllocate<char>( BUFFER_ALIGNMENT, bufSize, HK_MEMORY_CLASS_STREAM );
	m_bufSize = 0;
	m_bufCapacity = bufSize;
}

hkBufferedStreamWriter::hkBufferedStreamWriter(void* mem, int memSize, hkBool memoryIsString )
	:	m_stream(HK_NULL),
		m_buf( static_cast<char*>(mem) ),
		m_bufSize(0),
		m_bufCapacity( memoryIsString ? memSize-1 : memSize ),
        m_ownBuffer(false)
{
	if( memoryIsString )
	{
		hkString::memSet( mem, 0, memSize );
	}
}

hkBufferedStreamWriter::~hkBufferedStreamWriter()
{
	flush();
	if( m_stream )
	{
		m_stream->removeReference();
	}
    if( m_ownBuffer )
    {
        hkAlignedDeallocate<char>(m_buf);
    }
}

int hkBufferedStreamWriter::flushBuffer()
{
	if( m_stream )
	{
		int nbytes = m_bufSize;
		int bytesWritten = 0;
		while( bytesWritten < nbytes )
		{
			int thiswrite = m_stream->write( m_buf + bytesWritten, nbytes - bytesWritten );
			bytesWritten += thiswrite;
			if (thiswrite == 0 )
			{
				return bytesWritten;
			}
		}
		m_bufSize = 0;
		return bytesWritten;
	}
	else
	{
		return 0;
	}
}

int hkBufferedStreamWriter::write(const void* mem, int memSize)
{
	int bytesLeft = memSize;
	int bytesSpare = m_bufCapacity - m_bufSize;
	const char* cmem = static_cast<const char*>(mem);

	while( bytesLeft > bytesSpare ) // while bytes left bigger than buffer
	{
		hkString::memCpy( m_buf+m_bufSize, cmem, bytesSpare );
		cmem += bytesSpare;
		m_bufSize += bytesSpare;
		bytesLeft -= bytesSpare;

		int bytesInBuffer = m_bufSize;
		if( flushBuffer() != bytesInBuffer )
		{
			// didnt do a full write for some reason.
			return memSize - bytesLeft;
		}
		bytesSpare = m_bufCapacity - m_bufSize;
	}

	// bytes left fit into buffer
	hkString::memCpy(m_buf + m_bufSize, cmem, bytesLeft );
	m_bufSize += bytesLeft;
	return memSize;
}

void hkBufferedStreamWriter::flush()
{
	flushBuffer();
	if( m_stream )
	{
		m_stream->flush();
	}
}

hkBool hkBufferedStreamWriter::isOk() const
{
	return m_stream
		? m_stream->isOk()
		: hkBool(m_bufSize != m_bufCapacity);
}

hkBool hkBufferedStreamWriter::seekTellSupported() const
{
	return m_stream
	       ? m_stream->seekTellSupported()
	       : hkBool(true);
}

hkResult hkBufferedStreamWriter::seek(int relOffset, SeekWhence whence)
{
	if( m_stream )
	{
		// forward to stream
		flushBuffer(); //XXX inefficient if range is in buffer
		return m_stream->seek(relOffset,whence);
	}
	else
	{
		// memory stream
		int pos = -1;
		switch(whence)
		{
			case STREAM_SET:
				pos = relOffset;
				break;
			case STREAM_CUR:
				pos = m_bufSize + relOffset;
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
		else if( pos > m_bufCapacity )
		{
			pos = m_bufCapacity;
			ok = HK_FAILURE;
		}
		m_bufSize = pos;
		return ok;
	}
}

int hkBufferedStreamWriter::tell() const
{
	int childPos = m_stream ? m_stream->tell() : 0;
	if( childPos >= 0 )
	{
		return childPos + m_bufSize;
	}
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
