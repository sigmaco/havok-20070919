/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/SweptTransform/hkSweptTransformUtil.h>


void hkSweptTransformUtil::lerp2( const hkSweptTransform& sweptTrans, hkTime t, hkTransform& transformOut )
{
#if ! defined(HK_PLATFORM_SPU)
	hkReal r = sweptTrans.getInterpolationValue( t );
	_lerp2(sweptTrans, r, transformOut);
#else
	hkSweptTransformUtil::lerp2Ha( sweptTrans, t, 0.0f, transformOut );
#endif
}

void hkSweptTransformUtil::lerp2Ha( const hkSweptTransform& sweptTrans, hkTime t, hkReal tAddOn, hkTransform& transformOut )
{
	hkReal r = sweptTrans.getInterpolationValueHiAccuracy( t, tAddOn );
	_lerp2(sweptTrans, r, transformOut);
}

#if !defined (HK_PLATFORM_SPU)
void hkSweptTransformUtil::lerp2Rel( const hkSweptTransform& sweptTrans, hkReal r, hkTransform& transformOut )
{
	_lerp2(sweptTrans, r, transformOut);
}

	// only updates t1 and 'hkTransform' of the hkSweptTransform
void hkSweptTransformUtil::backStepMotionState( hkTime time, hkMotionState& motionState )
{
	hkSweptTransform& st = motionState.getSweptTransform();
	hkReal t = hkMath::max2( st.getInterpolationValue( time ), HK_REAL_EPSILON);

	_lerp2( st, t, st.m_rotation1 );
	hkReal newInvDeltaTime = st.getInvDeltaTime() / t;

	st.m_centerOfMass1.setInterpolate4( st.m_centerOfMass0, st.m_centerOfMass1, t );
	st.m_centerOfMass1(3) = newInvDeltaTime;
	motionState.m_deltaAngle.mul4( t );

	calcTransAtT1( st, motionState.getTransform());
}

	// resets both t0 and t1 transforms of the hkSweptTransform to the same value and 
	// sets invDeltaTime to zero
void hkSweptTransformUtil::freezeMotionState( hkTime time, hkMotionState& motionState )
{
	hkSweptTransform& st = motionState.getSweptTransform();
	HK_ASSERT2(0xf0ff0082, st.getInvDeltaTime() == 0.0f || (( time  * st.getInvDeltaTime() ) <= ( st.getBaseTime() * st.getInvDeltaTime() ) + 2.0f ) , "Inconsistent time in motion state.");

		// we actually freeze the object at the earliest moment (defined by hkSweptTransform.m_startTime) after 'time'
	time = hkMath::max2(time, st.getBaseTime());
	hkReal t = st.getInterpolationValue( time );

	_lerp2( st, t, st.m_rotation1 );
	st.m_rotation0 = st.m_rotation1;

	st.m_centerOfMass1.setInterpolate4( st.m_centerOfMass0, st.m_centerOfMass1, t );
	st.m_centerOfMass0 = st.m_centerOfMass1;

	// set time information
	st.m_centerOfMass0(3) = time;
	st.m_centerOfMass1(3) = 0.0f;

	calcTransAtT1( st, motionState.getTransform());
}

void hkSweptTransformUtil::setTimeInformation( hkTime startTime, hkReal invDeltaTime, hkMotionState& motionState)
{
	motionState.getSweptTransform().m_centerOfMass0(3) = startTime;
	motionState.getSweptTransform().m_centerOfMass1(3) = invDeltaTime;
}

void hkSweptTransformUtil::warpTo( const hkVector4& position, const hkQuaternion& rotation, hkMotionState& ms )
{
	hkSweptTransform& sweptTransform = ms.getSweptTransform();
	ms.m_deltaAngle.setZero4();

	sweptTransform.m_rotation0 = rotation;
	sweptTransform.m_rotation1 = rotation;

	ms.getTransform().setRotation( rotation );
	ms.getTransform().setTranslation( position );
	
	hkVector4 centerShift;
	centerShift._setRotatedDir( ms.getTransform().getRotation(), sweptTransform.m_centerOfMassLocal );

	hkReal baseTime = sweptTransform.m_centerOfMass0(3);

	sweptTransform.m_centerOfMass0.setAdd4( position, centerShift );
	sweptTransform.m_centerOfMass1 = sweptTransform.m_centerOfMass0;

	sweptTransform.m_centerOfMass0(3) = baseTime;	
	sweptTransform.m_centerOfMass1(3) = 0;	// invDeltaTime
}

void hkSweptTransformUtil::warpTo( const hkTransform& transform, hkMotionState& ms )
{
	hkSweptTransform& sweptTransform = ms.getSweptTransform();
	ms.m_deltaAngle.setZero4();

	hkQuaternion rotation; rotation.set( transform.getRotation() );
	ms.getTransform() = transform;

	sweptTransform.m_rotation0 = rotation;
	sweptTransform.m_rotation1 = rotation;
	
	hkVector4 centerShift;
	centerShift._setRotatedDir( transform.getRotation(), sweptTransform.m_centerOfMassLocal );

	hkReal baseTime = sweptTransform.m_centerOfMass0(3);

	sweptTransform.m_centerOfMass0.setAdd4( transform.getTranslation(), centerShift );
	sweptTransform.m_centerOfMass1 = sweptTransform.m_centerOfMass0;

	sweptTransform.m_centerOfMass0(3) = baseTime;	
	sweptTransform.m_centerOfMass1(3) = 0;	// invDeltaTime
}

void hkSweptTransformUtil::warpToPosition( const hkVector4& position, hkMotionState& ms )
{
	const hkRotation& currentRotation = ms.getTransform().getRotation();
	hkSweptTransform& sweptTransform = ms.getSweptTransform();

	ms.m_deltaAngle.setZero4();
	ms.getTransform().setTranslation( position );

	hkVector4 centerShift;
	centerShift._setRotatedDir( currentRotation, sweptTransform.m_centerOfMassLocal );

	hkReal baseTime = sweptTransform.m_centerOfMass0(3);

	sweptTransform.m_centerOfMass0.setAdd4( position, centerShift );
	sweptTransform.m_centerOfMass1 = sweptTransform.m_centerOfMass0;

	sweptTransform.m_rotation0 = sweptTransform.m_rotation1;

	sweptTransform.m_centerOfMass0(3) = baseTime;	
	sweptTransform.m_centerOfMass1(3) = 0.0f; // invDeltaTime
}

void hkSweptTransformUtil::warpToRotation( const hkQuaternion& rotation, hkMotionState& ms )
{
	warpTo( ms.getTransform().getTranslation(), rotation, ms );
}

void hkSweptTransformUtil::keyframeMotionState( const hkStepInfo& stepInfo, const hkVector4& pos1, const hkQuaternion& rot1, hkMotionState& ms )
{
	hkSweptTransform& sweptTransform = ms.getSweptTransform();

	sweptTransform.m_centerOfMass0 = sweptTransform.m_centerOfMass1;
	sweptTransform.m_rotation0 = sweptTransform.m_rotation1;

	sweptTransform.m_centerOfMass1 = pos1;
	sweptTransform.m_rotation1 = rot1;

	hkQuaternion diff; diff.setMulInverse( rot1, sweptTransform.m_rotation0 );

	hkReal angle =  diff.getAngle();
	hkVector4 axis;
	if ( angle )
	{
		diff.getAxis(axis);
	}
	else
	{
		axis.setZero4();
	}

	ms.m_deltaAngle.setMul4( angle, axis );
	ms.m_deltaAngle(3) = angle;
	
	//
	//	Use the angle to calculate redundant information
	//
	/*
	{
		const hkReal angle2 = angle * angle;
		const hkReal angle3 = angle * angle2;
		const hkReal sa = 0.044203f;
		const hkReal sb = 0.002343f;

			// this is:
			// 2.0f * sin( 0.5f * angle ) / angle
			// and can be used as a factor to m_deltaAngle
			// to get m_deltaAngleLower or the maximum projected distance any
			// point on the unit sphere of the object can travel 
		const hkReal rel2SinHalfAngle = 1.0f - sa * angle2 + sb * angle3;
		const hkReal collisionToleranceEps = 0.01f * 0.01f;
		ms.m_maxAngularError = collisionToleranceEps + ms.m_objectRadius * rel2SinHalfAngle * angle;
	}
	*/

	sweptTransform.m_centerOfMass0(3) = stepInfo.m_startTime;	
	sweptTransform.m_centerOfMass1(3) = stepInfo.m_invDeltaTime;

	calcTransAtT1( sweptTransform, ms.getTransform() );
}

void hkSweptTransformUtil::setCentreOfRotationLocal( const hkVector4& newCenterOfRotation, hkMotionState& motionState)
{
	hkVector4 offset; offset.setSub4(newCenterOfRotation, motionState.getSweptTransform().m_centerOfMassLocal);
	motionState.getSweptTransform().m_centerOfMassLocal = newCenterOfRotation;
	
	hkVector4 offsetWs; offsetWs.setRotatedDir(motionState.getTransform().getRotation(), offset);
	offsetWs.zeroElement(3);
	motionState.getSweptTransform().m_centerOfMass0.add3clobberW(offsetWs);
	motionState.getSweptTransform().m_centerOfMass1.add3clobberW(offsetWs);
}
#endif // spu



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
