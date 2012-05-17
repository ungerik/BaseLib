/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_NonCopyable_h
#define BaseLib_Utilities_NonCopyable_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Utilities {



class BL_EXPORT NonCopyable {
protected:

	NonCopyable() {}
	~NonCopyable() {}

private:
	NonCopyable(const NonCopyable&);
	const NonCopyable& operator=(const NonCopyable&);
};



class NonCopyableInline {
protected:

	inline NonCopyableInline() {}
	inline ~NonCopyableInline() {}

private:
	NonCopyableInline(const NonCopyableInline&);
	const NonCopyableInline& operator=(const NonCopyableInline&);
};



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_NonCopyable_h

