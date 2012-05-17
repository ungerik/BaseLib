/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_AbstractHandle_h
#define BaseLib_System_AbstractHandle_h



#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace System {



using BaseLib::Strings::String;



class BL_EXPORT AbstractHandle : public BaseLib::Reflection::Object {
public:

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::System::AbstractHandle);

	AbstractHandle();
	virtual ~AbstractHandle();

	virtual String getValueAsString() const = 0;
	virtual AbstractHandle* clone() const = 0;
	virtual bool isValid() const = 0;

};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_AbstractHandle_h
