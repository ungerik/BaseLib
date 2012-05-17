/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_ErrorHandling_h
#define BaseLib_ErrorHandling_h



#include "BaseLib/ErrorHandling/ErrorDefines.h"
#include "BaseLib/ErrorHandling/ErrorHandler.h"



namespace BaseLib {
namespace ErrorHandling {



using BaseLib::Strings::String;
using namespace BaseLib::Math;



#ifdef BL_PLATFORM_WIN32

extern BL_EXPORT String getLastWindowsError();

#endif



class BL_EXPORT Exception : public std::exception {
public:

	Exception(const Exception& causingException);
	Exception(const Exception& causingException, int errorCode);
	Exception(const Exception& causingException, const String& errorDescription);
	Exception(const Exception& causingException, const String& errorDescription, int errorCode);
    Exception(const String& errorDescription, int errorCode = 0);
	virtual ~Exception() throw();

	virtual const char * what() const throw();

	inline const String& getErrorString() const { return errorString; }
	inline int getErrorNumber() const { return errorNumber; }

protected:
    const String errorString;
	const int errorNumber;
	const Exception* cause;
};



class BL_EXPORT ArgumentException : public Exception {
public:
	ArgumentException(const Exception& causingException);
	ArgumentException(const Exception& causingException, int errorCode);
	ArgumentException(const Exception& causingException, const String& errorDescription);
	ArgumentException(const Exception& causingException, const String& errorDescription, int errorCode);
    ArgumentException(const String& errorDescription, int errorCode = 0);
};



class BL_EXPORT LogicException : public Exception {
public:
	LogicException(const Exception& causingException);
	LogicException(const Exception& causingException, int errorCode);
	LogicException(const Exception& causingException, const String& errorDescription);
	LogicException(const Exception& causingException, const String& errorDescription, int errorCode);
    LogicException(const String& errorDescription, int errorCode = 0);
};



class BL_EXPORT ResultException : public Exception {
public:
	ResultException(const Exception& causingException);
	ResultException(const Exception& causingException, int errorCode);
	ResultException(const Exception& causingException, const String& errorDescription);
	ResultException(const Exception& causingException, const String& errorDescription, int errorCode);
    ResultException(const String& errorDescription, int errorCode = 0);
};



class BL_EXPORT IoException : public Exception {
public:
	IoException(const Exception& causingException);
	IoException(const Exception& causingException, int errorCode);
	IoException(const Exception& causingException, const String& errorDescription);
	IoException(const Exception& causingException, const String& errorDescription, int errorCode);
    IoException(const String& errorDescription, int errorCode = 0);
};



class BL_EXPORT StateException : public Exception {
public:
	StateException(const Exception& causingException);
	StateException(const Exception& causingException, int errorCode);
	StateException(const Exception& causingException, const String& errorDescription);
	StateException(const Exception& causingException, const String& errorDescription, int errorCode);
    StateException(const String& errorDescription, int errorCode = 0);
};



class BL_EXPORT NotImplementedException : public Exception {
public:
	NotImplementedException(const Exception& causingException);
	NotImplementedException(const Exception& causingException, int errorCode);
	NotImplementedException(const Exception& causingException, const String& errorDescription);
	NotImplementedException(const Exception& causingException, const String& errorDescription, int errorCode);
    NotImplementedException(const String& errorDescription, int errorCode = 0);
};





extern BL_EXPORT ErrorHandler argumentErrorHandler;
extern BL_EXPORT ErrorHandler logicErrorHandler;
extern BL_EXPORT ErrorHandler resultErrorHandler;
extern BL_EXPORT ErrorHandler ioErrorHandler;
extern BL_EXPORT ErrorHandler stateErrorHandler;
extern BL_EXPORT ErrorHandler notImplementedErrorHandler;



inline void argumentError(const String& message, const String& type = Empty())
{
	#ifndef NO_ARGUMENT_ERRORS
		argumentErrorHandler.handleError<ArgumentException>(message, type);
	#endif
}



inline void logicError(const String& message, const String& type = Empty())
{
	#ifndef NO_LOGIC_ERRORS
		logicErrorHandler.handleError<LogicException>(message, type);
	#endif
}



inline void resultError(const String& message, const String& type = Empty())
{
	#ifndef NO_RESULT_ERRORS
		resultErrorHandler.handleError<ResultException>(message, type);
	#endif
}



inline void ioError(const String& message, const String& type = Empty())
{
	#ifndef NO_IO_ERRORS
		ioErrorHandler.handleError<IoException>(message, type);
	#endif
}



inline void stateError(const String& message, const String& type = Empty())
{
	#ifndef NO_STATE_ERRORS
		stateErrorHandler.handleError<StateException>(message, type);
	#endif
}



inline void notImplementedError(const String& message = "Functionality not implemented yet!", const String& type = Empty())
{
	#ifndef NO_STATE_ERRORS
		notImplementedErrorHandler.handleError<NotImplementedException>(message, type);
	#endif
}



template<typename T>
inline bool checkArgumentMin(T argument, T minimum, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument < minimum)
	{
		argumentError(String("Argument ") + String::createFrom(argument) + " is smaller than minimum=" + String::createFrom(minimum) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkArgumentMax(T argument, T maximum, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument > maximum)
	{
		argumentError(String("Argument ") + String::createFrom(argument) + " is greater than maximum=" + String::createFrom(maximum) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkArgumentRange(T argument, T minimum, T maximum, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (checkArgumentMin<T>(argument, minimum, errorAt) == true)
	{
		return checkArgumentMax<T>(argument, maximum, errorAt);
	}
	else
#endif
	{
		return true;
	}	
}



template<typename T>
inline bool checkArgumentRange(T argument, T maximum, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (checkArgumentPositive<T>(argument, errorAt) == true)
	{
		return checkArgumentMax<T>(argument, maximum, errorAt);
	}
	else
#endif
	{
		return true;
	}	
}



template<typename T>
inline bool checkArgumentPositive(T argument, const char * errorAt = ERROR_AT)
{
	return checkArgumentMin(argument, 0, errorAt);
}



inline bool checkArgumentNotNull(const void* argument, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument == NULL)
	{
		argumentError(String("Argument must not be null! ") + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkArgumentMin(const char * argumentName, T argument, T minimum, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument < minimum)
	{
		argumentError(String("Argument ") + argumentName + "=" + String::createFrom(argument) + " is smaller than minimum=" + String::createFrom(minimum) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



//template<>
//inline bool checkArgumentMin(const char * argumentName, const void* argument, const void* minimum, const char * errorAt = ERROR_AT)
//{
//	return checkArgumentMin<pint>(argumentName, reinterpret_cast<pint>(argument), reinterpret_cast<pint>(minimum), errorAt);
//}



template<typename T>
inline bool checkArgumentMax(const char * argumentName, T argument, T maximum, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument > maximum)
	{
		argumentError(String("Argument ") + argumentName + "=" + String::createFrom(argument) + " is greater than maximum=" + String::createFrom(maximum) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



//template<>
//inline bool checkArgumentMax(const char * argumentName, const void* argument, const void* maximum, const char * errorAt = ERROR_AT)
//{
//	return checkArgumentMax<pint>(argumentName, reinterpret_cast<pint>(argument), reinterpret_cast<pint>(maximum), errorAt);
//}



template<typename T>
inline bool checkArgumentGreater(const char * argumentName, T argument, T limit, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument <= limit)
	{
		argumentError(String("Argument ") + argumentName + "=" + String::createFrom(argument) + " is not greater than limit=" + String::createFrom(limit) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkArgumentSmaller(const char * argumentName, T argument, T limit, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument >= limit)
	{
		argumentError(String("Argument ") + argumentName + "=" + String::createFrom(argument) + " is not small than limit=" + String::createFrom(limit) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkArgumentEquals(const char * argumentName, T argument, T value, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument != value)
	{
		argumentError(String("Argument ") + argumentName + "=" + String::createFrom(argument) + " is not equal value=" + String::createFrom(value) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkArgumentRange(const char * argumentName, T argument, T minimum, T maximum, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (checkArgumentMin<T>(argumentName, argument, minimum, errorAt) == true)
	{
		return checkArgumentMax<T>(argumentName, argument, maximum, errorAt);
	}
	else
#endif
	{
		return true;
	}	
}



//template<typename T>
//inline bool checkArgumentRange(const char * argumentName, T argument, T maximum, const char * errorAt = ERROR_AT)
//{
//	if (checkArgumentPositive<T>(argumentName, argument, errorAt) == true)
//	{
//		return checkArgumentMax<T>(argumentName, argument, maximum, errorAt);
//	}
//	else
//	{
//		return false;
//	}	
//}



template<typename T>
inline bool checkArgumentPositive(const char * argumentName, T argument, const char * errorAt = ERROR_AT)
{
	return checkArgumentMin<T>(argumentName, argument, 0, errorAt);
}



inline bool checkArgumentNotNull(const char * argumentName, const void* argument, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument == NULL)
	{
		argumentError(String("Argument ") + argumentName + " must not be null !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkArgumentIsValidFloat(const char * argumentName, const T argument, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (isValidFloatNumber(argument) == false)
	{
		argumentError(String("Argument ") + argumentName + " is not a valid float-number !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkArgumentIsValidFloatAndNotZero(const char * argumentName, const T argument, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (isValidFloatNumber(argument) == false || argument == 0)
	{
		argumentError(String("Argument ") + argumentName + " is not a valid float-number or zero!" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



inline bool checkStateNotNull(const void* state, const char * errorAt = ERROR_AT)
{
#ifndef NO_STATE_CHECKS
	if (state == NULL)
	{
		stateError(String("State-value must not be null! ") + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



inline bool checkStateNotNull(const String& stateName, const void* state, const char * errorAt = ERROR_AT)
{
#ifndef NO_STATE_CHECKS
	if (state == NULL)
	{
		stateError("State " + stateName + " must not be null! " + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkStateIsValidFloat(const String& stateName, const T state, const char * errorAt = ERROR_AT)
{
#ifndef NO_STATE_CHECKS
	if (isValidFloatNumber(state) == false)
	{
		stateError("State " + stateName + " is not a valid float-number !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkStateIsValidFloatAndNotZero(const String& stateName, const T state, const char * errorAt = ERROR_AT)
{
#ifndef NO_STATE_CHECKS
	if (isValidFloatNumber(state) == false || state == 0)
	{
		stateError("State " + stateName + " is not a valid float-number or zero!" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkState(const String& stateName, const T state, const char * errorAt = ERROR_AT)
{
#ifndef NO_STATE_CHECKS
	if (state == static_cast<T>(0))
	{
		stateError("State " + stateName + " is not true!" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkStateGreater(const String& stateName, T state, T limit, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (state <= limit)
	{
		argumentError(String("State ") + stateName + "=" + String::createFrom(state) + " is not greater than limit=" + String::createFrom(limit) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



template<typename T>
inline bool checkStateSmaller(const String& stateName, T state, T limit, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (state >= limit)
	{
		argumentError(String("State ") + stateName + "=" + String::createFrom(state) + " is not small than limit=" + String::createFrom(limit) + " !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



inline bool checkArgumentNull(const void* argument, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument != NULL)
	{
		argumentError(String("Argument must not be null! ") + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



inline bool checkArgumentNull(const char * argumentName, const void* argument, const char * errorAt = ERROR_AT)
{
#ifndef NO_ARGUMENT_CHECKS
	if (argument != NULL)
	{
		argumentError(String("Argument ") + argumentName + " must not be null !" + errorAt);
		return false;
	}
	else
#endif
	{
		return true;
	}
}



} // namespace ErrorHandling
} // namespace BaseLib



#endif // #ifndef BaseLib_ErrorHandling_h