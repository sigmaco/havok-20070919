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
#include <Common/Base/Reflection/hkClassMemberAccessor.h>

void hkClassMemberAccessor::connect(void* obj, const hkClassMember* mem)
{
	HK_ASSERT(0x2a93cc79, obj != HK_NULL );
	HK_ASSERT(0x40645d7c, mem != HK_NULL );

	m_address = static_cast<char*>(obj) + mem->getOffset();
	m_member = mem;
}

void hkClassMemberAccessor::connect(void* obj, const hkClass& klass, const char* memberName)
{
	HK_ASSERT(0x2a93cc79, obj != HK_NULL );
	HK_ASSERT(0x6be6f5df, memberName != HK_NULL );

	m_address = HK_NULL;
	m_member = klass.getMemberByName(memberName);
	if( m_member )
	{
		m_address = static_cast<char*>(obj) + m_member->getOffset();
	}
	else
	{
		HK_ASSERT(0,0);
	}
}

hkClassMemberAccessor::hkClassMemberAccessor(void* obj, const hkClassMember* mem)
{
	connect( obj, mem );
}

hkClassMemberAccessor::hkClassMemberAccessor(const hkVariant& var, const char* memberName)
{
	connect( var.m_object, *var.m_class, memberName );
}

hkClassMemberAccessor::hkClassMemberAccessor(void* obj, const hkClass& klass, const char* memberName)
{
	connect( obj, klass, memberName );
}

hkBool hkClassMemberAccessor::isOk() const
{
	return m_address != HK_NULL;
}

void* hkClassMemberAccessor::asRaw() const
{
	HK_ASSERT(0x4463949a, isOk());
	return m_address;
}

void* hkClassMemberAccessor::getAddress() const
{
	HK_ASSERT(0x4463949a, isOk());
	return m_address;
}

hkClassMemberAccessor::Pointer& hkClassMemberAccessor::asPointer(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<void**>(m_address)[index];
}

hkClassMemberAccessor::Cstring& hkClassMemberAccessor::asCstring(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<char**>(m_address)[index];
}

hkBool& hkClassMemberAccessor::asBool(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkBool*>(m_address)[index];
}

hkReal& hkClassMemberAccessor::asReal(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkReal*>(m_address)[index];
}

hkInt32& hkClassMemberAccessor::asInt32(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkInt32*>(m_address)[index];
}

hkUint32& hkClassMemberAccessor::asUint32(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkUint32*>(m_address)[index];
}

hkUlong& hkClassMemberAccessor::asUlong(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkUlong*>(m_address)[index];
}

hkInt16& hkClassMemberAccessor::asInt16(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkInt16*>(m_address)[index];
}

hkUint16& hkClassMemberAccessor::asUint16(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkUint16*>(m_address)[index];
}

hkInt8& hkClassMemberAccessor::asInt8(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkInt8*>(m_address)[index];
}

hkUint8& hkClassMemberAccessor::asUint8(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkUint8*>(m_address)[index];
}

hkClassMemberAccessor::Vector4& hkClassMemberAccessor::asVector4(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkClassMemberAccessor::Vector4*>(m_address)[index];
}

hkClassMemberAccessor::Matrix3& hkClassMemberAccessor::asMatrix3(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkClassMemberAccessor::Matrix3*>(m_address)[index];
}

hkClassMemberAccessor::Transform& hkClassMemberAccessor::asTransform(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkClassMemberAccessor::Transform*>(m_address)[index];
}

hkClassMemberAccessor::Rotation& hkClassMemberAccessor::asRotation(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkClassMemberAccessor::Rotation*>(m_address)[index];
}

hkClassMemberAccessor::SimpleArray& hkClassMemberAccessor::asSimpleArray(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<SimpleArray*>(m_address)[index];
}

hkClassMemberAccessor::HomogeneousArray& hkClassMemberAccessor::asHomogeneousArray(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
    return reinterpret_cast<HomogeneousArray*>(m_address)[index];
}

hkVariant& hkClassMemberAccessor::asVariant(int index) const
{
	HK_ASSERT(0x4463949a, isOk());
	return reinterpret_cast<hkVariant*>(m_address)[index];
}

const hkClassMember& hkClassMemberAccessor::getClassMember() const
{
	HK_ASSERT(0x4463949a, isOk());
	return *m_member;
}

hkClassMemberAccessor hkClassMemberAccessor::member(const char* name) const
{
	HK_ASSERT(0x4463949a, isOk());
	HK_ASSERT(0x4463949b, name != HK_NULL);
	HK_ASSERT(0x4463949c, m_member->hasClass());
	HK_ASSERT(0x4463949d, m_member->getStructClass().getMemberByName(name) != HK_NULL);
	return hkClassMemberAccessor(m_address, m_member->getStructClass(), name);
}

hkClassAccessor hkClassMemberAccessor::object() const
{
	return hkClassAccessor(m_address, &m_member->getStructClass() );
}



hkClassAccessor::hkClassAccessor(void* object, const hkClass* klass)
{
	HK_ASSERT( 0x6a8cbbd4, object != HK_NULL );
	HK_ASSERT( 0x72cdb4e0, klass != HK_NULL );
	m_variant.m_object = object;
	m_variant.m_class = klass;
}

hkClassAccessor::hkClassAccessor( hkVariant& v ) :
	m_variant(v)
{
	HK_ASSERT( 0x6a8cbbd4, v.m_object != HK_NULL );
	HK_ASSERT( 0x72cdb4e0, v.m_class != HK_NULL );
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
