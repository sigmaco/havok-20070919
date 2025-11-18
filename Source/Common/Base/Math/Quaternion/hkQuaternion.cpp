/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

static const hkReal HK_QUATERNION_DELTA = 1e-3f;

void hkQuaternion::setAxisAngle(const hkVector4& axis, hkReal angle)
{
	HK_ON_DEBUG(hkReal al = hkMath::fabs( hkReal(axis.length3()) - 1.0f); )
	HK_ASSERT2(0x34bd3b6e, al < 0.01f, "Axis is not normalized in hkQuaternion::setAxisAngle()");
	hkReal halfAngle = 0.5f * angle;
	hkSimdReal sinHalf = hkMath::sin(halfAngle);
	m_vec.setMul4(sinHalf, axis);
	m_vec(3) = hkMath::cos(halfAngle);
}

hkBool hkQuaternion::isOk() const
{
	hkBool ok = m_vec.isOk4();
	hkReal length = m_vec.lengthSquared4();
	hkReal error = length - 1.0f;
	hkBool lenOk = (hkMath::fabs(error) < 1e-3f);
	ok = ok && lenOk;
	return ok;
}

// the rest of the code is not needed on SPU, move the define as necessary
#if !defined (HK_PLATFORM_SPU)

static void quaternionFromRotatation( hkQuadReal& quatOut, const hkRotation& r )
{
	hkReal trace = r(0,0) + r(1,1) + r(2,2);
	hkQuadRealUnion u;

	// This is an exceptional case:
	// if trace==-1.0 since this means real=sqrt(trace+1) =0.0
	// hence we can't use real to compute the imaginary terms
	// if trace is close to -1.0, then the normal algorithm is
	// subject to numerical error.
	// Either way, we should use an alternate algorithm.
	// Please see doc "Numerical Problem In Quaternion-Matrix Conversion.doc"
	if( trace > 0 )
	{
		// else we calculate simply:
		hkReal s = hkMath::sqrt( trace + 1.0f );
		hkReal t = 0.5f / s;
		u.r[0] = (r(2,1)-r(1,2)) * t;
		u.r[1] = (r(0,2)-r(2,0)) * t;
		u.r[2] = (r(1,0)-r(0,1)) * t;
		u.r[3] = 0.5f*s;
	}
	else
	{
		const int next[] = {1,2,0};
		int i=0;

		if(r(1,1) > r(0,0)) i=1;
		if(r(2,2) > r(i,i)) i=2;

		int j = next[i];
		int k = next[j];

		hkReal s = hkMath::sqrt(r(i,i) - (r(j,j)+r(k,k)) + 1.0f);
		hkReal t = 0.5f / s;

		u.r[i] = 0.5f * s;
		u.r[3] = (r(k,j)-r(j,k)) * t;
		u.r[j] = (r(j,i)+r(i,j)) * t;
		u.r[k] = (r(k,i)+r(i,k)) * t;
	}
	quatOut = u.q;
}

void hkQuaternion::set(const hkRotation& r)
{
	quaternionFromRotatation(m_vec.getQuad(),r);
	// Note: we don't renormalize here as we assume the rotation is orthonormal
	HK_ASSERT2(0x70dc41cb, isOk(), "hkRotation used for hkQuaternion construction is invalid. hkQuaternion is not normalized/invalid!");
}

void hkQuaternion::setAndNormalize(const hkRotation& r)
{
	quaternionFromRotatation(m_vec.getQuad(),r);
	normalize();
	HK_ASSERT2(0x70dc41cc, isOk(), "hkRotation used for hkQuaternion construction is invalid.");
}

void hkQuaternion::setSlerp(const hkQuaternion& q0, const hkQuaternion& q1, hkReal t)
{
	HK_ASSERT(0x10060af0, (t>=0)&&(t<=1));

	hkReal cosTheta = q0.m_vec.dot4(q1.m_vec);

	// If B is on the oposite hemisphere use -B instead of B
	hkReal signOfT1 = 1.0f;
	if (cosTheta < 0.0f)
	{
		cosTheta = -cosTheta;
		signOfT1 = -1.0f;
	}

	hkVector4 slerp;

	if (cosTheta < 1.0f - HK_QUATERNION_DELTA)
	{
		hkReal theta = hkMath::acos(cosTheta);
		// use sqrtInv(1+c^2) instead of 1.0/sin(theta) 
		hkReal iSinTheta = hkMath::sqrtInverse(1.0f - cosTheta*cosTheta);
		hkReal tTheta = t*theta;

		hkReal t0 = hkMath::sin(theta-tTheta) * iSinTheta;
		hkReal t1 = hkMath::sin(tTheta)       * iSinTheta;

		slerp.setMul4( t0,			q0.m_vec);
		slerp.addMul4( t1*signOfT1,	q1.m_vec);
	}
	else
	{
		// If q0 is nearly the same as q1 we just linearly interpolate
		hkReal t0 = 1.0f - t;
		hkReal t1 = t;

		slerp.setMul4( t0,          q0.m_vec);
		slerp.addMul4( t1*signOfT1, q1.m_vec);
	}	
	slerp.normalize4();
	m_vec = slerp;
}

void hkQuaternion::removeAxisComponent (const hkVector4& axis)
{
	// Rotate the desired axis 
	hkVector4 rotatedAxis;
	rotatedAxis.setRotatedDir(*this, axis);

	// Calculate the shortest rotation that would bring align both axis
	// Now, calculate the rotation required to reach that alignment
	// This is the component of the rotation perpendicular to the axis

	const hkReal dotProd = axis.dot3(rotatedAxis);

	// Parallel
	if ( (dotProd-1.0f) > -1e-3f )
	{
		setIdentity();
		return;
	}

	// Opposite
	if ( (dotProd+1.0f) < 1e-3f )
	{
		hkVector4 perpVector;
		hkVector4Util::calculatePerpendicularVector(axis, perpVector);
		this->setAxisAngle(perpVector, HK_REAL_PI);
		return;

	}

	// else
	{
		const hkReal rotationAngle = hkMath::acos(dotProd);

		hkVector4 rotationAxis;
		rotationAxis.setCross(axis, rotatedAxis);
		rotationAxis.normalize3();

		setAxisAngle(rotationAxis, rotationAngle);

	}
}

void hkQuaternion::decomposeRestAxis(const hkVector4& axis, hkQuaternion& restOut, hkReal& angleOut) const
{
	hkQuaternion axisRot;
	{
		restOut = *this;
		restOut.removeAxisComponent(axis);

		// axisRot = inv(rest) * q
		hkQuaternion inv_rest;
		inv_rest.setInverse(restOut);
		axisRot.setMul(inv_rest, *this);
	}

	angleOut = axisRot.getAngle();

	const hkBool reverse = ( hkSimdReal(axisRot.getReal()) * (axisRot.getImag().dot3(axis))) < hkSimdReal(0.0f);

	if (reverse)
	{

		angleOut = -angleOut;
	}
}


void hkQuaternion::setFlippedRotation(const hkVector4& from)
{
	hkVector4 vec;
	hkVector4Util::calculatePerpendicularVector(from, vec);
	vec.normalize3();
	vec(3) = 0.0f;
	m_vec = vec;
}

extern const hkQuaternion hkQuaternionIdentity;
const hkQuaternion hkQuaternionIdentity(0,0,0,1);
#endif

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
