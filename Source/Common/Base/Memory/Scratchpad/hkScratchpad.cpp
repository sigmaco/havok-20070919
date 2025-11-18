/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/Scratchpad/hkScratchpad.h>



#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#endif



	// using 128k video EDRAM as a scratch pad
#if defined( HK_PLATFORM_PSP ) && 0
	#include <psptypes.h>
	#include <libgu.h>
	#include <geman.h>
	struct  hkPspVmemScratchpad : public hkScratchpad
	{
		hkPspVmemScratchpad()	: hkScratchpad( HK_NULL, 0x20000) 
		{
			// get the address immediately after the VRAM buffer ( may corrupt texture data )
			unsigned char* eDRAM = (unsigned char*)sceGeEdramGetAddr();
			eDRAM += SCEGU_VRAM_BUFSIZE32*2 + SCEGU_VRAM_BUFSIZE;
			m_address = eDRAM;
		}
	};
	HK_SINGLETON_CUSTOM_IMPLEMENTATION(hkScratchpad, hkPspVmemScratchpad);

#elif defined( HK_ARCH_PS2 )
	struct hkPs2Scratchpad : public hkScratchpad
	{
		hkPs2Scratchpad(): hkScratchpad( reinterpret_cast<void*>(0x70000000), 0x4000)	{	}
	};
	HK_SINGLETON_CUSTOM_IMPLEMENTATION(hkScratchpad, hkPs2Scratchpad);

#else
	struct hkFakeScratchpad : public hkScratchpad
	{
		hkFakeScratchpad()	: hkScratchpad( m_buffer, 0x4000)	{		}
		HK_ALIGN16( char m_buffer[0x4000] );
	};
	HK_SINGLETON_CUSTOM_IMPLEMENTATION( hkScratchpad, hkFakeScratchpad );
#endif

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
