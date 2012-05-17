/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Win32_InstanceHandle_h
#define BaseLib_System_Win32_InstanceHandle_h



#include "BaseLib/System/AbstractHandle.h"
#include "BaseLib/intern/Windows.h"



namespace BaseLib {
namespace System {
namespace Win32 {



using BaseLib::System::AbstractHandle;
using BaseLib::Strings::String;



class BL_EXPORT InstanceHandle : public AbstractHandle {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::System::Win32::InstanceHandle, AbstractHandle);

	static InstanceHandle* castFrom(AbstractHandle* abstractHandle);
	static const InstanceHandle* castFrom(const AbstractHandle* abstractHandle);

	InstanceHandle(HINSTANCE newValue = 0);

	virtual String getValueAsString() const;
	virtual AbstractHandle* clone() const;
	virtual bool isValid() const;

	inline operator HINSTANCE() const
	{
		return value;
	}

	inline InstanceHandle& operator =(HINSTANCE right)
	{
		value = right;
		return *this;
	}

	inline HINSTANCE getValue() const
	{
		return value;
	}

private:

	HINSTANCE value;
};



} // namespace Win32
} // namespace Handles
} // namespace Ygui



#endif // #ifndef BaseLib_System_Win32_InstanceHandle_h
