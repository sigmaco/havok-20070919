/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_SERIALIZE_RESOURCE_H
#define HK_SERIALIZE_RESOURCE_H

	/// Abstract base class for resources which require cleanup.
class hkResource : public hkReferencedObject
{
	public:

			/// Object which this resource provides.
		struct Export
		{
				/// Symbol of exported object.
			const char* name;
				/// Exported object pointer.
			void* data;

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SERIALIZE, hkResource::Export );
		};

			/// Object which this resource requires.
		struct Import
		{
				/// Symbol of imported object.
			const char* name;
				/// Location inside this resource which points to the Export with the same name.
			void** location;

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SERIALIZE, hkResource::Import );
		};

	public:

			/// Get the name of this resource.
		virtual const char* getName() const = 0;

			/// Destroy the resource data.
			/// All contained objects are first destroyed then any allocated
			/// memory is freed.  See also callDestructors().
		virtual ~hkResource() { }

			/// Destruct objects.
			/// This method is separate from ~hkResource() because if multiple
			/// resources reference each other, it will usually be necessary to perform
			/// two passes. e.g because otherwise the destructors could call removeReference
			/// on freed memory. The first pass calls all destructors. The second pass frees memory.
		virtual void callDestructors() { }

			/// Get a list of the imports/exports from this resource.
		virtual void getImportsExports( hkArray<Import>& impOut, hkArray<Export>& expOut ) = 0;
};

#endif // HK_SERIALIZE_RESOURCE_H

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
