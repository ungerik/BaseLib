/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_NullOutputStream_h
#define BaseLib_Streams_NullOutputStream_h


#include "BaseLib/Streams/OutputStream.h"



namespace BaseLib {
namespace Streams {



/**
Never writes anything.
@see @ref BuffersAndStreams, OutputStream, NullInputStream
*/
class BL_EXPORT NullOutputStream : public OutputStream {
public:

	static NullOutputStream& singleton();

	NullOutputStream();

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
	inline void write(const char8 * source) const { write(String(source)); }
	inline void write(const char16 * source) const { write(String(source)); }

};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_Streams_NullOutputStream_h
