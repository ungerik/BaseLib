/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_MaximumFinder_h
#define BaseLib_Functors_MaximumFinder_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class MaximumFinder : public Enumerator<T> {
public:

	MaximumFinder<T>(T startMaximum)
		: maximum(startMaximum)
	{
	}

	virtual void enumerate(const T& value) const
	{
		maximum = max(maximum, value);
	}

	inline T getMaximum() const
	{
		return maximum;
	}

private:

	T maximum;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_MaximumFinder_h
