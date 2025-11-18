/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/hkBase.h>

#include <Physics/Utilities/Collide/ShapeUtils/CollapseTransform/hkpTransformCollapseUtil.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>
#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

/// Dynamics support
#include <Physics/Dynamics/Common/hkpProperty.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpWorld.h>

/// Collide support
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Collide/Shape/Compound/Collection/Mesh/hkpMeshShape.h>


// test of the hkCollapseTransforms utility (used by the BakeTransformShapes filter)
 

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
 
//create a placeholder convex vertices shape
static hkpConvexVerticesShape* createCVS()
{
	int numVertices = 4;
	int stride = 16;
	
	float vertices[] = { // 4 vertices plus padding
		-2.0f, 2.0f, 1.0f, 0.0f, // v0
		 1.0f, 3.0f, 0.0f, 0.0f, // v1
		 0.0f, 1.0f, 3.0f, 0.0f, // v2
		 1.0f, 0.0f, 0.0f, 0.0f  // v3
	};

	hkpConvexVerticesShape* shape;
	hkArray<hkVector4> planeEquations;

	hkGeometry geom;
	{
		hkStridedVertices stridedVerts;
		{
			stridedVerts.m_numVertices = numVertices;
			stridedVerts.m_striding = stride;
			stridedVerts.m_vertices = vertices;
		}

		hkError::getInstance().setEnabled(0x34df5494, false); //disable an annoying warning
		hkpGeometryUtility::createConvexGeometry( stridedVerts, geom, planeEquations );
		hkError::getInstance().setEnabled(0x34df5494, true);

		{
			stridedVerts.m_numVertices = geom.m_vertices.getSize();
			stridedVerts.m_striding = sizeof(hkVector4);
			stridedVerts.m_vertices = &(geom.m_vertices[0](0));
		}
		
		shape = new hkpConvexVerticesShape(stridedVerts, planeEquations);
	}

	return shape;
}

// definitions for the hkpMeshShape
//
const int NUM_VERTICES = 4;
const int NUM_TRIANGLES = 2;
const int NUM_DEGENERATE_TRIANGLES = 2;

//create a mesh shape
static hkpMeshShape* createMesh( hkVector4* vertices, hkUint16 numVertices, hkUint16* indices, hkUint16 numIndices )
{
	// create vertices
	vertices[0] = hkVector4( 1.0f, 0.0f, 1.0f );
	vertices[1] = hkVector4(-1.0f, 0.0f, 1.0f );
	vertices[2] = hkVector4( 1.0f, 0.0f,-1.0f );
	vertices[3] = hkVector4(-1.0f, 0.0f,-1.0f );

	// create the first non-degenerate triangle (0,1,2)
	indices[0] = 0;	
	indices[1] = 1;	
	indices[2] = 2;	

	// create a degenerate triangle (1,2,2)
	indices[3] = 2;	

	// create a degenerate triangle (2,2,1)
	indices[4] = 1;

	// create the second non-degenerate triangle (2,1,3)
	indices[5] = 3;	

	// create shapes
	hkpMeshShape* meshShape = new hkpMeshShape();
	meshShape->setScaling(hkVector4(20.0f, 20.0f, 20.0f));
	{
		hkpMeshShape::Subpart part;

		part.m_vertexBase = &(vertices[0](0));
		part.m_vertexStriding = sizeof(hkVector4);
		part.m_numVertices = NUM_VERTICES;

		part.m_indexBase = indices;
		part.m_indexStriding = sizeof( hkUint16 );
		part.m_numTriangles = NUM_TRIANGLES + NUM_DEGENERATE_TRIANGLES;
		part.m_stridingType = hkpMeshShape::INDICES_INT16;

		meshShape->addSubpart( part );
	}

	return meshShape;	
}

//define various test cases.

enum transformType
{
	identityTT,    //identity
	translationTT, //translation
	fullTT		   //translation+rotation
};
struct collapseTestCase
{
	hkpShapeType   inputTST;  // the input hkpTransformShape type
	transformType inputTT;   // the input hkpTransformShape transform type
	hkpShapeType   inputST;   // the input hkpTransformShape shape type	 
	hkpShapeType   outputTST; // the (expected) output shape type 
	hkpShapeType   outputST;  // the output shape's (expected) child shape type, if there is a child (otherwise HK_SHAPE_INVALID) 
	                         //(there is a child if outputTST is an hkpTransformShape, hkpConvexTransformShape, or hkpConvexTranslateShape)
};
static int numtestcases = 18;
static const collapseTestCase g_testVariants[] =
{
//																				(expected)					(expected)
//    input shape type:			  input transform:  input shape:				output shape type:			output shape child:
	{ HK_SHAPE_TRANSFORM,		  identityTT,       HK_SHAPE_BOX,				HK_SHAPE_BOX,				HK_SHAPE_INVALID },
	{ HK_SHAPE_TRANSFORM,		  translationTT,    HK_SHAPE_BOX,				HK_SHAPE_CONVEX_TRANSLATE,	HK_SHAPE_BOX     },
	{ HK_SHAPE_TRANSFORM,		  fullTT,		    HK_SHAPE_BOX,				HK_SHAPE_CONVEX_TRANSFORM,	HK_SHAPE_BOX     },
	{ HK_SHAPE_TRANSFORM,		  fullTT,		    HK_SHAPE_CAPSULE,			HK_SHAPE_CAPSULE,			HK_SHAPE_INVALID },
	{ HK_SHAPE_TRANSFORM,		  identityTT,		HK_SHAPE_CONVEX_VERTICES,   HK_SHAPE_CONVEX_VERTICES,	HK_SHAPE_INVALID },
	{ HK_SHAPE_TRANSFORM,		  fullTT,		    HK_SHAPE_CONVEX_VERTICES,   HK_SHAPE_CONVEX_VERTICES,	HK_SHAPE_INVALID },
	
	{ HK_SHAPE_CONVEX_TRANSFORM,  identityTT,		HK_SHAPE_BOX,				HK_SHAPE_BOX,				HK_SHAPE_INVALID },
	{ HK_SHAPE_CONVEX_TRANSFORM,  translationTT,    HK_SHAPE_BOX,				HK_SHAPE_CONVEX_TRANSLATE,	HK_SHAPE_BOX     },
	{ HK_SHAPE_CONVEX_TRANSFORM,  fullTT,			HK_SHAPE_BOX,				HK_SHAPE_CONVEX_TRANSFORM,	HK_SHAPE_BOX     },
	{ HK_SHAPE_CONVEX_TRANSFORM,  fullTT,		    HK_SHAPE_CAPSULE,			HK_SHAPE_CAPSULE,			HK_SHAPE_INVALID },
	{ HK_SHAPE_CONVEX_TRANSFORM,  identityTT,		HK_SHAPE_CONVEX_VERTICES,   HK_SHAPE_CONVEX_VERTICES,	HK_SHAPE_INVALID },
	{ HK_SHAPE_CONVEX_TRANSFORM,  fullTT,		    HK_SHAPE_CONVEX_VERTICES,   HK_SHAPE_CONVEX_VERTICES,	HK_SHAPE_INVALID },
	
	{ HK_SHAPE_CONVEX_TRANSLATE,  identityTT,		HK_SHAPE_BOX,				HK_SHAPE_BOX,				HK_SHAPE_INVALID },
	{ HK_SHAPE_CONVEX_TRANSLATE,  translationTT,    HK_SHAPE_BOX,				HK_SHAPE_CONVEX_TRANSLATE,	HK_SHAPE_BOX     },
	{ HK_SHAPE_CONVEX_TRANSLATE,  fullTT,			HK_SHAPE_BOX,				HK_SHAPE_CONVEX_TRANSLATE,	HK_SHAPE_BOX     },
	{ HK_SHAPE_CONVEX_TRANSLATE,  fullTT,		    HK_SHAPE_CAPSULE,			HK_SHAPE_CAPSULE,			HK_SHAPE_INVALID },
	{ HK_SHAPE_CONVEX_TRANSLATE,  identityTT,		HK_SHAPE_CONVEX_VERTICES,   HK_SHAPE_CONVEX_VERTICES,	HK_SHAPE_INVALID },
	{ HK_SHAPE_CONVEX_TRANSLATE,  fullTT,		    HK_SHAPE_CONVEX_VERTICES,   HK_SHAPE_CONVEX_VERTICES,	HK_SHAPE_INVALID }
};


// check that various shapes wrapped in an hkpTransformShape, hkpConvexTransformShape, or hkpConvexTranslateShape are correctly collapsed
static void checkCollapse()
{			
	hkVector4 rvec1( hkMath::rand01(), hkMath::rand01(), hkMath::rand01());
	hkVector4 rvec2( hkMath::rand01(), hkMath::rand01(), hkMath::rand01());

	hkpBoxShape* boxShape = new hkpBoxShape( rvec1 );
	hkpCapsuleShape* capsuleShape = new hkpCapsuleShape( rvec1, rvec2, hkMath::rand01() );
	hkpConvexVerticesShape* convexVerticesShape = createCVS();
	
	hkTransform in_t;  //the input transform
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);

	hkpConvexShape* in_s = HK_NULL; //the input (convex) shape
	hkpRigidBody* body = HK_NULL;

	const hkpShape* out_s; //the output shape
	hkpShapeType outTST;   //the output shape type
	hkpShapeType outST;    //the output shape's child's type

	for (int n=0; n<numtestcases; n++)
	{
		//input transform
		switch ( g_testVariants[n].inputTT )
		{
			case identityTT:
				{
					in_t.setIdentity();
					break;
				}
			case translationTT:
				{
					in_t.setIdentity();
					in_t.setTranslation(t_vec);
					break;
				}
			case fullTT:
				{
					in_t.setIdentity();
					in_t.setTranslation(t_vec);
					in_t.setRotation(t_quat);
					break;
				}
		}

		//input shape
		switch ( g_testVariants[n].inputST )
		{
			case HK_SHAPE_BOX:
				in_s = boxShape;
				break;

			case HK_SHAPE_CAPSULE:
				in_s = capsuleShape;
				break;

			case HK_SHAPE_CONVEX_VERTICES:
				in_s = convexVerticesShape;
				break;

			default:
				break;
		}

		//create a rigid body with the input transform and shape hierarchy, and apply collapse()
		switch ( g_testVariants[n].inputTST )
		{
			case HK_SHAPE_TRANSFORM:
				{
					hkpTransformShape* ts = new hkpTransformShape( in_s, in_t );
					body = createRB( ts );
					ts->removeReference();
					break;
				}
			case HK_SHAPE_CONVEX_TRANSFORM:
				{
					hkpConvexTransformShape* ts = new hkpConvexTransformShape( in_s, in_t );
					body = createRB( ts );
					ts->removeReference();
					break;
				}
			case HK_SHAPE_CONVEX_TRANSLATE:
				{
					hkpConvexTranslateShape* ts = new hkpConvexTranslateShape( in_s, in_t.getTranslation() );
					body = createRB( ts );
					ts->removeReference();
					break;
				}
			default:
				break;
		}

		hkpTransformCollapseUtil::Options options;
		hkpTransformCollapseUtil::Results results;
		hkpTransformCollapseUtil::collapseTransforms(body, options, results);

		//check the output shape hierarchy
		if (body)
		{
			out_s = body->getCollidable()->getShape();
			outTST = out_s->getType();
			
			switch ( outTST )
			{
				case HK_SHAPE_TRANSFORM:
					{
						const hkpTransformShape* tforms = static_cast<const hkpTransformShape*> (out_s);
						outST = tforms->getChildShape()->getType();
						break;
					}
				case HK_SHAPE_CONVEX_TRANSFORM:
					{
						const hkpConvexTransformShape* ctforms = static_cast<const hkpConvexTransformShape*> (out_s);
						outST = ctforms->getChildShape()->getType();
						break;
					}	
				case HK_SHAPE_CONVEX_TRANSLATE:
					{
						const hkpConvexTranslateShape* ctlates = static_cast<const hkpConvexTranslateShape*> (out_s);
						outST = ctlates->getChildShape()->getType();
						break;
					}
				default:
					{
						outST = HK_SHAPE_INVALID;
						break;
					}
			}
			
			HK_TEST( outTST == g_testVariants[n].outputTST );
			HK_TEST( outST  == g_testVariants[n].outputST );

			body->removeReference();
		}
	}

	boxShape->removeReference();
	capsuleShape->removeReference();
	convexVerticesShape->removeReference();

}

//check that a shape wrapped in two or more nested transform shapes is correctly collapsed
static void checkNestedTransformCollapse()
{
	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	hkpConvexVerticesShape* cvs = createCVS();
	hkpTransformShape* ts1 = new hkpTransformShape( cvs, in_t );
	cvs->removeReference();
	hkpTransformShape* ts2 = new hkpTransformShape( ts1, in_t );
	ts1->removeReference();
	hkpTransformShape* ts3 = new hkpTransformShape( ts2, in_t );
	ts2->removeReference();	

	hkpRigidBody* body = createRB( ts3 );
	ts3->removeReference();

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(body, options, results);

	//check the output shape
	const hkpShape* out_s = body->getCollidable()->getShape();
	hkpShapeType outTST = out_s->getType();
	
	HK_TEST( outTST == HK_SHAPE_CONVEX_VERTICES );

	body->removeReference();
}


// check that shapes wrapped in an hkpListShape are correctly collapsed
static void checkListCollapse()
{	
	hkTransform in_t;  //the input transform
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);

	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	int nChildren = 5;
	hkpShape** listShapes = hkAllocate<hkpShape*>(nChildren, HK_MEMORY_CLASS_DEMO);

	//create a transform shape ts pointing to a convex vertices shape
	hkpConvexVerticesShape* in_s = createCVS();
	hkpTransformShape* ts = new hkpTransformShape( in_s, in_t );
	in_s->removeReference();

	//create a list shape with several child shapes all pointing to ts
	for (int n=0; n<nChildren; n++) 
	{	
		listShapes[n] = ts;			
	}
	hkpListShape* ls = new hkpListShape(listShapes, nChildren);
	ts->removeReference();
	
	hkDeallocate( listShapes );
	hkpRigidBody* body = createRB( ls );
	ls->removeReference();	

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(body, options, results);

	//see that the output shape is a list
	const hkpShape* out_s = body->getCollidable()->getShape();
	hkpShapeType outTST = out_s->getType();
	HK_TEST( outTST == HK_SHAPE_LIST );
	if ( outTST != HK_SHAPE_LIST ) return;
	
	//see that the output list child shapes are now all convex vertices shapes rather than transform shapes
	const hkpListShape* check_ls = static_cast<const hkpListShape*> (out_s);
	for (int n=0; n<nChildren; n++) 
	{
		const hkpShape* cs = check_ls->getChildShapeInl(n);
		hkpShapeType csType = cs->getType();
		HK_TEST( csType == HK_SHAPE_CONVEX_VERTICES );
	}
	
	body->removeReference();
	
}


static void checkMesh()
{
	const hkUint16 numVertices = NUM_VERTICES;
	hkVector4	vertices[numVertices];

	const hkUint16 numIndices = NUM_TRIANGLES + NUM_DEGENERATE_TRIANGLES + 2;
	hkUint16	indices[numIndices];

	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); 
	t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);
 
	hkpMeshShape* meshShape = createMesh( vertices, NUM_VERTICES, indices, numIndices );

	hkpTransformShape* ts = new hkpTransformShape( meshShape, in_t );
	meshShape->removeReference();

	hkpRigidBody* body = createRB( ts );
	ts->removeReference();

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(body, options, results);

	//see that the rigid body shape is not modified
	const hkpShape* out_s = body->getCollidable()->getShape();
	
	HK_TEST( out_s == ts );

	body->removeReference();
}


//check that a list shape whose children are different nested transform shapes is correctly collapsed
/*

		RB - LS            =>       RB - LS'
			/ | \                       / | \
		   /  |  \                     /  |  \
		  /   |   \                   /   |   \
		 T1   T2  T3               CVS1' CVS2' CVS3'
         |    |    |
	     .    .    .
		 .    .    .
		 |    |    |
	    CVS1 CVS2 CVS3

*/
static void checkListOfDifferentNestedTransformCollapse()
{
	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	//create a list shape with nChildren different child shapes
	int nChildren = 5;
	hkpShape** listShapes = hkAllocate<hkpShape*> (nChildren, HK_MEMORY_CLASS_DEMO);

	for (int n=0; n<nChildren; n++) 
	{	
		//each child shape is a chain of mTransformShapes hkTransformShapes (followed by a convex vertices shape)
		int mTransformShapes = 3;

		hkpConvexVerticesShape* cvs = createCVS();
		hkpTransformShape* ts_prev = new hkpTransformShape( cvs, in_t );
		cvs->removeReference();

		hkpTransformShape *ts_next = ts_prev;
		for (int m=0; m<mTransformShapes-1; m++)
		{
			ts_next = new hkpTransformShape( ts_prev, in_t );
			ts_prev->removeReference();
			ts_prev = ts_next;
		}
		listShapes[n] = ts_next;			
	}
	
	hkpListShape* ls = new hkpListShape(listShapes, nChildren);
	
	for (int n=0; n<nChildren; n++) 
	{
		const hkpShape* childShape = ls->getChildShapeInl(n);
		childShape->removeReference();	
	}

	hkDeallocate( listShapes );
	hkpRigidBody* body = createRB( ls );
	ls->removeReference();

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(body, options, results);

	//see that the output shape is a list
	const hkpShape* out_s = body->getCollidable()->getShape();
	hkpShapeType outTST = out_s->getType();
	HK_TEST( outTST == HK_SHAPE_LIST );
	if ( outTST != HK_SHAPE_LIST ) return;
	
	//see that the output list child shapes are now all convex vertices shapes rather than transform shapes
	const hkpListShape* check_ls = static_cast<const hkpListShape*> (out_s);
	for (int n=0; n<nChildren; n++) 
	{
		const hkpShape* cs = check_ls->getChildShapeInl(n);
		hkpShapeType csType = cs->getType();
		HK_TEST( csType == HK_SHAPE_CONVEX_VERTICES );
	}

	body->removeReference();
}

//check that a list shape whose children are the same nested transform shape is correctly collapsed
/*

	RB - LS                 =>      RB - LS'
		/ | \                           / | \
	   /  |  \                         /  |  \
	   \  |  /                         \  |  /
	    \ | /                           \ | /
		  T - T - CVS                    CVS'

*/
static void checkListOfNestedTransformCollapse()
{
	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	hkpConvexVerticesShape* cvs = createCVS();
	hkpTransformShape* ts1 = new hkpTransformShape( cvs, in_t );
	cvs->removeReference();
	hkpTransformShape* ts2 = new hkpTransformShape( ts1, in_t );
	ts1->removeReference();
	hkpTransformShape* ts3 = new hkpTransformShape( ts2, in_t );
	ts2->removeReference();

	int nChildren = 5;
	hkpShape** listShapes = hkAllocate<hkpShape*>( nChildren, HK_MEMORY_CLASS_DEMO );

	//create a list shape with several child shapes all pointing to ts3
	for (int n=0; n<nChildren; n++) 
	{	
		listShapes[n] = ts3;			
	}
	hkpListShape* ls = new hkpListShape(listShapes, nChildren);
	ts3->removeReference();

	hkDeallocate( listShapes );
	hkpRigidBody* body = createRB( ls );
	ls->removeReference();

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(body, options, results);

	//see that the output shape is a list
	const hkpShape* out_s = body->getCollidable()->getShape();
	hkpShapeType outTST = out_s->getType();
	HK_TEST( outTST == HK_SHAPE_LIST );
	if ( outTST != HK_SHAPE_LIST ) return;
	
	//see that the output list child shapes are now all -- the same -- convex vertices shape
	//(testing the hkShapeReplacementMap)
	const hkpListShape* check_ls = static_cast<const hkpListShape*> (out_s);
	
	hkpShape* cs = const_cast<hkpShape*>(check_ls->getChildShapeInl(0));
	hkpShape* cs_prev = cs;
	bool allSame = true;
	for (int n=1; n<nChildren; n++) 
	{
		cs = const_cast<hkpShape*>(check_ls->getChildShapeInl(n));

		hkpShapeType csType = cs->getType();
		HK_TEST( csType == HK_SHAPE_CONVEX_VERTICES );

		if (cs != cs_prev) 
		{
			allSame = false;
			HK_TEST( allSame );
			break;
		}
		cs_prev = cs;
	}

	body->removeReference();
}

//check that a list shape whose children are also list shapes is correctly collapsed
static void checkListOfListCollapse()
{
	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	//create a list shape with nChildren different child shapes
	int nChildren = 5;
	hkpShape** listShapes = hkAllocate<hkpShape*> (nChildren, HK_MEMORY_CLASS_DEMO);

	for (int n=0; n<nChildren; n++) 
	{	
		//each child shape is a list shape with mTransformShapes children (each a transform shape followed by a convex vertices shape)
	
		int mTransformShapes = 3;
		hkpShape** childlistShapes = hkAllocate<hkpShape*> (mTransformShapes, HK_MEMORY_CLASS_DEMO);

		for (int m=0; m<mTransformShapes; m++)
		{
			hkpConvexVerticesShape* cvs = createCVS();
			hkpTransformShape* ts = new hkpTransformShape( cvs, in_t );
			cvs->removeReference();
			childlistShapes[m] = ts;
		}
				
		hkpListShape* cls = new hkpListShape(childlistShapes, mTransformShapes);
		listShapes[n] = cls;

		for (int m=0; m<mTransformShapes; m++)
		{
			const hkpShape* childlistShape = cls->getChildShapeInl(m);
			childlistShape->removeReference();	
		}

		hkDeallocate( childlistShapes );
	}

	hkpListShape* ls = new hkpListShape(listShapes, nChildren);
		
	for (int n=0; n<nChildren; n++) 
	{
		const hkpShape* childShape = ls->getChildShapeInl(n);
		childShape->removeReference();	
	}
	
	hkDeallocate( listShapes );
	hkpRigidBody* body = createRB( ls );
	ls->removeReference();

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(body, options, results);

	//see that the output shape is a list
	const hkpShape* out_s = body->getCollidable()->getShape();
	hkpShapeType outTST = out_s->getType();
	HK_TEST( outTST == HK_SHAPE_LIST );
	if ( outTST != HK_SHAPE_LIST ) return;

	//see that the output list child shapes are list shapes whose children are convex vertices shapes
	const hkpListShape* check_ls = static_cast<const hkpListShape*> (out_s);
	for (int n=0; n<nChildren; n++) 
	{
		const hkpShape* cs = check_ls->getChildShapeInl(n);
		hkpShapeType csType = cs->getType();
		HK_TEST( csType == HK_SHAPE_LIST );

		const hkpListShape* check_cls = static_cast<const hkpListShape*> (cs);
		int mChildren = check_cls->getNumChildShapes();
		for (int m=0; m<mChildren; m++)
		{
			const hkpShape* cls = check_cls->getChildShapeInl(m);
			hkpShapeType clsType = cls->getType();
			HK_TEST( clsType == HK_SHAPE_CONVEX_VERTICES );
		}
	}

	body->removeReference();
}


//check that a more complicated situation is correctly collapsed
/*

	RB - LS                 =>      RB - LS'
		/ | \                           / | \
       /  |  \                         /  |  \
       \  |   \                        \  |   \
	    \ |    \                        \ |    \
		 T1    T2                       CVS'   CVS''
		  \    |
		   \   |
		    \  |
			  T - CVS

*/
static void checkOddCase()
{
	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	hkpConvexVerticesShape* cvs = createCVS();
	hkpTransformShape* ts = new hkpTransformShape( cvs, in_t );
	cvs->removeReference();

	hkpTransformShape* ts1 = new hkpTransformShape( ts, in_t );
	hkpTransformShape* ts2 = new hkpTransformShape( ts, in_t );
	ts->removeReference();

	//create a list shape with 3 different children
	hkpShape** listShapes = hkAllocate<hkpShape*>(3, HK_MEMORY_CLASS_DEMO);

	//point first two children to ts1
	for (int n=0; n<2; n++) 
	{	
		listShapes[n] = ts1;			
	}
	//point last child to ts2
	listShapes[2] = ts2;
	
	hkpListShape* ls = new hkpListShape(listShapes, 3);
	ts1->removeReference();
	ts2->removeReference();
	
	hkDeallocate( listShapes );
	hkpRigidBody* body = createRB( ls );
	ls->removeReference();

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(body, options, results);

	//see that the output shape is a list
	const hkpShape* out_s = body->getCollidable()->getShape();
	hkpShapeType outTST = out_s->getType();
	HK_TEST( outTST == HK_SHAPE_LIST );
	if ( outTST != HK_SHAPE_LIST ) return;

	//check the first two child shapes are the same convex vertices shape
	const hkpListShape* check_ls = static_cast<const hkpListShape*> (out_s);

	hkpShape* cs0 = const_cast<hkpShape*>(check_ls->getChildShapeInl(0));
	hkpShapeType cs0Type = cs0->getType();
	HK_TEST( cs0Type == HK_SHAPE_CONVEX_VERTICES );
	
	hkpShape* cs1 = const_cast<hkpShape*>(check_ls->getChildShapeInl(1));
	HK_TEST( cs1 == cs0 );

	//check that the last child shape is a (different) convex vertices shape
	hkpShape* cs2 = const_cast<hkpShape*>(check_ls->getChildShapeInl(2));
	hkpShapeType cs2Type = cs2->getType();
	HK_TEST( cs2Type == HK_SHAPE_CONVEX_VERTICES );
	HK_TEST ( cs2 != cs0 );

	body->removeReference();

}

 

// check a simple case with multiple rigid bodies
/*

   RB1  RB2  RB3                  RB1  RB2  RB3        
	 \   |   /                      \   |   /
	  \  |  /          =>            \  |  /
	   \ | /                          \ | /
	    \|/                            \|/
	     T - CVS                       CVS'

*/
static void checkMultipleRigidBodyCollapse1()
{
	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); 
	t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	hkpConvexVerticesShape* cvs = createCVS();
	hkpTransformShape* ts = new hkpTransformShape( cvs, in_t );
	cvs->removeReference();

	hkpRigidBody* body1 = createRB( ts );
	hkpRigidBody* body2 = createRB( ts );
	hkpRigidBody* body3 = createRB( ts );
	ts->removeReference();
	
	hkArray<hkpRigidBody*> bodies;
	bodies.pushBack(body1);
	bodies.pushBack(body2);
	bodies.pushBack(body3);

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;

	hkpTransformCollapseUtil::collapseTransforms(bodies, options, results);

	body1->removeReference();
	body2->removeReference();
	body3->removeReference();

}

// check a simple case with multiple rigid bodies
/*
	full collapse:

	RB1 RB2 RB3       =>    RB1  RB2 RB3           
	 \  /   |                 \  /    |
	  \/    |                  \/     |
	  T1    T2                CVS1   CVS2
	    \  /                  
	     \/
		CVS

*/
static void checkMultipleRigidBodyCollapse2()
{

	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); 
	t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	hkpConvexVerticesShape* cvs = createCVS();
	hkpTransformShape* ts1 = new hkpTransformShape( cvs, in_t );
	hkpTransformShape* ts2 = new hkpTransformShape( cvs, in_t );
	cvs->removeReference();

	hkpRigidBody* body1 = createRB( ts1 );
	hkpRigidBody* body2 = createRB( ts1 );
	ts1->removeReference();

	hkpRigidBody* body3 = createRB( ts2 );
	ts2->removeReference();

	hkArray<hkpRigidBody*> bodies;
	bodies.pushBack(body1);
	bodies.pushBack(body2);
	bodies.pushBack(body3);

	//do the collapse
	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(bodies, options, results);

	body1->removeReference();
	body2->removeReference();
	body3->removeReference();

}


// check that the duplication threshold works in a simple case
/*
	case A:
	m_duplicateLimit = 0:

	RB1 RB2      =>       RB1   RB2           
	 |   |                 |     |
	T1   T2               CVS'  CVS''
	  \ /
	   T - CVS
	
	case B:
    m_duplicateLimit = 1:

    RB1 RB2      =>       RB1 RB2           
	 |   |                 |   |
    T1   T2               CT1 CT2 
      \ /                   \ /
	   T - CVS              CVS'
	
*/
static void checkThreshold1()
{
	//initialize transform shapes
	hkVector4 t_vec(1.0, 0.0, 0.0);
	hkQuaternion t_quat; t_quat.setIdentity(); 
	t_quat.setAxisAngle(t_vec, hkReal(0.25) * HK_REAL_PI);
	hkTransform in_t;
	in_t.setIdentity();
	in_t.setTranslation(t_vec);
	in_t.setRotation(t_quat);

	//
	//case A
	//

	hkpConvexVerticesShape* cvs_A = createCVS();
	hkpTransformShape* ts_A = new hkpTransformShape( cvs_A, in_t );
	cvs_A->removeReference();

	hkpTransformShape* ts1_A = new hkpTransformShape( ts_A, in_t );
	hkpTransformShape* ts2_A = new hkpTransformShape( ts_A, in_t );
	ts_A->removeReference();

	hkpRigidBody* body1_A = createRB( ts1_A );
	hkpRigidBody* body2_A = createRB( ts2_A );
	ts1_A->removeReference();
	ts2_A->removeReference();

	hkArray<hkpRigidBody*> bodies_A;
	bodies_A.pushBack(body1_A);
	bodies_A.pushBack(body2_A);
	
	hkpTransformCollapseUtil::Options options_A;
	options_A.m_sharedShapeBehaviour = hkpTransformCollapseUtil::ALWAYS_COLLAPSE;
		
	hkpTransformCollapseUtil::Results results_A;
	hkpTransformCollapseUtil::collapseTransforms(bodies_A, options_A, results_A);

	//check the collapse statistics
	HK_TEST( results_A.m_numCollapsedShapes == 3 );
	HK_TEST( results_A.m_numIdentityTransformsRemoved == 0 );
	HK_TEST( results_A.m_numSpecializedTransformShapes == 0 );
	HK_TEST( results_A.m_numPropagatedTransformsToLists == 0 );
 
	//see that the output shapes have the right type
	const hkpShape* out_s1A = body1_A->getCollidable()->getShape();
	const hkpShape* out_s2A = body2_A->getCollidable()->getShape();
	HK_TEST( out_s1A->getType() == HK_SHAPE_CONVEX_VERTICES );
	HK_TEST( out_s2A->getType() == HK_SHAPE_CONVEX_VERTICES );
	

	body1_A->removeReference();
	body2_A->removeReference();
	
	// 
	//case B
	//

	hkpConvexVerticesShape* cvs_B = createCVS();
	hkpTransformShape* ts_B = new hkpTransformShape( cvs_B, in_t );
	cvs_B->removeReference();

	hkpTransformShape* ts1_B = new hkpTransformShape( ts_B, in_t );
	hkpTransformShape* ts2_B = new hkpTransformShape( ts_B, in_t );
	ts_B->removeReference();

	hkpRigidBody* body1_B = createRB( ts1_B );
	hkpRigidBody* body2_B = createRB( ts2_B );
	ts1_B->removeReference();
	ts2_B->removeReference();

	hkArray<hkpRigidBody*> bodies_B;
	bodies_B.pushBack(body1_B);
	bodies_B.pushBack(body2_B);

	hkpTransformCollapseUtil::Options options_B;

	options_B.m_sharedShapeBehaviour = hkpTransformCollapseUtil::COLLAPSE_IF_LESS_THAN_THRESHOLD;
	options_B.m_sharedShapeThreshold = 2;
	
	hkpTransformCollapseUtil::Results results_B;
	hkpTransformCollapseUtil::collapseTransforms(bodies_B, options_B, results_B);

	//check the collapse statistics
	HK_TEST( results_B.m_numCollapsedShapes == 1 );
	HK_TEST( results_B.m_numIdentityTransformsRemoved == 0 );
	HK_TEST( results_B.m_numSpecializedTransformShapes == 2 );
	HK_TEST( results_B.m_numPropagatedTransformsToLists == 0 );

	//see that the output shapes have the right type
	hkpShape* out_s1B = const_cast<hkpShape*>(body1_B->getCollidable()->getShape());
	hkpShape* out_s2B = const_cast<hkpShape*>(body2_B->getCollidable()->getShape());
	hkpShapeType s1B_Type = out_s1B->getType();
	hkpShapeType s2B_Type = out_s2B->getType();

	bool s1B_Type_pass = (s1B_Type == HK_SHAPE_CONVEX_TRANSFORM);
	bool s2B_Type_pass = (s2B_Type == HK_SHAPE_CONVEX_TRANSFORM);
	HK_TEST( s1B_Type_pass );
	HK_TEST( s2B_Type_pass );

	if (!s1B_Type_pass || !s2B_Type_pass) return;

	hkpConvexTransformShape* out_cts1B = static_cast<hkpConvexTransformShape*>(out_s1B);
	hkpConvexTransformShape* out_cts2B = static_cast<hkpConvexTransformShape*>(out_s2B);
	const hkpShape* child_cts1B = out_cts1B->getChildShape();
	const hkpShape* child_cts2B = out_cts2B->getChildShape();
	HK_TEST( child_cts1B->getType() == HK_SHAPE_CONVEX_VERTICES );
	HK_TEST( child_cts2B->getType() == HK_SHAPE_CONVEX_VERTICES );


	body1_B->removeReference();
	body2_B->removeReference();
}




static void checkBoxCollapse()
{
	hkVector4 inputExtents( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );
	hkpBoxShape* boxShape = new hkpBoxShape( inputExtents );
	
	//Try all possible orientations of basis vectors which align with axes.
	//Do this by putting z-axis along each of the 6 directions,
	//and in each case rotating about the direction through all 4 quarter turns.

	hkQuaternion z_orient[6];
	hkVector4 z_axis[6];

	hkVector4 x_vec(1.0, 0.0, 0.0);
	hkVector4 y_vec(0.0, 1.0, 0.0);
	hkVector4 z_vec(0.0, 0.0, 1.0);

	//along z
	z_orient[0].setIdentity();
	z_axis[0] = z_vec;
	//along -z
	z_orient[1].setAxisAngle(y_vec, HK_REAL_PI);
	z_axis[1].setNeg4(z_vec);
	//along y
	z_orient[2].setAxisAngle(x_vec, -hkReal(0.5) * HK_REAL_PI);
	z_axis[2] = y_vec;
	//along -y
	z_orient[3].setAxisAngle(x_vec, hkReal(0.5) * HK_REAL_PI);
	z_axis[3].setNeg4(y_vec);
	//along x
	z_orient[4].setAxisAngle(y_vec, hkReal(0.5) * HK_REAL_PI);
	z_axis[4] = x_vec;
	//along -x
	z_orient[5].setAxisAngle(y_vec, -hkReal(0.5) * HK_REAL_PI);
	z_axis[5].setNeg4(x_vec);

	hkTransform in_t; 
	hkQuaternion rotate_axes;

	hkVector4 temp;
	hkVector4 transExtents;

	//zero translation
	hkVector4 t_vec0(0.0, 0.0, 0.0);

	for (int i=0; i<6; i++) 
	{
		for (int j=0; j<4; j++) 
		{
			rotate_axes.setAxisAngle(z_axis[i], j * hkReal(0.5) * HK_REAL_PI);
	
			hkQuaternion q1; 
			q1.setMul( rotate_axes, z_orient[i] );
			
			in_t.setTranslation(t_vec0);
			in_t.setRotation(q1);
		
			hkpTransformShape* ts = new hkpTransformShape( boxShape, in_t );

			hkpRigidBody* body = createRB( ts );
			ts->removeReference();
				
			hkpTransformCollapseUtil::Options options;
			options.m_sharedShapeBehaviour = hkpTransformCollapseUtil::ALWAYS_COLLAPSE;
	
			hkpTransformCollapseUtil::Results results;
			hkpTransformCollapseUtil::collapseTransforms(body, options, results);

			//check the results
			if (in_t.isApproximatelyEqual(hkTransform::getIdentity()))
			{
				HK_TEST( results.m_numCollapsedShapes == 0 );
				HK_TEST( results.m_numIdentityTransformsRemoved == 1 );
				HK_TEST( results.m_numSpecializedTransformShapes == 0 );
				HK_TEST( results.m_numPropagatedTransformsToLists == 0 );
			}

			else
			{
				HK_TEST( results.m_numCollapsedShapes == 1 );
				HK_TEST( results.m_numIdentityTransformsRemoved == 0 );
				HK_TEST( results.m_numSpecializedTransformShapes == 0 );
				HK_TEST( results.m_numPropagatedTransformsToLists == 0 );
			
				hkpShape* out_s = const_cast<hkpShape*>(body->getCollidable()->getShape());
				hkpShapeType sType = out_s->getType();

				bool sType_pass = (sType == HK_SHAPE_BOX);
				HK_TEST( sType_pass );
			
				if (!sType_pass) continue;
				
				hkpBoxShape* out_bs = static_cast<hkpBoxShape*>(out_s);

				//Check that the new box has extents equal to the transformed input extents
				
				//It's not hard to see that if the old extents are put in a vector t, 
				//the new extents are (i.e. should be) just Rt, where R is the rotation.
				//e.g. if z is rotated into x, clearly the new x extent is just the old z extent
				//(we don't care about the sign, rotating into x or -x has the same effect on the box)

				const hkVector4& halfExtents = out_bs->getHalfExtents();

				hkTransform boxRot; 
				boxRot.setIdentity();
				boxRot.setRotation( in_t.getRotation() );
				temp.setTransformedPos(boxRot, inputExtents);
				
				transExtents.set( hkMath::fabs(temp(0)), hkMath::fabs(temp(1)), hkMath::fabs(temp(2)) );

				HK_TEST( halfExtents.equals3(transExtents) );

			}
			
			body->removeReference();

		}
	}

	//non-zero translation
	hkVector4 t_vec1( hkMath::rand01(), hkMath::rand01(), hkMath::rand01() );

	for (int i=0; i<6; i++) 
	{
		for (int j=0; j<4; j++) 
		{
			rotate_axes.setAxisAngle(z_axis[i], j * hkReal(0.5) * HK_REAL_PI);
	
			hkQuaternion q1; 
			q1.setMul( rotate_axes, z_orient[i] );
			
			in_t.setTranslation(t_vec1);
			in_t.setRotation(q1);
		
			hkpTransformShape* ts = new hkpTransformShape( boxShape, in_t );

			hkpRigidBody* body = createRB( ts );
			ts->removeReference();
				
			hkpTransformCollapseUtil::Options options;
			options.m_sharedShapeBehaviour = hkpTransformCollapseUtil::ALWAYS_COLLAPSE;
	
			hkpTransformCollapseUtil::Results results;
			hkpTransformCollapseUtil::collapseTransforms(body, options, results);

			//check the results
			if (in_t.isApproximatelyEqual(hkTransform::getIdentity()))
			{
				HK_TEST( results.m_numCollapsedShapes == 0 );
				HK_TEST( results.m_numIdentityTransformsRemoved == 1 );
				HK_TEST( results.m_numSpecializedTransformShapes == 0 );
				HK_TEST( results.m_numPropagatedTransformsToLists == 0 );
			}

			else
			{
				HK_TEST( results.m_numCollapsedShapes == 0 );
				HK_TEST( results.m_numIdentityTransformsRemoved == 0 );
				HK_TEST( results.m_numSpecializedTransformShapes == 1 );
				HK_TEST( results.m_numPropagatedTransformsToLists == 0 );
			
				hkpShape* out_s = const_cast<hkpShape*>(body->getCollidable()->getShape());
				hkpShapeType sType = out_s->getType();

				//Check that we now have a box wrapped in a convex translate shape

				bool sType_pass = (sType == HK_SHAPE_CONVEX_TRANSLATE);
				HK_TEST( sType_pass );
			
				if (!sType_pass) continue;
				
				const hkpShape* child_s = static_cast<hkpConvexTransformShape*>(out_s)->getChildShape();
				bool cType_pass = (child_s->getType() == HK_SHAPE_BOX);
				HK_TEST( cType_pass );

				if (!cType_pass) continue;

				const hkpBoxShape* out_bs = static_cast<const hkpBoxShape*>(child_s);

				//Check that the new box has extents equal to the transformed input extents.
				
				//It's not hard to see that if the old extents are put in a vector t, 
				//the new extents are (i.e. should be) just Rt, where R is the rotation.
				//e.g. if z is rotated into x, clearly the new x extent is just the old z extent.
				//(we don't care about the sign, rotating into x or -x has the same effect on the box)

				const hkVector4& halfExtents = out_bs->getHalfExtents();

				hkTransform boxRot; 
				boxRot.setIdentity();
				boxRot.setRotation( in_t.getRotation() );
				temp.setTransformedPos(boxRot, inputExtents);
				
				transExtents.set( hkMath::fabs(temp(0)), hkMath::fabs(temp(1)), hkMath::fabs(temp(2)) );

				HK_TEST( halfExtents.equals3(transExtents) );

			}
			
			body->removeReference();

		}
	}

	// try a transform close to a "90 degree" one, but *not* close enough that the rotation should be replaced with modified extents
	{

		float dAngle_deg = 0.01f;
		float dAngle_rad = dAngle_deg * HK_REAL_PI / 180.0f;

		rotate_axes.setAxisAngle(z_axis[2], dAngle_rad + hkReal(0.5) * HK_REAL_PI);
		
		hkQuaternion q1; 
		q1.setMul( rotate_axes, z_orient[2] );
		
		in_t.setTranslation(t_vec0);
		in_t.setRotation(q1);

		hkpTransformShape* ts = new hkpTransformShape( boxShape, in_t );

		hkpRigidBody* body = createRB( ts );
		ts->removeReference();
			
		hkpTransformCollapseUtil::Options options;
		options.m_sharedShapeBehaviour = hkpTransformCollapseUtil::ALWAYS_COLLAPSE;

		hkpTransformCollapseUtil::Results results;
		hkpTransformCollapseUtil::collapseTransforms(body, options, results);

		HK_TEST( results.m_numCollapsedShapes == 0 );
		HK_TEST( results.m_numIdentityTransformsRemoved == 0 );
		HK_TEST( results.m_numSpecializedTransformShapes == 1 );
		HK_TEST( results.m_numPropagatedTransformsToLists == 0 );

		body->removeReference();

	}

	// try a transform close to a "90 degree" one - close enough that the rotation should be replaced with modified extents
	{

		float dAngle_deg = 0.005f;
		float dAngle_rad = dAngle_deg * HK_REAL_PI / 180.0f;

		rotate_axes.setAxisAngle(z_axis[2], dAngle_rad + hkReal(0.5) * HK_REAL_PI);
		
		hkQuaternion q1; 
		q1.setMul( rotate_axes, z_orient[2] );
		
		in_t.setTranslation(t_vec0);
		in_t.setRotation(q1);

		hkpTransformShape* ts = new hkpTransformShape( boxShape, in_t );

		hkpRigidBody* body = createRB( ts );
		ts->removeReference();
			
		hkpTransformCollapseUtil::Options options;
		options.m_sharedShapeBehaviour = hkpTransformCollapseUtil::ALWAYS_COLLAPSE;

		hkpTransformCollapseUtil::Results results;
		hkpTransformCollapseUtil::collapseTransforms(body, options, results);

		HK_TEST( results.m_numCollapsedShapes == 1 );
		HK_TEST( results.m_numIdentityTransformsRemoved == 0 );
		HK_TEST( results.m_numSpecializedTransformShapes == 0 );
		HK_TEST( results.m_numPropagatedTransformsToLists == 0 );

		body->removeReference();

	}

	boxShape->removeReference();

}

// Case where a transform shape containing only rotation is applied to sphere
// Since rotation is not important with sphere, and translation is zero, the whole transform should be gone
// (Previously only one of the optimizations [specialize to convex translate] was done)
void checkSphereIdentityCase()
{

	hkpShape* sphere = new hkpSphereShape (10.0f);

	// Arbitrary rotation
	hkQuaternion rotation(hkVector4(0,0,1), 0.2f);

	hkpTransformShape* tshape = new hkpTransformShape(sphere, hkTransform(rotation, hkVector4::getZero()));
	sphere->removeReference();

	hkpRigidBody* rbody = createRB	(tshape);
	tshape->removeReference();

	hkpTransformCollapseUtil::Options options;
	hkpTransformCollapseUtil::Results results;
	hkpTransformCollapseUtil::collapseTransforms(rbody, options, results);

	HK_TEST (results.m_numIdentityTransformsRemoved == 1);
	HK_TEST (rbody->getCollidable()->getShape() == sphere);

	rbody->removeReference();
}


/////////////////////////////////////////////////////////////////////////////////////
static int collapse_main()
{
	hkError::getInstance().setEnabled(0x2ff8c16f, false); //disable an annoying warning

	checkCollapse();
	checkListCollapse();
	checkMesh();
	checkNestedTransformCollapse();
	checkListOfDifferentNestedTransformCollapse();
	checkListOfNestedTransformCollapse();
	checkListOfListCollapse();
	checkOddCase();
	checkMultipleRigidBodyCollapse1();
	checkMultipleRigidBodyCollapse2();
	checkThreshold1();
	checkBoxCollapse();
	checkSphereIdentityCase();

	hkError::getInstance().setEnabled(0x2ff8c16f, true);

	checkBoxCollapse();

	return 0;

}   

#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(collapse_main, "Slow", "Physics/Test/UnitTest/Utilities/", __FILE__     );












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
