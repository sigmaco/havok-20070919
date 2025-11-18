/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_DMA_SPARSE_WRITER_H
#define HK_SPU_DMA_SPARSE_WRITER_H


	/// A double-buffered dma writer class.
	/// <ag.todo.aa> fix reference manual comments
	/// This writer class holds two separate buffers, each of them consisting of a base part and an overflow part.
	/// Requesting a buffer using requestBuffer() returns a valid pointer to local spu memory ready for
	/// writing. The user has to assert that he is not writing more data than can actually be stored inside
	/// a single one of the two buffers (i.e. not more than base + overflow size). When writing is officially
	/// finished by the user with finishWrite() the writer will itself dma-out the contents of the current
	/// buffer if it has already completely filled its base part and switch to the second buffer for
	/// future writing. As long as the base part of the currenty active buffer is not filled completely, no
	/// dma writing will take place.
class hkSpuDmaSparseWriter
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuDmaSparseWriter );

		HK_FORCE_INLINE hkSpuDmaSparseWriter();

			// overflow buffer must take account for the padding too..
		HK_FORCE_INLINE void init(void* bufferOnSpu, int baseBufferSize, int overflowBufferSize, int firstDmaGroup);

		HK_FORCE_INLINE ~hkSpuDmaSparseWriter();

		void putToMainMemorySmall64(hkReal val0, hkReal val1, HK_CPU_PTR(void*) dstInMainMemory);

		void putToMainMemorySmall128(hkReal val0, hkReal val1, hkReal val2, hkReal val3, HK_CPU_PTR(void*) dstInMainMemory);

			/// Manual flush in case we want to finish writing completely.
		void flush();

	private:

		void writeBackBuffer();

public:

		//
		// Temporary buffers
		// 
		struct BufferInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuDmaSparseWriter::BufferInfo );
				// Buffer start
			hkPadSpu<void*> m_buffer;

				// Buffer overflow area start
			hkPadSpu<void*> m_terminalMarker;

				// Dma group to be used for sending data in that buffer.
			hkPadSpu<int>   m_dmaGroup;
		};

		BufferInfo m_bufferInfos[2];

			// Current write buffer
		BufferInfo* m_workBufferInfo;
			// Second buffer used in the background to send stuff
		BufferInfo* m_transferBufferInfo;
		

			// The current position in the buffer we are currently writing to.
		hkPadSpu<void*> m_currentPositionInWorkBuffer;

		hkPadSpu<int>	m_overflowBufferSize;

};



#include <Common/Base/Spu/Dma/SparseWriter/hkSpuDmaSparseWriter.inl>



#endif // HK_SPU_DMA_SPARSE_WRITER_H

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
