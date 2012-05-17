/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Buffers/TextFileBuffer.h"



namespace BaseLib {
namespace Buffers {




TextFileBuffer::TextFileBuffer(const String& fileName, bool read, bool write)
  : TextBuffer()
  ,	name(fileName)
  , readable(read)
  , writeable(write)
{
	if (read == true)
	{
		BinaryFileBuffer fileBuffer(name, readable, false);
		assign(&fileBuffer);
	}
}



TextFileBuffer::~TextFileBuffer()
{
	close();
}



bool TextFileBuffer::isReadable() const
{
	return readable;
}



bool TextFileBuffer::isWriteable() const
{
	return writeable;
}



void TextFileBuffer::flush()
{
	if (writeable == true)
	{
		BinaryFileBuffer fileBuffer(name, false, writeable);
		if (bufferString.getEncoding() == CHAR16_ENCODING)
		{
			fileBuffer.writeAtPosition(0, bufferString.getChar16Array(), bufferString.getLength()*sizeof(char16));
		}
		else
		{
			BL_ASSERT(bufferString.getEncoding() == CHAR8_ENCODING);
			fileBuffer.writeAtPosition(0, bufferString.getChar8Array(), bufferString.getLength()*sizeof(char8));
		}
	}
}



void TextFileBuffer::close()
{
	flush();
}



} // namespace Buffers
} // namespace BaseLib


