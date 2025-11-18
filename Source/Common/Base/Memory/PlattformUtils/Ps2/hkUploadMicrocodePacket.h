/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


// Sets the method that hkUploadMicrocodePacket uses to wait for a
// DMA upload to complete.
enum hkDmaWaitCheck
{	
	USE_DSTAT,
	USE_BC0F
};

extern	"C"
{
	// Upload a microcode packet	
	void	hkUploadMicrocodePacket (void* microcodePacketStart, void* microcodePacketEnd );

	// Set the function that hkUploadMicrocodePacket uses to check that the DMA upload
	// Has completed. The two methods available are to check DSTAT which goes over the main
	// bus or to use BC0F which checks the COP1.
	void	hkSetUploadMicrocodePacketDmaWaitCheck( hkDmaWaitCheck dmaWaitCheckType );

	// Get the size in bytes of the solver microcode packet.
	hkUlong hkGetSizeInBytesOfSolverMicrocodePacket( );

	// NOTE: Only use for debugging purposes. hkUploadMicrocodePacket should always upload microcode
	// packets for correct operation of the engine..
	// Sets a flag [0|1] that determines whether hkUploadMicrocodePacket only uploads the solver
	// code once only. To reset call with [0], the next time hkUploadMicrocodePacket is called this will
	// result in normal operation.
	void	hkSetUploadMicrocodePacketOnce( int flag );
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
