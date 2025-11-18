/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>
#include <Common/Base/System/Io/IArchive/hkIArchive.h>
#include <Common/Base/System/Io/Reader/Buffered/hkBufferedStreamReader.h>
#include <Common/Base/System/Io/Reader/Memory/hkMemoryStreamReader.h>

hkIArchive::hkIArchive(hkStreamReader* sb, hkBool bs)
	:	m_streamReader(sb), m_byteSwap(bs)
{
	m_streamReader->addReference();
}

hkIArchive::hkIArchive(const char* filename, hkBool bs)
	: m_byteSwap(bs)
{
	m_streamReader = hkStreambufFactory::getInstance().openReader(filename);
}

hkIArchive::hkIArchive(const void* mem, int memSize, hkBool byteswap)
	: m_byteSwap(byteswap)
{
	m_streamReader = new hkMemoryStreamReader(mem, memSize, hkMemoryStreamReader::MEMORY_INPLACE);
}

hkIArchive::~hkIArchive()
{
	if(m_streamReader)
	{
		m_streamReader->removeReference();
	}
}

static HK_FORCE_INLINE void byteswap(char& a, char& b)
{
	char t = a;
	a = b;
	b = t;
}

void hkIArchive::readArrayGeneric(void* array, int elemsize, int arraySize)
{
	m_streamReader->read(array, elemsize * arraySize);
	if(m_byteSwap)
	{
		char* dst = static_cast<char*>(array);
		switch( elemsize )
		{
			case 1:
			{
				break;
			}
			case 2:
			{
				for(int i = 0; i < arraySize; ++i)
				{
					byteswap(dst[0], dst[1]);
					dst += 2;
				}
				break;
			}
			case 4:
			{
				for(int i = 0; i < arraySize; ++i)
				{
					byteswap(dst[0], dst[3]);
					byteswap(dst[1], dst[2]);
					dst += 4;
				}
				break;
			}
			case 8:
			{
				for(int i = 0; i < arraySize; ++i)
				{
					byteswap(dst[0], dst[7]);
					byteswap(dst[1], dst[6]);
					byteswap(dst[2], dst[5]);
					byteswap(dst[3], dst[4]);
					dst += 8;
				}
				break;
			}
			default:
			{
				HK_ASSERT2(0x3d71710d, 0, "elemsize " << elemsize << " not handled.\n" \
						"elemsize must be a power of two and no greater than 8 (64 bits)");

			}
		}
	}
}

int hkIArchive::readRaw(void* buf, int nbytes)
{
	return m_streamReader->read(buf, nbytes);
}

hkBool hkIArchive::isOk() const
{
	return m_streamReader->isOk();
}

hkStreamReader* hkIArchive::getStreamReader()
{
	return m_streamReader;
}

void hkIArchive::setStreamReader(hkStreamReader* newBuf)
{
	newBuf->addReference();
	m_streamReader->removeReference();
	m_streamReader = newBuf;
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
