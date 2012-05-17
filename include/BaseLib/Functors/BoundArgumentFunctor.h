/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_BoundArgumentFunctor_h
#define BaseLib_Functors_BoundArgumentFunctor_h



#include "BaseLib/Functors/Functor0.h"
#include "BaseLib/Functors/Functor1.h"
#include "BaseLib/Utilities/AutoPointer.h"



namespace BaseLib {
namespace Functors {



using BaseLib::Utilities::AutoPointer;



template<typename R, typename A0>
class BoundArgumentFunctor : public Functor0<R> {
public:

	typedef Functor1<R, A0> BoundFunctor;

	BoundArgumentFunctor(const BoundFunctor& boundFunctor, A0 boundArgumentValue)
		: functor(boundFunctor.clone())
		, boundValue(boundArgumentValue)
	{
	}

	BoundArgumentFunctor(BoundFunctor* boundFunctor, A0 boundArgumentValue) // takes ownership
		: functor(boundFunctor)
		, boundValue(boundArgumentValue)
	{
	}

	virtual R execute() const
	{
		return functor->execute(boundValue);
	}

	virtual FunctorType getFunctorType() const
	{
		return CUSTOM_FUNCTOR;
	}

	virtual bool operator ==(const Functor0<R>& right) const
	{
		return false;
	}

	virtual Functor0<R>* clone() const
	{
		return new BoundArgumentFunctor(*functor, boundValue);
	}

private:

	AutoPointer<BoundFunctor> functor;
	A0 boundValue;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor1_h
