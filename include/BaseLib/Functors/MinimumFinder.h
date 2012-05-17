/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_MinimumFinder_h
#define BaseLib_Functors_MinimumFinder_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class MinimumFinder : public Enumerator<T> {
public:

	MinimumFinder<T>(T startMinimum)
		: minimum(startMinimum)
	{
	}

	virtual void enumerate(const T& value) const
	{
		minimum = min(minimum, value);
	}

	inline T getMinimum() const
	{
		return minimum;
	}

private:

	T minimum;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_MinimumFinder_h
