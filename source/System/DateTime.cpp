/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/DateTime.h"
#ifndef BL_NO_ICU



#include "BaseLib/ErrorHandling.h"
#include <unicode/udat.h>
#include <unicode/uloc.h>
#include <unicode/ucal.h>



BaseLib::Strings::String getIcuError(UErrorCode errorCode);



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;



int getCalendarValue(const void* calendar, UCalendarDateFields dateField)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	const int result = ucal_get(static_cast<const UCalendar*>(calendar), dateField, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return result;
}



DateTime::Format::Format(Style dateStyle, Style timeStyle, const String& locale, const String& timeZone)
	: dateFormat(NULL)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	dateFormat = udat_open(
		static_cast<UDateFormatStyle>(timeStyle),
		static_cast<UDateFormatStyle>(dateStyle),
		locale.getChar8CString(),
		timeZone.isEmpty() == true ? NULL : timeZone.getChar16Array(),
		timeZone.getLength(),
		NULL,
		0,
		&errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



DateTime::Format::Format(const String& pattern, const String& locale, const String& timeZone)
	: dateFormat(NULL)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	dateFormat = udat_open(
		UDAT_IGNORE,
		UDAT_IGNORE,
		locale.getChar8CString(),
		timeZone.isEmpty() == true ? NULL : timeZone.getChar16Array(),
		timeZone.getLength(),
		pattern.getChar16Array(),
		pattern.getLength(),
		&errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



DateTime::Format::Format(const Format& other)
	: dateFormat(NULL)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	dateFormat = udat_clone(static_cast<const UDateFormat*>(other.dateFormat), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



DateTime::Format::Format(const DateTime& dateTimeForLocaleAndTimeZone, Style dateStyle, Style timeStyle)
	: dateFormat(NULL)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	dateFormat = udat_open(
		static_cast<UDateFormatStyle>(timeStyle),
		static_cast<UDateFormatStyle>(dateStyle),
		dateTimeForLocaleAndTimeZone.getLocale().getChar8CString(),
		dateTimeForLocaleAndTimeZone.getTimeZone().getChar16Array(),
		dateTimeForLocaleAndTimeZone.getTimeZone().getLength(),
		NULL,
		0,
		&errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



DateTime::Format::Format(const DateTime& dateTimeForLocaleAndTimeZone, const String& pattern)
	: dateFormat(NULL)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	dateFormat = udat_open(
		UDAT_IGNORE,
		UDAT_IGNORE,
		dateTimeForLocaleAndTimeZone.getLocale().getChar8CString(),
		dateTimeForLocaleAndTimeZone.getTimeZone().getChar16Array(),
		dateTimeForLocaleAndTimeZone.getTimeZone().getLength(),
		pattern.getChar16Array(),
		pattern.getLength(),
		&errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



DateTime::Format::~Format()
{
	udat_close(static_cast<UDateFormat*>(dateFormat));
}



DateTime::Format& DateTime::Format::operator =(const Format& right)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	UDateFormat* clonedDateFormat = udat_clone(static_cast<const UDateFormat*>(right.dateFormat), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	else
	{
		udat_close(static_cast<UDateFormat*>(dateFormat));
		dateFormat = clonedDateFormat;
	}
	return *this;
}



DateTime::Format& DateTime::Format::operator =(const String& right)
{
	udat_applyPattern(static_cast<UDateFormat*>(dateFormat), TRUE, right.getChar16Array(), right.getLength());

	//UErrorCode errorCode = U_ZERO_ERROR;
	//UDateFormat* newDateFormat = udat_open(
	//	UDAT_FULL,
	//	UDAT_FULL,
	//	uloc_getDefault(),
	//	NULL,
	//	0,
	//	right.getChar16Array(),
	//	right.getLength(),
	//	&errorCode);
	//if (U_FAILURE(errorCode))
	//{
	//	resultError(getIcuError(errorCode) + ERROR_AT);
	//}
	//else
	//{
	//	udat_close(static_cast<UDateFormat*>(dateFormat));
	//	dateFormat = newDateFormat;
	//}
	return *this;
}



DateTime::Format::operator String() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = udat_toPattern(static_cast<const UDateFormat*>(dateFormat), TRUE, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String DateTime::Format::format(const DateTime& dateTime) const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = udat_format(static_cast<const UDateFormat*>(dateFormat), dateTime, buffer, 256, NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



void DateTime::Format::parse(const String& dateTimeString, DateTime& dateTime) const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	udat_parseCalendar(static_cast<UDateFormat*>(dateFormat), static_cast<UCalendar*>(dateTime.calendar), dateTimeString.getChar16Array(), dateTimeString.getLength(), NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



bool DateTime::Format::isLenientParsing() const
{
	return udat_isLenient(static_cast<const UDateFormat*>(dateFormat)) == TRUE;
}



void DateTime::Format::setLenientParsing(bool newLenientParsing)
{
	udat_setLenient(static_cast<UDateFormat*>(dateFormat), newLenientParsing);
}



double DateTime::Format::get2DigitYearStart() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	const double result = udat_get2DigitYearStart(static_cast<const UDateFormat*>(dateFormat), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return result;
}



void DateTime::Format::set2DigitYearStart(double new2DigitYearStart)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	udat_set2DigitYearStart(static_cast<UDateFormat*>(dateFormat), new2DigitYearStart, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



String getTranslatedSymbol(const UDateFormat* dateFormat, UDateFormatSymbolType symbolType, int index)
{
	BL_ASSERT(index >= 0 && index < udat_countSymbols(dateFormat, symbolType));

	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int length = udat_getSymbols(dateFormat, symbolType, index, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, length);
}



String DateTime::Format::getWeekDayName(int dayOfWeek) const
{
	if (checkArgumentRange(NAME_VALUE(dayOfWeek), 0, 6) == true)
	{
		return getTranslatedSymbol(static_cast<const UDateFormat*>(dateFormat), UDAT_WEEKDAYS, dayOfWeek);
	}
	else
	{
		return Empty();
	}
}



String DateTime::Format::getShortWeekDayName(int dayOfWeek) const
{
	if (checkArgumentRange(NAME_VALUE(dayOfWeek), 0, 6) == true)
	{
		return getTranslatedSymbol(static_cast<const UDateFormat*>(dateFormat), UDAT_SHORT_WEEKDAYS, dayOfWeek);
	}
	else
	{
		return Empty();
	}
}



String DateTime::Format::getNarrowWeekDayName(int dayOfWeek) const
{
	if (checkArgumentRange(NAME_VALUE(dayOfWeek), 0, 6) == true)
	{
		return getTranslatedSymbol(static_cast<const UDateFormat*>(dateFormat), UDAT_NARROW_WEEKDAYS , dayOfWeek);
	}
	else
	{
		return Empty();
	}
}


String DateTime::Format::getMonthName(int month) const
{
	if (checkArgumentRange(NAME_VALUE(month), 1, 12) == true)
	{
		return getTranslatedSymbol(static_cast<const UDateFormat*>(dateFormat), UDAT_MONTHS, month - 1);
	}
	else
	{
		return Empty();
	}
}



String DateTime::Format::getShortMonthName(int month) const
{
	if (checkArgumentRange(NAME_VALUE(month), 1, 12) == true)
	{
		return getTranslatedSymbol(static_cast<const UDateFormat*>(dateFormat), UDAT_SHORT_MONTHS, month - 1);
	}
	else
	{
		return Empty();
	}
}



String DateTime::Format::getNarrowMonthName(int month) const
{
	if (checkArgumentRange(NAME_VALUE(month), 1, 12) == true)
	{
		return getTranslatedSymbol(static_cast<const UDateFormat*>(dateFormat), UDAT_NARROW_MONTHS, month - 1);
	}
	else
	{
		return Empty();
	}
}




//String DateTime::Format::getQuarter(int quarter) const
//{
//	if (checkArgumentRange(NAME_VALUE(quarter), 1, 4) == true)
//	{
//		return getTranslatedSymbol(static_cast<const UDateFormat*>(dateFormat), UDAT_QUARTERS, quarter - 1);
//	}
//	else
//	{
//		return Empty();
//	}
//}
//
//
//
//String DateTime::Format::getShortQuarter(int quarter) const
//{
//	if (checkArgumentRange(NAME_VALUE(quarter), 1, 4) == true)
//	{
//		return getTranslatedSymbol(static_cast<const UDateFormat*>(dateFormat), UDAT_SHORT_QUARTERS, quarter - 1);
//	}
//	else
//	{
//		return Empty();
//	}
//}




///////////////////////////////////////////////////////////////////////////////




void DateTime::enumAllTimeZones(const Enumerator<String>& enumerator)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	UEnumeration* enumeration = ucal_openTimeZones(&errorCode);
	if (enumeration != NULL)
	{
		for (const char16 * s = uenum_unext(enumeration, NULL, &errorCode); s != NULL; s = uenum_unext(enumeration, NULL, &errorCode))
		{
			enumerator.enumerate(s);
		}
		uenum_close(enumeration);
	}
	else
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



String DateTime::getDefaultTimeZone()
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = ucal_getDefaultTimeZone(buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



void DateTime::setDefaultTimeZone(const String& timeZoneId)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_setDefaultTimeZone(timeZoneId.getChar16CString(), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



BL_DEFINE_REFLECTION_BASE_CLASS(DateTime)
{
	registerProperty("locale", &DateTime::getLocale);
	registerProperty("year", &DateTime::getYear, &DateTime::setYear);
	registerProperty("month", &DateTime::getMonth, &DateTime::setMonth);
	registerProperty("weekOfMonth", &DateTime::getWeekOfMonth, &DateTime::setWeekOfMonth);
	registerProperty("weekOfYear", &DateTime::getWeekOfYear, &DateTime::setWeekOfYear);
	registerProperty("dayOfMonth", &DateTime::getDayOfMonth, &DateTime::setDayOfMonth);
	registerProperty("dayOfWeek", &DateTime::getDayOfWeek, &DateTime::setDayOfWeek);
	registerProperty("dayOfYear", &DateTime::getDayOfYear, &DateTime::setDayOfYear);
	registerProperty("hourOfDay", &DateTime::getHourOfDay, &DateTime::setHourOfDay);
	registerProperty("minute", &DateTime::getMinute, &DateTime::setMinute);
	registerProperty("second", &DateTime::getSecond, &DateTime::setSecond);
	registerProperty("secondAsFloat", &DateTime::getSecondAsFloat, &DateTime::setSecondAsFloat);
	registerProperty("second", &DateTime::getMillisecond, &DateTime::setMillisecond);
	registerProperty("inDaylightSavingsTime", &DateTime::isInDaylightSavingsTime);
	registerProperty("daylightSavingsMinutes", &DateTime::getDaylightSavingsMinutes);
	registerProperty("minutesFromGMT", &DateTime::getMinutesFromGreenwichMeanTime);
	registerProperty("actualWeekOfMonthMaximum", &DateTime::getActualWeekOfMonthMaximum);
	registerProperty("actualDayOfMonthMaximum", &DateTime::getActualDayOfMonthMaximum);
	registerProperty("actualDayOfYearMaximum", &DateTime::getActualDayOfYearMaximum);

	addPropertyMetaTag("weekOfMonth", NON_SERIALIZEABLE);
	addPropertyMetaTag("weekOfYear", NON_SERIALIZEABLE);
	addPropertyMetaTag("dayOfWeek", NON_SERIALIZEABLE);
	addPropertyMetaTag("dayOfYear", NON_SERIALIZEABLE);
	addPropertyMetaTag("secondAsFloat", NON_SERIALIZEABLE);
}



DateTime::DateTime(const String& forLocale, const String& forTimeZone)
	: BaseLib::Reflection::Object()
	, calendar(NULL)
	, locale(forLocale)
	, timeZone(forTimeZone)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	calendar = ucal_open(0, 0, locale.getChar8CString(), UCAL_GREGORIAN, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



DateTime::DateTime(double millis, const String& forLocale, const String& forTimeZone)
	: BaseLib::Reflection::Object()
	, calendar(NULL)
	, locale(forLocale)
	, timeZone(forTimeZone)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	calendar = ucal_open(0, 0, locale.getChar8CString(), UCAL_GREGORIAN, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	else
	{
		operator =(millis);
	}
}



DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, const String& forLocale, const String& forTimeZone)
	: BaseLib::Reflection::Object()
	, calendar(NULL)
	, locale(forLocale)
	, timeZone(forTimeZone)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	calendar = ucal_open(0, 0, locale.getChar8CString(), UCAL_GREGORIAN, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	else
	{
		set(year, month, day, hour, minute, second);
	}
}



DateTime::~DateTime()
{
	ucal_close(static_cast<UCalendar*>(calendar));
}



DateTime::operator double() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	const double result = ucal_getMillis(static_cast<const UCalendar*>(calendar), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return result;
}



DateTime& DateTime::operator =(double right)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_setMillis(static_cast<UCalendar*>(calendar), right, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return *this;
}



DateTime& DateTime::operator =(const DateTime& right)
{
	if (calendar != NULL)
	{
		ucal_close(static_cast<UCalendar*>(calendar));
	}
	UErrorCode errorCode = U_ZERO_ERROR;
	String locale = right.getLocale();
	calendar = ucal_open(0, 0, locale.getChar8CString(), UCAL_GREGORIAN, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	else
	{
		operator =(right.operator double());
	}	
	return *this;
}



String DateTime::getLocale() const
{
	return locale;
}



String DateTime::getTimeZone() const
{
	return timeZone;
}



void DateTime::setTimeZone(const String& timeZoneId)
{
	if (timeZoneId != timeZone)
	{
		UErrorCode errorCode = U_ZERO_ERROR;
		ucal_setTimeZone(static_cast<UCalendar*>(calendar), timeZoneId.getChar16CString(), timeZoneId.getLength(), &errorCode);
		if (U_SUCCESS(errorCode))
		{
			timeZone = timeZoneId;
		}
		else
		{
			resultError(getIcuError(errorCode) + ERROR_AT);
		}
	}
}



String DateTime::getDisplayTimeZone(DisplayTimeZoneType displayTimeZoneType, const String& displayLocale) const
{
	const char* usedDisplayLocale = displayLocale.isEmpty() == false ? displayLocale.getChar8CString() : locale.getChar8CString();
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = ucal_getTimeZoneDisplayName(
		static_cast<const UCalendar*>(calendar),
		static_cast<UCalendarDisplayNameType>(displayTimeZoneType),
		usedDisplayLocale,
		buffer,
		256,
		&errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



//const DateTime::Format GMT_TIME_ZONE_FORMAT("Z", Locale::ENGLISH, "GMT");



int DateTime::getMinutesFromGreenwichMeanTime() const
{
	//String timeZone = GMT_TIME_ZONE_FORMAT.format(*this);
	DateTime::Format format("Z", getLocale(), getTimeZone());
	String timeZone = format.format(*this);

	const int minutes = timeZone.parseInt(1, 2)*60 + timeZone.parseInt(3, 2);
	return timeZone.beginsWith('-') == true ? -minutes : minutes;
}



void DateTime::set(int year, int month, int day, int hour, int minute, int second)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_setDateTime(static_cast<UCalendar*>(calendar), year, month - JANUARY, day, hour, minute, second, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::resetToNow()
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_setMillis(static_cast<UCalendar*>(calendar), ucal_getNow(), &errorCode);
}



int DateTime::getYear() const
{
	return getCalendarValue(calendar, UCAL_YEAR);
}



void DateTime::setYear(int newYear)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_YEAR, newYear);
}



int DateTime::getMonth() const
{
	return getCalendarValue(calendar, UCAL_MONTH) + JANUARY;
}



void DateTime::setMonth(int newMonth)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_MONTH, newMonth - JANUARY);
}



int DateTime::getWeekOfMonth() const
{
	return getCalendarValue(calendar, UCAL_WEEK_OF_MONTH);
}



void DateTime::setWeekOfMonth(int newWeekOfMonth)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_WEEK_OF_MONTH, newWeekOfMonth);
}



int DateTime::getWeekOfYear() const
{
	return getCalendarValue(calendar, UCAL_WEEK_OF_YEAR);
}



void DateTime::setWeekOfYear(int newWeekOfYear)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_WEEK_OF_YEAR, newWeekOfYear);
}



int DateTime::getDayOfMonth() const
{
	return getCalendarValue(calendar, UCAL_DAY_OF_MONTH);
}



void DateTime::setDayOfMonth(int newDayDayOfMonth)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_DAY_OF_MONTH, newDayDayOfMonth);
}



int DateTime::getDayOfWeek() const
{
	return static_cast<WeekDay>(getCalendarValue(calendar, UCAL_DAY_OF_WEEK) - UCAL_SUNDAY);
}



void DateTime::setDayOfWeek(int newDayDayOfWeek)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_DAY_OF_WEEK, newDayDayOfWeek + UCAL_SUNDAY);
}



int DateTime::getDayOfYear() const
{
	return getCalendarValue(calendar, UCAL_DAY_OF_YEAR);
}



void DateTime::setDayOfYear(int newDayDayOfYear)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_DAY_OF_YEAR, newDayDayOfYear);
}



int DateTime::getHourOfDay() const
{
	return getCalendarValue(calendar, UCAL_HOUR_OF_DAY);
}



void DateTime::setHourOfDay(int newHourOfDay)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_HOUR_OF_DAY, newHourOfDay);
}



int DateTime::getMinute() const
{
	return getCalendarValue(calendar, UCAL_MINUTE);
}



void DateTime::setMinute(int newMinute)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_MINUTE, newMinute);
}



int DateTime::getSecond() const
{
	return getCalendarValue(calendar, UCAL_SECOND);
}



void DateTime::setSecond(int newSecond)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_SECOND, newSecond);
}



float DateTime::getSecondAsFloat() const
{
	return getCalendarValue(calendar, UCAL_MILLISECOND) * 0.001f;
}



void DateTime::setSecondAsFloat(float newSecondAsFloat)
{
	setMillisecond(round<int>(newSecondAsFloat * 1000.0f));
}



int DateTime::getMillisecond() const
{
	return getCalendarValue(calendar, UCAL_MILLISECOND);
}



void DateTime::setMillisecond(int newMillisecond)
{
	ucal_set(static_cast<UCalendar*>(calendar), UCAL_MILLISECOND, newMillisecond);
}



bool DateTime::isInDaylightSavingsTime() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	const bool result = ucal_inDaylightTime(static_cast<const UCalendar*>(calendar), &errorCode) == TRUE;
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return result;
}



int DateTime::getDaylightSavingsMinutes() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	const int result = round<int>(ucal_getDSTSavings(timeZone.getChar16CString(), &errorCode) / 60000.0f);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return result;
}



int DateTime::getActualWeekOfMonthMaximum() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	const int result = ucal_getLimit(static_cast<const UCalendar*>(calendar), UCAL_WEEK_OF_MONTH, UCAL_ACTUAL_MAXIMUM, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return result;
}



int DateTime::getActualDayOfMonthMaximum() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	const int result = ucal_getLimit(static_cast<const UCalendar*>(calendar), UCAL_DAY_OF_MONTH, UCAL_ACTUAL_MAXIMUM, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return result;
}



int DateTime::getActualDayOfYearMaximum() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	const int result = ucal_getLimit(static_cast<const UCalendar*>(calendar), UCAL_DAY_OF_YEAR, UCAL_ACTUAL_MAXIMUM, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return result;
}



void DateTime::addYears(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_add(static_cast<UCalendar*>(calendar), UCAL_YEAR, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::addMonths(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_add(static_cast<UCalendar*>(calendar), UCAL_MONTH, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::addWeeks(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_add(static_cast<UCalendar*>(calendar), UCAL_WEEK_OF_MONTH, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::addDays(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_add(static_cast<UCalendar*>(calendar), UCAL_DAY_OF_MONTH, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::addHours(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_add(static_cast<UCalendar*>(calendar), UCAL_HOUR_OF_DAY, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::addMinutes(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_add(static_cast<UCalendar*>(calendar), UCAL_MINUTE, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::addSeconds(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_add(static_cast<UCalendar*>(calendar), UCAL_SECOND, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::addMilliseconds(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_add(static_cast<UCalendar*>(calendar), UCAL_MILLISECOND, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::rollMonths(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_roll(static_cast<UCalendar*>(calendar), UCAL_MONTH, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::rollWeeks(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_roll(static_cast<UCalendar*>(calendar), UCAL_WEEK_OF_MONTH, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::rollDays(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_roll(static_cast<UCalendar*>(calendar), UCAL_DAY_OF_MONTH, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::rollHours(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_roll(static_cast<UCalendar*>(calendar), UCAL_HOUR_OF_DAY, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::rollMinutes(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_roll(static_cast<UCalendar*>(calendar), UCAL_MINUTE, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::rollSeconds(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_roll(static_cast<UCalendar*>(calendar), UCAL_SECOND, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void DateTime::rollMilliseconds(int amount)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	ucal_roll(static_cast<UCalendar*>(calendar), UCAL_MILLISECOND, amount, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



bool DateTime::dateEquals(const DateTime& other) const
{
	return
		getYear() == other.getYear() &&  
		getMonth() == other.getMonth() &&  
		getDayOfMonth() == other.getDayOfMonth();
}



bool DateTime::dayTimeEquals(const DateTime& other, bool compareSeconds, bool compareMilliseconds) const
{
	return
		getHourOfDay() == other.getHourOfDay() &&
		getMinute() == other.getMinute() &&
		(compareSeconds == true ? getSecond() == other.getSecond() : true) &&
		(compareMilliseconds == true ? getMillisecond() == other.getMillisecond() : true);
}



void DateTime::setDate(const DateTime& other)
{
	setYear(other.getYear());
	setMonth(other.getMonth());
	setDayOfMonth(other.getDayOfMonth());
}



void DateTime::setDayTime(const DateTime& other)
{
	setHourOfDay(other.getHourOfDay());
	setMinute(other.getMinute());
	setSecond(other.getSecond());
	setMillisecond(other.getMillisecond());
}



} // namespace System
} // namespace BaseLib



#endif // #ifndef BL_NO_ICU
