/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Util/hkMathUtil.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

void hkQsTransform::fastRenormalizeBatch( hkQsTransform* poseOut, hkReal* weight, hkUint32 numTransforms)
{
	for (unsigned i=0; i < numTransforms; i++)
	{
		const hkSimdReal invWeight = HK_SIMD_REAL(1.0f) / (hkSimdReal) weight[i];
		poseOut[i].m_translation.mul4(invWeight);
		poseOut[i].m_scale.mul4(invWeight);
	}

	// now normalize 4 quaternions at once
	hkQsTransform* blockStart = poseOut;
	unsigned numTransformsOver4 = numTransforms/4;
	for (unsigned i=0; i< numTransformsOver4; i++)
	{
		hkVector4 dots;
		hkVector4Util::dot4_4vs4(blockStart[0].m_rotation.m_vec, blockStart[0].m_rotation.m_vec,
			blockStart[1].m_rotation.m_vec, blockStart[1].m_rotation.m_vec,
			blockStart[2].m_rotation.m_vec, blockStart[2].m_rotation.m_vec,
			blockStart[3].m_rotation.m_vec, blockStart[3].m_rotation.m_vec,
			dots);
		hkVector4 inverseSqrtDots;
		inverseSqrtDots.setSqrtInverse4(dots);

		blockStart[0].m_rotation.m_vec.mul4(inverseSqrtDots.getSimdAt(0));
		blockStart[1].m_rotation.m_vec.mul4(inverseSqrtDots.getSimdAt(1));
		blockStart[2].m_rotation.m_vec.mul4(inverseSqrtDots.getSimdAt(2));
		blockStart[3].m_rotation.m_vec.mul4(inverseSqrtDots.getSimdAt(3));

		blockStart += 4;
	}

	unsigned leftovers = numTransforms%4;
	for (unsigned j=0; j<leftovers; j++)
	{
		blockStart[j].m_rotation.normalize();
	}

}

void hkQsTransform::setInverse( const hkQsTransform& t )
{
	// We are not "reference-safe" because quaternion inversion is not reference-safe
	HK_ASSERT2(0x1acceb8d, (&t != this) , "Using unsafe references in math operation");

	m_translation.setRotatedInverseDir(t.m_rotation, t.m_translation);
	m_translation.mul4(-1.0f);
	m_rotation.setInverse(t.m_rotation);

	hkVector4 invScale; invScale.setReciprocal3( t.m_scale );
	m_scale.setXYZ0( invScale );
}

#if !defined (HK_PLATFORM_SPU)

void hkQsTransform::get4x4ColumnMajor(hkReal* d) const
{

	// Calculate the 3x3 matrices for rotation and scale
	hkRotation rotMatrix; rotMatrix.set (m_rotation);
	hkRotation scaMatrix;
	scaMatrix.setZero();
	scaMatrix.setDiagonal(m_scale(0), m_scale(1), m_scale(2));

	// Calculate R*S
	hkRotation rotSca;
	rotSca.setMul(rotMatrix, scaMatrix);

	// Construct hkTransform
	hkTransform temp(rotSca, m_translation);

	// Use hkTransform implementation
	temp.get4x4ColumnMajor(d);

}

hkBool hkQsTransform::set4x4ColumnMajor(const hkReal* p)
{
	hkMathUtil::Decomposition decomposition;
	hkMathUtil::decompose4x4ColTransform(p, decomposition);

	set(decomposition.m_translation, decomposition.m_rotation, decomposition.m_scale);

	return !decomposition.m_hasSkew;

}


void hkQsTransform::setFromTransformNoScale (const hkTransform& transform)
{
	m_rotation.set(transform.getRotation());
	m_translation = transform.getTranslation();
	m_scale.setAll(1.0f);
}

void hkQsTransform::copyToTransformNoScale (hkTransform& transformOut) const
{
	transformOut.set(m_rotation, m_translation);
}

void hkQsTransform::setFromTransform (const hkTransform& transform)
{
	hkReal buffer[16];
	transform.get4x4ColumnMajor(buffer);
	set4x4ColumnMajor(buffer);
}

void hkQsTransform::copyToTransform (hkTransform& transformOut) const
{
	hkReal buffer[16];
	get4x4ColumnMajor(buffer);
	transformOut.set4x4ColumnMajor(buffer);
}




hkBool hkQsTransform::isOk() const
{
	const hkReal* r = reinterpret_cast<const hkReal*>(this);
	for(int i=0; i<12; ++i)
	{
		// Do not care about the w components of translation and scale
		if ((i==3) || (i==11)) continue;

		if( hkMath::isFinite(r[i]) == false )
		{
			return false;
		}
	}
	return true;
}

hkBool hkQsTransform::isApproximatelyEqual( const hkQsTransform& other, hkReal epsilon ) const
{

	if ( ! m_translation.equals3( other.m_translation, epsilon ) ) 
	{
		return false;
	}

	if ( ! m_scale.equals3(other.m_scale, epsilon) )
	{
		return false;
	}

	// Quaternions are sligtly trickier to compare due to the duplicity (-axis,angle) <=> (axis,-angle)

	hkVector4 toCompareThis = m_rotation.m_vec;
	hkVector4 toCompareOther = other.m_rotation.m_vec;

	// Make sure they both have a positive w component

	if (toCompareThis(3) * toCompareOther(3) < 0)
	{
		toCompareThis.mul4(-1.0f);
	}

	return toCompareThis.equals4(toCompareOther, epsilon) != false;
}


HK_ALIGN16( hkReal hkQsTransformIdentity[] ) =
{
		0,0,0,0, // position
		0,0,0,1, // rotation
		1,1,1,0, // scale
};

#endif //!defined(HK_PLATFORM_SPU)

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
