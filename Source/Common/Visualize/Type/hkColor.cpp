/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/Type/hkColor.h>

int HK_CALL hkColor::rgbFromChars(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	unsigned color =  (unsigned(alpha) * (256 * 256 * 256)) 
					+ (unsigned(red) * (256 * 256))
					+ (unsigned(green) * 256)
					+ unsigned(blue);
	return int(color);
}

int HK_CALL hkColor::rgbFromFloats(const hkReal red, const hkReal green, const hkReal blue, const hkReal alpha)
{
	HK_ASSERT2(0x5d228af1,  (alpha >= 0.0f) && (alpha <= 1.0f), "Color component is out of range!" );
	HK_ASSERT2(0x293c6824,  (red >= 0.0f) && (red <= 1.0f), "Color component is out of range!" );
	HK_ASSERT2(0x3df5f1a3,  (green >= 0.0f) && (green <= 1.0f), "Color component is out of range!" );
	HK_ASSERT2(0x293ff0fe,  (blue >= 0.0f) && (blue <= 1.0f), "Color component is out of range!" );

	unsigned char cAlpha = (unsigned char)(hkMath::hkFloatToInt(alpha * 255));
	unsigned char cRed   = (unsigned char)(hkMath::hkFloatToInt(red * 255));
	unsigned char cGreen = (unsigned char)(hkMath::hkFloatToInt(green * 255));
	unsigned char cBlue	 = (unsigned char)(hkMath::hkFloatToInt(blue * 255));

	return rgbFromChars(cRed, cGreen, cBlue, cAlpha);
}


int HK_CALL hkColor::getRandomColor()
{
		float r = hkMath::randRange(0.0f, 1.0f);
		float g = hkMath::randRange(0.0f, 1.0f);
		float b = hkMath::randRange(0.0f, 1.0f);
		float a = 1.0f;

		return rgbFromFloats(r,g,b,a);
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
