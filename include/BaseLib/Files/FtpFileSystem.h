/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Files_FtpFileSystem_h
#define BaseLib_Files_FtpFileSystem_h



#include "BaseLib/Files/AbstractFileSystem.h"



namespace BaseLib {
namespace Files {


///ToDo: Implementierung!
class BL_EXPORT FtpFileSystem : public AbstractFileSystem {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Files::FtpFileSystem, AbstractFileSystem);

	FtpFileSystem(const String& forURI);

	virtual bool areFilesWritable() const;
	virtual bool areDirectoriesWriteable() const;

	virtual bool exists(const String& path) const;
	virtual bool isDirectory(const String& path) const;
	virtual bool isEmpty(const String& path) const;
	virtual bool isReadable(const String& path) const;
	virtual bool isWriteable(const String& path) const;
	virtual void setWriteable(const String& path, bool writeable = true) const;
	virtual bool isExecuteable(const String& path) const;
	virtual int64 sizeOf(const String& path) const;

	virtual void setCurrentDirectory(const String& newCurrentDirectory);

	virtual void enumFileNames(const Enumerator<String>& enumerator, const String& path = ".", bool enumHiddenFiles = false, bool enumSystemFiles = false) const;
	virtual void enumFileInfos(const Enumerator<FileInfo>& enumerator, const String& path = ".", bool enumHiddenFiles = false, bool enumSystemFiles = false) const;
	virtual void enumDirectoryNames(const Enumerator<String>& enumerator, const String& path = ".", bool enumHiddenDirectories = false, bool enumSystemDirectories = false) const;

	virtual void copy(const String& sourcePath, const String& destinationPath, bool overwriteExisting = true) const;
	virtual void move(const String& sourcePath, const String& destinationPath, bool overwriteExisting = true) const;
	virtual void remove(const String& path) const;

	virtual void createDirectory(const String& path) const;

	virtual InputStream* createInputStream(const String& fileName) const;
	virtual OutputStream* createOutputStream(const String& fileName) const;

	///ToDo: Timeouts:
	virtual int64 writeFile(const String& path, InputStream& sourceStream, bool append = false, int64 bytes = -1) const; // bytes = -1 writes until end of stream
	virtual int64 readFile(const String& path, OutputStream& destinationStream, int64 start = 0, int64 bytes = -1) const; // bytes = -1 reads until end of file

private:


};



} // namespace Files
} // namespace BaseLib



#endif // #ifndef BaseLib_Files_FtpFileSystem_h
