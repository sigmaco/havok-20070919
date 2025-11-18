/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Visualize/hkVisualize.h>
#include <Common/Base/Config/hkConfigVersion.h>

#include <Common/Visualize/hkVersionReporter.h>
#include <Common/Visualize/Serialize/hkDisplaySerializeOStream.h>

// Protocal Revision Information
// Must be updated for any change to the visual debugger protocal
// Extensions to the protocal do not necessarily make the the client
// and server incompatible.
//
// Client can support more packets then the server is going to send...
// Server can send packets and the client can ignore them.
// Visa-versa for both of the above.
//
// If an existing packet changes its format then the minimum version
// must be updated to match the new protocal.
// (Unless the packet has an internal versioning system.)
//
// Date      Date      Version   Information
// (HEAD)    (Release) ver(min)
// --------- --------- --------- -----------------------------------------
// 20030430  ?         200(200)  First versioned protocal version. (BC)
//
// 

int hkVersionReporter::m_protocalMinimumCompatible = 2300;
int hkVersionReporter::m_protocalVersion = 4510; // stats changed for 3.2, new instance geom for 4.5, 3d text support in 4.5.1. 

// read as XYY -> vX.YY

#if defined(HK_PLATFORM_PS2)
#define HK_PLATFORM_INFO_STRING "PS2"
#elif defined(HK_PLATFORM_PS3)
#	if (HK_POINTER_SIZE==8)
#		define HK_PLATFORM_INFO_STRING "PS3_64"
#	else
#		define HK_PLATFORM_INFO_STRING "PS3_32"
#	endif
#elif defined(HK_PLATFORM_WIN32)
#	if (HK_POINTER_SIZE==8)
#		define HK_PLATFORM_INFO_STRING "PC_64"
#	else
#		define HK_PLATFORM_INFO_STRING "PC_32"
#	endif
#elif defined(HK_PLATFORM_XBOX) 
# define HK_PLATFORM_INFO_STRING "XBOX"
#elif defined(HK_PLATFORM_XBOX360) 
# define HK_PLATFORM_INFO_STRING "XBOX360"
#elif defined(HK_PLATFORM_GC)
#define HK_PLATFORM_INFO_STRING "GC"
#if defined(RVL_OS)
#define HK_PLATFORM_INFO_STRING "WII"
#endif
#elif defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_MACPPC)
#define HK_PLATFORM_INFO_STRING "MAC"
#else
#define HK_PLATFORM_INFO_STRING "UNKNOWN"
#endif

hkResult hkVersionReporter::sendVersionInformation( hkStreamWriter* connection )
{
	// send the data chunk describing the version information
	hkArray<char> rawData;
	hkDisplaySerializeOStream commandStream(rawData);

	commandStream.write8u(HK_VERSION_INFORMATION);

	// version and minimum compatible version
	commandStream.write32(m_protocalVersion);
	commandStream.write32(m_protocalMinimumCompatible);

	// send magic platform string
	const char* platformInfo = HK_PLATFORM_INFO_STRING;
	int length = hkString::strLen(platformInfo);
	if(length > 65535)
	{
		length = 65535;
	}
	commandStream.write16u((unsigned short)length);
	commandStream.writeRaw(platformInfo, length);

	// actually write the packet.
	hkDisplaySerializeOStream connectionStream(connection);
	connectionStream.write32( rawData.getSize() );
	connectionStream.writeRaw(rawData.begin(), rawData.getSize());

	return HK_SUCCESS;
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
