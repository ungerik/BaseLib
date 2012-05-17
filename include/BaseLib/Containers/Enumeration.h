/******************************************************************************

Developed and Copyright (c) by

Erik Unger

Contact: erik@erikunger.com

******************************************************************************/

#ifndef BaseLib_Containers_Enumeration_h
#define BaseLib_Containers_Enumeration_h



#include "BaseLib/Common.h"
#include "BaseLib/Utilities/AutoPointer.h"
#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Containers {



using BaseLib::Utilities::AutoPointer;
using BaseLib::Functors::Enumerator;



/**
Wraps any container read-only.
An Enumeration can be used as function argument-type,
to be able to pass any container as read-only parameter.
@see Array::Enumeration, EmptyEnumeration, EnumerationForCArray, EnumerationForCString, EnumerationForStdContainer
*/
template<class T>
class Enumeration {
public:

	/**
	Derived enumerator-implementations must implement this struct.
	*/
	struct AbstractIteratorImplementation {

		virtual ~AbstractIteratorImplementation() {}
		virtual AbstractIteratorImplementation* clone() const = 0;
		virtual const T get() const = 0;
		virtual void next() = 0;
		virtual void previous() = 0;
		virtual bool equals(const AbstractIteratorImplementation* right) const = 0;
	};

	class Iterator {
	public:

		inline Iterator(AbstractIteratorImplementation* newImplementation)
			: implementation(newImplementation)
		{
		}

		inline Iterator(const Iterator& other)
			: implementation(other.implementation->clone())
		{
		}

		inline Iterator& operator =(const Iterator& right)
		{
			implementation = right.implementation->clone();
		}

		inline const T operator *() const
		{
			return implementation->get();
		}

		inline const T* operator ->() const
		{
			return &implementation->get();
		}

		inline Iterator& operator ++()
		{
			implementation->next();
			return *this;
		}

		inline Iterator operator ++(int)
		{
			Iterator old = *this;
			implementation->next();
			return old;
		}

		inline Iterator& operator --()
		{
			implementation->previous();
			return *this;
		}

		inline Iterator operator --(int)
		{
			Iterator old = *this;
			implementation->previous();
			return old;
		}

		inline bool operator ==(const Iterator& right) const
		{
			return implementation->equals(right.implementation);
		}

		inline bool operator !=(const Iterator& right) const
		{
			return !operator ==(right);
		}

	private:

		#ifndef BL_COMPILER_GCC
			friend Iterator;
		#endif
		friend class Enumeration<T>;

		Iterator();

		AutoPointer<AbstractIteratorImplementation> implementation;
	};

	typedef Iterator ReverseIterator;
	typedef T ValueType;
	typedef T& ReferenceType;

	virtual ~Enumeration() {}

	virtual bool isEmpty() const = 0;
	virtual int getCount() const = 0;

	virtual Iterator begin() const = 0;
	virtual Iterator end() const = 0;
	virtual ReverseIterator reverseBegin() const = 0;
	virtual ReverseIterator reverseEnd() const = 0;

	inline void enumerate(const Enumerator<T>& enumerator, const Iterator& beginRange, const Iterator endRange) const
	{
		for (Iterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator.enumerate(*i);
		}
	}

	inline void enumerate(const Enumerator<T>* enumerator, const Iterator& beginRange, const Iterator endRange) const
	{
		for (Iterator i = beginRange; i != endRange && enumerator->stop() == false; ++i)
		{
			enumerator->enumerate(*i);
		}
	}

	inline void enumerate(const Enumerator<T>& enumerator) const
	{
		enumerate(enumerator, begin(), end());
	}

	inline void enumerate(const Enumerator<T>* enumerator) const
	{
		enumerate(enumerator, begin(), end());
	}

	template<template<typename> class E>
	inline void enumerate() const
	{
		enumerate(E<T>());
	}

	template<template<class, typename> class E, class C>
	inline void enumerate(C& other) const
	{
		enumerate(E<C, T>(other));
	}

	template<template<typename> class E>
	inline void enumerate(const Iterator& beginRange, const Iterator& endRange) const
	{
		enumerate(E<T>(), beginRange, endRange);
	}

	template<template<class, typename> class E, class C>
	inline void enumerate(C& other, const Iterator& beginRange, const Iterator& endRange) const
	{
		enumerate(E<C, T>(other), beginRange, endRange);
	}

protected:

	bool owner;

	Enumeration<T>(bool ownsWrappedContainer)
		: owner(ownsWrappedContainer)
	{
	}

};



/**
Enumeration that is always empty.
@see Enumeration, Array::Enumeration, EnumerationForCArray, EnumerationForCString, EnumerationForStdContainer
*/
template<class T>
class EmptyEnumeration : public Enumeration<T> {
public:

#ifdef BL_COMPILER_GCC
	class Iterator;
	class ReverseIterator;
	class AbstractIteratorImplementation;
#endif

	class EmptyIterator : public AbstractIteratorImplementation {
	public:

		virtual AbstractIteratorImplementation* clone() const
		{
			return new EmptyIterator();
		}

		virtual const T get() const
		{
			static const T defaultValue;
			return defaultValue;
		}

		virtual void next()
		{
		}

		virtual void previous()
		{
		}

		virtual bool equals(const AbstractIteratorImplementation* right) const
		{
			return true;
		}
	};

	EmptyEnumeration()
		: Enumeration<T>(false)
	{
	}

	virtual bool isEmpty() const
	{
		return true;
	}

	virtual int getCount() const
	{
		return 0;
	}

	virtual Iterator begin() const
	{
		return Iterator(new EmptyIterator());
	}

	virtual Iterator end() const
	{
		return Iterator(new EmptyIterator());
	}

	virtual ReverseIterator reverseBegin() const
	{
		return ReverseIterator(new EmptyIterator());
	}

	virtual ReverseIterator reverseEnd() const
	{
		return ReverseIterator(new EmptyIterator());
	}
};



/**
Enumeration that wraps a C-array.
@see Enumeration, Array::Enumeration, EmptyEnumeration, EnumerationForCString, EnumerationForStdContainer
*/
template<class T>
class EnumerationForCArray : public Enumeration<T> {
public:

#ifdef BL_COMPILER_GCC
	class Iterator;
	class ReverseIterator;
	class AbstractIteratorImplementation;
#endif

	template<int direction>
	class ArrayIterator : public AbstractIteratorImplementation {
	public:

		inline ArrayIterator(const T * forArray, int pos)
			: array(forArray)
			, position(pos)
		{
		}

		virtual AbstractIteratorImplementation* clone() const
		{
			return new ArrayIterator<direction>(array, position);
		}

		virtual const T get() const
		{
			return array[position];
		}

		virtual void next()
		{
			position += direction;
		}

		virtual void previous()
		{
			position -= direction;
		}

		virtual bool equals(const AbstractIteratorImplementation* right) const
		{
			const ArrayIterator<direction>* rightIterator = static_cast<const ArrayIterator<direction>*>(right);
			return array == rightIterator->array && position == rightIterator->position;
		}

	protected:

		const T * const array;
		int position;
	};

	EnumerationForCArray(const T * forArray, int arrayLength, bool ownsWrappedContainer = false)
		: Enumeration<T>(ownsWrappedContainer)
		, array(forArray)
		, length(arrayLength)
	{
	}

	virtual ~EnumerationForCArray()
	{
		if (owner == true)
		{
			delete[] array;
		}
	}

	virtual bool isEmpty() const
	{
		return length == 0;
	}

	virtual int getCount() const
	{
		return length;
	}

	virtual Iterator begin() const
	{
		return Iterator(new ArrayIterator<+1>(array, 0));
	}

	virtual Iterator end() const
	{
		return Iterator(new ArrayIterator<+1>(array, length));
	}

	virtual ReverseIterator reverseBegin() const
	{
		return ReverseIterator(new ArrayIterator<-1>(array, length-1));
	}

	virtual ReverseIterator reverseEnd() const
	{
		return ReverseIterator(new ArrayIterator<-1>(array, -1));
	}

protected:

	const T * const array;
	const int length;
};



template<class T>
inline Enumeration<T>* createEnumerationForCArray(const T * forArray, int arrayLength, bool ownsWrappedContainer = false)
{
	return new EnumerationForCArray<T>(forArray, arrayLength, ownsWrappedContainer);
}


/*
template<class T>
inline Enumeration<*T>* createEnumerationForCArray(T forArray)
{
	return new EnumerationForCArray(forArray, sizeof(T));
}
*/



/**
Enumeration that wraps a C-string.
@see Enumeration, Array::Enumeration, EmptyEnumeration, EnumerationForCArray, EnumerationForStdContainer
*/
template<class T = char8>
class EnumerationForCString : public EnumerationForCArray<T> {
protected:

	template<typename K>
	inline static int zeroTerminatedStringLength(const K * string)
	{
		int l = 0;
		while (string[l] != 0) ++l;
		return l;
	}

public:

	EnumerationForCString(const T * forString, bool ownsWrappedContainer = false)
		: EnumerationForCArray<T>(forString, zeroTerminatedStringLength(forString), ownsWrappedContainer)
	{
	}
};



template<class T>
inline Enumeration<T>* createEnumerationForCString(const T * forString, bool ownsWrappedContainer = false)
{
	return new EnumerationForCString<T>(forString, ownsWrappedContainer);
}



/**
Enumeration that wraps a STL container.
@see Enumeration, Array::Enumeration, EmptyEnumeration, EnumerationForCArray, EnumerationForCString
*/
template<class S>
class EnumerationForStdContainer : public Enumeration<typename S::value_type> {
public:

#ifdef BL_COMPILER_GCC
	class Iterator;
	class ReverseIterator;
	class AbstractIteratorImplementation;
#endif

	template<class I>
	class StdIterator : public AbstractIteratorImplementation {
	public:

		explicit inline StdIterator(const I& forStdIterator)
			: stdIterator(forStdIterator)
		{
		}

		virtual AbstractIteratorImplementation* clone() const
		{
			return new StdIterator<I>(stdIterator);
		}

		virtual const typename S::value_type get() const
		{
			return *stdIterator;
		}

		virtual void next()
		{
			++stdIterator;
		}

		virtual void previous()
		{
			++stdIterator;
		}

		virtual bool equals(const AbstractIteratorImplementation* right) const
		{
			const StdIterator<I>* rightIterator = static_cast<const StdIterator<I>*>(right);
			return stdIterator == rightIterator->stdIterator;
		}

	protected:

		I stdIterator;
	};

	EnumerationForStdContainer(const S& forStdContainer, bool ownsWrappedContainer = false)
		: Enumeration<typename S::value_type>(ownsWrappedContainer)
		, stdContainer(forStdContainer)
	{
	}

	virtual ~EnumerationForStdContainer()
	{
		if (owner == true)
		{
			delete stdContainer;
		}
	}

	virtual bool isEmpty() const
	{
		return stdContainer->empty();
	}

	virtual int getCount() const
	{
		return stdContainer->size();
	}

	virtual Iterator begin() const
	{
		return Iterator(new StdIterator<typename S::const_iterator>(stdContainer->begin()));
	}

	virtual Iterator end() const
	{
		return Iterator(new StdIterator<typename S::const_iterator>(stdContainer->end()));
	}

	virtual ReverseIterator reverseBegin() const
	{
		return ReverseIterator(new StdIterator<typename S::const_reverse_iterator>(stdContainer->rbegin()));
	}

	virtual ReverseIterator reverseEnd() const
	{
		return ReverseIterator(new StdIterator<typename S::const_reverse_iterator>(stdContainer->rend()));
	}

protected:

	const S* stdContainer;
};



template<class S>
inline Enumeration<typename S::value_type>* createEnumerationForStdContainer(const S& forStdContainer, bool ownsWrappedContainer = false)
{
	return new EnumerationForStdContainer<S>(forStdContainer, ownsWrappedContainer);
}



template<class T>
class AbstractIndexedEnumeration : public Enumeration<T> {
public:

    using Enumeration<T>::getCount;

#ifdef BL_COMPILER_GCC
	class Iterator;
	class ReverseIterator;
	class AbstractIteratorImplementation;
#endif

	template<int direction>
	class IndexedIterator : public AbstractIteratorImplementation {
	public:

		inline IndexedIterator(const AbstractIndexedEnumeration<T>& forEnumeration, int index)
			: enumeration(forEnumeration)
			, position(index)
		{
		}

		virtual AbstractIteratorImplementation* clone() const
		{
			return new IndexedIterator<direction>(enumeration, position);
		}

		virtual const T get() const
		{
			return enumeration.getValueAtIndex(position);
		}

		virtual void next()
		{
			position += direction;
		}

		virtual void previous()
		{
			position -= direction;
		}

		virtual bool equals(const AbstractIteratorImplementation* right) const
		{
			const IndexedIterator<direction>* rightIterator = static_cast<const IndexedIterator<direction>*>(right);
			return &enumeration == &rightIterator->enumeration && position == rightIterator->position;
		}

	protected:

		const AbstractIndexedEnumeration<T>& enumeration;
		int position;
	};

	AbstractIndexedEnumeration(bool ownsWrappedContainer = false)
		: Enumeration<T>(ownsWrappedContainer)
	{
	}

	virtual bool isEmpty() const
	{
		return getCount() == 0;
	}

	virtual const T getValueAtIndex(int index) const = 0;

	virtual Iterator begin() const
	{
		return Iterator(new IndexedIterator<+1>(*this, 0));
	}

	virtual Iterator end() const
	{
		return Iterator(new IndexedIterator<+1>(*this, getCount()));
	}

	virtual ReverseIterator reverseBegin() const
	{
		return ReverseIterator(new IndexedIterator<-1>(*this, getCount()-1));
	}

	virtual ReverseIterator reverseEnd() const
	{
		return ReverseIterator(new IndexedIterator<-1>(*this, -1));
	}

};



} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_Enumeration_h
