/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Deleter_h
#define BaseLib_Functors_Deleter_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class Deleter : public Enumerator<T> {
public:

	virtual void enumerate(const T& value) const
	{
		delete value;
	}

};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Deleter_h
