/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Buffers/BinaryFileBuffer.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Files/LocalFile.h"
#include <zlib.h>
//#include <io.h>
//#include <fcntl.h>



namespace BaseLib {
namespace Buffers {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Files;
using namespace BaseLib::Utilities;



#ifdef BL_PLATFORM_WIN32



/*
SetFilePointerEx() is not support in Win9x, so we have to emulate it with SetFilePointer():
*/
BOOL _SetFilePointerEx(HANDLE hFile, LARGE_INTEGER liDistanceToMove, PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod)
{
	LONG* lowDistance = &memoryAs<LONG>(&liDistanceToMove, 0);
	LONG* highDistance = &memoryAs<LONG>(&liDistanceToMove, sizeof(LONG));
	DWORD result = SetFilePointer(hFile, *lowDistance, highDistance, dwMoveMethod);
	if (result == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) return FALSE;
	if (lpNewFilePointer != NULL)
	{
		memoryAs<LONG>(lpNewFilePointer, 0) = result;
		memoryAs<LONG>(lpNewFilePointer, sizeof(LONG)) = *highDistance;
	}
	return TRUE;
}

#endif



BinaryFileBuffer::BinaryFileBuffer(const String& newFileName, bool read, bool write)
  : fileHandle(INVALID_HANDLE_VALUE)
  , fileName(newFileName)
  , readAllowed(read)
  , writeAllowed(write)
{
	BL_ASSERT(read == true || write == true);
	#ifdef BL_PLATFORM_WIN32
		const DWORD accessFlags = (read == true ? GENERIC_READ : 0) | (write == true ? GENERIC_WRITE : 0);
		const DWORD shareFlags = FILE_SHARE_READ | (write == false ? FILE_SHARE_WRITE : 0);
		const DWORD creationFlags = (write == true) ? OPEN_ALWAYS : OPEN_EXISTING;
		fileHandle = CreateFileW(fileName.getChar16CString(), accessFlags, shareFlags, 0, creationFlags, FILE_ATTRIBUTE_NORMAL, 0);
		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			String currentDirectory = LocalFile::getCurrentDirectory();
			ioError(CANT_OPEN_FILE(fileName));
		}
		else
		{
			size = GetFileSize(fileHandle, NULL);
		}
	#endif
}



BinaryFileBuffer::~BinaryFileBuffer()
{
	close();
}



void BinaryFileBuffer::setCurrentPosition(int64 newCurrentPosition)
{
	#if defined(BL_PLATFORM_WIN32) && defined(BL_DEBUG)
		LARGE_INTEGER pos;
		BL_ASSERT(_SetFilePointerEx(fileHandle, makeLargeInt(0), &pos, FILE_CURRENT) != FALSE);
		BL_ASSERT(makeLargeInt(currentPosition).QuadPart == pos.QuadPart);
	#endif

	if (newCurrentPosition != currentPosition)
	{
		currentPosition = newCurrentPosition;

		if (newCurrentPosition < 0)
		{
			newCurrentPosition = 0;
		}

		if (_SetFilePointerEx(fileHandle, makeLargeInt(newCurrentPosition), NULL, FILE_BEGIN) == FALSE)
		{
			ioError(CANT_SET_CURRENT_POSITION(newCurrentPosition));
		}

		#if defined(BL_PLATFORM_WIN32) && defined(BL_DEBUG)
			LARGE_INTEGER pos;
			BL_ASSERT(_SetFilePointerEx(fileHandle, makeLargeInt(0), &pos, FILE_CURRENT) != FALSE);
			BL_ASSERT(makeLargeInt(newCurrentPosition).QuadPart == pos.QuadPart);
		#endif		
	}
}



void BinaryFileBuffer::setSize(int64 newByteSize)
{
	BL_ASSERT(newByteSize >= 0);

	if (newByteSize != size)
	{

		#ifdef BL_PLATFORM_WIN32
			if (writeAllowed == false || isOpen() == false)
			{
				ioError(CANT_CHANGE_FILE(fileName));
				return;
			}

			BOOL res = TRUE;
			res &= _SetFilePointerEx(fileHandle, makeLargeInt(newByteSize), NULL, FILE_BEGIN);
			res &= SetEndOfFile(fileHandle);

			if (newByteSize > size)
			{
				if (allocateZeroFilled == true)
				{
					const int64 sizeDiff = newByteSize - size;
					const DWORD zeroBufferSize = sizeDiff > 4096 ? 4096 : static_cast<DWORD>(sizeDiff);
					BinaryMemBuffer zeroBuffer(zeroBufferSize, true);
					void* zeroBufferAddress = zeroBuffer.lock();

					_SetFilePointerEx(fileHandle, makeLargeInt(-sizeDiff), NULL, FILE_END);

					DWORD numberBytesWritten;

					if (zeroBufferSize == 4096)
					{
						for (int64 i = 0; i < sizeDiff; i += 4096)
						{
							WriteFile(fileHandle, zeroBufferAddress, 4096, &numberBytesWritten, NULL);
							SetFilePointer(fileHandle, 4096, NULL, FILE_CURRENT);
						}
						WriteFile(fileHandle, zeroBufferAddress, static_cast<DWORD>(sizeDiff % 4096), &numberBytesWritten, NULL);
					}
					else
					{
						WriteFile(fileHandle, zeroBufferAddress, zeroBufferSize, &numberBytesWritten, NULL);
					}
				}

				res &= _SetFilePointerEx(fileHandle, makeLargeInt(currentPosition), NULL, FILE_BEGIN);
				if (res == FALSE)
				{
					ioError(CANT_SET_CURRENT_POSITION(currentPosition));
					return;
				}
			}
			else
			{
				currentPosition = size;
			}
		#endif

		size = newByteSize;
	}
}



int BinaryFileBuffer::readFromPosition(int64 positionInBytes, void* destination, int byteCount) const
{
	BL_ASSERT(positionInBytes >= 0);
	BL_ASSERT(destination != NULL);

	if (byteCount == 0 || readAllowed == false || isOpen() == false) return 0;

	const int64 endOffset = positionInBytes + byteCount;
	if (endOffset > size)
	{
		byteCount = static_cast<int>(size - positionInBytes);
	}
	else if (endOffset < 0)
	{
		byteCount = -static_cast<int>(positionInBytes);
	}

	#ifdef BL_PLATFORM_WIN32
		DWORD bytesRead = 0;
		LARGE_INTEGER oldFilePointer = { 0, 0 };
		if (byteCount > 0)
		{
			LARGE_INTEGER newFilePointer = makeLargeInt(positionInBytes);
			_SetFilePointerEx(fileHandle, newFilePointer, &oldFilePointer, FILE_BEGIN);
			ReadFile(fileHandle, destination, byteCount, &bytesRead, NULL);
			_SetFilePointerEx(fileHandle, oldFilePointer, NULL, FILE_BEGIN);
			byteCount = bytesRead;
		}
		else if (byteCount < 0)
		{
			LARGE_INTEGER newFilePointer = makeLargeInt(positionInBytes+byteCount);
			_SetFilePointerEx(fileHandle, newFilePointer, &oldFilePointer, FILE_BEGIN);
			ReadFile(fileHandle, destination, -byteCount, &bytesRead, NULL);
			_SetFilePointerEx(fileHandle, oldFilePointer, NULL, FILE_BEGIN);
			byteCount = -static_cast<int>(bytesRead);
		}
		/* now readFromPosition()
		else // if (byteCount == 0)
		{
			const int64 remainingBytes = size - positionInBytes;
			if (remainingBytes <= INT_MAX)
			{
				byteCount = static_cast<int>(remainingBytes);
				LARGE_INTEGER newFilePointer = makeLargeInt(positionInBytes);
				_SetFilePointerEx(fileHandle, newFilePointer, &oldFilePointer, FILE_BEGIN);
				ReadFile(fileHandle, destination, byteCount, &bytesRead, NULL);
				_SetFilePointerEx(fileHandle, oldFilePointer, NULL, FILE_BEGIN);
				byteCount = bytesRead;
			}
			else
			{
				argumentError(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
				return 0;
			}
		}
		*/
	#endif

	return byteCount;
}



int BinaryFileBuffer::readFromCurrentPosition(void* destination, int byteCount, bool moveCurrentPos)
{
	BL_ASSERT(destination != NULL);


	if (byteCount == 0 || readAllowed == false || isOpen() == false) return 0;

	const int64 endOffset = currentPosition + byteCount;
	if (endOffset > size)
	{
		byteCount = static_cast<int>(size - currentPosition);
	}
	else if (endOffset < 0)
	{
		byteCount = -static_cast<int>(currentPosition);
	}

	#ifdef BL_PLATFORM_WIN32
		if (byteCount < 0)
		{
			_SetFilePointerEx(fileHandle, makeLargeInt(byteCount), NULL, FILE_CURRENT);
			byteCount = -byteCount;
		}
		/* now readAllFromCurrentPosition()
		else if (byteCount == 0)
		{
			const int64 remainingBytes = size - currentPosition;
			if (remainingBytes <= INT_MAX)
			{
				byteCount = static_cast<int>(remainingBytes);
			}
			else
			{
				argumentError(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
				return 0;
			}
		}
		*/

		DWORD bytesRead;
		ReadFile(fileHandle, destination, byteCount, &bytesRead, NULL);
		byteCount = bytesRead;
		if (moveCurrentPos == true)
		{
			currentPosition += byteCount;
		}
		else
		{
			SetFilePointer(fileHandle, -byteCount, 0, FILE_CURRENT);
		}
	#endif

	return byteCount;
}



void BinaryFileBuffer::moveBytesBack(int64 byteOffset)
{
	BL_ASSERT(byteOffset != 0);
	BL_ASSERT(writeAllowed == true);

	#ifdef BL_PLATFORM_WIN32
		const int64 moveBufferSize = size > CLUSTER_SIZE ? CLUSTER_SIZE : size;
		BinaryMemBuffer moveBuffer(moveBufferSize, false);
		void* moveBufferPointer = moveBuffer.lock();

		DWORD numberBytesWritten;
		DWORD numberBytesRead;

		if (moveBufferSize == CLUSTER_SIZE)
		{
			int64 remainingBytes = size % CLUSTER_SIZE;
			_SetFilePointerEx(fileHandle, makeLargeInt(-remainingBytes), NULL, FILE_END);
			ReadFile(fileHandle, moveBufferPointer, static_cast<DWORD>(remainingBytes), &numberBytesRead, NULL);
			_SetFilePointerEx(fileHandle, makeLargeInt(byteOffset-remainingBytes), NULL, FILE_END);
			WriteFile(fileHandle, moveBufferPointer, static_cast<DWORD>(remainingBytes), &numberBytesWritten, NULL);
			_SetFilePointerEx(fileHandle, makeLargeInt(-remainingBytes), NULL, FILE_CURRENT);
			BL_ASSERT(numberBytesRead == numberBytesWritten);

			for (int i = 0; i < size; i += CLUSTER_SIZE)
			{
				_SetFilePointerEx(fileHandle, makeLargeInt(-CLUSTER_SIZE), NULL, FILE_CURRENT);
				ReadFile(fileHandle, moveBufferPointer, CLUSTER_SIZE, &numberBytesRead, NULL);
				_SetFilePointerEx(fileHandle, makeLargeInt(byteOffset-CLUSTER_SIZE), NULL, FILE_CURRENT);
				WriteFile(fileHandle, moveBufferPointer, CLUSTER_SIZE, &numberBytesWritten, NULL);
				_SetFilePointerEx(fileHandle, makeLargeInt(-CLUSTER_SIZE), NULL, FILE_CURRENT);
			}
		}
		else
		{
			_SetFilePointerEx(fileHandle, makeLargeInt(-moveBufferSize), NULL, FILE_END);
			ReadFile(fileHandle, moveBufferPointer, static_cast<DWORD>(moveBufferSize), &numberBytesRead, NULL);
			_SetFilePointerEx(fileHandle, makeLargeInt(byteOffset-moveBufferSize), NULL, FILE_END);
			WriteFile(fileHandle, moveBufferPointer, static_cast<DWORD>(moveBufferSize), &numberBytesWritten, NULL);
			BL_ASSERT(numberBytesRead == numberBytesWritten);
		}

		moveBuffer.unlock(moveBufferPointer);
	#endif
	size += byteOffset;
	currentPosition += byteOffset;

	#if defined(BL_PLATFORM_WIN32) && defined(_DEBUG)
		LARGE_INTEGER currentSize;
		BL_ASSERT(GetFileSizeEx(fileHandle, &currentSize) != FALSE);
		BL_ASSERT(makeLargeInt(size).QuadPart == currentSize.QuadPart);
	#endif
}


int BinaryFileBuffer::writeAtPosition(int64 positionInBytes, const void* source, int byteCount)
{
	BL_ASSERT(source != NULL);
	if (writeAllowed == false || isOpen() == false) return 0;

	if (byteCount != 0)
	{
		if (positionInBytes < 0)
		{
			moveBytesBack(-positionInBytes);
			positionInBytes = 0;
		}

		const int64 endOffset = positionInBytes + byteCount;
		if (endOffset > size)
		{
			size = endOffset;
		}
		else if (endOffset < 0)
		{
			moveBytesBack(-endOffset);
			positionInBytes = -byteCount;
		}

		if (byteCount < 0)
		{
			byteCount = -byteCount;
			positionInBytes -= byteCount;
		}
		/*
		byteCount == 0 sollte immer bedeuten, dass keine Bytes geschrieben werden,
		und nicht dass bis zum Ende des Puffers geschrieben wird!
		else if (byteCount == 0)
		{
			const int64 remainingBytes = size - positionInBytes;
			if (remainingBytes <= INT_MAX)
			{
				byteCount = static_cast<int>(remainingBytes);
			}
			else
			{
				error(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
				return 0;
			}
		}
		*/

		#ifdef BL_PLATFORM_WIN32
			_SetFilePointerEx(fileHandle, makeLargeInt(positionInBytes), NULL, FILE_BEGIN);
			DWORD bytesWritten;
			WriteFile(fileHandle, source, byteCount, &bytesWritten, NULL);
			_SetFilePointerEx(fileHandle, makeLargeInt(currentPosition), NULL, FILE_BEGIN);
			byteCount = static_cast<int>(bytesWritten);
		#endif
	}

	return byteCount;
}



bool BinaryFileBuffer::insertAtPosition(int64 positionInBytes, int byteCount)
{
	if (writeAllowed == false || isOpen() == false) return false;
	///
	return false;
}



bool BinaryFileBuffer::removeAtPosition(int64 positionInBytes, int byteCount)
{
	if (writeAllowed == false || isOpen() == false) return false;
	///
	return false;
}



void* BinaryFileBuffer::lock(int64 byteOffset, int byteCount)
{
	const int64 endOffset = byteOffset + byteCount;
	if (endOffset > size || endOffset < 0 || byteOffset < 0)
	{
		argumentError(INVALID_POSITION_IN_BUFFER);
		return NULL;
	}

	if (byteCount < 0)
	{
		byteCount = -byteCount;
		byteOffset -= byteCount;
	}
	else if (byteCount == 0)
	{
		const int64 remainingBytes = size - byteOffset;
		if (remainingBytes <= INT_MAX)
		{
			byteCount = static_cast<int>(remainingBytes);
		}
		else
		{
			argumentError(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
			return NULL;
		}
	}
	
	void* lockBuffer = malloc(byteCount);

	#ifdef BL_PLATFORM_WIN32
		_SetFilePointerEx(fileHandle, makeLargeInt(byteOffset), NULL, FILE_BEGIN);
		DWORD bytesRead;
		ReadFile(fileHandle, lockBuffer, byteCount, &bytesRead, NULL);
		BL_ASSERT(bytesRead == byteCount);
		_SetFilePointerEx(fileHandle, makeLargeInt(currentPosition), NULL, FILE_BEGIN);
	#endif
	
	return lockBuffer;
}



const void* BinaryFileBuffer::lock(int64 byteOffset, int byteCount) const
{
	return const_cast<BinaryFileBuffer*>(this)->lock(byteOffset, byteCount);
}



void BinaryFileBuffer::unlock(void* lockPointer, int64 byteOffset, int byteCount)
{
	BL_ASSERT(lockPointer != NULL);
	BL_ASSERT(byteOffset >= 0);

	if (byteCount == 0)
	{
		const int64 remainingBytes = size - byteOffset;
		if (remainingBytes <= INT_MAX)
		{
			byteCount = static_cast<int>(remainingBytes);
		}
		else
		{
			argumentError(DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(remainingBytes, INT_MAX));
			return;
		}
	}

	writeAtPosition(byteOffset, lockPointer, byteCount);

	free(lockPointer);
}



void BinaryFileBuffer::discardLock(const void* lockPointer) const
{
	BL_ASSERT(lockPointer != NULL);
	free(const_cast<void*>(lockPointer));
}



void BinaryFileBuffer::fillWithZero()
{
	#ifdef BL_PLATFORM_WIN32
		if (writeAllowed == false || isOpen() == false)
		{
			ioError(CANT_CHANGE_FILE(fileName));
			return;
		}

		const int64 zeroBufferSize = size > CLUSTER_SIZE ? CLUSTER_SIZE : size;
		BinaryMemBuffer zeroBuffer(zeroBufferSize, true);
		void* zeroBufferAddress = zeroBuffer.lock();

		SetFilePointer(fileHandle, 0, 0, FILE_BEGIN);

		DWORD numberBytesWritten;

		if (zeroBufferSize == CLUSTER_SIZE)
		{
			for (int i = 0; i < size; i += CLUSTER_SIZE)
			{
				WriteFile(fileHandle, zeroBufferAddress, CLUSTER_SIZE, &numberBytesWritten, NULL);
				SetFilePointer(fileHandle, CLUSTER_SIZE, 0, FILE_CURRENT);
			}
			WriteFile(fileHandle, zeroBufferAddress, static_cast<DWORD>(size % CLUSTER_SIZE), &numberBytesWritten, NULL);
		}
		else
		{
			WriteFile(fileHandle, zeroBufferAddress, static_cast<DWORD>(zeroBufferSize), &numberBytesWritten, NULL);
		}

		zeroBuffer.unlock(zeroBufferAddress);
		_SetFilePointerEx(fileHandle, makeLargeInt(currentPosition), NULL, FILE_BEGIN);
	#endif	
}



void BinaryFileBuffer::flush()
{
	if (writeAllowed == true && isOpen() == true)
	{
		FlushFileBuffers(fileHandle);
	}
}



void BinaryFileBuffer::close()
{
	readAllowed = false;
	writeAllowed = false;
	currentPosition = 0;
	size = 0;
	if (isOpen() == true)
	{
		BOOL res = CloseHandle(fileHandle);
		fileHandle = INVALID_HANDLE_VALUE;
		//return (res != FALSE);
	}
	else
	{
		//return true;
	}
}



} // namespace Buffers
} // namespace BaseLib
