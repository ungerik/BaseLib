/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_h
#define BaseLib_Containers_h



/**
@page Containers

@section containers Containers

@subsection array Arrays

The most used class of this namespace is BaseLib::Containers::Array.
It can be parameterized with a template-argument for different implementation behaviours.
The default is BaseLib::Containers::Array_BufferPolicy_Dynamic which does everthing exspected from a dynamic array.
BaseLib::Containers::StaticArrayImplementation uses a static array but the logical length may vary from zero
to the length of the static array. BaseLib::Containers::FixedLengthArrayImplementation also uses a static array,
but the logical length can not be changed.
@see BaseLib::Containers::Array::canSetCount() and BaseLib::Containers::Array::canSetCapacity()

@subsection enumeration Enumerations

BaseLib::Containers::Enumeration is the abstract base-class for implementations that wrap other containers.
The wrapped container is accessible only for read access using BaseLib::Containers::Enumeration::getCount(),
BaseLib::Containers::Enumeration::begin() and BaseLib::Containers::Enumeration::end().
It can be used as function parameter-type to be able to pass any container to the function.
It's not suitable as result-type of a function. For returning values, use BaseLib::Functors::Enumerator instead.
@see BaseLib::Containers::Array::Enumeration, BaseLib::Containers::EmptyEnumeration, BaseLib::Containers::EnumerationForCArray, BaseLib::Containers::EnumerationForCString, BaseLib::Containers::EnumerationForStdContainer

@subsection enumerations Enumerators

...


@subsection missing Classes still missing

- Collection (base-class for returning containers)
- List (linked list)
- StringMap (own implementation, not using std::map)
- HashMap
- Set
- Queue
- Deque

Who want's to implement it ?

*/


#include "BaseLib/Containers/Algorithms.h"
#include "BaseLib/Containers/Array.h"
//#include "BaseLib/Containers/Collection.h"
#include "BaseLib/Containers/Combination.h"
#include "BaseLib/Containers/ConstCapacityBlockAllocationPool.h"
#include "BaseLib/Containers/Enumeration.h"
//#include "BaseLib/Containers/List.h"
//#include "BaseLib/Containers/ScopedArray.h"
#include "BaseLib/Containers/Stack.h"
#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Containers/HashMap.h"
//#include "BaseLib/Containers/Tree.h"
#include "BaseLib/Containers/Array_BufferPolicy_Dynamic.h"
#include "BaseLib/Containers/Array_BufferPolicy_ConstCount.h"
#include "BaseLib/Containers/Array_BufferPolicy_Static.h"



#endif // #ifndef BaseLib_Containers_h
