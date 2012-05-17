/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/BinaryStreamEncoding.h"



namespace BaseLib {
namespace Streams {



BinaryStreamEncoding::BinaryStreamEncoding(StringEncoding newStringEncoding, Endian newEndian)
	: stringEncoding(newStringEncoding)
	, endian(newEndian)
{
}



BinaryStreamEncoding::~BinaryStreamEncoding()
{
}



void BinaryStreamEncoding::setStringEncoding(StringEncoding newStringEncoding)
{
	stringEncoding = newStringEncoding;
}



void BinaryStreamEncoding::setEndian(Endian newEndian)
{
	endian = newEndian;
}




} // namespace Streams
} // namespace BaseLib