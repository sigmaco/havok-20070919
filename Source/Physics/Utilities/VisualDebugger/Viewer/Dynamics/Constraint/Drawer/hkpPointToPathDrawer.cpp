/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrimitiveDrawer.h>

#include <Physics/Dynamics/Constraint/Bilateral/PointToPath/hkpPointToPathConstraintData.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPointToPathDrawer.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>

void hkpPointToPathDrawer::drawConstraint(hkpConstraintInstance* constraint, hkDebugDisplayHandler* displayHandler, int tag)
{

	hkpPointToPathConstraintData* pToPConstraint = static_cast<hkpPointToPathConstraintData*>(constraint->getData());

	m_primitiveDrawer.setDisplayHandler(displayHandler);

	hkTransform refLocalToWorld;
	hkTransform attLocalToWorld;

	updateCommonParameters(constraint, refLocalToWorld, attLocalToWorld);
	m_bodyBWPivot = refLocalToWorld.getTranslation();

	pToPConstraint->calcPivot( constraint->getRigidBodyA()->getTransform(), m_bodyAWPivot);
	
	drawBodyFrames(tag);

	drawPivots(tag);

	// Draw the path
	if(pToPConstraint->getPath() != HK_NULL)
	{
		hkTransform refConstraintToWorld;
		refConstraintToWorld.setMul(refLocalToWorld, pToPConstraint->getConstraintToLocalTransform(1));

		hkpParametricCurve* curve = pToPConstraint->getPath(); 

		if(curve != HK_NULL)
		{
		
			hkArray<hkVector4> points;
			curve->getPointsToDraw(points);

			int size;
			size = points.getSize();
			hkVector4 p1;
			hkVector4 p2;
			hkVector4 p;

			for(int i = 1; i < size; i++)
			{
				p = points[i];
				p1.setTransformedPos(refConstraintToWorld, p);
				p = points[i - 1];
				p2.setTransformedPos(refConstraintToWorld, p);	
				displayHandler->displayLine(p1, p2, hkColor::rgbFromFloats(0.f, .25f, 1.f), tag);
			}
		}
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
