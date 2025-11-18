/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>
#include <Common/Base/System/Io/Reader/hkStreamReader.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Container/Tree/hkTree.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Serialize/Util/Xml/hkXmlParser.h>

const char* hkXmlParser::StartElement::getAttribute( const char* a, const char* d )
{
	for(int i = 0; i < attributes.getSize(); ++i)
	{
		if( attributes[i].name == a )
		{
			return attributes[i].value.cString();
		}
	}
	return d;
}

hkResult hkXmlParser::Characters::canonicalize(const char* spaceChars)
{
	hkLocalArray<char> buf( text.getLength() + 1 );
	int l = hkXmlParser::canonicalize(buf.begin(), text.cString(), spaceChars);
	if( l != -1 )
	{
		text = buf.begin();
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

#define RETURN_VALUE_IF(test, value) \
	if( test ) { return value; }
#define RETURN_FAILURE_IF(test, msg) \
	if( test ) { m_lastError.printf msg; return HK_FAILURE; }
#define RETURN_VALUE_IF2(id, test, msg, value) \
	if( test ) { HK_WARN(id, msg); return value; }
#define RETURN_VALUE_IF2_VOID(id, test, msg) \
	if( test ) { HK_WARN(id, msg); return; }


/*static hkOstream& operator<<(hkOstream& os, const hkXmlParser::Node& n)
{
	if( n.type == hkXmlParser::CHARACTERS )
	{
		os << "Characters (" << static_cast<const hkXmlParser::Characters&>(n).text << ")";
	}
	else if( n.type == hkXmlParser::START_ELEMENT )
	{
		const hkXmlParser::StartElement& e = static_cast<const hkXmlParser::StartElement&>(n);
		os << "StartElement (" << e.name << ") ";
		for( int i = 0; i < e.attributes.getSize(); ++i )
		{
			os << e.attributes[i].name << "=" << e.attributes[i].value << " ";
		}
	}
	else if( n.type == hkXmlParser::END_ELEMENT )
	{
		const hkXmlParser::EndElement& e = static_cast<const hkXmlParser::EndElement&>(n);
		os << "EndElement (" << e.name << ") ";
	}
	else
	{
		os << "Unknown node (" << n.type << ") ";
	}
	return os;
}*/

int hkXmlParser::translateEntities(char* dst, const char* src)
{
	char* d = dst;
	const char* s = src;
	while( *s )
	{
		char c = *s++;
		if( c == '&' )
		{
			const char* p = s;
			while( *s != ';' )
			{
				RETURN_VALUE_IF2( 0x4687f511, *s == 0, "Invalid entity '" << p << "'", -1 );
				++s;
			}
			s++;
			if( p[0] == '#' )
			{
				char num[10];
				int len = static_cast<int>(s - p) - 2;
				RETURN_VALUE_IF2( 0x5d0c3135, len >= hkSizeOf(num), "Invalid numeric entity '" << p << "'", -1 );
				hkString::strNcpy(num, p+1, len);
				num[len] = 0;
				int val = hkString::atoi(num);
				if( val > 255 && val!=9216 )  // by now 9216 is truncated to 0 ( UNICODE for NULL ) that is what we need 
				{
					HK_WARN(0x3bbc92b0, "Truncated numeric entity '" << val << "'");
				}
				*d++ = char(val);
			}
			else
			{
				const char* entities[] = { "<lt", ">gt", "&amp", "\"quot", "'apos", HK_NULL };
				int i;
				for( i = 0; entities[i] != HK_NULL; ++i )
				{
					char entity = entities[i][0];
					const char* entname = entities[i]+1;
					if( hkString::strNcmp( p, entname, hkString::strLen(entname) ) == 0 )
					{
						*d++ = entity;
						break;
					}
				}
				RETURN_VALUE_IF2( 0x20d1742c, entities[i] == HK_NULL, "Unknown entity '" << p << "'", -1);
			}
		}
		else
		{
			*d++ = c;
		}
	}
	*d = 0;
	return int(d-dst);
}

static inline bool inString(char c, const char* s)
{
	if(s)
	{
		while(*s)
		{
			if( c==*s++)
			{
				return true;
			}
		}
	}
	return false;
}

// Replace "spaceChars" with a single space then normalize whitespace.
// It is ok for dst==src as at all times len(dst)<=len(src)
int hkXmlParser::canonicalize(char* dst, const char* src, const char* spaceChars)
{
	char* d = dst;
	const char* s = src;
	hkBool inspace = true;
	while( *s )
	{
		char c = *s++;
		if( (  (c == ' ') || (c == '\t')
			|| (c == '\n') || (c == '\r') )
			|| inString(c, spaceChars) )
		{
			if( inspace == false )
			{
				*d++ = ' ';
				inspace = true;
			}
		}
		else
		{
			inspace = false;
			*d++ = c;
		}
	}
	if( d != dst && inspace)
	{
		d[-1] = 0;
	}
	else
	{
		*d = 0;
	}
	return int(d-dst);
}

static inline hkBool isSpace(char c)
{
	return (c==' ') || (c =='\t') || (c=='\n') || (c=='\r');
}

static const char* eatWhite(const char* p)
{
	while( isSpace(*p) )
	{
		++p;
	}
	return p;
}

static hkResult extractAttributes( const char* buf, hkObjectArray<hkXmlParser::Attribute>& attrs )
{
	const char* p = buf;
	while(1)
	{
		p = eatWhite(p);

		if( *p == 0 )
		{
			return HK_SUCCESS; // return
		}

		hkXmlParser::Attribute attr;

		// extract attribute name
		{
			const char* startName = p;
			while( (isSpace(*p) == false) && (*p != '=') )
			{
				RETURN_VALUE_IF2( 0x79a36cf5, *p++ == 0, "Missing '=' in attribute at '" << startName << "'", HK_FAILURE);
			}
			attr.name = hkString(startName, hkGetByteOffsetInt(startName, p));
		}

		// skip " = " with possible whitespace
		{
			p = eatWhite(p);
			RETURN_VALUE_IF2(0x6657b1ec, *p != '=', "Equals must follow attribute name", HK_FAILURE);
			++p; // skip =
			p = eatWhite(p);
			RETURN_VALUE_IF2(0x6657b1eb, *p != '"', "Quote must follow '='", HK_FAILURE);
			++p; // skip "
		}
		
		// extract attribute value
		{
			const char* startValue = p;
			while( *p != '"') // get value
			{
				RETURN_VALUE_IF2( 0x76582703, *p++ == 0, "Missing closing '\"' in attribute at " << startValue, HK_FAILURE);
			}
			attr.value = hkString(startValue, hkGetByteOffsetInt(startValue,p) );
			attrs.pushBack(attr);
			++p; // skip "
		}
	}
}

hkXmlParser::hkXmlParser()
{
}

hkXmlParser::~hkXmlParser()
{
	for( int i = 0; i < m_pendingNodes.getSize(); ++i )
	{
		delete m_pendingNodes[i];
	}
}

// eat chars up to closing tag >, putting them into tag if not null.
static void eatTag(char* buf, int bufSize, int bufCapacity, hkStreamReader* sb, hkArray<char>* tag = HK_NULL )
{
	int i = 0;
	while(1)
	{
		while( i < bufSize && buf[i] != '>' )
		{
			++i;
		}
		if( tag )
		{
			tag->insertAt( tag->getSize(), buf, i );
		}
		if( i != bufSize ) // got end >
		{
			sb->rewindToMark();
			sb->skip( i+1 );
			break;
		}
		else // refill
		{
			sb->setMark(bufCapacity);
			bufSize = sb->read( buf, bufCapacity);
			RETURN_VALUE_IF2_VOID( 0x7bde7263, bufSize == 0, "Premature EOF." );
			i = 0;
		}
	}
}

// eat chars up to but not including closing tag <, putting them into text
static void eatText(char* buf, int bufSize, int bufCapacity, hkStreamReader* sb, hkArray<char>& text )
{
	HK_ASSERT( 0x7733d613, bufSize && buf[0] != '<');
	int i = 0;
	while(1)
	{
		while( i < bufSize && buf[i] != '<' )
		{
			++i;
		}
		{
			text.insertAt( text.getSize(), buf, i );
		}

		if( i != bufSize ) // got to <
		{
			sb->rewindToMark();
			sb->skip( i );
			break;
		}
		else // refill if possible
		{
			sb->setMark(bufCapacity);
			bufSize = sb->read( buf, bufCapacity);
			if( bufSize == 0 )
			{
				break;
			}
			i = 0;
		}
	}
}

static void eatComment(char* buf, int bufSize, int bufCapacity, hkStreamReader* sb )
{
	int i = 0;
	const char comment[] = "-->";
	int commentPos = 0;
	while(1)
	{
		while( i < bufSize )
		{
			if( buf[i] == comment[commentPos] )
			{
				if( comment[++commentPos] == 0 ) // end comment
				{
					break;
				}
			}
			else if( buf[i] == '-' )
			{
				// handle ------>
			}
			else
			{
				commentPos = 0; // back to square 1
			}
			++i;
		}
		if( i != bufSize ) // got end -->
		{
			sb->rewindToMark();
			sb->skip( i+1 );
			break;
		}
		else // refill
		{
			sb->setMark(bufCapacity);
			bufSize = sb->read( buf, bufCapacity);
			RETURN_VALUE_IF2_VOID( 0x7bde7263, bufSize == 0, "Premature EOF." );
			i = 0;
		}
	}
}

hkResult hkXmlParser::nextNode( Node** ret, hkStreamReader* reader )
{
	hkIstream is(reader);
	if( m_pendingNodes.getSize() != 0 )
	{
		*ret = m_pendingNodes.back();
		m_pendingNodes.popBack();
		return HK_SUCCESS;		
	}

	*ret = HK_NULL;
	if( is.isOk() == false )
	{
		m_lastError = "End of stream";
		return HK_FAILURE;
	}

	const int MAX_BUF_SIZE = 32;
	int bufSize = 0;
	char buf[MAX_BUF_SIZE];
	hkStreamReader* sb = is.getStreamReader();

	hkArray<char> pendingChars;

	while(1)
	{
		sb->setMark(MAX_BUF_SIZE);
		bufSize = sb->read( buf, MAX_BUF_SIZE );
		RETURN_FAILURE_IF( bufSize == 0 || (buf[0] == '<' && bufSize < 2),
			("premature end of stream") );

		if(buf[0] == '<')
		{
			// Begin tag - 4 cases
			//        end of file (handled above)
			// !--    comment
			// ?      processing instruction
			// chars  normal begin tag

			if( buf[1] == '?' ) // processing instruction
			{
				eatTag( buf, bufSize, MAX_BUF_SIZE, sb );
			}
			else if( bufSize >= 4 && hkString::strNcmp("!--", buf+1, 3) == 0 ) // comment
			{
				eatComment( buf, bufSize, MAX_BUF_SIZE, sb );
			}
			else if( pendingChars.getSize() != 0 )
			{
				sb->rewindToMark(); // don't consume the <
				int i;
				for( i = 0; i < pendingChars.getSize(); ++i )
				{
					if( isSpace(pendingChars[i]) == false )
					{
						break;
					}
				}
				if( i != pendingChars.getSize() )
				{
					pendingChars.pushBack(0);
					char* s = pendingChars.begin();
					int l = translateEntities(s, s);
					*ret = new hkXmlParser::Characters(s, l);
					return HK_SUCCESS;
				}
				pendingChars.clear();
			}
			else // a real tag
			{
				hkArray<char> tag;
				eatTag( buf, bufSize, MAX_BUF_SIZE, sb, &tag);
				RETURN_FAILURE_IF( tag.getSize() == 0, ("Empty tag") );
				tag.pushBack(0);
				char* tagBegin = tag.begin();
				int tagLen = translateEntities(tagBegin, tagBegin);
				RETURN_FAILURE_IF( tagLen == -1, ("Bad tag") );
				tag.setSizeUnchecked(tagLen);

				if( tag[1] == '/' ) // an end tag
				{
					hkString endtag = tag.begin() + 2;
					*ret = new hkXmlParser::EndElement(endtag);
					return HK_SUCCESS;
				}

				// else a begin tag
				hkBool emptyElement = tag.back() == '/';
				if( emptyElement )
				{
					tag.back() = 0;
					tag.popBack();
				}
					
				int space = 0;
				while( space < tag.getSize() && tag[space] != ' ')
				{
					++space;
				}
					
				hkObjectArray<Attribute> attributes;
				if( space != tag.getSize() )
				{
					if( extractAttributes( tag.begin()+space, attributes ) == HK_FAILURE )
					{
						RETURN_FAILURE_IF(0, ("Cannot extract attributes") );
					}
					tag[space] = 0;
					tag.setSizeUnchecked(space);
				}
				const char* tagName = tag.begin() + 1;
				hkXmlParser::StartElement* n = new hkXmlParser::StartElement(tagName);
				n->attributes.swap( attributes );
					
				if( emptyElement ) // save the virtual end element for next call
				{
					putBack( new hkXmlParser::EndElement(tagName) );
				}

				*ret = n;
				return HK_SUCCESS;
			}
		}
		else // possibly text node
		{
			// Don't return characters yet. Add to pending chars and return them
			// when we get a real buf. e.g. <foo>some text<!-- comment -->moretext</foo>
			// will return one chars element as if the comment did not exist.
			eatText( buf, bufSize, MAX_BUF_SIZE, sb, pendingChars );
		}
	}
	return HK_SUCCESS;
}

void hkXmlParser::putBack( Node* node )
{
	m_pendingNodes.pushBack(node);
}

hkResult hkXmlParser::expandNode( StartElement* top, hkTree<Node*>& tree, hkStreamReader* reader )
{
	hkIstream is(reader);
	tree.clear();
	hkTree<Node*>::Iter iter = tree.append(tree.iterGetRoot(), top);
	hkXmlParser::Node* n = HK_NULL;
	while( (nextNode(&n, reader) == HK_SUCCESS) )
	{
		if(n == HK_NULL)
		{
			return HK_SUCCESS;
		}
		switch( n->type )
		{
			case START_ELEMENT:
			{
				iter = tree.append(iter, n);
				break;
			}
			case END_ELEMENT:
			{
				hkXmlParser::Node* s = tree.getValue(iter);
				StartElement* se = static_cast<StartElement*>(s);
				EndElement* ee = static_cast<EndElement*>(n);
				
				RETURN_FAILURE_IF( se->type == START_ELEMENT && se->name != ee->name,
					("Expected tag to end '%s' but got '%s'", se->name.cString(), ee->name.cString() ) );
				RETURN_FAILURE_IF( se->type != hkXmlParser::START_ELEMENT,
					("Unexpected end tag '%s'", ee->name.cString() ) );

				iter = tree.iterParent(iter);
				//tree.append(iter, n); // end elements in tree are waste of space.
				delete n;

				if( iter == HK_NULL )
				{
					return HK_SUCCESS;
				}
				
				break;
			}
			case CHARACTERS:
			{
				tree.append(iter, n);
				break;
			}
			default:
			{
				HK_ASSERT(0x18cb354d, 0); // unreachable
			}
		}
	}
	if( iter != HK_NULL )
	{
		m_lastError.printf("Missing closing tag of '%s'", tree.getValue(iter)->asStart()->name.cString() );
	}
	return HK_FAILURE;
}

hkResult hkXmlParser::parse( hkTree<Node*>& tree, hkStreamReader* reader )
{
	Node* n;
	RETURN_VALUE_IF( nextNode(&n, reader) != HK_SUCCESS, HK_FAILURE );
	RETURN_VALUE_IF( n == HK_NULL, HK_SUCCESS ); // empty doc is ok
	RETURN_FAILURE_IF( n->type != hkXmlParser::START_ELEMENT,
		("Document does not start with an element.") ;);
		
	StartElement* se = static_cast<StartElement*>(n);
	return expandNode(se, tree, reader);
}

const char* hkXmlParser::getLastError() const
{
	return m_lastError.cString();
}

//
// test program
//

#if 0
static void destroyXmlNode(void* p)
{
	hkXmlParser::Node* n = *static_cast<hkXmlParser::Node**>(p);
	delete n;
}

int main()
{
	hkBaseSystem::init();
	{
		typedef hkTree<hkXmlParser::Node*> Tree;
		Tree tree(destroyXmlNode);
		hkIstream is("hkpRigidBodyCinfo.xml");
		hkXmlParser xml;
		
		if(0)
		{
			int level = 0;
			hkXmlParser::Node* n;
			while( (xml.nextNode(is, &n) == HK_SUCCESS) && (n != HK_NULL) )
			{
				level -= n->type == hkXmlParser::END_ELEMENT;
				for(int i = 0; i< level; ++i )
					hkcout << ' ';
				hkcout << *n << '\n';
				level += n->type == hkXmlParser::START_ELEMENT;
				delete n;
			}
		}
		else if(1)
		{
			xml.parse(is, tree);

			Tree::Iter it = tree.iterGetRoot();
			if(1)
			{
				hkcout << "----\n";
				while( it != HK_NULL )
				{
					for(int i = 0; i < tree.getDepth(it); ++i )
						hkcout << "  ";
					hkXmlParser::Node* x = tree.getValue(it);
					hkcout << *x << '\n';
					it = tree.iterNextPreOrder(it);
				}
			}
		}
		else
		{
			hkXmlParser::Node* n;
			while( (xml.nextNode(is, &n) == HK_SUCCESS) && (n != HK_NULL) )
			{
				if(n->type == hkXmlParser::START_ELEMENT )
				{
					hkXmlParser::StartElement* se = static_cast<hkXmlParser::StartElement*>(n);
					if( se->name == "enum" )
					{
						xml.expandNode(is, se, tree);
						hkTree<hkXmlParser::Node*>::Iter iter = tree.iterGetRoot();
						while( iter != HK_NULL )
						{
							for(int i = 0; i< tree.getDepth(iter); ++i )
								hkcout << ' ';
							hkcout << *tree.getValue(iter) << '\n';
							iter = tree.iterNextPreOrder(iter);
						}
						break;
					}
				}
				delete n;
			}
		}
	}
	hkBaseSystem::quit();

	return 0;
}
#endif

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
