/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Serialize/UnitTest/taggedunion/taggedunion.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Serialize/Serialize/Xml/hkXmlObjectWriter.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>
#include <Common/Base/System/Io/StreambufFactory/hkStreambufFactory.h>
#include <Common/Base/System/Io/Writer/Printf/hkPrintfStreamWriter.cxx>

class hkTaggedUnionArrayWalker
{
	public:

		hkTaggedUnionArrayWalker(const hkClass* c)
		{
			m_tagSizeInBytes = c->getDeclaredMember(0).getStructClass().getDeclaredMember(0).getSizeInBytes();
			const hkClassEnum& e = c->getEnum(0);
			for( int i = 0; i < e.getNumItems(); ++i )
			{
				const char* name = e.getItem(i).getName();
				if( const hkClassMember* m = c->getMemberByName(name) )
				{
					m_map.insert( e.getItem(i).getValue(), &m->getStructClass() );
				}
			}
		}

		const hkClass* getClassFromStream(const void* p)
		{
			int val = 0;
			switch( m_tagSizeInBytes )
			{
				case 1: val = static_cast<const hkUint8*>(p)[0]; break;
				case 2: val = static_cast<const hkUint16*>(p)[0]; break;
				case 4: val = static_cast<const hkUint32*>(p)[0]; break;
			}
			return val
				? m_map.getWithDefault(val, HK_NULL)
				: HK_NULL;
		}

		hkPointerMap<int, const hkClass*> m_map;
		int m_tagSizeInBytes;
};

int taggedUnionTest()
{
	{
		char buffer[8192];
		hkString::memSet( buffer, 0, sizeof(buffer));
		{
			// create a dummy stream
			void* p = buffer;
			p = (new (p) hkTypeOne)+1;
			p = (new (p) hkAfterGap)+1;
			p = (new (p) hkTypeTwo)+1;
			p = (new (p) hkTypeTwo)+1;
			p = (new (p) hkTypeOne)+1;
			*(hkUint32*)p = 0;
		}
		extern const hkClass hkSimpleUnion3Class;
		hkTaggedUnionArrayWalker walker(&hkSimpleUnion3Class);
		hkXmlObjectWriter::SequentialNameFromAddress namer;
		hkXmlObjectWriter writer( namer );
		hkPrintfStreamWriter output(hkStreambufFactory::STDOUT);

		// walk the buffer
		void* p = buffer;
		while( const hkClass* c = walker.getClassFromStream(p) )
		{
			writer.writeObjectWithElement(&output, p, *c, HK_NULL);
			p = hkAddByteOffset(p, c->getObjectSize());
		}		
	}
	return 0;
}
HK_TEST_REGISTER(taggedUnionTest, "Fast", "Common/Test/UnitTest/Serialize/", __FILE__     );

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
