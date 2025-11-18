/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/Constraint/Bilateral/StiffSpring/hkpStiffSpringConstraintData.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpStiffSpringDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrimitiveDrawer.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>


////////////////////////////////////////////////////////////////////

void hkpStiffSpringDrawer::drawConstraint(hkpConstraintInstance* constraint, hkDebugDisplayHandler* displayHandler, int tag)
{

	hkpStiffSpringConstraintData* spring = static_cast<hkpStiffSpringConstraintData*>(constraint->getData());

	m_primitiveDrawer.setDisplayHandler(displayHandler);

	{
		hkTransform refLocalToWorld;
		hkTransform attLocalToWorld;
		updateCommonParameters(constraint, refLocalToWorld, attLocalToWorld);
		m_bodyBWPivot.setTransformedPos(refLocalToWorld, spring->m_atoms.m_pivots.m_translationB);
		m_bodyAWPivot.setTransformedPos(attLocalToWorld, spring->m_atoms.m_pivots.m_translationA);
	}

	drawPivots(tag);

	drawBodyFrames(tag);

	// draw the error
	// first draw the spring segment at its proper length in lblue
	// then draw error..if any in red
	{
		hkReal springLength = spring->getSpringLength();
		
		hkVector4 dir;
		dir.setSub4(m_bodyBWPivot,m_bodyAWPivot);
		dir.normalize3();
		dir.setMul4(springLength,dir);
		dir.add4(m_bodyAWPivot);
		displayHandler->displayLine(m_bodyAWPivot,dir,hkColor::rgbFromFloats(0,.5f,1), tag);
		displayHandler->displayLine(dir,m_bodyBWPivot,hkColor::RED, tag);
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
