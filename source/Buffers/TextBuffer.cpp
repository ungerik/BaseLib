/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Buffers/TextBuffer.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Buffers {



using namespace BaseLib::ErrorHandling;



class StringImplementationWrapper : public AbstractStringImplementation {
public:

	StringImplementationWrapper(AbstractStringImplementation* implementationToWrap)
	  : wrappedImplementation(implementationToWrap)
	  , textBuffer(NULL)
	{
	}

	virtual ~StringImplementationWrapper()
	{
		delete wrappedImplementation;
	}
	
	virtual AbstractStringImplementation* clone(int position, int length) const
	{
		if (textBuffer->checkReadPermission() == false) return NULL;
		return wrappedImplementation->clone(position, length);
	}

	virtual StringEncoding getEncoding() const
	{
		return wrappedImplementation->getEncoding();
	}

	virtual void setStringEncoding(StringEncoding newStringEncoding)
	{
		BL_ASSERT_NEVER_REACHED
		///...
	}

	virtual int getByteSize() const
	{
		return wrappedImplementation->getByteSize();
	}

	virtual int getCharacterByteSize() const
	{
		return wrappedImplementation->getCharacterByteSize();
	}

	virtual int getLength() const
	{
		return wrappedImplementation->getLength();
	}

	virtual void setLength(int newLength)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->setLength(newLength);
	}

	virtual void insert(int position, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->insert(position, length);
	}

	virtual void remove(int position, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->remove(position, length);
	}

	virtual char8 getChar8(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getChar8(position);
	}

	virtual char8 getLowerCaseChar8(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getLowerCaseChar8(position);
	}

	virtual char8 getUpperCaseChar8(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getUpperCaseChar8(position);
	}

	virtual void setChar(int position, char8 newChar)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->setChar(position, newChar);
	}

	virtual char16 getChar16(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getChar16(position);
	}

	virtual char16 getLowerCaseChar16(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getLowerCaseChar16(position);
	}

	virtual char16 getUpperCaseChar16(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getUpperCaseChar16(position);
	}

	virtual void setChar(int position, char16 newChar)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->setChar(position, newChar);
	}

	virtual char32 getChar32(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getChar32(position);
	}

	virtual char32 getLowerCaseChar32(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getLowerCaseChar32(position);
	}

	virtual char32 getUpperCaseChar32(int position) const
	{
		if (textBuffer->checkReadPermission() == false) return 0;
		return wrappedImplementation->getUpperCaseChar32(position);
	}

	virtual void setChar(int position, char32 newChar)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->setChar(position, newChar);
	}

	virtual void fill(char8 fillerChar, int position, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->fill(fillerChar, position, length);
	}

	virtual void fill(char16 fillerChar, int position, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->fill(fillerChar, position, length);
	}

	virtual void lowerCase(int position, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->lowerCase(position, length);
	}

	virtual void upperCase(int position, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->lowerCase(position, length);
	}

	virtual void copyFromStringImplementation(const AbstractStringImplementation* source, int sourcePosition, int destPosition, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->copyFromStringImplementation(source, sourcePosition, destPosition, length);
	}

	virtual void copyFromCharArray(const char8 * source, int destStartPosition, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->copyFromCharArray(source, destStartPosition, length);
	}

	virtual void copyToCharArray(char8 * destination, int sourceStartPosition, int length) const
	{
		if (textBuffer->checkReadPermission() == false) return;
		wrappedImplementation->copyToCharArray(destination, sourceStartPosition, length);
	}

	virtual void copyFromCharArray(const char16 * source, int destStartPosition, int length)
	{
		if (textBuffer->checkBufferStringWritePermission() == false) return;
		wrappedImplementation->copyFromCharArray(source, destStartPosition, length);
	}

	virtual void copyToCharArray(char16 * destination, int sourceStartPosition, int length) const
	{
		if (textBuffer->checkReadPermission() == false) return;
		wrappedImplementation->copyToCharArray(destination, sourceStartPosition, length);
	}

	virtual const void* getPointer() const
	{
		if (textBuffer->checkReadPermission() == false) return NULL;
		return wrappedImplementation->getPointer();
	}

	virtual const char8 * getChar8Array() const
	{
		if (textBuffer->checkReadPermission() == false) return NULL;
		return wrappedImplementation->getChar8Array();
	}

	virtual const char16 * getChar16Array() const
	{
		if (textBuffer->checkReadPermission() == false) return NULL;
		return wrappedImplementation->getChar16Array();
	}

	virtual const char8 * getChar8CString() const
	{
		if (textBuffer->checkReadPermission() == false) return NULL;
		return wrappedImplementation->getChar8CString();
	}

	virtual const char16 * getChar16CString() const
	{
		if (textBuffer->checkReadPermission() == false) return NULL;
		return wrappedImplementation->getChar16CString();
	}

	virtual int hash(int position, int length) const
	{
		return wrappedImplementation->hash(position, length);
	}

	inline AbstractStringImplementation* getWrappedImplementation()
	{
		return wrappedImplementation;
	}

	inline void setWrappedImplementation(AbstractStringImplementation* newWrappedImplementation, bool deleteOldImplementation = true)
	{
		BL_ASSERT(newWrappedImplementation != NULL);
		if (deleteOldImplementation == true) delete wrappedImplementation;
		wrappedImplementation = newWrappedImplementation;
		textBuffer->invalidateLineEnds();
	}

	inline void setTextBuffer(TextBuffer* newTextBuffer)
	{
		BL_ASSERT(newTextBuffer != NULL);
		textBuffer = newTextBuffer;
	}

private:

	mutable AbstractStringImplementation* wrappedImplementation;
	mutable TextBuffer* textBuffer;

};



///////////////////////////////////////////////////////////////////////////////


TextBuffer::BufferString::BufferString()
  : String(new StringImplementationWrapper(AbstractStringImplementation::create()))
{
}



TextBuffer::BufferString::BufferString(const String& text)
  : String(new StringImplementationWrapper(AbstractStringImplementation::create(text.getLength())))
{
	static_cast<StringImplementationWrapper*>(implementation)->getWrappedImplementation()->copyFromStringImplementation(text.getImplementation(), 0, 0, text.getLength());
}


void TextBuffer::BufferString::setImplementation(AbstractStringImplementation* newImplementation, bool deleteOldImplementation)
{
	static_cast<StringImplementationWrapper*>(implementation)->setWrappedImplementation(newImplementation, deleteOldImplementation);
}



TextBuffer::TextBuffer()
  : AbstractTextBuffer()
  , lineInfoTable()
  , bufferString()
{
	static_cast<StringImplementationWrapper*>(bufferString.getImplementation())->setTextBuffer(this);
}



TextBuffer::TextBuffer(const String& text)
  : AbstractTextBuffer()
  , lineInfoTable()
  , bufferString(text)
{
	static_cast<StringImplementationWrapper*>(bufferString.getImplementation())->setTextBuffer(this);
}



void TextBuffer::close()
{
}



int TextBuffer::getLength() const
{
	return bufferString.getLength();
}



void TextBuffer::setLength(int newLength)
{
	if (checkWritePermission() == false) return;

	bufferString.setLength(newLength);
}



String& TextBuffer::asString()
{
	return bufferString;
}



const String& TextBuffer::asString() const
{
	return bufferString;
}



StringEncoding TextBuffer::getStringEncoding() const
{
	return bufferString.getEncoding();
}



void TextBuffer::setStringEncoding(StringEncoding newStringEncoding)
{
	if (checkWritePermission() == false) return;

	if (newStringEncoding != getStringEncoding())
	{
		int length = bufferString.getLength();
		///...
/*
		StringImplementationWrapper* bufferStringImplementationWrapper = static_cast<StringImplementationWrapper*>(bufferString.getImplementation());
		AbstractStringImplementation* newImplementation = (shouldUseUnicode == true) ?
			AbstractStringImplementation::createWide(length)
		:
			AbstractStringImplementation::createNarrow(length);

		newImplementation->copyFromStringImplementation(bufferStringImplementationWrapper, 0, 0, length);

		bufferStringImplementationWrapper->setWrappedImplementation(newImplementation);
		*/
	}
}


AbstractTextBuffer& TextBuffer::assign(const AbstractTextBuffer& right)
{
	if (checkWritePermission() == false) *this;

	if (&right != this)
	{
		static_cast<String>(bufferString) = right.asString();
	}
	return *this;
}



AbstractTextBuffer& TextBuffer::assign(const void* binaryData, int lengthInChars, bool unicode)
{
	if (checkWritePermission() == false) *this;

	bufferString.setLength(lengthInChars);
	if (unicode == true)
	{
		bufferString.copyFromCharArray(static_cast<const char16 *>(binaryData), 0, lengthInChars);
	}
	else
	{
		bufferString.copyFromCharArray(static_cast<const char8 *>(binaryData), 0, lengthInChars);
	}
	return *this;
}



AbstractTextBuffer& TextBuffer::assign(const AbstractBinaryBuffer* binaryBuffer)
{
	if (checkWritePermission() == false) *this;

	BL_ASSERT(binaryBuffer != NULL);

	bool unicode = false; ///usesUnicode(); //FIX! binaryBuffer->usesUnicode();
	if (unicode == true)
	{
		const int length = binaryBuffer->getSizeAsInt() / sizeof(char16);
		bufferString.setLength(length);

		const int bufferSize = 4096;
		const int bufferLength = bufferSize / sizeof(char16);
		char16 buffer[bufferLength];
		
		int bytePosition = 0;
		int charPosition = 0;
		for (int i = 0; i < bufferLength / length; ++i)
		{
			binaryBuffer->readFromPosition(bytePosition, buffer, bufferSize);
			bytePosition += bufferSize;

			bufferString.copyFromCharArray(buffer, charPosition, bufferLength);
			charPosition += bufferLength;
		}

		const int restBufferLength = bufferLength % length;
		const int restBufferSize = bufferLength * sizeof(char16);

		binaryBuffer->readFromPosition(bytePosition, buffer, restBufferSize);
		bufferString.copyFromCharArray(buffer, charPosition, restBufferLength);
	}
	else
	{
		const int length = binaryBuffer->getSizeAsInt() / sizeof(char8);
		bufferString.setLength(length);

		const int bufferSize = 4096;
		const int bufferLength = bufferSize / sizeof(char8);
		char8 buffer[bufferLength];
		
		int bytePosition = 0;
		int charPosition = 0;
		int read = 0;

		while (bytePosition < length)
		{
			read = binaryBuffer->readFromPosition(bytePosition, buffer, bufferSize);

			if (read == 0)
				break;

			bytePosition += read;

			bufferString.copyFromCharArray(buffer, charPosition, read /* * factor */);
			charPosition += read /* * factor */;
		}

/*		for (int i = 0; i < bufferLength / length; ++i)
		{
			binaryBuffer->readFromPosition(bytePosition, buffer, bufferSize);
			bytePosition += bufferSize;

			bufferString.copyFromCharArray(buffer, charPosition, bufferLength);
			charPosition += bufferLength;
		}

		const int restBufferLength = bufferLength % length;
		const int restBufferSize = bufferLength * sizeof(char8);

		binaryBuffer->readFromPosition(bytePosition, buffer, restBufferSize);
		bufferString.copyFromCharArray(buffer, charPosition, restBufferLength);
*/	}

	return *this;
}



void TextBuffer::setLineEndChars(const String& newLineEndChars, bool invalidateCurrentLineEnds)
{
	if (checkWritePermission() == false) return;

	BL_ASSERT(newLineEndChars.isEmpty() == false && newLineEndChars.getLength() <= 2);

	if (newLineEndChars != lineEndChars)
	{
		lineEndChars = newLineEndChars;

		if (invalidateCurrentLineEnds == true) invalidateLineEnds();
	}
}



void TextBuffer::changeLineEndChars(const String& newLineEndChars)
{
	if (checkWritePermission() == false) return;

	if (newLineEndChars != lineEndChars)
	{
		bufferString.searchAndReplace(lineEndChars, newLineEndChars);
		setLineEndChars(newLineEndChars, newLineEndChars.getLength() != lineEndChars.getLength());
	}
}



int TextBuffer::getLineCount() const
{
	if (checkReadPermission() == false) return 0;

	validateLineEnds();
	return lineInfoTable.getCount();
}



void TextBuffer::setLineCount(int newLineCount)
{
	if (checkWritePermission() == false) return;

	BL_ASSERT(newLineCount >= 0);
	const bool valid = validLineEnds;
	const int lineCount = lineInfoTable.getCount();
	if (newLineCount < lineCount)
	{
		bufferString.setLength(lineInfoTable[newLineCount-1].startPosition + lineInfoTable[newLineCount-1].lineLength);
		lineInfoTable.setCount(newLineCount);
	}
	else if (newLineCount > lineCount)
	{
		bufferString.append(lineEndChars, newLineCount - lineCount);
		lineInfoTable.setCapacity(newLineCount);
		const int lineEndCharCount = lineEndChars.getLength();
		for (int i = lineCount; i < newLineCount; ++i)
		{
			LineInfo& lastLine = lineInfoTable[i-1];
			lineInfoTable.append(LineInfo(lastLine.startPosition + lastLine.lineLength + lineEndCharCount, 0)); 
		}
	}
	if (valid == true) validLineEnds = true;
}



String TextBuffer::getLine(int lineNumber) const
{
	if (checkReadPermission() == false ||
		(bufferString.isEmpty() == true && lineNumber == 0))
	{
		if (bufferString.isEmpty() == true && lineNumber == 0) BL_ASSERT(lineInfoTable.isEmpty() == true);
		return bufferString.subString(0, 0);
	}

	validateLineEnds();

	if (lineNumber < 0 || lineNumber >= lineInfoTable.getCount())
	{
		argumentError(LINE_OUT_OF_RANGE(lineNumber, lineInfoTable.getCount()));
		return bufferString.subString(0, 0);
	}

	return bufferString.subString(lineInfoTable[lineNumber].startPosition, lineInfoTable[lineNumber].lineLength);
}



void TextBuffer::setLine(int lineNumber, const String& lineText)
{
	if (checkWritePermission() == false) return;

	validateLineEnds();

	if (bufferString.isEmpty() == true && lineNumber == 0)
	{
		BL_ASSERT(lineInfoTable.isEmpty() == true);
		lineInfoTable.append(LineInfo(0, 0));
	}

	if (lineNumber < 0 || lineNumber >= lineInfoTable.getCount())
	{
		argumentError(LINE_OUT_OF_RANGE(lineNumber, lineInfoTable.getCount()));
		return;
	}

	int lineCount = getLineCount();
	BL_ASSERT(lineNumber >= 0 && lineNumber < lineCount);

	const int newLength = lineText.getLength();
	const int oldLength = lineInfoTable[lineNumber].lineLength;
	const int position = lineInfoTable[lineNumber].startPosition;	

	bufferString.replace(position, oldLength, lineText);

	if (newLength < oldLength)
	{
		const int deltaLength = oldLength - newLength;
		for (int i = lineNumber+1; i < lineCount; ++i)
		{
			lineInfoTable[i].startPosition -= deltaLength;
		}
	}
	else if (newLength > oldLength)
	{
		const int deltaLength = newLength - oldLength;
		for (int i = lineNumber+1; i < lineCount; ++i)
		{
			lineInfoTable[i].startPosition += deltaLength;
		}
	}

	validLineEnds = true;
}



void TextBuffer::removeLine(int lineNumber)
{
	if (checkWritePermission() == false) return;

	validateLineEnds();

	if (bufferString.isEmpty() == true && lineNumber == 0)
	{
		BL_ASSERT(lineInfoTable.isEmpty() == true);
		return;
	}

	if (lineNumber < 0 || lineNumber >= lineInfoTable.getCount())
	{
		argumentError(LINE_OUT_OF_RANGE(lineNumber, lineInfoTable.getCount()));
		return;
	}

	int lineCount = getLineCount();
	BL_ASSERT(lineNumber >= 0 && lineNumber < lineCount);

	const int lineLength = lineInfoTable[lineNumber].lineLength;
	bufferString.remove(lineInfoTable[lineNumber].startPosition, lineLength);

	for (int i = lineNumber+1; i < lineCount; ++i)
	{
		lineInfoTable[i-1].startPosition = lineInfoTable[i].startPosition - lineLength;
		lineInfoTable[i-1].lineLength = lineInfoTable[i].lineLength;
	}
	lineInfoTable.setCount(lineCount-1);

	validLineEnds = true;
}



void TextBuffer::insertLine(int lineNumber, const String& lineText)
{
	if (checkWritePermission() == false) return;

	validateLineEnds();

	if (lineNumber < 0 || lineNumber > lineInfoTable.getCount())
	{
		argumentError(LINE_OUT_OF_RANGE(lineNumber, lineInfoTable.getCount()+1));
		return;
	}

	const int lineTextLength = lineText.getLength();
	const int lineEndCharsCount = lineEndChars.getLength();
	const int insertLength = lineTextLength + lineEndCharsCount;

	if (lineNumber == lineInfoTable.getCount())
	{
		lineInfoTable.append(LineInfo(0, lineTextLength));

		bufferString.insert(0, insertLength);
		bufferString.copyFromString(lineText, 0, 0, lineTextLength);
		bufferString.copyFromString(lineEndChars, 0, lineTextLength, lineEndCharsCount);
	}
	else
	{
		int lineCount = getLineCount();

		lineInfoTable.setCount(lineCount+1);
		for (int i = lineNumber+1; i <= lineCount; ++i)
		{
			lineInfoTable[i].startPosition = lineInfoTable[i-1].startPosition + insertLength;
			lineInfoTable[i].lineLength = lineInfoTable[i-1].lineLength;
		}
		lineInfoTable[lineNumber].lineLength = lineTextLength;

		const int position = lineInfoTable[lineNumber].startPosition;
		bufferString.insert(position, insertLength);
		bufferString.copyFromString(lineText, 0, position, lineTextLength);
		bufferString.copyFromString(lineEndChars, 0, position + lineTextLength, lineEndCharsCount);
	}

	validLineEnds = true;
}



void TextBuffer::addLine(const String& lineText)
{
	if (checkWritePermission() == false) return;

	bufferString += lineText + lineEndChars;
	if (validLineEnds == true)
	{
		const LineInfo& lastLine = lineInfoTable[getLineCount()-1];
		const int lineEndCharsCount = lineEndChars.getLength();
		lineInfoTable.append(LineInfo(lastLine.startPosition + lastLine.lineLength + lineEndCharsCount, lineEndCharsCount));
	}
}



void TextBuffer::setCurrentPosition(int newCurrentPosition)
{
	currentPosition = newCurrentPosition;
}



bool TextBuffer::readFromCurrentPositionPossible() const
{
	return isReadable() == true && currentPosition >= 0 && currentPosition < getLength();
}



String TextBuffer::readLine(bool moveCurrentPos)
{
	if (checkReadPermission() == false) return bufferString.subString(0, 0);

	const int length = getLength();
	if (currentPosition < 0 || currentPosition >= length) return bufferString.subString(0, 0);

	const int lineStartPos = currentPosition;
	int lineEndPos = bufferString.findFirstOf(lineEndChars, lineStartPos);
	if (lineEndPos == String::END) lineEndPos = length;
	int lineLength = lineEndPos - lineStartPos;

	if (moveCurrentPos == true)
	{
		currentPosition += lineLength + 1;
		if (lineEndPos+1 < length && lineEndChars.getLength() > 1)
		{
			char16 firstEolChar = bufferString[lineEndPos];
			if (bufferString[lineEndPos+1] != firstEolChar) ++currentPosition;
		}
	}

	return bufferString.subString(currentPosition, lineLength);
}



String TextBuffer::readFromPosition(int position, int charCount) const
{
	if (checkReadPermission() == false) return bufferString.subString(0, 0);

	return bufferString.subString(position, charCount);
}



String TextBuffer::readAllFromPosition(int position) const
{
	if (checkReadPermission() == false) return bufferString.subString(0, 0);

	return bufferString.subString(position);
}



void TextBuffer::writeAtPosition(int position, const String& source)
{
	if (checkWritePermission() == false) return;

	const int sourceLength = source.getLength();
	const int neededLength = position + sourceLength;
	if (neededLength > sourceLength) bufferString.setLength(neededLength);
	bufferString.copyFromString(source, 0, position, sourceLength);
}



void TextBuffer::writeBeforePosition(int position, const String& source)
{
	writeAtPosition(position - source.getLength(), source);
}



void TextBuffer::insertAtPosition(int position, const String& source)
{
	if (checkWritePermission() == false) return;

	bufferString.insert(source, position);
}



void TextBuffer::removeAtPosition(int position, int charCount)
{
	if (checkWritePermission() == false) return;

	bufferString.remove(position, charCount);
}



void TextBuffer::updateLineEnds() const
{
	lineInfoTable.setCount(0);

	const int length = bufferString.getLength();
	if (length > 0)
	{
		int lastStart = 0;
		int position = 0;

		while ((position = bufferString.findFirstOf(lineEndChars, position)) != String::END)
		{
			lineInfoTable.append(LineInfo(lastStart, position - lastStart));
			char16 firstEolChar = bufferString[position];
			++position;
			if (position < length && bufferString[position] != firstEolChar) ++position;
			lastStart = position;
		}

		int lastLineLength = length - lastStart;
		if (lastLineLength > 0)	lineInfoTable.append(LineInfo(lastStart, lastLineLength));
	}
}



bool TextBuffer::checkReadPermission() const
{
	bool permission = isReadable();
	if (permission == false) stateError(READ_NOT_ALLOWED);
	return permission;
}



bool TextBuffer::checkWritePermission()
{
	bool permission = isWriteable();
	if (permission == false) stateError(WRITE_NOT_ALLOWED);
	return permission;
}



} // namespace Buffers
} // namespace BaseLib



