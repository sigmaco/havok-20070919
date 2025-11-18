/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Container/BitField/hkBitField.h>

void hkBitField::setSize( int numBits, int fillValue )
{
	HK_ASSERT( 0xa59289bc, fillValue >= 0 && fillValue <= 1 );

	int newNumWords = ( numBits + 31 ) >> 5;

	if( numBits == 0 )
	{
		// The bit field is non empty and requested size is zero.
		if( m_words != HK_NULL )
		{
			if ( shouldDeallocate() )
			{
				hkThreadMemory::getInstance().deallocateChunk( m_words, 4 * m_numWords, HK_MEMORY_CLASS_ARRAY );
			}

			m_words = HK_NULL;
		}
	}
	else 
	{
		// The bit field is empty. Allocate new memory block and fill it with 'value'
		if( m_words == HK_NULL )
		{
			m_words = static_cast<hkUint32*>( hkThreadMemory::getInstance().allocateChunk( 4 * newNumWords, HK_MEMORY_CLASS_ARRAY ) );
			m_numWords = newNumWords;

			assignAll( fillValue );
		}
		else
		{
			// The bit filled is non-empty and requested size requires more memory.
			if( newNumWords > m_numWords )
			{
				hkUint32* newWords = static_cast<hkUint32*>( hkThreadMemory::getInstance().allocateChunk( 4 * newNumWords, HK_MEMORY_CLASS_ARRAY ) );

				hkString::memCpy( newWords, m_words, m_numWords * sizeof( hkUint32 ) );

				if ( shouldDeallocate() )
				{
					hkThreadMemory::getInstance().deallocateChunk( m_words, 4 * m_numWords, HK_MEMORY_CLASS_ARRAY );
				}
	
				m_words = newWords;

				hkUint32 fill = fillValue ? 0xffffffff : 0;

				fillUnusedBits( fillValue );

				for( int i = m_numWords; i < newNumWords; ++i )
				{
					m_words[ i ] = fill;
				}
			}
			// The bit filled is non-empty and requested size requires less memory.
			else if( newNumWords < m_numWords )
			{
				hkUint32* newWords = static_cast<hkUint32*>( hkThreadMemory::getInstance().allocateChunk( 4 * newNumWords, HK_MEMORY_CLASS_ARRAY ) );

				hkString::memCpy( newWords, m_words, newNumWords * sizeof( hkUint32 ));

				if ( shouldDeallocate() )
				{
					hkThreadMemory::getInstance().deallocateChunk( m_words, 4 * m_numWords, HK_MEMORY_CLASS_ARRAY );
				}

				m_words = newWords;

			}
			// The bit field is non-empty, and requested size requires no extra memory.
			else
			{
				if( getSize() < numBits )
				{
					fillUnusedBits( fillValue );
				}

				// since we didn't reallocate, keep the old deallocate flag
				m_numBitsAndFlags = numBits | ( m_numBitsAndFlags & DONT_DEALLOCATE_FLAG );

				return;
			}
		}
	}

	// since we reallocated, we clear the DONT_DEALLOCATE_FLAG
	m_numBitsAndFlags = numBits;
	m_numWords = newNumWords;
}

void hkBitField::fillUnusedBits( int fillValue )
{
	HK_ASSERT( 0xf25ad34b, getSize() > 0 );

	int arrayIndex = (getSize() - 1) >> 5;
	hkUint32& word = m_words[arrayIndex];

	int usedBitsInLastWord = getSize() - (arrayIndex << 5);

	if( usedBitsInLastWord < 32 )
	{
		int a = 0xffffffff;
		a <<= usedBitsInLastWord;

		if( fillValue == 0 )
		{
			a = ~a;
			word &= a;
		}
		else
		{
			word |= a;
		}
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
