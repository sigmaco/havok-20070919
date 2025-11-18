/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Physics/Utilities/CharacterControl/StateMachine/Util/hkpCharacterMovementUtil.h>

void HK_CALL hkpCharacterMovementUtil::calculateMovement(const hkpMovementUtilInput& input, hkVector4& velocityOut)
{
	//
	// Move character relative to the surface we're standing on
	//

	// Construct a frame in world space
	hkRotation surfaceFrame;
	{
		hkVector4 binorm;
		binorm.setCross( input.m_forward, input.m_up  );


		if (binorm.lengthSquared3() < HK_REAL_EPSILON)
		{
			// Bad configuration space
			return;
		}
		binorm.normalize3();

		hkVector4 tangent;
		tangent.setCross( binorm, input.m_surfaceNormal );
		tangent.normalize3();
		binorm.setCross( tangent, input.m_surfaceNormal );
		binorm.normalize3();

		surfaceFrame.setCols(tangent, binorm, input.m_surfaceNormal);
	}

	// Calculate the relative velocity in the surface Frame
	hkVector4 relative;
	{
		relative.setSub4(input.m_currentVelocity, input.m_surfaceVelocity);
		relative.setRotatedInverseDir(surfaceFrame, relative);
	}

	// Calulate the difference between our desired and relative velocity
	hkVector4 diff;
	{
		diff.setSub4(input.m_desiredVelocity, relative);

		// Clamp the difference - can't be more than the max acceleration allowed
		if ( hkReal(diff.lengthSquared3()) * input.m_gain > (input.m_maxVelocityDelta * input.m_maxVelocityDelta) )
		{
			diff.normalize3();
			diff.mul4( input.m_maxVelocityDelta / input.m_gain );
		}
	}

	// Apply feedback controller in the local frame
	relative.setAddMul4(relative, diff, input.m_gain);
	
	// Transform back to world space and apply
	velocityOut.setRotatedDir(surfaceFrame, relative);

	// Add back in the surface velocity
	velocityOut.add4(input.m_surfaceVelocity);
	HK_ASSERT(0x447a0360,  velocityOut.isOk3() );
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
