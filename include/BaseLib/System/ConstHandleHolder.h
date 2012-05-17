/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_ConstHandleHolder_h
#define BaseLib_System_ConstHandleHolder_h



#include "BaseLib/System/AbstractHandle.h"
#include "BaseLib/Utilities/AutoPointer.h"



namespace BaseLib {
namespace System {



class HandleHolder;
using BaseLib::Utilities::AutoPointer;



class BL_EXPORT ConstHandleHolder : public AbstractHandle {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::System::ConstHandleHolder, AbstractHandle);

	ConstHandleHolder(const AbstractHandle* forHandle = NULL);
	ConstHandleHolder(const AbstractHandle& other); // creates and holds a clone
	ConstHandleHolder(const ConstHandleHolder& other); // creates and holds a clone
	ConstHandleHolder(const ConstHandleHolder* other); // creates and holds a clone

	ConstHandleHolder(const HandleHolder& other); // creates and holds a clone
	ConstHandleHolder(const HandleHolder* other); // creates and holds a clone

	virtual String getValueAsString() const;
	virtual AbstractHandle* clone() const;
	virtual bool isValid() const;

	inline const AbstractHandle* getHoldedHandle() const
	{
		return holdedHandle;
	}

protected:

	const AutoPointer<const AbstractHandle> holdedHandle;
};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_ConstHandleHolder_h
