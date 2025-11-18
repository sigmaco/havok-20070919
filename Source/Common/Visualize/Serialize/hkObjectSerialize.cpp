/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/Serialize/hkObjectSerialize.h>

#include <Common/Serialize/Serialize/Platform/hkPlatformObjectWriter.h>
#include <Common/Serialize/Serialize/hkRelocationInfo.h>

#include <Common/Base/System/Io/Reader/hkStreamReader.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>
#include <Common/Base/System/Io/OArchive/hkOArchive.h>
#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>

#define CHECK_STREAM(S, V) { if (!S->isOk()) return V; }

hkUint64 hkObjectSerialize::readObject( hkStreamReader* s, void*& data, hkUint32& dataSize, hkArray<GlobalFixup>& globalFixups, hkUint64& klassID)
{
	// The whole packet is assumed to have been targeted at this platform
	// so we don't need to endian swap etc.

	// id
	hkUint64 id;
	s->read(&id, sizeof(id));
	CHECK_STREAM(s,0)

		// read class ID, as it may be a virtual class we asked for, and here we know its exact, instance class type.
	s->read(&klassID, sizeof(klassID));
	CHECK_STREAM(s,0)

	// local fixups	
	hkArray<LocalFixup> localFixups;
	hkUint32 numLocal;
	s->read(&numLocal, sizeof(hkUint32));
	CHECK_STREAM(s,0)
	
	localFixups.setSize(numLocal);
	{
		for(hkUint32 li=0; (li < numLocal); ++li)
		{
			LocalFixup& lf = localFixups[li];
			s->read(&lf.fromOffset, sizeof(hkInt32));
			s->read(&lf.toOffset, sizeof(hkInt32));
			CHECK_STREAM(s,0)
		}
	}

	// global fixups
	hkUint32 numGlobal;
	s->read(&numGlobal, sizeof(hkUint32));
	CHECK_STREAM(s,0)

	globalFixups.setSize(numGlobal);
	{
		for(hkUint32 gi=0; (gi < numGlobal); ++gi)
		{
			GlobalFixup& gf = globalFixups[gi];
			s->read(&gf.fromOffset, sizeof(hkInt32));
			s->read(&gf.toID, sizeof(hkUint64));
			s->read(&gf.toClassID, sizeof(hkUint64));
			CHECK_STREAM(s,0)
		}
	}

	// data
	s->read(&dataSize, sizeof(hkUint32));
	CHECK_STREAM(s,0)

	char* dataPtr = hkAllocate<char>( dataSize, HK_MEMORY_CLASS_VDB );
	s->read(dataPtr, dataSize);
	if (!s->isOk()) 
	{
		hkDeallocate<char>( reinterpret_cast<char*>(dataPtr) );
		return 0;
	}

	// do the local fixups
	{
		for(hkUint32 li=0; (li < numLocal); ++li)
		{
			int srcOff = localFixups[li].fromOffset;
			if (srcOff < 0) continue;
			int dstOff = localFixups[li].toOffset;
			*(hkUlong*)(dataPtr+srcOff) = hkUlong(dataPtr+dstOff);
		}	
	}

	data = dataPtr;

	// done
	return id;
}

static int _writeData( hkStreamWriter* s, hkUint64 dataID, hkUint64 classID, void* data, hkUint32 dataSize, const hkRelocationInfo& reloc, hkBool endianSwap)
{
	HK_ASSERT2( 0x6ce419a2, dataID && data && (dataSize > 0), "Invalid data packet to write (has no size)");
	
	hkOArchive a(s, endianSwap);

	int bytesWritten = 0;

	// id
	a.write64u(dataID);
	CHECK_STREAM(s,-1)
	bytesWritten += 8;

	// id
	a.write64u(classID);
	CHECK_STREAM(s,-1)
	bytesWritten += 8;


	// local fixups will be performed on read on target
	hkUint32 numLocal = reloc.m_local.getSize();	
	a.write32u(numLocal);
	bytesWritten += 4;
	for (hkUint32 li=0; li < numLocal; ++li)
	{
		a.write32(reloc.m_local[li].m_fromOffset);			
		a.write32(reloc.m_local[li].m_toOffset);			
		CHECK_STREAM(s,-1)
		bytesWritten += 8;
	}
	
	// globals for convience
	hkUint32 numGlobal = reloc.m_global.getSize();	
	a.write32u(numGlobal);
	bytesWritten += 4;
	for (hkUint32  gi=0; gi < numGlobal; ++gi)
	{
		a.write32(reloc.m_global[gi].m_fromOffset);			
		a.write64u( hkUlong(reloc.m_global[gi].m_toAddress) ); //64 bit ptr (id)
		a.write64u( hkUlong(reloc.m_global[gi].m_toClass) ); // 64bit class ptr (id)
		CHECK_STREAM(s,-1)
		bytesWritten += (8*2) + 4;
	}

	// data 
	a.write32u(dataSize);
	CHECK_STREAM(s,-1)
	bytesWritten += 4;

	// the raw data chunk
	s->write(data, dataSize);
	CHECK_STREAM(s,-1)
	bytesWritten += dataSize;

	return bytesWritten;
} 

int hkObjectSerialize::writeObject( hkStreamWriter* s, const hkStructureLayout& destLayout, hkUint64 dataID, const void* data, const hkClass& klass, hkArray<GlobalFixup>& globalFixups )
{
	// need platform write.
	hkPlatformObjectWriter pw(destLayout);
	
	// The data chunk size is of unknown size until the writer has worked it out (incl array data)
	// so we write to a mem buffer and then write that to the normal stream as one big chunk.
	hkArray<char> buffer;
	hkArrayStreamWriter asw(&buffer, hkArrayStreamWriter::ARRAY_BORROW);

	// have to save the reloc info too.
	hkRelocationInfo reloc;
	pw.writeObject(&asw, data, klass, reloc );
	
	// store the global fixups.
	globalFixups.reserve( globalFixups.getSize() + reloc.m_global.getSize() );
	for (int i=0; i < reloc.m_global.getSize(); ++i)
	{
		GlobalFixup& gf = globalFixups.expandOne();
		gf.fromOffset = reloc.m_global[i].m_fromOffset;
		gf.toID = hkUlong( reloc.m_global[i].m_toAddress );
		gf.toClassID = hkUlong( reloc.m_global[i].m_toClass );
	}

	// finally write the whole thing.
	return _writeData( s, dataID, hkUlong(&klass), buffer.begin(), buffer.getSize(), reloc, destLayout.getRules().m_littleEndian != hkStructureLayout::HostLayoutRules.m_littleEndian );
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
