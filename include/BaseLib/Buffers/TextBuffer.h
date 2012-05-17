/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_TextBuffer_h
#define BaseLib_Buffers_TextBuffer_h



#include "BaseLib/Buffers/AbstractTextBuffer.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"
#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Buffers {



class StringImplementationWrapper;
using BaseLib::Containers::Array;


/**
Not implemented yet.
*/
class BL_EXPORT TextBuffer : public AbstractTextBuffer {
	friend StringImplementationWrapper;
public:

	TextBuffer();

	TextBuffer(const String& text);

	//TextBuffer(const AbstractTextBuffer& other);

	virtual void close();

	virtual int getLength() const;
	virtual void setLength(int newLength);

	virtual String& asString();
	virtual const String& asString() const;

	virtual StringEncoding getStringEncoding() const;
	virtual void setStringEncoding(StringEncoding newStringEncoding);

	virtual AbstractTextBuffer& assign(const AbstractTextBuffer& right);
	virtual AbstractTextBuffer& assign(const void* binaryData, int lengthInChars, bool unicode = false);
	virtual AbstractTextBuffer& assign(const AbstractBinaryBuffer* binaryBuffer);

	// Line functions:
	virtual void setLineEndChars(const String& newLineEndChars, bool reparseTextForLineEnds = false);
	virtual void changeLineEndChars(const String& newLineEndChars);

	virtual int getLineCount() const;
	virtual void setLineCount(int newLineCount);

	virtual String getLine(int lineNumber) const;

	virtual void setLine(int lineNumber, const String& lineText);

	virtual void removeLine(int lineNumber);
	virtual void insertLine(int lineNumber, const String& lineText);
	virtual void addLine(const String& lineText);

	// Position read/write functions:
	virtual void setCurrentPosition(int newCurrentPosition);

	virtual bool readFromCurrentPositionPossible() const;

	virtual String readLine(bool moveCurrentPos = true);
	
	virtual String readFromPosition(int position, int charCount) const;
	virtual String readAllFromPosition(int position) const;

	virtual void writeAtPosition(int position, const String& source);
	virtual void writeBeforePosition(int position, const String& source);

	virtual void insertAtPosition(int position, const String& source);

	virtual void removeAtPosition(int position, int charCount);

	virtual void updateLineEnds() const;

protected:

	struct LineInfo {
		inline LineInfo(int newStartPosition = 0, int newLength = 0) : startPosition(newStartPosition), lineLength(newLength) {}
		int startPosition;
		int lineLength;
	};
	typedef Array<LineInfo> LineInfoTable;
	mutable LineInfoTable lineInfoTable;

	class BufferString : public String {
	public:
		BufferString();
		BufferString(const String& text);

		virtual void setImplementation(AbstractStringImplementation* newImplementation, bool deleteOldImplementation = true);
	};

	BufferString bufferString;

	bool checkReadPermission() const;
	bool checkWritePermission();

	inline bool checkBufferStringWritePermission()
	{
		bool permission = checkWritePermission();
		if (permission == true) invalidateLineEnds();
		return permission;
	}
};



} // namespace Buffers
} // namespace BaseLib



#endif // #ifndef BaseLib_Buffers_TextBuffer_h
