/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Base/hkBase.h>

#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>
#include <Common/Base/Reflection/hkClassMemberAccessor.h>


#include <Common/Base/Memory/Memory/hkMemory.h>

#include <Common/Base/DebugUtil/StatisticsCollector/Util/hkStatisticsCollectorUtil.h>


hkStatisticsCollectorClassListener*
hkStatisticsCollectorUtil::_ensureListener(hkStatisticsCollectorClassListener* listener)
{
    if (listener) { return listener; }
    return &hkStatisticsCollectorClassListener::getInstance();
}

const hkClass*
hkStatisticsCollectorUtil::_getClass(void* in)
{
	// First we need to find the type
	const hkClass* cls = hkVtableClassRegistry::getInstance().getClassFromVirtualInstance(in);
    HK_ASSERT2(0x342423,"The object must be a hkReferencedObject derived and be registered",cls);

    return cls;
}

void
hkStatisticsCollectorUtil::_addCstring(const hkClassMember& mem,char* string,hkStatisticsCollector::StatisticClass cls,hkStatisticsCollector* collector)
{
    if (string == HK_NULL) { return; }

	int used = hkString::strLen(string)+1;
	int allocated = hkMemory::getInstance().getAllocatedSize(used);
	collector->addChunk(mem.getName(),cls,(void*)string,used,allocated);
}

void
hkStatisticsCollectorUtil::_addChildObject(const char* fieldName,void* obj,const hkClass& cls,hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener)
{
	if (obj == HK_NULL) { return; }

    hkStatisticsCollector::StatisticClass statCls = listener->getStatisticClass(cls);

	// We need to cast to do the calcStatistics... can't do it tho
	if (cls.hasVtable())
	{
		/// This is evil - but it havok assumes that hkReferencedObject is the start of all
		/// derived objects
		hkReferencedObject* refObj = reinterpret_cast<hkReferencedObject*>(obj);
		// Recurse - this adds the memory of the object as well as contained objects
        collector->addChildObject(fieldName,statCls,refObj);
	}
	else
	{
		// Add the memory containing the object

		/// Give the size of the object
		int usedSize = cls.getObjectSize();
		int allocatedSize = hkMemory::getInstance().getAllocatedSize(usedSize);
		// This is pointing to a non virtual class so I guess we just go with the size of it
		const char* name = fieldName?fieldName:cls.getName();
		collector->addChunk(name,statCls,(void*)obj,usedSize,allocatedSize);

		/// Add everything contained
        _addObjectContents(fieldName,obj,cls,collector,listener);
	}
}

int
hkStatisticsCollectorUtil::_getArrayElementSize(const hkClassMember& mem)
{
	// Now I need the element size
	const hkClassMember::TypeProperties& info = hkClassMember::getClassMemberTypeProperties(mem.getSubType());

    /// If it has a size, then we just use this
    if (info.m_size>0) { return info.m_size; }
    if (info.m_type == hkClassMember::TYPE_STRUCT)
    {
        const hkClass& cls = mem.getStructClass();
        return cls.getObjectSize();
    }
    HK_ASSERT(0x3424324,!"Couldn't find the size of the array element");
    return -1;
}

void
hkStatisticsCollectorUtil::_addArrayData(const hkClassMember& mem,void* data,int size,int capacity,int objSize,hkStatisticsCollector::StatisticClass statCls,hkStatisticsCollector* collector)
{
    /// Set the size of stuff
    int allocated = hkMemory::getInstance().getAllocatedSize(capacity*objSize);
    collector->addChunk(mem.getName(),statCls,data,size*objSize,allocated);
}


void
hkStatisticsCollectorUtil::_addHomogeneousArray(const hkClassMember& mem,void* data,const hkClass& cls,int size,hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener)
{
    int objSize = cls.getObjectSize();

    collector->pushDir(mem.getName());

    // Now need to handle the pointers
    char* contained = (char*)data;
    for (int i=0;i<size;i++)
    {
        _addChildObject(HK_NULL,(void*)contained,cls,collector,listener);
        contained+=objSize;
    }

    collector->popDir();
}

void
hkStatisticsCollectorUtil::_addArrayContents(const hkClassMember& mem,void* data,int size,hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener)
{
        /// If there is nothing stored we are done
    if (size<=0) { return; }

    switch (mem.getSubType())
	{
		case hkClassMember::TYPE_POINTER:
		{
            collector->pushDir(mem.getName());
            const hkClass& cls = mem.getStructClass();
			// Now need to handle the pointers
            void** contained = (void**)data;
			for (int i=0;i<size;i++)
			{
                _addChildObject(HK_NULL,contained[i],cls,collector,listener);
			}
            collector->popDir();
			break;
		}
		case hkClassMember::TYPE_STRUCT:
		{
            const hkClass& cls = mem.getStructClass();
            _addHomogeneousArray(mem,data,cls,size,collector,listener);
			break;
		}
		default: break;
	}
}

void
hkStatisticsCollectorUtil::_addObjectContents(const char* fieldName,void* obj, const hkClass& cls, hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener )
{
        // Check if we have an object at all
    if (obj == HK_NULL) { return; }

    hkStatisticsCollector::StatisticClass statCls = listener->getStatisticClass(cls);

    hkReferencedObject* refObj = HK_NULL;
    if (cls.hasVtable())
    {
        refObj = reinterpret_cast<hkReferencedObject*>(obj);
        collector->beginObject(cls.getName(), statCls, refObj);
    }

		/// We want to recursively add contents if we are doing the whole shebang
    addClassContentsAll(obj,cls,collector,listener);

    if (refObj)
    {
        /// Will only have been added if it was a referenced object
        collector->endObject();
    }
}

void
hkStatisticsCollectorUtil::addClassContents(void* obj, const hkClass& cls,hkStatisticsCollector* collector, hkStatisticsCollectorClassListener* listener )
{
        // Check if we have an object at all
    if (obj == HK_NULL) { return; }

    listener = _ensureListener(listener);
    hkStatisticsCollector::StatisticClass statCls = listener->getStatisticClass(cls);

		/// Make char* to make math easier
	char* byteObj = (char*)obj;

    int numMembers = cls.getNumDeclaredMembers();
    for (int i=0;i<numMembers;i++)
    {
        const hkClassMember & mem = cls.getDeclaredMember (i);
			// If we don't own it, we are done
		if (mem.getFlags().anyIsSet(hkClassMember::NOT_OWNED)) { continue; }

		/// See if the type means more memory has been allocated
        switch (mem.getType())
        {
			case hkClassMember::TYPE_CSTRING:
			{
				hkClassMemberAccessor accessor(obj,&mem);
				int size = mem.getCstyleArraySize();
				if (size<=1)
				{
                    _addCstring(mem,accessor.asCstring(),statCls,collector);
				}
				else
				{
                    for (int j=0;j<size;j++)
                    {
                        _addCstring(mem,accessor.asCstring(j),statCls,collector);
                    }
				}
				break;
			}
			case hkClassMember::TYPE_ARRAY:
			{
				const hkArray<char>& array = *(hkArray<char>*)(byteObj+mem.getOffset());

                /// If its not allocated we are done
                if (array.getCapacityAndFlags() & array.DONT_DEALLOCATE_FLAG) { break; }

                int size = array.getSize();
                int capacity = array.getCapacity();
                int objSize = _getArrayElementSize(mem);

                    /// Data chunk
                _addArrayData(mem,(void*)array.begin(),size,capacity,objSize,statCls,collector);
                    /// The contents
                _addArrayContents(mem,(void*)array.begin(),size,collector,listener);
				break;
			}
            case hkClassMember::TYPE_SIMPLEARRAY:
            {
				hkClassMemberAccessor accessor(obj,&mem);
                hkClassMemberAccessor::SimpleArray array = accessor.asSimpleArray();

                int objSize = _getArrayElementSize(mem);
                    /// Data chunk
                _addArrayData(mem,array.data,array.size,array.size,objSize,statCls,collector);
                    /// Contents
                _addArrayContents(mem,array.data,array.size,collector,listener);
                break;
            }
            case hkClassMember::TYPE_HOMOGENEOUSARRAY:
            {
				hkClassMemberAccessor accessor(obj,&mem);
                hkClassMemberAccessor::HomogeneousArray array = accessor.asHomogeneousArray();
                if (array.size>0&&array.klass&&array.data)
                {
                        /// Data chunk
                    _addArrayData(mem,array.data,array.size,array.size,array.klass->getObjectSize(),statCls,collector);
                        /// contents
                    _addHomogeneousArray(mem,array.data,*array.klass,array.size,collector,listener);
                }
                break;
            }
            case hkClassMember::TYPE_POINTER:
            {
                if (mem.getSubType() == hkClassMember::TYPE_STRUCT)
                {
                    void* child = *(void**)(byteObj+mem.getOffset());
                    _addChildObject(mem.getName(),child,mem.getStructClass(),collector,listener);
	                break;
                }
                // If its not a struct there is no way to know what size it is... , as it could be an array
                break;
            }
            case hkClassMember::TYPE_VARIANT:
            {
				const hkVariant& variant = *(hkVariant*)(byteObj+mem.getOffset());
				if (variant.m_object!=HK_NULL&&variant.m_class!=HK_NULL)
				{
                    _addChildObject(mem.getName(),variant.m_object,*variant.m_class,collector,listener);
				}
                break;
            }
            default: break;
        }
    }
}


void
hkStatisticsCollectorUtil::addClassContentsAll(void* obj, const hkClass& cls, hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener )
{
    if (obj == HK_NULL) { return; }

    listener = _ensureListener(listener);

    const hkClass* curCls = &cls;
    do
    {
            /// NOTE!!! There is an implicit and dangerous assumption here, that is that derived objects extend downwards
            /// such that CBase and CDerivived, CBase* reinterpret_cast<CBase*>&derived, is ok. This is an assumption in the
            /// havok object model.

            /// Add the contents of this part of the tree
        addClassContents(obj,*curCls,collector,listener);
            // Do the parent
        curCls = curCls->getParent();
    }
    while (curCls);
}

void hkStatisticsCollectorUtil::defaultCalcStatistics(void* obj, const hkClass& cls,hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener )
{
    listener = _ensureListener(listener);
    _addObjectContents(HK_NULL,obj, cls, collector,listener);
}

/// These are the helper methods, that do the lookup for hkReferencedObject derived classes

void hkStatisticsCollectorUtil::defaultCalcStatistics(void* obj, hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener )
{
    listener = _ensureListener(listener);

    const hkClass* cls = _getClass(obj);
    if (cls == HK_NULL) { return; }
		/// Ad the object
    _addObjectContents(HK_NULL,obj, *cls, collector,listener);
}

const hkClass*
hkStatisticsCollectorUtil::defaultBeginObject(void* obj, hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener )
{
    if (obj == HK_NULL) { return HK_NULL; }

    listener = _ensureListener(listener);

    const hkClass* cls = _getClass(obj);
    if (cls == HK_NULL) { return HK_NULL; }

    hkStatisticsCollector::StatisticClass statCls = listener->getStatisticClass(*cls);

    hkReferencedObject* refObj = HK_NULL;
    if (cls->hasVtable())
    {
        refObj = reinterpret_cast<hkReferencedObject*>(obj);
        collector->beginObject(cls->getName(), statCls, refObj);
        return cls;
    }
    return HK_NULL;
}


void
hkStatisticsCollectorUtil::addClassContents(void* obj, hkStatisticsCollector* collector,hkStatisticsCollectorClassListener* listener )
{
    const hkClass* cls = _getClass(obj);
    if (cls == HK_NULL) { return; }
    addClassContents(obj,*cls,collector ,listener);
}

void
hkStatisticsCollectorUtil::addClassContentsAll(void* obj, hkStatisticsCollector* collector, hkStatisticsCollectorClassListener* listener )
{
    const hkClass* cls = _getClass(obj);
    if (cls == HK_NULL) { return; }
    addClassContentsAll(obj,*cls,collector ,listener);
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
