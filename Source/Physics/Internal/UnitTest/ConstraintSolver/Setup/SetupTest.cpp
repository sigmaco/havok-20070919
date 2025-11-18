/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Internal/hkpInternal.h>
// This test calls solver routines directly

#include <Common/Base/UnitTest/hkUnitTest.h>


#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Physics/ConstraintSolver/Solve/hkpSolver.h>
#include <Physics/ConstraintSolver/Jacobian/hkpJacobianBuilder.h> 

#include <Physics/ConstraintSolver/Accumulator/hkpVelocityAccumulator.h>

#include <Physics/ConstraintSolver/Jacobian/hkpJacobianElement.h>
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

/*
	HK_FORCE_INLINE void HK_CALL initBuilder( const hkpVelocityAccumulator* opaA, const hkpVelocityAccumulator* opaB, const hkReal rhsFactor )
	HK_FORCE_INLINE void HK_CALL exitBuilder()
	HK_FORCE_INLINE void HK_CALL flush()
	HK_FORCE_INLINE void HK_CALL buildLinearBegin( const hkpVelocityAccumulator* opaA, const hkpVelocityAccumulator* opaB, const hkVector4& position, const hkVector4& direction, hkReal invJacFactor, hkp1Lin2AngJacobian& jac )
	HK_FORCE_INLINE void HK_CALL buildLinearEnd( hkp1Lin2AngJacobian& jac )	{	}
	HK_FORCE_INLINE void HK_CALL buildLinearEnd( hkp1Lin2AngJacobian& jac, hkReal rhs, hkReal rhsFactor )
	HK_FORCE_INLINE void HK_CALL buildLinearAndRhs( const hkpVelocityAccumulator* opaA, const hkpVelocityAccumulator* opaB, const hkVector4& positionA,const hkVector4& positionB, const hkVector4& direction, hkReal rhsFactor, hkReal virtMassFactor, hkp1Lin2AngJacobian& jac )
	HK_FORCE_INLINE void HK_CALL buildAngularBegin( const hkpVelocityAccumulator* opaA, const hkpVelocityAccumulator* opaB, const hkVector4& direction, float virtMassFactor, hkp2AngJacobian& jac )
	HK_FORCE_INLINE void HK_CALL buildAngularEnd( hkp2AngJacobian& jac )
	HK_FORCE_INLINE void mulInvJacDiag( hkp2AngJacobian* jac, hkReal f )
	HK_FORCE_INLINE void HK_CALL buildAngularEnd( hkp2AngJacobian& jac, hkReal rhs, hkReal rhsFactor )
	HK_FORCE_INLINE void copyJacRegToJac1Reg()
	HK_FORCE_INLINE float HK_CALL getInvJac01Optimized( const hkpVelocityAccumulator* opaA, const hkpVelocityAccumulator* opaB, hkp1Lin2AngJacobian* jac, hkReal virtMassFactor, hkReal nonDiagFactor )
	HK_FORCE_INLINE float HK_CALL getNonDiagSameObjects( const hkpVelocityAccumulator* opaA, const hkpVelocityAccumulator* opaB, hkp1Lin2AngJacobian& last, hkp1Lin2AngJacobian& other )
	HK_FORCE_INLINE float HK_CALL getNonDiagDifferentObjects( const hkpVelocityAccumulator* opaA, hkp1Lin2AngJacobian& last, hkp1Lin2AngJacobian& other )
	HK_FORCE_INLINE void HK_CALL addLastPosition( const hkVector4& pos, const hkVector4& dir, hkVector4& sumPos, hkVector4& sumDir)
*/

//
// test the setup
//
int setup_main(  )
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

	hkp1Lin2AngJacobian lin1ang2jacs[2];
	lin1ang2jacs[0].m_linear0.set(0.1f, 0.1f, 0.1f, 1.0f);
	lin1ang2jacs[0].m_angular[0].set(0.2f, -0.2f, 0.1f, 2.0f);
	lin1ang2jacs[0].m_angular[1].set(0.3f, 0.3f, 0.3f, 3.0f);
	lin1ang2jacs[1].m_linear0.set(0.1f, 0.1f, 0.3f, 2.0f);
	lin1ang2jacs[1].m_angular[0].set(0.1f, -0.2f, 0.3f, 2.0f);
	lin1ang2jacs[1].m_angular[1].set(0.4f, 0.4f, 0.4f, 3.0f);

 	hkp2AngJacobian ang2Jac;
	ang2Jac.m_angular[0].set(0.3f, 0.4f, 0.6f, 2.0f);
	ang2Jac.m_angular[1].set(-0.7f, 0.4f, 1.3f, 1.2f);

	hkp2Lin2AngJacobian lin2ang2jac;
	lin2ang2jac.m_angular[0].set(0.3f, 0.4f, 0.6f, 2.0f);
	lin2ang2jac.m_angular[1].set(-0.7f, 0.4f, 1.3f, 1.2f);
	lin2ang2jac.m_linear[0].set(-0.5f, 0.1f, 0.1f, 1.0f);
	lin2ang2jac.m_linear[1].set(0.1f, 0.3f, 0.1f, 1.3f);

	hkpJacTriple2Bil1Ang jacTrip;
	jacTrip.m_jac0 = lin1ang2jacs[0];
	jacTrip.m_jac1 = lin1ang2jacs[1];
	jacTrip.m_jac2 = ang2Jac;

	const hkReal rhsFactor = 0.25f;
	hkReal invJacFactor = 0.8f;
	hkReal virtMassFactor = 0.3f;

	hkVector4 pos; pos.set(0.1f, 0.2f, 0.3f);
	hkVector4 posB; posB.set(0.5f, 0.7f, 1.3f);
	hkVector4 dir; dir.set(-0.1f, 0.2f, -0.3f); dir.normalize3();

	// buildLinearBegin
	{
		hkp1Lin2AngJacobian& jac = lin1ang2jacs[0];

		hkJacobianBuilder::initBuilder( &mA, &mB, rhsFactor );
		hkJacobianBuilder::buildLinearBegin( &mA, &mB, pos, dir, invJacFactor, jac );
		hkJacobianBuilder::buildLinearEnd( jac );
		hkJacobianBuilder::flush();
		hkJacobianBuilder::exitBuilder();

		hkVector4 result; 
		result.set(-0.267261f, 0.534522f, -0.801784f);
		HK_TEST( result.equals3( jac.m_linear0 ) );
		result.set(-2.3519f, -2.3519f, -2.3519f, 0.0134881f);
		HK_TEST( result.equals4( jac.m_angular[0] ) );
		result.set(2.3519f, 0.213809f, 1.87083f, 59.3114f );
		HK_TEST( result.equals4( jac.m_angular[1] ) );
	}

	// buildLinearAndRhs
	{
		hkReal rhs = 0.123f;

		hkp1Lin2AngJacobian& jac = lin1ang2jacs[0];

		hkJacobianBuilder::initBuilder( &mA, &mB, rhsFactor );
		hkJacobianBuilder::buildLinearAndRhs( &mA, &mB, pos, posB, dir, rhsFactor, virtMassFactor, jac );
		hkJacobianBuilder::buildLinearEnd( jac, rhs, rhsFactor );
		hkJacobianBuilder::flush();
		hkJacobianBuilder::exitBuilder();

		hkVector4 result; 
		result.set(-0.267261f, 0.534522f, -0.801784f, 0.03075f);
		HK_TEST( result.equals4( jac.m_linear0 ) );
		result.set(-2.3519f, -2.3519f, -2.3519f, 0.00375984f);
		HK_TEST( result.equals4( jac.m_angular[0] ) );
		result.set(2.67261f, 0.748331f, 3.0735f, 79.7907f );
		HK_TEST( result.equals4( jac.m_angular[1] ) );
	}

	// buildAngularBegin
	{
		hkp2AngJacobian& jac = ang2Jac;

		hkJacobianBuilder::initBuilder( &mA, &mB, rhsFactor );
		hkJacobianBuilder::buildAngularBegin( &mA, &mB, dir, invJacFactor, jac );
		hkJacobianBuilder::buildAngularEnd( jac );
		hkJacobianBuilder::flush();
		hkJacobianBuilder::exitBuilder();

		hkVector4 result; 
		result.set(-2.13809f, -2.13809f, -2.13809f, 0.0185738f);
		HK_TEST( result.equals4( jac.m_angular[0] ) );
		result.set(2.13809f, 0.534523f, 1.87083f);
		HK_TEST( result.equals3( jac.m_angular[1] ) );
	}

	return 0;
}


//
// test registration
//
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(setup_main, "Fast", "Physics/Test/UnitTest/Internal/", __FILE__     );

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
