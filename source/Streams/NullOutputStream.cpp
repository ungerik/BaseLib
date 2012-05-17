/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/NullOutputStream.h"



namespace BaseLib {
namespace Streams {



NullOutputStream nullOutputStream;



NullOutputStream& NullOutputStream::singleton()
{
	return nullOutputStream;
}



NullOutputStream::NullOutputStream()
	: OutputStream()
{
}



void NullOutputStream::flush() const
{
}



void NullOutputStream::writeBinary(const void* source, int byteCount) const
{
}



void NullOutputStream::write(bool source) const
{
}



void NullOutputStream::write(const void* source) const 
{
}



void NullOutputStream::write(int8 source) const 
{
}



void NullOutputStream::write(uint8 source) const 
{
}



void NullOutputStream::write(int16 source) const 
{
}



void NullOutputStream::write(uint16 source) const 
{
}



void NullOutputStream::write(int32 source) const 
{
}



void NullOutputStream::write(uint32 source) const 
{
}



void NullOutputStream::write(int64 source) const 
{
}



void NullOutputStream::write(uint64 source) const 
{
}



void NullOutputStream::write(float source) const 
{
}



void NullOutputStream::write(double source) const 
{
}



void NullOutputStream::write(long double source) const 
{
}



void NullOutputStream::write(const String& source) const 
{
}



} // namespace Streams
} // namespace BaseLib

