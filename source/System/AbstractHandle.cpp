/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/AbstractHandle.h"



namespace BaseLib {
namespace System {



BL_DEFINE_REFLECTION_BASE_CLASS(BaseLib::System::AbstractHandle)
{
	registerProperty("value", &AbstractHandle::getValueAsString);
}



AbstractHandle::AbstractHandle()
	: BaseLib::Reflection::Object()
{
}



AbstractHandle::~AbstractHandle()
{
}



} // namespace System
} // namespace BaseLib
