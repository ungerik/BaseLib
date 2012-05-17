/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_AbstractTextBuffer_h
#define BaseLib_Buffers_AbstractTextBuffer_h



#include "BaseLib/Strings/String.h"
#include "BaseLib/Streams/TextInputStream.h"
#include "BaseLib/Streams/TextOutputStream.h"




namespace BaseLib {
namespace Streams { class TextInputStream; }
namespace Streams { class TextOutputStream; }
namespace Buffers {


using BaseLib::Streams::TextInputStream;
using BaseLib::Streams::TextOutputStream;

//class BaseLib::Streams::TextInputStream;
//class BaseLib::Streams::TextOutputStream;



using namespace BaseLib::Strings;



class AbstractBinaryBuffer;


/**
Not implemented yet.
*/
class BL_EXPORT AbstractTextBuffer {
public:

	virtual ~AbstractTextBuffer();

	virtual void close() = 0;

	inline bool isEmpty() const
	{
		return getLength() == 0;
	}

	virtual int getLength() const = 0;
	virtual void setLength(int newLength) = 0;

	virtual String& asString() = 0;
	virtual const String& asString() const = 0;

	virtual StringEncoding getStringEncoding() const = 0;
	virtual void setStringEncoding(StringEncoding newStringEncoding) = 0;

	virtual bool isReadable() const;
	virtual bool isWriteable() const;

	// String assign and conversion operators:
	virtual AbstractTextBuffer& assign(const AbstractTextBuffer& right) = 0;
	virtual AbstractTextBuffer& assign(const void* binaryData, int lengthInChars, bool unicode = false) = 0;
	virtual AbstractTextBuffer& assign(const AbstractBinaryBuffer* binaryBuffer) = 0;

	// Line functions:
	inline const String& getLineEndChars() const
	{
		return lineEndChars;
	}

	virtual void setLineEndChars(const String& newLineEndChars, bool reparseTextForLineEnds = false) = 0;
	virtual void changeLineEndChars(const String& newLineEndChars) = 0;

	virtual int getLineCount() const = 0;
	virtual void setLineCount(int newLineCount) = 0;

	virtual String getLine(int lineNumber) const = 0;

	virtual void setLine(int lineNumber, const String& lineText) = 0;

	virtual void removeLine(int lineNumber) = 0;
	virtual void insertLine(int lineNumber, const String& lineText) = 0;
	virtual void addLine(const String& lineText) = 0;

	// Position read/write functions:
	inline int getCurrentPosition()	{ return currentPosition; }
	virtual void setCurrentPosition(int newCurrentPosition) = 0;
	inline void moveCurrentPosition(int charCount) { setCurrentPosition(getCurrentPosition() + charCount);	}

	virtual bool readFromCurrentPositionPossible() const = 0;

	virtual String readLine(bool moveCurrentPos = true) = 0;

	virtual String readFromPosition(int position, int charCount) const = 0;
	virtual String readAllFromPosition(int position) const = 0;

	inline String readFromCurrentPosition(int charCount, bool moveCurrentPos = true)
	{
		String result = readFromPosition(currentPosition, charCount);
		const int length = result.getLength();
		if (length > 0 && moveCurrentPos == true) moveCurrentPosition(charCount >= 0 ? length : -length);
		return result;
	}

	inline String readAllFromCurrentPosition(bool moveCurrentPos = true)
	{
		String result = readAllFromPosition(currentPosition);
		const int length = result.getLength();
		if (length > 0 && moveCurrentPos == true) moveCurrentPosition(length);
		return result;
	}

	virtual void writeAtPosition(int position, const String& source) = 0;

	inline void writeAtCurrentPosition(const String& source, bool moveCurrentPos = true)
	{
		writeAtPosition(currentPosition, source);
		if (moveCurrentPos == true) moveCurrentPosition(source.getLength());
	}

	virtual void writeBeforePosition(int position, const String& source) = 0;

	inline void writeBeforeCurrentPosition(const String& source, bool moveCurrentPos = true)
	{
		writeBeforePosition(currentPosition, source);
		if (moveCurrentPos == true) moveCurrentPosition(-source.getLength());
	}

	/**
	insert.
	Kann vor und hinter die Puffergrenze schreiben, und somit die Puffergrösse verändern:
	*/
	virtual void insertAtPosition(int position, const String& source) = 0;

	inline void insertAtCurrentPosition(const String& source, bool moveCurrentPos = true)
	{
		insertAtPosition(currentPosition, source);
		if (moveCurrentPos == true) moveCurrentPosition(source.getLength());
	}


	virtual void removeAtPosition(int position, int charCount) = 0;
	inline void removeAtCurrentPosition(int charCount, bool moveCurrentPos = true)
	{
		removeAtPosition(currentPosition, charCount);
		if (moveCurrentPos == true && charCount < 0) moveCurrentPosition(charCount);
	}

	// Timeout functions:
	virtual double getTimeoutForNextRead() const { return 0.0; }
	virtual void setTimeoutForNextRead(double newReadTimeoutSeconds) {}

	virtual void flush();

	inline void invalidateLineEnds()
	{
		validLineEnds = false;
	}

	inline void validateLineEnds() const
	{
		if (validLineEnds == false) updateLineEnds();
	}

	virtual void updateLineEnds() const = 0;

protected:

	AbstractTextBuffer();

	int currentPosition;
	String lineEndChars;
	mutable bool validLineEnds;
};



inline TextInputStream& operator >>(TextInputStream& inputStream, AbstractTextBuffer& destination)
{
	String input;
	inputStream >> input;
	destination.writeAtCurrentPosition(input);
	return inputStream;
}



inline TextOutputStream& operator <<(TextOutputStream& outputStream, const AbstractTextBuffer& source)
{
	outputStream << source.asString();
	return outputStream;
}



} // namespace Buffers
} // namespace BaseLib



#endif // #ifndef BaseLib_Buffers_AbstractTextBuffer_h
