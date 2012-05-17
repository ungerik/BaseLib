/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Files_AbstractFileSystem_h
#define BaseLib_Files_AbstractFileSystem_h



//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Object.h"
#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Files/FileInfo.h"



namespace BaseLib {
namespace Files {



using BaseLib::Strings::String;
using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;
using BaseLib::Functors::Enumerator;



class FileSystemTreeIterator;
class DirectoryTreeIterator;



class BL_EXPORT AbstractFileSystem : public BaseLib::Reflection::Object {
public:

	static AbstractFileSystem* createFromUri(const String& uri);

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Files::AbstractFileSystem);

	virtual ~AbstractFileSystem();

	inline String getUri() const // always ends with '/'
	{
		return uri;
	}

	virtual bool areFilesWritable() const = 0;
	virtual bool areDirectoriesWriteable() const = 0;

	virtual bool exists(const String& path) const = 0;
	virtual bool isDirectory(const String& path) const = 0;
	virtual bool isEmpty(const String& path) const = 0;
	virtual bool isReadable(const String& path) const = 0;
	virtual bool isWriteable(const String& path) const = 0;
	virtual void setWriteable(const String& path, bool writeable = true) const = 0;
	virtual bool isExecuteable(const String& path) const = 0;
	virtual int64 sizeOf(const String& path) const = 0;

	inline String getCurrentDirectory() const // never begins with '/'
	{
		return currentDirectory;
	}
	virtual void setCurrentDirectory(const String& newCurrentDirectory) = 0;

	virtual void enumFileNames(const Enumerator<String>& enumerator, const String& path = ".", bool enumHiddenFiles = false, bool enumSystemFiles = false) const = 0;
	virtual void enumFileInfos(const Enumerator<FileInfo>& enumerator, const String& path = ".", bool enumHiddenFiles = false, bool enumSystemFiles = false) const = 0;
	virtual void enumDirectoryNames(const Enumerator<String>& enumerator, const String& path = ".", bool enumHiddenDirectories = false, bool enumSystemDirectories = false) const = 0;

	virtual void copy(const String& sourcePath, const String& destinationPath, bool overwriteExisting = true) const = 0;
	virtual void move(const String& sourcePath, const String& destinationPath, bool overwriteExisting = true) const = 0;
	virtual void remove(const String& path) const = 0;

	virtual void createDirectory(const String& path) const = 0;

	inline double getReadTimeout() const
	{
		return readTimeoutSeconds;
	}
	virtual void setReadTimeoutSeconds(double newReadTimeoutSeconds);

	inline double getWriteTimeout() const
	{
		return writeTimeout;
	}
	virtual void setWriteTimeout(double newWriteTimeout);

	virtual InputStream* createInputStream(const String& fileName) const = 0;
	virtual OutputStream* createOutputStream(const String& fileName) const = 0;

	virtual int64 writeFile(const String& path, InputStream& sourceStream, bool append = false, int64 bytes = -1) const = 0; // bytes = -1 writes until end of stream
	virtual int64 readFile(const String& path, OutputStream& destinationStream, int64 start = 0, int64 bytes = -1) const = 0; // bytes = -1 reads until end of file

	/// noch nicht fertig implementiert:
	virtual void copyFrom(AbstractFileSystem* sourceFileSystem, const String& sourcePath, const String& destinationPath, bool overwriteExisting = true, int bufferSize = 1024*1024) const;

	FileSystemTreeIterator* createTreeIterator(bool enumHiddenFiles = false, bool enumSystemFiles = false);
	const FileSystemTreeIterator* createTreeIterator(bool enumHiddenFiles = false, bool enumSystemFiles = false) const;

	DirectoryTreeIterator* createDirectoryTreeIterator(bool enumHiddenDirectories = false, bool enumSystemDirectories = false);
	const DirectoryTreeIterator* createDirectoryTreeIterator(bool enumHiddenDirectories = false, bool enumSystemDirectories = false) const;

protected:

	String uri;
	String currentDirectory;
	double readTimeoutSeconds;
	double writeTimeout;

	AbstractFileSystem(const String& forURI);
};



} // namespace Files
} // namespace BaseLib



#endif // #ifndef BaseLib_Files_AbstractFileSystem_h
