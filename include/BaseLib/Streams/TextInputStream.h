/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_TextInputStream_h
#define BaseLib_TextInputStream_h


#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Streams/BinaryStreamEncoding.h"



namespace BaseLib {
namespace Buffers { class AbstractTextBuffer; }
namespace Streams {



using BaseLib::Buffers::AbstractTextBuffer;



/**
Not implemented.
*/
class BL_EXPORT TextInputStream : public InputStream, public BinaryStreamEncoding {
public:

	TextInputStream(StringEncoding newStringEncoding = CHAR8);
	explicit TextInputStream(const InputStream& connectToInputStream, StringEncoding newStringEncoding = CHAR8);
	explicit TextInputStream(AbstractTextBuffer& connectToBuffer, StringEncoding newStringEncoding = CHAR8);
	virtual ~TextInputStream();

	virtual int readBinary(void* destination, int byteCount, double timeoutSeconds) const; 
	virtual bool readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const;
	virtual bool read(void*& destination, double timeoutSeconds) const;
	virtual bool read(int8& destination, double timeoutSeconds) const;
	virtual bool read(uint8& destination, double timeoutSeconds) const;
	virtual bool read(int16& destination, double timeoutSeconds) const;
	virtual bool read(uint16& destination, double timeoutSeconds) const;
	virtual bool read(int32& destination, double timeoutSeconds) const;
	virtual bool read(uint32& destination, double timeoutSeconds) const;
	virtual bool read(int64& destination, double timeoutSeconds) const;
	virtual bool read(uint64& destination, double timeoutSeconds) const;
	virtual bool read(float& destination, double timeoutSeconds) const;
	virtual bool read(double& destination, double timeoutSeconds) const;
	virtual bool read(long double& destination, double timeoutSeconds) const;
	virtual bool read(String& destination, double timeoutSeconds) const;

	virtual void unreadBinary(const void* source, int byteCount) const; 
	virtual void unread(bool source) const;
	virtual void unread(const void* source) const;
	virtual void unread(int8 source) const;
	virtual void unread(uint8 source) const;
	virtual void unread(int16 source) const;
	virtual void unread(uint16 source) const;
	virtual void unread(int32 source) const;
	virtual void unread(uint32 source) const;
	virtual void unread(int64 source) const;
	virtual void unread(uint64 source) const;
	virtual void unread(float source) const;
	virtual void unread(double source) const;
	virtual void unread(long double source) const;
	virtual void unread(const String& source) const;


	void unreadReadBuffer() const;

	virtual void connectToStream(const InputStream& newInputStream);

	virtual void connectToTextBuffer(AbstractTextBuffer& newBuffer);
	virtual void disconnectFromTextBuffer();

	virtual bool isConnected() const;

	bool unreadWhenLexicalCastFailed;

	virtual bool isInputAvailable() const;

	enum ReadBinaryMethode {
		INTERPRET_STRING_AS_BINARY_DATA,
		INTERPRET_STRING_AS_HEX_STRING,
		INTERPRET_STRING_AS_BIN_STRING,
		INTERPRET_STRING_AS_BASE64_STRING
	};

	inline ReadBinaryMethode getReadBinaryMethode() const {	return readBinaryMethode; }
	inline void setReadBinaryMethode(ReadBinaryMethode newReadBinaryMethode) { readBinaryMethode = newReadBinaryMethode; }

	enum ReadStringMethod {
		READ_STRING,
		READ_TOKEN,
		READ_LINE,
		READ_SINGLE_CHAR,
		READ_STRING_WITH_LENGTH
	};

	inline ReadStringMethod getReadStringMethod() const {	return readStringMethod; }
	inline void setReadStringMethod(ReadStringMethod newReadStringMethod) { readStringMethod = newReadStringMethod; }

	enum ReadTextBufferMethode {
		READ_TEXT_BUFFER_LINE,
		READ_TEXT_BUFFER_TOKEN,
		READ_TEXT_BUFFER_UNTIL_END,
		READ_TEXT_BUFFER_STRING_WITH_LENGTH
	};

	inline ReadTextBufferMethode getReadTextBufferMethode() const { return readTextBufferMethode; }
	virtual void setReadTextBufferMethode(ReadTextBufferMethode newReadTextBufferMethode);

	inline const String& getTokenDelimiters() const { return tokenDelimiters; }
	inline void setTokenDelimiters(const String& newTokenDelimiters) { tokenDelimiters = newTokenDelimiters; }

	inline const String& getLineEndChars() const {	return lineEndChars; }
	inline void setLineEndChars(const String& newLineEndChars) { lineEndChars = newLineEndChars; }

	bool readString(String& destination, double timeoutSeconds) const;
	bool readToken(String& destination, const String& tokenDelimiters, double timeoutSeconds) const; // only token written to echoStream
	inline bool readToken(String& destination, double timeoutSeconds) const { return readToken(destination, getTokenDelimiters(), timeoutSeconds); } // only token written to echoStream
	bool readLine(String& destination, double timeoutSeconds) const; // line without line-end written to echoStream
	bool readChar(char8& destination, double timeoutSeconds) const; // no output to echoStream
	bool readChar(char16& destination, double timeoutSeconds) const; // no output to echoStream
	bool readStringWithLength(String& destination, double timeoutSeconds) const;

	inline bool readString(String& destination) const { return readString(destination, readTimeoutSeconds); }
	inline bool readToken(String& destination, const String& tokenDelimiters) const { return readToken(destination, getTokenDelimiters(), readTimeoutSeconds); } // only token written to echoStream
	inline bool readToken(String& destination) const { return readToken(destination, getTokenDelimiters(), readTimeoutSeconds); } // only token written to echoStream
	inline bool readLine(String& destination) const { return readLine(destination, readTimeoutSeconds); } // line without line-end written to echoStream
	inline bool readChar(char8& destination) const { return readChar(destination, readTimeoutSeconds); } // no output to echoStream
	inline bool readChar(char16& destination) const { return readChar(destination, readTimeoutSeconds); } // no output to echoStream
	inline bool readStringWithLength(String& destination) const { return readStringWithLength(destination, readTimeoutSeconds); }



protected:

	AbstractTextBuffer* connectedTextBuffer;
	mutable String readBuffer;
	ReadBinaryMethode readBinaryMethode;
	ReadStringMethod readStringMethod;
	ReadTextBufferMethode readTextBufferMethode;

	String tokenDelimiters;

	String lineEndChars;

	template<typename C>
	bool readToken(String& destination, const String& tokenDelimiters, double timeoutSeconds) const;

	template<typename C>
	bool readLine(String& destination, double timeoutSeconds) const;

	template<typename C>
	bool readChar(C& destination, double timeoutSeconds, bool echo) const;

	template<typename C>
	bool readStringWithLength(String& destination, double timeoutSeconds) const;

private:

	template<typename T>
	bool readTemplate(T& destination, double timeoutSeconds) const;

	template<typename T>
	void unreadTemplate(const T source) const;

};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_TextInputStream_h
