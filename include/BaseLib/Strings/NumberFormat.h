/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Strings_NumberFormat_h
#define BaseLib_Strings_NumberFormat_h



#include "BaseLib/System/Locale.h"
#ifndef BL_NO_ICU



#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace Strings {



using BaseLib::System::Locale;



/**
Formats and parses numbers.

@code
Symbol     Location             Localized?  Meaning  
0          Number               Yes         Digit  
#          Number               Yes         Digit, zero shows as absent  
.          Number               Yes         Decimal separator or monetary decimal separator  
-          Number               Yes         Minus sign  
,          Number               Yes         Grouping separator  
E          Number               Yes         Separates mantissa and exponent in scientific notation. Need not be quoted in prefix or suffix.  
;          Subpattern boundary  Yes         Separates positive and negative subpatterns  
%          Prefix or suffix     Yes         Multiply by 100 and show as percentage  
\u2030     Prefix or suffix     Yes         Multiply by 1000 and show as per mille value  
¤ (\u00A4) Prefix or suffix     No          Currency sign, replaced by currency symbol. If doubled, replaced by international currency symbol. If present in a pattern, the monetary decimal separator is used instead of the decimal separator.  
'          Prefix or suffix     No          Used to quote special characters in a prefix or suffix, for example, "'#'#" formats 123 to "#123". To create a single quote itself, use two in a row: "# o''clock".  
@endcode

Numbers in scientific notation are expressed as the product of a mantissa and a power of ten, for example, 1234 can be expressed as 1.234 x 10^3. The mantissa is often in the range 1.0 <= x="x" <="<" 10.0,="10.0," but="but" it="it" need="need" not="not" be.="be." DecimalFormat can be instructed to format and parse scientific notation only via a pattern; there is currently no factory method that creates a scientific notation format. In a pattern, the exponent character immediately followed by one or more digit characters indicates scientific notation. Example: "0.###E0" formats the number 1234 as "1.234E3". 

The number of digit characters after the exponent character gives the minimum exponent digit count. There is no maximum. Negative exponents are formatted using the localized minus sign, not the prefix and suffix from the pattern. This allows patterns such as "0.###E0 m/s". 
The minimum and maximum number of integer digits are interpreted together: 
If the maximum number of integer digits is greater than their minimum number and greater than 1, it forces the exponent to be a multiple of the maximum number of integer digits, and the minimum number of integer digits to be interpreted as 1. The most common use of this is to generate engineering notation, in which the exponent is a multiple of three, e.g., "##0.#####E0". Using this pattern, the number 12345 formats to "12.345E3", and 123456 formats to "123.456E3". 
Otherwise, the minimum number of integer digits is achieved by adjusting the exponent. Example: 0.00123 formatted with "00.###E0" yields "12.3E-4". 
The number of significant digits in the mantissa is the sum of the minimum integer and maximum fraction digits, and is unaffected by the maximum integer digits. For example, 12345 formatted with "##0.##E0" is "12.3E3". To show all digits, set the significant digits count to zero. The number of significant digits does not affect parsing. 
Exponential patterns may not contain grouping separators. 

@see String
*/
class BL_EXPORT NumberFormat : public BaseLib::Reflection::Object {
public:

	inline static const NumberFormat* getDefault()
	{
		return defaultNumberFormat;
	}
	static void setDefault(const NumberFormat* newDefault); // Does not take ownership

	inline static const NumberFormat& getEnglish()
	{
		return ENGLISH;
	}
	inline static const NumberFormat& getEnglishScientific()
	{
		return ENGLISH_SCIENTIFIC;
	}
	inline static const NumberFormat& getLocalized()
	{
		return LOCALIZED;
	}


	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Strings::NumberFormat);

	NumberFormat(bool useScientific = false, const String& locale = Locale::getDefault());
	NumberFormat(const String& pattern, const String& locale = Locale::getDefault());
	NumberFormat(const char8 * pattern, const String& locale = Locale::getDefault());
	NumberFormat(const char16 * pattern, const String& locale = Locale::getDefault());
	~NumberFormat();

	bool isScientific() const;

	String getPattern() const;
	void setPattern(const String& newPattern);

	bool isGroupingUsed() const;
	void setGroupingUsed(bool newGroupingUsed);

	bool isDecimalAlwaysShown() const;
	void setDecimalAlwaysShown(bool newDecimalAlwaysShown);

	int getMinimalIntegerDigits() const;
	void setMinimalIntegerDigits(int newMinimalIntegerDigits);

	int getMaximalIntegerDigits() const;
	void setMaximalIntegerDigits(int newMaximalIntegerDigits);

	int getIntegerDigits() const;
	void setIntegerDigits(int newIntegerDigits);

	int getMinimalFractionDigits() const;
	void setMinimalFractionDigits(int newMinimalFractionDigits);

	int getMaximalFractionDigits() const;
	void setMaximalFractionDigits(int newMaximalFractionDigits);

	int getFractionDigits() const;
	void setFractionDigits(int newFractionDigits);

	int getFormatWidth() const;
	void setFormatWidth(int newFormatWidth);

	int getPaddingPosition() const;
	void setPaddingPosition(int newPaddingPosition);

	bool areSignificantDigitsUsed() const;
	void setSignificantDigitsUsed(bool newSignificantDigitsUsed);

	int getMinimalSignificantDigits() const;
	void setMinimalSignificantDigits(int newMinimalSignificantDigits);

	int getMaximalSignificantDigits() const;
	void setMaximalSignificantDigits(int newMaximalSignificantDigits);

	String getPositivePrefix() const;
	void setPositivePrefix(const String& newPositivePrefix);

	String getPositiveSuffix() const;
	void setPositiveSuffix(const String& newPositiveSuffix);

	String getNegativePrefix() const;
	void setNegativePrefix(const String& newNegativePrefix);

	String getNegativeSuffix() const;
	void setNegativeSuffix(const String& newNegativeSuffix);

	char16 getPaddingCharacter() const;
	void setPaddingCharacter(char16 newPaddingCharacter);
	String getPaddingCharacterAsString() const;
	void setPaddingCharacter(const String& newPaddingCharacter);

	String format(bool value, StringEncoding stringEncoding = String::getDefaultEncoding()) const;
	String format(uint32 value, StringEncoding stringEncoding = String::getDefaultEncoding()) const;
	String format(int32 value, StringEncoding stringEncoding = String::getDefaultEncoding()) const;
	String format(uint64 value, StringEncoding stringEncoding = String::getDefaultEncoding()) const;
	String format(int64 value, StringEncoding stringEncoding = String::getDefaultEncoding()) const;
	String format(float value, StringEncoding stringEncoding = String::getDefaultEncoding()) const;
	String format(double value, StringEncoding stringEncoding = String::getDefaultEncoding()) const;
	String format(long double value, StringEncoding stringEncoding = String::getDefaultEncoding()) const;

	bool parseBool(const String& value, int start = 0, int length = String::END) const;
	uint parseUint(const String& value, int start = 0, int length = String::END) const;
	int parseInt(const String& value, int start = 0, int length = String::END) const;
	uint8 parseUint8(const String& value, int start = 0, int length = String::END) const;
	int8 parseInt8(const String& value, int start = 0, int length = String::END) const;
	uint16 parseUint16(const String& value, int start = 0, int length = String::END) const;
	int16 parseInt16(const String& value, int start = 0, int length = String::END) const;
	uint32 parseUint32(const String& value, int start = 0, int length = String::END) const;
	int32 parseInt32(const String& value, int start = 0, int length = String::END) const;
	uint64 parseUint64(const String& value, int start = 0, int length = String::END) const;
	int64 parseInt64(const String& value, int start = 0, int length = String::END) const;
	float parseFloat(const String& value, int start = 0, int length = String::END) const;
	double parseDouble(const String& value, int start = 0, int length = String::END) const;
	long double parseLongDouble(const String& value, int start = 0, int length = String::END) const;

	bool tryParse(const String& value, bool& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, uint8& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, int8& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, uint16& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, int16& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, uint32& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, int32& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, uint64& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, int64& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, float& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, double& result, int start = 0, int length = String::END) const;
	bool tryParse(const String& value, long double& result, int start = 0, int length = String::END) const;

protected:

	static const NumberFormat LOCALIZED;
	static const NumberFormat ENGLISH;
	static const NumberFormat ENGLISH_SCIENTIFIC;
	static const NumberFormat* defaultNumberFormat;

	void* numberFormat;
	const bool scientific;
};




} // namespace Strings
} // namespace BaseLib



#endif // #ifndef BL_NO_ICU
#endif // #ifndef BaseLib_Strings_NumberFormat_h