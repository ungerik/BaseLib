/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_EventObserver_h
#define BaseLib_Functors_EventObserver_h



#include "BaseLib/Functors/EventManager.h"



namespace BaseLib {
namespace Functors {



template<class F>
class EventObserver {
public:

	typedef F FunctorType;

	template<class F_>
	friend class EventManager;

	EventObserver(const FunctorType& newFunctor, EventManager<FunctorType>* newEvent = NULL)
		: functor(newFunctor.clone())
		, event(NULL) // Gets set by EventManager::addObserver()
	{
		if (newEvent != NULL)
		{
			newEvent->addObserver(this);
		}
	}

	virtual ~EventObserver()
	{
		if (event != NULL)
		{
			event->removeObserver(this);
		}
	}

	inline const FunctorType& getFunctor() const
	{
		return *functor;
	}

	inline void setFunctor(const FunctorType& newFunctor)
	{
		functor = newFunctor.clone();
	}

	inline EventManager<FunctorType>* getEvent()
	{
		return event;
	}
	inline const EventManager<FunctorType>* getEvent() const
	{
		return event;
	}

private:

	FunctorType* functor;
	EventManager<FunctorType>* event;

};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_EventObserver_h
