/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Streams {


using namespace BaseLib::Strings;
using namespace BaseLib::ErrorHandling;



OutputStream::OutputStream()
	: connectedStreams()
	, ownerOfConnectedObjects(false)
	, totalBytesWritten(0)
{
}



OutputStream::OutputStream(const OutputStream& connectToOutputStream)
	: connectedStreams()
	, ownerOfConnectedObjects(false)
	, totalBytesWritten(0)
{
	connectToStream(connectToOutputStream);
}



OutputStream::OutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2)
	: connectedStreams()
	, ownerOfConnectedObjects(false)
	, totalBytesWritten(0)
{
	connectToStream(connectToOutputStream1);
	connectToStream(connectToOutputStream2);
}



OutputStream::~OutputStream()
{
	disconnectFromAllStreams();
	//close();
}


/*void OutputStream::close()
{
	flush();
	for (ConnectedStreams::Iterator i = connectedStreams.begin(); i != connectedStreams.end(); ++i)
	{
		(*i)->close();
	}
}*/



void OutputStream::flush() const
{
	for (ConnectedStreams::ConstIterator i = connectedStreams.begin(); i != connectedStreams.end(); ++i)
	{
		(*i)->flush();
	}
}



void OutputStream::writeBinary(const void* source, int byteCount) const
{
	if (checkArgumentNotNull(NAME_VALUE(source)) == true &&
		checkArgumentPositive(NAME_VALUE(byteCount)) == true)
	{
		totalBytesWritten += byteCount;

		for (ConnectedStreams::ConstIterator i = connectedStreams.begin(); i != connectedStreams.end(); ++i)
		{
			(*i)->writeBinary(source, byteCount);
		}

		if (connectedStreams.isEmpty() == true) stateError(NO_STREAM_CONNECTED_FOR_WRITE);
	}
}



template<typename T>
void OutputStream::writeTemplate(T source) const
{
	totalBytesWritten += sizeof(T);

	for (ConnectedStreams::ConstIterator i = connectedStreams.begin(); i != connectedStreams.end(); ++i)
	{
		(*i)->write(source);
	}

	if (connectedStreams.isEmpty() == true) stateError(NO_STREAM_CONNECTED_FOR_WRITE);
}



void OutputStream::write(bool source) const
{
	writeTemplate(source);
}



void OutputStream::write(const void* source) const 
{
	writeTemplate(source);
}



void OutputStream::write(int8 source) const 
{
	writeTemplate(source);
}



void OutputStream::write(uint8 source) const 
{
	writeTemplate(source);
}



void OutputStream::write(int16 source) const 
{
	writeTemplate(source);
}



void OutputStream::write(uint16 source) const 
{
	writeTemplate(source);
}



void OutputStream::write(int32 source) const 
{
	writeTemplate(source);
}



void OutputStream::write(uint32 source) const 
{
	writeTemplate(source);
}



void OutputStream::write(int64 source) const 
{
	writeTemplate(source);
}



void OutputStream::write(uint64 source) const 
{
	writeTemplate(source);
}



void OutputStream::write(float source) const 
{
	writeTemplate(source);
}



void OutputStream::write(double source) const 
{
	writeTemplate(source);
}



void OutputStream::write(long double source) const 
{
	writeTemplate(source);
}



void OutputStream::write(const String& source) const 
{
	writeTemplate(source);
}



void OutputStream::connectToStream(const OutputStream& newOutputStream)
{
	connectedStreams += &newOutputStream;
}



void OutputStream::disconnectFromStream(const OutputStream& oldOutputStream)
{
	int pos = connectedStreams.firstIndexOf(&oldOutputStream);
	if (pos != -1)
	{
		if (ownerOfConnectedObjects == true)
		{
			delete connectedStreams[pos];
		}
		connectedStreams.remove(pos);
	}
	else
	{
		argumentError(STREAM_TO_DISCONNECT_NOT_FOUND);
	}
}



void OutputStream::disconnectFromAllStreams()
{
	if (ownerOfConnectedObjects == true)
	{
		for (int i = 0; i < connectedStreams.getCount(); ++i)
		{
			delete connectedStreams[i];
		}
	}
	connectedStreams.setCount(0);
}



bool OutputStream::isConnected() const
{
	return (connectedStreams.getCount() != 0);
}




OutputStream& newLine(OutputStream& outputStream)
{
	return outputStream << defaultLineEndChars;
}



const OutputStream& newLine(const OutputStream& outputStream)
{
	return outputStream << defaultLineEndChars;
}



OutputStream& backSpace(OutputStream& outputStream)
{
	return outputStream << "\b \b";
}



const OutputStream& backSpace(const OutputStream& outputStream)
{
	return outputStream << "\b \b";
}



OutputStream& flush(OutputStream& outputStream)
{
	outputStream.flush();
	return outputStream;
}



const OutputStream& flush(const OutputStream& outputStream)
{
	outputStream.flush();
	return outputStream;
}



} // namespace Streams
} // namespace BaseLib

