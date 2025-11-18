/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Container/Tree/hkTree.h>

struct hkTreeBase::Node
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_TREE, hkTreeBase::Node);

	Node()
		:	m_firstChild(0),
			m_lastChild(0),
			m_next(0),
			m_prev(0),
			m_parent(0)
	{
	}

	// could use a better allocation scheme by reusing nodes here.
	static void destroy(Node* n, int nbytes)
	{
		hkDeallocateChunk<char>( reinterpret_cast<char*>(n), hkSizeOf(Node) + nbytes, HK_MEMORY_CLASS_ARRAY );
	}
	static Node* create(int nbytes)
	{
		void* p = hkAllocateChunk<char>( hkSizeOf(Node) + nbytes, HK_MEMORY_CLASS_ARRAY );
		return new (p) Node();
	}

	Node* m_firstChild;
	Node* m_lastChild;
	Node* m_next;
	Node* m_prev;
	Node* m_parent;
};

hkTreeBase::hkTreeBase(int size)
	: m_firstRoot(HK_NULL), m_lastRoot(HK_NULL), m_nodeSize(size)
{
}

hkTreeBase::~hkTreeBase()
{
}

hkTreeBase::Iter hkTreeBase::append(Iter iter, const void* value, int size)
{
	Node* n = Node::create(size);
	hkString::memCpy(n+1, value, size);

	if( iter )
	{
		if( iter->m_lastChild )
		{
			HK_ASSERT( 0x58af31fb, iter->m_lastChild->m_next == HK_NULL );
			iter->m_lastChild->m_next = n;
			n->m_prev = iter->m_lastChild;
			n->m_parent = iter;
			iter->m_lastChild = n;
		}
		else
		{
			iter->m_lastChild = n;
			iter->m_firstChild = n;
			n->m_parent = iter;
		}		
	}
	else if( m_lastRoot != HK_NULL)
	{
		HK_ASSERT(0x598966ef, m_firstRoot != HK_NULL );
		HK_ASSERT(0x158582d8, m_firstRoot->m_prev == HK_NULL );
		HK_ASSERT(0x23fdee4c, m_lastRoot->m_next == HK_NULL );
		n->m_prev = m_lastRoot;
		m_lastRoot->m_next = n;
		m_lastRoot = n;
	}
	else
	{
		m_firstRoot = n;
		m_lastRoot = n;
	}
	return Iter(n);
}

hkTreeBase::Iter hkTreeBase::remove(Iter iter, destructFunc destruct)
{
	HK_ASSERT( 0x21d5eb18, iter != HK_NULL );
	Iter ret = iter->m_next ? iter->m_next : iter->m_prev;
	// unhook node from tree
	{ 
		Node* n = iter;
		if( n->m_prev )
		{
			n->m_prev->m_next = n->m_next;
		}
		else if( n->m_parent )
		{
			HK_ASSERT( 0x72faeb46, n->m_parent->m_firstChild == n );
			n->m_parent->m_firstChild = n->m_next;
		}
		else if( n == m_firstRoot )
		{
			m_firstRoot = n->m_next;
		}

		if( n->m_next )
		{
			n->m_next->m_prev = n->m_prev;
		}
		else if( n->m_parent )
		{
			HK_ASSERT( 0x5a69caa8, n->m_parent->m_lastChild == n );
			n->m_parent->m_lastChild = n->m_prev;
		}
		else if( n == m_lastRoot )
		{
			m_lastRoot = n->m_prev;
		}
		n->m_parent = HK_NULL;
	}
	// deallocate nodes. could be smarter here and not need temp storage.
	{ 
		hkArray<Node*> remaining;
		remaining.pushBack( iter );
		while( remaining.getSize() )
		{
			Node* n = remaining.back();
			Node* s = n->m_firstChild;
			remaining.popBack();
			destruct(n+1); // destruct payload
			Node::destroy(n, m_nodeSize); // and the node itself.
			while( s )
			{
				remaining.pushBack(s);
				s = s->m_next;
			}
		}
	}
	return ret;
}

int hkTreeBase::getDepth(Iter i) const
{
	int d = -1;
	Node* n = i;
	while( n )
	{
		n = n->m_parent;
		d += 1;
	}
	return d;
}

int hkTreeBase::getNumChildren(Iter i) const
{
	int c = 0;
	Node* n = i->m_firstChild;
	while( n )
	{
		n = n->m_next;
		c += 1;
	}
	return c;
}

const void* hkTreeBase::getValue(Iter i) const
{
	HK_ASSERT(0x2bcb4e0c, i != HK_NULL);
	return i + 1;
}

hkTreeBase::Iter hkTreeBase::iterGetRoot() const
{
	return m_firstRoot;
}

hkTreeBase::Iter hkTreeBase::iterNext(Iter i) const
{
	HK_ASSERT(0x7db36cf5, i != HK_NULL);
	return i->m_next;
}

hkTreeBase::Iter hkTreeBase::iterNextPreOrder(Iter i) const
{
	HK_ASSERT(0x273481ab, i != HK_NULL);
	if( i->m_firstChild )
	{
		return i->m_firstChild;
	}
	else
	{
		while( i->m_next == HK_NULL )
		{
			i = i->m_parent;
			if( i == HK_NULL )
			{
				return HK_NULL;
			}
		}
		return i->m_next;
	}
}

hkTreeBase::Iter hkTreeBase::iterParent(Iter i) const
{
	HK_ASSERT( 0x220a464f, i != HK_NULL );
	return i->m_parent;
}

hkTreeBase::Iter hkTreeBase::iterChildren(Iter i) const
{
	HK_ASSERT( 0x629c6cf1, i != HK_NULL );
	return i->m_firstChild;
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
