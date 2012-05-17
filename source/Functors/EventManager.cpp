/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename F>
EventManager<F>::~EventManager()
{
	const int count = observers.getLength();
	for (int i = 0; i < count; ++i)
	{
		observers[i]->setEvent(NULL);
	}
}



template<typename F>
void EventManager<F>::addObserver(EventObserver<FunctorType>* newObserver)
{
	if (checkArgumentNotNull(NAME_VALUE(newObserver)) == true)
	{
		observers += newObserver;
		newObserver->event = this;
	}
}



template<typename F>
void EventManager<F>::removeObserver(EventObserver<FunctorType>* oldObserver)
{
	if (checkArgumentNotNull(NAME_VALUE(oldObserver)) == true)
	{
		observers -= oldObserver;
		oldObserver->event = NULL;
	}
}



} // namespace Functors
} // namespace BaseLib
