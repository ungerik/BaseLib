/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/FloatInputStream.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Math.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Functors;



FloatInputStream::FloatInputStream()
	: InputStream()
	, connectedFunctor(NULL)
	//, unreadStack()
{
}



FloatInputStream::FloatInputStream(const InputStream& connectToInputStream)
	: InputStream(connectToInputStream)
	, connectedFunctor(NULL)
	//, unreadStack()
{
}



FloatInputStream::FloatInputStream(const Functor& connectToGetterFunctor)
	: InputStream()
	, connectedFunctor(connectToGetterFunctor.clone())
	//, unreadStack()
{
}



FloatInputStream::FloatInputStream(const float* value)
	: InputStream()
	, connectedFunctor(new VariableFunctor(value))
{
}



FloatInputStream::FloatInputStream(float value)
	: InputStream()
	, connectedFunctor(new ValueGetterFunctor<float>(value))
{
}



int FloatInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
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



bool FloatInputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
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



bool FloatInputStream::read(bool& destination, double timeoutSeconds) const
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



bool FloatInputStream::read(int8& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<int8>(round<int32>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool FloatInputStream::read(uint8& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<uint8>(round<int32>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool FloatInputStream::read(void*& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = reinterpret_cast<void*>(round<int32>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool FloatInputStream::read(int16& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<int16>(round<int32>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool FloatInputStream::read(uint16& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<uint16>(round<int32>(value));
		return true;
	}
	else
	{
		return false;
	}
}



bool FloatInputStream::read(int32& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = round<int32>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool FloatInputStream::read(uint32& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = round<uint32>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool FloatInputStream::read(int64& destination, double timeoutSeconds) const
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



bool FloatInputStream::read(uint64& destination, double timeoutSeconds) const
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



bool FloatInputStream::read(float& destination, double timeoutSeconds) const
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



bool FloatInputStream::read(double& destination, double timeoutSeconds) const
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



bool FloatInputStream::read(long double& destination, double timeoutSeconds) const
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



bool FloatInputStream::read(String& destination, double timeoutSeconds) const
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
void FloatInputStream::unreadBinary(const void* source, int byteCount) const
{
}



void FloatInputStream::unread(bool source) const
{
	unread(static_cast<InputType>(source));
}



void FloatInputStream::unread(const void* source) const
{
	unread(reinterpret_cast<InputType>(source));
}



void FloatInputStream::unread(int8 source) const
{
	unread(static_cast<InputType>(source));
}



void FloatInputStream::unread(uint8 source) const
{
	unread(static_cast<InputType>(source));
}



void FloatInputStream::unread(int16 source) const
{
	unread(static_cast<InputType>(source));
}



void FloatInputStream::unread(uint16 source) const
{
	unread(static_cast<InputType>(source));
}


void FloatInputStream::unread(int32 source) const
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



void FloatInputStream::unread(uint32 source) const
{
	unread(static_cast<InputType>(source));
}



void FloatInputStream::unread(int64 source) const
{
	unread(static_cast<InputType>(source));
}



void FloatInputStream::unread(uint64 source) const
{
	unread(static_cast<InputType>(source));
}



void FloatInputStream::unread(float source) const
{
	unread(round<InputType>(source));
}



void FloatInputStream::unread(double source) const
{
	unread(round<InputType>(source));
}



void FloatInputStream::unread(long double source) const
{
	unread(round<InputType>(source));
}



void FloatInputStream::unread(const String& source) const
{
	unread(source.parse<InputType>());
}
*/


bool FloatInputStream::isConnected() const
{
	return (connectedFunctor != NULL || InputStream::isConnected() == true);
}



void FloatInputStream::connectToStream(const InputStream& newInputStream)
{
	if (connectedFunctor != NULL) disconnectFromFunctor();
	InputStream::connectToStream(newInputStream);
}



void FloatInputStream::connectToFunctor(const Functor& newFunctor)
{
	if (connectedStream != NULL) disconnectFromStream();
	connectedFunctor = newFunctor.clone();
}



void FloatInputStream::disconnectFromFunctor()
{
	connectedFunctor = NULL;
}



bool FloatInputStream::isInputAvailable() const
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
