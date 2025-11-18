/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkClassMember.h>
#include <Common/Base/Reflection/hkClassEnum.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkCustomAttributes.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/System/Io/Writer/Crc32/hkCrc32StreamWriter.h>
#include <Common/Base/System/Io/OArchive/hkOArchive.h>
#include <Common/Base/Types/hkTypedUnion.h>

HK_COMPILE_TIME_ASSERT( sizeof(hkInternalClassMember) == sizeof(hkClassMember) );
HK_COMPILE_TIME_ASSERT( sizeof(hkInternalClassEnum) == sizeof(hkClassEnum) );
HK_COMPILE_TIME_ASSERT( sizeof(hkInternalClassEnumItem) == sizeof(hkClassEnum::Item) );

hkClass::hkClass(const char* className,
				const hkClass* parentClass,
				int objectSizeInBytes,
				const hkClass** implementedInterfaces,
				int numImplementedInterfaces,
				const hkClassEnum* declaredEnums,
				int numDeclaredEnums,
				const hkClassMember* members,
				int numMembers, 
				const void* defaults,
				const hkCustomAttributes* attrs,
				hkUint32 flags )
	:	m_name(className),
		m_parent(parentClass),
		m_objectSize(objectSizeInBytes),
		//m_implementedInterfaces(implementedInterfaces),
		m_numImplementedInterfaces(numImplementedInterfaces),
		m_declaredEnums( declaredEnums ),
		m_numDeclaredEnums( numDeclaredEnums ),
		m_declaredMembers(members),
		m_numDeclaredMembers(numMembers),
		m_defaults(defaults),
		m_attributes(attrs),
		m_flags(flags),
		m_describedVersion(0)
{
#if defined(HK_DEBUG)
	for( int i = 1; i < numMembers; ++i )
	{
		// assert offsets are increasing, except for all zero offsets (as in hkcompat)
		if( (members[i].getOffset() != 0 || members[i-1].getOffset() != 0 )
		&&  (members[i].getOffset() <= members[i-1].getOffset()) ) // normal HK_OFFSET_OF
		{
			// cannot assert as usually these are statically initialized.
			HK_BREAKPOINT(0); //	Reflected member order must match declared order.
		}		
	}
#endif
}

const char* hkClass::getName() const
{
	return m_name;
}

const hkClass* hkClass::getParent() const
{
	return m_parent;
}

hkClass* hkClass::getParent()
{
	return const_cast<hkClass*>(m_parent);
}

int hkClass::getInheritanceDepth() const
{
	int depth = 0;
	const hkClass* c = this;
	while( c != HK_NULL )
	{
		++depth;
		c = c->m_parent;
	}
	return depth;
}

hkBool hkClass::isSuperClass(const hkClass& k) const
{
	const hkClass* c = &k;
	while( c )
	{
		if( c == this )
		{
			return true;
		}
		c = c->getParent();
	}
	return false;
}

#define RETURN_SUM_MEMBERS(MEMBER) \
	const hkClass* c = this->m_parent; \
	int RETURN = MEMBER; \
	while( c ) \
	{ \
		RETURN += c->MEMBER; \
		c = c->m_parent; \
	} \
	return RETURN

int hkClass::getNumInterfaces() const
{
	RETURN_SUM_MEMBERS(m_numImplementedInterfaces);
}

const hkClass* hkClass::getInterface( int i ) const
{
	return HK_NULL;
}

const hkClass* hkClass::getDeclaredInterface( int i ) const
{
	return HK_NULL;
}

int hkClass::getNumDeclaredInterfaces() const
{
	return m_numImplementedInterfaces;
}

int hkClass::getNumEnums() const
{
	RETURN_SUM_MEMBERS(m_numDeclaredEnums);
}

const hkClassEnum& hkClass::getEnum(int enumIndex) const
{
	int numEnums = getNumEnums();
	HK_ASSERT(0x275d8b19, enumIndex >= 0 && enumIndex < numEnums );
	const hkClass* c = this;
	int localIndex = enumIndex - numEnums;
	while( c )
	{
		localIndex += c->m_numDeclaredEnums;
		if( localIndex >= 0 )
		{
			return c->m_declaredEnums[localIndex];
		}
		c = c->m_parent;
	}
	HK_ASSERT2(0x1036239f, 0, "notreached");
	return m_declaredEnums[0];
}

const hkClassEnum* hkClass::getEnumByName(const char* name) const
{
	for( int i = 0; i < getNumEnums(); ++i)
	{
		const hkClassEnum& e = getEnum(i);
		if( hkString::strCmp(e.getName(), name) == 0)
		{
			return &e;
		}
	}
	return HK_NULL;
}


int hkClass::getNumMembers() const
{
	RETURN_SUM_MEMBERS(m_numDeclaredMembers);
}

const hkClassMember& hkClass::getMember(int memberIndex) const
{
	int numMembers = getNumMembers();
	HK_ASSERT(0x275d8b19, memberIndex >= 0 && memberIndex < numMembers );
	const hkClass* c = this;
	int localIndex = memberIndex - numMembers;
	while( c )
	{
		localIndex += c->m_numDeclaredMembers;
		if( localIndex >= 0 )
		{
			return c->m_declaredMembers[localIndex];
		}
		c = c->m_parent;
	}
	HK_ASSERT2(0x1036239f, 0, "notreached");
	return m_declaredMembers[0];
}

hkClassMember& hkClass::getMember(int memberIndex)
{
	const hkClass* constThis = this;
	return const_cast<hkClassMember&>( constThis->getMember(memberIndex) );
}

int hkClass::getNumDeclaredMembers() const
{
	return m_numDeclaredMembers;
}

const hkClassMember& hkClass::getDeclaredMember(int i) const
{
	HK_ASSERT(0x39d720db, i>=0 && i < m_numDeclaredMembers);
	return m_declaredMembers[i];
}

const hkClassMember* hkClass::getMemberByName(const char* name) const
{
	for( int i = 0; i < getNumMembers(); ++i)
	{
		const hkClassMember& m = getMember(i);
		if( hkString::strCmp(m.getName(), name) == 0)
		{
			return &m;
		}
	}
	return HK_NULL;
}


int hkClass::getObjectSize() const
{
	return m_objectSize;
}

void hkClass::setObjectSize(int size)
{
	m_objectSize = size;
}

hkBool hkClass::hasVtable() const
{
	const hkClass* c = this;
	while(c->getParent())
	{
		c = c->getParent();
	}
	HK_ON_DEBUG(int v = getNumInterfaces());
	int i = c->m_numImplementedInterfaces;
	HK_ASSERT2(0x279061ac, (i==0 && v==0) || (i!=0 && v!=0), "Vtable is not in base class.");
	return i != 0;
}

hkUint32 hkClass::getSignature(int signatureFlags) const
{
	hkCrc32StreamWriter crc;
	bool recurse = (signatureFlags & SIGNATURE_LOCAL)==0;
	const hkClass* c = this;
	while( c )
	{
		c->writeSignature(&crc);
		c = recurse ? c->getParent() : HK_NULL;
	}
	
	return crc.getCrc32();
}

hkResult hkClass::retrieveMember(int memberIndex, const void*& defaultOut, const hkClassMember*& memberOut) const
{
	int numMembers = getNumMembers();
	HK_ASSERT(0x275d8b19, memberIndex >= 0 && memberIndex < numMembers );
	const hkClass* c = this;
	int localIndex = memberIndex - numMembers;
	while( c )
	{
		localIndex += c->m_numDeclaredMembers;
		if( localIndex >= 0 )
		{
			if( c->m_defaults )
			{
				int defIndex = reinterpret_cast<const int*>(c->m_defaults)[localIndex];
				if( defIndex >= 0 )
				{
					defaultOut = static_cast<const char*>(c->m_defaults)+defIndex;
					memberOut = &(c->m_declaredMembers[localIndex]);
					return HK_SUCCESS;
				}
			}
			break;
		}
		c = c->m_parent;
	}
	return HK_FAILURE;
}

hkResult hkClass::getDefault(int memberIndex, hkStreamWriter* writer) const
{
	const void* defaultPtr;
	const hkClassMember* member;
	hkResult res = retrieveMember(memberIndex, defaultPtr, member);
	if( res == HK_SUCCESS )
	{
		writer->write( defaultPtr, member->getSizeInBytes() );
	}
	return res;
}


hkResult hkClass::getDefault(int memberIndex, hkTypedUnion& value) const
{
	const void* defaultPtr;
	const hkClassMember* member;
	hkResult res = retrieveMember(memberIndex, defaultPtr, member);
	if(res==HK_SUCCESS)
	{
		HK_ASSERT2(0x3f24c88c, member->getType() != hkClassMember::TYPE_STRUCT, "struct not supported");

		if( member->getType() == hkClassMember::TYPE_POINTER )
		{
			value.setObject( defaultPtr, member->getClass() );
		}
		else if( member->getType() == hkClassMember::TYPE_ENUM )
		{
			value.setEnum( member->getEnumValue(defaultPtr), &member->getEnumClass() );
		}
		else
		{
			res = value.setSimple( defaultPtr, member->getType() );
		}
	}
	return res;
}


void hkClass::writeSignature( hkStreamWriter* w ) const
{
	hkOArchive oa(w);
	//oa.writeRaw( m_name, hkString::strLen(m_name) );	// don't include name
	//oa.write32(m_objectSize ); // size not needed for cross platform signature.

	int i;
	
	for( i = 0; i < m_numImplementedInterfaces; ++i )
	{
		// crc.write( m_implementedInterfaces[i] );
	}
	oa.write32(m_numImplementedInterfaces);
	
	for( i = 0; i < m_numDeclaredEnums; ++i )
	{
		m_declaredEnums[i].writeSignature( w );
	}
	oa.write32( m_numDeclaredEnums );
	
	for( i = 0; i < m_numDeclaredMembers; ++i )
	{
		const hkClassMember& member = m_declaredMembers[i];
		hkInternalClassMember m = reinterpret_cast<const hkInternalClassMember&>(member);

		// In earlier hkClasses, the size of the enum was stored in some flag bits
		// (There was no other room for TYPE_ZERO+TYPE_ENUM members)
		// We use xor, not set so that even if the bits are recycled, the signature is valid.
		if( m.m_type == hkClassMember::TYPE_ENUM || m.m_type == hkClassMember::TYPE_FLAGS )
		{
			int sz = hkClassMember::getClassMemberTypeProperties( static_cast<hkClassMember::Type>(m.m_subtype) ).m_size;
			m.m_flags ^= sz * 8; // size8 == 8, size16 == 16 etc.
			m.m_subtype = hkClassMember::TYPE_VOID;
		}
		// In earlier hkClasses, the no-serialize flag was encoded as the primary type
		// and the real type in the subtype. We transform the data back to this format
		// for signature calculation so that all the old signatures don't change under us.
		hkInt16 subType2 = hkClassMember::TYPE_VOID;
		if( m.m_flags & hkClassMember::SERIALIZE_IGNORED )
		{
			m.m_flags ^= hkClassMember::SERIALIZE_IGNORED;
			if( m.m_subtype != hkClassMember::TYPE_VOID )
			{
				subType2 = m.m_subtype;
			}
			m.m_subtype = m.m_type;
			m.m_type = hkClassMember::TYPE_ZERO;
			//m.m_enum = HK_NULL;/?XXX
		}
		
		// From here on is the normal crc generation.
		if( m.m_class
			&& member.getType() != hkClassMember::TYPE_POINTER
			&& member.getSubType() != hkClassMember::TYPE_POINTER )
		{
			const hkClass* c = member.getClass();
			while( c )
			{
				c->writeSignature( w );
				c = c->getParent();
			}
		}
		if( m.m_enum )
		{
			member.getEnumClass().writeSignature(w);
		}
		oa.writeRaw( m.m_name, hkString::strLen(m.m_name) );
		oa.write16( m.m_type );
		oa.write16( m.m_subtype );
		if( subType2 != hkClassMember::TYPE_VOID )
		{
			oa.write16( subType2 );
		}
		oa.write16( m.m_cArraySize );
		oa.write16( m.m_flags );
		//oa.write16( m.m_offset ); // offset not needed for cross platform signature.
	}
	oa.write32( m_numDeclaredMembers );
	// don't include defaults in signature.
}

const hkVariant* hkClass::getAttribute(const char* id) const
{
	return m_attributes ? m_attributes->getAttribute(id) : HK_NULL;
}

const hkClass::Flags& hkClass::getFlags() const
{
	return m_flags;
}

hkClass::Flags& hkClass::getFlags()
{
	return m_flags;
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
