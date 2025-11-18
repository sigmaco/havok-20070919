/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/UnitTest/hkUnitTest.h>

#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/SceneData/Environment/hkxEnvironment.h>

// An error handler that catches all messages and can be used to test that warnings are raised
class hkAssertCatcher : public hkError
{
	public:

		int message(Message m, int id, const char* description, const char* file, int line);

		void setEnabled( int id, hkBool enabled ) {} ;
		hkBool isEnabled( int id ) {return true;} ;
		void enableAll() {}

		static void startCatching ();
		static int countMessagesRaised (int id, bool removeThem);
		static void clearAll ();
		static void stopCatching ();

private:

		static hkError* m_previousErrorHandler;

		struct ErrorMessage
		{
			Message m_type;
			int m_id;
			const char* m_description;
			const char* m_file;
			int m_line;
		};

		hkArray<ErrorMessage> m_messages;

};

hkError* hkAssertCatcher::m_previousErrorHandler = HK_NULL;


void hkAssertCatcher::startCatching()
{
	HK_ASSERT(0x0, m_previousErrorHandler == HK_NULL);
	hkAssertCatcher* newCatcher = new hkAssertCatcher();
	m_previousErrorHandler = &hkError::getInstance();
	m_previousErrorHandler->addReference();
	hkError::replaceInstance(newCatcher);
}

void hkAssertCatcher::stopCatching()
{
	hkAssertCatcher* theCatcher = static_cast<hkAssertCatcher*> (&hkError::getInstance());

	// Flush messages
	for (int i=0; i<theCatcher->m_messages.getSize(); i++)
	{
		const ErrorMessage& m = theCatcher->m_messages[i];

		m_previousErrorHandler->message(m.m_type, m.m_id, m.m_description, m.m_file, m.m_line);
	}

	theCatcher->m_messages.clear();

	hkError::replaceInstance(m_previousErrorHandler);
	m_previousErrorHandler = HK_NULL;
}


int hkAssertCatcher::countMessagesRaised (int id, bool removeThem)
{
	hkAssertCatcher* theCatcher = static_cast<hkAssertCatcher*> (&hkError::getInstance());
	int total = 0;
	for (int i=theCatcher->m_messages.getSize()-1; i>=0; --i)
	{
		if (theCatcher->m_messages[i].m_id==id)
		{
			++total;
			theCatcher->m_messages.removeAt(i);
		}
	}

	return total;
}

void hkAssertCatcher::clearAll ()
{
	hkAssertCatcher* theCatcher = static_cast<hkAssertCatcher*> (&hkError::getInstance());
	theCatcher->m_messages.clear();
}

int hkAssertCatcher::message(Message m, int id, const char* description, const char* file, int line)
{
	ErrorMessage errorMessage;
	errorMessage.m_type = m;
	errorMessage.m_id = id;
	errorMessage.m_description = description;
	errorMessage.m_file = file;
	errorMessage.m_line = line;
	m_messages.pushBack(errorMessage);

	return 0;
}


bool _environmentEquals (const hkxEnvironment& env1, const hkxEnvironment& env2)
{
	const int numEntries = env1.getNumVariables();

	// Must have same number of entries
	if (numEntries != env2.getNumVariables()) return false;

	for (int i=0; i<numEntries; i++)
	{
		const char* name1 = env1.getVariableName(i);
		const char* value1 = env1.getVariableValue(i);

		const char* value2 = env2.getVariableValue(name1);

		if (hkString::strCmp(value1, value2)!=0) return false;
	}

	return true;
}

// TEST SUITE 1 : Basic operations
static void check_basics()
{
	hkxEnvironment theEnvironment;

	theEnvironment.setVariable("var1", "potato");

	// Retrieve value
	{
		const char* value = theEnvironment.getVariableValue("var1");
		HK_TEST(hkString::strCmp(value, "potato")==0);
	}

	// Retrieve should be case-insensitive
	{
		const char* value = theEnvironment.getVariableValue("VAR1");
		HK_TEST(hkString::strCmp(value, "potato")==0);
	}

	// Not known values should be NULL
	{
		const char* value = theEnvironment.getVariableValue("dontknowit");
		HK_TEST(value==HK_NULL);
	}

	// Overwrite value
	{
		const hkResult res = theEnvironment.setVariable("var1", "banana");
		HK_TEST(res==HK_SUCCESS);
		const char* value = theEnvironment.getVariableValue("var1");
		HK_TEST(hkString::strCmp(value, "banana")==0);
	}

	// Overwrite value, case insensitive
	{
		const hkResult res = theEnvironment.setVariable("VaR1", "coconut");
		HK_TEST(res==HK_SUCCESS);
		const char* value = theEnvironment.getVariableValue("vAr1");
		HK_TEST(hkString::strCmp(value, "coconut")==0);
	}

	// Removing variables (not present)
	{
		const hkResult res = theEnvironment.setVariable("dontknowit", HK_NULL);
		HK_TEST(res==HK_FAILURE);
	}

	// Removing variables (present)
	{
		const hkResult res = theEnvironment.setVariable("VAR1", HK_NULL);
		HK_TEST(res==HK_SUCCESS);
		const char* value = theEnvironment.getVariableValue("var1");
		HK_TEST(value==HK_NULL);
	}

	// Adding multiple variables
	{
		theEnvironment.setVariable("vAR1", "rainbow");
		theEnvironment.setVariable("VaR2", "sunshine");
		theEnvironment.setVariable("vAr3", "bluesky");

		const char* value1 = theEnvironment.getVariableValue("var1");
		const char* value2 = theEnvironment.getVariableValue("var2");
		const char* value3 = theEnvironment.getVariableValue("var3");

		HK_TEST(hkString::strCmp(value1, "rainbow")==0);
		HK_TEST(hkString::strCmp(value2, "sunshine")==0);
		HK_TEST(hkString::strCmp(value3, "bluesky")==0);
	}

	// Clearing
	{
		theEnvironment.clear();

		const char* value1 = theEnvironment.getVariableValue("var1");
		const char* value2 = theEnvironment.getVariableValue("var2");
		const char* value3 = theEnvironment.getVariableValue("var3");

		HK_TEST(value1 == HK_NULL);
		HK_TEST(value2 == HK_NULL);
		HK_TEST(value3 == HK_NULL);
	}

	// Size
	{
		HK_TEST(theEnvironment.getNumVariables() == 0);

		theEnvironment.setVariable("test", "blah");

		HK_TEST(theEnvironment.getNumVariables() == 1);

		theEnvironment.setVariable("TEST", "bleh");

		HK_TEST(theEnvironment.getNumVariables() == 1);
	}
}

void check_stringConversion()
{
	// Tests of syntax and semantics
	{
		hkxEnvironment theEnvironment;

		// Basic operation
		{
			const hkResult res = theEnvironment.interpretString("var1=\"dark red\"; \"var 2\"= green; var_3=blue");
			HK_TEST (res == HK_SUCCESS);

			const char* darkred = theEnvironment.getVariableValue("var1");
			HK_TEST(hkString::strCmp(darkred, "dark red")==0);

			const char* green = theEnvironment.getVariableValue("var 2");
			HK_TEST(hkString::strCmp(green, "green")==0);

			const char* blue = theEnvironment.getVariableValue("VAR_3");
			HK_TEST(hkString::strCmp(blue, "blue")==0);
		}		

		// Allow finishing with a semicolon
		{
			const hkResult res = theEnvironment.interpretString("var4=white;");
			HK_TEST (res == HK_SUCCESS);

			const char* white = theEnvironment.getVariableValue("var4");
			HK_TEST(hkString::strCmp(white, "white")==0);
		}

		// Allow empty entries
		{
			const hkResult res = theEnvironment.interpretString("var5=black;;;\"var 6\" = c:\\test/test.hkx");
			HK_TEST	(res == HK_SUCCESS);

			const char* black = theEnvironment.getVariableValue("var5");
			HK_TEST(hkString::strCmp(black, "black")==0);

			const char* test = theEnvironment.getVariableValue("var 6");
			HK_TEST(hkString::strCmp(test, "c:\\test/test.hkx")==0);
		}

		// Allow almost everything inside quotes
		{
			const hkResult res = theEnvironment.interpretString("\"var=7\"= \"a;b; c;\"");
			HK_TEST (res == HK_SUCCESS);

			const char* abc = theEnvironment.getVariableValue("var=7");
			HK_TEST(hkString::strCmp(abc, "a;b; c;")==0);
		}

		// Removal
		{
			const hkResult res = theEnvironment.interpretString("\"VAR 2\"=; vaR1 =      ");
			HK_TEST (res == HK_SUCCESS);

			const char* nothing1 = theEnvironment.getVariableValue("var 2");
			HK_TEST (nothing1 == HK_NULL);

			const char* nothing2 = theEnvironment.getVariableValue("Var1");
			HK_TEST (nothing2 == HK_NULL);
		}
		
	}

	// Syntax only : Random well-formed strings
	{
		hkxEnvironment env;

		const char* goodTests[] =
		{
			"  a = \"c:\\;d:\\;e:/root/\" ;  \"another one\" = A-B-C;",
			" ; k=; path=a,b,c ",
			" PRODUCT = PHYSICS+ANIMATION ;",
			" A = C; \n B = \n D;\n F = G;\t K=L"
		};

		for (hkUint32 i=0; i<sizeof(goodTests)/sizeof(const char*); i++)
		{
			const char* str = goodTests[i];
			const hkResult res = env.interpretString(str);
			HK_TEST (res == HK_SUCCESS);
		}

	}

	// Syntax only : Random ill-formed strings
	{
		hkxEnvironment env;

		const char* badTests[] =
		{
			"potato",
			"carrot=\"",
			";=3;",
			"\"a=b\"",
		};

		for (hkUint32 i=0; i<sizeof(badTests)/sizeof(const char*); i++)
		{
			const char* str = badTests[i];

			hkAssertCatcher::startCatching();
				const hkResult res = env.interpretString(str);
				HK_TEST (res == HK_FAILURE);
				const int numWarnings = hkAssertCatcher::countMessagesRaised(0xabba7881, true);
				HK_TEST (numWarnings == 1);
			hkAssertCatcher::stopCatching();
		}
	}

	// Conversion to string and back
	{
		hkxEnvironment originalEnv;
		originalEnv.setVariable("blah", "bleh");
		originalEnv.setVariable("blue moon", "c:\\; a:/test/");
		originalEnv.setVariable("maths", "2+2=5");
		
		const hkString str = originalEnv.convertToString();

		hkxEnvironment newEnv;
		newEnv.interpretString(str);

		HK_TEST(_environmentEquals(originalEnv, newEnv));
	}
}

int environment_main()
{
	check_basics(); // Basic operations
	check_stringConversion(); // String conversion
	return 0;
}

//void ___1() { }
#if defined(HK_COMPILER_MWERKS)
#	pragma fullpath_file on
#endif
HK_TEST_REGISTER(environment_main, "Fast", "Common/Test/UnitTest/SceneData/", __FILE__     );


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
