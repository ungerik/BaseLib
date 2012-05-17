/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/AbstractFileSystem.h"
#include "BaseLib/Files/FileSystemTreeIterator.h"
#include "BaseLib/Files/DirectoryTreeIterator.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"
#include "BaseLib/Streams/BinaryInputStream.h"
#include "BaseLib/Streams/BinaryOutputStream.h"
#include "BaseLib/Files/LocalFileSystem.h"
#include "BaseLib/Files/FtpFileSystem.h"
#include "BaseLib/Files/HttpFileSystem.h"
#include "BaseLib/Files/ZipFileSystem.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Files {



using namespace BaseLib::Buffers;
using namespace BaseLib::Streams;
using namespace BaseLib::ErrorHandling;



AbstractFileSystem* AbstractFileSystem::createFromUri(const String& uri)
{
	if (uri.beginsWith("file://") == true)
	{
		return new LocalFileSystem(uri);
	}
	else if (uri.beginsWith("ftp://") == true)
	{
		return new FtpFileSystem(uri);
	}
	else if (uri.beginsWith("http://") == true)
	{
		return new HttpFileSystem(uri);
	}
	else if (uri.beginsWith("zip://") == true)
	{
		return new ZipFileSystem(uri);
	}
	else
	{
		argumentError("Unsupported URI: '" + uri + "' !" ERROR_AT);
		return NULL;
	}
}



BL_DEFINE_REFLECTION_BASE_CLASS(AbstractFileSystem)
{
	registerProperty("uri", &AbstractFileSystem::getUri);
	registerProperty("filesWritable", &AbstractFileSystem::areFilesWritable);
	registerProperty("directoriesWriteable", &AbstractFileSystem::areDirectoriesWriteable);
	registerProperty("currentDirectory", &AbstractFileSystem::getCurrentDirectory, &AbstractFileSystem::setCurrentDirectory);
	registerProperty("readTimeoutSeconds", &AbstractFileSystem::getReadTimeout, &AbstractFileSystem::setReadTimeoutSeconds);
	registerProperty("writeTimeout", &AbstractFileSystem::getWriteTimeout, &AbstractFileSystem::setWriteTimeout);
}



AbstractFileSystem::AbstractFileSystem(const String& forURI)
	: uri(forURI)
	, currentDirectory()
	, readTimeoutSeconds(3600)
	, writeTimeout(3600)
{
	uri.ensureEndsWith('/');
}



AbstractFileSystem::~AbstractFileSystem()
{
}



void AbstractFileSystem::setReadTimeoutSeconds(double newReadTimeoutSeconds)
{
	if (checkArgumentPositive(NAME_VALUE(newReadTimeoutSeconds)) == true)
	{
		readTimeoutSeconds = newReadTimeoutSeconds;
	}
}



void AbstractFileSystem::setWriteTimeout(double newWriteTimeout)
{
	if (checkArgumentPositive(NAME_VALUE(newWriteTimeout)) == true)
	{
		writeTimeout = newWriteTimeout;
	}
}



void AbstractFileSystem::copyFrom(AbstractFileSystem* sourceFileSystem, const String& sourcePath, const String& destinationPath, bool overwriteExisting, int bufferSize) const
{
	if (checkArgumentNotNull(NAME_VALUE(sourceFileSystem)) == true)
	{
		int64 byteCount = sourceFileSystem->sizeOf(sourcePath);

		BinaryMemBuffer buffer(bufferSize);
		BinaryInputStream inputStream(buffer);
		BinaryOutputStream outputStream(buffer);

		int64 position = 0;
		while (position < byteCount && position < bufferSize)
		{
			int64 bytesRead = sourceFileSystem->readFile(sourcePath, outputStream, position, bufferSize);
			buffer.setCurrentPosition(0);

			for (int64 bytesWritten = 0; bytesWritten < bytesRead; )
			{
				bytesWritten += writeFile(destinationPath, inputStream, true, bytesRead);
			}

			position += bytesRead;

		}
	}
}



FileSystemTreeIterator* AbstractFileSystem::createTreeIterator(bool enumHiddenFiles, bool enumSystemFiles)
{
	return new FileSystemTreeIterator(this, enumHiddenFiles, enumSystemFiles);
}



const FileSystemTreeIterator* AbstractFileSystem::createTreeIterator(bool enumHiddenFiles, bool enumSystemFiles) const
{
	return new FileSystemTreeIterator(this, enumHiddenFiles, enumSystemFiles);
}



DirectoryTreeIterator* AbstractFileSystem::createDirectoryTreeIterator(bool enumHiddenDirectories, bool enumSystemDirectories)
{
	return new DirectoryTreeIterator(this, enumHiddenDirectories, enumSystemDirectories);
}



const DirectoryTreeIterator* AbstractFileSystem::createDirectoryTreeIterator(bool enumHiddenDirectories, bool enumSystemDirectories) const
{
	return new DirectoryTreeIterator(this, enumHiddenDirectories, enumSystemDirectories);
}



} // namespace Files
} // namespace BaseLib
