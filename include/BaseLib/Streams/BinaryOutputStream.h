/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_BinaryOutputStream_h
#define BaseLib_Streams_BinaryOutputStream_h



#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Streams/BinaryStreamEncoding.h"




namespace BaseLib {
namespace Buffers { class AbstractBinaryBuffer; }
namespace Streams {


using BaseLib::Buffers::AbstractBinaryBuffer;


/**
Converts every write call to a writeBinary() call.
Beside an output-streams the stream can be connected to one or more BinaryBuffer.
Write-calls of every type get converted into writeBinary() calls of the connected
streams and buffers.
@see @ref BuffersAndStreams, BinaryInputStream, OutputStream, BinaryStreamEncoding
*/
class BL_EXPORT BinaryOutputStream : public OutputStream, public BinaryStreamEncoding {
public:

	BinaryOutputStream();
	explicit BinaryOutputStream(const OutputStream& connectToOutputStream);
	BinaryOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2);
	explicit BinaryOutputStream(AbstractBinaryBuffer& connectToBuffer);
	virtual ~BinaryOutputStream();

	//virtual void close();
	virtual void flush() const;

	virtual void writeBinary(const void* source, int byteCount) const;
	virtual void write(bool source) const;
	virtual void write(const void* source) const;
	virtual void write(int8 source) const;
	virtual void write(uint8 source) const;
	virtual void write(int16 source) const;
	virtual void write(uint16 source) const;
	virtual void write(int32 source) const;
	virtual void write(uint32 source) const;
	virtual void write(int64 source) const;
	virtual void write(uint64 source) const;
	virtual void write(float source) const;
	virtual void write(double source) const;
	virtual void write(long double source) const;
	virtual void write(const String& source) const;

	/**
	Connects the stram to a AbstractBinaryBuffer.
	Every write-call of the stream gets converted into a AbstractBinaryBuffer::writeAtCurrentPosition() call.
	@see disconnectFromBinaryBuffer(), disconnectFromAllBinaryBuffers()
	*/
	void connectToBinaryBuffer(AbstractBinaryBuffer& newBuffer);

	/**
	Disconnects the stram from a AbstractBinaryBuffer.
	@see connectToBinaryBuffer(), disconnectFromAllBinaryBuffers()
	*/
	void disconnectFromBinaryBuffer(AbstractBinaryBuffer& oldBuffer);

	/**
	Disconnects the stram from all binary-buffers.
	@see connectToBinaryBuffer(), disconnectFromBinaryBuffer()
	*/
	void disconnectFromAllBinaryBuffers();

	/**
	Returns the terminating string for string-writes.
	After every string-write the terminating string written after it.
	@see setStringTerminator()
	*/
	inline const String& getStringTerminator()
	{
		return stringTerminator;
	}

	/**
	Sets the terminating string for string-writes.
	After every string-write the terminating string written after it.
	@see getStringTerminator()
	*/
	inline void setStringTerminator(const String& newStringTerminator)
	{
		stringTerminator = newStringTerminator;
	}

	virtual bool isConnected() const;

protected:
	
	typedef Array<AbstractBinaryBuffer*> ConnectedBinaryBuffers;
	ConnectedBinaryBuffers connectedBinaryBuffers;

	String stringTerminator;

};



} // namespace Streams
} // namespace BaseLib


#endif // #ifndef BaseLib_Streams_BinaryOutputStream_h
