/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/intern/Errors.h"
#include "BaseLib/Streams/TextInputStream.h"
#include "BaseLib/Buffers/TextBuffer.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/System/Thread.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::Containers;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;



TextInputStream::TextInputStream(StringEncoding newStringEncoding)
  : InputStream()
  , BinaryStreamEncoding(newStringEncoding)
  , connectedTextBuffer(NULL)
  , unreadWhenLexicalCastFailed(true)
  , readBuffer(newStringEncoding == CHAR8 ? CHAR8_ENCODING : CHAR16_ENCODING)
  , readBinaryMethode(INTERPRET_STRING_AS_BINARY_DATA)
  , readStringMethod(READ_STRING)
  , readTextBufferMethode(READ_TEXT_BUFFER_LINE)
  , tokenDelimiters(defaultTokenDelimiters)
  , lineEndChars(defaultLineEndChars)
{
	BL_ASSERT(newStringEncoding != STRING_IMPLEMENTATION);
}



TextInputStream::TextInputStream(const InputStream& connectToInputStream, StringEncoding newStringEncoding)
  : InputStream(connectToInputStream)
  , BinaryStreamEncoding(newStringEncoding)
  , connectedTextBuffer(NULL)
  , unreadWhenLexicalCastFailed(true)
  , readBuffer(newStringEncoding == CHAR8 ? CHAR8_ENCODING : CHAR16_ENCODING)
  , readBinaryMethode(INTERPRET_STRING_AS_BINARY_DATA)
  , readStringMethod(READ_STRING)
  , readTextBufferMethode(READ_TEXT_BUFFER_LINE)
  , tokenDelimiters(defaultTokenDelimiters)
  , lineEndChars(defaultLineEndChars)
{
	BL_ASSERT(newStringEncoding != STRING_IMPLEMENTATION);
}



TextInputStream::TextInputStream(AbstractTextBuffer& connectToBuffer, StringEncoding newStringEncoding)
  : InputStream()
  , BinaryStreamEncoding(newStringEncoding)
  , connectedTextBuffer(NULL)
  , unreadWhenLexicalCastFailed(true)
  , readBuffer(newStringEncoding == CHAR8 ? CHAR8_ENCODING : CHAR16_ENCODING)
  , readBinaryMethode(INTERPRET_STRING_AS_BINARY_DATA)
  , readStringMethod(READ_STRING)
  , readTextBufferMethode(READ_TEXT_BUFFER_LINE)
  , tokenDelimiters(defaultTokenDelimiters)
  , lineEndChars(defaultLineEndChars)
{
	BL_ASSERT(newStringEncoding != STRING_IMPLEMENTATION);
	connectToTextBuffer(connectToBuffer);
}



TextInputStream::~TextInputStream()
{
	disconnectFromTextBuffer();
}



int TextInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
{
	BL_ASSERT_NEVER_REACHED

	BL_ASSERT(byteCount >= 0);
	BL_ASSERT(timeoutSeconds >= 0.0);

	bool readBufferRead = false;

	if (shouldUseUnicode() == false)
	{
		if (readBuffer.isEmpty() == true) 
		{ 
			if (read(readBuffer, timeoutSeconds) == false) return 0;
			readBufferRead = true;
		} 
	 
		BL_ASSERT(readBuffer.isEmpty() == false); 

		switch (readBinaryMethode)
		{
			case INTERPRET_STRING_AS_BINARY_DATA:
			{
				const int bytes = min(readBuffer.getByteSize(), byteCount);
				memCopy(destination, readBuffer.getPointer(), bytes);
				readBuffer.remove(0, bytes);
				return bytes;
			}

			case INTERPRET_STRING_AS_HEX_STRING:
			{
				const String s = readBuffer.subString(0, min(readBuffer.getLength(), byteCount*2));
				if (s.isHex() == true)
				{
					const int bytes = (s.getLength() + 1) / 2;
					s.hexToBinary(destination, false);
					if (echoStream != NULL) echoStream->writeBinary(destination, bytes);
					readBuffer.remove(0, s.getLength());
					return bytes;
				}
				else 
				{
					if (unreadWhenLexicalCastFailed == true && readBufferRead == true)
					{
						unread(readBuffer);
						readBuffer.setLength(0);
					}
					return 0;
				}
			}

			case INTERPRET_STRING_AS_BIN_STRING:
			{
				const String s = readBuffer.subString(0, min(readBuffer.getLength(), byteCount*8));
				if (isBinNumber(s.operator std::string()) == true)
				{
					const int bytes = binString2bin(s.operator std::string(), destination);
					if (echoStream != NULL) echoStream->writeBinary(destination, bytes);
					readBuffer.remove(0, s.getLength());
					return bytes;
				}
				else 
				{
					if (unreadWhenLexicalCastFailed == true && readBufferRead == true)
					{
						unread(readBuffer);
						readBuffer.setLength(0);
					}
					return 0;
				}
			}

			case INTERPRET_STRING_AS_BASE64_STRING:
			{
				BL_ASSERT_NEVER_REACHED
			}

			default:
				BL_ASSERT_NEVER_REACHED
				return 0;
		}
	}
	else // if (usesUnicode() == false)
	{
		BL_ASSERT_NEVER_REACHED ///
		return 0;
		/*
		if (readBuffer.length() == 0) 
		{ 
			if (read(readBufferW, timeoutSeconds) == false) return 0;
			readBufferRead = true;
		} 
	 
		BL_ASSERT(readBuffer.length() > 0); 

		switch (readBinaryMethode)
		{
			case INTERPRET_STRING_AS_BINARY_DATA:
			{
				const int bytes = min((int)readBuffer.length()*2, roundDownToEven(byteCount));
				memCopy(destination, readBuffer.c_str(), bytes);
				readBuffer.remove(0, bytes/2);
				return bytes;
			}

			case INTERPRET_STRING_AS_HEX_STRING:
			{
				const std::wstring s = readBufferW.subString(0, min((int)readBufferW.length(), byteCount*2));
				if (isHexNumber(s) == true)
				{
					const int bytes = hex2bin(s, destination);
					if (echoStream != NULL) echoStream->writeBinary(destination, bytes);
					readBufferW.remove(0, s.length());
					return bytes;
				}
				else 
				{
					if (unreadWhenLexicalCastFailed == true && readBufferRead == true)
					{
						unread(readBufferW);
						readBufferW.setLength(0);
					}
					return 0;
				}
			}

			case INTERPRET_STRING_AS_BIN_STRING:
			{
				const std::wstring s = readBufferW.subString(0, min((int)readBufferW.length(), byteCount*8));
				if (isBinNumber(s) == true)
				{
					const int bytes = binString2bin(s, destination);
					if (echoStream != NULL) echoStream->writeBinary(destination, bytes);
					readBufferW.remove(0, s.length());
					return bytes;
				}
				else 
				{
					if (unreadWhenLexicalCastFailed == true && readBufferRead == true)
					{
						unread(readBufferW);
						readBufferW.setLength(0);
					}
					return 0;
				}
			}

			default:
				BL_ASSERT_NEVER_REACHED
				return 0;
		}
		*/
	}
}



bool TextInputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
{
	BL_ASSERT_NEVER_REACHED

	BL_ASSERT(byteCount >= 0);
	BL_ASSERT(timeoutSeconds >= 0.0);

	int stringLength = byteCount;

	switch (readBinaryMethode)
	{
		case INTERPRET_STRING_AS_HEX_STRING:
			stringLength *= 2;
			break;

		case INTERPRET_STRING_AS_BIN_STRING:
			stringLength *= 8;
			break;
	}


	int readBufferRead = 0;
 
	const double endTime = Time::nowInSeconds() + timeoutSeconds;
	while (isInputAvailable() == false)
	{
		if (timeoutSeconds == 0.0) return false;
		timeoutSeconds = endTime - Time::nowInSeconds();
		if (timeoutSeconds < 0.0) return false;
		Thread::sleepSeconds(0.01);
	}

	if (shouldUseUnicode() == false)
	{
		if (readBuffer.getLength() < stringLength) 
		{ 
			String s;
			if (read(s, timeoutSeconds) == false) return false;
			readBuffer += s;
			readBufferRead += s.getLength();

			while (readBuffer.getLength() < stringLength && timeoutSeconds != 0.0)
			{
				Thread::sleepSeconds(0.01);
				timeoutSeconds = endTime - Time::nowInSeconds();
				if (timeoutSeconds < 0.0) return false;

				if (read(s, timeoutSeconds) == false) return false;
				readBuffer += s;
				readBufferRead += s.getLength();
			}
		} 

		BL_ASSERT(readBuffer.getLength() >= stringLength);

		switch (readBinaryMethode)
		{
			case INTERPRET_STRING_AS_BINARY_DATA:
			{
				memCopy(destination, readBuffer.getChar8Array(), byteCount); ///
				readBuffer.remove(0, byteCount);
				return true;
			}

			case INTERPRET_STRING_AS_HEX_STRING:
			{
				const String s = readBuffer.subString(0, stringLength);
				if (s.isHex() == true)
				{
					s.hexToBinary(destination);
					if (echoStream != NULL) echoStream->writeBinary(destination, byteCount);
					readBuffer.remove(0, stringLength);
				}
				else 
				{
					if (unreadWhenLexicalCastFailed == true && readBufferRead > 0)
					{
						unread(readBuffer.subString(readBuffer.getLength()-1 - readBufferRead));
						readBuffer.remove(readBuffer.getLength()-1 - readBufferRead);
					}
				}
				return true;
			}

			case INTERPRET_STRING_AS_BIN_STRING:
			{
				const String s = readBuffer.subString(0, stringLength);
				if (s.isBin() == true)
				{
					binString2bin(s.operator std::string(), destination);
					if (echoStream != NULL) echoStream->writeBinary(destination, byteCount);
					readBuffer.remove(0, stringLength);
				}
				else 
				{
					if (unreadWhenLexicalCastFailed == true && readBufferRead > 0)
					{
						unread(readBuffer.subString(readBuffer.getLength()-1 - readBufferRead));
						readBuffer.remove(readBuffer.getLength()-1 - readBufferRead);
					}
				}
				return true;
			}

			default:
				BL_ASSERT_NEVER_REACHED
				return false;
		}
	}
	else // if (usesUnicode() == false)
	{
		BL_ASSERT_NEVER_REACHED ///
		return false;

		/*
		if (readBinaryMethode == INTERPRET_STRING_AS_BINARY_DATA)
		{
			BL_ASSERT(isEven(byteCount));
			stringLength = (byteCount + 1) / 2;
		}

		if ((int)readBufferW.length() < stringLength) 
		{ 
			std::wstring s;
			if (read(s, timeoutSeconds) == false) return false;
			readBufferW += s;
			readBufferRead += s.length();

			while ((int)readBufferW.length() < stringLength)
			{
				Thread::sleepSeconds(0.01);
				timeoutSeconds = endTime - Time::nowInSeconds();
				if (timeoutSeconds < 0.0) return false;

				if (read(s, timeoutSeconds) == false) return false;
				readBufferW += s;
				readBufferRead += s.length();
			}
		} 

		BL_ASSERT((int)readBufferW.length() >= stringLength);

		switch (readBinaryMethode)
		{
			case INTERPRET_STRING_AS_BINARY_DATA:
			{
				memCopy(destination, readBufferW.c_str(), byteCount);
				readBufferW.remove(0, (byteCount + 1) / 2);
				return true;
			}

			case INTERPRET_STRING_AS_HEX_STRING:
			{
				const std::wstring s = readBufferW.subString(0, stringLength);
				if (isHexNumber(s) == true)
				{
					hex2bin(s, destination);
					if (echoStream != NULL) echoStream->writeBinary(destination, byteCount);
					readBufferW.remove(0, stringLength);
				}
				else 
				{
					if (unreadWhenLexicalCastFailed == true && readBufferRead > 0)
					{
						unread(readBufferW.subString(readBufferW.length()-1 - readBufferRead));
						readBufferW.remove(readBufferW.length()-1 - readBufferRead);
					}
				}
				return true;
			}

			case INTERPRET_STRING_AS_BIN_STRING:
			{
				const std::wstring s = readBufferW.subString(0, stringLength);
				if (isBinNumber(s) == true)
				{
					binString2bin(s, destination);
					if (echoStream != NULL) echoStream->writeBinary(destination, byteCount);
					readBufferW.remove(0, stringLength);
				}
				else 
				{
					if (unreadWhenLexicalCastFailed == true && readBufferRead > 0)
					{
						unread(readBufferW.subString(readBufferW.length()-1 - readBufferRead));
						readBufferW.remove(readBufferW.length()-1 - readBufferRead);
					}
				}
				return true;
			}

			default:
				BL_ASSERT_NEVER_REACHED
				return false;
		}
		*/
	}
}



template<typename T>
bool TextInputStream::readTemplate(T& destination, double timeoutSeconds) const
{
	//BL_ASSERT(timeoutSeconds >= 0.0);
	//String s(shouldUseUnicode() == true ? CHAR16_ENCODING : CHAR8_ENCODING);
	//if (readBuffer.isEmpty() == true)
	//{
	//	if (read(s, timeoutSeconds) == false) return false;
	//}
	//else
	//{
	//	s.swap(readBuffer);
	//}

	//BL_ASSERT(s.isEmpty() == false && readBuffer.isEmpty() == true);

	//if (s.tryParse(destination) == true)
	//{
	//	destination = d;
	//	if (echoStream != NULL) echoStream->write(destination);
	//	return true;
	//}
	//else
	//{
	//	if (unreadWhenLexicalCastFailed == true) readBuffer = s;
	//	return false;
	//}

	BL_ASSERT_NEVER_REACHED
	return false;
}

bool TextInputStream::read(void*& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(int8& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(uint8& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(int16& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(uint16& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(int32& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(uint32& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(int64& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(uint64& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(float& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(double& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}

bool TextInputStream::read(long double& destination, double timeoutSeconds) const
{
	return readTemplate(destination, timeoutSeconds);
}




bool TextInputStream::read(String& destination, double timeoutSeconds) const
{
	BL_ASSERT(timeoutSeconds >= 0.0);
	switch(readStringMethod)
	{
		case READ_STRING:
			return readString(destination, timeoutSeconds);

		case READ_TOKEN:
			return readToken(destination, timeoutSeconds);

		case READ_LINE:
			return readLine(destination, timeoutSeconds);

		case READ_SINGLE_CHAR:
		{
			if (shouldUseUnicode(destination) == true)
			{
				char16 c;
				bool result = readChar(c, timeoutSeconds);
				if (result == true)	destination = c;
				return result;
			}
			else
			{
				char8 c;
				bool result = readChar(c, timeoutSeconds);
				if (result == true)	destination = c;
				return result;
			}
		}

		case READ_STRING_WITH_LENGTH:
			return readStringWithLength(destination, timeoutSeconds);

		default:
			BL_ASSERT_NEVER_REACHED
			return false;
	}
}



bool TextInputStream::readString(String& destination, double timeoutSeconds) const
{
	BL_ASSERT(timeoutSeconds >= 0.0);
	BL_ASSERT(&destination != &readBuffer);

	if (readBuffer.isEmpty() == false)
	{
		destination = readBuffer;
		if (echoStream != NULL) echoStream->write(destination);
		readBuffer.setLength(0);
		return true;
	}
	else
	{
		BL_ASSERT(readBuffer.isEmpty() == true);

		if (connectedStream != NULL)
		{
			return InputStream::read(destination, timeoutSeconds);
		}
		else if (connectedTextBuffer != NULL)
		{
			connectedTextBuffer->setTimeoutForNextRead(timeoutSeconds);
			switch(readTextBufferMethode)
			{
				case READ_TEXT_BUFFER_LINE:
					readBuffer = connectedTextBuffer->readLine();
					break;

				case READ_TEXT_BUFFER_TOKEN:
					BL_ASSERT_NEVER_REACHED
					///readBuffer = connectedTextBuffer->readToken();
					break;

				case READ_TEXT_BUFFER_UNTIL_END:
					readBuffer = connectedTextBuffer->readAllFromCurrentPosition();
					break;

				case READ_TEXT_BUFFER_STRING_WITH_LENGTH:
					readBuffer = connectedTextBuffer->readFromCurrentPosition(destination.getLength());
					break;

				default:
					BL_ASSERT_NEVER_REACHED
					return false;
			}

			if (readBuffer.isEmpty() == false)
			{
				destination = readBuffer;
				if (echoStream != NULL) echoStream->write(destination);
				readBuffer.setLength(0);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}



template<typename C>
bool TextInputStream::readToken(String& destination, const String& tokenDelimiters, double timeoutSeconds) const
{
	BL_ASSERT(&destination != &readBuffer);
	const double endTime = Time::nowInSeconds() + timeoutSeconds;
	while (isInputAvailable() == false)
	{
		if (timeoutSeconds == 0.0) return false;
		timeoutSeconds = endTime - Time::nowInSeconds();
		if (timeoutSeconds < 0.0) return false;
		Thread::sleepSeconds(0.01);
	}

	C c;
	if (readChar(c, timeoutSeconds, false) == false) return false;
	if (timeoutSeconds != 0.0) timeoutSeconds = endTime - Time::nowInSeconds();
	bool isDelimiter = (tokenDelimiters.findFirst(c) != String::END);

	while (isDelimiter == true && timeoutSeconds >= 0.0) // read all delimiters before token:
	{
		if (readChar(c, timeoutSeconds, false) == false) return false;
		if (timeoutSeconds != 0.0) timeoutSeconds = endTime - Time::nowInSeconds();
		isDelimiter = (tokenDelimiters.findFirst(c) != String::END);
	}

	if (isDelimiter == true) return false;
	destination.setLength(0);

	do // read token:
	{
		destination += c;
		if (readChar(c, timeoutSeconds, false) == false) break;
		if (timeoutSeconds != 0.0) timeoutSeconds = endTime - Time::nowInSeconds();
		isDelimiter = (tokenDelimiters.findFirst(c) != String::END);
	}
	while (isDelimiter == false && timeoutSeconds >= 0.0);

	if (isDelimiter == false) destination += c;
	if (echoStream != NULL) echoStream->write(destination);
	return true;
}



bool TextInputStream::readToken(String& destination, const String& tokenDelimiters, double timeoutSeconds) const
{
	if (shouldUseUnicode(destination) == true)
	{
		return readToken<char16>(destination, tokenDelimiters, timeoutSeconds);
	}
	else
	{
		return readToken<char8>(destination, tokenDelimiters, timeoutSeconds);
	}
}



template<typename C>
bool TextInputStream::readLine(String& destination, double timeoutSeconds) const
{
	BL_ASSERT(&destination != &readBuffer);

	if (lineEndChars.isEmpty() == true)
	{
		stateError(NO_LINE_END_CHARS_DEFINED);
		return false;
	}

	const double endTime = Time::nowInSeconds() + timeoutSeconds;

	while (isInputAvailable() == false)
	{
		if (timeoutSeconds == 0.0) return false;
		timeoutSeconds = endTime - Time::nowInSeconds();
		if (timeoutSeconds < 0.0) return false;
		Thread::sleepSeconds(0.01);
	}

	C c;
	if (readChar(c, timeoutSeconds, false) == false) return false;
	String s(c);
	if (timeoutSeconds != 0.0)	timeoutSeconds = endTime - Time::nowInSeconds();
	int lineEndChar = lineEndChars.findFirst(c);

	while (lineEndChar == String::END)
	{
		if (timeoutSeconds < 0.0)
		{
			unread(s);
			return false;
		}
		if (readChar(c, timeoutSeconds, false) == false)
		{
			destination = s;
			return true; // If no input available, we have reached end of buffer and are happy
		}
		s += c;
		if (timeoutSeconds != 0.0)	timeoutSeconds = endTime - Time::nowInSeconds();
		lineEndChar = lineEndChars.findFirst(c);
	}

	BL_ASSERT(lineEndChar != String::END);
	s.setLength(s.getLength()-1);
	String foundLineEndChars(c);
	String availableLineEndChars = lineEndChars;

	do
	{
		availableLineEndChars.remove(lineEndChar, 1);
		if (availableLineEndChars.isEmpty() == true)
		{
			destination = s;
			return true;
		}

		if (timeoutSeconds < 0.0 || readChar(c, timeoutSeconds, false) == false)
		{
			unread(s+foundLineEndChars);
			return false;
		}
		foundLineEndChars += c;
		if (timeoutSeconds != 0.0)	timeoutSeconds = endTime - Time::nowInSeconds();
		lineEndChar = availableLineEndChars.findFirst(c);
	}
	while (lineEndChar != String::END);

	BL_ASSERT(lineEndChar == String::END);
	unread(String(c));
	destination = s;
	if (echoStream != NULL) echoStream->write(destination);
	return true;
}



bool TextInputStream::readLine(String& destination, double timeoutSeconds) const
{
	if (shouldUseUnicode(destination) == true)
	{
		return readLine<char16>(destination, timeoutSeconds);
	}
	else
	{
		return readLine<char8>(destination, timeoutSeconds);
	}
}



template<typename C>
bool TextInputStream::readChar(C& destination, double timeoutSeconds, bool echo) const
{
	if (readBuffer.isEmpty() == true)
	{
		if (connectedStream != NULL)
		{
			connectedStream->read(readBuffer, timeoutSeconds);
		}
		else if (connectedTextBuffer != NULL)
		{
			connectedTextBuffer->setTimeoutForNextRead(timeoutSeconds);
			readBuffer = connectedTextBuffer->readFromCurrentPosition(1);
		}
	}

	if (readBuffer.isEmpty() == false)
	{
		destination = readBuffer[0];
		if (echo == true && echoStream != NULL)
		{
			echoStream->write(readBuffer.subString(0, 1));
		}
		readBuffer.remove(0);
		return true;
	}
	else
	{
		return false;
	}
}



bool TextInputStream::readChar(char8& destination, double timeoutSeconds) const
{
	return readChar(destination, timeoutSeconds, true);
}



bool TextInputStream::readChar(char16& destination, double timeoutSeconds) const
{
	return readChar(destination, timeoutSeconds, true);
}



template<typename C>
bool TextInputStream::readStringWithLength(String& destination, double timeoutSeconds) const
{
	BL_ASSERT(&destination != &readBuffer);

	if (destination.isEmpty() == true) return true;

	const double endTime = Time::nowInSeconds() + timeoutSeconds;
	while (isInputAvailable() == false)
	{
		if (timeoutSeconds == 0.0) return false;
		timeoutSeconds = endTime - Time::nowInSeconds();
		if (timeoutSeconds < 0.0) return false;
		Thread::sleepSeconds(0.01);
	}

	const int length = destination.getLength();

	C c;
	String s(destination.getImplementation()->clone());

	do
	{
		if (readChar(c, timeoutSeconds, false) == false) break;
		s += c;
		if (timeoutSeconds != 0.0)	timeoutSeconds = endTime - Time::nowInSeconds();
	}
	while (readBuffer.getLength() < length);

	if (s.isEmpty() == true) return false;

	destination = s;
	if (echoStream != NULL) echoStream->write(destination);
	return true;
}



bool TextInputStream::readStringWithLength(String& destination, double timeoutSeconds) const
{
	if (shouldUseUnicode(destination) == true)
	{
		return readStringWithLength<char16>(destination, timeoutSeconds);
	}
	else
	{
		return readStringWithLength<char8>(destination, timeoutSeconds);
	}
}


void TextInputStream::unreadBinary(const void* source, int byteCount) const
{
	if (shouldUseUnicode() == false)
	{
		switch(readBinaryMethode)
		{
			case INTERPRET_STRING_AS_BINARY_DATA:
				unread(String(static_cast<const char8 *>(source), byteCount));
				return;

			case INTERPRET_STRING_AS_HEX_STRING:
				unread(bin2hex(source, byteCount));
				return;

			case INTERPRET_STRING_AS_BIN_STRING:
				unread(bin2binString(source, byteCount));
				return;
		}
	}
	else
	{
	BL_ASSERT_NEVER_REACHED ///
		/*
		switch(readBinaryMethode)
		{
			case INTERPRET_STRING_AS_BINARY_DATA:
				unread(std::wstring(static_cast<const char16 *>(source), byteCount/2));
				return;

			case INTERPRET_STRING_AS_HEX_STRING:
				unread(bin2hexW(source, byteCount));
				return;

			case INTERPRET_STRING_AS_BIN_STRING:
				unread(bin2binStringW(source, byteCount));
				return;
		}
		*/
	}

	BL_ASSERT_NEVER_REACHED
}



template<typename T>
void TextInputStream::unreadTemplate(T source) const
{
	unread(String::createFrom(source));
}



void TextInputStream::unread(bool source) const
{
	unreadTemplate(source);
}

void TextInputStream::unread(const void* source) const
{
	unreadTemplate(source);
}

void TextInputStream::unread(int8 source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(uint8 source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(int16 source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(uint16 source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(int32 source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(uint32 source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(int64 source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(uint64 source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(float source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(double source) const 
{
	unreadTemplate(source);
}

void TextInputStream::unread(long double source) const 
{
	unreadTemplate(source);
}




void TextInputStream::unread(const String& source) const
{
	BL_ASSERT(&source != &readBuffer);
	readBuffer.insert(source);
}



void TextInputStream::unreadReadBuffer() const
{
	if (connectedStream != NULL)
	{
		connectedStream->unread(readBuffer);
		readBuffer.setLength(0);
	}
	else if (connectedTextBuffer != NULL)
	{
		connectedTextBuffer->writeBeforeCurrentPosition(readBuffer);
		readBuffer.setLength(0);
	}
	else
	{
		stateError(NO_STREAM_OR_BUFFER_CONNECTED_FOR_UNREAD);
	}
}



void TextInputStream::connectToStream(const InputStream& newInputStream)
{
	if (connectedTextBuffer != NULL) disconnectFromTextBuffer();
	InputStream::connectToStream(newInputStream);
}



void TextInputStream::connectToTextBuffer(AbstractTextBuffer& newBuffer)
{
	if (connectedStream != NULL) disconnectFromStream();
	connectedTextBuffer = &newBuffer;
}



void TextInputStream::disconnectFromTextBuffer()
{
	if (ownerOfConnectedObjects == true)
	{
		delete connectedTextBuffer;
	}
	connectedTextBuffer = NULL;
}



bool TextInputStream::isConnected() const
{
	return (connectedTextBuffer != NULL || InputStream::isConnected() == true);
}



void TextInputStream::setReadTextBufferMethode(ReadTextBufferMethode newReadTextBufferMethode)
{
	readTextBufferMethode = newReadTextBufferMethode;
}



bool TextInputStream::isInputAvailable() const
{
	bool result = readBuffer.isEmpty() == false;

	if (result == false)
	{
		result = InputStream::isInputAvailable();
	}

	if (result == false && connectedTextBuffer != NULL)
	{
		result = connectedTextBuffer->readFromCurrentPositionPossible();
	}

	return result;
}



} // namespace Streams
} // namespace BaseLib
