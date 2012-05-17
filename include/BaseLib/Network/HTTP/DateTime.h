/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_HTTP_DateTime_h
#define BaseLib_HTTP_DateTime_h


#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Network {
namespace HTTP {



using BaseLib::Strings::String;


/*
HTTP-date    = rfc1123-date | rfc850-date | asctime-date
       rfc1123-date = wkday "," SP date1 SP time SP "GMT"
       rfc850-date  = weekday "," SP date2 SP time SP "GMT"
       asctime-date = wkday SP date3 SP time SP 4DIGIT
       date1        = 2DIGIT SP month SP 4DIGIT
                      ; day month year (e.g., 02 Jun 1982)
       date2        = 2DIGIT "-" month "-" 2DIGIT
                      ; day-month-year (e.g., 02-Jun-82)
       date3        = month SP ( 2DIGIT | ( SP 1DIGIT ))
                      ; month day (e.g., Jun  2)
       time         = 2DIGIT ":" 2DIGIT ":" 2DIGIT
                      ; 00:00:00 - 23:59:59
       wkday        = "Mon" | "Tue" | "Wed"
                    | "Thu" | "Fri" | "Sat" | "Sun"
       weekday      = "Monday" | "Tuesday" | "Wednesday"
                    | "Thursday" | "Friday" | "Saturday" | "Sunday"
       month        = "Jan" | "Feb" | "Mar" | "Apr"
                    | "May" | "Jun" | "Jul" | "Aug"
                    | "Sep" | "Oct" | "Nov" | "Dec"
*/

class BL_EXPORT DateTime {
public:

	enum Format {
		RFC_1123_FORMAT,
		RFC_850_FORMAT,
		RFC_ASCTIME_FORMAT
	};

	DateTime(const String& dateTimeString);

	inline Format getDefaultFormat() const { return defaultFormat; }
	inline void setDefaultFormat(Format newDefaultFormat) { defaultFormat = newDefaultFormat; }

	inline operator String() const { return getDefaultFormated(); }

	String getDefaultFormated() const;
	String getRfc1123Formated() const;
	String getRfc850Formated() const;
	String getAsctimeFormated() const;


protected:

	Format defaultFormat;


};



} // namespace HTTP
} // namespace Network
} // namespace BaseLib



#endif // #ifndef BaseLib_HTTP_DateTime_h
