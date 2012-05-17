/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Enumerator_h
#define BaseLib_Functors_Enumerator_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class Enumerator {
public:

	virtual ~Enumerator() {}

	virtual void enumerate(const T& value) const = 0;

	inline void operator()(const T& value) const
	{
		enumerate(value);
	}

	virtual bool stop() const
	{
		return false;
	}
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Enumerator_h
