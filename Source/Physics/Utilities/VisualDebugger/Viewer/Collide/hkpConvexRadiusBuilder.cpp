/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Collide/hkpConvexRadiusBuilder.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>

#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Misc/MultiSphere/hkpMultiSphereShape.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Physics/Collide/Shape/Misc/Bv/hkpBvShape.h>
#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>
#include <Physics/Collide/Shape/HeightField/Plane/hkpPlaneShape.h>

#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Misc/MultiRay/hkpMultiRayShape.h>

#include <Physics/Collide/Shape/Compound/Collection/ConvexPieceMesh/hkpConvexPieceShape.h>
#include <Physics/Collide/Util/hkpTriangleUtil.h>

#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

#include <Common/Visualize/Shape/hkDisplayPlane.h>
#include <Common/Visualize/Shape/hkDisplaySphere.h>
#include <Common/Visualize/Shape/hkDisplayCylinder.h>
#include <Common/Visualize/Shape/hkDisplayCapsule.h>
#include <Common/Visualize/Shape/hkDisplayBox.h>
#include <Common/Visualize/Shape/hkDisplayConvex.h>
#include <Common/Visualize/hkDebugDisplay.h>


hkpConvexRadiusBuilder::hkpConvexRadiusBuilderEnvironment::hkpConvexRadiusBuilderEnvironment()
:	m_minVisibleRadius(0.001f)
{
}



hkpConvexRadiusBuilder::hkpConvexRadiusBuilder(const hkpConvexRadiusBuilderEnvironment& env)
:	m_environment(env),
	m_currentGeometry(HK_NULL)
{
}


void hkpConvexRadiusBuilder::buildDisplayGeometries(		const hkpShape* shape,
														hkArray<hkDisplayGeometry*>& displayGeometries)
{

	hkTransform transform;
	transform.setIdentity();

	resetCurrentRawGeometry();
	displayGeometries.clear();

	buildShapeDisplay(shape, transform, displayGeometries);
}

static hkDisplayConvex* _createConvexDisplayFromPlanes( const hkArray<hkVector4>& planeEqs, const hkTransform& transform )
{
	// Create verts from planes
	hkArray<hkVector4> verts;
	hkpGeometryUtility::createVerticesFromPlaneEquations(planeEqs, verts);

	if (verts.getSize() < 1)
	{
		return HK_NULL;
	}

	// Transform verts
	hkArray<hkVector4> transformedVerts;
	int numVerts = verts.getSize();
	transformedVerts.setSize(numVerts);
	for (int i=0; i < numVerts; ++i)
	{
		transformedVerts[i].setTransformedPos(transform, verts[i]);
	}

	hkGeometry* outputGeom = new hkGeometry;
	hkStridedVertices stridedVerts;
	{
		stridedVerts.m_numVertices = transformedVerts.getSize();
		stridedVerts.m_striding = sizeof(hkVector4);
		stridedVerts.m_vertices = &(transformedVerts[0](0));
	}

	hkpGeometryUtility::createConvexGeometry( stridedVerts, *outputGeom );

	return new hkDisplayConvex(outputGeom);
}

static float _getPlaneToSurfaceDistance(const hkpConvexVerticesShape* shape)
{
	const hkArray<hkVector4>& planes = shape->getPlaneEquations();
	hkArray<hkVector4> vertices;
	shape->getOriginalVertices( vertices );

	const int numVerts = vertices.getSize();
	const int numPlanes = planes.getSize();
		
	float closest = -1000;
	for (int v = 0; v < numVerts; v++)
	{
		const hkVector4& vert = vertices[v];
		for (int p = 0; p < numPlanes; p++)
		{
			const hkReal distFromPlane = static_cast<hkReal>(vert.dot3(planes[p])) + planes[p](3);
			if (distFromPlane > closest) // dot is negative if on internal side.
			{
				closest = distFromPlane;
			}
		}
	}
	return closest;
}

static void _addBoundingPlanes(const hkpShape* s, float extraRadius, hkArray<hkVector4>& planes)
{
	hkAabb aabb;
	s->getAabb(hkTransform::getIdentity(), extraRadius, aabb);
	planes.expandBy(6);
	
	int numPlanes = planes.getSize();
	planes[ numPlanes - 6 ].set( 1, 0, 0, -aabb.m_max(0) );
	planes[ numPlanes - 5 ].set( 0, 1, 0, -aabb.m_max(1) );
	planes[ numPlanes - 4 ].set( 0, 0, 1, -aabb.m_max(2) );
	planes[ numPlanes - 3 ].set( -1, 0, 0, aabb.m_min(0) );
	planes[ numPlanes - 2 ].set( 0, -1, 0, aabb.m_min(1) );
	planes[ numPlanes - 1 ].set( 0, 0, -1, aabb.m_min(2) );
}

// This is the alternative to having a buildDisplayGeometry as a virtual function in Shape.
void hkpConvexRadiusBuilder::buildShapeDisplay(		const hkpShape* shape,
													const hkTransform& transform,
													hkArray<hkDisplayGeometry*>& displayGeometries)
{
	switch (shape->getType())
	{
		//
		// These do not use convex radius:
		//
		case HK_SHAPE_SPHERE:
		case HK_SHAPE_MULTI_SPHERE:
		case HK_SHAPE_PLANE:
		case HK_SHAPE_CAPSULE:
		case HK_SHAPE_MULTI_RAY:
		case HK_SHAPE_SAMPLED_HEIGHT_FIELD:
			break;
		
		//
		// Shape wrapper types
		//

		case HK_SHAPE_CONVEX_TRANSLATE:
		{
			const hkpConvexTranslateShape* ts = static_cast<const hkpConvexTranslateShape*>( shape );
			hkTransform tst; tst.setIdentity();	tst.setTranslation( ts->getTranslation());
			hkTransform T; T.setMul( transform, tst );
			buildShapeDisplay( ts->getChildShape(), T, displayGeometries);
			break;
		}

		case HK_SHAPE_CONVEX_TRANSFORM:
		{
			const hkpConvexTransformShape* ts = static_cast<const hkpConvexTransformShape*>( shape );
			hkTransform T; T.setMul( transform, ts->getTransform() );
			buildShapeDisplay( ts->getChildShape(), T, displayGeometries);
			break;
		}	

		case HK_SHAPE_TRANSFORM:
		{
			const hkpTransformShape* ts = static_cast<const hkpTransformShape*>( shape );
			hkTransform T; T.setMul( transform, ts->getTransform() );
			buildShapeDisplay( ts->getChildShape(), T, displayGeometries);
			break;
		}
		case HK_SHAPE_BV:
		{
			const hkpBvShape* bvShape = static_cast<const hkpBvShape*>(shape);
			buildShapeDisplay( bvShape->getBoundingVolumeShape(), transform, displayGeometries);
			break;
		}

		case HK_SHAPE_BV_TREE:
		case HK_SHAPE_MOPP:
		{
			const hkpBvTreeShape* bvShape = static_cast<const hkpBvTreeShape*>(shape);
			const hkpShapeContainer* shapeContainer = bvShape->getContainer();
			hkpShapeCollection::ShapeBuffer buffer;
			for (hkpShapeKey key = shapeContainer->getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = shapeContainer->getNextKey( key ) )
			{
				const hkpShape* child = shapeContainer->getChildShape(key, buffer );
				buildShapeDisplay(child, transform, displayGeometries);
			}
			break;
		}
		
		case HK_SHAPE_CONVEX_LIST:
		case HK_SHAPE_LIST:
		case HK_SHAPE_COLLECTION:
		case HK_SHAPE_TRIANGLE_COLLECTION:
		case HK_SHAPE_MOPP_EMBEDDED:
		{
			const hkpShapeContainer* container = shape->getContainer();

			hkpShapeCollection::ShapeBuffer buffer;
			for (hkpShapeKey key = container->getFirstKey(); container && key != HK_INVALID_SHAPE_KEY; key = container->getNextKey( key ) )
			{
				const hkpShape* child = container->getChildShape(key, buffer );
				buildShapeDisplay(child, transform, displayGeometries);
			}
			break;
		}

		case HK_SHAPE_CONVEX_PIECE:
		{
			const hkpConvexPieceShape* triangulatedConvexShape = static_cast<const hkpConvexPieceShape*>(shape);
			if (triangulatedConvexShape->getRadius() > m_environment.m_minVisibleRadius)
			{
				hkpShapeCollection::ShapeBuffer buffer2;
				for ( int i = 0 ; i < triangulatedConvexShape->m_numDisplayShapeKeys ; i++ )
				{
					const hkpTriangleShape& triangleShape = *( static_cast< const hkpTriangleShape* >( 
						triangulatedConvexShape->m_displayMesh->getChildShape( triangulatedConvexShape->m_displayShapeKeys[i], buffer2 ) ));
					buildShapeDisplay(&triangleShape, transform, displayGeometries);	
				}
			}
			break;
		}

		//
		// shapes that use a radius
		//

		case HK_SHAPE_CYLINDER:
		{
			const hkpCylinderShape* s = static_cast<const hkpCylinderShape*>(shape);
			float cylRadius = s->getCylinderRadius();
			float convexRadius = s->getRadius(); // cyl code has this as the 'padding' radius
			if (convexRadius > m_environment.m_minVisibleRadius)
			{
				hkVector4 top;		top.setTransformedPos( transform, s->getVertex(1) );
				hkVector4 bottom;	bottom.setTransformedPos( transform, s->getVertex(0) );

				// add in the top and bottom radius
				// the radius on the sides will be added to the cyl radius
				hkVector4 axis; axis.setSub4(top, bottom); axis.normalize3();
				axis.mul4(convexRadius);
				top.add4(axis);
				bottom.sub4(axis);

				float totalRadius = cylRadius + convexRadius;
				hkDisplayCylinder* displayCylinder = new hkDisplayCylinder( top, bottom, totalRadius );
				displayCylinder->getTransform() = transform;
				displayGeometries.pushBack( displayCylinder );
			}
			break;
		}

		case HK_SHAPE_BOX:
		{
			const hkpBoxShape* boxShape = static_cast<const hkpBoxShape*>(shape);
			float convexRadius = boxShape->getRadius();
			if (convexRadius > m_environment.m_minVisibleRadius)
			{
				hkVector4 trueExtents; trueExtents.setAll(convexRadius);
				trueExtents.add4( boxShape->getHalfExtents() );

				hkDisplayBox* displayBox = new hkDisplayBox(trueExtents);
				displayBox->getTransform() = transform;
				displayGeometries.pushBack(displayBox);
			}
			break;
		}

		case HK_SHAPE_TRIANGLE:
		{
			const hkpTriangleShape* triangleShape = static_cast<const hkpTriangleShape*>(shape);
			float convexRadius = triangleShape->getRadius();
			if (convexRadius > m_environment.m_minVisibleRadius)
			{
				// A triangle with radius is a convex object made of 5 planes (3 edges, 2 faces)
				// but the radius is distance from the verts so really the pointy edges are rounded
				// so we will add 3 planes at each end point too. If we don't thin triangled get very pointy
				// ends that look like a bug to the unknowing user. 

				// For a large landscape this may be too much to show (as each tri is now up to around 12 new tris (10 normal + flatened pointy ends)
				// but most landscapes have 0 radius.
				const hkVector4& p0 = triangleShape->getVertex(0);
				const hkVector4& p1 = triangleShape->getVertex(1);
				const hkVector4& p2 = triangleShape->getVertex(2);

				if ( hkpTriangleUtil::isDegenerate(p0, p1, p2, 0.001f) )
					break; // too small..

				hkVector4 edge01; edge01.setSub4(p1, p0);
				edge01.normalize3();
				hkVector4 edge12; edge12.setSub4(p2, p1);
				edge12.normalize3();
				hkVector4 edge02; edge02.setSub4(p2, p0);
				edge02.normalize3();
				hkVector4 normal; normal.setCross(edge01, edge02); 

				hkArray<hkVector4> planes(8);
				planes.setSize(8);				
				hkVector4 convexRadiusNormal; 
				hkVector4 planePoint; 

				// face planes
				planes[0] = normal; 
				convexRadiusNormal.setMul4(convexRadius, planes[0]);
				planePoint.setAdd4(convexRadiusNormal, p0);
				planes[0](3) = -planes[0].dot3( planePoint );

				planes[1].setNeg4(normal); 
				convexRadiusNormal.setMul4(convexRadius, planes[1]);
				planePoint.setAdd4(convexRadiusNormal, p0);
				planes[1](3) = -planes[1].dot3( planePoint );

				// edge planes
				planes[2].setCross(edge01, normal); 
				convexRadiusNormal.setMul4(convexRadius, planes[2]);
				planePoint.setAdd4(convexRadiusNormal, p0);
				planes[2](3) = -planes[2].dot3( planePoint );
				
				planes[3].setCross(edge12, normal); 
				convexRadiusNormal.setMul4(convexRadius, planes[3]);
				planePoint.setAdd4(convexRadiusNormal, p1);
				planes[3](3) = -planes[3].dot3( planePoint );
				
				planes[4].setCross(normal, edge02); 
				convexRadiusNormal.setMul4(convexRadius, planes[4]);
				planePoint.setAdd4(convexRadiusNormal, p2);
				planes[4](3) = -planes[4].dot3( planePoint );

				// extra edges and end points to tighten it up.
				planes[5].setAdd4(planes[2], planes[3]); planes[5].normalize3();
				convexRadiusNormal.setMul4(convexRadius, planes[5]);
				planePoint.setAdd4(convexRadiusNormal, p1);
				planes[5](3) = -planes[5].dot3( planePoint );

				planes[6].setAdd4(planes[3], planes[4]); planes[6].normalize3();
				convexRadiusNormal.setMul4(convexRadius, planes[6]);
				planePoint.setAdd4(convexRadiusNormal, p2);
				planes[6](3) = -planes[6].dot3( planePoint );

				planes[7].setAdd4(planes[4], planes[2]); planes[7].normalize3();
				convexRadiusNormal.setMul4(convexRadius, planes[7]);
				planePoint.setAdd4(convexRadiusNormal, p0);
				planes[7](3) = -planes[7].dot3( planePoint );

				// create vertices based on planes intersection points
				hkDisplayConvex* displayGeom = _createConvexDisplayFromPlanes( planes, transform  );
				if (displayGeom)
				{
					displayGeometries.pushBack(displayGeom);
				}
				else
				{		
					HK_WARN(0x3236452A, "Could not create shape representing the convex radius around a triangle!");
				}
			}
			break;
		}

		case HK_SHAPE_CONVEX_VERTICES:
		{
			const hkpConvexVerticesShape* convexVerticesShape = static_cast<const hkpConvexVerticesShape*>(shape);
			float convexRadius = convexVerticesShape->getRadius();
			if (convexRadius > m_environment.m_minVisibleRadius)
			{
				// copy plane equations and expand
				const hkArray<hkVector4>& planeEqs = convexVerticesShape->getPlaneEquations();

				// We don't know if the planes are from the verts or are pre expanded by the 
				// convex radius (as happens with the shrink filter)
				// Once there is agreement on whether the planes should
				// always be a radius distance from the verts then 
				hkReal currentDist = _getPlaneToSurfaceDistance(convexVerticesShape); // may be negative
				
				hkDisplayConvex* displayGeom = HK_NULL;
				const hkReal RADIUS_EPSILON = 0.005f;
				hkArray<hkVector4> newPlanesEqs; newPlanesEqs = planeEqs;
				if ( currentDist > (RADIUS_EPSILON - convexRadius) ) // then not already pushed out (vert within radius of a plane), assume the planes are close to 0 distance from the real object surface 
				{
					int numPlanes = planeEqs.getSize();
					for (int i=0; i < numPlanes; ++i)
					{
						newPlanesEqs[i](3) -= convexRadius;
					}
				}
				
				_addBoundingPlanes(convexVerticesShape, convexRadius, newPlanesEqs);
				displayGeom = _createConvexDisplayFromPlanes( newPlanesEqs, transform );
				
				if (displayGeom)
				{
					displayGeometries.pushBack(displayGeom);
				}
				else
				{		
					HK_WARN(0x3236452A, "Could not create shape representing the convex radius around a convex shape!");
				}
			}			
			break;
		}
	
		default:
			for (int i = 0; i < hkpUserConvexRadiusBuilder::getInstance().m_userConvexRadiusBuilders.getSize(); ++i )
			{
				if ( hkpUserConvexRadiusBuilder::getInstance().m_userConvexRadiusBuilders[i].type == shape->getType() )
				{
					hkpUserConvexRadiusBuilder::getInstance().m_userConvexRadiusBuilders[i].f( shape, transform, displayGeometries, this );
					continue;
				}
			}
	}
}

hkDisplayGeometry* hkpConvexRadiusBuilder::getCurrentRawGeometry(hkArray<hkDisplayGeometry*>& displayGeometries)
{
	if (m_currentGeometry == HK_NULL)
	{
		hkGeometry* geom = new hkGeometry;
		m_currentGeometry = new hkDisplayConvex(geom);
		displayGeometries.pushBack(m_currentGeometry);
	}
	return m_currentGeometry;
}


void hkpConvexRadiusBuilder::resetCurrentRawGeometry()
{
	m_currentGeometry = HK_NULL;
}


HK_SINGLETON_IMPLEMENTATION(hkpUserConvexRadiusBuilder);


void hkpUserConvexRadiusBuilder::registerUserConvexRadiusDisplayBuilder( ConvexRadiusBuilderFunction f, hkpShapeType type )
{
	for (int i = 0; i < m_userConvexRadiusBuilders.getSize(); ++i )
	{
		if ( m_userConvexRadiusBuilders[i].type == type )
		{
			HK_WARN(0x7bbfa3c4, "You have registered two convex shape display builders for user type" << type << ". Do you have two different shapes with this type?");
			return;
		}
	}
	UserShapeBuilder b;
	b.f = f;
	b.type = type;

	m_userConvexRadiusBuilders.pushBack(b);
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
