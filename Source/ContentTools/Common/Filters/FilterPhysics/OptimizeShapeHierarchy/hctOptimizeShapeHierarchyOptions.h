/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKOPTIMIZESHAPEOPTIONS__H
#define HKOPTIMIZESHAPEOPTIONS__H

/// hctOptimizeShapeHierarchyOptions meta information
extern const class hkClass hctOptimizeShapeHierarchyOptionsClass;

/// Options associated to our Optimize Shape Hierarchy filter.
struct hctOptimizeShapeHierarchyOptions
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_EXPORT, hctOptimizeShapeHierarchyOptions );
	HK_DECLARE_REFLECTION();
   
	/// options
	enum CollapseBehaviourOptionsType
	{
		COLLAPSE_OPTIONS_INVALID,
		COLLAPSE_OPTIONS_ALWAYS,
		COLLAPSE_OPTIONS_NEVER,
		COLLAPSE_OPTIONS_THRESHOLD,
		COLLAPSE_OPTIONS_MAX_ID
	};

	// if true, detect shared shapes
	hkBool m_shareShapes;  //IDC_CB_Share
	
	hkBool m_collapseTransforms; //IDC_CB_CollapseTransforms

	// tolerance value used to determine whether shapes are identical   
	float m_shareTolerance; 

	// specifies the behaviour of the collapse utility on encountering shared shapes:
	// COLLAPSE_OPTIONS_ALWAYS means the shape is always collapsed regardless of whether it is shared.
	// COLLAPSE_OPTIONS_NEVER  means the shape is not collapsed if it is shared by two or more parents.
	// COLLAPSE_OPTIONS_THRESHOLD means the shape is collapsed if it is shared by less than m_collapseThreshold parents.
	hkEnum<CollapseBehaviourOptionsType, hkUint8 > m_collapseBehaviourType;

	int m_collapseThreshold; 

	// if true, transforms are propagated into the children of list shapes.
	hkBool m_propagate; 

	// if true, detect equality of vertex arrays and triangles even with permutation.
	hkBool m_permuteDetect;

};

#endif // HKOPTIMIZESHAPEOPTIONS__H

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
