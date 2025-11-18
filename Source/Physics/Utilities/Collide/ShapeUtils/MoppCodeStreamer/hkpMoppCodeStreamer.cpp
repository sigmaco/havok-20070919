/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/Io/OArchive/hkOArchive.h>
#include <Common/Base/System/Io/IArchive/hkIArchive.h>

#include <Physics/Internal/Collide/Mopp/Code/hkpMoppCode.h>
#include <Physics/Utilities/Collide/ShapeUtils/MoppCodeStreamer/hkpMoppCodeStreamer.h>


hkpMoppCode* HK_CALL hkpMoppCodeStreamer::readMoppCodeFromArchive(hkIArchive &inputArchive)
{
		// Read in the header info, see writeMoppCodeToArchive()
	hkVector4 header; header.setAll3(1e10f);
	header(0) = inputArchive.readFloat32();
	header(1) = inputArchive.readFloat32();
	header(2) = inputArchive.readFloat32();
	header(3) = inputArchive.readFloat32();

		// Read in the MOPP byte code size
	int byteCodeSize = inputArchive.read32();

		// Put in some very basic "safety" checks here to detect file corruption. It is "unlikely" that
		// the offset values will be very large in magnitude.
	HK_ASSERT2(0x6a8a18e5, (header(0) > -1e9f) && (header(0) < 1e9f), "Header of MoppCode Archive is corrupt!");
	HK_ASSERT2(0x51cc39fe, (header(1) > -1e9f) && (header(1) < 1e9f), "Header of MoppCode Archive is corrupt!");
	HK_ASSERT2(0x7a84f907, (header(2) > -1e9f) && (header(2) < 1e9f), "Header of MoppCode Archive is corrupt!");
		// Also, assume size of data less than ~100 meg! This may be overly conservative!
	HK_ASSERT2(0x5f442ae7, byteCodeSize < 10000000, "Input Archive data corrupt, byte code size is huge!");
	

	hkpMoppCode* code = new hkpMoppCode();
	code->m_data.setSize( byteCodeSize );
	
	code->m_info.m_offset(0) = header(0);
	code->m_info.m_offset(1) = header(1);
	code->m_info.m_offset(2) = header(2);
	code->m_info.m_offset(3) = header(3);
			
		// Read in the byte code
	HK_ON_DEBUG(int numBytesRead =) inputArchive.readRaw( const_cast<hkUint8*>(&code->m_data[0]), byteCodeSize);
	HK_ASSERT2(0x1e5e6c92, numBytesRead == byteCodeSize, "Input Archive data corrupt, not enough bytes read!");
	
	return code;
}

void HK_CALL hkpMoppCodeStreamer::writeMoppCodeToArchive(const hkpMoppCode* code, hkOArchive &outputArchive)
{
		// Write out the header info
	outputArchive.writeFloat32(code->m_info.m_offset(0));
	outputArchive.writeFloat32(code->m_info.m_offset(1));
	outputArchive.writeFloat32(code->m_info.m_offset(2));
	outputArchive.writeFloat32(code->m_info.m_offset(3));
			
		// Write out the MOPP byte code size
	outputArchive.write32(code->m_data.getSize());
			
		// Write out the byte code
	outputArchive.writeRaw(&code->m_data[0], code->m_data.getSize());
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
