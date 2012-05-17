/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Testing_TestCase_h
#define BaseLib_Testing_TestCase_h



#include "BaseLib/Strings/String.h"
#include "BaseLib/Functors/Functor0.h"
#include "BaseLib/Console.h"
#include "BaseLib/Utilities/AutoPointer.h"



namespace BaseLib {
namespace Testing {



struct BL_EXPORT UnitTestAssertFailed {

	UnitTestAssertFailed(const BaseLib::Strings::String& what)
		: assertion(what)
	{
	}

	const BaseLib::Strings::String assertion;
};



class BL_EXPORT TestCase {
public:

	explicit TestCase(const BaseLib::Strings::String& testCaseName);

	virtual ~TestCase();
	virtual void setUp();
	virtual void tearDown();

	virtual void runTests() = 0;


	#define TEST_ASSERT(t) { ++testAssertCount; if ( !(t) ) throw UnitTestAssertFailed(BaseLib::Strings::String("TEST_ASSERT(") + #t + ") at line " + BaseLib::Strings::String::createFrom(__LINE__) + " in file '" + __FILE__ + "' FAILED!"); }
	#define CATCH_ASSERT(e) catch (e) { assertExceptionCatched = true; } if (assertExceptionCatched == false) throw UnitTestAssertFailed(BaseLib::Strings::String("Exception ") + #e + " not catched at line" + BaseLib::Strings::String::createFrom(__LINE__) + " in file '" + __FILE__ + "'!"); else assertExceptionCatched = false; ++catchAssertCount;


	inline int getAssertCount() const { return testAssertCount + catchAssertCount; }
	inline int getFailedAssertCount() const { return failedTestAssertCount; }
	inline const BaseLib::Strings::String& getName() const { return name; }

	static int getFailedTestCount();

	static void run(TestCase* testCase);

	static void summary();

protected:

	typedef BaseLib::Functors::Functor0<void> TestFunctor;

	template<class C>
	void namedTest(void (C::*testFunction)(), const BaseLib::Strings::String& testName)
	{
		namedTestImplementation(new BaseLib::Functors::MethodFunctor0<C, void>(static_cast<C*>(this), testFunction), testName);
	}

	void namedTestImplementation(TestFunctor* testFunction, const BaseLib::Strings::String& testName);

	#define runTest(t) { const BaseLib::Strings::String arg = #t; namedTest(t, arg.subString(arg.findLast(':')+1)); }


	const BaseLib::Strings::String name;
	bool assertExceptionCatched;
	int testAssertCount;
	int catchAssertCount;
	int failedTestAssertCount;

	static int testCount;
	static int failedTestCount;
	static int exceptionsCount;
};



} // namespace Testing
} // namespace BaseLib



#endif // #ifndef BaseLib_Testing_TestCase_h