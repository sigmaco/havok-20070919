/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/PlattformUtils/Ps2/hkUploadMicrocodePacket.h>

#include <eeregs.h>
#include <libdma.h>

static void useDstat()
{	
	while( !(*D_STAT & 1))
	{
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
	}
}

static void useBc0f()
{
	// block while waiting for dma to end
	//	if (block) ( Minimum of 5 cycles )
	asm __volatile__("DMACLEAR:");
	asm __volatile__("nop");
	asm __volatile__("nop");
	asm __volatile__("nop");
	asm __volatile__("nop");
	asm __volatile__("bc0f DMACLEAR");
	asm __volatile__("nop");
}

typedef void (*hkDmaWaitCheckFunc)(void);
static hkDmaWaitCheckFunc g_hkDmaWaitCheck = useBc0f;

#if ( HK_COMPILER_GCC_VERSION >= 30200 ) && !defined( HK_COMPILER_SNC )
static int g_hkUploadMicrocodePacketOnceOnly = 1;
#else
static int g_hkUploadMicrocodePacketOnceOnly = 0;
#endif

static int g_hkUploadMicrocodePacketUploaded = 0;

void hkSetUploadMicrocodePacketDmaWaitCheck( hkDmaWaitCheck dmaWaitCheckType )
{
	switch ( dmaWaitCheckType )
	{
		case USE_DSTAT :
		{
			g_hkDmaWaitCheck = useDstat;
			break;
		}
		case USE_BC0F :
		{
			g_hkDmaWaitCheck = useBc0f;
			break;
		}
		default:
			HK_ASSERT2(0x0f4f6b1e, 0, "Unknown hkDmaWaitCheck enumerated type specified, defaulting to using DSTAT.");
			g_hkDmaWaitCheck = useDstat;
			break;
	}
}

void hkSetUploadMicrocodePacketOnce( int flag )
{
	g_hkUploadMicrocodePacketOnceOnly = flag;
	g_hkUploadMicrocodePacketUploaded = 0;
}

void hkUploadMicrocodePacket (void* microcodePacketStart, void* microcodePacketEnd )

{
	if (!g_hkUploadMicrocodePacketUploaded || !g_hkUploadMicrocodePacketOnceOnly)
	{
		// set the uploaded flag
		g_hkUploadMicrocodePacketUploaded = 1;
		
		// Sanity check
		HK_ASSERT2(0x6a682dc7, (((unsigned int)microcodePacketStart & 0xf) == 0), "Microcode packet must start on 128 bit / 16 byte boundary - please check you have aligned the .vudata and .vutext sections");
		
		// calculate length of packet in quad words

		int size16 = ( (unsigned int)(microcodePacketEnd) - (unsigned int)(microcodePacketStart) ) >> 4;
		size16 += 1;
		*D0_QWC = size16;

		// set D_STAT and D_PCR

		*D_STAT		= 1;
		*D_PCR		= 1;

		// point DMA source memory address to start of packet

		*D0_MADR	= (unsigned int)microcodePacketStart;


		// Ensure that the channel interrupt mask is disabled.
		// The original state is restored upon completion.
			
		unsigned int	d_StatState = *D_STAT;
		hkBool		setChannelMask = false;
		
		if( d_StatState & 0x00010000 )
		{
			// Disable channel interrupt mask
			*D_STAT = 0x00010000;
			setChannelMask = true;
		}	
		
		// start DMA transfer

		*D0_CHCR = 0x0100;

		// ensure that memory is synchronised

		__asm__ __volatile__ ("sync.l");
		__asm__ __volatile__ ("sync.p");

		// test for completion
		g_hkDmaWaitCheck();
			
		// Transfer has completed without interrupt generation
		// We can now safely restore the channel interrupt mask
		
		if ( setChannelMask )
		{
			*D_STAT = 0x00010000;
		}
	}	
}

extern unsigned hkSolverMicrocodePacket __attribute__((section(".vudata")));
extern unsigned hkSolverMicrocodePacketEnd __attribute__((section(".vudata")));

hkUlong hkGetSizeInBytesOfSolverMicrocodePacket( )
{
	return hkUlong(&hkSolverMicrocodePacketEnd) - hkUlong(&hkSolverMicrocodePacket);
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
