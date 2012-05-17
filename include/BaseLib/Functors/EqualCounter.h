/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_EqualCounter_h
#define BaseLib_Functors_EqualCounter_h



#include "BaseLib/Functors/Counter.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class EqualCounter : public Counter<T> {
public:

	using Counter<T>::counter;

	EqualCounter<T>(const T& compareWith, int startValue = 0)
		: Counter<T>(startValue)
		, referenceValue(compareWith)
	{
	}

	virtual void enumerate(const T& value) const
	{
		if (value == referenceValue)
		{
			++counter;
		}
	}

private:

	const T& referenceValue;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_EqualCounter_h
