/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Win32_WindowHandle_h
#define BaseLib_System_Win32_WindowHandle_h



#include "BaseLib/System/AbstractWindowHandle.h"
#include "BaseLib/intern/Windows.h"



namespace BaseLib {
namespace System {
namespace Win32 {



using BaseLib::System::AbstractWindowHandle;
using BaseLib::Strings::String;



class BL_EXPORT WindowHandle : public AbstractWindowHandle {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::System::Win32::WindowHandle, AbstractWindowHandle);

	WindowHandle(HWND newValue = 0);

	virtual String getValueAsString() const;
	virtual AbstractHandle* clone() const;
	virtual bool isValid() const;

	inline operator HWND() const
	{
		return value;
	}

	inline WindowHandle& operator =(HWND right)
	{
		value = right;
		return *this;
	}

	inline HWND getValue() const
	{
		return value;
	}

	virtual int getLeft() const;
	virtual int getTop() const;

	virtual int getWidth() const;
	virtual int getHeight() const;

	virtual int getClientWidth() const;
	virtual int getClientHeight() const;

private:

	HWND value;
};



} // namespace Win32
} // namespace Handles
} // namespace Ygui



#endif // #ifndef BaseLib_System_Win32_WindowHandle_h
