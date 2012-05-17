/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/Time.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Utilities/AutoArray.h"
#include "BaseLib/intern/Windows.h"

#ifdef BL_PLATFORM_WIN32
	#include <mmsystem.h> // winmm.lib
#endif



namespace BaseLib {
namespace System {



using namespace BaseLib::Utilities;



const double Time::VERY_LONG = 10.0 * 365.0 * 24.0 * 3600.0;


	

bool getTimeInitialized = false;
//double firstTime = 0.0;
#ifdef BL_PLATFORM_WIN32
	bool performanceTimerAvailable = false;
	double ooPerformanceTimerFrequency = 0.0;
	//int64 performanceTimerFirstTime = 0;
#endif



void initializeGetTime()
{
	#ifdef BL_PLATFORM_WIN32
		int64 performanceTimerFrequency;
		performanceTimerAvailable = QueryPerformanceFrequency(&makeLargeInt(performanceTimerFrequency)) != 0;
		BL_ASSERT(performanceTimerFrequency > 0);
		ooPerformanceTimerFrequency = 1.0 / static_cast<double>(performanceTimerFrequency);
		/*
		if (performanceTimerAvailable == true)
		{
			QueryPerformanceCounter(&makeLargeInt(performanceTimerFirstTime));
		}
		firstTime = performanceTimerAvailable == true ? performanceTimerFirstTime * ooPerformanceTimerFrequency : Time::nowInSeconds();
		*/
	#endif
    getTimeInitialized = true;
}



double Time::nowInSeconds()
{
    if (getTimeInitialized == false)
    {
        initializeGetTime();
		//return 0.0;
    }

	#ifdef BL_PLATFORM_WIN32
		if (performanceTimerAvailable)
		{
			int64 performanceTimerTime;
			QueryPerformanceCounter(&makeLargeInt(performanceTimerTime));
			return (performanceTimerTime/* - performanceTimerFirstTime*/) * ooPerformanceTimerFrequency;
		}
		else
		{
			TIMECAPS timeCaps;
			timeGetDevCaps(&timeCaps, sizeof(timeCaps));
			timeBeginPeriod(timeCaps.wPeriodMin);
			double result = timeGetTime() * 0.001;
			timeEndPeriod(timeCaps.wPeriodMin);
			return result/* - firstTime*/;
		}
	#else
		return 0.0;
	#endif
}



} // namespace System
} // namespace BaseLib

