/******************************************************************************

Developed and Copyright (c) by

Erik Unger

Contact: erik@erikunger.com

******************************************************************************/

#ifndef BaseLib_Containers_HashMap_h
#define BaseLib_Containers_HashMap_h



#include "BaseLib/Containers/Array.h"
#include <utility>



namespace BaseLib {
namespace Containers {



template<typename Key, typename Value>
class HashMap {
public:

	typedef uint HashType;
	typedef typename Key KeyType;
	typedef typename Value ValueType;
	typedef typename std::pair<const KeyType, ValueType> PairType;

	HashMap()
		: count(0)
		, hashTable(31)
	{
	}

	inline void insert(const PairType& keyValuePair)
	{
		int hashTableSize = hashTable.getCount();
		if (count >= hashTableSize * 10)
		{
			increaseTableSize();
		}

		HashType hashValue = hash(key);
		hashValue %= hashTableSize;
		if (hashTable[hashValue].firstIndexOf(value) == -1)
		{
			hashTable[hashValue] += keyValuePair;
			++count;
		}
	}

	inline void insert(const KeyType& key, const ValueType& value)
	{
		insert(PairType(key, value));
	}

	inline bool remove(const KeyType& key)
	{
		HashType hashValue = hash(key);
		hashValue %= hashTable.getCount();
		Array<PairType>& list = hashTable[hashValue];
		const int count = list.getCount();
		for (int i = 0; i < count; ++i)
		{
			if (list[i].first == key)
			{
				list.remove(i);
				--count;
				return true;
			}
		}
		return false;
	}

	inline bool has(const KeyType& key) const
	{
		HashType hashValue = hash(key);
		hashValue %= hashTable.getCount();
		Array<PairType>& list = hashTable[hashValue];
		const int count = list.getCount();
		for (int i = 0; i < count; ++i)
		{
			if (list[i].first == key)
			{
				return true;
			}
		}
		return false;
	}

	inline ValueType get(const KeyType& key) const
	{
		HashType hashValue = hash(key);
		hashValue %= hashTable.getCount();
		Array<PairType>& list = hashTable[hashValue];
		const int count = list.getCount();
		for (int i = 0; i < count; ++i)
		{
			if (list[i].first == key)
			{
				return list[i].second;
			}
		}
		BaseLib::ErrorHandling::argumentError("Can't find value for key!");
		return ValueType();
	}

	inline int getCount() const
	{
		return count;
	}


private:

	int count;
	typedef Array<Array<PairType> > HashTable;
	HashTable hashTable;

	inline void increaseTableSize()
	{
		Array<PairType> buffer(count);
		int index = 0;
		for (int i = 0; i < hashTableSize; ++i)
		{
			Array<PairType>& list = hashTable[i];
			const int listSize = list.getCount();
			buffer.assign(&list.firstElement(), listSize, index);
			index += listSize;
			list.setCount(0);
		}
		
		hashTableSize = (hashTableSize + 1) * 2 - 1;
		hashTable.setCount(hashTableSize);

		for (int i = 0; i < count; ++i)
		{
			insert(buffer[i]);
		}
	}
};



} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_HashMap_h
