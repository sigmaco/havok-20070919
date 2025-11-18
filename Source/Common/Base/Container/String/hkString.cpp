/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Common/Base/hkBase.h>
#include <Common/Base/Fwd/hkcctype.h>
#include <Common/Base/Fwd/hkcstdarg.h>
#include <Common/Base/Fwd/hkcstdio.h>
#include <Common/Base/Fwd/hkcstdlib.h>
#include <Common/Base/Fwd/hkcstring.h>
using namespace std;

// very small strings will likely cause reallocations
static const int MINIMUM_STRING_CAPACITY = 64 - 1;

// Some platforms don't have vsnprintf, so we use vsprintf instead.
// vsprintf is not safe from overflows, so we include asserts.
// Win32 calls it _vsnprintf instead of vsprintf

#if defined(HK_PLATFORM_WIN32) || defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360)
#	define VSNPRINTF(BUF,LEN,FMT,ARGS) ::_vsnprintf(BUF,LEN,FMT,ARGS)
#elif defined(HK_PLATFORM_PS2) || defined( HK_PLATFORM_PSP )
#	define VSNPRINTF(BUF,LEN,FMT,ARGS) ::vsprintf(BUF,FMT,ARGS)
#else
#	define VSNPRINTF(BUF,LEN,FMT,ARGS) ::vsnprintf(BUF,LEN,FMT,ARGS)
#endif

// all the static methods go first so that they may be inlined
// in the nonstatic ones further on.

char HK_CALL hkString::toUpper( char c )
{
	return (c>='a'&&c<='z')
			? (char)(c - ('a' - 'A'))
			: c;
}
char HK_CALL hkString::toLower( char c )
{
	return (c>='A'&&c<='Z')
			? (char)(c + ('a' - 'A'))
			: c;
}


int HK_CALL hkString::vsnprintf( char* buf, int len, const char* fmt, hk_va_list hkargs)
{
	va_list args;
	
#if !defined(HK_ARCH_PPC) || defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360) || defined(HK_PLATFORM_MACPPC) || defined(HK_PLATFORM_MAC386)
	args = reinterpret_cast<va_list>(hkargs);
#else
	// to get arround void* --> array[1] reverse conversion we have to bypass the compiler 
	// in mwerks anyway
	hkString::memCpy(args,hkargs,sizeof(va_list));
#endif

	int ret = VSNPRINTF(buf, len, fmt, args);	
	HK_ASSERT2(0x2db7a07c, ret <= int(len), "Buffer overflow in string formatting");
	return ret;
	
}

int HK_CALL hkString::snprintf( char* buf, int len, const char* fmt, ...)
{
	va_list vlist;
	va_start(vlist, fmt);
	int ret = VSNPRINTF(buf, len, fmt, vlist);
	HK_ASSERT2(0x48675734, ret <= int(len), "Buffer overflow in string formatting");
	va_end(vlist);
	return ret;
}

int HK_CALL hkString::sprintf( char* buf, const char* fmt, ...)
{
	va_list vlist;
	va_start(vlist, fmt);
	int ret = ::vsprintf(buf, fmt, vlist);
	va_end(vlist);
	return ret;
}

int HK_CALL hkString::strCmp( const char* a, const char* b )
{
	HK_ASSERT(0x2540a587, a != HK_NULL);
	HK_ASSERT(0x571b5b6a, b != HK_NULL);
	return ::strcmp(a,b); 
}

int HK_CALL hkString::strNcmp( const char* a, const char* b, int n )
{
	HK_ASSERT(0x37ef1ca6, a != HK_NULL);
	HK_ASSERT(0x68ef40e3, b != HK_NULL);
	return ::strncmp(a,b,(unsigned)n);
}

int HK_CALL hkString::strCasecmp( const char* a, const char* b )
{
	HK_ASSERT(0x5cf1cfe9, a != HK_NULL);
	HK_ASSERT(0x49243d55, b != HK_NULL);
	int i = 0;
	while ( a[i] != 0 || b[i] != 0 )
	{
		if( toLower(a[i]) < toLower(b[i]) )
		{
			return -1;
		}
		else if( toLower(a[i]) > toLower(b[i]) )
		{
			return 1;
		}
		++i;
	}
	
	return 0;
}

int	HK_CALL hkString::strNcasecmp(const char* a, const char* b, int n)
{
	HK_ASSERT(0x7a31572d, a != HK_NULL);
	HK_ASSERT(0x54725cb9, b != HK_NULL);
	HK_ASSERT(0x7403b0c0, n >= 0);

	int i = 0;
	while ( (a[i] != 0 || b[i] != 0) && i < n )
	{
		if( toLower(a[i]) < toLower(b[i]) )
		{
			return -1;
		}
		else if( toLower(a[i]) > toLower(b[i]) )
		{
			return 1;
		}
		++i;
	}
	
	return 0;
}

void HK_CALL hkString::strCpy( char* dst, const char* src )
{
	HK_ASSERT(0x49fa77f1, src != HK_NULL);
	HK_ASSERT(0x7d3f002c, dst != HK_NULL);
	::strcpy(dst, src);
}

void HK_CALL hkString::strNcpy(char *dst, const char *src, int n)
{
	HK_ASSERT(0x6e527462, src != HK_NULL || n == 0);
	HK_ASSERT(0x67d37b1f, dst != HK_NULL || n == 0);
	if( n )
	{
		::strncpy(dst, src, (unsigned)n);
	}
}

int HK_CALL hkString::strLen( const char* src )
{
	HK_ASSERT(0x18be8938, src != HK_NULL);
	return (int) ::strlen(src);
}

int HK_CALL hkString::atoi( const char* in)
{
	return ::strtoul(in, HK_NULL, 0);
}

hkReal HK_CALL hkString::atof( const char* in )
{
	return static_cast<hkReal>( strtod( in, HK_NULL) );
}

const char* HK_CALL hkString::strStr(const char* haystack, const char* needle)
{
	return ::strstr(haystack, needle);
}

const char* HK_CALL hkString::strChr(const char* haystack, int needle)
{
	return ::strchr(haystack, needle);
}

const char* HK_CALL hkString::strRchr(const char* haystack, int needle)
{
	return ::strrchr(haystack, needle);
}

char* HK_CALL hkString::strDup(const char* src)
{
	HK_ASSERT(0x13e1d159, src != HK_NULL);
	char* r = hkAllocate<char>( strLen(src)+1, HK_MEMORY_CLASS_STRING );
	hkString::strCpy(r, src);
	return r;
}

char* HK_CALL hkString::strNdup(const char* src, int maxlen)
{
	HK_ASSERT(0x2e27506f, src != HK_NULL);
	int len = strLen(src);
	if( len > maxlen )
	{
		len = maxlen;
	}
	char* r = hkAllocate<char>( len+1, HK_MEMORY_CLASS_STRING );
	hkString::strNcpy(r, src, len);
	r[len] = 0;
	return r;
}

char* HK_CALL hkString::strLwr(char* s)
{
	HK_ASSERT(0x3779fe34, s != HK_NULL);
	int i=0;
	while(s[i])
	{
		s[i] = (char)(toLower(s[i]));
		i++;
	}
	return s;
}

char* HK_CALL hkString::strUpr(char* s)
{
	HK_ASSERT(0x128f807f, s != HK_NULL);
	int i=0;
	while(s[i])
	{
		s[i] = (char)(toUpper(s[i]));
		i++;
	}
	return s;
}
void HK_CALL hkString::memCpy( void* dst, const void* src, int n)
{
	::memcpy(dst,src,(unsigned)n);
}


void HK_CALL hkString::memMove(void* dst, const void* src, int n)
{
	::memmove(dst,src,(unsigned)n);
}

void HK_CALL hkString::memSet(void* dst, const int c, int n)
{
	::memset(dst,c,(unsigned)n);
}

int HK_CALL hkString::memCmp( const void *buf1, const void *buf2, int n)
{
	return ::memcmp(buf1,buf2,(unsigned)n);
}

//
// nonstatic member functions
//
#if !defined(HK_PLATFORM_PS3SPU) 
void HK_CALL hkString::printf(const char* fmt, ...)
{
	if( getCapacity() < MINIMUM_STRING_CAPACITY )
	{
		setCapacity( 255 );
	}	

	va_list args; 
	va_start(args, fmt);
	while(1)
	{
		int size = m_string.getCapacity();
		int nchars = hkString::vsnprintf(m_string.begin(), size, fmt, args);

		if( nchars >= 0 && nchars < size ) 
		{
			// usual case, it worked. update length		
			m_string.setSizeUnchecked( nchars+1 ); // reducing size
			break;
		}
		else if( nchars < 0 )
		{
			// there was not enough room, double capacity
			setLength( size*2 > 255 ? size*2 : 255 ); 
		}
		else
		{
			// there was not enough room and we were told how much
			// was needed (not including \0)
			setLength( nchars );
		}
	}
	va_end(args);
	m_string.optimizeCapacity( 0, true ); // shrink the array
}
#endif

int hkString::indexOf(char c, int start, int end) const
{
	for(int i = start; i < getLength() && i < end; ++i)
	{
		if( m_string[i] == c )
		{
			return i;
		}
	}
	return -1;
}

int hkString::lastIndexOf(char c, int start, int end) const
{
	if( end > getLength() )
	{
		end = getLength();
	}
	for(int i = end - 1; i >= start ; --i)
	{
		if( m_string[i] == c )
		{
			return i;
		}
	}
	return -1;
}

hkString hkString::operator+ (const hkString& other) const // this should use the char* version and be inlined
{
	int myLength = getLength();
	int otherLength = other.getLength();
	int totalLength= myLength + otherLength;
    // allocate a new chunk of memory to hold the result of concatenation
	char* p = hkAllocateChunk<char>( totalLength + 1, HK_MEMORY_CLASS_STRING ); 
	// copy the two strings
	hkString::memCpy( p, m_string.begin(), myLength );
	hkString::memCpy( p+myLength, other.m_string.begin(), otherLength+1 ); // copy null too

	return hkString(p, totalLength + 1, totalLength + 1); // the string is not copied, the array uses the buffer
}

hkString hkString::operator+ (const char* other) const
{
	int myLength = getLength();
	int otherLength = strLen(other);
	int totalLength= myLength + otherLength;
	// allocate a new chunk of memory to hold the result of concatenation
	char* p = hkAllocateChunk<char>( totalLength + 1, HK_MEMORY_CLASS_STRING );
	// copy the two strings
	hkString::memCpy( p, m_string.begin(), myLength );
	hkString::memCpy( p+myLength, other, otherLength+1 ); // copy null too
	
	return hkString( p, totalLength + 1, totalLength + 1 ); // the string is not copied, the array uses the buffer
}

hkString& hkString::operator+= (const hkString& other)
{
	int myLength = getLength();
	int otherLength = other.getLength();
	// increase size and concatenate the strings
	setLength( myLength + otherLength );
	hkString::memCpy( m_string.begin()+myLength, other.cString(), otherLength+1 ); // copy null too
	
	return *this;
}

hkString& hkString::operator+= (const char* other)
{
	int myLength = getLength();
	int otherLength = strLen(other);
	// increase size and concatenate the strings
	setLength( myLength + otherLength );
	hkString::memCpy( m_string.begin()+myLength, other, otherLength+1 ); // copy null too
	
	return *this;
}

hkString hkString::asUpperCase() const
{
	char* p = hkAllocateChunk<char>( m_string.getSize(), HK_MEMORY_CLASS_STRING );
	// don't use strupr because that doesn't deal with embedded nulls
	for(int i = 0; i < getLength(); ++i)
	{
		p[i] = toUpper(m_string[i]);
	}
	p[ getLength() ] = 0; // null terminate

	return hkString( p, m_string.getSize(), m_string.getSize() ); // memory is not copied, use the new buffer
}

hkString hkString::asLowerCase() const
{
	char* p = hkAllocateChunk<char>( m_string.getSize(), HK_MEMORY_CLASS_STRING );
	// don't use strlwr because that doesn't deal with embedded nulls
	for(int i = 0; i < getLength(); ++i)
	{
		p[i] = toLower(m_string[i]);
	}
	p[ getLength() ] = 0; // null terminate
	
	return hkString( p, m_string.getSize(), m_string.getSize() ); // memory is not copied, use the new buffer
}

hkBool hkString::beginsWith (const char* other) const
{
	for(int i=0; other[i] != 0; ++i)
	{
		if( i >= getLength() || m_string[i] != other[i] )
		{
			return false;
		}
	}
	return true;
}

hkBool hkString::endsWith (const hkString& other) const   // use the char* varsion? to avoid strLen?
{
	if( getLength() < other.getLength() )
	{
		return false;
	}
	int offset = getLength() - other.getLength();

	for(int i=0; i < other.getLength(); ++i)
	{
		if( m_string[i+offset] != other[i] )
		{
			return false;
		}
	}
	return true;
}

hkBool hkString::endsWith (const char* other) const
{
	int offset = getLength() - hkString::strLen(other);
	if(offset < 0)
	{
		return false;
	}
	for(int i=0; other[i] != 0; ++i)
	{
		if( m_string[i+offset] != other[i] )
		{
			return false;
		}
	}
	return true;
}

hkString hkString::replace(char oldchar, char newchar, hkString::ReplaceType rtype ) const
{
	char* p = hkAllocateChunk<char>( m_string.getSize(), HK_MEMORY_CLASS_STRING );
	hkString::memCpy( p, m_string.begin(), m_string.getSize() );
	for(int i = 0; i < getLength(); ++i)
	{
		if(p[i] == oldchar)
		{
			p[i] = newchar;
			if(rtype == REPLACE_ONE)
			{
				break;
			}
		}
	}
	p[ getLength() ] = 0; // null terminate

	return hkString( p, m_string.getSize(), m_string.getSize() ); // memory is not copied, the new buffer is used
}

hkString hkString::replace(const hkString& from, const hkString& to, hkString::ReplaceType rtype) const
{
	hkString ret;
	int current = 0;

	const char* thisp = this->cString();
	const char* fromp = from.cString();

	const char* p = strStr(thisp, fromp);
	while(p)
	{
		int i = static_cast<int>( p - thisp - current ); //XX 64 bit issue
		ret += this->substr(current, i ); 
		ret += to;
		current += i + from.getLength();

		if(rtype == REPLACE_ONE)
		{
			break;
		}

		p = strStr(thisp + current, fromp);
	}

	if( current != 0 ) // a replacement happened
	{
		ret += (thisp + current);
		return ret;
	}
	// otherwise original string is unchanged.
	return *this;
}

/*
extern int strtol(const char*, int b);
extern int strtol(const char* s, int base)
{
	return ::strtol( s, HK_NULL, base);
}
*/

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
