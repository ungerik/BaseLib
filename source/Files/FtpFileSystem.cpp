/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/FtpFileSystem.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Files {



using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_CLASS(FtpFileSystem, AbstractFileSystem)
{
}



FtpFileSystem::FtpFileSystem(const String& forURI)
	: AbstractFileSystem(forURI)
{
}



bool FtpFileSystem::areFilesWritable() const
{
	return false;
}



bool FtpFileSystem::areDirectoriesWriteable() const
{
	return false;
}



bool FtpFileSystem::exists(const String& path) const
{
	return false;
}



bool FtpFileSystem::isDirectory(const String& path) const
{
	return false;
}



bool FtpFileSystem::isEmpty(const String& path) const
{
	return true;
}



bool FtpFileSystem::isReadable(const String& path) const
{
	return false;
}



bool FtpFileSystem::isWriteable(const String& path) const
{
	return false;
}



void FtpFileSystem::setWriteable(const String& path, bool writeable) const
{
}



bool FtpFileSystem::isExecuteable(const String& path) const
{
	return false;
}



int64 FtpFileSystem::sizeOf(const String& path) const
{
	return -1;
}



void FtpFileSystem::setCurrentDirectory(const String& newCurrentDirectory)
{
	if (newCurrentDirectory != currentDirectory)
	{
		currentDirectory = newCurrentDirectory;
	}
}



void FtpFileSystem::enumFileNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles) const
{
}



void FtpFileSystem::enumFileInfos(const Enumerator<FileInfo>& enumerator, const String& path, bool enumHiddenFiles, bool enumSystemFiles) const
{
}



void FtpFileSystem::enumDirectoryNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenDirectories, bool enumSystemDirectories) const
{
}



void FtpFileSystem::copy(const String& sourcePath, const String& destinationPath, bool overwriteExisting) const
{
}



void FtpFileSystem::move(const String& sourcePath, const String& destinationPath, bool overwriteExisting) const
{
}



void FtpFileSystem::remove(const String& path) const
{
}



void FtpFileSystem::createDirectory(const String& path) const
{
}



InputStream* FtpFileSystem::createInputStream(const String& fileName) const
{
	return NULL;
}



OutputStream* FtpFileSystem::createOutputStream(const String& fileName) const
{
	return NULL;
}



int64 FtpFileSystem::writeFile(const String& path, InputStream& sourceStream, bool append, int64 bytes) const
{
	return 0;
}



int64 FtpFileSystem::readFile(const String& path, OutputStream& destinationStream, int64 start, int64 bytes) const
{
	return 0;
}





} // namespace Files
} // namespace BaseLib
