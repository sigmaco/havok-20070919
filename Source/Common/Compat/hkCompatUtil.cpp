/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/Compat/hkCompat.h>
#include <Common/Compat/hkCompatUtil.h>
#include <Common/Serialize/Version/hkVersionUtil.h>
#include <Common/Compat/hkHavokAllClasses.h>

typedef hkPointerMap<const hkClass*, hkInt32> UpdatedClassesMap;

static void updateNamedVariantClassName( hkVariant& namedVariantInOut, const hkVersionUtil::ClassRename* renames, hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor className(namedVariantInOut, "className");

	hkClassMemberAccessor::Cstring& namedVariantClassName = className.asCstring();
	while( renames->oldName && namedVariantClassName )
	{
		if( hkString::strCmp(namedVariantClassName, renames->oldName) == 0 )
		{
			char* variantClassName = hkString::strDup(renames->newName);
			tracker.addAllocation(variantClassName);
			namedVariantClassName = variantClassName;
			break;
		}
		++renames;
	}
}

static void updateAllNamedVariantsClassName( hkClassMemberAccessor::SimpleArray& namedVariantsArray, const hkClass& namedVariantClass, const hkVersionUtil::ClassRename* renames, hkObjectUpdateTracker& tracker )
{
	for( int i = 0; i < namedVariantsArray.size; ++i )
	{
		void* namedVariantObjPtr = static_cast<char*>(namedVariantsArray.data) + i*namedVariantClass.getObjectSize();
		hkVariant namedVariant = {namedVariantObjPtr, &namedVariantClass};
		updateNamedVariantClassName( namedVariant, renames, tracker );
	}
}

void hkCompatUtil::updateNamedVariantClassName( hkArray<hkVariant>& objectsInOut, const hkVersionUtil::ClassRename* renames, hkObjectUpdateTracker& tracker )
{
	if( renames->oldName == HK_NULL )
	{
		return;
	}

	for( int i = 0; i < objectsInOut.getSize(); ++i )
	{
		const hkClass* klass = objectsInOut[i].m_class;
		if( hkString::strCmp(klass->getName(), "hkRootLevelContainer") == 0 )
		{
			hkClassMemberAccessor namedVariants(objectsInOut[i], "namedVariants");
			hkClassMemberAccessor::SimpleArray& namedVariantsArray = namedVariants.asSimpleArray();
			updateAllNamedVariantsClassName( namedVariantsArray, namedVariants.object().getClass(), renames, tracker );
		}
		if( hkString::strCmp(klass->getName(), "hkRootLevelContainerNamedVariant") == 0 )
		{
			updateNamedVariantClassName( objectsInOut[i], renames, tracker );
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
