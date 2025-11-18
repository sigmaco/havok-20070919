/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Collide/hkpCollide.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>
#include <Physics/Utilities/VisualDebugger/Viewer/hkpShapeDisplayBuilder.h>
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
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppEmbeddedShape.h>
#include <Physics/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Physics/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Collide/Shape/Convex/PackedConvexVertices/hkpPackedConvexVerticesShape.h>
#include <Physics/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>
#include <Physics/Collide/Shape/HeightField/Plane/hkpPlaneShape.h>

#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Misc/MultiRay/hkpMultiRayShape.h>

#include <Physics/Collide/Shape/Compound/Collection/ConvexPieceMesh/hkpConvexPieceShape.h>

#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

#include <Common/Visualize/Shape/hkDisplayPlane.h>
#include <Common/Visualize/Shape/hkDisplaySphere.h>
#include <Common/Visualize/Shape/hkDisplayCylinder.h>
#include <Common/Visualize/Shape/hkDisplayCapsule.h>
#include <Common/Visualize/Shape/hkDisplayBox.h>
#include <Common/Visualize/Shape/hkDisplayConvex.h>
#include <Common/Visualize/hkDebugDisplay.h>


hkpShapeDisplayBuilder::hkpShapeDisplayBuilderEnvironment::hkpShapeDisplayBuilderEnvironment()
:	m_spherePhiRes(8),
	m_sphereThetaRes(8)
{
}



hkpShapeDisplayBuilder::hkpShapeDisplayBuilder(const hkpShapeDisplayBuilderEnvironment& env)
:	m_environment(env),
	m_currentGeometry(HK_NULL)
{
}


void hkpShapeDisplayBuilder::buildDisplayGeometries(		const hkpShape* shape,
														hkArray<hkDisplayGeometry*>& displayGeometries)
{

	hkTransform transform;
	transform.setIdentity();

	resetCurrentRawGeometry();
	displayGeometries.clear();

	buildShapeDisplay(shape, transform, displayGeometries);
}



// This is the alternative to having a buildDisplayGeometry as a virtual function in Shape.
void hkpShapeDisplayBuilder::buildShapeDisplay(		const hkpShape* shape,
													const hkTransform& transform,
													hkArray<hkDisplayGeometry*>& displayGeometries)
{
	switch (shape->getType())
	{
		case HK_SHAPE_SPHERE:
		{
			const hkpSphereShape* sphereShape = static_cast<const hkpSphereShape*>(shape);
			hkVector4 zeroVector;
			zeroVector.setZero4();
			hkSphere sphere( zeroVector, sphereShape->getRadius());

			hkDisplaySphere* displaySphere = new hkDisplaySphere(sphere, m_environment.m_sphereThetaRes, m_environment.m_spherePhiRes);

			displaySphere->getTransform() = transform;
			displayGeometries.pushBack(displaySphere);

			break;
		}
		case HK_SHAPE_MULTI_SPHERE:
		{
			const hkpMultiSphereShape* s = static_cast<const hkpMultiSphereShape*>(shape);
			const hkVector4* v = s->getSpheres();
			for(int i = 0; i < s->getNumSpheres(); ++i)
			{
				hkSphere sphere( hkVector4::getZero(), v[i](3) );
				hkDisplaySphere* displaySphere = new hkDisplaySphere(sphere, m_environment.m_sphereThetaRes, m_environment.m_spherePhiRes);

				displaySphere->getTransform().setIdentity();
				displaySphere->getTransform().setTranslation(v[i]);
				displayGeometries.pushBack(displaySphere);
			}

			break;
		}
		case HK_SHAPE_PLANE:
		{
			const hkpPlaneShape* planeShape = static_cast<const hkpPlaneShape*>(shape);
			const hkVector4& pEq = planeShape->getPlane();
			hkAabb localAabb;
			planeShape->getAabb(hkTransform::getIdentity(), 0.001f, localAabb);
			
			hkVector4 c; c.setSub4(localAabb.m_max, localAabb.m_min);
			hkVector4 perpToNorm; perpToNorm.setZero4(); perpToNorm(c.getMajorAxis()) = 1;
			c.mul4(0.5f);
			hkVector4 ext = c;
			c.add4(localAabb.m_min);

			hkDisplayPlane* displayPlane = new hkDisplayPlane(pEq, perpToNorm, c, ext);
			displayPlane->getTransform() = transform;
			displayGeometries.pushBack(displayPlane);
			break;
		}
		case HK_SHAPE_CAPSULE:
		{
			const hkpCapsuleShape* s = static_cast<const hkpCapsuleShape*>(shape);

			hkDisplayCapsule* displayCapsule = new hkDisplayCapsule( s->getVertex(1), s->getVertex(0), s->getRadius() );
			displayCapsule->getTransform() = transform;
			displayGeometries.pushBack( displayCapsule );
 
			break;
		}
		case HK_SHAPE_CYLINDER:
		{
			const hkpCylinderShape* s = static_cast<const hkpCylinderShape*>(shape);

			hkVector4 top;		top.setTransformedPos( transform, s->getVertex(1) );
			hkVector4 bottom;	bottom.setTransformedPos( transform, s->getVertex(0) );
			hkDisplayCylinder* displayCylinder = new hkDisplayCylinder( top, bottom, s->getCylinderRadius() );
			displayCylinder->getTransform() = transform;
			displayGeometries.pushBack( displayCylinder );
 
			break;
		}

		case HK_SHAPE_MULTI_RAY:
		{
			// TODO
			const hkpMultiRayShape* s = static_cast<const hkpMultiRayShape*>(shape);

			hkDisplayGeometry* displayGeom = getCurrentRawGeometry(displayGeometries);
			hkGeometry* geom = displayGeom->getGeometry();
			HK_ASSERT(0x142cb874, geom != HK_NULL);

			int vertBase = 0;

			for(int j = 0; j < s->getRays().getSize(); j++)
			{
				hkpMultiRayShape::Ray seg = s->getRays()[j];

				hkVector4& start = *geom->m_vertices.expandBy(1);
				start = seg.m_start;
				start.setTransformedPos( transform, start );

				hkVector4& joggle = *geom->m_vertices.expandBy(1);
				joggle = seg.m_start;
				hkVector4 offset; offset.set( 0.01f, 0.f, 0.f );
				joggle.add4( offset );

				hkVector4& end = *geom->m_vertices.expandBy(1);
				end = seg.m_end;
				end.setTransformedPos( transform, end );

				hkGeometry::Triangle& tri = *geom->m_triangles.expandBy(1);
				tri.set(vertBase, vertBase + 1, vertBase + 2);

				vertBase += 3;
			}
			break;
		}
		case HK_SHAPE_BOX:
		{
			const hkpBoxShape* boxShape = static_cast<const hkpBoxShape*>(shape);
			hkDisplayBox* displayBox = new hkDisplayBox(boxShape->getHalfExtents());
			displayBox->getTransform() = transform;
			displayGeometries.pushBack(displayBox);
			break;
		}
		
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
		/*
		case HK_SHAPE_CONVEX_WELDER:
		{
			const hkConvexWelderShape* cxWeldShape = static_cast<const hkConvexWelderShape*>(shape);
			shape = cxWeldShape->m_compoundShapeToBeWelded;
		}
		*/

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
		case HK_SHAPE_EXTENDED_MESH:
		case HK_SHAPE_MOPP_EMBEDDED:
		{
			const hkpShapeContainer* shapeContainer = shape->getContainer();
			
			hkpShapeCollection::ShapeBuffer buffer;

			for (hkpShapeKey key = shapeContainer->getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = shapeContainer->getNextKey( key ) )
			{
				const hkpShape* child = shapeContainer->getChildShape(key, buffer );
				buildShapeDisplay(child, transform, displayGeometries);
			}
		
			break;
		}
		case HK_SHAPE_TRIANGLE:
		{
			const hkpTriangleShape* triangleShape = static_cast<const hkpTriangleShape*>(shape);

			hkDisplayGeometry* displayGeom = getCurrentRawGeometry(displayGeometries);
			hkGeometry* geom = displayGeom->getGeometry();
			HK_ASSERT(0x4b5bb14e, geom != HK_NULL);

				// Convert these vertices to the transformed space.
			int vertBase = geom->m_vertices.getSize();

			geom->m_vertices.expandBy(1)->setTransformedPos(transform, triangleShape->getVertex(0));
			geom->m_vertices.expandBy(1)->setTransformedPos(transform, triangleShape->getVertex(1));
			geom->m_vertices.expandBy(1)->setTransformedPos(transform, triangleShape->getVertex(2));
			hkGeometry::Triangle& tri = *geom->m_triangles.expandBy(1);
			tri.set(vertBase, vertBase + 1, vertBase + 2);

			if ( triangleShape->getExtrusion().length3() > 0 )
			{
				hkVector4 ext0; ext0.setAdd4(triangleShape->getVertex(0), triangleShape->getExtrusion());
				hkVector4 ext1; ext1.setAdd4(triangleShape->getVertex(1), triangleShape->getExtrusion());
				hkVector4 ext2; ext2.setAdd4(triangleShape->getVertex(2), triangleShape->getExtrusion());
				geom->m_vertices.expandBy(1)->setTransformedPos(transform, ext0);
				geom->m_vertices.expandBy(1)->setTransformedPos(transform, ext1);
				geom->m_vertices.expandBy(1)->setTransformedPos(transform, ext2);

				hkGeometry::Triangle* extrudedTris = geom->m_triangles.expandBy(7);
				extrudedTris[0].set(vertBase + 3, vertBase + 1, vertBase + 0);
				extrudedTris[1].set(vertBase + 3, vertBase + 4, vertBase + 1);
				extrudedTris[2].set(vertBase + 4, vertBase + 5, vertBase + 1);
				extrudedTris[3].set(vertBase + 5, vertBase + 2, vertBase + 1);
				extrudedTris[4].set(vertBase + 5, vertBase + 0, vertBase + 2);
				extrudedTris[5].set(vertBase + 5, vertBase + 3, vertBase + 0);
				extrudedTris[6].set(vertBase + 5, vertBase + 4, vertBase + 3);
			}

			break;
		}

		case HK_SHAPE_CONVEX_VERTICES:
		case HK_SHAPE_PACKED_CONVEX_VERTICES:
		{
			int numSpheres = shape->getType() == HK_SHAPE_CONVEX_VERTICES
				? static_cast<const hkpConvexVerticesShape*>(shape)->getNumCollisionSpheres()
				: static_cast<const hkpPackedConvexVerticesShape*>(shape)->getNumCollisionSpheres();

			hkLocalArray<hkSphere> vertices(numSpheres); vertices.setSize( numSpheres );
			
			const hkSphere* spheres = shape->getType() == HK_SHAPE_CONVEX_VERTICES
				? static_cast<const hkpConvexVerticesShape*>(shape)->getCollisionSpheres(vertices.begin())
				: static_cast<const hkpPackedConvexVerticesShape*>(shape)->getCollisionSpheres(vertices.begin());

				// Convert these vertices to the transformed space.
			hkArray<hkVector4> transformedVertices;
			transformedVertices.setSize( numSpheres );
			for(int i = 0; i < numSpheres; i++)
			{
				transformedVertices[i].setTransformedPos(transform, spheres[i].getPosition());
			}

			hkGeometry* outputGeom = new hkGeometry;
			hkArray<hkVector4> usedVertices;
			hkStridedVertices stridedVerts;
			{
				stridedVerts.m_numVertices = transformedVertices.getSize();
				stridedVerts.m_striding = sizeof(hkVector4);
				stridedVerts.m_vertices = &(transformedVertices[0](0));
			}
			hkpGeometryUtility::createConvexGeometry( stridedVerts, *outputGeom );

			hkDisplayConvex* displayGeom = new hkDisplayConvex(outputGeom);

			displayGeometries.pushBack(displayGeom);
			break;
		}
		case HK_SHAPE_CONVEX_PIECE:
		{
			const hkpConvexPieceShape* triangulatedConvexShape = static_cast<const hkpConvexPieceShape*>(shape);

			// Create the geometry
			hkGeometry* outputGeom = new hkGeometry;

			hkpShapeCollection::ShapeBuffer buffer2;

			for ( int i = 0 ; i < triangulatedConvexShape->m_numDisplayShapeKeys ; i++ )
			{
				const hkpTriangleShape& triangleShape = *( static_cast< const hkpTriangleShape* >( 
					triangulatedConvexShape->m_displayMesh->getChildShape( triangulatedConvexShape->m_displayShapeKeys[i], buffer2 ) ));

				// pushback information about this triangle to the new geometry.
				hkGeometry::Triangle& tri = *outputGeom->m_triangles.expandBy(1);

				int vertexSize = outputGeom->m_vertices.getSize();
				tri.set( vertexSize, vertexSize+1, vertexSize+2	);

				for ( int j = 0 ; j < 3 ; j++ )
				{
					hkVector4& transformedVertex = *outputGeom->m_vertices.expandBy(1);
					transformedVertex.setTransformedPos(transform, triangleShape.getVertex( j ));
				}
			}
			
			hkDisplayConvex* displayGeom = new hkDisplayConvex(outputGeom);
			displayGeometries.pushBack(displayGeom);
			
			break;
		}

		case HK_SHAPE_SAMPLED_HEIGHT_FIELD:
		{
			const hkpSampledHeightFieldShape* heightField = static_cast<const hkpSampledHeightFieldShape*>(shape);

			hkDisplayGeometry* displayGeom = getCurrentRawGeometry(displayGeometries);
			hkGeometry* geom = displayGeom->getGeometry();
			HK_ASSERT(0x34673afe, geom != HK_NULL);

				// Convert these vertices to the transformed space.
			hkVector4 scale = heightField->m_intToFloatScale;

			for (int i = 0; i < heightField->m_xRes-1; i++)
			{
				for (int j = 0; j < heightField->m_zRes-1; j++)
				{
					hkVector4 p00; p00.set( i+0.f, heightField->getHeightAt( i+0, j+0 ), j+0.f ); p00.mul4( scale );
					hkVector4 p01; p01.set( i+0.f, heightField->getHeightAt( i+0, j+1 ), j+1.f ); p01.mul4( scale );
					hkVector4 p10; p10.set( i+1.f, heightField->getHeightAt( i+1, j+0 ), j+0.f ); p10.mul4( scale );
					hkVector4 p11; p11.set( i+1.f, heightField->getHeightAt( i+1, j+1 ), j+1.f ); p11.mul4( scale );

					{
						int vertBase = geom->m_vertices.getSize();

						geom->m_vertices.expandBy(1)->setTransformedPos(transform, p00 );
						geom->m_vertices.expandBy(1)->setTransformedPos(transform, p01 );
						geom->m_vertices.expandBy(1)->setTransformedPos(transform, p10 );
						geom->m_vertices.expandBy(1)->setTransformedPos(transform, p11 );

						if ( heightField->getTriangleFlip())
						{
							geom->m_triangles.expandBy(1)->set(vertBase + 0, vertBase + 1, vertBase + 3);
							geom->m_triangles.expandBy(1)->set(vertBase + 0, vertBase + 3, vertBase + 2);
						}
						else
						{
							geom->m_triangles.expandBy(1)->set(vertBase + 0, vertBase + 1, vertBase + 2);
							geom->m_triangles.expandBy(1)->set(vertBase + 3, vertBase + 2, vertBase + 1);
						}
					}
				}
			}

			break;			
		}

		default:
		{
			for (int i = 0; i < hkpUserShapeDisplayBuilder::getInstance().m_userShapeBuilders.getSize(); ++i )
			{
				if ( hkpUserShapeDisplayBuilder::getInstance().m_userShapeBuilders[i].type == shape->getType() )
				{
					hkpUserShapeDisplayBuilder::getInstance().m_userShapeBuilders[i].f( shape, transform, displayGeometries, this );
					continue;
				}
			}
		}
	}
}

hkDisplayGeometry* hkpShapeDisplayBuilder::getCurrentRawGeometry(hkArray<hkDisplayGeometry*>& displayGeometries)
{
	if (m_currentGeometry == HK_NULL)
	{
		hkGeometry* geom = new hkGeometry;
		m_currentGeometry = new hkDisplayConvex(geom);
		displayGeometries.pushBack(m_currentGeometry);
	}
	return m_currentGeometry;
}


void hkpShapeDisplayBuilder::resetCurrentRawGeometry()
{
	m_currentGeometry = HK_NULL;
}


HK_SINGLETON_IMPLEMENTATION(hkpUserShapeDisplayBuilder);


void hkpUserShapeDisplayBuilder::registerUserShapeDisplayBuilder( ShapeBuilderFunction f, hkpShapeType type )
{
	for (int i = 0; i < m_userShapeBuilders.getSize(); ++i )
	{
		if ( m_userShapeBuilders[i].type == type )
		{
			HK_WARN(0x7bbfa3c4, "You have registered two shape display builders for user type" << type << ". Do you have two different shapes with this type?");
			return;
		}
	}
	UserShapeBuilder b;
	b.f = f;
	b.type = type;

	m_userShapeBuilders.pushBack(b);
}

void HK_CALL hkpShapeDisplayBuilder::addObjectToDebugDisplay( const hkpShape* shape, hkTransform& t, hkUlong id )
{
	hkpShapeDisplayBuilder::hkpShapeDisplayBuilderEnvironment env;
	hkpShapeDisplayBuilder builder(env);


	hkArray<hkDisplayGeometry*> displayGeometries;

	builder.buildDisplayGeometries( shape, displayGeometries );
	hkDebugDisplay::getInstance().addGeometry( displayGeometries, t, id, 0, (hkUlong)shape );

	while( displayGeometries.getSize() )
	{
		delete displayGeometries[0];
		displayGeometries.removeAt(0);
	}
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
