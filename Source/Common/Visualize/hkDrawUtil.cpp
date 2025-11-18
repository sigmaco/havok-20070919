/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#define HK_USE_DEBUG_DISPLAY
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Visualize/hkDrawUtil.h>

hkDrawUtil::hkDrawUtil(hkReal new_scale):
	m_scale(new_scale)
{
}


void hkDrawUtil::displayOrientedPoint(const hkVector4& position,const hkRotation& rot,
									  hkReal size,unsigned int color)
{
	hkVector4 p1,p2,x,y,z,scaled;

	x = rot.getColumn(0);
	y = rot.getColumn(1);
	z = rot.getColumn(2);

	scaled.setMul4(size,x);
	p1.setSub4(position,scaled);
	scaled.setMul4(-size,x);
	p2.setSub4(position,scaled);
	HK_DISPLAY_LINE(p1, p2, color);
	scaled.setMul4(size,y);
	p1.setSub4(position,scaled);
	scaled.setMul4(-size,y);
	p2.setSub4(position,scaled);
	HK_DISPLAY_LINE(p1, p2, color);
	scaled.setMul4(size,z);
	p1.setSub4(position,scaled);
	scaled.setMul4(-size,z);
	p2.setSub4(position,scaled);
	HK_DISPLAY_LINE(p1, p2, color);
}

	

void hkDrawUtil::displayPoint(const hkVector4& position,hkReal size,hkUint32 color)
{
	hkVector4 p1,p2;
	p1 = position;
	p2 = position;
	p1(0)-=size;
	p2(0)+=size;
	HK_DISPLAY_LINE(p1, p2, color);
	p1(0) = position(0);
	p2(0) = position(0);
	p1(1)-=size;
	p2(1)+=size;
	HK_DISPLAY_LINE(p1, p2, color);
	p1(1) = position(1);
	p2(1) = position(1);
	p1(2)-=size;
	p2(2)+=size;
	HK_DISPLAY_LINE(p1, p2, color);
}

void hkDrawUtil::displaySegment(const hkVector4& p1, const hkVector4& p2, hkUint32 color)
{
	HK_DISPLAY_LINE(p1, p2, color);
}

hkReal hkDrawUtil::getScale()
{
	return m_scale;
}

void hkDrawUtil::setScale(hkReal newScale)
{
	m_scale = newScale;
}

void hkDrawUtil::displayCone(hkReal coneAngle, const hkVector4& startPos, 
							 const hkVector4& coneAxis, const hkVector4& perpVector, 
							 int numSegments, unsigned color)
{
	hkVector4* cone_points = hkAllocate<hkVector4>(numSegments, HK_MEMORY_CLASS_TOOLS);
	hkReal segment_length = m_scale/coneAngle;
	hkQuaternion RotationFromNormal(perpVector, coneAngle);
	hkQuaternion RotationAboutAxis (coneAxis, (HK_REAL_PI*2)/numSegments);

	hkVector4 offset_direction;
	offset_direction.setRotatedDir(RotationFromNormal, coneAxis);

	int i;
	for (i = 0; i < numSegments; i ++)
	{
		cone_points[i] = startPos;
		cone_points[i].addMul4(segment_length, offset_direction);
		offset_direction.setRotatedDir(RotationAboutAxis, offset_direction);
	}

	for (i = 0; i < numSegments; i++)
	{
		int next_point_index = (i+1)%numSegments;
		displaySegment(startPos, cone_points[i],color);
		displaySegment(cone_points[i], cone_points[next_point_index],color);
	}
	hkDeallocate<hkVector4>(cone_points);
}


void hkDrawUtil::drawSemiCircle(const hkVector4& center, hkVector4& normal, 
								hkVector4& startPerp,hkReal thetaMin,hkReal thetaMax,
								hkReal radius,int numSegments, 
								unsigned int color)
{
	hkReal thetaIncr = (thetaMax-thetaMin) / numSegments;
	hkVector4 startPos;
	startPerp.normalize3();
	normal.normalize3();

	hkRotation rot;
	rot.setAxisAngle(normal, thetaMin);

		// Initialise start position
	startPos.setMul4(radius, startPerp);	
	startPos.setRotatedDir(rot, startPos);
	startPos.add4(center);
	
	rot.setAxisAngle(normal,thetaIncr);
	
		// Sucessively rotate position to next position (there will be a small amount of numerical drift here)
	for (int i = 0; i < numSegments; i++)
	{
		hkVector4 next;
		next = startPos;
		next.sub4(center);
		next.setRotatedDir(rot, next); 
		next.add4(center);
		displaySegment(startPos, next, color);

		startPos = next;
	}
}


void hkDrawUtil::displayPlane(const hkVector4& startPos, const hkVector4& planeNormal, 
							  const hkVector4& vectorOnPlane, unsigned color, hkBool showNormal)
{
	
	hkVector4 plane_points[4];
	hkReal invRoot2 = 0.70711f; 
	hkVector4 newVectorOnPlane;
	newVectorOnPlane.setMul4(m_scale * invRoot2, vectorOnPlane);
	hkQuaternion NinetyAboutPlaneNormal (planeNormal, HK_REAL_PI/2);
	hkQuaternion FortyFiveAboutPlaneNormal (planeNormal,  HK_REAL_PI/4);// this is only in here so that the 
	//display looks more like a square than a diamond
	newVectorOnPlane.setRotatedDir(FortyFiveAboutPlaneNormal, newVectorOnPlane);
	for (int i = 0; i<4; i++)
	{
		plane_points[i] = startPos;
		plane_points[i].add4( newVectorOnPlane );
		newVectorOnPlane.setRotatedDir( NinetyAboutPlaneNormal, newVectorOnPlane);
	}
	displaySegment(plane_points[0], plane_points[1],color);
	displaySegment(plane_points[1], plane_points[2],color);
	displaySegment(plane_points[2], plane_points[3],color);
	displaySegment(plane_points[3], plane_points[0],color);
	displaySegment(plane_points[0], plane_points[2],color);
	displaySegment(plane_points[1], plane_points[3],color);
	if (showNormal)
	{
		newVectorOnPlane.normalize3();
		displayArrow(startPos, planeNormal, newVectorOnPlane, color);
	}
	
}


void hkDrawUtil::displayArrow(const hkVector4& startPos, const hkVector4& arrowDirection, 
							  const hkVector4& perpDirection, unsigned color)
{
	hkVector4 endPos = startPos;
	endPos.addMul4(m_scale, arrowDirection);
	displaySegment(startPos, endPos, color);
	hkQuaternion FortyFiveAboutPerpDirection (perpDirection, HK_REAL_PI/4);
	hkQuaternion MinusNinetyAboutPerpDirection (perpDirection, -1*HK_REAL_PI/2);

	hkVector4 headDirection = arrowDirection;
	headDirection.setRotatedDir(FortyFiveAboutPerpDirection, headDirection);
	hkVector4 temp = endPos;
	temp.addMul4(-m_scale * 0.333f, headDirection);
	displaySegment(endPos, temp , color);

	headDirection.setRotatedDir(MinusNinetyAboutPerpDirection, headDirection);
	temp = endPos;
	temp.addMul4(-m_scale * 0.333f, headDirection);
	displaySegment(endPos, temp, color);
	
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
