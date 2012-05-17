/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/BoolInputStream.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/Math.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;



BoolInputStream::BoolInputStream()
	: InputStream()
	, connectedFunctor(NULL)
	//, unreadStack()
{
}



BoolInputStream::BoolInputStream(const InputStream& connectToInputStream)
	: InputStream(connectToInputStream)
	, connectedFunctor(NULL)
	//, unreadStack()
{
}



BoolInputStream::BoolInputStream(const Functor& connectToGetterFunctor)
	: InputStream()
	, connectedFunctor(connectToGetterFunctor.clone())
	//, unreadStack()
{
}



BoolInputStream::BoolInputStream(const bool* value)
	: InputStream()
	, connectedFunctor(new VariableGetterFunctor<bool>(value))
{
}



BoolInputStream::BoolInputStream(bool value)
	: InputStream()
	, connectedFunctor(new ValueGetterFunctor<bool>(value))
{
}



int BoolInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
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



bool BoolInputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
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



bool BoolInputStream::read(bool& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(int8& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(uint8& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(void*& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = reinterpret_cast<void*>(value);
		return true;
	}
	else
	{
		return false;
	}
}



bool BoolInputStream::read(int16& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(uint16& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(int32& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(uint32& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(int64& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(uint64& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(float& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(double& destination, double timeoutSeconds) const
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


bool BoolInputStream::read(long double& destination, double timeoutSeconds) const
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



bool BoolInputStream::read(String& destination, double timeoutSeconds) const
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
void BoolInputStream::unreadBinary(const void* source, int byteCount) const
{
}



void BoolInputStream::unread(bool source) const
{
	unread(static_cast<InputType>(source));
}



void BoolInputStream::unread(const void* source) const
{
	unread(reinterpret_cast<InputType>(source));
}



void BoolInputStream::unread(int8 source) const
{
	unread(static_cast<InputType>(source));
}



void BoolInputStream::unread(uint8 source) const
{
	unread(static_cast<InputType>(source));
}



void BoolInputStream::unread(int16 source) const
{
	unread(static_cast<InputType>(source));
}



void BoolInputStream::unread(uint16 source) const
{
	unread(static_cast<InputType>(source));
}


void BoolInputStream::unread(int32 source) const
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



void BoolInputStream::unread(uint32 source) const
{
	unread(static_cast<InputType>(source));
}



void BoolInputStream::unread(int64 source) const
{
	unread(static_cast<InputType>(source));
}



void BoolInputStream::unread(uint64 source) const
{
	unread(static_cast<InputType>(source));
}



void BoolInputStream::unread(float source) const
{
	unread(round<InputType>(source));
}



void BoolInputStream::unread(double source) const
{
	unread(round<InputType>(source));
}



void BoolInputStream::unread(long double source) const
{
	unread(round<InputType>(source));
}



void BoolInputStream::unread(const String& source) const
{
	unread(source.parse<InputType>());
}
*/


bool BoolInputStream::isConnected() const
{
	return (connectedFunctor != NULL || InputStream::isConnected() == true);
}



void BoolInputStream::connectToStream(const InputStream& newInputStream)
{
	if (connectedFunctor != NULL) disconnectFromFunctor();
	InputStream::connectToStream(newInputStream);
}



void BoolInputStream::connectToFunctor(const Functor& newFunctor)
{
	if (connectedStream != NULL) disconnectFromStream();
	connectedFunctor = newFunctor.clone();
}



void BoolInputStream::disconnectFromFunctor()
{
	connectedFunctor = NULL;
}



bool BoolInputStream::isInputAvailable() const
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
