/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_BinaryInputStream_h
#define BaseLib_Streams_BinaryInputStream_h



#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Streams/BinaryStreamEncoding.h"



namespace BaseLib {
namespace Buffers { class AbstractBinaryBuffer; }
namespace Streams {


using BaseLib::Buffers::AbstractBinaryBuffer;


/**
Converts every read call to a readBinary() call.
Beside an InputStream the stream can be connected to a BinaryBuffer alternatively.
Read-calls of every type get converted into readBinary() calls.
Because there is more than one binary representation of strings,
the stream can be configured to different string-reading strategies. 
@see @ref BuffersAndStreams, BinaryOutputStream, InputStream, BinaryStreamEncoding, setReadStringMethod()
*/
class BL_EXPORT BinaryInputStream : public InputStream, public BinaryStreamEncoding {
public:

	BinaryInputStream();
	explicit BinaryInputStream(const InputStream& connectToInputStream);
	explicit BinaryInputStream(AbstractBinaryBuffer& connectToBuffer);
	virtual ~BinaryInputStream();

	virtual int readBinary(void* destination, int byteCount, double timeoutSeconds) const;
	virtual bool readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const;
	virtual bool read(bool& destination, double timeoutSeconds) const;
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

	/**
	Returns the token delimiters used for string-reading by token.
	@see setTokenDelimiters(), setReadStringMethod(), readStringToken()
	*/
	inline const String& getTokenDelimiters() const
	{
		return tokenDelimiters;
	}

	/**
	Sets the token delimiters used for string-reading by token.
	@see getTokenDelimiters(), setReadStringMethod(), readStringToken()
	*/
	inline void setTokenDelimiters(const String& newTokenDelimiters)
	{
		tokenDelimiters = newTokenDelimiters;
	}
	
	/**
	Reads a string-token from the stream using the passed tokenDelimiters.
	@see readStringWithLength(), readStringUntilNoInputAvailable()
	*/
	bool readStringToken(String& destination, const String& tokenDelimiters, double timeoutSeconds) const;

	/**
	Reads a string-token from the stream using the objects token-delimiters.
	@see setTokenDelimiters(), readStringWithLength(), readStringUntilNoInputAvailable()
	*/
	inline bool readStringToken(String& destination, double timeoutSeconds) const
	{
		return readStringToken(destination, getTokenDelimiters(), timeoutSeconds);
	}

	/**
	Reads a string-token from the stream using the passed tokenDelimiters.
	@see readStringWithLength(), readStringUntilNoInputAvailable()
	*/
	inline bool readStringToken(String& destination, const String& tokenDelimiters) const
	{
		return readStringToken(destination, tokenDelimiters, readTimeoutSeconds);
	}

	/**
	Reads a string-token from the stream using the objects token-delimiters.
	@see setTokenDelimiters(), readStringWithLength(), readStringUntilNoInputAvailable()
	*/
	inline bool readStringToken(String& destination) const
	{
		return readStringToken(destination, getTokenDelimiters(), readTimeoutSeconds);
	}

	/**
	Reads a string with the length of the passed string from the stream.
	@see readStringToken(), readStringUntilNoInputAvailable()
	*/
	bool readStringWithLength(String& destination, double timeoutSeconds) const;

	/**
	Reads a string with the length of the passed string from the stream.
	@see readStringToken(), readStringUntilNoInputAvailable()
	*/
	inline bool readStringWithLength(String& destination) const
	{
		return readStringWithLength(destination, readTimeoutSeconds);
	}

	/**
	Reads a string until no input is available from the stream.
	@see readStringToken(), readStringWithLength()
	*/
	bool readStringUntilNoInputAvailable(String& destination, double timeoutSeconds) const;

	/**
	Reads a string until no input is available from the stream.
	@see readStringToken(), readStringWithLength()
	*/
	inline bool readStringUntilNoInputAvailable(String& destination) const
	{
		return readStringUntilNoInputAvailable(destination, readTimeoutSeconds);
	}

	enum ReadStringMethod {
		READ_STRING_UNTIL_NO_INPUT_AVAILABLE,
		READ_STRING_TOKEN,
		READ_STRING_WITH_LENGTH
	};

	/**
	Returns the method of string-reading.
	@see setReadStringMethod ReadStringMethod
	*/
	inline ReadStringMethod getReadStringMethod() const
	{
		return readStringMethod;
	}

	/**
	Sets the method of string-reading.
	@see getReadStringMethod ReadStringMethod
	*/
	inline void setReadStringMethod(ReadStringMethod newReadStringMethod)
	{
		readStringMethod = newReadStringMethod;
	}

	virtual bool isInputAvailable() const;

	virtual bool isConnected() const;

	virtual void connectToStream(const InputStream& newInputStream);

	/**
	Connects the stram to a AbstractBinaryBuffer.
	A connected input-stream gets disconnected.
	Every read-call of the stream gets converted into a AbstractBinaryBuffer::readFromCurrentPosition() call.
	@see disconnectFromBinaryBuffer()
	*/
	virtual void connectToBinaryBuffer(AbstractBinaryBuffer& newBuffer);

	/**
	Disconnects the stram from a AbstractBinaryBuffer.
	@see connectToBinaryBuffer()
	*/
	void disconnectFromBinaryBuffer();


protected:

	String tokenDelimiters;
	ReadStringMethod readStringMethod;
	AbstractBinaryBuffer* connectedBinaryBuffer;

};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_Streams_BinaryInputStream_h
