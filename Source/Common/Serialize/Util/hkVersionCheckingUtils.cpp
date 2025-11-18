/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Util/hkVersionCheckingUtils.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>
#include <Common/Base/Container/StringMap/hkStringMap.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Serialize/Util/hkVersioningExceptionsArray.h>
#include <Common/Serialize/Util/hkRenamedClassNameRegistry.h>

extern const hkClassEnum* hkClassMemberTypeEnum;

namespace
{
	typedef hkStringMap<const hkClass*> Map;

	void makeMap( Map& m, hkArray<const hkClass*>& l)
	{
		for( int i = l.getSize() - 1; i >= 0; --i )
		{
			if(l[i])
			{
				m.insert( l[i]->getName(), l[i] );
			}
			else
			{
				l.removeAt(i);
			}
		}
	}

	void makeClassArray(const hkClass* const * nullTerminatedClassArray, hkArray<const hkClass*>& classArray)
	{
		const hkClass* const * current = nullTerminatedClassArray;
		while( *current )
		{
			classArray.pushBack(*current);
			++current;
		}
	}

	typedef hkStringMap<const char*> StringMap;
	inline hkBool32 equalNames(const char* oldClassName, const char* newClassName, const StringMap& newFromOldNameMap)
	{
		const char* renamedClass = newFromOldNameMap.getWithDefault(oldClassName, oldClassName);
		return (hkString::strCmp(renamedClass, newClassName) == 0);
	}

	class EmptyStreamWriter : public hkStreamWriter
	{
		virtual hkBool isOk() const { return true; }
		virtual int write(const void* buf, int nbytes) { return nbytes; }
	};
	int NOT(int i) { return !i; }
}

void HK_CALL hkVersionCheckingUtils::checkVersions( const hkClass* const * oldVersions, const hkClass* const * newVersions, hkArray<VersionDifference>& differences, const hkVersioningExceptionsArray* exceptions )
{
	hkArray<const hkClass*> cl0; makeClassArray( oldVersions, cl0 );
	hkArray<const hkClass*> cl1; makeClassArray( newVersions, cl1 );

	Map cm0; makeMap(cm0, cl0);
	Map cm1; makeMap(cm1, cl1);

	// removed classes?
	for( int c0index = 0; c0index < cl0.getSize(); ++c0index )
	{
		const hkClass* c0 = cl0[c0index];
		const hkClass* c1 = cm1.getWithDefault( c0->getName(), HK_NULL );
		if ( c1 == HK_NULL ) 
		{
			if (exceptions == HK_NULL)
			{
				differences.pushBack( VersionDifference( c0, c1 ) );
			}
			else 
			{
				hkVersioningExceptionsArray::VersioningException e( c0->getName(), c0->getSignature(), 0x0 );
				if ( exceptions->m_exceptions.indexOf( e ) == -1 )
				{
					// Class removed
					differences.pushBack( VersionDifference( c0, c1 ) );
				}
			}
		}
	}

	// changed, same, new
	for( int c1index = 0; c1index < cl1.getSize(); ++c1index )
	{
		const hkClass* c1 = cl1[c1index];
		const hkClass* c0 = cm0.getWithDefault( c1->getName(), HK_NULL );

		if ( c0 == HK_NULL ) 
		{
			if (exceptions == HK_NULL)
			{
				differences.pushBack( VersionDifference( c0, c1 ) );
			}
			else 
			{
				hkVersioningExceptionsArray::VersioningException e( c1->getName(), 0x0, c1->getSignature() );
				if ( exceptions->m_exceptions.indexOf( e ) == -1 )
				{
					// Class removed
					differences.pushBack( VersionDifference( c0, c1 ) );
				}
			}
		}
		else
		{
			hkUint32 c0sig = c0->getSignature();
			hkUint32 c1sig = c1->getSignature();

			if ( c0sig != c1sig ) 
			{
				hkUint32 c0lsig = c0->getSignature( hkClass::SIGNATURE_LOCAL );
				hkUint32 c1lsig = c1->getSignature( hkClass::SIGNATURE_LOCAL );

				const hkClass* p0 = c0;
				const hkClass* p1 = c1;

				// Check parents
				while (c0lsig == c1lsig)
				{
					p0 = p0->getParent();
					p1 = p1->getParent();

					c0lsig = p0->getSignature( hkClass::SIGNATURE_LOCAL );
					c1lsig = p1->getSignature( hkClass::SIGNATURE_LOCAL );
				}

				c0sig = c0->getSignature();
				c1sig = c1->getSignature();

				VersionDifference difference( c0, c1 );
				
				// Ensure we haven't reported this before
				if (differences.indexOf( difference ) == -1)
				{
					if (exceptions == HK_NULL)
					{
						differences.pushBack( difference );
					}
					else 
					{
						hkVersioningExceptionsArray::VersioningException e( c0->getName(), c0sig, c1sig );
						if ( exceptions->m_exceptions.indexOf( e ) == -1 )
						{
							// Class removed
							differences.pushBack( difference );
						}
					}
				}
			}
		}
	}
}

void HK_CALL hkVersionCheckingUtils::summarizeChanges(hkOstream& output, const hkClass& c0, const hkClass& c1, bool detailed )
{

	if ( (detailed) && ( c0.getObjectSize() != c1.getObjectSize() ) )
	{
		output.printf("\tobject sizes differ %i %i\n", c0.getObjectSize(), c1.getObjectSize() );
	}

	// Check for removed enumerations
	{
		int c0Enums = c0.getNumEnums();
		for (int e0=0; e0 < c0Enums; ++e0 )
		{
			const hkClassEnum& c0e = c0.getEnum( e0 );
			const hkClassEnum* c1ep = c1.getEnumByName( c0e.getName() );
			if (c1ep == HK_NULL)
			{
				output.printf( "\tenum '%s' removed\n", c0e.getName() );
			}
		}
	}

	// Check for added enumerations 
	{
		int c1Enums = c1.getNumEnums();
		for (int e1=0; e1 < c1Enums; ++e1 )
		{
			const hkClassEnum& c1e = c1.getEnum( e1 );
			const hkClassEnum* c0ep = c0.getEnumByName( c1e.getName() );
			if (c0ep == HK_NULL)
			{
				output.printf( "\tenum '%s' added\n", c1e.getName() );
			}
		}
	}

	// Checked for changed enumerations
	{
		int c1Enums = c1.getNumEnums();
		for (int e1=0; e1 < c1Enums; ++e1 )
		{
			const hkClassEnum& c1e = c1.getEnum( e1 );
			const hkClassEnum* c0ep = c0.getEnumByName( c1e.getName() );
			if ((c0ep != HK_NULL) && (c1e.getSignature() != c0ep->getSignature()) )
			{
				// Enumeration changed
				output.printf( "\tenum '%s' changed\n", c1e.getName() );

				// Added and changed
				{
					int c1Vals = c1e.getNumItems();
					for (int v1=0; v1 < c1Vals; ++v1)
					{
						int c0eVal;
						if ( c0ep->getValueOfName(c1e.getItem( v1 ).getName(), &c0eVal) == HK_FAILURE )
						{
							output.printf( "\t\tvalue added '%s'\n", c1e.getItem( v1 ).getName() );
						}
						else if ( c1e.getItem( v1 ).getValue() != c0eVal )
						{
							output.printf( "\t\tvalue changed '%s'\n",  c1e.getItem( v1 ).getName() );
						}
					}
				}

				// Removed
				{
					int c0Vals = c0ep->getNumItems();
					for (int v0=0; v0 < c0Vals; ++v0)
					{
						int c1eVal;
						if ( c1e.getValueOfName(c0ep->getItem( v0 ).getName(), &c1eVal) == HK_FAILURE )
						{
							output.printf( "\tEnumeration '%s' : value removed '%s'\n", c1e.getName(), c0ep->getItem( v0 ).getName() );
						}
					}
				}
			}
		}
	}

	// Check changed members
	int c1numMembers = c1.getNumMembers();
	for( int i1 = 0; i1 < c1numMembers; ++i1 )
	{
		const hkClassMember& c1m = c1.getMember( i1 );
		if( const hkClassMember* c0mp = c0.getMemberByName( c1m.getName() ) )
		{
			if ( detailed && ( &c1m.getStructClass() || &c0mp->getStructClass() ) )
			{
				const hkClass& c1s = c1m.getStructClass();
				const hkClass& c0s = c0mp->getStructClass();
				if( (&c1s) && (&c0s) )
				{
					if( c1s.getSignature() != c0s.getSignature() )
					{
						output.printf("\tdefinition of '%s' %s changed\n", c1m.getName(), c1s.getName() );
					}						
				}
				else
				{
					const hkClass& c = &c1s ? c1s : c0s;
					output.printf("\t?? new definition of '%s' %s\n", c1m.getName(), c.getName() );
				}
			}
			if ( detailed && ( c1m.getOffset() != c0mp->getOffset() ) )
			{
				output.printf("\toffset of '%s' changed %i %i\n", c1m.getName(), c0mp->getOffset(), c1m.getOffset() );
			}
			if( c1m.getSizeInBytes() != c0mp->getSizeInBytes() )
			{
				output.printf("\tsize of '%s' changed %i %i\n", c1m.getName(), c0mp->getSizeInBytes(), c1m.getSizeInBytes() );
			}
			if( c1m.getType() != c0mp->getType() || c1m.getSubType() != c0mp->getSubType())
			{
				const char* c0t = HK_NULL;
				const char* c0s = HK_NULL;
				const char* c1t = HK_NULL;
				const char* c1s = HK_NULL;
				hkClassMemberTypeEnum->getNameOfValue( c0mp->getType(), &c0t );
				hkClassMemberTypeEnum->getNameOfValue( c0mp->getSubType(), &c0s );
				hkClassMemberTypeEnum->getNameOfValue( c1m.getType(), &c1t );
				hkClassMemberTypeEnum->getNameOfValue( c1m.getSubType(), &c1s );

				output.printf("\ttype of '%s' changed %s.%s %s.%s\n", c1m.getName(), c0t,c0s, c1t,c1s);
			}
			if( c1m.getCstyleArraySize() != c0mp->getCstyleArraySize() )
			{
				output.printf("\tarray size of '%s' changed %i %i\n", c1m.getName(), c1m.getCstyleArraySize(), c0mp->getCstyleArraySize());
			}
			if( c1m.getFlags() != c0mp->getFlags() )
			{
				output.printf("\tflags of '%s' changed %i %i\n", c1m.getName(), c1m.getFlags(), c0mp->getFlags());
			}
		}
		else
		{
			

			EmptyStreamWriter nullWriter;
			bool hasDefault  = c1.getDefault( i1, &nullWriter ) == HK_SUCCESS;

			output.printf("\tmember '%s' added : has default %s\n", c1m.getName(), hasDefault ? "yes" : "no");
		}
	}
	int c0numMembers = c0.getNumMembers();
	for( int i0 = 0; i0 < c0numMembers; ++i0 )
	{
		const hkClassMember& c0m = c0.getMember( i0 );
		if( c1.getMemberByName( c0m.getName() ) == HK_NULL )
		{
			output.printf("\tmember '%s' removed\n", c0m.getName() );
		}
	}

}

static int containsVariants(const hkClass& klass)
{
	for( int i = 0; i < klass.getNumMembers(); ++i )
	{
		const hkClassMember& mem = klass.getMember(i);
		switch( mem.getType() )
		{
			case hkClassMember::TYPE_VARIANT:
			{
				return 1;
			}
			case hkClassMember::TYPE_ARRAY:
			case hkClassMember::TYPE_SIMPLEARRAY:
			{
				if( mem.getSubType() == hkClassMember::TYPE_VARIANT )
				{
					return 1;
				}
				else if( mem.getSubType() != hkClassMember::TYPE_STRUCT )
				{
					break;
				}
				// struct falls through
			}
			case hkClassMember::TYPE_STRUCT:
			{
				if( containsVariants(mem.getStructClass()) )
				{
					return 1;
				}
				break;
			}
			default:
			{
				// skip
			}
		}
	}
	return 0;
}

hkResult HK_CALL hkVersionCheckingUtils::verifyUpdateDescription(
	hkOstream& report,
	hkClass*const* oldClasses,
	const hkVersionUtil::UpdateDescription& updateDescription,
	Flags flags )
{
	const hkClassNameRegistry* newClassReg = hkVersionRegistry::getInstance().getClassNameRegistry( updateDescription.newClassList->version );
	hkRenamedClassNameRegistry newClassFromOldName(updateDescription.renames, newClassReg);

	hkResult result = HK_SUCCESS;

	for( int classIndex = 0; oldClasses[classIndex] != HK_NULL; ++classIndex )
	{
		const hkClass* oldClass = oldClasses[classIndex];
		hkUint32 oldGlobalSig = oldClass->getSignature();
		const hkVersionUtil::ClassAction* action = updateDescription.findActionForClass( *oldClass );

		// class still exists?
		const hkClass* newClass = newClassFromOldName.getClassByName( oldClass->getName() );
		if( newClass == HK_NULL || (action && (action->versionFlags & hkVersionUtil::VERSION_REMOVED)) )
		{
			if( action == HK_NULL )
			{
				report.printf("REMOVED(%s), but no removed action\n", oldClass->getName() );
				if (! (flags & IGNORE_REMOVED) )
				{
					result = HK_FAILURE;
				}
			}
			else if( NOT(action->versionFlags & hkVersionUtil::VERSION_REMOVED ) )
			{
				report.printf("REMOVED(%s), but action is not set to VERSION_REMOVED\n", oldClass->getName() );
				if (! (flags & IGNORE_REMOVED) )
				{
					result = HK_FAILURE;
				}
			}
			continue;
		}

		hkUint32 newGlobalSig = newClass->getSignature();
		if( containsVariants(*newClass) )
		{
			if( action == HK_NULL || !(action->versionFlags & hkVersionUtil::VERSION_VARIANT) )
			{
				report.printf("%s (0x%x, 0x%x) has variants, but does not set VERSION_VARIANT\n", newClass->getName(), oldGlobalSig, newGlobalSig );
				result = HK_FAILURE;
				continue;
			}
		}

		// early out if no diffs

		if( oldGlobalSig == newGlobalSig && action == HK_NULL )
		{
			continue;
		}

		// action must exist if changes exist
		if( action == HK_NULL ) 
		{
			report.printf("%s 0x%x, 0x%x MISSING ACTION\n", oldClass->getName(), oldGlobalSig, newGlobalSig );
			result = HK_FAILURE;
			continue;
		}

		hkUint32 oldLocalSig = oldClass->getSignature(hkClass::SIGNATURE_LOCAL);
		hkUint32 newLocalSig = newClass->getSignature(hkClass::SIGNATURE_LOCAL);
		const char* oldParentName = oldClass->getParent() ? oldClass->getParent()->getName() : "";
		const char* newParentName = newClass->getParent() ? newClass->getParent()->getName() : "";

		// no changes here, changes are in parent
		// Consider these cases where C is the class being checked : indicates inheritance
		// A:C -> B:C, B:C -> C, C -> B:C.
		if( oldLocalSig == newLocalSig
			// have the same inheritance/parent ?
			&& equalNames(oldParentName, newParentName, newClassFromOldName.m_renames) )
		{
			if( hkString::strCmp( action->oldClassName, oldClass->getName()) == 0
				&& !(action->versionFlags & hkVersionUtil::VERSION_VARIANT)
				&& equalNames( oldClass->getName(), newClass->getName(), newClassFromOldName.m_renames ) )
			{
				report.printf("%s 0x%x, 0x%x OBSOLETE ACTION\n", oldClass->getName(), oldGlobalSig, newGlobalSig );
				result = HK_FAILURE;
			}
			continue;
		}

		if (flags & VERBOSE)
		{
			hkArray<char> buf;
			hkOstream ostr(buf);
			hkVersionCheckingUtils::summarizeChanges( ostr, *oldClass, *newClass, true );
			report << "**" << oldClass->getName() << "\n" << buf.begin();
		}

		// changes are local - must have an entry
		if( hkString::strCmp(oldClass->getName(), action->oldClassName) != 0 )
		{
			report.printf("%s 0x%x, 0x%x has changes, but first action found for parent %s\n",
				oldClass->getName(), oldGlobalSig, newGlobalSig, action->oldClassName );
			result = HK_FAILURE;
			continue;
		}

		// is entry up to date
		if( action->oldSignature != oldGlobalSig || action->newSignature != newGlobalSig )
		{
			report.printf("%s (0x%x, 0x%x) (0x%x, 0x%x) signature mismatch\n", oldClass->getName(),
				action->oldSignature, action->newSignature,
				oldGlobalSig, newGlobalSig );
			result = HK_FAILURE;
		}

		// if parent calls func, then we should too
		if( action->versionFunc == HK_NULL )
		{
			for( const hkClass* c = oldClass->getParent(); c != HK_NULL; c = c->getParent() )
			{
				const hkVersionUtil::ClassAction* parentAction = updateDescription.findActionForClass( *c );
				if( parentAction )
				{
					if( parentAction->versionFunc != HK_NULL )
					{
						report.printf("%s has no version func, but parent %s has\n",
							oldClass->getName(), c->getName() );
						result = HK_FAILURE;
						break;
					}
				}
				else
				{
					break;
				}
			}
		}

		// type has changed
		if( action->versionFunc == HK_NULL )
		{
			for( int memberIndex = 0; memberIndex < oldClass->getNumMembers(); ++memberIndex )
			{
				const hkClassMember& oldMem = oldClass->getMember(memberIndex);
				const hkClassMember* newMemPtr = newClass->getMemberByName( oldMem.getName() );
				if( newMemPtr )
				{
					if( oldMem.getType() != newMemPtr->getType()
						&& oldMem.getType() != hkClassMember::TYPE_ZERO
						&& newMemPtr->getType() != hkClassMember::TYPE_ZERO )
					{
						report.printf("%s::m_%s type changed but no version func\n",
							oldClass->getName(), oldMem.getName() );
						result = HK_FAILURE;
						break;
					}
					else if( oldMem.hasClass()
							&& oldMem.getType() != hkClassMember::TYPE_POINTER
							&& oldMem.getSubType() != hkClassMember::TYPE_POINTER )
					{
						for( const hkClass* oldMemClass = &oldMem.getStructClass(); oldMemClass != HK_NULL; oldMemClass = oldMemClass->getParent() )
						{
							const hkVersionUtil::ClassAction* memClassAction = updateDescription.findActionForClass( *oldMemClass );
							if( memClassAction && memClassAction->versionFunc )
							{
								report.printf("%s::m_%s type has version func but %s has no version func\n",
												oldClass->getName(), oldMem.getName(), oldClass->getName());
								result = HK_FAILURE;
								break;
							}
						}
					}
				}
			}
		}

		// must copy if size has changed
		if( NOT( action->versionFlags & hkVersionUtil::VERSION_COPY ) )
		{
			int oldObjectSize = oldClass->getObjectSize();
			int newObjectSize = newClass->getObjectSize();

			//XXX check size has not changed on all platforms

			if( oldObjectSize != newObjectSize )
			{
				report.printf("%s has changed size %i %i, but not set to copy\n",
					oldClass->getName(), oldObjectSize, newObjectSize );
				result = HK_FAILURE;
				continue;
			}
		}

		// if parent copies, we must too
		if( NOT( action->versionFlags & hkVersionUtil::VERSION_COPY) )
		{
			for( const hkClass* c = oldClass->getParent(); c != HK_NULL; c = c->getParent() )
			{
				const hkVersionUtil::ClassAction* parentAction = updateDescription.findActionForClass( *c );
				if( parentAction )
				{
					if( parentAction->versionFlags & hkVersionUtil::VERSION_COPY )
					{
						report.printf("%s parent %s copies, so it should too.\n",
							oldClass->getName(), c->getName() );
						result = HK_FAILURE;
						break;
					}
				}
				else
				{
					break;
				}
			}
		}

		// if member copies, we must too
		if( NOT( action->versionFlags & hkVersionUtil::VERSION_COPY) )
		{
			for( int i = 0; i < oldClass->getNumDeclaredMembers(); ++i )
			{
				const hkClassMember& m = oldClass->getDeclaredMember(i);
				if( m.hasClass()
					&& m.getType() != hkClassMember::TYPE_POINTER
					&& m.getSubType() != hkClassMember::TYPE_POINTER )
				{
					for( const hkClass* c = &m.getStructClass(); c != HK_NULL; c = c->getParent() )
					{
						const hkVersionUtil::ClassAction* memClassAction = updateDescription.findActionForClass( *c );
						if( memClassAction )
						{
							if( memClassAction->versionFlags & hkVersionUtil::VERSION_COPY )
							{
								report.printf("%s::m_%s type (%s) copies, so %s should too.\n",
									oldClass->getName(), m.getName(), c->getName(), oldClass->getName());
								result = HK_FAILURE;
								break;
							}
						}
					}
				}
			}
		}
	}

	// now check the table itself
	hkClassNameRegistry oldClassFromName;
	oldClassFromName.registerList(oldClasses);

	for( const hkVersionUtil::ClassAction* action = updateDescription.actions; action->oldClassName != HK_NULL; ++action )
	{
		if( action->versionFlags & hkVersionUtil::VERSION_REMOVED )
		{
			if( newClassFromOldName.getClassByName( action->oldClassName ) != HK_NULL )
			{
				report.printf("%s is marked as removed, but is still present.\n", action->oldClassName );
				result = HK_FAILURE;
			}
		}

		if( const hkClass* actionClass = oldClassFromName.getClassByName( action->oldClassName ) )
		{
			for( const hkVersionUtil::ClassAction* a = action+1; a->oldClassName != HK_NULL; ++a )
			{
				const hkClass* c = oldClassFromName.getClassByName( a->oldClassName );

				if( actionClass->isSuperClass(*c) )
				{
					report.printf("entry %i for %s is hidden by entry %i for %s.\n",
						a - updateDescription.actions, a->oldClassName,
						action - updateDescription.actions, action->oldClassName );
				}
			}
		}
	}

	return result;
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
