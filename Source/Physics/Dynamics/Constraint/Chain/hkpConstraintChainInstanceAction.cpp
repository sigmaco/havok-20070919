/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Constraint/Chain/hkpConstraintChainInstanceAction.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>

void hkpConstraintChainInstanceAction::applyAction( const hkStepInfo& stepInfo ) 
{
	/// Just make sure the action was properly added to the world together with the constraint chain.
	HK_ASSERT2(0xad5677dd, getConstraintInstance()->getOwner() != HK_NULL, "Constraint was not added to the world.");
}

hkpAction* hkpConstraintChainInstanceAction::clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const
{
	HK_ASSERT2(0xad7765dd, false, "Cloning of hkpConstraintChainInstanceAction not supported."); 
	return HK_NULL;
}

void hkpConstraintChainInstanceAction::entityRemovedCallback(hkpEntity* entity)
{
	HK_ASSERT(0xad000227, getWorld() );
		// Call the constraint's callback, which in turn will immeidately remove this action from the world
	getConstraintInstance()->entityRemovedCallback(entity);
}


void hkpConstraintChainInstanceAction::getEntities( hkArray<hkpEntity*>& entitiesOut )
{
	entitiesOut = getConstraintInstance()->m_chainedEntities;
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
