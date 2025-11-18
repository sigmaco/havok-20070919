/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SHAPE_RAY_CAST_RESULTS
#define HK_SHAPE_RAY_CAST_RESULTS

#include <Physics/Collide/Shape/Query/hkpShapeRayCastCollectorOutput.h>

#if defined(HK_PLATFORM_SPU)
#	define hkpShapeRayCastCollectorOutput hkpShapeRayCastCollectorOutputPpu
#	define hkpShapeRayCastOutput hkpShapeRayCastOutputPpu
#endif

	/// The structure used for hkpShape::castRay results.
	/// Note: the structure can be used only for one raycast,
	/// If you want to reuse it, you have to call reset()
struct hkpShapeRayCastOutput : public hkpShapeRayCastCollectorOutput
{
#if !defined(HK_PLATFORM_SPU)

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShapeRayCastOutput );

		/// Create an initialized output.
	inline hkpShapeRayCastOutput();

#endif

		/// Resets this structure if you want to reuse it for another raycast, by setting the hitFraction to 1
	inline void reset();

		/// Maximum depth of key hierarchy.
	enum { MAX_HIERARCHY_DEPTH=8 };

		/// The shapekeys of all the intermediate shapes down to the leaf shape which has been hit.
		/// The list ends with HK_INVALID_SHAPE_KEY. See the "Raycast Hit Hierarchy" section of the user guide.
	hkpShapeKey m_shapeKeys[MAX_HIERARCHY_DEPTH];

#if !defined(HK_PLATFORM_SPU)

		// Internal. Used for shapes containing child shapes.
	inline void changeLevel(int delta);

		// Internal. Used with changeLevel().
	inline void setKey(hkpShapeKey key);

#endif

private:

	inline void _reset();

private:

	int m_shapeKeyIndex;

};


#if !defined(HK_PLATFORM_SPU)
	typedef hkpShapeRayCastOutput hkpShapeRayCastOutputPpu;
#	include <Physics/Collide/Shape/Query/hkpShapeRayCastOutput.inl>
#else
#	undef hkpShapeRayCastOutput
#	undef hkpShapeRayCastCollectorOutput
#	include <Physics/Collide/Shape/Query/hkpShapeRayCastOutputSpu.h>
#endif


#endif //HK_SHAPE_RAY_CAST_RESULTS

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
