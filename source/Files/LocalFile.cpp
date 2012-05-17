/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/LocalFile.h"
#include "BaseLib/Buffers/BinaryFileBuffer.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/Strings/StringTokenizer.h"
#include "BaseLib/System/User.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Files {



using namespace BaseLib::Streams;
using namespace BaseLib::Buffers;
using namespace BaseLib::Containers;
using namespace BaseLib::Strings;
using namespace BaseLib::ErrorHandling;



const char8 dirSeparatorChar = '\\';

const String dirSeparatorString(dirSeparatorChar);



const String& LocalFile::dirSeparator()
{
	return dirSeparatorString;
}



String LocalFile::getBaseName(const String& path)
{
	int pos = path.findLast(dirSeparatorChar);
	if (pos != String::END)
	{
		++pos;
		if ((path.getLength() - pos) != 0)
		{
			return path.subString(pos);
		}
		else
		{
			return getBaseName(String(path.subString(0, path.getLength()-1)));
		}
	}
	else
	{
		return path.subString(0);
	}
}



String LocalFile::getDirName(const String& path)
{
	if (isDirectory(path) == true)
	{
		return path;
	}
	else
	{
		return path.subString(0, path.findLast(dirSeparatorChar));
	}
}



bool LocalFile::hasWildcards(const String& path)
{
	return path.findFirstOf("*?") != String::END;
}



bool LocalFile::exists(const String& fileName)
{
	WIN32_FIND_DATAW findData;
	HANDLE searchHandle = FindFirstFile(fileName.getChar16CString(), &findData);
	if (searchHandle != INVALID_HANDLE_VALUE)
	{
		FindClose(searchHandle);
		return true;
	}
	else
	{
		return false;
	}
}



int64 LocalFile::sizeOf(const String& fileName)
{
	WIN32_FIND_DATAW findData;
	const HANDLE searchHandle = FindFirstFile(fileName.getChar16CString(), &findData);
	if (searchHandle == INVALID_HANDLE_VALUE)
	{
		ioError(FILE_NOT_FOUND(fileName));
		return -1;
	}
	FindClose(searchHandle);

	int64 fileSize;
	reinterpret_cast<DWORD*>(&fileSize)[0] = findData.nFileSizeLow;
	reinterpret_cast<DWORD*>(&fileSize)[1] = findData.nFileSizeHigh;

	return fileSize;
}



void LocalFile::create(const String& fileName, int64 size, bool fillWithZero)
{
	BL_ASSERT(size >= 0);

	BinaryFileBuffer binaryFileBuffer(fileName, false, true);
	if (binaryFileBuffer.isOpen() == true)
	{
		if (size > 0)
		{
			binaryFileBuffer.setAllocateFilledWithZero(fillWithZero);
			binaryFileBuffer.setSize(size);
		}
	}
}



void LocalFile::createDirectory(const String& directoryName)
{
	BOOL res = CreateDirectory(directoryName.getChar16CString(), NULL);
	if (res == FALSE)
	{
		ioError(CANT_CREATE_DIRECTORY(directoryName));
	}
}



void LocalFile::removeDirectory(const String& directoryName)
{
	BOOL res = RemoveDirectory(directoryName.getChar16CString());
	if (res == FALSE)
	{
		ioError(CANT_REMOVE_DIRECTORY(directoryName));
	}
}



void LocalFile::remove(const String& fileName)
{
	BOOL res = DeleteFile(fileName.getChar16CString());
	if (res == FALSE)
	{
		ioError(CANT_REMOVE_FILE(fileName));
	}
}



void LocalFile::copy(const String& sourceFileName, const String& destinationFileName, bool overwriteExisting)
{
	BOOL res = CopyFile(sourceFileName.getChar16CString(), destinationFileName.getChar16CString(), !overwriteExisting);
	if (res == FALSE)
	{
		ioError(CANT_COPY_FILE(sourceFileName, destinationFileName));
	}
}



void LocalFile::move(const String& sourceFileName, const String& destinationFileName, bool overwriteExisting)
{
#ifdef _WIN9X
	BOOL res = MoveFile(sourceFileName.getChar16CString(), destinationFileName.getChar16CString());
#else
	DWORD flags = MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH | (overwriteExisting == true ? MOVEFILE_REPLACE_EXISTING : 0);
	BOOL res = MoveFileEx(sourceFileName.getChar16CString(), destinationFileName.getChar16CString(), flags);
#endif
	if (res == FALSE)
	{
		ioError(CANT_MOVE_FILE(sourceFileName, destinationFileName));
	}
}



bool LocalFile::isArchive(const String& fileName)
{
	DWORD fileAttributes = GetFileAttributes(fileName.getChar16CString());
	if (fileAttributes != INVALID_FILE_ATTRIBUTES)
	{
		return (fileAttributes & FILE_ATTRIBUTE_ARCHIVE) != 0;
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
		return false;
	}
}



void LocalFile::setArchive(const String& fileName, bool archive)
{
	DWORD fileAttributes = GetFileAttributes(fileName.getChar16CString());
	if (fileAttributes != INVALID_FILE_ATTRIBUTES)
	{
		bool attribute = (fileAttributes & FILE_ATTRIBUTE_ARCHIVE) != 0;
		if (attribute != archive)
		{
			if (archive == true)
			{
				fileAttributes |= FILE_ATTRIBUTE_ARCHIVE;
			}
			else
			{
				fileAttributes &= ~FILE_ATTRIBUTE_ARCHIVE;
				if (fileAttributes == 0)
				{
					fileAttributes = FILE_ATTRIBUTE_NORMAL; // SetFileAttributes() wants FILE_ATTRIBUTE_NORMAL instead of NULL
				}
			}

			BOOL res = SetFileAttributes(fileName.getChar16CString(), fileAttributes);
			if (res == FALSE)
			{
				ioError(CANT_CHANGE_FILE_ATTRIBUTES(fileName));
			}
		}
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
	}
}



bool LocalFile::isHidden(const String& fileName)
{
	DWORD fileAttributes = GetFileAttributes(fileName.getChar16CString());
	if (fileAttributes != INVALID_FILE_ATTRIBUTES)
	{
		return (fileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
		return false;
	}
}



void LocalFile::setHidden(const String& fileName, bool hidden)
{
	DWORD fileAttributes = GetFileAttributes(fileName.getChar16CString());
	if (fileAttributes != INVALID_FILE_ATTRIBUTES)
	{
		const bool attribute = (fileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
		if (attribute != hidden)
		{
			if (hidden == true)
			{
				fileAttributes |= FILE_ATTRIBUTE_HIDDEN;
			}
			else
			{
				fileAttributes &= ~FILE_ATTRIBUTE_HIDDEN;
				if (fileAttributes == 0)
				{
					fileAttributes = FILE_ATTRIBUTE_NORMAL; // SetFileAttributes() wants FILE_ATTRIBUTE_NORMAL instead of NULL
				}
			}
			
			BOOL res = SetFileAttributes(fileName.getChar16CString(), fileAttributes);
			if (res == FALSE)
			{
				ioError(CANT_CHANGE_FILE_ATTRIBUTES(fileName));
			}
		}
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
	}
}



bool LocalFile::isDirectory(const String& fileName)
{
	DWORD fileAttributes = GetFileAttributes(fileName.getChar16CString());
	if (fileAttributes != INVALID_FILE_ATTRIBUTES)
	{
		return (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}
	else
	{
		// If GetFileAttributes() doesn't work, try FindFirstFile() as workaround:
		WIN32_FIND_DATAW findData;
		const HANDLE searchHandle = FindFirstFile(fileName.getChar16CString(), &findData);
		if (searchHandle != INVALID_HANDLE_VALUE)
		{
			return (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		}
		else
		{
			ioError(FILE_NOT_FOUND(fileName));
			return false;
		}
	}
}



bool LocalFile::isEmpty(const String& fileName)
{
	BL_ASSERT(hasWildcards(fileName) == false);

	if (isDirectory(fileName) == true)
	{
		String searchPath = fileName;
		searchPath.searchAndReplace('\\', '/');
		#ifdef BL_PLATFORM_WIN32
			// Append wild-cards if not present:
			if (searchPath.findFirstOf("*?") == String::END)
			{
				searchPath.ensureEndsWith("/*");
			}
		#endif
		WIN32_FIND_DATAW findData;
		const HANDLE searchHandle = FindFirstFile(searchPath.getChar16CString(), &findData);
		if (searchHandle != INVALID_HANDLE_VALUE)
		{
			do
			{
				if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 || (String(".") != findData.cFileName && String("..") != findData.cFileName))
				{
					FindClose(searchHandle);
					return false;
				}
			}
			while (FindNextFile(searchHandle, &findData) != FALSE);

			FindClose(searchHandle);
			return true;
		}
		else
		{
			ioError(FILE_NOT_FOUND(fileName));
			return false;
		}
	}
	else
	{
		return sizeOf(fileName) == 0;
	}
}



bool LocalFile::isReadable(const String& fileName)
{
	if (exists(fileName) == true)
	{
		return true;
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
		return false;
	}
}



bool LocalFile::isWriteable(const String& fileName)
{
	const DWORD fileAttributes = GetFileAttributes(fileName.getChar16CString());
	if (fileAttributes != INVALID_FILE_ATTRIBUTES)
	{
		return (fileAttributes & FILE_ATTRIBUTE_READONLY) == 0;
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
		return false;
	}
}



void LocalFile::setWriteable(const String& fileName, bool writeable)
{
	DWORD fileAttributes = GetFileAttributes(fileName.getChar16CString());
	if (fileAttributes != INVALID_FILE_ATTRIBUTES)
	{
		const bool attribute = (fileAttributes & FILE_ATTRIBUTE_READONLY) == 0;
		if (attribute != writeable)
		{
			if (writeable == false)
			{
				fileAttributes |= FILE_ATTRIBUTE_READONLY;
			}
			else
			{
				fileAttributes &= ~FILE_ATTRIBUTE_READONLY;
				if (fileAttributes == 0)
				{
					fileAttributes = FILE_ATTRIBUTE_NORMAL; // SetFileAttributes() wants FILE_ATTRIBUTE_NORMAL instead of NULL
				}
			}
			
			BOOL res = SetFileAttributes(fileName.getChar16CString(), fileAttributes);
			if (res == FALSE)
			{
				ioError(CANT_CHANGE_FILE_ATTRIBUTES(fileName));
			}
		}
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
	}
}



bool LocalFile::isExecuteable(const String& fileName)
{
	DWORD binaryType;
	return GetBinaryType(fileName.getChar16CString(), &binaryType) != FALSE;
}



DateTime getDateTime(const SYSTEMTIME& systemTime)
{
	return DateTime(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);
}



DateTime LocalFile::getCreationTime(const String& fileName)
{
	SYSTEMTIME fileTime;
	WIN32_FIND_DATAW findData;
	const HANDLE searchHandle = FindFirstFile(fileName.getChar16CString(), &findData);
	if (searchHandle != INVALID_HANDLE_VALUE)
	{
		FileTimeToSystemTime(&findData.ftCreationTime, &fileTime);
		FindClose(searchHandle);
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
	}
	return getDateTime(fileTime);
}



DateTime LocalFile::getAccessTime(const String& fileName)
{
	SYSTEMTIME fileTime;
	WIN32_FIND_DATAW findData;
	const HANDLE searchHandle = FindFirstFile(fileName.getChar16CString(), &findData);
	if (searchHandle != INVALID_HANDLE_VALUE)
	{
		FileTimeToSystemTime(&findData.ftLastAccessTime, &fileTime);
		FindClose(searchHandle);
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
	}
	return getDateTime(fileTime);
}



DateTime LocalFile::getWriteTime(const String& fileName)
{
	SYSTEMTIME fileTime;
	WIN32_FIND_DATAW findData;
	const HANDLE searchHandle = FindFirstFile(fileName.getChar16CString(), &findData);
	if (searchHandle != INVALID_HANDLE_VALUE)
	{
		FileTimeToSystemTime(&findData.ftLastWriteTime, &fileTime);
		FindClose(searchHandle);
	}
	else
	{
		ioError(FILE_NOT_FOUND(fileName));
	}
	return getDateTime(fileTime);
}



String LocalFile::find(const String& fileName, const String& searchPaths, const String& pathDelimiters)
{
	if (exists(fileName) == true)
	{
		return fileName;
	}
	else
	{
		StringTokenizer tokenizer(searchPaths, pathDelimiters);
		while (tokenizer.hasNextToken() == true)
		{
			String searchPath = tokenizer.nextToken();
			searchPath.trimFrontAndTail('"');
			searchPath = makeEndWithDirSeparator(searchPath);
			searchPath += fileName;
			if (exists(searchPath) == true)
			{
				return searchPath;
			}
		}
		return Empty();
	}
}



String LocalFile::makeEndWithDirSeparator(const String& dirName)
{
	if (dirName.endsWith(dirSeparatorChar) == false)
	{
		if (dirName.endsWith('/') == false && dirName.endsWith('\\') == false)
		{
			return dirName + '/';
		}
		else
		{
			String result = dirName;
			result[result.getLength()-1] = '/';
			return result;
		}
	}
	else
	{
		return dirName;
	}
}



String LocalFile::getTempDirectory()
{
	char16 buffer[MAX_PATH];
	return String(buffer, GetTempPath(MAX_PATH, buffer));
}



String LocalFile::getSystemDirectory()
{
	char16 buffer[MAX_PATH];
	return String(buffer, GetSystemDirectory(buffer, MAX_PATH));
}



String LocalFile::getUserHomeDirectory()
{
	return BaseLib::System::User::getHomeDirectory();
}




/*
String LocalFile::getTempFileName()
{
	char16 buffer[256];
	return String(buffer, GetTempFileName(256, buffer));
}
*/



String LocalFile::getCurrentDirectory()
{
	char16 buffer[MAX_PATH];
	return String(buffer, GetCurrentDirectory(MAX_PATH, buffer));
}



void LocalFile::setCurrentDirectory(const String& newCurrentDirectory)
{
	BOOL result;
	if (newCurrentDirectory.getEncoding() == CHAR8_ENCODING)
	{
		result = SetCurrentDirectoryA(newCurrentDirectory.getChar8CString());
	}
	else
	{
		result = SetCurrentDirectory(newCurrentDirectory.getChar16CString());
	}

	if (result == 0)
	{
		ioError(getLastWindowsError() + ERROR_AT);
	}
}



void LocalFile::enumFileNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles)
{
	if (enumerator.stop() == false)
	{
		String searchPath = path;
		searchPath.searchAndReplace('\\', '/');
		#ifdef BL_PLATFORM_WIN32
			// Append wild-cards if not present:
			if (searchPath.findFirstOf("*?") == String::END)
			{
				searchPath.ensureEndsWith("/*");
			}
		#endif
		WIN32_FIND_DATAW findData;
		const HANDLE searchHandle = FindFirstFile(searchPath.getChar16CString(), &findData);
		if (searchHandle != INVALID_HANDLE_VALUE && enumerator.stop() == false)
		{
			String fileName = findData.cFileName;
			bool hiddenFile = (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
			bool systemFile = (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0;
			if (fileName != "." &&
				fileName != ".." &&
				(enumSystemFiles == true || systemFile == false) &&
				(enumHiddenFiles == true || hiddenFile == false))
			{
				enumerator.enumerate(fileName);
			}

			while (FindNextFile(searchHandle, &findData) != FALSE && enumerator.stop() == false)
			{
				fileName = findData.cFileName;
				hiddenFile = (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
				systemFile = (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0;
				if (fileName != "." &&
					fileName != ".." &&
					(enumSystemFiles == true || systemFile == false) &&
					(enumHiddenFiles == true || hiddenFile == false))
				{
					enumerator.enumerate(fileName);
				}
			}

			FindClose(searchHandle);
		}
		else
		{
			ioError(FILE_NOT_FOUND(path));
		}
	}
}



void LocalFile::enumFileInfos(const Enumerator<FileInfo>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles)
{
	if (enumerator.stop() == false)
	{
		String searchPath = path;
		searchPath.searchAndReplace('\\', '/');
		#ifdef BL_PLATFORM_WIN32
			// Append wild-cards if not present:
			if (searchPath.findFirstOf("*?") == String::END)
			{
				searchPath.ensureEndsWith("/*");
			}
		#endif
		WIN32_FIND_DATAW findData;
		const HANDLE searchHandle = FindFirstFile(searchPath.getChar16CString(), &findData);
		if (searchHandle != INVALID_HANDLE_VALUE && enumerator.stop() == false)
		{
			FileInfo fileInfo;
			String fileName = findData.cFileName;
			bool hiddenFile = (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
			bool systemFile = (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0;
			if (fileName != "." &&
				fileName != ".." &&
				(enumSystemFiles == true || systemFile == false) &&
				(enumHiddenFiles == true || hiddenFile == false))
			{
				fileInfo.name = fileName;
				fileInfo.size = findData.nFileSizeLow;
				fileInfo.size |= (int64)findData.nFileSizeHigh << 32;
				fileInfo.archive = (findData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) != 0;
				fileInfo.hidden = (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
				fileInfo.directory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
				fileInfo.readable = true;
				fileInfo.writeable = (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) == 0;
				FileTimeToSystemTime(&findData.ftCreationTime, (LPSYSTEMTIME)&fileInfo.creationTime);
				FileTimeToSystemTime(&findData.ftLastAccessTime, (LPSYSTEMTIME)&fileInfo.accessTime);
				FileTimeToSystemTime(&findData.ftLastWriteTime, (LPSYSTEMTIME)&fileInfo.writeTime);

				enumerator.enumerate(fileInfo);
			}

			while (FindNextFile(searchHandle, &findData) != FALSE && enumerator.stop() == false)
			{
				fileName = findData.cFileName;
				hiddenFile = (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
				systemFile = (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0;
				if (fileName != "." &&
					fileName != ".." &&
					(enumSystemFiles == true || systemFile == false) &&
					(enumHiddenFiles == true || hiddenFile == false))
				{
					fileInfo.name = fileName;
					fileInfo.size = findData.nFileSizeLow;
					fileInfo.size |= (int64)findData.nFileSizeHigh << 32;
					fileInfo.archive = (findData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) != 0;
					fileInfo.hidden = (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
					fileInfo.directory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
					fileInfo.readable = true;
					fileInfo.writeable = (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) == 0;
					FileTimeToSystemTime(&findData.ftCreationTime, (LPSYSTEMTIME)&fileInfo.creationTime);
					FileTimeToSystemTime(&findData.ftLastAccessTime, (LPSYSTEMTIME)&fileInfo.accessTime);
					FileTimeToSystemTime(&findData.ftLastWriteTime, (LPSYSTEMTIME)&fileInfo.writeTime);

					enumerator.enumerate(fileInfo);
				}
			}

			FindClose(searchHandle);
		}
		else
		{
			ioError(FILE_NOT_FOUND(path));
		}
	}
}



void LocalFile::enumDirectoryNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenDirectories, bool enumSystemDirectories)
{
	if (enumerator.stop() == false)
	{
		String searchPath = path;
		searchPath.searchAndReplace('\\', '/');
		#ifdef BL_PLATFORM_WIN32
			// Append wild-cards if not present:
			if (searchPath.findFirstOf("*?") == String::END)
			{
				searchPath.ensureEndsWith("/*");
			}
		#endif
		WIN32_FIND_DATAW findData;
		const HANDLE searchHandle = FindFirstFile(searchPath.getChar16CString(), &findData);
		if (searchHandle != INVALID_HANDLE_VALUE && enumerator.stop() == false)
		{
			String fileName = findData.cFileName;
			bool hiddenDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
			bool systemDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0;
			bool directory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
			if (directory == true &&
				fileName != "." &&
				fileName != ".." &&
				(enumSystemDirectories == true || systemDirectory == false) &&
				(enumHiddenDirectories == true || hiddenDirectory == false))
			{
				enumerator.enumerate(fileName);
			}

			while (FindNextFile(searchHandle, &findData) != FALSE && enumerator.stop() == false)
			{
				fileName = findData.cFileName;
				hiddenDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
				systemDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0;
				directory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
				if (directory == true &&
					fileName != "." &&
					fileName != ".." &&
					(enumSystemDirectories == true || systemDirectory == false) &&
					(enumHiddenDirectories == true || hiddenDirectory == false))
				{
					enumerator.enumerate(fileName);
				}
			}

			FindClose(searchHandle);
		}
		else
		{
			ioError(FILE_NOT_FOUND(path));
		}
	}
}



} // namespace Files
} // namespace BaseLib
