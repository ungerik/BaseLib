/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Console/AbstractDriver.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/Buffers/DefaultTextBuffer.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/System/Thread.h"



namespace BaseLib {
namespace Console {



using namespace BaseLib::Buffers;
using namespace BaseLib::System;
using namespace BaseLib::Containers;




//class ConsoleTextBuffer : public DefaultTextBuffer {
//public:
//
//	ConsoleTextBuffer(AbstractDriver* newConsoleAbstractDriver)
//	  : consoleAbstractDriver(newConsoleAbstractDriver)
//	  , readTimeoutSeconds(Time::VERY_LONG)
//	  , insert(true)
//	  , echoInput(newConsoleAbstractDriver->isEchoInput())
//	  , autocompletionFunctor(newConsoleAbstractDriver->getAutocompletionCallback())
//	  , maxInputHistorySize(getMaxInputHistorySize())
//	  , inputHistory(newConsoleAbstractDriver->getInputHistory())
//	{		
//	}
//
//
//
//	virtual void writeAtPosition(int position, const String& source) // position is ignored
//	{
//		write(source);
//	}
//
//	virtual bool readFromCurrentPositionPossible() const
//	{
//		return isInputAvailable();
//	}
//
//	virtual void setCurrentPosition(int newCurrentPosition) // position is ignored
//	{
//	}
//
//	virtual double getTimeoutForNextRead() const
//	{
//		return readTimeoutSeconds;
//	}
//
//	virtual void setTimeoutForNextRead(double newReadTimeoutSeconds)
//	{
//		BL_ASSERT(newReadTimeoutSeconds >= 0);
//		readTimeoutSeconds = newReadTimeoutSeconds;
//	}
//
//protected:
//	
//	AbstractDriver* consoleAbstractDriver;
//	double readTimeoutSeconds;
//	mutable bool insert;
//	const bool& echoInput;
//	const AutocompletionFunc& autocompletionFunctor;
//	const int& maxInputHistorySize;
//	AbstractDriver::InputHistory& inputHistory;
//
//};



/////////////////////////////////////////////////////////////////////////////////



AbstractDriver::AbstractDriver()
	: NonCopyable() 
	, inputStream()
	, outputStream()
	, echoInput(true)
	, autocompletionFunctor(NULL)
	, maxInputHistorySize(16)
	, inputHistory()
	, insert(true)
{
	inputStream.setReadTimeoutSeconds(Time::VERY_LONG);
	inputStream.connectToFunctor(StringInputStream::NoConstMethodFunctor<AbstractDriver>(this, &AbstractDriver::read));
	inputStream.connectToInputAvailableFunctor(StringInputStream::InputAvailableMethodFunctor<AbstractDriver>(this, &AbstractDriver::isInputAvailable));

	outputStream.connectToFunctor(StringOutputStream::MethodFunctor<AbstractDriver>(this, &AbstractDriver::writeUnchecked));
}



AbstractDriver::~AbstractDriver()
{
}



void AbstractDriver::setMaxInputHistorySize(int newMaxInputHistorySize)
{
	BL_ASSERT(newMaxInputHistorySize >= 0);
	if (newMaxInputHistorySize != maxInputHistorySize)
	{
		maxInputHistorySize = newMaxInputHistorySize;

		if ((int)inputHistory.size() > maxInputHistorySize) inputHistory.resize(maxInputHistorySize);
	}
}



void AbstractDriver::addToInputHistory(const String& string)
{
	if (maxInputHistorySize > 0)
	{
		inputHistory.push_front(string);
		if ((int)inputHistory.size() > maxInputHistorySize) inputHistory.resize(maxInputHistorySize);
	}
}



void AbstractDriver::writeUnchecked(const String& source)
{
	write(source);
}



String AbstractDriver::read()
{
	String result;

	double timeout = inputStream.getReadTimeoutSeconds();
	if (timeout == 0.0)
	{
		while (isInputAvailable() == true)
		{
			result += getChar();
		}
		if (echoInput == true) write(result);

		addToInputHistory(result);
		return result;
	}
	else
	{
		const double endTime = Time::nowInSeconds() + timeout;
		String rightOfCursor;
		int inputHistoryPosition = -1;

		do
		{
			if (isInputAvailable() == true)
			{
				char8 c = wchar2char(getChar());
				switch(c)
				{
					case '\b':
						if (result.isEmpty() == false)
						{
							result.setLength(result.getLength()-1);
							if (echoInput == true) write(String("\b") + rightOfCursor + " " + String('\b', rightOfCursor.getLength()+1));
						}
						break;

					case 27: // escape
						if (echoInput == true) write(String('\b', result.getLength()) + String(' ', result.getLength()+rightOfCursor.getLength()) + String('\b', result.getLength()+rightOfCursor.getLength()));
						result = c;
						return result;

					case '\r':
					case '\n':
						addToInputHistory(result + rightOfCursor);
						return result;

					case 0:
					case (char8)0xE0:
						switch(getChar())
						{
							case 75: // left
								if (result.isEmpty() == false)
								{
									rightOfCursor.insert(result[result.getLength()-1]);
									result.setLength(result.getLength()-1);
									if (echoInput == true) write("\b");
								}
								break;

							case 77: // right
								if (rightOfCursor.isEmpty() == false)
								{
									result += (rightOfCursor[0]);
									if (echoInput == true) write(rightOfCursor.subString(0, 1));
									rightOfCursor.remove(0);
								}
								break;

							case 72: // up
								if (inputHistoryPosition < static_cast<int>(inputHistory.size())-1)
								{
									++inputHistoryPosition;
									if (echoInput == true)
									{
										write(String('\b', result.getLength()) + String(' ', result.getLength()+rightOfCursor.getLength()) + String('\b', result.getLength()+rightOfCursor.getLength()));
										rightOfCursor.setLength(0);
										BL_ASSERT(inputHistoryPosition < (int)inputHistory.size());
										result = inputHistory[inputHistoryPosition];
										write(result);											
									}
								}
								break;

							case 80: // down
								if (inputHistoryPosition > 0)
								{
									--inputHistoryPosition;
									if (echoInput == true)
									{
										write(String('\b', result.getLength()) + String(' ', result.getLength()+rightOfCursor.getLength()) + String('\b', result.getLength()+rightOfCursor.getLength()));
										rightOfCursor.setLength(0);
										BL_ASSERT(inputHistoryPosition >= 0 && inputHistoryPosition < (int)inputHistory.size());
										result = inputHistory[inputHistoryPosition];
										write(result);											
									}
								}
								break;

							case 71: // home
							case 73: // page-up
								if (result.isEmpty() == false)
								{
									if (echoInput == true) write(String('\b', result.getLength()));
									rightOfCursor.insert(result);
									result.setLength(0);
								}
								break;

							case 79: // end
							case 81: // page-down
								if (rightOfCursor.isEmpty() == false)
								{
									if (echoInput == true) write(rightOfCursor);
									result += rightOfCursor;
									rightOfCursor.setLength(0);
								}
								break;

							case 82: // insert
								insert = !insert;
								break;

							case 83: // delete
								if (rightOfCursor.isEmpty() == false)
								{
									rightOfCursor.remove(0);
									if (echoInput == true) write(rightOfCursor + " " + String('\b', rightOfCursor.getLength()+1));
								}
								break;

							default:
							//case 59..68: // F1-F10
								break;
						}
						break;
					
					case '\t':
						if (autocompletionFunctor != NULL)
						{
							const int incompleteLength = result.getLength();
							(*autocompletionFunctor)(result);
							BL_ASSERT(result.getLength() >= incompleteLength);
							if (echoInput == true && result.getLength() > incompleteLength) write(result.subString(incompleteLength));
							break;
						}
						else
						{
							c = ' ';
						}

					default:
						result += c;
						if (rightOfCursor.isEmpty() == false)
						{
							if (insert == true)
							{
								if (echoInput == true) write(String(c) + rightOfCursor + String('\b', rightOfCursor.getLength()));
							}
							else
							{
								rightOfCursor.remove(0);
								if (echoInput == true) write(String(c));
							}
						}
						else
						{
							if (echoInput == true) write(String(c));
						}
				}
			}
			else
			{
				Thread::sleepSeconds(0.01);
			}
			timeout = endTime - Time::nowInSeconds();
		}
		while (timeout >= 0.0);

		//return addToInputHistory(result + rightOfCursor);
		result = '\27';
		return result;
	}
}



} // namespace Console
} // namespace BaseLib
