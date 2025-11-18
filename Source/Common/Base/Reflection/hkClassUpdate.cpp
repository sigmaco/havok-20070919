/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>

typedef hkPointerMap<const hkClass*, hkInt32> UpdateFlagFromClassMap;
extern const hkClass hkClassVersion1Class;

namespace
{
	enum
	{
		UPDATED_NONE = 0,
		UPDATED_CLASS1_VERSION = 1 << 0 , // hkBool hasVtable -> m_defaults
		UPDATED_TYPE_CSTRING = 1 << 1, // POINTER CHAR -> CSTRING
		UPDATED_CONSTRAINT_INSTANCE_300 = 1 << 2, // incorrect metadata
		UPDATED_ENUM_SIZE_AND_TYPE_ZERO = 1 << 3 // size in flags -> size in subtype
	};

	typedef void (*ForEachMemberFunc)(hkClassMember&);
	static void walkMembers(
		hkClass* klass,
		UpdateFlagFromClassMap& updateFlagFromClass,
		int walkingFlag,
		ForEachMemberFunc memberCallback )
	{
		hkInt32 updateFlags = updateFlagFromClass.getWithDefault( klass, UPDATED_NONE );
		if( (updateFlags & walkingFlag) == 0 )
		{
			updateFlagFromClass.insert( klass, updateFlags | walkingFlag );

			for (int i = 0; i < klass->getNumDeclaredMembers(); i++)
			{
				const hkClassMember& klassMem = klass->getDeclaredMember(i);
				if( const hkClass* c = klassMem.getClass() )
				{
					walkMembers( const_cast<hkClass*>(c), updateFlagFromClass, walkingFlag, memberCallback );
				}
				memberCallback( *const_cast<hkClassMember*>( &klassMem ) );
			}

			if (klass->getParent() != HK_NULL)
			{
				walkMembers( klass->getParent(), updateFlagFromClass, walkingFlag, memberCallback );
			}
		}
	}

	static void updatePointerCharToCString( hkClassMember& klassMem )
	{
		if (klassMem.getType() == hkClassMember::TYPE_POINTER
			&& klassMem.getSubType() == hkClassMember::TYPE_CHAR)
		{
			klassMem.setType(hkClassMember::TYPE_CSTRING);
			klassMem.setSubType(hkClassMember::TYPE_VOID);
		}
	}

	static void updateClassVersion1Inplace( hkClass* classInOut, UpdateFlagFromClassMap& updateFlagFromClass )
	{
		hkInt32 updateFlags = updateFlagFromClass.getWithDefault( classInOut, UPDATED_NONE );

		if( (updateFlags & UPDATED_CLASS1_VERSION) == 0 )
		{
			updateFlagFromClass.insert( classInOut, updateFlags | UPDATED_CLASS1_VERSION );

			int voff = hkClassVersion1Class.getMemberByName("hasVtable")->getOffset();
			hkClass* k = classInOut;
			while( k->getParent() != HK_NULL )
			{
				*reinterpret_cast<void**>( reinterpret_cast<char*>(k) + voff) = HK_NULL;
				k = const_cast<hkClass*>( k->getParent() );
			}
			hkBool hasVtable = *(reinterpret_cast<char*>(k) + voff) != 0;
			if( hasVtable )
			{
				int ioff = hkClassVersion1Class.getMemberByName("numImplementedInterfaces")->getOffset();
				*reinterpret_cast<int*>( reinterpret_cast<char*>(k) + ioff ) += 1;
			}
			*reinterpret_cast<void**>( reinterpret_cast<char*>(k) + voff) = HK_NULL;
		
			for (int i = 0; i < classInOut->getNumDeclaredMembers(); i++)
			{
				const hkClassMember& klassMem = classInOut->getDeclaredMember(i);
				if (klassMem.hasClass())
				{
					updateClassVersion1Inplace( const_cast<hkClass*>(&klassMem.getStructClass()), updateFlagFromClass );
				}
			}

			if (classInOut->getParent() != HK_NULL)
			{
				updateClassVersion1Inplace( classInOut->getParent(), updateFlagFromClass );
			}
		}
	}

	static void updateConstraintInstance300( const hkClass* classInOut, UpdateFlagFromClassMap& updateFlagFromClass )
	{
		hkInt32 updateFlags = updateFlagFromClass.getWithDefault( classInOut, UPDATED_NONE );
		if( (updateFlags & UPDATED_CONSTRAINT_INSTANCE_300) == 0 )
		{
			updateFlagFromClass.insert( classInOut, updateFlags | UPDATED_CONSTRAINT_INSTANCE_300 );

			if( hkString::strCmp( classInOut->getName(), "hkpConstraintInstance" ) == 0 )
			{
				const hkClassMember& mem = classInOut->getDeclaredMember(2);
				HK_ASSERT( 0, hkString::strCmp("entities", mem.getName()) == 0);
				hkUint8* memp = reinterpret_cast<hkUint8*>( const_cast<hkClassMember*>(&mem) );
				memp[ hkClassMemberClass.getMember(4).getOffset() ] = hkClassMember::TYPE_STRUCT;
			}
		}
	}

	static void updateEnumSizeAndTypeZero(hkClassMember& member)
	{
		if( member.getType() == hkClassMember::TYPE_ZERO )
		{
			member.setType( member.getSubType() );
			member.setSubType( hkClassMember::TYPE_VOID );
			member.getFlags().orWith( hkClassMember::SERIALIZE_IGNORED );
		}
		if( member.getType() == hkClassMember::TYPE_ENUM || member.getType() == hkClassMember::TYPE_FLAGS )
		{
			hkInt16 replacements[][2] =	{
				{ hkClassMember::DEPRECATED_SIZE_8, hkClassMember::TYPE_UINT8 },
				{ hkClassMember::DEPRECATED_SIZE_16, hkClassMember::TYPE_UINT16 },
				{ hkClassMember::DEPRECATED_SIZE_32, hkClassMember::TYPE_UINT32 } };

			for( int i = 0; i < HK_COUNT_OF(replacements); ++i )
			{
				if( member.getFlags().get(replacements[i][0]) )
				{
					member.setSubType( static_cast<hkClassMember::Type>(replacements[i][1]) );
					member.getFlags().andWith( ~replacements[i][0] );
				}
			}
		}
	}
}

void hkClass::updateMetadataInplace( hkClass* c, UpdateFlagFromClassMap& updated, int sourceVersion )
{
	if( sourceVersion == 1 )
	{
		updateClassVersion1Inplace( c, updated );
		updateConstraintInstance300( c, updated );
	}
	if( sourceVersion < 4 )
	{
		walkMembers( c, updated, UPDATED_TYPE_CSTRING, updatePointerCharToCString );
	}
	if( sourceVersion < 5 )
	{
		walkMembers( c, updated, UPDATED_ENUM_SIZE_AND_TYPE_ZERO, updateEnumSizeAndTypeZero );
	}
}

void hkClass::updateMetadataInplace( hkClass** c, int sourceVersion )
{
	UpdateFlagFromClassMap updated;
	for( int i = 0; c[i] != HK_NULL; ++i )
	{
		hkClass::updateMetadataInplace(c[i], updated, sourceVersion );
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
