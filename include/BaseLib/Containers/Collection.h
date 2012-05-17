/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_Collection_h
#define BaseLib_Containers_Collection_h



#include "BaseLib/Containers/Enumeration.h"



namespace BaseLib {
namespace Containers {



/**
Not implemented.
Wraps any container...
@todo Implementation
*/
template<class T>
class Collection : public Enumeration<T> {
public:

	class AbstractImplementation {
	public:

		virtual ~AbstractImplementation() {}

		virtual bool isEmpty() const = 0;
		virtual int getCount() const = 0;

		virtual typename Enumeration<T>::Iterator begin() const = 0;
		virtual typename Enumeration<T>::Iterator end() const = 0;
		virtual typename Enumeration<T>::ReverseIterator reverseBegin() const = 0;
		virtual typename Enumeration<T>::ReverseIterator reverseEnd() const = 0;

		virtual ValueType& get(int index) = 0;
		virtual const ValueType get(int index) const = 0;
		virtual void set(int index, const ValueType& newValue) = 0;

		virtual void insert(int index, const ValueType& newValue) = 0;
		virtual void append(const ValueType& newValue) = 0;
		virtual void remove(int index) = 0;

		void addReference()
		{
			++referenceCount;
		}

		void releaseReference()
		{
			--referenceCount;
			if (referenceCount <= 0)
			{
				delete this;
			}
		}
	
	protected:

		AbstractImplementation()
			: referenceCount(1)
		{
		}

	private:

		int referenceCount;

	};

	virtual ~Collection()
	{
		if (implementation != NULL)
		{
			implementation->releaseReference();
		}
	}

	virtual bool isEmpty() const
	{
		return implementation == NULL || implementation->isEmpty();
	}

	virtual int getCount() const
	{
		return implementation != NULL ? implementation->getCount() : 0;
	}

	virtual Iterator begin() const
	{
		return implementation->begin(); // TODO: NullIterator
	}

	virtual Iterator end() const
	{
		return implementation->end();
	}

	virtual ReverseIterator reverseBegin() const
	{
		return implementation->reverseBegin();
	}

	virtual ReverseIterator reverseEnd() const
	{
		return implementation->reverseEnd();
	}

	inline ValueType& operator [](int index)
	{
		return implementation->get(index);
	}

	inline const ValueType& operator [](int index) const
	{
		return implementation->get(index);
	}

	inline void insert(int index, const ValueType& newValue)
	{
		if (implementation != NULL)
		{
			implementation->insert(index, newValue);
		}
	}

	inline void append(const ValueType& newValue)
	{
		if (implementation != NULL)
		{
			implementation->append(index, newValue);
		}
	}

	inline void remove(int index)
	{
		if (implementation != NULL)
		{
			implementation->remove(index);
		}
	}

	//inline void findAndRemove(const ValueType& oldValue)
	//{
	//	int index
	//	for (Iterator i = begin(); i != end(); ++i)
	//	{
	//		if (*i == oldValue)
	//	}
	//}

	inline Collection& operator +=(const ValueType& newValue)
	{
		append(newValue);
	}

	//inline Collection& operator -=(const ValueType& oldValue)
	//{
	//	findAndRemove(newValue);
	//}

private:

	AbstractImplementation* implementation;


};


} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_Collection_h
