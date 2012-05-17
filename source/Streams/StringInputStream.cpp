/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Streams/StringInputStream.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/Math.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Functors;



StringInputStream::StringInputStream()
	: InputStream()
	, connectedFunctor(NULL)
	, inputAvailableFunctor(NULL)
	, readBinaryMethode(INTERPRET_STRING_AS_BINARY_DATA)
	//, unreadStack()
{
}



StringInputStream::StringInputStream(const InputStream& connectToInputStream)
	: InputStream(connectToInputStream)
	, connectedFunctor(NULL)
	, inputAvailableFunctor(NULL)
	, readBinaryMethode(INTERPRET_STRING_AS_BINARY_DATA)
	//, unreadStack()
{
}



StringInputStream::StringInputStream(const Functor& connectToGetterFunctor)
	: InputStream()
	, connectedFunctor(connectToGetterFunctor.clone())
	, inputAvailableFunctor(NULL)
	, readBinaryMethode(INTERPRET_STRING_AS_BINARY_DATA)
	//, unreadStack()
{
}



StringInputStream::StringInputStream(const String* value)
	: InputStream()
	, connectedFunctor(new VariableGetterFunctor<String>(value))
	, inputAvailableFunctor(NULL)
	, readBinaryMethode(INTERPRET_STRING_AS_BINARY_DATA)
{
}



StringInputStream::StringInputStream(const String& value)
	: InputStream()
	, connectedFunctor(new ValueGetterFunctor<String>(value))
	, inputAvailableFunctor(NULL)
	, readBinaryMethode(INTERPRET_STRING_AS_BINARY_DATA)
{
}



int StringInputStream::readBinary(void* destination, int byteCount, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		switch (readBinaryMethode)
		{
			case INTERPRET_STRING_AS_BINARY_DATA:
			{
				int bytes = min(byteCount, value.getByteSize());
				memCopy(destination, value.getPointer(), bytes);
				totalBytesRead += bytes;
				return bytes;
			}

			case INTERPRET_STRING_AS_HEX_STRING:
			{
				int bytes = min(byteCount, value.getLength() / 2);
				value.hexToBinary(destination, false, 0, bytes*2);
				totalBytesRead += bytes;
				return bytes;
			}

			case INTERPRET_STRING_AS_BIN_STRING:
			{
				int bytes = min(byteCount, value.getLength() / 8);
				value.binNumberToBinary(destination, false, 0, bytes*8);
				totalBytesRead += bytes;
				return bytes;
			}

			case INTERPRET_STRING_AS_BASE64_STRING:
			{
				int bytes = min(byteCount, value.getLength() / 8 * 6);
				value.base64ToBinary(destination, 0, bytes*8/6);
				totalBytesRead += bytes;
				return bytes;
			}

			default:
				BL_ASSERT_NEVER_REACHED
				return 0;
		}
	}
	else
	{
		return 0;
	}
}



bool StringInputStream::readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		switch (readBinaryMethode)
		{
			case INTERPRET_STRING_AS_BINARY_DATA:
			{
				int bytes = min(byteCount, value.getByteSize());
				memCopy(destination, value.getPointer(), bytes);
				return true;
			}

			case INTERPRET_STRING_AS_HEX_STRING:
			{
				int bytes = min(byteCount, value.getLength() / 2);
				value.hexToBinary(destination, false, 0, bytes*2);
				return true;
			}

			case INTERPRET_STRING_AS_BIN_STRING:
			{
				int bytes = min(byteCount, value.getLength() / 8);
				value.binNumberToBinary(destination, false, 0, bytes*8);
				return true;
			}

			case INTERPRET_STRING_AS_BASE64_STRING:
			{
				int bytes = min(byteCount, value.getLength() / 8 * 6);
				value.base64ToBinary(destination, 0, bytes*8/6);
				return true;
			}

			default:
				BL_ASSERT_NEVER_REACHED
				return false;
		}
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(bool& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parseBool();
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(int8& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<int8>(value.parseInt());
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(uint8& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<uint8>(value.parseInt());
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(void*& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parsePointer();
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(int16& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<int16>(value.parseInt());
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(uint16& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = static_cast<uint16>(value.parseInt());
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(int32& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parseInt();
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(uint32& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parseUint();
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(int64& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parseInt64();
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(uint64& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parseUint64();
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(float& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parseFloat();
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(double& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parseDouble();
		return true;
	}
	else
	{
		return false;
	}
}


bool StringInputStream::read(long double& destination, double timeoutSeconds) const
{
	InputType value;
	if (read(value, timeoutSeconds) == true)
	{
		destination = value.parseLongDouble();
		return true;
	}
	else
	{
		return false;
	}
}



bool StringInputStream::read(String& destination, double timeoutSeconds) const
{
	if (connectedFunctor != NULL)
	{
		destination = (*connectedFunctor)();
		totalBytesRead += destination.getByteSize();
		return true;
	}
	else
	{
		return InputStream::read(destination, timeoutSeconds);
	}
}



/*
void StringInputStream::unreadBinary(const void* source, int byteCount) const
{
}



void StringInputStream::unread(bool source) const
{
	unread(static_cast<InputType>(source));
}



void StringInputStream::unread(const void* source) const
{
	unread(reinterpret_cast<InputType>(source));
}



void StringInputStream::unread(int8 source) const
{
	unread(static_cast<InputType>(source));
}



void StringInputStream::unread(uint8 source) const
{
	unread(static_cast<InputType>(source));
}



void StringInputStream::unread(int16 source) const
{
	unread(static_cast<InputType>(source));
}



void StringInputStream::unread(uint16 source) const
{
	unread(static_cast<InputType>(source));
}


void StringInputStream::unread(int32 source) const
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



void StringInputStream::unread(uint32 source) const
{
	unread(static_cast<InputType>(source));
}



void StringInputStream::unread(int64 source) const
{
	unread(static_cast<InputType>(source));
}



void StringInputStream::unread(uint64 source) const
{
	unread(static_cast<InputType>(source));
}



void StringInputStream::unread(float source) const
{
	unread(round<InputType>(source));
}



void StringInputStream::unread(double source) const
{
	unread(round<InputType>(source));
}



void StringInputStream::unread(long double source) const
{
	unread(round<InputType>(source));
}



void StringInputStream::unread(const String& source) const
{
	unread(source.parse<InputType>());
}
*/


bool StringInputStream::isConnected() const
{
	return (connectedFunctor != NULL || InputStream::isConnected() == true);
}



void StringInputStream::connectToStream(const InputStream& newInputStream)
{
	if (connectedFunctor != NULL) disconnectFromFunctor();
	InputStream::connectToStream(newInputStream);
}



void StringInputStream::connectToFunctor(const Functor& newFunctor)
{
	if (connectedStream != NULL) disconnectFromStream();
	connectedFunctor = newFunctor.clone();
}



void StringInputStream::disconnectFromFunctor()
{
	connectedFunctor = NULL;
}



void StringInputStream::connectToInputAvailableFunctor(const InputAvailableFunctor& newInputAvailableFunctor)
{
	inputAvailableFunctor = newInputAvailableFunctor.clone();
}



void StringInputStream::disconnectFromFunctorInputAvailable()
{
	inputAvailableFunctor = NULL;
}



bool StringInputStream::isInputAvailable() const
{
	bool result = InputStream::isInputAvailable();

	if (result == false && connectedFunctor != NULL)
	{		
		result = inputAvailableFunctor == NULL || (*inputAvailableFunctor)();
	}

	return result;
}



} // namespace Streams
} // namespace BaseLib
