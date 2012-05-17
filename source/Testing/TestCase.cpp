/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Testing/TestCase.h"



namespace BaseLib {
namespace Testing {



using namespace BaseLib;
using namespace BaseLib::Streams;



void TestCase::run(TestCase* testCase)
{
	AutoPointer<TestCase> testCaseHolder(testCase);
	OutputStream output(BaseLib::Console::out, BaseLib::Console::trace);
	output << "Performing tests of test-case [" << testCase->getName() << "]:" << BaseLib::Streams::newLine;
	testCase->runTests();
	output << "Performed " << testCase->getAssertCount() << " test-asserts where " << testCase->getFailedAssertCount() << " of them failed." << BaseLib::Streams::newLine << BaseLib::Streams::newLine;
	++testCount;
	if (testCase->getFailedAssertCount() != 0) ++failedTestCount;
}



int TestCase::getFailedTestCount()
{
	return failedTestCount;
}



void TestCase::summary()
{
	OutputStream output(BaseLib::Console::out, BaseLib::Console::trace);
	output
		<< "Summary: "
		<< testCount
		<< " tests ("
		<< failedTestCount
		<< " failing asserts) with "
		<< exceptionsCount
		<< " exceptions "
		<< newLine
		<< newLine;
}



TestCase::TestCase(const String& testCaseName)
	: name(testCaseName)
	, assertExceptionCatched(false)
	, testAssertCount(0)
	, catchAssertCount(0)
	, failedTestAssertCount(0)
{
}



TestCase::~TestCase()
{
}



void TestCase::setUp()
{
}



void TestCase::tearDown()
{
}



void TestCase::namedTestImplementation(TestFunctor* testFunction, const BaseLib::Strings::String& testName)
{
	AutoPointer<TestFunctor> testFunctionHolder(testFunction);
	OutputStream output(BaseLib::Console::out, BaseLib::Console::trace);

	output << "Test [" << testName << "] -> ";
	bool exceptionCatched = false;
	try
	{
		setUp();
	}
	catch (...)
	{
		output << "Error in setUp() before test [" << testName << "] in test-case [" << name << "]!" << BaseLib::Streams::newLine;
		output << "Quiting unit-test now..." << BaseLib::Streams::newLine;
		exit(-1);
	}

	try
	{
		(*testFunction)();
	}
	catch (const UnitTestAssertFailed& e)
	{
		output << "FAILED because: " << e.assertion << BaseLib::Streams::newLine;
		++failedTestAssertCount;
		exceptionCatched = true;
	}		
	catch (const std::exception& e)
	{
		output << "FAILED because of std::exception: " << e.what() << BaseLib::Streams::newLine;
		++exceptionsCount;
		exceptionCatched = true;
	}
	catch (...)
	{
		output << "FAILED because of unknown exception!" << BaseLib::Streams::newLine;
		++exceptionsCount;
		exceptionCatched = true;
	}

	if (exceptionCatched == true)
	{
		try
		{
			tearDown();
			return;
		}
		catch (...)
		{
			output << "Error in tearDown() after error in test [" << testName << "] of test-case [" << name << "]!" << BaseLib::Streams::newLine;
			output << "Quiting unit-test now..." << BaseLib::Streams::newLine;
			exit(-1);
		}
	}

	try
	{
		tearDown();
	}
	catch (...)
	{
		output << "Error in tearDown() after test [" << testName << "] in test-case [" << name << "]!" << BaseLib::Streams::newLine;
		output << "Quiting unit-test now..." << BaseLib::Streams::newLine;
		exit(-1);
	}

	output << "OK" << BaseLib::Streams::newLine;
}



} // namespace Testing
} // namespace BaseLib

