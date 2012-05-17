/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/StringOutputStream.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Math.h"
#include "BaseLib/Functors/Deleter.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib;
using namespace BaseLib::Functors;



StringOutputStream::StringOutputStream()
	: OutputStream()
	, connectedFunctors()
{
}


StringOutputStream::StringOutputStream(const OutputStream& connectToOutputStream)
	: OutputStream(connectToOutputStream)
	, connectedFunctors()
{
}



StringOutputStream::StringOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2)
	: OutputStream(connectToOutputStream1, connectToOutputStream2)
	, connectedFunctors()
{
}



StringOutputStream::StringOutputStream(const Functor& connectToSetterFunctor)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(connectToSetterFunctor);
}



StringOutputStream::StringOutputStream(String* value)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(VariableFunctor(value));
}



StringOutputStream::~StringOutputStream()
{
	disconnectFromAllFunctors();
}



void StringOutputStream::writeBinary(const void* source, int byteCount) const
{
	BL_ASSERT_NOT_IMPLEMENTED
	//OutputType value = false;
	//memCopy(&value, source, min(byteCount, (int)sizeof(OutputType)));
	//write(value);
}



void StringOutputStream::write(bool source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(const void* source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(int8 source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(uint8 source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(int16 source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(uint16 source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(int32 source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(uint32 source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(int64 source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(uint64 source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(float source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(double source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(long double source) const
{
	write(String::createFrom(source));
}



void StringOutputStream::write(const String& source) const
{
	totalBytesWritten += sizeof(source.getByteSize());

	for (ConnectedStreams::ConstIterator i = connectedStreams.begin(); i != connectedStreams.end(); ++i)
	{
		(*i)->write(source);
	}

	for (ConnectedFunctors::ConstIterator i = connectedFunctors.begin(); i != connectedFunctors.end(); ++i)
	{
		(*(*i))(source);
	}

	if (connectedStreams.isEmpty() == true && connectedFunctors.isEmpty() == true)
	{
		stateError(NO_STREAM_OR_FUNCTOR_CONNECTED_FOR_WRITE);
	}
}



void StringOutputStream::connectToFunctor(const Functor& newFunctor)
{
	connectedFunctors += newFunctor.clone();
}



void StringOutputStream::disconnectFromFunctor(const Functor& oldFunctor)
{
	int count = connectedFunctors.getCount();
	for (int i = 0; i < count; ++i)
	{
		if (*connectedFunctors[i] == oldFunctor)
		{
			delete connectedFunctors[i];
			connectedFunctors.remove(i);
			return;
		}
	}

	argumentError("Functor to disconnect from not found in list of connected functors !" ERROR_AT);
}



void StringOutputStream::disconnectFromAllFunctors()
{
	connectedFunctors.enumerate<Deleter>();
}



bool StringOutputStream::isConnected() const
{
	return (connectedFunctors.getCount() != 0 || OutputStream::isConnected() == true);
}



} // namespace Streams
} // namespace BaseLib


