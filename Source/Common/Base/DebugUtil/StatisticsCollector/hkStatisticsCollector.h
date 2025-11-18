/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKBASE_HKMONITOR_STATISTICS_COLLECTOR_H
#define HKBASE_HKMONITOR_STATISTICS_COLLECTOR_H


/// This is the interface to a statistics collector for Havok objects. Currently it only
/// collects memory usage statistics but could be extended in future to collect other
/// useful stats. Timing stats are collected separately through the hkMonitorStream.
///
/// All hkReferencedObject in Havok (most user level objects) have the following virtual call:
///
///    virtual void calcStatistics( hkStatisticsCollector* collector ) const { }
///
/// That call fills out the current memory usage of the object's data, excluding what is
/// counted in the m_memSizeAndFlags member of the hkReferencedObject itself. That is
/// to say that the storage for all its members will be automatically in the object size
/// already, but hkArrays for instance have external data storage which the object
/// adds and also lets the collector know of any pointed to, owned, children so it can recurse.
/// Normally the statistics collectors record the memory used the the object
/// (m_memSizeAndFLags + all used (<= allocated, eg: hkArray:getSize())) and also the total
/// allocated (m_memSizeAndFLags + all allocated (eg: hkArray::getCapacity()) ) so that
/// you can work out not only the total memory required but also if there is much wasted memory
class hkStatisticsCollector
{
	public:

		virtual ~hkStatisticsCollector() { m_clientData = 0; }

        /// Identifies the last used bit
        /// If a new StatisticsClass is added this number will need to be updated !
        enum { MAX_STATISTICS_CLASS_BIT = 5 };

		/// The list of available statistics you can gather. Currently only memory statistics
		/// are gathered, but more could be added in future.
		enum StatisticClass
		{
			MEMORY_ALL = 0xf,
				/// All the static objects allocated by the user outside of the engine which can be simultaneously
				/// shared between hkWorlds, e.g. hkShapes, mopp, hkpConstraintData
			MEMORY_SHARED = 1,
				/// All the static objects allocated by the user outside of the engine, except MEMORY_SHARED objects
				/// e.g. hkConstraintsInstance, hkEntities, hkActions
			MEMORY_INSTANCE = 2,
				/// Extra (fixed size) overhead added by the engine for every static object,e.g hkpConstraintRuntime.
			MEMORY_ENGINE = 4,
				/// Everything allocated by the engine, and what the user has no control over:
				/// e.g. agents, arrays, pointerLists
			MEMORY_RUNTIME = 8,
				/// Memory used in demos
			MEMORY_APPLICATION = 16,
				/// Mark the end
			MEMORY_LAST = 32
		};

			/// Start a new named object
			/// Should be put at the start of each object. If a name is given, it overrides the name the parent gave this object
		virtual void beginObject( const char* name, StatisticClass statisticClass, const hkReferencedObject* object ) = 0;

			/// Add a named chunk of memory for the current object. Both used and total allocated are usually given.
		virtual void addChunk( const char* name, StatisticClass statisticClass, const void* chunkAddress, int usedSize, int allocatedSize = 0) = 0;

			/// Add a piece of memory which was allocated using hkAllocate or hkAlignedAllocate
		void addAllocated( const char* name, StatisticClass statisticClass, const void* chunkAddress );

			/// Add a named child object. The object's m_memSizeAndFlags will be added as its size, and then
			/// calcStatistics will be called on the child. If the child has any extra allocated data (hkArrays etc) or children
			/// then the class should implement calcStatistics.
		virtual void addChildObject( const char* name, StatisticClass statisticClass, const hkReferencedObject* object ) = 0;

			/// Add a directory for logically grouping objects
		virtual void pushDir( const char* dirName ) = 0;

			/// End the current directory
		virtual void popDir() = 0;


			/// A convenience templated function to allow an hkArray to be easily added.
		template<typename T>
		HK_FORCE_INLINE void addArray( const char* name, StatisticClass statisticClass, const hkArray<T>& array )
		{
			if ( !(array.m_capacityAndFlags & array.DONT_DEALLOCATE_FLAG) )
			{
				addChunk( name, statisticClass, array.begin(), array.getSize() * hkSizeOf(T), array.getCapacity() * hkSizeOf(T) );
			}
		}

		template<typename T>
		HK_FORCE_INLINE void addSmallArray( const char* name, StatisticClass statisticClass, const hkSmallArray<T>& array )
		{
			if ( !(array.m_capacityAndFlags & array.DONT_DEALLOCATE_FLAG) )
			{
				addChunk( name, statisticClass, array.begin(), array.getSize() * hkSizeOf(T), array.getCapacity() * hkSizeOf(T) );
			}
		}

		template<typename T>
		HK_FORCE_INLINE void addObjectArray( const char* name, StatisticClass statisticClass, const hkObjectArray<T>& array )
		{
			if ( !(array.m_array.m_capacityAndFlags & array.m_array.DONT_DEALLOCATE_FLAG) )
			{
				addChunk( name, statisticClass, array.begin(), array.getSize() * hkSizeOf(T), array.getCapacity() * hkSizeOf(T) );
			}
		}

			/// End the current object.
		virtual void endObject( ) = 0;

	public:
			/// A client data which can be used to pass information from the parent to the child.
			/// For children of hkpWorld this points to the hkpCollisionInput.
		const void* m_clientData;
};


#endif // HKBASE_HKMONITOR_STATISTICS_COLLECTOR_H

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
