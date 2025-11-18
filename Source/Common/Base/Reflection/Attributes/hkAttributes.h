/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_ATTRIBUTE_CLASS_H
#define HK_ATTRIBUTE_CLASS_H

#include <Common/Base/Reflection/hkClassMember.h>
#include <Common/Base/Reflection/hkClassEnum.h>
#include <Common/Base/Reflection/hkFinishLoadedObjectFlag.h>
#include <Common/Base/Math/hkMath.h>

extern const hkClass hkRangeRealAttributeClass;

	/// An attribute for specifying the range of possible values for an hkReal.
struct hkRangeRealAttribute
{
	//+defineattribute(true)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_HKCLASS, hkRangeRealAttribute );
		HK_DECLARE_REFLECTION();

		inline hkRangeRealAttribute(hkReal absmin, hkReal absmax, hkReal softmin, hkReal softmax) :
			m_absmin(absmin), m_absmax(absmax), m_softmin(softmin), m_softmax(softmax)
		{
			HK_ASSERT2(0x2fd9e4a5, m_absmin <= m_absmax, "Make sure that absmin is less or equal than absmax.");
			HK_ASSERT2(0x2fd9e4a6, m_softmin <= m_softmax, "Make sure that softmin is less or equal than softmax.");
			HK_ASSERT2(0x2fd9e4a7, m_absmin <= m_softmin && m_softmax <= m_absmax, "Make sure that softmin and softmax are within [absmin,absmax] range.");
		}

			/// The value should never be lower than this.
			/// Default minimum is -HK_REAL_MAX.
		hkReal m_absmin;

			/// The value should never be higher than this.
			/// Default maximum is HK_REAL_MAX.
		hkReal m_absmax;

			/// The value should typically not by lower than this.
		hkReal m_softmin;

			/// The value should typically not be higher than this.
		hkReal m_softmax;
};

extern const hkClass hkRangeInt32AttributeClass;

	/// An attribute for specifying the range of possible values for an hkInt32.
struct hkRangeInt32Attribute
{
	//+defineattribute(true)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_HKCLASS, hkRangeInt32Attribute );
		HK_DECLARE_REFLECTION();
			
		inline hkRangeInt32Attribute(hkInt32 absmin, hkInt32 absmax, hkInt32 softmin, hkInt32 softmax) :
		m_absmin(absmin), m_absmax(absmax), m_softmin(softmin), m_softmax(softmax)
		{
			HK_ASSERT2(0x2fd9e4a8, m_absmin <= m_absmax, "Make sure that absmin is less or equal than absmax.");
			HK_ASSERT2(0x2fd9e4a9, m_softmin <= m_softmax, "Make sure that softmin is less or equal than softmax.");
			HK_ASSERT2(0x2fd9e4b0, m_absmin <= m_softmin && m_softmax <= m_absmax, "Make sure that softmin and softmax are within [absmin,absmax] range.");
		}
			/// The value should never be lower than this.
			/// Default minimum is HK_INT32_MIN.
		hkInt32 m_absmin;

			/// The value should never be higher than this.
			/// Default maximum is HK_INT32_MAX.
		hkInt32 m_absmax;

			/// The value should typically not by lower than this.
		hkInt32 m_softmin;

			/// The value should typically not be higher than this.
		hkInt32 m_softmax;
};

#endif // HK_ATTRIBUTE_CLASS_H

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
