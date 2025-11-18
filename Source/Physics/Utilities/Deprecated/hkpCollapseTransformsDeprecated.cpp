/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/Deprecated/hkpCollapseTransformsDeprecated.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

hkResult hkpCollapseTransformsDeprecated::collapseAllTransformShapes(hkpRigidBody* rigidBody)
{
	const hkpShape* originalShape = rigidBody->getCollidable()->getShape();

	const hkpShape* currentShape = originalShape;

	// We always act as if "currentShape" is a new shape (so we always remove a reference at the end)
	currentShape->addReference();

	// We do a while loop in case there is more than one chained transform shape
	while (currentShape->getType() == HK_SHAPE_TRANSFORM)
	{
		const hkpTransformShape* tshape = static_cast<const hkpTransformShape*> (currentShape);

		const hkpShape* newShape = collapseTransformShape(tshape);

		currentShape->removeReference();
		
		if (newShape == currentShape)
		{
			// collapseTransformShape couldn't collapse anymore - leave 
			break;
		}
		currentShape = newShape;
	}

	if (currentShape == originalShape)
	{
		// We haven't done really anything
		currentShape->removeReference();

		return HK_FAILURE;
	}
	else
	{
			// This should just really be : 
			//   rigidBody->setShape(currentShape);
			//   currentShape->removeReference();
			// But you can't call setShape() on an hkpRigidBody (yet)
			rigidBody->getCollidable()->getShape()->removeReference();
			rigidBody->getCollidableRw()->setShape( const_cast<hkpShape*> (currentShape) );	

			return HK_SUCCESS;
	}

}


const hkpShape* hkpCollapseTransformsDeprecated::collapseTransformShape(const hkpTransformShape* transformShape)
{
	const hkTransform& parentFromChild = transformShape->getTransform();
	const hkpShape* childShape = transformShape->getChildShape();
	const hkpShape* shape = collapseTransformShape( parentFromChild, childShape );
	if ( shape )
	{
		return shape;
	}
	transformShape->addReference();
	return transformShape;
}

const hkpShape* hkpCollapseTransformsDeprecated::collapseConvexTranslate(const hkpConvexTranslateShape* tls)
{
	hkTransform t; 	t.setIdentity();
	t.setTranslation( tls->getTranslation() );
	const hkpShape* childShape = tls->getChildShape();
	const hkpShape* shape = collapseTransformShape( t, childShape );
	if ( shape )
	{
		return shape;
	}
	tls->addReference();
	return tls;
}

const hkpShape* hkpCollapseTransformsDeprecated::collapseTransformShape(const hkTransform& parentFromChild, const hkpShape* childShape)
{

	// First case : transform is identity -> return child shape
	if (parentFromChild.isApproximatelyEqual(hkTransform::getIdentity()))
	{
		childShape->addReference();
		return childShape;
	}

	// Otherwise : do different stuff depending on the shape type
	const hkpShapeType type = childShape->getType();

	switch (type)
	{
		case HK_SHAPE_CAPSULE:
 			{
				// Capsule : Transform the vertices of the capsule (same as cylinder)
				const hkpCapsuleShape* childCapsuleShape = static_cast<const hkpCapsuleShape*> (childShape);
			
				const hkVector4& childA = childCapsuleShape->getVertices()[0];
				const hkVector4& childB = childCapsuleShape->getVertices()[1];
				const hkReal radius = childCapsuleShape->getRadius();

				hkVector4 parentA;
				parentA.setTransformedPos ( parentFromChild, childA );
				hkVector4 parentB;
				parentB.setTransformedPos ( parentFromChild, childB	);

				hkpCapsuleShape* newCapsule = new hkpCapsuleShape(parentA, parentB, radius);

				return newCapsule;

				break;
			}

		case HK_SHAPE_CYLINDER:
			{
				// Cylinder : Transform both vertices (same as capsule)
				const hkpCylinderShape* childCylinderShape = static_cast<const hkpCylinderShape*> (childShape);

				const hkVector4& childA = childCylinderShape->getVertices()[0];
				const hkVector4& childB = childCylinderShape->getVertices()[1];
				const hkReal cylRadius = childCylinderShape->getCylinderRadius();
				const hkReal radius = childCylinderShape->getRadius();

				hkVector4 parentA;
				parentA.setTransformedPos ( parentFromChild, childA );
				hkVector4 parentB;
				parentB.setTransformedPos ( parentFromChild, childB	);

				hkpCylinderShape* newCylinder = new hkpCylinderShape(parentA, parentB, cylRadius, radius);

				return newCylinder;
			}

		case HK_SHAPE_CONVEX:
		case HK_SHAPE_CONVEX_VERTICES:
		case HK_SHAPE_BOX:
		case HK_SHAPE_SPHERE:
			{
				// Convex shapes : Use hkConvexTranslate or hkConvexTransform shapes
				const hkpConvexShape* childConvexShape = static_cast<const hkpConvexShape*> (childShape);

				// Is is just translation? (sphere's rotation can safely be ignored)
				const hkBool translateOnly = 
					( type == HK_SHAPE_SPHERE ) 
					|| 
					( parentFromChild.getRotation().isApproximatelyEqual(hkTransform::getIdentity().getRotation()) );

				if (translateOnly )
				{
					const hkpConvexTranslateShape* newShape = new hkpConvexTranslateShape(childConvexShape, parentFromChild.getTranslation());
					return newShape;
				}
				else
				{
					const hkpConvexTransformShape* newShape = new hkpConvexTransformShape(childConvexShape, parentFromChild);

					return newShape;
				}

				break;
			}

		case HK_SHAPE_TRANSFORM:
			{
				// Another transform shape : multiply both transforms together
				const hkpTransformShape* childTransformShape = static_cast<const hkpTransformShape*> (childShape);

				const hkTransform& childFromGrandchild = childTransformShape->getTransform();
				const hkpShape* grandchildShape = childTransformShape->getChildShape();

				hkTransform parentFromGrandchild;
				parentFromGrandchild.setMul(parentFromChild, childFromGrandchild);

				hkpTransformShape* newTransformShape = new hkpTransformShape(grandchildShape, parentFromGrandchild);

				return newTransformShape;
			}

		case HK_SHAPE_CONVEX_TRANSFORM:
			{
				// Another transform shape : multiply both transforms together
				const hkpConvexTransformShape* childConvexTransformShape = static_cast<const hkpConvexTransformShape*> (childShape);
				const hkTransform& childFromGrandchild = childConvexTransformShape->getTransform();
				const hkpConvexShape* grandchildShape = childConvexTransformShape->getChildShape();

				hkTransform parentFromGrandchild;
				parentFromGrandchild.setMul(parentFromChild, childFromGrandchild);

				hkpConvexTransformShape* newTransformShape = new hkpConvexTransformShape(grandchildShape, parentFromGrandchild);

				return newTransformShape;
			}

		case HK_SHAPE_CONVEX_TRANSLATE:
			{
				// Another transform shape : multiply both transforms together
				const hkpConvexTranslateShape* childConvexTranslateShape = static_cast<const hkpConvexTranslateShape*> (childShape);

				const hkVector4& childFromGrandchildTranslation = childConvexTranslateShape->getTranslation();
				const hkTransform childFromGrandchild (hkQuaternion::getIdentity(), childFromGrandchildTranslation);
				const hkpConvexShape* grandchildShape = childConvexTranslateShape->getChildShape();


				hkTransform parentFromGrandchild;
				parentFromGrandchild.setMul(parentFromChild, childFromGrandchild);

				hkpConvexTransformShape* newTransformShape = new hkpConvexTransformShape(grandchildShape, parentFromGrandchild);

				return newTransformShape;
			}

		default:
			{
				// We couldn't collapse it
				// So return the original transform shape, adding one reference

				childShape->addReference();

				return childShape;

			}

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
