/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_NullInputStream_h
#define BaseLib_NullInputStream_h



#include "BaseLib/Streams/InputStream.h"



namespace BaseLib {
namespace Streams {



/**
Never reads anything.
@see @ref BuffersAndStreams, InputStream, NullOutputStream
*/
class BL_EXPORT NullInputStream : public InputStream {
public:

	static NullInputStream& singleton();

	NullInputStream();

	virtual int readBinary(void* destination, int byteCount, double timeout) const;
	virtual bool readBinaryComplete(void* destination, int byteCount, double timeout) const;
	virtual bool read(bool& destination, double timeout) const;
	virtual bool read(void*& destination, double timeout) const;
	virtual bool read(int8& destination, double timeout) const;
	virtual bool read(uint8& destination, double timeout) const;
	virtual bool read(int16& destination, double timeout) const;
	virtual bool read(uint16& destination, double timeout) const;
	virtual bool read(int32& destination, double timeout) const;
	virtual bool read(uint32& destination, double timeout) const;
	virtual bool read(int64& destination, double timeout) const;
	virtual bool read(uint64& destination, double timeout) const;
	virtual bool read(float& destination, double timeout) const;
	virtual bool read(double& destination, double timeout) const;
	virtual bool read(long double& destination, double timeout) const;
	virtual bool read(String& destination, double timeout) const;

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

	virtual bool isInputAvailable() const;

};



} // namespace Streams
} // namespace BaseLib




#endif // #ifndef BaseLib_NullInputStream_h
