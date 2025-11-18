/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Common/SceneData/hkSceneData.h>

#include <Common/SceneData/Attributes/hkxAttributeGroup.h>

#include <Common/SceneData/Graph/hkxNode.h>
#include <Common/Base/Reflection/hkClass.h>


hkResult hkxAttributeGroup::getBoolValue(const char* name, bool warnIfNotFound, hkBool& boolOut) const
{
	// Bool
	{
		hkxSparselyAnimatedBool* data = findBoolAttributeByName(name);
		if (data) 
		{
			boolOut=data->m_bools[0];
			return HK_SUCCESS;
		}
	}

	// Int
	{
		hkxSparselyAnimatedInt* data = findIntAttributeByName(name);
		if (data) 
		{
			boolOut = (data->m_ints[0] != 0);
			return HK_SUCCESS;
		}
	}

	if (warnIfNotFound)
	{
		HK_WARN_ALWAYS (0xabbaab81, "Bool attribute "<<name<<" not found in "<<m_name<<" attribute group");
	}

	return HK_FAILURE;
}

hkResult hkxAttributeGroup::getIntValue(const char* name, bool warnIfNotFound, int& intOut) const
{
	// Int
	{
		hkxSparselyAnimatedInt* data = findIntAttributeByName(name);
		if (data) 
		{
			intOut = data->m_ints[0];
			return HK_SUCCESS;
		}
	}

	// Bool
	{
		hkxSparselyAnimatedBool* data = findBoolAttributeByName(name);
		if (data) 
		{
			intOut=data->m_bools[0] ? 1 : 0;
			return HK_SUCCESS;
		}
	}

	// Enum
	{
		hkxSparselyAnimatedEnum* data = findEnumAttributeByName(name);
		if (data) 
		{
			intOut = data->m_ints[0];
			return HK_SUCCESS;
		}
	}

	if (warnIfNotFound)
	{
		HK_WARN_ALWAYS (0xabbaab81, "Integer attribute "<<name<<" not found in "<<m_name<<" attribute group");
	}

	return HK_FAILURE;
}

hkResult hkxAttributeGroup::getIntValue (const char* name, bool warnIfNotFound, hkUint32& intOut) const
{
	// We treat the same as ints
	return getIntValue(name, warnIfNotFound, (int&) (intOut));
}

hkResult hkxAttributeGroup::getStringValue(const char* name, bool warnIfNotFound, const char*& stringOut) const
{
	// String
	{
		hkxSparselyAnimatedString* data = findStringAttributeByName(name);
		if (data)
		{
			stringOut = data->m_strings[0].m_string;
			return HK_SUCCESS;
		}
	}

	// Enum
	{
		hkxSparselyAnimatedEnum* data = findEnumAttributeByName(name);
		if (data) 
		{
			int intValue = data->m_ints[0];
			data->m_type->getNameOfValue(intValue, &stringOut);

			return HK_SUCCESS;
		}
	}

	if (warnIfNotFound)
	{
		HK_WARN_ALWAYS (0xabbaab81, "String attribute "<<name<<" not found in "<<m_name<<" attribute group");
	}

	return HK_FAILURE;
}

hkResult hkxAttributeGroup::getFloatValue(const char* name, bool warnIfNotFound, float& floatOut) const
{
	hkxAnimatedFloat* data = findFloatAttributeByName(name);
	if (data) 
	{
		floatOut = data->m_floats[0];
		return HK_SUCCESS;
	}

	if (warnIfNotFound)
	{
		HK_WARN_ALWAYS (0xabbaab81, "Float attribute "<<name<<" not found in "<<m_name<<" attribute group");
	}

	return HK_FAILURE;
}

hkResult hkxAttributeGroup::getVectorValue(const char* name, bool warnIfNotFound, hkVector4& vectorOut) const
{
	hkxAnimatedVector* data = findVectorAttributeByName(name);
	if (data) 
	{
		vectorOut = data->m_vectors[0];
		return HK_SUCCESS;
	}

	if (warnIfNotFound)
	{
		HK_WARN_ALWAYS (0xabbaab81, "Float attribute "<<name<<" not found in "<<m_name<<" attribute group");
	}

	return HK_FAILURE;
}

hkResult hkxAttributeGroup::getQuaternionValue(const char* name, bool warnIfNotFound, hkQuaternion& quaternionOut) const
{
	hkxAnimatedQuaternion* data = findQuaternionAttributeByName(name);
	if (data) 
	{
		quaternionOut = data->m_quaternions[0];
		return HK_SUCCESS;
	}

	if (warnIfNotFound)
	{
		HK_WARN_ALWAYS (0xabbaab81, "Quaternion attribute "<<name<<" not found in "<<m_name<<" attribute group");
	}

	return HK_FAILURE;
}

hkResult hkxAttributeGroup::getMatrixValue(const char* name, bool warnIfNotFound, hkMatrix4& matrixOut) const
{
	hkxAnimatedMatrix* data = findMatrixAttributeByName(name);
	if (data) 
	{
		matrixOut = data->m_matrices[0];
		return HK_SUCCESS;
	}

	if (warnIfNotFound)
	{
		HK_WARN_ALWAYS (0xabbaab81, "Matrix attribute "<<name<<" not found in "<<m_name<<" attribute group");
	}

	return HK_FAILURE;
}

int hkxAttributeGroup::findAttributeIndexByName( const char* name ) const
{
	for (int i=0; i < m_numAttributes; ++i)
	{
		if (hkString::strCasecmp(m_attributes[i].m_name, name) == 0 )
		{
			return i;
		}
	}
	return -1;
}

const hkVariant* hkxAttributeGroup::findAttributeVariantByName(const char* name ) const
{
	const int index = findAttributeIndexByName( name );

	return (index<0) ? HK_NULL : &m_attributes[index].m_value;
}

void* hkxAttributeGroup::findAttributeObjectByName(const char* name, const hkClass* type ) const
{
	const hkVariant* var = findAttributeVariantByName(name );

	// compare class by name so that it deals with serialized classes etc better (for instance in the filters)
	if (var && (!type || (hkString::strCasecmp(type->getName(), var->m_class->getName()) == 0)) )
	{
		return var->m_object;
	}
	return HK_NULL;
}

struct hkxSparselyAnimatedBool* hkxAttributeGroup::findBoolAttributeByName (const char* name) const
{
	return static_cast<hkxSparselyAnimatedBool*> (findAttributeObjectByName(name, &hkxSparselyAnimatedBoolClass));

};

struct hkxSparselyAnimatedInt* hkxAttributeGroup::findIntAttributeByName (const char* name) const
{
	return static_cast<hkxSparselyAnimatedInt*> (findAttributeObjectByName(name, &hkxSparselyAnimatedIntClass));

};

struct hkxSparselyAnimatedEnum* hkxAttributeGroup::findEnumAttributeByName (const char* name) const
{
	return static_cast<hkxSparselyAnimatedEnum*> (findAttributeObjectByName(name, &hkxSparselyAnimatedEnumClass));

};

struct hkxSparselyAnimatedString* hkxAttributeGroup::findStringAttributeByName (const char* name) const
{
	return static_cast<hkxSparselyAnimatedString*> (findAttributeObjectByName(name, &hkxSparselyAnimatedStringClass));

};

struct hkxAnimatedFloat* hkxAttributeGroup::findFloatAttributeByName (const char* name) const
{
	return static_cast<hkxAnimatedFloat*> (findAttributeObjectByName(name, &hkxAnimatedFloatClass));

};

struct hkxAnimatedVector* hkxAttributeGroup::findVectorAttributeByName (const char* name) const
{
	return static_cast<hkxAnimatedVector*> (findAttributeObjectByName(name, &hkxAnimatedVectorClass));
};

struct hkxAnimatedQuaternion* hkxAttributeGroup::findQuaternionAttributeByName (const char* name) const
{
	return static_cast<hkxAnimatedQuaternion*> (findAttributeObjectByName(name, &hkxAnimatedQuaternionClass));

};

struct hkxAnimatedMatrix* hkxAttributeGroup::findMatrixAttributeByName (const char* name) const
{
	return static_cast<hkxAnimatedMatrix*> (findAttributeObjectByName(name, &hkxAnimatedMatrixClass));

};


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
