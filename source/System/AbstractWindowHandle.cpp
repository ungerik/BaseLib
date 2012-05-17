/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/AbstractWindowHandle.h"



namespace BaseLib {
namespace System {



BL_DEFINE_REFLECTION_CLASS(AbstractWindowHandle, AbstractHandle)
{
	registerProperty("left", &AbstractWindowHandle::getLeft);
	registerProperty("top", &AbstractWindowHandle::getTop);
	registerProperty("width", &AbstractWindowHandle::getWidth);
	registerProperty("height", &AbstractWindowHandle::getHeight);
	registerProperty("clientWidth", &AbstractWindowHandle::getClientWidth);
	registerProperty("clientHeight", &AbstractWindowHandle::getClientHeight);
}



AbstractWindowHandle::AbstractWindowHandle()
	: BaseLib::System::AbstractHandle()
{
}



} // namespace System
} // namespace BaseLib
