/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_MultiEnumerator_h
#define BaseLib_Functors_MultiEnumerator_h



#include "BaseLib/Functors/Enumerator.h"
#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Functors {



using BaseLib::Containers::Array;



template<typename T>
class MultiEnumerator : public Enumerator<T> {
public:

	MultiEnumerator<T>()
		: enumerators()
	{
	}

	MultiEnumerator<T>(const Enumerator<T>& enum0)
		: enumerators()
	{
		enumerators += enum0;
	}

	MultiEnumerator<T>(const Enumerator<T>& enum0, const Enumerator<T>& enum1)
		: enumerators()
	{
		enumerators += enum0;
		enumerators += enum1;
	}

	MultiEnumerator<T>(const Enumerator<T>& enum0, const Enumerator<T>& enum1, const Enumerator<T>& enum2)
		: enumerators()
	{
		enumerators += enum0;
		enumerators += enum1;
		enumerators += enum2;
	}

	inline void add(const Enumerator<T>& newEnumerator)
	{
		enumerators += &newEnumerator;
	}

	inline void remove(const Enumerator<T>& oldEnumerator)
	{
		enumerators -= &oldEnumerator;
	}

	virtual void enumerate(const T& value) const
	{
		for (int i = 0; i < enumerators.getLength(); ++i)
		{
			enumerators[i].enumerate(value);
		}
	}

private:

	Array<const Enumerator<T>*> enumerators;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_MultiEnumerator_h
