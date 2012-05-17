/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/Streams/TextOutputStream.h"
#include "BaseLib/Buffers/AbstractTextBuffer.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::Containers;
using namespace BaseLib::ErrorHandling;



TextOutputStream::TextOutputStream()
  : OutputStream()
  , useWideString(false)
  , writeBinaryMethod(WRITE_BINARY_AS_HEX_STRING)
{
}



TextOutputStream::TextOutputStream(const OutputStream& connectToOutputStream)
  : OutputStream(connectToOutputStream)
  , useWideString(false)
  , writeBinaryMethod(WRITE_BINARY_AS_HEX_STRING)
{
}



TextOutputStream::TextOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2)
  : OutputStream(connectToOutputStream1, connectToOutputStream2)
  , useWideString(false)
  , writeBinaryMethod(WRITE_BINARY_AS_HEX_STRING)
{
}



TextOutputStream::TextOutputStream(AbstractTextBuffer& connectToBuffer)
  : OutputStream()
  , useWideString(false)
  , writeBinaryMethod(WRITE_BINARY_AS_HEX_STRING)
{
	connectToTextBuffer(connectToBuffer);
}



TextOutputStream::~TextOutputStream()
{
	//close();
}



/*void TextOutputStream::close()
{
	OutputStream::close();

	for (ConnectedTextBuffers::Iterator i = connectedTextBuffers.begin(); i != connectedTextBuffers.end(); ++i)
	{
		(*i)->close();
	}
}*/



void TextOutputStream::writeBinary(const void* source, int byteCount) const
{
	if (useWideString == false)
	{
		switch(writeBinaryMethod)
		{
			case WRITE_BINARY_AS_HEX_STRING:
				write(bin2hex(source, byteCount));
				return;

			case WRITE_BINARY_AS_BIN_STRING:
				write(bin2binString(source, byteCount));
				return;
		}
	}
	else
	{
		switch(writeBinaryMethod)
		{
			case WRITE_BINARY_AS_HEX_STRING:
				write(bin2hexW(source, byteCount));
				return;

			case WRITE_BINARY_AS_BIN_STRING:
				write(bin2binStringW(source, byteCount));
				return;
		}
	}

	BL_ASSERT_NEVER_REACHED
}



template<typename T>
void TextOutputStream::writeTemplate(T source) const
{
	write(String::createFrom(source));
}



void TextOutputStream::write(bool source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(const void* source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(int8 source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(uint8 source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(int16 source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(uint16 source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(int32 source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(uint32 source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(int64 source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(uint64 source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(float source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(double source) const 
{
	writeTemplate(source);
}

void TextOutputStream::write(long double source) const 
{
	writeTemplate(source);
}




void TextOutputStream::write(const String& source) const
{
	const String s = source + stringTerminator;

	for (ConnectedStreams::ConstIterator i = connectedStreams.begin(); i != connectedStreams.end(); ++i)
	{
		(*i)->write(s);
	}

	for (ConnectedTextBuffers::ConstIterator i = connectedTextBuffers.begin(); i != connectedTextBuffers.end(); ++i)
	{
		(*i)->writeAtCurrentPosition(s);
	}

	if (connectedStreams.isEmpty() == true && connectedTextBuffers.isEmpty() == true) stateError(NO_STREAM_OR_BUFFER_CONNECTED_FOR_WRITE);
}



void TextOutputStream::connectToTextBuffer(AbstractTextBuffer& newBuffer)
{
	connectedTextBuffers += &newBuffer;
}



void TextOutputStream::disconnectFromTextBuffer(AbstractTextBuffer& oldBuffer)
{
	int pos = connectedTextBuffers.firstIndexOf(&oldBuffer);
	if (pos != -1)
	{
		connectedTextBuffers.remove(pos);
	}
	else
	{
		argumentError(BUFFER_TO_DISCONNECT_NOT_FOUND);
	}
}



bool TextOutputStream::isConnected() const
{
	return (connectedTextBuffers.getCount() != 0 || OutputStream::isConnected() == true);
}



void TextOutputStream::flush() const
{
	OutputStream::flush();

	for (ConnectedTextBuffers::ConstIterator i = connectedTextBuffers.begin(); i != connectedTextBuffers.end(); ++i)
	{
		(*i)->flush();
	}
}



} // namespace Streams
} // namespace BaseLib

