/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */


#define HK_VECTOR4_setCross
inline void hkVector4::setCross(const hkVector4& v1, const hkVector4& v2)
{
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c010, %1			\n"
		"lv.q		c020, %2			\n"	
		"vcrsp.t	c000, c010, c020	\n"
		"sv.q		c000, %0			\n"
		".set		pop					\n"				// restore assembler options
		: "=m" (*this)
		: "m" (v1), "m" (v2)
		);	
}

#define HK_VECTOR4_setMin4
inline void hkVector4::setMin4(const hkVector4& a, const hkVector4& b)
{
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c010, %1			\n"
		"lv.q		c020, %2			\n"	
		"vmin.q		c000, c010, c020	\n"
		"sv.q		c000, %0			\n"
		".set		pop					\n"				// restore assembler options
		: "=m" (*this)
		: "m" (a), "m" (b)
		);	
}

#define HK_VECTOR4_setMax4
inline void hkVector4::setMax4(const hkVector4& a, const hkVector4& b)
{
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c010, %1			\n"
		"lv.q		c020, %2			\n"	
		"vmax.q		c000, c010, c020	\n"
		"sv.q		c000, %0			\n"
		".set		pop					\n"				// restore assembler options
		: "=m" (*this)
		: "m" (a), "m" (b)
		);		
}

//#define HK_VECTOR4__setMul3
//inline void hkVector4::_setMul3( const hkMatrix3& r, const hkVector4& v )
//{
//	__asm__ (
//		".set		push				\n"				// save assembler options
//		".set		noreorder			\n"				// suppress reordering
//		"lv.q		c030, %2			\n"				// vector loaded
//		"lv.q		c000,  0 + %1		\n"
//		"lv.q		c010, 16 + %1		\n"
//		"lv.q		c020, 32 + %1		\n"				// matrix loaded
//		"vtfm3.t	c130, e000, c030	\n"
//		"vzero.s	s133				\n"				// this(3) = 0
//		"sv.q		c130, %0			\n"
//		".set		pop					\n"				// restore assembler options
//		: "=m" (*this)
//		: "m" (r), "m" (v) 
//		);			
//}

#define HK_VECTOR4__setMul4
inline void hkVector4::_setMul4( const hkMatrix3& t, const hkVector4& v )
{
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c030, %2			\n"				// vector loaded
		"vzero.s	s033				\n"				// v(3) = 0
		"lv.q		c000,  0 + %1		\n"
		"lv.q		c010, 16 + %1		\n"
		"lv.q		c020, 32 + %1		\n"				// matrix loaded
		"vtfm4.q	c130, e000, c030	\n"
		"sv.q		c130, %0			\n"
		".set		pop					\n"				// restore assembler options
		: "=m" (*this)
		: "m" (t), "m" (v)
		);				
}

#define HK_VECTOR4__setMul4xyz1
inline void hkVector4::_setMul4xyz1( const hkTransform& t, const hkVector4& v )
{
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c130, %2			\n"				// vector loaded
		"lv.q		c000,  0 + %1		\n"
		"lv.q		c010, 16 + %1		\n"
		"lv.q		c020, 32 + %1		\n"	
		"lv.q		c030, 48 + %1		\n"				// matrix loaded
		"vone.s		s133				\n"				// v(3) = 1
		"vtfm4.q	c120, e000, c130	\n"
		"sv.q		c120, %0			\n"
		".set		pop					\n"				// restore assembler options
		: "=m" (*this)
		: "m" (t), "m" (v)
		);				
}
#define HK_VECTOR4__setRotatedInverseDir
inline void hkVector4::_setRotatedInverseDir(const hkRotation& r, const hkVector4& v)
{
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c000,  0 + %1		\n"
		"lv.q		c010, 16 + %1		\n"
		"lv.q		c020, 32 + %1		\n"				// matrix loaded
		"lv.q		c030, %2			\n"				// vector loaded
		"vtfm3.t	c130, m000, c030	\n"
		"vzero.s	s133				\n"				// this(3) = 0
		"sv.q		c130, %0			\n"
		".set		pop					\n"				// restore assembler options
		: "=m" (*this)
		: "m" (r), "m" (v)
		);					
}

//#define HK_VECTOR4__setTransformedPos
//inline void hkVector4::_setTransformedPos(const hkTransform& t, const hkVector4& v)
//{
//	// call assembly code above	
//	_setMul4xyz1( t, v );
//}

//#define HK_VECTOR4__setTransformedInversePos
//inline void hkVector4::_setTransformedInversePos(const hkTransform& t, const hkVector4& v)
//{	
//	__asm__ (
//		".set		push				\n"				// save assembler options
//		".set		noreorder			\n"				// suppress reordering
//		"lv.q		c030, 48 + %1		\n"				// matrix loaded
//		"lv.q		c130, %2			\n"				// vector loaded
//		"vsub.q		c130, c130, c030	\n"				// v - t
//		"lv.q		c000,  0 + %1		\n"
//		"lv.q		c010, 16 + %1		\n"
//		"lv.q		c020, 32 + %1		\n"	
//		"vtfm3.t	c120, m000, c130	\n"
//		"vzero.s	s123				\n"
//		"sv.q		c120, %0			\n"
//		".set		pop					\n"				// restore assembler options
//		: "=m" (*this)
//		: "m" (t), "m" (v)
//		);					
//}


//#define HK_VECTOR4_length3
//	inline hkSimdReal hkVector4::length3() const
//	{
//		hkReal result;
//		
//		__asm__ (
//			".set		push				\n"				// save assembler options
//			".set		noreorder			\n"				// suppress reordering
//			"lv.q		c000, %1			\n"
//			"vdot.t		s010, c000, c000	\n"
//			"vsqrt.s	s020, s010			\n"
//			"sv.s		s020, 0 + %0		\n"
//			".set		pop					\n"				// restore assembler options
//			: "=m" (result)
//			: "m" (*this)
//			);		
//		
//		return result;	
//	}

//#define HK_VECTOR4_lengthInverse3
//inline hkSimdReal hkVector4::lengthInverse3() const
//{
//	hkReal result;
//	__asm__ (
//		".set		push				\n"				// save assembler options
//		".set		noreorder			\n"				// suppress reordering
//		"lv.q		c000, %1			\n"
//		"vdot.t		s010, c000, c000	\n"
//		"vrsq.s		s020, s010			\n"
//		"sv.s		s020, 0 + %0		\n"	
//		".set		pop					\n"				// restore assembler options
//		: "=m" (result)
//		: "m" (*this)
//		);		
//	return result;	
//}



// define this method to override the default
//#define HK_VECTOR4_length4
//inline hkSimdReal hkVector4::length4() const
//{
//	hkReal result;
//	
//	__asm__ (
//		".set		push				\n"				// save assembler options
//		".set		noreorder			\n"				// suppress reordering
//		"lv.q		c000, %1			\n"
//		"vdot.q		s010, c000, c000	\n"
//		"vsqrt.s	s020, s010			\n"
//		"sv.s		s020, 0 + %0		\n"	
//		".set		pop					\n"				// restore assembler options
//		: "=m" (result)
//		: "m" (*this)
//		);		
//	return result;
//}

//#define HK_VECTOR4_lengthInverse4
//inline hkSimdReal hkVector4::lengthInverse4() const
//{
//	hkReal result;
//	
//	__asm__ (
//		".set		push				\n"				// save assembler options
//		".set		noreorder			\n"				// suppress reordering
//		"lv.q		c000, %1			\n"
//		"vdot.q		s010, c000, c000	\n"
//		"vrsq.s		s020, s010			\n"
//		"sv.s		s020, 0 + %0		\n"	
//		".set		pop					\n"				// restore assembler options
//		: "=m" (result)
//		: "m" (*this)
//		);		
//	return result;	
//}

#define HK_VECTOR4_normalize3
inline void hkVector4::normalize3()
{
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c000, %1			\n"
		"vdot.t		s010, c000, c000	\n"
		"vrsq.s		s020, s010			\n"
		"vscl.q		c000, c000, s020	\n"
		"sv.q		c000, %0			\n"
		".set		pop					\n"				// restore assembler options
		: "=m" (*this)
		: "m" (*this)
		);
}

#define HK_VECTOR4_normalizeWithLength3
inline hkSimdReal hkVector4::normalizeWithLength3()
{
	hkReal result;
	
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c000, %2			\n"
		"vdot.t		s010, c000, c000	\n"
		"vrsq.s		s020, s010			\n"
		"vscl.q		c000, c000, s020	\n"
		"vsqrt.s	s030, s010			\n"
		"sv.q		c000, %0			\n"
		"sv.s		s030, 0 + %1		\n"	
		".set		pop					\n"				// restore assembler options
		: "=m"(*this), "=m" (result)
		: "m" (*this)
		);				
	return result;
}

#define HK_VECTOR4_normalize4
inline void hkVector4::normalize4()
{	
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c000, %1			\n"
		"vdot.q		s010, c000, c000	\n"
		"vrsq.s		s020, s010			\n"
		"vscl.q		c000, c000, s020	\n"
		"sv.q		c000, %0			\n"
		".set		pop					\n"				// restore assembler options
		: "=m"(*this)
		: "m"(*this)
		);				
}

#define HK_VECTOR4_normalizeWithLength4
inline hkSimdReal hkVector4::normalizeWithLength4()
{
	hkReal result;
	__asm__ (
		".set		push				\n"				// save assembler options
		".set		noreorder			\n"				// suppress reordering
		"lv.q		c000, %2			\n"
		"vdot.q		s010, c000, c000	\n"
		"vrsq.s		s020, s010			\n"
		"vscl.q		c000, c000, s020	\n"
		"vsqrt.s	s030, s010			\n"
		"sv.q		c000, %0			\n"
		"sv.s		s030, 0 + %1		\n"	
		".set		pop					\n"				// restore assembler options
		: "=m"(*this), "=m"(result)
		: "m"(*this)
		);				
	return result;
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
