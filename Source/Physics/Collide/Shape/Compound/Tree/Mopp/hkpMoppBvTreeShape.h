/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_COLLIDE2_MOPP_BV_TREE_SHAPE_H
#define HK_COLLIDE2_MOPP_BV_TREE_SHAPE_H

#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics/Internal/Collide/Mopp/Code/hkpMoppCode.h>

extern const hkClass hkpMoppBvTreeShapeClass;

class hkpMoppCode;

class hkMoppBvTreeShapeBase: public hkpBvTreeShape
{
	public:
		HK_DECLARE_REFLECTION();

		/// Constructs a new hkpMoppBvTreeShape. You can use the <hkpMoppUtility.h> to build a MOPP code.
		hkMoppBvTreeShapeBase( hkpShapeType type, const hkpMoppCode* code);

		inline hkMoppBvTreeShapeBase( hkFinishLoadedObjectFlag flag ):hkpBvTreeShape(flag) {}

		inline ~hkMoppBvTreeShapeBase()
		{
			m_code->removeReference();
		}

		// hkpBvTreeShape interface implementation.
		virtual void queryObb( const hkTransform& obbToMopp, const hkVector4& extent, hkReal tolerance, hkArray<hkpShapeKey>& hits ) const;

		// hkpBvTreeShape interface implementation.
		virtual void queryAabb( const hkAabb& aabb, hkArray<hkpShapeKey>& hits ) const;

		// hkpBvTreeShape interface implementation.
		virtual hkUint32 queryAabb( const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) const;

		virtual void calcStatistics( hkStatisticsCollector* collector) const = 0;

	public:

		const class hkpMoppCode*		m_code;
		const  hkUint8*				m_moppData;		//+nosave
		hkUint32					m_moppDataSize; //+nosave
		hkVector4					m_codeInfoCopy; //+nosave
};


	/// This class implements a hkpBvTreeShape using MOPP technology.
class hkpMoppBvTreeShape: public hkMoppBvTreeShapeBase
{
	public:

		HK_DECLARE_REFLECTION();

			/// Constructs a new hkpMoppBvTreeShape. You can use the <hkpMoppUtility.h> to build a MOPP code.
		hkpMoppBvTreeShape( const hkpShapeCollection* collection, const hkpMoppCode* code);

		inline hkpMoppBvTreeShape( hkFinishLoadedObjectFlag flag );

			// destructor
		virtual ~hkpMoppBvTreeShape();

		//
		// hkpShape implementation
		//
			// hkpShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(void) HK_GET_AABB_FUNCTION;

			//	hkpShape interface implementation.
		HK_SPU_VIRTUAL_DECLSPEC(hkBool) HK_RAYCAST_FUNCTION;

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerSimulationFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerCollideQueryFunctions( ShapeFuncs& sf );

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerGetAabbFunction( hkpShape::ShapeFuncs& sf );

			// hkpShape Interface implementation
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;
		
			/// Get the internal data used by the MOPP algorithms
		inline const hkpMoppCode* getMoppCode() const;

		inline void setMoppCode(const hkpMoppCode* code);

		virtual void calcStatistics( hkStatisticsCollector* collector) const;

		/// Gets the hkpShapeCollection.
		inline const hkpShapeCollection* getShapeCollection() const;

		inline virtual const hkpShapeContainer* getContainer() const;

		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;

		void getChildShapeFromPpu() const;

		HK_FORCE_INLINE const hkpShape* getChild() const;

	protected:

		class hkpSingleShapeContainer m_child;

	public:
		mutable int					m_childSize;	//+nosave


};

#include <Physics/Collide/Shape/Compound/Tree/Mopp/hkpMoppBvTreeShape.inl>

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
