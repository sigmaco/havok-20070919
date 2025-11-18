/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Serialize/hkRelocationInfo.h>
#include <Common/Base/Container/StringMap/hkStringMap.h>

struct hkRelocationInfo::StringPool : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT);

		StringPool() {}

		~StringPool()
		{
			for( hkStringMap<char*>::Iterator i = m_pool.getIterator();
				m_pool.isValid(i);
				i = m_pool.getNext(i) )
			{
				hkDeallocate( m_pool.getKey(i) );
			}
		}

		char* insert(const char* s)
		{
			char* r;
			if( m_pool.get( s, &r ) == HK_NULL )
			{
				return r;
			}
			else
			{
				r = hkString::strDup(s);
				m_pool.insert(r, r);
				return r;
			}
		}

		hkStringMap<char*> m_pool;
};

hkRelocationInfo::~hkRelocationInfo()
{
	delete m_pool;
}

void hkRelocationInfo::applyLocalAndGlobal( void* buffer )
{
	char* ret = static_cast<char*>(buffer);

	// apply all fixups
	{
		for( int i = 0; i < m_local.getSize(); ++i )
		{
			*(void**)(ret + m_local[i].m_fromOffset) = ret + m_local[i].m_toOffset;
		}
	}
	{
		for( int i = 0; i < m_global.getSize(); ++i )
		{
			*(void**)(ret + m_global[i].m_fromOffset) = m_global[i].m_toAddress;
		}
	}
}

void hkRelocationInfo::addImport(int off, const char* name)
{
	if( m_pool == HK_NULL )
	{
		m_pool = new StringPool();
	}
	m_imports.pushBack( Import(off, m_pool->insert(name) ) );
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
