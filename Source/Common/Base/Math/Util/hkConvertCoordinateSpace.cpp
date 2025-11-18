/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Util/hkConvertCoordinateSpace.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>


hkConvertCS::hkConvertCS (ConversionType type)
{
	setConversionType(type);
}

void hkConvertCS::setConversionType (ConversionType type)
{
	hkRotation rotation;
	rotation.setIdentity();

	switch (type)
	{
	case CT_IDENTITY:
		{
			// Do nothing
			break;
		}
	case CT_FLIP_X:
		{
			rotation(0,0) = -1.0f;
			break;
		}
	case CT_FLIP_Y:
		{
			rotation(1,1) = -1.0f;
			break;
		}
	case CT_FLIP_Z:
		{
			rotation(2,2) = -1.0f;
			break;
		}
	case CT_SWITCH_YZ:
		{
			hkVector4 c0; c0.set(1,0,0,0); 
			hkVector4 c1; c1.set(0,0,1,0); 
			hkVector4 c2; c2.set(0,1,0,0);
			rotation.setCols(c0,c1,c2);
			break;
		}
	default:
		HK_ASSERT2(0x74224073, 0, "Unknown Coordinate System Conversion Type");
		return;
	}	

	setConversionRotation(rotation);
}

void hkConvertCS::setConversionRotation (const hkRotation& rotation)
{
	m_conversionRotation = rotation;

	// We calculate the determinant
	hkVector4 r0;
	r0.setCross(rotation.getColumn(1), rotation.getColumn(2));
	hkReal determinant = rotation.getColumn(0).dot3(r0);

	HK_ASSERT2(0x2e6d8741, hkMath::fabs(hkMath::fabs(determinant) -1) < 1e-2f, "Matrix (rotation) for conversion has scale!");

	// If determinant is (close to) -1, we are doing a handness conversion
	m_flipping = ( hkMath::fabs(determinant + 1) < 1e-2f );
	
}

void hkConvertCS::convertVector (hkVector4& vectorInOut) const
{
	vectorInOut.setRotatedDir(m_conversionRotation, vectorInOut);
}

void hkConvertCS::convertQuaternion (hkQuaternion& quaternionInOut) const
{
	// First we transform the axis of rotation
	hkVector4 imag;
	imag = quaternionInOut.getImag();
	imag.setRotatedDir(m_conversionRotation, imag);
	quaternionInOut.setImag(imag);

	// Second, if the transformation is a "flipping" one (one that changes handeness) we also flip the sign
	if (m_flipping)
	{
		quaternionInOut.setReal(-quaternionInOut.getReal());
	}

}

void hkConvertCS::convertRotation (hkRotation& rotationInOut) const
{
	rotationInOut.changeBasis(m_conversionRotation);
}

void hkConvertCS::convertTransform (hkTransform& transformInOut) const
{
	convertRotation(transformInOut.getRotation());
	convertVector(transformInOut.getTranslation());
}


void hkConvertCS::convertRotationAngle (hkReal& angle) const
{
	if (m_flipping)
	{
		angle = -angle;
	}
}

void hkConvertCS::convertMinMaxAngles (hkReal& minAngle, hkReal& maxAngle) const
{
	convertRotationAngle(minAngle);
	convertRotationAngle(maxAngle);
	if (minAngle>maxAngle)
	{
		hkAlgorithm::swap(minAngle, maxAngle);
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
