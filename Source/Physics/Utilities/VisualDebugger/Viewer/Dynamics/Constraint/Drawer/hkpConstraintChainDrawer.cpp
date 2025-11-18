/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/Constraint/Chain/hkpConstraintChainData.h>
#include <Physics/Dynamics/Constraint/Chain/BallSocket/hkpBallSocketChainData.h>
#include <Physics/Dynamics/Constraint/Chain/StiffSpring/hkpStiffSpringChainData.h>
#include <Physics/Dynamics/Constraint/Chain/Powered/hkpPoweredChainData.h>
#include <Physics/Dynamics/Constraint/Chain/hkpConstraintChainInstance.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpConstraintChainDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrimitiveDrawer.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>

#include <Common/Base/Math/Vector/hkVector4Util.h>



void hkpConstraintChainDrawer::drawConstraint(hkpConstraintInstance* constraint, hkDebugDisplayHandler* displayHandler, int tag)
{
	hkpConstraintChainInstance* instance = static_cast<hkpConstraintChainInstance*>(constraint);
	hkpConstraintChainData* data = instance->getData();

	m_primitiveDrawer.setDisplayHandler(displayHandler);

	int numConstraints = instance->m_chainedEntities.getSize() - 1;
	
	for (int i = 0; i < numConstraints; i++)
	{
		hkTransform refLocalToWorld;
		hkTransform attLocalToWorld;

		hkpRigidBody *refBody = reinterpret_cast<hkpRigidBody*>(instance->m_chainedEntities[i+1]);
		hkpRigidBody *attBody = reinterpret_cast<hkpRigidBody*>(instance->m_chainedEntities[i]);

		refLocalToWorld = refBody->getTransform();
		attLocalToWorld = attBody->getTransform();

		m_RB = refLocalToWorld.getRotation();
		m_RA = attLocalToWorld.getRotation();

		m_bodyBWPos = refLocalToWorld.getTranslation();
		m_bodyAWPos = attLocalToWorld.getTranslation();

		hkVector4 pivotInB;
		hkVector4 pivotInA;

		switch( data->getType() )
		{
		case hkpConstraintData::CONSTRAINT_TYPE_STIFF_SPRING_CHAIN:
			pivotInB = static_cast<hkpStiffSpringChainData*>(data)->m_infos[i].m_pivotInB;
			pivotInA = static_cast<hkpStiffSpringChainData*>(data)->m_infos[i].m_pivotInA;
			break;
		case hkpConstraintData::CONSTRAINT_TYPE_BALL_SOCKET_CHAIN:
			pivotInB = static_cast<hkpBallSocketChainData*>(data)->m_infos[i].m_pivotInB;
			pivotInA = static_cast<hkpBallSocketChainData*>(data)->m_infos[i].m_pivotInA;
			break;
		case hkpConstraintData::CONSTRAINT_TYPE_POWERED_CHAIN:
			pivotInB = static_cast<hkpPoweredChainData*>(data)->m_infos[i].m_pivotInB;
			pivotInA = static_cast<hkpPoweredChainData*>(data)->m_infos[i].m_pivotInA;
			break;
		default:
			HK_ASSERT2(0xad6777dd, false, "Chain type not supproted by the drawer.");
		}

		m_bodyBWPivot.setTransformedPos(refLocalToWorld, pivotInB);
		m_bodyAWPivot.setTransformedPos(attLocalToWorld, pivotInA);

		// drawing
		
		drawPivots(tag);
		drawBodyFrames(tag);
		displayHandler->displayLine(m_bodyAWPivot, m_bodyBWPivot, hkColor::RED, tag);
	}

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
