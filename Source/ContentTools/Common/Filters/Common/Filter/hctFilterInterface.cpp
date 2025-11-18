/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

hctFilterInterface::hctFilterInterface (const hctFilterManagerInterface* owner) : hkReferencedObject (), m_filterManager (owner)
{

}
/*virtual*/ hctFilterInterface::~hctFilterInterface ()
{

}


/*virtual*/ HWND hctFilterInterface::showOptions ( HWND owner )
{
	return HK_NULL;
}

/*virtual*/ void hctFilterInterface::hideOptions()
{

}


/*virtual*/ void hctFilterInterface::setOptions (const void* optionData, int optionDataSize, unsigned int version)
{

}

/*virtual*/ int hctFilterInterface::getOptionsSize() const
{
	return 0;
}

/*virtual*/ void hctFilterInterface::getOptions(void* optionData) const
{


}

const hctFilterManagerInterface* hctFilterInterface::getFilterManager() const
{
	return m_filterManager;
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
