/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Defines.h"
#ifdef BL_PLATFORM_WIN32



#include "BaseLib/System/Win32/InstanceHandle.h"
#include "BaseLib/System/HandleHolder.h"
#include "BaseLib/System/ConstHandleHolder.h"



namespace BaseLib {
namespace System {
namespace Win32 {



using namespace BaseLib::System;



BL_DEFINE_REFLECTION_CLASS(InstanceHandle, AbstractHandle)
{
}



InstanceHandle* InstanceHandle::castFrom(AbstractHandle* abstractHandle)
{
	if (abstractHandle != NULL)
	{
		if (abstractHandle->getClass() == CLASS)
		{
			return static_cast<InstanceHandle*>(abstractHandle);
		}
		else if (abstractHandle->getClass() == HandleHolder::CLASS)
		{
			return castFrom(static_cast<HandleHolder*>(abstractHandle)->getHoldedHandle());
		}
	}
	return NULL;
}



const InstanceHandle* InstanceHandle::castFrom(const AbstractHandle* abstractHandle)
{
	if (abstractHandle != NULL)
	{
		if (abstractHandle->getClass() == CLASS)
		{
			return static_cast<const InstanceHandle*>(abstractHandle);
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



InstanceHandle::InstanceHandle(HINSTANCE newValue)
	: AbstractHandle()
	, value(newValue)
{
}



String InstanceHandle::getValueAsString() const
{
	return String::createFrom(value);
}



AbstractHandle* InstanceHandle::clone() const
{
	return new InstanceHandle(value);
}



bool InstanceHandle::isValid() const
{
	return value != NULL;
}



} // namespace Win32
} // namespace System
} // namespace BaseLib



#endif // #ifdef BL_PLATFORM_WIN32
