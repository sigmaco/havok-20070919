/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>
#include <Common/Base/System/Io/OArchive/hkOArchive.h>
#include <Common/Base/System/Io/Writer/Buffered/hkBufferedStreamWriter.h>
#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>

hkOArchive::hkOArchive(hkStreamWriter* sw, hkBool bs)
	:	m_writer(sw), m_byteSwap(bs)
{
	m_writer->addReference();
}

hkOArchive::hkOArchive(const char* filename, hkBool bs)
	: m_byteSwap(bs)
{
	m_writer = hkStreambufFactory::getInstance().openWriter(filename);
}

hkOArchive::hkOArchive(void* mem, int memSize, hkBool bs)
	: m_byteSwap(bs)
{
	m_writer = new hkBufferedStreamWriter(mem, memSize, false);
}

hkOArchive::hkOArchive(hkArray<char>& arr, hkBool bs)
	: m_byteSwap(bs)
{
	m_writer = new hkArrayStreamWriter(&arr, hkArrayStreamWriter::ARRAY_BORROW);
}

hkOArchive::~hkOArchive()
{
	m_writer->removeReference();
}

//
// Singles
//

void hkOArchive::write8(hkChar c)
{
	m_writer->write(&c, 1);
}

void hkOArchive::write8u(hkUchar u)
{
	m_writer->write(&u, 1);
}

void hkOArchive::write16(hkInt16 i)
{
	writeArrayGeneric( &i, 2, 1);
}

void hkOArchive::write16u(hkUint16 u)
{
	writeArrayGeneric( &u, 2, 1);
}

void hkOArchive::write32(hkInt32 i)
{
	writeArrayGeneric( &i, 4, 1);
}

void hkOArchive::write32u(hkUint32 u)
{
	writeArrayGeneric( &u, 4, 1);
}

void hkOArchive::write64(hkInt64 i)
{
	writeArrayGeneric( &i, 8, 1);
}

void hkOArchive::write64u(hkUint64 u)
{
	writeArrayGeneric( &u, 8, 1);
}

void hkOArchive::writeFloat32(hkFloat32 f)
{
	writeArrayGeneric( &f, 4, 1);
}

void hkOArchive::writeDouble64(hkDouble64 d)
{
	writeArrayGeneric( &d, 8, 1);
}

//
// Arrays
//

void hkOArchive::writeArray8(const hkInt8* array, int nelem)
{
	writeArrayGeneric(array, 1, nelem);
}

void hkOArchive::writeArray8u(const hkUint8* array, int nelem)
{
	writeArrayGeneric(array, 1, nelem);
}

void hkOArchive::writeArray16(const hkInt16* array, int nelem)
{
	writeArrayGeneric(array, 2, nelem);
}

void hkOArchive::writeArray16u(const hkUint16* array, int nelem)
{
	writeArrayGeneric(array, 2, nelem);
}

void hkOArchive::writeArray32(const hkInt32* array, int nelem)
{
	writeArrayGeneric(array, 4, nelem);
}

void hkOArchive::writeArray32u(const hkUint32* array, int nelem)
{
	writeArrayGeneric(array, 4, nelem);
}

void hkOArchive::writeArray64(const hkInt64* array, int nelem)
{
	writeArrayGeneric(array, 8, nelem);
}

void hkOArchive::writeArray64u(const hkUint64* array, int nelem)
{
	writeArrayGeneric(array, 8, nelem);
}

void hkOArchive::writeArrayFloat32(const hkFloat32* array, int nelem)
{
	writeArrayGeneric(array, 4, nelem);
}

void hkOArchive::writeArrayDouble64(const hkDouble64* array, int nelem)
{
	writeArrayGeneric(array, 8, nelem);
}

//
// Master
//

static HK_FORCE_INLINE void byteswap(char& a, char& b)
{
	char t = a;
	a = b;
	b = t;
}

void hkOArchive::writeArrayGeneric(const void* ptr, int elemSize, int arraySize)
{
	if( m_byteSwap == false)
	{
		m_writer->write(ptr, arraySize * elemSize);
	}
	else
	{
		const int BUFSIZE = 512;
		char buf[BUFSIZE];
		const char* src = static_cast<const char*>(ptr);
		int bytesLeft = elemSize * arraySize;

		int chunkBytes = BUFSIZE;
		int chunkElems = BUFSIZE / elemSize;
		HK_ASSERT(0x14a08fb1,  BUFSIZE % elemSize == 0);

		int leftoverBytes = bytesLeft % BUFSIZE;
		int leftoverElems = leftoverBytes / elemSize;
		HK_ASSERT(0x7405771d,  leftoverBytes % elemSize == 0);

		while( bytesLeft > 0 )
		{
			if( bytesLeft < BUFSIZE )
			{
				chunkBytes = leftoverBytes;
				chunkElems = leftoverElems;
			}
			hkString::memCpy( buf, src, chunkBytes );

			switch( elemSize )
			{
				case 1:
				{
					break;
				}
				case 2:
				{
					char* bufp = buf;
					for(int i = 0; i < chunkElems; ++i)
					{
						byteswap(bufp[0], bufp[1]);
						bufp += 2;
					}
					break;
				}
				case 4:
				{
					char* bufp = buf;
					for(int i = 0; i < chunkElems; ++i)
					{
						byteswap(bufp[0], bufp[3]);
						byteswap(bufp[1], bufp[2]);
						bufp += 4;
					}
					break;
				}
				case 8:
				{
					char* bufp = buf;
					for(int i = 0; i < chunkElems; ++i)
					{
						byteswap(bufp[0], bufp[7]);
						byteswap(bufp[1], bufp[6]);
						byteswap(bufp[2], bufp[5]);
						byteswap(bufp[3], bufp[4]);
						bufp += 8;
					}
					break;
				}
				default:
				{

					HK_ASSERT2(0x2cbaf98f, 0, "elemsize " << elemSize << " not handled.\n" \
							"elemsize must be a power of two and no greater than 8 (64 bits)");

				}
			}

			m_writer->write(buf, chunkBytes);
			bytesLeft -= chunkBytes;
			src += chunkBytes;
		}
	}
}

//
// Misc
//

int hkOArchive::writeRaw(const void* buf, int nbytes)
{
	return m_writer->write(buf, nbytes);
}

void hkOArchive::setByteSwap(hkBool on)
{
	m_byteSwap = on;
}

hkBool hkOArchive::getByteSwap() const
{
	return m_byteSwap;
}

hkBool hkOArchive::isOk() const
{
	return m_writer->isOk();
}

hkStreamWriter* hkOArchive::getStreamWriter()
{
	return m_writer;
}

void hkOArchive::setStreamWriter(hkStreamWriter* newWriter)
{
	newWriter->addReference();
	m_writer->removeReference();
	m_writer = newWriter;	
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
