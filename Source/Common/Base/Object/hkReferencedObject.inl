/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

HK_FORCE_INLINE hkReferencedObject::hkReferencedObject()
: m_referenceCount(1)
{
}

HK_FORCE_INLINE hkReferencedObject::hkReferencedObject( const hkReferencedObject& originalObject )
: hkBaseObject(), m_referenceCount(1) 
{
}


/*
HK_FORCE_INLINE hkReferencedObject::~hkReferencedObject()
{
#ifdef HK_DEBUG
	extern void HK_CALL hkRemoveReferenceError(const hkReferencedObject*, const char*);

	// if we are in a dtor and the do not delete flag
	// is set then we have call delete on an object that does not own its memory and
	// the dtor should never have been called.
	// But objects which are not new'd will all have random values in this size
	// param and we can't set it in the ctor to something other than 0 as the 
	// the ctor is called after the alloc in hkMemory (where the size mem is set..)
	// if ( m_memSizeAndFlags == 0 ) ..
	
	// reference count is either zero because this method was called 
	// from removeReference or one because we are a local variable.
	if( (m_referenceCount & (~1)) != 0)
	{
		hkRemoveReferenceError(this,"hkReferencedObject destructor");
	}
	// After calling delete the reference count should always be zero. This catches
	// cases where delete is explicitly called.
	m_referenceCount = 0;
#endif
}
*/

HK_FORCE_INLINE void hkReferencedObject::addReference() const
{
	// we don't bother keeping references if the reference is going to be ignored.
	if ( m_memSizeAndFlags != 0 )
	{
	#ifdef HK_DEBUG
		if( m_referenceCount <= 0 )
		{
			extern void HK_CALL hkRemoveReferenceError(const hkReferencedObject*,const char*);
			hkRemoveReferenceError(this, "addReference");
		}
	#endif
		++m_referenceCount;
	}
}

HK_FORCE_INLINE void hkReferencedObject::removeReference() const
{
	if ( m_memSizeAndFlags != 0 )
	{	
	#ifdef HK_DEBUG	
		if( m_referenceCount <= 0 )
		{
			extern void HK_CALL hkRemoveReferenceError(const hkReferencedObject*, const char*);
			hkRemoveReferenceError(this,"removeReference");
		}
	#endif
	
		--m_referenceCount;
    
		if ( m_referenceCount == 0 )
		{
			delete this;
		}
	}
}

HK_FORCE_INLINE int hkReferencedObject::getReferenceCount() const
{
	return m_referenceCount;
}


HK_FORCE_INLINE int hkReferencedObject::getAllocatedSize() const
{
	return m_memSizeAndFlags & MASK_MEMSIZE;
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
