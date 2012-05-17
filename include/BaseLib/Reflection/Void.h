/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_Void_h
#define BaseLib_Reflection_Void_h



#include "BaseLib/Reflection/BoxedValueType.h"



namespace BaseLib {
namespace Reflection {



class BL_EXPORT Void : public BoxedValueType {
public:

	typedef Void Type;
	typedef void ValueType;

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Reflection::Void, BoxedValueType);

	Void(ValueType);

	ValueType getValue() const;
	virtual void setValue(ValueType);

	inline ValueType operator ()() const
	{
	}

	inline operator ValueType() const
	{
	}

};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_Void_h