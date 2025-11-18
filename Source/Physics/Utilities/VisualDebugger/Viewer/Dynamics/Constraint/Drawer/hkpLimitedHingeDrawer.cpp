/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpLimitedHingeDrawer.h>
#include <Physics/Dynamics/Constraint/Bilateral/LimitedHinge/hkpLimitedHingeConstraintData.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrimitiveDrawer.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>


////////////////////////////////////////////////////////////////////

void hkpLimitedHingeDrawer::drawConstraint(hkpConstraintInstance* constraint, hkDebugDisplayHandler* displayHandler, int tag)
{
	hkpLimitedHingeConstraintData* lhinge = static_cast<hkpLimitedHingeConstraintData*>(constraint->getData());

	m_primitiveDrawer.setDisplayHandler(displayHandler);

	{
		hkTransform refLocalToWorld;
		hkTransform attLocalToWorld;
		updateCommonParameters(constraint, refLocalToWorld, attLocalToWorld);
		m_bodyBWPivot.setTransformedPos(refLocalToWorld, lhinge->m_atoms.m_transforms.m_transformB.getTranslation());
		m_bodyAWPivot.setTransformedPos(attLocalToWorld, lhinge->m_atoms.m_transforms.m_transformA.getTranslation());
	}
	
	drawBodyFrames(tag);

	drawPivots(tag);

	hkVector4 axisInWorld;
	axisInWorld.setRotatedDir(m_RB, lhinge->m_atoms.m_transforms.m_transformB.getColumn(hkpLimitedHingeConstraintData::Atoms::AXIS_AXLE));

	hkVector4 axisPerpInWorld;
	axisPerpInWorld.setRotatedDir(m_RB, lhinge->m_atoms.m_transforms.m_transformB.getColumn(hkpLimitedHingeConstraintData::Atoms::AXIS_PERP_TO_AXLE_2));


	// draw a red error line between the pivots
	displayHandler->displayLine(m_bodyAWPivot, m_bodyBWPivot, hkColor::RED, tag);

	// draw the free DOF
	{
		hkVector4 startAxis,endAxis;
		endAxis.setMul4(.5f * m_lineLength, axisInWorld);
		endAxis.add4(m_bodyBWPivot);
		startAxis.setMul4(-.5f * m_lineLength, axisInWorld);
		startAxis.add4(m_bodyBWPivot);
		displayHandler->displayLine(startAxis, endAxis, hkColor::rgbFromFloats(0.f, .5f, 1.f), tag);
	}

	// draw the limits
	if (lhinge->m_atoms.m_angLimit.m_isEnabled)
	{
		hkReal thetaMax = lhinge->getMaxAngularLimit();
		hkReal thetaMin = lhinge->getMinAngularLimit();

		if (thetaMax - thetaMin < 1e14f)
		{
			m_angularLimit.setParameters(1.5f,thetaMin,thetaMax,24,m_bodyBWPivot,axisInWorld,axisPerpInWorld);
			hkArray<hkDisplayGeometry*> geometry;
			geometry.setSize(1);
			geometry[0] = &(m_angularLimit);
			displayHandler->displayGeometry(geometry,hkColor::WHITE, tag);
		}
	}

	// draw a line representing m_axisPerpInWorld to which the angle
	// is with respect to.
	{
		hkVector4 start;
		hkVector4 end;
		start = m_bodyBWPivot;
		end = start;
		end.addMul4(0.5f * m_lineLength, axisPerpInWorld);
		displayHandler->displayLine(start, end, hkColor::YELLOW, tag);

		hkVector4 axisPerpA;
		axisPerpA.setRotatedDir(m_RA, lhinge->m_atoms.m_transforms.m_transformA.getColumn(hkpLimitedHingeConstraintData::Atoms::AXIS_PERP_TO_AXLE_2)); 
		axisPerpA.normalize3();

		start = m_bodyAWPivot;
		end = start;
		end.addMul4(0.5f * m_lineLength, axisPerpA);
		displayHandler->displayLine(start, end, hkColor::YELLOW, tag);
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
