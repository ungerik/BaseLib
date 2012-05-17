/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Time_h
#define BaseLib_System_Time_h



#include "BaseLib/Types.h"



namespace BaseLib {
namespace System {



class BL_EXPORT Time : public StaticClass {
public:

	/**
	Returns the system-time in seconds.
	The time is as exact as possible on the system.
	*/
	static double nowInSeconds();


	/**
	Returns system-time in seconds.
	The time is as exact as possible on the system.
	@see getTime
	*/
	static inline float nowInSecondsAsFloat() { return static_cast<float>(nowInSeconds()); }



	static const double VERY_LONG;

private:
	Time();
};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_Time_h
