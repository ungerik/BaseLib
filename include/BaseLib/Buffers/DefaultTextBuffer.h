/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_DefaultTextBuffer_h
#define BaseLib_Buffers_DefaultTextBuffer_h



#include "BaseLib/Buffers/AbstractTextBuffer.h"



namespace BaseLib {
namespace Buffers {




class BL_EXPORT DefaultTextBuffer : public AbstractTextBuffer {
public:

	virtual void close() {}

	virtual int getLength() const { BL_ASSERT_NEVER_REACHED return 0; }
	virtual void setLength(int newLength) { BL_ASSERT_NEVER_REACHED }

	virtual String& asString() { BL_ASSERT_NEVER_REACHED return bufferString; };
	virtual const String& asString() const { BL_ASSERT_NEVER_REACHED return bufferString; };

	virtual StringEncoding getStringEncoding() const { BL_ASSERT_NEVER_REACHED return CHAR8_ENCODING; };
	virtual void setStringEncoding(StringEncoding newStringEncoding) { BL_ASSERT_NEVER_REACHED }

	virtual AbstractTextBuffer& assign(const AbstractTextBuffer& right) { BL_ASSERT_NEVER_REACHED return *this; }
	virtual AbstractTextBuffer& assign(const void* binaryData, int lengthInChars, bool unicode = false) { BL_ASSERT_NEVER_REACHED return *this; }
	virtual AbstractTextBuffer& assign(const AbstractBinaryBuffer* binaryBuffer) { BL_ASSERT_NEVER_REACHED return *this; }

	// Line functions:
	virtual void setLineEndChars(const String& newLineEndChars, bool reparseTextForLineEnds = false) { BL_ASSERT_NEVER_REACHED }
	virtual void changeLineEndChars(const String& newLineEndChars) { BL_ASSERT_NEVER_REACHED }

	virtual int getLineCount() const { BL_ASSERT_NEVER_REACHED return 0; }
	virtual void setLineCount(int newLineCount) { BL_ASSERT_NEVER_REACHED }

	virtual String getLine(int lineNumber) const { BL_ASSERT_NEVER_REACHED return String(NULL); }

	virtual void setLine(int lineNumber, const String& lineText) { BL_ASSERT_NEVER_REACHED }

	virtual void removeLine(int lineNumber) { BL_ASSERT_NEVER_REACHED }
	virtual void insertLine(int lineNumber, const String& lineText) { BL_ASSERT_NEVER_REACHED }
	virtual void addLine(const String& lineText) { BL_ASSERT_NEVER_REACHED }

	// Position read/write functions:
	virtual void setCurrentPosition(int newCurrentPosition) { BL_ASSERT_NEVER_REACHED }

	virtual bool readFromCurrentPositionPossible() const { BL_ASSERT_NEVER_REACHED return false; }

	virtual String readLine(bool moveCurrentPos = true) { BL_ASSERT_NEVER_REACHED return String(NULL); }

	virtual String readFromPosition(int position, int charCount) const { BL_ASSERT_NEVER_REACHED return String(NULL); }
	virtual String readAllFromPosition(int position) const { BL_ASSERT_NEVER_REACHED return String(NULL); }

	virtual void writeAtPosition(int position, const String& source) { BL_ASSERT_NEVER_REACHED };

	virtual void writeBeforePosition(int position, const String& source) { BL_ASSERT_NEVER_REACHED };

	virtual void insertAtPosition(int position, const String& source) { BL_ASSERT_NEVER_REACHED };

	virtual void removeAtPosition(int position, int charCount) { BL_ASSERT_NEVER_REACHED };

	virtual void updateLineEnds() const { BL_ASSERT_NEVER_REACHED };


protected:

	String bufferString;
};



} // namespace Buffers
} // namespace BaseLib


#endif // #ifndef BaseLib_Buffers_DefaultTextBuffer_h
