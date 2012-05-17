/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/NullHandle.h"



namespace BaseLib {
namespace System {



BL_DEFINE_REFLECTION_CLASS(NullHandle, AbstractHandle)
{
}



String NullHandle::getValueAsString() const
{
	return "null";
}



AbstractHandle* NullHandle::clone() const
{
	return new NullHandle();
}



bool NullHandle::isValid() const
{
	return false;
}



} // namespace System
} // namespace BaseLib
