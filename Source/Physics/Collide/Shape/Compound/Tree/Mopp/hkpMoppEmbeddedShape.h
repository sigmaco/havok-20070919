/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_MOPP_EMBEDDED_SHAPE_H
#define HK_COLLIDE2_MOPP_EMBEDDED_SHAPE_H

#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Physics/Internal/Collide/Mopp/Code/hkpMoppCode.h>
#include <Physics/Collide/Shape/Compound/Collection/Mesh/hkpMeshMaterial.h>
#include <Physics/Collide/Util/Welding/hkpWeldingUtility.h>
#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.h>

	/// These shapes are embedded directly in the MOPP code.
	/// Since the shapes are embedded in the mopp this also acts as a shape container
class hkpMoppEmbeddedShape:  public hkMoppBvTreeShapeBase, public hkpShapeContainer 
{
	public:

		HK_DECLARE_REFLECTION();
		//HK_DECLARE_GET_SIZE_FOR_SPU(hkpMoppEmbeddedShape);

			/// Constructs a new hkpMoppEmbeddedShape. You can use the <hkpMoppUtility.h> to build a MOPP code.
			/// The code will have to have been built with embedded shapes.
			/// The reindexedTerminals are optional. A copy of the array is stored with this shape
			/// to allow you too lookup the original key for a given chunk
		hkpMoppEmbeddedShape( const hkpMoppCode* codeWithEmbeddedShapes, hkArray<hkpMoppCodeReindexedTerminal>* reindexedTerminals = HK_NULL);

		hkpMoppEmbeddedShape( hkFinishLoadedObjectFlag flag );

			// destructor
		virtual ~hkpMoppEmbeddedShape();

			// Alternate construction method
		void initialize( const hkpMoppCode::CodeInfo& info, const hkUint8* codeData, hkUint32 codeDataSize  );

			/// Compute welding info. If welding info has not already been computed for the mopp code then
			/// this routine will go and recompute it and embed it directly in the code.
			/// This is an expensive call, and should be done off line
		void computeWeldingInfo( hkpWeldingUtility::WeldingType weldingType );

		HK_FORCE_INLINE const hkpMoppCode* getMoppCode() const { return m_code; }

			/// call this whenever your underlying mesh increases its AABB
		void recalcAabbExtents();

		//
		// hkpShape implementation
		//
			// hkpShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_AABB_FUNCTION;

			//	hkpShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(hkBool) HK_RAYCAST_FUNCTION;
		
		virtual void calcStatistics( hkStatisticsCollector* collector) const;

		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;

		// hkpShape function implementations
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

		/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerSimulationFunctions( ShapeFuncs& sf );

		/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerCollideQueryFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerGetAabbFunction( ShapeFuncs& sf );

		inline virtual const hkpShapeContainer* getContainer() const
		{
			return this;
		}

		//
		// hkpShape Container implementation
		//

		virtual int getNumChildShapes() const;

		virtual hkpShapeKey getFirstKey() const ;

		virtual hkpShapeKey getNextKey( hkpShapeKey oldKey ) const ;

		HK_SPU_VIRTUAL_DECLSPEC(const hkpShape*)	HK_GET_CHILD_SHAPE_FUNCTION;

		HK_SPU_VIRTUAL_DECLSPEC(hkUint32) HK_GET_COLLISION_FILTER_INFO_FUNCTION;

			/// returns the original shape key / terminal ID 
		hkpShapeKey getOriginalKey( hkpShapeKey key ) const;

			/// Sets the triangle extrusion shared by all triangles in the shape
		HK_FORCE_INLINE void setTriangleExtrusion(const hkVector4& extrusion) { m_triangleExtrusion = extrusion; recalcAabbExtents(); }

	protected:

		hkVector4					m_aabbHalfExtents;
		hkVector4					m_aabbCenter;
		hkVector4					m_triangleExtrusion;

	public:

			/// the radius for all convex children
		hkReal	m_childRadius;

			/// The welding type for this mesh
		hkEnum<hkpWeldingUtility::WeldingType, hkUint8> m_weldingType; // +default(hkpWeldingUtility::WELDING_TYPE_NONE)

			/// The base for the material table, the byte offset between two hkMeshMaterials is defined by
			/// m_materialStriding. If you are storing your materials externally and not using per-triangle filtering
			/// set this element to HK_NULL. The material array may be shared between meshes.
		const hkpMeshMaterial* m_materialBase; //+nosave

			/// The byte offset between two hkMeshMaterials
		int	m_materialStriding;		

			/// The number of materials
		int	m_numMaterials;

	protected:

		hkArray<struct hkpMoppCodeReindexedTerminal> m_reindexedTerminals;


};


#endif // HK_COLLIDE2_MOPP_BV_TREE_SHAPE_H

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
