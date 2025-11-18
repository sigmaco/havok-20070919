/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Constraint/Util/hkpConstraintDataCloningUtil.h>
#include <Physics/Dynamics/Constraint/hkpConstraintData.h>
#include <Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h>

#include <Physics/Dynamics/Constraint/Bilateral/LimitedHinge/hkpLimitedHingeConstraintData.h>
#include <Physics/Dynamics/Constraint/Bilateral/Prismatic/hkpPrismaticConstraintData.h>
#include <Physics/Dynamics/Constraint/Bilateral/Ragdoll/hkpRagdollConstraintData.h>
#include <Physics/Dynamics/Constraint/Motor/hkpConstraintMotor.h>


hkpConstraintData* hkpConstraintDataCloningUtil::cloneIfCanHaveMotors(const hkpConstraintData* data)
{
	hkpConstraintData::ConstraintType type = (hkpConstraintData::ConstraintType)data->getType();

	switch(type)
	{
		case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:		
		{
			const hkpLimitedHingeConstraintData* oldData = static_cast<const hkpLimitedHingeConstraintData*>(data);

			// Create new instance
			hkpLimitedHingeConstraintData* newData = new hkpLimitedHingeConstraintData();

			// Copy all data
			newData->m_atoms = oldData->m_atoms;
			newData->m_userData = oldData->m_userData;

			// Clone motors
			HK_CPU_PTR(class hkpConstraintMotor*)& motor = newData->m_atoms.m_angMotor.m_motor;
			if (motor)
			{
				motor = motor->clone();
			}

			// All done
			return newData;
		}

		case hkpConstraintData::CONSTRAINT_TYPE_PRISMATIC:			
		{
			const hkpPrismaticConstraintData* oldData = static_cast<const hkpPrismaticConstraintData*>(data);

			// Create new instance
			hkpPrismaticConstraintData* newData = new hkpPrismaticConstraintData();

			// Copy all data
			newData->m_atoms = oldData->m_atoms;
			newData->m_userData = oldData->m_userData;

			// Clone motors
			HK_CPU_PTR(class hkpConstraintMotor*)& motor = newData->m_atoms.m_motor.m_motor;
			if (motor)
			{
				motor = motor->clone();
			}

			// All done
			return newData;
		}

		case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:				
		{
			const hkpRagdollConstraintData* oldData = static_cast<const hkpRagdollConstraintData*>(data);

			// Create new instance
			hkpRagdollConstraintData* newData = new hkpRagdollConstraintData();

			// Copy all data
			newData->m_atoms = oldData->m_atoms;
			newData->m_userData = oldData->m_userData;

			// Clone motors
			HK_CPU_PTR(class hkpConstraintMotor*)* motors = newData->m_atoms.m_ragdollMotors.m_motors;
			for (int i = 0; i < 3; i++)
			{
				if (motors[i])
				{
					motors[i] = motors[i]->clone();
				}
			}

			// All done
			return newData;
		}

		default:
		{
			// Constraint doesn't have motors
			return HK_NULL;
		}

	}
	
}


//
//hkpConstraintData* hkpConstraintDataCloningUtil::deepClone(const hkpConstraintData* data) const
//{
//	hkpConstraintData* newConstraint = HK_NULL;
//	hkpConstraintAtom* oldAtoms = HK_NULL;
//	hkpConstraintAtom* newAtoms = HK_NULL;
//	int atomsSize;
//
//	hkpConstraintData::ConstraintType type = data->getType();
//	switch(type)
//	{
//		case hkpConstraintData::CONSTRAINT_TYPE_BALLANDSOCKET:
//		{
//
//			newConstraint = new hkpBallAndSocketConstraintData(); 
//			break;
//		}
//
//		case hkpConstraintData::CONSTRAINT_TYPE_HINGE:				
//		{
//			newConstraint = new hkpHingeConstraintData(); 
//			break;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:		
//		{
//			newConstraint = new hkpLimitedHingeConstraintData(); break;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_POINTTOPATH:			
//		{
//			newConstraint = new hkpPointToPathConstraintData(); break;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_PRISMATIC:			
//		{
//			newConstraint = new hkpPrismaticConstraintData(); break;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:				
//		{
//			newConstraint = new hkpRagdollConstraintData(); break;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_STIFFSPRING:			
//		{
//			newConstraint = new hkpStiffSpringConstraintData(); break;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_WHEEL:				
//		{
//			newConstraint = new hkpWheelConstraintData(); break;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_POINTTOPLANE:		
//		{
//			newConstraint = new hkpPointToPlaneConstraintData(); break;
//		}
//
//		case hkpConstraintData::CONSTRAINT_TYPE_PULLEY:				
//		{
//			newConstraint = new hkpPulleyConstraintData(); break;
//		}
//
//		case hkpConstraintData::CONSTRAINT_TYPE_HINGE_LIMITS:		
//		{
//			newConstraint = new hkpHingeLimitsData(); break;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL_LIMITS:		
//		{
//			newConstraint = new hkpRagdollLimitsData(); break;
//		}
//
//			// Breakable & malleable
//		case hkpConstraintData::CONSTRAINT_TYPE_BREAKABLE:			
//		{
//			hkpBreakableConstraintData* oldBreakable = static_cast<hkpBreakableConstraintData*>(this);
//			hkpConstraintData* newChild = oldBreakable->getWrappedConstraintData()->deepClone();
//			HK_ASSERT2(0XAD76BA32, newChild, "Wrapped constraintData of a hkpBreakableConstraintData is not clonable.");
//			if (!newChild)
//			{
//				return HK_NULL;
//			}
//
//			hkpBreakableConstraintData* newBreakable = new hkpBreakableConstraintData(newChild); 
//			newConstraint = newBreakable;
//			newChild->removeReference();
//
//			newBreakable->m_solverResultLimit = oldBreakable->m_solverResultLimit;
//			newBreakable->m_removeWhenBroken = oldBreakable->m_removeWhenBroken;
//			newBreakable->m_revertBackVelocityOnBreak = oldBreakable->m_revertBackVelocityOnBreak;
//			newBreakable->m_solverResultLimit = HK_NULL;
//			newBreakable->m_userData = oldBreakable->m_userData;
//
//			return newBreakable;
//		}
//		case hkpConstraintData::CONSTRAINT_TYPE_MALLEABLE:			
//		{
//			hkpMalleableConstraintData* oldMalleable = static_cast<hkpMalleableConstraintData*>(this);
//			hkpConstraintData* newChild = oldMalleable->getWrappedConstraintData()->deepClone();
//			HK_ASSERT2(0XAD76BA32, newChild, "Wrapped constraintData of a hkpMalleableConstraintData is not clonable.");
//			if (!newChild)
//			{
//				return HK_NULL;
//			}
//
//			hkpMalleableConstraintData* newMalleable = new hkpMalleableConstraintData(newChild); 
//			newConstraint = newMalleable;
//			newChild->removeReference();
//
//			newMalleable->m_strength = oldMalleable->m_strength;
//			newMalleable->m_userData = oldMalleable->m_userData;
//
//			return newMalleable;
//		}
//
//			// Generic & contact constrainsts
//		case hkpConstraintData::CONSTRAINT_TYPE_GENERIC:			HK_ASSERT2(0xad7644dd, false, "Cloning of hkpGenericConstraintData is not supported."); return HK_NULL;
//		case hkpConstraintData::CONSTRAINT_TYPE_CONTACT:			HK_ASSERT2(0xad7644de, false, "Cloning of hkpSimpleContactConstraintData is not supported."); return HK_NULL;
//
//			// Chain constraints
//		case hkpConstraintData::CONSTRAINT_TYPE_STIFF_SPRING_CHAIN: 
//		case hkpConstraintData::CONSTRAINT_TYPE_BALL_SOCKET_CHAIN: 
//		case hkpConstraintData::CONSTRAINT_TYPE_POWERED_CHAIN:
//		{
//			HK_ASSERT2(0xad8754dd, false, "Cloning of chain costraints not supported.");
//			return HK_NULL;
//		}
//	};
//
//	// Now handle atoms for constraints using hkConstraintAtoms
//	{
//		newConstraint->geta
//	}
//
//	return HK_NULL;
//}

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
