/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_DMA_READER_H
#define HK_SPU_DMA_READER_H


	/// This class implements a double-buffering scheme, where 
	///  - one buffer is used to do work, 
	///  - another is used to prefetch more data
	///
	/// To use it simply initialize the reader with data pointer & data size in the main memory, 
	/// and with a memory block to be used on spu.
	/// Then control the progress through the buffer calling controlBufferProgress() which updates the currentPositionOnSpu pointer.
	/// Once done -- start & then finish flush().
	///
	/// This class is a cut-down version of hkSpuDmaAccessor. To see more detailed information on its internals look at the hkSpuDmaAccessor.
class hkSpuDmaReader
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuDmaReader );

		HK_FORCE_INLINE hkSpuDmaReader();

		HK_FORCE_INLINE ~hkSpuDmaReader();

			/// Initialize the reader on a memory block.
			///  - bufferInMainMemory must be of size == 2*(2*overflowBufferSize + baseBufferSize)
			///  - size if a reference size of the buffer in main memory -- used only to assert that we're not past the buffer's end when reading or writing back.
						void startInit(const HK_CPU_PTR(void*) bufferInMainMemory, int size, void* bufferOnSpu, int baseBufferSize, int overflowBufferSize, int firstDmaGroup);

			/// This waits for the first work buffer to be ready to use.
		HK_FORCE_INLINE void finishInit();

			/// To be used once only -- get's the initial position in the work buffer (only valid before the first call to controlBufferProgress)
		HK_FORCE_INLINE const void* getInitialBufferPosition() { return m_workInfo->m_startMarker; }

			/// Mark where used data, that will not be referenced anymore, ends.
		HK_FORCE_INLINE void controlBufferProgress(const void*& currentPositionOnSpu);

			/// Closes the reader, and waits for any outstanding dma's to finish.
		HK_FORCE_INLINE void waitForDmaAndClose();

		static HK_FORCE_INLINE int getMemoryNeededForBufferSizes(int baseBufferSize, int overflowBufferSize)
		{
			int size = 2 * (overflowBufferSize + baseBufferSize + overflowBufferSize);
			return HK_NEXT_MULTIPLE_OF(128, size );
		}

	private:

		const void* switchBuffers(const void* currentPositionOnSpu);

	protected:

		//
		// buffers
		// 
		
		struct BufferInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuDmaReader::BufferInfo );
				// Absolute start of the buffer memory.
			hkPadSpu<void*> m_buffer;
				// Start marker. When reading data, you start reading into the buffer starting at this marker.
			hkPadSpu<void*> m_startMarker;
				// Terminal marker. When working on data, you switch buffers once you go pass this marker.
			hkPadSpu<void*> m_terminalMarker;
				// DmaManager's group to be used for this buffer's dma operations
			hkPadSpu<int> m_dmaGroup;

#		if defined(HK_PLATFORM_WIN32)
				// Debug variable needed to supply dma data to the performFinalChecks() function.
			hkPadSpu<HK_CPU_PTR(const void*)> m_mainMemPtrForFinalChecks;
				// Debug variable needed to supply dma data to the performFinalChecks() function.
			hkPadSpu<int> m_mainMemSizeForFinalChecks;
#		endif


		};

		BufferInfo m_bufferInfos[2];

		// Three buffer info pointers
		hkPadSpu<BufferInfo*> m_prefetchInfo;
		hkPadSpu<BufferInfo*> m_workInfo;

			// The size of the base buffer
		hkPadSpu<int> m_baseBufferSize;

			// The size of the overflow buffer
		hkPadSpu<int> m_overflowBufferSize;


		//
		// Destination 
		//

			// Beginning of the buffer to be read. Stored to enable resetting of the reader.
		hkPadSpu<HK_CPU_PTR(const void*)> m_bufferStartInMainMemory;

			// Current read position in the destination buffer in main memory
		hkPadSpu<HK_CPU_PTR(const void*)> m_currentReadPositionInMainMemory;

			// End of the buffer in main memory
		hkPadSpu<HK_CPU_PTR(const void*)> m_bufferEndInMainMemory;

};


#include <Common/Base/Spu/Dma/Reader/hkSpuDmaReader.inl>



#endif // HK_SPU_DMA_READER_H

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
