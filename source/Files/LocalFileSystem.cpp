/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/LocalFileSystem.h"
#include "BaseLib/Files/LocalFile.h"
#include "BaseLib/Buffers/BinaryFileBuffer.h"
#include "BaseLib/Streams/BinaryInputStream.h"
#include "BaseLib/Streams/BinaryOutputStream.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Strings/Manipulation.h"



namespace BaseLib {
namespace Files {



using namespace BaseLib::Containers;
using namespace BaseLib::Buffers;
using namespace BaseLib::Streams;
using namespace BaseLib::ErrorHandling;



BL_DEFINE_REFLECTION_CLASS(LocalFileSystem, AbstractFileSystem)
{
}



LocalFileSystem::LocalFileSystem(const String& forURI)
	: AbstractFileSystem(forURI)
	, rootDirectory(forURI)
	, lastPathContent()
	, lastPathContentEnumeration(&lastPathContent)
{
	uri.searchAndReplace('\\', '/');
	if (uri.beginsWith("file://") == false)
	{
		uri.ensureBeginsWith('/');
		uri = uri.insert("file://");
	}
	uri.ensureEndsWith('/');

	rootDirectory.searchAndReplace('\\', '/');
	if (rootDirectory.beginsWith("file://") == true)
	{
		rootDirectory.trimFrontBy(CSTRING_LENGTH("file://"));
	}
	rootDirectory.ensureEndsWith('/');
}



bool LocalFileSystem::areFilesWritable() const
{
	return false;
}



bool LocalFileSystem::areDirectoriesWriteable() const
{
	return false;
}



bool LocalFileSystem::exists(const String& path) const
{
	return LocalFile::exists(rootDirectory + currentDirectory + path);
}



bool LocalFileSystem::isDirectory(const String& path) const
{
	return LocalFile::isDirectory(rootDirectory + currentDirectory + path);
}



bool LocalFileSystem::isEmpty(const String& path) const
{
	return LocalFile::isEmpty(rootDirectory + currentDirectory + path);
}



bool LocalFileSystem::isReadable(const String& path) const
{
	return LocalFile::isReadable(rootDirectory + currentDirectory + path);
}



bool LocalFileSystem::isWriteable(const String& path) const
{
	return LocalFile::isWriteable(rootDirectory + currentDirectory + path);
}



void LocalFileSystem::setWriteable(const String& path, bool writeable) const
{
	LocalFile::setWriteable(rootDirectory + currentDirectory + path);
}



bool LocalFileSystem::isExecuteable(const String& path) const
{
	return LocalFile::isExecuteable(rootDirectory + currentDirectory + path);
}



int64 LocalFileSystem::sizeOf(const String& path) const
{
	return LocalFile::sizeOf(rootDirectory + currentDirectory + path);
}



void LocalFileSystem::setCurrentDirectory(const String& newCurrentDirectory)
{
	String newDirectory = newCurrentDirectory;
	newDirectory.searchAndReplace('\\', '/');
	newDirectory.ensureEndsWith('/');
	newDirectory.trimFront('/');
	if (newDirectory != currentDirectory)
	{
		String localDirectory = rootDirectory + newDirectory;
		if (LocalFile::exists(localDirectory) == true)
		{
			currentDirectory = newDirectory;
		}
		else
		{
			ioError("Directory '" + localDirectory + "' does not exist!" ERROR_AT);
		}
	}
}



void LocalFileSystem::enumFileNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles) const
{
	LocalFile::enumFileNames(enumerator, rootDirectory + currentDirectory + path, enumHiddenFiles, enumSystemFiles);
}



void LocalFileSystem::enumFileInfos(const Enumerator<FileInfo>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles) const
{
	LocalFile::enumFileInfos(enumerator, rootDirectory + currentDirectory + path, enumHiddenFiles, enumSystemFiles);
}



void LocalFileSystem::enumDirectoryNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenDirectories, bool enumSystemDirectories) const
{
	LocalFile::enumDirectoryNames(enumerator, rootDirectory + currentDirectory + path, enumHiddenDirectories, enumSystemDirectories);
}



void LocalFileSystem::copy(const String& sourcePath, const String& destinationPath, bool overwriteExisting) const
{
	String basePath = rootDirectory + currentDirectory;
	LocalFile::copy(basePath + sourcePath, basePath + destinationPath, overwriteExisting);
}



void LocalFileSystem::move(const String& sourcePath, const String& destinationPath, bool overwriteExisting) const
{
	String basePath = rootDirectory + currentDirectory;
	LocalFile::move(basePath + sourcePath, basePath + destinationPath, overwriteExisting);
}



void LocalFileSystem::remove(const String& path) const
{
	LocalFile::remove(rootDirectory + currentDirectory + path);
}



void LocalFileSystem::createDirectory(const String& path) const
{
	LocalFile::createDirectory(rootDirectory + currentDirectory + path);
}



InputStream* LocalFileSystem::createInputStream(const String& fileName) const
{
	BinaryFileBuffer* binaryFileBuffer = new BinaryFileBuffer(rootDirectory + currentDirectory + fileName, true, false);
	BinaryInputStream* binaryInputStream = new BinaryInputStream(*binaryFileBuffer);
	binaryInputStream->setOwnerOfConnectedObjects(true);
	return binaryInputStream;
}



OutputStream* LocalFileSystem::createOutputStream(const String& fileName) const
{
	BinaryFileBuffer* binaryFileBuffer = new BinaryFileBuffer(rootDirectory + currentDirectory + fileName, false, true);
	BinaryOutputStream* binaryOutputStream = new BinaryOutputStream(*binaryFileBuffer);
	binaryOutputStream->setOwnerOfConnectedObjects(true);
	return binaryOutputStream;
}



const int64 bufferSize = 1024*4;


int64 LocalFileSystem::writeFile(const String& path, InputStream& sourceStream, bool append, int64 bytes) const
{
	//ToDo: bytes = -1 writes until end of stream

	String fileName = rootDirectory + currentDirectory + path;

	// If file exists and we don't want to append, delete it:
	if (append == false && LocalFile::exists(fileName) == true)
	{
		LocalFile::remove(fileName);
	}

	BinaryFileBuffer fileBuffer(fileName, false, true);
	if (append == true)
	{
		fileBuffer.setCurrentPosition(fileBuffer.getSize());
	}

	BinaryInputStream binaryStream(sourceStream);

	byte buffer[bufferSize];
	int64 position = 0;
	while (position < bytes)
	{
		int bytesRead = binaryStream.readBinary(buffer, static_cast<int>(max(bytes - position, bufferSize)), readTimeoutSeconds);
		if (bytesRead > 0)
		{
			fileBuffer.writeAtCurrentPosition(buffer, bytesRead);
			position += bytesRead;
		}
		else
		{
			break;
		}
	}

	return position;
}



int64 LocalFileSystem::readFile(const String& path, OutputStream& destinationStream, int64 start, int64 bytes) const
{
	return 0;
}



} // namespace Files
} // namespace BaseLib
