/******************************************************************************
                                  
Developed and Copyright (c) by       
                                  
Erik Unger          
                                  
Contact: erik@erikunger.com
                                  
******************************************************************************/

// Included by BaseLib/Containers/Array.h



/**
Template for iterators.
@see Iterator, ConstIterator, ReverseIterator, ConstReverseIterator
*/
template<typename Ti, int direction>
class IteratorTemplate {

	template<typename, int>
	friend class IteratorTemplate;

public:
	
	typedef IteratorTemplate<Ti, direction> IteratorType;

	inline explicit IteratorTemplate(Ti* newPointer)
		: pointer(newPointer)
	{
	}
	
	inline Ti& operator *()
	{
		return *pointer;
	}

	inline Ti* operator ->()
	{
		return pointer;
	}

	inline Ti& operator *() const
	{
		return *pointer;
	}

	inline Ti* operator ->() const
	{
		return pointer;
	}

	inline IteratorType& operator ++()
	{
		pointer = offsetPointer(pointer, +(int)sizeof(Ti)*direction);
		return *this;
	}

	inline IteratorType operator ++(int) 
	{
		const IteratorType old = *this;
		pointer = offsetPointer(pointer, +(int)sizeof(Ti)*direction);
		return old;
	}

	inline IteratorType& operator --() 
	{
		pointer = offsetPointer(pointer, -(int)sizeof(Ti)*direction);
		return *this;
	}

	inline IteratorType operator --(int) 
	{
		const IteratorType old = *this;
		pointer = offsetPointer(pointer, -(int)sizeof(Ti)*direction);
		return old;
	}

	inline IteratorType& operator +=(int right)
	{
		pointer = offsetPointer(pointer, +(int)sizeof(Ti)*direction * right);
		return *this;
	}

	inline IteratorType& operator -=(int right)
	{
		pointer = offsetPointer(pointer, -(int)sizeof(Ti)*direction * right);
		return *this;
	}

	inline IteratorType operator +(int right)
	{
		return IteratorType(offsetPointer(pointer, +(int)sizeof(Ti)*direction * right));
	}

	inline IteratorType operator -(int right)
	{
		return IteratorType(offsetPointer(pointer, -(int)sizeof(Ti)*direction * right));
	}

	inline int operator -(const IteratorType& right) const
	{
		return distanceFrom(right);
	}

	inline bool operator ==(const IteratorType& right) const
	{
		return pointer == right.pointer;
	}

	inline bool operator !=(const IteratorType& right) const
	{
		return !operator ==(right);
	}

	inline bool operator <(const IteratorType& right) const
	{
		return pointer < right.pointer;
	}

	/*bool operator<(const IteratorType& right)
	{
		return pointer < right.pointer;
	}

	bool operator>(const IteratorType& right)
	{
		return pointer > right.pointer;
	}*/

	inline int distanceFrom(const IteratorType& other) const
	{
		return (ptr2int(pointer) - ptr2int(other.pointer)) / sizeof(Ti) * direction;
	}

private:

	IteratorTemplate();
	Ti* pointer;

}; // class Array::IteratorTemplate

