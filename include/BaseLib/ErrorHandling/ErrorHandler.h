/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_ErrorHandling_ErrorHandler_h
#define BaseLib_ErrorHandling_ErrorHandler_h



#include "BaseLib/Streams/Logger.h"
#include "BaseLib/System/RecursiveMutex.h"



namespace BaseLib {
namespace ErrorHandling {



using BaseLib::Strings::String;
using BaseLib::Streams::Logger;
using BaseLib::System::RecursiveMutex;



class BL_EXPORT ErrorHandler : public Logger {
public:

	ErrorHandler();

	template<class E>
	inline void handleError(const String& message, const String& type = Empty()) const
	{
		RecursiveMutex::ScopedLock lock(mutex); // Errorhandler has to be threadsafe

		if (writingLog == true)
		{
			exit(-1); // Exit application if there is an error in writing an error message
		}

		if (writingLog == true)
		{
			currentlyWritingLog = true;
			write(message, type);
			currentlyWritingLog = false;
		}

		#ifndef BL_NO_EXCEPTIONS
			if (throwingException == true)
			{
				throw E(message);
			}
		#endif
	}

	inline bool isWritingLog() const
	{
		return writingLog;
	}

	inline void setWritingLog(bool shouldWriteLog)
	{
		writingLog = shouldWriteLog;
	}

	inline bool isThrowingException() const
	{
		return throwingException;
	}

	inline void setThrowingException(bool shouldThrowException)
	{
		#ifndef BL_NO_EXCEPTIONS
			throwingException = shouldThrowException;
		#endif
	}

protected:

	static bool currentlyWritingLog;

	mutable RecursiveMutex mutex;
	bool writingLog;
	bool throwingException;
};



} // namespace ErrorHandling
} // namespace BaseLib



#endif // #ifndef BaseLib_ErrorHandling_ErrorHandler_h