/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/intern/Windows.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Containers/Stack.h"
#include "BaseLib/Console.h"
//#include <cassert>
#include <vector>



namespace BaseLib {
namespace ErrorHandling {



using namespace BaseLib::Containers;



ErrorHandler argumentErrorHandler;
ErrorHandler logicErrorHandler;
ErrorHandler resultErrorHandler;
ErrorHandler ioErrorHandler;
ErrorHandler stateErrorHandler;
ErrorHandler notImplementedErrorHandler;



String getLastWindowsError()
{
    char16 errorString[2048];
    errorString[0] = '\0';
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), errorString, sizeof(errorString), NULL);
    return String(errorString);
}



Exception::Exception(const Exception& causingException)
	: std::exception()
	, errorString(causingException.what())
	, errorNumber(causingException.getErrorNumber())
	, cause(&causingException)
{
}



Exception::Exception(const Exception& causingException, int errorCode)
	: std::exception()
	, errorString(causingException.what())
	, errorNumber(errorCode)
	, cause(&causingException)
{
}



Exception::Exception(const Exception& causingException, const String& errorDescription)
	: std::exception(errorDescription.getChar8CString())
	, errorString(errorDescription)
	, errorNumber(causingException.getErrorNumber())
	, cause(&causingException)
{
}



Exception::Exception(const Exception& causingException, const String& errorDescription, int errorCode)
	: std::exception(errorDescription.getChar8CString())
	, errorString(errorDescription)
	, errorNumber(errorCode)
	, cause(&causingException)
{
}



Exception::Exception(const String& errorDescription, int errorCode)
	: std::exception(errorDescription.getChar8CString())
	, errorString(errorDescription)
	, errorNumber(errorCode)
	, cause(NULL)
{
}



Exception::~Exception()
{
}



const char * Exception::what() const
{
	return errorString.getChar8CString();
}



ArgumentException::ArgumentException(const Exception& causingException)
	: Exception(causingException)
{
}



ArgumentException::ArgumentException(const Exception& causingException, int errorCode)
	: Exception(causingException, errorCode)
{
}



ArgumentException::ArgumentException(const Exception& causingException, const String& errorDescription)
	: Exception(causingException, errorDescription)
{
}



ArgumentException::ArgumentException(const Exception& causingException, const String& errorDescription, int errorCode)
	: Exception(causingException, errorDescription, errorCode)
{
}



ArgumentException::ArgumentException(const String& errorDescription, int errorCode)
	: Exception(errorDescription, errorCode)
{
}



LogicException::LogicException(const Exception& causingException)
	: Exception(causingException)
{
}



LogicException::LogicException(const Exception& causingException, int errorCode)
	: Exception(causingException, errorCode)
{
}



LogicException::LogicException(const Exception& causingException, const String& errorDescription)
	: Exception(causingException, errorDescription)
{
}



LogicException::LogicException(const Exception& causingException, const String& errorDescription, int errorCode)
	: Exception(causingException, errorDescription, errorCode)
{
}



LogicException::LogicException(const String& errorDescription, int errorCode)
	: Exception(errorDescription, errorCode)
{
}



ResultException::ResultException(const Exception& causingException)
	: Exception(causingException)
{
}



ResultException::ResultException(const Exception& causingException, int errorCode)
	: Exception(causingException, errorCode)
{
}



ResultException::ResultException(const Exception& causingException, const String& errorDescription)
	: Exception(causingException, errorDescription)
{
}



ResultException::ResultException(const Exception& causingException, const String& errorDescription, int errorCode)
	: Exception(causingException, errorDescription, errorCode)
{
}



ResultException::ResultException(const String& errorDescription, int errorCode)
	: Exception(errorDescription, errorCode)
{
}



IoException::IoException(const Exception& causingException)
	: Exception(causingException)
{
}



IoException::IoException(const Exception& causingException, int errorCode)
	: Exception(causingException, errorCode)
{
}



IoException::IoException(const Exception& causingException, const String& errorDescription)
	: Exception(causingException, errorDescription)
{
}



IoException::IoException(const Exception& causingException, const String& errorDescription, int errorCode)
	: Exception(causingException, errorDescription, errorCode)
{
}



IoException::IoException(const String& errorDescription, int errorCode)
	: Exception(errorDescription, errorCode)
{
}



StateException::StateException(const Exception& causingException)
	: Exception(causingException)
{
}



StateException::StateException(const Exception& causingException, int errorCode)
	: Exception(causingException, errorCode)
{
}



StateException::StateException(const Exception& causingException, const String& errorDescription)
	: Exception(causingException, errorDescription)
{
}



StateException::StateException(const Exception& causingException, const String& errorDescription, int errorCode)
	: Exception(causingException, errorDescription, errorCode)
{
}



StateException::StateException(const String& errorDescription, int errorCode)
	: Exception(errorDescription, errorCode)
{
}







NotImplementedException::NotImplementedException(const Exception& causingException)
	: Exception(causingException)
{
}



NotImplementedException::NotImplementedException(const Exception& causingException, int errorCode)
	: Exception(causingException, errorCode)
{
}



NotImplementedException::NotImplementedException(const Exception& causingException, const String& errorDescription)
	: Exception(causingException, errorDescription)
{
}



NotImplementedException::NotImplementedException(const Exception& causingException, const String& errorDescription, int errorCode)
	: Exception(causingException, errorDescription, errorCode)
{
}



NotImplementedException::NotImplementedException(const String& errorDescription, int errorCode)
	: Exception(errorDescription, errorCode)
{
}











} // namespace ErrorHandling
} // namespace BaseLib