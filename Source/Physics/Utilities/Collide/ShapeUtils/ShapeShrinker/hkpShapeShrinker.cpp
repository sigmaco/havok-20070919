/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Collide/hkpCollide.h>
#include <Physics/Utilities/Collide/ShapeUtils/ShapeShrinker/hkpShapeShrinker.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Physics/Collide/Shape/Misc/Bv/hkpBvShape.h>
#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Misc/ConvexList/hkpConvexListShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>


static hkpShape* _shrinkShape(hkpShape* shape, hkArray<hkpShapeShrinker::ShapeCache>& doneShapes)
{
	// To support shared shapes in a hierarchy, we check if we have done this one before.
	for (int dsi=0; dsi < doneShapes.getSize(); ++dsi)
	{
		if (doneShapes[dsi].originalShape == shape)
		{
			return doneShapes[dsi].newShape;
		}
	}

	hkpShapeShrinker::ShapeCache ds;
	ds.originalShape = shape;
	ds.newShape = HK_NULL;

	switch (shape->getType())
	{
		// types that require no shrink (radius == proper radius or no convex shape radius used)
	case HK_SHAPE_SPHERE: 
	case HK_SHAPE_MULTI_SPHERE:
	case HK_SHAPE_PLANE:
	case HK_SHAPE_CAPSULE: 
			break;

		// Unshrinkable (2D)
	case HK_SHAPE_TRIANGLE:
	case HK_SHAPE_TRIANGLE_COLLECTION:
			break;

		// Collections or shape wrappers
	case HK_SHAPE_CONVEX_TRANSLATE:
		{
			hkpConvexTranslateShape* ts = static_cast<hkpConvexTranslateShape*>( shape );
			
			// Grab the child shape and shrink it
			hkpConvexShape* shrunkenChild = static_cast<hkpConvexShape*>(_shrinkShape(const_cast<hkpConvexShape*>(ts->getChildShape()), doneShapes));

			// EXP-685 : It can be NULL if there were no changes
			if (shrunkenChild)
			{
				// Create a new translate shape with the newly shrunken child
				hkpConvexTranslateShape* shrunkenTranslateShape = new hkpConvexTranslateShape(shrunkenChild, ts->getTranslation());

				ds.newShape = shrunkenTranslateShape;
			}
			break;
		}
	case HK_SHAPE_CONVEX_TRANSFORM:
		{
			hkpConvexTransformShape* ts = static_cast<hkpConvexTransformShape*>( shape );

			// Grab the child shape and shrink it
			hkpConvexShape* shrunkenChild = static_cast<hkpConvexShape*>(_shrinkShape(const_cast<hkpConvexShape*>(ts->getChildShape()), doneShapes));

			// EXP-685 : It can be NULL if there were no changes
			if (shrunkenChild)
			{
				// Create a new transform shape with the newly shrunken child
				hkpConvexTransformShape* shrunkenTransformShape = new hkpConvexTransformShape(shrunkenChild, ts->getTransform());

				ds.newShape = shrunkenTransformShape;
			}

			break;
		}	
	case HK_SHAPE_TRANSFORM:
		{
			hkpTransformShape* ts = static_cast<hkpTransformShape*>( shape );

			// Grab the child shape and shrink it
			hkpShape* shrunkenChild = static_cast<hkpShape*>(_shrinkShape(const_cast<hkpShape*>(ts->getChildShape()), doneShapes));

			// EXP-685 : It can be NULL if there were no changes
			if (shrunkenChild)
			{
				// Create a new transform shape with the newly shrunken child
				hkpTransformShape* shrunkenTransformShape = new hkpTransformShape(shrunkenChild, ts->getTransform());

				ds.newShape = shrunkenTransformShape;
			}

			break;
		}
	case HK_SHAPE_BV:
		{
			hkpBvShape* bvShape = static_cast<hkpBvShape*>(shape);
			ds.newShape = _shrinkShape( const_cast<hkpShape*>(bvShape->getChildShape()), doneShapes );
			break;
		}

	case HK_SHAPE_BV_TREE:
	case HK_SHAPE_MOPP:
		{
			// const hkpBvTreeShape* bvShape = static_cast<const hkpBvTreeShape*>(shape);
			// TODO: chould add an option to reduced the landscape radius. (can't 
			//       really add to radius as the mopp is created? )

			break;
		}
	case HK_SHAPE_CONVEX_LIST:
	case HK_SHAPE_LIST:
	case HK_SHAPE_COLLECTION:
		{
			const hkpShapeContainer* shapeContainer = shape->getContainer();
			HK_ASSERT2(0xDBC03771, shapeContainer, "Shape to be shrunk returned a null shape container.");

			hkpShapeCollection::ShapeBuffer buffer;

			const bool isMutable = ((shape->getType() == HK_SHAPE_LIST) || (shape->getType() == HK_SHAPE_CONVEX_LIST));
			hkArray<hkpShape*> newShapes;
			newShapes.reserveExactly(shapeContainer->getNumChildShapes());
			bool foundNewOnes = false;
			for (hkpShapeKey key = shapeContainer->getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = shapeContainer->getNextKey( key ) )
			{
				const hkpShape* child = shapeContainer->getChildShape(key, buffer );
				hkpShape* newShape = _shrinkShape(const_cast<hkpShape*>(child), doneShapes);
				if (newShape)
				{
					// ehh.. not in charge of the shapes in the collecton so can't change them
					if (!isMutable)
					{
						HK_WARN( 0x0, "Found a shape collection with children that required changing. Not processing.");
					}
					foundNewOnes = true;
				}
				newShapes.pushBack(newShape? newShape : const_cast<hkpShape*>(child) );
			}

			hkpShape* newS = HK_NULL;
			if (foundNewOnes && isMutable)
			{
				if ( shape->getType() == HK_SHAPE_LIST ) 
				{
					newS = new hkpListShape( newShapes.begin(), newShapes.getSize() );
				}
				else if ( shape->getType() == HK_SHAPE_CONVEX_LIST )
				{
					newS = new hkpConvexListShape( (const hkpConvexShape**)newShapes.begin(), newShapes.getSize() );
				}
			}

			ds.newShape = newS;
			break;
		}

	case HK_SHAPE_CYLINDER: // created with two radii. One is the correct one, the other (padding) left at default, so if we reduce the normal 
		// radius by the padding, and the length by the padding too it will be visually correct
		{
			hkpCylinderShape* cylShape = static_cast<hkpCylinderShape*>(shape);
			float rP = cylShape->getRadius();	
			float rC = cylShape->getCylinderRadius();
			
			if (rC > rP)
			{
				rC -= rP;
				
				cylShape->setCylinderRadius(rC);

				// shift the end points down by radius;
				hkVector4 dir; dir.setSub4( cylShape->getVertex(1), cylShape->getVertex(0) );
				dir.normalize3();
				dir.mul4( rP );

				hkVector4 newV0; newV0.setAdd4(cylShape->getVertex(0), dir);
				hkVector4 newV1; newV1.setSub4(cylShape->getVertex(1), dir );
				cylShape->setVertex(0, newV0);
				cylShape->setVertex(1, newV1);
			}
			else
			{
				HK_WARN_ALWAYS(0x443a52c0,
					"hkpShapeShrinker has attempted to shrink a hkpCylinderShape too far,"
					" and the resulting shape is invalid. The shape has not been modified.");
			}
			
			// EXP-682 : We need to register in-place changes as well, otherwise they may happen more than once
			ds.newShape = cylShape;
			break;
		}

	case HK_SHAPE_BOX: // exported from max etc with default radius so definitly needs a shrink
		{
			hkpBoxShape* boxShape = static_cast<hkpBoxShape*>(shape);
			// reduce the extents by the radius
			float r = boxShape->getRadius();
			hkVector4 ext = boxShape->getHalfExtents();
			bool toosmall = false;

			if (ext(0) > r)
			{
				ext(0) -= r;
			}
			else
			{
				toosmall = true;
			}
			if (ext(1) > r)
			{
				ext(1) -= r;
			}
			else
			{
				toosmall = true;
			}
			if (ext(2) > r)
			{
				ext(2) -= r;
			}
			else
			{
				toosmall = true;
			}

			if (!toosmall)
			{
				boxShape->setHalfExtents(ext);
			}
			else
			{
				HK_WARN_ALWAYS(0x445e14b2,
					"hkpShapeShrinker has attempted to shrink a hkpBoxShape too far,"
					" and the resulting shape is invalid. The shape has not been modified.");
			}
			
			// EXP-682 : We need to register in-place changes as well, otherwise they may happen more than once
			ds.newShape = boxShape;
			break;
		}

	case HK_SHAPE_CONVEX_VERTICES:
		{
			hkpConvexVerticesShape* convexVerticesShape = static_cast<hkpConvexVerticesShape*>(shape);
			const hkArray<hkVector4>& planeEq = convexVerticesShape->getPlaneEquations();
			const float radius = convexVerticesShape->getRadius();
			const int numPlanes = planeEq.getSize();
			hkArray<hkVector4> newVerts;

			// reduce the planes distance by the padding radius
			hkArray<hkVector4> newPlaneEq(numPlanes);

			for (int pidx = 0; pidx < numPlanes; ++pidx)
			{
				newPlaneEq[pidx] = planeEq[pidx];
				newPlaneEq[pidx](3) += radius;
			}

			// create new vertices based on the shrunk verts and weld
			hkpGeometryUtility::createVerticesFromPlaneEquations(newPlaneEq, newVerts);

			// easy to shrink a shape too far and make no verts
			// so check if that has happened.
			if (newVerts.getSize() < 1)
			{
				HK_WARN_ALWAYS(0x447f32f6,
					"hkpShapeShrinker has attempted to shrink a hkpConvexVerticesShape too far,"
					" and the resulting shape is invalid. The shape has not been modified.");
				break;
			}
			
			hkStridedVertices newSverts;
			newSverts.m_numVertices = newVerts.getSize();
			newSverts.m_striding = sizeof(hkVector4);
			newSverts.m_vertices = (const float*)( newVerts.begin() );

			// new verts, orig planes (for casts)
			hkpConvexVerticesShape* newShape = new hkpConvexVerticesShape(newSverts, planeEq, radius);
			ds.newShape = newShape;
			break;
		}

		//
		// Unhandled at this time
		//
	case HK_SHAPE_CONVEX_PIECE:
	case HK_SHAPE_SAMPLED_HEIGHT_FIELD:	
	default:
		break;
	}

	// HVK-3576
	// If we have created a new shape, copy the old user data to the new shape.
	if (ds.newShape)
	{
		ds.newShape->setUserData(ds.originalShape->getUserData());
		doneShapes.pushBack(ds);
	}

	return ds.newShape; // new shape, null if not new
}

hkpShape* hkpShapeShrinker::shrinkByConvexRadius( hkpShape* s, hkArray<ShapeCache>* doneShapes )
{
	if (doneShapes)
	{
		return _shrinkShape(s, *doneShapes);
	}
	else
	{
		// make a temp one
		hkArray<ShapeCache> shapeCache;
		return _shrinkShape(s, shapeCache);
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
