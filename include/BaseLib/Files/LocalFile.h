/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Files_LocalFile_h
#define BaseLib_Files_LocalFile_h



#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/intern/Windows.h"
#include "BaseLib/Files/FileInfo.h"
#include "BaseLib/Containers/Array.h"
#include "BaseLib/Files/AbstractPath.h"
#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Files {



using BaseLib::Strings::String;
using BaseLib::Containers::Array;
using BaseLib::Functors::Enumerator;



class BL_EXPORT LocalFile {
public:

	//class BL_EXPORT Path : public AbstractPath {

	//};

	static const String& dirSeparator();

	static String getBaseName(const String& path);
	static String getDirName(const String& path);
	static bool hasWildcards(const String& path);
	static bool exists(const String& fileName);
	static int64 sizeOf(const String& fileName);
	static void create(const String& fileName, int64 size = 0, bool fillWithZero = false);
	static void createDirectory(const String& directoryName);
	static void removeDirectory(const String& directoryName);
	static void remove(const String& fileName);
	static void copy(const String& sourceFileName, const String& destinationFileName, bool overwriteExisting = true);
	static void move(const String& sourceFileName, const String& destinationFileName, bool overwriteExisting = true);
	static bool isArchive(const String& fileName);
	static void setArchive(const String& fileName, bool archive = true);
	static bool isHidden(const String& fileName);
	static void setHidden(const String& fileName, bool hidden = true);
	static bool isDirectory(const String& fileName);
	static bool isEmpty(const String& fileName);
	static bool isReadable(const String& fileName);
	static bool isWriteable(const String& fileName);
	static void setWriteable(const String& fileName, bool writeable = true);
	static bool isExecuteable(const String& fileName);
	static String getSystemDirectory();
	static String getTempDirectory();
	static String getUserHomeDirectory();
	//static String getTempFileName();
	static String getCurrentDirectory();
	static void setCurrentDirectory(const String& newCurrentDirectory);

	static String find(const String& fileName, const String& searchPaths, const String& pathDelimiters = ";");
	static String makeEndWithDirSeparator(const String& dirName);

	static inline void removeIfExists(const String& fileName)
	{
		if (LocalFile::exists(fileName) == true)
		{
			LocalFile::remove(fileName);
		}
	}

	static inline void rename(const String& sourceFileName, const String& destinationFileName)
	{
		move(sourceFileName, destinationFileName, true);
	}

	static inline int sizeOfInt(const String& fileName)
	{
		int64 largeSize = sizeOf(fileName);
		return largeSize <= INT_MAX ? static_cast<int>(largeSize) : -1;
	}

	static DateTime getCreationTime(const String& fileName);
	static DateTime getAccessTime(const String& fileName);
	static DateTime getWriteTime(const String& fileName);

	static void enumFileNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenFiles = false, bool enumSystemFiles = false);
	static void enumFileInfos(const Enumerator<FileInfo>& enumerator, const String& path, bool enumHiddenFiles = false, bool enumSystemFiles = false);
	static void enumDirectoryNames(const Enumerator<String>& enumerator, const String& path, bool enumHiddenDirectories = false, bool enumSystemDirectories = false);

private:

	LocalFile();
};



} // namespace Files
} // namespace BaseLib



#endif // #ifndef BaseLib_Files_LocalFile_h
