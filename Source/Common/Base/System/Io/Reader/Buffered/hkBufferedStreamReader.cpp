/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/Reader/Buffered/hkBufferedStreamReader.h>

static const int BUFFER_ALIGNMENT = 64;
static const int BUFFER_BLOCK_SIZE = 512;

#define IS_POWER_OF_2(A) (((A)&((A)-1))==0)

HK_COMPILE_TIME_ASSERT( IS_POWER_OF_2(BUFFER_ALIGNMENT) );
HK_COMPILE_TIME_ASSERT( IS_POWER_OF_2(BUFFER_BLOCK_SIZE) );

hkBufferedStreamReader::Buffer::Buffer(int cap)
	:	begin( hkAlignedAllocate<char>( BUFFER_ALIGNMENT, cap, HK_MEMORY_CLASS_STREAM ) ),
		current(0),
		size(0),
		capacity(cap),
		markPos(-1),
		markLimit(-1)
{
	HK_ASSERT2( 0x3a82bd7f, cap % BUFFER_BLOCK_SIZE == 0, "block size needs to be a multiple of " << BUFFER_BLOCK_SIZE );
}

hkBufferedStreamReader::Buffer::~Buffer()
{
    hkAlignedDeallocate<char>(begin);
}

hkBufferedStreamReader::hkBufferedStreamReader(hkStreamReader* s, int bufSize)
	:	m_stream(s),
		m_buf(bufSize)

{
	HK_ASSERT( 0x3a82bd80, m_stream != HK_NULL );
	m_stream->addReference();
}


hkBufferedStreamReader::~hkBufferedStreamReader()
{
	m_stream->removeReference();
}

void hkBufferedStreamReader::prepareBufferForRefill()
{
	if( m_buf.markPos < 0 )
	{
		// usual case, no mark set, use the whole buffer
		m_buf.current = 0;
		m_buf.size = 0;
	}
	else if( m_buf.current - m_buf.markPos > m_buf.markLimit )
	{
		// we've gone past the marklimit, destroy the mark
		m_buf.current = 0;
		m_buf.size = 0;
		m_buf.markPos = -1;
		m_buf.markLimit = -1;
	}
	else if( m_buf.markPos > 0 )
	{
		// move marked region to beginning of buffer, allowing for alignment
		int nbytesMarked = m_buf.current - m_buf.markPos;
		int rounded = nbytesMarked % BUFFER_BLOCK_SIZE;
		int destPos = rounded ? BUFFER_BLOCK_SIZE - rounded : 0;
		hkString::memMove(	m_buf.begin + destPos,
							m_buf.begin + m_buf.markPos,
							nbytesMarked ); 
		m_buf.markPos = destPos;
		int blocksUsed = (nbytesMarked / BUFFER_BLOCK_SIZE) + (rounded ? 1 : 0);
		m_buf.current = blocksUsed * BUFFER_BLOCK_SIZE;
		m_buf.size = m_buf.current;
	}
	else // m_markPos == 0
	{
		// Unreachable. The mark is at the beginning of the buffer and current
		// is at the end. And the distance between them is less than marklimit.
		// We checked that this was impossible in setMark().
		//HK_ASSERT2(0x20df3999,  m_bufCurrent==0, "Impossible.");
	}
}

hkResult hkBufferedStreamReader::refillBuffer()
{
	if( m_stream->isOk()==false )
	{
		return HK_FAILURE;
	}
	prepareBufferForRefill();

	int nbytes = m_buf.capacity - m_buf.size;
	int bytesRead = 0;
	while( bytesRead < nbytes )
	{
		int thisRead = m_stream->read( m_buf.begin + m_buf.current, nbytes);
		bytesRead += thisRead;
		m_buf.size += thisRead;
		
		if( thisRead != nbytes ) // early out to stop trying to read past the end of buffer.
		{
			return bytesRead ? HK_SUCCESS : HK_FAILURE;
		}
	}

	return HK_SUCCESS;
}

int hkBufferedStreamReader::read(void* buf, int nbytes)
{
	int bytesLeft = nbytes;
	int bytesAvailable = m_buf.size - m_buf.current;
	char* cbuf = static_cast<char*>(buf);

	while( bytesLeft > bytesAvailable ) // while bytes left bigger than buffer
	{
		hkString::memCpy(cbuf, m_buf.begin+m_buf.current, bytesAvailable );
		cbuf += bytesAvailable;
		bytesLeft -= bytesAvailable;
		m_buf.current += bytesAvailable;

		if( refillBuffer() != HK_SUCCESS ) // reached eof early out
		{
			return nbytes - bytesLeft;
		}
		bytesAvailable = m_buf.size - m_buf.current;
	}

	// bytes are satisfied by buffer
	hkString::memCpy(cbuf, m_buf.begin+m_buf.current, bytesLeft );
	m_buf.current += bytesLeft;

	return nbytes;
}

int hkBufferedStreamReader::skip(int nbytes)
{
	int bytesLeft = nbytes;
	int bytesAvailable = m_buf.size - m_buf.current;

	while( bytesLeft > bytesAvailable ) // while bytes left bigger than buffer
	{
		bytesLeft -= bytesAvailable;

		if( refillBuffer() != HK_SUCCESS ) // reached eof early out
		{
			return nbytes - bytesLeft;
		}
		bytesAvailable = m_buf.size - m_buf.current;
	}

	// bytes are satisfied by buffer
	m_buf.current += bytesLeft;
	return nbytes;
}

hkBool hkBufferedStreamReader::isOk() const
{
	return m_buf.current != m_buf.size || m_stream->isOk();
}

hkBool hkBufferedStreamReader::markSupported() const
{
	return m_buf.capacity != 0;
}

hkResult hkBufferedStreamReader::setMark(int markLimit)
{
	HK_ASSERT2(0x6e85f2fe, markLimit <= m_buf.capacity,
				"setMark() was called with an limit greater than the buffer size.");
	m_buf.markPos = m_buf.current;
	m_buf.markLimit = markLimit;
	return markLimit <= m_buf.capacity ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkBufferedStreamReader::rewindToMark()
{
	if(m_buf.markPos >= 0)
	{
		m_buf.current = m_buf.markPos;
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

hkBool hkBufferedStreamReader::seekTellSupported() const
{
	return m_stream->seekTellSupported();
}

hkResult hkBufferedStreamReader::seek( int offset, SeekWhence whence)
{
	m_buf.markPos = -1;
	m_buf.markLimit = -1; // seeking resets the mark
	m_buf.current = 0;
	m_buf.size = 0; // and clears the buffer
	return m_stream->seek(offset, whence);
}

int hkBufferedStreamReader::tell() const
{
	int childPos = m_stream->tell();
	if( childPos >= 0 )
	{
		int offset = m_buf.size - m_buf.current;
		return childPos - offset;
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
