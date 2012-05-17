/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_Sorting_h
#define BaseLib_Utilities_Sorting_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Utilities {



template<typename T>
inline int compare(const T& left, const T& right)
{
	if (left < right) return -1;
	if (left > right) return +1;
	return 0;
}



template<typename T>
inline int compareInverse(const T& left, const T& right)
{
	if (left > right) return -1;
	if (left < right) return +1;
	return 0;
}



template<typename V, typename A>
inline void quicksort(A& array, int length)
{
	quicksort<V, A>(array, 0, length-1);
}



template<typename V, typename A>
inline void quicksort(A& array, int firstIndex, int lastIndex)
{
	int i = firstIndex;
	int j = lastIndex;

    V x = array[(firstIndex + lastIndex) / 2];

    while (i <= j)
    {    
        while (array[i] < x) ++i; 
        while (x < array[j]) --j;
        if (i <= j)
        {
			swap(array[i], array[j]);
            ++i;
			--j;
        }
    }

    if (firstIndex < j) quicksort<V, A>(array, firstIndex, j);
    if (i < lastIndex) quicksort<V, A>(array, i, lastIndex);	
}



template<typename V, typename A>
inline void quicksort(A& array, int length, int (*compareFunc)(const V& left, const V& right))
{
	quicksort<V, A>(array, 0, length-1, compareFunc);
}



template<typename V, typename A>
inline void quicksort(A& array, int firstIndex, int lastIndex, int (*compareFunc)(const V& left, const V& right))
{
	int i = firstIndex;
	int j = lastIndex;

    V x = array[(firstIndex + lastIndex) / 2];

    while (i <= j)
    {    
        while (compareFunc(array[i], x) < 0) ++i; 
        while (compareFunc(x, array[j]) < 0) --j;
        if (i <= j)
        {
			swap(array[i], array[j]);
            ++i;
			--j;
        }
    }

    if (firstIndex < j) quicksort<V, A>(array, firstIndex, j, compareFunc);
    if (i < lastIndex) quicksort<V, A>(array, i, lastIndex, compareFunc);	
}









template<typename V, typename A>
inline void quicksortInverse(A& array, int length)
{
	quicksortInverse<V, A>(array, 0, length-1);
}



template<typename V, typename A>
inline void quicksortInverse(A& array, int firstIndex, int lastIndex)
{
	int i = firstIndex;
	int j = lastIndex;

    V x = array[(firstIndex + lastIndex) / 2];

    while (i <= j)
    {    
        while (!(array[i] < x)) ++i; 
        while (!(x < array[j])) --j;
        if (i <= j)
        {
			swap(array[i], array[j]);
            ++i;
			--j;
        }
    }

    if (firstIndex < j) quicksortInverse<V, A>(array, firstIndex, j);
    if (i < lastIndex) quicksortInverse<V, A>(array, i, lastIndex);	
}



template<typename V, typename A>
inline void quicksortInverse(A& array, int length, int (*compareFunc)(const V& left, const V& right))
{
	quicksortInverse<V, A>(array, 0, length-1, compareFunc);
}



template<typename V, typename A>
inline void quicksortInverse(A& array, int firstIndex, int lastIndex, int (*compareFunc)(const V& left, const V& right))
{
	int i = firstIndex;
	int j = lastIndex;

    V x = array[(firstIndex + lastIndex) / 2];

    while (i <= j)
    {    
        while (compareFunc(array[i], x) > 0) ++i; 
        while (compareFunc(x, array[j]) > 0) --j;
        if (i <= j)
        {
			swap(array[i], array[j]);
            ++i;
			--j;
        }
    }

    if (firstIndex < j) quicksortInverse<V, A>(array, firstIndex, j, compareFunc);
    if (i < lastIndex) quicksortInverse<V, A>(array, i, lastIndex, compareFunc);	
}



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_Sorting_h
