/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/BinaryOutputStream.h"
#include "BaseLib/Buffers/AbstractBinaryBuffer.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Utilities/AutoArray.h"


namespace BaseLib {
namespace Streams {



using BaseLib::Utilities::AutoArray;
using namespace BaseLib::ErrorHandling;



BinaryOutputStream::BinaryOutputStream()
	: OutputStream()
	, connectedBinaryBuffers()
{
}



BinaryOutputStream::BinaryOutputStream(const OutputStream& connectToOutputStream)
	: OutputStream(connectToOutputStream)
	, connectedBinaryBuffers()
{
}



BinaryOutputStream::BinaryOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2)
	: OutputStream(connectToOutputStream1, connectToOutputStream2)
	, connectedBinaryBuffers()
{
}



BinaryOutputStream::BinaryOutputStream(AbstractBinaryBuffer& connectToBuffer)
	: OutputStream()
	, connectedBinaryBuffers()
{
	connectToBinaryBuffer(connectToBuffer);
}



BinaryOutputStream::~BinaryOutputStream()
{
	disconnectFromAllBinaryBuffers();
}


/*
void BinaryOutputStream::close()
{
	OutputStream::close();

	for (ConnectedBinaryBuffers::Iterator i = connectedBinaryBuffers.begin(); i != connectedBinaryBuffers.end(); ++i)
	{
		(*i)->close();
	}
}*/



void BinaryOutputStream::writeBinary(const void* source, int byteCount) const
{
	if (checkArgumentNotNull(NAME_VALUE(source)) == true &&
		checkArgumentPositive(NAME_VALUE(byteCount)) == true)
	{
		totalBytesWritten += byteCount;

		for (ConnectedStreams::ConstIterator i = connectedStreams.begin(); i != connectedStreams.end(); ++i)
		{
			(*i)->writeBinary(source, byteCount);
		}

		for (ConnectedBinaryBuffers::ConstIterator i = connectedBinaryBuffers.begin(); i != connectedBinaryBuffers.end(); ++i)
		{
			(*i)->writeAtCurrentPosition(source, byteCount);
		}

		if (connectedStreams.isEmpty() == true && connectedBinaryBuffers.isEmpty() == true) stateError(NO_STREAM_OR_BUFFER_CONNECTED_FOR_WRITE);
	}
}



#define WRITEBINARY { correctEndian(source); writeBinary(&source, sizeof(source)); }



void BinaryOutputStream::write(bool source) const WRITEBINARY
void BinaryOutputStream::write(const void* source) const WRITEBINARY
void BinaryOutputStream::write(int8 source) const WRITEBINARY
void BinaryOutputStream::write(uint8 source) const WRITEBINARY
void BinaryOutputStream::write(int16 source) const WRITEBINARY
void BinaryOutputStream::write(uint16 source) const WRITEBINARY
void BinaryOutputStream::write(int32 source) const WRITEBINARY
void BinaryOutputStream::write(uint32 source) const WRITEBINARY
void BinaryOutputStream::write(int64 source) const WRITEBINARY
void BinaryOutputStream::write(uint64 source) const WRITEBINARY
void BinaryOutputStream::write(float source) const WRITEBINARY
void BinaryOutputStream::write(double source) const WRITEBINARY
void BinaryOutputStream::write(long double source) const WRITEBINARY



void BinaryOutputStream::write(const String& source) const
{
	int termLength = stringTerminator.getLength();

	if (shouldUseUnicode(source) == true)
	{
		int length = source.getLength();
		if (mustCorrectEndian() == true)
		{
			AutoArray<char16> buffer(new char16[length]); ///
			//source.copyToCharArray(buffer);
			for (int i = 0; i < length; ++i) swapEndian(buffer[i]);
			writeBinary(buffer, length * sizeof(char16));
			if (termLength > 0)
			{
				if (termLength > length) buffer = new char16[termLength];
			}
		}
		else
		{
			writeBinary(source.getChar16Array(), source.getLength() * sizeof(char16));
			if (termLength > 0)
			{
				writeBinary(stringTerminator.getChar16Array(), termLength * sizeof(char16));
			}
		}
	}
	else
	{
		writeBinary(source.getChar8Array(), source.getLength() * sizeof(char8));
		if (termLength > 0)
		{
			writeBinary(stringTerminator.getChar8Array(), termLength * sizeof(char8));
		}
	}
}



void BinaryOutputStream::connectToBinaryBuffer(AbstractBinaryBuffer& newBuffer)
{
	connectedBinaryBuffers += &newBuffer;
}



void BinaryOutputStream::disconnectFromBinaryBuffer(AbstractBinaryBuffer& oldBuffer)
{
	int pos = connectedBinaryBuffers.firstIndexOf(&oldBuffer);
	if (pos != -1)
	{
		connectedBinaryBuffers.remove(pos);
	}
	else
	{
		argumentError(BUFFER_TO_DISCONNECT_NOT_FOUND);
	}
}



void BinaryOutputStream::disconnectFromAllBinaryBuffers()
{
	if (ownerOfConnectedObjects == true)
	{
		for (int i = 0; i < connectedBinaryBuffers.getCount(); ++i)
		{
			delete connectedBinaryBuffers[i];
		}
	}
	connectedBinaryBuffers.setCount(0);
}



void BinaryOutputStream::flush() const
{
	OutputStream::flush();

	for (ConnectedBinaryBuffers::ConstIterator i = connectedBinaryBuffers.begin(); i != connectedBinaryBuffers.end(); ++i)
	{
		(*i)->flush();
	}
}



bool BinaryOutputStream::isConnected() const
{
	return (connectedBinaryBuffers.getCount() != 0 || OutputStream::isConnected() == true);
}



} // namespace Streams
} // namespace BaseLib


