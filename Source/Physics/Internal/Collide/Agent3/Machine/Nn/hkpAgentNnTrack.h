/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_COLLISION_AGENT_TRACK_H
#define HK_COLLIDE2_COLLISION_AGENT_TRACK_H

#include <Common/Base/hkBase.h>
#include <Physics/Internal/Collide/Agent3/hkpAgent3.h>
typedef void hkpAgentData;
struct hkpAgentNnEntry;
struct hkpAgentNnSector; 
class hkpCollidable;

#if ( HK_POINTER_SIZE == 4 )
#	define HK_AGENT3_AGENT_SIZE 128
#	define HK_AGENT3_SECTOR_SIZE 512
#else //XXX
#	define HK_AGENT3_AGENT_SIZE 160
#	define HK_AGENT3_SECTOR_SIZE 960
#endif
#define HK_AGENT3_AGENTS_PER_SECTOR (HK_AGENT3_SECTOR_SIZE/HK_AGENT3_AGENT_SIZE)


	// Make sure if you use this entry that you pad to get a 16 byte alignment
	// Notes: 
	//
	//   HK_POINTER_SIZE == 4
	//   --------------------
	//   - sizeof(hkpAgentEntry) = 8
	//   - sizeof(hkpAgentNnEntry) = 8 + 20
	//
	//   HK_POINTER_SIZE == 8
	//   --------------------
	//   - sizeof(hkpAgentEntry) = 16
	//   - sizeof(hkpAgentNnEntry) = 16 + 32
struct hkpAgentNnEntry: hkpAgentEntry
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkpAgentNnEntry );

	hkObjectIndex		m_agentIndexOnCollidable[2]; // this value must not be written back from spu!
	hkpContactMgr*		m_contactMgr;

	hkUchar				m_collisionQualityIndex;
	hkUchar				m_forceCollideOntoPpu;	// only used if the platform has an spu
	hkUchar				m_padding[2];
	// Additional 4 bytes padding on 64-bit platforms
	hkpLinkedCollidable*	m_collidable[2];

	inline hkpCollidable*  getCollidableA(){ return reinterpret_cast<hkpCollidable*>(m_collidable[0]); }
	inline hkpCollidable*  getCollidableB(){ return reinterpret_cast<hkpCollidable*>(m_collidable[1]); }
};


struct hkpAgentNnSector
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AGENT, hkpAgentNnSector);
	
	hkUint8 m_data[ HK_AGENT3_SECTOR_SIZE ];

	hkpAgentNnEntry* getBegin()
	{
		return reinterpret_cast<hkpAgentNnEntry*>( &m_data[0] );
	}

	hkpAgentNnEntry* getEnd()
	{
		return reinterpret_cast<hkpAgentNnEntry*>( &m_data[HK_AGENT3_SECTOR_SIZE] );
	}
};

struct hkpAgentNnTrack
{
	hkpAgentNnTrack( )
	{
#if defined(HK_PLATFORM_HAS_SPU)
		m_sectors.reserve(4);	// align array on 16 byte boundary
		m_spuNumSectors = 0;
		m_spuBytesUsedInLastSector = HK_AGENT3_SECTOR_SIZE;

		m_ppuBytesUsedInLastSector = HK_AGENT3_SECTOR_SIZE;
#else
		m_bytesUsedInLastSector = HK_AGENT3_SECTOR_SIZE;
#endif
		HK_ASSERT2(0xf0ff0088, HK_AGENT3_SECTOR_SIZE % HK_AGENT3_AGENT_SIZE == 0, "SectorSize must be a multiple of agentSize");
	}

	int getSectorSize( int sectorIndex ) const
	{
#if !defined(HK_PLATFORM_HAS_SPU)
		if ( sectorIndex+1 == m_sectors.getSize())
		{
			return m_bytesUsedInLastSector;
		}
#else
		if ( sectorIndex+1 == m_spuNumSectors)
		{
			return m_spuBytesUsedInLastSector;
		}

		if ( sectorIndex+1 == m_sectors.getSize())
		{
			return m_ppuBytesUsedInLastSector;
		}
#endif
		return HK_AGENT3_SECTOR_SIZE;
	}


	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkpAgentNnTrack );

#ifdef HK_PLATFORM_HAS_SPU
	hkUint16	m_spuNumSectors;
	hkUint16    m_spuBytesUsedInLastSector;
	hkUint16    m_ppuBytesUsedInLastSector;
	HK_FORCE_INLINE int getNumPpuSectors() const { return m_sectors.getSize() - m_spuNumSectors; }
#else
	hkUint32	m_bytesUsedInLastSector;
#endif

#if defined(HK_PLATFORM_HAS_SPU)
		// spu sectors come first, than some bytes of padding, than ppu sectors
	hkArray<hkpAgentNnSector*> m_sectors; // constructor sets size to 4 so that array will be 16byte-aligned
#else
	hkInplaceArray<hkpAgentNnSector*,1> m_sectors; 
#endif
};





#endif // HK_COLLIDE2_COLLISION_AGENT_TRACK_H


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
