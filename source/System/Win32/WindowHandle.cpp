/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Defines.h"
#ifdef BL_PLATFORM_WIN32



#include "BaseLib/System/Win32/WindowHandle.h"
#include "BaseLib/System/HandleHolder.h"
#include "BaseLib/System/ConstHandleHolder.h"



namespace BaseLib {
namespace System {
namespace Win32 {



using namespace BaseLib::System;



BL_DEFINE_REFLECTION_CLASS(WindowHandle, AbstractWindowHandle)
{
}



WindowHandle::WindowHandle(HWND newValue)
	: AbstractWindowHandle()
	, value(newValue)
{
}



String WindowHandle::getValueAsString() const
{
	return String::createFrom(value);
}



AbstractHandle* WindowHandle::clone() const
{
	return new WindowHandle(value);
}



bool WindowHandle::isValid() const
{
	return value != NULL;
}



int WindowHandle::getLeft() const
{
	RECT rect;
	GetWindowRect(value, &rect);
	return rect.left;
}



int WindowHandle::getTop() const
{
	RECT rect;
	GetWindowRect(value, &rect);
	return rect.top;
}



int WindowHandle::getWidth() const
{
	RECT rect;
	GetWindowRect(value, &rect);
	return rect.right - rect.left;
}



int WindowHandle::getHeight() const
{
	RECT rect;
	GetWindowRect(value, &rect);
	return rect.bottom - rect.top;
}



int WindowHandle::getClientWidth() const
{
	RECT rect;
	GetClientRect(value, &rect);
	return rect.right;
}



int WindowHandle::getClientHeight() const
{
	RECT rect;
	GetClientRect(value, &rect);
	return rect.bottom;
}



} // namespace Win32
} // namespace System
} // namespace BaseLib



#endif // #ifdef BL_PLATFORM_WIN32
