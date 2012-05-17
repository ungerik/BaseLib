/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/HandleHolder.h"
#include "BaseLib/System/NullHandle.h"
#include "BaseLib/System/ConstHandleHolder.h"



namespace BaseLib {
namespace System {



BL_DEFINE_REFLECTION_CLASS(HandleHolder, AbstractHandle)
{
}



HandleHolder::HandleHolder(AbstractHandle* forHandle)
	: AbstractHandle()
	, holdedHandle(forHandle)
{
}



HandleHolder::HandleHolder(const AbstractHandle& other)
	: AbstractHandle()
	, holdedHandle(other.clone())
{
}



HandleHolder::HandleHolder(const HandleHolder& other)
	: AbstractHandle()
	, holdedHandle(other.getHoldedHandle() != NULL ? other.getHoldedHandle()->clone() : NULL)
{
}



HandleHolder::HandleHolder(const HandleHolder* other)
	: AbstractHandle()
	, holdedHandle(other != NULL && other->getHoldedHandle() != NULL ? other->getHoldedHandle()->clone() : NULL)
{
}



HandleHolder::HandleHolder(const ConstHandleHolder& other)
	: AbstractHandle()
	, holdedHandle(other.getHoldedHandle() != NULL ? other.getHoldedHandle()->clone() : NULL)
{
}



HandleHolder::HandleHolder(const ConstHandleHolder* other)
	: AbstractHandle()
	, holdedHandle(other != NULL && other->getHoldedHandle() != NULL ? other->getHoldedHandle()->clone() : NULL)
{
}



HandleHolder& HandleHolder::operator=(const ConstHandleHolder& right)
{
	holdedHandle = (right.getHoldedHandle() != NULL) ? right.getHoldedHandle()->clone() : NULL;
	return *this;
}



String HandleHolder::getValueAsString() const
{
	return holdedHandle != NULL ? holdedHandle->getValueAsString() : NullHandle::INSTANCE.getValueAsString();
}



AbstractHandle* HandleHolder::clone() const
{
	return new HandleHolder(holdedHandle != NULL ? holdedHandle->clone() : NULL);
}



bool HandleHolder::isValid() const
{
	return holdedHandle != NULL ? holdedHandle->isValid() : false;
}



} // namespace System
} // namespace BaseLib
