/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Vehicle/hkpVehicle.h>

#include <Physics/Vehicle/Camera/hkp1dAngularFollowCam.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

hkp1dAngularFollowCam::hkp1dAngularFollowCam() :
	m_cameraYawAngle(0),
	m_yawCorrection(0), 
	m_yawSignCorrection(0)
{
	m_upDirWS.setZero4(); 
	m_rigidBodyForwardDir.setZero4();

	m_flat0DirWS.setZero4();
	m_flat1DirWS.setZero4();
}


hkp1dAngularFollowCamCinfo::hkp1dAngularFollowCamCinfo()
{
	m_yawCorrection = 0.0f;
	m_yawSignCorrection = 1.0f;
	m_rigidBodyForwardDir.set( 0.0f, 1.0f, 0.0f);
	m_upDirWS.set( 0.0f, 0.0f, 1.0f );
}


hkp1dAngularFollowCamCinfo::CameraSet::CameraSet()
{
	m_positionUS.set( 0.0f, 12.0f, 5.5f);
	m_lookAtUS.setZero4();

	m_fov = 1.0f;

	m_velocity = 0.0f;
	m_speedInfluenceOnCameraDirection = 0.01f;
	m_angularRelaxation = 4.0f;
}


void hkp1dAngularFollowCam::reinitialize( const hkp1dAngularFollowCamCinfo &bp )
{
	m_yawCorrection = bp.m_yawCorrection;
	m_yawSignCorrection = bp.m_yawSignCorrection;
	m_upDirWS = bp.m_upDirWS; 
	m_rigidBodyForwardDir = bp.m_rigidBodyForwardDir;

	m_flat0DirWS.setCross( m_upDirWS, m_rigidBodyForwardDir );
	m_flat0DirWS.normalize3();

	m_flat1DirWS.setCross( m_upDirWS, m_flat0DirWS );
		
	m_cameraYawAngle = 0.0f;

	m_set[0] = bp.m_set[0];
	m_set[1] = bp.m_set[1];
}


hkp1dAngularFollowCam::hkp1dAngularFollowCam(const hkp1dAngularFollowCamCinfo &bp)
{
	reinitialize(bp);
}

hkp1dAngularFollowCam::~hkp1dAngularFollowCam()
{
}


hkReal hkp1dAngularFollowCam::calcYawAngle(const hkReal factor1, const hkTransform& trans, const hkVector4& linearVelocity)
{
	const hkReal factor0 = 1.0f - factor1;

	const hkTransform &t_wsFcs    = trans;

/*
// uncomment following if you want the camera to use the local 'up'
// is handy if you are driving in loopings etc.

	//#define USE_LOCAL_UP
#ifdef USE_LOCAL_UP
	m_upDirWS=hkVector4(t_wsFcs.getRotation()(0,2),t_wsFcs.getRotation()(1,2),t_wsFcs.getRotation()(2,2));
	m_flat0DirWS.setCross(m_upDirWS,m_flat1DirWS);
	m_flat0DirWS.normalize3();
	m_flat1DirWS.setCross(m_upDirWS,m_flat0DirWS );
#endif
*/

	hkVector4 forwardDirWS;
	forwardDirWS.setRotatedDir(t_wsFcs.getRotation(), m_rigidBodyForwardDir );

	const hkReal speedInfluenceOnCameraDirection = m_set[0].m_speedInfluenceOnCameraDirection * factor0 + m_set[1].m_speedInfluenceOnCameraDirection * factor1;

	const hkVector4 &velocityWS = linearVelocity;

	hkVector4 tv; tv.setAddMul4( forwardDirWS, velocityWS, 0.01f * speedInfluenceOnCameraDirection);

		// calculate new yaw angle
	const hkReal u = tv.dot3( m_flat0DirWS );
	const hkReal v = tv.dot3( m_flat1DirWS );

	hkReal yaw_angle = hkMath::atan2fApproximation( v, u ) * m_yawSignCorrection - m_yawCorrection + 0.5f * HK_REAL_PI;	

	return yaw_angle;
}


hkReal hkp1dAngularFollowCam::calcVelocityFactor(const hkVector4& chassisVelocity)
{
		// Work out factors based on velocity
	const hkReal  absVelocity = chassisVelocity.length3();

	hkReal factor1 = (absVelocity-m_set[0].m_velocity) / (m_set[1].m_velocity-m_set[0].m_velocity);
	{   // clip factor1
		factor1 = hkMath::min2( factor1, 1.0f);  // clip it 
		factor1 = hkMath::max2( 0.0f, factor1);
	}

	return factor1;
}


void hkp1dAngularFollowCam::resetCamera( const hkTransform& trans, const hkVector4& linearVelocity, const hkVector4& angularVelocity)
{
	const hkReal factor1 = calcVelocityFactor(linearVelocity);
	hkReal yawAngle = calcYawAngle(factor1, trans,linearVelocity);

	m_cameraYawAngle = yawAngle;
}

void hkp1dAngularFollowCam::calculateCamera( const CameraInput &in, CameraOutput &out )
{
	const hkReal factor1 = calcVelocityFactor(in.m_linearVelocity);
	const hkReal factor0 = 1.0f - factor1;

		// Work out yaw change based on factors and velocity.
	{
		
		hkReal yawAngle = calcYawAngle(factor1, in.m_fromTrans,in.m_linearVelocity);

		if (hkMath::isFinite(yawAngle)) // To avoid hanging if the object flies to infinity
		{
			while ( ( yawAngle + HK_REAL_PI ) < m_cameraYawAngle )
			{
				m_cameraYawAngle -= ( 2.0f * HK_REAL_PI );
			}

			while ( ( yawAngle - HK_REAL_PI ) > m_cameraYawAngle )
			{
				m_cameraYawAngle += ( 2.0f * HK_REAL_PI );
			}
		}
		

		// now lets see how fast we turn the camera to achieve this target angle.
		const hkReal angularRelaxation = factor0 * m_set[0].m_angularRelaxation + factor1 * m_set[1].m_angularRelaxation;
		const hkReal angularFactor = hkMath::min2( 1.0f, angularRelaxation * in.m_deltaTime );
		const hkReal deltaAngle = angularFactor * (yawAngle - m_cameraYawAngle);

		m_cameraYawAngle += deltaAngle;
		
	}

	const hkTransform& chassisTransform = in.m_fromTrans;
	
	const hkQuaternion q(m_upDirWS, m_cameraYawAngle);
	const hkTransform	r_ws_us(q, chassisTransform.getTranslation());

	{	// calculate camera position
		hkVector4 camPosUS;
		camPosUS.setInterpolate4( m_set[0].m_positionUS, m_set[1].m_positionUS, factor1);
		out.m_positionWS.setTransformedPos(r_ws_us,camPosUS);
	}

    
	{	// calculate lookat 
		hkVector4 lookAtUS;
		lookAtUS.setInterpolate4( m_set[0].m_lookAtUS, m_set[1].m_lookAtUS, factor1);
		out.m_lookAtWS.setTransformedPos(chassisTransform,lookAtUS);
	}

	
	{	// calculate updir
		out.m_upDirWS = m_upDirWS;
	}

	{	// calculate fov
		out.m_fov = m_set[0].m_fov * factor0 + m_set[1].m_fov * factor1;
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
