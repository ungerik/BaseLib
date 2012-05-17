/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_EventManager_h
#define BaseLib_Functors_EventManager_h



#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Functors {



template<class F>
class EventObserver;



template<class F>
class EventManager {
public:

	typedef F FunctorType;

	inline EventManager()
		: observers()
	{
	}

	virtual ~EventManager();

	void addObserver(EventObserver<FunctorType>* newObserver);
	void removeObserver(EventObserver<FunctorType>* oldObserver);

	inline int getObserverCount() const
	{
		return observers.getCount();
	}

	inline EventObserver<FunctorType>* getObserver(int index)
	{
		return observers[index];
	}
	inline const EventObserver<FunctorType>* getObserver(int index) const
	{
		return observers[index];
	}

protected:

	typedef BaseLib::Containers::Array<EventObserver<FunctorType>*> Observers;
	Observers observers;

};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_EventManager_h
