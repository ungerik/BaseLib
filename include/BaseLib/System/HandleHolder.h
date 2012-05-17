/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_HandleHolder_h
#define BaseLib_System_HandleHolder_h



#include "BaseLib/System/AbstractHandle.h"



namespace BaseLib {
namespace System {



class ConstHandleHolder;
using BaseLib::Utilities::AutoPointer;



class BL_EXPORT HandleHolder : public AbstractHandle {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::System::HandleHolder, AbstractHandle);

	HandleHolder(AbstractHandle* forHandle = NULL);
	HandleHolder(const AbstractHandle& other); // creates and holds a clone
	HandleHolder(const HandleHolder& other); // creates and holds a clone
	HandleHolder(const HandleHolder* other); // creates and holds a clone
	
	inline HandleHolder& operator=(const AbstractHandle& right) // creates and holds a clone
	{
		holdedHandle = right.clone();
		return *this;
	}

	inline HandleHolder& operator=(const HandleHolder& right) // creates and holds a clone
	{
		holdedHandle = (right.getHoldedHandle() != NULL) ? right.getHoldedHandle()->clone() : NULL;
		return *this;
	}

	HandleHolder(const ConstHandleHolder& other); // creates and holds a clone
	HandleHolder(const ConstHandleHolder* other); // creates and holds a clone
	HandleHolder& operator=(const ConstHandleHolder& right); // creates and holds a clone

	virtual String getValueAsString() const;
	virtual AbstractHandle* clone() const;
	virtual bool isValid() const;

	inline AbstractHandle* getHoldedHandle()
	{
		return holdedHandle;
	}

	inline const AbstractHandle* getHoldedHandle() const
	{
		return holdedHandle;
	}

	inline void setHoldedHandle(AbstractHandle* newHoldedHandle)
	{
		holdedHandle = newHoldedHandle;
	}

protected:

	AutoPointer<AbstractHandle> holdedHandle;
};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_HandleHolder_h
