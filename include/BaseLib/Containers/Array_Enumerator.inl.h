/******************************************************************************
                                  
Developed and Copyright (c) by       
                                  
Erik Unger          
                                  
Contact: erik@erikunger.com
                                  
******************************************************************************/

// Included by BaseLib/Containers/Array.h



/**
Enumerates count elements starting at index.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>& enumerator, int index, int count) const
{
	if (count != 0 &&
		checkArgumentRange(NAME_VALUE(index), 0, getCount()-1, ERROR_AT) == true &&
		checkArgumentRange(NAME_VALUE(count), 0, getCount() - index, ERROR_AT) == true)
	{
		for (int i = index; i < index + count && enumerator.stop() == false; ++i)
		{
			enumerator.enumerate(BufferPolicyType::buffer[i]);
		}
	}
}



/**
Enumerates count elements starting at index.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>* enumerator, int index, int count) const
{
	if (count != 0 &&
		checkArgumentRange(NAME_VALUE(index), 0, getCount()-1, ERROR_AT) == true &&
		checkArgumentRange(NAME_VALUE(count), 0, getCount() - index, ERROR_AT) == true &&
		checkArgumentNotNull(NAME_VALUE(enumerator), ERROR_AT) == true)
	{
		for (int i = index; i < index + count && enumerator.stop() == false; ++i)
		{
			enumerator->enumerate(BufferPolicyType::buffer[i]);
		}
	}
}



/**
Enumerates all elements.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>& enumerator) const
{
	enumerate(enumerator, 0, getCount());
}



/**
Enumerates all elements.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>* enumerator) const
{
	if (checkArgumentNotNull(NAME_VALUE(enumerator), ERROR_AT) == true)
	{
		enumerate(enumerator, 0, getCount());
	}
}



/**
Enumerates an const-iterator-range.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>& enumerator, const ConstIterator& beginRange, const ConstIterator endRange) const
{
	for (ConstIterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
	{
		enumerator.enumerate(*i);
	}
}



/**
Enumerates an const-iterator-range.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>* enumerator, const ConstIterator& beginRange, const ConstIterator endRange) const
{
	if (checkArgumentNotNull(NAME_VALUE(enumerator), ERROR_AT) == true)
	{
		for (ConstIterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator->enumerate(*i);
		}
	}
}



/**
Enumerates an iterator-range.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>& enumerator, const Iterator& beginRange, const Iterator endRange)
{
	for (Iterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
	{
		enumerator.enumerate(*i);
	}
}



/**
Enumerates an iterator-range.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>* enumerator, const Iterator& beginRange, const Iterator endRange)
{
	if (checkArgumentNotNull(NAME_VALUE(enumerator), ERROR_AT) == true)
	{
		for (Iterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator->enumerate(*i);
		}
	}
}



/**
Enumerates an const-reverse-iterator-range.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>& enumerator, const ConstReverseIterator& beginRange, const ConstReverseIterator endRange) const
{
	for (ConstIterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
	{
		enumerator.enumerate(*i);
	}
}



/**
Enumerates an const-reverse-iterator-range.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>* enumerator, const ConstReverseIterator& beginRange, const ConstReverseIterator endRange) const
{
	if (checkArgumentNotNull(NAME_VALUE(enumerator), ERROR_AT) == true)
	{
		for (ConstIterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator->enumerate(*i);
		}
	}
}



/**
Enumerates an reverse-iterator-range.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>& enumerator, const ReverseIterator& beginRange, const ReverseIterator endRange)
{
	for (Iterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
	{
		enumerator.enumerate(*i);
	}
}



/**
Enumerates an reverse-iterator-range.
The enumeration can be stoped by the enumerator.
@see Enumerator
*/
inline void enumerate(const Enumerator<T>* enumerator, const ReverseIterator& beginRange, const ReverseIterator endRange)
{
	if (checkArgumentNotNull(NAME_VALUE(enumerator), ERROR_AT) == true)
	{
		for (Iterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator->enumerate(*i);
		}
	}
}



/**
Enumerates the array using an enumerator specified as template-argument.
For example:
@code
Array<MyClass*> myArray;
myArray.enumerate<BaseLib::Functors::Deleter>(); // Deletes all elements of the array
@endcode
*/
template<template<typename> class E>
inline void enumerate() const
{
	enumerate(E<T>());
}



/**
Enumerates the array using an enumerator specified as template-argument.
*/
template<template<class, typename> class E, class C>
inline void enumerate(C& other) const
{
	enumerate(E<C, T>(other));
}



/**
Enumerates a range of the array using an enumerator specified as template-argument.
For example:
@code
Array<MyClass*> myArray;
myArray.enumerate<BaseLib::Functors::Deleter>(0, 5); // Deletes the first 5 elements of the array
@endcode
*/
template<template<typename> class E>
inline void enumerate(int position, int count) const
{
	enumerate(E<T>(), position, count);
}



/**
Enumerates a range of the array using an enumerator specified as template-argument.
*/
template<template<class, typename> class E, class C>
inline void enumerate(C& other, int position, int count) const
{
	enumerate(E<C, T>(other), position, count);
}



/**
Enumerates a range of the array using an enumerator specified as template-argument.
*/
template<template<typename> class E>
inline void enumerate(const ConstIterator& beginRange, const ConstIterator& endRange) const
{
	enumerate(E<T>(), beginRange, endRange);
}



/**
Enumerates a range of the array using an enumerator specified as template-argument.
*/
template<template<class, typename> class E, class C>
inline void enumerate(C& other, const ConstIterator& beginRange, const ConstIterator& endRange) const
{
	enumerate(E<C, T>(other), beginRange, endRange);
}



/**
Enumerates a range of the array using an enumerator specified as template-argument.
*/
template<template<typename> class E>
inline void enumerate(const Iterator& beginRange, const Iterator& endRange)
{
	enumerate(E<T>(), beginRange, endRange);
}



/**
Enumerates a range of the array using an enumerator specified as template-argument.
*/
template<template<class, typename> class E, class C>
inline void enumerate(C& other, const Iterator& beginRange, const Iterator& endRange)
{
	enumerate(E<C, T>(other), beginRange, endRange);
}



/**
Converts the array into a BaseLib::Functors::Adder.
The adder can be used to add the content of the array to an other container.
@see BaseLib::Functors::Adder
*/
inline operator Adder<Array<T>, T>()
{
	return Adder<Array<T>, T>(*this);
}



/**
Enumeration implementation that wraps an array.
@see Enumeration
*/
class Enumeration : public BaseLib::Containers::Enumeration<ValueType> {
public:

	//typedef ::BaseLib::Containers::Enumeration<ValueType>::AbstractIteratorImplementation AbstractIteratorImplementation;

	template<class WrapedIterator>
	struct ArrayIterator : BaseLib::Containers::Enumeration<ValueType>::AbstractIteratorImplementation {

		typedef typename BaseLib::Containers::Enumeration<ValueType>::AbstractIteratorImplementation BaseType; 

		explicit ArrayIterator(const WrapedIterator& newWrapedIterator)
			: BaseType()
			, wrapedIterator(newWrapedIterator)
		{
		}

		virtual typename BaseType* clone() const
		{
			return new ArrayIterator(wrapedIterator);
		}

		virtual const ValueType get() const
		{
			return *wrapedIterator;
		}

		virtual void next()
		{
			++wrapedIterator;
		}

		virtual void previous()
		{
			--wrapedIterator;
		}

		virtual bool equals(const BaseType* right) const // TODO: const ArrayIterator* ist nicht das Interface der zu überschreibenden Methode
		{
			return wrapedIterator == static_cast<const ArrayIterator*>(right)->wrapedIterator;
		}

	protected:

		WrapedIterator wrapedIterator;

	}; // class Array::Enumeration::ArrayIterator
	

	Enumeration(ArrayType* forArray, bool ownsWrappedContainer = false)
		: BaseLib::Containers::Enumeration<ValueType>(ownsWrappedContainer)
		, array(forArray)
	{
	}

	virtual ~Enumeration()
	{
		if (owner == true)
		{
			delete array;
		}
	}

	virtual bool isEmpty() const
	{
		return array->isEmpty();
	}

	virtual int getCount() const
	{
		return array->getCount();
	}

	virtual Iterator begin() const
	{
		return Iterator(new ArrayIterator<ArrayType::Iterator>(array->begin()));
	}

	virtual Iterator end() const
	{
		return Iterator(new ArrayIterator<ArrayType::Iterator>(array->end()));
	}

	virtual ReverseIterator reverseBegin() const
	{
		return ReverseIterator(new ArrayIterator<ArrayType::ReverseIterator>(array->reverseBegin()));
	}

	virtual ReverseIterator reverseEnd() const
	{
		return ReverseIterator(new ArrayIterator<ArrayType::ReverseIterator>(array->reverseEnd()));
	}

protected:
	
	ArrayType* array;

}; // class Array::Enumeration



inline BaseLib::Containers::Enumeration<T>* createEnumeration(bool ownsWrappedContainer = false)
{
	return new Enumeration(this, ownsWrappedContainer);
}



/**
Enumeration implementation that wraps a const array.
@see Enumeration
*/
class ConstEnumeration : public BaseLib::Containers::Enumeration<ValueType> {
public:

	template<class WrapedIterator>
	struct ArrayIterator : BaseLib::Containers::Enumeration<ValueType>::AbstractIteratorImplementation {

		typedef typename BaseLib::Containers::Enumeration<ValueType>::AbstractIteratorImplementation BaseType; 

		explicit ArrayIterator(const WrapedIterator& newWrapedIterator)
			: BaseType()
			, wrapedIterator(newWrapedIterator)
		{
		}

		virtual BaseType* clone() const
		{
			return new ArrayIterator(wrapedIterator);
		}

		virtual const ValueType get() const
		{
			return *wrapedIterator;
		}

		virtual void next()
		{
			++wrapedIterator;
		}

		virtual void previous()
		{
			--wrapedIterator;
		}

		virtual bool equals(const BaseType* right) const // TODO: const ArrayIterator* ist nicht das Interface der zu überschreibenden Methode
		{
			return wrapedIterator == static_cast<const ArrayIterator*>(right)->wrapedIterator;
		}

	protected:

		WrapedIterator wrapedIterator;

	}; // class Array::ConstEnumeration::ArrayIterator
	

	ConstEnumeration(const ArrayType* forArray, bool ownsWrappedContainer = false)
		: BaseLib::Containers::Enumeration<ValueType>(ownsWrappedContainer)
		, array(forArray)
	{
	}

	virtual ~ConstEnumeration()
	{
		if (owner == true)
		{
			delete array;
		}
	}

	virtual bool isEmpty() const
	{
		return array->isEmpty();
	}

	virtual int getCount() const
	{
		return array->getCount();
	}

	virtual Iterator begin() const
	{
		return Iterator(new ArrayIterator<ArrayType::ConstIterator>(array->begin()));
	}

	virtual Iterator end() const
	{
		return Iterator(new ArrayIterator<ArrayType::ConstIterator>(array->end()));
	}

	virtual ReverseIterator reverseBegin() const
	{
		return ReverseIterator(new ArrayIterator<ArrayType::ConstIterator>(array->reverseBegin()));
	}

	virtual ReverseIterator reverseEnd() const
	{
		return ReverseIterator(new ArrayIterator<ArrayType::ConstIterator>(array->reverseEnd()));
	}

protected:
	
	const ArrayType* array;

}; // class Array::ConstEnumeration



/**
Factory-function that creates an Enumeration that wraps the array.
*/
inline ::BaseLib::Containers::Enumeration<T>* createEnumeration(bool ownsWrappedContainer = false) const
{
	return new ConstEnumeration(this, ownsWrappedContainer);
}

