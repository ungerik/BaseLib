/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/BoolOutputStream.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Math.h"
#include "BaseLib/Functors/Deleter.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib;



BoolOutputStream::BoolOutputStream()
	: OutputStream()
	, connectedFunctors()
{
}



BoolOutputStream::BoolOutputStream(const OutputStream& connectToOutputStream)
	: OutputStream(connectToOutputStream)
	, connectedFunctors()
{
}



BoolOutputStream::BoolOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2)
	: OutputStream(connectToOutputStream1, connectToOutputStream2)
	, connectedFunctors()
{
}



BoolOutputStream::BoolOutputStream(const Functor& connectToSetterFunctor)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(connectToSetterFunctor);
}



BoolOutputStream::BoolOutputStream(bool* value)
	: OutputStream()
	, connectedFunctors()
{
	connectToFunctor(VariableFunctor(value));
}



BoolOutputStream::~BoolOutputStream()
{
	disconnectFromAllFunctors();
}



void BoolOutputStream::writeBinary(const void* source, int byteCount) const
{
	OutputType value = false;
	memCopy(&value, source, min(byteCount, (int)sizeof(OutputType)));
	write(value);
}



void BoolOutputStream::write(bool source) const
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



void BoolOutputStream::write(const void* source) const
{
	write(source != NULL);
}



void BoolOutputStream::write(int8 source) const
{
	write(source != 0);
}



void BoolOutputStream::write(uint8 source) const
{
	write(source != 0);
}



void BoolOutputStream::write(int16 source) const
{
	write(source != 0);
}



void BoolOutputStream::write(uint16 source) const
{
	write(source != 0);
}



void BoolOutputStream::write(int32 source) const
{
	write(source != 0);
}



void BoolOutputStream::write(uint32 source) const
{
	write(source != 0);
}



void BoolOutputStream::write(int64 source) const
{
	write(source != 0);
}



void BoolOutputStream::write(uint64 source) const
{
	write(source != 0);
}



void BoolOutputStream::write(float source) const
{
	write(source != 0);
}



void BoolOutputStream::write(double source) const
{
	write(source != 0);
}



void BoolOutputStream::write(long double source) const
{
	write(source != 0);
}



void BoolOutputStream::write(const String& source) const
{
	write(source.parseBool());
}



void BoolOutputStream::connectToFunctor(const Functor& newFunctor)
{
	connectedFunctors += newFunctor.clone();
}



void BoolOutputStream::disconnectFromFunctor(const Functor& oldFunctor)
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



void BoolOutputStream::disconnectFromAllFunctors()
{
	connectedFunctors.enumerate<Deleter>();
}



bool BoolOutputStream::isConnected() const
{
	return (connectedFunctors.getCount() != 0 || OutputStream::isConnected() == true);
}



} // namespace Streams
} // namespace BaseLib


