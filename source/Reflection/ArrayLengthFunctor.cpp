/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/


#include "BaseLib/Reflection/intern/ArrayLengthFunctor.h"
#include "BaseLib/Reflection/intern/Errors.h"



namespace BaseLib {
namespace Reflection {



//using namespace BaseLib::ErrorHandling;


/*
AbstractArrayLengthFunctor::~AbstractArrayLengthFunctor()
{
}



FixedArrayLengthFunctor FixedArrayLengthFunctor::one(1);



FixedArrayLengthFunctor::FixedArrayLengthFunctor(int newArrayLength)
	: arrayLength(newArrayLength)
{
}



bool FixedArrayLengthFunctor::isFixedArrayLength() const
{
	return true;
}



int FixedArrayLengthFunctor::getArrayLength(const void* instance) const
{
	checkArgumentNotNull(NAME_VALUE(instance));
	return arrayLength;
}



void FixedArrayLengthFunctor::setArrayLength(void* instance, int newLength)
{
	stateError(ARRAY_LENGTH_IS_READ_ONLY);
}
*/


} // namespace Reflection
} // namespace BaseLib
