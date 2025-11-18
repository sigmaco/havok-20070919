/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkTypeInfo.h>

#include <Common/Base/DebugUtil/StatisticsCollector/Util/hkStatisticsCollectorUtil.h>

// base object does not define placement new, so implement manually
// a.k.a. HK_REFLECTION_DEFINE_VIRTUAL(hkBaseObject);
static void HK_CALL finishLoadedObjecthkBaseObject(void*)
{
}
static void HK_CALL cleanupLoadedObjecthkBaseObject(void*)
{
}
static const void* HK_CALL getVtablehkBaseObject()
{
	hkBaseObject o;
	return *(void**)(&o);
}
extern const hkTypeInfo hkBaseObjectTypeInfo;
const hkTypeInfo hkBaseObjectTypeInfo( "hkBaseObject", finishLoadedObjecthkBaseObject, cleanupLoadedObjecthkBaseObject, getVtablehkBaseObject() );

void hkReferencedObject::calcStatistics( hkStatisticsCollector* collector ) const
{
    const hkClass* cls = hkStatisticsCollectorUtil::defaultBeginObject((void*)this,collector);
    if (cls)
    {
        calcContentStatistics(collector,cls);
        collector->endObject();
    }
	else
	{
		// assume we don't have child pointers
		collector->beginObject(HK_NULL, hkStatisticsCollector::MEMORY_ENGINE, this);
		collector->endObject();
	}
}

void
hkReferencedObject::calcContentStatistics( hkStatisticsCollector* collector,const hkClass* cls ) const
{
    HK_ASSERT(0x423423,cls != HK_NULL&&"For the default implementation to work the class must be passed in");
    hkStatisticsCollectorUtil::addClassContentsAll((void*)this, *cls,collector);
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
