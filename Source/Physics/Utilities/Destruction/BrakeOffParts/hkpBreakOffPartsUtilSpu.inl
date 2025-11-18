/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#include <Physics/Utilities/Destruction/BrakeOffParts/hkpBreakOffPartsUtil.h>
#include <Physics/Dynamics/World/hkpPhysicsSystem.h>

template < typename T > HK_FORCE_INLINE
T hkPointerMapBase<T>::getWithDefaultSpu( T key, T def ) const
{
	if ( getSize() ==0 )
	{
		return def;
	}
	T i = pointerHash(key, m_hashMod);

		// once we access the hash we are not allowed to access any member variables any more
	T* elems = &m_elem[0];
	int hashMod = m_hashMod;

	HK_ASM_SEP("+++");	// force the compiler to be careful
	while (true)
	{
		const T* local;
		{
			const hkUlong mask = (HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE-1);
			void *ppu = &elems[i];
			hkUlong basePpu =  hkUlong(ppu) & ~mask;
			hkUlong offset  =  hkUlong(ppu) & mask;
			local = reinterpret_cast<const T*>( g_SpuCollideUntypedCache->getFromMainMemory( (void*)basePpu, HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE) );
			local = hkAddByteOffsetConst( local, offset );
		}
		if ( local[0] == T(HK_POINTERMAP_EMPTY_KEY) )
		{
			return def;
		}

		if ( local[0] == key )
		{
			const hkUlong mask = (HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE-1);
			void *ppu = &elems[i+hashMod+1];
			hkUlong basePpu =  hkUlong(ppu) & ~mask;
			hkUlong offset  =  hkUlong(ppu) & mask;
			local = reinterpret_cast<const T*>( g_SpuCollideUntypedCache->getFromMainMemory( (void*)basePpu, HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE) );
			local = hkAddByteOffsetConst( local, offset );
			return (T)local[0];
		}
		i = (i+1) & hashMod;
	}	
// 	for( 
// 		m_elem[i] != 0;	
// 		i = (i+1) & m_hashMod)
// 	{
// 		if( m_elem[i] == key )
// 		{
// 			return (T)m_elem[i+m_hashMod+1];
// 		}
// 	}
// 	return def;
}


void hkpBreakOffPartsUtil::LimitContactImpulseUtil::contactPointAddedCallbackSpu(hkpEntity* entityA, hkpEntity* entityB, hkpContactPointAddedEvent& event)
{
	//
	//	Get the utils into main memory
	//
	hkpEntity* entity = entityA;
	hkpShapeKey key   = event.m_bodyA->getShapeKey();
	int maxImpulse = hkUFloat8::MAX_VALUE-1;
	hkpEntity* entityOfUtil = HK_NULL; 

	for (int i =0; i < 2; i++)
	{
		const LimitContactImpulseUtil* util = (LimitContactImpulseUtil*)entity->m_breakOffPartsUtil;
		if (util)
		{
			util = reinterpret_cast<const LimitContactImpulseUtil*>( g_SpuCollideUntypedCache->getFromMainMemory(util, sizeof(*util)) );
			int utilMaxImpulse = util->m_maxImpulse.m_value;

			// access the hash, this could mean the util gets swapped out
			hkpEntity* entityInMainMemory = util->m_entity;
			{
				int m = (int)util->m_shapeKeyToMaxImpulse.m_map.getWithDefaultSpu( key, 0 );
				if ( !m )
				{
					// try the default maxImpulse
					m = utilMaxImpulse;
					key = HK_INVALID_SHAPE_KEY;
				}
				if ( m < maxImpulse )
				{
					entityOfUtil = entityInMainMemory;
					maxImpulse = m;
				}
			}
		}
		entity = entityB;
		key    = event.m_bodyB->getShapeKey();
	}

	if ( maxImpulse != hkUFloat8::MAX_VALUE-1)
	{
		hkUFloat8 maxImp; maxImp.m_value = hkUint8(maxImpulse);
		event.m_contactPointProperties->setMaxImpulsePerStep( maxImp );


		hkpSimpleConstraintContactMgr* mgr = reinterpret_cast<hkpSimpleConstraintContactMgr*>(event.m_internalContactMgr.val());
		if ( entityOfUtil != mgr->m_constraint.getEntityA() )
		{
			event.m_contactPointProperties->m_flags |= hkContactPointMaterial::CONTACT_BREAKOFF_OBJECT_ID;
		}
		else
		{
			event.m_contactPointProperties->m_flags &= ~hkContactPointMaterial::CONTACT_BREAKOFF_OBJECT_ID;
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
