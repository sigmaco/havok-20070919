/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#ifndef HAVOK_FILTER_OPTIMIZE_SHAPE_H
#define HAVOK_FILTER_OPTIMIZE_SHAPE_H

#include <ContentTools/Common/Filters/FilterPhysics/OptimizeShapeHierarchy/hctOptimizeShapeHierarchyOptions.h>

#include <Common/Base/Container/Array/hkObjectArray.h>

class hctOptimizeShapeHierarchyFilter : public hctFilterInterface
{
	public:

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT);

	hctOptimizeShapeHierarchyFilter(const hctFilterManagerInterface* owner);

	/*virtual*/ ~hctOptimizeShapeHierarchyFilter();
	/*virtual*/ void process( class hkRootLevelContainer& data, bool batchMode );
	/*virtual*/ HWND showOptions(HWND owner);
	/*virtual*/ void hideOptions();
	/*virtual*/ void setOptions(const void* optionData, int optionDataSize, unsigned int version);
	/*virtual*/ int getOptionsSize() const;
	/*virtual*/ void getOptions(void* optionData) const;

	public:

		HWND m_optionsDialog;
		void setDataFromControls();
		void setControlsFromData();
		void enableControls();
		hctOptimizeShapeHierarchyOptions m_options;
		mutable hkArray<char> m_optionsBuf;

};



class hctOptimizeShapeHierarchyFilterDesc : public hctFilterDescriptor
{
	public:

	/*virtual*/ unsigned int getID() const { return 0x472e73da; }
	/*virtual*/ FilterCategory getCategory() const { return HK_CATEGORY_PHYSICS; }
	/*virtual*/ FilterBehaviour getFilterBehaviour() const { return HK_DATA_MUTATES_INPLACE; }
	/*virtual*/ const char* getShortName() const { return "Optimize Shape Hierarchy"; }
	/*virtual*/ const char* getLongName() const { return "Optimize shape hierarchy by collapsing transform shapes where possible."; }
	/*virtual*/ unsigned int getFilterVersion() const { return HCT_FILTER_VERSION(1,0,0); }
	/*virtual*/ hctFilterInterface* createFilter(const class hctFilterManagerInterface* owner) const { return new hctOptimizeShapeHierarchyFilter(owner); }

	/*virtual*/ HavokComponentMask getRequiredHavokComponents () const { return HK_COMPONENT_PHYSICS; }
};

extern hctOptimizeShapeHierarchyFilterDesc g_optimizeShapeHierarchyDesc;

#endif // HAVOK_FILTER_OPTIMIZE_SHAPE_H


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
