/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>

const hkReal hkUFloat8_intToReal[hkUFloat8::MAX_VALUE] = 
{
	0.000f, 0.010f, 0.020f, 0.030f, 0.040f, 0.050f, 0.060f, 0.070f, 0.075f, 0.080f, 0.085f, 0.091f, 0.098f, 0.104f, 0.111f, 0.119f,
	0.127f, 0.136f, 0.145f, 0.155f, 0.166f, 0.177f, 0.190f, 0.203f, 0.217f, 0.231f, 0.247f, 0.264f, 0.282f, 0.302f, 0.323f, 0.345f,
	0.368f, 0.394f, 0.421f, 0.450f, 0.481f, 0.514f, 0.549f, 0.587f, 0.627f, 0.670f, 0.716f, 0.765f, 0.818f, 0.874f, 0.934f, 0.998f,
	1.067f, 1.140f, 1.218f, 1.302f, 1.391f, 1.487f, 1.589f, 1.698f, 1.815f, 1.939f, 2.072f, 2.215f, 2.367f, 2.529f, 2.703f, 2.889f,
	3.087f, 3.299f, 3.526f, 3.768f, 4.027f, 4.304f, 4.599f, 4.915f, 5.253f, 5.613f, 5.999f, 6.411f, 6.851f, 7.322f, 7.825f, 8.362f,
	8.937f, 9.551f, 10.21f, 10.91f, 11.66f, 12.46f, 13.31f, 14.23f, 15.20f, 16.25f, 17.37f, 18.56f, 19.83f, 21.20f, 22.65f, 24.21f,
	25.87f, 27.65f, 29.55f, 31.57f, 33.74f, 36.06f, 38.54f, 41.18f, 44.01f, 47.04f, 50.27f, 53.72f, 57.41f, 61.35f, 65.57f, 70.07f,
	74.88f, 80.03f, 85.52f, 91.40f, 97.68f, 104.4f, 111.6f, 119.2f, 127.4f, 136.2f, 145.5f, 155.5f, 166.2f, 177.6f, 189.8f, 202.8f,
	216.8f, 231.7f, 247.6f, 264.6f, 282.7f, 302.2f, 322.9f, 345.1f, 368.8f, 394.1f, 421.2f, 450.1f, 481.1f, 514.1f, 549.4f, 587.2f,
	627.5f, 670.6f, 716.6f, 765.9f, 818.5f, 874.7f, 934.8f, 999.0f, 1068.f, 1141.f, 1219.f, 1303.f, 1393.f, 1488.f, 1590.f, 1700.f,
	1816.f, 1941.f, 2074.f, 2217.f, 2369.f, 2532.f, 2706.f, 2892.f, 3090.f, 3303.f, 3530.f, 3772.f, 4031.f, 4308.f, 4604.f, 4920.f,
	5258.f, 5619.f, 6005.f, 6418.f, 6858.f, 7329.f, 7833.f, 8371.f, 8946.f, 9560.f, 10217.f, 10919.f, 11669.f, 12470.f, 13327.f, 14242.f,
	15220.f, 16266.f, 17383.f, 18577.f, 19853.f, 21217.f, 22674.f, 24231.f, 25896.f, 27674.f, 29575.f, 31607.f, 33778.f, 36098.f, 38577.f, 41227.f,
	44059.f, 47085.f, 50319.f, 53775.f, 57469.f, 61416.f, 65635.f, 70143.f, 74961.f, 80110.f, 85612.f, 91493.f, 97777.f, 104493.f, 111670.f, 119340.f,
	127538.f, 136298.f, 145660.f, 155664.f, 166356.f, 177783.f, 189994.f, 203044.f, 216991.f, 231895.f, 247823.f, 264846.f, 283037.f, 302478.f, 323254.f, 345457.f,
	369186.f, 394544.f, 421644.f, 450605.f, 481556.f, 514632.f, 549980.f, 587757.f, 628128.f, 671272.f, 717379.f, 766654.f, 819313.f, 875589.f, 935730.f, 1000002.f,
};

#if 0
	// this function built the above table
void hkUFloat8_buildTable()
{
	// the first 8 steps are used to evenly increase the value by eps
	int i;
	hkReal lastValue = 0.0f;
	for (i =0; i < 8; i++)
	{
		hkUFloat8_intToReal[i] = lastValue = i * hkUFloat8_eps;
	}

	// now we have to distribute the values evenly from i to max
	float numSteps = float( MAX_VALUE - i );
	float range = hkUFloat8_maxValue/lastValue;
	float factor = pow(range, 1.0f/numSteps);

	for ( ; i < MAX_VALUE; i++)
	{
		lastValue *= factor;
		hkUFloat8_intToReal[i] = lastValue;
	}

	{
		for (int f= 0;f < MAX_VALUE; f++)
		{
			float v = hkUFloat8_intToReal[f];
			if ( v < 10.0f )
			{
				hkprintf("%.3ff, ", v );
			}
			else if ( v < 100.0f )
			{
				hkprintf("%.2ff, ", v );
			}
			else if ( v < 1000.0f )
			{
				hkprintf("%.1ff, ", v );
			}
			else 
			{
				hkprintf("%.0f.f, ", v );
			}
			if ( (f & 15) == 15)hkprintf("\n");
		}
	}
}
#endif

const hkReal hkUInt8ToReal[256] =
{
	0,		1,		2,		3,		4,		5,		6,		7,		8,		9,		10,		11,		12,		13,		14,		15,
	16,		17,		18,		19,		20,		21,		22,		23,		24,		25,		26,		27,		28,		29,		30,		31,
	32,		33,		34,		35,		36,		37,		38,		39,		40,		41,		42,		43,		44,		45,		46,		47,
	48,		49,		50,		51,		52,		53,		54,		55,		56,		57,		58,		59,		60,		61,		62,		63,
	64,		65,		66,		67,		68,		69,		70,		71,		72,		73,		74,		75,		76,		77,		78,		79,
	80,		81,		82,		83,		84,		85,		86,		87,		88,		89,		90,		91,		92,		93,		94,		95,
	96,		97,		98,		99,		100,	101,	102,	103,	104,	105,	106,	107,	108,	109,	110,	111,
	112,	113,	114,	115,	116,	117,	118,	119,	120,	121,	122,	123,	124,	125,	126,	127,
	128,	129,	130,	131,	132,	133,	134,	135,	136,	137,	138,	139,	140,	141,	142,	143,
	144,	145,	146,	147,	148,	149,	150,	151,	152,	153,	154,	155,	156,	157,	158,	159,
	160,	161,	162,	163,	164,	165,	166,	167,	168,	169,	170,	171,	172,	173,	174,	175,
	176,	177,	178,	179,	180,	181,	182,	183,	184,	185,	186,	187,	188,	189,	190,	191,
	192,	193,	194,	195,	196,	197,	198,	199,	200,	201,	202,	203,	204,	205,	206,	207,
	208,	209,	210,	211,	212,	213,	214,	215,	216,	217,	218,	219,	220,	221,	222,	223,
	224,	225,	226,	227,	228,	229,	230,	231,	232,	233,	234,	235,	236,	237,	238,	239,
	240,	241,	242,	243,	244,	245,	246,	247,	248,	249,	250,	251,	252,	253,	254,	255
};


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
