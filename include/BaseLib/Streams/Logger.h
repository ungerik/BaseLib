/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_Logger_h
#define BaseLib_Streams_Logger_h



#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Streams {



using BaseLib::Containers::Array;



/**
Class for logging-messages, not derived from OutputStream.
Logger is not derived from OutpustStream, because when you want to log something it should 
typically be done atomar. With streams an output-string can be built from many different
stream-operator calls. So the stream can't know when a log-message ends.
We could use new-line as separator, but what if you want to send a multiline message?
So it's more clean to use exactly one call per message.
@see @ref AbstractBinaryBuffer, OutputStream
*/
class BL_EXPORT Logger {
public:

	class AbstractFilter {
	public:
		virtual ~AbstractFilter();
		virtual String filterMessage(const String& message, const String& type) = 0;
	};

	~Logger();

	// write() Methode anstatt eines OutputStreams, da Operationen pro
	// write möglich sein sollen; bei einem Stream könnte man nur newLine
	// als Terminator für ein komplettes write verwenden, was aber unsauber ist:
	/**
	@todo
	*/
	void write(const String& message, const String& type = Empty()) const;
	void write(const String& message, ...) const;

	bool addOutputStream(OutputStream& newOutputStream);
	bool addOutputStream(OutputStream& newOutputStream, AbstractFilter& filter);
	bool removeOutputStream(OutputStream& oldOutputStream);

protected:

	struct LoggerOutput {
		LoggerOutput(OutputStream* newOutputStream, AbstractFilter* newFilter = NULL)
			: outputStream(newOutputStream)
			, filter(newFilter)
		{
		}

		OutputStream* outputStream;
		AbstractFilter* filter;
	};

	typedef Array<LoggerOutput*> LoggerOutputs;
	LoggerOutputs loggerOutputs;

};






} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_Streams_Logger_h