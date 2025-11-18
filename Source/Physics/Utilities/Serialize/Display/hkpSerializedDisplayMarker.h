/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_UTILITIES2_SERIALIZE_DISPLAYMARKER_H
#define HK_UTILITIES2_SERIALIZE_DISPLAYMARKER_H
#include <Common/Base/hkBase.h>
/// A marker is a a helper created in Max for instance to give hints or
/// frames of reference for runtime setup functions.
/// Typically used by the hke2xml converter etc.
class hkpSerializedDisplayMarker : public hkReferencedObject
{
	//+vtable(1)
public:
		
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT);
	HK_DECLARE_REFLECTION();

	inline hkpSerializedDisplayMarker();

public:

	hkTransform m_transform; // the transform for this marker.
	hkpSerializedDisplayMarker(hkFinishLoadedObjectFlag) { }
};

#include <Physics/Utilities/Serialize/Display/hkpSerializedDisplayMarker.inl>

#endif // HK_UTILITIES2_SERIALIZE_DISPLAYMARKER_H

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
