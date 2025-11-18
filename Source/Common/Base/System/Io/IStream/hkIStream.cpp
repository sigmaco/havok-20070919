/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

#include <Common/Base/Fwd/hkcstdarg.h>
#include <Common/Base/Fwd/hkcstdio.h>
#include <Common/Base/Fwd/hkcstdlib.h>
#include <Common/Base/Fwd/hkcstring.h>
using namespace std;

#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Base/System/Io/Reader/Buffered/hkBufferedStreamReader.h>
#include <Common/Base/System/Io/Reader/Memory/hkMemoryStreamReader.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>

// isOk should return true directly after a successful read
// isOk should return false directly after an unsuccessful read

const int TEMP_STORAGE_SIZE = 256;

hkIstream::hkIstream(hkStreamReader* sb)
	:	m_streamReader(sb)
{
	m_streamReader->addReference();
}


hkIstream::hkIstream(const char* fname)
{
	m_streamReader = hkStreambufFactory::getInstance().openReader(fname);
}

hkIstream::hkIstream(const void* mem, int memSize)
{
	m_streamReader = new hkMemoryStreamReader(mem, memSize, hkMemoryStreamReader::MEMORY_INPLACE);
}

hkIstream::~hkIstream()
{
	if (m_streamReader)
	{
		m_streamReader->removeReference();
	}
}

hkBool hkIstream::isOk() const
{
	if (m_streamReader)
	{
		return m_streamReader->isOk();
	}
	return false;
}


#define IS_DECIMALPOINT(c) ( ((c) == '.') || ((c) == ',') )
#define IS_INTEGER(c)      ( ((c) >= '0') && ((c) <= '9') )
#define IS_HEX(c)          (  ( ((c) >= 'a') && ((c) <= 'f') ) || ( ((c) >= 'A') && ((c) <= 'F') )  )
#define IS_SIGN(c)         ( ((c) == '+') || ((c) == '-') )
#define IS_SPACE(c)		   ( ((c) == ' ') || ((c) == '\t') )
#define IS_EXP(c)		   ( ((c) == 'E') || ((c) == 'e') )
#define IS_EOL(c)		   ( ( (c) == '\r') || ((c) == '\n') )

// eat white space from reader
static void HK_CALL eatWhiteSpace( hkStreamReader* reader )
{
	char buf[64];
	while(1)
	{
		reader->setMark(sizeof(buf));
		int n = reader->read(buf, sizeof(buf));
		if( n == 0 )
		{
			return; //eof
		}
		for( int i = 0; i < n; ++i )
		{
			if( IS_SPACE(buf[i]) == false && IS_EOL(buf[i]) == false ) // real char
			{
				reader->rewindToMark();
				reader->skip(i);
				return;
			}
		}
	}
}

static hkUint64 HK_CALL readInteger64( hkStreamReader* reader, hkBool& negOut )
{
	eatWhiteSpace(reader);

	negOut = false;
	hkUint64 u64 = 0;

	char storage[TEMP_STORAGE_SIZE];
	int startIndex = 0;

	reader->setMark(TEMP_STORAGE_SIZE-1); // allow for trailing null
	int nbytes = reader->read( storage, TEMP_STORAGE_SIZE-1 );

	if( nbytes )
	{
		if( storage[0] == '+')
		{
			startIndex = 1;
		}
		else if( storage[0] == '-')
		{
			negOut = true;
			startIndex = 1;
		}

		unsigned base = 0;
		// base16? need at least 3 chars 0x<digit|hex>.
		if( startIndex+3 < nbytes
			&& storage[startIndex] == '0'
			&& ( storage[startIndex+1] == 'x' || storage[startIndex+1] == 'X')
			&& ( IS_INTEGER(storage[startIndex+2]) || IS_HEX(storage[startIndex+2]) ) )
		{
			base = 16;
			startIndex += 2;
		}
		// base8? need at least two chars 0<digit>
		else if( startIndex+2 < nbytes
			&& storage[startIndex] == '0'
			&& IS_INTEGER( storage[startIndex+1] ) )
		{
			base = 8;
			startIndex += 1;
		}
		// no prefix, use base10
		else
		{
			base = 10;
		}

		int i;
		for( i = startIndex; i < nbytes; ++i )
		{
			unsigned next = unsigned(-1);
			if( IS_INTEGER(storage[i]) )
			{
				next = static_cast<unsigned>(storage[i] - '0');
			}
			else if( storage[i] > 'A' && storage[i] <= 'F' )
			{
				next = static_cast<unsigned>(storage[i] + 10 - 'A');
			}
			else if( storage[i] > 'a' && storage[i] <= 'f' )
			{
				next = static_cast<unsigned>(storage[i] + 10 - 'a');
			}

			if( next < base )
			{
				u64 *= base;
				u64 += next;
			}
			else
			{
				break;
			}
		}
		reader->rewindToMark();
		reader->skip(i);

		return u64;
	}

	return 0;
}


static float HK_CALL readFloat(hkStreamReader* reader)
{
	eatWhiteSpace(reader);
	
	char storage[TEMP_STORAGE_SIZE];
	int validChars = 0;

	reader->setMark(TEMP_STORAGE_SIZE-1);
	int nbytes = reader->read( storage, TEMP_STORAGE_SIZE-1 );
	if( (nbytes != 0) && (IS_INTEGER(storage[0]) || IS_SIGN(storage[0])
						|| IS_DECIMALPOINT(storage[0]) ) ) // optional +-.
	{
		++validChars;

		while( validChars < nbytes )
		{
			char c = storage[validChars];
			if( IS_INTEGER(c) || IS_SIGN(c) || IS_EXP(c) || IS_DECIMALPOINT(c) )
			{
				if (IS_DECIMALPOINT(c))
				{
					// HVK-1548
					storage[validChars] = '.';
				}
				++validChars; // most likely
				continue;
			}
			break; // else not a valid float character
		}
	}

	reader->rewindToMark();
	reader->skip(validChars);
	storage[validChars] = '\0';

	if( validChars > 0 )
	{
		return (float)strtod( storage, HK_NULL );
	}
	return -1;
}

hkIstream& hkIstream::operator>> (hkBool& b)
{
	eatWhiteSpace(m_streamReader);
	m_streamReader->setMark(6);
	char buf[6];
	int nread = m_streamReader->read(buf, 6);
	// "false":5 "true":4
	// Be careful about "true<EOF>" - if we read too far, isOk
	// will return false even though we have a good read.
	if( nread >= 4 && (hkString::strNcmp(buf, "true", 4) == 0) )
	{
		if( nread == 4 || (IS_SPACE(buf[4]) || (IS_EOL(buf[4]) ) ) )
		{
			b = true;
			m_streamReader->rewindToMark();
			m_streamReader->skip( 4 );
			return *this;
		}
	}
	if( nread >= 5 && (hkString::strNcmp(buf, "false", 4) == 0) )
	{
		if( nread == 5 || (IS_SPACE(buf[5]) || (IS_EOL(buf[5]) ) ) )
		{
			b = false;
			m_streamReader->rewindToMark();
			m_streamReader->skip( 5 );
			return *this;
		}
	}
	m_streamReader->rewindToMark();
	return *this;
}

hkIstream& hkIstream::operator>> (char& c)
{
	m_streamReader->read(&c, 1);
	return *this;
}

#if defined(HK_COMPILER_MSVC)
#	pragma warning(push)
#	pragma warning(disable:4146)
#endif
template <typename T>
inline void readInteger( hkStreamReader* reader, T& tOut )
{
	hkBool neg;
	hkUint64 u64 = readInteger64(reader, neg);
	T t = static_cast<T>(u64);
	tOut = neg ? static_cast<T>(-t) : t;
}
#if defined(HK_COMPILER_MSVC)
#	pragma warning(pop)
#endif

hkIstream& hkIstream::operator>> (short& s)
{
	readInteger(m_streamReader, s);
	return *this;
}

hkIstream& hkIstream::operator>> (unsigned short& s)
{
	readInteger(m_streamReader, s);
	return *this;

}

hkIstream& hkIstream::operator>> (int& i)
{
	readInteger(m_streamReader, i);
	return *this;
}

hkIstream& hkIstream::operator>> (unsigned int& i)
{
	readInteger(m_streamReader, i);
	return *this;
}

hkIstream& hkIstream::operator>> (float & f)
{
	f = readFloat(m_streamReader);
	return (*this);
}

hkIstream& hkIstream::operator>> (double& d)
{
	// XXX down size as Havok doesn't use doubles usually,
	// but change this if doubles required
	d = static_cast<float>( readFloat(m_streamReader) );
	return *this;
}

hkIstream& hkIstream::operator>> (hkInt64& i)
{
	readInteger(m_streamReader, i);
	return *this;
}

hkIstream& hkIstream::operator>> (hkUint64& i)
{
	readInteger(m_streamReader, i);
	return *this;
}

hkIstream& hkIstream::operator>> (hkString& str)
{
	hkArray<char> buf; //XXX batch me
	buf.reserve(64);
	eatWhiteSpace( m_streamReader );
	while( 1 )
	{
		m_streamReader->setMark(1);
		int c = m_streamReader->readChar();
		if( (c == -1) || IS_SPACE(c) || IS_EOL(c) )
		{
			m_streamReader->rewindToMark();
			break;
		}
		buf.pushBack(char(c));
	}
	buf.pushBack(0);
	str = &buf[0];
	return *this;
}

int hkIstream::getline(char* str, int maxlen, char delim)
{
	HK_ASSERT(0x50a0d3e2, maxlen > 0); //XXX batch me
	eatWhiteSpace( m_streamReader );

	int i = 0;
	while(i < maxlen) 
	{
		int c = m_streamReader->readChar();
		if( c == -1 || c == delim)
		{
			str[i] = '\0';
			return i;
		}
		str[i++] = static_cast<char>(c);
	}

	// if we reach maxlen, we return -1
	return -1;
}

int hkIstream::read( char* buf, int nbytes )
{
	return m_streamReader->read(buf, nbytes);
}

HK_FORCE_INLINE void hkIstream::setStreamReader(hkStreamReader* newReader)
{
	newReader->addReference();
	m_streamReader->removeReference();
	m_streamReader = newReader;
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
