/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_Stack_h
#define BaseLib_Containers_Stack_h



#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Containers {



/**
Array-based stack.
Stack derives from Array and extends it with the functions push(), pop() and top().
@see Array
*/
template<typename T, int CAPACITY = -1, template<typename, int> class BufferPolicy = Array_BufferPolicy_Dynamic>
class Stack : public Array<T, CAPACITY, BufferPolicy> {
public:

	typedef Array<T, CAPACITY, BufferPolicy> BaseType;

	using BaseType::remove;
	using BaseType::lastElement;
	using BaseType::getCount;

	explicit inline Stack(int newLength = 0)
  		: BaseType(newLength)
	{
	}

	explicit inline Stack(const T& value, int newLength = 1)
  		: BaseType(value, newLength)
	{
	}

	inline Stack(const T * values, int newLength)
  		: BaseType(values, newLength)
	{
	}

	/**
	Returns a reference to the top element on the stack.
	*/
	inline T& top()
	{
		return lastElement();
	}

	/**
	Returns a const-reference to the top element on the stack.
	*/
	inline const T& top() const
	{
		return lastElement();
	}

	/**
	Pushes a value on the top of the stack.
	@pop()
	*/
	inline void push(const T& value)
	{
		append(value);
	}

	/**
	Pops a value from the top of the stack and discards it.
	@see pop(T&), push()
	*/
	inline void pop()
	{
		remove(getCount()-1);
	}

	/**
	Pops a value from the top of the stack and returns it.
	@see pop(), push()
	*/
	inline void pop(T& value)
	{
		value = top();
		pop();
	}

};



} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_Stack_h