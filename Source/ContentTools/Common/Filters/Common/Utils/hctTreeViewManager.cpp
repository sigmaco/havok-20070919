/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/Common/hctFilterCommon.h>

#include <Common/Serialize/hkSerialize.h>

#include <Common/SceneData/Graph/hkxNode.h>
#include <Common/SceneData/Skin/hkxSkinBinding.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/hkxIndexBuffer.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Material/hkxMaterial.h>
#include <Common/SceneData/Material/hkxTextureInplace.h>
#include <Common/SceneData/Material/hkxTextureFile.h>
#include <Common/SceneData/Light/hkxLight.h>
#include <Common/SceneData/Camera/hkxCamera.h>
#include <Common/SceneData/Attributes/hkxAttributeGroup.h>
#include <Common/SceneData/Environment/hkxEnvironment.h>


void hctTreeViewManager::init( HWND treeWnd )
{
	m_treeWnd = treeWnd;
	if( m_root )
	{
		addItem( TVI_ROOT, *m_root );
	}
}

BOOL hctTreeViewManager::handleNotification( LPNMHDR n )
{
	switch (n->code)
	{
	case TVN_ITEMEXPANDING:
		{
			LPNMTREEVIEW treeViewNM = (LPNMTREEVIEW)n;
			TVITEM& tvParent = treeViewNM->itemNew; // hItem, state, and lParam are valid
			int varIndex = (int)tvParent.lParam;
			if( ( varIndex >= 0 ) && ( varIndex < m_variantMap.getSize() ) ) 
			{
				hkVariant& var = m_variantMap[varIndex];
				
				hkString name;
				hkArray< hkVariant > children;
				int imageIndex;
				getItemData( var, name, children, imageIndex );
				
				if( (treeViewNM->action & TVE_EXPAND) && ( children.getSize() > 0 ) ) // expanding, we must add the children (if not added already)
				{
					if ( TreeView_GetChild( m_treeWnd, tvParent.hItem ) == NULL )
					{
						for( int ci=0; ci<children.getSize(); ++ci )
						{
							HK_ASSERT( 0x0, children[ci].m_class );
							addItem( tvParent.hItem, children[ci] );
						}
					}
				}

				return TRUE; // handled it
			}
		}
	}

	return FALSE;
}

bool hctTreeViewManager::getSelectedVariant( hkVariant& var )
{
	TVITEM tvi;
	tvi.hItem = TreeView_GetSelection( m_treeWnd );
	tvi.mask = TVIF_PARAM;
	TreeView_GetItem( m_treeWnd, &tvi );
	
	if ( ( tvi.lParam >= 0 ) && ( tvi.lParam < m_variantMap.getSize() ) )
	{
		int varIndex = (int)( tvi.lParam );
		var = m_variantMap[varIndex];
		return true;
	}
	
	var.m_class = HK_NULL;
	var.m_object = HK_NULL;
	return false;
}



int hctTreeViewManager::getVariantIndex( const hkVariant& var )
{
	int numVars = m_variantMap.getSize();
	for( int vi=0; vi < numVars; ++vi )
	{
		if( m_variantMap[vi].m_object == var.m_object )
		{
			return vi;
		}
	}
	
	hkVariant& newVar = m_variantMap.expandOne();
	newVar = var;
	return numVars;
}


template <typename T>
struct _DummyArray
{
	T* data;
	int size;
};

void hctTreeViewManager::getItemData( const hkVariant& var, hkString& name, hkArray< hkVariant >& children, int& imageIndex )
{
	name = "";
	children.clear();
	imageIndex = -1;
	
	// Generic klass walker
	const hkClass& klass = *var.m_class;
	const void* obj = var.m_object;
	for (int mi=0; mi < klass.getNumMembers(); ++mi)
	{
		const hkClassMember& m = klass.getMember(mi);
		switch ( m.getType() )
		{
			case hkClassMember::TYPE_VARIANT:
			{
				hkVariant& mvar = *(hkVariant*)(((char*)obj) + m.getOffset()); // ptr to a variant
				if (mvar.m_object && mvar.m_class)
				{
					hkVariant& var = children.expandOne();
					HK_ASSERT( 0x0, mvar.m_class );
					var = mvar;
				}
				break;
			}

			case hkClassMember::TYPE_STRUCT:
			{
				const hkClass* c = m.hasClass()? &(m.getStructClass()) : HK_NULL;
				if (c)
				{
					// EXP-980 : Handle fixed size C arrays of structs
					int size = m.getCstyleArraySize();

					// Pretend it's a C-array of 1 even if it's not an array
					if (size==0) size=1;

					char* arrayStart = ((char*)obj) + m.getOffset(); // ptr to a struct
					for (int ai=0; ai<size; ai++)
					{
						char* objectStart = arrayStart + c->getObjectSize() * ai;

						hkVariant& var = children.expandOne();

						var.m_object = objectStart;
						var.m_class = c;
					}
					
				}
				break;
			}

			case hkClassMember::TYPE_POINTER:
			{
				if (m.getSubType() >= hkClassMember::TYPE_POINTER)
				{
					void* vobj = *(void**)( ((char*)obj) + m.getOffset() ); // ptr to a ptr.
					if (vobj)
					{
						HK_ASSERT( 0x0, m.hasClass() );
						const hkClass& c = m.getStructClass();
						hkVariant& var = children.expandOne();
						var.m_class = &c;
						var.m_object = vobj;
					}
				}
				break;
			}

			// EXP-650 : C strings are now a new type
			case hkClassMember::TYPE_CSTRING:
			{
				if ( hkString::strCmp( m.getName(), "name" ) == 0 ) // any member that is called name that is a char* ptr we will uses as the name ;)
				{
					char* vobj = *(char**)( ((char*)obj) + m.getOffset() ); // ptr to a ptr.
					name = vobj; // should be null terminated.
				}
				break;
			}

			case hkClassMember::TYPE_ARRAY: //hkarray<>
			case hkClassMember::TYPE_INPLACEARRAY:
			case hkClassMember::TYPE_SIMPLEARRAY: // void*,int
			{
				const hkClass* c = m.hasClass()? &(m.getStructClass()) : HK_NULL;
				_DummyArray<char>* array = (_DummyArray<char>*)( ((char*)obj) + m.getOffset() );

				for (int ai=0; ai < array->size; ++ai)
				{
					char* bytePtr = array->data + (m.getArrayMemberSize()*ai);
					if (m.getSubType() == hkClassMember::TYPE_VARIANT)
					{
						hkVariant& avar = *(hkVariant*)( bytePtr ); // ptr to a variant
						if (avar.m_object && avar.m_class)
						{
							hkVariant& var = children.expandOne();
							var = avar;
						}
					}
					else if (m.getSubType() == hkClassMember::TYPE_STRUCT)
					{
						void* vobj = bytePtr; // ptr to a struct
						if (vobj)
						{
							hkVariant& var = children.expandOne();
							var.m_object = vobj;
							var.m_class = c;
							HK_ASSERT( 0x0, c );

						}
					}
					else if (m.getSubType() == hkClassMember::TYPE_POINTER)
					{
						void* vobj = *(void**)(bytePtr); // ptr to ptr
						if (vobj)
						{
							hkVariant& var = children.expandOne();
							var.m_object = vobj;
							var.m_class = c;
							HK_ASSERT( 0x0, c );

						}
					}
				}
				break;
			}
		}
	}
	
	// use address if not named
	if( name.getLength() < 1 )
	{
		name.printf("%s @ 0x%x", klass.getName(), obj);
	}

	// handle virtual class types
	if( m_classReg )
	{
		for( int ci=0; ci<children.getSize(); ++ci )
		{
			if ( children[ci].m_class && children[ci].m_class->hasVtable() )
			{
				const hkClass* subClass = m_classReg->getClassFromVirtualInstance( children[ci].m_object );
				if( subClass )
				{
					children[ci].m_class = subClass;
				}
			}
		}
	}
	
	// filter allowed types only
	for( int ci=children.getSize()-1; ci>=0; --ci )
	{
		if( !isViewable( *children[ci].m_class ) )
		{
			children.removeAtAndCopy( ci );
		}
	}
	
	//
	// image index
	// NOTE that the image list must be setup by the filter itself
	//
	
	// class names representing the bitmaps in order
	// DO NOT CHANGE/REMOVE CLASSES WITHOUT UPDATING IMAGES
	static const char* klassNames[] =
	{
		"hkaAnimationContainer",
		"hkaBoneAttachment",
		"hkaBone",
		"hkFxClothBodySubsystemCollection",
		"hkFxPhysicsCollection",
		"hkFxRigidBody",
		"hkFxShape",
		"hkxSkinBinding",
		"hkpPhysicsData",
		"hkpRigidBody",
		"hkRootLevelContainer",
		"hkaSkeleton",
		"hkxCamera",
		"hkxEnvironment",
		"hkxLight",
		"hkxMaterial",
		"hkxMesh",
		"hkxMeshSection",
		"hkxNode",
		"hkxScene",
		"hkxAttributeGroup",
		"" // Unknown
	};
	
	static int numKnownClassNames = sizeof(klassNames) / sizeof(const char*);


	// get class name - variants assume the name of their sub class
	hkString klassName = klass.getName();
	if( klassName.compareTo( hkRootLevelContainerNamedVariantClass.getName() ) == 0 )
	{
		hkRootLevelContainer::NamedVariant* variant = (hkRootLevelContainer::NamedVariant*)obj;
		const hkClass* subKlass = variant->getClass();
		if( subKlass )
		{
			klassName = subKlass->getName();
		}
	}
	
	// hkaMeshBinding uses the same icon as hkxSkinBinding
	if( klassName.compareTo( "hkMeshBinding" ) == 0 )
	{
		klassName = hkxSkinBindingClass.getName();
	}
	
	// find the matching bitmap index, if any
	imageIndex = numKnownClassNames-1; // Unknown by default
	for( int i=0; i<numKnownClassNames; ++i )
	{
		if( klassName.compareTo( klassNames[i] ) == 0 )
		{
			imageIndex = i;
			break;
		}
	}
}

void hctTreeViewManager::addItem( HTREEITEM parent, const hkVariant& var )
{
	// don't want to have an ever growing array of vars to obj, so we look if it is in there already (from a prev expand / collapse)
	int varIndex = getVariantIndex( var );

	TVINSERTSTRUCT tvi;
	tvi.hInsertAfter = TVI_ROOT;
	tvi.itemex.mask = TVIF_CHILDREN | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvi.hParent = parent;
	tvi.itemex.iImage = tvi.itemex.iSelectedImage = 0; // 0 == unknown
	tvi.itemex.lParam = varIndex; // index into the variant array.

	hkString name;
	hkArray< hkVariant > children;
	int imageIndex;
	getItemData( var, name, children, imageIndex );

	tvi.itemex.pszText = (LPSTR)( name.cString() );
	tvi.itemex.iImage = tvi.itemex.iSelectedImage = imageIndex;
	tvi.itemex.cChildren = children.getSize() > 0? 1 : 0;

	TreeView_InsertItem( m_treeWnd, &tvi );
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
