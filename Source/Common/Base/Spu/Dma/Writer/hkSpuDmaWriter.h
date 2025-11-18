/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_DMA_WRITER_H
#define HK_SPU_DMA_WRITER_H



/// A double-buffered dma writer class.
///
/// This writer class holds two separate buffers, each of them consisting of a base part and an overflow part.
/// Requesting a buffer using requestBuffer() returns a valid pointer to local spu memory ready for
/// writing. The user has to assert that he is not writing more data than can actually be stored inside
/// a single one of the two buffers (i.e. not more than base + overflow size). When writing is officially
/// finished by the user with finishWrite() the writer will itself dma-out the contents of the current
/// buffer if it has already completely filled its base part and switch to the second buffer for
/// future writing. As long as the base part of the currenty active buffer is not filled completely, no
/// dma writing will take place.
class hkSpuDmaWriter
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuDmaWriter );

		HK_FORCE_INLINE hkSpuDmaWriter();

		HK_FORCE_INLINE void init(HK_CPU_PTR(void*) dstInMainMemory, int size, void* bufferOnSpu, int baseBufferSize, int overflowBufferSize, int dmaGroup0, int dmaGroup1);

		HK_FORCE_INLINE ~hkSpuDmaWriter();

			/// Returns pointer to a continuous buffer
		HK_FORCE_INLINE void* requestBuffer();

			/// Finish a write and set end-of-written-data position
		HK_FORCE_INLINE void finishWrite(void* currentPositionOnSpu);

			/// Get the main memory address where the writer is currently pointing to.
			/// Note that this value is not accurate between calls to requestBuffer() and finishWrite().
		HK_FORCE_INLINE void* getCurrentDestInMainMemory();

			/// Manual flush in case we want to finish writing completely.
		void flush();

	private:


		void writeBackBuffer(int sizebufferUsed);


	protected:

		//
		// Temporary buffers
		// 
		
			// Current write buffer
		hkPadSpu<void*> m_workBuffer;
			// DmaManager's group to be used for each of the buffer's writebacks
		hkPadSpu<int> m_workDmaGroup;

			// Second buffer used in the background to send stuff
		hkPadSpu<void*> m_transferBuffer;
			// DmaManager's group to be used for each of the buffer's writebacks
		hkPadSpu<int> m_transferDmaGroup;

			// The size of the base buffer
		hkPadSpu<int> m_baseBufferSize;


			// The current position in the buffer we are currently writing to
		hkPadSpu<void*> m_currentPositionInWorkBuffer;


		//
		// Destination 
		//

			// Current position in the destination buffer in main memory
		hkPadSpu<HK_CPU_PTR(void*)> m_currentDstPosition;



		//
		// Other helpers for debugging
		//
			// End of the destination buffer in main memory
		hkPadSpu<HK_CPU_PTR(void*)> m_dstEnd;

		hkPadSpu<int> m_wasBufferRequested;

			// The size of the overflow buffer
		hkPadSpu<int> m_overflowBufferSize;

};



#include <Common/Base/Spu/Dma/Writer/hkSpuDmaWriter.inl>



#endif // HK_SPU_DMA_WRITER_H

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
