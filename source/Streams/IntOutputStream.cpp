/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/IntOutputStream.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Math.h"
#include "BaseLib/Functors/Deleter.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib;
using namespace BaseLib::Functors;



IntOutputStream::IntOutputStream()
	: OutputStream()
	, connectedFunctors()
{
}


IntOutputStream::IntOutputStream(const OutputStream& connectToOutputStream)
	: OutputStream(connectToOutputStream)
	, connectedFunctors()
{
}



IntOutputStream::IntOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2)
	: OutputStream(connectToOutputStream1, connectToOutputStream2)
	, connectedFunctors()
{
}



IntOutputStream::IntOutputStream(const Functor& connectToSetterFunctor)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(connectToSetterFunctor);
}



IntOutputStream::IntOutputStream(int* value)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(VariableFunctor(value));
}



IntOutputStream::~IntOutputStream()
{
	disconnectFromAllFunctors();
}



void IntOutputStream::writeBinary(const void* source, int byteCount) const
{
	OutputType value = 0;
	memCopy(&value, source, min(byteCount, (int)sizeof(OutputType)));
	write(value);
}



void IntOutputStream::write(bool source) const
{
	write(static_cast<OutputType>(source));
}



void IntOutputStream::write(const void* source) const
{
	write(reinterpret_cast<OutputType>(source));
}



void IntOutputStream::write(int8 source) const
{
	write(static_cast<OutputType>(source));
}



void IntOutputStream::write(uint8 source) const
{
	write(static_cast<OutputType>(source));
}



void IntOutputStream::write(int16 source) const
{
	write(static_cast<OutputType>(source));
}



void IntOutputStream::write(uint16 source) const
{
	write(static_cast<OutputType>(source));
}



void IntOutputStream::write(int32 source) const
{
	totalBytesWritten += sizeof(source);

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



void IntOutputStream::write(uint32 source) const
{
	write(static_cast<OutputType>(source));
}



void IntOutputStream::write(int64 source) const
{
	write(static_cast<OutputType>(source));
}



void IntOutputStream::write(uint64 source) const
{
	write(static_cast<OutputType>(source));
}



void IntOutputStream::write(float source) const
{
	write(round<OutputType>(source));
}



void IntOutputStream::write(double source) const
{
	write(round<OutputType>(source));
}



void IntOutputStream::write(long double source) const
{
	write(round<OutputType>(source));
}



void IntOutputStream::write(const String& source) const
{
	write(source.parseInt());
}



void IntOutputStream::connectToFunctor(const Functor& newFunctor)
{
	connectedFunctors += newFunctor.clone();
}



void IntOutputStream::disconnectFromFunctor(const Functor& oldFunctor)
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



void IntOutputStream::disconnectFromAllFunctors()
{
	connectedFunctors.enumerate<Deleter>();
}



bool IntOutputStream::isConnected() const
{
	return (connectedFunctors.getCount() != 0 || OutputStream::isConnected() == true);
}



} // namespace Streams
} // namespace BaseLib


