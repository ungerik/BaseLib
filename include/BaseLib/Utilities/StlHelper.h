/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_StlHelper_h
#define BaseLib_Utilities_StlHelper_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Utilities {



/**
Deletes the the second member of a std::pair.
Useful in combination with std::for_each to delete every element in a map
*/
struct DeleteSecond {

	template<class P>
	inline void operator()(P& p) const
	{
		delete p.second;
	}

};



/**
Returns the first value of a std::pair.
@see getSecond()
*/
template<typename First, typename Second>
inline Second getFirst(const std::pair<First, Second>& pair)
{
	return pair.first;
}



/**
Returns the second value of a std::pair.
@see getFirst()
*/
template<typename First, typename Second>
inline Second getSecond(const std::pair<First, Second>& pair)
{
	return pair.second;
}



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_StlHelper_h

