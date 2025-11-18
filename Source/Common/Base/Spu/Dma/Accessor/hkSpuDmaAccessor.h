/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_DMA_ACCESSOR_H
#define HK_SPU_DMA_ACCESSOR_H


	/// This class implements a triple-buffering scheme, where 
	///  - one buffer is used to do work, 
	///  - another is used to prefetch more data
	///  - yet another is kept until write-back of processed data is finished.
	///
	/// To use it simply initialize the accessor with data pointer & data size in the main memory, 
	/// and with a memory block to be used on spu.
	/// Then control the progress through the buffer calling controlBufferProgress() which updates the currentPositionOnSpu pointer.
	/// Once done -- start & then finish flush().
class hkSpuDmaAccessor
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuDmaAccessor );

		HK_FORCE_INLINE hkSpuDmaAccessor();

		HK_FORCE_INLINE ~hkSpuDmaAccessor();

			/// Initialize the accessor on a memory block.
			///  - bufferInMainMemory must be of size == 3*(2*overflowBufferSize + baseBufferSize)
			///  - size if a reference size of the buffer in main memory -- used only to assert that we're not past the buffer's end when reading or writing back.
						void startInit(HK_CPU_PTR(void*) bufferInMainMemory, int size, void* bufferOnSpu, int baseBufferSize, int overflowBufferSize, int firstDmaGroup, hkBool initAllToZero = false);

			/// This waits for the first work buffer to be ready to use.
		HK_FORCE_INLINE void finishInit();

			/// To be used once only -- get's the initial position in the work buffer (only valid before the first call to controlBufferProgress)
		HK_FORCE_INLINE void* getInitialBufferPosition() { return m_workInfo->m_startMarker; }

			/// Finish a write and set end-of-written-data position
		HK_FORCE_INLINE void controlBufferProgress(void*& currentPositionOnSpu);

			/// Manual flush in case we want to finish writing completely.
						void startFlush(void*& currentPositionOnSpu);

		HK_FORCE_INLINE void finishFlushAndClose();


		static HK_FORCE_INLINE int getMemoryNeededForBufferSizes(int baseBufferSize, int overflowBufferSize)
		{
			int size = 3 * (overflowBufferSize + baseBufferSize + overflowBufferSize);
			return HK_NEXT_MULTIPLE_OF(128, size );
		}

	private:

			// switches buffers and returns the new currentPositionOnSpu
		void* switchBuffers(void* currentPositionOnSpu);

	protected:

		//
		// buffers
		// 	
		struct BufferInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuDmaAccessor::BufferInfo );
				// Absolute start of the buffer memory.
			hkPadSpu<void*> m_buffer;
				// Start of data in the buffer (needed to know where to start writing back from).
			hkPadSpu<void*> m_startOfData;
				// Start marker. When reading data, you start reading into the buffer starting at this marker.
			hkPadSpu<void*> m_startMarker;
				// Terminal marker. When working on data, you switch buffers once you go pass this marker.
			hkPadSpu<void*> m_terminalMarker;
				// DmaManager's group to be used for this buffer's dma operations
			hkPadSpu<int> m_dmaGroup;

#		if defined(HK_PLATFORM_WIN32)
				// Debug variable needed to supply dma data to the performFinalChecks() function.
			hkPadSpu<HK_CPU_PTR(void*)> m_mainMemPtrForFinalChecks;
				// Debug variable needed to supply dma data to the performFinalChecks() function.
			hkPadSpu<int> m_mainMemSizeForFinalChecks;
#		endif


		};

		hkPadSpu<hkBool32> m_initAllToZero;

		BufferInfo m_bufferInfos[3];

		// Three buffer info pointers
		hkPadSpu<BufferInfo*> m_prefetchInfo;
		hkPadSpu<BufferInfo*> m_workInfo;
		hkPadSpu<BufferInfo*> m_writeInfo;

		//
		//
		//
		//  |-----|----------------|-----|
		//  |     |                \bufferTerminalMarker
		//  |     \bufferStartMarker
		//  \buffer
		//     . startOfData is in the range [buffer, bufferStartmarker] and tells where the data to be written out later starts
		//
		//  Operation:
		//  1. initially start reading into work- & prefetch- buffers; wait for the work buffer to finish reading
		//      - when reading, we always fill the buffer from the bufferStartMarker to the end of the buffer.
		//  
		//        |current pos
		//        rrrrrrrrrrrrrrrrrrrrrrr  data read
		//  |-----|----------------|-----|
		//  
		//  2. use the work buffer. 
		//  3. once we get past the terminal marker we:
		//      - write out from startOfData to currentPosition
		//      - copy data from curretnPosition to the end of buffer to corresponding location at the beginning of the prefetch buffer -- right before the data that was dma'd in
		//      - mark the next buffer as the work buffer
		//      - trigger a dma read to the yet next buffer.
		//
		//  
		//  buffer n
		//                            |current pos
		//        wwwwwwwwwwwwwwwwwwwwccc  data written out / data copied to the next buffer  
		//  |-----|----------------|-----|
		//  
		//
		//  buffer n+1                
		//     |new current pos
		//     cccrrrrrrrrrrrrrrrrrrrrrrr  data copied from the previous buffer / more data dma'ed in
		//  |-----|----------------|-----|
		//
		//
		//


			// The size of the base buffer
		hkPadSpu<int> m_baseBufferSize;

			// The size of the overflow buffer
		hkPadSpu<int> m_overflowBufferSize;

		//	// The current position in the buffer we are currently writing to
		//hkPadSpu<void*> m_currentPositionInWorkBuffer;


		//
		// Destination 
		//

			// Start of the buffer in main memory
		hkPadSpu<HK_CPU_PTR(void*)> m_bufferStartInMainMemory;

			// Current read position in the destination buffer in main memory
		hkPadSpu<HK_CPU_PTR(void*)> m_currentReadPositionInMainMemory;

			// Current write position in the destination buffer in main memory
		hkPadSpu<HK_CPU_PTR(void*)> m_currentWritePositionInMainMemory;

			// End of the buffer in main memory
		hkPadSpu<HK_CPU_PTR(void*)> m_bufferEndInMainMemory;

};


#include <Common/Base/Spu/Dma/Accessor/hkSpuDmaAccessor.inl>



#endif // HK_SPU_DMA_ACCESSOR_H

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
