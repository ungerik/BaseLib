/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Averager_h
#define BaseLib_Functors_Averager_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class Averager : public Enumerator<T> {
public:

	Averager<T>()
		: sum(0)
		, count(0)
	{
	}

	virtual void enumerate(const T& value) const
	{
		sum += value;
		++count;
	}

	inline T getAverage() const
	{
		return sum / count;
	}

private:

	T sum;
	int count;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Averager_h
