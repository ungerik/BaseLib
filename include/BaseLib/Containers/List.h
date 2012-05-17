/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_List_h
#define BaseLib_Containers_List_h



#include "BaseLib/Common.h"



namespace BaseLib {
namespace Containers {




template<class T>
class List {
public:

	typedef typename T ValueType;
	typedef typename T& ReferenceType;
	typedef typename const T& ConstReferenceType;

	inline List()
  		: firstEntry(NULL)
		, lastEntry(NULL)
	{
	}

	inline List(const T& value, int newLength = 1)
	{
		///
	}

	inline List(const T * values, int newLength)
	{
		///
	}

	inline List(const List<T>& other)
	{
		///
	}

	inline List<T>& operator=(const List<T>& right)
	{
		///
		return *this;
	}

	/*inline T& get(int index)
	{
		BL_ASSERT(index >= 0 && index < getCount());
		///
	}

	inline const T& get(int index) const
	{
		BL_ASSERT(index >= 0 && index < getCount());
		///
	}*/

	inline List<T>& operator+=(const T& right)
	{
		append(right);
		return *this;
	}

	inline void append(const T& value)
	{
		if (lastEntry == NULL)
		{
			firstEntry = new Entry(NULL, NULL, value);
			lastEntry = firstEntry;
		}
		else
		{
			lastEntry->next = new Entry(lastEntry, NULL, value);
			lastEntry = lastEntry->next;
		}
	}

	inline void append(const T& value, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			append(value);
		}
	}

	inline void insert(const T& value, const int index = 0, const int count = 1)
	{
	}

	inline void remove(int index = 0, int count = 1)
	{
	}

	inline void fill(const T& value, int beginIndex = 0)
	{
		BL_ASSERT(beginIndex >= 0);
	}

	inline void fill(const T& value, int beginIndex, int endIndex)
	{
		BL_ASSERT(beginIndex >= 0 && endIndex >= 0);
	}

	inline T& firstElement()
	{
		BL_ASSERT(firstEntry != NULL);
		return firstEntry->value;
	}

	inline const T& firstElement() const
	{
		BL_ASSERT(firstEntry != NULL);
		return firstEntry->value;
	}

	inline T& lastElement()
	{
		BL_ASSERT(lastEntry != NULL);
		return lastEntry->value;
	}

	inline const T& lastElement() const
	{
		BL_ASSERT(lastEntry != NULL);
		return lastEntry->value;
	}

	inline int find(const T& value) const
	{
		///
		return -1;
	}

	inline int reverseFind(const T& value) const
	{
		///
		return -1;
	}

	inline bool isEmpty() const
	{
		return firstEntry == NULL;
	}

	inline int getCount() const
	{
		int length = 0;
		for (Entry* entry = firstEntry; entry != NULL; entry = entry->next)
		{
			++length;
		}
		return length;
	}

	inline void setLength(int newLength)
	{
		BL_ASSERT(newLength >= 0);
		///
	}


protected:

	struct Entry {

		Entry(Entry* newPrev, Entry* newNext, const T& newValue)
			: prev(newPrev)
			, next(newNext)
			, value(newValue)
		{
		}

		Entry* prev;
		Entry* next;
		T value;
	};

	Entry* firstEntry;
	Entry* lastEntry;

};


} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_List_h