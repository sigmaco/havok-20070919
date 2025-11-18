/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
 // Large include
#include <Common/Base/UnitTest/hkUnitTest.h>

// We will need these shapes
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics/Collide/Shape/Query/hkpShapeRayCastOutput.h>
#include <Physics/Collide/Shape/hkpShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>

int shapeCollectionCastRay_main()
{
	//
	// Make the hkpListShape, based on Nihilistic's character proxy
	//

	// the char proxy will be a list shape
	hkArray<hkpShape*> shapeArray;

	//
	// child1 and child2
	//

	hkpSphereShape* child1	= new hkpSphereShape(0.5f);
	hkpSphereShape* child2	= new hkpSphereShape(0.5f);

	hkTransform	 trans_child1;
	hkTransform	 trans_child2;

	hkVector4 translate; translate.set(0.0f, 1.0f, 0.0f);

	trans_child1.setIdentity();
	trans_child1.setTranslation(translate);

	{
		hkVector4 tmp; tmp.set( 0.0f, 0.75f, 0.0f );
		translate.add4( tmp );
	}

	trans_child2.setIdentity();
	trans_child2.setTranslation(translate);

	hkpTransformShape* trans_shape_child1 = new hkpTransformShape(child1, trans_child1);
	hkpTransformShape* trans_shape_child2 = new hkpTransformShape(child2, trans_child2);
	child1->removeReference();
	child2->removeReference();

	shapeArray.pushBack(trans_shape_child1);
	shapeArray.pushBack(trans_shape_child2);

	//
	// child3
	//

	hkVector4 halfExtents; halfExtents.set(0.3f, 0.1f, 0.3f);
	hkpBoxShape* child3 = new hkpBoxShape(halfExtents, 0 );
	hkpTransformShape* trans_shape_child3 = new hkpTransformShape(child3, hkTransform::getIdentity());
	child3->removeReference();

	shapeArray.pushBack(trans_shape_child3);

	hkpListShape* listShape = new hkpListShape(shapeArray.begin(), shapeArray.getSize());
	trans_shape_child1->removeReference();
	trans_shape_child2->removeReference();
	trans_shape_child3->removeReference();

	//
	// need to be absolutely sure that the order of the shapes in the list
	// shape is what we think it is.
	//

	unsigned int	order[3];
	hkpShapeKey key = listShape->getFirstKey();

	hkpShapeCollection::ShapeBuffer shapeBuffer;

	for (int i = 0; i < listShape->getNumChildShapes(); i++)
	{
		const hkpShape* shape = listShape->getChildShape( key, shapeBuffer);

		key = listShape->getNextKey( key );

		if ( (shape != HK_NULL) )
		{
			if (shape == trans_shape_child1)
				order[0] = i;
			if (shape == trans_shape_child2)
				order[1] = i;
			if (shape == trans_shape_child3)
				order[2] = i;
		}
	}
	
	// these vectors will ensure that we hit each of the child shapes
	hkVector4 rayStart; rayStart.set(10.0f, 0.0f, 0.0f);

	//
	// Test for child1
	//

	{
		// ray results

		hkpShapeRayCastInput input;
		input.m_from = rayStart;
		input.m_to.set(0.0f, 1.0f, 0.0f);
		hkpShapeRayCastOutput output;


//			hkpShape::hkRayResults rayResultsChild1;
		// set a detectable value in the unnormalized hit normal
//			rayResultsChild1.m_unnormalizedHitNormal.set(-1.0f, -1.0f, -1.0f, 0);

		hkBool result = listShape->castRay(input, output);
		
		HK_TEST(result == true);
		HK_TEST( (output.m_hitFraction > 0) && (output.m_hitFraction < 1));
		HK_TEST( (output.m_shapeKeys[0] == order[0]) );
		HK_TEST( (output.m_normal.isOk3() == true) );
		HK_TEST( (output.m_normal.isNormalized3() == true) );
	}

	//
	// Test for child2
	//

	{	

		hkpShapeRayCastInput input;
		input.m_from = rayStart;
		input.m_to.set(0.0f, 1.75f, 0.0f);
		hkpShapeRayCastOutput output;


		int result = listShape->castRay( input, output );

		HK_TEST(result == 1);
		HK_TEST( ( output.m_hitFraction > 0 ) && ( output.m_hitFraction < 1 ));
		HK_TEST( ( output.m_shapeKeys[0] == order[1]) );
		HK_TEST( ( output.m_normal.isOk3() == true) );
		HK_TEST( ( output.m_normal.isNormalized3() == true) );
	}

	//
	// Test for child3
	//

	{
		hkpShapeRayCastInput input;
		input.m_from = rayStart;
		input.m_to.set(0.0f, 0.1f, 0.0f);
		hkpShapeRayCastOutput output;


		int result = listShape->castRay( input, output );

		HK_TEST(result == 1);
		HK_TEST( (output.m_hitFraction > 0) && (output.m_hitFraction < 1));
		HK_TEST( (output.m_shapeKeys[0] == order[2]) );
		HK_TEST( (output.m_normal.isOk3() == true) );
		HK_TEST( (output.m_normal.isNormalized3() == true) );
	}

	delete listShape;

	return 0;
}


#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(shapeCollectionCastRay_main, "Fast", "Physics/Test/UnitTest/Collide/", __FILE__     );



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
