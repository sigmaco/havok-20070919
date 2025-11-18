/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClassMember.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkClassEnum.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkCustomAttributes.h>

#ifdef HK_COMPILER_MSVC
#	pragma warning(disable: 4610) // struct '`anonymous-namespace'::ClassMemberProperty' can never be instantiated - user defined constructor required
#endif

namespace
{
	// some compilers have problems with alignof(hkArray<char>) so
	// use this dummy with the same layout instead.
	struct DummyArray
	{
		void* p;
		int s;
		int c;
	};

	struct DummySimpleArray
	{
		void* p;
		int s;
	};

	struct DummyHomogeneousArray
	{
		hkClass* t;
		void* p;
		int s;
	};

}

#if defined(HK_COMPILER_MSVC)
#	define HK_ALIGN_OF(T) __alignof(T)
#elif defined(HK_COMPILER_GCC) || defined(HK_COMPILER_SNC)
#	define HK_ALIGN_OF(T) __alignof__(T)
#elif defined(HK_COMPILER_MWERKS)
#	define HK_ALIGN_OF(T) __builtin_align(T)
#else
#	error fixme
#endif

#if defined(HK_COMPILER_MWERKS)

struct SimpleTypeProperties
{
		/// The type associated with this
	hkInt8 m_type;
		/// Zero terminated name
	const char* m_name;
		/// Size of the type in bytes <=0 it is not defined
	short m_size;
		/// Alignment in bytes, if <=0 it is not defined
	short m_align;
};

HK_COMPILE_TIME_ASSERT( sizeof(SimpleTypeProperties) == sizeof(hkClassMember::TypeProperties));

#define CLASS_MEMBER_TYPE_PROPERTIES SimpleTypeProperties

#else
#define CLASS_MEMBER_TYPE_PROPERTIES hkClassMember::TypeProperties
#endif

static  CLASS_MEMBER_TYPE_PROPERTIES ClassMemberProperties[] =
{
	{ hkClassMember::TYPE_VOID, "void", -1, -1 },
	{ hkClassMember::TYPE_BOOL, "hkBool", sizeof(char), HK_ALIGN_OF(char) },
	{ hkClassMember::TYPE_CHAR, "hkChar", sizeof(char), HK_ALIGN_OF(char) },
	{ hkClassMember::TYPE_INT8, "hkInt8", sizeof(hkInt8), HK_ALIGN_OF(hkInt8) },
	{ hkClassMember::TYPE_UINT8, "hkUint8", sizeof(hkUint8), HK_ALIGN_OF(hkUint8) },

	{ hkClassMember::TYPE_INT16, "hkInt16", sizeof(hkInt16), HK_ALIGN_OF(hkInt16) },
	{ hkClassMember::TYPE_UINT16, "hkUint16", sizeof(hkUint16), HK_ALIGN_OF(hkUint16) },
	{ hkClassMember::TYPE_INT32, "hkInt32", sizeof(hkInt32), HK_ALIGN_OF(hkInt32) },
	{ hkClassMember::TYPE_UINT32, "hkUint32", sizeof(hkUint32), HK_ALIGN_OF(hkUint32) },
	{ hkClassMember::TYPE_INT64, "hkInt64", sizeof(hkInt64), HK_ALIGN_OF(hkInt64) },

	{ hkClassMember::TYPE_UINT64, "hkUint64", sizeof(hkUint64), HK_ALIGN_OF(hkUint64) },
	{ hkClassMember::TYPE_REAL, "hkReal", sizeof(hkReal), HK_ALIGN_OF(hkReal) },
	{ hkClassMember::TYPE_VECTOR4, "hkVector4", 4*sizeof(hkReal), 4*HK_ALIGN_OF(hkReal) },
	{ hkClassMember::TYPE_QUATERNION, "hkQuaternion", 4*sizeof(hkReal), 4*HK_ALIGN_OF(hkReal) },
	{ hkClassMember::TYPE_MATRIX3, "hkMatrix3", 12*sizeof(hkReal), 4*HK_ALIGN_OF(hkReal) },

	{ hkClassMember::TYPE_ROTATION, "hkRotation", 12*sizeof(hkReal), 4*HK_ALIGN_OF(hkReal) },
	{ hkClassMember::TYPE_QSTRANSFORM, "hkQsTransform", 12*sizeof(hkReal), 4*HK_ALIGN_OF(hkReal) },
	{ hkClassMember::TYPE_MATRIX4, "hkMatrix4", 16*sizeof(hkReal), 4*HK_ALIGN_OF(hkReal) },
	{ hkClassMember::TYPE_TRANSFORM, "hkTransform", 16*sizeof(hkReal), 4*HK_ALIGN_OF(hkReal) },
	{ hkClassMember::TYPE_ZERO, "hkZero", -1, -1 },

	{ hkClassMember::TYPE_POINTER, "hkPointer", sizeof(void*), HK_ALIGN_OF(void*) },
	{ hkClassMember::TYPE_FUNCTIONPOINTER, "hkFunctionPointer", sizeof(void*), HK_ALIGN_OF(void*) },
	{ hkClassMember::TYPE_ARRAY, "hkArray", sizeof(DummyArray), HK_ALIGN_OF(DummyArray) },
	{ hkClassMember::TYPE_INPLACEARRAY, "hkInplaceArray", -1, -1 },
	{ hkClassMember::TYPE_ENUM, "hkEnum", -1, -1 },

	{ hkClassMember::TYPE_STRUCT, "hkStruct", -1, -1 },
	{ hkClassMember::TYPE_SIMPLEARRAY, "hkSimpleArray", sizeof(DummySimpleArray), HK_ALIGN_OF(DummySimpleArray) },
	{ hkClassMember::TYPE_HOMOGENEOUSARRAY, "hkHomogeneousArray", sizeof(DummyHomogeneousArray), HK_ALIGN_OF(DummyHomogeneousArray) },
	{ hkClassMember::TYPE_VARIANT, "hkVariant", 2*sizeof(void*), HK_ALIGN_OF(void*) },
	{ hkClassMember::TYPE_CSTRING, "char*", sizeof(char*), HK_ALIGN_OF(char*) },
	{ hkClassMember::TYPE_ULONG, "hkUlong", sizeof(hkUlong), HK_ALIGN_OF(hkUlong) },
	{ hkClassMember::TYPE_FLAGS, "hkFlags", -1, -1 },
	{ hkClassMember::TYPE_MAX, "hkTypeMax", -1, -1 }
};

HK_COMPILE_TIME_ASSERT( sizeof(hkReal) == 4); // check alignment of vector4
HK_COMPILE_TIME_ASSERT( sizeof(ClassMemberProperties)/sizeof(hkClassMember::TypeProperties) == hkClassMember::TYPE_MAX + 1 );
HK_COMPILE_TIME_ASSERT( sizeof(hkUint32) <= sizeof(void*) );
HK_COMPILE_TIME_ASSERT( sizeof(hkReal) <= sizeof(void*) );

const hkClassMember::TypeProperties&
hkClassMember::getClassMemberTypeProperties(Type type)
{
    return ((hkClassMember::TypeProperties*)ClassMemberProperties)[type];
}

int hkClassMember::getSizeInBytes() const
{
	int nbytes = -1;
	switch( int type = getType() )
	{
		case TYPE_BOOL:
		case TYPE_CHAR:
		case TYPE_INT8:
		case TYPE_UINT8:
		case TYPE_INT16:
		case TYPE_UINT16:
		case TYPE_INT32:
		case TYPE_UINT32:
		case TYPE_INT64:
		case TYPE_UINT64:
		case TYPE_ULONG:
		case TYPE_REAL:
		case TYPE_VECTOR4:
		case TYPE_QUATERNION:
		case TYPE_MATRIX3:
		case TYPE_ROTATION:
		case TYPE_QSTRANSFORM:
		case TYPE_MATRIX4:
		case TYPE_TRANSFORM:
		case TYPE_POINTER:
		case TYPE_FUNCTIONPOINTER:
		case TYPE_ARRAY:
		case TYPE_SIMPLEARRAY:
		case TYPE_HOMOGENEOUSARRAY:
		case TYPE_VARIANT:
		case TYPE_CSTRING:
		{
			int nelem = getCstyleArraySize() ? getCstyleArraySize() : 1;
			nbytes = ClassMemberProperties[ type ].m_size * nelem;
			break;
		}
		case TYPE_ENUM:
		case TYPE_FLAGS:
		{
			int nelem = getCstyleArraySize() ? getCstyleArraySize() : 1;
			nbytes = ClassMemberProperties[ getSubType() ].m_size * nelem;
			break;
		}
		case TYPE_STRUCT:
		{
			int nelem = getCstyleArraySize() ? getCstyleArraySize() : 1;
			nbytes = getStructClass().getObjectSize()* nelem;
			break;
		}
		case TYPE_INPLACEARRAY:
		case TYPE_VOID:
		case TYPE_MAX:
		case TYPE_ZERO:
		default:
		{
			HK_ASSERT(0,0);
		}
	}
	HK_ASSERT(0, nbytes >= 0);
	return nbytes;
}

hkBool hkClassMember::isNotOwner() const
{
    return m_flags.allAreSet(NOT_OWNED);
}

int hkClassMember::getAlignment() const
{
	int type = getType();
	int align;
	if( type == TYPE_ENUM || type == TYPE_FLAGS )
	{
		type = getSubType();
	}
	if( type == TYPE_STRUCT )
	{
		HK_ASSERT(0, m_class != HK_NULL );
		int biggestAlign = 1;
		for( int i = 0; i < m_class->getNumMembers(); ++i )
		{
			if( m_class->getMember(i).getAlignment() > biggestAlign )
			{
				biggestAlign = m_class->getMember(i).getAlignment();
			}
		}
		align = biggestAlign;
	}
	else
	{
		align = ClassMemberProperties[ type ].m_align;
	}
	HK_ASSERT(0, align != -1);
	if( getFlags().anyIsSet(ALIGN_16|ALIGN_8) )
	{
		int forcedAlign = getFlags().anyIsSet(ALIGN_16) ? 16 : 8;
		align = forcedAlign > align ? forcedAlign : align;
	}
	return align;
}

static void getSimpleTypeName( hkClassMember::Type type, int nelem,  hkString& ret )
{
	HK_ASSERT(0x22bb9606, type >= hkClassMember::TYPE_VOID && type < hkClassMember::TYPE_POINTER || (type == hkClassMember::TYPE_HOMOGENEOUSARRAY) || (type == hkClassMember::TYPE_CSTRING)  );
	if( nelem == 0 )
	{
		ret = ClassMemberProperties[ type ].m_name;
	}
	else // c array
	{
		ret.printf("%s[%i]", ClassMemberProperties[ type ].m_name, nelem );
	}
}

int hkClassMember::getTypeName(char* buf, int bufLen) const
{
	hkClassMember::Type type = getType();
	const char* className = m_class ? m_class->getName() : "unknown";
	const char* enumName = m_enum ? m_enum->getName() : "unknown";
	hkString ret;
	if( (type < TYPE_POINTER) || (type == TYPE_HOMOGENEOUSARRAY) || (type == TYPE_CSTRING))
	{
		getSimpleTypeName( type, m_cArraySize, ret );
	}
	else if( type == TYPE_POINTER )
	{
		if( m_class )
		{
			ret.printf("struct %s*", m_class->getName() );
		}
		else if (getSubType() == TYPE_CHAR)
		{ // char* are assumed to be c strings
			ret = "char*";
		}
		else
		{
			ret = "void*";
		}
	}
	else if( ( type == TYPE_ARRAY ) || ( type == TYPE_SIMPLEARRAY ))
	{
		Type atype = getArrayType();
		const char* arrayContainer = (type == TYPE_ARRAY ? "hkArray" : "hkSimpleArray" );
		if( atype < TYPE_POINTER || atype == TYPE_CSTRING )
		{
			ret.printf("%s&lt;%s&gt;", arrayContainer, ClassMemberProperties[ atype ].m_name );
		}
		else if( atype == TYPE_POINTER )
		{
			if( m_class )
			{
				ret.printf("%s&lt;%s*&gt;", arrayContainer, className );
			}
			else
			{
				ret.printf("%s&lt;void*&gt;", arrayContainer);
			}
		}
		else if( atype == TYPE_STRUCT )
		{
			ret.printf("%s&lt;struct %s&gt;", arrayContainer, className );
		}
		else if( atype == TYPE_VARIANT )
		{
			ret.printf("%s&lt;struct hkVariant&gt;", arrayContainer );
		}
		else
		{
			HK_ASSERT2( 0x3e29dd3b, 0, "Array of unsupported types");
		}
	}
	else if( type == TYPE_ENUM )
	{
		ret.printf("enum %s", enumName );
	}
	else if( type == TYPE_FLAGS )
	{
		ret.printf("flags %s", enumName );
	}
	else if( type == TYPE_STRUCT )
	{
		if( m_cArraySize == 0 )
		{
			ret.printf("struct %s", className );
		}
		else
		{
			ret.printf("struct %s[%i]", className, m_cArraySize);
		}
	}
	hkString::strNcpy( buf, ret.cString(), bufLen );
	return ret.getLength();
}

hkClassMember::Type hkClassMember::getArrayType() const
{
	HK_ASSERT( 0x3dcf4bbd, (getType() == TYPE_ARRAY)
		|| (getType() == TYPE_SIMPLEARRAY)
		|| (getType() == TYPE_POINTER) //XXX
		|| (getType() == TYPE_HOMOGENEOUSARRAY));
	return static_cast<hkClassMember::Type>(m_subtype);
}

int hkClassMember::getArrayMemberSize() const
{
	HK_ASSERT( 0x11a02fc6,	(getType() == TYPE_ARRAY) ||
							(getType() == TYPE_SIMPLEARRAY) ||
							(getType() == TYPE_HOMOGENEOUSARRAY) );

	// arrays of enums?
	if ( getArrayType() == TYPE_ENUM  || getArrayType() == TYPE_FLAGS )
	{
		HK_ASSERT2(0x198765e3,0,"Arrays of enums/flags are not supported yet...");
		return -1;
	}
	else if( getArrayType() != TYPE_STRUCT )
	{
		int sz = ClassMemberProperties[ getArrayType() ].m_size;
		HK_ASSERT( 0x51251f5c, sz > 0 );
		return sz;
	}
	else
	{
		return getStructClass().getObjectSize();
	}
}

const hkClass& hkClassMember::getStructClass() const
{
	return *m_class;
}

const hkClass* hkClassMember::getClass() const
{
	return m_class;
}

const hkClassEnum& hkClassMember::getEnumClass() const
{
	return *m_enum;
}

int hkClassMember::getCstyleArraySize() const
{
	return m_cArraySize;
}

const hkClassEnum& hkClassMember::getEnumType() const
{
	HK_ASSERT( 0x709bd5aa, getType() == TYPE_ENUM || getType() == TYPE_FLAGS );
	return *m_enum;
}

int hkClassMember::getEnumValue(const void* memberAddress) const
{
	int value = 0;
	switch(getSizeInBytes())
	{
		case 1:	value = *(const hkInt8* )memberAddress; break;
		case 2:	value = *(const hkInt16*)memberAddress; break;
		case 4:	value = *(const hkInt32*)memberAddress; break;
		default: HK_ASSERT(0x114dd964, 0);
	}
	return value;
}

void hkClassMember::setEnumValue(void* memberAddress, int value) const
{
	switch(getSizeInBytes())
	{
		case 1:	*(hkUint8* )memberAddress = hkUint8 (value); break;
		case 2:	*(hkUint16*)memberAddress = hkUint16(value); break;
		case 4:	*(hkUint32*)memberAddress = hkUint32(value); break;
		default: HK_ASSERT(0x114dd965, 0);
	}
}

const hkVariant* hkClassMember::getAttribute(const char* id) const
{
	return m_attributes ? m_attributes->getAttribute(id) : HK_NULL;
}

hkClassMember::Type hkClassMember::getTypeOf( const char* name )
{
	if( hkString::strNcmp(name, "enum ", 5) == 0 )
	{
		return hkClassMember::TYPE_ENUM;
	}
	if( hkString::strNcmp(name, "flags ", 6) == 0 )
	{
		return hkClassMember::TYPE_FLAGS;
	}
	else if( hkString::strNcmp(name, "hkArray<", 8) == 0 )
	{
		return hkClassMember::TYPE_ARRAY;
	}
	else if( hkString::strNcmp(name, "hkSimpleArray<", 14) == 0 )
	{
		return hkClassMember::TYPE_SIMPLEARRAY;
	}
	else if( hkString::strNcmp(name, "char*", 5) == 0 )
	{
		return hkClassMember::TYPE_CSTRING;
	}
	else if( const char* star = hkString::strRchr(name, '*') )
	{
		if( star[1] == 0 )
		{
			return hkClassMember::TYPE_POINTER;
		}
	}
	hkString sname = name;
	if( const char* brace = hkString::strChr(name, '[') )
	{
		sname = sname.substr(0, int(brace - name));
	}
	for( int i = 0; i < hkClassMember::TYPE_MAX; ++i )
	{
		if( sname == ClassMemberProperties[i].m_name )
		{
			return hkClassMember::Type(i);
		}
	}
	return hkClassMember::TYPE_VOID;
}

hkClassMember::Type hkClassMember::getSubtypeOf( const char* name )
{
	if( hkString::strNcmp(name, "hkArray<", 8) == 0 )
	{
		hkString s(name+8, hkString::strLen(name+8) - 1 );
		return getTypeOf( s.cString() );
	}
	if( hkString::strNcmp(name, "hkSimpleArray<", 14) == 0 )
	{
		hkString s(name+14, hkString::strLen(name+14) - 1 );
		return getTypeOf( s.cString() );
	}
	else if( const char* p = hkString::strChr(name, '[') )
	{
		const char* q = hkString::strChr(name, ']');
		HK_ASSERT(0x638af50c, q != HK_NULL);
		hkString s(p+1, int(q-p)-1 );
		return hkClassMember::Type( hkString::atoi( s.cString() ) );
	}
	return hkClassMember::TYPE_VOID; // includes TYPE_HOMOGENEOUSARRAY
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
