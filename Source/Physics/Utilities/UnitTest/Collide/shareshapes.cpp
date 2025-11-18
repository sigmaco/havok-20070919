/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/hkBase.h>
#include <Common/Base/hkBase.h>

#include <Physics/Utilities/Collide/ShapeUtils/ShapeSharing/hkpShapeSharingUtil.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>
#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

/// Dynamics support
#include <Physics/Dynamics/Common/hkpProperty.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpWorld.h>

/// Collide support
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Collide/Shape/Compound/Collection/SimpleMesh/hkpSimpleMeshShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppUtility.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>

#include <Physics/Utilities/Collide/hkpShapeGenerator.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

// Test the hkpShapeSharingUtil

hkArray<hkVector4>* g_convexVerticesVerts = HK_NULL;
hkArray<hkVector4>* g_convexVerticesPlanes = HK_NULL;

hkArray<hkVector4>* g_meshVertices = HK_NULL;
hkArray<hkpSimpleMeshShape::Triangle>* g_meshTriangles = HK_NULL;

static void initGlobals()
{
	// Reusable convex vertices
	{
		g_convexVerticesPlanes = new hkArray<hkVector4>;
		g_convexVerticesVerts = new hkArray<hkVector4>;

		hkPseudoRandomGenerator generator(20);
		const hkpConvexVerticesShape* cvsShape = hkpShapeGenerator::createRandomConvexVerticesShape(hkVector4(-10.0f,-10.0f,-10.f),hkVector4(10.0f,10.0f,1.0f), 10,&generator);

		cvsShape->getOriginalVertices(*g_convexVerticesVerts);
		*g_convexVerticesPlanes = cvsShape->getPlaneEquations();

		cvsShape->removeReference();
	}

	// Reusable mesh
	{
		g_meshVertices = new hkArray<hkVector4>;
		g_meshTriangles = new hkArray<hkpSimpleMeshShape::Triangle>;

		const int numVerts = 20;
		for (int i=0; i<numVerts; i++)
		{
			g_meshVertices->pushBack(hkVector4(hkMath::rand01()*10-5, hkMath::rand01()*10-5, hkMath::rand01()*10-5));
			if (i>=2)
			{
				hkpSimpleMeshShape::Triangle triangle;
				triangle.m_a = i-2;
				triangle.m_b = i-1;
				triangle.m_c = i;
				g_meshTriangles->pushBack(triangle);
			}
		}
	}
}

static void releaseGlobals()
{
	delete g_convexVerticesPlanes;
	delete g_convexVerticesVerts;

	delete g_meshTriangles;
	delete g_meshVertices;

}

static bool _isShapeTypeConvex (hkpShapeType shapeType)
{
	switch (shapeType)
	{
		case HK_SHAPE_SPHERE:
		case HK_SHAPE_BOX:
		case HK_SHAPE_CAPSULE:
		case HK_SHAPE_CYLINDER:
		case HK_SHAPE_CONVEX_VERTICES:
			return true;
		case HK_SHAPE_TRIANGLE_COLLECTION:
			return false;
		default:
			HK_ASSERT2(0x0,0,"Unexpected shape type");
			return false;
	}
}

static void _getRandomRotation (hkRotation& rotationOut)
{
	hkVector4 rand_first_row; rand_first_row.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
	rand_first_row.normalize3();
	hkVector4 rand_second_row;
	hkVector4Util::calculatePerpendicularVector( rand_first_row, rand_second_row);
	rand_second_row.normalize3();

	hkVector4 rand_third_row;
	rand_third_row.setCross( rand_first_row, rand_second_row );

	rotationOut.setRows( rand_first_row, rand_second_row, rand_third_row );

}

static void _getRandomTranslation (hkVector4& translationOut)
{
	translationOut.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
}

static void _getRandomTransform (hkTransform& transformOut)
{
	hkRotation rand_rotation; _getRandomRotation(rand_rotation);
	hkVector4 rand_translation; _getRandomTranslation(rand_translation);

	transformOut = hkTransform( rand_rotation, rand_translation );
}

static const hkpShape* _createRandomTransformHierarchy (const hkpShape* child, int depth)
{
	const hkpShape* lastShape = child;
	for (int i=0; i<depth; i++)
	{
		hkTransform transform; _getRandomTransform(transform);
		const hkpShape* newShape = new hkpTransformShape(lastShape, transform);
		lastShape->removeReference();
		lastShape = newShape;
	}
	return lastShape;
}

static void _deleteRbs(hkArray<hkpRigidBody*>& rigidBodies)
{
	for (int j=0; j<rigidBodies.getSize(); j++)
	{
		rigidBodies[j]->removeReference();
	}
	rigidBodies.clear();
}

//create a placeholder rigid body
static hkpRigidBody* createRB( const hkpShape* shape )
{
	hkpRigidBodyCinfo info;
	{
		info.m_shape = shape;

		info.m_position.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );			
		hkVector4 axis( 0.0f, 1.0f, 0.0f );
		info.m_rotation.setAxisAngle( axis, HK_REAL_PI / ((hkMath::rand01() * 4.0f) + 0.01f) );
		info.m_linearVelocity.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
		info.m_angularVelocity.set( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );

		info.m_maxAngularVelocity = hkMath::randRange( 1.0f, 100.0f );
		info.m_maxLinearVelocity = hkMath::randRange( 1.0f, 100.0f );
		info.m_linearDamping = hkMath::rand01();
		info.m_angularDamping = hkMath::rand01();

		info.m_friction = hkMath::rand01();
		info.m_restitution = hkMath::rand01();			
		info.m_motionType = hkpMotion::MOTION_DYNAMIC;							
		info.m_qualityType = HK_COLLIDABLE_QUALITY_FIXED;
	}

	hkpRigidBody* body = new hkpRigidBody( info );
	return body;
}

static const hkpShape* createSphereShape (float e, bool)
{
	return new hkpSphereShape(5.0f+e);
}

static const hkpShape* createBoxShape (float e,bool)
{
	return new hkpBoxShape (hkVector4(1.0f+e, 1.0f+e,1.0f+e), hkConvexShapeDefaultRadius+e);
}

static const hkpShape* createCapsule (float e, bool)
{
	const bool flip = hkMath::rand01() >= 0.5f;

	const hkVector4 pa (-2.0f-e, -2.0f-e, -2.0f-e);
	const hkVector4 pb (2.0f+e, 2.0f+e, 2.0f+e);

	const hkReal radius = 3.0f + e;

	if (flip)
	{
		return new hkpCapsuleShape (pb, pa, radius);
	}
	else
	{
		return new hkpCapsuleShape (pa, pb, radius);
	}
}

static const hkpShape* createCylinder (float e, bool)
{
	const bool flip = hkMath::rand01() >= 0.5f;

	const hkVector4 pa (-2.0f-e, -2.0f-e, -2.0f-e);
	const hkVector4 pb (2.0f+e, 2.0f+e, 2.0f+e);

	const hkReal radius = 2.0f+e;
	const hkReal cvxRadius = hkConvexShapeDefaultRadius+e;

	if (flip)
	{
		return new hkpCylinderShape (pb, pa, radius, cvxRadius );
	}
	else
	{
		return new hkpCylinderShape (pa, pb, radius, cvxRadius );
	}
}

template<typename T>
static void _shuffleArray(hkArray<T>& array)
{
	if (array.getSize()<2) return;

	// swap the last two items to ensure that the output is different from input
	hkAlgorithm::swap(array[array.getSize()-2],array[array.getSize()-1]);

	// then shuffle the n-2 remaining elements
	const int size = array.getSize()-2;

	const int numShuffles = (int) (hkMath::rand01()*size*0.4f);
	for (int i=0; i<numShuffles; i++)
	{
		const int orig = (int) (hkMath::rand01()*size);
		const int dest = (int) (hkMath::rand01()*size);

		T temp = array[orig];
		array[orig] = array[dest];
		array[dest] = temp;
	}
}

static void _perturbVectorArray(hkArray<hkVector4>& array, const float error)
{
	for (int i=0; i<array.getSize(); i++)
	{
		// Perturb a random x,y or z component
		int component = (int) (hkMath::rand01()*3.0f);
		array[i](component)+=error;
	}
}

static const hkpShape* createConvexVertices (float e, bool permute)
{
	hkArray<hkVector4> vertsCopy; vertsCopy =  *g_convexVerticesVerts;

	hkArray<hkVector4> planesCopy; planesCopy = *g_convexVerticesPlanes;

	// Shuffle 
	if (permute) 
	{
		_shuffleArray(vertsCopy);
		_shuffleArray(planesCopy);
	}


	const hkReal cvxRadius = hkConvexShapeDefaultRadius + e;

	hkStridedVertices stridedVerts;
	stridedVerts.m_numVertices = vertsCopy.getSize();
	stridedVerts.m_striding = sizeof(hkVector4);
	stridedVerts.m_vertices = &(vertsCopy[0](0));

	const hkpConvexVerticesShape* newShape = new hkpConvexVerticesShape(stridedVerts, planesCopy, cvxRadius);
	return newShape;

}

static const hkpShape* createSimpleMesh (float e, bool permute)
{
	hkArray<hkVector4> vertsCopy; vertsCopy = *g_meshVertices;
	_perturbVectorArray(vertsCopy, e);

	hkArray<hkpSimpleMeshShape::Triangle> triangCopy; triangCopy = *g_meshTriangles;

	// Shuffle triangles
	if (permute) _shuffleArray(triangCopy);

	const hkReal cvxRadius = hkConvexShapeDefaultRadius + e;

	hkpSimpleMeshShape* simpleMeshShape = new hkpSimpleMeshShape(cvxRadius);

	simpleMeshShape->m_triangles = triangCopy;
	simpleMeshShape->m_vertices = vertsCopy;


	const bool addMopp = permute && (hkMath::rand01()>=0.5f);

	if (addMopp)
	{
		hkpMoppCode* moppCode = hkpMoppUtility::buildCode(simpleMeshShape, hkpMoppCompilerInput());

		hkpMoppBvTreeShape* moppBvTreeShape = new hkpMoppBvTreeShape(simpleMeshShape, moppCode);
		simpleMeshShape->removeReference();
		moppCode->removeReference();

		return moppBvTreeShape;
	}
	else
	{
		return simpleMeshShape;
	}
}

typedef const hkpShape* (*_ShapeCreator) (float,bool);

struct _ShapeCreationFuncPair
{
	hkpShapeType m_shapeType;
	_ShapeCreator m_creator;
};

_ShapeCreationFuncPair g_shapeCreators[] =
{
	{HK_SHAPE_SPHERE, createSphereShape},
	{HK_SHAPE_BOX, createBoxShape},
	{HK_SHAPE_CAPSULE, createCapsule},
	{HK_SHAPE_CYLINDER, createCylinder},
	{HK_SHAPE_CONVEX_VERTICES, createConvexVertices},
	{HK_SHAPE_TRIANGLE_COLLECTION, createSimpleMesh},
};

static const int g_numShapeCreators = sizeof(g_shapeCreators) / sizeof(_ShapeCreationFuncPair);


/*  
	RB1->S1
	RB2->S2
	..
	RBn->Sn  

	where Sx==Sy 
*/

static int test_rigidBodiesSharingShape()
{
	// Create 2-10 rigid bodies, all sharing the same cloned shape
	for (int i=0; i<g_numShapeCreators; i++)
	{
		for (int nr=2; nr<10; nr++)
		{
			hkArray<hkpRigidBody*> rigidBodies;
			for (int rbi=0; rbi<nr; rbi++)
			{
				const hkpShape* theShape = g_shapeCreators[i].m_creator(0.0f, true);
				hkpRigidBody* rb = createRB(theShape);
				theShape->removeReference();
				rigidBodies.pushBack(rb);
			}

			hkpShapeSharingUtil::Options options;
			hkpShapeSharingUtil::Results results;
			hkpShapeSharingUtil::shareShapes(rigidBodies,options,results);

			HK_TEST(results.m_numSharedShapes == (nr-1));

			for (int j=0; j<nr; j++)
			{
				delete rigidBodies[j];
			}
		}
	}
	return 0;
}


/*
	RB1->T1->S1
	RB2->T2->S2
	...
	RBx->Tn->Sn 

	where Sx==Sy but Tx!=Ty
*/
static int test_transformShapesSharingShape()
{
	for (int i=0; i<g_numShapeCreators; i++)
	{
		for (int nr=2; nr<10; nr++)
		{
			hkArray<hkpRigidBody*> rigidBodies;
			for (int rbi=0; rbi<nr; rbi++)
			{
				const hkpShape* leafShape = g_shapeCreators[i].m_creator(0.0f, true);
				const hkpShape* transformShape = _createRandomTransformHierarchy(leafShape,1);

				hkpRigidBody* rb = createRB(transformShape);
				transformShape->removeReference();

				rigidBodies.pushBack(rb);
			}

			hkpShapeSharingUtil::Options options;
			hkpShapeSharingUtil::Results results;
			hkpShapeSharingUtil::shareShapes(rigidBodies,options,results);

			HK_TEST(results.m_numSharedShapes == (nr-1));

			_deleteRbs(rigidBodies);
		}
	}
	return 0;
}

/*
	RB1->Ta->Tb->...->S
	RB2->Tc->S
	...

	different depths all pointing to the same shape at the end
*/

static int test_differentDepthSharingShape()
{
	for (int i=0; i<g_numShapeCreators; i++)
	{
		for (int nr=2; nr<10; nr++)
		{
			hkArray<hkpRigidBody*> rigidBodies;
			for (int rbi=0; rbi<nr; rbi++)
			{
				const hkpShape* leafShape = g_shapeCreators[i].m_creator(0.0f, true);
				const hkpShape* finalShape = _createRandomTransformHierarchy(leafShape, (int) (hkMath::rand01()*10.0f));

				hkpRigidBody* rb = createRB(finalShape);
				finalShape->removeReference();

				rigidBodies.pushBack(rb);
			}

			hkpShapeSharingUtil::Options options;
			hkpShapeSharingUtil::Results results;
			hkpShapeSharingUtil::shareShapes(rigidBodies,options,results);

			HK_TEST(results.m_numSharedShapes == (nr-1));

			_deleteRbs(rigidBodies);
		}
	}
	return 0;
}

/*
	RB1->L1->(S1,S2,..,Sn)
	RB2->L2->(S1',S2'...,Sn')
	...
	RBm->Lm->(S1''',S2''', ..., Sn''')

	where S1==S1'==S1'''
*/
static int test_listshapeSharingShape()
{
	for (int nr=2; nr<10; nr++)
	{
		hkArray<hkpRigidBody*> rigidBodies;
		for (int rbi=0; rbi<nr; rbi++)
		{
			hkArray<const hkpShape*> childrenShapes;

			for (int st=0; st<g_numShapeCreators; st++)
			{
				const hkpShape* childShape = g_shapeCreators[st].m_creator(0.0f, true);
				childrenShapes.pushBack(childShape);
			}

			_shuffleArray(childrenShapes);

			const hkpListShape* listShape = new hkpListShape(childrenShapes.begin(), childrenShapes.getSize());
			for (int j=0; j<childrenShapes.getSize(); j++)
			{
				childrenShapes[j]->removeReference();
			}

			hkpRigidBody* rb = createRB(listShape);
			listShape->removeReference();

			rigidBodies.pushBack(rb);
		}

		hkpShapeSharingUtil::Options options;
		hkpShapeSharingUtil::Results results;
		hkpShapeSharingUtil::shareShapes(rigidBodies, options, results);

		HK_TEST(results.m_numSharedShapes == (g_numShapeCreators+1)*(nr-1));

		// Test that all rigid bodies share the same root shape (the list)
		{
			for (int j=1; j<nr; j++)
			{
				const hkpShape* prevShape = rigidBodies[j-1]->getCollidable()->getShape();
				const hkpShape* thisShape = rigidBodies[j]->getCollidable()->getShape();
				HK_TEST (prevShape==thisShape);
			}
		}

		// Delete rigid bodies
		{
			for (int j=0; j<nr; j++)
			{
				delete rigidBodies[j];
			}
		}
	}
	return 0;
}


/*
	RB1->S1
	RB2->S2
	..
	RBb->Sn

	where Sx = S1+0.1f*x difference

	test that different thresholds will return different amount of shared shapes
*/
static int test_equalityThreshold()
{
	const float errors[] = { 0.0f, 0.01f, 0.004f, 0.5f };
	const int numErrors = sizeof(errors)/sizeof(float);

	for (int ei1=0; ei1<numErrors; ei1++) 
	{
		for (int ei2=0; ei2<numErrors; ei2++)
		{
			if (ei1==ei2) continue;

			const float error = errors[ei1];
			const float threshold = errors[ei2];

			for (int st=0; st<g_numShapeCreators; st++) 
			{
				hkArray<hkpRigidBody*> rigidBodies;

				// Create 2 rigid bodies, one with error, one with no error
				for (int rbi=0; rbi<2; rbi++)
				{
					const hkpShape* theShape = g_shapeCreators[st].m_creator(error*rbi, true);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}

				hkpShapeSharingUtil::Options options;
				options.m_equalityThreshold = threshold;
				hkpShapeSharingUtil::Results results;
				hkpShapeSharingUtil::shareShapes(rigidBodies,options,results);

				// No shapes should be shared if above threshold
				if (error<threshold)
				{
					HK_TEST(results.m_numSharedShapes == 1);
				}
				else
				{
					HK_TEST(results.m_numSharedShapes == 0);
				}

				_deleteRbs(rigidBodies);
			}
		}

	}

	return 0;
}

/*
	Test the m_detectPermutedComponents option
*/
static int test_permuteOnOff()
{
	bool doPermute = false;
	while (1) // doPermute = false, true
	{
		bool checkPermute = true;
		while (1) // checkPermute = false, true
		{
			for (int st=0; st<g_numShapeCreators; st++) 
			{
				hkArray<hkpRigidBody*> rigidBodies;

				// Create 2 rigid bodies, one not permuted, second one possibly permuted
				for (int rbi=0; rbi<2; rbi++)
				{
					const bool permuted = (rbi==0) ? false : doPermute;
					const hkpShape* theShape = g_shapeCreators[st].m_creator(0.0f, permuted);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}

				hkpShapeSharingUtil::Options options;
				options.m_detectPermutedComponents =  checkPermute;
				hkpShapeSharingUtil::Results results;
				hkpShapeSharingUtil::shareShapes(rigidBodies,options,results);

				bool shouldShare = true;
				switch (g_shapeCreators[st].m_shapeType)
				{
					case HK_SHAPE_SPHERE:
					case HK_SHAPE_BOX:
					case HK_SHAPE_CAPSULE:
					case HK_SHAPE_CYLINDER:
						shouldShare = true ;// as permutations are always detected
						break;
					case HK_SHAPE_CONVEX_VERTICES:
					case HK_SHAPE_TRIANGLE_COLLECTION:
						shouldShare = !doPermute || checkPermute;
						break;
					default:
						break;
				}

				if (shouldShare)
				{
					HK_TEST(results.m_numSharedShapes == 1);
				}
				else
				{
					HK_TEST(results.m_numSharedShapes == 0);
				}

				_deleteRbs(rigidBodies);
			}

			checkPermute = !checkPermute;
			if (checkPermute==false) break;
		}

		doPermute = !doPermute;
		if (doPermute==false) break;
	}

	return 0;
}

/*
    RB1->box
	RB2->sphere
	RB3->capsule
	..

	test completely different shapes (no sharing)
*/
static int test_differentShapes()
{
	hkArray<hkpRigidBody*> rigidBodies;

	for (int st=0; st<g_numShapeCreators; st++)
	{
		const hkpShape* theShape = g_shapeCreators[st].m_creator(0.0f,true);
		hkpRigidBody* rb = createRB(theShape);
		theShape->removeReference();
		rigidBodies.pushBack(rb);
	}

	hkpShapeSharingUtil::Options options;
	hkpShapeSharingUtil::Results results;
	hkpShapeSharingUtil::shareShapes(rigidBodies,options,results);

	// Nothing should be shared
	HK_TEST(results.m_numSharedShapes==0);

	_deleteRbs(rigidBodies);

	return 0;
}

/*
	RB->T->S
	RB->Translate->S

	Test equivalence between transform/convextransform/convextranslate shapes
*/
static int test_transformShapeEquivalence()
{
	hkTransform fullTransform1; _getRandomTransform(fullTransform1);
	hkTransform fullTransform2; _getRandomTransform(fullTransform2);
	hkVector4 translation1; _getRandomTranslation(translation1);
	hkVector4 translation2; _getRandomTranslation(translation2);
	hkTransform transTransform1 (hkTransform::getIdentity()); transTransform1.setTranslation(translation1);
	hkTransform transTransform2 (hkTransform::getIdentity()); transTransform2.setTranslation(translation2);

	hkArray<hkpRigidBody*> rigidBodies;
	hkpShapeSharingUtil::Options options;
	hkpShapeSharingUtil::Results results;

	bool instancedShape = false;
	while (1)  // instancedShape = false, true
	{
		for (int st=0; st<g_numShapeCreators; st++)
		{
			// this only works for convex shapes
			if (!_isShapeTypeConvex(g_shapeCreators[st].m_shapeType)) continue;

			const hkpConvexShape* shape1 = static_cast<const hkpConvexShape*> (g_shapeCreators[st].m_creator(0.0f,true));
			const hkpConvexShape* shape2 = instancedShape ? shape1 : static_cast<const hkpConvexShape*> (g_shapeCreators[st].m_creator(0.0f,true));
			if (instancedShape) shape2->addReference();

			// Test 1 : Transform == CVX Transform
			{
				{
					const hkpTransformShape* theShape = new hkpTransformShape (shape1, fullTransform1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}
				{
					const hkpConvexTransformShape* theShape = new hkpConvexTransformShape (shape2, fullTransform1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}
				
				hkpShapeSharingUtil::shareShapes(rigidBodies, options, results);
				HK_TEST(results.m_numSharedShapes == (instancedShape ? 1 : 2));

				_deleteRbs(rigidBodies);
			}

			// Test 2 : Transform == CVX Translation
			{
				{
					const hkpTransformShape* theShape = new hkpTransformShape (shape1, transTransform1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}
				{
					const hkpConvexTranslateShape* theShape = new hkpConvexTranslateShape (shape2, translation1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}

				hkpShapeSharingUtil::shareShapes(rigidBodies, options, results);
				HK_TEST(results.m_numSharedShapes == (instancedShape ? 1 : 2));

				_deleteRbs(rigidBodies);
			}

			// Test 3 : CVX Transform = CVX Translation
			{
				{
					const hkpConvexTransformShape* theShape = new hkpConvexTransformShape (shape1, transTransform1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}
				{
					const hkpConvexTranslateShape* theShape = new hkpConvexTranslateShape (shape2, translation1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}

				hkpShapeSharingUtil::shareShapes(rigidBodies, options, results);
				HK_TEST(results.m_numSharedShapes == (instancedShape ? 1 : 2));

				_deleteRbs(rigidBodies);
			}

			// Test 4 : Transform == Transform
			{
				{
					const hkpTransformShape* theShape = new hkpTransformShape (shape1, fullTransform1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}
				{
					const hkpTransformShape* theShape = new hkpTransformShape (shape2, fullTransform1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}

				hkpShapeSharingUtil::shareShapes(rigidBodies, options, results);
				HK_TEST(results.m_numSharedShapes == (instancedShape ? 1 : 2));

				_deleteRbs(rigidBodies);
			}

			// Test 5 : Transform != Transform (same child but different transform)
			{
				{
					const hkpTransformShape* theShape = new hkpTransformShape (shape1, fullTransform1);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}
				{
					const hkpTransformShape* theShape = new hkpTransformShape (shape2, fullTransform2);
					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}

				hkpShapeSharingUtil::shareShapes(rigidBodies, options, results);
				HK_TEST(results.m_numSharedShapes == (instancedShape ? 0 : 1));

				_deleteRbs(rigidBodies);
			}


			shape1->removeReference();
			shape2->removeReference();
			_deleteRbs(rigidBodies);
		}

		if (instancedShape==true) break;
		instancedShape = true;
	}
	return 0;
}

/*
	Test that if shapes are already shared we don't do anything
*/
static int test_noWorkIfAlreadyShared()
{
	hkArray<hkpRigidBody*> rigidBodies;
	hkpShapeSharingUtil::Options options;
	hkpShapeSharingUtil::Results results;

	for (int st=0; st<g_numShapeCreators; st++)
	{

		const hkpShape* theShape = g_shapeCreators[st].m_creator(0.0f,true);
		hkpRigidBody* rb1 = createRB(theShape);
		hkpRigidBody* rb2 = createRB(theShape);
		theShape->removeReference();
		rigidBodies.pushBack(rb1);
		rigidBodies.pushBack(rb2);

		hkpShapeSharingUtil::shareShapes(rigidBodies, options, results);

		HK_TEST(results.m_numSharedShapes == 0);

		_deleteRbs(rigidBodies);
	}

	return 0;
}


/*
	Test same shapes with different user data
*/
static int test_userData()
{
	const void *userData[4] = { "Blah", &hkError::getInstance(), g_meshTriangles, HK_NULL };

	for (int ud1=0; ud1<4; ud1++) 
	{
		for (int ud2=0; ud2<4; ud2++)
		{
			for (int st=0; st<g_numShapeCreators; st++) 
			{
				hkArray<hkpRigidBody*> rigidBodies;

				for (int rbi=0; rbi<2; rbi++)
				{
					const hkpShape* theShape = g_shapeCreators[st].m_creator(0.0f, false);
				
					{
						hkpShape* nonconstShape = const_cast<hkpShape*> (theShape);
						nonconstShape->setUserData( reinterpret_cast<hkUlong> (rbi==0 ? userData[ud1] : userData[ud2]) );
					}

					hkpRigidBody* rb = createRB(theShape);
					theShape->removeReference();
					rigidBodies.pushBack(rb);
				}

				hkpShapeSharingUtil::Options options;
				hkpShapeSharingUtil::Results results;
				hkpShapeSharingUtil::shareShapes(rigidBodies,options,results);

				if (ud1==ud2)
				{
					HK_TEST(results.m_numSharedShapes == 1);
				}
				else
				{
					HK_TEST(results.m_numSharedShapes == 0);
				}

				_deleteRbs(rigidBodies);
			}
		}
	}

	return 0;
}


static int shareshapes_main()
{
	initGlobals();

	hkError::getInstance().setEnabled(0x2ff8c16c, false); 
	hkError::getInstance().setEnabled(0x2ff8c16d, false); 
	hkError::getInstance().setEnabled(0x2ff8c16e, false); 
	hkError::getInstance().setEnabled(0x2ff8c16f, false); 
	hkError::getInstance().setEnabled(0x7dd65995, false); 
	hkError::getInstance().setEnabled(0x6e8d163b, false); 

	test_rigidBodiesSharingShape();
	test_differentDepthSharingShape();
	test_transformShapesSharingShape();
	test_listshapeSharingShape();
	test_equalityThreshold();
	test_permuteOnOff();
	test_differentShapes();
	test_transformShapeEquivalence();
	test_noWorkIfAlreadyShared();
	test_userData();

	hkError::getInstance().setEnabled(0x2ff8c16c, true); 
	hkError::getInstance().setEnabled(0x2ff8c16d, true); 
	hkError::getInstance().setEnabled(0x2ff8c16e, true); 
	hkError::getInstance().setEnabled(0x2ff8c16f, true); 
	hkError::getInstance().setEnabled(0x7dd65995, true); 
	hkError::getInstance().setEnabled(0x6e8d163b, true); 

	releaseGlobals();

	return 0;

}   

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(shareshapes_main, "Slow", "Physics/Test/UnitTest/Utilities/", __FILE__     );

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
