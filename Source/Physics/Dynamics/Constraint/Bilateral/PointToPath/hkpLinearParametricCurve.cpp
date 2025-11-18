/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Physics/Dynamics/Constraint/Bilateral/PointToPath/hkpLinearParametricCurve.h>

hkpLinearParametricCurve::hkpLinearParametricCurve()
:	m_smoothingFactor( 0.01f ), m_closedLoop( false )
{
	m_dirNotParallelToTangentAlongWholePath.set(0,1,0);
}

//////////////////////////////////////////////////////////////////////

void hkpLinearParametricCurve::getPoint( hkReal t, hkVector4& pointOnCurve ) const
{
	int ia, ib;

	if( t < 0 )
	{
		ia = 0;
	}
	else
	{
		ia = hkMath::hkFloatToInt(t);
	}

	ib = ia + 1;
	const hkReal dt = t-(hkReal)ia;

	if( ib < m_points.getSize() )
	{
		pointOnCurve.setInterpolate4(m_points[ia], m_points[ib], dt);
	}
	else
	{
		pointOnCurve = m_points[ia];
	}
}

//////////////////////////////////////////////////////////////////////

void hkpLinearParametricCurve::setClosedLoop( hkBool closeLoop )
{
	m_closedLoop = closeLoop;
}

//////////////////////////////////////////////////////////////////////

hkBool hkpLinearParametricCurve::isClosedLoop() const
{
	return m_closedLoop;
}


//////////////////////////////////////////////////////////////////////

hkReal hkpLinearParametricCurve::getNearestPoint( hkReal t, const hkVector4& nearPoint, hkVector4& pointOnCurve ) const
{

	HK_ASSERT(0x5967b43a,  m_points.getSize() > 1 );

	if( t < 0 )
	{
		t = 0;
	}

	int ia = hkMath::hkFloatToInt(t);
	int ib = ia + 1;

	if( ib >= m_points.getSize() )
	{
		ib = m_points.getSize()-1;
		ia = ib - 1;
	}

	hkReal nearProjAB = 0;

	// search for straddling points
	while( 1 )
	{

		hkVector4 tangentAB;	tangentAB.setSub4( m_points[ib], m_points[ia]);

		//
		//	Check for first side
		//

		hkVector4 fromA;	fromA.setSub4( nearPoint, m_points[ia]);

		nearProjAB = tangentAB.dot3( fromA );
		// this will be a # between 0 and 1 if the point lies between them, it can be < 0 or > 1
		// at boundary cases
		hkReal tanLenSqrd = tangentAB.dot3(tangentAB);
		nearProjAB /= tanLenSqrd;

		if( nearProjAB < 0 )
		{
			if ( ia == 0)
			{
				break;
			}
			else
			{
				ia--;
				ib--;
				continue;
			}
		}

		hkVector4 fromB;		fromB.setSub4( nearPoint, m_points[ib]);
		const hkReal checkEndAB = tangentAB.dot3( fromB );

		if ( checkEndAB <= 0.0f )
		{
			break;
		}

		int ic = ib + 1;
		if( ic >= m_points.getSize() )
		{
			break;
		}

		hkVector4 tangentBC;	tangentBC.setSub4( m_points[ic], m_points[ib]);

		hkReal nearProjBC = tangentBC.dot3( fromB );
		if( nearProjBC > 0 )
		{
			ia++;
			ib++;
			continue;
		}

		{  // ack, it's in the reflex elbo of a seam
			
			// find the segment it is angularly closer to and make the point lay there
			tangentAB.normalize3();
			tangentBC.normalize3();

			hkReal angleToAB = fromB.dot3( tangentAB );
			hkReal angleToBC = fromB.dot3( tangentBC );

			if( -angleToBC > angleToAB )
			{
				nearProjAB = 0.99f;
				break;
			} 
			else
			{
				ia++;
				ib++;
				tangentAB = tangentBC;
				nearProjAB = 0.01f;
				break;
			}
		}
	}


	hkReal new_parametric_value = ia + nearProjAB;
	
	pointOnCurve.setInterpolate4( m_points[ia],  m_points[ib], nearProjAB);

	// for a closed loop the last segment should overlap the first segement exactly
	// we place two transition points where the body jumps from one end of the path to the other 
	if( m_closedLoop )
	{
		hkReal endPoint = hkReal( m_points.getSize()-1 );
		if( new_parametric_value < 0.25f )
		{
			new_parametric_value = endPoint - ( 1.0f - new_parametric_value );
			new_parametric_value = getNearestPoint( new_parametric_value, nearPoint, pointOnCurve );
		}
		else if( new_parametric_value > endPoint - 0.25f )
		{
			new_parametric_value = 1.0f - ( endPoint - new_parametric_value );
			new_parametric_value = getNearestPoint( new_parametric_value, nearPoint, pointOnCurve );
		}
	}

	return new_parametric_value;

}

//////////////////////////////////////////////////////////////////////

void hkpLinearParametricCurve::getTangent( hkReal t, hkVector4& tangent ) const
{

	const hkReal smooth_tolerance = m_smoothingFactor;
	const hkReal smooth_tolerance_inv = 1.0f/smooth_tolerance;
	int ia = hkMath::hkFloatToInt(t);
	int ib = ia + 1;

	
	if( ib >= m_points.getSize() )
	{
		ib = m_points.getSize() - 1;
		ia = ib - 1;
	}
	else if(ia < 0)
	{
		ia = 0; 
		ib = 1;
	}

	tangent.setSub4( m_points[ib], m_points[ia]);

	tangent.normalize3();

	hkReal t_remainder = t - ia;
	// if we are near a seam, smooth it out a bit
	if( t_remainder < smooth_tolerance && ia > 0 )
	{
		hkVector4 tangent2;

		ia--;
		ib--;

		tangent2.setSub4( m_points[ib], m_points[ia]);
		tangent2.normalize3();

		hkReal interp = 0.5f * ( smooth_tolerance - t_remainder ) * smooth_tolerance_inv;
		tangent.setInterpolate4( tangent,  tangent2, interp );
		tangent.normalize3();
	}

	t_remainder = ib - t;
	// if we are near a seam, smooth it out a bit
	if( t_remainder < smooth_tolerance && ib < m_points.getSize()-1 )
	{
		hkVector4 tangent2;

		ia++;
		ib++;

		tangent2.setSub4( m_points[ib], m_points[ia]);
		tangent2.normalize3();

		hkReal interp = 0.5f * ( smooth_tolerance - t_remainder ) * smooth_tolerance_inv;
		tangent.setInterpolate4( tangent, tangent2, interp);
		tangent.normalize3();				
	}

}

//////////////////////////////////////////////////////////////////////

hkReal hkpLinearParametricCurve::getStart() const
{
	return 0;
}

//////////////////////////////////////////////////////////////////////

hkReal hkpLinearParametricCurve::getEnd() const
{
	return hkReal( m_points.getSize()-1 );
}

//////////////////////////////////////////////////////////////////////

hkReal hkpLinearParametricCurve::getLengthFromStart( hkReal t ) const
{

	int ia = hkMath::hkFloatToInt(t);
	hkReal segment_scale = 0;

	if( ia >= m_points.getSize()-1 )
	{
		ia = m_points.getSize()-1;

		segment_scale = m_distance[ia] - m_distance[ia-1];

	}
	else
	{
		if( ia < 0 )
		{
			ia = 0;
		}
		segment_scale = m_distance[ia+1] - m_distance[ia];
	}

	hkReal dist = m_distance[ia] + (t-hkReal(ia))*segment_scale;

	return dist;

}

//////////////////////////////////////////////////////////////////////

void hkpLinearParametricCurve::getBinormal( hkReal t, hkVector4& up ) const
{
	hkVector4 tangent;
	getTangent( t, tangent );

	if( (hkReal)(tangent.dot3( hkTransform::getIdentity().getColumn((1)))) < 0.98f  )
	{
		up.setCross(tangent,m_dirNotParallelToTangentAlongWholePath);
	}
	else
	{
		hkVector4Util::calculatePerpendicularVector( tangent, up );
	}

	up.normalize3();
} 

//////////////////////////////////////////////////////////////////////

void hkpLinearParametricCurve::addPoint(const hkVector4& p )
{

	m_points.pushBack( p );

	if( m_points.getSize() == 1 )
	{
		m_distance.pushBack( 0.0f );
	}
	else
	{
		hkVector4 p0 = m_points[ m_points.getSize() - 2 ];
		hkVector4 delta;
		delta.setSub4( p, p0);

		hkSimdReal last_dist = m_distance[ m_distance.getSize() - 1 ];
		m_distance.pushBack( delta.length3() + last_dist );
	}

}

//////////////////////////////////////////////////////////////////////

hkReal hkpLinearParametricCurve::getSmoothingFactor() const
{
	return m_smoothingFactor;
}


//////////////////////////////////////////////////////////////////////

void hkpLinearParametricCurve::setSmoothingFactor( hkReal smooth )
{
	m_smoothingFactor = smooth;
}

//////////////////////////////////////////////////////////////////////

void hkpLinearParametricCurve::getPointsToDraw(hkArray<hkVector4>& pathPoints) const
{
	// Okay so we are doing a copy. Could pass pointer, but 
	// that interface assumes that all path types maintain a list of points
	// used for display. 
	pathPoints = m_points;
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
