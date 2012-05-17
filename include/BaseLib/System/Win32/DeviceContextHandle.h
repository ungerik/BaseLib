/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Win32_DeviceContextHandle_h
#define BaseLib_System_Win32_DeviceContextHandle_h



#include "BaseLib/System/AbstractHandle.h"
#include "BaseLib/intern/Windows.h"



namespace BaseLib {
namespace System {
namespace Win32 {



using BaseLib::System::AbstractHandle;
using BaseLib::Strings::String;



class BL_EXPORT DeviceContextHandle : public AbstractHandle {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::System::Win32::DeviceContextHandle, AbstractHandle);

	static DeviceContextHandle* castFrom(AbstractHandle* abstractHandle);
	static const DeviceContextHandle* castFrom(const AbstractHandle* abstractHandle);

	DeviceContextHandle(HDC newValue = 0);

	virtual String getValueAsString() const;
	virtual AbstractHandle* clone() const;
	virtual bool isValid() const;

	inline operator HDC() const
	{
		return value;
	}

	inline DeviceContextHandle& operator =(HDC right)
	{
		value = right;
		return *this;
	}

	inline HDC getValue() const
	{
		return value;
	}

private:

	HDC value;
};



} // namespace Win32
} // namespace Handles
} // namespace Ygui



#endif // #ifndef BaseLib_System_Win32_DeviceContextHandle_h
