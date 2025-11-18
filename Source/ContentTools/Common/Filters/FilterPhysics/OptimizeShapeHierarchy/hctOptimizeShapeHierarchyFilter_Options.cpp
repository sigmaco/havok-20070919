/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <ContentTools/Common/Filters/FilterPhysics/hctFilterPhysics.h>

#include <ContentTools/Common/Filters/FilterPhysics/OptimizeShapeHierarchy/hctOptimizeShapeHierarchyFilter.h>


void hctOptimizeShapeHierarchyFilter::setOptions(const void* optionData, int optionDataSize, unsigned int version ) 
{
	// Get the options from the XML data.
	if ( hctFilterUtils::readOptionsXml( optionData, optionDataSize, m_optionsBuf, hctOptimizeShapeHierarchyOptionsClass ) == HK_SUCCESS )
	{
		hctOptimizeShapeHierarchyOptions* options = reinterpret_cast<hctOptimizeShapeHierarchyOptions*>( m_optionsBuf.begin() );

		m_options.m_shareTolerance = options->m_shareTolerance;
		m_options.m_shareShapes = options->m_shareShapes;
		m_options.m_permuteDetect = options->m_permuteDetect;
		m_options.m_collapseTransforms = options->m_collapseTransforms;
		m_options.m_collapseThreshold = options->m_collapseThreshold;
		m_options.m_collapseBehaviourType = options->m_collapseBehaviourType;
		m_options.m_propagate = options->m_propagate;
	}
	else
	{
		HK_WARN_ALWAYS( 0xabba482b, "The XML for the " << g_optimizeShapeHierarchyDesc.getShortName() << " option data could not be loaded." );
		return;
	}
}

int hctOptimizeShapeHierarchyFilter::getOptionsSize() const
{
	// We write the options to a temporary buffer and return the size of it. The buffer itself will be used
	// later on by getOptions().
	hctFilterUtils::writeOptionsXml( hctOptimizeShapeHierarchyOptionsClass, &m_options, m_optionsBuf, g_optimizeShapeHierarchyDesc.getShortName() );
	return m_optionsBuf.getSize();
}

void hctOptimizeShapeHierarchyFilter::getOptions(void* optionData) const
{
	// Get options is always called after getOptionsSize() - so we reuse the temporary buffer we used in getOptionsSize()
	hkString::memCpy( optionData, m_optionsBuf.begin(), m_optionsBuf.getSize() );	
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
