/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>

#if defined( HK_PLATFORM_PSP )
#	if defined( HK_COMPILER_GCC )
#		include <Common/Base/Math/Types/Psp/hkPspGccMathTypesC.inl>
#	endif // HK_COMPILER_GCC
#endif // HK_PLATFORM_PSP


hkReal HK_CALL hkMath_atan2fApproximation( hkReal x, hkReal y )
{
	hkReal fx = hkMath::fabs(x);
	hkReal fy = hkMath::fabs(y);

	hkReal result;
	const hkReal c2 = -0.121079f;
	const hkReal c3 = HK_REAL_PI * 0.25f - 1.0f - c2;

	{
		if ( fx <= fy )
		{
			fy += HK_REAL_EPSILON;
			hkReal a = fx / fy;
			result = a;
			result += c2 * a*a;
			result += c3 * a*a*a;
		}
		else
		{
			fx += HK_REAL_EPSILON;
			hkReal a = fy / fx;
			result = a;
			result += c2 * a*a;
			result += c3 * a*a*a;
			result = HK_REAL_PI * 0.5f - result;
		}
	}

	if ( y < .0f)
	{
		result = HK_REAL_PI - result;
	}

	if ( x < .0f )
	{
		result = -result;
	}
	return result;
}

#if !defined(HK_PLATFORM_PS3SPU)

#if defined(HK_PLATFORM_PS3)
#	include <bits/f_ceilf.h>
#	include <bits/f_sinf.h>
#	include <bits/f_cosf.h>
#	include <bits/f_floorf.h>
#	define HK_FORWARD_MATH_CALL(from,to) hkReal hkMath::from(hkReal r) { return to(r); }
	HK_FORWARD_MATH_CALL(ceil,f_ceilf)
	HK_FORWARD_MATH_CALL(sin,f_sinf)
	HK_FORWARD_MATH_CALL(cos,f_cosf)
	HK_FORWARD_MATH_CALL(floor,f_floorf)
#	undef HK_FORWARD_MATH_CALL
#endif

hkReal HK_CALL hkMath::rand01()
{
	static unsigned seed = 'h'+'a'+'v'+'o'+'k';
	const unsigned a = 1103515245;
	const unsigned c = 12345;
	const unsigned m = unsigned(-1) >> 1;
	seed = (a * seed + c ) & m;
	return (hkReal(seed) / m);
}

union fi
{
	float f;
	int i;
	unsigned u;
};

#if !defined( HK_MATH_TYPES_hkFloor )

hkReal HK_CALL hkMath::hkFloor(hkReal r)
{
	//interpert as int
	fi convert;
	convert.f = r;

	//mask out the fractional part
	int fracMask = 0xff800000;

	//mask out the sign and mantissa
	unsigned exp = convert.u & 0x7f800000;

	//work out the exponent
	//
	//shift down to bottom of number
	exp >>= 0x017;
	//subtract bias of 127
	exp -= 0x07f;

	//rshift is used to shift the fracmask (down to the fractional part)
	int rshift = 0x17 - int(exp);

	//if the exponent is greater than 0x17 (23 bits), then we don't need a
	//frackmask (there is no fractional part, not enough bits to store it)
	//i.e. if rshift >= 0, then leave alone, otherwise set rshift to zero
	int sign = ~(rshift >> 0x01f);
	rshift &= sign;

	//if none of the bits are set in the original number (see ieee floating point
	//standard), then the number = 0
	//we mask out the sign bit, and check if anything is set
	//if it is, we must keep convert.i, otherwise we can set it to 0
	int nexp = (convert.i) & 0x7fffffff;
	nexp = (nexp - 1) >> 0x01f;
	//if the number had no bits, the sign is also destroyed
	convert.i &= ~nexp;

	//shift down to the fractional part
	//if the exponent had been >= 0x17 (23) then the sign destroys with an AND
	//and preserves with an OR (and vice versa). In the case of sign preserving
	//with AND, we end up with frackmask >> exp, else frackmask = 0xffffffff
	fracMask >>= (0x17 & sign) - rshift;
	fracMask |= ~sign;

	//find out whether the floating point is negative
	//sign -> 0xffffffff if neg. 0x00000000 otherwise
	sign = int(convert.u & 0x80000000);
	sign >>= 0x01f;

	int addMask = 0x00800000;

	//if the number is negative AND NOT whole
	//we increase it's magnitude, this is due
	//to the definition of floor
	addMask >>= int(exp);
	//if negative, do the addition (broadcast with sign)
	addMask &= sign;
	//check to see if there was anything in the fractional part
	addMask &= ~((convert.i & (~fracMask)) - 1);
	convert.i += addMask;

	convert.i &= fracMask;

	//if the exponent is negative AND the number is positive
	//then the number is less than 1.0f and floor sets it to 0.0f
	//if it is negative, it gets set to -1.0f
	nexp = int(exp);
	nexp = nexp >> 0x01f;
	//note: 0xbf800000 is -1.0f - which we need to assign in (easier than calculating)
	exp = (0xbf800000 & nexp) & sign;
	convert.i &= ~nexp;
	convert.u |= exp;

	return convert.f;
}

#endif // HK_MATH_HKFLOOR



#if !defined( HK_MATH_TYPES_hkFloorToInt )

int HK_CALL hkMath::hkFloorToInt(hkReal r)
{
	//interpert as int
	fi convert;
	convert.f = r;

	//mask out the fractional part
	int fracMask = 0xff800000;

	//mask out the sign and mantissa
	unsigned exp = convert.u & 0x7f800000;

	//work out the exponent
	//
	//shift down to bottom of number
	exp >>= 0x017;
	//subtract bias of 127
	exp -= 0x07f;

	//now split the exp into two shift magnitudes, a left
	//shift and a right shift, one of which must be 0
	int lshift = int(exp) - 0x17;
	int rshift = 0x17 - int(exp);

	//if lshift is <=0, then set to zero, otherwise set rshift to zero
	int sign = (lshift-1) >> 0x01f;
	lshift &= ~sign;
	rshift &= sign;

	//if none of the bits are set in the original number (see ieee floating point
	//standard), then the number = 0
	//we mask out the sign bit, and check if anything is set
	//if it is, we must keep convert.i, otherwise we can set it to 0
	int nexp = (convert.i) & 0x7fffffff;
	nexp = (nexp - 1) >> 0x01f;
	//if the number had no bits, the sign is also destroyed
	convert.i &= ~nexp;

	//move the fraction mask to the correct place
	fracMask >>= (0x17 & sign) - rshift;
	fracMask |= ~sign;

	//find out whether the floating point is negative
	//sign -> 0xffffffff if neg. 0x00000000 otherwise
	sign = int(convert.u & 0x80000000);
	sign >>= 0x01f;

	//floor increases the magnitude of negative numbers
	int addMask = 0x00800000;

	//if the number is negative AND NOT whole
	//we increase it's magnitude, this is due
	//to the definition of floor
	addMask >>= int(exp);
	addMask &= sign;
	addMask &= ~((convert.i & (~fracMask)) - 1);

	//if the exponent is negative AND the number is positive
	//then the number is less than 1.0f and floor sets it to 0.0f
	//if it is negative, it gets set to -1.0f (or at least what that
	//would be if we had gotten this far in the function)
	nexp = int(exp);
	nexp = nexp >> 0x01f;
	exp = unsigned((0x00800000 & nexp) & sign);
	convert.i &= ~nexp;

	convert.i += addMask;

	//get rid of the exponent and sign
	convert.i &= 0x007fffff;
	//insert the 1 that is assumed in the floating point standard
	//UNLESS the exponent is negative
	convert.i |= (0x00800000 & ~nexp);
	//if the exponent is negative AND the sign is negative
	//then it is set to -1, otherwise 0
	convert.u |= exp;

	//truncate
	convert.i &= fracMask;

	//if the sign is negative, convert to 2's complement
	//otherwise leave untouched (ie subtract x from 0 or
	//subtract from x from 2x -> -x or x)
	int temp = 0x0;
	temp = (convert.i << 0x01) - 1;
	temp |= sign;
	convert.i = (temp - convert.i) + 1;

	//shift mantissa to correct place
	convert.i >>= rshift;
	convert.i <<= lshift;

	return convert.i;
}

#endif // HK_MATH_FLOORTOINT



#if !defined( HK_MATH_TYPES_hkFloatToInt )

//performs a truncation
int HK_CALL hkMath::hkFloatToInt(hkReal r)
{
	//interpert as int
	fi convert;
	convert.f = r;

	//mask out the fractional part
	int fracMask = 0xff800000;

	//mask out the sign and mantissa
	unsigned int exp = convert.u & 0x7f800000;

	//work out the exponent
	//
	//shift down to bottom of number
	exp >>= 0x017;
	//subtract bias of 127
	exp -= 0x07f;

	//now split the exp into two shift magnitudes, a left
	//shift and a right shift, one of which must be 0
	int lshift = int(exp) - 0x17;
	int rshift = 0x17 - int(exp);

	//if lshift is <=0, then set to zero, otherwise set rshift to zero
	int sign = (lshift-1) >> 0x01f;
	lshift &= ~sign;
	rshift &= sign;

	//if none of the bits are set in the original number (see ieee floating point
	//standard), then the number = 0
	//we mask out the sign bit, and check if anything is set
	//if it is, we must keep convert.i, otherwise we can set it to 0
	int nexp = (convert.i) & 0x7fffffff;
	nexp = (nexp - 1) >> 0x01f;
	//if the number had no bits, the sign is also destroyed
	convert.i &= ~nexp;

	//shift down to the fractional part
	//if the exponent had been >= 0x17 (23) then the sign destroys with an AND
	//and preserves with an OR (and vice versa). In the case of sign preserving
	//with AND, we end up with frackmask >> exp, else frackmask = 0xffffffff
	fracMask >>= (0x17 & sign) - rshift;
	fracMask |= ~sign;

	//find out whether the floating point is negative
	//sign -> 0xffffffff if neg. 0x00000000 otherwise
	sign = int(convert.u & 0x80000000);
	sign >>= 0x01f;

	//get rid of the exponent and sign
	convert.i &= 0x007fffff;
	//insert the 1 that is assumed in the floating point standard
	convert.i |= 0x00800000;

	//truncate
	convert.i &= fracMask;

	//if the sign is negative, convert to 2's complement
	//otherwise leave untouched (ie subtract x from 0 or
	//subtract from x from 2x => -x or x)
	int temp = 0x0;
	temp = (convert.i << 0x01) - 1;
	temp |= sign;
	convert.i = (temp - convert.i) + 1;

	//if the exponent is negative, then the number is less than 1.0f
	//and float to int truncates that to 0
	nexp = int(exp);
	nexp = ~(nexp >> 0x1f);
	convert.i &= nexp;

	//shift mantissa to correct place (one of these will be zero)
	convert.i >>= rshift;
	convert.i <<= lshift;

	return convert.i;
}

#endif // HK_MATH_HKFLOATTOINT

#if defined(HK_PLATFORM_PS3) || defined(HK_PLATFORM_XBOX360)

#define X unsigned(-1)
#define Y unsigned(-1)
#define Z unsigned(-1)
#define W unsigned(-1)

#	if defined(HK_PLATFORM_XBOX360)
	typedef __vector4 MaskType;
	inline __vector4 QUAD(unsigned a, unsigned b, unsigned c, unsigned d)
	{
		__vector4 v;
		v.u[0] = a;
		v.u[1] = b;
		v.u[2] = c;
		v.u[3] = d;
		return v;
	}

	inline __vector4 INV_QUAD(unsigned a, unsigned b, unsigned c, unsigned d)
	{
		__vector4 v;
		v.u[0] = ~a;
		v.u[1] = ~b;
		v.u[2] = ~c;
		v.u[3] = ~d;
		return v;
	}
#elif defined(HK_PLATFORM_PS3)
	typedef vector unsigned int MaskType;
#	define QUAD(a,b,c,d) (vector unsigned int){ a, b, c, d}
#	define INV_QUAD(a,b,c,d) (vector unsigned int){~a,~b,~c,~d}
#endif

const MaskType hkVector4Comparison::s_maskFromBits[hkVector4Comparison::MASK_XYZW+1] =
{
	QUAD(0,0,0,0),
	QUAD(0,0,0,W),
	QUAD(0,0,Z,0),
	QUAD(0,0,Z,W),

	QUAD(0,Y,0,0),
	QUAD(0,Y,0,W),
	QUAD(0,Y,Z,0),
	QUAD(0,Y,Z,W),

	QUAD(X,0,0,0),
	QUAD(X,0,0,W),
	QUAD(X,0,Z,0),
	QUAD(X,0,Z,W),

	QUAD(X,Y,0,0),
	QUAD(X,Y,0,W),
	QUAD(X,Y,Z,0),
	QUAD(X,Y,Z,W)
};

const MaskType hkVector4Comparison::s_invMaskFromBits[hkVector4Comparison::MASK_XYZW+1] =
{
	INV_QUAD(0,0,0,0),
	INV_QUAD(0,0,0,W),
	INV_QUAD(0,0,Z,0),
	INV_QUAD(0,0,Z,W),

	INV_QUAD(0,Y,0,0),
	INV_QUAD(0,Y,0,W),
	INV_QUAD(0,Y,Z,0),
	INV_QUAD(0,Y,Z,W),

	INV_QUAD(X,0,0,0),
	INV_QUAD(X,0,0,W),
	INV_QUAD(X,0,Z,0),
	INV_QUAD(X,0,Z,W),

	INV_QUAD(X,Y,0,0),
	INV_QUAD(X,Y,0,W),
	INV_QUAD(X,Y,Z,0),
	INV_QUAD(X,Y,Z,W)
};

#endif // andbits

// sanity check masks
HK_COMPILE_TIME_ASSERT( hkVector4Comparison::MASK_NONE == 0);
#define SAME2(A,B) ((hkVector4Comparison::MASK_##A | hkVector4Comparison::MASK_##B) == hkVector4Comparison::MASK_##A##B)
HK_COMPILE_TIME_ASSERT( SAME2(X,Y) );
HK_COMPILE_TIME_ASSERT( SAME2(X,Z) );
HK_COMPILE_TIME_ASSERT( SAME2(X,W) );
HK_COMPILE_TIME_ASSERT( SAME2(Y,Z) );
HK_COMPILE_TIME_ASSERT( SAME2(Y,W) );
HK_COMPILE_TIME_ASSERT( SAME2(Z,W) );

#endif // !defined HK_PLATFORM_PS3SPU

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
