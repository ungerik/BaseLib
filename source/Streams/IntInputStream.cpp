/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/IntInputStream.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Math.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Functors;



IntInputStream::IntInputStream()
	: InputStream()
	, connectedFunctor(NULL)
	//, unreadStack()
{
}



IntInputStream::IntInputStream(const InputStream& connectToInputStream)
	: InputStream(connectToInputStream)
	, connectedFunctor(NULL)
	//, unreadStack()
{
}



IntInputStream::IntInputStream(const Functor& connectToGetterFunctor)
	: InputStream()
	, connectedFunctor(connectToGetterFunctor.clone())
	//, unreadStack()
{
}



IntInputStream::IntInputStream(const int* value)
	: InputStream()
	, connectedFunctor(new VariableFunctor(value))
{
}



IntInputStream::IntInputStream(int value)
	: InputStream()
	, connectedFunctor(new ValueGetterFunctor<int>(value))
{
}



int IntInputStream::readBinary(void* destination, int byteCount, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
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



bool IntInputStream::readBinaryComplete(void* destination, int byteCount, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
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



bool IntInputStream::read(bool& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = value != 0;
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(int8& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = static_cast<int8>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(uint8& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = static_cast<uint8>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(void*& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = reinterpret_cast<void*>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(int16& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = static_cast<int16>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(uint16& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = static_cast<uint16>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(int32& destination, double timeout) const
{
	if (connectedFunctor != NULL)
	{
		destination = (*connectedFunctor)();
		totalBytesRead += sizeof(destination);
		return true;
	}
	else
	{
		return InputStream::read(destination, timeout);
	}
}



bool IntInputStream::read(uint32& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = static_cast<uint32>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(int64& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = value;
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(uint64& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = value;
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(float& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = static_cast<float>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(double& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = value;
		return true;
	}
	else
	{
		return false;
	}
}


bool IntInputStream::read(long double& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
	{
		destination = value;
		return true;
	}
	else
	{
		return false;
	}
}



bool IntInputStream::read(String& destination, double timeout) const
{
	InputType value;
	if (read(value, timeout) == true)
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
void IntInputStream::unreadBinary(const void* source, int byteCount) const
{
}



void IntInputStream::unread(bool source) const
{
	unread(static_cast<InputType>(source));
}



void IntInputStream::unread(const void* source) const
{
	unread(reinterpret_cast<InputType>(source));
}



void IntInputStream::unread(int8 source) const
{
	unread(static_cast<InputType>(source));
}



void IntInputStream::unread(uint8 source) const
{
	unread(static_cast<InputType>(source));
}



void IntInputStream::unread(int16 source) const
{
	unread(static_cast<InputType>(source));
}



void IntInputStream::unread(uint16 source) const
{
	unread(static_cast<InputType>(source));
}


void IntInputStream::unread(int32 source) const
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



void IntInputStream::unread(uint32 source) const
{
	unread(static_cast<InputType>(source));
}



void IntInputStream::unread(int64 source) const
{
	unread(static_cast<InputType>(source));
}



void IntInputStream::unread(uint64 source) const
{
	unread(static_cast<InputType>(source));
}



void IntInputStream::unread(float source) const
{
	unread(round<InputType>(source));
}



void IntInputStream::unread(double source) const
{
	unread(round<InputType>(source));
}



void IntInputStream::unread(long double source) const
{
	unread(round<InputType>(source));
}



void IntInputStream::unread(const String& source) const
{
	unread(source.parse<InputType>());
}
*/


bool IntInputStream::isConnected() const
{
	return (connectedFunctor != NULL || InputStream::isConnected() == true);
}



void IntInputStream::connectToStream(const InputStream& newInputStream)
{
	if (connectedFunctor != NULL) disconnectFromFunctor();
	InputStream::connectToStream(newInputStream);
}



void IntInputStream::connectToFunctor(const Functor& newFunctor)
{
	if (connectedStream != NULL) disconnectFromStream();
	connectedFunctor = newFunctor.clone();
}



void IntInputStream::disconnectFromFunctor()
{
	connectedFunctor = NULL;
}



bool IntInputStream::isInputAvailable() const
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
