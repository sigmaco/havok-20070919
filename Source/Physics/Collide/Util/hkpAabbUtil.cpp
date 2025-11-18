/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Util/hkpAabbUtil.h>

void HK_CALL hkpAabbUtil::calcAabb( const float* vertexArray, int numVertices, int striding, hkAabb& aabbOut )
{
	hkVector4 mi; mi.load3( vertexArray );
	hkVector4 ma; ma = mi;

	for (int i = 1; i < numVertices; i++)
	{
		hkVector4 v; v.load3( hkAddByteOffsetConst(vertexArray, i*striding) );
		mi.setMin4( mi, v );
		ma.setMax4( ma, v );
	}
	aabbOut.m_min.setXYZ0( mi );
	aabbOut.m_max.setXYZ0( ma );
}

#if defined(HK_PLATFORM_SPU)
void HK_CALL hkpAabbUtil::sweepOffsetAabb(const hkpAabbUtil::OffsetAabbInput& input, const hkAabb& aabbIn, hkAabb& aabbOut) 
{
	hkAabbUtil_sweepOffsetAabb(input, aabbIn, aabbOut);
}
#endif

void HK_CALL hkpAabbUtil::initOffsetAabbInput(const hkMotionState* motionState, hkpAabbUtil::OffsetAabbInput& input)
{
	input.m_motionState = motionState;
	input.m_endTransformInv.setInverse(motionState->getTransform());

	const hkSweptTransform& swept = motionState->getSweptTransform();
	swept._approxTransformAt(swept.getBaseTime(), input.m_startTransform);

	if (swept.getInvDeltaTime() != 0.0f)
	{
		const hkReal deltaTime = 1.0f / swept.getInvDeltaTime();
		float deltaAngle = motionState->m_deltaAngle(3);
		if (deltaAngle <= HK_REAL_PI * 0.125f)
		{
			// Just one inter transform
			hkReal cosApprox = 1 - deltaAngle*deltaAngle*0.5f;
			input.m_transforms[0] = input.m_startTransform;
			input.m_transforms[0].getTranslation()(3) = 1.0f / cosApprox;
			input.m_numTransforms = 1;
			return;
		}

		if (deltaAngle <= HK_REAL_PI * 0.25f)
		{
			// Just one inter transform
			hkReal time = swept.getBaseTime() + 0.5f * deltaTime;
			motionState->getSweptTransform()._approxTransformAt(time, input.m_transforms[0]);
			// extended arm for the in-between transforms (cos(22.5deg)
			hkReal cosApprox = 1 - deltaAngle*deltaAngle*0.25f*0.5f;
			input.m_transforms[0].getTranslation()(3) = 1.0f / cosApprox;
			input.m_numTransforms = 1;
			return;
		}

		{
			hkReal parts = (deltaAngle + HK_REAL_PI * 0.125f) / (HK_REAL_PI * 0.125f);
			hkReal partsInv = 1.0f / parts;
			input.m_numTransforms = 0;
			for (hkReal p = 1.0f; p < parts; p += 2.0f)
			{
				hkReal time = swept.getBaseTime() + (p*partsInv) * deltaTime;
				HK_ASSERT2(0xad7644aa, input.m_numTransforms < 4, "The fixed-capacity Transforms array to small. Make it larger.");
				hkTransform& t = input.m_transforms[input.m_numTransforms];
				input.m_numTransforms = input.m_numTransforms + 1;
				motionState->getSweptTransform()._approxTransformAt(time, t);
				t.getTranslation()(3) = 1.0824f;
			}
		}
	}
	else
	{
		input.m_numTransforms = 0;
	}
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
