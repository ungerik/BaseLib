/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/DoubleOutputStream.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Math.h"
#include "BaseLib/Functors/Deleter.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib;
using namespace BaseLib::Functors;



DoubleOutputStream::DoubleOutputStream()
	: OutputStream()
	, connectedFunctors()
{
}


DoubleOutputStream::DoubleOutputStream(const OutputStream& connectToOutputStream)
	: OutputStream(connectToOutputStream)
	, connectedFunctors()
{
}



DoubleOutputStream::DoubleOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2)
	: OutputStream(connectToOutputStream1, connectToOutputStream2)
	, connectedFunctors()
{
}



DoubleOutputStream::DoubleOutputStream(const Functor& connectToSetterFunctor)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(connectToSetterFunctor);
}



DoubleOutputStream::DoubleOutputStream(double* value)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(VariableFunctor(value));
}



DoubleOutputStream::~DoubleOutputStream()
{
	disconnectFromAllFunctors();
}



void DoubleOutputStream::writeBinary(const void* source, int byteCount) const
{
	OutputType value = 0;
	memCopy(&value, source, min(byteCount, (int)sizeof(OutputType)));
	write(value);
}



void DoubleOutputStream::write(bool source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(const void* source) const
{
	write(static_cast<OutputType>(reinterpret_cast<int64>(source)));
}



void DoubleOutputStream::write(int8 source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(uint8 source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(int16 source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(uint16 source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(int32 source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(uint32 source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(int64 source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(uint64 source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(float source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(double source) const
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



void DoubleOutputStream::write(long double source) const
{
	write(static_cast<OutputType>(source));
}



void DoubleOutputStream::write(const String& source) const
{
	write(source.parseDouble());
}



void DoubleOutputStream::connectToFunctor(const Functor& newFunctor)
{
	connectedFunctors += newFunctor.clone();
}



void DoubleOutputStream::disconnectFromFunctor(const Functor& oldFunctor)
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



void DoubleOutputStream::disconnectFromAllFunctors()
{
	connectedFunctors.enumerate<Deleter>();
}



bool DoubleOutputStream::isConnected() const
{
	return (connectedFunctors.getCount() != 0 || OutputStream::isConnected() == true);
}



} // namespace Streams
} // namespace BaseLib


