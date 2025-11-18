/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'ContentTools/Common/Filters/FilterScene/PlatformWriter/hctPlatformWriterOptions.h'
#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <ContentTools/Common/Filters/FilterScene/PlatformWriter/hctPlatformWriterOptions.h>



//
// Enum hctPlatformWriterOptions::Preset
//
static const hkInternalClassEnumItem hctPlatformWriterOptionsPresetEnumItems[] =
{
	{0, "CUSTOM"},
	{1, "MSVC_WIN32"},
	{2, "MSVC_XBOX"},
	{3, "MSVC_AMD64"},
	{4, "CW_PS2"},
	{5, "CW_GAMECUBE"},
	{6, "CW_PSP"},
	{7, "CW_WII"},
	{8, "GCC33_PS2"},
	{9, "GCC32_PS2"},
	{10, "GCC295_PS2"},
	{11, "SN31_PS2"},
	{12, "SN393_GAMECUBE"},
	{13, "SNC_PSP"},
	{14, "GCC151_PSP"},
	{15, "X360"},
	{16, "GCC_PS3"},
	{17, "MAC_PPC"},
	{18, "MAC_386"},
	{19, "XML"},
};
static const hkInternalClassEnum hctPlatformWriterOptionsEnums[] = {
	{"Preset", hctPlatformWriterOptionsPresetEnumItems, 20, HK_NULL, 0 }
};
extern const hkClassEnum* hctPlatformWriterOptionsPresetEnum = reinterpret_cast<const hkClassEnum*>(&hctPlatformWriterOptionsEnums[0]);

//
// Class hctPlatformWriterOptions
//
HK_REFLECTION_DEFINE_SIMPLE(hctPlatformWriterOptions);
static const hkInternalClassMember hctPlatformWriterOptionsClass_Members[] =
{
	{ "filename", HK_NULL, HK_NULL, hkClassMember::TYPE_CSTRING, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_filename), HK_NULL },
	{ "preset", HK_NULL, hctPlatformWriterOptionsPresetEnum, hkClassMember::TYPE_ENUM, hkClassMember::TYPE_INT8, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_preset), HK_NULL },
	{ "bytesInPointer", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_bytesInPointer), HK_NULL },
	{ "littleEndian", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_littleEndian), HK_NULL },
	{ "reusePaddingOptimized", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_reusePaddingOptimized), HK_NULL },
	{ "emptyBaseClassOptimized", HK_NULL, HK_NULL, hkClassMember::TYPE_INT8, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_emptyBaseClassOptimized), HK_NULL },
	{ "removeMetadata", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_removeMetadata), HK_NULL },
	{ "userTag", HK_NULL, HK_NULL, hkClassMember::TYPE_UINT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_userTag), HK_NULL },
	{ "saveEnvironmentData", HK_NULL, HK_NULL, hkClassMember::TYPE_BOOL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(hctPlatformWriterOptions,m_saveEnvironmentData), HK_NULL }
};
namespace
{
	struct hctPlatformWriterOptions_DefaultStruct
	{
		int s_defaultOffsets[9];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkInt8 /* hkEnum<Preset, hkInt8> */ m_preset;
		hkInt8 m_bytesInPointer;
		hkInt8 m_littleEndian;
		hkInt8 m_emptyBaseClassOptimized;
		_hkBool m_removeMetadata;
	};
	const hctPlatformWriterOptions_DefaultStruct hctPlatformWriterOptions_Default =
	{
		{-1,HK_OFFSET_OF(hctPlatformWriterOptions_DefaultStruct,m_preset),HK_OFFSET_OF(hctPlatformWriterOptions_DefaultStruct,m_bytesInPointer),HK_OFFSET_OF(hctPlatformWriterOptions_DefaultStruct,m_littleEndian),-1,HK_OFFSET_OF(hctPlatformWriterOptions_DefaultStruct,m_emptyBaseClassOptimized),HK_OFFSET_OF(hctPlatformWriterOptions_DefaultStruct,m_removeMetadata),-1,-1},
		hctPlatformWriterOptions::MSVC_WIN32,4,1,1,true
	};
}
extern const hkClass hctPlatformWriterOptionsClass;
const hkClass hctPlatformWriterOptionsClass(
	"hctPlatformWriterOptions",
	HK_NULL, // parent
	sizeof(hctPlatformWriterOptions),
	HK_NULL,
	0, // interfaces
	reinterpret_cast<const hkClassEnum*>(hctPlatformWriterOptionsEnums),
	1, // enums
	reinterpret_cast<const hkClassMember*>(hctPlatformWriterOptionsClass_Members),
	HK_COUNT_OF(hctPlatformWriterOptionsClass_Members),
	&hctPlatformWriterOptions_Default,
	HK_NULL, // attributes
	0
	);

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
