/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_Factory0_h
#define BaseLib_Utilities_Factory0_h



#include "BaseLib/Functors/Functor0.h"
#include "BaseLib/Containers/StringMap.h"



namespace BaseLib {
namespace Utilities {



using BaseLib::Containers::StringMap;
using BaseLib::Strings::String;
using BaseLib::Functors::Functor0;
using BaseLib::Functors::FunctorType;



template<typename R>
class Factory0 {
public:

	typedef Functor0<R*> Functor;
	typedef R ResultType;

	inline Factory0()
		: functors()
	{
	}

	inline ~Factory0()
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

	inline ResultType* create(const String& name) const
	{
		Functors::ConstIterator i = functors.find(name);
		return i != functors.end() ? i->second->execute() : NULL;
	}

private:

	template<typename T>
	class DefaultFunctor : public Functor0<R*> {
	public:

		virtual R* execute() const
		{
			return new T();
		}
		
		virtual FunctorType getFunctorType() const
		{
			return BaseLib::Functors::CUSTOM_FUNCTOR;
		}

		virtual bool operator ==(const Functor0<R*>& right) const
		{
			return false;
		}

		virtual Functor0<R*>* clone() const
		{
			return new DefaultFunctor<T>();
		}
	};

	typedef StringMap<Functor*> Functors;
	Functors functors;
};



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_Factory0_h

