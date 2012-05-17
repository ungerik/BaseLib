/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/ZipFileSystem.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Files {


using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(ZipFileSystem, AbstractFileSystem)
{
}



ZipFileSystem::ZipFileSystem(const String& forURI)
	: AbstractFileSystem(forURI)
{
}



bool ZipFileSystem::areFilesWritable() const
{
	return false;
}



bool ZipFileSystem::areDirectoriesWriteable() const
{
	return false;
}



bool ZipFileSystem::exists(const String& path) const
{
	return false;
}



bool ZipFileSystem::isDirectory(const String& path) const
{
	return false;
}



bool ZipFileSystem::isEmpty(const String& path) const
{
	return true;
}



bool ZipFileSystem::isReadable(const String& path) const
{
	return false;
}



bool ZipFileSystem::isWriteable(const String& path) const
{
	return false;
}



void ZipFileSystem::setWriteable(const String& path, bool writeable) const
{
}



bool ZipFileSystem::isExecuteable(const String& path) const
{
	return false;
}



int64 ZipFileSystem::sizeOf(const String& path) const
{
	return -1;
}



void ZipFileSystem::setCurrentDirectory(const String& newCurrentDirectory)
{
	if (newCurrentDirectory != currentDirectory)
	{
		currentDirectory = newCurrentDirectory;
	}
}



void ZipFileSystem::enumFileNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles) const
{
}



void ZipFileSystem::enumFileInfos(const Enumerator<FileInfo>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles) const
{
}



void ZipFileSystem::enumDirectoryNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenDirectories, bool enumSystemDirectories) const
{
}



void ZipFileSystem::copy(const String& sourcePath, const String& destinationPath, bool overwriteExisting) const
{
}



void ZipFileSystem::move(const String& sourcePath, const String& destinationPath, bool overwriteExisting) const
{
}



void ZipFileSystem::remove(const String& path) const
{
}



void ZipFileSystem::createDirectory(const String& path) const
{
}



InputStream* ZipFileSystem::createInputStream(const String& fileName) const
{
	return NULL;
}



OutputStream* ZipFileSystem::createOutputStream(const String& fileName) const
{
	return NULL;
}



int64 ZipFileSystem::writeFile(const String& path, InputStream& sourceStream, bool append, int64 bytes) const
{
	return 0;
}



int64 ZipFileSystem::readFile(const String& path, OutputStream& destinationStream, int64 start, int64 bytes) const
{
	return 0;
}



} // namespace Files
} // namespace BaseLib
