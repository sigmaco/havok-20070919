/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Algorithm/UnionFind/hkUnionFind.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>

/* Heres the deal, m_nodes contains all possible nodes in the graph.
 * we make sure all nodes are known before adding edges so that we
 * can do clever preallocation of m_parents.
 *
 * m_parents is a list of indices.
 * Let p = m_parents[i] for any i.
 * p>=0 means that the m_nodes[i] is connected to m_nodes[p]
 * p<0 means that m_nodes[i] is a root. Also m_nodes[i] has -p child nodes
 */


/*************************************************************** HELPER */


/*************************************************************** HELPER */

/*
#ifdef HK_DEBUG

hkOstream& operator << (hkOstream& os, const hkUnionFind::IntArray& parents );

hkOstream& operator << (hkOstream& os, const hkUnionFind::IntArray& parents )
{
	int* c = parents.begin();
	int* e = parents.end();
	os << "[ ";
	for( ; c!=e; ++c)
	{
		os << *c << " ";
	}
	os << "]\n\n";

	return os;
}

#endif //HK_DEBUG
*/

/*************************************************************** CONSTRUCT DESTRUCT */

hkUnionFind::hkUnionFind( IntArray& parents, int numnode )
:	m_parents(parents)
{
	m_numNodes = numnode;
	for(int i = 0; i < numnode; ++i)
	{
		m_parents[i] = -1;
	}
}


/*************************************************************** PRIVATE FUNC */

// do path compression on the way up the tree
HK_FORCE_INLINE int hkUnionFind::findRootOfNode(int i)
{
	// find root
	int root = i;
	while ( 1 )
	{
		if ( m_parents[root] < 0 )
		{
			break;
		}
		root = m_parents[root];
	}

	// set all 
	while(m_parents[i]>=0) 
	{
		int j = m_parents[i];
		m_parents[i] = root;
		i = j;
	}
	return i;
}

/*************************************************************** PRIVATE FUNC */


// join two roots - make the one earlier in the list the new root
HK_FORCE_INLINE void hkUnionFind::unionRoots(int r1, int r2) 
{
	int n1 = m_parents[r1];
	int n2 = m_parents[r2];

	if(r1 < r2) 
	{
		m_parents[r1] += n2;
		m_parents[r2] = r1;
	}
	else
	{
		m_parents[r2] += n1;
		m_parents[r1] = r2;
	}
}







/*************************************************************** ADDEDGE */

void hkUnionFind::addEdge( int i1, int i2 )
{
	if ( i1 > i2 )
	{
		int h = i1; i1 = i2; i2 = h;
	}

	const int r1 = findRootOfNode(i1);
	const int r2 = findRootOfNode(i2);

	HK_ASSERT(0x2a09ea55, m_parents[r1]<0 && m_parents[r2]<0);

	if(r1!=r2)
	{
		unionRoots(r1, r2);
	}
}

/*************************************************************** COLLAPSE */

void hkUnionFind::collapseTree()
{
	// collapse nodes

	int* c = m_parents.begin();
	int* e = c + m_numNodes;

	for( ; c!=e; ++c)
	{
		if(*c>=0)
		{
			while( m_parents[*c]>=0 )
			{
				*c = m_parents[*c];
			}
		}
	}
}

void hkUnionFind::assignGroups( hkArray<int>& elementsPerGroup )
{
	collapseTree();

	int numGroups = 0;

	// populate the groups array
	for (int i = 0; i < m_numNodes; ++i)
	{
		int parent = m_parents[i];
		if ( parent < 0)
		{
			// a new root node - add a new group
			elementsPerGroup.pushBack( -parent );
			m_parents[i] = numGroups++;
		}
		else
		{
			int group = m_parents[parent];
			m_parents[i] = group;
			HK_ASSERT(0x27fc55e0, group >=0 && group < numGroups);
		}
	}
}




int hkUnionFind::moveBiggestGroupToIndexZero( hkArray<int>& elementsPerGroup )
{
	// resort the data so that the biggest group is zero
	int biggestSize = elementsPerGroup[0];
	int biggestIndex = 0;
	int ngroups = elementsPerGroup.getSize();
	{
		for (int i = 1; i < ngroups;i++)
		{
			if ( elementsPerGroup[i] > biggestSize)
			{
				biggestSize = elementsPerGroup[i];
				biggestIndex = i;
			}
		}
	}

	if ( biggestIndex == 0)
	{
		return 0;
	}

	// now swap 0 with biggest index
	hkLocalBuffer<int> rindex(ngroups);
	{
		for (int i = 0; i < ngroups;i++)
		{
			rindex[i] = i;
		}
		rindex[0] = biggestIndex;
		rindex[biggestIndex] = 0;
		int h = elementsPerGroup[ biggestIndex ];
		elementsPerGroup[ biggestIndex ] = elementsPerGroup[0];
		elementsPerGroup[0] = h;
	}

	for (int i = 0; i < m_numNodes;i++)
	{
		int oldGroup = m_parents[i];
		int newGroup = rindex[oldGroup];
		m_parents[i] = newGroup;
	}
	return biggestIndex;
}

void hkUnionFind::reindex( const hkFixedArray<int>& rindex, int numNewGroups, hkArray<int>& elementsPerGroup )
{
	HK_ASSERT( 0xf0322345, rindex.getSizeDebug() == elementsPerGroup.getSize() );
	for (int i = 0; i < m_numNodes;i++)
	{
		int oldGroup = m_parents[i];
		int newGroup = rindex[oldGroup];
		m_parents[i] = newGroup;
	}

	hkLocalBuffer<int> newSizes( numNewGroups );
	{ for (int i = 0; i < numNewGroups; i++){	 newSizes[i] = 0;	} }

	{
		for (int i = 0; i < elementsPerGroup.getSize(); i++)
		{
			int newGroup = rindex[i];
			newSizes[newGroup] += elementsPerGroup[i];
		}
	}

	elementsPerGroup.setSize( numNewGroups );
	{ for (int i = 0; i < numNewGroups; i++){	 elementsPerGroup[i] = newSizes[i];	} }

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
