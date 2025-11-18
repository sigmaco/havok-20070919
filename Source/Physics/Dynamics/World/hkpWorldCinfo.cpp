/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/World/hkpWorldCinfo.h>

hkpWorldCinfo::hkpWorldCinfo()
{
	m_gravity.set(0.0f, -9.8f, 0.0f);
	m_enableSimulationIslands = true;
	m_broadPhaseQuerySize = 1024;
	m_broadPhaseWorldAabb.m_min.set(-500.0f, -500.0f, -500.0f);
	m_broadPhaseWorldAabb.m_max.set(500.0f, 500.0f, 500.0f);
	m_collisionFilter = HK_NULL;
	m_convexListFilter = HK_NULL; 
	m_broadPhaseNumMarkers = 0;
	m_sizeOfToiEventQueue = 250;
	m_solverTau = 0.6f;
	m_solverDamp = 1.0f;
	m_contactRestingVelocity = HK_REAL_MAX;
	m_solverIterations = 4;
	m_solverMicrosteps = 1; 
	m_forceCoherentConstraintOrderingInSolver = false;
	m_snapCollisionToConvexEdgeThreshold = 0.524f;
	m_snapCollisionToConcaveEdgeThreshold = 0.698f;
	m_enableToiWeldRejection = false;
	m_collisionTolerance = 0.1f;
	m_broadPhaseBorderBehaviour = BROADPHASE_BORDER_ASSERT;
	m_toiCollisionResponseRotateNormal = 0.2f;
	m_deactivationReferenceDistance = 0.02f;
	m_expectedMaxLinearVelocity = 200.0f;
	m_expectedMinPsiDeltaTime = 1.0f / 30.0f;
	m_iterativeLinearCastEarlyOutDistance = 0.01f;
	m_enableDeprecatedWelding = false;
	m_iterativeLinearCastMaxIterations = 20;
	m_enableDeactivation = true;
	m_shouldActivateOnRigidBodyTransformChange = true;
	m_minDesiredIslandSize = 64;
	m_highFrequencyDeactivationPeriod = 0.1f;
	m_lowFrequencyDeactivationPeriod = 1.0f;
	m_deactivationNumInactiveFramesSelectFlag0 = 0;
	m_deactivationNumInactiveFramesSelectFlag1 = 0;
	m_deactivationIntegrateCounter = 0;
	m_contactPointGeneration = CONTACT_POINT_REJECT_MANY;
	m_simulationType = SimulationType(SIMULATION_TYPE_CONTINUOUS);
	m_frameMarkerPsiSnap = .0001f;
	m_memoryWatchDog = HK_NULL;
	m_processActionsInSingleThread = true;
}

void hkpWorldCinfo::setBroadPhaseWorldSize(hkReal sideLength)
{
	m_broadPhaseWorldAabb.m_min.setAll( -0.5f * sideLength );
	m_broadPhaseWorldAabb.m_max.setAll(  0.5f * sideLength );
}

void hkpWorldCinfo::setupSolverInfo( enum hkpWorldCinfo::SolverType st)
{
	switch ( st )
	{
        case SOLVER_TYPE_2ITERS_SOFT:
                                    m_solverTau = 0.3f;
                                    m_solverDamp = 0.9f;
                                    m_solverIterations = 2;
                                    break;
        case SOLVER_TYPE_2ITERS_MEDIUM:
                                    m_solverTau = 0.6f;
                                    m_solverDamp = 1.0f;
                                    m_solverIterations = 2;
                                    break;
        case SOLVER_TYPE_2ITERS_HARD:
                                    m_solverTau = 0.9f;
                                    m_solverDamp = 1.1f;
                                    m_solverIterations = 2;
                                    break;
        case SOLVER_TYPE_4ITERS_SOFT:
                                    m_solverTau = 0.3f;
                                    m_solverDamp = 0.9f;
                                    m_solverIterations = 4;
                                    break;
        case SOLVER_TYPE_4ITERS_MEDIUM:
                                    m_solverTau = 0.6f;
                                    m_solverDamp = 1.0f;
                                    m_solverIterations = 4;
                                    break;
        case SOLVER_TYPE_4ITERS_HARD:
                                    m_solverTau = 0.9f;
                                    m_solverDamp = 1.1f;
                                    m_solverIterations = 4;
                                    break;
        case SOLVER_TYPE_8ITERS_SOFT:
                                    m_solverTau = 0.3f;
                                    m_solverDamp = 0.9f;
                                    m_solverIterations = 8;
                                    break;
        case SOLVER_TYPE_8ITERS_MEDIUM:
                                    m_solverTau = 0.6f;
                                    m_solverDamp = 1.0f;
                                    m_solverIterations = 8;
                                    break;
        case SOLVER_TYPE_8ITERS_HARD:
                                    m_solverTau = 0.9f;
                                    m_solverDamp = 1.1f;
                                    m_solverIterations = 8;
                                    break;
        default:
            HK_ASSERT2(0x32ba3a5b, 0, "Unknown solver type" );
	}
}

hkpWorldCinfo::hkpWorldCinfo( hkFinishLoadedObjectFlag flag )
{
	if( flag.m_finishing )
	{
		if ( 0.0f == m_contactRestingVelocity )
		{
			HK_WARN( 0xf03243ed, "m_contactRestingVelocity not set, setting it to REAL_MAX, so that the new collision restitution code will be disabled" );
			m_contactRestingVelocity = HK_REAL_MAX;
		} 
	}
}


/*
* Havok SDK - CLIENT RELEASE, BUILD(#20070919)
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
