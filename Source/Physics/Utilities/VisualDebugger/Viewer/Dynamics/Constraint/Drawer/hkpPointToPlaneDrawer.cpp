/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/Constraint/Bilateral/PointToPlane/hkpPointToPlaneConstraintData.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPointToPlaneDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrimitiveDrawer.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>

#include <Common/Base/Math/Vector/hkVector4Util.h>


////////////////////////////////////////////////////////////////////

void hkpPointToPlaneDrawer::drawConstraint(hkpConstraintInstance* constraint, hkDebugDisplayHandler* displayHandler, int tag)
{

	hkpPointToPlaneConstraintData* plane = static_cast<hkpPointToPlaneConstraintData*>(constraint->getData());

	m_primitiveDrawer.setDisplayHandler(displayHandler);

	{
		hkTransform refLocalToWorld;
		hkTransform attLocalToWorld;
		updateCommonParameters(constraint, refLocalToWorld, attLocalToWorld);
		m_bodyBWPivot.setTransformedPos(refLocalToWorld, plane->m_atoms.m_transforms.m_transformB.getTranslation() );
		m_bodyAWPivot.setTransformedPos(attLocalToWorld, plane->m_atoms.m_transforms.m_transformA.getTranslation());
	}

	drawPivots(tag);

	drawBodyFrames(tag);

		// illustrate the constraint plane attached to body A
	    // by drawing a set of lines in the plane
	{
		hkVector4 perpVec0; perpVec0.setRotatedDir(m_RB, plane->m_atoms.m_transforms.m_transformB.getColumn((plane->m_atoms.m_lin.m_axisIndex+1)%3) );
		hkVector4 perpVec1; perpVec1.setRotatedDir(m_RB, plane->m_atoms.m_transforms.m_transformB.getColumn((plane->m_atoms.m_lin.m_axisIndex+2)%3) );

		hkVector4 lines[6][2];
		for (int coord = 0; coord < 2; coord++)
		{
			for (int i = -1; i <= 1; i++)
			{
				hkVector4 v0 = coord ? perpVec0 : perpVec1;
				hkVector4 v1 = coord ? perpVec1 : perpVec0;
				lines[coord*3 + i + 1][0] = m_bodyBWPivot;
				lines[coord*3 + i + 1][1] = m_bodyBWPivot;
				lines[coord*3 + i + 1][0].addMul4( 2.0f, v0);
				lines[coord*3 + i + 1][1].addMul4(-2.0f, v0);
				lines[coord*3 + i + 1][0].addMul4(hkReal(i) * 1.4f, v1);
				lines[coord*3 + i + 1][1].addMul4(hkReal(i) * 1.4f, v1);
			}
		}

		for (int i = 0; i < 6; i++)
		{
			displayHandler->displayLine(lines[i][0],lines[i][1],hkColor::rgbFromFloats(0.8f,.8f,.8f), tag);
		}
	}

		// draw the pivot arm for body A
	displayHandler->displayLine(m_bodyAWPivot,m_bodyAWPos,hkColor::rgbFromFloats(0.3f,.3f,.8f), tag);
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
