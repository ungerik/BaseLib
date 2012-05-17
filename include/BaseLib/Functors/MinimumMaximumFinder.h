/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_MinimumMaximumFinder_h
#define BaseLib_Functors_MinimumMaximumFinder_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class MinimumMaximumFinder : public Enumerator<T> {
public:

	MinimumMaximumFinder<T>(const T& startMinimum, const T& startMaximum)
		: minimum(startMinimum)
		, maximum(startMaximum)
	{
	}

	virtual void enumerate(const T& value) const
	{
		minimum = min(minimum, value);
		maximum = max(maximum, value);
	}

	inline T getMinimum() const
	{
		return minimum;
	}

	inline T getMaximum() const
	{
		return maximum;
	}

private:

	mutable T minimum;
	mutable T maximum;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_MinimumMaximumFinder_h
