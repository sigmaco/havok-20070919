/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>

#if defined(HK_PLATFORM_SPU)
#	include <Common/Base/Spu/Dma/Manager/hkSpuDmaManager.h>
#endif

#include <Physics/Dynamics/World/Util/hkpWorldConstraintUtil.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h>
#include <Physics/Dynamics/Constraint/hkpConstraintInstance.h>

#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/Util/hkpWorldOperationUtil.h>
#include <Physics/Dynamics/World/Simulation/Multithreaded/Spu/hkpSpuConfig.h>


#if !defined(HK_COMPILER_MWERKS)
// Metroworks compilers use a post-attribute for alignment.  To make the code cleaner,
// class alignment (i.e. HK_ALIGNCLASS) has been disabled metroworks compilers.
HK_COMPILE_TIME_ASSERT( (sizeof(hkpSoftContactModifierConstraintAtom)    & 0xf) == 0);
HK_COMPILE_TIME_ASSERT( (sizeof(hkpMassChangerModifierConstraintAtom)    & 0xf) == 0);
HK_COMPILE_TIME_ASSERT( (sizeof(hkpViscousSurfaceModifierConstraintAtom) & 0xf) == 0);
HK_COMPILE_TIME_ASSERT( (sizeof(hkpMovingSurfaceModifierConstraintAtom)  & 0xf) == 0);
#endif

//HK_COMPILE_TIME_ASSERT( (HK_OFFSET_OF(hkMovingSurfaceModifierAtomContainer, m_modifier.m_velocity[0]) & 0xf) == 0); // VS2005 does not like this...


#if !defined(HK_PLATFORM_SPU)

void hkpWorldConstraintUtil::addConstraint( hkpWorld* world, hkpConstraintInstance* constraint )
{
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->m_entities[0]->getSimulationIsland(), HK_ACCESS_RW);
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->m_entities[1]->getSimulationIsland(), HK_ACCESS_RW);

	HK_ASSERT2(0x312cc775 , HK_NULL == constraint->getOwner(), "A constraint cannot be added to the world twice.");
#ifdef HK_DEBUG
	for (int i = 0; i < 2; ++i)
	{
		HK_ASSERT2(0x1158af49, constraint->m_entities[i], "Both entities must be set before adding a constraint to the world.");
		HK_ASSERT2(0x476bb28b, constraint->m_entities[i]->getSimulationIsland(), "Both entities must be added to a world before adding the constraint." );
	}
#endif

	// add reference (kept by the owner)
	constraint->addReference();

	hkpConstraintData::ConstraintInfo info;	constraint->getData()->getConstraintInfo(info);

	hkConstraintInternal internalBuffer;
	{
		internalBuffer.m_constraint  = constraint;
		internalBuffer.m_entities[0] = constraint->m_entities[0];
		internalBuffer.m_entities[1] = constraint->m_entities[1];
		hkpModifierConstraintAtom* mod = constraint->m_constraintModifiers;
		internalBuffer.m_atoms       = (mod) ? mod             : info.m_atoms;
		internalBuffer.m_atomsSize   = (mod) ? mod->m_modifierAtomSize : hkUint16(info.m_sizeOfAllAtoms);
		internalBuffer.m_priority    = constraint->m_priority;
	}

	hkConstraintInternal* intern = &internalBuffer;
	HK_ASSERT2(0x77f2af97 , intern->m_entities[0]->getWorld() == intern->m_entities[1]->getWorld(),  "Both constraints must be added to the same world.");
	hkpWorldOperationUtil::mergeIslandsIfNeeded(intern->m_entities[0], intern->m_entities[1]);

	// choose the master entity
	{
		// in case of a non multithreaded environment we choose our master 
		// if several threads are running our choice must independent of the current master lists
#	if HK_CONFIG_THREAD != HK_CONFIG_MULTI_THREADED 
		if (intern->m_entities[0]->isFixed() == intern->m_entities[1]->isFixed())
		{
			// choose the one with more number of master constraints unless we have more than 8 masters
			int numMasters0 = intern->m_entities[0]->m_constraintsMaster.getSize();
			int numMasters1 = intern->m_entities[1]->m_constraintsMaster.getSize();
			if ( numMasters0 + numMasters1 < 8 )
			{
				intern->m_whoIsMaster =  numMasters0 >= numMasters1;
			}
			else
			{
				intern->m_whoIsMaster =  numMasters0 <= numMasters1;
			}
		}
		else
#	endif
		{
			// choose the unfixed one (if both are fixed/unfixed)
			intern->m_whoIsMaster = intern->m_entities[0]->isFixed();
		}
	}
	hkpEntity* masterEntity = intern->getMasterEntity();

	// mark the constraint as inserted into the world
	hkpSimulationIsland* island = masterEntity->getSimulationIsland();

	constraint->setOwner( island );
	island->m_numConstraints++;

	// update hkSimulationInformation (to adjust its constraint cache)
	{
		hkpConstraintAtom::AtomType atomType = intern->getAtoms()->getType();

		intern->m_isNormalType    = true;
		intern->m_callbackRequest = hkpConstraintAtom::CALLBACK_REQUEST_NONE;

		if ( atomType == hkpConstraintAtom::TYPE_BRIDGE )
		{
			intern->m_callbackRequest |= hkpConstraintAtom::CALLBACK_REQUEST_SETUP_PPU_ONLY;

			if (constraint->getData()->isBuildJacobianCallbackRequired())
			{
				intern->m_callbackRequest |= hkpConstraintAtom::CALLBACK_REQUEST_SETUP_CALLBACK;
			}

			intern->m_isNormalType = constraint->getType() == hkpConstraintInstance::TYPE_NORMAL;
		}

		if ( atomType == hkpConstraintAtom::TYPE_PULLEY )
		{
			intern->m_callbackRequest |= hkpConstraintAtom::CALLBACK_REQUEST_SETUP_PPU_ONLY;
		}

		if ( constraint->m_constraintModifiers)
		{
			intern->m_callbackRequest |= hkpModifierConstraintAtom::addAllModifierDataToConstraintInfo( constraint->m_constraintModifiers, info );
		}
		intern->clearConstraintInfo();
		constraint->m_internal = intern;	// direct internal to our temporary buffer, will be corrected later
		constraint->getOwner()->addConstraintInfo(constraint, info);
	}

	
	//
	// insert m_internal to the entity's list and preserve the constraint order
	//
	int insertPos;
	{
		hkSmallArray<hkConstraintInternal>& masters = masterEntity->m_constraintsMaster;
		int lim = masters.getSize();
		for (insertPos = 0; insertPos < lim; insertPos++)
		{
			hkConstraintInternal& currentMaster = masters[insertPos];
			// add constraint after the last other constraint of the same or lesser priority
			if (currentMaster.m_priority > intern->m_priority)
			{
				break;
			}

			// in case of a multithreaded environment we have to make sure that all constraints
			// are processed in a deterministic way. We archive this by making sure that the
			// order of constraints in the currentMaster list is independent from the order constraints are added.
#		if HK_CONFIG_THREAD == HK_CONFIG_MULTI_THREADED 
			else if (currentMaster.m_priority == intern->m_priority)
			{
				// We delay querying of entity[1] uids to avoid unnecessary cache misses
				const hkUint32 masterUid = currentMaster.m_entities[0]->getUid();
				const hkUint32    newUid = intern->m_entities[0]->getUid();

				// to guarantee deterministic order, we simply order the constraint by the uid's of their entities.
				if ( masterUid > newUid  || ( masterUid == newUid  && currentMaster.m_entities[1]->getUid() > intern->m_entities[1]->getUid() ) )
				{
					break;
				}
			}
#		endif
		}

		int firstIndexToRelink = ( masters.getSize() < masters.getCapacity() ) ? insertPos : 0;

		// move the instance of hkConstraintInternal
		// and relink our masters
		masters.insertAt( insertPos, *intern );

		for ( int m = firstIndexToRelink; m < masters.getSize(); m++ )
		{
			hkConstraintInternal* ci = &masters[m];
			ci->m_constraint->m_internal = ci;
		}

		// refresh the pointer 
		intern = constraint->m_internal;
	}

	//    
	// allocate and reserve space in our constraintRuntime
	//
	{
		hkSmallArray<hkConstraintInternal>& masters = masterEntity->m_constraintsMaster;
		hkpConstraintData::RuntimeInfo rInfo;
		intern->m_constraint->getData()->getRuntimeInfo( constraint->m_wantRuntime, rInfo );
		rInfo.m_sizeOfExternalRuntime = HK_NEXT_MULTIPLE_OF(16, rInfo.m_sizeOfExternalRuntime);
		intern->m_runtimeSize = (hkUint16)( rInfo.m_sizeOfExternalRuntime );
		// <os.todo.a> think about that assert and where it belongs
		//HK_ASSERT2(0x589d57fa, hkUlong(intern->m_runtimeSize) <= HK_SPU_CONSTRAINT_RUNTIME_BUFFER_SIZE, "Runtime doesn't fit into static buffer on spu.");

		if ( rInfo.m_sizeOfExternalRuntime )
		{
			hkArray<hkUint8>& rt = masterEntity->m_constraintRuntime;
			int oldSize = rt.getSize();
			hkUint8* oldStart = rt.begin();
			rt.reserveExactly( oldSize + rInfo.m_sizeOfExternalRuntime );
			rt.setSizeUnchecked( oldSize + rInfo.m_sizeOfExternalRuntime );
			hkUint8* newStart = rt.begin();
			hkUint8* insertPoint = newStart;
			hkUlong offset = hkGetByteOffset( oldStart, newStart );

			// fix pointers of all constraints till insertPos
			int p;
			for (p = 0; p < insertPos; p++)
			{
				hkConstraintInternal* ci = &masters[p];
				if ( ci->m_runtime )
				{
					ci->m_runtime = hkAddByteOffset( ci->m_runtime, offset );
					insertPoint = (hkUint8*)hkAddByteOffset( ci->m_runtime, ci->m_runtimeSize );
				}
			}
			// insert our runtime data
			{
				hkUint8* restEnd = rt.end() - intern->m_runtimeSize;
				hkUlong restSize = hkGetByteOffset( insertPoint, restEnd );
				hkString::memMove( insertPoint + intern->m_runtimeSize, insertPoint, int(restSize) );
				intern->m_runtime = reinterpret_cast<hkpConstraintRuntime*>(insertPoint);
				p++;
			}

			// fix pointers of the rest of the constraints
			offset += intern->m_runtimeSize;
			for (; p < masters.getSize(); p++)
			{
				hkConstraintInternal* ci = &masters[p];
				ci->m_runtime = (ci->m_runtime) ? hkAddByteOffset( ci->m_runtime, offset ): HK_NULL;
			}
		}
		else
		{
			intern->m_runtime = HK_NULL;
		}
		intern->m_constraint->m_data->addInstance( constraint, intern->m_runtime, intern->m_runtimeSize );
	}

	// just update the slave's pointer to the constraint
	hkpEntity* slaveEntity = intern->getSlaveEntity();
	{
		intern->m_slaveIndex = hkObjectIndex( slaveEntity->m_constraintsSlave.getSize() );
		slaveEntity->m_constraintsSlave.pushBack( constraint );
	}
}


void hkpWorldConstraintUtil::removeConstraint( hkpConstraintInstance* constraint )
{
	HK_ASSERT2(0x654d83cc, HK_NULL != constraint->getOwner(), "Trying to remove a constraint that has not been added to a world.");

	HK_ON_DEBUG_MULTI_THREADING( hkpWorld* world = constraint->m_entities[0]->getWorld() );
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->m_entities[0]->getSimulationIsland(), HK_ACCESS_RW);
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, constraint->m_entities[1]->getSimulationIsland(), HK_ACCESS_RW);

	hkConstraintInternal* intern = constraint->m_internal;

	//
	// remove the constraint from the island; reset island's cache, reset constraints' owner
	//
	
	// request island split check
	hkpSimulationIsland* island = static_cast<hkpSimulationIsland*>(constraint->getOwner());
	{
		island->m_splitCheckRequested = true;
		HK_ACCESS_CHECK_WITH_PARENT( island->m_world, HK_ACCESS_RO, island, HK_ACCESS_RW );
	}

	// update hkSimulationInformation (to adjust its constraint cache)
	{
		hkpConstraintInfo info;
		intern->getConstraintInfo(info);
		constraint->getOwner()->subConstraintInfo(constraint, info);
	}
	island->m_numConstraints--;
	constraint->setOwner( HK_NULL );

	// remove the constraint from the slave body 
	{
		hkpEntity* slaveEntity = intern->getSlaveEntity();
		hkObjectIndex slaveIndex = intern->m_slaveIndex;

		hkArray<hkpConstraintInstance*>& slaves = slaveEntity->m_constraintsSlave;
		hkpConstraintInstance* lastConstraint = slaves.back();
			// check whether we are removing the right thing
		HK_ASSERT( 0Xf0346778, slaves[slaveIndex] == constraint );
		slaves[slaveIndex] = lastConstraint;
		slaves.popBack();
		lastConstraint->m_internal->m_slaveIndex = slaveIndex;
	}

	hkpEntity* masterEntity = intern->getMasterEntity();

	// remove the runtime data from the master body
	intern->m_constraint->getData()->removeInstance( constraint, intern->m_runtime, intern->m_runtimeSize );
	hkUlong runtimeOffset = 0;
	if ( intern->m_runtime )
	{
		hkConstraintInternal* ci = intern;
		runtimeOffset = -ci->m_runtimeSize;
		hkpConstraintRuntime* toDeleteBegin = ci->m_runtime;
		hkpConstraintRuntime* toDeleteEnd   = hkAddByteOffset( ci->m_runtime, ci->m_runtimeSize );
		hkUint8* totalEnd      = masterEntity->m_constraintRuntime.end();
		hkUlong restLen = hkGetByteOffset( toDeleteEnd, totalEnd );
		hkString::memMove( toDeleteBegin, toDeleteEnd,  int(restLen) );
		masterEntity->m_constraintRuntime.popBack( ci->m_runtimeSize );
		ci->m_runtime = HK_NULL; 
	}

	//
	//	Delete modifiers
	//
	{
		hkpConstraintAtom* atom = intern->m_atoms;
		while ( 1 )
		{
			if ( !atom->isModifierType() )
			{
				break;
			}
			hkpModifierConstraintAtom* modifier = reinterpret_cast<hkpModifierConstraintAtom*>(atom);
			atom = modifier->m_child;
			hkThreadMemory::getInstance().deallocateChunk(modifier, modifier->m_modifierAtomSize, HK_MEMORY_CLASS_CONSTRAINT );
		}
		intern->m_constraint->m_constraintModifiers = HK_NULL;
		intern->m_atoms = HK_NULL;
	}

	// remove the constraint from the master body (it's gotta be there !!)
	// and relink the rest of the entries
	{
		hkConstraintInternal* ci = intern;

		constraint->m_internal = HK_NULL;

		hkConstraintInternal* back = &masterEntity->m_constraintsMaster.back();

		// preserve the order of constraints
		while( ci < back )
		{
			ci[0] = ci[1];
			ci->m_constraint->m_internal = ci;
			ci->m_runtime = (ci->m_runtime) ? hkAddByteOffset(ci->m_runtime, runtimeOffset): HK_NULL;
			ci++;
		}
		masterEntity->m_constraintsMaster.popBack();
	}

	// remove reference (been kept by the owner)
	constraint->removeReference();
}

hkpConstraintInstance* hkpWorldConstraintUtil::getConstraint( const hkpEntity* entityA, const hkpEntity* entityB)
{
	HK_ON_DEBUG_MULTI_THREADING( hkpWorld* world = entityA->getWorld() );
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_IGNORE, entityA->getSimulationIsland(), HK_ACCESS_RO);
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_IGNORE, entityB->getSimulationIsland(), HK_ACCESS_RO);

	const hkpEntity* entities[] = { entityA, entityB };

	for (int i = 0; i < 2; i++)
	{
		const hkpEntity* masterEntity = entities[i];
		const hkpEntity* otherEntity  = entities[1-i];

		for (int c = 0; c < masterEntity->m_constraintsMaster.getSize(); c++)
		{
			if (masterEntity->m_constraintsMaster[c].getOtherEntity(masterEntity) == otherEntity)
			{
				// one or more constraints exist
				return masterEntity->m_constraintsMaster[c].m_constraint;
			}
		}
	}
	return HK_NULL;
}



void hkpWorldConstraintUtil::addModifier( hkpConstraintInstance* instance, hkpConstraintOwner& constraintOwner, hkpModifierConstraintAtom* newModifier )
{
	constraintOwner.checkAccessRw();

	hkpModifierConstraintAtom* lastModifier = hkpWorldConstraintUtil::findLastModifier( instance );
	hkConstraintInternal* cInternal = instance->m_internal;

	if ( newModifier->getType() == hkpConstraintAtom::TYPE_MODIFIER_MOVING_SURFACE && lastModifier != HK_NULL )
	{
		//
		// only insert new container at the end of the modifiers-list if new modifier is of type "moving surface"
		// and if there are already modifiers attached to this constraint
		//
		newModifier->m_child     = lastModifier->m_child;
		newModifier->m_childSize = lastModifier->m_childSize;

		// insert new modifier between terminal atom and the current "last modifier"
		lastModifier->m_child     =  newModifier;
		lastModifier->m_childSize =  newModifier->m_modifierAtomSize;
	}
	else
	{
		// add new modifier at the begin of our modifier list
		instance->m_constraintModifiers = newModifier;


		if ( cInternal )
		{
			newModifier->m_child     = cInternal->m_atoms;
			newModifier->m_childSize = cInternal->m_atomsSize;
			cInternal->m_atoms       =  newModifier;
			cInternal->m_atomsSize   =  newModifier->m_modifierAtomSize;
		}
		else
		{
			hkpConstraintData::ConstraintInfo cinfo; instance->getData()->getConstraintInfo( cinfo );
			newModifier->m_child     = cinfo.m_atoms;
			newModifier->m_childSize = hkUint16(cinfo.m_sizeOfAllAtoms);
		}
	}

	//
	//	Update constraint info in constraint owner and master list only if the constraint is added to the world
	//
	if ( cInternal )
	{
		hkpConstraintInfo cinfo;		cinfo.clear();

		int callbackRequest = newModifier->addModifierDataToConstraintInfo( cinfo );
		constraintOwner.addConstraintInfo( instance, cinfo );

		if ( instance->m_internal )
		{
			instance->m_internal->m_callbackRequest |= callbackRequest;
		}
	}
}



void hkpWorldConstraintUtil::removeModifier( hkpConstraintInstance* instance, hkpConstraintOwner& constraintOwner, hkpConstraintAtom::AtomType type )
{
	constraintOwner.checkAccessRw();

	hkpModifierConstraintAtom* modifier = instance->m_constraintModifiers;

	if ( !modifier )
	{
		return;
	}
	hkConstraintInternal* cInternal = instance->m_internal;


	//
	//	Check whether we are the first modifier
	//
	{
		HK_ASSERT( 0xf0323454, modifier->isModifierType());

		hkpConstraintAtom::AtomType modType = modifier->getType();
		if ( modType == type)
		{
			hkpConstraintAtom* child = modifier->m_child;
			if ( cInternal )
			{
				cInternal->m_atoms     = modifier->m_child;
				cInternal->m_atomsSize = modifier->m_childSize;
			}

			if ( child->isModifierType() )
			{
				instance->m_constraintModifiers = static_cast<hkpModifierConstraintAtom*>(child);
			}
			else
			{
				instance->m_constraintModifiers = HK_NULL;
			}

			goto UPDATE_CONSTRAINT_INFO;
		}
	}

	{
	    hkpModifierConstraintAtom* father = modifier;
	    hkpConstraintAtom* atom = modifier->m_child;
    
	    while ( 1 )
	    {
		    // abort if we reached the constraint's original atom
		    if ( !atom->isModifierType() )
		    {
			    return;
		    }
		    modifier = static_cast<hkpModifierConstraintAtom*>(atom);
    
		    hkpConstraintAtom::AtomType modType = modifier->getType();
    
		    if ( modType == type )
		    {
			    father->m_child     = modifier->m_child;
			    father->m_childSize = modifier->m_childSize;
			    goto UPDATE_CONSTRAINT_INFO;
		    }
		    father  = modifier;
		    atom   = modifier->m_child;
	    }
	}

UPDATE_CONSTRAINT_INFO:
	//
	//	Update constraint info in constraintOwner and master list
	//
	if (cInternal)
	{
		hkpConstraintInfo cinfo;	cinfo.clear();
		modifier->addModifierDataToConstraintInfo( cinfo );
		constraintOwner.subConstraintInfo( cInternal->m_constraint, cinfo );
	}
	hkThreadMemory::getInstance().deallocateChunk(modifier, modifier->m_modifierAtomSize, HK_MEMORY_CLASS_CONSTRAINT );
}



hkpModifierConstraintAtom* hkpWorldConstraintUtil::findModifier( hkpConstraintInstance* instance, hkpConstraintAtom::AtomType type )
{
	HK_ON_DEBUG( hkpWorld* world = instance->m_entities[0]->getWorld() );
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_RO, instance->getSimulationIsland(), HK_ACCESS_RO);

	hkpModifierConstraintAtom* atom = instance->m_constraintModifiers;
	if (!atom)
	{
		return HK_NULL;
	}

	while ( 1 )
	{
		// abort if we reached the constraint's original atom
		hkpConstraintAtom::AtomType modType = atom->getType();

		if ( modType == type )
		{
			return atom;
		}
		if ( !atom->m_child->isModifierType() )
		{
			return HK_NULL;
		}

		atom = static_cast<hkpModifierConstraintAtom*>(atom->m_child);
	}

}



hkpModifierConstraintAtom* hkpWorldConstraintUtil::findLastModifier( hkpConstraintInstance* instance )
{
	HK_ON_DEBUG_MULTI_THREADING( hkpWorld* world = instance->getEntityA()->getWorld());
	HK_ACCESS_CHECK_WITH_PARENT( world, HK_ACCESS_IGNORE, instance->getSimulationIsland(), HK_ACCESS_RO);

	hkpModifierConstraintAtom* atom = instance->m_constraintModifiers;

		//
		// return HK_NULL if no modifier present
		//
	if ( !atom )
	{
		return HK_NULL;
	}

		//
		// search modifier list for last modifier
		//
	while ( 1 )
	{
		hkpConstraintAtom* childAtom     = atom->m_child;

		// abort if we reached the constraint's terminal atom
		if ( !childAtom->isModifierType() )
		{
			return atom;
		}

		atom = static_cast<hkpModifierConstraintAtom*>(childAtom);
	}
}

#endif

void hkpWorldConstraintUtil::updateFatherOfMovedAtom( hkpConstraintInstance* instance, const hkpConstraintAtom* oldAtom, const hkpConstraintAtom* updatedAtom, int updatedSizeOfAtom )
{
	HK_ASSERT2(0xaf83fe64, updatedAtom, "Updated atom is invalid.");

	//
	// update constraint internal if no modifiers are attached to constraint
	//
	hkConstraintInternal* cInternal = instance->m_internal;
	if ( !instance->m_constraintModifiers )
	{
		if (cInternal)
		{
			HK_ASSERT( 0xf0e3ed45, oldAtom == cInternal->m_atoms);
			cInternal->m_atoms     = const_cast<hkpConstraintAtom*>( updatedAtom );
			cInternal->m_atomsSize = hkUint16(updatedSizeOfAtom);
		}
		return;
	}

	if ( instance->m_constraintModifiers == oldAtom )
	{
		instance->m_constraintModifiers = const_cast<hkpModifierConstraintAtom*>(static_cast<const hkpModifierConstraintAtom*>(updatedAtom));
		if (cInternal)
		{
		    cInternal->m_atoms     = const_cast<hkpConstraintAtom*>( updatedAtom );
		    cInternal->m_atomsSize = hkUint16(updatedSizeOfAtom);
		}
		return;
	}

	//
	// search modifier list for last modifier
	//
#if defined(HK_PLATFORM_SPU)
	HK_ALIGN16( hkUint8 modifierBuffer[HK_NEXT_MULTIPLE_OF(16, sizeof(hkpModifierConstraintAtom))] );
	hkpModifierConstraintAtom* localModifier = reinterpret_cast<hkpModifierConstraintAtom*>( &modifierBuffer[0] );
#else
	hkpModifierConstraintAtom* localModifier = instance->m_constraintModifiers;
#endif

	hkpModifierConstraintAtom* modifier = instance->m_constraintModifiers;
	while ( 1 )
	{
#if defined(HK_PLATFORM_SPU)
		hkSpuDmaManager::getFromMainMemoryAndWaitForCompletion(localModifier, modifier, sizeof(hkpModifierConstraintAtom), hkSpuDmaManager::READ_COPY);
		HK_SPU_DMA_PERFORM_FINAL_CHECKS                       (modifier, localModifier, sizeof(hkpModifierConstraintAtom));
#endif

		hkpConstraintAtom* childAtom = localModifier->m_child;

		// abort if we reached the constraint's original atom
		if ( childAtom == oldAtom )
		{
			//
			// update last modifier
			//
			localModifier->m_child     = const_cast<hkpConstraintAtom*>( updatedAtom );
			localModifier->m_childSize = hkUint16(updatedSizeOfAtom);

#if defined(HK_PLATFORM_SPU)
			hkSpuDmaManager::putToMainMemoryAndWaitForCompletion(modifier, localModifier, sizeof(hkpModifierConstraintAtom), hkSpuDmaManager::WRITE_NEW);
			HK_SPU_DMA_PERFORM_FINAL_CHECKS                     (modifier, localModifier, sizeof(hkpModifierConstraintAtom));
#endif
			break;
		}
		HK_ASSERT2( 0xf0323454, childAtom->isModifierType(), "Internal inconsistencies with constraint modifiers" );
		modifier = static_cast<hkpModifierConstraintAtom*>(childAtom);
	}

}


/*
* Havok SDK - CLIENT RELEASE, BUILD(#20070919)
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
