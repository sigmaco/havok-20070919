/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/hkBase.h>
#include <Physics/Collide/Util/hkpTriangleUtil.h>

hkReal hkDefaultTriangleDegeneracyTolerance = 1e-7f;


hkBool hkpTriangleUtil::rayIntersect( hkReal &t, hkReal &u, hkReal &v, const hkVector4 &pos, const hkVector4 &dir,
										const hkVector4& a, const hkVector4& b, const hkVector4& c, hkBool perform_culling )
{
 
	/* find vectors for two edges sharing vert0 */

	hkVector4 edge1; edge1.setSub4(b,a);
	hkVector4 edge2; edge2.setSub4(c,a);

	/* begin calculating determinant - also used to calculate U parameter */
	hkVector4 pvec;	pvec.setCross(dir,edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	const hkReal det = edge1.dot3(pvec);

	/* Negatives values are valid if culling is off. Zero is invalid always */
	// if (perform_culling ? (det < 0.0001f) : ((det>-0.0001f)&&(det<0.0001f)))  return false;
	// (line rewritten since it caused a compiler error in MWERKS for DC
	if (perform_culling)
	{
		if (det<0.0001f) return false;
	}
	else
	{
		if ((det>-0.0001f)&&(det<0.0001f)) return false;
	}


	/* Now we can safely calculate this */
	const hkReal inv_det = 1.0f / det;

	/* calculate distance from vert0 to ray origin */
	hkVector4 tvec; tvec.setSub4(pos, a);

	/* calculate U parameter and test bounds */
	u = tvec.dot3(pvec);

	if (u < 0.0f || u > det)
	{
	   return false;
	}

	/* prepare to test V parameter */
	hkVector4 qvec;	qvec.setCross(tvec,edge1);

	/* calculate V parameter and test bounds */
	v = dir.dot3(qvec);

	if (v < 0.0f || (u + v) > det)
	{
	   return false;
	}

	/* calculate t */
	t = edge2.dot3(qvec);

	/* scale parameters */
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;

	/* Ray intersects triangle  */
	return true;
}

hkBool hkpTriangleUtil::isDegenerate(const hkVector4& a, const hkVector4& b, const hkVector4& c , hkReal tolerance)
{
	// small area check
	{
		hkVector4 edge1; edge1.setSub4( a, b );
		hkVector4 edge2; edge2.setSub4( a, c );
		hkVector4 cross; cross.setCross( edge1, edge2 );

		hkVector4 edge1b; edge1b.setSub4( b, a );
		hkVector4 edge2b; edge2b.setSub4( b, c );
		hkVector4 crossb; crossb.setCross( edge1b, edge2b );
		
		if ( ( hkReal(cross.lengthSquared3() ) < tolerance ) || ( hkReal(crossb.lengthSquared3() ) < tolerance ))
		{ 
			return true;
		}
	}

	// point triangle distance check
	{
		hkVector4 Q; Q.setSub4(a, b);      
		hkVector4 R; R.setSub4(c, b);

		const hkReal QQ = Q.lengthSquared3();
		const hkReal RR = R.lengthSquared3();
		const hkReal QR = R.dot3(Q);

		hkReal QQRR = QQ * RR;
		hkReal QRQR = QR * QR;
		hkReal Det = (QQRR - QRQR);

		if( Det == 0.0f )
		{
			return true;
		}
	}

	return false;
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
