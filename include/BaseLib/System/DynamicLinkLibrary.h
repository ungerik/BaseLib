/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_DynamicLinkLibrary_h
#define BaseLib_System_DynamicLinkLibrary_h



#include "BaseLib/Strings/String.h"



#ifdef BL_PLATFORM_WIN32		
	struct HINSTANCE__;
#endif



namespace BaseLib {
namespace System {



using BaseLib::Strings::String;



class BL_EXPORT DynamicLinkLibrary : public NonCopyable {
public:

	explicit DynamicLinkLibrary(const String& libraryFileName, const String& searchPaths = Empty(), bool unloadWhenDestroyed = false);
	~DynamicLinkLibrary();

	inline const String& getFileName() const
	{
		return fileName;
	}

	inline bool isLoaded() const
	{
		#ifdef BL_PLATFORM_WIN32		
			return dllHandle != NULL;
		#else
			return false;
		#endif
	}

	void load();
	void unload();

	void* getFunctionAddress(const String& functionName) const;

	template<typename T>
	inline T getFunctionAddress(const String& functionName) const
	{
		return static_cast<T>(getFunctionAddress(functionName));
	}

	inline bool isUnloadedWhenDestroyed() const
	{
		return unloadedWhenDestroyed;
	}

	inline void setUnloadedWhenDestroyed(bool newUnloadedWhenDestroyed)
	{
		unloadedWhenDestroyed = newUnloadedWhenDestroyed;
	}

	String getLoadedPath() const;

private:

	String fileName;
	String paths;
	#ifdef BL_PLATFORM_WIN32		
		HINSTANCE__* dllHandle;
	#endif
	bool unloadedWhenDestroyed;
}; 


} // namespace System
} // namespace BaseLib


#endif // #ifndef BaseLib_System_DynamicLinkLibrary_h
