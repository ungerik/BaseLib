/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Finder_h
#define BaseLib_Functors_Finder_h



#include "BaseLib/Functors/Counter.h"



namespace BaseLib {
namespace Functors {



template<typename T, bool NEGATE = false>
class Finder : public Counter<T> {
public:

	using Counter<T>::counter;

	Finder<T, NEGATE>(const T& compareWith)
		: Counter<T>(-1)
		, referenceValue(compareWith)
		, found(false)
	{
	}

	virtual void enumerate(const T& value) const
	{
		++counter;
		found = (NEGATE == false) ? (value == referenceValue) : (value != referenceValue);
	}

	virtual bool stop() const
	{
		return found;
	}

	inline bool hasResult() const
	{
		return found;
	}

	inline int getIndex() const
	{
		return counter;
	}

private:

	const T& referenceValue;
	mutable bool found;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Finder_h
