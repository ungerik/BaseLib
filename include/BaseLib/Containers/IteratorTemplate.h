/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_IteratorTemplate_h
#define BaseLib_Containers_IteratorTemplate_h



#include "BaseLib/Defines.h"



namespace BaseLib {
namespace Containers {



template<typename T, template<typename> class Implementation>
class Iterator_MovePolicy_Increment : protected Implementation<T> {

	using Implementation<T>::increment;

public:

	inline const Implementation<T>& operator ++()
	{
		increment();
		return *this;
	}

	inline Implementation<T> operator ++(int)
	{
		const Implementation<T> old = *this;
		increment();
		return old;
	}

};



template<typename T, template<typename> class Implementation>
class Iterator_MovePolicy_IncrementDecrement : protected Iterator_MovePolicy_Increment<T, Implementation> {

	using Implementation<T>::decrement;

public:

	inline const Implementation<T>& operator --()
	{
		decrement();
		return *this;
	}

	inline Implementation<T> operator --(int)
	{
		const Implementation<T> old = *this;
		decrement();
		return old;
	}

};



template<typename T, template<typename> class Implementation>
class Iterator_MovePolicy_ReverseIncrement : protected Implementation<T> {

	using Implementation<T>::decrement;

public:

	inline const Implementation<T>& operator ++()
	{
		decrement();
		return *this;
	}

	inline Implementation<T> operator ++(int)
	{
		const Implementation<T> old = *this;
		decrement();
		return old;
	}

};



template<typename T, template<typename> class Implementation>
class Iterator_MovePolicy_ReverseIncrementDecrement : protected Iterator_MovePolicy_ReverseIncrement<T, Implementation> {

	using Implementation<T>::increment;

public:

	inline const Implementation<T>& operator --()
	{
		increment();
		return *this;
	}

	inline Implementation<T> operator --(int)
	{
		const Implementation<T> old = *this;
		increment();
		return old;
	}

};



template<typename T, template<typename> class Implementation>
class Iterator_ComparePolicy_Equals : protected Implementation<T> {

	using Implementation<T>::equals;

public:

	inline bool operator ==(const Implementation<T>& right) const
	{
		return equals(right);
	}

	inline bool operator !=(const Implementation<T>& right) const
	{
		return !operator ==(right);
	}
};



template<typename T, template<typename> class Implementation>
class Iterator_ComparePolicy_EqualsSmallerThan : public Iterator_ComparePolicy_Equals<T, Implementation> {

	using Implementation<T>::smallerThan;

public:

	inline bool operator <(const Implementation<T>& right) const
	{
		return smallerThan(right);
	}

	inline bool operator <=(const Implementation<T>& right) const
	{
		return smallerThan(right) || equas(right);
	}

	inline bool operator >(const Implementation<T>& right) const
	{
		return !operator <=(right);
	}

	inline bool operator >=(const Implementation<T>& right) const
	{
		return equals(right) && !smallerThan(right);
	}
};



template<typename T, template<typename> class Implementation, template<typename, template<typename> class> class MovePolicy, template<typename, template<typename> class> class ComparePolicy>
class IteratorTemplate : public Implementation<T>, public MovePolicy<T, Implementation>, public ComparePolicy<T, Implementation>  {

	using Implementation<T>::getValue;
	using Implementation<T>::assign;

protected:

	inline IteratorTemplate(const typename Implementation<T>::InitParam& initParam)
		: Implementation<T>(initParam)
	{
	}

public:

	typedef IteratorTemplate<T, Implementation, MovePolicy, ComparePolicy> IteratorType;

	inline IteratorTemplate(const Implementation<T>& other)
		: Implementation<T>(other)
	{
	}

	inline const IteratorType& operator =(const Implementation<T>& right)
	{
		assign(right);
		return *this;
	}

	inline T operator *()
	{
		getValue();
	}

	inline T operator *() const
	{
		getValue();
	}


};



} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_IteratorTemplate_h