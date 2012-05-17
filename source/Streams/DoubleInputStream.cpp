/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/DoubleInputStream.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Math.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Functors;



DoubleInputStream::DoubleInputStream()
	: InputStream()
	, connectedFunctor(NULL)
	//, unreadStack()
{
}



DoubleInputStream::DoubleInputStream(const InputStream& connectToInputStream)
	: InputStream(connectToInputStream)
	, connectedFunctor(NULL)
	//, unreadStack()
{
}



DoubleInputStream::DoubleInputStream(const Functor& connectToGetterFunctor)
	: InputStream()
	, connectedFunctor(connectToGetterFunctor.clone())
	//, unreadStack()
{
}



DoubleInputStream::DoubleInputStream(const double* value)
	: InputStream()
	, connectedFunctor(new VariableFunctor(value))
{
}



DoubleInputStream::DoubleInputStream(double value)
	: InputStream()
	, connectedFunctor(new ValueGetterFunctor<double>(value))
{
}



int DoubleInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		int bytes = min(byteCount, (int)sizeof(InputType));
		memCopy(destination, &value, bytes);
		totalBytesRead += bytes;
		return bytes;
	}
	else
	{
		return 0;
	}
}



bool DoubleInputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		int bytes = min(byteCount, (int)sizeof(InputType));
		memCopy(destination, &value, bytes);
		totalBytesRead += bytes;
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(bool& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value != 0;
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(int8& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<int8>(round<int64>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(uint8& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<uint8>(round<int64>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(void*& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = reinterpret_cast<void*>(round<int64>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(int16& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<int16>(round<int64>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(uint16& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<uint16>(round<int64>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(int32& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<int32>(round<int64>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(uint32& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<uint32>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(int64& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = round<int64>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(uint64& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = round<uint64>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(float& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<float>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(double& destination, double timeoutSeconds) const
{
	if (connectedFunctor != NULL)
	{
		destination = (*connectedFunctor)();
		totalBytesRead += sizeof(destination);
		return true;
	}
	else
	{
		return InputStream::read(destination, timeoutSeconds);
	}
}



bool DoubleInputStream::read(long double& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value;
		return true;
	}
	else
	{
		return false;
	}
}



bool DoubleInputStream::read(String& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = String::createFrom(value);
		return true;
	}
	else
	{
		return false;
	}
}



/*
void DoubleInputStream::unreadBinary(const void* source, int byteCount) const
{
}



void DoubleInputStream::unread(bool source) const
{
	unread(static_cast<InputType>(source));
}



void DoubleInputStream::unread(const void* source) const
{
	unread(reinterpret_cast<InputType>(source));
}



void DoubleInputStream::unread(int8 source) const
{
	unread(static_cast<InputType>(source));
}



void DoubleInputStream::unread(uint8 source) const
{
	unread(static_cast<InputType>(source));
}



void DoubleInputStream::unread(int16 source) const
{
	unread(static_cast<InputType>(source));
}



void DoubleInputStream::unread(uint16 source) const
{
	unread(static_cast<InputType>(source));
}


void DoubleInputStream::unread(int32 source) const
{
	if (connectedStream != NULL)
	{
		connectedStream->unread(source);
	}
	else
	{
		unreadStack.push(source);
	}
}



void DoubleInputStream::unread(uint32 source) const
{
	unread(static_cast<InputType>(source));
}



void DoubleInputStream::unread(int64 source) const
{
	unread(static_cast<InputType>(source));
}



void DoubleInputStream::unread(uint64 source) const
{
	unread(static_cast<InputType>(source));
}



void DoubleInputStream::unread(float source) const
{
	unread(round<InputType>(source));
}



void DoubleInputStream::unread(double source) const
{
	unread(round<InputType>(source));
}



void DoubleInputStream::unread(long double source) const
{
	unread(round<InputType>(source));
}



void DoubleInputStream::unread(const String& source) const
{
	unread(source.parse<InputType>());
}
*/


bool DoubleInputStream::isConnected() const
{
	return (connectedFunctor != NULL || InputStream::isConnected() == true);
}



void DoubleInputStream::connectToStream(const InputStream& newInputStream)
{
	if (connectedFunctor != NULL) disconnectFromFunctor();
	InputStream::connectToStream(newInputStream);
}



void DoubleInputStream::connectToFunctor(const Functor& newFunctor)
{
	if (connectedStream != NULL) disconnectFromStream();
	connectedFunctor = newFunctor.clone();
}



void DoubleInputStream::disconnectFromFunctor()
{
	connectedFunctor = NULL;
}



bool DoubleInputStream::isInputAvailable() const
{
	bool result = InputStream::isInputAvailable();

	if (result == false && connectedFunctor != NULL)
	{
		result = true;
	}

	return result;
}



} // namespace Streams
} // namespace BaseLib
