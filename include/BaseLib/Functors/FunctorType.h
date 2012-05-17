/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_FunctorType_h
#define BaseLib_Functors_FunctorType_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Functors {



enum FunctorType {
	FUNCTION_FUNCTOR,
	METHOD_FUNCTOR,
	VARIABLE_FUNCTOR,
	VALUE_FUNCTOR,
	CUSTOM_FUNCTOR
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_FunctorType_h
