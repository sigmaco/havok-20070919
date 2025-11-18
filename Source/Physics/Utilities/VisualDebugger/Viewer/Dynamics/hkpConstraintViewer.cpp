/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/hkBase.h>

#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpConstraintViewer.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>
#include <Common/Visualize/hkProcessFactory.h>

#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Visualize/Type/hkColor.h>
#include <Physics/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Physics/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Physics/Dynamics/Constraint/Malleable/hkpMalleableConstraintData.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpHingeDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpLimitedHingeDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpRagdollDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPrismaticDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpWheelDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpStiffSpringDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpBallSocketDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPointToPathDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPointToPlaneDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpPulleyDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpConstraintChainDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpHingeLimitsDrawer.h>
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/Constraint/Drawer/hkpRagdollLimitsDrawer.h>

int hkpConstraintViewer::m_tag = 0;

void HK_CALL hkpConstraintViewer::registerViewer()
{
	m_tag = hkProcessFactory::getInstance().registerProcess( getName(), create );
}

hkProcess* HK_CALL hkpConstraintViewer::create(const hkArray<hkProcessContext*>& contexts)
{
	return new hkpConstraintViewer(contexts);
}

hkpConstraintViewer::hkpConstraintViewer(const hkArray<hkProcessContext*>& contexts)
: hkpWorldViewerBase( contexts )
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			hkpWorld* world = m_context->getWorld(i);
	//		world->addConstraintListener( this );
			world->markForWrite();
			world->addWorldPostSimulationListener( this );
			world->unmarkForWrite();
		}
	}
}

hkpConstraintViewer::~hkpConstraintViewer()
{
	if (m_context)
	{
		for (int i=0; i < m_context->getNumWorlds(); ++i)
		{
			hkpWorld* world = m_context->getWorld(i);
	//		world->removeConstraintListener( this );
			world->markForWrite();
			world->removeWorldPostSimulationListener( this );
			world->unmarkForWrite();
		}
	}
}



void hkpConstraintViewer::worldAddedCallback( hkpWorld* world)
{
//	world->addConstraintListener( this );
	world->markForWrite();
	world->addWorldPostSimulationListener( this );
	world->unmarkForWrite();
}

void hkpConstraintViewer::worldRemovedCallback( hkpWorld* world)
{
//	world->removeConstraintListener( this );
	world->markForWrite();
	world->removeWorldPostSimulationListener( this );
	world->unmarkForWrite();
}

void hkpConstraintViewer::postSimulationCallback( hkpWorld* world )
{
	HK_TIMER_BEGIN("hkpConstraintViewer", this);

	{
		const hkArray<hkpSimulationIsland*>& islands = world->getActiveSimulationIslands();
		for ( int i = 0; i < islands.getSize(); ++i )
		{
			for ( int e = 0; e < islands[i]->getEntities().getSize(); e++)
			{
				hkpEntity* entity = islands[i]->getEntities()[e];
				const hkSmallArray<struct hkConstraintInternal>&  constraintMasters = entity->getConstraintMasters();

				for ( int c = 0; c < constraintMasters.getSize(); c++)
				{
					draw ( constraintMasters[c].m_constraint, m_displayHandler );
				}
			}
		}
	}

	{
		const hkArray<hkpSimulationIsland*>& islands = world->getInactiveSimulationIslands();
		for ( int i = 0; i < islands.getSize(); ++i )
		{
			for ( int e = 0; e < islands[i]->getEntities().getSize(); e++)
			{
				hkpEntity* entity = islands[i]->getEntities()[e];
				const hkSmallArray<struct hkConstraintInternal>&  constraintMasters = entity->getConstraintMasters();
				for ( int c = 0; c < constraintMasters.getSize(); c++)
				{
					draw ( constraintMasters[c].m_constraint, m_displayHandler );
				}
			}
		}
	}

	HK_TIMER_END();
}


void hkpConstraintViewer::draw(hkpConstraintInstance* constraint, hkDebugDisplayHandler* displayHandler)
{
	HK_TIMER_BEGIN("draw", this);

	int type = constraint->getData()->getType();

	HK_ASSERT2(0x21d74fd9, displayHandler,"displayHandler is NULL");

	switch(type)
	{
		case hkpConstraintData::CONSTRAINT_TYPE_BALLANDSOCKET:
		{
			hkpBallSocketDrawer ballSocketDrawer;
			ballSocketDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_HINGE:
		{
			hkpHingeDrawer hingeDrawer;
			hingeDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:
		{
			hkpLimitedHingeDrawer limitedHingeDrawer;
			limitedHingeDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_PRISMATIC:
		{
			hkpPrismaticDrawer prismaticDrawer;
			prismaticDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_STIFFSPRING:
		{
			hkpStiffSpringDrawer stiffSpringDrawer;
			stiffSpringDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_WHEEL:
		{
			hkpWheelDrawer wheelDrawer;
			wheelDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_POINTTOPATH:
		{
			hkpPointToPathDrawer pToPDrawer;
			pToPDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_POINTTOPLANE:
		{
			hkpPointToPlaneDrawer pToPlaneDrawer;
			pToPlaneDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:
		{
			hkpRagdollDrawer ragdollDrawer;
			ragdollDrawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_BREAKABLE:
		{
			hkpBreakableConstraintData* breakableConstraint = static_cast<hkpBreakableConstraintData*>(constraint->getData());
			hkpConstraintInstance fakeConstraint(constraint->getEntityA(), constraint->getEntityB(), breakableConstraint->getWrappedConstraintData() );
			draw(&fakeConstraint, displayHandler);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_MALLEABLE:
		{
			hkpMalleableConstraintData* malleableConstraint = static_cast<hkpMalleableConstraintData*>(constraint->getData());
			hkpConstraintInstance fakeConstraint(constraint->getEntityA(), constraint->getEntityB(), malleableConstraint->getWrappedConstraintData() );
			draw(&fakeConstraint, displayHandler);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_PULLEY:
		{
			hkpPulleyDrawer drawer;
			drawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;

		case hkpConstraintData::CONSTRAINT_TYPE_STIFF_SPRING_CHAIN:
		case hkpConstraintData::CONSTRAINT_TYPE_BALL_SOCKET_CHAIN:
		case hkpConstraintData::CONSTRAINT_TYPE_POWERED_CHAIN:
		{
			hkpConstraintChainDrawer drawer;
			drawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;
		case hkpConstraintData::CONSTRAINT_TYPE_HINGE_LIMITS:
		{
			hkpHingeLimitsDrawer drawer;
			drawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;
		case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL_LIMITS:
		{
			hkpRagdollLimitsDrawer drawer;
			drawer.drawConstraint(constraint, displayHandler, m_tag);
		}
		break;
	}

	HK_TIMER_END();


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
