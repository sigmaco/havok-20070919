/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrismaticDrawer.h>
#include <Physics/Dynamics/Constraint/Bilateral/Prismatic/hkpPrismaticConstraintData.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrimitiveDrawer.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>

////////////////////////////////////////////////////////////////////

void hkpPrismaticDrawer::drawConstraint(hkpConstraintInstance* constraint, hkDebugDisplayHandler* displayHandler, int tag)
{
	hkpPrismaticConstraintData* prismatic = static_cast<hkpPrismaticConstraintData*>(constraint->getData());

	m_primitiveDrawer.setDisplayHandler(displayHandler);

	{
		hkTransform refLocalToWorld;
		hkTransform attLocalToWorld;
		updateCommonParameters(constraint, refLocalToWorld, attLocalToWorld);
		m_bodyBWPivot.setTransformedPos(refLocalToWorld, prismatic->m_atoms.m_transforms.m_transformB.getTranslation());
		m_bodyAWPivot.setTransformedPos(attLocalToWorld, prismatic->m_atoms.m_transforms.m_transformA.getTranslation());
	}

	drawPivots(tag);

	drawBodyFrames(tag);

	hkVector4 axisInWorld;
	axisInWorld.setRotatedDir(m_RB, prismatic->m_atoms.m_transforms.m_transformB.getColumn(hkpPrismaticConstraintData::Atoms::AXIS_SHAFT));
	hkVector4 axisPerpInWorld;
	axisPerpInWorld.setRotatedDir(m_RB, prismatic->m_atoms.m_transforms.m_transformB.getColumn(hkpPrismaticConstraintData::Atoms::AXIS_PERP_TO_SHAFT));

	// not a full depiction of the error
	// draw a red error line between the pivots
	displayHandler->displayLine(m_bodyAWPivot, m_bodyBWPivot, hkColor::RED, tag);
	

	// draw the free DOF
	{
		hkVector4 startAxis,endAxis;
		if(prismatic->getMaxLinearLimit() != HK_REAL_MAX)
		{
			endAxis.setMul4(prismatic->getMaxLinearLimit(), axisInWorld);
		    endAxis.add4(m_bodyBWPivot);
			startAxis.setMul4(prismatic->getMinLinearLimit(), axisInWorld);
			startAxis.add4(m_bodyBWPivot);
			displayHandler->displayLine(startAxis, endAxis, hkColor::rgbFromFloats(0.f, .5f, 1.f), tag);
		}
		else
		{
			endAxis.setMul4(m_lineLength, axisInWorld);
		    endAxis.add4(m_bodyBWPivot);
			startAxis.setMul4(-m_lineLength, axisInWorld);
			startAxis.add4(m_bodyBWPivot);
			displayHandler->displayLine(startAxis, endAxis, hkColor::rgbFromFloats(0.f, .5f, 1.f), tag);
		}
	}

	// draw limits in white
	{
		hkVector4 startLine;
		hkVector4 endLine;
		hkVector4 center;
		hkVector4 temp;

		hkReal minLimit = prismatic->getMinLinearLimit();
		hkReal maxLimit = prismatic->getMaxLinearLimit();

		temp.setMul4(minLimit, axisInWorld);
		center.setAdd4(m_bodyBWPivot,temp);
		temp.setMul4(.5f * m_lineLength, axisPerpInWorld);
		startLine.setAdd4(center,temp);
		temp.setMul4(-.5f * m_lineLength, axisPerpInWorld);
		endLine.setAdd4(center, temp);
		displayHandler->displayLine(startLine, endLine, hkColor::WHITE, tag);

		temp.setMul4(maxLimit, axisInWorld);
		center.setAdd4(m_bodyBWPivot,temp);
		temp.setMul4(.5f * m_lineLength, axisPerpInWorld);
		startLine.setAdd4(center,temp);
		temp.setMul4(-.5f * m_lineLength, axisPerpInWorld);
		endLine.setAdd4(center, temp);
		displayHandler->displayLine(startLine, endLine, hkColor::WHITE, tag);
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
