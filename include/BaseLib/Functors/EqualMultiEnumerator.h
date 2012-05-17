/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_EqualMultiEnumerator_h
#define BaseLib_Functors_EqualMultiEnumerator_h



#include "BaseLib/Functors/MultiEnumerator.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class EqualMultiEnumerator : public MultiEnumerator<T> {
public:

	EqualMultiEnumerator<T>(const T& compareWith)
		: MultiEnumerator<T>()
		, referenceValue(compareWith)
	{
	}

	EqualMultiEnumerator<T>(const T& compareWith, const Enumerator<T>& enum0)
		: MultiEnumerator<T>(enum0)
		, referenceValue(compareWith)
	{
	}

	EqualMultiEnumerator<T>(const T& compareWith, const Enumerator<T>& enum0, const Enumerator<T>& enum1)
		: MultiEnumerator<T>(enum0, enum1)
		, referenceValue(compareWith)
	{
	}

	EqualMultiEnumerator<T>(const T& compareWith, const Enumerator<T>& enum0, const Enumerator<T>& enum1, const Enumerator<T>& enum2)
		: MultiEnumerator<T>(enum0, enum1, enum1, enum2)
		, referenceValue(compareWith)
	{
	}

	virtual void enumerate(const T& value) const
	{
		if (value == referenceValue)
		{
			MultiEnumerator<T>::enumerate(value);
		}
	}

private:

	const T& referenceValue;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_EqualMultiEnumerator_h
