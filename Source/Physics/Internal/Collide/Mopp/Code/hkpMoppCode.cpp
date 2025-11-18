/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Internal/hkpInternal.h>
#include <Physics/Internal/Collide/Mopp/Code/hkpMoppCode.h>
#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>

	// MOPP chunk size must be a power of 2
HK_COMPILE_TIME_ASSERT( (HK_MOPP_CHUNK_SIZE & (HK_MOPP_CHUNK_SIZE - 1)) == 0 );

#if defined(HK_PLATFORM_SPU)
hkpMoppCache* g_SpuMoppCache;
#endif


void hkpMoppCode::calcStatistics( hkStatisticsCollector* collector ) const
{
	collector->beginObject("hkpMoppCode", collector->MEMORY_SHARED, this);
	collector->addArray( "Code", collector->MEMORY_SHARED, this->m_data );
	collector->endObject();
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
