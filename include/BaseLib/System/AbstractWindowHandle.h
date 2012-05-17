/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_AbstractWindowHandle_h
#define BaseLib_System_AbstractWindowHandle_h



#include "BaseLib/System/AbstractHandle.h"



namespace BaseLib {
namespace System {



class BL_EXPORT AbstractWindowHandle : public AbstractHandle {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::System::AbstractWindowHandle, AbstractHandle);

	AbstractWindowHandle();

	virtual int getLeft() const = 0;
	virtual int getTop() const = 0;

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	virtual int getClientWidth() const = 0;
	virtual int getClientHeight() const = 0;
};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_AbstractWindowHandle_h
