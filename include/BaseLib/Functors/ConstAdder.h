/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_ConstAdder_h
#define BaseLib_Functors_ConstAdder_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename C, typename T>
class ConstAdder : public Enumerator<T> {
public:

	ConstAdder<C, T>(C& forBase, const C& value)
		: base(forBase)
		, addValue(value)
	{
	}

	virtual void enumerate(const T& value) const
	{
		base += addValue;
	}

private:

	C& base;
	C addValue;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_ConstAdder_h
