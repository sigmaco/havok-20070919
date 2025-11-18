/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

#include <Common/Visualize/Shape/hkDisplayCone.h>

hkDisplayCone::hkDisplayCone(const hkReal coneAngle, const hkReal coneHeight,
							 const int numSegments, const hkVector4& coneAxis, 
							 const hkVector4& startPos )
:	hkDisplayGeometry(HK_DISPLAY_CONE),
	m_startPos(startPos),
	m_coneAxis(coneAxis),
	m_numSegments(numSegments),
	m_coneAngle(coneAngle), 
	m_coneHeight(coneHeight)
{

}

hkDisplayCone::hkDisplayCone()
:	hkDisplayGeometry(HK_DISPLAY_CONE),
	m_numSegments(0),
	m_coneAngle(0.0f),
	m_coneHeight(0.0f)
{
	m_startPos.setZero4();
	m_coneAxis.setZero4();
}



void hkDisplayCone::setParameters(const hkReal coneAngle, 
								  const hkReal coneHeight,
								  const int numSegments, 
							      const hkVector4& coneAxis, 
							      const hkVector4& startPos)
{
	m_coneAngle = coneAngle;
	m_startPos = startPos;
	m_coneAxis = coneAxis;
	m_coneHeight = coneHeight;
	m_numSegments = numSegments;
}


void hkDisplayCone::generateConeVertices(hkArray<hkVector4>& conePoints)
{
//	hkVector4 base;
//	hkVector4 previous;
//	hkVector4 current;

	// Better way -- member of class??
	conePoints.setSize(m_numSegments);

	hkVector4 perpVector;

	hkVector4Util::calculatePerpendicularVector(m_coneAxis, perpVector);
	perpVector.normalize3();

	hkQuaternion rotationFromNormal(perpVector, m_coneAngle);
	
	hkQuaternion rotationAboutAxis (m_coneAxis, (HK_REAL_PI*2.0f) / m_numSegments);

	hkVector4 offsetDirection;
	
	offsetDirection.setRotatedDir(rotationFromNormal, m_coneAxis);

	for(int i = 0; i < m_numSegments; i++)
	{
		conePoints[i] = m_startPos;
		conePoints[i].addMul4(m_coneHeight , offsetDirection);
		offsetDirection.setRotatedDir(rotationAboutAxis, offsetDirection);
	}
}


void hkDisplayCone::buildGeometry()
{
	// build triangle hkGeometry

	m_geometry = new hkGeometry;

	generateConeVertices(m_geometry->m_vertices);
	
	m_geometry->m_vertices.pushBack(m_startPos);
	m_geometry->m_triangles.setSize(m_numSegments);

	int i;
	for(i = 0; i < m_numSegments - 1; i++)
	{
		m_geometry->m_triangles[i].set(m_numSegments, i + 1, i);
	}
	m_geometry->m_triangles[i].set(m_numSegments, 0, i);
}


void hkDisplayCone::getWireframeGeometry(hkArray<hkVector4>& lines)
{
	hkInplaceArrayAligned16<hkVector4,256> conePoints;

	generateConeVertices(conePoints);
	
	lines.setSize(4*m_numSegments);
	
	int k = 0;

	for (int j = 0; j < m_numSegments; )
	{
		lines[k] = m_startPos;
		lines[++k] = conePoints[j];
		lines[++k] = conePoints[j];
		int next_point_index = (++j) % m_numSegments;
		lines[++k] = conePoints[next_point_index];
		k++;
	}
}


hkVector4 hkDisplayCone::getPosition()
{
	return m_startPos;
}


hkVector4 hkDisplayCone::getAxis()
{
	return m_coneAxis;
}

hkReal hkDisplayCone::getHeight()
{
	return m_coneHeight;
}

hkReal hkDisplayCone::getAngle()
{
	return m_coneAngle;	
}

int hkDisplayCone::getNumSegments()
{
	return m_numSegments;
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
