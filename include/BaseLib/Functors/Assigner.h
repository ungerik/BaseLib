/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Assigner_h
#define BaseLib_Functors_Assigner_h



#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Functors {



template<typename C, typename T>
class Assigner : public Enumerator<T> {
public:

	Assigner<C, T>(C& forBase)
		: base(forBase)
	{
	}

	virtual void enumerate(const T& value) const
	{
		base = value;
	}

private:

	C& base;
};


} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Assigner_h
