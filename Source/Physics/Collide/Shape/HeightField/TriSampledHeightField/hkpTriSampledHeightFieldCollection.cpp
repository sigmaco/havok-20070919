/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Shape/HeightField/TriSampledHeightField/hkpTriSampledHeightFieldCollection.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>

#include <Common/Visualize/hkDebugDisplay.h>


hkpTriSampledHeightFieldCollection::hkpTriSampledHeightFieldCollection( const hkpSampledHeightFieldShape* shape, hkReal radius )
: hkpShapeCollection( HK_SHAPE_COLLECTION )
{
	HK_ASSERT2(0xf89724ab, shape != HK_NULL, "You must pass a non-NULL shape pointer to this function");
	m_heightfield = shape;
	m_radius = radius;
	m_heightfield->addReference();
	HK_ASSERT2( 0x128376ab, shape->m_xRes < 0x7fff, "X Resolution of the HeightField must be less than 32767" );
	HK_ASSERT2( 0x128377ab, shape->m_zRes < 0xffff, "Y Resolution of the HeightField must be less than 65535" );
}



hkpTriSampledHeightFieldCollection::~hkpTriSampledHeightFieldCollection()
{
	m_heightfield->removeReference();
}

hkpShapeKey hkpTriSampledHeightFieldCollection::getFirstKey() const
{
	return 0;
}

void hkpTriSampledHeightFieldCollection::getAabbImpl( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out  ) const
{
	hkReal modifiedTolerance = tolerance + m_radius;
	m_heightfield->getAabb( localToWorld, modifiedTolerance, out );
}


hkpShapeKey hkpTriSampledHeightFieldCollection::getNextKey( hkpShapeKey oldKey ) const
{
	if (( oldKey & 1) == 0)
	{
		return oldKey | 1;
	}

	int x = (oldKey & 0x0000ffff) >> 1;
	int z = oldKey >> 16;

	x += 1;
	if (x == m_heightfield->m_xRes - 1)
	{
		x = 0;
		z += 1;
		if (z == m_heightfield->m_zRes - 1)
		{
			return HK_INVALID_SHAPE_KEY;
		}
	}

	return (x << 1) + (z << 16);
}


const hkpShape* hkpTriSampledHeightFieldCollection::getChildShape( hkpShapeKey key, ShapeBuffer& buffer ) const
{
	int x = (key & 0x0000ffff) >> 1;
	int z = key >> 16;

	hkpTriangleShape* triangle = new ( buffer ) hkpTriangleShape( m_radius );
	const hkVector4& scale = m_heightfield->m_intToFloatScale;

	// Doing an extra calculation here, but keeps code size down
	hkVector4 p00; p00.set( x+0.f, m_heightfield->getHeightAt( x+0, z+0 ), z+0.f ); p00.mul4( scale );
	hkVector4 p01; p01.set( x+0.f, m_heightfield->getHeightAt( x+0, z+1 ), z+1.f ); p01.mul4( scale );
	hkVector4 p10; p10.set( x+1.f, m_heightfield->getHeightAt( x+1, z+0 ), z+0.f ); p10.mul4( scale );
	hkVector4 p11; p11.set( x+1.f, m_heightfield->getHeightAt( x+1, z+1 ), z+1.f ); p11.mul4( scale );

	if ( m_heightfield->getTriangleFlip() )
	{
		if ( (key & 1) == 0 )
		{
			triangle->setVertex(0, p00);
			triangle->setVertex(1, p01);
			triangle->setVertex(2, p11);
		}
		else
		{
			triangle->setVertex(0, p00);
			triangle->setVertex(1, p11);
			triangle->setVertex(2, p10);
		}
	}
	else
	{
		if ( (key & 1) == 0 )
		{
			triangle->setVertex( 0, p00 );
			triangle->setVertex( 1, p01 );
			triangle->setVertex( 2, p10 );
		}
		else
		{
			triangle->setVertex( 0, p11 );
			triangle->setVertex( 1, p10 );
			triangle->setVertex( 2, p01 );
		}
	}


	return triangle;
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
