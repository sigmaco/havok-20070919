/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpRagdollLimitsDrawer.h>
#include <Physics/Dynamics/Constraint/Chain/RagdollLimits/hkpRagdollLimitsData.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrimitiveDrawer.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>


////////////////////////////////////////////////////////////////////

// Nearly exact copy of the code from hkpRagdollDrawer. (With exception of the pivot vectors being zeroed.)
void hkpRagdollLimitsDrawer::drawConstraint(hkpConstraintInstance* constraint, hkDebugDisplayHandler* displayHandler, int tag)
{

	hkpRagdollLimitsData* ragdoll = static_cast<hkpRagdollLimitsData*>(constraint->getData());

	m_primitiveDrawer.setDisplayHandler(displayHandler);

	{
		hkTransform refLocalToWorld;
		hkTransform attLocalToWorld;
		updateCommonParameters(constraint, refLocalToWorld, attLocalToWorld);
		m_bodyBWPivot.setTransformedPos(refLocalToWorld, hkVector4::getZero());
		m_bodyAWPivot.setTransformedPos(attLocalToWorld, hkVector4::getZero());
	}

	drawPivots(tag);

	const hkVector4* baseA = &ragdoll->m_atoms.m_rotations.m_rotationA.getColumn(0);
	const hkVector4* baseB = &ragdoll->m_atoms.m_rotations.m_rotationB.getColumn(0);

	// Get parameters from ragdoll constraint
	hkVector4 refTwistAxisWorld;
	refTwistAxisWorld.setRotatedDir(m_RB, baseB[hkpRagdollLimitsData::Atoms::AXIS_TWIST]);

	hkVector4 refCrossedWorld;
	refCrossedWorld.setCross( baseB[hkpRagdollLimitsData::Atoms::AXIS_TWIST], baseB[hkpRagdollLimitsData::Atoms::AXIS_PLANES] );
	refCrossedWorld.normalize3();
	refCrossedWorld.setRotatedDir(m_RB, refCrossedWorld);

	hkVector4 refPlaneNormalWorld;
	refPlaneNormalWorld.setRotatedDir(m_RB, baseB[hkpRagdollLimitsData::Atoms::AXIS_PLANES]);

	hkVector4 cross;
	cross.setCross(baseA[hkpRagdollLimitsData::Atoms::AXIS_PLANES], baseA[hkpRagdollLimitsData::Atoms::AXIS_TWIST]);
	cross.normalize3();
	hkVector4 attCrossedWorld;
	attCrossedWorld.setRotatedDir(m_RA, cross);

	hkVector4 attTwistAxisWorld;
	attTwistAxisWorld.setRotatedDir(m_RA, baseA[hkpRagdollLimitsData::Atoms::AXIS_TWIST]);
	
	/////////////////////////////////////////////

	//always display twist axes
	m_primitiveDrawer.displayArrow(m_bodyBWPivot, refTwistAxisWorld, refCrossedWorld, hkColor::GREEN,m_arrowSize, tag);
	m_primitiveDrawer.displayArrow(m_bodyAWPivot, attTwistAxisWorld, attCrossedWorld, hkColor::rgbFromChars(255, 255, 0), m_arrowSize, tag);

	// draw twist cone
	hkReal coneHeight = 0.5f;
	m_twistCone.setParameters( ragdoll->getConeAngularLimit(), coneHeight, 24, refTwistAxisWorld, m_bodyBWPivot);
	
	// draw plane	
	hkVector4 ext; ext.setAll3(coneHeight*0.5f);
	m_plane.setParameters(refPlaneNormalWorld, refCrossedWorld, m_bodyBWPivot, ext);



	// draw plane cones
	{
		hkReal planeMaxLimit = ragdoll->m_atoms.m_planesLimit.m_maxAngle;
		hkReal planeMinLimit = ragdoll->m_atoms.m_planesLimit.m_minAngle;

		// These limits are negative for "lower cone", positive for upper,
		// but are "negative" cones (ie. areas in which the constrained bject/axis
		// should not be, so we have to draw cones of internal angle PI/2 - limit.

		m_planeCone1.setParameters((HK_REAL_PI/2.f - hkMath::fabs(planeMaxLimit)), coneHeight, 24, refPlaneNormalWorld, m_bodyBWPivot);

		refPlaneNormalWorld.setNeg4(refPlaneNormalWorld);	// Flip axis of cone to draw min limit

		m_planeCone2.setParameters((HK_REAL_PI/2.f - hkMath::fabs(planeMinLimit)), coneHeight, 24, refPlaneNormalWorld, m_bodyBWPivot);
	}


	// Pass geometries off to display handler
	{
		hkArray<hkDisplayGeometry*> twist;
		hkArray<hkDisplayGeometry*> planeCones;
		hkArray<hkDisplayGeometry*> plane;
	    twist.setSize(1);
		plane.setSize(1);
		planeCones.setSize(2);
		twist[0] = &m_twistCone;
		planeCones[0] = &m_planeCone1;
		planeCones[1] =  &m_planeCone2;
		plane[0] = &m_plane;
		displayHandler->displayGeometry(twist, hkColor::YELLOW, tag);
		displayHandler->displayGeometry(planeCones, hkColor::RED, tag);
		displayHandler->displayGeometry(plane, hkColor::rgbFromChars(255, 0, 255), tag);
	}
}

////////////////////////////////////////////////////////////////////

























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
