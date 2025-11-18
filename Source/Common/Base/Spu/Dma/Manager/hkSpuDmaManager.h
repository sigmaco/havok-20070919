/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_DMA_MANAGER_H
#define HK_SPU_DMA_MANAGER_H

#include <Common/Base/hkBase.h>
#include <Common/Base/Spu/Dma/Utils/hkSpuDmaUtils.h>


#define HK_DMAWAIT_BITSHIFT(GROUP) (1 << GROUP)


	// this structure is an exact copy of 'CellDmaListElement' (as found in the CELL SDK)
struct hkSpuDmaListElement
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkSpuDmaListElement );

	hkUint64	m_notify				:  1;
	hkUint64	m_reserved				: 15;
	hkUint64	m_memoryBlockSize		: 16;
	hkUint64	m_addressInMainMemory	: 32;

	hkSpuDmaListElement()
	{
		m_notify				= 0;
		m_reserved				= 0;
		m_memoryBlockSize		= 0;
		m_addressInMainMemory	= 0;
	}
};


/// Use this for asynchronous or synchronous dmas
class hkSpuDmaManager
{

	public:
		enum READ_MODE
		{
				// use this if you only want a pure read only copy
			READ_ONLY,	
				// use this if you want to copy the data, want to change it but do not want to write it back
			READ_COPY,
			READ_WRITE
		};

			/// Start fetching data from main memory. 
		HK_FORCE_INLINE static void HK_CALL getFromMainMemory(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// Start fetching small data from main memory (1,2,4, or 8 bytes). 
		HK_FORCE_INLINE static void HK_CALL getFromMainMemorySmall(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// Start gathering scattered data from main memory into a contiguous block on spu.
			///
			/// The different source memory blocks are each defined by one entry in the listOnSpu array. The data is written consecutively into dstOnSpu.
			/// Note that the listOnSpu has to be kept in memory and valid until this list-transfer is finished through a waitForDmaCompletion() call.
			/// The spuBufferSize parameter is only used for a buffer overrun test in debug mode.
		HK_FORCE_INLINE static void HK_CALL getFromMainMemoryList(void* dstOnSpu, hkSpuDmaListElement* listOnSpu, int numListEntries, int spuBufferSize, READ_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// adds a value to a variable on the ppu in a thread safe way and returns the old value
		HK_FORCE_INLINE static hkUint32 HK_CALL atomicExchangeAdd(hkUint32* varOnPpu, int increment);
		

		/// Fetch data from main memory. Size must be a multiple of 16 and less than 16k
		///
		/// Stalls the thread until data has arrived. Note that this might actually stall longer
		/// than necessary if there are any additional ongoing dma's that share the same id.
		static void HK_CALL getFromMainMemoryAndWaitForCompletion(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

		/// Fetch data from main memory. Size must be a multiple of 16 
		///
		/// Stalls the thread until data has arrived. Note that this might actually stall longer
		/// than necessary if there are any additional ongoing dma's that share the same id.
		static void HK_CALL getFromMainMemoryLargeAndWaitForCompletion(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// Fetch a small amount of data from main memory (1,2,4, or 8 bytes).
			///
			/// Stalls the thread until data has arrived. Note that this might actually stall longer
			/// than necessary if there are any additional ongoing dma's that share the same id.
		static void HK_CALL getFromMainMemorySmallAndWaitForCompletion(void* dstOnSpu, const HK_CPU_PTR(void*) srcInMainMemory, int size, READ_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// Call this function once you do not need a fetched memory any more. This is only used for debugging on WIN32 and compiles to nothing on PS3
		HK_FORCE_INLINE static void HK_CALL performFinalChecks( const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size );

		HK_FORCE_INLINE static void HK_CALL tryToPerformFinalChecks(const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size );

		HK_FORCE_INLINE static void HK_CALL deferFinalChecksUntilWait(const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size );

		HK_FORCE_INLINE static void HK_CALL abortDebugTracking(const HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size );

		enum WRITE_MODE
		{
			WRITE_BACK,
			WRITE_BACK_SUBSET, 
			WRITE_NEW
		};

			/// Start writing data back to main memory.
		HK_FORCE_INLINE static void HK_CALL putToMainMemory(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// Start writing small amount of data back to main memory (1,2,4, or 8 bytes).
		HK_FORCE_INLINE static void HK_CALL putToMainMemorySmall(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// Start writing data back from a contiguous block of spu memory to scattered main memory addresses
			///
			/// The different destination memory blocks are each defined by one entry in the listOnSpu array. The data is read consecutively from srcOnSpu.
			/// Note that the listOnSpu has to be kept in memory and valid until this list-transfer is finished through a waitForDmaCompletion() call.
			/// The spuBufferSize parameter is only used for a buffer overrun test in debug mode.
		HK_FORCE_INLINE static void HK_CALL putToMainMemoryList(void* srcOnSpu, hkSpuDmaListElement* listOnSpu, int numListEntries, int spuBufferSize, WRITE_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// Write data back to main memory.
			///
			/// Stalls the thread until data has been written. Note that this might actually stall longer
			/// than necessary if there are any additional ongoing dma's that share the same id.
		static void HK_CALL putToMainMemoryAndWaitForCompletion(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);

			/// Write data back to main memory (1,2,4, or 8 bytes).
			///
			/// Stalls the thread until data has been written. Note that this might actually stall longer
			/// than necessary if there are any additional ongoing dma's that share the same id.
		static void HK_CALL putToMainMemorySmallAndWaitForCompletion(HK_CPU_PTR(void*) dstInMainMemory, const void* srcOnSpu, int size, WRITE_MODE mode, int dmaGroupId = HK_SPU_DMA_GROUP_STALL);


			/// Stall the thread until dma for the supplied group is finished.
			///
			/// (i.e. wait until all data from the dmaGroupId group is available or has been written).
		HK_FORCE_INLINE static void HK_CALL waitForDmaCompletion(int dmaGroupId = HK_SPU_DMA_GROUP_STALL );

			/// Stall the thread until dma for all supplied group (defined by a bitfield) are finished.
		HK_FORCE_INLINE static void HK_CALL waitForDmaCompletionUsingBitfield(int dmaGroupMask = HK_DMAWAIT_BITSHIFT(HK_SPU_DMA_GROUP_STALL) );

			/// Stall the thread until all dma has been finished.
		HK_FORCE_INLINE static void HK_CALL waitForAllDmaCompletion();

			/// this function converts the internal logic from READ_ONLY to READ_WRITE 
			///
			/// you can only do this after the calls to getFromMainMemory(READ_ONLY) and waitDmaGroup() have returned
			/// note: it is actually ok to call this function when already in READ_WRITE mode; it will immediately return then.
			// note: this is currently only used for contact constraints as all atoms are DMAed as READ_ONLY, yet
			// contact constraints need to write-back data to ppu
		HK_FORCE_INLINE static void HK_CALL convertReadOnlyToReadWrite(void* ppuPtr, const void* spuPtr, int size);

};


#if defined HK_PLATFORM_PS3SPU

#	define HK_SPU_DMA_PERFORM_FINAL_CHECKS(DEST, SRC, SIZE) 
#	define HK_SPU_DMA_TRY_TO_PERFORM_FINAL_CHECKS(DEST, SRC, SIZE)
#	define HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT(DEST, SRC, SIZE)
#	define HK_SPU_DMA_ABORT_DEBUG_TRACKING(DEST, SRC, SIZE)

#	include <Common/Base/Spu/Dma/Manager/Ps3/hkPs3SpuDmaManager.inl>

#elif defined HK_SIMULATE_SPU_DMA_ON_CPU

#	define HK_SPU_DMA_PERFORM_FINAL_CHECKS(DEST, SRC, SIZE)				hkSpuDmaManager::performFinalChecks			(DEST, SRC, SIZE)
#	define HK_SPU_DMA_TRY_TO_PERFORM_FINAL_CHECKS(DEST, SRC, SIZE)		hkSpuDmaManager::tryToPerformFinalChecks	(DEST, SRC, SIZE)
#	define HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT(DEST, SRC, SIZE)	hkSpuDmaManager::deferFinalChecksUntilWait	(DEST, SRC, SIZE)
#	define HK_SPU_DMA_ABORT_DEBUG_TRACKING(DEST, SRC, SIZE)				hkSpuDmaManager::abortDebugTracking			(DEST, SRC, SIZE)

#	include <Common/Base/Spu/Dma/Manager/SpuSim/hkWin32SpuDmaManager.inl>

#else

#	define HK_SPU_DMA_PERFORM_FINAL_CHECKS(DEST, SRC, SIZE) 
#	define HK_SPU_DMA_TRY_TO_PERFORM_FINAL_CHECKS(DEST, SRC, SIZE)
#	define HK_SPU_DMA_DEFER_FINAL_CHECKS_UNTIL_WAIT(DEST, SRC, SIZE)
#	define HK_SPU_DMA_ABORT_DEBUG_TRACKING(DEST, SRC, SIZE)

#	include <Common/Base/Spu/Dma/Manager/Empty/hkEmptySpuDmaManager.inl>

#endif


#endif // HK_SPU_DMA_MANAGER_H


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
