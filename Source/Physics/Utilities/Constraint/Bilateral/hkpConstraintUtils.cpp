/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Utilities/Constraint/Bilateral/hkpConstraintUtils.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/Constraint/Bilateral/BallAndSocket/hkpBallAndSocketConstraintData.h>
#include <Physics/Dynamics/Constraint/Bilateral/Hinge/hkpHingeConstraintData.h>
#include <Physics/Dynamics/Constraint/Bilateral/LimitedHinge/hkpLimitedHingeConstraintData.h>

#include <Physics/Dynamics/Constraint/Chain/BallSocket/hkpBallSocketChainData.h>
#include <Physics/Dynamics/Constraint/Chain/Powered/hkpPoweredChainData.h>

#include <Physics/Dynamics/Constraint/Bilateral/Ragdoll/hkpRagdollConstraintData.h>

#include <Physics/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Physics/Dynamics/Constraint/Motor/hkpConstraintMotor.h>
#include <Physics/Dynamics/Constraint/Chain/hkpConstraintChainInstance.h>
#include <Physics/Dynamics/Constraint/Chain/BallSocket/hkpBallSocketChainData.h>

#include <Physics/Dynamics/Constraint/Bilateral/BallAndSocket/hkpBallAndSocketConstraintData.h>
//#include <hkdynamics/constraint/motor/position/hkpPositionConstraintMotor.h>

#include <Physics/Dynamics/World/hkpSimulationIsland.h>

#include <Physics/Dynamics/Constraint/Chain/RagdollLimits/hkpRagdollLimitsData.h>
#include <Physics/Dynamics/Constraint/Chain/HingeLimits/hkpHingeLimitsData.h>

#include <Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h>

hkpConstraintInstance* hkpConstraintUtils::convertToPowered (const hkpConstraintInstance* originalConstraint, hkpConstraintMotor* constraintMotor, hkBool enableMotors)
{
	hkpConstraintInstance* newConstraint = HK_NULL;
	hkpConstraintData* constraintData = originalConstraint->getData();
	
	hkpEntity* entityA = originalConstraint->getEntityA();
	hkpEntity* entityB = originalConstraint->getEntityB();

	switch (constraintData->getType())
	{
		case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:
			{
				hkpLimitedHingeConstraintData* oldConstraintData = static_cast<hkpLimitedHingeConstraintData*> (constraintData);
				hkpLimitedHingeConstraintData* newConstraintData = new hkpLimitedHingeConstraintData();

				newConstraintData->m_atoms = oldConstraintData->m_atoms;

				newConstraintData->setMotor( constraintMotor );
				newConstraintData->setMotorActive(HK_NULL, enableMotors);

				newConstraint = new hkpConstraintInstance (entityA, entityB, newConstraintData, originalConstraint->getPriority());
				newConstraintData->removeReference();

				newConstraint->setName( originalConstraint->getName() );

				break;
			}

		case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:
			{
				hkpRagdollConstraintData* oldConstraintData = static_cast<hkpRagdollConstraintData*> (constraintData);
				hkpRagdollConstraintData* newConstraintData = new hkpRagdollConstraintData();

				newConstraintData->m_atoms = oldConstraintData->m_atoms;

				newConstraintData->setTwistMotor(constraintMotor);
				newConstraintData->setPlaneMotor(constraintMotor);
				newConstraintData->setConeMotor(constraintMotor);
				newConstraintData->setMotorsActive(HK_NULL, enableMotors);
				
				newConstraint = new hkpConstraintInstance (entityA, entityB, newConstraintData, originalConstraint->getPriority());
				newConstraintData->removeReference();

				newConstraint->setName( originalConstraint->getName() );

				break;

			}

		default:
			{
				HK_WARN_ALWAYS (0xabba1b34, "Cannot convert constraint \""<<originalConstraint->getName()<<"\" to a powered constraint.");
				HK_WARN_ALWAYS (0xabba1b34, "Only limited hinges and ragdoll constraints can be powered.");
				return HK_NULL;
			}
	}
	
	return newConstraint;
}

hkpConstraintInstance* HK_CALL hkpConstraintUtils::convertToLimits (hkpConstraintInstance* originalConstraint)
{
	hkpConstraintData* originalData = originalConstraint->getData();
	hkpConstraintData* limitData = HK_NULL;

	switch(originalData->getType())
	{
	case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:
		{
			hkpRagdollLimitsData* n = new hkpRagdollLimitsData();
			hkpRagdollConstraintData* o = static_cast<hkpRagdollConstraintData*>(originalData);
			limitData = n;

			n->m_atoms.m_rotations.m_rotationA = o->m_atoms.m_transforms.m_transformA.getRotation();
			n->m_atoms.m_rotations.m_rotationB = o->m_atoms.m_transforms.m_transformB.getRotation();
			n->m_atoms.m_twistLimit  = o->m_atoms.m_twistLimit;
			n->m_atoms.m_planesLimit = o->m_atoms.m_planesLimit;
			n->m_atoms.m_coneLimit   = o->m_atoms.m_coneLimit;
			hkBool stabilizationEnabled = o->getConeLimitStabilization();
			n->setConeLimitStabilization(stabilizationEnabled);

			break;
		}
	case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:
		{
			hkpHingeLimitsData* n = new hkpHingeLimitsData();
			hkpLimitedHingeConstraintData* o = static_cast<hkpLimitedHingeConstraintData*>(originalData);
			limitData = n;

			n->m_atoms.m_rotations.m_rotationA = o->m_atoms.m_transforms.m_transformA.getRotation();
			n->m_atoms.m_rotations.m_rotationB = o->m_atoms.m_transforms.m_transformB.getRotation();
			n->m_atoms.m_angLimit = o->m_atoms.m_angLimit;
			n->m_atoms.m_2dAng     = o->m_atoms.m_2dAng;

			break;
		}
	case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL_LIMITS:
	case hkpConstraintData::CONSTRAINT_TYPE_HINGE_LIMITS:
		{
			// Just return the original constraint.
			// Remember to add a reference.
			HK_WARN(0xad67d7db, "The original constraint already is of the 'limits' type.");
			originalConstraint->addReference();
			return originalConstraint;
		}

	default:
		{
			HK_ASSERT2(0xad67d7da, false, "Unsupported constraint type. Cannot generate limits constraints.");
			return HK_NULL;
		}
	}

	if (limitData)
	{
		hkpConstraintInstance* limitInstance = new hkpConstraintInstance( originalConstraint->getEntityA(), originalConstraint->getEntityB(), limitData, originalConstraint->getPriority() );
		limitData->removeReference();

		return limitInstance;
	}

	return HK_NULL;
}



hkResult hkpConstraintUtils::getConstraintPivots (const hkpConstraintInstance* constraint, hkVector4& pivotInAOut, hkVector4& pivotInBOut)
{
	hkpConstraintData *constraintData = constraint->getData();

	switch (constraintData->getType())
	{
		case hkpConstraintData::CONSTRAINT_TYPE_BALLANDSOCKET:
		{
			hkpBallAndSocketConstraintData* bsConstraint = static_cast<hkpBallAndSocketConstraintData*> (constraintData);
			pivotInAOut = bsConstraint->m_atoms.m_pivots.m_translationA;
			pivotInBOut = bsConstraint->m_atoms.m_pivots.m_translationB;
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_HINGE:
		{
			hkpHingeConstraintData* hConstraint = static_cast<hkpHingeConstraintData*> (constraintData);
			pivotInAOut = hConstraint->m_atoms.m_transforms.m_transformA.getTranslation();
			pivotInBOut = hConstraint->m_atoms.m_transforms.m_transformB.getTranslation();
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:
		{
			hkpLimitedHingeConstraintData* hConstraint = static_cast<hkpLimitedHingeConstraintData*> (constraintData);
			pivotInAOut = hConstraint->m_atoms.m_transforms.m_transformA.getTranslation();
			pivotInBOut = hConstraint->m_atoms.m_transforms.m_transformB.getTranslation();
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:
		{
			hkpRagdollConstraintData* rConstraint = static_cast<hkpRagdollConstraintData*> (constraintData);
			pivotInAOut = rConstraint->m_atoms.m_transforms.m_transformA.getTranslation();
			pivotInBOut = rConstraint->m_atoms.m_transforms.m_transformB.getTranslation();
		}
		break;

		default:
		{
			HK_WARN_ALWAYS (0xabbabf3b, "Unsupported type of constraint in prepareSystemForRagdoll()");
			return HK_FAILURE;
		}
	}

	return HK_SUCCESS;
}

hkResult hkpConstraintUtils::getConstraintMotors(const hkpConstraintData* constraintData, hkpConstraintMotor*& motor0, hkpConstraintMotor*& motor1, hkpConstraintMotor*& motor2 )
{
	switch (constraintData->getType())
	{
	case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:
		{
			const hkpLimitedHingeConstraintData* hConstraint = static_cast<const hkpLimitedHingeConstraintData*> (constraintData);
			motor0 = hConstraint->getMotor();
			motor1 = HK_NULL;
			motor2 = HK_NULL;
		}
		break;

	case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:
		{
			const hkpRagdollConstraintData* rConstraint = static_cast<const hkpRagdollConstraintData*> (constraintData);
			// Possibly, those motors should be extracted in a different order.
			motor0 = rConstraint->getTwistMotor();
			motor1 = rConstraint->getConeMotor();
			motor2 = rConstraint->getPlaneMotor();
		}
		break;

	default:
		{
			motor0 = motor1 = motor2 = HK_NULL;
			HK_WARN_ALWAYS (0xabbae233, "This type of constraint does not have motors");
			return HK_FAILURE;
		}
	}

	return HK_SUCCESS;
}


hkBool hkpConstraintUtils::checkAndFixConstraint (const hkpConstraintInstance* constraint, hkReal maxAllowedError, hkReal relativeFixupOnError)
{
	hkVector4 childPivotInChild;
	hkVector4 parentPivotInParent;

	hkResult res = 	getConstraintPivots(constraint, childPivotInChild, parentPivotInParent);

	// Unsupported constraint type? return false
	if (res!=HK_SUCCESS)
	{
		return false;
	}

	// The pivotInA should be 0,0,0 if the pivots are properly aligned, warn otherwise
	if (childPivotInChild.lengthSquared3()>1e-6f)
	{
		HK_WARN_ALWAYS (0xabba5dff, "Pivot of child rigid body (A) is expected to be aligned with the constraint at setup time.");
	}

	hkpRigidBody* parentRigidBody = constraint->getRigidBodyB();
	hkpRigidBody* childRigidBody = constraint->getRigidBodyA();

	const hkTransform& worldFromParent = parentRigidBody->getTransform();
	const hkTransform& worldFromChild = childRigidBody->getTransform();

	hkVector4 parentPivotInWorld; parentPivotInWorld.setTransformedPos(worldFromParent, parentPivotInParent);
	hkVector4 childPivotInWorld; childPivotInWorld.setTransformedPos(worldFromChild, childPivotInChild);

	hkVector4 error; error.setSub4(parentPivotInWorld, childPivotInWorld);

	// Are they aligned ?
	if (error.lengthSquared3()>maxAllowedError*maxAllowedError)
	{
		// NO

		// Interpolate the new position between the desired position and the position of the parent
		const hkVector4& parentPositionInWorld = parentRigidBody->getPosition();
		hkVector4 newChildPositionInWorld; newChildPositionInWorld.setInterpolate4(parentPivotInWorld, parentPositionInWorld, relativeFixupOnError);

		childRigidBody->setPosition(newChildPositionInWorld);

		// Set the velocity to match the parent
		childRigidBody->setLinearVelocity(parentRigidBody->getLinearVelocity());
		childRigidBody->setAngularVelocity(parentRigidBody->getAngularVelocity());

		return true; // fix up done
	}
	else
	{
		// YES

		return false; // no fix up done
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
