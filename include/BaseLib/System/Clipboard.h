/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Clipboard_h
#define BaseLib_System_Clipboard_h



#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace System {



using BaseLib::Strings::String;



class BL_EXPORT Clipboard : public StaticClass {
public:

	static bool isEmpty();
	static void makeEmpty();

	static String getText();
	static void setText(const String& newText);

};


} // namespace System
} // namespace BaseLib


#endif // #ifndef BaseLib_System_Clipboard_h
