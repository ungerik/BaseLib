/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DeflateOutputStream_h
#define BaseLib_DeflateOutputStream_h



#include "BaseLib/Streams/BinaryOutputStream.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"



struct z_stream_s;



namespace BaseLib {
namespace Buffers { class BinaryMemBuffer; }
namespace Streams {



using BaseLib::Buffers::BinaryMemBuffer;



/**
Deflates binary data with zlib.
@note: This implementation is in experimental state.
*/
class BL_EXPORT DeflateOutputStream : public BinaryOutputStream {
public:

	static int defaultMaxCompressionBufferSize;

	explicit DeflateOutputStream(double newCompressionLevel = 1.0, int newMaxCompressionBufferSize = defaultMaxCompressionBufferSize);
	explicit DeflateOutputStream(const OutputStream& connectToOutputStream, double newCompressionLevel = 1.0, int newMaxCompressionBufferSize = defaultMaxCompressionBufferSize);
	explicit DeflateOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2, double newCompressionLevel = 1.0, int newMaxCompressionBufferSize = defaultMaxCompressionBufferSize);
	explicit DeflateOutputStream(AbstractBinaryBuffer& connectToBuffer, double newCompressionLevel = 1.0, int newMaxCompressionBufferSize = defaultMaxCompressionBufferSize);

	~DeflateOutputStream();

	void resetCompression();
	void resetCompression(double newCompressionLevel);

	inline float getCompressionLevel() const { return compressionLevel; }
	
	inline int getMaxCompressionBufferSize() const { return maxCompressionBufferSize; }
	void setMaxCompressionBufferSize(int newMaxCompressionBufferSize);


	virtual void writeBinary(const void* source, int byteCount) const;

protected:

	int maxCompressionBufferSize;
	mutable BinaryMemBuffer compressionBuffer;

	void initZStream();

	float compressionLevel;	
	z_stream_s* zStream;
};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_DeflateOutputStream_h
