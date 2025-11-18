/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>
#include <Common/Visualize/hkDebugDisplay.h>

hkDebugDisplay::hkDebugDisplay()
{
	m_arrayLock = new hkCriticalSection(1000); // usually no contention
}

hkDebugDisplay::~hkDebugDisplay()
{
	delete m_arrayLock;
}

void hkDebugDisplay::addDebugDisplayHandler(hkDebugDisplayHandler* debugDisplay)
{
	m_arrayLock->enter();
		m_debugDisplayHandlers.pushBack( debugDisplay );
	m_arrayLock->leave();
}

void hkDebugDisplay::removeDebugDisplayHandler(hkDebugDisplayHandler* debugDisplay)
{
	m_arrayLock->enter();
	int index = m_debugDisplayHandlers.indexOf(debugDisplay);
	if(index >= 0)
	{
		m_debugDisplayHandlers.removeAt(index); 
	}
	m_arrayLock->leave();
}

void hkDebugDisplay::clear()
{
	m_arrayLock->enter();
	m_debugDisplayHandlers.clear();
	m_arrayLock->leave();
}

//
// Debug Display functionality
//
void hkDebugDisplay::addGeometry(const hkArray<hkDisplayGeometry*>& geometries, const hkTransform& transform, hkUlong id, int tag, hkUlong shapeIdHint)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->addGeometry(geometries, transform, id, tag, shapeIdHint);
	}
	m_arrayLock->leave();
}

void hkDebugDisplay::addGeometryInstance(hkUlong instanceId, const hkTransform& transform, hkUlong id, int tag, hkUlong shapeIdHint)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->addGeometryInstance(instanceId, transform, id, tag, shapeIdHint);
	}
	m_arrayLock->leave();
}


void hkDebugDisplay::setGeometryColor(int color, hkUlong id, int tag)
{
	// keep a record of the color change (so that new displayViewer may be informed
	// NOT going to worry about this for the moment...
	m_arrayLock->enter();
	// send color change out too all existing displayViewers
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->setGeometryColor(color, id, tag);
	}
	m_arrayLock->leave();
}

void hkDebugDisplay::updateGeometry(const hkTransform& transform, hkUlong id, int tag)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->updateGeometry(transform, id, tag);
	}
	m_arrayLock->leave();
}

void hkDebugDisplay::removeGeometry(hkUlong id, int tag, hkUlong shapeIdHint)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->removeGeometry(id, tag, shapeIdHint);
	}
	m_arrayLock->leave();
}


void hkDebugDisplay::updateCamera(const hkVector4& from, const hkVector4& to, const hkVector4& up, hkReal nearPlane, hkReal farPlane, hkReal fov, const char* name)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->updateCamera(from, to, up, nearPlane, farPlane, fov, name);
	}
	m_arrayLock->leave();

}


void hkDebugDisplay::displayPoint(const hkVector4& position, int color, int tag)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->displayPoint(position, color, tag);
	}
	m_arrayLock->leave();
}

void hkDebugDisplay::displayLine(const hkVector4& start, const hkVector4& end, int color, int tag)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
//		m_debugDisplayHandlers[i]->holdImmediate();
		m_debugDisplayHandlers[i]->displayLine(start, end, color, tag);
//		m_debugDisplayHandlers[i]->step();
	}
	m_arrayLock->leave();
}

void hkDebugDisplay::displayLineModelSpace(const hkQsTransform& worldFromModel, const hkVector4& start, const hkVector4& end, int color, int tag)
{
	hkVector4 startWorld;
	hkVector4 endWorld;

	startWorld.setTransformedPos( worldFromModel, start );
	endWorld.setTransformedPos( worldFromModel, end );

	displayLine( startWorld, endWorld, color, tag );
}

void hkDebugDisplay::displayLineModelSpace(const hkTransform& worldFromModel, const hkVector4& start, const hkVector4& end, int color, int tag)
{
	hkQsTransform t;
	t.setFromTransform( worldFromModel );
	displayLineModelSpace( t, start, end, color, tag );
}

void hkDebugDisplay::displayRay(const hkVector4& start, const hkVector4& direction, int color, int tag)
{
	hkVector4 end;
	end.setAdd4( start, direction );

	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->displayLine(start, end, color, tag);
	}
}

void hkDebugDisplay::displayRayModelSpace(const hkQsTransform& worldFromModel, const hkVector4& start, const hkVector4& direction, int color, int tag)
{
	hkVector4 startWorld;
	hkVector4 directionWorld;

	startWorld.setTransformedPos( worldFromModel, start );
	directionWorld.setRotatedDir( worldFromModel.m_rotation, direction );

	displayRay( startWorld, directionWorld, color, tag );
}

void hkDebugDisplay::displayRayModelSpace(const hkTransform& worldFromModel, const hkVector4& start, const hkVector4& direction, int color, int tag)
{
	hkQsTransform t;
	t.setFromTransform( worldFromModel );
	displayRayModelSpace( t, start, direction, color, tag );
}

void hkDebugDisplay::displayFrame( const hkQsTransform& worldFromLocal, hkReal size, int tag )
{
	hkVector4 ZERO;
	hkVector4 X;
	hkVector4 Y;
	hkVector4 Z;

	hkVector4 vec; vec.setZero4();
	ZERO.setTransformedPos( worldFromLocal, vec );
	vec.set( size, 0, 0, 0 );
	X.setTransformedPos( worldFromLocal, vec );
	vec.set( 0, size, 0, 0 );
	Y.setTransformedPos( worldFromLocal, vec );
	vec.set( 0, 0, size, 0 );
	Z.setTransformedPos( worldFromLocal, vec );

	hkVector4 dirX; dirX.setSub4( X, ZERO );
	hkVector4 dirY; dirY.setSub4( Y, ZERO );
	hkVector4 dirZ; dirZ.setSub4( Z, ZERO );

	displayArrow( ZERO, dirX, hkColor::RED, tag );
	displayArrow( ZERO, dirY, hkColor::GREEN, tag );
	displayArrow( ZERO, dirZ, hkColor::BLUE, tag );
}

void hkDebugDisplay::displayFrame( const hkTransform& worldFromLocal, hkReal size, int tag )
{
	hkQsTransform t;
	t.setFromTransform( worldFromLocal );
	displayFrame( t, size, tag );
}

void hkDebugDisplay::displayArrow(const hkVector4& from, const hkVector4& dir, int color, int tag)
{
	// Check that we have a valid direction
	if (dir.lengthSquared3() < HK_REAL_EPSILON)
	{
		return;
	}

	hkVector4 to; to.setAdd4( from, dir );
	hkVector4 ort; hkVector4Util::calculatePerpendicularVector( dir, ort );
	ort.normalize3();
	hkVector4 ort2; ort2.setCross( dir, ort );

	ort.mul4( dir.length3() );

	const hkReal c = 0.85f;
	hkVector4 p; p.setInterpolate4( from, to, c );
	hkVector4 p0; p0.setAddMul4( p, ort, 1.0f - c );
	hkVector4 p1; p1.setAddMul4( p, ort, -(1.0f - c) );
	hkVector4 p2; p2.setAddMul4( p, ort2, 1.0f - c );
	hkVector4 p3; p3.setAddMul4( p, ort2, -(1.0f - c) );

	displayLine( from, to, color, tag );
	displayLine( to, p0, color, tag );
	displayLine( to, p1, color, tag );
	displayLine( to, p2, color, tag );
	displayLine( to, p3, color, tag );
}

void hkDebugDisplay::displayStar(const hkVector4& position, hkReal scale, int color, int tag)
{
	for (int k=0; k<3; k++)
	{
		hkVector4 star, pt1, pt2;
		star.setZero4();

		star(k) = scale;
		pt1.setAdd4(position,star);
		pt2.setSub4(position,star);
		displayLine(pt1, pt2, color, tag);
	}
}

void hkDebugDisplay::displayStarModelSpace(const hkQsTransform& worldFromModel, const hkVector4& position, hkReal scale, int color, int tag)
{
	hkVector4 positionWorld;
	positionWorld.setTransformedPos( worldFromModel, position );
	displayStar( positionWorld, scale, color, tag );
}

void hkDebugDisplay::displayStarModelSpace(const hkTransform& worldFromModel, const hkVector4& position, hkReal scale, int color, int tag)
{
	hkVector4 positionWorld;
	positionWorld.setTransformedPos( worldFromModel, position );
	displayStar( positionWorld, scale, color, tag );
}

void hkDebugDisplay::displayPlane(const hkVector4& plane, const hkVector4& offset, hkReal scale, int color, int tag)
{
	hkVector4 pos;

	pos.setAddMul4(offset, plane, -plane(3));
	const hkVector4& normal = plane;

	int major = normal.getMajorAxis();
	hkVector4 binorm; binorm.setZero4();
	binorm((major+1) % 3) = 1;

	binorm.setCross(normal, binorm);
	binorm.fastNormalize3();
	binorm.mul4(scale);

	hkVector4 tangent;
	tangent.setCross(binorm, normal);
	tangent.fastNormalize3();
	tangent.mul4(scale);

	//Draw the plane
	for (int e=0; e<4; e++)
	{
		hkVector4 pt1 = pos;
		(((e+0)%4)/2) ? pt1.sub4(tangent) : pt1.add4(tangent);
		(((e+1)%4)/2) ? pt1.sub4(binorm)  : pt1.add4(binorm);

		hkVector4 pt2 = pos;
		(((e+1)%4)/2) ? pt2.sub4(tangent) : pt2.add4(tangent);
		(((e+2)%4)/2) ? pt2.sub4(binorm)  : pt2.add4(binorm);	

		displayLine(pt1, pt2, color, tag);
	}

	//Draw the normal
	hkVector4 scaledNormal; scaledNormal.setMul4(scale, normal);
	displayArrow(pos, scaledNormal, color, tag);
}

void hkDebugDisplay::displayText(const char* text, int color, int tag)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->displayText(text, color, tag);
	}
	m_arrayLock->leave();

}

void hkDebugDisplay::display3dText(const char* text, const hkVector4& pos, int color, int tag)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->display3dText(text, pos, color, tag);
	}
	m_arrayLock->leave();
}

void hkDebugDisplay::displayGeometry(const hkArray<hkDisplayGeometry*>& geometries, const hkTransform& transform, int color, int tag)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->displayGeometry(geometries, transform, color, tag);
	}
	m_arrayLock->leave();

}

void hkDebugDisplay::displayGeometry(const hkArray<hkDisplayGeometry*>& geometries, int color, int tag)
{
	m_arrayLock->enter();
	for(int i = 0; i < m_debugDisplayHandlers.getSize(); i++)
	{
		m_debugDisplayHandlers[i]->displayGeometry(geometries, color, tag);
	}
	m_arrayLock->leave();
}

#if defined(HK_COMPILER_MWERKS)
#	pragma force_active on
#endif

HK_SINGLETON_IMPLEMENTATION(hkDebugDisplay);

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
