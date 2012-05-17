/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_ValueAtIndexFinder_h
#define BaseLib_Functors_ValueAtIndexFinder_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename T>
class ValueAtIndexFinder : public Counter<T> {
public:

	ValueAtIndexFinder<T>(int atIndex, const T& defaultResult = T())
		: counter(-1)
		, index(atIndex)
		, result(defaultResult)
		, found(false)
	{
	}

	virtual void enumerate(const T& value) const
	{
		++counter;
		if (index == counter)
		{
			found = true;
			result = value;
		}
	}

	virtual bool stop() const
	{
		return found;
	}

	inline bool hasResult() const
	{
		return found;
	}

	inline int getIndex() const
	{
		return index;
	}

	inline void setIndex(int newIndex)
	{
		index = newIndex;
	}

	inline const T& getValue() const
	{
		return result;
	}

private:

	mutable int counter;
	int index;
	mutable T result;
	mutable bool found;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_ValueAtIndexFinder_h
