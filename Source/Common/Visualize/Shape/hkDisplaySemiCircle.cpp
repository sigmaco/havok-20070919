/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h> //PCH
#include <Common/Visualize/Shape/hkDisplaySemiCircle.h>

hkDisplaySemiCircle::hkDisplaySemiCircle(const hkVector4& center, 
										 const hkVector4& normal, 
								         const hkVector4& startPerp,
										 const hkReal thetaMin,
										 const hkReal thetaMax,
								         const hkReal radius,
										 const int numSegments)
:	hkDisplayGeometry(HK_DISPLAY_SEMICIRCLE),
	m_normal(normal),
	m_perp(startPerp),
	m_center(center),
	m_thetaMin(thetaMin),
	m_thetaMax(thetaMax),
	m_radius(radius),
	m_numSegments(numSegments)
{
}

hkDisplaySemiCircle::hkDisplaySemiCircle()
:	hkDisplayGeometry(HK_DISPLAY_SEMICIRCLE),
	m_thetaMin(0),
	m_thetaMax(0),
	m_radius(0),
	m_numSegments(0)
{
	m_normal.setZero4();
	m_center.setZero4();
	m_perp.setZero4();
}

void hkDisplaySemiCircle::generatePoints(hkArray<hkVector4>& points)
{

	hkReal thetaIncr = (m_thetaMax - m_thetaMin) / m_numSegments;
	
	hkRotation rot;
	rot.setAxisAngle(m_normal, m_thetaMin);

	// Initialize start position
	hkVector4 startPos;
	startPos.setMul4(m_radius, m_perp);	
	startPos.setRotatedDir(rot, startPos);
	startPos.add4( m_center );
	
	rot.setAxisAngle(m_normal, thetaIncr);
	
	points.setSize(m_numSegments + 2);
	points[0] = startPos;

	for (int i = 0; i <= m_numSegments; i++)
	{
		hkVector4 next;
		next = startPos;
		next.sub4( m_center );
		next.setRotatedDir(rot, next); 
		next.add4( m_center );
        points[i+1] = next;
		startPos = next;
	}
}


void hkDisplaySemiCircle::buildGeometry()
{
	// build triangle hkGeometry
	m_geometry = new hkGeometry;

	generatePoints(m_geometry->m_vertices);
	m_geometry->m_vertices.pushBack(m_center);

	int lastIndex = m_geometry->m_vertices.getSize() - 1; 

	for(int i = 0; i < m_numSegments; i++)
	{
		m_geometry->m_triangles[i].set(lastIndex, i + 1, i);
	}
}


void hkDisplaySemiCircle::getWireframeGeometry(hkArray<hkVector4>& lines)
{
	hkArray<hkVector4> points;
	generatePoints(points);
	
	lines.setSize(2 * m_numSegments);
	int k = 0;

	for(int i = 0; i < m_numSegments; i++ )
	{
		lines[k] = points[i];
		lines[++k] = points[i + 1];
		k++;
	}
}


void hkDisplaySemiCircle::setParameters(const hkReal radius, 
										const hkReal thetaMin, 
										const hkReal thetaMax, 
										const int numSegments, 
										const hkVector4& center, 
										const hkVector4& normal,
										const hkVector4& startPerp)
{
	m_center = center;
	m_normal = normal;
	m_perp = startPerp;
	m_thetaMin = thetaMin;
	m_thetaMax = thetaMax;
	m_radius = radius;
	m_numSegments = numSegments;	
}

hkVector4 hkDisplaySemiCircle::getNormal()
{
	return m_normal;	
}

hkVector4 hkDisplaySemiCircle::getPerp()
{
	return m_perp;	
}
	
hkReal hkDisplaySemiCircle::getThetaMin()
{
	return m_thetaMin;
}
	
hkReal hkDisplaySemiCircle::getThetaMax()
{
	return m_thetaMax;	
}
		
hkReal hkDisplaySemiCircle::getRadius()
{
	return m_radius;
}

int hkDisplaySemiCircle::getNumSegments()
{
	return m_numSegments;
}


hkVector4 hkDisplaySemiCircle::getCenter()
{
	return m_center;
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
