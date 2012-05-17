/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_NullHandle_h
#define BaseLib_System_NullHandle_h



#include "BaseLib/System/AbstractHandle.h"



namespace BaseLib {
namespace System {



class BL_EXPORT NullHandle : public AbstractHandle {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::System::NullHandle, AbstractHandle);

	static const NullHandle INSTANCE;

	virtual String getValueAsString() const;
	virtual AbstractHandle* clone() const;
	virtual bool isValid() const;

};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_NullHandle_h
