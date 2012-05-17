/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_BufferedBinaryInputStream_h
#define BaseLib_BufferedBinaryInputStream_h



#include "BaseLib/Streams/BinaryInputStream.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"



namespace BaseLib {
namespace Streams {


using BaseLib::Buffers::BinaryMemBuffer;


/**
Buffers binary input data for cached read calls.
@see @ref BuffersAndStreams, BinaryOutputStream, BinaryInputStream, setBufferSize()
*/
class BL_EXPORT BufferedBinaryInputStream : public BinaryInputStream {
public:

	/**
	Default buffer-size for every new instance.
	*/
	static int defaultBufferSize;

	explicit BufferedBinaryInputStream(int bufferSize = defaultBufferSize);
	explicit BufferedBinaryInputStream(const InputStream& connectToInputStream, int bufferSize = defaultBufferSize);
	explicit BufferedBinaryInputStream(AbstractBinaryBuffer& connectToBinaryBuffer, int bufferSize = defaultBufferSize);

	virtual ~BufferedBinaryInputStream();

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

	virtual void unreadBinary(const void* source, int byteCount) const; 

	/**
	Returns the size of the cache-buffer.
	@see setBufferSize()
	*/
	inline int getBufferSize() const
	{
		return cacheBuffer.getSizeAsInt();
	}

	/**
	Sets the size of the cache-buffer.
	@see getBufferSize()
	*/
	void setBufferSize(int newBufferSize);

	inline int getAvailableBufferSize() const
	{
		return static_cast<int>(static_cast<int64>(inputEndPosition) - cacheBuffer.getCurrentPosition());
	}

	/*inline BinaryMemBuffer& getCacheBuffer() { return cacheBuffer; }
	inline const BinaryMemBuffer& getCacheBuffer() const { return cacheBuffer; }*/

	virtual bool isInputAvailable() const;

	virtual void connectToStream(const InputStream& newInputStream);
	virtual void connectToBinaryBuffer(AbstractBinaryBuffer& newBuffer);

	/**
	Resets the current position of the cache-buffer to zero.
	*/
	void resetBuffer();

protected:

	mutable BinaryMemBuffer cacheBuffer;
	mutable int inputEndPosition;
	mutable void* readCompleteBuffer;
	mutable int readCompleteBufferSize;

};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_BufferedBinaryInputStream_h
