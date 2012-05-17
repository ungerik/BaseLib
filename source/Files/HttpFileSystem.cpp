/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/HttpFileSystem.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Files {



using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(HttpFileSystem, AbstractFileSystem)
{
}



HttpFileSystem::HttpFileSystem(const String& forURI)
	: AbstractFileSystem(forURI)
{
}



bool HttpFileSystem::areFilesWritable() const
{
	return false;
}



bool HttpFileSystem::areDirectoriesWriteable() const
{
	return false;
}



bool HttpFileSystem::exists(const String& path) const
{
	return false;
}



bool HttpFileSystem::isDirectory(const String& path) const
{
	return false;
}



bool HttpFileSystem::isEmpty(const String& path) const
{
	return true;
}



bool HttpFileSystem::isReadable(const String& path) const
{
	return false;
}



bool HttpFileSystem::isWriteable(const String& path) const
{
	return false;
}



void HttpFileSystem::setWriteable(const String& path, bool writeable) const
{
}



bool HttpFileSystem::isExecuteable(const String& path) const
{
	return false;
}



int64 HttpFileSystem::sizeOf(const String& path) const
{
	return -1;
}



void HttpFileSystem::setCurrentDirectory(const String& newCurrentDirectory)
{
	if (newCurrentDirectory != currentDirectory)
	{
		currentDirectory = newCurrentDirectory;
	}
}



void HttpFileSystem::enumFileNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles) const
{
}



void HttpFileSystem::enumFileInfos(const Enumerator<FileInfo>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles) const
{
}



void HttpFileSystem::enumDirectoryNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenDirectories, bool enumSystemDirectories) const
{
}



void HttpFileSystem::copy(const String& sourcePath, const String& destinationPath, bool overwriteExisting) const
{
}



void HttpFileSystem::move(const String& sourcePath, const String& destinationPath, bool overwriteExisting) const
{
}



void HttpFileSystem::remove(const String& path) const
{
}



void HttpFileSystem::createDirectory(const String& path) const
{
}



InputStream* HttpFileSystem::createInputStream(const String& fileName) const
{
	return NULL;
}



OutputStream* HttpFileSystem::createOutputStream(const String& fileName) const
{
	return NULL;
}



int64 HttpFileSystem::writeFile(const String& path, InputStream& sourceStream, bool append, int64 bytes) const
{
	return 0;
}



int64 HttpFileSystem::readFile(const String& path, OutputStream& destinationStream, int64 start, int64 bytes) const
{
	return 0;
}



} // namespace Files
} // namespace BaseLib
