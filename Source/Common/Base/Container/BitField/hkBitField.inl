/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

HK_FORCE_INLINE void hkBitField::assignAll( int value )
{
	HK_ASSERT( 0xa59289bb, value >= 0 && value <= 1 );

	hkUint32 fill = value ? 0xffffffff : 0;

	for( int i = 0; i < m_numWords; i++ )
	{
		m_words[i] = fill;
	}
}

HK_FORCE_INLINE hkBool32 hkBitField::shouldDeallocate() const
{
	return ( ( m_words != HK_NULL ) && !( m_numBitsAndFlags & DONT_DEALLOCATE_FLAG ) );
}

HK_FORCE_INLINE hkBitField::hkBitField( int numBits )
:	m_numWords( ( numBits + 31 ) >> 5 ),
	m_numBitsAndFlags(numBits)
{
	if ( m_numWords )
	{
		m_words = static_cast<hkUint32*>( hkThreadMemory::getInstance().allocateChunk( 4 * m_numWords, HK_MEMORY_CLASS_ARRAY ) );
	}
	else
	{
		m_words = HK_NULL;
	}
}

HK_FORCE_INLINE hkBitField::hkBitField( int numBits, int initialValue )
:	m_numWords( ( numBits + 31 ) >> 5 ),
	m_numBitsAndFlags(numBits)
{
	HK_ASSERT( 0xa63ab345, initialValue >= 0 && initialValue <= 1 );

	if ( m_numWords )
	{
		m_words = static_cast<hkUint32*>( hkThreadMemory::getInstance().allocateChunk( 4 * m_numWords, HK_MEMORY_CLASS_ARRAY ) );
	}
	else
	{
		m_words = HK_NULL;
	}

	assignAll( initialValue );
}

HK_FORCE_INLINE hkBitField::~hkBitField()
{
	if( shouldDeallocate() )
	{
		hkThreadMemory::getInstance().deallocateChunk( m_words, 4 * m_numWords, HK_MEMORY_CLASS_ARRAY );
	}
}

HK_FORCE_INLINE int hkBitField::get( int index )
{
	HK_ASSERT( 0x48d17bd3, index >= 0 && index < getSize() );

	int arrayIndex = index >> 5;
	return ( ( m_words[arrayIndex] >> ( index & 0x1f ) ) & 1 );
}

HK_FORCE_INLINE void hkBitField::set( int index )
{
	HK_ASSERT( 0x48a97bc3, index >= 0 && index < getSize() );

	int arrayIndex = index >> 5;
	m_words[arrayIndex] |= ( 1 << ( index & 0x1f ) );
}

HK_FORCE_INLINE void hkBitField::clear( int index )
{
	HK_ASSERT( 0x38a87bb3, index >= 0 && index < getSize() );

	int arrayIndex = index >> 5;
	m_words[arrayIndex] &= ~( 1 << ( index & 0x1f ) );
}

HK_FORCE_INLINE void hkBitField::assign( int index, int value )
{
	HK_ASSERT( 0x48a27b13, index >= 0 && index < getSize() );
	HK_ASSERT( 0xe68bb345, value >= 0 && value <= 1 );

	int arrayIndex = index >> 5;
	hkUint32 mask = 1 << (index & 0x1f);

	m_words[arrayIndex] = ( m_words[arrayIndex] & ~mask ) | ( mask & ~( value - 1 ) );
}



HK_FORCE_INLINE int hkBitField::getSize() const
{
	return ( m_numBitsAndFlags & NUM_BITS_MASK );
}

HK_FORCE_INLINE hkBitField::hkBitField( hkFinishLoadedObjectFlag flag )
{
	if ( flag.m_finishing )
	{
		m_numBitsAndFlags |= DONT_DEALLOCATE_FLAG;
	}
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
