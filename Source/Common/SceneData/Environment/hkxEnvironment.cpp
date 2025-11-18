/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/SceneData/hkSceneData.h>
#include <Common/SceneData/Scene/hkxScene.h>
#include <Common/SceneData/Environment/hkxEnvironment.h>
#include <Common/SceneData/Graph/hkxNode.h>

hkResult hkxEnvironment::setVariable (const char* name, const char* value)
{
	const int position = findVariableByName (name);

	if (value==HK_NULL) 
	{
		// Remove
		if (position==-1)
		{
			return HK_FAILURE;
		}
		else
		{
			m_variables.removeAt(position);
			return HK_SUCCESS;
		}
	}

	// Set/Add
	if (position!=-1)
	{
		m_variables[position].m_value = value;
	}
	else
	{
		Variable newVar;
		newVar.m_name = name;
		newVar.m_value = value;
		m_variables.pushBack(newVar);
	}

	return HK_SUCCESS;
}

const char* hkxEnvironment::getVariableValue (const char* name) const
{
	const int position = findVariableByName (name);

	if (position!=-1)
	{
		return m_variables[position].m_value;
	}
	else
	{
		return HK_NULL;
	}

}


void hkxEnvironment::clear ()
{
	m_variables.clear();
}

int hkxEnvironment::findVariableByName(const char* name) const
{
	for (int i=0; i<m_variables.getSize(); i++)
	{
		if (hkString::strCasecmp(m_variables[i].m_name, name)==0)
		{
			return i;
		}
	}

	return -1;
}

int hkxEnvironment::getNumVariables () const
{
	return m_variables.getSize();
}

const char* hkxEnvironment::getVariableName (int i) const
{
	return m_variables[i].m_name;
}

const char* hkxEnvironment::getVariableValue (int i) const
{
	return m_variables[i].m_value;
}

static bool _needsQuotes (const char* str)
{
	while (*str != 0)
	{
		if (*str <= ' ' ) return true;
		if (*str == '=' ) return true;
		if (*str == ';' ) return true;
		str++;
	}

	return false;
}

hkString hkxEnvironment::convertToString () const
{
	hkString result = "";
	
	const hkString quoteStr = "\"";
	for (int i=0; i<m_variables.getSize(); i++)
	{
		const char* name = m_variables[i].m_name;
		const char* value = m_variables[i].m_value;

		hkString nameStr = _needsQuotes(name) ? quoteStr + name + quoteStr : name;
		hkString valueStr = _needsQuotes(value) ? quoteStr + value + quoteStr : value;

		result += nameStr + "=" + valueStr;

		// Add a semicolon after each entry except the last one
		if (i<m_variables.getSize()-1)
		{
			result += "; ";
		}

	}

	return result;
}

hkResult hkxEnvironment::interpretString(const hkString& str)
{
	enum State
	{
		ST_JUMP_BLANKS_1,	// Jumping blanks before name
		ST_NAME_SIMPLE,		// Reading name (no quotes)
		ST_NAME_QUOTES,		// Reading name (inside quotes)
		ST_JUMP_BLANKS_2,	// Jumping blanks after name, before =
		ST_JUMP_BLANKS_3,	// Jumping blanks after = , before value
		ST_VALUE_SIMPLE,	// Reading value (no quotes)
		ST_VALUE_QUOTES,	// Reading value (inside quotes)
		ST_JUMP_BLANKS_4,	// Jumping blanks after value, before ; or end of string
		ST_END,				// Finished
		ST_ERROR,			// Failed
	};

	enum Token
	{
		TK_BLANK,			// Spaces
		TK_QUOTE,			// "
		TK_EQUAL,			// =
		TK_SEMICOLON,		// ;
		TK_OTHER,			// Other characters
		TK_EOS				// End of string
	};

	enum Action
	{
		AC_SKIP,			// Do nothing and continue
		AC_ADD_TO_NAME,		// Add character to name and continue
		AC_ADD_TO_VALUE,	// Add character to value and continue
		AC_ADD_PAIR,		// Add (name,value) to environment, clear both strings, and continue
		AC_REMOVE_VAR,		// Remove the variable (used when VAR= [no value] is found), clear strings, and continue
		AC_NONE,			// Do nothing
		AC_ERROR,			// Error
	};

	struct Transition
	{
		State m_origState;
		Token m_token;
		State m_finalState;
		Action m_action;
	};

	static const Transition transitions[] =
	{
		// Skipping blanks before name
		{ST_JUMP_BLANKS_1,	TK_BLANK,			ST_JUMP_BLANKS_1,	AC_SKIP},
		{ST_JUMP_BLANKS_1,	TK_SEMICOLON,		ST_JUMP_BLANKS_1,	AC_SKIP},
		{ST_JUMP_BLANKS_1,	TK_QUOTE,			ST_NAME_QUOTES,		AC_SKIP},
		{ST_JUMP_BLANKS_1,	TK_OTHER,			ST_NAME_SIMPLE,		AC_ADD_TO_NAME},
		{ST_JUMP_BLANKS_1,	TK_EOS,				ST_END,				AC_NONE},
		
		// Reading name 
		{ST_NAME_SIMPLE,	TK_OTHER,			ST_NAME_SIMPLE,		AC_ADD_TO_NAME},
		{ST_NAME_SIMPLE,	TK_BLANK,			ST_JUMP_BLANKS_2,	AC_SKIP},
		{ST_NAME_SIMPLE,	TK_EQUAL,			ST_JUMP_BLANKS_3,	AC_SKIP},
		
		// Reading name inside quotes
		{ST_NAME_QUOTES,	TK_QUOTE,			ST_JUMP_BLANKS_2,	AC_SKIP},
		{ST_NAME_QUOTES,	TK_OTHER,			ST_NAME_QUOTES,		AC_ADD_TO_NAME},
		{ST_NAME_QUOTES,	TK_BLANK,			ST_NAME_QUOTES,		AC_ADD_TO_NAME},
		{ST_NAME_QUOTES,	TK_SEMICOLON,		ST_NAME_QUOTES,		AC_ADD_TO_NAME},
		{ST_NAME_QUOTES,	TK_EQUAL,			ST_NAME_QUOTES,		AC_ADD_TO_NAME},

		// Skipping blanks before =
		{ST_JUMP_BLANKS_2,	TK_BLANK,			ST_JUMP_BLANKS_2,	AC_SKIP},
		{ST_JUMP_BLANKS_2,	TK_EQUAL,			ST_JUMP_BLANKS_3,	AC_SKIP},

		// Skipping blanks after =
		{ST_JUMP_BLANKS_3,	TK_BLANK,			ST_JUMP_BLANKS_3,	AC_SKIP},
		{ST_JUMP_BLANKS_3,	TK_QUOTE,			ST_VALUE_QUOTES,	AC_SKIP},
		{ST_JUMP_BLANKS_3,	TK_OTHER,			ST_VALUE_SIMPLE,	AC_ADD_TO_VALUE},
		{ST_JUMP_BLANKS_3,	TK_EOS,				ST_END,				AC_REMOVE_VAR},
		{ST_JUMP_BLANKS_3,	TK_SEMICOLON,		ST_JUMP_BLANKS_1,	AC_REMOVE_VAR},

		// Reading value
		{ST_VALUE_SIMPLE,	TK_OTHER,			ST_VALUE_SIMPLE,	AC_ADD_TO_VALUE},
		{ST_VALUE_SIMPLE,	TK_SEMICOLON,		ST_JUMP_BLANKS_1,	AC_ADD_PAIR},
		{ST_VALUE_SIMPLE,	TK_BLANK,			ST_JUMP_BLANKS_4,	AC_ADD_PAIR},
		{ST_VALUE_SIMPLE,	TK_EOS,				ST_END,				AC_ADD_PAIR},

		// Reading value inside quotes
		{ST_VALUE_QUOTES,	TK_QUOTE,			ST_JUMP_BLANKS_4,	AC_ADD_PAIR},
		{ST_VALUE_QUOTES,	TK_OTHER,			ST_VALUE_QUOTES,	AC_ADD_TO_VALUE},
		{ST_VALUE_QUOTES,	TK_BLANK,			ST_VALUE_QUOTES,	AC_ADD_TO_VALUE},
		{ST_VALUE_QUOTES,	TK_SEMICOLON,		ST_VALUE_QUOTES,	AC_ADD_TO_VALUE},
		{ST_VALUE_QUOTES,	TK_EQUAL,			ST_VALUE_QUOTES,	AC_ADD_TO_VALUE},

		// Skipping blanks before ;
		{ST_JUMP_BLANKS_4,	TK_BLANK,			ST_JUMP_BLANKS_4,	AC_SKIP},
		{ST_JUMP_BLANKS_4,	TK_EOS,				ST_END,				AC_NONE},
		{ST_JUMP_BLANKS_4,	TK_SEMICOLON,		ST_JUMP_BLANKS_1,	AC_SKIP},

	};

	State currentState = ST_JUMP_BLANKS_1;
	int currentIndex = 0;
	hkString currentName = "";
	hkString currentValue = "";

	while(1)
	{
		Token currentToken = TK_OTHER;

		if (currentIndex>=str.getLength())
		{
			currentToken = TK_EOS;
		}
		else
		{
			const char character = str[currentIndex];
			if (character <= ' ') currentToken = TK_BLANK;
			if (character == '\"') currentToken = TK_QUOTE;
			if (character == '=') currentToken = TK_EQUAL;
			if (character == ';') currentToken = TK_SEMICOLON;
		}

		// Search for action on the table
		Action action = AC_ERROR;
		State nextState = ST_ERROR;
		const int numItemsTable = sizeof(transitions) / sizeof(Transition);
		for (int i=0; i<numItemsTable; i++)
		{
			if ((transitions[i].m_origState == currentState) && (transitions[i].m_token==currentToken))
			{
				nextState = transitions[i].m_finalState;
				action = transitions[i].m_action;
			}
		}
		
		switch (action)
		{
			case AC_SKIP:
				{
					++currentIndex;
					break;
				}
			case AC_ADD_TO_NAME:
				{
					const char character[2] = {str[currentIndex],0};
					currentName += hkString(character);
					++currentIndex;
					break;
				}
			case AC_ADD_TO_VALUE:
				{
					const char character[2] = {str[currentIndex],0};
					currentValue += hkString(character);
					++currentIndex;
					break;
				}
			case AC_ADD_PAIR:
				{
					setVariable(hkString::strDup(currentName.cString()), hkString::strDup(currentValue.cString()));
					currentName = currentValue = "";
					++currentIndex;
					break;
				}
			case AC_REMOVE_VAR:
				{
					setVariable(currentName.cString(), HK_NULL);
					currentName = currentValue = "";
					++currentIndex;
					break;
				}
			case AC_ERROR:
				{
					HK_WARN_ALWAYS(0xabba7881, "Error parsing environment string: '" << str << "'" );
					// Abort
					return HK_FAILURE;
					break;
				}
			case AC_NONE:
				{
					// Nothing to do;
					break;
				}
			default:
				{
					HK_WARN_ALWAYS(0xabba0032, "Internal Error: Unknown action parsing environment string: '" << str << "'" );
					return HK_FAILURE;
					break;
				}

		}

		currentState = nextState;

		if (currentState == ST_END)
		{
			return HK_SUCCESS;
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
