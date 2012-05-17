/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/FloatOutputStream.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Math.h"
#include "BaseLib/Functors/Deleter.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib;
using namespace BaseLib::Functors;



FloatOutputStream::FloatOutputStream()
	: OutputStream()
	, connectedFunctors()
{
}


FloatOutputStream::FloatOutputStream(const OutputStream& connectToOutputStream)
	: OutputStream(connectToOutputStream)
	, connectedFunctors()
{
}



FloatOutputStream::FloatOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2)
	: OutputStream(connectToOutputStream1, connectToOutputStream2)
	, connectedFunctors()
{
}



FloatOutputStream::FloatOutputStream(const Functor& connectToSetterFunctor)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(connectToSetterFunctor);
}



FloatOutputStream::FloatOutputStream(float* value)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(VariableFunctor(value));
}



FloatOutputStream::~FloatOutputStream()
{
	disconnectFromAllFunctors();
}



void FloatOutputStream::writeBinary(const void* source, int byteCount) const
{
	OutputType value = 0;
	memCopy(&value, source, min(byteCount, (int)sizeof(OutputType)));
	write(value);
}



void FloatOutputStream::write(bool source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(const void* source) const
{
	write(static_cast<OutputType>(reinterpret_cast<int32>(source)));
}



void FloatOutputStream::write(int8 source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(uint8 source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(int16 source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(uint16 source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(int32 source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(uint32 source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(int64 source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(uint64 source) const
{
	write(static_cast<OutputType>(source));
}



void FloatOutputStream::write(float source) const
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



void FloatOutputStream::write(double source) const
{
	write(round<OutputType>(source));
}



void FloatOutputStream::write(long double source) const
{
	write(round<OutputType>(source));
}



void FloatOutputStream::write(const String& source) const
{
	write(source.parseFloat());
}



void FloatOutputStream::connectToFunctor(const Functor& newFunctor)
{
	connectedFunctors += newFunctor.clone();
}



void FloatOutputStream::disconnectFromFunctor(const Functor& oldFunctor)
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



void FloatOutputStream::disconnectFromAllFunctors()
{
	connectedFunctors.enumerate<Deleter>();
}



bool FloatOutputStream::isConnected() const
{
	return (connectedFunctors.getCount() != 0 || OutputStream::isConnected() == true);
}



} // namespace Streams
} // namespace BaseLib


