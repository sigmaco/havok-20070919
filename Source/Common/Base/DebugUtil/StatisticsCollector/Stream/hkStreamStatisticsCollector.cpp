/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Container/Array/hkObjectArray.h>
#include <Common/Base/DebugUtil/StatisticsCollector/Stream/hkStreamStatisticsCollector.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>
#include <Common/Base/Memory/Memory/hkMemory.h>

hkStreamStatisticsCollector::hkStreamStatisticsCollector(int memSize)
: m_stream(memSize) // capacity
{
    m_stream.setSize(0);
}

hkStreamStatisticsCollector::~hkStreamStatisticsCollector()
{

}

union b4
{
    hkUint8 b[2];
    hkUint16 d;
};
inline void _byteSwapUint16( hkUint16& v )
{
    union b4 dataIn;
    union b4 dataOut;

    dataIn.d = v;
    dataOut.b[0] = dataIn.b[1];
    dataOut.b[1] = dataIn.b[0];
    v = dataOut.d;
}

void hkStreamStatisticsCollector::setDataByCopying(const char* buffer, int length, hkBool endianSwap)
{
    m_stream.setSize(length);
    hkString::memCpy( m_stream.begin(), buffer, length);
    if ( endianSwap )
    {
        int curPos = 0;
        while (curPos < m_stream.getSize() )
        {
            Command* c = (Command*)( &(m_stream[curPos]) );
            _byteSwapUint16( c->memSize );
            _byteSwapUint16( c->allocSize );
            curPos += hkSizeOf(Command) + c->slen;
        }
    }
}

static hkStreamStatisticsCollector::Node* _newNode( hkStreamStatisticsCollector::Node* parent, const char* name, int size, int allocSize, hkArray<hkString*>* stringTable)
{
    if ( allocSize == 0 )
    {
        allocSize = size;
    }

    if ( !name ) name = "?";

    hkStreamStatisticsCollector::Node* node = HK_NULL;
    for (int c=0; parent && (c < parent->m_children.getSize()); ++c)
    {
        if (hkString::strCmp(parent->m_children[c]->m_name, name) == 0)
        {
            node = parent->m_children[c];
            break;
        }
    }

    if (!node)
    {
        if (stringTable && name)
        {
            stringTable->pushBack( new hkString(name) );
            name = stringTable->back()->cString();
        }

        node = new hkStreamStatisticsCollector::Node( parent, name, hkMonitorStreamAnalyzer::Node::NODE_TYPE_DIRECTORY );
    }

    // set straight, even if we are resuing, as the _sum func will sort it out if
    // this is a dir etc.
    node->m_value[0] += hkReal(size);
    node->m_value[1] += hkReal(allocSize);
    node->m_count[0] += 1;
    node->m_count[1] += 1;
    return node;
}

static hkStreamStatisticsCollector::Command* _newCommand( hkArray<char>& stream, int nameLen )
{
    char* data;
    if (stream.getSize() > 0)
    {
        data = (&stream.back()) + 1;
    }
    else
    {
        data = &stream.expandOne();
        stream.setSize(0);
    }

    hkStreamStatisticsCollector::Command * newCommand = (hkStreamStatisticsCollector::Command*) data;
    stream.setSize( stream.getSize() + hkSizeOf(hkStreamStatisticsCollector::Command) + nameLen );

    return newCommand;
}

void _sumNodes( hkStreamStatisticsCollector::Node* n, hkArray<hkString*>* stringTable )
{
    if ( n && n->m_children.getSize() )
    {
        // do children
        int c = 0;
        for (c = 0; c < n->m_children.getSize(); c++)
        {
            _sumNodes(n->m_children[c], stringTable);
        }

        // do self
        if ( n->m_value[0] )
        {
            hkStreamStatisticsCollector::Node* self = _newNode( n, "self", (int)n->m_value[0], (int)n->m_value[1], stringTable);
            // so self appears first in list
            if ( n->m_children.back() == self)
            {
                n->m_children.popBack();
                n->m_children.insertAt(0, self );
            }
        }

        // do total sum
        n->m_value[0] = 0;
        n->m_value[1] = 0;
        for (c = 0; c < n->m_children.getSize(); c++)
        {
            hkStreamStatisticsCollector::Node* child = n->m_children[c];
            n->m_value[0] += child->m_value[0];
            n->m_value[1] += child->m_value[1];
        }
    }
}
void hkStreamStatisticsCollector::makeTree(hkArray<Node*>& m_nodesOut, hkArray<hkString*>* stringTable)
{
    // basically do what the simple stat collector does
    // except all in one go based on the current stream.
    hkArray<Node*> currentStack;

    bool haveNodes = m_nodesOut.getSize() > 0;
    Node* node = HK_NULL;
    if (haveNodes)
    {
        node = m_nodesOut[0];
        HK_ON_DEBUG( int diff = hkString::strCmp( node->m_name, "/" ) );
        HK_ASSERT2( 0x6d0d92fa, diff == 0, "Root node give is not the proper root dir.");

        // don't want to goive wrong impression on size..
        while (m_nodesOut.getSize() > 1)
        {
            delete m_nodesOut.back();
            m_nodesOut.popBack();
        }
    }
    else
    {
        node = new Node(HK_NULL, "/", hkMonitorStreamAnalyzer::Node::NODE_TYPE_DIRECTORY );
        m_nodesOut.pushBack(node);
    }

    currentStack.pushBack(node);

    int curPos = 0;
    while (curPos < m_stream.getSize() )
    {
        const Command* c = (const Command*)( &(m_stream[curPos]) );
        const char* name = c->slen > 0? (const char*)(c+1) : HK_NULL;
        int csize = hkSizeOf(Command) + c->slen;

        switch (c->cmd)
        {
        case HK_MEM_STREAM_COMMAND_PUSH:
            {
                Node* cwd  = currentStack.back();
                Node* n = _newNode( cwd, name, c->memSize, c->allocSize, stringTable );
                currentStack.pushBack( n );

                break;
            }

        case HK_MEM_STREAM_COMMAND_CHUNK:
            {
                Node* cwd  = currentStack.back();
                /*Node* node =*/ _newNode( cwd, name, c->memSize, c->allocSize, stringTable );
                break;
            }

        case HK_MEM_STREAM_COMMAND_POP:
            {
                /*Node* node = currentStack.back(); */
                currentStack.popBack();

                // can't sum here as we do multiple push/pop
                // on same node as we reuse nodes for efficency
                // We will do the sums later in a depth first fasion
                break;
            }

        default:
            {
                HK_ASSERT2( 0xf0212f61, 0, "Invalid command stream" );
                return;
            }
        }

        curPos += csize;
    }

    _sumNodes(node, stringTable);
}

void hkStreamStatisticsCollector::writeStatistics( hkOstream& outstream, int reportLevel )
{
    hkArray<Node*> nodes;

    makeTree(nodes);

//  hkMonitorStreamAnalyzer::writeStatistics( outstream, nodes, "hkpWorld", reportLevel);

    while ( nodes.getSize() )
    {
        delete nodes.back();
        nodes.popBack();
    }
}

void hkStreamStatisticsCollector::beginSnapshot( int statisticClasses )
{
    m_knownObjects.clear();
    m_enabledStatisticClasses = statisticClasses;
}

void hkStreamStatisticsCollector::endSnapshot(  )
{
    m_knownObjects.clear();
}

void hkStreamStatisticsCollector::reset()
{
    m_knownObjects.clear();
    m_stream.clear();
}

void hkStreamStatisticsCollector::beginObject( const char* name, StatisticClass statisticClass, const hkReferencedObject* object )
{

}

void hkStreamStatisticsCollector::addChunk( const char* name, StatisticClass statisticClass, const void* chunkAddress, int usedSize, int allocSize)
{
    if ( hasSpace() )
    {
        if ( !( statisticClass & m_enabledStatisticClasses) )
        {
            return;
        }

        if ( usedSize == 0 && allocSize == 0 )
        {
            return;
        }

        int nameLen = 0;
        int extraLen = 0;
        if (name)
        {
            nameLen = hkString::strLen( name ) + 1;// null terminate, and round up to a multiple of two (so that command struct stride is mutiple of 16bits, not a possible 8 (ps2 will crash))
            extraLen = (nameLen % 2); // 0 or 1.
        }

        Command* newCommand = _newCommand(m_stream, nameLen + extraLen);
        newCommand->cmd = HK_MEM_STREAM_COMMAND_CHUNK;
        newCommand->slen = (hkUint8)(nameLen + extraLen);
        newCommand->memSize = (hkUint16)usedSize;
        newCommand->allocSize = (hkUint16)( (allocSize==0)? 0 : hkMemory::getInstance().getAllocatedSize( allocSize ) );

        if (nameLen > 0)
        {
            hkString::memCpy( (char*)(newCommand + 1), name, nameLen);
            if (extraLen) // and an extra null.
            {
                ((char*)(newCommand + 1))[nameLen] = '\0';
            }
        }
    }
}

void hkStreamStatisticsCollector::addChildObject( const char* name, StatisticClass statisticClass, const hkReferencedObject* object )
{
    if ( hasSpace() )
    {
        //
        //  Check for existing objects
        //
        if ( !object )
        {
            return;
        }

        int isKnown = m_knownObjects.getWithDefault( const_cast<hkReferencedObject*>(object), 0 );
        if (isKnown != 0)
        {
            return;
        }

        m_knownObjects.insert( const_cast<hkReferencedObject*>(object), 1 );

        int size = MASK_MEMSIZE & object->m_memSizeAndFlags;

        if ( !( statisticClass & m_enabledStatisticClasses) )
        {
            size = 0;
        }

        int nameLen = 0;
        int extraLen = 0;
        if (name)
        {
            nameLen = hkString::strLen( name ) + 1;// null terminate
            extraLen = (nameLen % 2); // 0 or 1.
        }

        // Push command to house the child
        Command* newCommand = _newCommand(m_stream, nameLen + extraLen);
        newCommand->cmd = HK_MEM_STREAM_COMMAND_PUSH;
        newCommand->slen = (hkUint8)(nameLen + extraLen);
        newCommand->memSize =(hkUint16)size;
        newCommand->allocSize = (hkUint16)( (size==0)? 0 : hkMemory::getInstance().getAllocatedSize( size ) );
        if (nameLen > 0)
        {
            hkString::memCpy( (char*)(newCommand + 1), name, nameLen);
            if (extraLen) // and an extra null.
            {
                ((char*)(newCommand + 1))[nameLen] = '\0';
            }
        }

        // the child
        object->calcStatistics( this );

        // the pop.
        popDir();
    }
}

void hkStreamStatisticsCollector::pushDir( const char* dirName )
{
    if ( hasSpace() )
    {
        int nameLen = 0;
        int extraLen = 0;
        if (dirName)
        {
            nameLen = hkString::strLen( dirName ) + 1;// null terminate
            extraLen = (nameLen % 2); // 0 or 1.
        }

        Command* newCommand = _newCommand(m_stream, nameLen + extraLen);
        newCommand->cmd = HK_MEM_STREAM_COMMAND_PUSH;
        newCommand->slen = (hkUint8)(nameLen + extraLen);
        newCommand->memSize = 0;
        newCommand->allocSize = 0;
        if (nameLen > 0)
        {
            hkString::memCpy( (char*)(newCommand + 1), dirName, nameLen);
            if (extraLen) // and an extra null.
            {
                ((char*)(newCommand + 1))[nameLen] = '\0';
            }
        }
    }
}

void hkStreamStatisticsCollector::popDir()
{
    if ( hasSpace() )
    {
        Command* newCommand = _newCommand(m_stream, 0);
        newCommand->cmd = HK_MEM_STREAM_COMMAND_POP;
        newCommand->slen = 0;
        newCommand->memSize = 0;
        newCommand->allocSize = 0;
    }
}

void hkStreamStatisticsCollector::endObject( )
{
    // do nothing.
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
