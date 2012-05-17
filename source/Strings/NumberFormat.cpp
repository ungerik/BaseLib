/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/NumberFormat.h"
#ifndef BL_NO_ICU



#include "BaseLib/ErrorHandling.h"
#include <unicode/unum.h>



BaseLib::Strings::String getIcuError(UErrorCode errorCode);



namespace BaseLib {
namespace Strings {



using namespace BaseLib::ErrorHandling;



// Moved to BaseLib.cpp:
// AutoPointer<NumberFormat> NumberFormat::defaultNumberFormat;
//const NumberFormat NumberFormat::ENGLISH(false, Locale::ENGLISH);
//const NumberFormat NumberFormat::ENGLISH_SCIENTIFIC(true, Locale::ENGLISH);
//const NumberFormat NumberFormat::LOCALIZED;


void NumberFormat::setDefault(const NumberFormat* newDefault)
{
	if (checkArgumentNotNull(NAME_VALUE(newDefault)) == true)
	{
		defaultNumberFormat = newDefault;
	}
}



BL_DEFINE_REFLECTION_BASE_CLASS(NumberFormat)
{
	registerProperty("scientific", &NumberFormat::isScientific);
	registerProperty("pattern", &NumberFormat::getPattern, &NumberFormat::setPattern);
	registerProperty("grouping", &NumberFormat::isGroupingUsed, &NumberFormat::setGroupingUsed);
	registerProperty("decimalShown", &NumberFormat::isDecimalAlwaysShown, &NumberFormat::setDecimalAlwaysShown);
	registerProperty("minIntegerDigits", &NumberFormat::getMinimalIntegerDigits, &NumberFormat::setMinimalIntegerDigits);
	registerProperty("maxIntegerDigits", &NumberFormat::getMaximalIntegerDigits, &NumberFormat::setMaximalIntegerDigits);
	registerProperty("integerDigits", &NumberFormat::getIntegerDigits, &NumberFormat::setIntegerDigits);
	registerProperty("minFractionDigits", &NumberFormat::getMinimalFractionDigits, &NumberFormat::setMinimalFractionDigits);
	registerProperty("maxFractionDigits", &NumberFormat::getMaximalFractionDigits, &NumberFormat::setMaximalFractionDigits);
	registerProperty("fractionDigits", &NumberFormat::getFractionDigits, &NumberFormat::setFractionDigits);
	registerProperty("width", &NumberFormat::getFormatWidth, &NumberFormat::setFormatWidth);
	registerProperty("paddingPosition", &NumberFormat::getPaddingPosition, &NumberFormat::setPaddingPosition);
	registerProperty("significandDigits", &NumberFormat::areSignificantDigitsUsed, &NumberFormat::setSignificantDigitsUsed);
	registerProperty("minSignificantDigits", &NumberFormat::getMinimalSignificantDigits, &NumberFormat::setMinimalSignificantDigits);
	registerProperty("maxSignificantDigits", &NumberFormat::getMaximalSignificantDigits, &NumberFormat::setMaximalSignificantDigits);
	registerProperty("positivePrefix", &NumberFormat::getPositivePrefix, &NumberFormat::setPositivePrefix);
	registerProperty("positiveSuffix", &NumberFormat::getPositiveSuffix, &NumberFormat::setPositiveSuffix);
	registerProperty("negativePrefix", &NumberFormat::getNegativePrefix, &NumberFormat::setNegativePrefix);
	registerProperty("negativeSuffix", &NumberFormat::getNegativeSuffix, &NumberFormat::setNegativeSuffix);
	registerProperty("paddingCharacter", &NumberFormat::getPaddingCharacterAsString, &NumberFormat::setPaddingCharacter);
}



NumberFormat::NumberFormat(bool useScientific, const String& locale)
	: Object()
	, numberFormat(NULL)
	, scientific(useScientific)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	numberFormat = unum_open(scientific == true ? UNUM_SCIENTIFIC : UNUM_DECIMAL, NULL, 0, locale.getChar8CString(), NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



NumberFormat::NumberFormat(const String& pattern, const String& locale)
	: /*Object()
	, */numberFormat(NULL)
	, scientific(false)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	numberFormat = unum_open(UNUM_PATTERN_DECIMAL, pattern.getChar16Array(), pattern.getLength(), locale.getChar8CString(), NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



NumberFormat::NumberFormat(const char8 * pattern, const String& locale)
	: /*Object()
	, */numberFormat(NULL)
	, scientific(false)
{
	String unicodePattern = pattern;
	UErrorCode errorCode = U_ZERO_ERROR;
	numberFormat = unum_open(UNUM_PATTERN_DECIMAL, unicodePattern.getChar16Array(), unicodePattern.getLength(), locale.getChar8CString(), NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



NumberFormat::NumberFormat(const char16 * pattern, const String& locale)
	: /*Object()
	, */numberFormat(NULL)
	, scientific(false)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	numberFormat = unum_open(UNUM_PATTERN_DECIMAL, pattern, -1, locale.getChar8CString(), NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



NumberFormat::~NumberFormat()
{
	unum_close(static_cast<UNumberFormat*>(numberFormat));
}



bool NumberFormat::isScientific() const
{
	return scientific;
}



String NumberFormat::getPattern() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = unum_toPattern(static_cast<const UNumberFormat*>(numberFormat), FALSE, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
		return Empty();
	}
	return String(buffer, resultLength);
}



void NumberFormat::setPattern(const String& newPattern)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	unum_applyPattern(static_cast<UNumberFormat*>(numberFormat), FALSE, newPattern.getChar16Array(), newPattern.getLength(), NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



bool NumberFormat::isGroupingUsed() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_GROUPING_USED) != NULL;
}



void NumberFormat::setGroupingUsed(bool newGroupingUsed)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_GROUPING_USED, newGroupingUsed);
}



bool NumberFormat::isDecimalAlwaysShown() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_DECIMAL_ALWAYS_SHOWN) != NULL;
}



void NumberFormat::setDecimalAlwaysShown(bool newDecimalAlwaysShown)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_DECIMAL_ALWAYS_SHOWN, newDecimalAlwaysShown);
}



int NumberFormat::getMinimalIntegerDigits() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_MIN_INTEGER_DIGITS);
}



void NumberFormat::setMinimalIntegerDigits(int newMinimalIntegerDigits)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_MIN_INTEGER_DIGITS, newMinimalIntegerDigits);
}



int NumberFormat::getMaximalIntegerDigits() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_MAX_INTEGER_DIGITS);
}



void NumberFormat::setMaximalIntegerDigits(int newMaximalIntegerDigits)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_MAX_INTEGER_DIGITS, newMaximalIntegerDigits);
}



int NumberFormat::getIntegerDigits() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_INTEGER_DIGITS);
}



void NumberFormat::setIntegerDigits(int newIntegerDigits)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_INTEGER_DIGITS, newIntegerDigits);
}



int NumberFormat::getMinimalFractionDigits() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_MIN_FRACTION_DIGITS);
}



void NumberFormat::setMinimalFractionDigits(int newMinimalFractionDigits)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_MIN_FRACTION_DIGITS, newMinimalFractionDigits);
}



int NumberFormat::getMaximalFractionDigits() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_MAX_FRACTION_DIGITS);
}



void NumberFormat::setMaximalFractionDigits(int newMaximalFractionDigits)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_MAX_FRACTION_DIGITS, newMaximalFractionDigits);
}



int NumberFormat::getFractionDigits() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_FRACTION_DIGITS);
}



void NumberFormat::setFractionDigits(int newFractionDigits)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_FRACTION_DIGITS, newFractionDigits);
}



int NumberFormat::getFormatWidth() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_FORMAT_WIDTH);
}



void NumberFormat::setFormatWidth(int newFormatWidth)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_FORMAT_WIDTH, newFormatWidth);
}



int NumberFormat::getPaddingPosition() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_PADDING_POSITION);
}



void NumberFormat::setPaddingPosition(int newPaddingPosition)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_PADDING_POSITION, newPaddingPosition);
}



bool NumberFormat::areSignificantDigitsUsed() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_SIGNIFICANT_DIGITS_USED) != NULL;
}



void NumberFormat::setSignificantDigitsUsed(bool newSignificantDigitsUsed)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_SIGNIFICANT_DIGITS_USED, newSignificantDigitsUsed);
}



int NumberFormat::getMinimalSignificantDigits() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_MIN_SIGNIFICANT_DIGITS);
}



void NumberFormat::setMinimalSignificantDigits(int newMinimalSignificantDigits)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_MIN_SIGNIFICANT_DIGITS, newMinimalSignificantDigits);
}



int NumberFormat::getMaximalSignificantDigits() const
{
	return unum_getAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_MAX_SIGNIFICANT_DIGITS);
}



void NumberFormat::setMaximalSignificantDigits(int newMaximalSignificantDigits)
{
	unum_setAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_MAX_SIGNIFICANT_DIGITS, newMaximalSignificantDigits);
}



String NumberFormat::getPositivePrefix() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = unum_getTextAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_POSITIVE_PREFIX, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



void NumberFormat::setPositivePrefix(const String& newPositivePrefix)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	unum_setTextAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_POSITIVE_PREFIX, newPositivePrefix.getChar16CString(), newPositivePrefix.getLength(), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



String NumberFormat::getPositiveSuffix() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = unum_getTextAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_POSITIVE_SUFFIX, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



void NumberFormat::setPositiveSuffix(const String& newPositiveSuffix)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	unum_setTextAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_POSITIVE_SUFFIX, newPositiveSuffix.getChar16CString(), newPositiveSuffix.getLength(), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



String NumberFormat::getNegativePrefix() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = unum_getTextAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_NEGATIVE_PREFIX, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



void NumberFormat::setNegativePrefix(const String& newNegativePrefix)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	unum_setTextAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_NEGATIVE_PREFIX, newNegativePrefix.getChar16CString(), newNegativePrefix.getLength(), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



String NumberFormat::getNegativeSuffix() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = unum_getTextAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_NEGATIVE_SUFFIX, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



void NumberFormat::setNegativeSuffix(const String& newNegativeSuffix)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	unum_setTextAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_NEGATIVE_SUFFIX, newNegativeSuffix.getChar16CString(), newNegativeSuffix.getLength(), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



char16 NumberFormat::getPaddingCharacter() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[1];
	const int resultLength = unum_getTextAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_PADDING_CHARACTER, buffer, 1, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return buffer[0];
}



void NumberFormat::setPaddingCharacter(char16 newPaddingCharacter)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	unum_setTextAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_PADDING_CHARACTER, &newPaddingCharacter, 1, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



String NumberFormat::getPaddingCharacterAsString() const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = unum_getTextAttribute(static_cast<const UNumberFormat*>(numberFormat), UNUM_PADDING_CHARACTER, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



void NumberFormat::setPaddingCharacter(const String& newPaddingCharacter)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	unum_setTextAttribute(static_cast<UNumberFormat*>(numberFormat), UNUM_PADDING_CHARACTER, newPaddingCharacter.getChar16CString(), newPaddingCharacter.getLength(), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



String NumberFormat::format(bool value, StringEncoding stringEncoding) const
{
	return String(value == true ? "true" : "false", stringEncoding);
}



String NumberFormat::format(uint32 value, StringEncoding stringEncoding) const
{
	UErrorCode errorCode = U_ZERO_ERROR;
	UChar buffer[256];
	const int resultLength = unum_formatInt64(static_cast<const UNumberFormat*>(numberFormat), value, buffer, 256, NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength, stringEncoding);
}



String NumberFormat::format(int32 value, StringEncoding stringEncoding) const
{
	UChar buffer[256];
	UErrorCode errorCode = U_ZERO_ERROR;
	const int resultLength = unum_format(static_cast<const UNumberFormat*>(numberFormat), value, buffer, 256, NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength, stringEncoding);
}



String NumberFormat::format(uint64 value, StringEncoding stringEncoding) const
{
	UChar buffer[256];
	UErrorCode errorCode = U_ZERO_ERROR;
	const int resultLength = unum_formatInt64(static_cast<const UNumberFormat*>(numberFormat), value, buffer, 256, NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength, stringEncoding);
}



String NumberFormat::format(int64 value, StringEncoding stringEncoding) const
{
	UChar buffer[256];
	UErrorCode errorCode = U_ZERO_ERROR;
	const int resultLength = unum_formatInt64(static_cast<const UNumberFormat*>(numberFormat), value, buffer, 256, NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength, stringEncoding);
}



String NumberFormat::format(float value, StringEncoding stringEncoding) const
{
	UChar buffer[256];
	UErrorCode errorCode = U_ZERO_ERROR;
	const int resultLength = unum_formatDouble(static_cast<const UNumberFormat*>(numberFormat), value, buffer, 256, NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength, stringEncoding);
}



String NumberFormat::format(double value, StringEncoding stringEncoding) const
{
	UChar buffer[256];
	UErrorCode errorCode = U_ZERO_ERROR;
	const int resultLength = unum_formatDouble(static_cast<const UNumberFormat*>(numberFormat), value, buffer, 256, NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength, stringEncoding);
}



String NumberFormat::format(long double value, StringEncoding stringEncoding) const
{
	UChar buffer[256];
	UErrorCode errorCode = U_ZERO_ERROR;
	const int resultLength = unum_formatDouble(static_cast<const UNumberFormat*>(numberFormat), value, buffer, 256, NULL, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength, stringEncoding);
}



bool NumberFormat::parseBool(const String& value, int start, int length) const
{
	const String valueString = value.subString(start, length);
	if (valueString.isEmpty() == false)
	{
		return valueString.equalsCaseInsensitive("true") || valueString == "1";
	}
	else
	{
		return false;
	}
}



uint NumberFormat::parseUint(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		uint result = (uint)unum_parseInt64(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse unsigned int from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse unsigned int from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



int NumberFormat::parseInt(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		int result = unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse int from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse int from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



uint8 NumberFormat::parseUint8(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		uint8 result = (uint8)unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse uint8 from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse uint8 from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



int8 NumberFormat::parseInt8(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		int8 result = (int8)unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse int8 from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse int8 from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



uint16 NumberFormat::parseUint16(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		uint16 result = (uint16)unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse uint16 from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse uint16 from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



int16 NumberFormat::parseInt16(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		int16 result = (int16)unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse int16 from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse int16 from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



uint32 NumberFormat::parseUint32(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		uint32 result = (uint32)unum_parseInt64(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse uint32 from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse uint32 from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



int32 NumberFormat::parseInt32(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		int32 result = unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse int32 from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
		argumentError("Can't parse int32 from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



uint64 NumberFormat::parseUint64(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		uint64 result = unum_parseInt64(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse uint64 from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse uint64 from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



int64 NumberFormat::parseInt64(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		int64 result = unum_parseInt64(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse int64 from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse int64 from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



float NumberFormat::parseFloat(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		float result = (float)unum_parseDouble(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse float from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse float from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



double NumberFormat::parseDouble(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		double result = unum_parseDouble(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse double from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse double from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



long double NumberFormat::parseLongDouble(const String& value, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		long double result = unum_parseDouble(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		if (U_SUCCESS(errorCode))
		{
			if (start != end)
			{
				argumentError("Can't parse long double from value '" + value + "' !" + ERROR_AT);
			}
			return result;
		}
		else
		{
			argumentError("Can't parse long double from value '" + value + "' because of error: " + getIcuError(errorCode) + ERROR_AT);
		}
	}
	return 0;
}



bool NumberFormat::tryParse(const String& value, bool& result, int start, int length) const
{
	result = parseBool(value, start, length);
	return true;
}



bool NumberFormat::tryParse(const String& value, uint8& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = (uint8)unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, int8& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = (int8)unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, uint16& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = (uint16)unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, int16& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = (int16)unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, uint32& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = (uint32)unum_parseInt64(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, int32& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = unum_parse(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, uint64& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = unum_parseInt64(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, int64& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = unum_parseInt64(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, float& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = (float)unum_parseDouble(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, double& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = unum_parseDouble(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



bool NumberFormat::tryParse(const String& value, long double& result, int start, int length) const
{
	const int stringLength = value.getLength();
	if (length == String::END) length = value.getLength() - start;	
	if (checkArgumentRange(NAME_VALUE(start), 0, stringLength) == true &&
		checkArgumentRange(NAME_VALUE(length), 0, stringLength - start) == true)
	{
		const int end = start + length;
		UErrorCode errorCode = U_ZERO_ERROR;
		result = unum_parseDouble(static_cast<const UNumberFormat*>(numberFormat), value.getChar16Array(), end, &start, &errorCode);
		return U_SUCCESS(errorCode) && start == end ? true : false;
	}
	else
	{
		return false;
	}
}



} // namespace Strings
} // namespace BaseLib



#endif // #ifndef BL_NO_ICU
