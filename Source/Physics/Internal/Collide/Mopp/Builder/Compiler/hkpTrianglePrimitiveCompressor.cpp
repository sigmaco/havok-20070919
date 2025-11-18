/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Internal/hkpInternal.h>
#include <Physics/Internal/Collide/Mopp/Builder/hkbuilder.h>
#include <Physics/Collide/Shape/hkpShapeContainer.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Physics/Collide/Util/hkpTriangleCompressor.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>
#include <Physics/Internal/Collide/Mopp/Builder/Compiler/hkpTrianglePrimitiveCompressor.h>

hkpTriangleContainerCompressor::hkpTriangleContainerCompressor(const hkpShapeContainer* container, const hkUint8* materialIndices) : m_container(container), m_materialIndices(materialIndices) {}

int hkpTriangleContainerCompressor::calcPrimitivesSize( const hkpMoppPrimitiveId* primitiveIdArray, int numPrimitives ) const
{
	hkpShapeCollection::ShapeBuffer buffer;
	hkLocalBuffer<hkpTriangleShape> tris(numPrimitives); 
	
	for (int i=0 ; i< numPrimitives; i++)
	{
		const hkpShape* shape = m_container->getChildShape( primitiveIdArray[i], buffer );
		HK_ASSERT2(0x65432123, shape->getType() == HK_SHAPE_TRIANGLE , "Can only compress triangles right now" );
		tris[i] = *static_cast<const hkpTriangleShape*>( shape );
	}

	return hkpTriangleCompressor::getCompressedSize( tris.begin(), numPrimitives, m_materialIndices );
}

void hkpTriangleContainerCompressor::storePrimitives( const hkpMoppPrimitiveId* primitiveIdArray, int numPrimitives, unsigned char* data ) const 
{
	hkpShapeCollection::ShapeBuffer buffer;
	hkLocalBuffer<hkpTriangleShape> tris(numPrimitives); 
	hkLocalBuffer<hkUint8> materialIndices( numPrimitives );

	for (int i=0; i < numPrimitives; i++)
	{
		const hkpShape* shape = m_container->getChildShape( primitiveIdArray[i], buffer );
		HK_ASSERT2(0x65432123, shape->getType() == HK_SHAPE_TRIANGLE , "Can only compress triangles right now" );
		tris[i] = *static_cast<const hkpTriangleShape*>( shape );

		if (m_materialIndices)
		{
			materialIndices[i] = m_materialIndices[ primitiveIdArray[i] ];
		}
	}

	hkUint8* materialIndicesPtr = m_materialIndices ? materialIndices.begin() : HK_NULL;
	hkpTriangleCompressor::compress( tris.begin(), numPrimitives, materialIndicesPtr, data );
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
