/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Internal/hkpInternal.h>
#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Physics/ConstraintSolver/Solve/hkpSolver.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobianElement.h>


#if defined(USE_SOLVER_PS2_ASSEMBLY)
#	include <Physics/ConstraintSolver/Solve/Ps2/hkpPs2SolverInternal.h>
#elif defined ( USE_SOLVER_PSP_ASSEMBLY )
#	include <Physics/ConstraintSolver/Solve/Psp/hkpPspGccSolverInternal.h>
#elif defined ( USE_SOLVER_XBOX360_ASSEMBLY )
#	include <Physics/ConstraintSolver/Solve/Xbox360/hkpXbox360SolverInternal.h>
#else
#	include <Physics/ConstraintSolver/Solve/Fpu/hkpFpuSolverInternal.h>
#endif



#include <Physics/ConstraintSolver/Jacobian/hkpJacobianHeaderSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobianPairContactSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobian3dFrictionSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dFrictionSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dBilateralSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dAngularSchema.h>

#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dAngularFrictionSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dAngularLimitsSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dLinearLimitsSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dLinearMotorSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dAngularMotorSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobianCallbackSchema.h>

#include <Physics/ConstraintSolver/Jacobian/hkpJacobian1dPulleySchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobianStiffSpringChainSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobianBallSocketChainSchema.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobianPoweredChainSchema.h>

#include <Physics/ConstraintSolver/Constraint/Bilateral/hkp1dBilateralConstraintInfo.h>
#include <Physics/ConstraintSolver/Constraint/Chain/hkpPoweredChainSolverUtil.h>

//
// test the solver
//
int solver_main(  )
{
	hkpSolverInfo solverInfo;
	solverInfo.m_contactRestingVelocity = 0.0f;
	solverInfo.setTauAndDamping(0.8f, 0.1f);

	hkpVelocityAccumulator mA;
	mA.m_deactivationClass = hkpSolverInfo::DEACTIVATION_CLASS_OFF;
	mA.m_matrixIsIdentity = false;
	mA.m_linearVel.set(0.1f, 0.2f, 0.3f, 0.0f);
	mA.m_angularVel.set( 0.05f, 0.05f, 0.05f, 0.0f );
	mA.m_invMasses.set(1,2,3,5);
	mA.m_scratch0.set(1,1,1,1);
	mA.m_scratch1.set(2,2,2,2);
	mA.m_scratch2.set(3,3,3,3);
	mA.m_scratch3.set(4,4,4,4);

	hkpVelocityAccumulator mB;
	mB.m_deactivationClass = hkpSolverInfo::DEACTIVATION_CLASS_OFF;
	mB.m_matrixIsIdentity = false;
	mB.m_linearVel.set(0.5f, 0.6f, -0.7f, 0.0f);
	mB.m_angularVel.set( 0.05f, -0.25f, 0.05f, 0.0f );
	mB.m_invMasses.set(1,2,3,5);
	mB.m_scratch0.set(1,1,1,1);
	mB.m_scratch1.set(2,1,3,2);
	mB.m_scratch2.set(3,1,4,3);
	mB.m_scratch3.set(4,1,4,1);

	hkp1Lin2AngJacobian jacs[2];
	jacs[0].m_linear0.set(0.1f, 0.1f, 0.1f, 1.0f);
	jacs[0].m_angular[0].set(0.2f, -0.2f, 0.1f, 2.0f);
	jacs[0].m_angular[1].set(0.3f, 0.3f, 0.3f, 3.0f);

	jacs[1].m_linear0.set(0.1f, 0.1f, 0.3f, 2.0f);
	jacs[1].m_angular[0].set(0.1f, -0.2f, 0.3f, 2.0f);
	jacs[1].m_angular[1].set(0.4f, 0.4f, 0.4f, 3.0f);

	hkSolver::loadFixedRegisters();

	// getLinearDv0
	{
		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSimdReal result = hkSolver::getLinearDv0( jacs[0], mA, mB, solverInfo );
		HK_TEST( hkMath::equal( result, 1.02f) );
	}

	// getLinearDv0UserTau
	{
		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSimdReal result = hkSolver::getLinearDv0UserTau( jacs[0], mA, mB, solverInfo, 0.5f, 0.3f );
		HK_TEST( hkMath::equal( result, 0.981f) );
	}


	// getVelocity
	{
		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSimdReal result = hkSolver::getVelocity( jacs[0], mA, mB );
		HK_TEST( hkMath::equal( result, -0.02f) );
	}


	hkp2AngJacobian angJac;
	angJac.m_angular[0].set(0.3f, 0.4f, 0.6f, 2.0f);
	angJac.m_angular[1].set(-0.7f, 0.4f, 1.3f, 1.2f);

	// getAngularDv0
	{
		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSimdReal result = hkSolver::getAngularDv0( angJac, mA, mB, solverInfo );
		HK_TEST( hkMath::equal( result, 1.205f) );
	}

	// getAngularDv0UserTau
	{
		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSimdReal result = hkSolver::getAngularDv0UserTau( angJac, mA, mB, solverInfo, 0.6f, 0.3f );
		HK_TEST( hkMath::equal( result, 1.959f) );
	}

	// getDv01
#ifndef USE_SOLVER_PS2_ASSEMBLY
	{
		hkSolver::loadVelocityAccumulators( mA, mB );

		hkVector4 velOut;
		hkSolver::getDv01( jacs, mA, mB, solverInfo, velOut );

		HK_TEST( hkMath::equal( velOut(0), 1.02f) );
		HK_TEST( hkMath::equal( velOut(1), 1.83f) );
	}
#endif

	hkp2Lin2AngJacobian lin2ang2jac;
	lin2ang2jac.m_angular[0].set(0.3f, 0.4f, 0.6f, 2.0f);
	lin2ang2jac.m_angular[1].set(-0.7f, 0.4f, 1.3f, 1.2f);
	lin2ang2jac.m_linear[0].set(-0.5f, 0.1f, 0.1f, 1.0f);
	lin2ang2jac.m_linear[1].set(0.1f, 0.3f, 0.1f, 1.3f);

	// getDv2Lin2Ang
	{
		hkSimdReal result = hkSolver::getDv2Lin2Ang( lin2ang2jac, mA, mB, solverInfo );
		HK_TEST( hkMath::equal( result, 1.165f) );
	}

	hkpJacTriple2Bil1Ang jacTrip;
	jacTrip.m_jac0 = jacs[0];
	jacTrip.m_jac1 = jacs[1];
	jacTrip.m_jac2 = angJac;

	// getDv012
#ifndef USE_SOLVER_PS2_ASSEMBLY
	{
		hkSolver::loadVelocityAccumulators( mA, mB );

		hkVector4 velOut;
		hkSolver::getDv012( &jacTrip, mA, mB, solverInfo, velOut );
		HK_TEST( hkMath::equal( velOut(0), 1.02f) );
		HK_TEST( hkMath::equal( velOut(1), 1.83f) );
		HK_TEST( hkMath::equal( velOut(2), 1.205f) );
	}
#endif

	hkSimdReal imp = 0.25f;
	hkpSolverElemTemp sr;
	hkpSolverElemTemp srs[2];

	// applyImpulse
	{
		sr.m_impulseApplied = 0.0f;
		mA.m_linearVel.set(0.1f, 0.2f, 0.3f, 0.0f);
		mA.m_angularVel.set( 0.05f, 0.05f, 0.05f, 0.0f );
		mB.m_linearVel.set(0.5f, 0.6f, -0.7f, 0.0f);
		mB.m_angularVel.set( 0.05f, -0.25f, 0.05f, 0.0f );

		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSolver::applyImpulse( imp, jacs[0], mA, mB, sr);
		hkSolver::storeVelocityAccumulators( mA, mB );

		HK_TEST( hkMath::equal( sr.m_impulseApplied, 0.25f) );

		hkVector4 result;
		result.set(0.225f, 0.325f, 0.425f);
		HK_TEST( result.equals3( mA.m_linearVel ) );
		result.set(0.1f, -0.05f, 0.125f);
		HK_TEST( result.equals3( mA.m_angularVel ) );
		result.set(0.375f, 0.475f, -0.825f);
		HK_TEST( result.equals3( mB.m_linearVel ) );
		result.set(0.125f, -0.1f, 0.275f);
		HK_TEST( result.equals3( mB.m_angularVel ) );
	}

	// applyImpulse2Lin2Ang
	{
		sr.m_impulseApplied = 0.0f;
		mA.m_linearVel.set(0.1f, 0.2f, 0.3f, 0.0f);
		mA.m_angularVel.set( 0.05f, 0.05f, 0.05f, 0.0f );
		mB.m_linearVel.set(0.5f, 0.6f, -0.7f, 0.0f);
		mB.m_angularVel.set( 0.05f, -0.25f, 0.05f, 0.0f );

		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSolver::applyImpulse2Lin2Ang( imp, lin2ang2jac, mA, mB, sr);
		hkSolver::storeVelocityAccumulators( mA, mB );

		HK_TEST( hkMath::equal( sr.m_impulseApplied, 0.25f) );

		hkVector4 result;
		result.set(-0.525f, 0.325f, 0.425f);
		HK_TEST( result.equals3( mA.m_linearVel ) );
		result.set(0.125f, 0.25f, 0.5f);
		HK_TEST( result.equals3( mA.m_angularVel ) );
		result.set(0.375f, 0.225f, -0.825f);
		HK_TEST( result.equals3( mB.m_linearVel ) );
		result.set(-0.125f, -0.05f, 1.025f);
		HK_TEST( result.equals3( mB.m_angularVel ) );
	}

	// applyImpulse2Lin2Ang
	{
		sr.m_impulseApplied = 0.0f;
		mA.m_linearVel.set(0.1f, 0.2f, 0.3f, 0.0f);
		mA.m_angularVel.set( 0.05f, 0.05f, 0.05f, 0.0f );
		mB.m_linearVel.set(0.5f, 0.6f, -0.7f, 0.0f);
		mB.m_angularVel.set( 0.05f, -0.25f, 0.05f, 0.0f );

		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSolver::applyAngularImpulse( imp, angJac, mA, mB, sr);
		hkSolver::storeVelocityAccumulators( mA, mB );

		HK_TEST( hkMath::equal( sr.m_impulseApplied, 0.25f) );

		hkVector4 result;
		result.set(0.1f, 0.2f, 0.3f);
		HK_TEST( result.equals3( mA.m_linearVel ) );
		result.set(0.125f, 0.25f, 0.5f);
		HK_TEST( result.equals3( mA.m_angularVel ) );
		result.set(0.5f, 0.6f, -0.7f);
		HK_TEST( result.equals3( mB.m_linearVel ) );
		result.set(-0.125f, -0.05f, 1.025f);
		HK_TEST( result.equals3( mB.m_angularVel ) );
	}

	// applyImpulse0
	{
		sr.m_impulseApplied = 0.0f;
		mA.m_linearVel.set(0.1f, 0.2f, 0.3f, 0.0f);
		mA.m_angularVel.set( 0.05f, 0.05f, 0.05f, 0.0f );
		mB.m_linearVel.set(0.5f, 0.6f, -0.7f, 0.0f);
		mB.m_angularVel.set( 0.05f, -0.25f, 0.05f, 0.0f );

		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSolver::getLinearDv0( jacs[0], mA, mB, solverInfo );
		hkSolver::applyImpulse0( imp, jacs[0], mA, mB, sr);
		hkSolver::storeVelocityAccumulators( mA, mB );

		HK_TEST( hkMath::equal( sr.m_impulseApplied, 0.25f) );

		hkVector4 result;
		result.set(0.225f, 0.325f, 0.425f);
		HK_TEST( result.equals3( mA.m_linearVel ) );
		result.set(0.1f, -0.05f, 0.125f);
		HK_TEST( result.equals3( mA.m_angularVel ) );
		result.set(0.375f, 0.475f, -0.825f);
		HK_TEST( result.equals3( mB.m_linearVel ) );
		result.set(0.125f, -0.1f, 0.275f);
		HK_TEST( result.equals3( mB.m_angularVel ) );

	}

	// applyImpulse1
#ifndef USE_SOLVER_PS2_ASSEMBLY
	{
		sr.m_impulseApplied = 0.0f;
		mA.m_linearVel.set(0.1f, 0.2f, 0.3f, 0.0f);
		mA.m_angularVel.set( 0.05f, 0.05f, 0.05f, 0.0f );
		mB.m_linearVel.set(0.5f, 0.6f, -0.7f, 0.0f);
		mB.m_angularVel.set( 0.05f, -0.25f, 0.05f, 0.0f );

		hkSolver::loadVelocityAccumulators( mA, mB );
		hkVector4 velOut;
		hkSolver::getDv01( jacs, mA, mB, solverInfo, velOut );
		hkSolver::applyImpulse1( imp, jacs[1], mA, mB, sr);
		hkSolver::storeVelocityAccumulators( mA, mB );

		HK_TEST( hkMath::equal( sr.m_impulseApplied, 0.25f) );

		hkVector4 result;
		result.set(0.225f, 0.325f, 0.675f);
		HK_TEST( result.equals3( mA.m_linearVel ) );
		result.set(0.075f, -0.05f, 0.275f);
		HK_TEST( result.equals3( mA.m_angularVel ) );
		result.set(0.375f, 0.475f, -1.075f);
		HK_TEST( result.equals3( mB.m_linearVel ) );
		result.set(0.15f, -0.05f, 0.35f);
		HK_TEST( result.equals3( mB.m_angularVel ) );
	}
#endif

	// applyImpulse01
#ifndef USE_SOLVER_PS2_ASSEMBLY
	{
		srs[0].m_impulseApplied = 0.0f;
		srs[1].m_impulseApplied = 0.0f;
		mA.m_linearVel.set(0.1f, 0.2f, 0.3f, 0.0f);
		mA.m_angularVel.set( 0.05f, 0.05f, 0.05f, 0.0f );
		mB.m_linearVel.set(0.5f, 0.6f, -0.7f, 0.0f);
		mB.m_angularVel.set( 0.05f, -0.25f, 0.05f, 0.0f );

		hkSolver::loadVelocityAccumulators( mA, mB );
		hkVector4 velOut;
		hkSolver::getDv01( jacs, mA, mB, solverInfo, velOut );
		hkSolver::applyImpulse01( imp, imp, jacs, mA, mB, srs);
		hkSolver::storeVelocityAccumulators( mA, mB );

		HK_TEST( hkMath::equal( srs[0].m_impulseApplied, 0.25f) );
		HK_TEST( hkMath::equal( srs[1].m_impulseApplied, 0.25f) );

		hkVector4 result;
		result.set(0.35f, 0.45f, 0.8f);
		HK_TEST( result.equals3( mA.m_linearVel ) );
		result.set(0.125f, -0.15f, 0.35f);
		HK_TEST( result.equals3( mA.m_angularVel ) );
		result.set(0.25f, 0.35f, -1.2f);
		HK_TEST( result.equals3( mB.m_linearVel ) );
		result.set(0.225f, 0.1f, 0.575f);
		HK_TEST( result.equals3( mB.m_angularVel ) );
	}
#endif
	//void HK_CALL hkSolver::applyImpulse01( hkSimdRealParameter imp0, hkSimdRealParameter imp1,	const hkp1Lin2AngJacobian* jacs,	hkpVelocityAccumulator& mA, hkpVelocityAccumulator& mB,	hkpSolverElemTemp* srs)


	// applyAngularImpulse0
	{
		sr.m_impulseApplied = 0.0f;
		mA.m_linearVel.set(0.1f, 0.2f, 0.3f, 0.0f);
		mA.m_angularVel.set( 0.05f, 0.05f, 0.05f, 0.0f );
		mB.m_linearVel.set(0.5f, 0.6f, -0.7f, 0.0f);
		mB.m_angularVel.set( 0.05f, -0.25f, 0.05f, 0.0f );

		hkSolver::loadVelocityAccumulators( mA, mB );
		hkSolver::applyAngularImpulse0( imp, angJac, mA, mB, sr);
		hkSolver::storeVelocityAccumulators( mA, mB );


		HK_TEST( hkMath::equal( sr.m_impulseApplied, 0.25f) );

// This section of code causes an internal compiler error in debug mode for PS3_GCC_411
#if (!defined HK_PLATFORM_PS3) || (HK_COMPILER_GCC_VERSION < 40100) || (!defined HK_DEBUG)
		hkVector4 result;
		result.set(0.1f, 0.2f, 0.3f);
		HK_TEST( result.equals3( mA.m_linearVel ) );
		result.set(0.125f, 0.25f, 0.5f);
		HK_TEST( result.equals3( mA.m_angularVel ) );
		result.set(0.5f, 0.6f, -0.7f);
		HK_TEST( result.equals3( mB.m_linearVel ) );
		result.set(-0.125f, -0.05f, 1.025f);
		HK_TEST( result.equals3( mB.m_angularVel ) );
#endif

	}

	/*
	// integrateRhs
	{
		hkReal oldRhsFactor = 0.3f;
		hkReal sumVelocitiesFactor = 0.7f;
		hkReal result;
		result = hkSolver::integrateRhs ( mA, mB, &jacs[0], oldRhsFactor, sumVelocitiesFactor);
		HK_TEST( hkMath::equal( result, -1.09999f) );
	}

	// integrateAngularRhs
	{
		hkReal oldRhsFactor = 0.3f;
		hkReal sumVelocitiesFactor = 0.7f;

		hkReal result;
		result = hkSolver::integrateAngularRhs ( mA, mB, &angJac, oldRhsFactor, sumVelocitiesFactor);
		HK_TEST( hkMath::equal( result, -3.49f) );
	}
	*/

	return 0;
}


//
// test registration
//
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(solver_main, "Fast", "Physics/Test/UnitTest/Internal/", __FILE__     );


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
