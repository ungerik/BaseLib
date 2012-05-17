/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/Logger.h"
#include <stdarg.h>



namespace BaseLib {
namespace Streams {



Logger::AbstractFilter::~AbstractFilter()
{
}



Logger::~Logger()
{
	foreach (LoggerOutputs::Iterator, i, loggerOutputs)
	{
		delete *i;
	}
}



void Logger::write(const String& message, const String& type) const
{
	for (LoggerOutputs::ConstIterator i = loggerOutputs.begin(); i != loggerOutputs.end(); ++i)
	{
		*((*i)->outputStream) << (((*i)->filter != NULL) ? (*i)->filter->filterMessage(message, type) : message) << newLine;
	}
}



void Logger::write(const String& message, ...) const
{
	va_list	argumentList;
	va_start(argumentList, message);
	write(String::createFrom(message, argumentList), String());
}



bool Logger::addOutputStream(OutputStream& newOutputStream)
{
	return addOutputStream(newOutputStream, *static_cast<AbstractFilter*>(NULL));
}



bool Logger::addOutputStream(OutputStream& newOutputStream, AbstractFilter& filter)
{
	foreach (LoggerOutputs::Iterator, i, loggerOutputs)
	{
		if ((*i)->outputStream == &newOutputStream) return false;
	}

	loggerOutputs += new LoggerOutput(&newOutputStream, &filter);
	return true;
}



bool Logger::removeOutputStream(OutputStream& oldOutputStream)
{
	foreach (LoggerOutputs::Iterator, i, loggerOutputs)
	{
		if ((*i)->outputStream == &oldOutputStream)
		{
			delete *i;
			loggerOutputs -= i;
			return true;
		}
	}

	return false;
}




} // namespace Streams
} // namespace BaseLib