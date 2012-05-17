/******************************************************************************

Developed and Copyright (c) by

Erik Unger

Contact: erik@erikunger.com

******************************************************************************/

#ifndef BaseLib_Containers_StringMap_h
#define BaseLib_Containers_StringMap_h



#include "BaseLib/Strings/String.h"
#include "BaseLib/Containers/Enumeration.h"



/*
#if _MSC_VER >= 1300
	#define USE_HASH_MAP_FOR_STRING_MAP
#endif
*/


#ifdef USE_HASH_MAP_FOR_STRING_MAP
	#include <hash_map>
	#define STRING_MAP_BASE_CLASS std::hash_map
#else
	#include <map>
	#define STRING_MAP_BASE_CLASS std::map
#endif



//#define StringMap(T) STRING_MAP_BASE_CLASS<std::string, T>


namespace BaseLib {
namespace Containers {



using BaseLib::Strings::String;



template<class T = String>
class StringMap : public STRING_MAP_BASE_CLASS<String, T> {
public:

	typedef typename STRING_MAP_BASE_CLASS<String, T>::iterator Iterator;
	typedef typename STRING_MAP_BASE_CLASS<String, T>::reverse_iterator ReverseIterator;
	typedef typename STRING_MAP_BASE_CLASS<String, T>::const_iterator ConstIterator;
	typedef typename STRING_MAP_BASE_CLASS<String, T>::const_reverse_iterator ConstReverseIterator;

	Iterator getByIndex(size_type index)
    {
		if (index >= size())
		{
            argumentError(PROPERTY_INDEX_OUT_OF_RANGE(index, 0, size()-1));
            return end();
		}

        Iterator it = begin();
        for (size_type i = 0; i < index; ++i)
        {
            ++it;
        }
        return it;
    }

    ConstIterator getByIndex(size_type index) const
    {
		if (index >= size())
		{
            argumentError(PROPERTY_INDEX_OUT_OF_RANGE(index, 0, size()-1));
            return end();
		}

        ConstIterator it = begin();
        for (size_type i = 0; i < index; ++i)
        {
            ++it;
        }
        return it;
    }

	String getKeyByIndex(size_type index)
    {
		if (index >= size())
		{
            argumentError(PROPERTY_INDEX_OUT_OF_RANGE(index, 0, size()-1));
            return Empty();
		}

        Iterator it = begin();
        for (size_type i = 0; i < index; ++i)
        {
            ++it;
        }
        return it->first;
    }

	String getKeyByIndex(size_type index) const
    {
		if (index >= size())
		{
            argumentError(PROPERTY_INDEX_OUT_OF_RANGE(index, 0, size()-1));
            return Empty();
		}

        ConstIterator it = begin();
        for (size_type i = 0; i < index; ++i)
        {
            ++it;
        }
        return it->first;
    }

    Iterator findValue(const T& value)
    {
        for (Iterator i = begin(); i != end(); ++i)
        {
            if (i->second == value) return i;
        }

        return end();
    }

    ConstIterator findValue(const T& value) const
    {
        for (ConstIterator i = begin(); i != end(); ++i)
        {
            if (i->second == value) return i;
        }

        return end();
    }


	inline void enumerate(const Enumerator<T>& enumerator, const ConstIterator& beginRange, const ConstIterator& endRange) const
	{
		for (ConstIterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator.enumerate(*i);
		}
	}

	inline void enumerate(const Enumerator<T>* enumerator, const ConstIterator& beginRange, const ConstIterator& endRange) const
	{
		for (ConstIterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator->enumerate(*i);
		}
	}

	inline void enumerate(const Enumerator<T>& enumerator, const Iterator& beginRange, const Iterator& endRange)
	{
		for (Iterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator.enumerate(*i);
		}
	}

	inline void enumerate(const Enumerator<T>* enumerator, const Iterator& beginRange, const Iterator& endRange)
	{
		for (Iterator i = beginRange; i != endRange && enumerator.stop() == false; ++i)
		{
			enumerator->enumerate(*i);
		}
	}

	void enumerate(const Enumerator<T>& enumerator) const
	{
		enumerator.enumerate(begin(), end());
	}

	void enumerate(const Enumerator<T>* enumerator) const
	{
		enumerator->enumerate(begin(), end());
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
	inline void enumerate(const ConstIterator& beginRange, const ConstIterator& endRange) const
	{
		enumerate(E<T>(), beginRange, endRange);
	}

	template<template<class, typename> class E, class C>
	inline void enumerate(C& other, const ConstIterator& beginRange, const ConstIterator& endRange) const
	{
		enumerate(E<C, T>(other), beginRange, endRange);
	}

	template<template<typename> class E>
	inline void enumerate(const Iterator& beginRange, const Iterator& endRange)
	{
		enumerate(E<T>(), beginRange, endRange);
	}

	template<template<class, typename> class E, class C>
	inline void enumerate(C& other, const Iterator& beginRange, const Iterator& endRange)
	{
		enumerate(E<C, T>(other), beginRange, endRange);
	}


	class KeyEnumeration : public Enumeration<String> {
	public:

		template<class I>
		class PairIterator : public Enumeration<String>::AbstractIteratorImplementation {
		public:

			explicit PairIterator(const I& forStdIterator)
				: pairIterator(forStdIterator)
			{
			}

			virtual Enumeration<String>::AbstractIteratorImplementation* clone() const
			{
				return new PairIterator<I>(pairIterator);
			}

			virtual const String get() const
			{
				return pairIterator->first;
			}

			virtual void next()
			{
				++pairIterator;
			}

			virtual void previous()
			{
				++pairIterator;
			}

			virtual bool equals(const Enumeration<String>::AbstractIteratorImplementation* right) const
			{
				const PairIterator<I>* rightIterator = static_cast<const PairIterator<I>*>(right);
				return pairIterator == rightIterator->pairIterator;
			}

		protected:

			I pairIterator;
		};

		KeyEnumeration(StringMap<T>* forStringMap, bool ownsWrappedContainer = false)
			: Enumeration<String>(ownsWrappedContainer)
			, stringMap(forStringMap)
		{
		}

		virtual ~KeyEnumeration()
		{
			if (owner == true)
			{
				delete stringMap;
			}
		}

		virtual bool isEmpty() const
		{
			return stringMap->empty();
		}

		virtual int getCount() const
		{
			return static_cast<int>(stringMap->size());
		}

		virtual Iterator begin() const
		{
			return Iterator(new PairIterator<StringMap<T>::Iterator>(stringMap->begin()));
		}

		virtual Iterator end() const
		{
			return Iterator(new PairIterator<StringMap<T>::Iterator>(stringMap->end()));
		}

		virtual ReverseIterator reverseBegin() const
		{
			return ReverseIterator(new PairIterator<StringMap<T>::ReverseIterator>(stringMap->rbegin()));
		}

		virtual ReverseIterator reverseEnd() const
		{
			return ReverseIterator(new PairIterator<StringMap<T>::ReverseIterator>(stringMap->rend()));
		}

	protected:

		StringMap<T>* stringMap;
	};


	Enumeration<String>* createKeyEnumeration(bool ownsWrappedContainer = false)
	{
		return new KeyEnumeration(this, ownsWrappedContainer);
	}

	class ValueEnumeration : public Enumeration<T> {
	public:

		typedef T ValueType;

		template<class I>
		class PairIterator : public Enumeration<T>::AbstractIteratorImplementation {
		public:

			explicit PairIterator(const I& forStdIterator)
				: pairIterator(forStdIterator)
			{
			}

			virtual typename Enumeration<ValueType>::AbstractIteratorImplementation* clone() const
			{
				return new PairIterator<I>(pairIterator);
			}

			virtual const T get() const
			{
				return pairIterator->second;
			}

			virtual void next()
			{
				++pairIterator;
			}

			virtual void previous()
			{
				++pairIterator;
			}

			virtual bool equals(typename const Enumeration<ValueType>::AbstractIteratorImplementation* right) const
			{
				const PairIterator<I>* rightIterator = static_cast<const PairIterator<I>*>(right);
				return pairIterator == rightIterator->pairIterator;
			}

		protected:

			I pairIterator;
		};

		ValueEnumeration(StringMap<T>* forStringMap, bool ownsWrappedContainer = false)
			: Enumeration<T>(ownsWrappedContainer)
			, stringMap(forStringMap)
		{
		}

		virtual ~ValueEnumeration()
		{
			if (owner == true)
			{
				delete stringMap;
			}
		}

		virtual bool isEmpty() const
		{
			return stringMap->empty();
		}

		virtual int getCount() const
		{
			return stringMap->size();
		}

		virtual Iterator begin() const
		{
			return Iterator(new PairIterator<StringMap<T>::Iterator>(stringMap->begin()));
		}

		virtual Iterator end() const
		{
			return Iterator(new PairIterator<StringMap<T>::Iterator>(stringMap->end()));
		}

		virtual ReverseIterator reverseBegin() const
		{
			return ReverseIterator(new PairIterator<StringMap<T>::ReverseIterator>(stringMap->rbegin()));
		}

		virtual ReverseIterator reverseEnd() const
		{
			return ReverseIterator(new PairIterator<StringMap<T>::ReverseIterator>(stringMap->rend()));
		}

	protected:

		StringMap<T>* stringMap;
	};


	Enumeration<T>* createValueEnumeration(bool ownsWrappedContainer = false)
	{
		return new ValueEnumeration(this, ownsWrappedContainer);
	}


	class ConstKeyEnumeration : public Enumeration<String> {
	public:

		template<class I>
		class PairIterator : public Enumeration<String>::AbstractIteratorImplementation {
		public:

			explicit PairIterator(const I& forStdIterator)
				: pairIterator(forStdIterator)
			{
			}

			virtual Enumeration<String>::AbstractIteratorImplementation* clone() const
			{
				return new PairIterator<I>(pairIterator);
			}

			virtual const String get() const
			{
				return pairIterator->first;
			}

			virtual void next()
			{
				++pairIterator;
			}

			virtual void previous()
			{
				++pairIterator;
			}

			virtual bool equals(const Enumeration<String>::AbstractIteratorImplementation* right) const
			{
				const PairIterator<I>* rightIterator = static_cast<const PairIterator<I>*>(right);
				return pairIterator == rightIterator->pairIterator;
			}

		protected:

			I pairIterator;
		};

		ConstKeyEnumeration(const StringMap<T>* forStringMap, bool ownsWrappedContainer = false)
			: Enumeration<String>(ownsWrappedContainer)
			, stringMap(forStringMap)
		{
		}

		virtual ~ConstKeyEnumeration()
		{
			if (owner == true)
			{
				delete stringMap;
			}
		}

		virtual bool isEmpty() const
		{
			return stringMap->empty();
		}

		virtual int getCount() const
		{
			return static_cast<int>(stringMap->size());
		}

		virtual Iterator begin() const
		{
			return Iterator(new PairIterator<StringMap<T>::ConstIterator>(stringMap->begin()));
		}

		virtual Iterator end() const
		{
			return Iterator(new PairIterator<StringMap<T>::ConstIterator>(stringMap->end()));
		}

		virtual ReverseIterator reverseBegin() const
		{
			return ReverseIterator(new PairIterator<StringMap<T>::ConstReverseIterator>(stringMap->rbegin()));
		}

		virtual ReverseIterator reverseEnd() const
		{
			return ReverseIterator(new PairIterator<StringMap<T>::ConstReverseIterator>(stringMap->rend()));
		}

	protected:

		const StringMap<T>* stringMap;
	};


	Enumeration<String>* createKeyEnumeration(bool ownsWrappedContainer = false) const
	{
		return new ConstKeyEnumeration(this, ownsWrappedContainer);
	}

	class ConstValueEnumeration : public Enumeration<T> {
	public:

		typedef T ValueType;

		template<class I>
		class PairIterator : public Enumeration<ValueType>::AbstractIteratorImplementation {
		public:

			explicit PairIterator(const I& forStdIterator)
				: pairIterator(forStdIterator)
			{
			}

			virtual Enumeration<ValueType>::AbstractIteratorImplementation* clone() const
			{
				return new PairIterator<I>(pairIterator);
			}

			virtual const T get() const
			{
				return pairIterator->second;
			}

			virtual void next()
			{
				++pairIterator;
			}

			virtual void previous()
			{
				++pairIterator;
			}

			virtual bool equals(const Enumeration<ValueType>::AbstractIteratorImplementation* right) const
			{
				const PairIterator<I>* rightIterator = static_cast<const PairIterator<I>*>(right);
				return pairIterator == rightIterator->pairIterator;
			}

		protected:

			I pairIterator;
		};

		ConstValueEnumeration(const StringMap<T>* forStringMap, bool ownsWrappedContainer = false)
			: Enumeration<T>(ownsWrappedContainer)
			, stringMap(forStringMap)
		{
		}

		virtual ~ConstValueEnumeration()
		{
			if (owner == true)
			{
				delete stringMap;
			}
		}

		virtual bool isEmpty() const
		{
			return stringMap->empty();
		}

		virtual int getCount() const
		{
			return stringMap->size();
		}

		virtual Iterator begin() const
		{
			return Iterator(new PairIterator<StringMap<T>::ConstIterator>(stringMap->begin()));
		}

		virtual Iterator end() const
		{
			return Iterator(new PairIterator<StringMap<T>::ConstIterator>(stringMap->end()));
		}

		virtual ReverseIterator reverseBegin() const
		{
			return ReverseIterator(new PairIterator<StringMap<T>::ConstReverseIterator>(stringMap->rbegin()));
		}

		virtual ReverseIterator reverseEnd() const
		{
			return ReverseIterator(new PairIterator<StringMap<T>::ConstReverseIterator>(stringMap->rend()));
		}

	protected:

		const StringMap<T>* stringMap;
	};


	Enumeration<T>* createValueEnumeration(bool ownsWrappedContainer = false) const
	{
		return new ConstValueEnumeration(this, ownsWrappedContainer);
	}



};


/*
template<class T>
inline const std::string getStringMapKeyByIndex(T& stringMap, T::size_type index)
{
	if (index >= stringMap.size())
	{
        argumentError(PROPERTY_INDEX_OUT_OF_RANGE(index, 0, stringMap.size()-1));
        return Empty();
	}

    T::iterator it = stringMap.begin();
    for (T::size_type i = 0; i < index; ++i)
    {
        ++it;
    }
    return it->first;
}



template<class T>
inline const std::string getStringMapKeyByIndex(const T& stringMap, T::size_type index)
{
	if (index >= stringMap.size())
	{
        argumentError(PROPERTY_INDEX_OUT_OF_RANGE(index, 0, stringMap.size()-1));
        return Empty();
	}

    T::const_iterator it = stringMap.begin();
    for (T::size_type i = 0; i < index; ++i)
    {
        ++it;
    }
    return it->first;
}
*/



} // namespace Containers
} // namespace BaseLib


#endif // #ifndef BaseLib_Containers_StringMap_h
