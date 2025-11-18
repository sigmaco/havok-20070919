/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKBASE_HKREFERENCEDOBJECT_H
#define HKBASE_HKREFERENCEDOBJECT_H

extern const hkClass hkReferencedObjectClass;

class hkStatisticsCollector;

/// Base for all classes in the Havok SDK.
/// All core SDK objects that can be owned by multiple owners inherit from this class -
/// rigid bodies, constraints, and actions are all hkReferencedObjects
/// and any object that is memory managed by Havok also inherits from it.
class hkReferencedObject : public hkBaseObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS);
		HK_DECLARE_REFLECTION();

			/// Creates a new referenced object with an initial reference count of 1.
		HK_FORCE_INLINE hkReferencedObject();

			/// Copy constructor, any default subclass's copy constructor will correctly initialize reference count to 1.
		HK_FORCE_INLINE hkReferencedObject( const hkReferencedObject& originalObject );

			/// Destroy this object.
		virtual ~hkReferencedObject() { }

			/// Adds a reference to the object - this increments the reference count.
		HK_FORCE_INLINE void addReference() const;

			/// Removes a reference to the object - this decrements the reference count.
		HK_FORCE_INLINE void removeReference() const;

			/// Returns the current reference count. Used for debugging only.
		HK_FORCE_INLINE int getReferenceCount() const;

			/// Returns the size of this object
			/// A memory size of 0 is a special case and indicates
			/// that the object should not be freed (as it has
			/// probably been read in from a packed file for instance)
			/// or is embedded in another structure
		HK_FORCE_INLINE int getAllocatedSize() const;

#if !defined(HK_PLATFORM_SPU)
			/// Generate statistics (currently memory information only)
			/// See the hkStatisticsCollector class for more information.
        virtual void calcStatistics( hkStatisticsCollector* collector ) const;
            /// Calculates the statistics for the contained members. Will not call beginObject/endObject
            /// If cls is HK_NULL an implementation must implement the traversal, as a default traversal is unable to
            /// be performed.
        virtual void calcContentStatistics( hkStatisticsCollector* collector,const hkClass* cls ) const;
#endif

	public:

		enum
		{
			MASK_MEMSIZE = 0x7fff // limits mem size of a object to 32K.  Leaves the upper bit for a flag (used to have some, none at the moment).
		};

			/// Stores the object's size for use by the memory manager.
			/// See the hkBase user guide to find out more about this.
			/// Top bit is used as a flag (no current internal usage)
			/// Bottom 15 bits are for the memory size.
			/// A memory size of 0 is a special case and indicates
			/// that the object should not be freed (as it has
			/// probably been read in from a packed file for instance)
		hkUint16 m_memSizeAndFlags; //+nosave

			/// Reference count. Note that if m_memSizeAndFlags == 0,
			/// reference counting is disabled for this object.
		mutable hkInt16 m_referenceCount; //+nosave

	public:

		hkReferencedObject( class hkFinishLoadedObjectFlag flag ) : m_referenceCount(1) {}
};

#include <Common/Base/Object/hkReferencedObject.inl>

#endif // HKBASE_HKREFERENCEDOBJECT_H

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
