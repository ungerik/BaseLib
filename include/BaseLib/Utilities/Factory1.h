/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_Factory1_h
#define BaseLib_Utilities_Factory1_h



#include "BaseLib/Functors/Functor1.h"
#include "BaseLib/Containers/StringMap.h"



namespace BaseLib {
namespace Utilities {



using BaseLib::Containers::StringMap;
using BaseLib::Strings::String;
using BaseLib::Functors::Functor1;
using BaseLib::Functors::FunctorType;



template<class R, typename A0>
class Factory1 {
public:

	typedef Functor1<R*, A0> Functor;
	typedef R ResultType;

	inline Factory1()
		: functors()
	{
	}

	inline ~Factory1()
	{
		foreach (Functors::Iterator, i, functors)
		{
			delete i->second;
		}
	}

	inline void addFunctor(const String& name, const Functor& newFunctor)
	{
		functors[name] = newFunctor.clone();
	}

	template<typename T>
	inline void addFunctor(const String& name)
	{
		functors[name] = new DefaultFunctor<T>();
	}

	inline void removeFunctor(const String& name)
	{
		functors.erase(name);
	}

	inline ResultType* create(const String& name, A0 arg0) const
	{
		Functors::ConstIterator i = functors.find(name);
		return i != functors.end() ? i->second->execute(arg0) : NULL;
	}

private:

	template<typename T>
	class DefaultFunctor : public Functor1<R*, A0> {
	public:

		virtual R* execute(A0 arg0) const
		{
			return new T(arg0);
		}
		
		virtual FunctorType getFunctorType() const
		{
			return BaseLib::Functors::CUSTOM_FUNCTOR;
		}

		virtual bool operator ==(const Functor1<R*, A0>& right) const
		{
			return false;
		}

		virtual Functor1<R*, A0>* clone() const
		{
			return new DefaultFunctor<T>();
		}
	};

	typedef StringMap<Functor*> Functors;
	Functors functors;
};



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_Factory1_h

