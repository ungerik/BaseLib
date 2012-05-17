/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef CppUtilities_ListenerHolder_h
#define CppUtilities_ListenerHolder_h



#include "Array.h"



namespace CppUtilities {


template<class T, class L = Array<T*> >
class ListenerHolder {
protected:

	typedef typename L Listeners;
	Listeners listeners;

public:

	void addListener(T* newListener)
	{
		listeners.append(newListener);
	}

	void removeListener(T* oldListener)
	{
		Listeners::Iterator i = listeners.findFirst(oldListener);
		if (i != listeners.end())
		{
			listeners.remove(i);
		}
	}
};

} // namespace CppUtilities



#endif // #ifndef CppUtilities_ListenerHolder_h