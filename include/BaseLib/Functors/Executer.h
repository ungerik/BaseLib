/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Executer_h
#define BaseLib_Functors_Executer_h



#include "BaseLib/Functors/Enumerator.h"
#include "BaseLib/Functors/Functor1.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class Executer : public Enumerator<T> {
public:

	typedef Functor1<void, const T&> Functor;

	Executer<T>(const Functor& forFunctor)
		: functor(forFunctor)
	{
	}

	virtual void enumerate(const T& value) const
	{
		(*functor)(value);
	}

private:

	const Functor& functor;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Executer_h
