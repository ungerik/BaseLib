/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Win32_ApplicationStyle_h
#define BaseLib_System_Win32_ApplicationStyle_h


#include "BaseLib/Common.h"
#include "BaseLib/intern/Windows.h"



namespace BaseLib {
namespace System {
namespace Win32 {



class BL_EXPORT ApplicationStyle {
public:

	static bool isStyleUsedForNonClientAreas();
	static bool isStyleUsedForControls();
	static bool isStyleUsedForWebContent();

	static void setStyleUsedForNonClientAreas(bool useStyle);
	static void setStyleUsedForControls(bool useStyle);
	static void setStyleUsedForWebContent(bool useStyle);

private:

	ApplicationStyle();
};



} // namespace Win32
} // namespace Handles
} // namespace Ygui



#endif // #ifndef BaseLib_System_Win32_ApplicationStyle_h
