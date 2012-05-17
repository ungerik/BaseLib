/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_DateTime_h
#define BaseLib_System_DateTime_h



#include "BaseLib/System/Locale.h"
#ifndef BL_NO_ICU



#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace System {



using BaseLib::Strings::String;
using BaseLib::Functors::Enumerator;
using BaseLib::System::Locale;



class BL_EXPORT DateTime : public BaseLib::Reflection::Object {
public:

	/**
	Formats and parses DateTime values.

	Date and time formats are specified by date and time pattern strings.
	Within date and time pattern strings, unquoted letters from 'A' to 'Z' and from 'a' to 'z' are interpreted as
	pattern letters representing the components of a date or time string.
	Text can be quoted using single quotes (') to avoid interpretation.
	"''" represents a single quote.
	All other characters are not interpreted;
	they're simply copied into the output string during formatting or matched against the input string during parsing. 

	The following pattern letters are defined (all other characters from 'A' to 'Z' and from 'a' to 'z' are reserved): 

	@code
	Letter  Date or Time Component  Presentation       Examples
	G       Era designator          Text               AD  
	y       Year                    Year               1996; 96  
	M       Month in year           Month              July; Jul; 07  
	w       Week in year            Number             27  
	W       Week in month           Number             2  
	D       Day in year             Number             189  
	d       Day in month            Number             10  
	F       Day of week in month    Number             2  
	E       Day in week             Text               Tuesday; Tue  
	a       Am/pm marker            Text               PM  
	H       Hour in day (0-23)      Number             0  
	k       Hour in day (1-24)      Number             24  
	K       Hour in am/pm (0-11)    Number             0  
	h       Hour in am/pm (1-12)    Number             12  
	m       Minute in hour          Number             30  
	s       Second in minute        Number             55  
	S       Millisecond             Number             978  
	z       Time zone               General time zone  Pacific Standard Time; PST; GMT-08:00  
	Z       Time zone               RFC 822 time zone  -0800  
	@endcode

	The following examples show how date and time patterns are interpreted in the U.S. locale.
	The given date and time are 2001-07-04 12:08:56 local time in the U.S. Pacific Time time zone. 
	@code
	Date and Time Pattern           Result  
	"yyyy.MM.dd G 'at' HH:mm:ss z"  2001.07.04 AD at 12:08:56 PDT  
	"EEE, MMM d, ''yy"              Wed, Jul 4, '01  
	"h:mm a"                        12:08 PM  
	"hh 'o''clock' a, zzzz"         12 o'clock PM, Pacific Daylight Time  
	"K:mm a, z"                     0:08 PM, PDT  
	"yyyyy.MMMMM.dd GGG hh:mm aaa"  02001.July.04 AD 12:08 PM  
	"EEE, d MMM yyyy HH:mm:ss Z"    Wed, 4 Jul 2001 12:08:56 -0700  
	"yyMMddHHmmssZ"                 010704120856-0700  
	"yyyy-MM-dd'T'HH:mm:ss.SSSZ"    2001-07-04T12:08:56.235-0700  
	@endcode
	*/
	class BL_EXPORT Format {
	public:

		enum Style {
			NONE = -1,
			FULL,
			LONG,
			MEDIUM,
			SHORT
		};

		Format(Style dateStyle = MEDIUM, Style timeStyle = MEDIUM, const String& locale = Locale::getDefault(), const String& timeZone = Empty());
		Format(const String& pattern, const String& locale = Locale::getDefault(), const String& timeZone = Empty());
		Format(const DateTime& dateTimeForLocaleAndTimeZone, Style dateStyle = MEDIUM, Style timeStyle = MEDIUM);
		Format(const DateTime& dateTimeForLocaleAndTimeZone, const String& pattern);
		Format(const Format& other);
		~Format();

		Format& operator =(const Format& right);
		Format& operator =(const String& right);
		operator String() const;

		String format(const DateTime& dateTime) const;
		void parse(const String& dateTimeString, DateTime& dateTime) const;

		bool isLenientParsing() const;
		void setLenientParsing(bool newLenientParsing);

		double get2DigitYearStart() const;
		void set2DigitYearStart(double new2DigitYearStart);

		String getWeekDayName(int dayOfWeek) const; // Starts with 0 = SUNDAY
		String getShortWeekDayName(int dayOfWeek) const; // Starts with 0 = SUNDAY
		String getNarrowWeekDayName(int dayOfWeek) const; // Starts with 0 = SUNDAY

		String getMonthName(int month) const; // Starts with 1 = JANUARY
		String getShortMonthName(int month) const; // Starts with 1 = JANUARY
		String getNarrowMonthName(int month) const; // Starts with 1 = JANUARY

		//String getQuarter(int quarter) const; // Starts with 1
		//String getShortQuarter(int quarter) const; // Starts with 1

	private:

		void* dateFormat;
	};

	friend Format;
	friend DateTime;

	enum WeekDay {
		SUNDAY,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY
	};

	enum Month {
	  JANUARY = 1,
	  FEBRUARY,
	  MARCH,
	  APRIL,
	  UCAL_MAY,
	  JUNE,
	  JULY,
	  AUGUST,
	  SEPTEMBER,
	  OCTOBER,
	  NOVEMBER,
	  DECEMBER
	};

	enum DisplayTimeZoneType {
		DISPLAY_TIME_ZONE_STANDARD,
		DISPLAY_TIME_ZONE_SHORT_STANDARD,
		DISPLAY_TIME_ZONE_DST,
		DISPLAY_TIME_ZONE_SHORT_DST
	};

	static void enumAllTimeZones(const Enumerator<String>& enumerator);

	static String getDefaultTimeZone();
	static void setDefaultTimeZone(const String& timeZoneId);

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::System::DateTime);

	explicit DateTime(const String& forLocale = Locale::getDefault(), const String& forTimeZone = getDefaultTimeZone());
	DateTime(double millis, const String& forLocale = Locale::getDefault(), const String& forTimeZone = getDefaultTimeZone());
	DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, const String& forLocale = Locale::getDefault(), const String& forTimeZone = getDefaultTimeZone());	
	inline DateTime(const DateTime& other)
		: calendar(NULL)
		, locale()
	{
		operator =(other);
	}
	~DateTime();

	operator double() const;
	DateTime& operator =(double right);
	DateTime& operator =(const DateTime& right);

	inline bool operator ==(const DateTime& right) const
	{
		return this->operator double() == right.operator double();
	}
	inline bool operator !=(const DateTime& right) const
	{
		return !operator ==(right);
	}
	inline bool operator <(const DateTime& right) const
	{
		return this->operator double() < right.operator double();
	}

	String getLocale() const;

	String getTimeZone() const;
	void setTimeZone(const String& timeZoneId);

	String getDisplayTimeZone(DisplayTimeZoneType displayTimeZoneType = DISPLAY_TIME_ZONE_STANDARD, const String& displayLocale = Empty()) const;

	void set(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
	void resetToNow();

	int getYear() const;
	void setYear(int newYear);

	int getMonth() const; // Starts with 1 = JANUARY
	void setMonth(int newMonth); // Starts with 1 = JANUARY

	int getWeekOfMonth() const; // Starts with 1
	void setWeekOfMonth(int newWeekOfMonth); // Starts with 1
	int getWeekOfYear() const; // Starts with 1
	void setWeekOfYear(int newWeekOfYear); // Starts with 1

	int getDayOfMonth() const; // Starts with 1
	void setDayOfMonth(int newDayDayOfMonth); // Starts with 1
	int getDayOfWeek() const; // Starts with 0 = SUNDAY
	void setDayOfWeek(int newDayDayOfWeek); // Starts with 0 = SUNDAY
	int getDayOfYear() const; // Starts with 1
	void setDayOfYear(int newDayDayOfYear); // Starts with 1

	int getHourOfDay() const;
	void setHourOfDay(int newHourOfDay);

	int getMinute() const;
	void setMinute(int newMinute);

	int getSecond() const;
	void setSecond(int newSecond);
	float getSecondAsFloat() const;
	void setSecondAsFloat(float newSecondAsFloat);

	int getMillisecond() const;
	void setMillisecond(int newMillisecond);

	int getMinutesFromGreenwichMeanTime() const;

	bool isInDaylightSavingsTime() const;
	int getDaylightSavingsMinutes() const;

	int getActualWeekOfMonthMaximum() const;
	int getActualDayOfMonthMaximum() const;
	int getActualDayOfYearMaximum() const;

	void addYears(int amount);
	void addMonths(int amount);
	void addWeeks(int amount);
	void addDays(int amount);
	void addHours(int amount);
	void addMinutes(int amount);
	void addSeconds(int amount);
	void addMilliseconds(int amount);

	void rollYears(int amount);
	void rollMonths(int amount);
	void rollWeeks(int amount);
	void rollDays(int amount);
	void rollHours(int amount);
	void rollMinutes(int amount);
	void rollSeconds(int amount);
	void rollMilliseconds(int amount);

	bool dateEquals(const DateTime& other) const;
	bool dayTimeEquals(const DateTime& other, bool compareSeconds = true, bool compareMilliseconds = true) const;

	void setDate(const DateTime& other);
	void setDayTime(const DateTime& other);

private:

	void* calendar;
	String locale;
	String timeZone;

};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BL_NO_ICU
#endif // #ifndef BaseLib_System_DateTime_h
