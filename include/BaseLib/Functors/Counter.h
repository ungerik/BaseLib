/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Counter_h
#define BaseLib_Functors_Counter_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class Counter : public Enumerator<T> {
public:

	Counter<T>(int startValue = 0)
		: counter(startValue)
	{
	}

	virtual void enumerate(const T& value) const
	{
		++counter;
	}

	inline int getCount() const
	{
		return counter;
	}

	inline void setCount(int newCount)
	{
		counter = newCount;
	}

protected:

	mutable int counter;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Counter_h
