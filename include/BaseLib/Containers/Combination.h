/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_Combination_h
#define BaseLib_Containers_Combination_h



#include "BaseLib/Containers/Enumeration.h"
#include <set>



namespace BaseLib {
namespace Containers {



/**
Combination if different values or flags.
This class is intended as replacement for bit-masks that combine flags in a single value.
*/
template<typename E>
class Combination {
public:

	typedef typename E ValueType;
	typedef typename E& ReferenceType;
	typedef typename const E& ConstReferenceType;

	template<typename E>
	class IteratorTemplate {

		friend Combination<E>;

	public:

		inline const E& operator*() const
		{
			return *implementation;
		}

		inline const E* operator->() const
		{
			return implementation.operator ->();
		}

		inline IteratorTemplate<E>& operator ++()
		{
			++implementation;
			return *this;
		}

		inline IteratorTemplate<E> operator ++(int) 
		{
			Iterator<E> old = *this;
			++implementation;
			return old;
		}

		inline IteratorTemplate<E>& operator --() 
		{
			--implementation;
			return *this;
		}

		inline IteratorTemplate<E> operator --(int) 
		{
			Iterator<E> old = *this;
			--implementation;
			return old;
		}

		inline bool operator ==(const IteratorTemplate<E>& right) const
		{
			return implementation == right.implementation;
		}

		inline bool operator !=(const IteratorTemplate<E>& right) const
		{
			return !operator==(right);
		}

	private:

		IteratorTemplate();

		inline IteratorTemplate(typename const std::set<E>::const_iterator& iterator)
			: implementation(iterator)
		{
		}

		typename std::set<E>::const_iterator implementation;
	};

	typedef typename IteratorTemplate<E> Iterator;



	inline Combination()
		: values()
	{
	}

	inline Combination(const E& value0)
		: values()
	{
		values.insert(value0);
	}

	inline Combination(const E& value0, const E& value1)
		: values()
	{
		values.insert(value0);
		values.insert(value1);
	}

	inline Combination(const E& value0, const E& value1, const E& value2)
		: values()
	{
		values.insert(value0);
		values.insert(value1);
		values.insert(value2);
	}

	inline Combination(const E& value0, const E& value1, const E& value2, const E& value3)
		: values()
	{
		values.insert(value0);
		values.insert(value1);
		values.insert(value2);
		values.insert(value3);
	}

	inline Combination(const E& value0, const E& value1, const E& value2, const E& value3, const E& value4)
		: values()
	{
		values.insert(value0);
		values.insert(value1);
		values.insert(value2);
		values.insert(value3);
		values.insert(value4);
	}

	inline Combination(const E& value0, const E& value1, const E& value2, const E& value3, const E& value4, const E& value5)
		: values()
	{
		values.insert(value0);
		values.insert(value1);
		values.insert(value2);
		values.insert(value3);
		values.insert(value4);
		values.insert(value5);
	}

	inline Combination(const Combination<E>& other)
		: values(other.values)
	{
	}

	inline Combination<E>& operator =(const Combination<E>& right)
	{
		values = right.values;
		return *this;
	}

	inline Combination<E>& operator =(E right)
	{
		values.clear();
		values.insert(right);
		return *this;
	}

	inline bool operator [](E value) const
	{
		return values.find(value) != values.end();
	}

	inline void add(E value)
	{
		values.insert(values);
	}

	inline void remove(E value)
	{
		values.erase(value);
	}

	inline Iterator begin() const
	{
		return Iterator(values.begin());
	}

	inline Iterator end() const
	{
		return Iterator(values.end());
	}

private:
	std::set<E> values;

};



} // namespace Containers
} // namespace BaseLib



#endif // BaseLib_Containers_Combination_h

