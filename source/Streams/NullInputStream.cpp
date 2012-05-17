/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/NullInputStream.h"



namespace BaseLib {
namespace Streams {



NullInputStream nullInputStream;



NullInputStream& NullInputStream::singleton()
{
	return nullInputStream;
}



NullInputStream::NullInputStream()
	: InputStream()
{
}



int NullInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
{
	return 0;
}



bool NullInputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(bool& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(void*& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(int8& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(uint8& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(int16& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(uint16& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(int32& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(uint32& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(int64& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(uint64& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(float& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(double& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(long double& destination, double timeoutSeconds) const
{
	return false;
}



bool NullInputStream::read(String& destination, double timeoutSeconds) const
{
	return false;
}



void NullInputStream::unreadBinary(const void* source, int byteCount) const
{
}



void NullInputStream::unread(bool source) const
{
}



void NullInputStream::unread(const void* source) const
{
}



void NullInputStream::unread(int8 source) const
{
}



void NullInputStream::unread(uint8 source) const
{
}



void NullInputStream::unread(int16 source) const
{
}



void NullInputStream::unread(uint16 source) const
{
}



void NullInputStream::unread(int32 source) const
{
}



void NullInputStream::unread(uint32 source) const
{
}



void NullInputStream::unread(int64 source) const
{
}



void NullInputStream::unread(uint64 source) const
{
}



void NullInputStream::unread(float source) const
{
}



void NullInputStream::unread(double source) const
{
}



void NullInputStream::unread(long double source) const
{
}



void NullInputStream::unread(const String& source) const
{
}



bool NullInputStream::isInputAvailable() const
{
	return false;
}



} // namespace Streams
} // namespace BaseLib
