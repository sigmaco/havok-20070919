/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Utilities/Constraint/Chain/hkpPoweredChainMapper.h>
#include <Physics/Utilities/Constraint/Chain/hkpConstraintChainUtil.h>
#include <Physics/Utilities/Constraint/Bilateral/hkpConstraintUtils.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include <Physics/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Physics/Dynamics/Constraint/Motor/hkpConstraintMotor.h>
#include <Physics/Dynamics/Constraint/Motor/hkpLimitedForceConstraintMotor.h>
#include <Physics/Dynamics/Constraint/Chain/hkpConstraintChainInstance.h>
#include <Physics/Dynamics/Constraint/Chain/Powered/hkpPoweredChainData.h>

namespace
{
	struct hkMapperTargetInfo
	{
		hkpPoweredChainMapper::Target m_target;
		int m_linkIndex;
	};
}

hkpPoweredChainMapper* hkpPoweredChainMapper::buildChainMapper(const Config config, const hkArray<hkpConstraintInstance*>& allConstraints, const hkArray<ChainEndpoints>& pairs, hkArray<hkpConstraintInstance*>* unusedConstraints)
{
	hkpPoweredChainMapper* mapper = new hkpPoweredChainMapper();
	hkArray<hkMapperTargetInfo> targetInfos;
	hkArray<int> linkIdxToNumTargets;
	{
		linkIdxToNumTargets.setSize(allConstraints.getSize());
		hkString::memSet( linkIdxToNumTargets.begin(), 0, linkIdxToNumTargets.getSize() * sizeof(int) );
	}

	hkPointerMap<hkpConstraintInstance*, int> constraintToLink;

	//
	// Build constraint to index mapping
	//
	for (int c = 0; c < allConstraints.getSize(); c++)
	{
		constraintToLink.insert(allConstraints[c], c);
	}

	//
	// Populate the link array
	//
	mapper->m_links.setSize(allConstraints.getSize());
	hkString::memSet( mapper->m_links.begin(), 0, mapper->m_links.getSize() * sizeof(LinkInfo) );

	//
	// iterate through all pairs and add consecutive chains to the mapper
	//
	for (int p = 0; p < pairs.getSize(); p++)
	{
		hkArray<hkpEntity*> linkedEntities;
		hkArray<hkpConstraintInstance*> linkedConstraints;

		// attempt to find a chain
		if ( HK_FAILURE == hkpConstraintChainUtil::findConstraintLinkBetweenEntities(allConstraints, pairs[p].m_start, pairs[p].m_end, linkedEntities, linkedConstraints) )
		{
			HK_WARN_ALWAYS(0xabbaaa88, "Cannot find a chain of constraints linking one of the entity pairs.");
			mapper->removeReference();
			return HK_NULL;
		}

		// create chain constraint 
		hkpConstraintChainInstance* chainInstance = hkpConstraintChainUtil::buildPoweredChain(linkedConstraints, config.m_cloneMotors);

		if (!chainInstance)
		{
			HK_WARN_ALWAYS(0Xabbaddaa, "Failed to build a chain.");
			mapper->removeReference();
			return HK_NULL;
		}

		mapper->m_chains.pushBack(chainInstance);

		// Add targets to the link array
		//
		// Also, overlay limit constraints
		for (int c = 0; c < linkedConstraints.getSize(); c++)
		{
			hkPointerMap<hkpConstraintInstance*, int>::Iterator it = constraintToLink.findKey(linkedConstraints[c]);
			if (!constraintToLink.isValid(it))
			{
				HK_WARN_ALWAYS(0xabba99dd, "Internal error.");
				chainInstance->removeReference();
				mapper->removeReference();
				return HK_NULL;
			}
			int linkIndex = constraintToLink.getValue(it);

			LinkInfo& link = mapper->m_links[linkIndex];
			hkMapperTargetInfo& info = targetInfos.expandOne();
			Target& target = info.m_target;
			info.m_linkIndex = linkIndex;
			linkIdxToNumTargets[linkIndex]++;

			if (chainInstance->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_POWERED_CHAIN)
			{
				HK_WARN_ALWAYS(0xabba9d6d, "Internal error; invalid chain type.");
				chainInstance->removeReference();
				mapper->removeReference();
				return HK_NULL;
			}
			target.m_chain = static_cast<hkpPoweredChainData*>( chainInstance->getData() );
			target.m_infoIndex = c;

			if (config.m_createLimitConstraints && (! link.m_limitConstraint))
			{
				link.m_limitConstraint = hkpConstraintUtils::convertToLimits(linkedConstraints[c]);
			}
		}
	}

	//
	// Now populate the mapper->m_targets and mapper->m_links arrays.
	//
	{
		int numAllLinksTillThisLink = 0;
		for (int l = 0; l < mapper->m_links.getSize(); l++)
		{
			mapper->m_links[l].m_firstTargetIdx = numAllLinksTillThisLink;
			numAllLinksTillThisLink += linkIdxToNumTargets[l];
			mapper->m_links[l].m_numTargets = 0;
		}

		mapper->m_targets.setSize(numAllLinksTillThisLink);
        
		HK_ASSERT2(0xad789d65, numAllLinksTillThisLink == targetInfos.getSize(), "Internal error.");
		for (int t = 0; t < targetInfos.getSize(); t++)
		{
			hkMapperTargetInfo& info = targetInfos[t];
			LinkInfo& link = mapper->m_links[info.m_linkIndex];

			// copy target info
			const int dstTargetIdx = link.m_firstTargetIdx + link.m_numTargets;
			mapper->m_targets[dstTargetIdx] = info.m_target;

			// update num targets in link
			link.m_numTargets++;
		}

		//Debug
#if defined HK_DEBUG
		for (int lnk = 0; lnk < mapper->m_links.getSize()-1; lnk++)
		{
			HK_ASSERT2(0xad77d854, mapper->m_links[lnk].m_firstTargetIdx + mapper->m_links[lnk].m_numTargets == mapper->m_links[lnk+1].m_firstTargetIdx, "Internal error.");
		}
#endif
	}

	//
	// Fill the unused constraints index
	//
	if(unusedConstraints)
	{
		for (int l = 0; l < mapper->m_links.getSize(); l++)
		{
			if (mapper->m_links[l].m_numTargets == 0)
			{
				unusedConstraints->pushBack(allConstraints[l]);
			}
		}
	}
	
	return mapper;
}


hkpPoweredChainMapper::~hkpPoweredChainMapper()
{
	for (int l = 0; l < m_links.getSize(); l++)
	{
		if (m_links[l].m_limitConstraint)
		{
			m_links[l].m_limitConstraint->removeReference();
		}
	}

	for (int c = 0; c < m_chains.getSize(); c++)
	{
		m_chains[c]->removeReference();
	}
}





void hkpPoweredChainMapper::setForceLimits(int linkIndex, int coordinageIndex, hkReal minForce, hkReal maxForce)
{
	hkArray<hkpConstraintMotor*> motors;
	getMotors(linkIndex, coordinageIndex, motors);
	if (motors.getSize())
	{
		minForce /= motors.getSize();
		maxForce /= motors.getSize();

		for (int m = 0; m < motors.getSize(); m++)
		{
			HK_ON_DEBUG( hkpConstraintMotor::MotorType type = motors[m]->getType());
			HK_ASSERT2(0xad67d9a1, type == hkpConstraintMotor::TYPE_POSITION
				                || type == hkpConstraintMotor::TYPE_VELOCITY
								|| type == hkpConstraintMotor::TYPE_SPRING_DAMPER, "Unsupported motor type. If your custom motor derives from the hkpLimitedForceConstraintMotor class, you can safely ignore this assert.");

			hkpLimitedForceConstraintMotor* limited = static_cast<hkpLimitedForceConstraintMotor*>(motors[m]);
			limited->m_minForce = minForce;
			limited->m_maxForce = maxForce;
		}
	}
}

void hkpPoweredChainMapper::getMotors(int linkIndex, int coordinateIndex, hkArray<hkpConstraintMotor*>& motorsOut)
{
	LinkInfo& link = m_links[linkIndex];

	for (int t = 0; t < link.m_numTargets; t++)
	{
		//Target& target = link.m_targets[t];
		Target& target = m_targets[link.m_firstTargetIdx + t];

		HK_ASSERT2(0x79c0f6a2, target.m_chain->getType() == hkpConstraintData::CONSTRAINT_TYPE_POWERED_CHAIN, "Illegal chain type in the mapper. Attempting to extract motors from a non-powered chain.");

		hkpPoweredChainData* powered = static_cast<hkpPoweredChainData*>(target.m_chain);
		hkpConstraintMotor* motor = powered->m_infos[target.m_infoIndex].m_motors[coordinateIndex];
		if (motor)
		{
			motorsOut.pushBack(motor); 
		}
		else
		{
			HK_WARN(0xad67885d, "Attempting to extract motors from a powered chain's link/coordinate that has no motor assigned.");
		}
	}
}

void hkpPoweredChainMapper::setMotors(int linkIndex, int coordinateIndex, hkpConstraintMotor* newMotor)
{
	LinkInfo& link = m_links[linkIndex];

	for (int t = 0; t < link.m_numTargets; t++)
	{
		//Target& target = link.m_targets[t];
		Target& target = m_targets[link.m_firstTargetIdx + t];

		HK_ASSERT2(0x4e035480, target.m_chain->getType() == hkpConstraintData::CONSTRAINT_TYPE_POWERED_CHAIN, "Illegal chain type in the mapper. Attempting to extract motors from a non-powered chain.");

		hkpPoweredChainData* powered = static_cast<hkpPoweredChainData*>(target.m_chain);
		hkpConstraintMotor* motor = powered->m_infos[target.m_infoIndex].m_motors[coordinateIndex];
		if (motor)
		{
			motor->removeReference();
		}

		powered->m_infos[target.m_infoIndex].m_motors[coordinateIndex] = newMotor;
		if (newMotor)
		{
			newMotor->addReference();
		}
	}
}

void hkpPoweredChainMapper::setTargetOrientation(int linkIndex, const hkQuaternion& newTarget)
{
	LinkInfo& link = m_links[linkIndex];

	for (int t = 0; t < link.m_numTargets; t++)
	{
		//Target& target = link.m_targets[t];
		Target& target = m_targets[link.m_firstTargetIdx + t];
		HK_ASSERT2(0x7ccc1cad, target.m_chain->getType() == hkpConstraintData::CONSTRAINT_TYPE_POWERED_CHAIN, "Illegal chain type in the mapper. Attempting to extract motors from a non-powered chain.");
		hkpPoweredChainData* powered = static_cast<hkpPoweredChainData*>(target.m_chain);
		powered->m_infos[target.m_infoIndex].m_aTc = newTarget;
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
