/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_Array_h
#define BaseLib_Containers_Array_h



//#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Strings/String.h"
#include "BaseLib/Containers/Enumeration.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Containers/Array_BufferPolicy_Static.h"
#include "BaseLib/Containers/Array_BufferPolicy_Dynamic.h"
#include "BaseLib/Containers/Array_BufferPolicy_ConstCount.h"
#include "BaseLib/Functors/Adder.h"
#include "BaseLib/ErrorHandling/ErrorDefines.h"



namespace BaseLib {
	namespace ErrorHandling {
		template<typename T>
		bool checkArgumentPositive(const char * argumentName, T argument, const char * errorAt);

		template<typename T>
		bool checkArgumentRange(const char * argumentName, T argument, T minimum, T maximum, const char * errorAt);

		template<typename T>
		bool checkArgumentPositive(const char * argumentName, T argument, const char * errorAt);

		template<typename T>
		inline bool checkState(const BaseLib::Strings::String& stateName, const T state, const char * errorAt);

		template<typename T>
		inline bool checkStateGreater(const BaseLib::Strings::String& stateName, T state, T limit, const char * errorAt);

		bool checkArgumentNotNull(const char * argumentName, const void* argument, const char * errorAt);
	}
}


namespace BaseLib {
namespace Containers {



using namespace BaseLib::Utilities;
using namespace BaseLib::ErrorHandling;
using BaseLib::Functors::Adder;



/**
Array with templated BufferPolicyType::

@see DynamicArrayImplementation, FixedLengthArrayImplementation, StaticArrayImplementation
*/
template<typename T, int CAPACITY = -1, template<typename, int> class BufferPolicy = Array_BufferPolicy_Dynamic>
class Array : protected BufferPolicy<T, CAPACITY> {
public:

	typedef Array<T, CAPACITY, BufferPolicy> ArrayType;
	typedef BufferPolicy<T, CAPACITY> BufferPolicyType;

	friend class ArrayType;

	#include "BaseLib/Containers/Array_IteratorTemplate.inl.h"

	typedef T ValueType;
	typedef T& ReferenceType;
	typedef const T& ConstReferenceType;

	typedef IteratorTemplate<ValueType, +1> Iterator;
	typedef IteratorTemplate<const ValueType, +1> ConstIterator;
	typedef IteratorTemplate<ValueType, -1> ReverseIterator;
	typedef IteratorTemplate<const ValueType, -1> ConstReverseIterator;

	/**
	Creates an empty array.
	*/
	inline Array()
		: BufferPolicyType(0, 0)
	{
	}

	/**
	Creates an empty array.
	*/
	inline Array(Empty)
		: BufferPolicyType(0, 0)
	{
	}

	/**
	Empties the array.
	*/
	inline const ArrayType& operator =(Empty)
	{
		setCount(0);
		return *this;
	}

	/**
	Sets the length of the array.
	*/
	explicit inline Array(int newCount)
		: BufferPolicyType(newCount, newCount)
	{
		checkArgumentPositive(NAME_VALUE(newCount), ERROR_AT);
	}

	/**
	Sets the array to a length, and initializes all fields with a single value.
	*/
	explicit inline Array(const T& value, int newCount = 1)
		: BufferPolicyType(newCount, newCount)
	{
		checkArgumentPositive(NAME_VALUE(newCount), ERROR_AT);
		for (int i = 0; i < newCount; ++i)
		{
			BufferPolicyType::buffer[i] = value;
		}
	}

	/**
	Sets the array to a length, and initializes all fields with values from a C array.
	*/
	inline Array(const T * values, int newCount)
		: BufferPolicyType(newCount, newCount)
	{
		checkArgumentPositive(NAME_VALUE(newCount), ERROR_AT);
		for (int i = 0; i < newCount; ++i)
		{
			BufferPolicyType::buffer[i] = values[i];
		}
	}

	/**
	Copy constructor.
	*/
	inline Array(const ArrayType& other)
  		: BufferPolicyType(other.getCount(), other.getCount())
	{
		for (int i = 0; i < getCount(); ++i)
		{
			BufferPolicyType::buffer[i] = other[i];
		}
	}

	/**
	Copies all values.
	*/
	inline ArrayType& operator =(const ArrayType& right)
	{
		setCount(right.getCount());
		for (int i = 0; i < getCount(); ++i)
		{
			BufferPolicyType::buffer[i] = right[i];
		}
		return *this;
	}

	/**
	Appends a range to the array.
	*/
	template<class I>
	inline Array(const I& beginRange, const I& endRange)
  		: BufferPolicyType(0, 0)
	{
		append(beginRange, endRange);
	}

	inline T& operator [](int index)
	{
		checkArgumentRange(NAME_VALUE(index), 0, getCount()-1, ERROR_AT);
		return BufferPolicyType::buffer[index];
	}

	inline const T& operator [](int index) const
	{
		checkArgumentRange(NAME_VALUE(index), 0, getCount()-1, ERROR_AT);
		return BufferPolicyType::buffer[index];
	}

	/**
	Append.
	@see append(), operator -=()
	*/
	inline const ArrayType& operator +=(const T& right)
	{
		append(right);
		return *this;
	}

	/**
	Removes the last element that has the value right.
	@see removeLast(), operator +=()
	*/
	inline const ArrayType& operator -=(const T& right)
	{
		removeLast(right);
		return *this;
	}

	/**
	Removes the element at the iterator position.
	@see remove()
	*/
	inline const ArrayType& operator -=(const Iterator& position)
	{
		remove(position);
		return *this;
	}

	/**
	Removes the element at the iterator position.
	@see remove()
	*/
	inline const ArrayType& operator -=(const ReverseIterator& position)
	{
		remove(position);
		return *this;
	}

	/**
	Appends a value count times.
	@see remove()
	*/
	inline void append(const T& value, int count = 1)
	{
		if (count != 0 &&
			checkState(NAME_VALUE(canSetCount()), ERROR_AT) == true &&
			checkArgumentPositive(NAME_VALUE(count), ERROR_AT) == true)
		{
			const int oldCount = getCount();
			setCount(oldCount + count);
			for (int i = oldCount; i < getCount(); ++i)
			{
				BufferPolicyType::buffer[i] = value;
			}
		}
	}

	/**
	Appends a range count times.
	@see remove()
	*/
	template<class I>
	inline void append(const I& beginRange, const I endRange, int count = 1)
	{
		if (count != 0 &&
			checkState(NAME_VALUE(canSetCount()), ERROR_AT) == true &&
			checkArgumentPositive(NAME_VALUE(count), ERROR_AT) == true)
		{
			for (int c = 0; c < count; ++c)
			{
				for (I i = beginRange; i != endRange; ++i)
				{
					append(*i);
				}
			}
		}
	}

	/**
	Inserts a value at a index count times.
	@see remove()
	*/
	inline void insert(const T& value, const int index = 0, const int count = 1)
	{
		if (count != 0 &&
			checkArgumentRange(NAME_VALUE(index), 0, getCount(), ERROR_AT) == true &&
			checkArgumentPositive(NAME_VALUE(count), ERROR_AT) == true)
		{
			if (canSetCount() == true)
			{
				int oldCount = getCount();
				setCount(oldCount + count);

				for (int i = oldCount-1; i >= index; --i)
				{
					BufferPolicyType::buffer[i+count] = BufferPolicyType::buffer[i];
				}
				for (int i = index; i < index + count; ++i)
				{
					BufferPolicyType::buffer[i] = value;
				}
			}
			else
			{
				for (int i = getCount()-1-count; i >= index; --i)
				{
					BufferPolicyType::buffer[i+count] = BufferPolicyType::buffer[i];
				}
				for (int i = index; i < index + count; ++i)
				{
					BufferPolicyType::buffer[i] = value;
				}
			}
		}
	}

	/**
	Inserts a value at a iterator-position count times.
	@see remove()
	*/
	inline void insert(const T& value, const Iterator& position, const int count = 1)
	{
		insert(value, position.distanceFrom(begin()), count);
	}

	/**
	Inserts a value at a reverse-iterator-position count times.
	@see remove()
	*/
	inline void insert(const T& value, const ReverseIterator& position, const int count = 1)
	{
		insert(value, position.distanceFrom(reverseLast()), count);
	}

	/**
	Removes count elements at the index.
	@see insert(), removeFastByReplacingWithLastElement()
	*/
	inline void remove(int index = 0, int count = 1)
	{
		if (count != 0 &&
			checkArgumentRange(NAME_VALUE(index), 0, getCount()-1, ERROR_AT) == true &&
			checkArgumentRange(NAME_VALUE(count), 0, getCount() - index, ERROR_AT) == true)
		{
			const int oldCount = getCount();
			for (int i = index + count; i < oldCount; ++i)
			{
				BufferPolicyType::buffer[i-count] = BufferPolicyType::buffer[i];
			}
			if (canSetCount() == true)
			{
				setCount(oldCount - count);
			}
		}
	}

	/**
	Removes the element at the index by moving the last element at its place.
	@see remove()
	*/
	inline void removeFastByReplacingWithLastElement(int index = 0)
	{
		if (count != 0 &&
			checkArgumentRange(NAME_VALUE(index), 0, getCount()-1, ERROR_AT) == true &&
			checkArgumentRange(NAME_VALUE(count), 0, getCount() - index, ERROR_AT) == true)
		{
			const int newCount = getCount() - 1;
			if (newCount > 1)
			{
				BufferPolicyType::buffer[index] = implementation[newCount];
			}
			if (canSetCount() == true)
			{
				setCount(oldCount - count);
			}
		}
	}

	/**
	Removes count elements at the iterator-position.
	@see insert()
	*/
	inline void remove(const Iterator& position, int count = 1)
	{
		remove(position.distanceFrom(begin()), count);
	}

	/**
	Removes count elements at the reverse-iterator-position.
	@see insert()
	*/
	inline void remove(const ReverseIterator& position, int count = 1)
	{
		remove(position.distanceFrom(reverseLast()), count);
	}

	/**
	Removes the first element with a specified value.
	@see removeLast()
	*/
	inline void removeFirst(const T& value)
	{
		remove(findFirst(value));
	}

	/**
	Removes the last element with a specified value.
	@see removeLast()
	*/
	inline void removeLast(const T& value)
	{
		remove(findLast(value));
	}

	/**
	Asigns a value to an index-range.
	@see append()
	*/
	inline void assign(const T& value, int beginIndex, int endIndex)
	{
		if (checkArgumentRange(NAME_VALUE(beginIndex), 0, getCount()-1, ERROR_AT) == true &&
			checkArgumentRange(NAME_VALUE(endIndex), beginIndex, getCount()-1, ERROR_AT) == true)
		{
			for (int i = beginIndex; i < endIndex; ++i)
			{
				BufferPolicyType::buffer[i] = value;
			}
		}
	}

	/**
	Assigns a value from a begin-index to the end.
	*/
	inline void assign(const T& value, int beginIndex = 0)
	{
		assign(value, beginIndex, getCount() - beginIndex);
	}

	/**
	Assigns a value from to all elements within an iterator-range.
	*/
	inline void assign(const T& value, const Iterator& beginPosition, const Iterator endPosition)
	{
		for (Iterator i = beginPosition; i != endPosition; ++i)
		{
			*i = value;
		}
	}

	/**
	Assigns a value from to all elements within an reverse-iterator-range.
	*/
	inline void assign(const T& value, const ReverseIterator& beginPosition, const ReverseIterator endPosition)
	{
		for (ReverseIterator i = beginPosition; i != endPosition; ++i)
		{
			*i = value;
		}
	}

	/**
	Assigns a value from a begin iterator-position to the end.
	*/
	inline void assign(const T& value, const Iterator& beginPosition)
	{
		assign(value, beginPosition, end());
	}

	/**
	Assigns a value from a begin reverse-iterator-position to the end.
	*/
	inline void assign(const T& value, const ReverseIterator& beginPosition)
	{
		assign(value, beginPosition, reverseEnd());
	}

	/**
	Assigns an C-array with length count to this array starting at destinationIndex.
	*/
	inline void assign(const T * values, int count, int destinationIndex = 0)
	{
		if (count != 0 &&
			checkArgumentRange(NAME_VALUE(destinationIndex), 0, getCount()-1, ERROR_AT) == true &&
			checkArgumentRange(NAME_VALUE(count), 0, getCount() - destinationIndex, ERROR_AT) == true)
		{
			for (int i = 0; i < count; ++i, ++destinationIndex)
			{
				BufferPolicyType::buffer[destinationIndex] = values[i];
			}
		}
	}

	/**
	Returns a reference to the first element.
	*/
	inline T& firstElement()
	{
		checkStateGreater(NAME_VALUE(getCount()), 0);
		return BufferPolicyType::buffer[0];
	}

	/**
	Returns a const-reference to the first element.
	*/
	inline const T& firstElement() const
	{
		checkStateGreater(NAME_VALUE(getCount()), 0);
		return BufferPolicyType::buffer[0];
	}

	/**
	Returns a reference to the last element.
	*/
	inline T& lastElement()
	{
		checkStateGreater(NAME_VALUE(getCount()), 0);
		return BufferPolicyType::buffer[getCount()-1];
	}

	/**
	Returns a const-reference to the last element.
	*/
	inline const T& lastElement() const
	{
		checkStateGreater(NAME_VALUE(getCount()), 0);
		return BufferPolicyType::buffer[getCount()-1];
	}

	inline Iterator begin()
	{
		return Iterator(BufferPolicyType::buffer);
	}

	inline ConstIterator begin() const
	{
		return ConstIterator(BufferPolicyType::buffer);
	}

	inline Iterator end()
	{
		return Iterator(&BufferPolicyType::buffer[getCount()]);
	}

	inline ConstIterator end() const
	{
		return ConstIterator(&BufferPolicyType::buffer[getCount()]);
	}

	inline Iterator last()
	{
		return Iterator(&BufferPolicyType::buffer[getCount()-1]);
	}

	inline ConstIterator last() const
	{
		return ConstIterator(&BufferPolicyType::buffer[getCount()-1]);
	}

	inline ReverseIterator reverseBegin()
	{
		return ReverseIterator(&BufferPolicyType::buffer[getCount()-1]);
	}

	inline ConstReverseIterator reverseBegin() const
	{
		return ConstReverseIterator(&BufferPolicyType::buffer[getCount()-1]);
	}

	inline ReverseIterator reverseEnd()
	{
		return ReverseIterator(&BufferPolicyType::buffer[-1]);
	}

	inline ConstReverseIterator reverseEnd() const
	{
		return ConstReverseIterator(&BufferPolicyType::buffer[-1]);
	}

	inline ReverseIterator reverseLast()
	{
		return ReverseIterator(&BufferPolicyType::buffer[0]);
	}

	inline ConstReverseIterator reverseLast() const
	{
		return ConstReverseIterator(&BufferPolicyType::buffer[0]);
	}

	/**
	Returns the index of the first occurence of a value.
	@see lastIndexOf()
	*/
	inline int firstIndexOf(const T& value) const
	{
		for (int i = 0; i < getCount(); ++i)
		{
			if (BufferPolicyType::buffer[i] == value) return i;
		}
		return -1;
	}

	/**
	Returns the index of the last occurence of a value.
	@see firstIndexOf()
	*/
	inline int lastIndexOf(const T& value) const
	{
		for (int i = getCount()-1; i >= 0; --i)
		{
			if (BufferPolicyType::buffer[i] == value) return i;
		}
		return -1;
	}

	/**
	Returns an const-iterator with the position of the first occurence of a value.
	@see findLast
	*/
	inline ConstIterator findFirst(const T& value) const
	{
		const ConstIterator constEnd = end();
		for (ConstIterator i = begin(); i != constEnd; ++i)
		{
			if ((*i) == value) return i;
		}
		return end();
	}

	/**
	Returns an const-reverse-iterator with the position of the last occurence of a value.
	Position of the last occurence ist the first position for a reverse-iterator.
	@see findLast
	*/
	inline ConstReverseIterator findLast(const T& value) const
	{
		const ConstReverseIterator constReverseEnd = reverseEnd();
		for (ConstReverseIterator i = reverseBegin(); i != constReverseEnd(); ++i)
		{
			if ((*i) == value) return i;
		}
		return reverseEnd();
	}

	/**
	Returns an iterator with the position of the first occurence of a value.
	@see findLast
	*/
	inline Iterator findFirst(const T& value)
	{
		const Iterator constEnd = end();
		for (Iterator i = begin(); i != constEnd; ++i)
		{
			if ((*i) == value) return i;
		}
		return end();
	}

	/**
	Returns an reverse-iterator with the position of the last occurence of a value.
	Position of the last occurence ist the first position for a reverse-iterator.
	@see findFirst
	*/
	inline ReverseIterator findLast(const T& value)
	{
		const ReverseIterator constReverseEnd = reverseEnd();
		for (ReverseIterator i = reverseBegin(); i != constReverseEnd; ++i)
		{
			if ((*i) == value) return i;
		}
		return reverseEnd();
	}

	inline int getSizeInBytes() const
	{
		return getCount() * sizeof(T);
	}

	inline void invertOrder()
	{
		const int halfCount = getCount() / 2;
		const int lastIndex = getCount()-1;
		for (int i = 0; i < halfCount; ++i)
		{
			swap(BufferPolicyType::buffer[i], BufferPolicyType::buffer[lastIndex-i]);
		}
	}

	inline void quicksort()
	{
		BaseLib::Utilities::quicksort<T>(*this, 0, getCount());
	}

	inline void quicksortInverse()
	{
		BaseLib::Utilities::quicksortInverse<T>(*this, 0, getCount());
	}

	inline void quicksort(int firstIndex, int lastIndex)
	{
		BaseLib::Utilities::quicksort<T>(*this, firstIndex, lastIndex);
	}

	inline void quicksortInverse(int firstIndex, int lastIndex)
	{
		BaseLib::Utilities::quicksortInverse<T>(*this, firstIndex, lastIndex);
	}

	inline bool isEmpty() const
	{
		return getCount() == 0;
	}

	//Delegation to Imlementation:

	inline int getCount() const
	{
		return BufferPolicyType::getCount();
	}

	inline void setCount(int newCount)
	{
		if (checkArgumentPositive(NAME_VALUE(newCount), ERROR_AT) == true &&
			checkState(NAME_VALUE(canSetCount()), ERROR_AT) == true)
		{
			BufferPolicyType::setCount(newCount);
		}
	}

	inline bool canSetCount() const
	{
		return BufferPolicyType::canSetCount();
	}

	inline int getCapacity() const
	{
		return BufferPolicyType::getCapacity();
	}

	/**
	Changes the capacity if possible.
	@result Returns true if elements have moved in memory.
	*/
	inline bool setCapacity(int newCapacity)
	{
		if (checkArgumentPositive(NAME_VALUE(newCapacity), ERROR_AT) == true &&
			checkState(NAME_VALUE(canSetCapacity()), ERROR_AT) == true)
		{
			return BufferPolicyType::setCapacity(newCapacity);
		}
		else
		{
			return false;
		}
	}

	inline bool canSetCapacity() const
	{
		return BufferPolicyType::canSetCapacity();
	}


	#include "BaseLib/Containers/Array_Enumerator.inl.h"

};



} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_Array_h