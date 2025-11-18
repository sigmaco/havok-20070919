/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Utilities/Constraint/Chain/hkpPoweredChainMapperUtil.h>
#include <Physics/Utilities/Constraint/Chain/hkpPoweredChainMapper.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/Constraint/Chain/hkpConstraintChainInstance.h>



void hkpPoweredChainMapperUtil::addToWorld(hkpWorld* world, hkpPoweredChainMapper* mapper)
{
	for (int c = 0; c < mapper->m_chains.getSize(); c++)
	{
		world->addConstraint( mapper->m_chains[c] );
	}

	for (int l = 0; l < mapper->m_links.getSize(); l++)
	{
		hkpConstraintInstance* instance = mapper->m_links[l].m_limitConstraint;
		if (instance)
		{
			world->addConstraint( instance );
		}
	}
}

void hkpPoweredChainMapperUtil::removeFromWorld(hkpWorld* world, hkpPoweredChainMapper* mapper)
{
	for (int c = 0; c < mapper->m_chains.getSize(); c++)
	{
		world->removeConstraint( mapper->m_chains[c] );
	}

	for (int l = 0; l < mapper->m_links.getSize(); l++)
	{
		hkpConstraintInstance* instance = mapper->m_links[l].m_limitConstraint;
		if (instance)
		{
			world->removeConstraint( instance );
		}
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
