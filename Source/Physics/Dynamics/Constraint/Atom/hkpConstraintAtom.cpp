/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>

#include <Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h>
#include <Physics/ConstraintSolver/SimpleConstraints/hkpSimpleConstraintUtil.h>

void HK_CALL hkBridgeConstraintAtom_callData( class hkpConstraintData* m_constraintData, const hkpConstraintQueryIn &in, hkpConstraintQueryOut &out )
{
	m_constraintData->buildJacobian( in, out );
}

void hkpBridgeConstraintAtom::init( class hkpConstraintData* constraintData )
{
	this->m_constraintData = constraintData;
	this->m_buildJacobianFunc = hkBridgeConstraintAtom_callData;
}

hkpSimpleContactConstraintAtom::hkpSimpleContactConstraintAtom(hkFinishLoadedObjectFlag f) :
		hkpConstraintAtom(f),	  m_info(f)
{
	m_contactPointPropertiesStriding = 	sizeof(hkpContactPointProperties) + (m_numUserDatasForBodyA+ m_numUserDatasForBodyB) * sizeof(hkpContactPointProperties::UserData);
}

void hkpMassChangerModifierConstraintAtom::collisionResponseBeginCallback( const hkContactPoint& cp, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB)
{
	hkReal massScaleFactorA = m_factorA;
	hkReal massScaleFactorB = m_factorB;

	inA.m_invMass *= massScaleFactorA;
	inA.m_invInertia.mul( massScaleFactorA );

	inB.m_invMass *= massScaleFactorB;
	inB.m_invInertia.mul( massScaleFactorB );
}

void hkpMassChangerModifierConstraintAtom::collisionResponseEndCallback( const hkContactPoint& cp, float impulseApplied, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB)
{
}

static hkpBodyVelocity s_bodyVelocities[2];
static hkBool s_bodyVelocitiesInitialized = false;

void hkpSoftContactModifierConstraintAtom::collisionResponseBeginCallback( const hkContactPoint& cp, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB)
{
	HK_WARN_ONCE(0x12015a6e, "Using soft contacts (scaling of response force) in TOI events. This may cause a significant performance drop. This pair of bodies should not use continuous collision detection. Reduce the quality type of either of the bodies.");
	HK_ASSERT2(0x172400f2, s_bodyVelocitiesInitialized == false, "hkSoftContactConstraintData uses static variables for processing of TOI collision. It assumed that TOI are always processed in series one after another. If that's changed this class has to be rewritten. ");
	s_bodyVelocities[0] = velA;
	s_bodyVelocities[1] = velB;
}

void hkpSoftContactModifierConstraintAtom::collisionResponseEndCallback( const hkContactPoint& cp, float impulseApplied, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB)
{
	hkReal usedImpulseFraction = this->m_tau;

	hkpBodyVelocity& oldA = s_bodyVelocities[0];
	hkpBodyVelocity& oldB = s_bodyVelocities[1];

	velA.m_linear.setInterpolate4(oldA.m_linear, velA.m_linear, usedImpulseFraction);
	velA.m_angular.setInterpolate4(oldA.m_angular, velA.m_angular, usedImpulseFraction);
	velB.m_linear.setInterpolate4(oldB.m_linear, velB.m_linear, usedImpulseFraction);
	velB.m_angular.setInterpolate4(oldB.m_angular, velB.m_angular, usedImpulseFraction);
}

void hkpMovingSurfaceModifierConstraintAtom::collisionResponseBeginCallback( const hkContactPoint& cp, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB)
{
	hkVector4 vel = getVelocity();
	// project velocity into the contact plane (so that objects do not sink in)
	hkSimdReal dot = vel.dot3(cp.getNormal());
	hkVector4 perp; perp.setMul4( dot, vel );
	vel.sub4( perp );
	velB.m_linear.add4( vel );
}

void hkpMovingSurfaceModifierConstraintAtom::collisionResponseEndCallback( const hkContactPoint& cp, float impulseApplied, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB)
{
	hkVector4 vel = getVelocity();

	// project velocity into the contact plane (so that objects do not sink in)
	hkSimdReal dot = vel.dot3(cp.getNormal());
	hkVector4 perp; perp.setMul4( dot, vel );
	vel.sub4( perp );
	velB.m_linear.sub4( vel );
}


int hkpModifierConstraintAtom::addModifierDataToConstraintInfo( hkpConstraintInfo& cinfo ) const
{
	int callBackRequest = CALLBACK_REQUEST_NONE;
	const hkpModifierConstraintAtom* modifier = this;

	switch( modifier->getType() )
	{

	case hkpConstraintAtom::TYPE_MODIFIER_VISCOUS_SURFACE:
		{
			const hkpViscousSurfaceModifierConstraintAtom* m = static_cast<const hkpViscousSurfaceModifierConstraintAtom*>( modifier );
			callBackRequest |= m->getConstraintInfo ( cinfo );
			break;
		}
	case hkpConstraintAtom::TYPE_MODIFIER_SOFT_CONTACT:
		{
			const hkpSoftContactModifierConstraintAtom* m = static_cast<const hkpSoftContactModifierConstraintAtom*>( modifier );
			callBackRequest |= m->getConstraintInfo ( cinfo );
			break;
		}

	case hkpConstraintAtom::TYPE_MODIFIER_MASS_CHANGER:
		{
			const hkpMassChangerModifierConstraintAtom* m = static_cast<const hkpMassChangerModifierConstraintAtom*>( modifier );
			callBackRequest |= m->getConstraintInfo ( cinfo );
			break;
		}

	case hkpConstraintAtom::TYPE_MODIFIER_MOVING_SURFACE:
		{
			const hkpMovingSurfaceModifierConstraintAtom* m = static_cast<const hkpMovingSurfaceModifierConstraintAtom*>( modifier );
			callBackRequest |= m->getConstraintInfo ( cinfo );
			break;
		}

	default:
		{
			HK_ASSERT2(0xaf673682, 0, "Unknown constraint modifier type.");
			break;
		}
	}
	return callBackRequest;
}

int HK_CALL hkpModifierConstraintAtom::addAllModifierDataToConstraintInfo( hkpModifierConstraintAtom* modifier, hkpConstraintInfo& cinfo )
{
	int callBackRequest = CALLBACK_REQUEST_NONE;
	
	hkpConstraintAtom* atom = modifier;

	while ( 1 )
	{
		// abort if we reached the constraint's original atom
		if ( !atom->isModifierType() )
		{
			break;
		}
		hkpModifierConstraintAtom* mac = reinterpret_cast<hkpModifierConstraintAtom*>(atom);

		callBackRequest |= mac->addModifierDataToConstraintInfo( cinfo );

		atom = mac->m_child;
	}
	return callBackRequest;
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
