/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Collide/ShapeUtils/ShapeSharing/hkpShapeSharingUtil.h>

#include <Common/Base/Container/LocalArray/hkLocalArray.h>

#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>

#include <Physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h>

#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Collection/SimpleMesh/hkpSimpleMeshShape.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Common/Base/Algorithm/Sort/hkSort.h>


hkpShapeSharingUtil::Options::Options()
{
	m_equalityThreshold = 1e-6f;
	m_detectPermutedComponents = true;
}


hkpShapeSharingUtil::Results::Results()
: m_numSharedShapes(0)
{
	reset();
}

void hkpShapeSharingUtil::Results::reset()
{
	m_numSharedShapes=0;

}

void hkpShapeSharingUtil::Results::report()
{
	HK_REPORT("Number of shared shapes " << m_numSharedShapes);
}

static void _getShapeChildren (const hkpShape* shape, hkArray<const hkpShape*>& childrenOut)
{
	switch (shape->getType())
	{
		case HK_SHAPE_LIST:
			{
				const hkpListShape* listshape = static_cast<const hkpListShape*> (shape);
				for (int n=0; n<listshape->getNumChildShapes(); n++) 
				{
					const hkpShape* listChildShape = listshape->getChildShapeInl(n); 
					childrenOut.pushBack(listChildShape);
				}
				break;
			}

		case HK_SHAPE_TRANSFORM:
			{
				const hkpTransformShape* transformShape = static_cast<const hkpTransformShape*> (shape);
				childrenOut.pushBack(transformShape->getChildShape());
				break;
			}

		case HK_SHAPE_CONVEX_TRANSFORM:
			{
				const hkpConvexTransformShape* convexTransformShape = static_cast<const hkpConvexTransformShape*> (shape);
				childrenOut.pushBack(convexTransformShape->getChildShape());
				break;
			}

		case HK_SHAPE_CONVEX_TRANSLATE:
			{
				const hkpConvexTranslateShape* convexTranslateShape = static_cast<const hkpConvexTranslateShape*> (shape);
				childrenOut.pushBack(convexTranslateShape->getChildShape());
				break;
			}
		default:
			break;
	}

}

class _ShapeReplacementData
{
	public:



		const hkpShape* findReplacement (const hkpShape* original) const
		{
			for (int i=0; i<m_shapeReplacements.getSize(); i++)
			{
				if (m_shapeReplacements[i].m_originalShape == original)
				{
					return m_shapeReplacements[i].m_replacementShape;
				}
			}

			return HK_NULL;

		}

		void setReplacement(const hkpShape* shape, const hkpShape* replacement)
		{
			for (int i=0; i<m_shapeReplacements.getSize(); i++)
			{
				if ( (m_shapeReplacements[i].m_originalShape == shape) ||
					(m_shapeReplacements[i].m_replacementShape == shape) )
				{
					replacement->addReference();

					if (m_shapeReplacements[i].m_replacementShape)
					{
						m_shapeReplacements[i].m_replacementShape->removeReference();
					}

					m_shapeReplacements[i].m_replacementShape = replacement;
				}
			}
		}

		struct ShapeReplacement
		{
			const hkpShape* m_originalShape;
			const hkpShape* m_replacementShape;
			int m_maxDepth;
		};

		hkArray<ShapeReplacement> m_shapeReplacements;

		int findShapeDataIndex (const hkpShape* shape) const
		{
			for (int i=0; i<m_shapeReplacements.getSize(); i++)
			{
				if (m_shapeReplacements[i].m_originalShape == shape)
				{
					return i;
				}
			}
			return -1;
		}


		void recursivelyParseShapes (const hkpShape* shape, int currentDepth);

		_ShapeReplacementData (const hkArray<hkpRigidBody*>& rigidBodies)
		{
			for (int i=0; i<rigidBodies.getSize(); i++)
			{
				recursivelyParseShapes (rigidBodies[i]->getCollidable()->getShape(),1);
			}
		}

		~_ShapeReplacementData ()
		{
			for (int i=0; i<m_shapeReplacements.getSize(); i++)
			{
				if (m_shapeReplacements[i].m_originalShape)
				{
					m_shapeReplacements[i].m_originalShape->removeReference();
				}
				if (m_shapeReplacements[i].m_replacementShape)
				{
					m_shapeReplacements[i].m_replacementShape->removeReference();
				}
			}
		}
};


void _ShapeReplacementData::recursivelyParseShapes (const hkpShape* shape, int currentDepth)
{
	int index = findShapeDataIndex(shape);

	if (index>=0)
	{
		if (currentDepth > m_shapeReplacements[index].m_maxDepth)
		{
			m_shapeReplacements[index].m_maxDepth=currentDepth;
		}
	}
	else
	{
		ShapeReplacement shapeData;
		shapeData.m_originalShape = shape;
		shapeData.m_replacementShape = HK_NULL;
		shapeData.m_maxDepth = currentDepth;
		m_shapeReplacements.pushBack(shapeData);
		shape->addReference();
	}

	hkArray<const hkpShape*> children;
	_getShapeChildren(shape, children);

	for (int i=0; i<children.getSize(); i++)
	{
		recursivelyParseShapes(children[i], currentDepth+1);
	}
}


/*static*/ hkResult hkpShapeSharingUtil::shareShapes (hkpRigidBody* rigidBody, const Options& options, Results& resultsOut)
{
	hkArray<hkpRigidBody*> tempArray;
	tempArray.pushBack(rigidBody);

	return shareShapes(tempArray, options, resultsOut);
}

/*static*/ hkResult hkpShapeSharingUtil::shareShapes (hkArray<hkpRigidBody*>& rigidBodies, const Options& options, Results& resultsOut)
{
	_ShapeReplacementData shapeReplacementData(rigidBodies);

	resultsOut.reset();

	findIdenticalShapes(options, shapeReplacementData, resultsOut);

	for (int i=0; i<rigidBodies.getSize(); i++)
	{
		hkpRigidBody* rb = rigidBodies[i];
		const hkpShape* originalShape = rb->getCollidable()->getShape();
		const hkpShape* newShape = replaceShapesRecursively(originalShape, shapeReplacementData);

		//remove the previous shape
		originalShape->removeReference();

		rb->getCollidableRw()->setShape( const_cast<hkpShape*>(newShape) );

	}

	return HK_SUCCESS;
}

/*static*/ const hkpShape* hkpShapeSharingUtil::replaceShapesRecursively (const hkpShape* shape, class _ShapeReplacementData& shapeReplacementData)
{
	const hkpShape* replacement = shapeReplacementData.findReplacement(shape);
	if (replacement)
	{
		replacement->addReference();
		return replacement;
	}

	hkArray<const hkpShape*> originalChildren;
	_getShapeChildren(shape, originalChildren);

	const int nChildren = originalChildren.getSize();

	if (nChildren==0)
	{
		shape->addReference();
		return shape;
	}

	hkArray<const hkpShape*> newChildren;
	bool childrenUnmodified = true;
	for (int i=0; i<nChildren;i++) 
	{
		const hkpShape* childShape = originalChildren[i]; 
		const hkpShape* newShape = replaceShapesRecursively(childShape, shapeReplacementData);		
		newChildren.pushBack(newShape);

		if (newShape != childShape) childrenUnmodified = false;
	}

	if (childrenUnmodified)
	{
		for (int i=0; i<nChildren; i++) 
		{
			newChildren[i]->removeReference();
		}
		shape->addReference();
		return shape;
	}

	// else - the children have been modified so we need a new shape:

	switch (shape->getType())
	{
		case HK_SHAPE_LIST:
			{
				//otherwise create a new list, and relinquish ownership of the newly created children to the new list
				hkpListShape* newListShape = new hkpListShape(newChildren.begin(), nChildren);
				for (int n=0; n<nChildren; n++) 
				{
					newChildren[n]->removeReference();		
				}
				
				shapeReplacementData.setReplacement(shape, newListShape);
				return newListShape;
				break;
			}

		case HK_SHAPE_TRANSFORM:
			{
				const hkpTransformShape* transformShape = static_cast<const hkpTransformShape*> (shape);
				const hkpTransformShape* newTransformShape = new hkpTransformShape (newChildren[0], transformShape->getTransform());
				
				newChildren[0]->removeReference();
				shapeReplacementData.setReplacement(transformShape, newTransformShape);

				return newTransformShape;
			}					

		case HK_SHAPE_CONVEX_TRANSFORM:
			{
				const hkpConvexTransformShape* convexTransformShape = static_cast<const hkpConvexTransformShape*> (shape);
				const hkpConvexShape* cvxChild = static_cast<const hkpConvexShape*> (newChildren[0]);
				const hkpConvexTransformShape* newConvexTransformShape = new hkpConvexTransformShape (cvxChild, convexTransformShape->getTransform());

				newChildren[0]->removeReference();
				shapeReplacementData.setReplacement(convexTransformShape, newConvexTransformShape);

				return newConvexTransformShape;
			}

		case HK_SHAPE_CONVEX_TRANSLATE:
			{
				const hkpConvexTranslateShape* convexTranslateShape = static_cast<const hkpConvexTranslateShape*> (shape);
				const hkpConvexShape* cvxChild = static_cast<const hkpConvexShape*> (newChildren[0]);
				const hkpConvexTranslateShape* newConvexTranslateShape = new hkpConvexTranslateShape (cvxChild, convexTranslateShape->getTranslation());

				newChildren[0]->removeReference();
				shapeReplacementData.setReplacement(convexTranslateShape, newConvexTranslateShape);

				return newConvexTranslateShape;
			}
		default:
			break;
	}

	HK_ASSERT(0,0); // We shouldn't get here

	return HK_NULL;
}

static hkTransform _getTransform (const hkpShape* transformShape)
{
	hkpShapeType transformShapeType = transformShape->getType();
	hkTransform parentFromChild;

	switch ( transformShapeType )
	{
		case HK_SHAPE_TRANSFORM:
			{
				const hkpTransformShape* tformshape = static_cast<const hkpTransformShape*> (transformShape);
				parentFromChild = tformshape->getTransform();
				break;
			} 
		case HK_SHAPE_CONVEX_TRANSFORM:
			{
				const hkpConvexTransformShape* ctformshape = static_cast<const hkpConvexTransformShape*> (transformShape);
				parentFromChild = ctformshape->getTransform();
				break;
			}
		case HK_SHAPE_CONVEX_TRANSLATE:
			{
				const hkpConvexTranslateShape* ctlateshape = static_cast<const hkpConvexTranslateShape*> (transformShape);
				parentFromChild.setIdentity();
				parentFromChild.setTranslation( ctlateshape->getTranslation() );
				break;
			}
		default:
			// Shouldn't get here
			HK_ASSERT(0, "Internal error");
			break;
	}

	return parentFromChild;
}

static bool _areShapesIdentical (const hkpShape* shape1, const hkpShape* shape2, const _ShapeReplacementData& shapeReplacementData, const hkpShapeSharingUtil::Options& options);

static bool _areShapeArraysIdentical (const hkArray<const hkpShape*>& array1, const hkArray<const hkpShape*>& array2, const _ShapeReplacementData& shapeReplacementData, const hkpShapeSharingUtil::Options& options)
{
	if (array1.getSize()!=array2.getSize()) return false;

	hkArray<const hkpShape*> copy2; copy2 = array2;

	for (int i=0; i<array1.getSize(); i++)
	{
		for (int j=0; j<copy2.getSize(); j++)
		{
			if (_areShapesIdentical(array1[i], copy2[j], shapeReplacementData, options))
			{
				copy2.removeAt(j);
				break;
			}
		}
	}

	return (copy2.getSize()==0);

}

static bool _floatEqual(const float a, const float b, const hkpShapeSharingUtil::Options& options)
{
	return (hkMath::fabs(a-b)<=options.m_equalityThreshold);
}

static hkBool32 _vectorEqual(const hkVector4& a, const hkVector4& b, const hkpShapeSharingUtil::Options& options)
{
	return (a.equals3(b, options.m_equalityThreshold));
}

static bool _vectorArrayEqual(const hkArray<hkVector4>& arrayA, const hkArray<hkVector4>& arrayB, const hkpShapeSharingUtil::Options& options)
{
	if (arrayA.getSize()!=arrayB.getSize()) return false;

	if (options.m_detectPermutedComponents)
	{
		hkArray<hkVector4> copyB; copyB = arrayB;

		for (int i=0; i<arrayA.getSize(); i++)
		{
			// find closest match in B
			int closest = -1; 
			float minDistSqr = HK_REAL_MAX;

			for (int j=0; j<copyB.getSize(); j++)
			{
				hkVector4 diff; diff.setSub4(arrayA[i], copyB[j]);
				const hkReal distSqr = diff.lengthSquared3();
				if (distSqr < minDistSqr)
				{
					closest = j;
					minDistSqr = distSqr;
				}
			}

			if (closest>=0)
			{
				if (_vectorEqual(arrayA[i], copyB[closest], options))
				{
					copyB.removeAt(closest);
				}
			}
		}

		return copyB.getSize()==0;
	}
	else
	{

		for (int i=0; i<arrayA.getSize(); i++)
		{
			if (!_vectorEqual(arrayA[i], arrayB[i], options))
			{
				return false;
			}
		}

		return true;
	}

}

struct _Triangle
{
	hkVector4 m_vertices[3];
	hkUint8 m_material;

	bool equals (const _Triangle& other, const hkpShapeSharingUtil::Options& options)
	{
		if (m_material!=other.m_material) return false;

		// Allow for triangle indices to be rotated but with the same winding
		for (int shift=0; shift<3; shift++)
		{
			if ( _vectorEqual(m_vertices[0], other.m_vertices[(0+shift)%3], options) && 
				 _vectorEqual(m_vertices[1], other.m_vertices[(1+shift)%3], options) &&
				 _vectorEqual(m_vertices[2], other.m_vertices[(2+shift)%3], options)
				 )
			{
				return true;
			}
		}

		return false;
	}
};

static void _getMeshTriangles (const hkpSimpleMeshShape* meshShape, hkArray<_Triangle>& trianglesOut)
{
	for (int tri=0; tri<meshShape->m_triangles.getSize(); tri++)
	{
		_Triangle triangle;
		triangle.m_material = meshShape->m_materialIndices.getSize()>0 ? meshShape->m_materialIndices[tri] : -1;
		triangle.m_vertices[0] = meshShape->m_vertices[meshShape->m_triangles[tri].m_a];
		triangle.m_vertices[1] = meshShape->m_vertices[meshShape->m_triangles[tri].m_b];
		triangle.m_vertices[2] = meshShape->m_vertices[meshShape->m_triangles[tri].m_c];
		trianglesOut.pushBack(triangle);
	}

}


static bool _areShapesIdentical (const hkpShape* shape1, const hkpShape* shape2, const _ShapeReplacementData& shapeReplacementData, const hkpShapeSharingUtil::Options& options)
{
	// Shapes with different user data shouldn't be shared
	if (shape1->getUserData() != shape2->getUserData())
	{
		return false;
	}

	const hkpShape* replacement1 = shapeReplacementData.findReplacement(shape1);
	if (replacement1 ==shape2) 
	{
		return true;
	}
	
	const hkpShape* replacement2 = shapeReplacementData.findReplacement(shape2);
	if (replacement2==shape1)
	{
		return true;
	}

	if (replacement1 && (replacement1==replacement2))
	{
		return true;
	}

	// Ignore mopps, go to the collection inside it
	if (shape1->getType() == HK_SHAPE_MOPP)
	{
		const hkpMoppBvTreeShape* mopp1 = static_cast<const hkpMoppBvTreeShape*> (shape1);
		const hkpShapeCollection* actualShape1 = mopp1->getShapeCollection();

		return _areShapesIdentical(actualShape1, shape2, shapeReplacementData, options);
	}

	if (shape2->getType() == HK_SHAPE_MOPP)
	{
		const hkpMoppBvTreeShape* mopp2 = static_cast<const hkpMoppBvTreeShape*> (shape2);
		const hkpShapeCollection* actualShape2 = mopp2->getShapeCollection();

		return _areShapesIdentical(shape1, actualShape2, shapeReplacementData, options);
	}

	hkArray<const hkpShape*> children1;
	_getShapeChildren(shape1, children1);
	hkArray<const hkpShape*> children2;
	_getShapeChildren(shape2, children2);

	if (! _areShapeArraysIdentical (children1, children2, shapeReplacementData, options) )
	{
		return false;
	}

	switch (shape1->getType())
	{
		case HK_SHAPE_TRANSFORM:
		case HK_SHAPE_CONVEX_TRANSFORM:
		case HK_SHAPE_CONVEX_TRANSLATE:
			{
				switch (shape2->getType())
				{
					case HK_SHAPE_TRANSFORM:
					case HK_SHAPE_CONVEX_TRANSFORM:
					case HK_SHAPE_CONVEX_TRANSLATE:
						{
							hkTransform trans1 = _getTransform(shape1);
							hkTransform trans2 = _getTransform(shape2);

							if (trans1.isApproximatelyEqual(trans2))
							{
								return true;
							}
							else
							{
								return false;
							}
						}			
					default:
						return false;
				}
			}
		case HK_SHAPE_LIST:
			{
				if (shape2->getType()!=HK_SHAPE_LIST) return false;

				// The children are identical so we are identical
				return true; 				
			}

		case HK_SHAPE_SPHERE:
			{
				if (shape2->getType()!=HK_SHAPE_SPHERE) return false;

				const hkpSphereShape* sphere1 = static_cast<const hkpSphereShape*> (shape1);
				const hkpSphereShape* sphere2 = static_cast<const hkpSphereShape*> (shape2);

				if (!_floatEqual(sphere1->getRadius(), sphere2->getRadius(), options))
				{
					return false;
				}

				return true;
			}

		case HK_SHAPE_BOX:
			{
				if (shape2->getType()!=HK_SHAPE_BOX) return false;

				const hkpBoxShape* box1 = static_cast<const hkpBoxShape*> (shape1);
				const hkpBoxShape* box2 = static_cast<const hkpBoxShape*> (shape2);

				if (!_floatEqual(box1->getRadius(), box2->getRadius(), options))
				{
					return false;
				}

				if (!_vectorEqual(box1->getHalfExtents(), box2->getHalfExtents(), options))
				{
					return false;
				}

				return true;
			}
		case HK_SHAPE_CAPSULE:
			{
				if (shape2->getType()!=HK_SHAPE_CAPSULE) return false;

				const hkpCapsuleShape* capsule1 = static_cast<const hkpCapsuleShape*> (shape1);
				const hkpCapsuleShape* capsule2 = static_cast<const hkpCapsuleShape*> (shape2);

				if (!_floatEqual(capsule1->getRadius(), capsule2->getRadius(), options))
				{
					return false;
				}

				if ( _vectorEqual(capsule1->getVertex(0), capsule2->getVertex(0), options) &&
					 _vectorEqual(capsule1->getVertex(1), capsule2->getVertex(1), options) 
					)
				{
					return true;
				}

				if ( _vectorEqual(capsule1->getVertex(0), capsule2->getVertex(1), options) &&
					_vectorEqual(capsule1->getVertex(1), capsule2->getVertex(0), options) 
					)
				{
					return true;
				}

				return false;
			}

		case HK_SHAPE_CYLINDER:
			{
				if (shape2->getType()!=HK_SHAPE_CYLINDER) return false;

				const hkpCylinderShape* cylinder1 = static_cast<const hkpCylinderShape*> (shape1);
				const hkpCylinderShape* cylinder2 = static_cast<const hkpCylinderShape*> (shape2);

				if (!_floatEqual(cylinder1->getRadius(), cylinder2->getRadius(), options))
				{
					return false;
				}

				if (!_floatEqual(cylinder1->getCylinderRadius(), cylinder2->getCylinderRadius(), options))
				{
					return false;
				}

				if ( _vectorEqual(cylinder1->getVertex(0), cylinder2->getVertex(0), options) &&
					_vectorEqual(cylinder1->getVertex(1), cylinder2->getVertex(1), options) 
					)
				{
					return true;
				}

				if ( _vectorEqual(cylinder1->getVertex(0), cylinder2->getVertex(1), options) &&
					_vectorEqual(cylinder1->getVertex(1), cylinder2->getVertex(0), options) 
					)
				{
					return true;
				}

				return false;
			}
		case HK_SHAPE_CONVEX_VERTICES:
			{
				if (shape2->getType()!=HK_SHAPE_CONVEX_VERTICES) return false;

				const hkpConvexVerticesShape* cvs1 = static_cast<const hkpConvexVerticesShape*> (shape1);
				const hkpConvexVerticesShape* cvs2 = static_cast<const hkpConvexVerticesShape*> (shape2);

				if (!_floatEqual(cvs1->getRadius(), cvs2->getRadius(), options))
				{
					return false;
				}

				hkArray<hkVector4> vertices1; cvs1->getOriginalVertices(vertices1);
				hkArray<hkVector4> vertices2; cvs2->getOriginalVertices(vertices2);

				if (!_vectorArrayEqual(vertices1, vertices2, options))
				{
					return false;
				}

				const hkArray<hkVector4>& planes1 = cvs1->getPlaneEquations();
				const hkArray<hkVector4>& planes2 = cvs2->getPlaneEquations();

				if (!_vectorArrayEqual(planes1, planes2, options))
				{
					return false;
				}

				return true;
			}


		case HK_SHAPE_TRIANGLE_COLLECTION:
			{
				if (shape2->getType()!=HK_SHAPE_TRIANGLE_COLLECTION) return false;

				const hkpSimpleMeshShape* meshShape1 = static_cast<const hkpSimpleMeshShape*> (shape1);
				const hkpSimpleMeshShape* meshShape2 = static_cast<const hkpSimpleMeshShape*> (shape2);

				if (!_floatEqual(meshShape1->getRadius(), meshShape2->getRadius(), options))
				{
					return false;
				}

				if (meshShape1->m_vertices.getSize()!=meshShape2->m_vertices.getSize())
				{
					return false;
				}

				if (meshShape1->m_triangles.getSize()!=meshShape2->m_triangles.getSize())
				{
					return false;
				}

				if (meshShape1->m_materialIndices.getSize()!=meshShape2->m_materialIndices.getSize())
				{
					return false;
				}

				if (options.m_detectPermutedComponents)
				{
					// construct array of explicit triangles
					hkArray<_Triangle> triangles1; _getMeshTriangles(meshShape1, triangles1);
					hkArray<_Triangle> triangles2; _getMeshTriangles(meshShape2, triangles2);

					if (triangles1.getSize()!=triangles2.getSize()) return false;

					hkArray<_Triangle> copy2; copy2 = triangles2;

					for (int i=0; i<triangles1.getSize(); i++)
					{
						for (int j=0; j<copy2.getSize(); j++)
						{
							if (triangles1[i].equals(copy2[j], options))
							{
								copy2.removeAt(j);
								break;
							}
						}
					}

					return (copy2.getSize()==0);

				}
				else
				{
					// compare triangle indices
					for (int i=0; i<meshShape1->m_triangles.getSize(); i++)
					{
						const hkpSimpleMeshShape::Triangle& tri1 = meshShape1->m_triangles[i];
						const hkpSimpleMeshShape::Triangle& tri2 = meshShape2->m_triangles[i];
						if ( (tri1.m_a != tri2.m_a) || (tri1.m_b != tri2.m_b) || (tri1.m_c != tri2.m_c))
						{
							return false;
						}
					}

					// compare vector positions
					if (!_vectorArrayEqual(meshShape1->m_vertices, meshShape2->m_vertices, options))
					{
						return false;
					}

					// compare material indices
					for (int j=0; j<meshShape1->m_materialIndices.getSize(); j++)
					{
						if (meshShape1->m_materialIndices[j]!=meshShape2->m_materialIndices[j])
						{
							return false;
						}
					}

					return true;

				}

			}
		default:
			break;
	}

	return false;
}

const bool _goesFirst (const _ShapeReplacementData::ShapeReplacement& a, const _ShapeReplacementData::ShapeReplacement& b)
{
	return (a.m_maxDepth>b.m_maxDepth);
}

/*static*/ hkResult hkpShapeSharingUtil::findIdenticalShapes (const Options& options, class _ShapeReplacementData& shapeReplacementData, Results& resultsOut)
{
	hkArray<_ShapeReplacementData::ShapeReplacement>& shapeReplacements = shapeReplacementData.m_shapeReplacements;

	// Reorder 
	hkAlgorithm::quickSort(shapeReplacements.begin(), shapeReplacements.getSize(), _goesFirst);

	for (int i=0; i<shapeReplacements.getSize(); i++)
	{
		const hkpShape* shape1 = shapeReplacements[i].m_originalShape;

		for (int j=i+1; j<shapeReplacements.getSize(); j++)
		{
			if (shapeReplacements[j].m_replacementShape!=HK_NULL) continue; // already replaced

			const hkpShape* shape2 = shapeReplacements[j].m_originalShape;

			if (_areShapesIdentical(shape1, shape2, shapeReplacementData, options))
			{
				shapeReplacementData.setReplacement(shape2, shape1);
				shapeReplacementData.setReplacement(shape1, shape1); // mark shape for no more replacements
				resultsOut.m_numSharedShapes++;
			}
		}
	}

	return HK_SUCCESS;
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
