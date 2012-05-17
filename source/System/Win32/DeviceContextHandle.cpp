/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Defines.h"
#ifdef BL_PLATFORM_WIN32



#include "BaseLib/System/Win32/DeviceContextHandle.h"
#include "BaseLib/System/HandleHolder.h"
#include "BaseLib/System/ConstHandleHolder.h"



namespace BaseLib {
namespace System {
namespace Win32 {



using namespace BaseLib::System;




BL_DEFINE_REFLECTION_CLASS(DeviceContextHandle, AbstractHandle)
{
}



DeviceContextHandle* DeviceContextHandle::castFrom(AbstractHandle* abstractHandle)
{
	if (abstractHandle != NULL)
	{
		if (abstractHandle->getClass() == CLASS)
		{
			return static_cast<DeviceContextHandle*>(abstractHandle);
		}
		else if (abstractHandle->getClass() == HandleHolder::CLASS)
		{
			return castFrom(static_cast<HandleHolder*>(abstractHandle)->getHoldedHandle());
		}
	}
	return NULL;
}



const DeviceContextHandle* DeviceContextHandle::castFrom(const AbstractHandle* abstractHandle)
{
	if (abstractHandle != NULL)
	{
		if (abstractHandle->getClass() == CLASS)
		{
			return static_cast<const DeviceContextHandle*>(abstractHandle);
		}
		else if (abstractHandle->getClass() == HandleHolder::CLASS)
		{
			return castFrom(static_cast<const HandleHolder*>(abstractHandle)->getHoldedHandle());
		}
		else if (abstractHandle->getClass() == ConstHandleHolder::CLASS)
		{
			return castFrom(static_cast<const ConstHandleHolder*>(abstractHandle)->getHoldedHandle());
		}
	}
	return NULL;
}



DeviceContextHandle::DeviceContextHandle(HDC newValue)
	: AbstractHandle()
	, value(newValue)
{
}



String DeviceContextHandle::getValueAsString() const
{
	return String::createFrom(value);
}



AbstractHandle* DeviceContextHandle::clone() const
{
	return new DeviceContextHandle(value);
}



bool DeviceContextHandle::isValid() const
{
	return value != NULL;
}



} // namespace Win32
} // namespace System
} // namespace BaseLib



#endif // #ifdef BL_PLATFORM_WIN32
