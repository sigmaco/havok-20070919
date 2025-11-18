/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// construction

inline const hkVector4& hkQuaternion::getImag() const
{
	return m_vec;
}

inline void hkQuaternion::setImag(const hkVector4& i)
{
	m_vec.setXYZ(i);
}


inline hkReal hkQuaternion::getReal() const
{
	return m_vec(3);
}
inline void hkQuaternion::setReal(hkReal r)
{
	m_vec(3) = r;
}

inline hkQuaternion::hkQuaternion(const hkRotation& r)
{
	set(r);
}

inline hkQuaternion::hkQuaternion(hkReal x, hkReal y, hkReal z, hkReal w)
{
	m_vec.set(x,y,z,w);
	HK_ASSERT2(0x3c15eca2,  isOk(), "hkQuaternion components were not normalized." );
}

inline hkQuaternion::hkQuaternion(const hkVector4& axis, hkReal angle)
{
	setAxisAngle(axis,angle);
}

inline void hkQuaternion::operator= (const hkQuaternion& q)
{
	m_vec = q.m_vec;
}

inline void hkQuaternion::set(hkReal x, hkReal y, hkReal z, hkReal w)
{
	m_vec.set(x,y,z,w);
	HK_ASSERT2(0x1adaad0e,  isOk(), "hkQuaternion components were not normalized." );
}

inline void hkQuaternion::setIdentity()
{
#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	extern const hkQuadReal hkQuadReal0001;
	m_vec.getQuad() = hkQuadReal0001;
#else
	m_vec.set(0,0,0,1);
#endif
}

inline void hkQuaternion::normalize()
{
	m_vec.normalize4();	
}

inline void hkQuaternion::setMul(hkSimdRealParameter r, const hkQuaternion& q)
{
	m_vec.setMul4(r,q.m_vec);
}

inline void hkQuaternion::addMul(hkSimdRealParameter r, const hkQuaternion& q)
{
	m_vec.addMul4(r,q.m_vec);
}

inline void hkQuaternion::setMul(const hkQuaternion& q0, const hkQuaternion& q1)
{
	hkVector4 vec;
	vec.setCross(q0.getImag(), q1.getImag());
	//vec.zeroElement(3);
	vec.addMul4(q0.m_vec.getSimdAt(3), q1.getImag());
	vec.addMul4(q1.m_vec.getSimdAt(3), q0.getImag());

	hkReal real = q0.getReal() * q1.getReal() - hkReal( q0.m_vec.dot3( q1.m_vec ) );
	m_vec = vec;
	m_vec(3) = real;
}

		
inline void hkQuaternion::mul(const hkQuaternion& q)
{
	hkVector4 vec;
	vec.setCross(getImag(), q.getImag());
	vec.addMul4(m_vec.getSimdAt(3), q.getImag());
	vec.addMul4(q.m_vec.getSimdAt(3), getImag());
	hkReal w = getReal() * q.getReal() - hkReal(getImag().dot3( q.getImag() ));	
	m_vec = vec;
	m_vec(3) = w;
}

inline void hkQuaternion::setMulInverse(const hkQuaternion& q0, const hkQuaternion& q1)
{
	hkVector4 h; h.setCross(q1.getImag(), q0.getImag());
	h.subMul4(q0.m_vec.getSimdAt(3), q1.getImag());
	h.addMul4(q1.m_vec.getSimdAt(3), q0.getImag());
#if 0 && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED 
	hkVector4 w; w.getQuad() = q0.m_vec.dot4(q1.m_vec).getQuad();
	w.broadcast(0);
	h.setW( w );
	m_vec = h;
#else
	m_vec = h;
	m_vec(3) = q0.m_vec.dot4(q1.m_vec);
#endif
}

inline void hkQuaternion::setInverseMul(const hkQuaternion& q0, const hkQuaternion& q1)
{
	HK_ASSERT2(0xad67d9aa, this != &q0 && this != &q1, "This method cannot take 'this' pointer as a parameter.");
	m_vec.setCross(q1.getImag(), q0.getImag());
	m_vec.addMul4(q0.m_vec.getSimdAt(3), q1.getImag());
	m_vec.subMul4(q1.m_vec.getSimdAt(3), q0.getImag());
	m_vec(3) = q0.m_vec.dot4(q1.m_vec);
}

inline void hkQuaternion::estimateAngleTo(const hkQuaternion& to, hkVector4& angleOut) const
{
	const hkQuaternion& from = *this;
	angleOut.setCross(from.getImag(),         to.getImag());
	angleOut.subMul4(to.m_vec.getSimdAt(3),   from.getImag());
	angleOut.addMul4(from.m_vec.getSimdAt(3), to.getImag());
	angleOut.add4(angleOut);
	if ( hkMath::isNegative(  to.getImag().dot4( from.getImag() ) ) )
	{
		angleOut.setNeg4( angleOut );
	}
}


void hkQuaternion::setInverse( const hkQuaternion &q )
{
	hkReal real = q.getReal();
	m_vec.setNeg4( q.getImag() );
	setReal( real );
}

const hkReal& hkQuaternion::operator()(int i) const
{
	return m_vec(i);
}

inline hkReal hkQuaternion::getAngle() const
{
	hkReal angle = hkMath::fabs( m_vec(3) );
	angle = hkMath::acos(angle);
	angle *= 2.0f;
	return(angle);
}

inline void hkQuaternion::getAxis(hkVector4 &axis) const
{
	HK_ASSERT2(0x266e2bd7,  m_vec.length3() > HK_REAL_EPSILON, "Cannot extract axis from a Quaternion representing (within numerical tolerance) the Identity rotation (or Quaternion may not be normalized).");
	axis = m_vec;
	axis.normalize3();
	if(m_vec(3) < 0.0f)
	{
		axis.setNeg4(axis);
	}
}

inline void hkQuaternion::setShortestRotation(const hkVector4& from, const hkVector4& to)
{
#if !defined(HK_PLATFORM_SPU)
	HK_ASSERT2(0xad87ba22, from.isNormalized3() && to.isNormalized3(), "The input vectors are not normalized.");
#endif

	const hkReal dotProd = from.dot3( to ); // cos(theta)
	const hkReal nearlyOne = 1.0f - 1e-5f;
	const hkReal somewhatNearlyOne = 1.0f - 1e-3f;
	if( dotProd > nearlyOne )
	{
		setIdentity();
	}
	else if( dotProd < -nearlyOne )
	{
		setFlippedRotation( from );
	}
	else
	{
		// Using cos(theta) = 2*cos^2(theta/2) - 1
		const hkReal c = (dotProd + 1.0f) * 0.5f; 
		const hkReal cosT2 = hkMath::sqrt( c );

		hkVector4 cross;
		cross.setCross( from, to ); // ~sin(theta)* axis -- this is not exact sin(theta) .. error around 1-e2 for angles close to 180deg

		hkReal rescaleSin  = 0.5f / cosT2;

		if (dotProd < -somewhatNearlyOne)
		{
			// Extra correction needed for angles around 180deg
			//
			const hkReal sinT2 = hkMath::sqrt( cosT2 * cosT2 - dotProd );
			const hkReal approxSinT = cross.length3(); // this has errors around 1-e2 for angles around 180 deg.
			const hkReal sinT = 2 * sinT2 * cosT2;
			rescaleSin *= (sinT / approxSinT);
		}

		// Using sin(theta) = 2*cos(theta/2)*sin(theta/2)
		cross.mul4( rescaleSin );
		cross(3) = cosT2;
		m_vec = cross;
	}

	HK_ASSERT2(0xad78999d, isOk(), "Resulting quaternion is not normalized.");
}

inline void hkQuaternion::setShortestRotationDamped(hkReal gain, const hkVector4& from, const hkVector4& to)
{
	const hkReal dotProd = from.dot3( to ); // cos(theta)
	const hkReal dampedDot = 1.0f - gain + gain * dotProd;
	const hkReal nearlyOne = 1.0f - 1e-5f;
	if( dampedDot > nearlyOne )
	{
		setIdentity();
	}
	else if( dampedDot < -nearlyOne )
	{
		setFlippedRotation( from );
	}
	else
	{
		// Using cos(theta) = 2*cos^2(theta/2) - 1
		const hkReal c = (dampedDot + 1.0f) * 0.5f;
		const hkReal cosT2 = hkMath::sqrt( c );

		hkVector4 cross;
		cross.setCross( from, to ); // sin(theta)* axis

		// Using sin(theta) = 2*cos(theta/2)*sin(theta/2)
		const hkReal rescaleSin  = gain * 0.5f / cosT2;
		cross.mul4( rescaleSin );
		cross(3) = cosT2;

		// renormalize for gain.
		cross.normalize4();
		m_vec = cross;
	}
	HK_ASSERT2(0xad78999e, isOk(), "Resulting quaternion is not normalized.");
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
