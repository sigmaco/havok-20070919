/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_INTERNAL_1AXIS_SWEEP_H
#define HK_INTERNAL_1AXIS_SWEEP_H

#include <Common/Base/hkBase.h>
#include <Physics/Collide/Shape/hkpShape.h>
#include <Physics/Internal/Collide/BroadPhase/hkpBroadPhase.h>

class hkShapeKeyPair;
class hk1AxisSweep
{
	public:

		struct AabbInt : public hkAabbUint32
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hk1AxisSweep::AabbInt );

			//hkUint32 m_min[3];
			//hkUint32 m_shapeKey;
			//hkUint32 m_max[3];
			//hkUint32 m_originalObjectIndex;

			HK_FORCE_INLINE hkUint32 yzDisjoint( const AabbInt& other ) const
			{
				hkUint32 yab = m_max[1] - other.m_min[1];
				hkUint32 yba = other.m_max[1] - m_min[1];
				hkUint32 zab = m_max[2] - other.m_min[2];
				hkUint32 zba = other.m_max[2] - m_min[2];
				hkUint32 combined = (yab | yba) | (zab | zba);
				return combined & 0x80000000;
			}

			hkpShapeKey& getShapeKey() { return m_min[3]; }
			const hkpShapeKey& getShapeKey() const { return m_min[3]; }

			HK_FORCE_INLINE bool operator<(const hk1AxisSweep::AabbInt& aabb1) const
			{
				return this->m_min[0] < aabb1.m_min[0];
			}


			static HK_FORCE_INLINE bool HK_CALL less(const hk1AxisSweep::AabbInt& aabb0, const hk1AxisSweep::AabbInt& aabb1)
			{
				return aabb0.m_min[0] < aabb1.m_min[0];
			}

			void operator=( const AabbInt& other )
			{
				hkString::memCpy16<sizeof(AabbInt)>( this, &other );
			}
		};

			/// This returns all overlapping Aabb paris, where one aabb is from the first list, and the other from the second list.
			/// Both lists must be appended with four Aabb elements, where aabb.m_min[0] == HK_REAL_MAX.
			/// numA/numB should be equal to the actual number of elements excluding the padding aabbs.
		static int HK_CALL collide( const AabbInt* pa, int numA, const AabbInt* pb, int numB, hkShapeKeyPair* HK_RESTRICT pairsOut, int maxNumPairs, int& numPairsSkipped);
};





#endif // HK_INTERNAL_1AXIS_SWEEP_H

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
