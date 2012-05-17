/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/ConstHandleHolder.h"
#include "BaseLib/System/NullHandle.h"
#include "BaseLib/System/HandleHolder.h"



namespace BaseLib {
namespace System {



BL_DEFINE_REFLECTION_CLASS(ConstHandleHolder, AbstractHandle)
{
}



ConstHandleHolder::ConstHandleHolder(const AbstractHandle* forHandle)
	: AbstractHandle()
	, holdedHandle(forHandle)
{
}



ConstHandleHolder::ConstHandleHolder(const AbstractHandle& other)
	: AbstractHandle()
	, holdedHandle(other.clone())
{
}



ConstHandleHolder::ConstHandleHolder(const ConstHandleHolder& other)
	: AbstractHandle()
	, holdedHandle(other.getHoldedHandle() != NULL ? other.getHoldedHandle()->clone() : NULL)
{
}



ConstHandleHolder::ConstHandleHolder(const ConstHandleHolder* other)
	: AbstractHandle()
	, holdedHandle(other != NULL && other->getHoldedHandle() != NULL ? other->getHoldedHandle()->clone() : NULL)
{
}



ConstHandleHolder::ConstHandleHolder(const HandleHolder& other)
	: AbstractHandle()
	, holdedHandle(other.getHoldedHandle() != NULL ? other.getHoldedHandle()->clone() : NULL)
{
}



ConstHandleHolder::ConstHandleHolder(const HandleHolder* other)
	: AbstractHandle()
	, holdedHandle(other != NULL && other->getHoldedHandle() != NULL ? other->getHoldedHandle()->clone() : NULL)
{
}



String ConstHandleHolder::getValueAsString() const
{
	return holdedHandle != NULL ? holdedHandle->getValueAsString() : NullHandle::INSTANCE.getValueAsString();
}



AbstractHandle* ConstHandleHolder::clone() const
{
	return new ConstHandleHolder(holdedHandle != NULL ? holdedHandle->clone() : NULL);
}



bool ConstHandleHolder::isValid() const
{
	return holdedHandle != NULL ? holdedHandle->isValid() : false;
}



} // namespace System
} // namespace BaseLib
