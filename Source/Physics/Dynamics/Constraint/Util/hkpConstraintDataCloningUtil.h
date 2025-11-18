/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_DYNAMICS2_CONSTRAINT_DATA_CLONING_UTIL_H
#define HK_DYNAMICS2_CONSTRAINT_DATA_CLONING_UTIL_H

class hkpConstraintData;

	/// Simple utility for cloning of constraint datas (which reference motors).
class hkpConstraintDataCloningUtil
{
	public:
			/// This creates a clone of the three constraints that can have motors.
			/// Namely hkpLimitedHingeConstraintData, hkpPrismaticConstraintData and hkpRagdollConstraintData.
			/// This does not support the powered chains.
			/// The function return HK_NULL for not supported types of constraints.
		static hkpConstraintData* cloneIfCanHaveMotors(const hkpConstraintData* data);
};

#endif // HK_DYNAMICS2_CONSTRAINT_DATA_CLONING_UTIL_H

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
