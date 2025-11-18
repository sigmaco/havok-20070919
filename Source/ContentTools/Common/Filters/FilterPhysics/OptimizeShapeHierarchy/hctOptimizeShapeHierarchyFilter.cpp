/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/FilterPhysics/hctFilterPhysics.h>
#include <ContentTools/Common/Filters/FilterPhysics/OptimizeShapeHierarchy/hctOptimizeShapeHierarchyFilter.h>

//utilities
#include <Physics/Utilities/Collide/ShapeUtils/CollapseTransform/hkpTransformCollapseUtil.h>
#include <Physics/Utilities/Collide/ShapeUtils/ShapeSharing/hkpShapeSharingUtil.h>


// The only instance of our filter descriptor
hctOptimizeShapeHierarchyFilterDesc g_optimizeShapeHierarchyDesc;

hctOptimizeShapeHierarchyFilter::hctOptimizeShapeHierarchyFilter(const hctFilterManagerInterface* owner)
:	hctFilterInterface (owner)
{
	m_options.m_shareShapes = true;
	m_options.m_collapseTransforms = true;
	m_options.m_permuteDetect = true;
	m_options.m_propagate = true;
	m_options.m_shareTolerance = 1e-6f;
	m_options.m_collapseThreshold = 0;
	m_options.m_collapseBehaviourType = hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_ALWAYS;
	m_optionsDialog = HK_NULL;
} 

hctOptimizeShapeHierarchyFilter::~hctOptimizeShapeHierarchyFilter()
{
}

void hctOptimizeShapeHierarchyFilter::process( hkRootLevelContainer& data, bool batchMode )
{
	// Find an hkxScene and a hkPhysics Data object in the root level container
	hkxScene* scenePtr = reinterpret_cast<hkxScene*>( data.findObjectByType( hkxSceneClass.getName() ) );
	if (scenePtr == HK_NULL || (scenePtr->m_rootNode == HK_NULL) )
	{
		HK_WARN_ALWAYS(0xabbaa5f0, "No scene data (or scene data root hkxNode) found. Can't continue.");
		return;
	}
	hkpPhysicsData* physicsPtr = reinterpret_cast<hkpPhysicsData*>( data.findObjectByType( hkpPhysicsDataClass.getName() ) );
	if (physicsPtr == HK_NULL)
	{
		HK_WARN_ALWAYS(0xabbaa3d0, "No physics data found, you need to use Create Rigid Bodies before this filter or have bodies already in the input data.");
		return;
	}

	// Search for rigid bodies in the scene
	hkArray<hkpRigidBody*> rigidbodies;
	for (int psi=0; psi<physicsPtr->getPhysicsSystems().getSize(); psi++)
	{
		const hkpPhysicsSystem* psystem = physicsPtr->getPhysicsSystems()[psi];

		for (int rbi=0; rbi<psystem->getRigidBodies().getSize(); rbi++)
		{
			hkpRigidBody* rbody = psystem->getRigidBodies()[rbi];
			rigidbodies.pushBack(rbody);
		}
	}

	// Give a warning if the filter didn't do anything useful
	if (rigidbodies.getSize()==0)
	{
		HK_WARN_ALWAYS(0xabba7632, "No rigid bodies processed.");
	}
	else
	{
		HK_REPORT("Processing "<<rigidbodies.getSize()<<" rigid bodies...");

		//identify-shared-shapes step
		if (m_options.m_shareShapes)
		{
			hkpShapeSharingUtil::Options shapeSharingUtilOptions;
			hkpShapeSharingUtil::Results shapeSharingUtilResults;
			
			shapeSharingUtilOptions.m_detectPermutedComponents = m_options.m_permuteDetect;
			shapeSharingUtilOptions.m_equalityThreshold = m_options.m_shareTolerance;
			
			hkpShapeSharingUtil::shareShapes(rigidbodies, shapeSharingUtilOptions, shapeSharingUtilResults);
			shapeSharingUtilResults.report();
		}
		
		//collapse-transforms step
		if (m_options.m_collapseTransforms)
		{
			hkpTransformCollapseUtil::Options transformCollapseOptions;
	
			transformCollapseOptions.m_propageTransformInList = m_options.m_propagate;

			switch (m_options.m_collapseBehaviourType)
			{
				case hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_ALWAYS:
					transformCollapseOptions.m_sharedShapeBehaviour = hkpTransformCollapseUtil::ALWAYS_COLLAPSE;
					break;

				case hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_NEVER:
					transformCollapseOptions.m_sharedShapeBehaviour = hkpTransformCollapseUtil::NEVER_COLLAPSE;
					break;

				case hctOptimizeShapeHierarchyOptions::COLLAPSE_OPTIONS_THRESHOLD:
					transformCollapseOptions.m_sharedShapeBehaviour = hkpTransformCollapseUtil::COLLAPSE_IF_LESS_THAN_THRESHOLD;
					transformCollapseOptions.m_sharedShapeThreshold = m_options.m_collapseThreshold;
					break;
			}

			hkpTransformCollapseUtil::Results transformCollapseResults;
			hkpTransformCollapseUtil::collapseTransforms(rigidbodies, transformCollapseOptions, transformCollapseResults);
			transformCollapseResults.report();

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
