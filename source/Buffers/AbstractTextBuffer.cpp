/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Buffers/AbstractTextBuffer.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Buffers {



AbstractTextBuffer::AbstractTextBuffer()
  : currentPosition(0)
  , lineEndChars(defaultLineEndChars)
  , validLineEnds(false)
{
}




AbstractTextBuffer::~AbstractTextBuffer()
{
}



bool AbstractTextBuffer::isReadable() const
{
	return true;
}



bool AbstractTextBuffer::isWriteable() const
{
	return true;
}



void AbstractTextBuffer::flush()
{
}


} // namespace Buffers
} // namespace BaseLib
